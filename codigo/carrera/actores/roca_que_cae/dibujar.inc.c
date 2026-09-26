#include <carrera/actores.h>
#include <sistema/bucle_principal.h>
#include "recursos/pistas/choco_mountain/datos_pista.h"

void renderizar_roca_cayendo_actor(Camara* camara, struct RocaCayendo* roca) {
    Vec3s sp98;
    Vec3f sp8_c;
    Mat4 sp4_c;
    f32 altura;
    SIN_USO s32 relleno[4];

    if (roca->temporizador_reaparicion != 0) {
        return;
    }

    altura = distancia_si_visible(camara->pos, roca->pos, camara->rot[1], 400.0f, acercar_camara[camara - camara1],
                                     4000000.0f);

    if (altura < 0.0f) {
        return;
    }

    if (altura < 250000.0f) {

        if (roca->desconocido30.unk34 == 1) {
            sp8_c[0] = roca->pos[0];
            sp8_c[2] = roca->pos[2];
            altura = calcular_altura_superficie(sp8_c[0], roca->pos[1], sp8_c[2], roca->desconocido30.indice_zx_malla);
            sp98[0] = 0;
            sp98[1] = 0;
            sp98[2] = 0;
            sp8_c[1] = altura + 2.0f;
            rotar_traslacion_zxy_mtxf(sp4_c, sp8_c, sp98);
            if (fijar_posicion_render(sp4_c, 0) == 0) {
                return;
            }
            gSPDisplayList(display_list_cabeza++, d_circuito_choco_montania_dl_6F88);
        }
    }
    rotar_traslacion_zxy_mtxf(sp4_c, roca->pos, roca->rot);
    if (fijar_posicion_render(sp4_c, 0) == 0) {
        return;
    }
    gSPDisplayList(display_list_cabeza++, d_circuito_choco_mountain_roca_cayendo_dl);
}
