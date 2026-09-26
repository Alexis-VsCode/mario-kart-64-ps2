#ifndef DEPURACION_ESTADISTICAS_MEMORIA_H
#define DEPURACION_ESTADISTICAS_MEMORIA_H

#include <tamtypes.h>

typedef struct {
    u32 monton_libre;       /* newlib: lo que aun puede dar malloc, en bytes */
    u32 pool_juego_libre;    /* pool del juego (siguiente_libre_memoria_direccion..ptr_fin_monton) */
    u32 audio_usado;        /* montón de audio: pools de init + sesion ocupados */
    u32 audio_total;
    u32 texturas_entradas;  /* entradas validas en la cache de texturas */
    u32 texturas_bytes;     /* VRAM que ocupan esas entradas */
    u32 texturas_capacidad; /* tamano del anillo de texturas en VRAM */
} EstadisticasMemoria;

void consultar_memoria(EstadisticasMemoria *e);

#endif
