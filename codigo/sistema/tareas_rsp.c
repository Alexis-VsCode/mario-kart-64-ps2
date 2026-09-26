#include <ultra64.h>
#include <PR/os.h>
#include <PR/sptask.h>

#include "sistema/sistema_ps2.h"
#include "graficos/interprete_f3dex.h"
#include "audio/salida_audio.h"
#include "sistema/perfilado.h"

static OSTask *tarea_cargado;

void osSpTaskLoad(OSTask *tarea)
{
    tarea_cargado = tarea;
}

void osSpTaskStartGo(OSTask *tarea)
{
    if (tarea == NULL) {
        tarea = tarea_cargado;
    }
    tarea_cargado = NULL;
    if (tarea == NULL) {
        return;
    }

#ifdef SMK64_TRAZA
    marcar_punto_control(tarea->t.type == M_GFXTASK ? "rsp: graficos inicio" : "rsp: audio inicio");
#endif
    switch (tarea->t.type) {
        case M_GFXTASK:
            ejecutar_tarea_graficos((Gfx *) tarea->t.data_ptr);
#ifdef SMK64_TRAZA
            marcar_punto_control("rsp: graficos fin");
#endif
            enviar_evento_sistema(OS_EVENT_SP);
            enviar_evento_sistema(OS_EVENT_DP);
            break;
        case M_AUDTASK: {
            EMPEZAR_PROF(PROF_AUDIO);
            ejecutar_tarea_ps2_audio((u64 *) tarea->t.data_ptr, tarea->t.data_size);
            FIN_PROF(PROF_AUDIO);
#ifdef SMK64_TRAZA
            marcar_punto_control("rsp: audio fin");
#endif
            enviar_evento_sistema(OS_EVENT_SP);
            break;
        }
        default:
            registrar("tarea RSP desconocida: %d", (int) tarea->t.type);
            enviar_evento_sistema(OS_EVENT_SP);
            break;
    }
}

volatile u32 ps2_audio_tarea_ciclos;

void ejecutar_tarea_audio_rsp_ps2(OSTask *tarea)
{
    u32 t0;

    __asm__ __volatile__("mfc0 %0, $9" : "=r"(t0));
    {
        EMPEZAR_PROF(PROF_AUDIO);
        ejecutar_tarea_ps2_audio((u64 *) tarea->t.data_ptr, tarea->t.data_size);
        FIN_PROF(PROF_AUDIO);
    }
    {
        u32 t1;

        __asm__ __volatile__("mfc0 %0, $9" : "=r"(t1));
        ps2_audio_tarea_ciclos += t1 - t0;
    }
}

void osSpTaskYield(void)
{
    /* Las tareas terminan dentro de osSpTaskStartGo */
}

OSYieldResult osSpTaskYielded(OSTask *tarea)
{
    (void) tarea;
    return 0;
}
