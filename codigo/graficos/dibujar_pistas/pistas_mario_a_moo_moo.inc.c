// Pistas mario a moo moo

s16 dato_802B87B0 = 995;
s16 dato_802B87B4 = 1000;
SIN_USO s32 dato_802B87B8 = 0;
s32 dato_802B87BC = 0;
SIN_USO s32 dato_802B87C0 = 0;
s32 dato_802B87C4 = 0;
s32 dato_802B87C8 = 0;
s32 dato_802B87CC = 0;
s16 dato_802B87D0 = 0;
s16 dato_802B87D4 = 0;
s16 seccion_pantalla_actual = 0;

s32 funcion_80290C20(Camara* camara) {
    if (camara->colision.unk34 == 0) {
        return 1;
    }
    if ((camara->colision.desconocido30 == 1) && (camara->colision.distancia_superficie[0] < 3.0f)) {
        return 1;
    }
    if ((camara->colision.desconocido32 == 1) && (camara->colision.distancia_superficie[1] < 3.0f)) {
        return 1;
    }
    return 0;
}

void analizar_displaylists_circuito(uintptr_t direccion) {
    s32 segmento = SEGMENT_NUMBER2(direccion);
    s32 desplazamiento = SEGMENT_OFFSET(direccion);
    SeccionesPista* section = (SeccionesPista*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);

    while (section->addr != 0) {
        if (section->flags & 0x8000) {
            dato_8015F59C = 1;
        } else {
            dato_8015F59C = 0;
        }
        if (section->flags & 0x2000) {
            dato_8015F5A0 = 1;
        } else {
            dato_8015F5A0 = 0;
        }
        if (section->flags & 0x4000) {
            dato_8015F5A4 = 1;
        } else {
            dato_8015F5A4 = 0;
        }
        generar_malla_colision(section->addr, section->tipo_superficie, section->id_seccion);
        section++;
    }
}

extern u32 es_flycam;

void renderizar_segmentos_circuito(uintptr_t direccion, struct desconocido_struct_800DC5EC* parametro1) {
    Jugador* jugador = parametro1->jugador;
    Camara* camara = parametro1->camara;
    u32 segmento = SEGMENT_NUMBER2(direccion);
    u32 desplazamiento = SEGMENT_OFFSET(direccion);
    s32* gfx = (s32*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    s16 sentido;
    s16 index;
    s16 sp1_e;
    s16 temporal_v0_3;
    u16 rot;
    if (es_modo_espejo) {
        rot = (u16) camara->rot[1];
        if (rot < GRADOS(45)) {
            sentido = SUR;
        } else if (rot < GRADOS(135)) {
            sentido = OESTE;
        } else if (rot < GRADOS(225)) {
            sentido = NORTE;
        } else if (rot < GRADOS(315)) {
            sentido = ESTE;
        } else {
            sentido = SUR;
        }
    } else {
        rot = (u16) camara->rot[1];
        if (rot < GRADOS(45)) {
            sentido = SUR;
        } else if (rot < GRADOS(135)) {
            sentido = ESTE;
        } else if (rot < GRADOS(225)) {
            sentido = NORTE;
        } else if (rot < GRADOS(315)) {
            sentido = OESTE;
        } else {
            sentido = SUR;
        }
    }
    parametro1->sentido_jugador = sentido;

    if (dato_80152300[camara - camara1] == 1) {
        sp1_e = obtener_id_seccion_pista(camara->colision.indice_zx_malla);
        temporal_v0_3 = obtener_id_seccion_pista(jugador->colision.indice_zx_malla);
        index = sp1_e - temporal_v0_3;
        if ((index < 2) && (index >= -1)) {
            if (sp1_e == 255) {
                if (temporal_v0_3 == 255) {
                    index = parametro1->contador_camino;
                } else if (jugador->colision.distancia_superficie[2] > 30.0f) {
                    index = parametro1->contador_camino;
                } else {
                    index = temporal_v0_3;
                }
            } else if (camara->colision.distancia_superficie[2] > 30.0f) {
                index = parametro1->contador_camino;
            } else {
                index = sp1_e;
            }
        } else {

            switch (id_circuito_actual) {
                case CIRCUITO_BOWSER_CASTLE:
                    if ((temporal_v0_3 >= 0x11) && (temporal_v0_3 < 0x18)) {
                        index = temporal_v0_3;
                    } else if ((temporal_v0_3 == 255) && (sp1_e != 255)) {
                        index = sp1_e;
                    } else if ((temporal_v0_3 != 255) && (sp1_e == 255)) {
                        index = temporal_v0_3;
                    } else {
                        index = parametro1->contador_camino;
                    }
                    break;
                case CIRCUITO_CHOCO_MOUNTAIN:
                    if ((temporal_v0_3 >= 0xE) && (temporal_v0_3 < 0x16)) {
                        index = temporal_v0_3;
                    } else if ((temporal_v0_3 == 255) && (sp1_e != 255)) {
                        index = sp1_e;
                    } else if ((temporal_v0_3 != 255) && (sp1_e == 255)) {
                        index = temporal_v0_3;
                    } else {
                        index = parametro1->contador_camino;
                    }
                    break;
                default:
                    if (temporal_v0_3 == 255) {
                        index = parametro1->contador_camino;
                    } else if (jugador->colision.distancia_superficie[2] > 30.0f) {
                        index = parametro1->contador_camino;
                    } else {
                        index = temporal_v0_3;
                    }
                    break;
            }
        }
    } else {
        index = obtener_id_seccion_pista(camara->colision.indice_zx_malla);
        if (camara->colision.distancia_superficie[2] > 30.0f) {
            index = parametro1->contador_camino;
        } else if (index == 255) {
            index = parametro1->contador_camino;
        }
    }

    parametro1->contador_camino = index;
    index = ((index - 1) * 4) + sentido;
    gSPDisplayList(display_list_cabeza++, gfx[index]);
}

void funcion_80291198(void) {
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07001140));
}

