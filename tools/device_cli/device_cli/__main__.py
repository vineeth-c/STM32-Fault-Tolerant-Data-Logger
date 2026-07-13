from __future__ import annotations

import argparse
import sys

from .protocol import Frame


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "command",
        choices=[
            "ping",
            "info",
            "health",
            "diagnostics",
            "sample",
            "reboot",
            "enter-bootloader",
        ],
    )
    parser.add_argument("--port", default="/dev/ttyUSB0")
    parser.add_argument("--baud", type=int, default=115200)
    args = parser.parse_args()

    message_types = {
        "ping": 1,
        "info": 2,
        "health": 3,
        "diagnostics": 4,
        "sample": 5,
        "reboot": 11,
        "enter-bootloader": 12,
    }

    try:
        import serial
    except ImportError:
        print(
            "pyserial is required; install with "
            "pip install -e tools/device_cli",
            file=sys.stderr,
        )
        return 2

    frame = Frame(message_type=message_types[args.command])

    with serial.Serial(args.port, args.baud, timeout=1) as serial_port:
        serial_port.write(frame.encode())
        print(serial_port.read(512).hex())

    return 0


if __name__ == "__main__":
    raise SystemExit(main())