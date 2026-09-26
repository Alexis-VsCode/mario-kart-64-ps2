// Objetos animados

void renderizar_modelo_thwomps_objeto(s32 indice_objeto) {
    if ((lista_objeto[indice_objeto].state >= 2) && (funcion_80072354(indice_objeto, 0x00000040) != 0)) {
        funcion_8004A7AC(indice_objeto, 1.75f);
        fijar_transformacion_matriz_rsp(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].orientacion,
                                      lista_objeto[indice_objeto].escalado_tamanio);
        funcion_800534E8(indice_objeto);
        gSPDisplayList(display_list_cabeza++, dato_0D007828);
        gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
        gDPLoadTLUT_pal256(display_list_cabeza++, d_circuito_bowsers_castle_thwomp_tlut);
        cargar_mascara_textura_rsp(lista_objeto[indice_objeto].textura_activo, 0x00000010, 0x00000040, 4);
        gSPDisplayList(display_list_cabeza++, lista_objeto[indice_objeto].model);
    }
}

void renderizar_thwomps_objeto(s32 id_camara) {
    s32 indice_objeto;
    s32 i;
    SIN_USO s32 margen_pila_0;
    s16 menos_uno, mas_uno;
    Camara* camara;
    Objeto* objeto;

    camara = &camara1[id_camara];
    if (id_camara == JUGADOR_UNO) {
        for (i = 0; i < thwomps_activo_num; i++) {
            indice_objeto = lista_objeto_indice_1[i];
            fijar_objeto_bandera_situacion_false(indice_objeto, 0x00070000);
            funcion_800722CC(indice_objeto, 0x00000110);
        }
    }

    funcion_800534A4(indice_objeto);
    for (i = 0; i < thwomps_activo_num; i++) {
        indice_objeto = lista_objeto_indice_1[i];
        menos_uno = lista_objeto[indice_objeto].desconocido_0DF - 1;
        mas_uno = lista_objeto[indice_objeto].desconocido_0DF + 1;
        if (estado_juego != 9) {
            if ((dato_8018CF68[id_camara] >= menos_uno) && (mas_uno >= dato_8018CF68[id_camara]) &&
                (es_visible_objeto_en_camara(indice_objeto, camara, 0x8000U) != 0)) {
                renderizar_modelo_thwomps_objeto(indice_objeto);
            }
        } else {
            renderizar_modelo_thwomps_objeto(indice_objeto);
        }
    }
    gSPDisplayList(display_list_cabeza++, dato_0D0079C8);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gSPNumLights(display_list_cabeza++, 1);
    gSPLight(display_list_cabeza++, &dato_800E4668.l[0], LIGHT_1);
    gSPLight(display_list_cabeza++, &dato_800E4668.a, LIGHT_2);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_LIGHTING | G_SHADING_SMOOTH);
    cargar_textura_bloque_rgba16_espejo(d_circuito_bowsers_castle_thwomp_lado, 0x00000020, 0x00000020);
    for (i = 0; i < objeto_particula_3_tamanio; i++) {
        indice_objeto = particula_objeto_3[i];
        if (indice_objeto != ID_OBJETO_NULO) {
            objeto = &lista_objeto[indice_objeto];
            if ((objeto->state > 0) && (objeto->desconocido_0D5 == 3) && (cantidad_hud_matriz <= MTX_HUD_POOL_TAMANIO_MAX)) {
                fijar_transformacion_matriz_rsp(objeto->pos, objeto->orientacion, objeto->escalado_tamanio);
                gSPVertex(display_list_cabeza++, dato_0D005C00, 3, 0);
                gSPDisplayList(display_list_cabeza++, dato_0D006930);
            }
        }
    }
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPTexture(display_list_cabeza++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
    gSPDisplayList(display_list_cabeza++, dato_0D007AE0);
    cargar_nomirror_bloque_ia8_textura(dato_8018D490, 0x00000020, 0x00000020);
    funcion_8004B3C8(0);
    dato_80183E80[0] = 0;
    dato_80183E80[2] = 0x8000;
    for (i = 0; i < objeto_particula_2_tamanio; i++) {
        indice_objeto = particula_objeto_2[i];
        if (indice_objeto != ID_OBJETO_NULO) {
            objeto = &lista_objeto[indice_objeto];
            if ((objeto->state >= 2) && (objeto->desconocido_0D5 == 2) && (cantidad_hud_matriz <= MTX_HUD_POOL_TAMANIO_MAX)) {
                funcion_8004B138(0x000000FF, 0x000000FF, 0x000000FF, (s32) objeto->prim_alpha);
                dato_80183E80[1] = funcion_800418AC(objeto->pos[0], objeto->pos[2], camara->pos);
                funcion_800431B0(objeto->pos, dato_80183E80, objeto->escalado_tamanio, dato_0D005AE0);
            }
        }
    }
}

void funcion_80053D74(s32 indice_objeto, SIN_USO s32 parametro1, s32 indice_vertice) {
    Objeto* objeto;

    if (cantidad_hud_matriz <= MTX_HUD_POOL_TAMANIO_MAX) {
        objeto = &lista_objeto[indice_objeto];
        dato_80183E80[2] = (s16) (objeto->desconocido_084[6] + 0x8000);
        fijar_transformacion_matriz_rsp(objeto->pos, (u16*) dato_80183E80, objeto->escalado_tamanio);
        renderizar_color_conjunto((s32) objeto->desconocido_084[0], (s32) objeto->desconocido_084[1], (s32) objeto->desconocido_084[2],
                         (s32) objeto->desconocido_084[3], (s32) objeto->desconocido_084[4], (s32) objeto->desconocido_084[5],
                         (s32) objeto->prim_alpha);
        gSPVertex(display_list_cabeza++, &erizo_vtx_comun[indice_vertice], 4, 0);
        gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
    }
}

