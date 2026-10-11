#ifndef ENTRADA_EJE_PALANCA_H
#define ENTRADA_EJE_PALANCA_H

#include <PR/ultratypes.h>

#define CENTRO_PALANCA   128
/* Solo absorbe el ruido del stick en reposo: el juego aplica después su propia zona
   muerta de 12 sobre el valor convertido, y la suma de las dos fija dónde empieza el giro. */
#define ZONA_MUERTA_PALANCA 8
#define MAX_PALANCA_N64  80 /* recorrido típico de un stick de N64 en MK64 */

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

/* Mientras el stick izquierdo está en reposo, la cruceta hace de stick. El reposo tiene su
   propio umbral, más ancho que la zona muerta, para que la deriva de un stick gastado no
   anule la cruceta: hasta 25 del centro, donde convertir_eje daba 0 con la zona de 24. */
#define ZONA_REPOSO_CRUCETA 26

static inline int eje_en_reposo(u8 crudo)
{
    int v = (int) crudo - CENTRO_PALANCA;

    return v > -ZONA_REPOSO_CRUCETA && v < ZONA_REPOSO_CRUCETA;
}

/* Si la cruceta hace de stick: siempre sin modo analógico (el mando no da ejes) y, con él,
   solo mientras los dos ejes del stick izquierdo están en reposo. */
static inline int cruceta_manda_stick(int analogico, u8 crudo_h, u8 crudo_v)
{
    return !analogico || (eje_en_reposo(crudo_h) && eje_en_reposo(crudo_v));
}

#endif
