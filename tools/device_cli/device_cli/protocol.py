from __future__ import annotations

import struct
import zlib
from dataclasses import dataclass


SOF = b"\xA5\x5A"
MAX_PAYLOAD_SIZE = 256
HEADER_SIZE = 6
CRC_SIZE = 4
MIN_FRAME_SIZE = len(SOF) + HEADER_SIZE + CRC_SIZE


@dataclass(slots=True)
class Frame:
    version: int = 1
    message_type: int = 1
    flags: int = 0
    sequence: int = 0
    payload: bytes = b""

    def encode(self) -> bytes:
        if len(self.payload) > MAX_PAYLOAD_SIZE:
            raise ValueError("payload too large")

        header = struct.pack(
            "<BBBBH",
            self.version,
            self.message_type,
            self.flags,
            self.sequence,
            len(self.payload),
        )
        body = header + self.payload
        checksum = zlib.crc32(body) & 0xFFFFFFFF

        return SOF + body + struct.pack("<I", checksum)

    @classmethod
    def decode(cls, data: bytes) -> Frame:
        if len(data) < MIN_FRAME_SIZE or data[:2] != SOF:
            raise ValueError("malformed frame")

        version, message_type, flags, sequence, payload_length = (
            struct.unpack_from("<BBBBH", data, 2)
        )

        expected_length = MIN_FRAME_SIZE + payload_length
        if len(data) != expected_length:
            raise ValueError("length mismatch")

        body_end = 8 + payload_length
        body = data[2:body_end]
        received_checksum = struct.unpack_from("<I", data, body_end)[0]
        calculated_checksum = zlib.crc32(body) & 0xFFFFFFFF

        if calculated_checksum != received_checksum:
            raise ValueError("CRC mismatch")

        return cls(
            version=version,
            message_type=message_type,
            flags=flags,
            sequence=sequence,
            payload=data[8:body_end],
        )