void renderizar_objeto_gran_premio_globos(s32 parametro0) {
    s32 variable_s1;
    s32 indice_objeto;

    gSPDisplayList(display_list_cabeza++, dato_0D007E98);
    gDPLoadTLUT_pal256(display_list_cabeza++, dato_800E52D0);
    funcion_8004B614(0, 0, 0, 0, 0, 0, 0);
    dato_80183E80[0] = 0;
    dato_80183E80[1] = 0x8000;
    cargar_textura_rsp(dato_8018D4BC, 64, 32);
    for (variable_s1 = 0; variable_s1 < dato_80165738; variable_s1++) {
        indice_objeto = particula_objeto_3[variable_s1];
        if ((indice_objeto != ID_OBJETO_NULO) && (lista_objeto[indice_objeto].state >= 2)) {
            funcion_80053D74(indice_objeto, parametro0, 0);
        }
    }
    cargar_textura_rsp(dato_8018D4C0, 64, 32);
    for (variable_s1 = 0; variable_s1 < dato_80165738; variable_s1++) {
        indice_objeto = particula_objeto_3[variable_s1];
        if ((indice_objeto != ID_OBJETO_NULO) && (lista_objeto[indice_objeto].state >= 2)) {
            funcion_80053D74(indice_objeto, parametro0, 4);
        }
    }
}

void renderizar_objeto_tren_humo_particula(s32 indice_objeto, s32 id_camara) {
    Camara* camara;

    camara = &camara1[id_camara];
    if (indice_objeto != ID_OBJETO_NULO) {
        if ((lista_objeto[indice_objeto].state >= 2) && (lista_objeto[indice_objeto].desconocido_0D5 == 1) &&
            (cantidad_hud_matriz <= MTX_HUD_POOL_TAMANIO_MAX)) {
            renderizar_color_conjunto((s32) lista_objeto[indice_objeto].type, (s32) lista_objeto[indice_objeto].type,
                             (s32) lista_objeto[indice_objeto].type, 0, 0, 0, (s32) lista_objeto[indice_objeto].prim_alpha);
            dato_80183E80[1] =
                funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], camara->pos);
            funcion_800431B0(lista_objeto[indice_objeto].pos, dato_80183E80, lista_objeto[indice_objeto].escalado_tamanio, dato_0D005AE0);
        }
    }
}

void renderizar_objeto_trenes_humo_particulas(s32 id_camara) {
    SIN_USO s32 relleno;
    SIN_USO s32 j;
    Camara* camara;
    s32 i;

    camara = &camara1[id_camara];
    gSPDisplayList(display_list_cabeza++, dato_0D007AE0);
    cargar_nomirror_bloque_i8_textura(dato_0D029458, 32, 32);
    funcion_8004B72C(255, 255, 255, 255, 255, 255, 255);
    dato_80183E80[0] = 0;
    dato_80183E80[2] = 0x8000;

#ifdef AVOID_UB_WIP
    for (j = 0; j < TRENES_NUM; j++) {
        if ((lista_tren[j].algun_banderas != 0) &&
            (es_particula_en_pantalla(&lista_tren[j].locomotora.position, camara, 0x4000U) != 0)) {

            for (i = 0; i < 128; i++) {
                renderizar_objeto_tren_humo_particula(particula_objeto_2[i], id_camara);
            }
        }
    }
#else

    if ((lista_tren[0].algun_banderas != 0) &&
        (es_particula_en_pantalla(lista_tren[0].locomotora.position, camara, 0x4000U) != 0)) {

        for (i = 0; i < objeto_particula_2_tamanio; i++) {
            renderizar_objeto_tren_humo_particula(particula_objeto_2[i], id_camara);
        }
    }
    if ((lista_tren[1].algun_banderas != 0) &&
        (es_particula_en_pantalla(lista_tren[1].locomotora.position, camara, 0x4000U) != 0)) {
        for (i = 0; i < objeto_particula_3_tamanio; i++) {
            renderizar_objeto_tren_humo_particula(particula_objeto_3[i], id_camara);
        }
    }
#endif
}

void renderizar_objeto_paleta_barco_humo_particula(s32 indice_objeto, s32 id_camara) {
    Camara* camara;

    camara = &camara1[id_camara];
    if (indice_objeto != ID_OBJETO_NULO) {
        if ((lista_objeto[indice_objeto].state >= 2) && (lista_objeto[indice_objeto].desconocido_0D5 == 6) &&
            (cantidad_hud_matriz <= MTX_HUD_POOL_TAMANIO_MAX)) {
            renderizar_color_conjunto((s32) lista_objeto[indice_objeto].type, (s32) lista_objeto[indice_objeto].type,
                             (s32) lista_objeto[indice_objeto].type, lista_objeto[indice_objeto].desconocido_0A2,
                             lista_objeto[indice_objeto].desconocido_0A2, lista_objeto[indice_objeto].desconocido_0A2,
                             (s32) lista_objeto[indice_objeto].prim_alpha);
            dato_80183E80[1] =
                funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], camara->pos);
            funcion_800431B0(lista_objeto[indice_objeto].pos, dato_80183E80, lista_objeto[indice_objeto].escalado_tamanio, dato_0D005AE0);
        }
    }
}

