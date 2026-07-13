import pytest

from device_cli.protocol import Frame


def test_roundtrip() -> None:
    frame = Frame(
        message_type=4,
        sequence=9,
        payload=b"abc",
    )

    assert Frame.decode(frame.encode()) == frame


def test_crc_rejected() -> None:
    encoded = bytearray(Frame(payload=b"x").encode())
    encoded[-1] ^= 1

    with pytest.raises(ValueError, match="CRC mismatch"):
        Frame.decode(bytes(encoded))