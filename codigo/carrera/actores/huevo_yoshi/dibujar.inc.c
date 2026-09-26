#include <carrera/camara.h>
#include <carrera/actores.h>
#include <juego/definiciones.h>
#include <sistema/bucle_principal.h>
#include "recursos/pistas/yoshi_valley/datos_pista.h"

void renderizar_actor_yoshi_huevo(Camara* parametro0, Mat4 parametro1, struct YoshiValleyHuevo* huevo, u16 parametro3) {
    Mat4 sp60;
    Vec3s sp5_c;
    Vec3f sp54;
    f32 temporal_f0;

    if (estado_juego != SECUENCIA_CREDITOS) {
        temporal_f0 = distancia_si_visible(parametro0->pos, huevo->pos, parametro0->rot[1], 200.0f, acercar_camara[parametro0 - camara1],
                                          16000000.0f);
        if (temporal_f0 < 0.0f) {
            return;
        }
    } else {
        parametro3 = 15;
        temporal_f0 = 0.0f;
    }

    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    if ((parametro3 > 12) && (parametro3 < 20)) {
        if (temporal_f0 < 640000.0f) {
            sp54[0] = huevo->pos[0];
            sp54[1] = 3.0f;
            sp54[2] = huevo->pos[2];
            funcion_802976D8(sp5_c);
            funcion_8029794C(sp54, sp5_c, 10.0f);
        }
        sp5_c[0] = 0;
        sp5_c[1] = huevo->rot_huevo;
        sp5_c[2] = 0;
        rotar_traslacion_zxy_mtxf(sp60, huevo->pos, sp5_c);
        if (fijar_posicion_render(sp60, 0) == 0) {
            return;
        }

        gSPSetGeometryMode(display_list_cabeza++, G_LIGHTING);
        gSPDisplayList(display_list_cabeza++, d_circuito_yoshi_valle_dl_16D70);
    } else {
        parametro1[3][0] = huevo->pos[0];
        parametro1[3][1] = huevo->pos[1];
        parametro1[3][2] = huevo->pos[2];

        if (fijar_posicion_render(parametro1, 0) != 0) {
            gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
            gSPDisplayList(display_list_cabeza++, d_circuito_yoshi_valley_lod0_huevo_dl);
        }
    }
}
