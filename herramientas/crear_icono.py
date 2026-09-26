#!/usr/bin/env python3
"""Crea el icono de la partida en la Memory Card.

    crear_icono.py salida.ico
"""
import struct
import sys

SIZE = 128
FX = 4096


def texel(r, g, b, a=1):
    return (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10) | (a << 15)


# Dos cifras "6" y "4" de 5x7 pixeles.
DIGITS = {
    '6': ["01110", "10000", "10000", "11110", "10001", "10001", "01110"],
    '4': ["00010", "00110", "01010", "10010", "11111", "00010", "00010"],
}


def texture():
    red, white, black = texel(200, 20, 20), texel(250, 250, 250), texel(20, 20, 20)
    img = [[red] * SIZE for _ in range(SIZE)]
    # Bandera a cuadros en la mitad superior
    for y in range(12, 68):
        for x in range(16, 112):
            img[y][x] = white if ((x - 16) // 12 + (y - 12) // 14) % 2 == 0 else black
    # Asta
    for y in range(12, 120):
        for x in range(10, 16):
            img[y][x] = white
    # "64" en la mitad inferior, escalado x5
    for i, ch in enumerate("64"):
        for row, bits in enumerate(DIGITS[ch]):
            for col, bit in enumerate(bits):
                if bit == '1':
                    for yy in range(5):
                        for xx in range(5):
                            y = 76 + row * 5 + yy - 4
                            x = 38 + i * 32 + col * 5 + xx
                            if 0 <= y < SIZE:
                                img[y][x] = white
    return b''.join(struct.pack('<H', v) for row in img for v in row)


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    x0, x1, y0, y1 = -1.2, 1.2, -2.6, -0.2
    quad = [((x0, y0), (0.0, 0.0)), ((x1, y0), (1.0, 0.0)), ((x1, y1), (1.0, 1.0)),
            ((x0, y0), (0.0, 0.0)), ((x1, y1), (1.0, 1.0)), ((x0, y1), (0.0, 1.0))]
    verts = []
    for normal_z, tris in ((-1.0, quad), (1.0, [quad[i] for i in (0, 2, 1, 3, 5, 4)])):
        for (x, y), (u, v) in tris:
            verts.append((x, y, u, v, normal_z))

    out = bytearray()
    out += struct.pack('<IIIfI', 0x00010000, 1, 0x07, 1.0, len(verts))
    for x, y, u, v, nz in verts:
        out += struct.pack('<4h', int(x * FX), int(y * FX), 0, 0)
        out += struct.pack('<4h', 0, 0, int(nz * FX), 0)
        out += struct.pack('<2h', int(u * FX), int(v * FX))
        out += struct.pack('<4B', 0x80, 0x80, 0x80, 0x80)
    out += struct.pack('<IIfII', 1, 1, 1.0, 0, 1)
    out += struct.pack('<IIII', 0, 1, 1, 0)
    out += struct.pack('<ff', 1.0, 1.0)
    out += texture()
    with open(sys.argv[1], 'wb') as f:
        f.write(out)


if __name__ == '__main__':
    main()
