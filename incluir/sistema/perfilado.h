#ifndef SISTEMA_PERFILADO_H
#define SISTEMA_PERFILADO_H

#include <tamtypes.h>

enum {
    RENDER_PROF,     /* tarea de graficos completa */
    PROF_DL,         /* recorrido de la display list */
    PROF_VTX,
    PROF_TRI,
    PROF_RECT,       /* rectangulos texturizados y rellenos */
    ESTADO_PROF,      /* construir_estado (combinador, modos del GS) */
    CARGA_PROF,
    PREPARAR_PROF,    /* preparar_textura: clave, busqueda en la cache */
    DECODIFICACION_PROF,     /* decodificacion y subida de texturas nuevas */
    ENVIO_PROF,       /* envio del paquete y espera del DMA */
    PROF_AUDIO,      /* tarea de audio */
    JUEGO_PROF,       /* hilo de juego: logica y armado de la display list */
    PROF_AUDIOGAME,  /* hilo de audio: secuencias y armado de la lista Acmd */
    COMBINACION_PROF,    /* combinador de color por vertice (dentro de tri) */
    RECORTE_PROF,       /* triangulos recortados (dentro de tri) */
    EMITIR_PROF,       /* paquete del GS de los triangulos (dentro de tri) */
    CANTIDAD_PROF
};

#if defined(SMK64_PROF) || defined(SMK64_MEDIDOR)
#define SECCIONES_PROF_PS2 1
extern u32 ciclos_prof[CANTIDAD_PROF];
extern u32 prof_calls[CANTIDAD_PROF];

static inline u32 ahora_prof(void)
{
    u32 c;

    __asm__ __volatile__("mfc0 %0, $9" : "=r"(c));
    return c;
}

#ifdef SMK64_PROF
/* Perfilador por muestreo (muestreo_cpu.c). */
void iniciar_perfil_muestreo(void);
void terminar_perfil_muestreo(const char *nombre);
#endif

extern u32 inicio_prof[CANTIDAD_PROF];
/* Ciclos de la sintesis de audio (seccion audio, sin esperas) */
extern volatile u32 prof_preempt;
extern u32 inicio_pre_prof[CANTIDAD_PROF];
#define EMPEZAR_PROF(id) (inicio_prof[id] = ahora_prof(), inicio_pre_prof[id] = prof_preempt)
#define FIN_PROF(id)                                                             \
    do {                                                                         \
        u32 _e = ahora_prof() - inicio_prof[id];                                    \
        if ((id) == PROF_AUDIO) {                                                \
            prof_preempt += _e;                                                  \
        } else if ((id) != JUEGO_PROF && (id) != PROF_AUDIOGAME) {                \
            _e -= prof_preempt - inicio_pre_prof[id];                              \
        }                                                                        \
        ciclos_prof[id] += _e;                                                   \
        prof_calls[id]++;                                                        \
    } while (0)
#else
#define EMPEZAR_PROF(id) do { } while (0)
#define FIN_PROF(id)   do { } while (0)
#endif

#endif
