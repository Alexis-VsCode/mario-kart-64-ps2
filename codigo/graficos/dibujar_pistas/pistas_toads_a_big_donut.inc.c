// Pistas toads a big donut

void renderizar_toads_turnpike(struct desconocido_struct_800DC5EC* parametro0) {
    SIN_USO s32 relleno[13];

    fijar_iluminacion_circuito(dato_800DC610, dato_802B87D4, 0, 1);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gDPSetFogColor(display_list_cabeza++, dato_801625EC, dato_801625F4, dato_801625F0, 0xFF);
    gDPSetCycleType(display_list_cabeza++, G_CYC_2CYCLE);
    gSPFogPosition(display_list_cabeza++, dato_802B87B0, dato_802B87B4);
    gSPSetGeometryMode(display_list_cabeza++, G_FOG);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEI, G_CC_PASS2);
    gDPSetRenderMode(display_list_cabeza++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);

    renderizar_segmentos_circuito((uintptr_t) d_circuito_toads_turnpike_lista_dl, parametro0);

    gDPSetRenderMode(display_list_cabeza++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2);
    gDPSetCombineMode(display_list_cabeza++, G_CC_DECALRGBA, G_CC_PASS2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000000));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000068));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070000D8));
    gSPClearGeometryMode(display_list_cabeza++, G_FOG);
    gDPSetCycleType(display_list_cabeza++, G_CYC_1CYCLE);
}

void renderizar_kalimari_desert(struct desconocido_struct_800DC5EC* parametro0) {

    fijar_iluminacion_circuito(dato_800DC610, dato_802B87D4, 0, 1);

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);

    if (funcion_80290C20(parametro0->camara) == 1) {
        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070071C8));
    }

    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    renderizar_segmentos_circuito((uintptr_t) kalimari_desert_dls, parametro0);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07001ED8));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07001B18));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07008330));
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000998));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000270));
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void renderizar_sherbet_land(struct desconocido_struct_800DC5EC* parametro0) {

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    renderizar_segmentos_circuito((uintptr_t) sherbet_land_dls, parametro0);
}

void renderizar_rainbow_road(SIN_USO struct desconocido_struct_800DC5EC* parametro0) {

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

void renderizar_wario_stadium(struct desconocido_struct_800DC5EC* parametro0) {
    s16 frame_ant;

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    if (funcion_80290C20(parametro0->camara) == 1) {

        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x0700A0C8));
    }
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATERGBA, G_CC_MODULATERGBA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    renderizar_segmentos_circuito((uintptr_t) wario_stadium_dls, parametro0);

    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x0700A228));
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000A88));
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);

    dato_800DC5DC = 88;
    dato_800DC5E0 = 72;
    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
        frame_ant = (s16) s_framebuffer_renderizado - 1;
        if (frame_ant < 0) {
            frame_ant = 2;
        } else if (frame_ant >= 3) {
            frame_ant = 0;
        }
        seccion_pantalla_actual++;
        if (seccion_pantalla_actual > 5) {
            seccion_pantalla_actual = 0;
        }
        switch (seccion_pantalla_actual) {
            case 0:
                copiar_framebuffer(dato_800DC5DC, dato_800DC5E0, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x8800));
                break;
            case 1:
                copiar_framebuffer(dato_800DC5DC + 64, dato_800DC5E0, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x9800));
                break;
            case 2:
                copiar_framebuffer(dato_800DC5DC, dato_800DC5E0 + 32, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0xA800));
                break;
            case 3:
                copiar_framebuffer(dato_800DC5DC + 64, dato_800DC5E0 + 32, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0xB800));
                break;
            case 4:
                copiar_framebuffer(dato_800DC5DC, dato_800DC5E0 + 64, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0xC800));
                break;
            case 5:
                copiar_framebuffer(dato_800DC5DC + 64, dato_800DC5E0 + 64, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0xD800));
                break;
        }
    }
}

void renderizar_block_fort(SIN_USO struct desconocido_struct_800DC5EC* parametro0) {

    fijar_iluminacion_circuito(dato_800DC610, dato_802B87D4, 0, 1);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070015C0));
}

void renderizar_skyscraper(SIN_USO struct desconocido_struct_800DC5EC* parametro0) {
    fijar_iluminacion_circuito(dato_800DC610, dato_802B87D4, 0, 1);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000FE8));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000C60));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000B70));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070006B8));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000570));
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070010C8));
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000258));
}