void renderizar_objeto_paleta_barco_humo_particulas(s32 id_camara) {
    SIN_USO s32 relleno[2];
    Camara* camara;
    s32 i;

    camara = &camara1[id_camara];
    gSPDisplayList(display_list_cabeza++, dato_0D007AE0);

    cargar_nomirror_bloque_i8_textura(dato_0D029458, 32, 32);
    funcion_8004B72C(255, 255, 255, 255, 255, 255, 255);
    dato_80183E80[0] = 0;
    dato_80183E80[2] = 0x8000;
    if ((barcos_paleta[0].algun_banderas != 0) && (es_particula_en_pantalla(barcos_paleta[0].position, camara, 0x4000U) != 0)) {
        for (i = 0; i < objeto_particula_2_tamanio; i++) {
            renderizar_objeto_paleta_barco_humo_particula(particula_objeto_2[i], id_camara);
        }
    }
    if ((barcos_paleta[1].algun_banderas != 0) && (es_particula_en_pantalla(barcos_paleta[1].position, camara, 0x4000U) != 0)) {
        for (i = 0; i < objeto_particula_3_tamanio; i++) {
            renderizar_objeto_paleta_barco_humo_particula(particula_objeto_3[i], id_camara);
        }
    }
}

void renderizar_objeto_bowser_particula_llama(s32 indice_objeto, s32 id_camara) {
    Camara* camara;
    Objeto* objeto;

    camara = &camara1[id_camara];
    if (cantidad_hud_matriz <= MTX_HUD_POOL_TAMANIO_MAX) {
        objeto = &lista_objeto[indice_objeto];
        if (objeto->desconocido_0D5 == 9) {
            funcion_8004B72C(0xFF, (s32) objeto->type, 0, (s32) objeto->desconocido_0A2, 0, 0, (s32) objeto->prim_alpha);
        } else {
            funcion_8004B138(0xFF, (s32) objeto->type, 0, (s32) objeto->prim_alpha);
        }
        dato_80183E80[1] = funcion_800418AC(objeto->pos[0], objeto->pos[2], camara->pos);
        funcion_800431B0(objeto->pos, dato_80183E80, objeto->escalado_tamanio, dato_0D005AE0);
    }
}

void renderizar_objeto_bowser_llama(s32 id_camara) {
    s32 variable_s0;
    s32 indice_objeto;

    gSPDisplayList(display_list_cabeza++, dato_0D007AE0);
    cargar_nomirror_bloque_i8_textura(comun_textura_particula_humo[dato_80165598], 0x00000020, 0x00000020);
    funcion_8004B414(0, 0, 0, 0x000000FF);
    dato_80183E80[0] = 0;
    dato_80183E80[2] = 0x8000;
    for (variable_s0 = 0; variable_s0 < objeto_particula_1_tamanio; variable_s0++) {
        indice_objeto = particula_objeto_1[variable_s0];
        if ((indice_objeto != ID_OBJETO_NULO) && (lista_objeto[indice_objeto].state >= 3)) {
            renderizar_objeto_bowser_particula_llama(indice_objeto, id_camara);
        }
    }
}

void funcion_8005477C(s32 indice_objeto, u8 parametro1, Vec3f parametro2) {
    if (cantidad_hud_matriz <= MTX_HUD_POOL_TAMANIO_MAX) {
        switch (parametro1) { /* irregular */
            case 0:
                renderizar_color_conjunto(0xE6, 0xFF, 0xFF, 0x00, 0x00, 0xFF, (s32) lista_objeto[indice_objeto].prim_alpha);
                break;
            case 1:
                renderizar_color_conjunto(0xFF, 0xFF, 0x96, 0xFF, 0x00, 0x00, (s32) lista_objeto[indice_objeto].prim_alpha);
                break;
            case 2:
                renderizar_color_conjunto(0xFF, 0xE6, 0xFF, 0xFF, 0x00, 0x96, (s32) lista_objeto[indice_objeto].prim_alpha);
                break;
            case 3:
                renderizar_color_conjunto(0xFF, 0xFF, 0x1E, 0xFF, 0x00, 0x00, (s32) lista_objeto[indice_objeto].prim_alpha);
                break;
            default:
                break;
        }
        dato_80183E80[1] = funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], parametro2);
        funcion_800431B0(lista_objeto[indice_objeto].pos, dato_80183E80, lista_objeto[indice_objeto].escalado_tamanio, dato_0D005AE0);
    }
}

void renderizar_particulas_humo_objeto(s32 id_camara) {
    SIN_USO s32 margen_pila[2];
    Camara* sp54;
    s32 variable_s0;
    s32 indice_objeto;
    Objeto* objeto;

    sp54 = &camara1[id_camara];
    gSPDisplayList(display_list_cabeza++, dato_0D007AE0);
    cargar_nomirror_bloque_i8_textura(comun_textura_particula_humo[dato_80165598], 32, 32);
    funcion_8004B72C(255, 255, 255, 255, 255, 255, 255);
    dato_80183E80[0] = 0;
    dato_80183E80[2] = 0x8000;
    for (variable_s0 = 0; variable_s0 < objeto_particula_4_tamanio; variable_s0++) {
        indice_objeto = particula_objeto_4[variable_s0];
        if (indice_objeto != ID_OBJETO_NULO) {
            objeto = &lista_objeto[indice_objeto];
            if (objeto->state >= 2) {
                if (objeto->desconocido_0D8 == 3) {
                    funcion_8008A364(indice_objeto, id_camara, 0x4000U, 0x00000514);
                } else {
                    funcion_8008A364(indice_objeto, id_camara, 0x4000U, 0x000001F4);
                }
                if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
                    funcion_8005477C(indice_objeto, objeto->desconocido_0D8, sp54->pos);
                }
            }
        }
    }
}

