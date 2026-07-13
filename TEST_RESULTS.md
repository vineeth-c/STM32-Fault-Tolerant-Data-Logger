# Executed Verification

Environment date: 2026-07-12

## Passed

- `make test` — host C build passed with strict warnings, AddressSanitizer, and UndefinedBehaviorSanitizer; output: `ALL TESTS PASSED`.
- `make python-test` — 2 Python protocol tests passed.

## Not executed

- `make firmware`
- `make bootloader`
- `make size`
- `make package`

The ARM GNU Embedded toolchain (`arm-none-eabi-gcc`) was not installed in the generation environment. These targets are configured in the Makefile and GitHub Actions workflow but were not falsely reported as executed.

## Hardware validation

No STM32F103C8T6 board was connected. HIL tests and register-level peripheral validation remain required.
