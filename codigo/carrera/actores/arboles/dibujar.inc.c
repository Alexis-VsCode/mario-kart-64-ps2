#include <carrera/actores.h>
#include <PR/gbi.h>
#include <sistema/bucle_principal.h>
#include <recursos/datos_comunes.h>
#include "recursos/pistas/todos_datos_pistas.h"

void renderizar_arbol_actor_mario_raceway(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 16000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 250000.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 3.0f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gDPLoadTLUT_pal256(display_list_cabeza++, comun_tlut_arboles_importar);
        gSPDisplayList(display_list_cabeza++, d_circuito_mario_raceway_arbol_dl);
    }
}

void renderizar_arbol_actor_yoshi_valley(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 4000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 250000.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 2.79999995f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gDPLoadTLUT_pal256(display_list_cabeza++, comun_tlut_arboles_importar);
        gSPDisplayList(display_list_cabeza++, d_circuito_yoshi_valley_arbol_dl);
    }
}

void renderizar_arbol_actor_royal_raceway(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 4000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 250000.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 2.79999995f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gDPLoadTLUT_pal256(display_list_cabeza++, comun_tlut_arboles_importar);
        gSPDisplayList(display_list_cabeza++, d_circuito_royal_raceway_arbol_dl);
    }
}

void renderizar_arbol_actor_moo_moo_farm(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 6250000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 600.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 5.0f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gDPLoadTLUT_pal256(display_list_cabeza++, comun_tlut_arboles_importar);
        gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_arbol_dl);
    }
}

void funcion_80299864(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 4000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 250000.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 2.79999995f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gDPLoadTLUT_pal256(display_list_cabeza++, comun_tlut_arboles_importar);
        gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_tlut_topo);
    }
}

void renderizar_arbol_actor_bowser_castle(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 4000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 250000.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 2.79999995f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gDPLoadTLUT_pal256(display_list_cabeza++, comun_tlut_arboles_importar);
        gSPDisplayList(display_list_cabeza++, d_circuito_royal_raceway_arbol_castillo_dl);
    }
}

void renderizar_arbusto_actor_bowser_castle(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 640000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 250000.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 2.79999995f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gDPLoadTLUT_pal256(display_list_cabeza++, comun_tlut_arboles_importar);
        gSPDisplayList(display_list_cabeza++, d_circuito_bowsers_castle_arbusto_dl);
    }
}

void renderizar_arbol_actor_frappe_snowland(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 4000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 250000.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 2.79999995f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gSPDisplayList(display_list_cabeza++, d_circuito_frappe_snowland_arbol_dl);
    }
}

void renderizar_cactus1_arbol_actor_kalimari_desert(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 4000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 40000.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 1.0f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desert_cactus1_dl);
    }
}

void renderizar_cactus2_arbol_actor_kalimari_desert(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 4000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 40000.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 1.0f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desert_cactus2_dl);
    }
}

void renderizar_cactus3_arbol_actor_kalimari_desert(Camara* camara, Mat4 parametro1, struct Actor* parametro2) {
    f32 temporal_f0;
    s16 temporal_v0 = parametro2->flags;

    if ((temporal_v0 & 0x800) != 0) {
        return;
    }

    temporal_f0 =
        distancia_si_visible(camara->pos, parametro2->pos, camara->rot[1], 0, acercar_camara[camara - camara1], 4000000.0f);

    if (temporal_f0 < 0.0f) {
        return;
    }

    if (((temporal_v0 & 0x400) == 0) && (temporal_f0 < 40000.0f)) {
        funcion_8029794C(parametro2->pos, parametro2->rot, 0.80000001f);
    }
    parametro1[3][0] = parametro2->pos[0];
    parametro1[3][1] = parametro2->pos[1];
    parametro1[3][2] = parametro2->pos[2];

    if (fijar_posicion_render(parametro1, 0) != 0) {
        gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desert_cactus3_dl);
    }
}
