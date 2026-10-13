#!/usr/bin/env python3
"""Revisa el registro y el resultado del guion que deja el ELF de DEV en host:.

Uso: comprobar_registro.py <carpeta host> <PAL|NTSC|desconocida> [--exige TEXTO ...]

Pasa si el registro (smk64_log_NN.txt seguidos de smk64_log.txt) llegó al
bucle principal sin pánico ni cuelgue, tiene la línea de región que da el
ROMVER sintético, la línea 'audio: audsrv listo' (sin avisos de libsd,
audsrv_init ni audsrv_set_format), y smk64_test.txt acaba el guion con su
orden 'fin', 0 fallos y ninguna captura perdida. --exige añade líneas que tienen que estar
en el registro (por ejemplo, los valores de los registros de vídeo).
"""
import argparse
import os
import sys

# Marcas de incluir/depuracion/marcas_registro.h y textos de arranque_ps2.c
PANICO = "PÁNICO"
CUELGUE = "cuelgue"
BUCLE = "entrando en el bucle principal del juego"
REGIONES = {
    "PAL": "consola PAL: la imagen sale en NTSC a 60 Hz",
    "NTSC": "consola NTSC",
    "desconocida": "región de la consola desconocida",
}
# Audio (salida_audio.c y arranque_ps2.c): la línea de éxito y los avisos de fallo
AUDIO_LISTO = "audio: audsrv listo, anillo"
AVISOS_AUDIO = ("audsrv_init falló", "audsrv_set_format falló",
                "libsd.irx no quedó cargado", "audsrv.irx no quedó cargado")
FIN_BIEN = "FIN DEL GUION (fin): 0 fallos"
CAPTURA_PERDIDA = "aviso: nadie hizo la captura"


def leer(ruta):
    with open(ruta, encoding="utf-8", errors="replace") as f:
        return f.read()


def registro_completo(host):
    partes = sorted(n for n in os.listdir(host) if n.startswith("smk64_log_") and n.endswith(".txt"))
    if os.path.exists(os.path.join(host, "smk64_log.txt")):
        partes.append("smk64_log.txt")
    return "".join(leer(os.path.join(host, n)) for n in partes) if partes else None


def comprobar(host, region, exige=()):
    """Lista de errores (vacía si la ejecución es buena)."""
    errores = []
    registro = registro_completo(host)
    if not registro:
        errores.append("no hay registro (smk64_log*.txt) en %s" % host)
    else:
        if BUCLE not in registro:
            errores.append("el registro no llega al bucle principal")
        for linea in registro.splitlines():
            if PANICO in linea or CUELGUE in linea:
                errores.append("registro: " + linea)
        if AUDIO_LISTO not in registro:
            errores.append("falta la línea de audio '%s'" % AUDIO_LISTO)
        for linea in registro.splitlines():
            if any(a in linea for a in AVISOS_AUDIO):
                errores.append("registro: " + linea)
        lineas_region = [l for l in registro.splitlines() if any(t in l for t in REGIONES.values())]
        if not any(REGIONES[region] in l for l in lineas_region):
            errores.append("falta la línea de región %s; hay: %r" % (region, lineas_region))
        for texto in exige:
            if texto not in registro:
                errores.append("falta en el registro: %s" % texto)
    ruta = os.path.join(host, "smk64_test.txt")
    if not os.path.exists(ruta):
        errores.append("no hay smk64_test.txt")
    else:
        guion = leer(ruta)
        if FIN_BIEN not in guion:
            fin = [l for l in guion.splitlines() if "FIN DEL GUION" in l]
            errores.append("el guion no terminó bien: %s" % (fin[-1] if fin else "sin FIN DEL GUION"))
        for linea in guion.splitlines():
            if CAPTURA_PERDIDA in linea:
                errores.append("guion: " + linea)
    return errores


def main():
    p = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    p.add_argument("host")
    p.add_argument("region", choices=sorted(REGIONES))
    p.add_argument("--exige", action="append", default=[])
    args = p.parse_args()
    errores = comprobar(args.host, args.region, args.exige)
    for e in errores:
        print("FALLO " + e)
    if not errores:
        print("registro y guion correctos (región %s)" % args.region)
    return 1 if errores else 0


if __name__ == "__main__":
    sys.exit(main())