void renderizar_double_deck(SIN_USO struct desconocido_struct_800DC5EC* parametro0) {

    fijar_iluminacion_circuito(dato_800DC610, dato_802B87D4, 0, 1);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000738));
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void renderizar_dks_jungle_parkway(struct desconocido_struct_800DC5EC* parametro0) {

    fijar_iluminacion_circuito(dato_800DC610, dato_802B87D4, 0, 1);
    fijar_iluminacion_circuito(&dato_800DC610[1], dato_802B87D4, dato_802B87D0, 1);

    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK | G_LIGHTING);

    if (funcion_80290C20(parametro0->camara) == 1) {
        gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070092D8));
    }

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    renderizar_segmentos_circuito((uintptr_t) d_circuito_dks_jungle_parkway_lista_dl_desconocido, parametro0);

    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void renderizar_big_donut(struct desconocido_struct_800DC5EC* parametro0) {

    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    fijar_iluminacion_circuito(dato_800DC610, dato_802B87D4, 0, 1);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);

    if (funcion_80290C20(parametro0->camara) == 1) {
        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000DE8));
    }
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000450));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000AC0));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000D20));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000230));
}

void renderizar_creditos_circuito(void) {
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            gSPDisplayList(display_list_cabeza++, d_circuito_mario_raceway_dl_9348);
            break;
        case CIRCUITO_CHOCO_MOUNTAIN:
            gSPDisplayList(display_list_cabeza++, d_circuito_choco_montania_dl_71B8);
            break;
        case CIRCUITO_BOWSER_CASTLE:
            gSPDisplayList(display_list_cabeza++, d_circuito_bowsers_castle_dl_9148);
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            gSPDisplayList(display_list_cabeza++, d_circuito_banshee_boardwalk_dl_B308);
            break;
        case CIRCUITO_YOSHI_VALLEY:
            gSPDisplayList(display_list_cabeza++, d_circuito_yoshi_valley_dl_18020);
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            gSPDisplayList(display_list_cabeza++, d_circuito_frappe_snowland_dl_76A0);
            break;
        case CIRCUITO_KOOPA_BEACH:
            gSPDisplayList(display_list_cabeza++, d_circuito_koopa_troopa_beach_dl_18D68);
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            gSPDisplayList(display_list_cabeza++, d_circuito_royal_raceway_dl_D8E8);
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            gSPDisplayList(display_list_cabeza++, d_circuito_luigi_raceway_dl_FD40);
            break;
        case CIRCUITO_MOO_MOO_FARM:
            gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_dl_14088);
            break;
        case CIRCUITO_TOADS_TURNPIKE:
            gSPDisplayList(display_list_cabeza++, d_circuito_toads_turnpike_dl_23930);
            break;
        case CIRCUITO_KALAMARI_DESERT:
            gSPDisplayList(display_list_cabeza++, d_circuito_kalimari_desierto_dl_22E00);
            break;
        case CIRCUITO_SHERBET_LAND:
            gSPDisplayList(display_list_cabeza++, d_circuito_sherbet_tierra_dl_9AE8);
            break;
        case CIRCUITO_RAINBOW_ROAD:
            gSPDisplayList(display_list_cabeza++, d_circuito_rainbow_road_dl_16220);
            break;
        case CIRCUITO_WARIO_STADIUM:
            gSPDisplayList(display_list_cabeza++, d_circuito_wario_stadium_dl_CA78);
            break;
        case CIRCUITO_BLOCK_FORT:
            gSPDisplayList(display_list_cabeza++, d_circuito_sherbet_land_dl_0);
            break;
        case CIRCUITO_SKYSCRAPER:
            gSPDisplayList(display_list_cabeza++, d_circuito_sherbet_land_dl_0);
            break;
        case CIRCUITO_DOUBLE_DECK:
            gSPDisplayList(display_list_cabeza++, d_circuito_sherbet_land_dl_0);
            break;
        case CIRCUITO_DK_JUNGLE:
            gSPDisplayList(display_list_cabeza++, d_circuito_dks_jungle_parkway_dl_13C30);
            break;
        case CIRCUITO_BIG_DONUT:
            gSPDisplayList(display_list_cabeza++, d_circuito_sherbet_land_dl_0);
            break;
    }
#else

#endif
}

