#!/usr/bin/env python3
"""Las lineas del panel de rendimiento caben en TEXTO_COLUMNAS.

Formatea cada linea de medidor_rendimiento.c con los valores mas anchos
que puede mostrar y cuenta columnas como escribir_linea_5x7: una por
caracter, lleve tilde o no. Lo que pasa de TEXTO_COLUMNAS se corta sin
avisar. La linea MAX se prueba con cada paso del cronometro.
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(__file__))
from prueba_textos_port import RAIZ, fuentes_del_codigo, literales_de  # noqa: E402

PANEL = "codigo/depuracion/medidor_rendimiento.c"
TEXTO = "incluir/depuracion/texto_pantalla.h"
FUENTE = "incluir/depuracion/fuente_5x7.h"

MS = "99.9"  # decimas() hasta 99.9 ms por cuadro
MS3 = "999"  # decimas_cortas(): 3 columnas hasta 999 ms
# Formato -> valores mas anchos. Topes: 32 MB de RAM del EE, 8 MB de la
# N64, 4 MB de VRAM, 291 KB de monton de audio, porcentajes hasta 100.
PEOR = {
    "FPS %s  MÍN -  MÁX -  PROM -": ("60.00",),
    "FPS %s MÍN %s MÁX %s PROM %s": ("60.00", "60.0", "60.0", "60.0"),
    "CUADRO %s MS  PICO %s  CPU %u%%": ("999.9", "9999.9", 100),
    "MS/C REND %s AUD %s GS %s DMA %s": (MS, MS, MS, MS),
    "CPU%% VIDEO %u JUEGO %u AUDIO %u LIBRE %u": (99, 99, 99, 99),
    "DMA %u/C %uKB/C SUBIDAS %u/C %uKB/C": (999, 4096, 999, 4096),
    "TRI %u RECT %u TEX %u %u/%uKB": (99999, 999, 9999, 4096, 4096),
    "LIBRE %uKB RESERVA %uKB AUD %u/%uKB": (32768, 8192, 291, 291),
    "AUDIO CORTES %u COLA MÍN %u MS": (99999, 999),
    "OTROS HILOS %u%%  ROM EN RAM %u%%": (100, 100),
    "ARRANQUE %s MS  CARGA PISTA %s MS": ("99999", "99999"),
    "MÁX %u MS %s": None,  # con cada paso del cronometro
    "MÁX -": (),
    "VÉRT %s TRI %s TEX %s EST %s ENV %s": (MS3, MS3, MS3, MS3, MS3),
    "MIDIENDO...": (),
}
LLAMADA = re.compile(r'(?:snprintf\(linea,\s*sizeof\(linea\),|texto_escribir_linea\(&texto,\s*\d+,)\s*"([^"]*)"')

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def definicion(ruta, nombre):
    with open(os.path.join(RAIZ, ruta), encoding="utf-8") as f:
        return re.search(r"#define\s+%s\s+([^/\n]+)" % nombre, f.read()).group(1).strip()


def columnas_panel():
    ancho = int(definicion(TEXTO, "TEXTO_ANCHO_TEXTURA"))
    return ancho // int(definicion(FUENTE, "FUENTE_5X7_AVANCE"))


def pasos_cronometro():
    for ruta in fuentes_del_codigo():
        for _, paso in literales_de(ruta, ("marcar_tiempos_ps2", "MARCAR_TIEMPOS_PS2")):
            yield paso


def main():
    columnas = columnas_panel()
    with open(os.path.join(RAIZ, PANEL), encoding="utf-8") as f:
        formatos = LLAMADA.findall(f.read())
    comprobar(formatos, "%s: no se encontro ninguna linea del panel" % PANEL)
    pasos = sorted(set(pasos_cronometro()))
    comprobar(pasos, "no se encontro ningun paso del cronometro")
    for formato in formatos:
        if formato not in PEOR:
            comprobar(False, "%s: '%s' no tiene su peor caso en PEOR" % (PANEL, formato))
            continue
        casos = [(99999, p) for p in pasos] if PEOR[formato] is None else [PEOR[formato]]
        for valores in casos:
            linea = formato % valores
            comprobar(len(linea) <= columnas,
                      "%s: '%s' ocupa %d columnas de %d" % (PANEL, linea, len(linea), columnas))
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
