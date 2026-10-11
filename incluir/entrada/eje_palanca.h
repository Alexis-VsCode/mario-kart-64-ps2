#ifndef ENTRADA_EJE_PALANCA_H
#define ENTRADA_EJE_PALANCA_H

#include <PR/ultratypes.h>

#define CENTRO_PALANCA   128
/* Solo absorbe el ruido del stick en reposo: el juego aplica después su propia zona
   muerta de 12 sobre el valor convertido, y la suma de las dos fija dónde empieza el giro. */
#define ZONA_MUERTA_PALANCA 8
#define MAX_PALANCA_N64  80 /* recorrido tipico de un stick de N64 en MK64 */

static inline s8 convertir_eje(u8 crudo)
{
    int v = (int) crudo - CENTRO_PALANCA;
    int sign = (v < 0) ? -1 : 1;

    v *= sign;
    if (v < ZONA_MUERTA_PALANCA) {
        return 0;
    }
    v = (v - ZONA_MUERTA_PALANCA) * MAX_PALANCA_N64 / (127 - ZONA_MUERTA_PALANCA);
    if (v > MAX_PALANCA_N64) {
        v = MAX_PALANCA_N64;
    }
    return (s8) (v * sign);
}

#endif