void funcion_802911C4(void) {
    if (seleccion_modo_pantalla == MODO_PANTALLA_1P) {
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070008E8));
    } else {
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07002D68));
    }
}

void funcion_8029122C(struct desconocido_struct_800DC5EC* parametro0, s32 id_jugador) {
    SIN_USO s32 relleno;
    Jugador* jugador = parametro0->jugador;
    Mat4 matriz;
    Vec3f vector;
    u16 contador_camino;
    u16 rot_camara;
    s16 sentido_jugador;

    inicializar_rdp();
    contador_camino = (u16) parametro0->contador_camino;
    rot_camara = (u16) parametro0->camara->rot[1];
    sentido_jugador = parametro0->sentido_jugador;
    switch (id_jugador) {
        case JUGADOR_UNO:
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[JUGADOR_UNO]),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[JUGADOR_UNO]),
                      G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
            break;
        case JUGADOR_DOS:
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[JUGADOR_DOS]),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[JUGADOR_DOS]),
                      G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
            break;
        case JUGADOR_TRES:
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[JUGADOR_TRES]),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[JUGADOR_TRES]),
                      G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
            break;
        case JUGADOR_CUATRO:
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[JUGADOR_CUATRO]),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
            gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[JUGADOR_CUATRO]),
                      G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
            break;
    }
    identidad_mtxf(matriz);
    fijar_posicion_render(matriz, 0);
    switch (id_circuito_actual) {
        case CIRCUITO_BOWSER_CASTLE:
            if (modo_pantalla_activo != MODO_PANTALLA_1P) {
                return;
            }
            if (contador_camino < 6) {
                return;
            }
            if (contador_camino > 9) {
                return;
            }
            if (contador_camino == 9) {
                if (rot_camara < 0xA000) {
                    return;
                }
                if (rot_camara > 0xE000) {
                    return;
                }
            }
            gSPDisplayList(display_list_cabeza++, d_circuito_bowsers_castle_dl_9228);
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            gDPPipeSync(display_list_cabeza++);
            gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
            gDPSetBlendMask(display_list_cabeza++, 0xFF);
            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            gSPDisplayList(display_list_cabeza++, 0x07000878);
            gDPSetAlphaCompare(display_list_cabeza++, G_AC_NONE);
            gDPPipeSync(display_list_cabeza++);
            break;
        case CIRCUITO_KOOPA_BEACH:

            gDPPipeSync(display_list_cabeza++);
            gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
            gDPSetBlendMask(display_list_cabeza++, 0xFF);
            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);

            switch (contador_camino) {
                case 22:
                case 23:
                case 29:
                case 30:
                case 31:
                case 37:
                    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
                    gSPDisplayList(display_list_cabeza++, 0x07009E70);
                    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
                    break;
            }
            vector[0] = 0.0f;
            vector[1] = dato_8015F8E4;
            vector[2] = 0.0f;
            trasladar_mtxf(matriz, vector);
            fijar_posicion_render(matriz, 0);

            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
            gDPSetBlendMask(display_list_cabeza++, 0xFF);
            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
            renderizar_segmentos_circuito((uintptr_t) d_circuito_koopa_troopa_beach_lista2_dl, parametro0);
            gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 1, 1, G_OFF);
            gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
            gDPSetAlphaCompare(display_list_cabeza++, G_AC_NONE);
            gDPPipeSync(display_list_cabeza++);
            break;
        case CIRCUITO_SHERBET_LAND:

            gDPPipeSync(display_list_cabeza++);
            gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
            gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetBlendMask(display_list_cabeza++, 0xFF);
            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            gDPSetTextureFilter(display_list_cabeza++, G_TF_BILERP);
            gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);

            identidad_mtxf(matriz);
            fijar_posicion_render(matriz, 0);
            renderizar_segmentos_circuito((uintptr_t) sherbet_land_dls_2, parametro0);

            gDPSetAlphaCompare(display_list_cabeza++, G_AC_NONE);
            if ((funcion_80290C20(parametro0->camara) == 1) && (funcion_802AAB4C(jugador) < jugador->pos[1])) {
                gSPSetGeometryMode(display_list_cabeza++, G_ZBUFFER);
                gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
                gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
                gSPDisplayList(display_list_cabeza++, 0x07002B48);
            }
            gDPPipeSync(display_list_cabeza++);
            break;
        case CIRCUITO_RAINBOW_ROAD:
            gDPPipeSync(display_list_cabeza++);
            identidad_mtxf(matriz);
            fijar_posicion_render(matriz, 0);
            gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
            renderizar_segmentos_circuito((uintptr_t) &d_circuito_rainbow_road_lista_dl, parametro0);
            gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
            gDPSetAlphaCompare(display_list_cabeza++, G_AC_NONE);
            gDPPipeSync(display_list_cabeza++);
            break;
        case CIRCUITO_WARIO_STADIUM:
            gDPPipeSync(display_list_cabeza++);
            gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
            gDPSetBlendMask(display_list_cabeza++, 0xFF);
            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            gDPSetTextureFilter(display_list_cabeza++, G_TF_BILERP);
            gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);

            identidad_mtxf(matriz);
            fijar_posicion_render(matriz, 0);

            gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            gDPSetPrimColor(display_list_cabeza++, 0, 0, 0xFF, 0xFF, 0x00, 0xFF);
            gSPDisplayList(display_list_cabeza++, 0x07000EC0);
            gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 1, 1, G_OFF);
            gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
            gDPSetAlphaCompare(display_list_cabeza++, G_AC_NONE);
            gDPPipeSync(display_list_cabeza++);
            break;
        case CIRCUITO_DK_JUNGLE:
            gDPPipeSync(display_list_cabeza++);
            gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
            gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetBlendMask(display_list_cabeza++, 0xFF);
            gDPSetTextureFilter(display_list_cabeza++, G_TF_BILERP);
            gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);

            identidad_mtxf(matriz);
            fijar_posicion_render(matriz, 0);

            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);

            if (contador_camino < 17) {
                gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                gSPDisplayList(display_list_cabeza++, 0x07003E40);
                gSPDisplayList(display_list_cabeza++, 0x07003EB0);
                if ((contador_camino >= 6) && (contador_camino < 13)) {
                    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                    gSPDisplayList(display_list_cabeza++, 0x07003DD0);
                }
            } else if ((contador_camino == 21) || (contador_camino == 22)) {
                if (sentido_jugador == 3) {
                    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
                    gSPDisplayList(display_list_cabeza++, 0x070036A8);
                }
                if ((sentido_jugador == 1) || (sentido_jugador == 0)) {
                    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
                    gSPDisplayList(display_list_cabeza++, 0x070036A8);
                } else {
                    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                    gSPDisplayList(display_list_cabeza++, 0x07003F30);
                    gSPDisplayList(display_list_cabeza++, 0x070036A8);
                }
            } else if (contador_camino == 24) {
                if ((sentido_jugador == 0) || (sentido_jugador == 3)) {
                    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
                    gSPDisplayList(display_list_cabeza++, 0x070036A8);
                }
            } else if (contador_camino == 23) {
                if (sentido_jugador == 3) {
                    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
                    gSPDisplayList(display_list_cabeza++, 0x070036A8);
                } else if (sentido_jugador == 0) {
                    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
                    gSPDisplayList(display_list_cabeza++, 0x070036A8);
                }
            }
            gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            switch (contador_camino) {
                case 5:
                    if (sentido_jugador != 3) {
                        gSPDisplayList(display_list_cabeza++, 0x07003DD0);
                    }
                    break;
                case 17:
                    switch (sentido_jugador) {
                        case 0:
                            gSPDisplayList(display_list_cabeza++, 0x07003E40);
                            gSPDisplayList(display_list_cabeza++, 0x07003EB0);
                            break;
                        case 1:
                            gSPDisplayList(display_list_cabeza++, 0x07003DD0);
                            gSPDisplayList(display_list_cabeza++, 0x07003E40);
                            gSPDisplayList(display_list_cabeza++, 0x07003EB0);
                            break;
                        case 2:
                            gSPDisplayList(display_list_cabeza++, 0x07003E40);
                            gSPDisplayList(display_list_cabeza++, 0x07003EB0);
                            gSPDisplayList(display_list_cabeza++, 0x07003F30);
                            break;
                        case 3:
                            gSPDisplayList(display_list_cabeza++, 0x07003EB0);
                            gSPDisplayList(display_list_cabeza++, 0x07003F30);
                            break;
                    }
                    break;
                case 18:
                    switch (sentido_jugador) {
                        case 0:
                            gSPDisplayList(display_list_cabeza++, 0x07003E40);
                            gSPDisplayList(display_list_cabeza++, 0x07003EB0);
                            break;
                        case 1:
                            gSPDisplayList(display_list_cabeza++, 0x07003DD0);
                            gSPDisplayList(display_list_cabeza++, 0x07003E40);
                            gSPDisplayList(display_list_cabeza++, 0x07003EB0);
                            break;
                        case 2:
                            gSPDisplayList(display_list_cabeza++, 0x07003E40);
                            gSPDisplayList(display_list_cabeza++, 0x07003EB0);
                            break;
                    }
                    break;
                case 21:
                    if ((sentido_jugador == 0) || (sentido_jugador == 1)) {
                        gSPDisplayList(display_list_cabeza++, 0x07003E40);
                        gSPDisplayList(display_list_cabeza++, 0x07003EB0);
                        gSPDisplayList(display_list_cabeza++, 0x07003F30);
                    } else {
                        gSPDisplayList(display_list_cabeza++, 0x07003EB0);
                    }
                    break;
                case 22:
                    if (sentido_jugador == 0) {
                        gSPDisplayList(display_list_cabeza++, 0x07003F30);
                    }
                    break;
                case 23:
                    if (sentido_jugador != 1) {
                        gSPDisplayList(display_list_cabeza++, 0x07003F30);
                    }
                    break;
            }
            gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 1, 1, G_OFF);
            gDPSetAlphaCompare(display_list_cabeza++, G_AC_NONE);
            gDPPipeSync(display_list_cabeza++);
            break;
    }
}

