#include <PR/ultratypes.h>
#include "juego/desplazamientos_pista.h"

extern u8 textura_contorno_estrella[];
extern u8 textura_67A1B8[];
extern u8 textura_blanco_negro_tablero[];
extern u8 textura_662A34[];
extern u8 textura_rainbow[];

const textura_circuito rainbow_road_texturas[] = {
    { textura_contorno_estrella, 0x037A, 0x0800, 0x0 },
    { textura_67A1B8, 0x01B7, 0x0800, 0x0 },
    { textura_blanco_negro_tablero, 0x0107, 0x0800, 0x0 },
    { textura_662A34, 0x0106, 0x0800, 0x0 },
    { textura_rainbow, 0x025D, 0x1000, 0x0 },
    { 0x00000000, 0x0000, 0x0000, 0x0 },
};
