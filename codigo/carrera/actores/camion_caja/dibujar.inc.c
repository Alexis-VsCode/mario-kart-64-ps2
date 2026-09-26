#include <carrera/actores.h>
#include <PR/gbi.h>
#include <sistema/bucle_principal.h>
#include <juego/definiciones.h>
#include "recursos/pistas/toads_turnpike/datos_pista.h"

void renderizar_camion_caja_actor(Camara* parametro0, struct Actor* parametro1) {
    SIN_USO s32 relleno[6];
    Mat4 sp_d8;
    SIN_USO s32 relleno2[32];
    f32 temporal_f0 =
        distancia_si_visible(parametro0->pos, parametro1->pos, parametro0->rot[1], 2500.0f, acercar_camara[parametro0 - camara1], 9000000.0f);
    if (temporal_f0 < 0.0f) {
        return;
    }

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    rotar_traslacion_zxy_mtxf(sp_d8, parametro1->pos, parametro1->rot);
    if (fijar_posicion_render(sp_d8, 0) != 0) {

        switch (parametro1->state) {
            case 0:
                gSPDisplayList(display_list_cabeza++, &d_circuito_toads_turnpike_dl_23858);
                break;
            case 1:
                gSPDisplayList(display_list_cabeza++, &d_circuito_toads_turnpike_dl_238A0);
                break;
            case 2:
                gSPDisplayList(display_list_cabeza++, &d_circuito_toads_turnpike_dl_238E8);
                break;
        }

        if (modo_pantalla_activo == MODO_PANTALLA_1P) {
            if (temporal_f0 < 160000.0f) {
                gSPDisplayList(display_list_cabeza++, &toads_turnpike_dl_0);
            } else if (temporal_f0 < 640000.0f) {
                gSPDisplayList(display_list_cabeza++, &toads_turnpike_dl_1);
            } else {
                gSPDisplayList(display_list_cabeza++, &toads_turnpike_dl_2);
            }
        } else if (temporal_f0 < 160000.0f) {
            gSPDisplayList(display_list_cabeza++, &toads_turnpike_dl_1);
        } else {
            gSPDisplayList(display_list_cabeza++, &toads_turnpike_dl_2);
        }
    }
}
