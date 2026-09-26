#include <carrera/camara.h>
#include <carrera/actores.h>
#include <sistema/bucle_principal.h>
#include <PR/gbi.h>
#include "recursos/pistas/moo_moo_farm/datos_pista.h"

void renderizar_vaca_actor(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    if (distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1],
                                  4000000.0f) < 0) {
        return;
    }

    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        switch (parametro2->state) {
            case 0:
                gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_vaca1_dl);
                break;
            case 1:
                gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_vaca2_dl);
                break;
            case 2:
                gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_vaca3_dl);
                break;
            case 3:
                gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_vaca4_dl);
                break;
            case 4:
                gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_vaca5_dl);
                break;
        }
    }
}
