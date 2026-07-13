#!/usr/bin/env python3
from __future__ import annotations
import argparse,struct,zlib
MAGIC=b"FWP1"
def main():
 p=argparse.ArgumentParser();p.add_argument("input");p.add_argument("output");a=p.parse_args();data=open(a.input,"rb").read();hdr=struct.pack("<4sIIII",MAGIC,1,0xF103C8,0x08004000,len(data));open(a.output,"wb").write(hdr+struct.pack("<I",zlib.crc32(data)&0xffffffff)+data)
if __name__=="__main__":main()