void funcion_80054AFC(s32 indice_objeto, Vec3f parametro1) {
    dato_80183E80[0] = funcion_800418E8(lista_objeto[indice_objeto].pos[2], lista_objeto[indice_objeto].pos[1], parametro1);
    dato_80183E80[1] = funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], parametro1);
    dato_80183E80[2] = (u16) lista_objeto[indice_objeto].orientacion[2];
    funcion_8004B138((s32) lista_objeto[indice_objeto].desconocido_084[0], (s32) lista_objeto[indice_objeto].desconocido_084[1],
                  (s32) lista_objeto[indice_objeto].desconocido_084[2], (s32) lista_objeto[indice_objeto].prim_alpha);
    fijar_transformacion_matriz_rsp(lista_objeto[indice_objeto].pos, (u16*) dato_80183E80,
                                  lista_objeto[indice_objeto].escalado_tamanio);
    gSPVertex(display_list_cabeza++, dato_0D005AE0, 4, 0);
    gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
}

void funcion_80054BE8(s32 id_camara) {
    s32 variable_s0;
    s32 temporal_a0;
    Camara* camara;

    camara = &camara1[id_camara];
    gSPDisplayList(display_list_cabeza++, dato_0D007AE0);
    cargar_nomirror_bloque_ia8_textura(dato_8018D488, 0x00000020, 0x00000020);
    funcion_8004B35C(0x000000FF, 0x000000FF, 0, 0x000000FF);
    dato_80183E80[0] = 0;
    for (variable_s0 = 0; variable_s0 < objeto_particula_3_tamanio; variable_s0++) {
        temporal_a0 = particula_objeto_3[variable_s0];
        if ((temporal_a0 != -1) && (lista_objeto[temporal_a0].state >= 2)) {
            funcion_80054AFC(temporal_a0, camara->pos);
        }
    }
}

void funcion_80054D00(s32 indice_objeto, s32 id_camara) {
    Camara* camara;

    camara = &camara1[id_camara];
    if (lista_objeto[indice_objeto].state >= 3) {
        funcion_8008A364(indice_objeto, id_camara, 0x2AABU, 0x0000012C);
        if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
            dato_80183E80[0] = (s16) lista_objeto[indice_objeto].orientacion[0];
            dato_80183E80[1] =
                funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], camara->pos);
            dato_80183E80[2] = (u16) lista_objeto[indice_objeto].orientacion[2];
            funcion_80048130(lista_objeto[indice_objeto].pos, (u16*) dato_80183E80, lista_objeto[indice_objeto].escalado_tamanio,
                          (u8*) lista_objeto[indice_objeto].t_lut_activo, lista_objeto[indice_objeto].textura_activo, dato_0D0062B0,
                          0x00000020, 0x00000040, 0x00000020, 0x00000040, 5);
        }
    }
}

void funcion_80054E10(s32 indice_objeto) {
    if (lista_objeto[indice_objeto].state > 0) {
        if (es_obj_bandera_situacion_activo(indice_objeto, 0x00800000) != 0) {
            dato_80183E50[0] = lista_objeto[indice_objeto].pos[0];
            dato_80183E50[1] = lista_objeto[indice_objeto].altura_superficie + 0.8;
            dato_80183E50[2] = lista_objeto[indice_objeto].pos[2];
            dato_80183E70[0] = lista_objeto[indice_objeto].velocidad[0];
            dato_80183E70[1] = lista_objeto[indice_objeto].velocidad[1];
            dato_80183E70[2] = lista_objeto[indice_objeto].velocidad[2];
            funcion_8004A9B8(lista_objeto[indice_objeto].escalado_tamanio);
        }
    }
}

void funcion_80054EB8(SIN_USO s32 unused) {
    s32 algun_indice;

    for (algun_indice = 0; algun_indice < TOPOS_TOTAL_NUM; algun_indice++) {
        funcion_80054E10(particula_objeto_1[algun_indice]);
    }
}