void renderizar_circuito(struct desconocido_struct_800DC5EC* parametro0) {

    fijar_iluminacion_circuito(dato_800DC610, dato_802B87D4, 0, 1);
    if (modo_render_creditos) {
        renderizar_creditos_circuito();
        return;
    }

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            renderizar_mario_raceway(parametro0);
            break;
        case CIRCUITO_CHOCO_MOUNTAIN:
            renderizar_choco_mountain(parametro0);
            break;
        case CIRCUITO_BOWSER_CASTLE:
            renderizar_bowsers_castle(parametro0);
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            renderizar_banshee_boardwalk(parametro0);
            break;
        case CIRCUITO_YOSHI_VALLEY:
            renderizar_yoshi_valley(parametro0);
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            renderizar_frappe_snowland(parametro0);
            break;
        case CIRCUITO_KOOPA_BEACH:
            renderizar_koopa_troopa_beach(parametro0);
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            renderizar_royal_raceway(parametro0);
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            renderizar_luigi_raceway(parametro0);
            break;
        case CIRCUITO_MOO_MOO_FARM:
            renderizar_moo_moo_farm(parametro0);
            break;
        case CIRCUITO_TOADS_TURNPIKE:
            renderizar_toads_turnpike(parametro0);
            break;
        case CIRCUITO_KALAMARI_DESERT:
            renderizar_kalimari_desert(parametro0);
            break;
        case CIRCUITO_SHERBET_LAND:
            renderizar_sherbet_land(parametro0);
            break;
        case CIRCUITO_RAINBOW_ROAD:
            renderizar_rainbow_road(parametro0);
            break;
        case CIRCUITO_WARIO_STADIUM:
            renderizar_wario_stadium(parametro0);
            break;
        case CIRCUITO_BLOCK_FORT:
            renderizar_block_fort(parametro0);
            break;
        case CIRCUITO_SKYSCRAPER:
            renderizar_skyscraper(parametro0);
            break;
        case CIRCUITO_DOUBLE_DECK:
            renderizar_double_deck(parametro0);
            break;
        case CIRCUITO_DK_JUNGLE:
            renderizar_dks_jungle_parkway(parametro0);
            break;
        case CIRCUITO_BIG_DONUT:
            renderizar_big_donut(parametro0);
            break;
    }
#else

#endif
}

void funcion_80295BF8(s32 indice_jugador) {
    Jugador* jugador = &jugadores[indice_jugador];
    funcion_802AAAAC(&jugador->colision);
    jugador->ruedas[DERECHA_FRENTE].banderas_superficie = 0;
    jugador->ruedas[IZQUIERDA_FRENTE].banderas_superficie = 0;
    jugador->ruedas[DERECHA_ATRAS].banderas_superficie = 0;
    jugador->ruedas[IZQUIERDA_ATRAS].banderas_superficie = 0;

    jugador->ruedas[DERECHA_FRENTE].indice_malla_colision = 0x1388;
    jugador->ruedas[IZQUIERDA_FRENTE].indice_malla_colision = 0x1388;
    jugador->ruedas[DERECHA_ATRAS].indice_malla_colision = 0x1388;
    jugador->ruedas[IZQUIERDA_ATRAS].indice_malla_colision = 0x1388;
}

void funcion_80295C6C(void) {
    siguiente_libre_memoria_direccion += ALIGN16(cantidad_malla_colision * sizeof(TrianguloColision));
    max_x_circuito += 20;
    max_z_circuito += 20;
    min_x_circuito += -20;
    min_z_circuito += -20;
    min_y_circuito += -20;
    MARCAR_TIEMPOS_PS2("colisión: malla");
    generar_cuadricula_colision();
    MARCAR_TIEMPOS_PS2("colisión: cuadrícula");
    siguiente_libre_memoria_direccion += ALIGN16(triangulos_colision_num * sizeof(u16));
}

SIN_USO void funcion_80295D50(s16 parametro0, s16 parametro1) {
    dato_8015F6F4 = parametro1;
    dato_8015F6F6 = parametro0;
}

void funcion_80295D6C(void) {
    dato_8015F6F4 = 3000;
    dato_8015F6F6 = -3000;
}

