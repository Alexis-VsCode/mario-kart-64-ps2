#include <carrera/actores.h>
#include <sistema/bucle_principal.h>
#include <juego/definiciones.h>

void renderizar_automovil_actor(Camara* parametro0, struct Actor* parametro1) {
    SIN_USO s32 relleno[6];
    Mat4 sp_c8;
    SIN_USO s32 relleno2[32];
    f32 temporal_f0 =
        distancia_si_visible(parametro0->pos, parametro1->pos, parametro0->rot[1], 2500.0f, acercar_camara[parametro0 - camara1], 9000000.0f);

    if (!(temporal_f0 < 0.0f)) {

        gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

        rotar_traslacion_zxy_mtxf(sp_c8, parametro1->pos, parametro1->rot);
        escalar_mtxf(sp_c8, 0.1f);
        if (fijar_posicion_render(sp_c8, 0) != 0) {

            if (modo_pantalla_activo == MODO_PANTALLA_1P) {
                if (temporal_f0 < 160000.0f) {
                    gSPDisplayList(display_list_cabeza++, &toads_turnpike_dl_9);
                } else if (temporal_f0 < 640000.0f) {
                    gSPDisplayList(display_list_cabeza++, &toads_turnpike_dl_10);
                } else {
                    gSPDisplayList(display_list_cabeza++, &toads_turnpike_dl_11);
                }
            } else if (temporal_f0 < 160000.0f) {
                gSPDisplayList(display_list_cabeza++, &toads_turnpike_dl_10);
            } else {
                gSPDisplayList(display_list_cabeza++, &toads_turnpike_dl_11);
            }
        }
    }
}
