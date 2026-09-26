#ifndef AUDIO_SALIDA_AUDIO_H
#define AUDIO_SALIDA_AUDIO_H

#include <ultra64.h>

typedef struct {
    u32 vaciados; /* el anillo de audsrv se vacio con sonido (corte audible) */
    u32 ms_cola;   /* audio en cola en el ultimo bloque */
    u32 max_us_tarea; /* tarea de audio mas larga en el EE, en us */
    u32 blocks;
    s16 pico;      /* pico del ultimo bloque */
} EstadisticasAudioPs2;

void inicializar_ps2_audio(void);
void obtener_estadisticas_audio_ps2(EstadisticasAudioPs2 *salida);
void ejecutar_tarea_ps2_audio(u64 *lista_cmd, u32 bytes_tamanio);
#ifdef SMK64_DEV
void grabar_salida_audio(const char *nombre, int segundos);
#endif

#endif
