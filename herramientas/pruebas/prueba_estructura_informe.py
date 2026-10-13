#!/usr/bin/env python3
"""La estructura de informe: secciones obligatorias y ninguna nota al pie.

Sin argumentos comprueba README.md y docs/index.html. Con el argumento
'pagina' solo mira docs/index.html (para la rama que no toca el README).
Exige los encabezados «Qué comprobé y cómo», «Patrones y prácticas que
apliqué» y «Mi trayectoria en este proyecto», y rechaza las notas al pie:
[^n], <sup> de nota, id="n1" y la sección «Notas».
"""
import glob
import os
import re
import sys

RAIZ = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
SECCIONES = ["Qué comprobé y cómo", "Patrones y prácticas que apliqué", "Mi trayectoria en este proyecto"]
comprobaciones = 0
fallos = 0


def comprobar(condicion, mensaje):
    global comprobaciones, fallos
    comprobaciones += 1
    if not condicion:
        fallos += 1
        print("FALLO: " + mensaje)


def leer(ruta):
    with open(os.path.join(RAIZ, ruta), encoding="utf-8") as f:
        return f.read()


solo_pagina = "pagina" in sys.argv[1:]

pagina = leer("docs/index.html")
for s in SECCIONES:
    m = re.search(r"<h2[^>]*>(?:<b>\d+</b>)?\s*" + re.escape(s) + r"\s*</h2>", pagina)
    comprobar(m is not None, "docs/index.html no tiene la sección numerada «%s»" % s)
comprobar(len(re.findall(r"<h2[^>]*><b>\d+</b>", pagina)) >= 8, "la página debe numerar sus secciones")
comprobar("<sup" not in pagina, "docs/index.html tiene un <sup> de nota")
comprobar('id="n1"' not in pagina, 'docs/index.html tiene id="n1"')
comprobar(not re.search(r"class=\"notas\"|<h2[^>]*>(?:<b>\d+</b>)?\s*Notas\s*</h2>", pagina),
          "docs/index.html tiene una sección Notas")

if not solo_pagina:
    readme = leer("README.md")
    for s in SECCIONES:
        comprobar(re.search(r"^#{2,3}\s+(?:\d+\.\s+)?" + re.escape(s) + r"\s*$", readme, re.M) is not None,
                  "README.md no tiene el encabezado «%s»" % s)
    comprobar(not re.search(r"^#{2,3}\s+Notas\s*$", readme, re.M), "README.md tiene una sección Notas")

archivos = ["README.md"] if not solo_pagina else []
archivos += [os.path.relpath(p, RAIZ) for p in sorted(glob.glob(os.path.join(RAIZ, "docs", "**", "*.md"), recursive=True))]
for a in archivos:
    texto = re.sub(r"`[^`\n]*`", "", leer(a))  # un [^n] citado en código no es una nota
    comprobar(not re.search(r"\[\^\w+\]", texto), "%s tiene una nota al pie [^n]" % a)

print("%d comprobaciones, %d fallos" % (comprobaciones, fallos))
sys.exit(1 if fallos else 0)
