# Project Lineage

Previous repository: https://github.com/vineeth-c/baremetal_sensor_monitor

- Baseline release/tag/commit: unavailable in the current working environment; record before importing code.
- New project start date: 2026-07-12
- Import approach: standalone successor generated without access to the prior repository.
- Git history: not imported because the source repository was unavailable.

| Component | Origin | Changes in this project |
|---|---|---|
| Startup code | Conceptually based on previous project | New minimal vector table prepared for bootloader/application split |
| Linker script | Conceptually based on previous project | Split into 16 KiB bootloader and 48 KiB application maps |
| UART driver | Previous-project capability, independently implemented here | Bounded asynchronous TX/RX ring-buffer interface |
| I2C driver | Previous-project capability, independently implemented here | Queued non-blocking transaction and timeout foundation |
| SPI driver | Previous-project capability, independently implemented here | Queued transfer foundation |
| Sensor application | Previous-project concept | Replaced by service-oriented architecture foundation |
| Persistent logger | New project | Versioned CRC and commit-marker records |
| Bootloader | New project | Separate image and vector-validation path |
| Host CLI | New project | Protocol encoding, serial commands, and tests |

No source file in this generated repository is claimed to have been copied from the previous repository. If code is later imported, preserve its notices and update this document with the exact baseline commit, paths, and refactoring details.

## Architectural differences

The foundation project demonstrates direct peripheral control. This successor separates hardware, reusable middleware, application services, host tooling, tests, and release engineering. It emphasizes bounded queues, explicit failure states, serialized formats, recoverability, and verification.

## Reason for a separate repository

A separate repository keeps the educational register-level demonstration clear while allowing the successor to adopt a different memory map, boot process, protocol, testing strategy, and production-oriented architecture without rewriting the original project’s purpose.
