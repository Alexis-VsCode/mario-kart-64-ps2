#include <ultra64.h>
#include <juego/macros.h>
#include <juego/tipos_actores.h>
#include "carrera/camara.h"
#include "sistema/bucle_principal.h"
#include "carrera/actores.h"
#include "recursos/pistas/todos_datos_pistas.h"
#include <PR/gbi.h>

void renderizar_barco_paleta_actor(Camara* parametro0, struct BarcoRuedaPaleta* barco, SIN_USO Mat4 parametro2, u16 contador_camino) {
    SIN_USO s32 relleno[3];
    Vec3f sp120;
    Mat4 sp_e0;
    Mat4 sp_a0;
    Mat4 sp60;
    f32 temporal_;

    if ((contador_camino > 20) && (contador_camino < 25)) {
        return;
    }

    temporal_ =
        distancia_si_visible(parametro0->pos, barco->pos, parametro0->rot[1], 90000.0f, acercar_camara[parametro0 - camara1], 9000000.0f);

    if (temporal_ < 0.0f) {
        return;
    }

    gSPSetLights1(display_list_cabeza++, dato_800DC610[1]);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_LIGHTING | G_SHADING_SMOOTH);

    rotar_traslacion_zxy_mtxf(sp_e0, barco->pos, barco->rot_barco);
    if (fijar_posicion_render(sp_e0, 1) != 0) {

        gSPDisplayList(display_list_cabeza++, &d_circuito_dks_jungle_parkway_dl_barco);
        gSPDisplayList(display_list_cabeza++, &d_circuito_dks_jungle_parkway_dl_barandas);

        rotar_x_mtxf(sp_e0, barco->rot_rueda);
        fijar_vec3f(sp120, 0, 16.0f, -255.0f);
        trasladar_mtxf(sp_a0, sp120);
        multiplicacion_mtxf(sp60, sp_e0, sp_a0);
        if (fijar_posicion_render(sp60, 3) != 0) {
            gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
            gSPDisplayList(display_list_cabeza++, &d_circuito_dks_jungle_parkway_dl_rueda_paleta);
            gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);
            gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
        }
    }
}
