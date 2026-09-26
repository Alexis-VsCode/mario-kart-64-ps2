#ifndef DEPURACION_MONITOR_AUDIO_H
#define DEPURACION_MONITOR_AUDIO_H

#include <ultra64.h>

#define PS2_AUDIO_SONIDO_BANCOS 6
#define PS2_AUDIO_SFX_JUGADOR  2 /* jugadores_secuencia[2] toca la secuencia 0 (efectos) */
#define PS2_AUDIO_VOZ_BANCO  2 /* banco de efectos de las voces de los personajes */

typedef struct {
    /* notas del motor (el limite es el del modo de juego: 16-28) */
    u16 activo_notas, max_notas;
    u16 musica_notas, sfx_notas, voz_notas;
    u16 sfx_por_banco[PS2_AUDIO_SONIDO_BANCOS];
    u16 notas_por_jugador[4];
    u8 sec[4];
    u32 vaciados;      /* veces que el anillo de audsrv se vacio con sonido */
    u32 ms_cola;        /* audio en cola ahora */
    u32 max_us_tarea;      /* tarea de audio mas larga en el EE (us) */
    u32 blocks;         /* bloques entregados */
    s16 pico;           /* pico del ultimo bloque */
    u32 steals_nota, drops_nota;
} CopiaAudioPs2;

void ps2_audio_monitor_copia(CopiaAudioPs2 *s);
int ps2_audio_monitor_canal_banco(int indice_canal);
/* Hasta lineas_max lineas de texto (width columnas cada una) */
int ps2_audio_monitor_lineas(char (*lineas_2)[64], int lineas_max);
void ps2_audio_monitor_frame(void);

#endif
