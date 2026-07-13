# Testing Strategy

`make test` builds hardware-independent C modules with AddressSanitizer and UndefinedBehaviorSanitizer. `make python-test` tests host protocol handling. `make hil-test PORT=/dev/ttyUSB0` is reserved for physical-board tests and is skipped without `HIL_PORT`.
