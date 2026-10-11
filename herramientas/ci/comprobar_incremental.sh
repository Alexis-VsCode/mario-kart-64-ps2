#!/bin/sh
# R-TEX-08 (D-04): al quitar una sustitución del HUD, el siguiente build
# incremental vuelve a la textura original, y al reponerla vuelve el mismo ELF.
#
# Uso (tras un make de release, con el entorno del SDK cargado):
#     sh herramientas/ci/comprobar_incremental.sh [ruta del .inc.c]
#
# Se quita el PNG de recursos/es/inc/ (la lista que firma ES_SELLO), se
# compila sin make clean y se exige:
#   - que build/ps2/es ya no tenga esa .inc.c;
#   - que la versión de be/ sea la del repositorio invertida, no la española;
#   - que cambie el ELF.
# Después se repone el PNG, se compila otra vez y se exige el ELF del principio.
# El PNG se repone también si algo falla por el camino.
set -eu

RUTA=${1:-recursos/comunes/texturas/vuelta_hud.rgba16.inc.c}
BUILD=build/ps2
PNG=recursos/es/inc/${RUTA%.inc.c}.png
TMP=$(mktemp -d)
ELF=$BUILD/SLUS_999.99
JOBS=$(nproc 2>/dev/null || echo 2)

test -f "$PNG" || { echo "FALLO no existe la sustitución $PNG"; exit 1; }
test -f "$ELF" || { echo "FALLO falta $ELF: compila antes"; exit 1; }

reponer() {
    if [ -f "$TMP/sustitucion.png" ]; then
        mv "$TMP/sustitucion.png" "$PNG"
    fi
    rm -rf "$TMP"
}
trap reponer EXIT

suma() { sha256sum "$1" | cut -d ' ' -f 1; }

ELF_INICIAL=$(suma "$ELF")
BE_ES=$(suma "$BUILD/be/$RUTA")

echo "== quitar $PNG y compilar sin make clean"
mv "$PNG" "$TMP/sustitucion.png"
make -j"$JOBS"

fallos=0
if [ -e "$BUILD/es/$RUTA" ]; then
    echo "FALLO $BUILD/es/$RUTA sigue ahí y tapa a la original"
    fallos=$((fallos + 1))
fi
# Referencia: el repositorio invertido sin superponer nada
python3 herramientas/invertir_texturas.py "$TMP/be" codigo recursos > /dev/null
if ! cmp -s "$TMP/be/$RUTA" "$BUILD/be/$RUTA"; then
    echo "FALLO $BUILD/be/$RUTA no es la textura original invertida"
    fallos=$((fallos + 1))
fi
if [ "$(suma "$BUILD/be/$RUTA")" = "$BE_ES" ]; then
    echo "FALLO $BUILD/be/$RUTA sigue siendo la española"
    fallos=$((fallos + 1))
fi
if [ "$(suma "$ELF")" = "$ELF_INICIAL" ]; then
    echo "FALLO el ELF no cambió al quitar la sustitución"
    fallos=$((fallos + 1))
fi

echo "== reponer $PNG y compilar sin make clean"
mv "$TMP/sustitucion.png" "$PNG"
make -j"$JOBS"
if [ "$(suma "$ELF")" != "$ELF_INICIAL" ]; then
    echo "FALLO con la sustitución repuesta el ELF no es el del principio"
    fallos=$((fallos + 1))
fi

if [ "$fallos" -ne 0 ]; then
    echo "build incremental: $fallos $( [ "$fallos" -eq 1 ] && echo fallo || echo fallos )"
    exit 1
fi
echo "build incremental: vuelve la textura original de $RUTA y, al reponerla, el mismo ELF"
