PROJECT:=stm32_fault_tolerant_logger
ARM_CC?=arm-none-eabi-gcc
ARM_OBJCOPY?=arm-none-eabi-objcopy
HOST_CC?=cc
CFLAGS_COMMON=-std=c11 -Wall -Wextra -Werror -Wshadow -Wconversion -Wsign-conversion -Wundef -Wformat=2 -Wstrict-prototypes -Iinclude -Iplatform -Iplatform/scheduler -Imiddleware/crc -Imiddleware/protocol -Imiddleware/persistent_log -Imiddleware/health -Imiddleware/firmware_image -Idrivers/uart_async -Idrivers/i2c_async -Idrivers/spi_async -Iapp/acquisition
ARMFLAGS=$(CFLAGS_COMMON) -mcpu=cortex-m3 -mthumb -ffreestanding -fdata-sections -ffunction-sections -Os
COMMON_SRC=platform/ring_buffer.c platform/event_queue.c platform/scheduler/scheduler.c middleware/crc/crc32.c middleware/protocol/protocol.c middleware/persistent_log/persistent_log.c middleware/health/health.c middleware/firmware_image/firmware_image.c drivers/uart_async/uart_async.c drivers/i2c_async/i2c_async.c drivers/spi_async/spi_async.c
.PHONY: all firmware bootloader test python-test hil-test lint analyze format format-check size package clean
all: test
build:
	mkdir -p build
firmware: build
	$(ARM_CC) $(ARMFLAGS) -Tlinker/application.ld startup/startup_stm32f103.s app/main.c $(COMMON_SRC) -Wl,--gc-sections,-Map=build/application.map -nostartfiles -o build/application.elf
	$(ARM_OBJCOPY) -O binary build/application.elf build/application.bin
	$(ARM_OBJCOPY) -O ihex build/application.elf build/application.hex
bootloader: build
	$(ARM_CC) $(ARMFLAGS) -Tlinker/bootloader.ld startup/startup_stm32f103.s bootloader/main.c -Wl,--gc-sections,-Map=build/bootloader.map -nostartfiles -o build/bootloader.elf
	$(ARM_OBJCOPY) -O binary build/bootloader.elf build/bootloader.bin
	$(ARM_OBJCOPY) -O ihex build/bootloader.elf build/bootloader.hex
test: build
	$(HOST_CC) $(CFLAGS_COMMON) -fsanitize=address,undefined -g tests/unit/test_main.c $(COMMON_SRC) -o build/unit_tests
	./build/unit_tests
python-test:
	PYTHONPATH=tools/device_cli python3 -m pytest -q tools/device_cli/tests
hil-test:
	HIL_PORT=$(PORT) PYTHONPATH=tools/device_cli python3 -m pytest -q tests/hil
lint:
	cppcheck --error-exitcode=1 --enable=warning,performance,portability --suppress=missingIncludeSystem app bootloader drivers middleware platform
	python3 -m ruff check tools/device_cli
analyze: lint
format:
	find app bootloader drivers middleware platform include tests -name '*.[ch]' -print0 | xargs -0 clang-format -i
format-check:
	find app bootloader drivers middleware platform include tests -name '*.[ch]' -print0 | xargs -0 clang-format --dry-run --Werror
size: firmware bootloader
	arm-none-eabi-size build/application.elf build/bootloader.elf | tee build/size-report.txt
package: firmware
	python3 tools/firmware_packager.py build/application.bin build/application.pkg
clean:
	rm -rf build .pytest_cache
