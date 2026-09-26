// Particulas y onomatopeyas

void renderizar_particulas_suelo_jugador(Jugador* jugador, SIN_USO s8 indice_jugador, s16 parametro2, s8 parametro3) {
    Vec3f pos;
    Vec3s sp_d4;
    s16 prim_rojo;
    s16 verde_prim;
    s16 azul_prim;
    s16 prim_alpha;
    s16 amb_rojo;
    s16 verde_amb;
    s16 azul_amb;

    if ((jugador->pool_particula_1[parametro2].vivo_es == 1) && (jugador->pool_particula_1[parametro2].temporizador != 0)) {
        pos[0] = jugador->pool_particula_1[parametro2].pos[0];
        pos[1] = jugador->pool_particula_1[parametro2].pos[1];
        pos[2] = jugador->pool_particula_1[parametro2].pos[2];
        sp_d4[0] = 0;
        sp_d4[1] = jugador->desconocido_048[parametro3];
        sp_d4[2] = 0;
        funcion_800652D4(pos, sp_d4, jugador->pool_particula_1[parametro2].scale * jugador->size);
        if ((s32) jugador->pool_particula_1[parametro2].tipo_superficie != PASTO) {
            prim_rojo =
                ((dato_800E47DC[jugador->pool_particula_1[parametro2].rojo] >> 0x10) & 0xFF) - jugador->pool_particula_1[parametro2].verde;
            verde_prim =
                ((dato_800E47DC[jugador->pool_particula_1[parametro2].rojo] >> 0x08) & 0xFF) - jugador->pool_particula_1[parametro2].verde;
            azul_prim =
                ((dato_800E47DC[jugador->pool_particula_1[parametro2].rojo] >> 0x00) & 0xFF) - jugador->pool_particula_1[parametro2].verde;
            amb_rojo = ((dato_800E480C[jugador->pool_particula_1[parametro2].rojo] >> 0x10) & 0xFF) - jugador->pool_particula_1[parametro2].verde;
            verde_amb =
                ((dato_800E480C[jugador->pool_particula_1[parametro2].rojo] >> 0x08) & 0xFF) - jugador->pool_particula_1[parametro2].verde;
            azul_amb =
                ((dato_800E480C[jugador->pool_particula_1[parametro2].rojo] >> 0x00) & 0xFF) - jugador->pool_particula_1[parametro2].verde;
            prim_alpha = jugador->pool_particula_1[parametro2].alpha;
            if (jugador->pool_particula_1[parametro2].desconocido_040 == 0) {
                gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
                gDPLoadTextureBlock(display_list_cabeza++, polvo_suelo_cargado, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
                funcion_8004B72C(prim_rojo, verde_prim, azul_prim, amb_rojo, verde_amb, azul_amb, prim_alpha);
                gSPDisplayList(display_list_cabeza++, dato_0D008E48);
            } else {
                gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
                gDPLoadTextureBlock(display_list_cabeza++, polvo_suelo_cargado, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
                funcion_8004B72C(prim_rojo, verde_prim, azul_prim, amb_rojo, verde_amb, azul_amb, prim_alpha);
                gDPSetAlphaCompare(display_list_cabeza++, G_AC_DITHER);
                gSPDisplayList(display_list_cabeza++, dato_0D008E48);
            }
        } else {
            prim_rojo = jugador->pool_particula_1[parametro2].rojo;
            verde_prim = jugador->pool_particula_1[parametro2].verde;
            azul_prim = jugador->pool_particula_1[parametro2].azul;
            gSPDisplayList(display_list_cabeza++, dato_0D008C90);
            gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
            gDPLoadTextureBlock(display_list_cabeza++, particula_pasto_cargado, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            funcion_8004B35C(prim_rojo, verde_prim, azul_prim, 0x000000FF);
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
            gSPVertex(display_list_cabeza++, dato_800E8C00, 4, 0);
            gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        }
        cantidad_efecto_matriz += 1;
    }
}

void funcion_800664E0(Jugador* jugador, SIN_USO s8 indice_jugador, s16 parametro2, s8 parametro3) {
    Vec3f sp54;
    Vec3s sp4_c;
    s16 rojo;
    s16 verde;
    s16 azul;
    s16 alpha;

    if (jugador->pool_particula_1[parametro2].vivo_es == 1) {
        rojo = jugador->pool_particula_1[parametro2].rojo;
        verde = jugador->pool_particula_1[parametro2].verde;
        azul = jugador->pool_particula_1[parametro2].azul;
        alpha = jugador->pool_particula_1[parametro2].alpha;
        sp54[0] = jugador->pool_particula_1[parametro2].pos[0];
        sp54[1] = jugador->pool_particula_1[parametro2].pos[1];
        sp54[2] = jugador->pool_particula_1[parametro2].pos[2];
        sp4_c[0] = 0;
        sp4_c[1] = jugador->desconocido_048[parametro3];
        sp4_c[2] = 0;
        funcion_800652D4(sp54, sp4_c, jugador->pool_particula_1[parametro2].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
        gDPSetAlphaCompare(display_list_cabeza++, G_AC_DITHER);
        gDPLoadTextureBlock(display_list_cabeza++, dato_8018D48C, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        funcion_8004B35C(rojo, verde, azul, alpha);
        gSPDisplayList(display_list_cabeza++, dato_0D008E48);
        cantidad_efecto_matriz += 1;
    }
}

void funcion_80066714(Jugador* jugador, SIN_USO s32 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp5_c;
    Vec3s sp54;
    s16 rojo;
    s16 verde;
    s16 azul;
    s16 alpha;

    if (jugador->pool_particula_1[parametro2].vivo_es == 1) {
        rojo = jugador->pool_particula_1[parametro2].rojo;
        verde = jugador->pool_particula_1[parametro2].verde;
        azul = jugador->pool_particula_1[parametro2].azul;
        alpha = jugador->pool_particula_1[parametro2].alpha;
        sp5_c[0] = jugador->pool_particula_1[parametro2].pos[0];
        sp5_c[1] = jugador->pool_particula_1[parametro2].pos[1];
        sp5_c[2] = jugador->pool_particula_1[parametro2].pos[2];
        sp54[0] = 0;
        sp54[1] = jugador->desconocido_048[parametro3];
        sp54[2] = 0;
        funcion_800652D4(sp5_c, sp54, jugador->pool_particula_1[parametro2].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008C90);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
        gDPLoadTextureBlock(display_list_cabeza++, comun_textura_particula_fuego, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        funcion_8004B35C(rojo, verde, azul, alpha);
        gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);
        gSPVertex(display_list_cabeza++, dato_800E8B00, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz += 1;
    }
}

void funcion_80066998(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp54;
    Vec3s sp4_c;
    s16 rojo;
    s16 verde;
    s16 azul;
    s16 alpha;

    if (jugador->pool_particula_0[parametro2].vivo_es == 1) {
        rojo = jugador->pool_particula_0[parametro2].rojo;
        verde = jugador->pool_particula_0[parametro2].verde;
        azul = jugador->pool_particula_0[parametro2].azul;
        alpha = jugador->pool_particula_0[parametro2].alpha;
        sp54[0] = jugador->pool_particula_0[parametro2].pos[0];
        sp54[1] = jugador->pool_particula_0[parametro2].pos[1];
        sp54[2] = jugador->pool_particula_0[parametro2].pos[2];
        sp4_c[0] = 0x4000;
        sp4_c[1] = jugador->desconocido_048[parametro3];
        sp4_c[2] = 0;
        funcion_800652D4(sp54, sp4_c, jugador->pool_particula_0[parametro2].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
        gDPLoadTextureBlock(display_list_cabeza++, dato_8018D48C, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        funcion_8004B35C(rojo, verde, azul, alpha);
        gSPDisplayList(display_list_cabeza++, dato_0D008E48);
        cantidad_efecto_matriz += 1;
    }
}

void funcion_80066BAC(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp_dc;
    Vec3s sp_d4;
    SIN_USO s32 margen_pila;

    if ((jugador->pool_particula_0[parametro2].vivo_es == 1) && (jugador->pool_particula_0[parametro2].rojo != 0x00FF)) {

        if (jugador->colision.distancia_superficie[2] >= 300.0f) {
            sp_dc[1] = jugador->pos[1] + 5.0f;
        } else {
            sp_dc[1] = jugador->pos[1] - 3.0f;
        }
        sp_dc[2] = jugador->pos[2] + (coss(jugador->desconocido_048[parametro3]) * -10.0f);
        sp_dc[0] = jugador->pos[0] + (senos(jugador->desconocido_048[parametro3]) * -10.0f);
        if (jugador->colision.distancia_superficie[2] >= 300.0f) {
            sp_d4[0] = camaras[parametro3].rot[0] - GRADOS(90);
        } else {
            sp_d4[0] = 0;
        }
        sp_d4[1] = jugador->desconocido_048[parametro3];
        sp_d4[2] = 0;
        funcion_800652D4(sp_dc, sp_d4, jugador->pool_particula_0[parametro2].scale * jugador->size);
        if (jugador->pool_particula_0[parametro2].rojo == 0) {
            gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
            gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
            gDPLoadTextureBlock(display_list_cabeza++, textura_cargado_rayo_0, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPVertex(display_list_cabeza++, &dato_800E8900[0][jugador->pool_particula_0[parametro2].rojo], 4, 0);
            gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
            gDPLoadTextureBlock(display_list_cabeza++, textura_cargado_rayo_1, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPVertex(display_list_cabeza++, &dato_800E8900[1][jugador->pool_particula_0[parametro2].rojo], 4, 0);
            gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        } else {
            gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
            gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
            gDPLoadTextureBlock(display_list_cabeza++, textura_cargado_rayo_1, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPVertex(display_list_cabeza++, &dato_800E8900[0][jugador->pool_particula_0[parametro2].rojo], 4, 0);
            gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
            gDPLoadTextureBlock(display_list_cabeza++, textura_cargado_rayo_0, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPVertex(display_list_cabeza++, &dato_800E8900[1][jugador->pool_particula_0[parametro2].rojo], 4, 0);
            gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        }
        cantidad_efecto_matriz += 1;
    }
}

void funcion_80067280(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp7_c;
    Vec3s sp74;
    s16 rojo;
    s16 verde;
    s16 azul;
    s16 alpha;

    if (jugador->pool_particula_3[parametro2].vivo_es == 1) {
        rojo = jugador->pool_particula_3[parametro2].rojo;
        verde = jugador->pool_particula_3[parametro2].verde;
        azul = jugador->pool_particula_3[parametro2].azul;
        alpha = jugador->pool_particula_3[parametro2].alpha;
        sp7_c[0] = jugador->pool_particula_3[parametro2].pos[0];
        sp7_c[1] = jugador->pool_particula_3[parametro2].pos[1];
        sp7_c[2] = jugador->pool_particula_3[parametro2].pos[2];
        sp74[0] = -0x071C;
        sp74[2] = 0;
        if (jugador->pool_particula_3[parametro2].desconocido_010 == 1) {
            sp74[1] = jugador->desconocido_048[parametro3] - 0x2000;
            funcion_800652D4(sp7_c, sp74, jugador->pool_particula_3[parametro2].scale * jugador->size);
            gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
            gDPLoadTextureBlock(display_list_cabeza++, dato_8018D48C, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            funcion_8004B35C(rojo, verde, azul, alpha);
            gSPDisplayList(display_list_cabeza++, dato_0D008E70);
        } else {
            sp74[1] = jugador->desconocido_048[parametro3] + 0x2000;
            funcion_800652D4(sp7_c, sp74, jugador->pool_particula_3[parametro2].scale * jugador->size);
            gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
            gDPLoadTextureBlock(display_list_cabeza++, dato_8018D48C, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            funcion_8004B35C(rojo, verde, azul, alpha & 0xFFFFFFFF);
            gSPDisplayList(display_list_cabeza++, dato_0D008E48);
        }
        cantidad_efecto_matriz += 1;
    }
}

void renderizar_jugador_impulso_chispa_particulas(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp8_c;
    Vec3s sp84;
    SIN_USO s32 margen_pila[4];

    if (jugador->pool_particula_3[parametro2].vivo_es == 1) {
        sp8_c[0] = jugador->pool_particula_3[parametro2].pos[0];
        sp8_c[1] = jugador->pool_particula_3[parametro2].pos[1];
        sp8_c[2] = jugador->pool_particula_3[parametro2].pos[2];
        sp84[0] = 0;
        sp84[1] = jugador->desconocido_048[parametro3];
        sp84[2] = 0;
        funcion_800652D4(sp8_c, sp84, jugador->pool_particula_3[parametro2].scale * jugador->size);
        if (jugador->pool_particula_3[parametro2].desconocido_010 == 1) {
            gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
            gDPLoadTextureBlock(display_list_cabeza++, comun_textura_particula_chispa, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            funcion_8004B72C(0x000000FF, 0x000000FF, 0x000000DF, 0x000000FF, 0x0000005F, 0, 0x00000060);
            gSPDisplayList(display_list_cabeza++, dato_0D008E70);
        } else {
            gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
            gDPLoadTextureBlock(display_list_cabeza++, comun_textura_particula_chispa, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            funcion_8004B72C(0x000000FF, 0x000000FF, 0x000000DF, 0x000000FF, 0x0000005F, 0, 0x00000060);
            gSPDisplayList(display_list_cabeza++, dato_0D008E48);
        }
        cantidad_efecto_matriz += 1;
    }
}

void renderizar_whrrrr_onomatopeya_jugador(Jugador* jugador, SIN_USO s8 parametro1, f32 parametro2, SIN_USO s8 parametro3, s8 parametro4) {
    Vec3f sp9_c;
    Vec3s sp94;
    SIN_USO s32 margen_pila[2];

    if (jugador->pool_particula_2[parametro4].vivo_es == 1) {
        sp9_c[0] = jugador->pool_particula_2[parametro4].pos[0];
        sp9_c[1] = jugador->pool_particula_2[parametro4].pos[1];
        sp9_c[2] = jugador->pool_particula_2[parametro4].pos[2];
        sp94[0] = 0;
        sp94[1] = jugador->pool_particula_2[parametro4].rotacion;
        sp94[2] = 0;
        funcion_800652D4(sp9_c, sp94, jugador->size * parametro2);
        gSPDisplayList(display_list_cabeza++, dato_0D008C90);
        gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
        gDPLoadTLUT_pal256(display_list_cabeza++, dato_800E52D0);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
        gDPLoadTextureBlock(display_list_cabeza++, textura_whrrrr_onomatopeya_cargado_1, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(display_list_cabeza++, dato_800E8840, 4, 0);
        gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
        gDPLoadTextureBlock(display_list_cabeza++, textura_whrrrr_onomatopeya_cargado_2, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(display_list_cabeza++, dato_800E8800, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz += 1;
    }
}

void renderizar_burbuja_voz_jugador(Jugador* jugador, s8 parametro1, u8* textura, s8 parametro3, f32 parametro4, s32 parametro5) {
    Vec3f sp7_c;
    Vec3s sp74;
    f32 sp54[8] = { 0.0f, -1.2f, 0.1f, 1.2f, -1.7f, -0.8f, -0.2f, -1.9f };
    s16 rojo = ((parametro5 >> 0x10) & 0xFF) & 0xFF;
    s16 verde = ((parametro5 >> 0x08) & 0xFF) & 0xFF;
    s16 azul = ((parametro5 >> 0x00) & 0xFF) & 0xFF;

    if (jugador->pool_particula_2[parametro3].vivo_es == 1) {
        sp74[0] = 0;
        sp74[1] = jugador->desconocido_048[parametro1];
        sp74[2] = 0;
        sp7_c[0] = jugador->pos[0] + (senos((0x4000 & 0xFFFFFFFF) - (jugador->rotacion[1] + jugador->desconocido_0C0)) * parametro4);
        sp7_c[1] = jugador->pos[1] + jugador->tamanio_caja_envolvente - sp54[jugador->id_personaje] - 2.0f;
        sp7_c[2] = jugador->pos[2] + (coss((0x4000 & 0xFFFFFFFF) - (jugador->rotacion[1] + jugador->desconocido_0C0)) * parametro4);
        funcion_800652D4(sp7_c, sp74, jugador->pool_particula_2[parametro3].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
        gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        funcion_8004B414(rojo, verde, azul, 0x000000FF);
        gSPDisplayList(display_list_cabeza++, dato_0D008E20);
        cantidad_efecto_matriz += 1;
    }
}

void renderizar_nota_musica(Jugador* jugador, s8 parametro1, u8* textura, s8 parametro3, f32 parametro4, s32 parametro5) {
    Vec3f sp7_c;
    Vec3s sp74;
    f32 sp54[8] = { -0.7f, -1.9f, -0.6f, 0.4f, -2.5f, -1.6f, -0.95f, -2.7f };
    s16 rojo = ((parametro5 >> 0x10) & 0xFF) & 0xFF;
    s16 verde = ((parametro5 >> 0x08) & 0xFF) & 0xFF;
    s16 azul = ((parametro5 >> 0x00) & 0xFF) & 0xFF;

    if (jugador->pool_particula_2[parametro3].vivo_es == 1) {
        sp74[0] = 0;
        sp74[1] = jugador->desconocido_048[parametro1];
        sp74[2] = 0;
        sp7_c[0] = jugador->pos[0] + (senos((0x4000 & 0xFFFFFFFF) - (jugador->rotacion[1] + jugador->desconocido_0C0)) * parametro4);
        sp7_c[1] = jugador->pos[1] + jugador->tamanio_caja_envolvente - sp54[jugador->id_personaje] - 2.0f;
        sp7_c[2] = jugador->pos[2] + (coss((0x4000 & 0xFFFFFFFF) - (jugador->rotacion[1] + jugador->desconocido_0C0)) * parametro4);
        funcion_800652D4(sp7_c, sp74, jugador->pool_particula_2[parametro3].scale * jugador->size * 0.8);
        gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
        gDPLoadTextureBlock(display_list_cabeza++, textura, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        funcion_8004B414(rojo, verde, azul, 0x000000FF);
        gSPDisplayList(display_list_cabeza++, dato_0D008E20);
        cantidad_efecto_matriz += 1;
    }
}

void renderizar_error_onomatopeya_jugador(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO f32 parametro2, s8 parametro3, s8 parametro4) {
    SIN_USO s32 margen_pila[16];
    Vec3f sp9_c;
    Vec3s sp94;

    if (jugador->pool_particula_2[parametro4].vivo_es == 1) {
        sp9_c[1] = jugador->pool_particula_2[parametro4].pos[1];
        sp9_c[2] = jugador->pos[2] + (coss(jugador->desconocido_048[parametro3]) * -10.0f);
        sp9_c[0] = jugador->pos[0] + (senos(jugador->desconocido_048[parametro3]) * -10.0f);
        sp94[0] = 0;
        sp94[1] = jugador->desconocido_048[parametro3];
        sp94[2] = 0;
        funcion_800652D4(sp9_c, sp94, jugador->pool_particula_2[parametro4].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008C90);
        gDPLoadTLUT_pal256(display_list_cabeza++, dato_800E52D0);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
        gDPLoadTextureBlock(display_list_cabeza++, textura_error_onomatopeya_cargado_1, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(display_list_cabeza++, dato_800E8880, 4, 0);
        gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
        gDPLoadTextureBlock(display_list_cabeza++, textura_error_onomatopeya_cargado_2, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(display_list_cabeza++, dato_800E88C0, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz += 1;
    }
}

void funcion_80068724(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO f32 parametro2, s8 parametro3, s8 parametro4) {
    SIN_USO s32 margen_pila[16];
    Vec3f sp84;
    Vec3s sp7_c;

    if (jugador->pool_particula_2[parametro4].vivo_es == 1) {
        sp84[1] = jugador->pos[1] - 3.0f;
        sp84[2] = jugador->pos[2] + (coss(jugador->desconocido_048[parametro3]) * -10.0f);
        sp84[0] = jugador->pos[0] + (senos(jugador->desconocido_048[parametro3]) * -10.0f);
        sp7_c[0] = 0;
        sp7_c[1] = jugador->desconocido_048[parametro3];
        sp7_c[2] = 0;
        funcion_800652D4(sp84, sp7_c, jugador->pool_particula_2[parametro4].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
        gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
        gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        gDPLoadTextureBlock(display_list_cabeza++, textura_cargado_rayo_0, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSPVertex(display_list_cabeza++, dato_800E8A00, 4, 0);
        gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
        gDPLoadTextureBlock(display_list_cabeza++, textura_cargado_rayo_1, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSPVertex(display_list_cabeza++, dato_800E8A40, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz += 1;
    }
}

void renderizar_boing_onomatopeya_jugador(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO f32 parametro2, s8 parametro3, s8 parametro4) {
    Vec3f sp64;
    Vec3s sp5_c;

    if ((jugador->pool_particula_2[parametro4].vivo_es == 1) && (jugador->anim_frame_selector[parametro3] < 0xD)) {
        sp64[1] = jugador->pos[1] - 3.0f;
        sp64[2] = jugador->pos[2] + ((-2.5 * jugador->pool_particula_2[parametro4].temporizador) * coss(jugador->desconocido_048[parametro3]));
        sp64[0] = jugador->pos[0] + ((-2.5 * jugador->pool_particula_2[parametro4].temporizador) * senos(jugador->desconocido_048[parametro3]));
        sp5_c[0] = 0;
        sp5_c[1] = jugador->desconocido_048[parametro3];
        sp5_c[2] = 0;
        funcion_800652D4(sp64, sp5_c, jugador->pool_particula_2[parametro4].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008D58);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
        gDPLoadTextureBlock(display_list_cabeza++, dato_8018D4A0, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        funcion_8004B35C(0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF);
        gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        gSPVertex(display_list_cabeza++, dato_800E8B40, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz += 1;
    }
}

void renderizar_pomp_onomatopeya_jugador(Jugador* jugador, SIN_USO s8 parametro1, SIN_USO f32 parametro2, s8 parametro3, s8 parametro4) {
    Vec3f sp9_c;
    Vec3s sp94;

    if ((jugador->pool_particula_2[parametro4].vivo_es == 1) && ((s32) jugador->anim_frame_selector[parametro3] < 0xD)) {
        sp9_c[1] = (jugador->pos[1] - 3.0f) + jugador->pool_particula_2[parametro4].pos[1];
        sp9_c[2] = jugador->pos[2] + (coss(jugador->desconocido_048[parametro3]) * -10.0f);
        sp9_c[0] = jugador->pos[0] + (senos(jugador->desconocido_048[parametro3]) * -10.0f);
        sp94[0] = 0;
        sp94[1] = jugador->desconocido_048[parametro3];
        sp94[2] = 0;
        funcion_800652D4(sp9_c, sp94, jugador->pool_particula_2[parametro4].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008C90);
        gDPLoadTLUT_pal256(display_list_cabeza++, dato_800E52D0);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
        gDPLoadTextureBlock(display_list_cabeza++, textura_poomp_onomatopeya_cargado_1, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSPVertex(display_list_cabeza++, dato_800E8B80, 4, 0);
        gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
        gDPLoadTextureBlock(display_list_cabeza++, textura_poomp_onomatopeya_cargado_2, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSPVertex(display_list_cabeza++, dato_800E8BC0, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz += 1;
    }
}

void renderizar_particulas_golpe_actor(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp5_c;
    Vec3s sp54;
    s16 alpha;

    if (jugador->pool_particula_3[parametro2].vivo_es == 1) {
        alpha = jugador->pool_particula_3[parametro2].alpha;
        sp5_c[0] = jugador->pool_particula_3[parametro2].pos[0];
        sp5_c[1] = jugador->pool_particula_3[parametro2].pos[1];
        sp5_c[2] = jugador->pool_particula_3[parametro2].pos[2];
        sp54[0] = 0;
        sp54[1] = jugador->desconocido_048[parametro3];
        jugador->pool_particula_3[parametro2].verde += 0x1C71;
        sp54[2] = jugador->pool_particula_3[parametro2].verde;
        funcion_800652D4(sp5_c, sp54, jugador->size * 0.5);
        gSPDisplayList(display_list_cabeza++, dato_0D008D58);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
        gDPLoadTextureBlock(display_list_cabeza++, dato_8018D488, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        funcion_8004B35C(0xFF, 0xFF, 0, alpha);
        gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        gSPVertex(display_list_cabeza++, dato_800E87C0, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz++;
    }
}

void funcion_80069444(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp74;
    Vec3s sp6_c;
    s16 prim_rojo;
    s16 verde_prim;
    s16 azul_prim;
    s16 prim_alpha;
    s16 amb_rojo;
    s16 verde_amb;
    s16 azul_amb;
    u16 probar;
    if (jugador->pool_particula_3[parametro2].vivo_es == 1) {
        prim_rojo = (dato_800E47DC[jugador->pool_particula_3[parametro2].rojo] >> 0x10) & 0xFF;
        verde_prim = (dato_800E47DC[jugador->pool_particula_3[parametro2].rojo] >> 8) & 0xFF;
        azul_prim = dato_800E47DC[jugador->pool_particula_3[parametro2].rojo] & 0xFF;

        amb_rojo = (dato_800E480C[jugador->pool_particula_3[parametro2].rojo] >> 0x10) & 0xFF;
        verde_amb = (dato_800E480C[jugador->pool_particula_3[parametro2].rojo] >> 8) & 0xFF;
        azul_amb = dato_800E480C[jugador->pool_particula_3[parametro2].rojo] & 0xFF;
        prim_alpha = jugador->pool_particula_3[parametro2].alpha;

        sp74[0] = jugador->pool_particula_3[parametro2].pos[0];
        sp74[1] = jugador->pool_particula_3[parametro2].pos[1];
        sp74[2] = jugador->pool_particula_3[parametro2].pos[2];
        sp6_c[0] = 0;
        sp6_c[1] = jugador->desconocido_048[parametro3];
        sp6_c[2] = 0;
        funcion_800652D4(sp74, sp6_c, jugador->size * 1.5);
        gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
        gDPLoadTextureBlock(display_list_cabeza++, polvo_suelo_cargado, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        probar = amb_rojo;
        funcion_8004B72C(prim_rojo, verde_prim, azul_prim, (s16) probar, verde_amb, azul_amb, prim_alpha);
        gSPDisplayList(display_list_cabeza++, dato_0D008E48);
        cantidad_efecto_matriz += 1;
    }
}

void renderizar_pared_golpe_estrella_particulas(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3, f32 parametro4) {
    Vec3f sp5_c;
    Vec3s sp54;
    s16 alpha;

    if (jugador->pool_particula_3[parametro2].vivo_es == 1) {
        alpha = jugador->pool_particula_3[parametro2].alpha;
        sp5_c[0] = jugador->pool_particula_3[parametro2].pos[0];
        sp5_c[1] = jugador->pool_particula_3[parametro2].pos[1];
        sp5_c[2] = jugador->pool_particula_3[parametro2].pos[2];
        sp54[0] = 0;
        sp54[1] = jugador->desconocido_048[parametro3];
        sp54[2] = 0;
        funcion_800652D4(sp5_c, sp54, jugador->size * parametro4);
        gSPDisplayList(display_list_cabeza++, dato_0D008D58);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
        gDPLoadTextureBlock(display_list_cabeza++, dato_8018D488, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        funcion_8004B35C(0x000000FF, 0x000000FF, 0, alpha);
        gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        gSPVertex(display_list_cabeza++, dato_800E87C0, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz += 1;
    }
}

void funcion_80069938(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp5_c;
    Vec3s sp54;
    s16 alpha;

    if (jugador->pool_particula_3[parametro2].vivo_es == 1) {
        alpha = jugador->pool_particula_3[parametro2].alpha;
        sp5_c[0] = jugador->pool_particula_3[parametro2].pos[0];
        sp5_c[1] = jugador->pool_particula_3[parametro2].pos[1];
        sp5_c[2] = jugador->pool_particula_3[parametro2].pos[2];
        sp54[0] = 0;
        sp54[1] = jugador->desconocido_048[parametro3];
        sp54[2] = jugador->pool_particula_3[parametro2].rojo;
        funcion_800652D4(sp5_c, sp54, jugador->pool_particula_3[parametro2].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008D58);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
        gDPLoadTextureBlock(display_list_cabeza++, dato_8018D488, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        funcion_8004B35C(0x000000FF, 0x000000FF, 0, alpha);
        gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        gSPVertex(display_list_cabeza++, dato_800E87C0, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz += 1;
    }
}

void funcion_80069BA8(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp54;
    Vec3s sp4_c;
    s16 rojo;
    s16 verde;
    s16 azul;
    s16 alpha;

    if (jugador->pool_particula_3[parametro2].vivo_es == 1) {
        rojo = jugador->pool_particula_3[parametro2].rojo;
        verde = jugador->pool_particula_3[parametro2].verde;
        azul = jugador->pool_particula_3[parametro2].azul;
        alpha = jugador->pool_particula_3[parametro2].alpha;
        sp54[0] = jugador->pool_particula_3[parametro2].pos[0];
        sp54[1] = jugador->pool_particula_3[parametro2].pos[1];
        sp54[2] = jugador->pool_particula_3[parametro2].pos[2];
        sp4_c[0] = 0;
        sp4_c[1] = jugador->desconocido_048[parametro3];
        sp4_c[2] = 0;
        funcion_800652D4(sp54, sp4_c, jugador->pool_particula_3[parametro2].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
        gDPLoadTextureBlock(display_list_cabeza++, dato_8018D48C, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        funcion_8004B35C(rojo, verde, azul, alpha);
        gSPDisplayList(display_list_cabeza++, dato_0D008E48);
        cantidad_efecto_matriz += 1;
    }
}

void funcion_80069DB8(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp5_c;
    Vec3s sp54;
    SIN_USO s32 margen_pila[2];

    if (jugador->pool_particula_3[parametro2].vivo_es == 1) {
        sp5_c[0] = jugador->pool_particula_3[parametro2].pos[0];
        sp5_c[1] = jugador->pool_particula_3[parametro2].pos[1];
        sp5_c[2] = jugador->pool_particula_3[parametro2].pos[2];
        sp54[0] = 0;
        sp54[1] = jugador->desconocido_048[parametro3];
        sp54[2] = 0;
        funcion_800652D4(sp5_c, sp54, jugador->pool_particula_3[parametro2].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008D58);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
        gDPLoadTextureBlock(display_list_cabeza++, dato_8018D49C, G_IM_FMT_IA, G_IM_SIZ_16b, 16, 16, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        funcion_8004B35C(0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF);
        gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        gSPVertex(display_list_cabeza++, dato_800E8740, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz += 1;
    }
}

void funcion_8006A01C(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp54;
    Vec3s sp4_c;

    if (jugador->pool_particula_0[parametro2].vivo_es == 1) {
        sp54[0] = jugador->pool_particula_1[parametro2].pos[0];
        sp54[1] = jugador->pool_particula_1[parametro2].pos[1];
        sp54[2] = jugador->pool_particula_1[parametro2].pos[2];
        sp4_c[0] = 0;
        sp4_c[1] = jugador->desconocido_048[parametro3];
        sp4_c[2] = 0;
        funcion_800652D4(sp54, sp4_c, jugador->pool_particula_1[parametro2].scale * jugador->size);

        gSPDisplayList(display_list_cabeza++, dato_0D008D58);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
        gDPLoadTextureBlock(display_list_cabeza++, dato_8018D49C, G_IM_FMT_IA, G_IM_SIZ_16b, 16, 16, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        funcion_8004B35C(0xFF, 0xFF, 0xFF, 0xFF);
        gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        gSPVertex(display_list_cabeza++, dato_0D008B78, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz++;
    }
}

void funcion_8006A280(Jugador* jugador, SIN_USO s8 parametro1, s16 parametro2, s8 parametro3) {
    Vec3f sp5_c;
    Vec3s sp54;
    s16 rojo;
    s16 verde;
    s16 azul;

    if (jugador->pool_particula_0[parametro2].vivo_es == 1) {
        rojo = jugador->pool_particula_0[parametro2].rojo;
        verde = jugador->pool_particula_0[parametro2].verde;
        azul = jugador->pool_particula_0[parametro2].azul;
        sp5_c[0] = jugador->pool_particula_0[parametro2].pos[0];
        sp5_c[1] = jugador->pool_particula_0[parametro2].pos[1];
        sp5_c[2] = jugador->pool_particula_0[parametro2].pos[2];
        sp54[0] = 0;
        sp54[1] = jugador->desconocido_048[parametro3];
        sp54[2] = 0;
        funcion_800652D4(sp5_c, sp54, jugador->pool_particula_0[parametro2].scale * jugador->size);
        gSPDisplayList(display_list_cabeza++, dato_0D008D58);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
        gDPLoadTextureBlock_4b(display_list_cabeza++, *dato_800E47A0[jugador->pool_particula_0[parametro2].temporizador], G_IM_FMT_I, 64, 64,
                               0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
        funcion_8004B414(rojo, verde, azul, 0x000000FF);
        gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        gSPVertex(display_list_cabeza++, dato_800E8780, 4, 0);
        gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
        cantidad_efecto_matriz += 1;
    }
}

void inicializar_globo(Jugador* jugador, f32 parametro1, f32 parametro2, s8 indice_jugador, s8 indice_globo, s16 rotacion) {
    f32 algun_x;
    f32 algun_y;
    f32 algun_z;

    situacion_globo_jugador[indice_jugador][indice_globo] = IDO_SITUACION_GLOBO;
    dato_8018D650[indice_jugador][indice_globo] = 0.1f;
    dato_8018D6B0[indice_jugador][indice_globo] = 0.0f;
    dato_8018D710[indice_jugador][indice_globo] = 0.0f;
    dato_8018D770[indice_jugador][indice_globo] = 0;
    dato_8018D7A0[indice_jugador][indice_globo] = 0;
    dato_8018D7D0[indice_jugador][indice_globo] = 0;
    dato_8018D800[indice_jugador][indice_globo] = 5;
    dato_8018D830[indice_jugador][indice_globo] = 1;
    dato_8018D620[indice_jugador][indice_globo] = -jugador->rotacion[1] - jugador->desconocido_0C0;
    funcion_80062B18(&algun_x, &algun_y, &algun_z, parametro1, 4.0f, parametro2 + -3.8, -jugador->rotacion[1], 0);
    pos_x_globo_jugador[indice_jugador][indice_globo] = jugador->pos[0] + algun_x;
    pos_z_globo_jugador[indice_jugador][indice_globo] = jugador->pos[2] + algun_z;
    pos_y_globo_jugador[indice_jugador][indice_globo] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + algun_y;
    situacion_globo_jugador[indice_jugador][indice_globo] |= PRESENTE_SITUACION_GLOBO;
    rotacion_globo_jugador[indice_jugador][indice_globo] = rotacion;
    dato_8018D890[indice_jugador][indice_globo] = 0;
}

void actualizar_posicion_globo_jugador_uno(Jugador* jugador, f32 parametro1, f32 parametro2, s8 id_jugador, s8 id_globo) {
    f32 sp80[] = {
        9.0f, 10.0f, 9.0f, 8.0f, 10.0f, 9.5f, 9.5f, 11.0f,
    };
    SIN_USO s32 margen_pila_0;
    f32 algun_x;
    f32 algun_y;
    f32 algun_z;
    f32 sp6_c;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;

    sp6_c = (-(jugador->speed / 18.0f) * 216.0f) / 10.0f;
    if ((situacion_globo_jugador[id_jugador][id_globo] & 2) != 2) {
        dato_8018D650[id_jugador][id_globo] += -0.003 + (-jugador->speed * 0.0006);
        if (dato_8018D650[id_jugador][id_globo] >= 0.05) {
            dato_8018D650[id_jugador][id_globo] = 0.05f;
        }
        if (dato_8018D650[id_jugador][id_globo] <= -0.05) {
            dato_8018D650[id_jugador][id_globo] = -0.05f;
        }
        dato_8018D6B0[id_jugador][id_globo] += dato_8018D650[id_jugador][id_globo];
        if (dato_8018D6B0[id_jugador][id_globo] >= 0.06) {
            dato_8018D6B0[id_jugador][id_globo] = 0.06f;
        }
        if (dato_8018D6B0[id_jugador][id_globo] <= -0.06) {
            dato_8018D6B0[id_jugador][id_globo] = -0.06f;
        }
        dato_8018D710[id_jugador][id_globo] += dato_8018D6B0[id_jugador][id_globo];
        if (dato_8018D710[id_jugador][id_globo] < 0.0f) {
            dato_8018D650[id_jugador][id_globo] = int_aleatorio(0x000BU) / 10;
            dato_8018D6B0[id_jugador][id_globo] = 0.0f;
            dato_8018D710[id_jugador][id_globo] = 0.0f;
        }
        dato_8018D620[id_jugador][id_globo] = -jugador->rotacion[1] - jugador->desconocido_0C0;
        mover_s16_hacia(&dato_8018D890[id_jugador][id_globo], jugador->speed * (f32) GRADOS(1), 0.1f);
    }
    if (dato_8018D830[id_jugador][id_globo] == 1) {
        dato_8018D770[id_jugador][id_globo] += dato_8018D800[id_jugador][id_globo] - jugador->speed;
    } else {
        dato_8018D770[id_jugador][id_globo] += dato_8018D800[id_jugador][id_globo] + jugador->speed;
    }
    if (dato_8018D770[id_jugador][id_globo] >= 0xB) {
        dato_8018D770[id_jugador][id_globo] = 0x000B;
    }
    if (dato_8018D770[id_jugador][id_globo] < -0xA) {
        dato_8018D770[id_jugador][id_globo] = -0x000B;
    }
    dato_8018D7A0[id_jugador][id_globo] += dato_8018D770[id_jugador][id_globo];
    if (dato_8018D7A0[id_jugador][id_globo] >= 0x29) {
        dato_8018D7A0[id_jugador][id_globo] = 0x0029;
    }
    if (dato_8018D7A0[id_jugador][id_globo] < -0x28) {
        dato_8018D7A0[id_jugador][id_globo] = -0x0029;
    }
    dato_8018D7D0[id_jugador][id_globo] += dato_8018D7A0[id_jugador][id_globo];
    if (dato_8018D7D0[id_jugador][id_globo] >= 0x38E) {
        dato_8018D800[id_jugador][id_globo] = -int_aleatorio(8U);
        if (dato_8018D830[id_jugador][id_globo] != 1) {
            dato_8018D830[id_jugador][id_globo] = 1;
        }
    }
    if (dato_8018D7D0[id_jugador][id_globo] < -0x38D) {
        dato_8018D800[id_jugador][id_globo] = int_aleatorio(8U);
        if (dato_8018D830[id_jugador][id_globo] != -1) {
            dato_8018D830[id_jugador][id_globo] = -1;
        }
    }
    funcion_80062B18(&algun_x, &algun_y, &algun_z, parametro1, sp80[jugador->id_personaje] - dato_8018D710[id_jugador][id_globo],
                  parametro2 + -3.2 + (sp6_c * 1), -dato_8018D620[id_jugador][id_globo], -jugador->desconocido_206 * 2);
    if ((situacion_globo_jugador[id_jugador][id_globo] & 2) != 2) {
        pos_y_globo_jugador[id_jugador][id_globo] = (jugador->pos[1] - jugador->tamanio_caja_envolvente) + algun_y;
        pos_x_globo_jugador[id_jugador][id_globo] = jugador->pos[0] + algun_x;
        pos_z_globo_jugador[id_jugador][id_globo] = jugador->pos[2] + algun_z;
        jugador_globo_partiendo_temporizador[id_jugador][id_globo] = 0;
    } else {
        pos_y_globo_jugador[id_jugador][id_globo] += 0.2;
        jugador_globo_partiendo_temporizador[id_jugador][id_globo] += 1;
        mover_s16_hacia(&dato_8018D890[id_jugador][id_globo], 0, 0.1f);
        mover_s16_hacia(&rotacion_globo_jugador[id_jugador][id_globo], 0, 0.1f);
        if (jugador_globo_partiendo_temporizador[id_jugador][id_globo] >= 0x78) {
            fijar_globo_jugador_a_ido((s32) jugador, id_jugador, id_globo);
        }
    }
}
