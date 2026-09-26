#!/usr/bin/env python3
"""Parte la ROM en la cabecera (va en el ELF) y SMK64ROM.BIN (se carga del disco).

    partir_rom.py rom.bin <desplazamiento> cabecera.bin SMK64ROM.BIN
"""
import sys

CHUNK = 64 * 1024


def main():
    if len(sys.argv) != 5:
        sys.exit(__doc__)
    rom = open(sys.argv[1], 'rb').read()
    offset = int(sys.argv[2], 0)
    if offset <= 0 or offset > len(rom) or offset % CHUNK:
        sys.exit('partir_rom: desplazamiento %#x invalido (ROM de %#x bytes)' % (offset, len(rom)))
    tail = rom[offset:]
    tail += bytes(-len(tail) % CHUNK)
    with open(sys.argv[3], 'wb') as f:
        f.write(rom[:offset])
    with open(sys.argv[4], 'wb') as f:
        f.write(tail)
    print('  ROM     cabecera %d KB en el ELF, %s %d KB' % (offset // 1024, sys.argv[4].split('/')[-1],
                                                          len(tail) // 1024))


if __name__ == '__main__':
    main()
