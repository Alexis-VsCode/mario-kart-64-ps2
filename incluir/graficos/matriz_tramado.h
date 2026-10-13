#ifndef GRAFICOS_MATRIZ_TRAMADO_H
#define GRAFICOS_MATRIZ_TRAMADO_H

#include <stdint.h>

// Matriz de tramado del GS (registro DIMX). gsKit_init_global_custom copia la
// suya con «for (i = 0; i < 15; i++)» sobre una estructura puesta a cero con
// calloc, así que la celda 15 queda en 0 y no en la que le toca (el gsKit fijado
// escribe {4,2,5,3,0,6,1,7,5,3,4,2,1,7,0,6} en celdas de 3 bits: -4,2,-3,3,0,
// -2,1,-1,-3,3,-4,2,1,-1,0 y un 0 en vez de -2). El port escribe su propio DIMX
// al empezar cada paquete con la matriz de tramado del RDP de la N64.
//
// Matriz «mágica» del RDP (valores 0 a 7 que se suman al color de 8 bits antes
// de truncar a 5). La celda del GS es un entero con signo de 3 bits (-4 a 3) que
// se suma igual, así que se resta 4: la misma disposición con el rango centrado.
// Es la fila-mayor de 4x4: la celda i es la fila i/4 y la columna i%4.

static inline int matriz_tramado_celda_gs(int indice)
{
    static const int8_t magica_rdp[16] = { 0, 6, 1, 7, 4, 2, 5, 3, 3, 5, 2, 4, 7, 1, 6, 0 };

    return magica_rdp[indice & 15] - 4;
}

// DIMX con las primeras n celdas (0 a 16) escritas y el resto en 0: n = 15
// reproduce el defecto de gsKit. Cada celda ocupa 4 bits, la celda i en los
// bits 4i a 4i+2 (DM00 en 0-2, DM01 en 4-6, ... DM33 en 60-62).
static inline uint64_t matriz_tramado_dimx_con_celdas(int n)
{
    uint64_t dimx = 0;
    int i;

    for (i = 0; i < n && i < 16; i++) {
        dimx |= (uint64_t) ((unsigned) matriz_tramado_celda_gs(i) & 7u) << (4 * i);
    }
    return dimx;
}

static inline uint64_t matriz_tramado_dimx(void)
{
    return matriz_tramado_dimx_con_celdas(16);
}

#endif
