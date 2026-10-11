#!/bin/sh
# Arranca el ELF de DEV en Play! bajo Xvfb con un guion de host: y lo detiene
# al terminar el guion, al aparecer un pánico o al vencer el tiempo.
#
# Uso: ejecutar_play.sh <Play> <ELF> <carpeta> <guion> <segundos>
#
# <Play> es el binario de la AppImage extraída (squashfs-root/usr/bin/Play).
# <carpeta> se vacía y hace de carpeta de datos de Play! (portable.txt):
# host: es '<carpeta>/Play Data Files/vfs/host', mc0: 'vfs/mc0' y rom0: 'vfs/rom0'.
# rom0:ROMVER es sintético (variable ROMVER; por defecto el de una consola
# europea) para comprobar la línea de región del registro.
# Sale con 0 si el guion llegó a su fin, 1 si no.
set -eu

if [ $# -ne 5 ]; then
    echo "uso: $0 <Play> <ELF> <carpeta> <guion> <segundos>" >&2
    exit 2
fi
PLAY=$(realpath "$1")
ELF=$(realpath "$2")
CARPETA=$3
GUION=$(realpath "$4")
SEGUNDOS=$5
ROMVER=${ROMVER:-0160EC20010704}
CONFIG=$(dirname "$(realpath "$0")")/play_config.xml

rm -rf "$CARPETA"
DATOS="$CARPETA/Play Data Files"
HOST="$DATOS/vfs/host"
mkdir -p "$HOST" "$DATOS/vfs/mc0" "$DATOS/vfs/rom0"
CARPETA=$(realpath "$CARPETA")
DATOS="$CARPETA/Play Data Files"
HOST="$DATOS/vfs/host"
touch "$CARPETA/portable.txt"
# Vulkan con lecturas de la RAM del GS: con OpenGL la captura (GS -> EE) sale vacía
cp "$CONFIG" "$DATOS/config.xml"
cp "$GUION" "$HOST/smk64_input.txt"
printf '%s\0' "$ROMVER" > "$DATOS/vfs/rom0/ROMVER"
# Sin tarjeta de sonido: ALSA a un dispositivo nulo, o Play! aborta al abrir el audio
printf 'pcm.!default { type null }\nctl.!default { type hw card 0 }\n' > "$CARPETA/.asoundrc"

cd "$CARPETA"
inicio=$(date +%s)
HOME="$CARPETA" LC_ALL=C.UTF-8 QT_QPA_PLATFORM=xcb LIBGL_ALWAYS_SOFTWARE=1 \
    xvfb-run -a -s "-screen 0 1024x768x24" "$PLAY" --elf "$ELF" > "$CARPETA/play.log" 2>&1 &
pid=$!

resultado=1
while :; do
    transcurrido=$(( $(date +%s) - inicio ))
    if grep -q "FIN DEL GUION" "$HOST/smk64_test.txt" 2>/dev/null; then
        # El registro se vuelca cada 60 retrazos: se deja que salga el último trozo
        sleep 3
        resultado=0
        echo "guion terminado en ${transcurrido} s"
        break
    fi
    if cat "$HOST"/smk64_log*.txt 2>/dev/null | grep -q "PÁNICO"; then
        sleep 3
        echo "pánico en el registro a los ${transcurrido} s"
        break
    fi
    if ! kill -0 "$pid" 2>/dev/null; then
        echo "Play! terminó solo a los ${transcurrido} s"
        break
    fi
    if [ "$transcurrido" -ge "$SEGUNDOS" ]; then
        echo "tiempo vencido (${SEGUNDOS} s) sin el fin del guion"
        break
    fi
    sleep 2
done

# Play! es nieto de este guion: se busca por su línea de órdenes, que empieza por
# su ruta (la de xvfb-run, no). Muerto Play!, xvfb-run cierra Xvfb.
pkill -KILL -f -- "^$PLAY --elf" 2>/dev/null || true
wait "$pid" 2>/dev/null || true
exit "$resultado"
