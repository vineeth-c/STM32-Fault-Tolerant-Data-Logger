from __future__ import annotations
from dataclasses import dataclass
import struct,zlib
SOF=b"\xA5\x5A"
@dataclass(slots=True)
class Frame:
    version:int=1; message_type:int=1; flags:int=0; sequence:int=0; payload:bytes=b""
    def encode(self)->bytes:
        if len(self.payload)>256: raise ValueError("payload too large")
        h=struct.pack("<BBBBH",self.version,self.message_type,self.flags,self.sequence,len(self.payload))
        body=h+self.payload
        return SOF+body+struct.pack("<I",zlib.crc32(body)&0xffffffff)
    @classmethod
    def decode(cls,data:bytes)->"Frame":
        if len(data)<12 or data[:2]!=SOF: raise ValueError("malformed frame")
        v,t,f,s,n=struct.unpack_from("<BBBBH",data,2)
        if len(data)!=12+n: raise ValueError("length mismatch")
        body=data[2:8+n]
        got=struct.unpack_from("<I",data,8+n)[0]
        if zlib.crc32(body)&0xffffffff!=got: raise ValueError("CRC mismatch")
        return cls(v,t,f,s,data[8:8+n])