void circuito_generar_colision_malla(void) {
    actores_num = 0;

    min_x_circuito = 0;
    min_y_circuito = 0;
    min_z_circuito = 0;

    max_x_circuito = 0;
    max_y_circuito = 0;
    max_z_circuito = 0;

    dato_8015F59C = 0;
    dato_8015F5A0 = 0;
    funcion_80295D6C();
    dato_8015F58C = 0;
    cantidad_malla_colision = 0;
    malla_colision = (TrianguloColision*) siguiente_libre_memoria_direccion;
    dato_800DC5BC = 0;
    dato_800DC5C8 = 0;
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            generar_malla_colision_con_predeterminados((Gfx*) 0x07001140);
            if (seleccion_modo_pantalla == MODO_PANTALLA_1P) {
                generar_malla_colision_con_predeterminados((Gfx*) 0x070008E8);
            } else {
                generar_malla_colision_con_predeterminados((Gfx*) 0x07002D68);
            }
            analizar_displaylists_circuito((uintptr_t) d_circuito_mario_raceway_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = min_y_circuito - 10.0f;
            break;
        case CIRCUITO_CHOCO_MOUNTAIN:
            dato_800DC5BC = 1;
            dato_801625EC = 255;
            dato_801625F4 = 255;
            dato_801625F0 = 255;
            dato_802B87B0 = 0x3E3;
            dato_802B87B4 = 0x3E8;
            dato_802B87D4 = 0x71C;
            dato_802B87D0 = 0xE38;

            if ((seleccion_cc != CC_50) && (seleccion_modo != CONTRARRELOJ)) {
                anular_displaylist((uintptr_t) 0x07000000);
                anular_displaylist((uintptr_t) 0x07000098);
                anular_displaylist((uintptr_t) 0x07000178);
                anular_displaylist((uintptr_t) 0x07000280);
                anular_displaylist((uintptr_t) 0x07000340);
                anular_displaylist((uintptr_t) 0x070003C8);
            }
            analizar_displaylists_circuito((uintptr_t) &d_circuito_choco_mountain_direccion);
            vec_unidad_z_rot_x_rot_y(GRADOS(50), GRADOS(70), dato_8015F590);
            funcion_80295C6C();
            dato_8015F8E4 = -80.0f;
            break;
        case CIRCUITO_BOWSER_CASTLE:
            analizar_displaylists_circuito((uintptr_t) d_circuito_bowsers_castle_direccion);
            funcion_80295C6C();
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07001350, 0x32, 0, 0, 0);
            dato_8015F8E4 = -50.0f;
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            dato_800DC5BC = 1;
            dato_801625EC = 0;
            dato_801625F4 = 0;
            dato_801625F0 = 0;
            analizar_displaylists_circuito((uintptr_t) d_circuito_banshee_boardwalk_secciones_pista);
            funcion_80295C6C();
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07000878, 128, 0, 0, 0);
            dato_8015F8E4 = -80.0f;
            break;
        case CIRCUITO_YOSHI_VALLEY:
            fijar_iluminacion_circuito(&d_circuito_yoshi_valley_luces4, -0x38F0, 0x1C70, 1);
            analizar_displaylists_circuito((uintptr_t) d_circuito_yoshi_valley_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = min_y_circuito - 10.0f;
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            analizar_displaylists_circuito((uintptr_t) d_circuito_frappe_snowland_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = -50.0f;
            break;
        case CIRCUITO_KOOPA_BEACH:
            analizar_displaylists_circuito((uintptr_t) d_circuito_koopa_troopa_beach_direccion);
            funcion_80295C6C();
            fijar_colores_vtx_buscar_y((uintptr_t) 0x0700ADE0, 150, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x0700A540, 150, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07009E70, 150, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07000358, 150, 255, 255, 255);
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            analizar_displaylists_circuito((uintptr_t) d_circuito_royal_raceway_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = -60.0f;
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            analizar_displaylists_circuito((uintptr_t) d_circuito_luigi_raceway_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = min_y_circuito - 10.0f;
            break;
        case CIRCUITO_MOO_MOO_FARM:
            analizar_displaylists_circuito((uintptr_t) d_circuito_moo_moo_farm_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = min_y_circuito - 10.0f;
            break;
        case CIRCUITO_TOADS_TURNPIKE:
            dato_801625EC = 43;
            dato_801625F4 = 13;
            dato_801625F0 = 4;
            dato_802B87B0 = 993;
            dato_802B87B4 = 1000;
            analizar_displaylists_circuito((uintptr_t) d_circuito_toads_turnpike_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = min_y_circuito - 10.0f;
            break;
        case CIRCUITO_KALAMARI_DESERT:
            analizar_displaylists_circuito((uintptr_t) d_circuito_kalimari_desert_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = min_y_circuito - 10.0f;
            break;
        case CIRCUITO_SHERBET_LAND:
            analizar_displaylists_circuito((uintptr_t) d_circuito_sherbet_land_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = -18.0f;
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07001EB8, 180, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07002308, 150, 255, 255, 255);
            break;
        case CIRCUITO_RAINBOW_ROAD:
            dato_800DC5C8 = 1;
            analizar_displaylists_circuito((uintptr_t) d_circuito_rainbow_road_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = 0.0f;
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07002068, 150, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07001E18, 150, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07001318, 255, 255, 255, 0);
            if (estado_juego != SECUENCIA_CREDITOS) {
                fijar_colores_vtx_buscar_y((uintptr_t) 0x07001FB8, 150, 255, 255, 255);
            }
            break;
        case CIRCUITO_WARIO_STADIUM:
            analizar_displaylists_circuito((uintptr_t) d_circuito_wario_stadium_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = min_y_circuito - 10.0f;
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07000C50, 100, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07000BD8, 100, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07000B60, 100, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07000AE8, 100, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07000CC8, 100, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07000D50, 100, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07000DD0, 100, 255, 255, 255);
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07000E48, 100, 255, 255, 255);
            break;
        case CIRCUITO_BLOCK_FORT:
            generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x070015C0, 1);
            funcion_80295C6C();
            dato_8015F8E4 = min_y_circuito - 10.0f;
            break;
        case CIRCUITO_SKYSCRAPER:
            generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07001110, 1);
            generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07000258, 1);
            funcion_80295C6C();

            dato_8015F8E4 = -480.0f;
            break;
        case CIRCUITO_DOUBLE_DECK:
            generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07000738, 1);
            funcion_80295C6C();
            dato_8015F8E4 = min_y_circuito - 10.0f;
            break;
        case CIRCUITO_DK_JUNGLE:
            analizar_displaylists_circuito((uintptr_t) d_circuito_dks_jungle_parkway_direccion);
            funcion_80295C6C();
            dato_8015F8E4 = -475.0f;
            fijar_colores_vtx_buscar_y((uintptr_t) 0x07003FA8, 120, 255, 255, 255);
            break;
        case CIRCUITO_BIG_DONUT:
            generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07001018, 6);
            generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07000450, 6);
            generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07000AC0, 6);
            generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07000B58, 6);
            generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07000230, 6);
            funcion_80295C6C();
            dato_8015F8E4 = 100.0f;
            break;
    }