void funcion_80054F04(s32 id_camara) {
    s32 variable_s2;
    s32 indice_objeto;
    Camara* sp44;
    Objeto* objeto;

    sp44 = &camara1[id_camara];
    gSPDisplayList(display_list_cabeza++, dato_0D0079C8);
    cargar_textura_bloque_rgba16_espejo(d_circuito_moo_moo_farm_tierra_topo, 0x00000010, 0x00000010);
    for (variable_s2 = 0; variable_s2 < objeto_particula_2_tamanio; variable_s2++) {
        indice_objeto = particula_objeto_2[variable_s2];
        objeto = &lista_objeto[indice_objeto];
        if (objeto->state > 0) {
            funcion_8008A364(indice_objeto, id_camara, 0x2AABU, 0x000000C8);
            if ((es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) && (cantidad_hud_matriz <= MTX_HUD_POOL_TAMANIO_MAX)) {
                objeto->orientacion[1] = funcion_800418AC(objeto->pos[0], objeto->pos[2], sp44->pos);
                rsp_conjunto_matriz_g_objeto_lista(indice_objeto);
                gSPDisplayList(display_list_cabeza++, dato_0D006980);
            }
        }
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void renderizar_topos_objeto(s32 id_camara) {
    s32 i;

    for (i = 0; i < TOPOS_GROUP1_NUM; i++) {
        funcion_80054D00(lista_objeto_indice_1[i], id_camara);
    }
    for (i = 0; i < TOPOS_GROUP2_NUM; i++) {
        funcion_80054D00(lista_objeto_indice_2[i], id_camara);
    }
    for (i = 0; i < TOPOS_GROUP3_NUM; i++) {
        funcion_80054D00(lista_objeto_indice_3[i], id_camara);
    }
    funcion_80054EB8(id_camara);
    funcion_80054F04(id_camara);
}

void funcion_80055164(s32 indice_objeto) {
    if (lista_objeto[indice_objeto].state >= 2) {
        gSPDisplayList(display_list_cabeza++, dato_0D0077A0);
        fijar_transformacion_matriz_rsp(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].angulo_sentido,
                                      lista_objeto[indice_objeto].escalado_tamanio);
        if (juego_en_pausa == 0) {
            lista_objeto[indice_objeto].desconocido_0A2 = renderizar_modelo_animado((Armadura*) lista_objeto[indice_objeto].model,
                                                                     (Animacion**) lista_objeto[indice_objeto].vertice, 0,
                                                                     lista_objeto[indice_objeto].desconocido_0A2);
        } else {
            renderizar_modelo_animado((Armadura*) lista_objeto[indice_objeto].model,
                                  (Animacion**) lista_objeto[indice_objeto].vertice, 0, lista_objeto[indice_objeto].desconocido_0A2);
        }
    }
}

void funcion_80055228(s32 id_camara) {
    s32 variable_s1;
    s32 temporal_s0;

    for (variable_s1 = 0; variable_s1 < 4; variable_s1++) {
        temporal_s0 = lista_objeto_indice_1[variable_s1];
        funcion_8008A364(temporal_s0, id_camara, 0x4000U, 0x000005DC);
        if (es_obj_bandera_situacion_activo(temporal_s0, VISIBLE) != 0) {
            funcion_80055164(temporal_s0);
        }
    }
}

void funcion_800552BC(s32 indice_objeto) {
    if (lista_objeto[indice_objeto].state >= 2) {
        fijar_transformacion_matriz_rsp(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].angulo_sentido,
                                      lista_objeto[indice_objeto].escalado_tamanio);
        gSPDisplayList(display_list_cabeza++, dato_0D0077D0);
        if (juego_en_pausa == 0) {
            lista_objeto[indice_objeto].desconocido_0A2 = renderizar_modelo_animado((Armadura*) lista_objeto[indice_objeto].model,
                                                                     (Animacion**) lista_objeto[indice_objeto].vertice, 0,
                                                                     lista_objeto[indice_objeto].desconocido_0A2);
        } else {
            renderizar_modelo_animado((Armadura*) lista_objeto[indice_objeto].model,
                                  (Animacion**) lista_objeto[indice_objeto].vertice, 0, lista_objeto[indice_objeto].desconocido_0A2);
        }
    }
}

void renderizar_gaviotas_objeto(s32 parametro0) {
    s32 i;
    s32 variable_s1;

    for (i = 0; i < GAVIOTAS_NUM; i++) {
        variable_s1 = lista_objeto_indice_2[i];
        if (funcion_8008A364(variable_s1, parametro0, 0x5555U, 0x000005DC) < 0x9C401) {
            dato_80165908 = 1;
            funcion_800722A4(variable_s1, 2);
        }
        if (es_obj_bandera_situacion_activo(variable_s1, VISIBLE) != 0) {
            funcion_800552BC(variable_s1);
        }
    }
}

void dibujar_cangrejos(s32 indice_objeto, s32 id_camara) {
    Camara* camara;

    if (lista_objeto[indice_objeto].state >= 2) {
        camara = &camara1[id_camara];
        funcion_8004A6EC(indice_objeto, 0.5f);
        lista_objeto[indice_objeto].orientacion[1] =
            funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], camara->pos);
        dibujar_2d_textura_en(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].orientacion,
                           lista_objeto[indice_objeto].escalado_tamanio, (u8*) lista_objeto[indice_objeto].t_lut_activo,
                           lista_objeto[indice_objeto].textura_activo, erizo_vtx_comun, 0x00000040, 0x00000040,
                           0x00000040, 0x00000020);
    }
}

void renderizar_cangrejos_objeto(s32 parametro0) {
    s32 algun_indice;
    s32 probar;

    for (algun_indice = 0; algun_indice < CANGREJOS_NUM; algun_indice++) {
        probar = lista_objeto_indice_1[algun_indice];
        funcion_8008A364(probar, parametro0, 0x2AABU, 0x00000320);
        if (es_obj_bandera_situacion_activo(probar, VISIBLE) != 0) {
            dibujar_cangrejos(probar, parametro0);
        }
    }
}

void funcion_800555BC(s32 indice_objeto, s32 id_camara) {
    Camara* camara;

    if (lista_objeto[indice_objeto].state >= 2) {
        camara = &camara1[id_camara];
        funcion_8004A870(indice_objeto, 0.7f);
        lista_objeto[indice_objeto].orientacion[1] =
            funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], camara->pos);
        dibujar_2d_textura_en(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].orientacion,
                           lista_objeto[indice_objeto].escalado_tamanio, (u8*) lista_objeto[indice_objeto].t_lut_activo,
                           lista_objeto[indice_objeto].textura_activo, lista_objeto[indice_objeto].vertice, 64, 64, 64, 32);
    }
}