void renderizar_mario_raceway(struct desconocido_struct_800DC5EC* parametro0) {
    SIN_USO s32 relleno;
    u16 sp22 = parametro0->contador_camino;
    u16 sentido_jugador = parametro0->sentido_jugador;

    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    if (funcion_80290C20(parametro0->camara) == 1) {
        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07003050));
    }

    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gDPPipeSync(display_list_cabeza++);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    switch (sp22) {
        case 1:
        case 2:
        case 17:
            if ((sentido_jugador == 2) || (sentido_jugador == 1)) {
                funcion_802911C4();
            }
            break;
        case 3:
            if (sentido_jugador != 0) {
                funcion_802911C4();
            }
            break;
        case 4:
            if (sentido_jugador == 0) {
                funcion_80291198();
            } else {
                if (sentido_jugador == 1) {
                    funcion_80291198();
                }
                funcion_802911C4();
            }
            break;
        case 5:
        case 6:
            if ((sentido_jugador == 2) || (sentido_jugador == 3)) {
                funcion_802911C4();
            } else {
                funcion_80291198();
            }
            break;
        case 7:
            funcion_80291198();
            if ((sentido_jugador == 2) || (sentido_jugador == 3)) {
                funcion_802911C4();
            }
            break;
        case 8:
        case 9:
            if (sentido_jugador != 1) {
                funcion_802911C4();
            }
        case 10:
            if (sentido_jugador != 2) {
                funcion_80291198();
            }
            break;
        case 11:
            if (sentido_jugador == 0) {
                funcion_802911C4();
                funcion_80291198();
            } else if (sentido_jugador == 3) {
                funcion_802911C4();
            }
            break;
        case 12:
            if ((sentido_jugador == 0) || (sentido_jugador == 3)) {
                funcion_802911C4();
            }
            break;
        case 13:
        case 14:
            if (sentido_jugador != 1) {
                case 15:
                case 16:
                    funcion_802911C4();
            }
            break;
    }
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07003508));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07003240));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070014A0));

    renderizar_segmentos_circuito((uintptr_t) mario_raceway_dls, parametro0);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000450));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000240));
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070000E0));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000160));
}

