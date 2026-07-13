# Storage Format

Records use explicit fields: magic, sequence, timestamp, version, payload length, payload CRC32, header CRC32, commit marker, then payload. Integers are little-endian on media. The commit marker is written last. Startup scanning stops at the first invalid or uncommitted record. Production media ports must split writes according to page geometry and verify power-failure behavior after each write stage.
