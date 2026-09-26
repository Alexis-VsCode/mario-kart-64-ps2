#include <carrera/actores.h>
#include <carrera/preparacion_carrera.h>
#include <PR/gbi.h>
#include <sistema/bucle_principal.h>

void renderizar_actor_caja_item_falsa(Camara* camara, struct CajaItemFalsa* caja_item_falsa_2) {
    Vec3s algun_rot;
    SIN_USO s32 relleno[3];
    Vec3f algun_vec;
    Mat4 algun_matriz_2;
    Mat4 algun_matriz_3;
    SIN_USO s32 relleno2[12];
    f32 temporal_f0_2;
    f32 temporal_f0_3;
    f32 temporal_f12;
    f32 temporal_f2;
    f32 cosa;
    f32 temporal_f2_2;
    f32 algun_multiplicador;

    if (distancia_si_visible(camara->pos, caja_item_falsa_2->pos, camara->rot[1], 2500.0f, acercar_camara[camara - camara1],
                                1000000.0f) < 0) {
        actor_no_renderizado(camara, (struct Actor*) caja_item_falsa_2);
        return;
    }
    if (((f32) max_y_circuito + 800.0f) < caja_item_falsa_2->pos[1]) {
        actor_no_renderizado(camara, (struct Actor*) caja_item_falsa_2);
        return;
    }
    if (caja_item_falsa_2->pos[1] < ((f32) min_y_circuito - 800.0f)) {
        actor_no_renderizado(camara, (struct Actor*) caja_item_falsa_2);
        return;
    }

    actor_renderizado(camara, (struct Actor*) caja_item_falsa_2);
    algun_rot[0] = 0;
    algun_rot[1] = caja_item_falsa_2->rot[1];
    algun_rot[2] = 0;
    rotar_traslacion_zxy_mtxf(algun_matriz_2, caja_item_falsa_2->pos, algun_rot);
    escalar_mtxf(algun_matriz_2, caja_item_falsa_2->escalado_tamanio);
    if (caja_item_falsa_2->state != 2) {

        if (!fijar_posicion_render(algun_matriz_2, 0)) {
            return;
        }

        gSPDisplayList(display_list_cabeza++, comun_modelo_falso_caja_item);
        rotar_traslacion_zxy_mtxf(algun_matriz_2, caja_item_falsa_2->pos, caja_item_falsa_2->rot);
        escalar_mtxf(algun_matriz_2, caja_item_falsa_2->escalado_tamanio);

        if (!fijar_posicion_render(algun_matriz_2, 0)) {
            return;
        }

        gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
        gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
        if ((caja_item_falsa_2->rot[1] < GRADOS(14.95f)) && (caja_item_falsa_2->rot[1] > 0)) {
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        } else if ((caja_item_falsa_2->rot[1] > (150 * GRADOS(1))) && (caja_item_falsa_2->rot[1] < (165 * GRADOS(1)))) {
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        } else if ((caja_item_falsa_2->rot[1] > (80 * GRADOS(1))) && (caja_item_falsa_2->rot[1] < (95 * GRADOS(1)))) {
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        } else if ((caja_item_falsa_2->rot[1] > (280 * GRADOS(1))) && (caja_item_falsa_2->rot[1] < (295 * GRADOS(1)))) {
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        } else {
            gDPSetBlendMask(display_list_cabeza++, 0xFF);
            gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        }
        gSPDisplayList(display_list_cabeza++, dato_0D003090);
    } else {
        gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
        gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
        gDPSetBlendMask(display_list_cabeza++, 0xFF);
        cosa = caja_item_falsa_2->algun_temporizador;
        rotar_traslacion_zxy_mtxf(algun_matriz_2, caja_item_falsa_2->pos, caja_item_falsa_2->rot);
        if (cosa < 10.0f) {
            algun_multiplicador = 1.0f;
        } else {
            algun_multiplicador = 1.0f - ((cosa - 10.0f) * 0.1f);
        }
        escalar_mtxf(algun_matriz_2, algun_multiplicador);
        if (caja_item_falsa_2->algun_temporizador & 1) {
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        } else {
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
        }
        temporal_f2 = 2.0f * cosa;
        algun_vec[0] = 0.0f;
        algun_vec[1] = temporal_f2;
        algun_vec[2] = cosa;
        trasladar_vec3f_mat4_agregar(algun_matriz_2, algun_matriz_3, algun_vec);

        if (!fijar_posicion_render(algun_matriz_3, 0)) {
            return;
        }

        gSPDisplayList(display_list_cabeza++, dato_0D003158);
        temporal_f2_2 = 0.8f * cosa;
        temporal_f12 = 0.5f * cosa;
        algun_vec[0] = temporal_f2_2;
        algun_vec[1] = 2.3f * cosa;
        algun_vec[2] = temporal_f12;
        trasladar_vec3f_mat4_agregar(algun_matriz_2, algun_matriz_3, algun_vec);

        if (!fijar_posicion_render(algun_matriz_3, 0)) {
            return;
        }

        gSPDisplayList(display_list_cabeza++, dato_0D0031B8);
        temporal_f0_2 = -0.5f * cosa;
        algun_vec[0] = temporal_f2_2;
        algun_vec[1] = 1.2f * cosa;
        algun_vec[2] = temporal_f0_2;
        trasladar_vec3f_mat4_agregar(algun_matriz_2, algun_matriz_3, algun_vec);

        if (!fijar_posicion_render(algun_matriz_3, 0)) {
            return;
        }

        gSPDisplayList(display_list_cabeza++, dato_0D003128);
        if (!(caja_item_falsa_2->algun_temporizador & 1)) {
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        } else {
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
        }
        algun_vec[0] = 0.0f;
        algun_vec[1] = 1.8f * cosa;
        algun_vec[2] = -1.0f * cosa;
        trasladar_vec3f_mat4_agregar(algun_matriz_2, algun_matriz_3, algun_vec);

        if (!fijar_posicion_render(algun_matriz_3, 0)) {
            return;
        }

        gSPDisplayList(display_list_cabeza++, dato_0D0031E8);
        temporal_f0_3 = -0.8f * cosa;
        algun_vec[0] = temporal_f0_3;
        algun_vec[1] = 0.6f * cosa;
        algun_vec[2] = temporal_f0_2;
        trasladar_vec3f_mat4_agregar(algun_matriz_2, algun_matriz_3, algun_vec);

        if (!fijar_posicion_render(algun_matriz_3, 0)) {
            return;
        }

        gSPDisplayList(display_list_cabeza++, dato_0D003188);
        algun_vec[0] = temporal_f0_3;
        algun_vec[1] = temporal_f2;
        algun_vec[2] = temporal_f12;
        trasladar_vec3f_mat4_agregar(algun_matriz_2, algun_matriz_3, algun_vec);

        if (!fijar_posicion_render(algun_matriz_3, 0)) {
            return;
        }

        gSPDisplayList(display_list_cabeza++, dato_0D0030F8);
        gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    }
}