void renderizar_erizos_objeto(s32 parametro0) {
    s32 probar;
    u32 algo_;
    s32 algun_indice;

    for (algun_indice = 0; algun_indice < ERIZOS_NUM; algun_indice++) {
        probar = lista_objeto_indice_2[algun_indice];
        algo_ = funcion_8008A364(probar, parametro0, 0x4000U, 0x000003E8);
        if (es_obj_bandera_situacion_activo(probar, VISIBLE) != 0) {
            fijar_objeto_bandera_situacion_true(probar, 0x00200000);
            if (algo_ < 0x2711U) {
                fijar_objeto_bandera_situacion_true(probar, 0x00000020);
            } else {
                fijar_objeto_bandera_situacion_false(probar, 0x00000020);
            }
            if (algo_ < 0x57E41U) {
                fijar_objeto_bandera_situacion_true(probar, 0x00400000);
            }
            if (algo_ < 0x52211U) {
                funcion_800555BC(probar, parametro0);
            }
        }
    }
}

SIN_USO void funcion_800557AC() {
}

void funcion_800557B4(s32 indice_objeto, u32 parametro1, u32 parametro2) {
    Vec3f sp34;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    if (objeto->state >= 2) {
        if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000020) != 0) {
            if (funcion_80072320(indice_objeto, 4) != 0) {
                if (parametro2 >= parametro1) {
                    sp34[0] = objeto->pos[0];
                    sp34[1] = objeto->pos[1] - 1.0;
                    sp34[2] = objeto->pos[2];
                    fijar_matriz_transformacion_invertido_x_y_orientacion_rsp(sp34, objeto->orientacion,
                                                                           objeto->escalado_tamanio);
                    gSPDisplayList(display_list_cabeza++, dato_0D0077D0);
                    renderizar_modelo_animado((Armadura*) objeto->model, (Animacion**) objeto->vertice,
                                          (s16) objeto->desconocido_0D8, (s16) objeto->textura_indice_lista);
                }
            } else if (parametro1 < 0x15F91U) {
                funcion_8004A7AC(indice_objeto, 1.5f);
            }
        }
        fijar_transformacion_matriz_rsp(objeto->pos, objeto->orientacion, objeto->escalado_tamanio);
        gSPDisplayList(display_list_cabeza++, dato_0D0077D0);
        renderizar_modelo_animado((Armadura*) objeto->model, (Animacion**) objeto->vertice, (s16) objeto->desconocido_0D8,
                              (s16) objeto->textura_indice_lista);
    }
}

void renderizar_pinguinos_tren_objeto(s32 id_camara) {
    s32 i;
    s32 indice_objeto;
    s32 temporal_s1;
    s32 variable_a3;
    u16 variable_s1;
    u32 variable_s3;

    if (seleccion_cantidad_jugador_1 == 1) {
        variable_s3 = 0x0003D090;
    } else if (seleccion_cantidad_jugador_1 == 2) {
        variable_s3 = 0x00027100;
    } else {
        variable_s3 = 0x00015F90;
    }
    for (i = 0; i < PINGUINOS_NUM; i++) {
        indice_objeto = lista_objeto_indice_1[i];
        if (lista_objeto[indice_objeto].state >= 2) {
            if (seleccion_cantidad_jugador_1 == 1) {
                variable_s1 = 0x4000;
                if (i == 0) {
                    variable_a3 = 0x000005DC;
                } else if (funcion_80072320(indice_objeto, 8) != 0) {
                    variable_a3 = 0x00000320;
                } else {
                    variable_a3 = 0x000003E8;
                }
            } else {
                if (funcion_80072320(indice_objeto, 8) != 0) {
                    variable_a3 = 0x000001F4;
                    variable_s1 = 0x4000;
                } else {
                    variable_a3 = 0x00000258;
                    variable_s1 = 0x5555;
                }
            }
            temporal_s1 = funcion_8008A364(indice_objeto, id_camara, variable_s1, variable_a3);
            if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
                funcion_800557B4(indice_objeto, (u32) temporal_s1, variable_s3);
            }
        }
    }
}

void funcion_80055AB8(s32 indice_objeto, s32 id_camara) {
    Camara* camara;

    camara = &camara1[id_camara];
    if (lista_objeto[indice_objeto].state >= 2) {
        if (es_obj_bandera_situacion_activo(indice_objeto, 0x00100000) != 0) {
            dato_80183E40[0] = lista_objeto[indice_objeto].pos[0];
            dato_80183E40[1] = lista_objeto[indice_objeto].pos[1] + 16.0;
            dato_80183E40[2] = lista_objeto[indice_objeto].pos[2];
            dato_80183E80[0] = 0;
            dato_80183E80[1] =
                funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], camara->pos);
            dato_80183E80[2] = 0x8000;
            funcion_800468E0(dato_80183E40, dato_80183E80, 0.54f, d_circuito_rainbow_road_esfera, dato_0D0062B0, 0x00000020,
                          0x00000040, 0x00000020, 0x00000040, 5);
        } else {
            fijar_transformacion_matriz_rsp(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].angulo_sentido,
                                          lista_objeto[indice_objeto].escalado_tamanio);
            gSPDisplayList(display_list_cabeza++, dato_0D0077D0);
            renderizar_modelo_animado((Armadura*) lista_objeto[indice_objeto].model,
                                  (Animacion**) lista_objeto[indice_objeto].vertice, 0,
                                  (s16) lista_objeto[indice_objeto].textura_indice_lista);
        }
    }
}

