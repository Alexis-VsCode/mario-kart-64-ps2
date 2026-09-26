#include <carrera/actores.h>
#include <PR/gbi.h>
#include <sistema/bucle_principal.h>
#include "recursos/pistas/kalimari_desert/datos_pista.h"

void renderizar_motor_tren_actor(Camara* camara, struct AutomovilTren* actor) {
    SIN_USO s32 relleno[2];
    s32 max_objetos_alcanzado;
    Vec3f sp160;
    Mat4 sp120;
    Mat4 sp_e0;
    Mat4 sp_a0;

    f32 distancia = distancia_si_visible(camara->pos, actor->pos, camara->rot[1], 2500.0f,
                                           acercar_camara[camara - camara1], 9000000.0f);

    if (distancia < 0.0f) {
        return;
    }

    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    rotar_traslacion_zxy_mtxf(sp120, actor->pos, actor->rot);
    max_objetos_alcanzado = fijar_posicion_render(sp120, 0) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    if (distancia < 122500.0f) {

        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_1C0F0);
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_1B978);

    } else if (distancia < 640000.0f) {

        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_1D670);
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_1D160);
    } else {
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_1E910);
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_1E480);
    }
    if (1440000.0f < distancia) {
        return;
    }

    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22D28);

    rotar_x_mtxf(sp120, actor->rot_rueda);
    fijar_vec3f(sp160, 17.0f, 6.0f, 32.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    max_objetos_alcanzado = fijar_posicion_render(sp_a0, 3) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, actor->rot_rueda);
    fijar_vec3f(sp160, -17.0, 6.0f, 32.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    max_objetos_alcanzado = fijar_posicion_render(sp_a0, 3) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(2)));
    fijar_vec3f(sp160, 17.0f, 6.0f, 16.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    max_objetos_alcanzado = fijar_posicion_render(sp_a0, 3) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(2)));
    fijar_vec3f(sp160, -17.0f, 6.0f, 16.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    max_objetos_alcanzado = fijar_posicion_render(sp_a0, 3) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(6)));
    fijar_vec3f(sp160, 17.0f, 12.0f, -12.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    max_objetos_alcanzado = fijar_posicion_render(sp_a0, 3) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22D70);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(6)));
    fijar_vec3f(sp160, -17.0f, 12.0f, -12.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    max_objetos_alcanzado = fijar_posicion_render(sp_a0, 3) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22D70);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(4)));
    fijar_vec3f(sp160, 17.0f, 12.0f, -34.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    max_objetos_alcanzado = fijar_posicion_render(sp_a0, 3) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22D70);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(4)));
    fijar_vec3f(sp160, -17.0f, 12.0f, -34.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    max_objetos_alcanzado = fijar_posicion_render(sp_a0, 3) == 0;
    if (max_objetos_alcanzado) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22D70);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void renderizar_tender_tren_actor(Camara* camara, struct AutomovilTren* actor) {
    Mat4 sp120;
    Vec3f sp160;
    Mat4 sp_e0;
    Mat4 sp_a0;

    f32 temporal_f0 = distancia_si_visible(camara->pos, actor->pos, camara->rot[1], 625.0f,
                                          acercar_camara[camara - camara1], 9000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    rotar_traslacion_zxy_mtxf(sp120, actor->pos, actor->rot);
    if (fijar_posicion_render(sp120, 0) == 0) {
        return;
    }

    if (temporal_f0 < 250000.0f) {

        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_1F228);

    } else if (temporal_f0 < 1000000.0f) {
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_1F708);
    } else {
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_1FAF8);
    }
    if (1440000.0f < temporal_f0) {
        return;
    }

    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22D28);

    rotar_x_mtxf(sp120, actor->rot_rueda);
    fijar_vec3f(sp160, 17.0f, 6.0f, 8.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, actor->rot_rueda);
    fijar_vec3f(sp160, -17.0, 6.0f, 8.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(6)));
    fijar_vec3f(sp160, 17.0f, 6.0f, -8.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(6)));
    fijar_vec3f(sp160, -17.0f, 6.0f, -8.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }
    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void renderizar_actor_tren_pasajero_automovil(Camara* camara, struct AutomovilTren* actor) {
    Mat4 sp120;
    Vec3f sp160;
    Mat4 sp_e0;
    Mat4 sp_a0;

    f32 temporal_f0 = distancia_si_visible(camara->pos, actor->pos, camara->rot[1], 2025.0f,
                                          acercar_camara[camara - camara1], 9000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    rotar_traslacion_zxy_mtxf(sp120, actor->pos, actor->rot);

    if (fijar_posicion_render(sp120, 0) == 0) {
        return;
    }

    if (temporal_f0 < 250000.0f) {

        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_20A20);
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_20A08);

    } else if (temporal_f0 < 1000000.0f) {

        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desert_dl_21550);
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desert_dl_21220);
    } else {
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_21C90);
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_21A80);
    }
    if (1440000.0f < temporal_f0) {
        return;
    }

    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22D28);

    rotar_x_mtxf(sp120, actor->rot_rueda);
    fijar_vec3f(sp160, 17.0f, 6.0f, 28.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, actor->rot_rueda);
    fijar_vec3f(sp160, -17.0, 6.0f, 28.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(3)));
    fijar_vec3f(sp160, 17.0f, 6.0f, 12.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(3)));
    fijar_vec3f(sp160, -17.0f, 6.0f, 12.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(8)));
    fijar_vec3f(sp160, 17.0f, 6.0f, -8.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(8)));
    fijar_vec3f(sp160, -17.0f, 6.0f, -8.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(2)));
    fijar_vec3f(sp160, 17.0f, 6.0f, -24.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);

    rotar_x_mtxf(sp120, (s16) (actor->rot_rueda + GRADOS(2)));
    fijar_vec3f(sp160, -17.0f, 6.0f, -24.0f);
    trasladar_mtxf(sp_e0, sp160);
    multiplicacion_mtxf(sp_a0, sp120, sp_e0);

    if (fijar_posicion_render(sp_a0, 3) == 0) {
        return;
    }

    gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22DB8);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}
