# Memory Map

| Region | Address | Size |
|---|---:|---:|
| Bootloader | 0x08000000 | 16 KiB |
| Application | 0x08004000 | 48 KiB |
| SRAM | 0x20000000 | 20 KiB |

External SPI EEPROM/flash is used for log storage and update staging in the intended production configuration.
