#include <carrera/actores.h>
#include <PR/gbi.h>
#include <sistema/bucle_principal.h>
#include "recursos/pistas/wario_stadium/datos_pista.h"

void renderizar_actor_wario_cartel(Camara* parametro0, struct Actor* parametro1) {
    Mat4 sp38;
    f32 desconocido = distancia_si_visible(parametro0->pos, parametro1->pos, parametro0->rot[1], 0, acercar_camara[parametro0 - camara1], 16000000.0f);

    if (!(desconocido < 0.0f)) {
        gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
        gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

        rotar_traslacion_zxy_mtxf(sp38, parametro1->pos, parametro1->rot);
        if (fijar_posicion_render(sp38, 0) != 0) {

            gSPDisplayList(display_list_cabeza++, d_circuito_wario_stadium_cartel_dl);
        }
    }
}