void renderizar_choco_mountain(struct desconocido_struct_800DC5EC* parametro0) {
    SIN_USO s32 relleno[13];

    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    if (funcion_80290C20(parametro0->camara) == 1) {
        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07004608));
    }
    gDPSetCycleType(display_list_cabeza++, G_CYC_2CYCLE);
    gDPSetFogColor(display_list_cabeza++, dato_801625EC, dato_801625F4, dato_801625F0, 0xFF);
    gSPFogPosition(display_list_cabeza++, dato_802B87B0, dato_802B87B4);

    gDPPipeSync(display_list_cabeza++);
    gSPSetGeometryMode(display_list_cabeza++, G_FOG);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATERGB, G_CC_PASS2);

    gDPSetRenderMode(display_list_cabeza++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07005A70));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000828));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070008E0));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07005868));
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    renderizar_segmentos_circuito((uintptr_t) choco_mountain_dls, parametro0);

    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gDPSetRenderMode(display_list_cabeza++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2);
    gDPSetCombineMode(display_list_cabeza++, G_CC_DECALRGBA, G_CC_PASS2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000448));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070005D8));
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000718));
    gSPClearGeometryMode(display_list_cabeza++, G_FOG);
    gDPSetCycleType(display_list_cabeza++, G_CYC_1CYCLE);
    gDPPipeSync(display_list_cabeza++);
}

