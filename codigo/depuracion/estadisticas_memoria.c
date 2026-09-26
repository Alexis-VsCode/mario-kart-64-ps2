#include <kernel.h>
#include <malloc.h>
#include <unistd.h>

#include <ultra64.h>

#include "audio/datos.h"
#include "audio/monton.h"
#include "carrera/preparacion_carrera.h"
#include "graficos/memoria_texturas.h"
#include "depuracion/estadisticas_memoria.h"

void consultar_memoria(EstadisticasMemoria *e)
{
    struct mallinfo info = mallinfo();
    uintptr_t fin_monton = (uintptr_t) EndOfHeap();
    uintptr_t cortes = (uintptr_t) sbrk(0);

    e->monton_libre = (u32) ((fin_monton > cortes) ? fin_monton - cortes : 0) + (u32) info.fordblks;

    e->pool_juego_libre = (ptr_fin_monton > siguiente_libre_memoria_direccion) ? (u32) (ptr_fin_monton - siguiente_libre_memoria_direccion) : 0;

    e->audio_usado = (u32) (pool_inicializacion_audio.act - pool_inicializacion_audio.start) +
                    (u32) (pool_sesion_audio.act - pool_sesion_audio.start);
    e->audio_total = (u32) tamanio_monton_audio;

    tmem_uso_cache(&e->texturas_entradas, &e->texturas_bytes, &e->texturas_capacidad);
}
