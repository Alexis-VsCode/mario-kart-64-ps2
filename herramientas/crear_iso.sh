#!/bin/sh
set -eu

ID=SLUS_999.99
VOLUME=SMK64_PS2
ELF=${1:-build/ps2/$ID}
ISO=${2:-compilaciones/SLUS_999.99.SuperMarioKart64.iso}
STAGE=${ISO_CONTENIDO:-compilaciones/disco/contenido}
OPLDIR=${ISO_OPL:-compilaciones/disco/OPL/CD}
OPLNAME=${ISO_NOMBRE_OPL:-$ID.SuperMarioKart64.iso}

if [ ! -f "$ELF" ]; then
    echo "make_iso: no existe $ELF (ejecuta 'make' antes)" >&2
    exit 1
fi
command -v genisoimage >/dev/null 2>&1 || {
    echo "make_iso: falta genisoimage (apt install genisoimage)" >&2
    exit 1
}

if [ -z "${SOURCE_DATE_EPOCH:-}" ]; then
    SOURCE_DATE_EPOCH=$(git log -1 --format=%ct 2>/dev/null || echo 0)
fi
export SOURCE_DATE_EPOCH

rm -rf "$STAGE"
mkdir -p "$STAGE" "$(dirname "$ISO")" "$OPLDIR"

# ELF y SYSTEM.CNF (arranque desde el disco)
cp "$ELF" "$STAGE/$ID"
printf 'BOOT2 = cdrom0:\\%s;1\r\nVER = 1.00\r\nVMODE = NTSC\r\n' "$ID" > "$STAGE/SYSTEM.CNF"
touch -d "@$SOURCE_DATE_EPOCH" "$STAGE/SYSTEM.CNF" "$STAGE/$ID"
if [ -n "${ISO_ROM:-}" ]; then
    [ -f "$ISO_ROM" ] || { echo "make_iso: no existe $ISO_ROM" >&2; exit 1; }
    cp "$ISO_ROM" "$STAGE/SMK64ROM.BIN"
    touch -d "@$SOURCE_DATE_EPOCH" "$STAGE/SMK64ROM.BIN"
fi
touch -d "@$SOURCE_DATE_EPOCH" "$STAGE"

genisoimage -quiet -iso-level 1 -input-charset iso8859-1 \
    -sysid PLAYSTATION -A PLAYSTATION -V "$VOLUME" -p SMK64 -publisher SMK64 \
    -sort /dev/null -o "$ISO" "$STAGE"

python3 - "$ISO" "$SOURCE_DATE_EPOCH" <<'EOF'
import sys, time
iso, epoch = sys.argv[1], int(sys.argv[2])
t = time.gmtime(epoch)
stamp = time.strftime('%Y%m%d%H%M%S', t).encode() + b'00' + bytes([0])
pvd = 16 * 2048
with open(iso, 'r+b') as f:
    f.seek(pvd)
    if f.read(6) != b'\x01CD001':
        sys.exit('make_iso: descriptor primario no encontrado')
    for off in (813, 830):          # creacion, modificacion
        f.seek(pvd + off); f.write(stamp)
    for off in (847, 864):          # expiracion, efectiva: "sin fecha"
        f.seek(pvd + off); f.write(b'0' * 16 + b'\x00')
EOF

cp "$ISO" "$OPLDIR/$OPLNAME"

echo "ISO:        $ISO ($(stat -c %s "$ISO") bytes)"
echo "SHA-256:    $(sha256sum "$ISO" | cut -d' ' -f1)"
echo "Para OPL:   $OPLDIR/$OPLNAME  (copiar la carpeta CD/ a la raiz del USB o del recurso SMB)"
