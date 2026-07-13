# Binary Protocol

Frame, little-endian: `A5 5A | version:u8 | type:u8 | flags:u8 | sequence:u8 | length:u16 | payload | crc32:u32`.
CRC covers the header from version through payload. Maximum payload is 256 bytes. The parser consumes one byte at a time, rejects oversized frames, detects CRC errors, and searches for the next start marker.
