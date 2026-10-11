#!/usr/bin/env python3
"""herramientas/ci/inspeccionar_fuente_libdebug.py con una fuente sintética.

El inspector busca el símbolo msx (256 glifos de 8x8, un byte por fila) en
libdebug.a o en un objeto ELF32 suelto y exige que los códigos CP437 de
á é í ó ú ñ Ñ ü ¿ ¡ tengan los glifos esperados. Aquí la fuente se
arma con los glifos esperados del propio inspector dentro de un .o y de un
.a sintéticos; un solo bit cambiado tiene que dar fallo.
"""
import os
import struct
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "ci"))
import inspeccionar_fuente_libdebug as ifl  # noqa: E402

GUION = os.path.join(os.path.dirname(__file__), "..", "ci", "inspeccionar_fuente_libdebug.py")

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def objeto_elf(datos, simbolo="msx", relleno=b"\xaa" * 24):
    """ELF32 little-endian relocatable con datos en .rodata (tras un relleno) y el símbolo global."""
    rodata = relleno + datos
    strtab = b"\x00" + simbolo.encode() + b"\x00"
    shstrtab = b"\x00.rodata\x00.symtab\x00.strtab\x00.shstrtab\x00"
    nombres = {n: shstrtab.index(n.encode()) for n in (".rodata", ".symtab", ".strtab", ".shstrtab")}
    symtab = b"\x00" * 16 + struct.pack("<IIIBBH", 1, len(relleno), len(datos), 0x11, 0, 1)
    cuerpo = b""
    desplazamientos = []
    for s in (rodata, symtab, strtab, shstrtab):
        desplazamientos.append(52 + len(cuerpo))
        cuerpo += s + b"\x00" * (-len(s) % 4)
    shoff = 52 + len(cuerpo)
    secciones = b"\x00" * 40
    secciones += struct.pack("<10I", nombres[".rodata"], 1, 2, 0, desplazamientos[0], len(rodata), 0, 0, 16, 0)
    secciones += struct.pack("<10I", nombres[".symtab"], 2, 0, 0, desplazamientos[1], len(symtab), 3, 1, 4, 16)
    secciones += struct.pack("<10I", nombres[".strtab"], 3, 0, 0, desplazamientos[2], len(strtab), 0, 0, 1, 0)
    secciones += struct.pack("<10I", nombres[".shstrtab"], 3, 0, 0, desplazamientos[3], len(shstrtab), 0, 0, 1, 0)
    cabecera = b"\x7fELF\x01\x01\x01" + b"\x00" * 9
    cabecera += struct.pack("<HHIIIIIHHHHHH", 1, 8, 1, 0, 0, shoff, 0, 52, 0, 0, 40, 5, 4)
    return cabecera + cuerpo + secciones


def archivo_ar(miembros):
    salida = b"!<arch>\n"
    for nombre, datos in miembros:
        salida += ("%-16s%-12d%-6d%-6d%-8o%-10d" % (nombre + "/", 0, 0, 0, 0o644, len(datos))).encode() + b"`\n"
        salida += datos + (b"\n" if len(datos) % 2 else b"")
    return salida


def fuente_buena():
    fuente = bytearray(2048)
    for codigo, (_, filas) in ifl.ESPERADOS.items():
        fuente[codigo * 8:codigo * 8 + 8] = ifl.bytes_de_glifo(filas)
    return fuente


def ejecutar(ruta):
    return subprocess.run([sys.executable, GUION, ruta], capture_output=True, text=True).returncode


def main():
    buena = fuente_buena()
    comprobar(len(ifl.ESPERADOS) == 10, "diez letras: %d" % len(ifl.ESPERADOS))
    comprobar(sorted(ifl.ESPERADOS) == [0x81, 0x82, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA8, 0xAD],
              "códigos CP437 de ü é á í ó ú ñ Ñ ¿ ¡")
    comprobar(ifl.glifos_distintos(bytes(buena)) == [], "la fuente con los glifos esperados pasa")

    mala = bytearray(buena)
    mala[0xA4 * 8 + 4] ^= 0x01  # un bit de la ñ
    distintos = ifl.glifos_distintos(bytes(mala))
    comprobar(distintos == [0xA4], "un bit cambiado en la ñ: %r" % distintos)

    with tempfile.TemporaryDirectory() as tmp:
        def escribir(nombre, datos):
            ruta = os.path.join(tmp, nombre)
            with open(ruta, "wb") as f:
                f.write(datos)
            return ruta

        obj = escribir("font.o", objeto_elf(bytes(buena)))
        comprobar(ifl.fuente_de_archivo(obj) == bytes(buena), "lee msx de un .o")
        comprobar(ejecutar(obj) == 0, "la orden pasa con el .o bueno")

        otro = objeto_elf(b"\x01" * 64, simbolo="otra")
        lib = escribir("libdebug.a", archivo_ar([("scr_printf.o", otro), ("font.o", objeto_elf(bytes(buena)))]))
        comprobar(ifl.fuente_de_archivo(lib) == bytes(buena), "lee msx del .a aunque no sea el primer miembro")
        comprobar(ejecutar(lib) == 0, "la orden pasa con el .a bueno")

        lib_mala = escribir("libdebug_mala.a", archivo_ar([("font.o", objeto_elf(bytes(mala)))]))
        comprobar(ejecutar(lib_mala) == 1, "la orden falla con la ñ cambiada")
        sin_msx = escribir("sin_msx.a", archivo_ar([("scr_printf.o", otro)]))
        comprobar(ejecutar(sin_msx) != 0, "sin el símbolo msx falla")
        corta = escribir("corta.o", objeto_elf(bytes(buena[:0xB0 * 8])))
        comprobar(ejecutar(corta) != 0, "una fuente de menos de 256 glifos falla")

    print("%d comprobaciones, %d %s" % (comprobaciones, fallos, "fallo" if fallos == 1 else "fallos"))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
