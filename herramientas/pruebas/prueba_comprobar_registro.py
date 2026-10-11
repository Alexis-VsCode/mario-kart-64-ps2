#!/usr/bin/env python3
"""herramientas/emulador/comprobar_registro.py con carpetas host: sintéticas.

El job 'emulador' da por buena una ejecución si el registro existe y llegó
al bucle principal, no tiene pánico ni cuelgue, el guion terminó con su
orden 'fin' sin fallos ni capturas perdidas y la línea de región es la del
ROMVER sintético. El registro puede venir partido en smk64_log_NN.txt.
"""
import os
import sys
import tempfile

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "emulador"))
import comprobar_registro as cr  # noqa: E402

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


REGISTRO = ("[     0] consola PAL: la imagen sale en NTSC a 60 Hz; hace falta una TV que acepte 60 Hz\n"
            "[     1] entrando en el bucle principal del juego\n")
GUION = ("[     0 f     0] guion cargado: 3 órdenes\n"
         "[   667 f   301] captura titulo\n"
         "[   730 f   332] FIN DEL GUION (fin): 0 fallos\n")


def carpeta(tmp, nombre, archivos):
    ruta = os.path.join(tmp, nombre)
    os.makedirs(ruta)
    for n, texto in archivos.items():
        with open(os.path.join(ruta, n), "w", encoding="utf-8") as f:
            f.write(texto)
    return ruta


def main():
    with tempfile.TemporaryDirectory() as tmp:
        def errores(nombre, archivos, region="PAL"):
            return cr.comprobar(carpeta(tmp, nombre, archivos), region)

        bueno = {"smk64_log.txt": REGISTRO, "smk64_test.txt": GUION}
        comprobar(errores("bueno", bueno) == [], "una ejecución buena pasa: %r" % errores("bueno2", bueno))

        # Región: cada ROMVER tiene su línea, y las otras no valen
        ntsc = dict(bueno, **{"smk64_log.txt": REGISTRO.replace(
            "consola PAL: la imagen sale en NTSC a 60 Hz; hace falta una TV que acepte 60 Hz", "consola NTSC")})
        comprobar(errores("ntsc", ntsc, "NTSC") == [], "NTSC con su línea pasa")
        comprobar(errores("ntsc_pal", ntsc, "PAL") != [], "NTSC no vale si se espera PAL")
        comprobar(errores("pal_ntsc", bueno, "NTSC") != [], "PAL no vale si se espera NTSC")
        desconocida = dict(bueno, **{"smk64_log.txt": REGISTRO.replace(
            "consola PAL: la imagen sale en NTSC a 60 Hz; hace falta una TV que acepte 60 Hz",
            "región de la consola desconocida")})
        comprobar(errores("desc", desconocida, "desconocida") == [], "desconocida con su línea pasa")
        comprobar(errores("desc_pal", desconocida, "PAL") != [], "desconocida no vale si se espera PAL")

        # El registro partido: la región está en la primera parte
        partido = {"smk64_log_00.txt": REGISTRO, "smk64_log.txt": "[  9000] cuadro 3001\n", "smk64_test.txt": GUION}
        comprobar(errores("partido", partido) == [], "registro partido pasa")
        comprobar(errores("sin_registro", {"smk64_test.txt": GUION}) != [], "sin registro falla")
        comprobar(errores("sin_bucle", dict(bueno, **{"smk64_log.txt": REGISTRO.splitlines(True)[0]})) != [],
                  "sin llegar al bucle principal falla")

        # Pánico o cuelgue en cualquier parte del registro
        comprobar(errores("panico", dict(partido, **{"smk64_log.txt": "[  9000] PÁNICO: TLB\n"})) != [],
                  "pánico en la última parte falla")
        comprobar(errores("cuelgue", dict(bueno, **{"smk64_log.txt": REGISTRO + "[ 900] sin cuadros en 5 s: cuelgue\n"}))
                  != [], "cuelgue falla")

        # Guion: falta, no terminó, con fallos, abortado o con una captura perdida
        comprobar(errores("sin_guion", {"smk64_log.txt": REGISTRO}) != [], "sin smk64_test.txt falla")
        comprobar(errores("sin_fin", dict(bueno, **{"smk64_test.txt": GUION.splitlines(True)[0]})) != [],
                  "guion sin terminar falla")
        comprobar(errores("con_fallos", dict(bueno, **{"smk64_test.txt": GUION.replace(": 0 fallos", ": 1 fallos")}))
                  != [], "guion con un fallo falla")
        comprobar(errores("abortado", dict(bueno, **{"smk64_test.txt": GUION.replace("(fin)", "(abortado)")})) != [],
                  "guion abortado falla")
        comprobar(errores("perdida", dict(bueno, **{"smk64_test.txt": GUION.replace(
            "captura titulo\n", "captura titulo\n[ 900 f 400] aviso: nadie hizo la captura titulo\n")})) != [],
            "captura perdida falla")

    print("%d comprobaciones, %d %s" % (comprobaciones, fallos, "fallo" if fallos == 1 else "fallos"))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
