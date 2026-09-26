#include <carrera/actores.h>
#include <sistema/bucle_principal.h>
#include <juego/macros.h>

void renderizar_actor_caja_item(Camara* camara, struct CajaItem* caja_item_2) {
    SIN_USO s32 relleno[2];
    Vec3f algun_vec_1;
    Vec3f algun_vec_2;
    Vec3s algun_rot;
    f32 cosa;
    SIN_USO s32 relleno2;
    Mat4 algun_matriz_1;
    Mat4 algun_matriz_2;
    SIN_USO s32 relleno3[4];
    f32 temporal_f0;
    f32 temporal_f0_2;
    f32 temporal_f0_3;
    f32 temporal_f12;
    f32 temporal_f2;
    f32 temporal_f2_2;
    f32 algun_multiplicador;

    temporal_f0 = distancia_si_visible(camara->pos, caja_item_2->pos, camara->rot[1], 0.0f, acercar_camara[camara - camara1],
                                      4000000.0f);
    if (!(temporal_f0 < 0.0f) && !(600000.0f < temporal_f0)) {
        if ((caja_item_2->state == 2) && (temporal_f0 < 100000.0f)) {
            algun_rot[0] = 0;
            algun_rot[1] = caja_item_2->rot[1];
            algun_rot[2] = 0;
            algun_vec_2[0] = caja_item_2->pos[0];
            algun_vec_2[1] = caja_item_2->distancia_reinicio + 2.0f;
            algun_vec_2[2] = caja_item_2->pos[2];
            rotar_traslacion_zxy_mtxf(algun_matriz_1, algun_vec_2, algun_rot);

            if (!fijar_posicion_render(algun_matriz_1, 0)) {
                return;
            }

            gSPDisplayList(display_list_cabeza++, dato_0D002EE8);
            algun_rot[1] = caja_item_2->rot[1] * 2;
            algun_vec_2[1] = caja_item_2->pos[1];
            rotar_traslacion_zxy_mtxf(algun_matriz_1, algun_vec_2, algun_rot);

            if (!fijar_posicion_render(algun_matriz_1, 0)) {
                return;
            }

            gSPDisplayList(display_list_cabeza++, caja_item_signo_pregunta_modelo);
        }
        if (caja_item_2->state == 5) {
            rotar_traslacion_zxy_mtxf(algun_matriz_1, caja_item_2->pos, caja_item_2->rot);

            if (!fijar_posicion_render(algun_matriz_1, 0)) {
                return;
            }

            gSPDisplayList(display_list_cabeza++, caja_item_signo_pregunta_modelo);
        }
        if (caja_item_2->state != 3) {
            rotar_traslacion_zxy_mtxf(algun_matriz_1, caja_item_2->pos, caja_item_2->rot);

            if (!fijar_posicion_render(algun_matriz_1, 0)) {
                return;
            }

            gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            if ((caja_item_2->rot[1] < GRADOS(14.95f)) && (caja_item_2->rot[1] > 0)) {
                gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
            } else if ((caja_item_2->rot[1] > (150 * GRADOS(1))) && (caja_item_2->rot[1] < (165 * GRADOS(1)))) {
                gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
            } else if ((caja_item_2->rot[1] > (80 * GRADOS(1))) && (caja_item_2->rot[1] < (95 * GRADOS(1)))) {
                gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
            } else if ((caja_item_2->rot[1] > (280 * GRADOS(1))) && (caja_item_2->rot[1] < (295 * GRADOS(1)))) {
                gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
            } else {
                gDPSetBlendMask(display_list_cabeza++, 0xFF);
                gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
            }
            gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
            gSPDisplayList(display_list_cabeza++, dato_0D003090);
        } else {
            gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
            gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
            gDPSetBlendMask(display_list_cabeza++, 0xFF);
            cosa = caja_item_2->algun_temporizador;
            rotar_traslacion_zxy_mtxf(algun_matriz_1, caja_item_2->pos, caja_item_2->rot);
            if (cosa < 10.0f) {
                algun_multiplicador = 1.0f;
            } else {
                algun_multiplicador = 1.0f - ((cosa - 10.0f) * 0.1f);
            }
            escalar_mtxf(algun_matriz_1, algun_multiplicador);
            if (caja_item_2->algun_temporizador & 1) {
                gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
            } else {
                gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
            }
            temporal_f2 = 2.0f * cosa;
            algun_vec_1[0] = 0.0f;
            algun_vec_1[1] = temporal_f2;
            algun_vec_1[2] = cosa;
            trasladar_vec3f_mat4_agregar(algun_matriz_1, algun_matriz_2, algun_vec_1);

            if (!fijar_posicion_render(algun_matriz_2, 0)) {
                return;
            }

            gSPDisplayList(display_list_cabeza++, dato_0D003158);
            temporal_f2_2 = 0.8f * cosa;
            temporal_f12 = 0.5f * cosa;
            algun_vec_1[0] = temporal_f2_2;
            algun_vec_1[1] = 2.3f * cosa;
            algun_vec_1[2] = temporal_f12;
            trasladar_vec3f_mat4_agregar(algun_matriz_1, algun_matriz_2, algun_vec_1);

            if (!fijar_posicion_render(algun_matriz_2, 0)) {
                return;
            }

            gSPDisplayList(display_list_cabeza++, dato_0D0031B8);
            temporal_f0_2 = -0.5f * cosa;
            algun_vec_1[0] = temporal_f2_2;
            algun_vec_1[1] = 1.2f * cosa;
            algun_vec_1[2] = temporal_f0_2;
            trasladar_vec3f_mat4_agregar(algun_matriz_1, algun_matriz_2, algun_vec_1);

            if (!fijar_posicion_render(algun_matriz_2, 0)) {
                return;
            }

            gSPDisplayList(display_list_cabeza++, dato_0D003128);
            if (!(caja_item_2->algun_temporizador & 1)) {
                gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
            } else {
                gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
            }
            algun_vec_1[0] = 0.0f;
            algun_vec_1[1] = 1.8f * cosa;
            algun_vec_1[2] = -1.0f * cosa;
            trasladar_vec3f_mat4_agregar(algun_matriz_1, algun_matriz_2, algun_vec_1);

            if (!fijar_posicion_render(algun_matriz_2, 0)) {
                return;
            }

            gSPDisplayList(display_list_cabeza++, dato_0D0031E8);
            temporal_f0_3 = -0.8f * cosa;
            algun_vec_1[0] = temporal_f0_3;
            algun_vec_1[1] = 0.6f * cosa;
            algun_vec_1[2] = temporal_f0_2;
            trasladar_vec3f_mat4_agregar(algun_matriz_1, algun_matriz_2, algun_vec_1);

            if (!fijar_posicion_render(algun_matriz_2, 0)) {
                return;
            }

            gSPDisplayList(display_list_cabeza++, dato_0D003188);
            algun_vec_1[0] = temporal_f0_3;
            algun_vec_1[1] = temporal_f2;
            algun_vec_1[2] = temporal_f12;
            trasladar_vec3f_mat4_agregar(algun_matriz_1, algun_matriz_2, algun_vec_1);

            if (!fijar_posicion_render(algun_matriz_2, 0)) {
                return;
            }

            gSPDisplayList(display_list_cabeza++, dato_0D0030F8);
            gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
        }
        gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    }
}
