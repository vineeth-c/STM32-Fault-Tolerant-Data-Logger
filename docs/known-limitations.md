# Known Limitations

- Physical STM32 hardware was not available in the generation environment.
- UART, I2C, SPI, ADC, watchdog, flash programming, and fault capture still need complete register-level BSP integration.
- Persistent log implementation is a host-testable reference core; media page boundaries, wear leveling, redundant metadata, and bounded scan indexing require completion.
- Bootloader validates vectors but does not yet implement staged installation, rollback, or application confirmation.
- CRC32 provides integrity detection, not authenticity.
