from device_cli.protocol import Frame
import pytest
def test_roundtrip():
 f=Frame(message_type=4,sequence=9,payload=b"abc");assert Frame.decode(f.encode())==f
def test_crc_rejected():
 b=bytearray(Frame(payload=b"x").encode());b[-1]^=1
 with pytest.raises(ValueError):Frame.decode(bytes(b))
