#include <carrera/actores.h>
#include <sistema/bucle_principal.h>
#include "recursos/pistas/koopa_troopa_beach/datos_pista.h"

void renderizar_arbol_palmera_actor(Camara* parametro0, SIN_USO Mat4 parametro1, struct ArbolPalmera* parametro2) {
    Vec3s sp_a8 = { 0, 0, 0 };
    Mat4 sp68;
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800)) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(parametro0->pos, parametro2->pos, parametro0->rot[1], 0.0f, acercar_camara[parametro0 - camara1], 4000000.0f);

    if (!(temporal_f0 < 0.0f)) {
        if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 250000.0f)) {
            funcion_8029794C(parametro2->pos, parametro2->rot, 2.0f);
        }
        rotar_traslacion_zxy_mtxf(sp68, parametro2->pos, sp_a8);
        if (fijar_posicion_render(sp68, 0) != 0) {

            gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
            gSPSetGeometryMode(display_list_cabeza++, G_LIGHTING);

            switch (parametro2->variante) {
                case 0:
                    gSPDisplayList(display_list_cabeza++, &d_circuito_koopa_troopa_beach_tronco1_arbol_dl);
                    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
                    gSPDisplayList(display_list_cabeza++, &d_circuito_koopa_troopa_beach_arriba1_arbol_dl);
                    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
                    break;

                case 1:
                    gSPDisplayList(display_list_cabeza++, &d_circuito_koopa_troopa_beach_tronco2_arbol_dl);
                    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
                    gSPDisplayList(display_list_cabeza++, &d_circuito_koopa_troopa_beach_arriba2_arbol_dl);
                    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
                    break;

                case 2:
                    gSPDisplayList(display_list_cabeza++, &d_circuito_koopa_troopa_beach_tronco3_arbol_dl);
                    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
                    gSPDisplayList(display_list_cabeza++, &d_circuito_koopa_troopa_beach_arriba3_arbol_dl);
                    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
                    break;
            }
        }
    }
}