void renderizar_chomps_cadena_objeto(s32 id_camara) {
    s32 variable_s1;
    s32 indice_objeto;

    for (variable_s1 = 0; variable_s1 < CHOMPS_CADENA_NUM; variable_s1++) {
        indice_objeto = lista_objeto_indice_2[variable_s1];
        funcion_8008A1D0(indice_objeto, id_camara, 0x000005DC, 0x000009C4);
        if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
            funcion_80055AB8(indice_objeto, id_camara);
        }
    }
}

void funcion_80055CCC(s32 indice_objeto, s32 id_camara) {
    SIN_USO s32 relleno;
    f32 probar;
    Camara* camara;

    camara = &camara1[id_camara];
    if (lista_objeto[indice_objeto].state >= 2) {
        funcion_8008A454(indice_objeto, id_camara, 0x0000012C);
        probar = lista_objeto[indice_objeto].pos[1] - lista_objeto[indice_objeto].altura_superficie;
        funcion_8004A6EC(indice_objeto, (20.0 / probar) + 0.5);
        if (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x00100000) != 0) {
            funcion_80043328(lista_objeto[indice_objeto].pos, (u16*) lista_objeto[indice_objeto].angulo_sentido,
                          lista_objeto[indice_objeto].escalado_tamanio, d_circuito_luigi_raceway_dl_F960);
            gSPDisplayList(display_list_cabeza++, d_circuito_luigi_raceway_dl_F650);
        } else {
            dato_80183E80[0] = (s16) lista_objeto[indice_objeto].angulo_sentido[0];
            dato_80183E80[1] =
                (s16) (funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], camara->pos) +
                       0x8000);
            dato_80183E80[2] = (u16) lista_objeto[indice_objeto].angulo_sentido[2];
            funcion_80043328(lista_objeto[indice_objeto].pos, dato_80183E80, lista_objeto[indice_objeto].escalado_tamanio,
                          d_circuito_luigi_raceway_dl_FBE0);
            gSPDisplayList(display_list_cabeza++, d_circuito_luigi_raceway_dl_FA20);
            if (seleccion_cantidad_jugador_1 == 1) {
                lista_objeto[indice_objeto].angulo_sentido[1] = 0;
            }
        }
    }
}

void renderizar_objeto_globo_aerostatico(s32 parametro0) {
    s32 indice_objeto;
    indice_objeto = lista_objeto_indice_1[0];
    if (estado_juego != 9) {
        funcion_8008A1D0(indice_objeto, parametro0, 0x000005DC, 0x00000BB8);
        if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
            funcion_80055CCC(indice_objeto, parametro0);
        }
    } else {
        fijar_objeto_bandera_situacion_false(indice_objeto, 0x00100000);
        funcion_80055CCC(indice_objeto, parametro0);
    }
}

void funcion_80055EF4(s32 indice_objeto, SIN_USO s32 parametro1) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    if (objeto->state >= 2) {
        funcion_80043220(objeto->pos, objeto->angulo_sentido, objeto->escalado_tamanio, objeto->model);
    }
}

void funcion_80055F48(s32 parametro0) {
    s32 algun_indice;

    for (algun_indice = 0; algun_indice < 3; algun_indice++) {
        funcion_80055EF4(lista_objeto_indice_1[algun_indice], parametro0);
    }
}

void funcion_80055FA0(s32 indice_objeto, SIN_USO s32 parametro1) {
    Mat4 algun_matriz_1;
    Mat4 algun_matriz_2;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    if (objeto->state >= 2) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[0]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        fijar_transformacion_matriz_mtxf(algun_matriz_1, objeto->pos, objeto->angulo_sentido, objeto->escalado_tamanio);
        convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], algun_matriz_1);
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gSPDisplayList(display_list_cabeza++, dato_0D0077A0);
        gSPDisplayList(display_list_cabeza++, objeto->model);
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(algun_matriz_2);
        fijar_posicion_render(algun_matriz_2, 0);
    }
}

void funcion_80056160(s32 parametro0) {
    funcion_80055FA0(lista_objeto_indice_1[3], parametro0);
}

void renderizar_neon_objeto(s32 id_camara) {
    Camara* camara;
    s32 variable_s2;
    s32 indice_objeto;
    Objeto* objeto;

    camara = &camara1[id_camara];
    for (variable_s2 = 0; variable_s2 < 10; variable_s2++) {
        indice_objeto = lista_objeto_indice_1[variable_s2];
        if (dato_8018E838[id_camara] == 0) {
            objeto = &lista_objeto[indice_objeto];
            if ((objeto->state >= 2) && (es_obj_indice_bandera_situacion_inactivo(indice_objeto, 0x00080000) != 0) &&
                (es_visible_objeto_en_camara(indice_objeto, camara, 0x2AABU) != 0)) {
                objeto->orientacion[1] = angulo_entre_camara_objeto(indice_objeto, camara);
                dibujar_2d_textura_en(objeto->pos, objeto->orientacion, objeto->escalado_tamanio, (u8*) objeto->t_lut_activo,
                                   objeto->textura_activo, erizo_vtx_comun, 0x00000040, 0x00000040, 0x00000040,
                                   0x00000020);
            }
        }
    }
}

