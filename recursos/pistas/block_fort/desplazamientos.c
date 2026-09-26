#include <PR/ultratypes.h>
#include "juego/desplazamientos_pista.h"

extern u8 textura_64286C[];
extern u8 textura_tablero_gris[];
extern u8 textura_adoquin_gris[];
extern u8 textura_64275C[];
extern u8 textura_642978[];
extern u8 textura_6747C4[];
extern u8 textura_6442D4[];

const textura_circuito block_fort_texturas[] = {
    { textura_64286C, 0x010A, 0x0800, 0x0 },          { textura_tablero_gris, 0x010C, 0x0800, 0x0 },
    { textura_adoquin_gris, 0x010C, 0x0800, 0x0 }, { textura_64275C, 0x0110, 0x0800, 0x0 },
    { textura_642978, 0x010D, 0x0800, 0x0 },          { textura_6747C4, 0x0145, 0x0800, 0x0 },
    { textura_6442D4, 0x0138, 0x0800, 0x0 },          { 0x00000000, 0x0000, 0x0000, 0x0 },
};
