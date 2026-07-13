from __future__ import annotations
import argparse,sys
from .protocol import Frame

def main()->int:
 p=argparse.ArgumentParser(prog="device_cli")
 p.add_argument("command",choices=["info","health","diagnostics","sample","ping","reboot","enter-bootloader"])
 p.add_argument("--port",default="/dev/ttyUSB0")
 p.add_argument("--baud",type=int,default=115200)
 a=p.parse_args(); types={"ping":1,"info":2,"health":3,"diagnostics":4,"sample":5,"reboot":11,"enter-bootloader":12}
 try:
  import serial
 except ImportError:
  print("pyserial is required; install with pip install -e tools/device_cli",file=sys.stderr);return 2
 with serial.Serial(a.port,a.baud,timeout=1) as s:
  s.write(Frame(message_type=types[a.command]).encode());print(s.read(512).hex())
 return 0
if __name__=="__main__": raise SystemExit(main())