void funcion_800562E4(s32 parametro0, s32 parametro1, s32 parametro2) {
    dato_80165860 = dato_800E46F8[parametro0][0];
    dato_8016586C = dato_800E46F8[parametro0][1];
    dato_80165878 = dato_800E46F8[parametro0][2];
    funcion_8004B138(dato_80165860, dato_8016586C, dato_80165878, parametro2);
    fijar_transformacion_matriz_rsp(dato_80183E40, dato_80183E80, 0.2f);
    funcion_80044BF8(comun_textura_particula_chispa[parametro1], 0x00000020, 0x00000020);
    gSPVertex(display_list_cabeza++, dato_0D005AE0, 4, 0);
    gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
}

void funcion_800563DC(s32 indice_objeto, s32 id_camara, s32 parametro2) {
    s32 temporal_s0;
    s32 temporal_v0;
    s32 residuo;
    Camara* camara;
    Objeto* objeto;

    camara = &camara1[id_camara];
    objeto = &lista_objeto[indice_objeto];
    residuo = dato_801655CC % 4U;
    dato_80183E40[0] = objeto->pos[0];
    dato_80183E40[1] = objeto->pos[1] + 1.0;
    dato_80183E40[2] = objeto->pos[2];
    dato_80183E80[0] = 0;
    dato_80183E80[1] = funcion_800418AC(objeto->pos[0], objeto->pos[2], camara->pos);
    dato_80183E80[2] = 0x8000;
    fijar_transformacion_matriz_rsp(dato_80183E40, dato_80183E80, 0.2f);
    gSPDisplayList(display_list_cabeza++, dato_0D007E98);
    funcion_8004B310(parametro2);
    dibujar_superponer_textura_rectangulo((u8*) bomba_tlut_comun, bomba_textura_comun[residuo], dato_0D005AE0, 0x00000020,
                                   0x00000020, 0x00000020, 0x00000020);
    temporal_s0 = dato_8018D400;
    gSPDisplayList(display_list_cabeza++, dato_0D007B00);
    funcion_8004B414(0, 0, 0, parametro2);
    dato_80183E40[1] = dato_80183E40[1] + 4.0;
    dato_80183E80[2] = 0;
    funcion_800562E4(temporal_s0 % 3, temporal_s0 % 4, parametro2);
    temporal_v0 = temporal_s0 + 1;
    dato_80183E80[2] = 0x6000;
    funcion_800562E4(temporal_v0 % 3, temporal_v0 % 4, parametro2);
    temporal_v0 = temporal_s0 + 2;
    dato_80183E80[2] = 0xA000;
    funcion_800562E4(temporal_v0 % 3, temporal_v0 % 4, parametro2);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_8005669C(s32 indice_objeto, SIN_USO s32 parametro1, s32 parametro2) {
    gSPDisplayList(display_list_cabeza++, dato_0D0079E8);
    funcion_8004B310(parametro2);
    cargar_textura_bloque_rgba16_espejo((u8*) dato_0D02AA58, 0x00000010, 0x00000010);
    dato_80183E40[1] = lista_objeto[indice_objeto].pos[1] - 2.0;
    dato_80183E40[0] = lista_objeto[indice_objeto].pos[0] + 2.0;
    dato_80183E40[2] = lista_objeto[indice_objeto].pos[2] + 2.0;
    funcion_800431B0(dato_80183E40, dato_80183E80, 0.15f, rectangulo_vtx_comun);
    dato_80183E40[0] = lista_objeto[indice_objeto].pos[0] + 2.0;
    dato_80183E40[2] = lista_objeto[indice_objeto].pos[2] - 2.0;
    funcion_800431B0(dato_80183E40, dato_80183E80, 0.15f, rectangulo_vtx_comun);
    dato_80183E40[0] = lista_objeto[indice_objeto].pos[0] - 2.0;
    dato_80183E40[2] = lista_objeto[indice_objeto].pos[2] - 2.0;
    funcion_800431B0(dato_80183E40, dato_80183E80, 0.15f, rectangulo_vtx_comun);
    dato_80183E40[0] = lista_objeto[indice_objeto].pos[0] - 2.0;
    dato_80183E40[2] = lista_objeto[indice_objeto].pos[2] + 2.0;
    funcion_800431B0(dato_80183E40, dato_80183E80, 0.15f, rectangulo_vtx_comun);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_800568A0(s32 indice_objeto, s32 id_jugador) {
    Mat4 sp30;
    Jugador* jugador;

    jugador = &jugador_uno[id_jugador];
    dato_80183E50[0] = lista_objeto[indice_objeto].pos[0];
    dato_80183E50[1] = lista_objeto[indice_objeto].altura_superficie + 0.8;
    dato_80183E50[2] = lista_objeto[indice_objeto].pos[2];
    transformar_matriz_conjunto(sp30, jugador->colision.vector_orientacion, dato_80183E50, 0U, 0.5f);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], sp30);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(display_list_cabeza++, dato_0D007B98);
}

void funcion_800569F4(s32 indice_jugador) {
    s32 indice_objeto;

    indice_objeto = objeto_indice_kart_bomba[indice_jugador];
    inicializar_objeto(indice_objeto, 0);
    lista_objeto[indice_objeto].prim_alpha = 0;
}

void funcion_80056A40(s32 indice_jugador, s32 prim_alpha) {
    s32 indice_objeto;

    indice_objeto = objeto_indice_kart_bomba[indice_jugador];
    inicializar_objeto(indice_objeto, 0);
    lista_objeto[indice_objeto].prim_alpha = (s16) prim_alpha;
}

void funcion_80056A94(s32 indice_jugador) {
    funcion_80072428(objeto_indice_kart_bomba[indice_jugador]);
}
