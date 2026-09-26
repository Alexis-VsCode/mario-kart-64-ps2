#include <carrera/actores.h>
#include <sistema/bucle_principal.h>
#include <PR/gbi.h>
#include "recursos/pistas/mario_raceway/datos_pista.h"
#include "recursos/pistas/royal_raceway/datos_pista.h"

void renderizar_actor_planta_piranha(Camara* parametro0, Mat4 parametro1, struct PlantaPiranha* parametro2) {
    SIN_USO s32 relleno;
    u8* direccion;
    s16 temporal_lo = parametro0 - camara1;
    s16 frame_animacion;
    s16 temporal_ = parametro2->flags;
    f32 temporal_f0;
    s32 max_objetos_alcanzado;

    if (temporal_ & 0x800) {
        return;
    }

    temporal_f0 = distancia_si_visible(parametro0->pos, parametro2->pos, parametro0->rot[1], 0, acercar_camara[parametro0 - camara1], 1000000.0f);

    if (temporal_f0 < 0.0f) {

        switch (temporal_lo) {
            case 0:
                parametro2->estados_visibilidad[0] = -1;
                break;
            case 1:
                parametro2->estados_visibilidad[1] = -1;
                break;
            case 2:
                parametro2->estados_visibilidad[2] = -1;
                break;
            case 3:
                parametro2->estados_visibilidad[3] = -1;
                break;
        }
        return;
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];
    max_objetos_alcanzado = fijar_posicion_render(parametro1, 0) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    if (90000.0f < temporal_f0) {

        switch (temporal_lo) {
            case 0:
                parametro2->estados_visibilidad[0] = 0;
                break;
            case 1:
                parametro2->estados_visibilidad[1] = 0;
                break;
            case 2:
                parametro2->estados_visibilidad[2] = 0;
                break;
            case 3:
                parametro2->estados_visibilidad[3] = 0;
                break;
        }
        frame_animacion = 0;

    } else {
        switch (temporal_lo) {
            case 0:
                parametro2->estados_visibilidad[0] = 1;
                break;
            case 1:
                parametro2->estados_visibilidad[1] = 1;
                break;
            case 2:
                parametro2->estados_visibilidad[2] = 1;
                break;
            case 3:
                parametro2->estados_visibilidad[3] = 1;
                break;
        }

        switch (temporal_lo) {
            case 0:
                frame_animacion = parametro2->temporizadores[0];
                break;
            case 1:
                frame_animacion = parametro2->temporizadores[1];
                break;
            case 2:
                frame_animacion = parametro2->temporizadores[2];
                break;
            case 3:
                frame_animacion = parametro2->temporizadores[3];
                break;
        }
    }
    frame_animacion /= 6;

    if (frame_animacion > 8) {
        frame_animacion = 8;
    }
    direccion = dato_802BA058 + (frame_animacion << 0xB);
    gDPLoadTextureBlock(display_list_cabeza++, VIRTUAL_A_FISICO(direccion), G_IM_FMT_CI, G_IM_SIZ_8b, 32, 64, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    if (id_circuito_actual == CIRCUITO_MARIO_RACEWAY) {
        gSPDisplayList(display_list_cabeza++, &d_circuito_mario_raceway_dl_planta_piranha);
    } else {
        gSPDisplayList(display_list_cabeza++, &d_circuito_royal_raceway_dl_planta_piranha);
    }
}
