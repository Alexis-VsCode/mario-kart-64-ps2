#!/usr/bin/env python3
"""Falla si build/ps2/rom.bin crece 256 KiB o más sobre la base medida.

Uso: tope_rom.py <rom.bin> [--base BYTES]

La base es rom.bin de main medido en la compilación versionada de F7.
"""
import argparse
import os
import sys

BASE = 11292880
TOPE = 256 * 1024


def dentro_del_tope(tamanio, base):
    return tamanio - base < TOPE


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    p.add_argument("rom")
    p.add_argument("--base", type=int, default=BASE)
    args = p.parse_args()
    tamanio = os.path.getsize(args.rom)
    crece = tamanio - args.base
    print("%s: %d B, %+d B sobre la base de %d B (tope: menos de %d B)" % (args.rom, tamanio, crece, args.base, TOPE))
    if not dentro_del_tope(tamanio, args.base):
        print("FALLO la ROM crece %d B, el tope es de menos de %d B" % (crece, TOPE))
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
