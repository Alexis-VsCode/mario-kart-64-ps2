#!/usr/bin/env python3
"""Comprueba que la fuente de libdebug tiene las letras del español en CP437 (D-07).

Uso: inspeccionar_fuente_libdebug.py [libdebug.a | objeto.o]
     (por defecto $PS2SDK/ee/lib/libdebug.a)

scr_putchar() dibuja el glifo ch de msx[] (ee/debug/src/font.c de ps2sdk):
256 glifos de 8x8, un byte por fila y el bit 7 a la izquierda. La pantalla de
fallo podría escribir con tildes si esos glifos son los de CP437. Se busca el
símbolo msx en el archivo (o en el objeto ELF32 little-endian), se dibujan
los diez glifos y se comparan con los esperados. Sale con 1 si alguno difiere.
"""
import os
import struct
import sys

# Código CP437: (letra, filas de arriba abajo). Revisados a ojo.
ESPERADOS = {
    0xA0: ("á", ("...#....", "..#.....", ".###....", "....#...", ".####...", "#...#...", ".####...", "........")),
    0x82: ("é", ("...#....", "..#.....", ".###....", "#...#...", "#####...", "#.......", ".###....", "........")),
    0xA1: ("í", ("...#....", "..#.....", "........", ".##.....", "..#.....", "..#.....", ".###....", "........")),
    0xA2: ("ó", ("..#.....", ".#......", "........", ".##.....", "#..#....", "#..#....", ".##.....", "........")),
    0xA3: ("ú", ("..#.....", ".#......", "........", "#..#....", "#..#....", "#..#....", ".##.#...", "........")),
    0xA4: ("ñ", (".#.#....", "#.#.....", "........", "#.#.....", "##.#....", "#..#....", "#..#....", "........")),
    0xA5: ("Ñ", ("..#.#...", ".#.#....", "........", "##..#...", "#.#.#...", "#..##...", "#...#...", "........")),
    0x81: ("ü", ("#..#....", "........", "........", "#..#....", "#..#....", "#..#....", ".##.#...", "........")),
    0xA8: ("¿", ("..#.....", "........", "..#.....", ".#......", "#.......", "#...#...", ".###....", "........")),
    0xAD: ("¡", ("..#.....", "........", "........", "..#.....", "..#.....", "..#.....", "..#.....", "........")),
}
SIMBOLO = b"msx"
TAMANIO = 256 * 8


def bytes_de_glifo(filas):
    return bytes(sum(128 >> j for j, c in enumerate(fila) if c == "#") for fila in filas)


def filas_de_glifo(datos):
    return tuple("".join("#" if b & (128 >> j) else "." for j in range(8)) for b in datos)


def simbolo_en_elf(elf, nombre):
    """Bytes del símbolo nombre de un ELF32 little-endian, o None si no lo define."""
    if elf[:4] != b"\x7fELF" or elf[4] != 1 or elf[5] != 1:
        return None
    shoff, = struct.unpack_from("<I", elf, 32)
    shentsize, shnum = struct.unpack_from("<HH", elf, 46)
    secciones = [struct.unpack_from("<10I", elf, shoff + i * shentsize) for i in range(shnum)]
    for sec in secciones:
        if sec[1] != 2:  # SHT_SYMTAB
            continue
        strtab = secciones[sec[6]]
        for k in range(sec[5] // 16):
            st_name, st_value, st_size, _, _, st_shndx = struct.unpack_from("<IIIBBH", elf, sec[4] + k * 16)
            inicio = strtab[4] + st_name
            if elf[inicio:elf.index(b"\x00", inicio)] != nombre or st_shndx == 0 or st_shndx >= len(secciones):
                continue
            datos = secciones[st_shndx]
            return elf[datos[4] + st_value:datos[4] + st_value + st_size]
    return None


def miembros_ar(datos):
    i = 8
    while i + 60 <= len(datos):
        largo = int(datos[i + 48:i + 58].decode().strip())
        yield datos[i + 60:i + 60 + largo]
        i += 60 + largo + (largo % 2)


def fuente_de_archivo(ruta):
    with open(ruta, "rb") as f:
        datos = f.read()
    candidatos = miembros_ar(datos) if datos.startswith(b"!<arch>\n") else [datos]
    for miembro in candidatos:
        fuente = simbolo_en_elf(miembro, SIMBOLO)
        if fuente is not None:
            return fuente
    return None


def glifos_distintos(fuente):
    return [c for c, (_, filas) in sorted(ESPERADOS.items()) if fuente[c * 8:c * 8 + 8] != bytes_de_glifo(filas)]


def main():
    if len(sys.argv) > 2:
        sys.exit(__doc__)
    if len(sys.argv) == 2:
        ruta = sys.argv[1]
    else:
        ruta = os.path.join(os.environ.get("PS2SDK", ""), "ee", "lib", "libdebug.a")
    fuente = fuente_de_archivo(ruta)
    if fuente is None:
        print("FALLO %s no define el símbolo msx" % ruta)
        return 2
    if len(fuente) < TAMANIO:
        print("FALLO msx mide %d B, menos de 256 glifos" % len(fuente))
        return 2
    distintos = glifos_distintos(fuente)
    for codigo, (letra, filas) in sorted(ESPERADOS.items()):
        reales = filas_de_glifo(fuente[codigo * 8:codigo * 8 + 8])
        print("0x%02X %s %s" % (codigo, letra, "bien" if codigo not in distintos else "DISTINTO"))
        for real, esperada in zip(reales, filas):
            print("    %s   %s" % (real, esperada if codigo in distintos else ""))
    if distintos:
        print("FALLO %d de %d glifos no son los de CP437" % (len(distintos), len(ESPERADOS)))
        return 1
    print("la fuente de %s tiene los %d glifos CP437 del español" % (ruta, len(ESPERADOS)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
