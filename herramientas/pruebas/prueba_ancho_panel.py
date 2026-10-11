#!/usr/bin/env python3
"""Las líneas del panel de rendimiento caben en TEXTO_COLUMNAS y en la textura.

Formatea cada línea de medidor_rendimiento.c con los valores más anchos
que puede mostrar y cuenta columnas como escribir_linea_5x7: una por
carácter, lleve tilde o no. Lo que pasa de TEXTO_COLUMNAS se corta sin
avisar. La línea MÁX se prueba con cada paso del cronómetro, y cada paso
cabe también en su columna del informe del cronómetro.

En alto, escribir_linea_5x7 pinta FUENTE_5X7_FILAS filas por línea (el
signo y la letra) y cada línea ocupa TEXTO_ALTO_LINEA: tiene que sobrar
al menos una fila para que la tilde no toque la línea de arriba. Las
MEDIDOR_LINEAS líneas caben en TEXTO_ALTO_TEXTURA, que cabe en el alto
que lee el GS, y MEDIDOR_VRAM_BYTES cubre las páginas de la textura.
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(__file__))
from prueba_textos_port import RAIZ, fuentes_del_codigo, literales_de  # noqa: E402

PANEL = "codigo/depuracion/medidor_rendimiento.c"
TEXTO = "incluir/depuracion/texto_pantalla.h"
FUENTE = "incluir/depuracion/fuente_5x7.h"
MEDIDOR = "incluir/depuracion/medidor_rendimiento.h"
CRONOMETRO = "codigo/sistema/cronometro_fases.c"

MS = "99.9"  # decimas() hasta 99.9 ms por cuadro
MS3 = "999"  # decimas_cortas(): 3 columnas hasta 999 ms
# Formato -> valores más anchos. Topes: 32 MB de RAM del EE, 8 MB de la
# N64, 4 MB de VRAM, 291 KB de montón de audio, porcentajes hasta 100.
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
    "MÁX %u MS %s": None,  # con cada paso del cronómetro
    "MÁX -": (),
    "VÉRT %s TRI %s TEX %s EST %s ENV %s": (MS3, MS3, MS3, MS3, MS3),
    "MIDIENDO...": (),
}
# Página de la VRAM del GS: 8 KB, 64x32 píxeles en CT32. Una textura CT32
# ocupa filas de páginas enteras, TBW páginas por fila.
PAGINA_BYTES, PAGINA_ANCHO, PAGINA_ALTO = 8192, 64, 32
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


def valor(ruta, nombre, **macros):
    """Valor entero de un #define aritmetico, con las macros dadas ya resueltas."""
    return int(eval(definicion(ruta, nombre), {"__builtins__": {}}, macros))


def columnas_panel():
    ancho = int(definicion(TEXTO, "TEXTO_ANCHO_TEXTURA"))
    return ancho // int(definicion(FUENTE, "FUENTE_5X7_AVANCE"))


def ancho_paso_informe():
    """Ancho de la columna de pasos del informe ("%-26s")."""
    with open(os.path.join(RAIZ, CRONOMETRO), encoding="utf-8") as f:
        return int(re.search(r'"  %-(\d+)s ', f.read()).group(1))


def pasos_cronometro():
    for ruta in fuentes_del_codigo():
        for _, paso in literales_de(ruta, ("marcar_tiempos_ps2", "MARCAR_TIEMPOS_PS2")):
            yield paso


def probar_alto():
    """Paso entre líneas, alto de la textura y VRAM que reserva el panel."""
    filas_celda = valor(FUENTE, "FUENTE_5X7_FILAS")
    alto_linea = valor(TEXTO, "TEXTO_ALTO_LINEA", FUENTE_5X7_FILAS=filas_celda)
    ancho = valor(TEXTO, "TEXTO_ANCHO_TEXTURA")
    alto = valor(TEXTO, "TEXTO_ALTO_TEXTURA")
    alto_gs = 1 << valor(TEXTO, "TEXTO_ALTO_GS_LOG2")
    lineas = valor(PANEL, "MEDIDOR_LINEAS")
    comprobar(alto_linea > filas_celda,
              "%s: TEXTO_ALTO_LINEA %d no deja fila libre debajo de las %d filas de cada línea: "
              "la tilde toca la línea de arriba" % (TEXTO, alto_linea, filas_celda))
    comprobar(lineas * alto_linea <= alto <= alto_gs,
              "%s: %d líneas de %d filas en una textura de %d filas que el GS lee con %d"
              % (TEXTO, lineas, alto_linea, alto, alto_gs))
    paginas = -(-ancho // PAGINA_ANCHO) * -(-alto // PAGINA_ALTO)
    vram = valor(MEDIDOR, "MEDIDOR_VRAM_BYTES")
    comprobar(vram >= paginas * PAGINA_BYTES,
              "%s: MEDIDOR_VRAM_BYTES %d no cubre las %d páginas (%d bytes) de la textura de %dx%d"
              % (MEDIDOR, vram, paginas, paginas * PAGINA_BYTES, ancho, alto))


def main():
    probar_alto()
    columnas = columnas_panel()
    with open(os.path.join(RAIZ, PANEL), encoding="utf-8") as f:
        formatos = LLAMADA.findall(f.read())
    comprobar(formatos, "%s: no se encontró ninguna línea del panel" % PANEL)
    pasos = sorted(set(pasos_cronometro()))
    comprobar(pasos, "no se encontró ningún paso del cronómetro")
    ancho_paso = ancho_paso_informe()
    for paso in pasos:
        comprobar(len(paso) <= ancho_paso, "%s: el paso '%s' ocupa %d columnas de %d en el informe"
                  % (CRONOMETRO, paso, len(paso), ancho_paso))
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
