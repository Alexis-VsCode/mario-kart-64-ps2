#!/usr/bin/env python3
"""Pruebas del conversor UTF-8 -> EUC-JP del build.

    prueba_convertir_eucjp.py <archivo.c> [<archivo.c> ...]

Recibe los archivos que el Makefile convierte. Para cada uno, el conversor
tiene que dar exactamente los mismos bytes que iconv, que es lo que usaba
el build antes.
"""
import os
import shutil
import subprocess
import sys
import tempfile

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
CONVERSOR = os.path.join(RAIZ, "herramientas", "convertir_eucjp.py")

fallos = 0
comprobaciones = 0


def comprobar(cond, mensaje):
    global fallos, comprobaciones
    comprobaciones += 1
    if not cond:
        fallos += 1
        print("FALLO " + mensaje)


def convertir(origen, destino):
    return subprocess.run([sys.executable, CONVERSOR, origen, destino], capture_output=True, text=True)


def convertir_texto(texto):
    """Convierte un texto suelto; devuelve (codigo, bytes o None, stderr)."""
    with tempfile.TemporaryDirectory() as tmp:
        origen = os.path.join(tmp, "origen.c")
        destino = os.path.join(tmp, "destino.c")
        with open(origen, "wb") as f:
            f.write(texto if isinstance(texto, bytes) else texto.encode("utf-8"))
        r = convertir(origen, destino)
        datos = open(destino, "rb").read() if os.path.exists(destino) else None
        return r.returncode, datos, r.stderr


def probar_igual_que_iconv(archivos):
    """Paso 1: mismos bytes que iconv en todos los archivos del build."""
    comprobar(len(archivos) >= 20, "se esperaban los archivos del build, llegaron %d" % len(archivos))
    if shutil.which("iconv") is None:
        print("AVISO iconv no esta instalado: no se compara contra iconv")
        return
    with tempfile.TemporaryDirectory() as tmp:
        destino = os.path.join(tmp, "salida.c")
        for origen in archivos:
            r = convertir(origen, destino)
            comprobar(r.returncode == 0, "%s: el conversor fallo: %s" % (origen, r.stderr.strip()))
            if r.returncode != 0:
                continue
            referencia = subprocess.run(["iconv", "-f", "UTF-8", "-t", "EUC-JP", origen], capture_output=True)
            comprobar(referencia.returncode == 0, "%s: iconv fallo" % origen)
            comprobar(open(destino, "rb").read() == referencia.stdout, "%s: distinto de iconv" % origen)


def probar_espanol():
    """Paso 2: los caracteres del espanol salen en JIS X 0212 (3 bytes, 0x8F)."""
    esperados = {
        "Á": b"\x8f\xaa\xa1", "É": b"\x8f\xaa\xb1", "Í": b"\x8f\xaa\xbf", "Ó": b"\x8f\xaa\xd1",
        "Ú": b"\x8f\xaa\xe2", "Ñ": b"\x8f\xaa\xd0", "Ü": b"\x8f\xaa\xe4",
        "á": b"\x8f\xab\xa1", "ñ": b"\x8f\xab\xd0", "¡": b"\x8f\xa2\xc2", "¿": b"\x8f\xa2\xc4",
        "º": b"\x8f\xa2\xeb", "ª": b"\x8f\xa2\xec",
    }
    for caracter, bytes_esperados in esperados.items():
        codigo, datos, _ = convertir_texto('"%s"\n' % caracter)
        comprobar(codigo == 0 and datos == b'"' + bytes_esperados + b'"\n',
                  "%s -> %r, se esperaba %r" % (caracter, datos, bytes_esperados))


def probar_formato():
    """Paso 3: los finales de linea y el ASCII no cambian."""
    codigo, datos, _ = convertir_texto("a\r\nb\nc")
    comprobar(codigo == 0 and datos == b"a\r\nb\nc", "finales de linea: %r" % datos)


def probar_rechazos():
    """Paso 4: lo que no se puede convertir corta el build y no deja salida."""
    codigo, datos, error = convertir_texto('int x;\nchar* s = "«HOLA»";\n')
    comprobar(codigo != 0, "un caracter sin EUC-JP tiene que fallar")
    comprobar(":2:" in error, "el error tiene que indicar la linea: %r" % error)
    comprobar(datos is None, "no tiene que quedar un archivo a medias")
    codigo, datos, _ = convertir_texto(b"\xff\xfe")
    comprobar(codigo != 0 and datos is None, "una entrada que no es UTF-8 tiene que fallar")


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    comprobar(os.path.exists(CONVERSOR), "no existe %s" % CONVERSOR)
    if not fallos:
        probar_igual_que_iconv(sys.argv[1:])
        probar_espanol()
        probar_formato()
        probar_rechazos()
    print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
    sys.exit(1 if fallos else 0)


if __name__ == "__main__":
    main()