void renderizar_bowsers_castle(struct desconocido_struct_800DC5EC* parametro0) {

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    if (funcion_80290C20(parametro0->camara) == 1) {
        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07006A80));
    }

    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    dato_802B87BC++;
    if (dato_802B87BC > 255) {
        dato_802B87BC = 0;
    }
    renderizar_segmentos_circuito((uintptr_t) bowsers_castle_dls, parametro0);

    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000248));
}

void renderizar_banshee_boardwalk(struct desconocido_struct_800DC5EC* parametro0) {
    Camara* camara = parametro0->camara;
    Mat4 sp_cc;
    SIN_USO s32 relleno[6];
    Vec3f sp_a8;
    SIN_USO s32 relleno2[6];

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(display_list_cabeza++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07007228));

    gSPFogPosition(display_list_cabeza++, dato_802B87B0, dato_802B87B4);

    gDPPipeSync(display_list_cabeza++);

    gSPClearGeometryMode(display_list_cabeza++,
                         G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07005CD0));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07004E60));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070069B0));

    renderizar_segmentos_circuito((uintptr_t) banshee_boardwalk_dls, parametro0);

    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000580));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000060));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000540));

    if (camara->pos[1] < -20.0f) {
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07006310));
    }
    sp_a8[0] = camara->pos[0];
    sp_a8[1] = -82.0f;
    sp_a8[2] = camara->pos[2];
    trasladar_mtxf(sp_cc, sp_a8);
    fijar_posicion_render(sp_cc, 0);

    gSPDisplayList(display_list_cabeza++, d_circuito_banshee_boardwalk_dl_B278);
    gDPPipeSync(display_list_cabeza++);
}

void renderizar_yoshi_valley(struct desconocido_struct_800DC5EC* parametro0) {

    gDPPipeSync(display_list_cabeza++);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    renderizar_segmentos_circuito((uintptr_t) d_circuito_yoshi_valley_lista_dl, parametro0);
    gDPPipeSync(display_list_cabeza++);
}

void renderizar_frappe_snowland(struct desconocido_struct_800DC5EC* parametro0) {

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    if (funcion_80290C20(parametro0->camara) == 1) {
        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070065E0));
    }

    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    renderizar_segmentos_circuito((uintptr_t) d_circuito_frappe_snowland_lista_dl, parametro0);
}

void renderizar_koopa_troopa_beach(struct desconocido_struct_800DC5EC* parametro0) {

    gDPPipeSync(display_list_cabeza++);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);

    if (funcion_80290C20(parametro0->camara) == 1) {
        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07009CC0));
    }
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07009688));
    renderizar_segmentos_circuito((uintptr_t) d_circuito_koopa_troopa_beach_lista1_dl, parametro0);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070002C0));
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gDPPipeSync(display_list_cabeza++);
}

