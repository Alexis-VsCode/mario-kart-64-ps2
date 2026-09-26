#include <ultra64.h>
#include "carrera/ia_vehiculos_y_camara.h"
#include <juego/definiciones.h>
#include <juego/macros.h>

void funcion_8001AB00(void) {
    s32 variable_v1;

    for (variable_v1 = 0; variable_v1 < JUGADORES_NUM; variable_v1++) {
        cpu_item_estrategia[variable_v1].rama = 0;
        cpu_item_estrategia[variable_v1].temporizador = 0;
        cpu_item_estrategia[variable_v1].indice_actor = -1;
        cpu_item_estrategia[variable_v1].usar_item_num = 0;
        cpu_item_estrategia[variable_v1].num_soltado_banana_grupo = 0;
    }
}

void cpu_decisiones_rama_item(SIN_USO s32 id_jugador, s16* rama, s32 item_id) {
    s32 value = -1;
    switch (item_id) {
        case ITEM_CAJA_ITEM_FALSA:
            value = ITEM_ESTRATEGIA_CPU_CAJA_ITEM_FALSA;
            break;
        case ITEM_BOO:
            value = ITEM_ESTRATEGIA_CPU_BOO;
            break;
        case ITEM_BANANA:
            value = CPU_ESTRATEGIA_ITEM_BANANA;
            break;
        case RAYO_ITEM:
            value = CPU_ESTRATEGIA_ITEM_RAYO;
            break;
        case ESTRELLA_ITEM:
            value = CPU_ESTRATEGIA_ITEM_ESTRELLA;
            break;
        case HONGO_ITEM:
            value = CPU_ESTRATEGIA_ITEM_HONGO;
            break;
        case HONGO_DOBLE_ITEM:
            break;
        case ITEM_TRIPLE_HONGO:
            break;
        case ITEM_SUPER_HONGO:
            break;
    }
    if (value >= 0) {
        *rama = value;
    }
}

void funcion_8001ABE0(SIN_USO s32 id_jugador, SIN_USO CpuItemEstrategiaDatos* parametro1) {
}

void borrar_estrategias_vencido(CpuItemEstrategiaDatos* parametro0) {
    if ((parametro0->indice_actor < 0) || (parametro0->indice_actor >= 0x64)) {
        parametro0->rama = 0;
        parametro0->temporizador = 0;
    }
}
