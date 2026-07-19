# Production-Grade STM32 Fault-Tolerant Data Logger

A register-level STM32F103C8T6 firmware project focused on bounded asynchronous execution, deterministic scheduling, persistent logging, diagnostics, watchdog supervision, firmware lifecycle, and automated verification.

**Previous project:** [STM32 Bare-Metal Sensor Monitor](https://github.com/vineeth-c/baremetal_sensor_monitor)

**Foundation project:** [STM32 Bare-Metal Sensor Monitor](https://github.com/vineeth-c/baremetal_sensor_monitor)

## Project lineage

This project is the production-oriented successor to [STM32 Bare-Metal Sensor Monitor](https://github.com/vineeth-c/baremetal_sensor_monitor).

The earlier project focuses on register-level peripheral control and bare-metal STM32 fundamentals. This repository builds on those foundations and focuses on asynchronous drivers, fault recovery, deterministic scheduling, persistent storage, watchdog supervision, firmware updates, automated testing, and production-style engineering practices.

The first project remains a focused foundation project with a different engineering objective; it is not obsolete or inferior. Detailed attribution is in [docs/project-lineage.md](docs/project-lineage.md).

## Implemented foundation

- Cortex-M3 startup and separate 16 KiB bootloader / 48 KiB application linker maps
- Bounded ring buffer and event queue
- Wraparound-safe time helpers and cooperative scheduler
- Asynchronous UART buffering and bounded I2C/SPI transaction queues
- Versioned CRC32 binary protocol with incremental resynchronizing parser
- Power-failure-aware committed circular-record foundation
- Firmware image validation and host package generation
- Health-window watchdog gating model
- Host C unit tests with ASan/UBSan
- Python protocol package and CLI
- GitHub Actions build, test, analysis, size, and package workflow

## Build

```bash
make test
make firmware
make bootloader
make size
make package
```

ARM firmware builds require `arm-none-eabi-gcc`. Host tests require GCC or Clang. Python tests require Python 3.11+ and `pytest`.

```bash
python -m pip install -e 'tools/device_cli[dev]'
make python-test
```

## Flash

```bash
st-flash write build/bootloader.bin 0x08000000
st-flash write build/application.bin 0x08004000
```

## Hardware connections

- USART1: PA9 TX, PA10 RX, 115200 8N1
- I2C1 TMP102: PB6 SCL, PB7 SDA, 3.3 V pull-ups
- SPI1 storage: PA5 SCK, PA6 MISO, PA7 MOSI; chip select configured by BSP
- SWD: PA13 SWDIO, PA14 SWCLK

## Important status

Host-testable infrastructure is implemented and tested. Register-level hardware engines, complete fault-frame capture, production EEPROM media integration, and full firmware installation flows require board-specific completion and physical HIL validation. No hardware-validation claim is made.

## First repository cross-link
```markdown
Continued development: [STM32 Fault-Tolerant Data Logger](https://github.com/vineeth-c/STM32-Fault-Tolerant-Data-Logger)
```
