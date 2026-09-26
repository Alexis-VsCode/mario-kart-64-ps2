// Objetos ambiente

void funcion_80050320(void) {
    s16 temporal_v0;
    s16 id_personaje;
    s32 variable_s0;
    s32 cantidad_vuelta;
    s32 variable_a0;

    if (dato_801657E2 == 0) {
        for (variable_s0 = 0; variable_s0 < 4; variable_s0++) {
            variable_a0 = 0;
            if (dato_8018D050[variable_s0] >= 0.0f) {
                if (dato_8018D078[variable_s0] < 0.0) {
                    variable_a0 = 1;
                }
                temporal_v0 = gp_actual_carrera_jugador_id_por_puesto[variable_s0];
                id_personaje = gp_actual_carrera_personaje_id_por_puesto[variable_s0];
                cantidad_vuelta = cantidad_vuelta_por_id_jugador[temporal_v0];
                if (id_personaje == jugador_uno->id_personaje) {
                    funcion_8004FDB4(dato_8018D028[variable_s0], dato_8018D050[variable_s0], variable_s0, cantidad_vuelta, id_personaje, 0x000000FF, 1,
                                  variable_a0, 0);
                } else {
                    funcion_8004FDB4(dato_8018D028[variable_s0], dato_8018D050[variable_s0], variable_s0, cantidad_vuelta, id_personaje, dato_8018D3E0, 0,
                                  variable_a0, 0);
                }
            }
        }
    } else {
        for (variable_s0 = 0; variable_s0 < 8; variable_s0++) {
            variable_a0 = 0;
            if (dato_8018D050[variable_s0] >= 0.0f) {
                if (dato_8018D078[variable_s0] <= 0.0) {
                    variable_a0 = 1;
                }
                temporal_v0 = gp_actual_carrera_jugador_id_por_puesto[variable_s0];
                id_personaje = (jugador_uno + temporal_v0)->id_personaje;
                cantidad_vuelta = cantidad_vuelta_por_id_jugador[temporal_v0];
                if (temporal_v0 == 0) {
                    funcion_8004FDB4(dato_8018D028[variable_s0], dato_8018D050[variable_s0], variable_s0, cantidad_vuelta, id_personaje, 0x000000FF, 1,
                                  variable_a0, 1);
                } else {
                    funcion_8004FDB4(dato_8018D028[variable_s0], dato_8018D050[variable_s0], variable_s0, cantidad_vuelta, id_personaje, 0x000000FF, 0,
                                  variable_a0, 1);
                }
            }
        }
    }
    gSPTexture(display_list_cabeza++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

s32 funcion_80050644(u16 parametro0, s32* parametro1, s32* parametro2) {
    s32 variable_v0 = 0;
    s32 cosa = 0;
    s32 probar = cantidad_vuelta_por_id_jugador[parametro0];

    if (probar < 3) {
        if (seleccion_cantidad_jugador_1 == 1) {
            if (probar >= 0) {
                cosa = (s32) (porciento_finalizacion_vuelta_por_id_jugador[parametro0] * 928);
            }
            if (cosa < 0x104) {
                *parametro1 = cosa;
                *parametro2 = 0;
                variable_v0 = 1;
            } else if (cosa < 0x1D0) {
                *parametro1 = 0x00000104;
                *parametro2 = cosa - 0x104;
                variable_v0 = 2;
            } else if (cosa < 0x2D4) {
                *parametro1 = 0x2D4 - cosa;
                *parametro2 = 0x000000CC;
                variable_v0 = 3;
            } else {
                *parametro1 = 0;
                *parametro2 = 0x3A0 - cosa;
                variable_v0 = 4;
            }
        } else {
            if (probar >= 0) {
                cosa = (s32) (porciento_finalizacion_vuelta_por_id_jugador[parametro0] * 260);
            }
            *parametro1 = cosa;
            *parametro2 = 0;
        }
    } else if (seleccion_cantidad_jugador_1 == 1) {
        *parametro1 = 0x00000020;
        *parametro2 = (gp_actual_carrera_puesto_por_id_jugador[parametro0] * 0x14) + 0x20;
    } else {
        cosa = (s32) (porciento_finalizacion_vuelta_por_id_jugador[parametro0] * 260);
        *parametro1 = cosa;
        *parametro2 = 0;
    }
    return variable_v0;
}

void funcion_800507D8(u16 indice_bomba, s32* parametro1, s32* parametro2) {
    s32 temporal_v0 = karts_bomba[indice_bomba].indice_punto_camino;
    s32 variable_v1 = 0;

    if (temporal_v0 != 0) {
        variable_v1 = (s32) (temporal_v0 * 0x3A0) / (s32) cantidad_camino_seleccionado;
    }
    if (variable_v1 < 0x104) {
        *parametro1 = variable_v1;
        *parametro2 = 0;
    } else if (variable_v1 < 0x1D0) {
        *parametro1 = 0x00000104;
        *parametro2 = variable_v1 - 0x104;
    } else if (variable_v1 < 0x2D4) {
        *parametro1 = 0x2D4 - variable_v1;
        *parametro2 = 0x000000CC;
    } else {
        *parametro1 = 0;
        *parametro2 = 0x3A0 - variable_v1;
    }
}

void funcion_800508C0(void) {
    s32 sp54;
    s32 sp50;
    s32 sp4_c;
    s32 temporal_v1;
    s16 variable_s0;
    SIN_USO s16 margen_pila;
    u16 variable_s0_2;
    u16 variable_s1;
    u16 variable_s2;

    if (seleccion_modo == CONTRARRELOJ) {
        variable_s0 = id_jugador_ant_por_puesto[0];
    } else {
        variable_s0 = gp_actual_carrera_jugador_id_por_puesto[0];
    }
    sp4_c = funcion_80050644(variable_s0, &sp54, &sp50);
    temporal_v1 = cantidad_vuelta_por_id_jugador[variable_s0];
    if (temporal_v1 > 0) {
        if (temporal_v1 == 1) {
            variable_s0_2 = 0;
            variable_s1 = 0;
            variable_s2 = 0x000000FF;
        } else {
            if (temporal_v1 == 2) {
                variable_s0_2 = 0x00FF;
                variable_s1 = 0x000000FF;
                variable_s2 = 0;
            } else {
                variable_s0_2 = 0x00FF;
                variable_s1 = 0;
                variable_s2 = 0;
            }
        }
        funcion_8004C024(0x0020, 0x0012, 0x0104, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
        funcion_8004C148(0x0124, 0x0012, 0x00CC, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
        funcion_8004C024(0x0020, 0x00DE, 0x0104, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
        funcion_8004C148(0x0020, 0x0012, 0x00CC, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
    }
    if ((temporal_v1 < 0) || (temporal_v1 >= 3)) {
        return;
    }
    switch (temporal_v1) {
        case 0:
            variable_s0_2 = 0;
            variable_s1 = 0;
            variable_s2 = 0x00FF;
            break;
        case 1:
            variable_s0_2 = 0x00FF;
            variable_s1 = 0x00FF;
            variable_s2 = 0;
            break;
        case 2:
            variable_s0_2 = 0x00FF;
            variable_s1 = 0;
            variable_s2 = 0;
            break;
        default:
            break;
    }
    switch (sp4_c) {
        case 1:
            funcion_8004C024(0x0020, 0x0012, sp54, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
            break;
        case 2:
            funcion_8004C024(0x0020, 0x0012, 0x0104, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
            funcion_8004C148(0x0124, 0x0012, sp50, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
            break;
        case 3:
            funcion_8004C024(0x0020, 0x0012, 0x0104, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
            funcion_8004C148(0x0124, 0x0012, 0x00CC, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
            funcion_8004C024(sp54 + 0x20, 0x00DE, 0x104 - sp54, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
            break;
        case 4:
            funcion_8004C024(0x0020, 0x0012, 0x0104, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
            funcion_8004C148(0x0124, 0x0012, 0x00CC, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
            funcion_8004C024(0x0020, 0x00DE, 0x0104, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
            funcion_8004C148(0x0020, sp50 + 0x12, 0xCC - sp50, variable_s0_2, variable_s1, variable_s2, 0x000000FF);
            break;
        case 0:
        default:
            break;
    }
}

void funcion_80050C68(void) {
    SIN_USO s32 margen_pila_0;
    s32 sp88;
    s32 sp84;
    SIN_USO s32 margen_pila_1;
    s32 variable_s1;

    for (variable_s1 = 0; variable_s1 < NUM_KARTS_BOMBA_VERSUS; variable_s1++) {
        if ((karts_bomba[variable_s1].state != BOMBA_ESTADO_EXPLOTADO) && (karts_bomba[variable_s1].state != INACTIVO_ESTADO_BOMBA)) {
            funcion_800507D8(variable_s1, &sp88, &sp84);
            gSPDisplayList(display_list_cabeza++, dato_0D007DB8);
            gDPLoadTLUT_pal256(display_list_cabeza++, retrato_tlut_comun_kart_bomba_y_signo_pregunta);
            cargar_textura_rsp(retrato_textura_comun_kart_bomba, 0x00000020, 0x00000020);
            funcion_80042330(sp88 + 0x20, sp84 + 0x12, 0U, 0.6f);
            gSPDisplayList(display_list_cabeza++, dato_0D0069E0);
        }
    }
}

void funcion_80050E34(s32 id_jugador, s32 parametro1) {
    s32 indice_objeto;
    s32 sp_d0;
    s32 sp_cc;
    Jugador *ficticio = &jugador_uno[id_jugador];
    s32 sp_c4;
    s32 cantidad_vuelta;
    s32 id_personaje;
    s32 sp_b8;
    s32 temporal_v0_2;
    Objeto* objeto;
    Jugador *jugador = &jugador_uno[id_jugador];

    cantidad_vuelta = cantidad_vuelta_por_id_jugador[id_jugador];
    id_personaje = jugador->id_personaje;
    indice_objeto = dato_8018CE10[id_jugador].indice_objeto;

    if (seleccion_cantidad_jugador_1 == 1) {
        sp_c4 = 0x00000012;
    } else {
        sp_c4 = 0x00000078;
    }

    temporal_v0_2 = funcion_80050644(id_jugador, &sp_d0, &sp_cc);
    if ((temporal_v0_2 == 2) || (temporal_v0_2 == 3)) {
        sp_b8 = 1;
    } else {
        sp_b8 = 0;
    }

    if ((id_circuito_actual == CIRCUITO_YOSHI_VALLEY) && (cantidad_vuelta < 3)) {
        gSPDisplayList(display_list_cabeza++, dato_0D007DB8);
        gDPLoadTLUT_pal256(display_list_cabeza++, retrato_tlut_comun_kart_bomba_y_signo_pregunta);
        cargar_textura_rsp(retrato_textura_comun_signo_pregunta, 0x00000020, 0x00000020);
        objeto = &lista_objeto[indice_objeto];
        objeto->pos[0] = objeto->offset[0] + ((f32) (sp_d0 + 0x20));
        objeto->pos[1] = objeto->offset[1] + ((f32) (sp_c4 + sp_cc));
        objeto->pos[2] = objeto->offset[2];
        fijar_transformacion_matriz_rsp(objeto->pos, objeto->angulo_sentido, objeto->escalado_tamanio);
        gSPDisplayList(display_list_cabeza++, dato_0D0069E0);
    } else {
        gDPLoadTLUT_pal256(display_list_cabeza++, ts_tlu_retrato[id_personaje]);
        gSPDisplayList(display_list_cabeza++, dato_0D007DB8);
        if (jugador->efectos & EFECTO_ESTRELLA) {
            funcion_8004B614((s32) dato_801656C0, (s32) dato_801656D0, (s32) dato_801656E0, 0x00000080, 0x00000080, 0x00000080,
                          (s32) lista_objeto[indice_objeto].prim_alpha);
        } else {
            fijar_transparencia((s32) lista_objeto[indice_objeto].prim_alpha);
        }
        cargar_textura_rsp(texturas_retrato[id_personaje], 0x00000020, 0x00000020);
        objeto = &lista_objeto[indice_objeto];
        objeto->pos[0] = objeto->offset[0] + ((f32) (sp_d0 + 0x20));
        objeto->pos[1] = objeto->offset[1] + ((f32) (sp_c4 + sp_cc));
        objeto->pos[2] = objeto->offset[2];
        fijar_transformacion_matriz_rsp(objeto->pos, objeto->angulo_sentido, objeto->escalado_tamanio);
        if (sp_b8 != 0) {
            gSPDisplayList(display_list_cabeza++, dato_0D0069F8);
        } else {
            gSPDisplayList(display_list_cabeza++, dato_0D0069E0);
        }
        gDPLoadTLUT_pal256(display_list_cabeza++, comun_tlut_hud_tipo_c_puesto_diminuto_fuente);
        cargar_textura_rsp(comun_textura_hud_tipo_c_puesto_diminuto_fuente[parametro1 + 1], 8, 8);
        if (sp_b8 != 0) {
            funcion_80042330(sp_d0 + 0x26, (sp_c4 + sp_cc) + 4, 0U, 1.0f);
        } else {
            funcion_80042330(sp_d0 + 0x1B, (sp_c4 + sp_cc) + 4, 0U, 1.0f);
        }
        gSPDisplayList(display_list_cabeza++, dato_0D006950);
        if ((jugador == jugador_uno) && (seleccion_modo_pantalla == MODO_PANTALLA_1P)) {
            gSPDisplayList(display_list_cabeza++, dato_0D007A40);
            funcion_8004B35C(dato_8018D3E4, dato_8018D3E8, dato_8018D3EC, 0x000000FF);
            funcion_80044924(comun_textura_personaje_retrato_borde, 0x00000020, 0x00000020);
            fijar_transformacion_matriz_rsp(objeto->pos, objeto->angulo_sentido, objeto->escalado_tamanio);
            gSPDisplayList(display_list_cabeza++, dato_0D0069E0);
        }
    }
}

void funcion_800514BC(void) {
    s32 temporal_a0;
    s32 variable_s0;
    s32 variable_s1;
    s32 variable_s3;
    Jugador* jugador;

    if (seleccion_modo_pantalla == 0) {
        funcion_800508C0();
    }
    variable_s3 = 8;
    if ((seleccion_cantidad_jugador_1 == 2) && (modo_pantalla_activo == 2)) {
        variable_s3 = 0;
    }
    for (variable_s0 = variable_s3 - 1, variable_s1 = 0; variable_s1 < variable_s3; variable_s1++, variable_s0--) {
        temporal_a0 = gp_actual_carrera_jugador_id_por_puesto[variable_s0];
        jugador = &jugador_uno[temporal_a0];
        if ((jugador->type & EXISTE_JUGADOR) && ((temporal_a0 != 0) || (seleccion_cantidad_jugador_1 != 1))) {
            funcion_80050E34(temporal_a0, variable_s0);
        }
    }
    if (seleccion_modo == 1) {
        funcion_80050E34(0, gp_actual_carrera_puesto_por_duplicar_id_jugador[0]);
    } else if (seleccion_cantidad_jugador_1 == 1) {
        funcion_80050E34(0, gp_actual_carrera_puesto_por_id_jugador[0]);
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void renderizar_particula_hoja_objeto(SIN_USO s32 id_camara) {
    s32 algun_indice;
    s32 indice_hoja;
    Objeto* objeto;

    gSPDisplayList(display_list_cabeza++, dato_0D0079C8);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
    cargar_textura_bloque_rgba16_espejo((u8*) comun_textura_particula_hoja, 0x00000020, 0x00000010);
    for (algun_indice = 0; algun_indice < hoja_particula_tamanio; algun_indice++) {
        indice_hoja = particula_hoja[algun_indice];
        if (indice_hoja != -1) {
            objeto = &lista_objeto[indice_hoja];
            if ((objeto->state >= 2) && (objeto->desconocido_0D5 == 7) && (cantidad_hud_matriz <= MTX_HUD_POOL_TAMANIO_MAX)) {
                rsp_conjunto_matriz_g_objeto_lista(indice_hoja);
                gSPDisplayList(display_list_cabeza++, dato_0D0069C8);
            }
        }
    }
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void renderizar_particulas_copos_objeto(void) {
    s32 algun_indice;
    s32 indice_copo;

    gSPDisplayList(display_list_cabeza++, dato_0D007AE0);
    gDPSetCombineLERP(display_list_cabeza++, 1, 0, SHADE, 0, 0, 0, 0, TEXEL0, 1, 0, SHADE, 0, 0, 0, 0, TEXEL0);
    funcion_80044F34(dato_0D0293D8, 0x10, 0x10);
    for (algun_indice = 0; algun_indice < COPOS_NUM; algun_indice++) {
        indice_copo = particula_objeto_1[algun_indice];
        if (lista_objeto[indice_copo].state >= 2) {
            rsp_conjunto_matriz_g_objeto_lista(indice_copo);
            gSPDisplayList(display_list_cabeza++, dato_0D006980);
        }
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_800518F8(s32 indice_objeto, s16 parametro1, s16 parametro2) {
    SIN_USO s32 relleno[1];
    if (lista_objeto[indice_objeto].status & 0x10) {
        if (dato_8018D228 != lista_objeto[indice_objeto].desconocido_0D5) {
            dato_8018D228 = lista_objeto[indice_objeto].desconocido_0D5;
            funcion_80044DA0(lista_objeto[indice_objeto].textura_activo, lista_objeto[indice_objeto].textura_ancho,
                          lista_objeto[indice_objeto].textura_altura);
        }
        funcion_80042330(parametro1, parametro2, 0U, lista_objeto[indice_objeto].escalado_tamanio);
        gSPVertex(display_list_cabeza++, lista_objeto[indice_objeto].vertice, 4, 0);
        gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
    }
}

void funcion_800519D4(s32 indice_objeto, s16 parametro1, s16 parametro2) {
    if (lista_objeto[indice_objeto].status & 0x10) {
        if (dato_8018D228 != lista_objeto[indice_objeto].desconocido_0D5) {
            dato_8018D228 = lista_objeto[indice_objeto].desconocido_0D5;
            funcion_80044DA0(lista_objeto[indice_objeto].textura_activo, lista_objeto[indice_objeto].textura_ancho,
                          lista_objeto[indice_objeto].textura_altura);
        }
        funcion_8004B138(0x000000FF, 0x000000FF, 0x000000FF, lista_objeto[indice_objeto].prim_alpha);
        funcion_80042330(parametro1, parametro2, 0U, lista_objeto[indice_objeto].escalado_tamanio);
        gSPVertex(display_list_cabeza++, lista_objeto[indice_objeto].vertice, 4, 0);
        gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
    }
}

void funcion_80051ABC(s16 parametro0, s32 parametro1) {
    s32 variable_s0;
    s32 indice_objeto;
    Objeto* objeto;

    dato_8018D228 = 0xFF;
    gSPDisplayList(display_list_cabeza++, dato_0D007A60);
    if ((u8) dato_8018D230 != 0) {
        funcion_8004B414(0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF);
        for (variable_s0 = 0; variable_s0 < dato_8018D1F0; variable_s0++) {
            indice_objeto = dato_8018CC80[parametro1 + variable_s0];
            objeto = &lista_objeto[indice_objeto];
            funcion_800519D4(indice_objeto, objeto->desconocido_09C, parametro0 - objeto->desconocido_09E);
        }
    } else {
        funcion_8004B6C4(0x000000FF, 0x000000FF, 0x000000FF);
        for (variable_s0 = 0; variable_s0 < dato_8018D1F0; variable_s0++) {
            indice_objeto = dato_8018CC80[parametro1 + variable_s0];
            objeto = &lista_objeto[indice_objeto];
            funcion_800518F8(indice_objeto, objeto->desconocido_09C, parametro0 - objeto->desconocido_09E);
        }
    }
}

void funcion_80051C60(s16 parametro0, s32 parametro1) {
    s16 variable_s5;
    s32 variable_s0;
    s32 indice_objeto;
    Objeto* objeto;

    if (dato_801658FE == 0) {
        if (id_circuito_actual == CIRCUITO_KOOPA_BEACH) {
            variable_s5 = parametro0;
        } else if (id_circuito_actual == CIRCUITO_MOO_MOO_FARM) {
            variable_s5 = parametro0 - 0x10;
        } else if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
            variable_s5 = parametro0 - 0x10;
        } else {
            variable_s5 = parametro0 + 0x10;
        }
    } else if (id_circuito_actual == CIRCUITO_KOOPA_BEACH) {
        variable_s5 = parametro0 * 2;
    } else {
        variable_s5 = parametro0 + 0x20;
    }
    dato_8018D228 = 0xFF;
    gSPDisplayList(display_list_cabeza++, dato_0D007A60);
    if ((u8) dato_8018D230 != 0) {
        funcion_8004B414(0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF);
        for (variable_s0 = 0; variable_s0 < dato_8018D1F0; variable_s0++) {
            indice_objeto = dato_8018CC80[parametro1 + variable_s0];
            objeto = &lista_objeto[indice_objeto];
            funcion_800519D4(indice_objeto, objeto->desconocido_09C, (variable_s5 - objeto->desconocido_09E) / 2);
        }
    } else {
        funcion_8004B6C4(0x000000FF, 0x000000FF, 0x000000FF);
        for (variable_s0 = 0; variable_s0 < dato_8018D1F0; variable_s0++) {
            indice_objeto = dato_8018CC80[parametro1 + variable_s0];
            objeto = &lista_objeto[indice_objeto];
            funcion_800518F8(indice_objeto, objeto->desconocido_09C, (variable_s5 - objeto->desconocido_09E) / 2);
        }
    }
}

void funcion_80051EBC(void) {
    funcion_80051ABC(240 - dato_800DC5EC->altura_camara, 0);
}

void funcion_80051EF8(void) {
    s16 temporal_a0;

    temporal_a0 = 0xF0 - dato_800DC5EC->altura_camara;
    if (id_circuito_actual == CIRCUITO_KOOPA_BEACH) {
        temporal_a0 = temporal_a0 - 0x30;
    } else if (id_circuito_actual == CIRCUITO_MOO_MOO_FARM) {
        temporal_a0 = temporal_a0 - 0x40;
    } else if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
        temporal_a0 = temporal_a0 - 0x40;
    } else {
        temporal_a0 = temporal_a0 - 0x30;
    }
    funcion_80051ABC(temporal_a0, 0);
}

void funcion_80051F9C(void) {
    s16 temporal_a0;

    temporal_a0 = 0xF0 - dato_800DC5F0->altura_camara;
    if (id_circuito_actual == CIRCUITO_KOOPA_BEACH) {
        temporal_a0 = temporal_a0 - 0x30;
    } else if (id_circuito_actual == CIRCUITO_MOO_MOO_FARM) {
        temporal_a0 = temporal_a0 - 0x40;
    } else if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
        temporal_a0 = temporal_a0 - 0x40;
    } else {
        temporal_a0 = temporal_a0 - 0x30;
    }
    funcion_80051ABC(temporal_a0, dato_8018D1F0);
}

void funcion_80052044(void) {
    funcion_80051C60(240 - dato_800DC5EC->altura_camara, 0);
}

void funcion_80052080(void) {
    funcion_80051C60(240 - dato_800DC5F0->altura_camara, dato_8018D1F0);
}

void funcion_800520C0(s32 parametro0) {
    if (lista_objeto[parametro0].desconocido_0D5 == 0) {
        dato_800E45C0[0].l[0].l.dir[0] = dato_800E45C0[1].l[0].l.dir[0] = dato_800E45C0[2].l[0].l.dir[0] =
            dato_800E45C0[3].l[0].l.dir[0] = 0;
        dato_800E45C0[0].l[0].l.dir[1] = dato_800E45C0[1].l[0].l.dir[1] = dato_800E45C0[2].l[0].l.dir[1] =
            dato_800E45C0[3].l[0].l.dir[1] = -0x78;
        dato_800E45C0[0].l[0].l.dir[2] = dato_800E45C0[1].l[0].l.dir[2] = dato_800E45C0[2].l[0].l.dir[2] =
            dato_800E45C0[3].l[0].l.dir[2] = 0;
    } else {
        dato_800E45C0[0].l[0].l.dir[0] = dato_800E45C0[1].l[0].l.dir[0] = dato_800E45C0[2].l[0].l.dir[0] =
            dato_800E45C0[3].l[0].l.dir[0] = 0x63;
        dato_800E45C0[0].l[0].l.dir[1] = dato_800E45C0[1].l[0].l.dir[1] = dato_800E45C0[2].l[0].l.dir[1] =
            dato_800E45C0[3].l[0].l.dir[1] = 0x42;
        dato_800E45C0[0].l[0].l.dir[2] = dato_800E45C0[1].l[0].l.dir[2] = dato_800E45C0[2].l[0].l.dir[2] =
            dato_800E45C0[3].l[0].l.dir[2] = 0;
    }
}

void funcion_8005217C(SIN_USO s32 parametro0) {
    Objeto* objeto;
    s32 temporal_a3;

    temporal_a3 = lista_objeto_indice_2[0];
    objeto = &lista_objeto[temporal_a3];
    if (objeto->state >= 2) {
        if (es_obj_bandera_situacion_activo(temporal_a3, 0x00000010) != 0) {
            fijar_transformacion_matriz_rsp(objeto->pos, objeto->angulo_sentido, objeto->escalado_tamanio);
            funcion_800520C0(temporal_a3);

            gSPDisplayList(display_list_cabeza++, dato_0D007828);
            gSPLight(display_list_cabeza++, &dato_800E45C0[0].l[0], LIGHT_1);
            gSPLight(display_list_cabeza++, &dato_800E45C0[0].a, LIGHT_2);
            gSPDisplayList(display_list_cabeza++, d_circuito_banshee_boardwalk_dl_7B38);
            gSPLight(display_list_cabeza++, &dato_800E45C0[1].l[0], LIGHT_1);
            gSPLight(display_list_cabeza++, &dato_800E45C0[1].a, LIGHT_2);
            gSPDisplayList(display_list_cabeza++, d_circuito_banshee_boardwalk_dl_7978);
            gSPLight(display_list_cabeza++, &dato_800E45C0[2].l[0], LIGHT_1);
            gSPLight(display_list_cabeza++, &dato_800E45C0[2].a, LIGHT_2);
            gSPDisplayList(display_list_cabeza++, d_circuito_banshee_boardwalk_dl_78C0);
            gSPLight(display_list_cabeza++, &dato_800E45C0[3].l[0], LIGHT_1);
            gSPLight(display_list_cabeza++, &dato_800E45C0[3].a, LIGHT_2);
            gSPDisplayList(display_list_cabeza++, d_circuito_banshee_boardwalk_dl_7650);
        }
    }
}

void funcion_800523B8(s32 indice_objeto, s32 parametro1, u32 parametro2) {
    SIN_USO s32 relleno[2];
    Objeto* objeto;
    Camara* camara = &camara1[parametro1];

    objeto = &lista_objeto[indice_objeto];
    objeto->orientacion[1] = funcion_800418AC(objeto->pos[0], objeto->pos[2], camara->pos);
    funcion_800484BC(objeto->pos, objeto->orientacion, objeto->escalado_tamanio, objeto->prim_alpha, (u8*) objeto->t_lut_activo,
                  objeto->textura_activo, objeto->vertice, 0x00000030, 0x00000028, 0x00000030, 0x00000028);
    if ((es_obj_bandera_situacion_activo(indice_objeto, 0x00000020) != 0) && (parametro2 < 0x15F91U)) {
        funcion_8004A630(&dato_8018C830, objeto->pos, 0.4f);
    }
}

void renderizar_boos_objeto(s32 parametro0) {
    u32 temporal_s2;
    s32 algun_indice;
    s32 indice_objeto;

    for (algun_indice = 0; algun_indice < NUM_BOOS; algun_indice++) {
        indice_objeto = lista_objeto_indice_3[algun_indice];
        if (lista_objeto[indice_objeto].state >= 2) {
            temporal_s2 = funcion_8008A364(indice_objeto, parametro0, 0x4000U, 0x00000320);
            if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
                funcion_800523B8(indice_objeto, parametro0, temporal_s2);
            }
        }
    }
}

void renderizar_murcielago_objeto(s32 id_camara) {
    s32 variable_s2;
    s32 indice_objeto;
    Camara* temporal_s7;

    indice_objeto = lista_objeto_indice_1[0];
    temporal_s7 = &camara1[id_camara];
    funcion_80046F60(lista_objeto[indice_objeto].t_lut_activo, lista_objeto[indice_objeto].textura_activo, 0x00000020, 0x00000040,
                  5);
    dato_80183E80[0] = lista_objeto[indice_objeto].orientacion[0];
    dato_80183E80[2] = lista_objeto[indice_objeto].orientacion[2];
    if ((dato_8018CFB0 != 0) || (dato_8018CFC8 != 0)) {
        for (variable_s2 = 0; variable_s2 < 40; variable_s2++) {
            indice_objeto = particula_objeto_2[variable_s2];
            if (indice_objeto == -1) {
                continue;
            }

            if ((lista_objeto[indice_objeto].state >= 2) && (cantidad_hud_matriz < 0x2EF)) {
                dato_80183E80[1] =
                    funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], temporal_s7->pos);
                funcion_800431B0(lista_objeto[indice_objeto].pos, dato_80183E80, lista_objeto[indice_objeto].escalado_tamanio,
                              dato_0D0062B0);
            }
        }
    }
    if ((dato_8018CFE8 != 0) || (dato_8018D000 != 0)) {
        for (variable_s2 = 0; variable_s2 < 30; variable_s2++) {
            indice_objeto = particula_objeto_3[variable_s2];
            if (indice_objeto == -1) {
                continue;
            }

            if ((lista_objeto[indice_objeto].state >= 2) && (cantidad_hud_matriz < 0x2EF)) {
                dato_80183E80[1] =
                    funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], temporal_s7->pos);
                funcion_800431B0(lista_objeto[indice_objeto].pos, dato_80183E80, lista_objeto[indice_objeto].escalado_tamanio,
                              dato_0D0062B0);
            }
        }
    }
    gSPTexture(display_list_cabeza++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

void renderizar_bin_basura_objeto(s32 id_camara) {
    s32 indice_objeto;
    Objeto* objeto;

    indice_objeto = lista_objeto_indice_1[1];
    funcion_8008A364(indice_objeto, id_camara, 0x5555U, 0x00000320);
    if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
        objeto = &lista_objeto[indice_objeto];
        if (objeto->state >= 2) {
            funcion_80043220(objeto->pos, objeto->orientacion, objeto->escalado_tamanio, objeto->model);
        }
    }
}

void funcion_8005285C(s32 parametro0) {
    Jugador* temporal_v0;

    temporal_v0 = &jugador_uno[parametro0];
    dato_80183E40[0] = temporal_v0->pos[0];
    dato_80183E40[1] = temporal_v0->pos[1];
    dato_80183E40[2] = temporal_v0->pos[2];
    dato_80183E80[0] = 0;
    dato_80183E80[1] = 0;
    dato_80183E80[2] = 0;
    funcion_80043500(dato_80183E40, dato_80183E80, 0.02f, d_circuito_sherbet_land_bloque_hielo_dl);
}

void funcion_800528EC(s32 parametro0) {
    s32 variable_s3;
    s32 indice_objeto;
    Objeto* objeto;

    dato_80183E80[0] = dato_8016582C[0];
    dato_80183E80[1] = dato_8016582C[1];
    dato_80183E80[2] = dato_8016582C[2];
    gSPDisplayList(display_list_cabeza++, dato_0D007B00);
    gSPNumLights(display_list_cabeza++, 1);
    gSPLight(display_list_cabeza++, &dato_800E4620.l[0], LIGHT_1);
    gSPLight(display_list_cabeza++, &dato_800E4620.a, LIGHT_2);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_LIGHTING | G_SHADING_SMOOTH);
    cargar_nomirror_bloque_ia16_textura(d_circuito_sherbet_land_hielo, 0x00000020, 0x00000020);
    if (seleccion_cantidad_jugador_1 < 3) {
        for (variable_s3 = 0; variable_s3 < objeto_particula_2_tamanio; variable_s3++) {
            indice_objeto = particula_objeto_2[variable_s3];
            if (indice_objeto != ID_OBJETO_NULO) {
                objeto = &lista_objeto[indice_objeto];
                if (objeto->state > 0) {
                    fijar_transformacion_matriz_rsp(objeto->pos, dato_80183E80, objeto->escalado_tamanio);
                    gSPVertex(display_list_cabeza++, dato_0D005BD0, 3, 0);
                    gSPDisplayList(display_list_cabeza++, dato_0D006930);
                }
            }
        }
    } else {
        for (variable_s3 = 0; variable_s3 < objeto_particula_2_tamanio; variable_s3++) {
            indice_objeto = particula_objeto_2[variable_s3];
            if (indice_objeto != ID_OBJETO_NULO) {
                objeto = &lista_objeto[indice_objeto];
                if ((objeto->state > 0) && (parametro0 == objeto->desconocido_084[7]) && (cantidad_hud_matriz <= MTX_HUD_POOL_TAMANIO_MAX)) {
                    fijar_transformacion_matriz_rsp(objeto->pos, dato_80183E80, objeto->escalado_tamanio);
                    gSPVertex(display_list_cabeza++, dato_0D005BD0, 3, 0);
                    gSPDisplayList(display_list_cabeza++, dato_0D006930);
                }
            }
        }
    }
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPTexture(display_list_cabeza++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

void renderizar_bloque_hielo(s32 parametro0) {
    s32 id_jugador;
    s32 indice_objeto;

    dato_800E4620.l[0].l.dir[0] = dato_80165840[0];
    dato_800E4620.l[0].l.dir[1] = dato_80165840[1];
    dato_800E4620.l[0].l.dir[2] = dato_80165840[2];
    gSPLight(display_list_cabeza++, &dato_800E4620.l[0], LIGHT_1);
    gSPLight(display_list_cabeza++, &dato_800E4620.a, LIGHT_2);
    for (id_jugador = 0; id_jugador < seleccion_cantidad_jugador_1; id_jugador++) {
        indice_objeto = indice_lakitu_lista[id_jugador];
        if (indice_objeto) {}
        if (funcion_80072320(indice_objeto, 4) != false) {
            funcion_8005285C(id_jugador);
        }
        funcion_80072320(indice_objeto, 0x00000010);
    }
    funcion_800528EC(parametro0);
}

void funcion_80052D70(s32 id_jugador) {
    s32 probar;
    Jugador* temporal_v1;

    temporal_v1 = &jugador_uno[id_jugador];
    probar = indice_lakitu_lista[id_jugador];
    if (funcion_80072320(probar, 8) != 0) {
        dato_80183E40[0] = temporal_v1->pos[0];
        dato_80183E40[1] = temporal_v1->desconocido_074 - 6.5;
        dato_80183E40[2] = temporal_v1->pos[2];
        funcion_800435A0(dato_80183E40, (u16*) dato_80183E80, 0.02f, d_circuito_sherbet_land_bloque_hielo_dl, 0x000000FF);
    }
}

void funcion_80052E30(SIN_USO s32 parametro0) {
    s32 variable_s0;

    dato_800E4620.l[0].l.dir[0] = dato_80165840[0];
    dato_800E4620.l[0].l.dir[1] = dato_80165840[1];
    dato_800E4620.l[0].l.dir[2] = dato_80165840[2];
    gSPLight(display_list_cabeza++, &dato_800E4620.l[0], LIGHT_1);
    gSPLight(display_list_cabeza++, &dato_800E4620.a, LIGHT_2);
    dato_80183E80[0] = 0;
    dato_80183E80[1] = 0;
    dato_80183E80[2] = 0;
    if (cantidad_jugador == 1) {
        for (variable_s0 = 0; variable_s0 < seleccion_cantidad_jugador_1; variable_s0++) {
            funcion_80052D70(variable_s0);
        }
    }
}

void renderizar_lista_muniecos_nieve_objeto_2(s32 id_camara) {
    SIN_USO s32 margen_pila[2];
    Camara* sp44;
    s32 algun_indice;
    s32 indice_objeto;
    Objeto* objeto;

    sp44 = &camara1[id_camara];
    cargar_textura_y_tlut(d_circuito_frappe_snowland_tlut_nieve, d_circuito_frappe_snowland_nieve, 0x00000020, 0x00000020);
    for (algun_indice = 0; algun_indice < objeto_particula_2_tamanio; algun_indice++) {
        indice_objeto = particula_objeto_2[algun_indice];
        if (indice_objeto != ID_OBJETO_NULO) {
            objeto = &lista_objeto[indice_objeto];
            if (objeto->state > 0) {
                funcion_8008A364(indice_objeto, id_camara, 0x2AABU, 0x000001F4);
                if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
                    objeto->orientacion[1] = funcion_800418AC(objeto->pos[0], objeto->pos[2], sp44->pos);
                    rsp_conjunto_matriz_g_objeto_lista(indice_objeto);
                    gSPDisplayList(display_list_cabeza++, dato_0D0069E0);
                }
            }
        }
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void renderizar_lista_muniecos_nieve_objeto_1(s32 id_camara) {
    s32 variable_s4;
    s32 indice_objeto;
    Camara* camara;

    camara = &camara1[id_camara];
    for (variable_s4 = 0; variable_s4 < MUNIECOS_NIEVE_NUM; variable_s4++) {
        indice_objeto = lista_objeto_indice_1[variable_s4];
        if (lista_objeto[indice_objeto].state >= 2) {
            funcion_8008A364(indice_objeto, id_camara, 0x2AABU, 0x00000258);
            if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
                dato_80183E80[0] = (s16) lista_objeto[indice_objeto].orientacion[0];
                dato_80183E80[1] =
                    funcion_800418AC(lista_objeto[indice_objeto].pos[0], lista_objeto[indice_objeto].pos[2], camara->pos);
                dato_80183E80[2] = (u16) lista_objeto[indice_objeto].orientacion[2];
                if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000010) != 0) {
                    dibujar_2d_textura_en(lista_objeto[indice_objeto].pos, (u16*) dato_80183E80,
                                       lista_objeto[indice_objeto].escalado_tamanio, (u8*) lista_objeto[indice_objeto].t_lut_activo,
                                       lista_objeto[indice_objeto].textura_activo, lista_objeto[indice_objeto].vertice,
                                       0x00000040, 0x00000040, 0x00000040, 0x00000020);
                }
                indice_objeto = lista_objeto_indice_2[variable_s4];
                dato_80183E80[0] = (s16) lista_objeto[indice_objeto].orientacion[0];
                dato_80183E80[2] = (u16) lista_objeto[indice_objeto].orientacion[2];
                dibujar_2d_textura_en(lista_objeto[indice_objeto].pos, (u16*) dato_80183E80,
                                   lista_objeto[indice_objeto].escalado_tamanio, (u8*) lista_objeto[indice_objeto].t_lut_activo,
                                   lista_objeto[indice_objeto].textura_activo, lista_objeto[indice_objeto].vertice, 0x00000040,
                                   0x00000040, 0x00000040, 0x00000020);
            }
        }
    }
}

void renderizar_muniecos_nieve_objeto(s32 parametro0) {
    renderizar_lista_muniecos_nieve_objeto_1(parametro0);
    renderizar_lista_muniecos_nieve_objeto_2(parametro0);
}

void renderizar_lakitu(s32 id_camara) {
    SIN_USO s32 margen_pila;
    Camara* camara;
    f32 variable_f0;
    f32 variable_f2;
    s32 indice_objeto;
    Objeto* objeto;

    indice_objeto = indice_lakitu_lista[id_camara];
    camara = &camara1[id_camara];
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000010) != 0) {
        objeto = &lista_objeto[indice_objeto];
        objeto->orientacion[0] = 0;
        objeto->orientacion[1] = funcion_800418AC(objeto->pos[0], objeto->pos[2], camara->pos);
        objeto->orientacion[2] = 0x8000;
        if (funcion_80072354(indice_objeto, 2) != 0) {
            dibujar_2d_textura_en(objeto->pos, objeto->orientacion, objeto->escalado_tamanio, (u8*) objeto->t_lut_activo,
                               objeto->textura_activo, objeto->vertice, (s32) objeto->textura_ancho,
                               (s32) objeto->textura_altura, (s32) objeto->textura_ancho,
                               (s32) objeto->textura_altura / 2);
        } else {
            funcion_800485C4(objeto->pos, objeto->orientacion, objeto->escalado_tamanio, (s32) objeto->prim_alpha,
                          (u8*) objeto->t_lut_activo, objeto->textura_activo, objeto->vertice, (s32) objeto->textura_ancho,
                          (s32) objeto->textura_altura, (s32) objeto->textura_ancho, (s32) objeto->textura_altura / 2);
        }
        if (seleccion_modo_pantalla == MODO_PANTALLA_1P) {
            variable_f0 = objeto->pos[0] - dato_8018CF14->pos[0];
            variable_f2 = objeto->pos[2] - dato_8018CF14->pos[2];
            if (variable_f0 < 0.0f) {
                variable_f0 = -variable_f0;
            }
            if (variable_f2 < 0.0f) {
                variable_f2 = -variable_f2;
            }
            if ((variable_f0 + variable_f2) <= 200.0) {
                funcion_8004A630(&dato_8018C0B0[id_camara], objeto->pos, 0.35f);
            }
        }
    }
}

void funcion_800534A4(SIN_USO s32 parametro0) {
    funcion_800419F8();
    dato_800E4638.l[0].l.dir[0] = dato_80165840[0];
    dato_800E4638.l[0].l.dir[1] = dato_80165840[1];
    dato_800E4638.l[0].l.dir[2] = dato_80165840[2];
}

void funcion_800534E8(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].type) {
        case 0:
            gSPLight(display_list_cabeza++, &dato_800E4638.l[0], LIGHT_1);
            gSPLight(display_list_cabeza++, &dato_800E4638.a, LIGHT_2);
            break;
        case 1:
            gSPLight(display_list_cabeza++, &dato_800E4650.l[0], LIGHT_1);
            gSPLight(display_list_cabeza++, &dato_800E4650.a, LIGHT_2);
            break;
        case 2:
            gSPLight(display_list_cabeza++, &dato_800E4668.l[0], LIGHT_1);
            gSPLight(display_list_cabeza++, &dato_800E4668.a, LIGHT_2);
            break;
        case 3:
            gSPLight(display_list_cabeza++, &dato_800E4680.l[0], LIGHT_1);
            gSPLight(display_list_cabeza++, &dato_800E4680.a, LIGHT_2);
            break;
        case 4:
            gSPLight(display_list_cabeza++, &dato_800E4698.l[0], LIGHT_1);
            gSPLight(display_list_cabeza++, &dato_800E4698.a, LIGHT_2);
            break;
        default:
            break;
    }
}
