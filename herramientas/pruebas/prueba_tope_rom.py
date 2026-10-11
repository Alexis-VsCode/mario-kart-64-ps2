#!/usr/bin/env python3
"""herramientas/ci/tope_rom.py: la ROM crece menos de 256 KiB sobre la base medida.

La base es build/ps2/rom.bin de main medido en F7 (11 292 880 B). Con
base + 256 KiB - 1 bytes pasa; con base + 256 KiB, no.
"""
import os
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "ci"))
import tope_rom  # noqa: E402

GUION = os.path.join(os.path.dirname(__file__), "..", "ci", "tope_rom.py")

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def ejecutar(tamanio, *extra):
    with tempfile.TemporaryDirectory() as tmp:
        rom = os.path.join(tmp, "rom.bin")
        with open(rom, "wb") as f:
            f.truncate(tamanio)
        return subprocess.run([sys.executable, GUION, rom, *extra], capture_output=True, text=True).returncode


def main():
    base = tope_rom.BASE
    limite = base + 256 * 1024
    comprobar(base == 11292880, "la base es la medida en main: %d" % base)
    comprobar(tope_rom.dentro_del_tope(base, base), "la base pasa")
    comprobar(tope_rom.dentro_del_tope(limite - 1, base), "límite - 1 pasa")
    comprobar(not tope_rom.dentro_del_tope(limite, base), "el límite no pasa")
    comprobar(tope_rom.dentro_del_tope(base - 4096, base), "una ROM más pequeña pasa")
    comprobar(ejecutar(limite - 1) == 0, "la orden sale con 0 en límite - 1")
    comprobar(ejecutar(limite) == 1, "la orden sale con 1 en el límite")
    comprobar(ejecutar(1000 + 256 * 1024 - 1, "--base", "1000") == 0, "--base cambia la base (límite - 1)")
    comprobar(ejecutar(1000 + 256 * 1024, "--base", "1000") == 1, "--base cambia la base (límite)")
    sin_rom = subprocess.run([sys.executable, GUION, "/no/existe/rom.bin"], capture_output=True).returncode
    comprobar(sin_rom != 0, "sin la ROM falla")
    print("%d comprobaciones, %d %s" % (comprobaciones, fallos, "fallo" if fallos == 1 else "fallos"))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
