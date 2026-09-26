#include <carrera/actores.h>
#include <PR/gbi.h>
#include <sistema/bucle_principal.h>
#include "recursos/pistas/kalimari_desert/datos_pista.h"

void renderizar_actor_paso_a_nivel(Camara* parametro0, struct PasoANivel* cruce_rr) {
    SIN_USO Vec3s sp80 = { 0, 0, 0 };
    Mat4 sp40;
    f32 desconocido = distancia_si_visible(parametro0->pos, cruce_rr->pos, parametro0->rot[1], 0.0f, acercar_camara[parametro0 - camara1],
                                      4000000.0f);

    if (!(desconocido < 0.0f)) {
        rotar_traslacion_zxy_mtxf(sp40, cruce_rr->pos, cruce_rr->rot);

        if (fijar_posicion_render(sp40, 0) != 0) {
            gSPSetGeometryMode(display_list_cabeza++, G_LIGHTING);
            gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);

            if (es_cruce_disparado_por_indice[cruce_rr->id_cruce]) {

                if (cruce_rr->algun_temporizador < 20) {
                    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desert_dl_cruce_derecha_activo);
                } else {
                    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desert_dl_cruce_izquierda_activo);
                }
            } else {
                gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desert_dl_cruce_ambos_inactivo);
            }
            gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
        }
    }
}
