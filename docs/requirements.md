# Requirements

| ID | Requirement | Verification |
|---|---|---|
| SYS-001 | Firmware shall avoid dynamic allocation. | Review/build |
| SCH-001 | Scheduler time comparisons shall be wraparound-safe. | Unit test |
| COM-001 | Protocol frames shall be versioned and CRC-protected. | Unit/Python tests |
| STO-001 | A record shall be considered valid only after its commit marker is written. | Unit test |
| BLD-001 | Bootloader and application shall use separate linker maps. | Build/map review |
| TST-001 | Hardware-independent modules shall build and run on Linux. | `make test` |