void renderizar_royal_raceway(struct desconocido_struct_800DC5EC* parametro0) {

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    if (funcion_80290C20(parametro0->camara) == 1) {
        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x0700B030));
    }
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x0700A648));

    renderizar_segmentos_circuito((uintptr_t) royal_raceway_dls, parametro0);

    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070011A8));
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070008A0));
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
}

void renderizar_luigi_raceway(struct desconocido_struct_800DC5EC* parametro0) {

    SIN_USO s32 relleno;
    u16 sp22 = (u16) parametro0->contador_camino;
    s16 frame_ant;

    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);

    if (funcion_80290C20(parametro0->camara) == 1) {
        gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07009EC0));
    }

    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    renderizar_segmentos_circuito((uintptr_t) luigi_raceway_dls, parametro0);

    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070000E0));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07000068));

    dato_800DC5DC = 88;
    dato_800DC5E0 = 72;

    if ((modo_pantalla_activo == MODO_PANTALLA_1P) && (sp22 >= 10) && (sp22 < 17)) {

        frame_ant = (s16) s_framebuffer_renderizado - 1;

        if (frame_ant < 0) {
            frame_ant = 2;
        } else if (frame_ant >= 3) {
            frame_ant = 0;
        }
        seccion_pantalla_actual++;
        if (seccion_pantalla_actual >= 6) {
            seccion_pantalla_actual = 0;
        }
        switch (seccion_pantalla_actual) {
            case 0:
                copiar_framebuffer(dato_800DC5DC, dato_800DC5E0, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0xF800));
                break;
            case 1:
                copiar_framebuffer(dato_800DC5DC + 64, dato_800DC5E0, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x10800));
                break;
            case 2:
                copiar_framebuffer(dato_800DC5DC, dato_800DC5E0 + 32, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x11800));
                break;
            case 3:
                copiar_framebuffer(dato_800DC5DC + 64, dato_800DC5E0 + 32, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x12800));
                break;
            case 4:
                copiar_framebuffer(dato_800DC5DC, dato_800DC5E0 + 64, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x13800));
                break;
            case 5:
                copiar_framebuffer(dato_800DC5DC + 64, dato_800DC5E0 + 64, 64, 32,
                                 (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[frame_ant]),
                                 (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x14800));
                break;
        }
    }
}

void renderizar_moo_moo_farm(struct desconocido_struct_800DC5EC* parametro0) {
    SIN_USO s32 relleno[13];
    s16 temporal_s0 = parametro0->contador_camino;
    s16 sentido_jugador = parametro0->sentido_jugador;

    fijar_iluminacion_circuito(dato_800DC610, dato_802B87D4, 0, 1);
    gSPTexture(display_list_cabeza++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07004DF8));
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07005640));
    gSPFogPosition(display_list_cabeza++, dato_802B87B0, dato_802B87B4);

    renderizar_segmentos_circuito((uintptr_t) moo_moo_farm_dls, parametro0);

    if ((temporal_s0 < 14) && (temporal_s0 > 10)) {
        if ((sentido_jugador == 2) || (sentido_jugador == 3) || (sentido_jugador == 1))
            gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_dl_13FF8);

    } else if (temporal_s0 < 16) {
        gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_dl_13FF8);
    } else if (temporal_s0 < 19) {
        if (sentido_jugador != 2)
            gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_dl_13FF8);

    } else if (temporal_s0 < 20) {
        if (sentido_jugador == 0)
            gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_dl_13FF8);
    }
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    if ((temporal_s0 >= 16) && (temporal_s0 < 24)) {
        if ((sentido_jugador == 2) || (sentido_jugador == 3))
            gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07005410));

    } else if (temporal_s0 < 9) {
        if (sentido_jugador == 2)
            gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x07005410));
    }
    if (temporal_s0 < 4) {
        if (sentido_jugador != 0)
            gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_dl_14060);

    } else if (temporal_s0 < 8) {
        if (sentido_jugador == 2)
            gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_dl_14060);

    } else if (temporal_s0 >= 22) {
        gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_dl_14060);
    } else if (temporal_s0 >= 18) {
        if ((sentido_jugador == 0) || (sentido_jugador == 3))
            gSPDisplayList(display_list_cabeza++, d_circuito_moo_moo_farm_dl_14060);
    }
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPDisplayList(display_list_cabeza++, ((uintptr_t) 0x070010C0));
}
