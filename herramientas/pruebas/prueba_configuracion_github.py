#!/usr/bin/env python3
"""La configuración de GitHub está completa y sin menciones prohibidas.

Comprueba plantillas de incidencias y de PR, SECURITY.md, CODEOWNERS y la
imagen social (1280x640, menos de 1 MB).
"""
import os
import re
import struct
import sys

import yaml

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
comprobaciones = 0
fallos = 0

AVISOS = "https://github.com/Alexis-VsCode/mario-kart-64-ps2/security/advisories/new"
PLANTILLAS = ["bug.yml", "mejora.yml", "pregunta.yml", "retirada.yml"]
ARCHIVOS = (
    [".github/ISSUE_TEMPLATE/" + p for p in PLANTILLAS]
    + [".github/ISSUE_TEMPLATE/config.yml", ".github/pull_request_template.md",
       "SECURITY.md", ".github/CODEOWNERS", "docs/img/social.png"]
)
PROHIBIDO = re.compile(r"\b(claude|anthropic|chatgpt|copilot|openai|gpt|ia|inteligencia artificial)\b",
                       re.IGNORECASE)


def comprobar(condicion, mensaje):
    global comprobaciones, fallos
    comprobaciones += 1
    if not condicion:
        fallos += 1
        print("FALLO: " + mensaje)


def leer(ruta):
    try:
        with open(os.path.join(RAIZ, ruta), encoding="utf-8") as f:
            return f.read()
    except OSError:
        return None


for ruta in ARCHIVOS:
    comprobar(os.path.isfile(os.path.join(RAIZ, ruta)), "falta " + ruta)

for p in PLANTILLAS:
    texto = leer(".github/ISSUE_TEMPLATE/" + p)
    try:
        datos = yaml.safe_load(texto) if texto is not None else None
    except yaml.YAMLError:
        datos = None
    comprobar(isinstance(datos, dict), p + " no es YAML válido")
    if isinstance(datos, dict):
        for clave in ("name", "description", "body"):
            comprobar(bool(datos.get(clave)), p + " no tiene " + clave)

texto = leer(".github/ISSUE_TEMPLATE/config.yml")
try:
    datos = yaml.safe_load(texto) if texto is not None else None
except yaml.YAMLError:
    datos = None
comprobar(isinstance(datos, dict), "config.yml no es YAML válido")

texto = leer(".github/CODEOWNERS") or ""
comprobar(re.search(r"^\*\s+@Alexis-VsCode\s*$", texto, re.MULTILINE) is not None,
          "CODEOWNERS no asigna * a @Alexis-VsCode")

texto = leer("SECURITY.md") or ""
comprobar(AVISOS in texto, "SECURITY.md no enlaza los avisos privados")
comprobar("1.3" in texto and "soporte" in texto.lower(),
          "SECURITY.md no dice qué versiones tienen soporte")

texto = leer(".github/pull_request_template.md") or ""
comprobar(texto.count("- [ ]") >= 4, "la plantilla de PR no lleva lista de comprobación")
for pieza in ("make test", "comprobar_lineas", "CC-", "trailers"):
    comprobar(pieza in texto, "la plantilla de PR no menciona " + pieza)

for ruta in ARCHIVOS:
    if ruta.endswith(".png"):
        continue
    t = leer(ruta) or ""
    comprobar(PROHIBIDO.search(t) is None, ruta + " menciona IA")
    comprobar(re.search(r"universidad|empresa|empleador|instituci", t, re.IGNORECASE) is None,
              ruta + " menciona empleador o institución")
    comprobar("[^" not in t, ruta + " lleva notas al pie")

try:
    with open(os.path.join(RAIZ, "docs/img/social.png"), "rb") as f:
        datos = f.read()
    ancho, alto = struct.unpack(">II", datos[16:24])
    comprobar((ancho, alto) == (1280, 640), "social.png mide %dx%d" % (ancho, alto))
    comprobar(len(datos) < 1000000, "social.png pesa 1 MB o más")
except (OSError, struct.error):
    comprobar(False, "social.png no se puede leer")

print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
sys.exit(1 if fallos else 0)