#else

#endif
}

void actualizar_agua_circuito(void) {
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_KOOPA_BEACH:
            if (dato_8015F8E8 < 0.0f) {
                if (dato_8015F8E4 < -20.0f) { dato_8015F8E8 *= -1.0f; }
            } else {
                if (dato_8015F8E4 > 0.0f) { dato_8015F8E8 *= -1.0f; }
            }
            dato_8015F8E4 += dato_8015F8E8;

            dato_802B87BC += 9;
            if (dato_802B87BC > 255) {
                dato_802B87BC = 0;
            }
            dato_802B87C4 += 3;
            if (dato_802B87C4 > 255) {
                dato_802B87C4 = 0;
            }
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x07009D58, 0, dato_802B87BC);
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x07009CD0, 0, dato_802B87C4);
            dato_802B87CC = int_aleatorio(300) / 40;
            if (dato_802B87C8 < 0) {
                dato_802B87C8 = int_aleatorio(300) / 40;
            } else {
                dato_802B87C8 = -(int_aleatorio(300) / 40);
            }
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x070002E8, dato_802B87C8, dato_802B87CC);
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            dato_802B87BC++;

            if (dato_802B87BC >= 0x100) {
                dato_802B87BC = 0;
            }
            fijar_tamanio_tile_buscar_y((uintptr_t) d_circuito_banshee_boardwalk_dl_B278, 0, dato_802B87BC);
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            dato_802B87BC -= 20;
            if (dato_802B87BC < 0) {
                dato_802B87BC = 0xFF;
            }
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x0700A6A8, 0, dato_802B87BC);
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x0700A648, 0, dato_802B87BC);
            break;
        case CIRCUITO_DK_JUNGLE:
            dato_802B87BC += 2;
            if (dato_802B87BC > 255) {
                dato_802B87BC = 0;
            }
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x07003DD0, 0, dato_802B87BC);
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x07003E40, 0, dato_802B87BC);
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x07003EB0, 0, dato_802B87BC);
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x07003F30, 0, dato_802B87BC);
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x070036A8, 0, dato_802B87BC);
            dato_802B87C4 -= 20;
            if (dato_802B87C4 < 0) {
                dato_802B87C4 = 0xFF;
            }
            fijar_tamanio_tile_buscar_y((uintptr_t) 0x07009880, 0, dato_802B87C4);
            evaluar_colision_jugadores_palmera_arboles();
            break;
    }
#else

#endif
}

void funcion_802969F8(void) {

    switch (id_circuito_actual) {
        case CIRCUITO_MOO_MOO_FARM:
            dato_8015F702 = 0;
            dato_8015F700 = 200;
            break;
        case CIRCUITO_KOOPA_BEACH:
            dato_8015F8E8 = -0.1f;
            dato_8015F8E4 = 0.0f;
            break;
    }
}
