#!/usr/bin/env python3
"""Precalcula los caminos 2D del tren y del barco con la aritmetica de la N64.

    generar_caminos_vehiculos.py salida.h
"""
import math
import os
import re
import struct
import sys

PATHS = [
    # (nombre en la tabla, fichero, array)
    ("tren", "recursos/pistas/kalimari_desert/datos_pista.c", "d_circuito_kalimari_desert_camino_tren"),
    ("barco", "recursos/pistas/dks_jungle_parkway/datos_pista.c", "d_circuito_dks_jungle_parkway_camino_ferry"),
]


def f32(x):
    """Redondeo de un double a float (IEEE, al mas cercano)."""
    return struct.unpack("<f", struct.pack("<f", x))[0]


def trunc_s16(x):
    """(s16) de un float: truncado hacia cero; el valor debe caber."""
    v = int(x)  # hacia cero
    if not -32768 <= v <= 32767:
        sys.exit("generar_caminos_vehiculos: %r no cabe en s16" % x)
    return v


def load_points(path, name):
    src = open(path, encoding="utf-8").read()
    start = src.find(name + "[] = {")
    if start < 0:
        sys.exit("generar_caminos_vehiculos: no encuentro %s en %s" % (name, path))
    body = src[start:src.index("};", start)]
    pts = [tuple(int(v, 0) for v in m) for m in re.findall(r"\{\s*(-?\w+),\s*(-?\w+),\s*(-?\w+),\s*(-?\w+)\s*\}", body)]
    for i, p in enumerate(pts):
        if p[0] & 0xFFFF == 0x8000:
            return pts, i - 1
    sys.exit("generar_caminos_vehiculos: %s sin punto final 0x8000" % name)


def generate_2d_path(src, n):
    """El bucle de generate_2d_path, operacion por operacion (sin espejo)."""
    out = []
    spA8 = f32(src[0][0])
    spA0 = f32(src[0][2])
    t6 = 0.0
    for i in range(n):
        p1, p2, p3 = src[i % n], src[(i + 1) % n], src[(i + 2) % n]
        x1, z1, x2, z2, x3, z3 = (f32(v) for v in (p1[0], p1[2], p2[0], p2[2], p3[0], p3[2]))

        def dist(ax, az, bx, bz):
            dx = f32(bx - ax)
            dz = f32(bz - az)
            return f32(math.sqrt(f32(f32(dx * dx) + f32(dz * dz))))

        sp7C = f32(0.05 / f32(dist(x1, z1, x2, z2) + dist(x2, z2, x3, z3)))
        j = 0.0
        while j <= 1.0:
            w1 = f32((1.0 - j) * 0.5 * (1.0 - j))
            w2 = f32(((1.0 - j) * j) + 0.5)
            w3 = f32(j * 0.5 * j)
            t24 = f32(f32(f32(w1 * x1) + f32(w2 * x2)) + f32(w3 * x3))
            t26 = f32(f32(f32(w1 * z1) + f32(w2 * z2)) + f32(w3 * z3))
            dx = f32(t24 - spA8)
            dz = f32(t26 - spA0)
            t6 = f32(t6 + f32(math.sqrt(f32(f32(dx * dx) + f32(dz * dz)))))
            spA8 = t24
            spA0 = t26
            if t6 > 20.0 or (i == 0 and j == 0.0):
                x = trunc_s16(spA8)
                if x == -32768:
                    sys.exit("generar_caminos_vehiculos: x = -32768 no admite espejo")
                out.append((x, trunc_s16(spA0)))
                t6 = 0.0
            j = f32(j + sp7C)
    return out


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    root = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
    lines = [
        "/* Generado por herramientas/generar_caminos_vehiculos.py: no editar. Caminos 2D del",
        " * tren y del barco con la aritmetica de la N64; por camino: n, c, n pares",
        " * (posX, posZ) de origen y c pares (x, z) sin espejo. Termina en 0. */",
    ]
    for label, path, name in PATHS:
        src, n = load_points(os.path.join(root, path), name)
        out = generate_2d_path(src, n)
        lines.append("/* %s: %s, %d puntos -> %d */" % (label, name, n, len(out)))
        lines.append("%d, %d," % (n, len(out)))
        pairs = [(p[0], p[2]) for p in src[:n]] + out
        for k in range(0, len(pairs), 8):
            lines.append(" ".join("%d, %d," % p for p in pairs[k:k + 8]))
    lines.append("0")
    tmp = sys.argv[1] + ".tmp"
    with open(tmp, "w") as f:
        f.write("\n".join(lines) + "\n")
    os.replace(tmp, sys.argv[1])


if __name__ == "__main__":
    main()
