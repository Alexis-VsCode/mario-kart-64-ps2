#!/bin/sh
# Compila <base> y el arbol actual desde cero y compara lo que va a la
# consola: el ELF sin simbolos y SMK64ROM.BIN. Un refactor tiene que dar
# los mismos bytes.
#
#   sh herramientas/comparar_binario.sh <ref-base> [variables de make]
#   sh herramientas/comparar_binario.sh origin/main DEBUG=1
set -eu

BASE=${1:?uso: comparar_binario.sh <ref-base> [variables de make]}
shift
TMP=$(mktemp -d)
trap 'git worktree remove --force "$TMP/base" >/dev/null 2>&1 || true; rm -rf "$TMP"' EXIT

# Paso 1: copia limpia de la base
git worktree add --detach "$TMP/base" "$BASE" >/dev/null

# Paso 2: los dos arboles se compilan desde cero (build/ esta versionado)
compilar() {
    (cd "$1" && shift && make clean >/dev/null && make -j"$(nproc)" "$@" >/dev/null)
}
compilar "$TMP/base" "$@"
compilar . "$@"

# Paso 3: comparar los archivos de salida
OBJDIR=$(make -s "$@" print-OBJDIR)
DISTINTOS=0
for archivo in SLUS_999.99 SMK64ROM.BIN; do
    if [ ! -f "$OBJDIR/$archivo" ]; then
        continue
    fi
    if cmp -s "$TMP/base/$OBJDIR/$archivo" "$OBJDIR/$archivo"; then
        echo "igual     $OBJDIR/$archivo"
    else
        echo "DISTINTO  $OBJDIR/$archivo"
        DISTINTOS=1
    fi
done
exit $DISTINTOS
