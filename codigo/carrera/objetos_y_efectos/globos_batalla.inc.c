// Globos batalla

void renderizar_globo_batalla(Jugador* jugador, s8 indice_jugador, s16 indice_globo, s8 id_pantalla) {
    Mat4 sp140;
    Vec3f sp134;
    Vec3s sp12_c;
    SIN_USO s16 margen_pila;
    s16 prim_rojo;
    s16 verde_prim;
    s16 azul_prim;
    s16 amb_rojo;
    s16 verde_amb;
    s16 azul_amb;
    s16 temporal_t1;
    f32 xdiff;
    f32 zdiff;
    f32 variable_f20;
    s32 colores_prim[] = {
        HACER_RGB(0xC8, 0x01, 0x00), HACER_RGB(0x00, 0x70, 0x01), HACER_RGB(0x10, 0x79, 0x51), HACER_RGB(0x00, 0x59, 0x70),
        HACER_RGB(0x70, 0x55, 0x00), HACER_RGB(0x7A, 0x7E, 0x00), HACER_RGB(0x77, 0x2C, 0x24), HACER_RGB(0x30, 0x14, 0x58),
    };
    s32 colores_amb[] = {
        HACER_RGB(0xDC, 0x00, 0x00), HACER_RGB(0x00, 0x8C, 0x06), HACER_RGB(0x00, 0x00, 0x51), HACER_RGB(0x00, 0x00, 0x00),
        HACER_RGB(0x00, 0x00, 0x00), HACER_RGB(0x00, 0x00, 0x00), HACER_RGB(0x00, 0x00, 0x00), HACER_RGB(0x00, 0x00, 0x00),
    };

    prim_rojo = (colores_prim[jugador->id_personaje] >> 0x10) & 0xFF;
    verde_prim = (colores_prim[jugador->id_personaje] >> 0x08) & 0xFF;
    azul_prim = (colores_prim[jugador->id_personaje] >> 0x00) & 0xFF;
    amb_rojo = (colores_amb[jugador->id_personaje] >> 0x10) & 0xFF;
    verde_amb = (colores_amb[jugador->id_personaje] >> 0x08) & 0xFF;
    azul_amb = (colores_amb[jugador->id_personaje] >> 0x00) & 0xFF;
    temporal_t1 = (((jugador->desconocido_048[id_pantalla] + jugador->rotacion[1] + jugador->desconocido_0C0) & 0xFFFF) / 128);
    temporal_t1 <<= 7;
    if (id_pantalla == indice_jugador) {
        variable_f20 = 0.3f;
    } else {
        xdiff = (variable_f20 = jugador->pos[0] - camaras[id_pantalla].pos[0]);
        zdiff = jugador->pos[2] - camaras[id_pantalla].pos[2];
        if (modo_pantalla_activo != 3) {
            variable_f20 = sqrtf((xdiff * xdiff) + (zdiff * zdiff)) / 300.0f;
        } else {
            variable_f20 = sqrtf((xdiff * xdiff) + (zdiff * zdiff)) / 200.0f;
        }
        if (variable_f20 >= 1.8) {
            variable_f20 = 1.8f;
        }
        if (variable_f20 <= 0.3) {
            variable_f20 = 0.3f;
        }
    }
    sp134[0] = pos_x_globo_jugador[indice_jugador][indice_globo];
    sp134[1] = pos_y_globo_jugador[indice_jugador][indice_globo];
    sp134[2] = pos_z_globo_jugador[indice_jugador][indice_globo];
    sp12_c[0] = -((dato_8018D890[indice_jugador][indice_globo] * 4) * coss(temporal_t1));
    sp12_c[1] = jugador->desconocido_048[id_pantalla];
    sp12_c[2] = dato_8018D7D0[indice_jugador][indice_globo] -
               (rotacion_globo_jugador[indice_jugador][indice_globo] * coss(temporal_t1)) -
               ((dato_8018D890[indice_jugador][indice_globo] * 8) * senos(temporal_t1));
    trasladar_rotacion_mtxf(sp140, sp134, sp12_c);
    escala2_mtxf(sp140, variable_f20);
    convertir_a_matriz_punto_fijo(&gfx_pool->efecto_mtx[cantidad_efecto_matriz], sp140);

    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
    gDPLoadTLUT_pal256(display_list_cabeza++, dato_800E52D0);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);

    funcion_8004B614(prim_rojo, verde_prim, azul_prim, amb_rojo, verde_amb, azul_amb, 0x000000D8);

    gDPSetRenderMode(display_list_cabeza++,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                         GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    gDPLoadTextureBlock(display_list_cabeza++, dato_8018D4BC, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, plano_vertice_globo_1, 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gDPLoadTextureBlock(display_list_cabeza++, dato_8018D4C0 - 0x40, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, plano_vertice_globo_2, 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gSPTexture(display_list_cabeza++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
    cantidad_efecto_matriz++;
}

void inicializar_todos_globos_jugador(Jugador* jugador, s8 indice_jugador) {
    inicializar_globo(jugador, 0.0f, 0.0f, indice_jugador, (s8) 0, (s16) 0);
    inicializar_globo(jugador, 1.5f, 2.0f, indice_jugador, (s8) 1, (s16) 0x1C70);
    inicializar_globo(jugador, -1.5f, 2.0f, indice_jugador, (s8) 2, (s16) -0x1C70);
    cantidad_globo_jugador[indice_jugador] = 2;
}

void borrar_todos_globos_jugador(SIN_USO Jugador* jugador, s8 indice_jugador) {
    situacion_globo_jugador[indice_jugador][0] = IDO_SITUACION_GLOBO;
    situacion_globo_jugador[indice_jugador][1] = IDO_SITUACION_GLOBO;
    situacion_globo_jugador[indice_jugador][2] = IDO_SITUACION_GLOBO;
}

void sacar_globo_jugador(Jugador* jugador, s8 indice_jugador) {
    if (cantidad_globo_jugador[indice_jugador] >= 0) {
        situacion_globo_jugador[indice_jugador][cantidad_globo_jugador[indice_jugador]] &= ~PRESENTE_SITUACION_GLOBO;
        situacion_globo_jugador[indice_jugador][cantidad_globo_jugador[indice_jugador]] |= PARTIENDO_SITUACION_GLOBO;
        cantidad_globo_jugador[indice_jugador]--;
        funcion_800C9060(indice_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x90, 0x51));
        if (cantidad_globo_jugador[indice_jugador] < 0) {
            funcion_8008FD4C(jugador, indice_jugador);
        }
    }
}

void fijar_globo_jugador_a_ido(SIN_USO s32 parametro0, s8 indice_jugador, s8 indice_globo) {
    if (cantidad_globo_jugador[indice_jugador] >= 0) {
        situacion_globo_jugador[indice_jugador][indice_globo] = IDO_SITUACION_GLOBO;
    }
}

void actualizar_posicion_globos_jugador(Jugador* jugador, s8 id_jugador) {
    if (situacion_globo_jugador[id_jugador][0] != IDO_SITUACION_GLOBO) {
        actualizar_posicion_globo_jugador_uno(jugador, 0.0f, 0.0f, id_jugador, 0);
    }

    if (situacion_globo_jugador[id_jugador][1] != IDO_SITUACION_GLOBO) {
        actualizar_posicion_globo_jugador_uno(jugador, 1.8f, 2.6f, id_jugador, 1);
    }

    if (situacion_globo_jugador[id_jugador][2] != IDO_SITUACION_GLOBO) {
        actualizar_posicion_globo_jugador_uno(jugador, -1.8f, 2.6f, id_jugador, 2);
    }
}

void renderizar_globos_batalla_restante(Jugador* jugador, s8 indice_jugador, s8 id_pantalla) {
    if (situacion_globo_jugador[indice_jugador][0] != IDO_SITUACION_GLOBO) {
        renderizar_globo_batalla(jugador, indice_jugador, 0, id_pantalla);
    }
    if (situacion_globo_jugador[indice_jugador][1] != IDO_SITUACION_GLOBO) {
        renderizar_globo_batalla(jugador, indice_jugador, 1, id_pantalla);
    }
    if (situacion_globo_jugador[indice_jugador][2] != IDO_SITUACION_GLOBO) {
        renderizar_globo_batalla(jugador, indice_jugador, 2, id_pantalla);
    }
}

void renderizar_globo(Vec3f parametro0, f32 parametro1, s16 parametro2, s16 parametro3) {
    Mat4 sp108;
    Vec3f sp_fc;
    Vec3s sp_f4;
    SIN_USO s16 margen_pila;
    s16 prim_rojo;
    s16 verde_prim;
    s16 azul_prim;
    s16 amb_rojo;
    s16 verde_amb;
    s16 azul_amb;
    s32 colores_prim[] = {
        HACER_RGB(0xC8, 0x01, 0x00), HACER_RGB(0x00, 0x70, 0x01), HACER_RGB(0x10, 0x79, 0x51), HACER_RGB(0x00, 0x59, 0x70),
        HACER_RGB(0x70, 0x55, 0x00), HACER_RGB(0x7A, 0x7E, 0x00), HACER_RGB(0x77, 0x2C, 0x24), HACER_RGB(0x30, 0x14, 0x58),
    };
    s32 colores_amb[] = {
        HACER_RGB(0xDC, 0x00, 0x00), HACER_RGB(0x00, 0x8C, 0x06), HACER_RGB(0x00, 0x00, 0x51), HACER_RGB(0x00, 0x00, 0x00),
        HACER_RGB(0x00, 0x00, 0x00), HACER_RGB(0x00, 0x00, 0x00), HACER_RGB(0x00, 0x00, 0x00), HACER_RGB(0x00, 0x00, 0x00),
    };

    prim_rojo = (colores_prim[parametro3] >> 0x10) & 0xFF;
    verde_prim = (colores_prim[parametro3] >> 0x08) & 0xFF;
    azul_prim = (colores_prim[parametro3] >> 0x00) & 0xFF;
    amb_rojo = (colores_amb[parametro3] >> 0x10) & 0xFF;
    verde_amb = (colores_amb[parametro3] >> 0x08) & 0xFF;
    azul_amb = (colores_amb[parametro3] >> 0x00) & 0xFF;
    sp_fc[0] = parametro0[0];
    sp_fc[1] = parametro0[1];
    sp_fc[2] = parametro0[2];
    sp_f4[0] = 0;
    sp_f4[1] = camara1->rot[1];
    sp_f4[2] = parametro2;
    trasladar_rotacion_mtxf(sp108, sp_fc, sp_f4);
    escala2_mtxf(sp108, parametro1);
    convertir_a_matriz_punto_fijo(&gfx_pool->efecto_mtx[cantidad_efecto_matriz], sp108);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
    gDPLoadTLUT_pal256(display_list_cabeza++, dato_800E52D0);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_RGBA16);
    funcion_8004B614(prim_rojo, verde_prim, azul_prim, amb_rojo, verde_amb, azul_amb, 0x000000D8);
    gDPSetRenderMode(display_list_cabeza++,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                         GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    gDPLoadTextureBlock(display_list_cabeza++, dato_8018D4BC, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, plano_vertice_globo_1, 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gDPLoadTextureBlock(display_list_cabeza++, dato_8018D4C0 - 0x40, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPVertex(display_list_cabeza++, plano_vertice_globo_2, 4, 0);
    gSPDisplayList(display_list_cabeza++, renderizar_simple_cuadrado_comun);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
    cantidad_efecto_matriz += 1;
}

void funcion_8006C0C8(Vec3f parametro0, f32 parametro1, s32 rgb, s16 alpha) {
    Vec3f sp4_c;
    Vec3s sp44;
    s16 rojo;
    s16 verde;
    s16 azul;

    sp4_c[0] = parametro0[0];
    sp4_c[1] = parametro0[1];
    sp4_c[2] = parametro0[2];
    sp44[0] = 0;
    sp44[1] = camara1->rot[1];
    sp44[2] = 0;
    funcion_800652D4(sp4_c, sp44, parametro1);
    gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
    gDPLoadTextureBlock(display_list_cabeza++, dato_8018D48C, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    rojo = ((rgb >> 0x10) & 0xFF) & 0xFF;
    verde = ((rgb >> 0x08) & 0xFF) & 0xFF;
    azul = ((rgb >> 0x00) & 0xFF) & 0xFF;
    funcion_8004B35C(rojo, verde, azul, alpha);
    gSPDisplayList(display_list_cabeza++, dato_0D008E48);
    cantidad_efecto_matriz += 1;
}

void funcion_8006C294(Vec3f parametro0, f32 parametro1, s32 rgb, s16 alpha) {
    Vec3f sp5_c;
    Vec3s sp54;
    s16 rojo = ((rgb >> 0x10) & 0xFF) & 0xFF;
    s16 verde = ((rgb >> 0x08) & 0xFF) & 0xFF;
    s16 azul = ((rgb >> 0x00) & 0xFF) & 0xFF;

    sp5_c[0] = parametro0[0];
    sp5_c[1] = parametro0[1];
    sp5_c[2] = parametro0[2];
    sp54[0] = 0;
    sp54[1] = camara1->rot[1];
    sp54[2] = 0;
    funcion_800652D4(sp5_c, sp54, parametro1);
    gSPDisplayList(display_list_cabeza++, dato_0D008D58);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
    gDPLoadTextureBlock(display_list_cabeza++, dato_8018D488, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    funcion_8004B35C(rojo, verde, azul, alpha);
    gDPSetRenderMode(display_list_cabeza++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
    gSPVertex(display_list_cabeza++, dato_800E87C0, 4, 0);
    gSPDisplayList(display_list_cabeza++, dato_0D008DA0);
    cantidad_efecto_matriz += 1;
}

void funcion_8006C4D4(Vec3f parametro0, f32 parametro1, s32 rgb, s16 alpha, s16 parametro4) {
    Vec3f sp4_c;
    Vec3s sp44;
    s16 rojo = ((rgb >> 0x10) & 0xFF) & 0xFF;
    s16 verde = ((rgb >> 0x08) & 0xFF) & 0xFF;
    s16 azul = ((rgb >> 0x00) & 0xFF) & 0xFF;

    sp4_c[0] = parametro0[0];
    sp4_c[1] = parametro0[1];
    sp4_c[2] = parametro0[2];
    sp44[0] = 0;
    sp44[1] = camara1->rot[1];
    sp44[2] = 0;
    funcion_800652D4(sp4_c, sp44, parametro1);
    gSPDisplayList(display_list_cabeza++, dato_0D008DB8);
    gDPLoadTextureBlock(display_list_cabeza++, comun_textura_particula_chispa[parametro4], G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    funcion_8004B414(rojo, verde, azul, alpha);
    gSPDisplayList(display_list_cabeza++, dato_0D008E48);
    cantidad_efecto_matriz += 1;
}

void funcion_8006C6AC(Jugador* jugador, s16 indice_particula, s8 id_jugador, s8 parametro3) {
    s8 copia_id_jugador = id_jugador;
    s32 sp28;

    sp28 = indice_particula - 1;
    if (sp28 < 0) {
        sp28 = 9;
    }
    if (jugador->pool_particula_1[indice_particula].vivo_es == 1) {
        switch (jugador->pool_particula_1[indice_particula].type) {
            case 1:
                funcion_80063408(jugador, indice_particula, copia_id_jugador, parametro3);
                break;
            case 2:
                funcion_800635D4(jugador, indice_particula, copia_id_jugador, parametro3);
                break;
            case 3:
                funcion_80063BD4(jugador, indice_particula, copia_id_jugador, parametro3);
                break;
            case 4:
                funcion_800643A8(jugador, indice_particula, copia_id_jugador, parametro3);
                break;
            case 5:
                funcion_800639DC(jugador, indice_particula, copia_id_jugador, parametro3);
                break;
            case 9:
                funcion_80063D58(jugador, indice_particula, copia_id_jugador, parametro3);
                break;
            case 11:
                funcion_80062F98(jugador, indice_particula, copia_id_jugador, parametro3);
                break;
            default:
                break;
        }
    } else {
        if (jugador->oob_props & BAJO_OOB_O_NIVEL_FLUIDO) {
            funcion_80060BCC(jugador, indice_particula, sp28, copia_id_jugador, parametro3);
        } else if (!(jugador->efectos & EFECTO_EN_EL_AIRE) && !(jugador->efectos & EFECTO_SALTO)) {
            if (((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) &&
                ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) {
                preparar_valido_particulas_derrape_comprobacion(jugador, indice_particula, sp28, copia_id_jugador, parametro3);
            } else if (((f64) (dato_801652A0[copia_id_jugador] - jugador->ruedas[DERECHA_ATRAS].altura_base) >= 3.5) ||
                       ((f64) (dato_801652A0[copia_id_jugador] - jugador->ruedas[IZQUIERDA_ATRAS].altura_base) >= 3.5)) {
                funcion_8005EA94(jugador, indice_particula, sp28, copia_id_jugador, parametro3);
            } else if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
                       ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO)) {
                funcion_8005F90C(jugador, indice_particula, sp28, copia_id_jugador, parametro3);
            } else if (((jugador->efectos & TEMPRANO_INICIO_TROMPO_EFECTO) && !(jugador->type & SECUENCIA_INICIO_JUGADOR)) ||
                       (jugador->efectos & BANANA_CERCA_EFECTO_TROMPO) || (jugador->efectos & EFECTO_GIRO_AB) ||
                       (jugador->kart_props & CONDUCIENDO_CERCA_TROMPO)) {
                funcion_8005ED48(jugador, indice_particula, sp28, copia_id_jugador, parametro3);
            } else {
                preparar_particulas_rueda(jugador, indice_particula, sp28, copia_id_jugador, parametro3);
            }
        }
    }
}

void funcion_8006C9B8(Jugador* jugador, s16 parametro1, s8 indice_jugador, s8 parametro3) {
    SIN_USO s32 margen_pila;
    s32 sp28;
    sp28 = parametro1 - 1;
    if (sp28 < 0) {
        sp28 = 9;
    }
    if (jugador->pool_particula_3[parametro1].vivo_es == 1) {
        switch (jugador->pool_particula_3[parametro1].type) {
            case 1:
                funcion_800644E8(jugador, parametro1, indice_jugador, parametro3);
                break;

            case 2:
                funcion_800649F4(jugador, parametro1, indice_jugador, parametro3);
                break;

            case 3:
                funcion_80064C74(jugador, parametro1, indice_jugador, parametro3);
                break;

            case 4:
                funcion_800647C8(jugador, parametro1, indice_jugador, parametro3);
                break;

            case 5:
                funcion_80064B30(jugador, parametro1, indice_jugador, parametro3);
                break;

            case 6:
                funcion_800648E4(jugador, parametro1, indice_jugador, parametro3);
                break;

            case 7:
                funcion_80064988(jugador, parametro1, indice_jugador, parametro3);
                break;

            case 8:
                funcion_80064C74(jugador, parametro1, indice_jugador, parametro3);
                break;

            case 9:
                funcion_80064664(jugador, parametro1, indice_jugador, parametro3);
                break;

            default:
                break;
        }
    } else {
        if (jugador->kart_props & sin_uso_0_x_1000) {
            funcion_80061430(jugador, parametro1, sp28, indice_jugador, parametro3);
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            return;
        }
        if (((((jugador->lakitu_props & LAKITU_LAVA) == LAKITU_LAVA) ||
              ((jugador->desconocido_0E0 < 2) && (jugador->efectos & EFECTO_ERROR_EXPLOSION))) ||
             ((jugador->desconocido_0E0 < 2) && (jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA))) ||
            (jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO)) {
            funcion_8006199C(jugador, parametro1, sp28, indice_jugador, parametro3);
            jugador->desconocido_046 &= ~0x0008;
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            return;
        }
        if ((jugador->lakitu_props & LAKITU_AGUA) == LAKITU_AGUA) {
            funcion_80061A34(jugador, parametro1, sp28, indice_jugador, parametro3);
            jugador->desconocido_046 &= ~0x0008;
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            return;
        }
        if ((jugador->efectos & EFECTO_ESTRELLA) &&
            ((((s32) temporizador_circuito) - jugador_estrella_efecto_inicio_tiempo[indice_jugador]) < DURACION_EFECTO_ESTRELLA - 1)) {
            funcion_800615AC(jugador, parametro1, sp28, indice_jugador, parametro3);
            jugador->desconocido_046 &= ~0x0008;
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            return;
        }
        if ((jugador->desconocido_046 & 8) == 8) {
            funcion_800612F8(jugador, parametro1, sp28, indice_jugador, parametro3);
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            return;
        }
        if (((jugador->desconocido_046 & 0x20) == 0x20) && (((jugador->speed / 18.0f) * 216.0f) >= 20.0f)) {
            funcion_80061D4C(jugador, parametro1, sp28, indice_jugador, parametro3);
            jugador->desconocido_046 &= ~0x0008;
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            return;
        }
        if ((jugador->efectos & EFECTO_HONGO) && (jugador->type & HUMANO_JUGADOR)) {
            funcion_800621BC(jugador, parametro1, sp28, indice_jugador, parametro3);
            return;
        }
        if (((jugador->efectos & EFECTO_RAPIDO_CPU) || (jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO)) &&
            ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) {
            funcion_80061EF4(jugador, parametro1, sp28, indice_jugador, parametro3);
            jugador->desconocido_046 &= ~0x0008;
            jugador->kart_props &= ~ACELERADOR_VUELCO_PUBLICAR;
            return;
        }
        if ((jugador->kart_props & ACELERADOR_VUELCO_PUBLICAR) == ACELERADOR_VUELCO_PUBLICAR) {
            funcion_800624D8(jugador, parametro1, sp28, indice_jugador, parametro3);
            jugador->desconocido_046 &= ~0x0008;
        }
    }
}

void funcion_8006CEC0(Jugador* parametro0, s16 parametro1, s8 id_jugador, s8 parametro3) {
    SIN_USO u16 temporal_v0_3;
    s32 sp20 = parametro1;
    if (--sp20 < 0) {
        sp20 = 9;
    }
    if (parametro0->pool_particula_0[parametro1].vivo_es == 1) {
        switch (parametro0->pool_particula_0[parametro1].type) {
            case 1:
                funcion_80062C74(parametro0, parametro1, id_jugador, parametro3);
                break;
            case 3:
                funcion_80064184(parametro0, parametro1, id_jugador, parametro3);
                break;
            case 5:
                fijar_oob_salpicadura_particula_posicion(parametro0, parametro1, id_jugador, parametro3);
                break;
            case 6:
                funcion_800631A8(parametro0, parametro1, id_jugador, parametro3);
                break;
            case 7:
                funcion_80063268(parametro0, parametro1, id_jugador, parametro3);
                break;
        }
    } else {
        if ((parametro0->kart_props & INVISIBLE_VOLVERSE) && (parametro0->type & CONDUCIENDO_CERCA_TROMPO)) {
            funcion_80061224(parametro0, parametro1, sp20, id_jugador, parametro3);
            return;
        } else if (((parametro0->efectos & EFECTO_RAYO) == EFECTO_RAYO) && (parametro0->desconocido_0B0 < 0x32)) {
            funcion_80061094(parametro0, parametro1, sp20, id_jugador, parametro3);
            return;
        } else if ((parametro0->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
            if ((parametro0->oob_props & BAJO_NIVEL_OOB) == BAJO_NIVEL_OOB) {
                funcion_80060F50(parametro0, parametro1, sp20, id_jugador, parametro3);
                return;
            } else if ((parametro0->oob_props & OOB_PASADA_O_NIVEL_FLUIDO) || (parametro0->oob_props & BAJO_OOB_O_NIVEL_FLUIDO)) {
                funcion_80060B14(parametro0, parametro1, sp20, id_jugador, parametro3);
                return;
            }
        }
        switch (modo_pantalla_activo) {
            case MODO_PANTALLA_1P:
                if (((parametro0->efectos & EFECTO_APLASTAMIENTO) != EFECTO_APLASTAMIENTO) &&
                    ((parametro0->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) != GOLPE_POR_CAPARAZON_VERDE_EFECTO) &&
                    ((parametro0->efectos & EFECTO_ERROR_EXPLOSION) != EFECTO_ERROR_EXPLOSION)) {
                    if (((parametro0->lakitu_props & MANTENIDO_POR_LAKITU) != MANTENIDO_POR_LAKITU) &&
                        ((parametro0->lakitu_props & EFECTO_HELADO) != EFECTO_HELADO) &&
                        !(parametro0->lakitu_props & WENT_SOBRE_OOB)) {
                        funcion_80060504(parametro0, parametro1, sp20, id_jugador, parametro3);
                    }
                }
                break;
            default:
                break;
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                if (((parametro0->type & HUMANO_JUGADOR) != 0) && ((parametro0->efectos & EFECTO_APLASTAMIENTO) != EFECTO_APLASTAMIENTO) &&
                    ((parametro0->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) != GOLPE_POR_CAPARAZON_VERDE_EFECTO) &&
                    ((parametro0->efectos & EFECTO_ERROR_EXPLOSION) != EFECTO_ERROR_EXPLOSION)) {
                    if (((parametro0->lakitu_props & MANTENIDO_POR_LAKITU) != MANTENIDO_POR_LAKITU) &&
                        ((parametro0->lakitu_props & EFECTO_HELADO) != EFECTO_HELADO) &&
                        !(parametro0->lakitu_props & WENT_SOBRE_OOB)) {
                        funcion_80060504(parametro0, parametro1, sp20, id_jugador, parametro3);
                    }
                }
            break;
        }
    }
}

void funcion_8006D194(Jugador* jugador, s8 indice_jugador, s8 parametro2) {
    if (jugador->pool_particula_2[0].vivo_es == 1) {
        switch (jugador->pool_particula_2[0].type) {
            case 2:
                funcion_80064DEC(jugador, indice_jugador, parametro2, 0);
                break;
            case 3:
                funcion_800650FC(jugador, indice_jugador, parametro2, 0);
                break;
            case 4:
                funcion_80064EA4(jugador, indice_jugador, parametro2, 0);
                break;
            case 5:
                funcion_80064F88(jugador, indice_jugador, parametro2, 0);
                break;
            case 6:
                funcion_80065030(jugador, indice_jugador, parametro2, 0);
                break;
        }
    } else {
        if ((jugador->graficos_kart & ERROR_) == ERROR_) {
            funcion_800628C0(jugador, indice_jugador, parametro2, 0);
        }
        if ((jugador->graficos_kart & BOING) == BOING) {
            funcion_80062968(jugador, indice_jugador, parametro2, 0);
        }
        if ((jugador->graficos_kart & EXPLOSION) == EXPLOSION) {
            funcion_80062914(jugador, indice_jugador, parametro2, 0);
        }
        if ((jugador->graficos_kart & WHIRRR) == WHIRRR) {
            funcion_80062A18(jugador, indice_jugador, parametro2, 0);
        }
        if ((jugador->graficos_kart & POOMP) == POOMP) {
            funcion_800629BC(jugador, indice_jugador, parametro2, 0);
        }
    }
    if (jugador->pool_particula_2[1].vivo_es == 1) {
        if (jugador->pool_particula_2[1].type == 5) {
            funcion_800651F4(jugador, indice_jugador, parametro2, 1);
        }
    } else if ((jugador->graficos_kart & SILBATO) == SILBATO) {
        funcion_80062AA8(jugador, indice_jugador, parametro2, 1);
    }
}

void funcion_8006D474(Jugador* jugador, s8 id_jugador, s8 id_pantalla) {
    s16 variable_s2;
    if ((jugador->desconocido_002 & (LADO_DE_KART << (id_pantalla * 4))) == (LADO_DE_KART << (id_pantalla * 4))) {
        for (variable_s2 = 0; variable_s2 < 10; variable_s2++) {
            switch (jugador->pool_particula_0[variable_s2].type) {
                case 1:
                    if (modo_pantalla_activo == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
                        if (id_pantalla == id_jugador) {
                            funcion_8006538C(jugador, id_jugador, variable_s2, id_pantalla);
                        }
                    } else {
                        funcion_8006538C(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
                case 6:
                    if (modo_pantalla_activo == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
                        if (id_pantalla == id_jugador) {
                            funcion_80066BAC(jugador, id_jugador, variable_s2, id_pantalla);
                        }
                    } else if (id_pantalla == id_jugador) {
                        funcion_80066BAC(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
            }
            switch (jugador->pool_particula_3[variable_s2].type) {
                case 1:
                case 9:
                    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
                        renderizar_particulas_golpe_actor(jugador, id_jugador, variable_s2, id_pantalla);
                    } else if (id_pantalla == id_jugador) {
                        renderizar_particulas_golpe_actor(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
                case 2:
                    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
                        renderizar_pared_golpe_estrella_particulas(jugador, id_jugador, variable_s2, id_pantalla, jugador->pool_particula_3[variable_s2].scale);
                    } else if (id_pantalla == id_jugador) {
                        renderizar_pared_golpe_estrella_particulas(jugador, id_jugador, variable_s2, id_pantalla, jugador->pool_particula_3[variable_s2].scale);
                    }
                    break;
                case 3:
                    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
                        funcion_80067280(jugador, id_jugador, variable_s2, id_pantalla);
                    } else if (id_pantalla == id_jugador) {
                        funcion_80067280(jugador, (s32) id_jugador, variable_s2, id_pantalla);
                    }
                    break;
                case 4:
                    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
                        funcion_80069444(jugador, id_jugador, variable_s2, id_pantalla);
                    } else if (id_pantalla == id_jugador) {
                        funcion_80069444(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
                case 5:
                    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
                        funcion_80069938(jugador, id_jugador, variable_s2, id_pantalla);
                    } else if (id_pantalla == id_jugador) {
                        funcion_80069938(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
                case 6:
                    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
                        funcion_80069BA8(jugador, id_jugador, variable_s2, id_pantalla);
                    } else if (id_pantalla == id_jugador) {
                        funcion_80069BA8(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
                case 7:
                    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
                        funcion_80069DB8(jugador, id_jugador, variable_s2, id_pantalla);
                    } else if (id_pantalla == id_jugador) {
                        funcion_80069DB8(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
                case 8:
                    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
                        renderizar_jugador_impulso_chispa_particulas(jugador, id_jugador, variable_s2, id_pantalla);
                    } else if (id_pantalla == id_jugador) {
                        renderizar_jugador_impulso_chispa_particulas(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
            }
            switch (jugador->pool_particula_1[variable_s2].type) {
                case PARTICULA_DERRAPE:
                    if (modo_pantalla_activo == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
                        if (id_pantalla == id_jugador) {
                            renderizar_particulas_derrape_jugador(jugador, id_jugador, variable_s2, id_pantalla);
                        }
                    } else {
                        renderizar_particulas_derrape_jugador(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
                case PARTICULA_SUELO:
                case PARTICULA_PASTO:
                case 4:
                case 5:
                    if (modo_pantalla_activo == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
                        if (id_pantalla == id_jugador) {
                            renderizar_particulas_suelo_jugador(jugador, id_jugador, variable_s2, id_pantalla);
                        }
                    } else {
                        renderizar_particulas_suelo_jugador(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
                case 9:
                    if (modo_pantalla_activo == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
                        if (id_pantalla == id_jugador) {
                            funcion_800664E0(jugador, (s32) id_jugador, variable_s2, id_pantalla);
                        }
                    } else {
                        funcion_800664E0(jugador, (s32) id_jugador, variable_s2, id_pantalla);
                    }
                    break;
                case 11:
                    if (modo_pantalla_activo == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
                        if (id_pantalla == id_jugador) {
                            funcion_8006A01C(jugador, id_jugador, variable_s2, id_pantalla);
                        }
                    } else if (id_pantalla == id_jugador) {
                        funcion_8006A01C(jugador, id_jugador, variable_s2, id_pantalla);
                    }
                    break;
            }
        }
    }
    if ((seleccion_modo == BATALLA) && (jugador->desconocido_002 & (desconocido_002_desconocido_0_x2 << (id_pantalla * 4)))) {
        renderizar_globos_batalla_restante(jugador, id_jugador, id_pantalla);
    }
}

void funcion_8006DC54(Jugador* jugador, s8 indice_jugador, s8 id_pantalla) {
    s16 i;
    s32 mascara_bit_a_bit;

    mascara_bit_a_bit = LADO_DE_KART << (id_pantalla * 4);
    if (mascara_bit_a_bit == (jugador->desconocido_002 & mascara_bit_a_bit)) {
        for (i = 0; i < 10; i++) {
            if (jugador->pool_particula_0[i].type == 7) {
                funcion_800658A0(jugador, indice_jugador, i, id_pantalla);
            }
        }
    }
}

void funcion_8006DD3C(Jugador* parametro0, s8 parametro1, s8 parametro2) {
    s16 temporal_s0;
    s32 temporal_v0;

    temporal_v0 = LADO_DE_KART << (parametro2 * 4);
    if (temporal_v0 == (parametro0->desconocido_002 & temporal_v0)) {
        for (temporal_s0 = 0; temporal_s0 < 10; ++temporal_s0) {
            temporal_v0 = parametro0->pool_particula_0[temporal_s0].type;
            if (temporal_v0 != 3) {
                if (temporal_v0 == 5) {
                    funcion_8006A280(parametro0, parametro1, temporal_s0, parametro2);
                }
            } else if (modo_pantalla_activo == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
                if (parametro2 == parametro1) {
                    funcion_80066998(parametro0, parametro1, temporal_s0, parametro2);
                }
            } else {
                funcion_80066998(parametro0, parametro1, temporal_s0, parametro2);
            }
        }

        if (((parametro0->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) && (parametro2 == parametro1)) {
            switch (parametro0->pool_particula_2[0].type) {
                case 2:
                    renderizar_error_onomatopeya_jugador(parametro0, parametro1, parametro0->pool_particula_2[0].scale, parametro2, 0);
                    break;
                case 3:
                    renderizar_whrrrr_onomatopeya_jugador(parametro0, parametro1, parametro0->pool_particula_2[0].scale, parametro2, 0);
                    break;
                case 4:
                    funcion_80068724(parametro0, parametro1, parametro0->pool_particula_2[0].scale, parametro2, 0);
                    break;
                case 5:
                    renderizar_boing_onomatopeya_jugador(parametro0, parametro1, parametro0->pool_particula_2[0].scale, parametro2, 0);
                    break;
                case 6:
                    renderizar_pomp_onomatopeya_jugador(parametro0, parametro1, parametro0->pool_particula_2[0].scale, parametro2, 0);
                    break;
            }
            if (parametro0->pool_particula_2[1].type == 5) {
                renderizar_burbuja_voz_jugador(parametro0, parametro2, dato_8018D480, 1, 1.6f, 0xFFFFFF);
                renderizar_nota_musica(parametro0, parametro2, dato_8018D484, 1, 1.6f, 0xFF);
            }
        }
    }
}

void funcion_8006E058(void) {
    switch (modo_pantalla_activo) {
        case MODO_PANTALLA_1P:
            switch (seleccion_modo) {
                case GRAN_PREMIO:
                    funcion_8006E420(jugador_uno, JUGADOR_UNO, 0);
                    funcion_8006E420(jugador_dos, JUGADOR_DOS, 0);
                    funcion_8006E420(jugador_tres, JUGADOR_TRES, 0);
                    funcion_8006E420(jugador_cuatro, JUGADOR_CUATRO, 0);
                    funcion_8006E420(jugador_cinco, JUGADOR_CINCO, 0);
                    funcion_8006E420(jugador_seis, JUGADOR_SEIS, 0);
                    funcion_8006E420(jugador_siete, JUGADOR_SIETE, 0);
                    funcion_8006E420(jugador_ocho, JUGADOR_OCHO, 0);

                    break;
                case CONTRARRELOJ:
                    funcion_8006E420(jugador_uno, JUGADOR_UNO, 0);

                    if ((jugador_dos->type & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) {
                        funcion_8006E420(jugador_dos, JUGADOR_DOS, 0);
                    }

                    if ((jugador_tres->type & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) {
                        funcion_8006E420(jugador_tres, JUGADOR_TRES, 0);
                        break;
                    }

                    break;
                case VERSUS:
                case BATALLA:
                    funcion_8006E420(jugador_uno, JUGADOR_UNO, 0);
                    funcion_8006E420(jugador_dos, JUGADOR_DOS, 0);

                    if (seleccion_cantidad_jugador_1 >= 3) {
                        funcion_8006E420(jugador_tres, JUGADOR_TRES, 0);
                    }

                    if (seleccion_cantidad_jugador_1 == 4) {
                        funcion_8006E420(jugador_cuatro, JUGADOR_CUATRO, 0);
                        break;
                    }

                    break;
            }

            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            switch (seleccion_modo) {
                case GRAN_PREMIO:
                    funcion_8006E420(jugador_uno, JUGADOR_UNO, 0);
                    funcion_8006E420(jugador_dos, JUGADOR_DOS, 0);
                    funcion_8006E420(jugador_tres, JUGADOR_TRES, 0);
                    funcion_8006E420(jugador_cuatro, JUGADOR_CUATRO, 0);
                    funcion_8006E420(jugador_cinco, JUGADOR_CINCO, 0);
                    funcion_8006E420(jugador_seis, JUGADOR_SEIS, 0);
                    funcion_8006E420(jugador_siete, JUGADOR_SIETE, 0);
                    funcion_8006E420(jugador_ocho, JUGADOR_OCHO, 0);

                    break;
                case VERSUS:
                case BATALLA:
                    funcion_8006E420(jugador_uno, JUGADOR_UNO, 0);
                    funcion_8006E420(jugador_dos, JUGADOR_DOS, 0);

                    break;
                case CONTRARRELOJ:
                    funcion_8006E420(jugador_uno, JUGADOR_UNO, 0);

                    if ((jugador_dos->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
                        funcion_8006E420(jugador_dos, JUGADOR_DOS, 0);
                        break;
                    }

                    break;
            }

            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            if ((VERSUS == seleccion_modo) || (BATALLA == seleccion_modo)) {
                funcion_8006E420(jugador_uno, JUGADOR_UNO, 0);
                funcion_8006E420(jugador_dos, JUGADOR_DOS, 0);
                funcion_8006E420(jugador_tres, JUGADOR_TRES, 0);

                if (seleccion_cantidad_jugador_1 == 4) {
                    funcion_8006E420(jugador_cuatro, JUGADOR_CUATRO, 0);
                }
            }

            break;
    }
}

void funcion_8006E420(Jugador* jugador, s8 indice_jugador, s8 parametro2) {
    s16 temporal_s0;

    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        if ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) {
            funcion_8006D194(jugador, indice_jugador, parametro2);
        }

        for (temporal_s0 = 0; temporal_s0 < 10; ++temporal_s0) {
            funcion_8006CEC0(jugador, temporal_s0, indice_jugador, parametro2);
            if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) || (estado_juego == FINAL)) {
                funcion_8006C9B8(jugador, temporal_s0, indice_jugador, parametro2);
            }
            funcion_8006C6AC(jugador, temporal_s0, indice_jugador, parametro2);
        }

        if (seleccion_modo == BATALLA) {
            actualizar_posicion_globos_jugador(jugador, indice_jugador);
        }
    }
}

void renderizar_particula_kart_en_pantalla_uno(Jugador* jugador, s8 id_jugador, s8 id_pantalla) {
    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
            if (id_jugador == id_pantalla) {
                funcion_8006D474(jugador, id_jugador, id_pantalla);
            }
        } else {
            funcion_8006D474(jugador, id_jugador, id_pantalla);
        }
        funcion_8006DC54(jugador, id_jugador, id_pantalla);
    }
}

void renderizar_particula_kart_en_pantalla_dos(Jugador* jugador, s8 indice_jugador, s8 id_pantalla) {
    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
            if (indice_jugador == id_pantalla) {
                funcion_8006D474(jugador, indice_jugador, id_pantalla);
            }
        } else {
            funcion_8006D474(jugador, indice_jugador, id_pantalla);
        }
        funcion_8006DC54(jugador, indice_jugador, id_pantalla);
    }
}

void renderizar_particula_kart_en_pantalla_tres(Jugador* jugador, s8 indice_jugador, s8 id_pantalla) {
    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
            if (indice_jugador == id_pantalla) {
                funcion_8006D474(jugador, indice_jugador, id_pantalla);
            }
        } else {
            funcion_8006D474(jugador, indice_jugador, id_pantalla);
        }
        funcion_8006DC54(jugador, indice_jugador, id_pantalla);
    }
}

void renderizar_particula_kart_en_pantalla_cuatro(Jugador* jugador, s8 indice_jugador, s8 id_pantalla) {
    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
            if (indice_jugador == id_pantalla) {
                funcion_8006D474(jugador, indice_jugador, id_pantalla);
            }
        } else {
            funcion_8006D474(jugador, indice_jugador, id_pantalla);
        }
        funcion_8006DC54(jugador, indice_jugador, id_pantalla);
    }
}

void funcion_8006E7CC(Jugador* jugador, s8 parametro1, s8 parametro2) {
    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
            if (parametro1 == parametro2) {
                funcion_8006DD3C(jugador, parametro1, parametro2);
            }
        } else {
            funcion_8006DD3C(jugador, parametro1, parametro2);
        }
    }
}

void funcion_8006E848(Jugador* jugador, s8 parametro1, s8 parametro2) {
    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
            if (parametro1 == parametro2) {
                funcion_8006DD3C(jugador, parametro1, parametro2);
            }
        } else {
            funcion_8006DD3C(jugador, parametro1, parametro2);
        }
    }
}

void funcion_8006E8C4(Jugador* jugador, s8 parametro1, s8 parametro2) {
    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
            if (parametro1 == parametro2) {
                funcion_8006DD3C(jugador, parametro1, parametro2);
            }
        } else {
            funcion_8006DD3C(jugador, parametro1, parametro2);
        }
    }
}

void funcion_8006E940(Jugador* jugador, s8 parametro1, s8 parametro2) {
    if ((jugador->type & EXISTE_JUGADOR) == EXISTE_JUGADOR) {
        if ((jugador->efectos & BOO_EFECTO) == BOO_EFECTO) {
            if (parametro1 == parametro2) {
                funcion_8006DD3C(jugador, parametro1, parametro2);
            }
        } else {
            funcion_8006DD3C(jugador, parametro1, parametro2);
        }
    }
}

s32 algun_datos_sin_uso = 10;

#undef HACER_RGB
