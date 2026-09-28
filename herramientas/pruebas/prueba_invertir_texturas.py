#!/usr/bin/env python3
"""Pruebas de invertir_texturas.py con --superponer, en carpetas temporales.

    prueba_invertir_texturas.py

Si <superponer>/<ruta del .inc.c> existe se invierte esa version; si se
quita, vuelve la del repo aunque su mtime sea mas viejo que la salida.
"""
import os
import subprocess
import sys
import tempfile
import time

RAIZ = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
SCRIPT = os.path.join(RAIZ, "herramientas", "invertir_texturas.py")

fallos = 0
comprobaciones = 0

TABLA = 'u16 tabla[] = {\n#include "tex/a.rgba16.inc.c"\n};\nu16 otra[] = {\n#include "tex/b.rgba16.inc.c"\n};\n'
ORIGINAL = "0x1234, 0xabcd,\n"
INVERTIDO = "0x3412, 0xcdab,\n"
OVERRIDE = "0x5678, 0x9abc,\n"
OVERRIDE_INVERTIDO = "0x7856, 0xbc9a,\n"


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def escribir(ruta, texto, mtime=None):
    os.makedirs(os.path.dirname(ruta), exist_ok=True)
    with open(ruta, "w") as f:
        f.write(texto)
    if mtime is not None:
        os.utime(ruta, (mtime, mtime))


def leer(ruta):
    return open(ruta).read() if os.path.exists(ruta) else None


def invertir(tmp, *opciones):
    return subprocess.run([sys.executable, SCRIPT] + list(opciones) + ["salida", "codigo"], cwd=tmp,
                          capture_output=True, text=True)


def main():
    with tempfile.TemporaryDirectory() as tmp:
        escribir(os.path.join(tmp, "codigo", "tabla.c"), TABLA)
        escribir(os.path.join(tmp, "tex", "a.rgba16.inc.c"), ORIGINAL, 1000)
        escribir(os.path.join(tmp, "tex", "b.rgba16.inc.c"), "0x0001,\n", 1000)
        salida_a = os.path.join(tmp, "salida", "tex", "a.rgba16.inc.c")
        salida_b = os.path.join(tmp, "salida", "tex", "b.rgba16.inc.c")
        sello = os.path.join(tmp, "sello")
        override = os.path.join(tmp, "es", "tex", "a.rgba16.inc.c")

        r = invertir(tmp, "--stamp", sello)
        comprobar(r.returncode == 0, "sin --superponer fallo: %s" % r.stderr.strip())
        comprobar(leer(salida_a) == INVERTIDO, "sin --superponer: %r" % leer(salida_a))

        escribir(override, OVERRIDE, time.time() + 10)
        os.utime(sello, (1, 1))
        r = invertir(tmp, "--stamp", sello, "--superponer", "es")
        comprobar(r.returncode == 0, "con --superponer fallo: %s" % r.stderr.strip())
        comprobar(leer(salida_a) == OVERRIDE_INVERTIDO, "con override: %r" % leer(salida_a))
        comprobar(leer(salida_b) == "0x0100,\n", "sin override b sigue igual: %r" % leer(salida_b))
        comprobar(os.path.getmtime(sello) > 1, "el sello tiene que renovarse al cambiar una salida")

        # La salida es mas nueva que el original: el mtime solo no la regeneraria
        os.remove(override)
        r = invertir(tmp, "--superponer", "es", "--stamp", sello)
        comprobar(r.returncode == 0, "al quitar el override fallo: %s" % r.stderr.strip())
        comprobar(leer(salida_a) == INVERTIDO, "al quitar el override no vuelve el original: %r" % leer(salida_a))

        # Override mas viejo que la salida (copiado conservando la fecha)
        escribir(override, OVERRIDE, 500)
        r = invertir(tmp, "--superponer", "es", "--stamp", sello)
        comprobar(leer(salida_a) == OVERRIDE_INVERTIDO, "override mas viejo que la salida: %r" % leer(salida_a))

        os.utime(sello, (1, 1))
        invertir(tmp, "--stamp", sello, "--superponer", "es")
        comprobar(os.path.getmtime(sello) == 1, "sin cambios el sello no se toca")

        escribir(override, "0x12, algo,\n")
        r = invertir(tmp, "--superponer", "es")
        comprobar(r.returncode != 0, "un override que no es un array de datos tiene que fallar")
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
