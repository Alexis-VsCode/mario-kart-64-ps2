#include <carrera/actores.h>
#include <sistema/bucle_principal.h>
#include "recursos/pistas/mario_raceway/datos_pista.h"

void renderizar_actor_mario_cartel(Camara* parametro0, SIN_USO Mat4 parametro1, struct Actor* parametro2) {
    Mat4 sp40;
    f32 desconocido;
    s16 temporal_ = parametro2->flags;

    if (temporal_ & 0x800) {
        return;
    }

    desconocido = distancia_si_visible(parametro0->pos, parametro2->pos, parametro0->rot[1], 0, acercar_camara[parametro0 - camara1], 16000000.0f);
    if (!(desconocido < 0.0f)) {
        gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
        gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
        rotar_traslacion_zxy_mtxf(sp40, parametro2->pos, parametro2->rot);
        if (fijar_posicion_render(sp40, 0) != 0) {
            gSPDisplayList(display_list_cabeza++, d_circuito_mario_raceway_cartel_dl);
        }
    }
}
