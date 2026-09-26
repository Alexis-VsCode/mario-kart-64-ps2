// Imprimir texto

s32 funcion_80092EE4(char* character) {
    u8 temporal_t6;
    s32 variable_v1;

    temporal_t6 = (character[1] + 0x80);
    variable_v1 = 2;
    switch (character[0]) {
        case -95:
            switch (temporal_t6) {
                case 0x22:
                case 0x24:
                    variable_v1 = 0x000000EA;
                    break;
                case 0x23:
                    variable_v1 = 0x000000E9;
                    break;
                case 0x25:
                    variable_v1 = 0x000000D0;
                    break;
                case 0x2A:
                    variable_v1 = 0x000000E8;
                    break;
                case 0x30:
                    variable_v1 = 0x000000EB;
                    break;
                case 0x47:
                    variable_v1 = 0x000000D1;
                    break;
                case 0x49:
                    variable_v1 = 0x000000D2;
                    break;
                case 0x5C:
                    variable_v1 = 0x000000D3;
                    break;
                case 0x3C:
                case 0x3D:
                case 0x5D:
                    variable_v1 = 0x000000D4;
                    break;
                default:
                    break;
            }
            break;
        case -93:
            if ((temporal_t6 >= 0x30) && (temporal_t6 < 0x3A)) {
                variable_v1 = temporal_t6 + 0xA5;
            } else {
                switch (temporal_t6) {
                    case 0x44:
                        variable_v1 = 0x000000DF;
                        break;
                    case 0x43:
                    case 0x63:
                        variable_v1 = 0x000000E0;
                        break;
                    case 0x4E:
                    case 0x6E:
                        variable_v1 = 0x000000E1;
                        break;
                    case 0x50:
                    case 0x70:
                        variable_v1 = 0x000000E2;
                        break;
                    case 0x52:
                    case 0x72:
                        variable_v1 = 0x000000E3;
                        break;
                    case 0x73:
                        variable_v1 = 0x000000E4;
                        break;
                    case 0x54:
                    case 0x74:
                        variable_v1 = 0x000000E5;
                        break;
                    case 0x53:
                        variable_v1 = 0x000000E6;
                        break;
                    case 0x56:
                    case 0x76:
                        variable_v1 = 0x000000E7;
                        break;
                    default:
                        break;
                }
            }
            break;
        case -85:
            if (temporal_t6 == 0x2E) {
                variable_v1 = 0x000000E0;
            }
            break;
        default:
            variable_v1 = 2;
    }
    return variable_v1;
}

s32 obtener_ancho_cadena(char* buffer) {
    s32 indice_glifo;
    s32 ancho_cadena = 0;

    if (*buffer != 0) {
        do {
            indice_glifo = car_a_indice_glifo(buffer);
            if (indice_glifo >= 0) {
                ancho_cadena += ancho_pantalla_glifo[indice_glifo];
            } else if (indice_glifo == -1) {
                ancho_cadena += 7;
            }
            if (indice_glifo >= 0x30) {
                buffer += 2;
            } else {
                buffer += 1;
            }
        } while (*buffer != 0);
    }
    return ancho_cadena;
}

void fijar_color_texto(s32 parametro0) {
    g_color_texto = parametro0;
}

SIN_USO void funcion_800930E4(s32 parametro0, s32 parametro1, char* parametro2) {
    fijar_color_texto(AZUL_TEXTO);
    imprimir_modo_texto_1(parametro0, parametro1, parametro2, 0, 1.0, 1.0);
}

void imprimir_texto0(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y, s32 mode) {
    s32 ancho_cadena = 0;
    s32 indice_glifo;

    gSPDisplayList(display_list_cabeza++, dato_020077A8);
    if (*text != 0) {
        do {
            indice_glifo = car_a_indice_glifo(text);
            if (indice_glifo >= 0) {
                cargar_img_menu((TexturaMenu*) segmentado_a_duplicado_virtual((const void*) lut_textura_glifo[indice_glifo]));
                display_list_cabeza =
                    imprimir_letra(display_list_cabeza,
                                 (TexturaMenu*) segmentado_a_duplicado_virtual((const void*) lut_textura_glifo[indice_glifo]),
                                 columna + (ancho_cadena * escalar_x), renglon, mode, escalar_x, escalar_y);
                ancho_cadena += ancho_pantalla_glifo[indice_glifo] + tracking;
            } else if ((indice_glifo != -2) && (indice_glifo == -1)) {
                ancho_cadena += tracking + 7;
            } else {
                gSPDisplayList(display_list_cabeza++, dato_020077D8);
                return;
            }
            if (indice_glifo >= 0x30) {
                text += 2;
            } else {
                text += 1;
            }
        } while (*text != 0);
    }
    gSPDisplayList(display_list_cabeza++, dato_020077D8);
}

void imprimir_modo_texto_1(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y) {
    imprimir_texto0(columna, renglon, text, tracking, escalar_x, escalar_y, 1);
}

void imprimir_modo_texto_2(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y) {
    imprimir_texto0(columna, renglon, text, tracking, escalar_x, escalar_y, 2);
}

void imprimir_texto1(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y, s32 parametro6) {
    char* cadena_temporal = text;
    s32 ancho_cadena = 0;
    s32 indice_glifo;
    s32 sp60;

    while (*cadena_temporal != 0) {
        indice_glifo = car_a_indice_glifo(cadena_temporal);
        if (indice_glifo >= 0) {
            ancho_cadena += ((ancho_pantalla_glifo[indice_glifo] + tracking) * escalar_x);
        } else if ((indice_glifo != -2) && (indice_glifo == -1)) {
            ancho_cadena += ((tracking + 7) * escalar_x);
        } else {
            return;
        }
        if (indice_glifo >= 0x30) {
            cadena_temporal += 2;
        } else {
            cadena_temporal += 1;
        }
    }

    switch (parametro6) {
        case TEXTO_IZQUIERDA:
            do {
            } while (0);
        case TEXTO_DERECHA:
            columna -= ancho_cadena;
            break;
        case MODO_TEXTO_CENTRO_1:
        case MODO_TEXTO_CENTRO_2:
            columna -= ancho_cadena / 2;
            break;
        default:
            break;
    }

    if (parametro6 < 3) {
        sp60 = 1;
    } else {
        sp60 = 2;
    }

    gSPDisplayList(display_list_cabeza++, dato_020077A8);
    while (*text != 0) {
        indice_glifo = car_a_indice_glifo(text);
#if defined(TARGET_PS2) && defined(SMK64_DEV)
        if (indice_glifo >= (s32) (sizeof(lut_textura_glifo) / sizeof(lut_textura_glifo[0]))) {
            void registrar(const char* fmt, ...);
            registrar("print_text1: glifo %d fuera de rango en \"%s\" (%02x %02x %02x)", indice_glifo, text,
                    (u8) text[0], (u8) text[1], (u8) text[2]);
        }
#endif
        if (indice_glifo >= 0) {
            cargar_img_menu(segmentado_a_duplicado_virtual(lut_textura_glifo[indice_glifo]));
            display_list_cabeza = imprimir_letra(display_list_cabeza, segmentado_a_duplicado_virtual(lut_textura_glifo[indice_glifo]),
                                            columna, renglon, sp60, escalar_x, escalar_y);
            columna = columna + (s32) ((ancho_pantalla_glifo[indice_glifo] + tracking) * escalar_x);
        } else if ((indice_glifo != -2) && (indice_glifo == -1)) {
            columna = columna + (s32) ((tracking + 7) * escalar_x);
        } else {
            gSPDisplayList(display_list_cabeza++, dato_020077D8);
            return;
        }
        if (indice_glifo >= 0x30) {
            text += 2;
        } else {
            text += 1;
        }
    }
    gSPDisplayList(display_list_cabeza++, dato_020077D8);
}

void imprimir_izquierda_texto1(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y) {
    imprimir_texto1(columna, renglon, text, tracking, escalar_x, escalar_y, TEXTO_IZQUIERDA);
}

void imprimir_modo_centro_texto1_1(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y) {
    imprimir_texto1(columna, renglon, text, tracking, escalar_x, escalar_y, MODO_TEXTO_CENTRO_1);
}

void imprimir_derecha_texto1(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y) {
    imprimir_texto1(columna, renglon, text, tracking, escalar_x, escalar_y, TEXTO_DERECHA);
}

void imprimir_modo_centro_texto1_2(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y) {
    imprimir_texto1(columna, renglon, text, tracking, escalar_x, escalar_y, MODO_TEXTO_CENTRO_2);
}

void imprimir_texto2(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y, s32 parametro6) {
    TexturaMenu* textura_glifo;
    s32 ancho_personaje;
    s32 indice_glifo;

    gSPDisplayList(display_list_cabeza++, dato_020077A8);
    if (*text != 0) {
        do {
            indice_glifo = car_a_indice_glifo(text);
            if (indice_glifo >= 0) {
                textura_glifo = (TexturaMenu*) segmentado_a_duplicado_virtual((const void*) lut_textura_glifo[indice_glifo]);
                cargar_img_menu(textura_glifo);
                display_list_cabeza =
                    imprimir_letra(display_list_cabeza, textura_glifo, columna - (ancho_pantalla_glifo[indice_glifo] / 2), renglon,
                                 parametro6, escalar_x, escalar_y);
                if ((indice_glifo >= 0xD5) && (indice_glifo < 0xE0)) {
                    ancho_personaje = 0x20;
                } else {
                    ancho_personaje = 0xC;
                }
                columna = columna + (s32) ((ancho_personaje + tracking) * escalar_x);
            } else if ((indice_glifo != -2) && (indice_glifo == -1)) {
                columna = columna + (s32) ((tracking + 7) * escalar_x);
            } else {
                gSPDisplayList(display_list_cabeza++, dato_020077D8);
                return;
            }
            if (indice_glifo >= 0x30) {
                text += 2;
            } else {
                text += 1;
            }
        } while (*text != 0);
    }

    gSPDisplayList(display_list_cabeza++, dato_020077D8);
}

void funcion_800939C8(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y) {
    imprimir_texto2(columna, renglon, text, tracking, escalar_x, escalar_y, 1);
}

void dibujar_texto(s32 columna, s32 renglon, char* text, s32 tracking, f32 escalar_x, f32 escalar_y) {
    imprimir_texto2(columna, renglon, text, tracking, escalar_x, escalar_y, 2);
}

void funcion_80093A30(s32 parametro0) {
    funcion_8009E2A8(dato_800F0B1C[parametro0]);
}

void funcion_80093A5C(u32 parametro0) {
    if (dato_8015F788 == 0) {
        funcion_8009C918();
    }
    switch (parametro0) {
        case RENDER_PANTALLA_MODO_1J_JUGADOR_UNO:
            funcion_800940EC((s32) dato_800F0B1C[parametro0]);
            break;
        case RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO:
        case RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS:
        case RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO:
        case RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS:
            if (dato_8015F788 == 0) {
                funcion_80093C1C((s32) dato_800F0B1C[parametro0]);
            } else {
                funcion_800940EC((s32) dato_800F0B1C[parametro0]);
            }
            break;
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO:
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS:
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES:
        case RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO:
            if (dato_8015F788 == 3) {
                funcion_800940EC((s32) dato_800F0B1C[parametro0]);
            } else {
                funcion_80093C1C((s32) dato_800F0B1C[parametro0]);
            }
            break;
    }
    gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
}

SIN_USO void funcion_80093B70(u32 parametro0) {
    if ((parametro0 == 0) || (parametro0 == 2) || (parametro0 == 3) || (parametro0 == 8)) {
        funcion_8009C918();
    }
    switch (parametro0) {
        case 0:
            funcion_800940EC(0);
            break;
        case 2:
        case 3:
        case 8:
            funcion_80093C1C(0);
            break;
        case 1:
        case 4:
        case 9:
            funcion_800940EC(1);
            break;
        case 10:
            funcion_80093C1C(2);
            break;
        case 11:
            funcion_800940EC(3);
            break;
        default:
            break;
    }
}

void funcion_80093C1C(s32 parametro0) {
    gSPDisplayList(display_list_cabeza++, dato_02007F18);
    funcion_8009CA6C(parametro0);
    gSPDisplayList(display_list_cabeza++, dato_02007F48);
}

SIN_USO void funcion_80093C88(void) {
    return;
}

SIN_USO void funcion_80093C90(void) {
    return;
}

void funcion_80093C98(s32 parametro0) {
    gSPViewport(display_list_cabeza++, VIRTUAL_A_FISICO(dato_802B8880));
    guOrtho(&gfx_pool->efecto_mtx[cantidad_efecto_matriz], 0.0f, 319.0f, 239.0f, 0.0f, -100.0f, 100.0f, 1.0f);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(display_list_cabeza++, dato_02007F18);
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA, ALTURA_PANTALLA);
    manejar_especial_menus();
    if (parametro0 == 0) {
        funcion_800A54EC();
        funcion_8009CA6C(4);
        dato_80165754 = cantidad_efecto_matriz;
        cantidad_efecto_matriz = 0;
    }
}

void funcion_80093E20(void) {
    funcion_80093C98(0);
}

void funcion_80093E40(void) {
    funcion_80093C98(1);
}

void funcion_80093E60(void) {
    s32 i;

    buffer_comprimido_menu = obtener_siguiente_disponible_memoria_direccion(0x00002800);
#ifdef AVOID_UB
    fijar_buffer_textura_menu((u16*) obtener_siguiente_disponible_memoria_direccion(0x000124F8), 0x000124F8);
#else
    buffer_textura_menu = (u16*) obtener_siguiente_disponible_memoria_direccion(0x000124F8);
#endif
    tkmk_00_bajo_res_buffer = obtener_siguiente_disponible_memoria_direccion(0x00001000);
    copia_puntos_gp = obtener_siguiente_disponible_memoria_direccion(4U);

    for (i = 0; i < 5; i++) {
        tipo_transicion[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        dato_8018E838[i] = 0;
    }

    borrar_texturas_menu();
    funcion_8009A344();
    borrar_menus();
    funcion_80092258();
    dato_8018ED91 = 0;
}

void funcion_80093F10(void) {
    gSPViewport(display_list_cabeza++, VIRTUAL_A_FISICO(dato_802B8880));
    guOrtho(&gfx_pool->efecto_mtx[cantidad_efecto_matriz], 0.0f, 319.0f, 239.0f, 0.0f, -100.0f, 100.0f, 1.0f);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(display_list_cabeza++, dato_02007F18);
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    funcion_80092290(4, dato_8018E850, dato_8018E858);
    funcion_80092290(5, (s32*) &dato_8018E850[1], (s32*) &dato_8018E858[1]);
    funcion_8009C918();
    funcion_80099A70();
    funcion_80099E54();
    manejar_predeterminado_menus();
    funcion_80099AEC();
    funcion_80099EC4();
    funcion_8009CA2C();
    gSPDisplayList(display_list_cabeza++, dato_02007F48);
    cantidad_efecto_matriz = 0;
}

void funcion_800940EC(s32 parametro0) {
    gSPViewport(display_list_cabeza++, VIRTUAL_A_FISICO(dato_802B8880));
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA, ALTURA_PANTALLA);
    guOrtho(&gfx_pool->efecto_mtx[cantidad_efecto_matriz], 0.0f, 319.0f, 239.0f, 0.0f, -100.0f, 100.0f, 1.0f);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(display_list_cabeza++, dato_02007F18);
    funcion_80092290(4, dato_8018E850, dato_8018E858);
    funcion_80092290(5, (s32*) &dato_8018E850[1], (s32*) &dato_8018E858[1]);
    funcion_80092148();
    funcion_80099A70();
    funcion_80099E54();
    manejar_predeterminado_menus();
    funcion_80099AEC();
    funcion_80099EC4();
    funcion_8009CA6C(parametro0);
    gSPDisplayList(display_list_cabeza++, dato_02007F48);
    funcion_80057CE4();
}

void funcion_800942D0(void) {
    Mtx* probar;
    f32 variable_f26;
    s32 variable_s2;
    s32 cosa;
    probar = &gfx_pool->objeto_mtx[0];
    gSPMatrix(display_list_cabeza++, &gfx_pool->pantalla_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, &gfx_pool->mtx_mirar_a[0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    guRotate(probar, rot_x_modelo_intro, 1.0f, 0.0f, 0.0f);
    guRotate(probar + 1, rot_y_modelo_intro, 0.0f, 1.0f, 0.0f);
    guScale(probar + 2, 1.0f, 1.0f, escala_modelo_intro);
    gSPMatrix(display_list_cabeza++, probar++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPMatrix(display_list_cabeza++, probar++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPMatrix(display_list_cabeza++, probar++, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gDPSetEnvColor(display_list_cabeza++, 0x00, 0x00, 0x00, 0x00);
    gSPDisplayList(display_list_cabeza++, dato_02007F60);
    gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);
    if (intro_modelo_movimiento_rapidez > 0) {
        variable_f26 = intro_modelo_rapidez;
        if (variable_f26 > 10.0f) {
            variable_f26 = 10.0f;
        }
        for (variable_s2 = 0, cosa = 0xC0; variable_s2 < 0xC; variable_s2++, cosa -= 0x10) {
            guRotate(probar, 0.0f, 1.0f, 0.0f, 0.0f);
            guRotate(probar + 1, (variable_s2 + 1) * intro_modelo_movimiento_rapidez * variable_f26, 0.0f, 1.0f, 0.0f);
            guScale(probar + 2, 1.0f, 1.0f, 2.0f);
            gSPMatrix(display_list_cabeza++, probar++, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPMatrix(display_list_cabeza++, probar++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPMatrix(display_list_cabeza++, probar++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            gDPSetEnvColor(display_list_cabeza++, 0x00, 0x00, 0x00, cosa);
            gSPDisplayList(display_list_cabeza++, textura_inicio_dl4);
            gSPPopMatrix(display_list_cabeza++, G_MTX_MODELVIEW);
        }
    }
}

void funcion_80094660(struct GfxPool* parametro0, SIN_USO s32 parametro1) {
    u16 norma_persp;
    mover_tabla_segmento_a_dmem();
    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    guPerspective(&parametro0->pantalla_mtx, &norma_persp, 45.0f, 1.3333334f, 100.0f, 12800.0f, 1.0f);
    gSPPerspNormalize(display_list_cabeza++, norma_persp);
    guLookAt(&parametro0->mtx_mirar_a[0], 0.0f, 0.0f, (f32) ojo_modelo_z_intro, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    funcion_800942D0();
    gDPPipeSync(display_list_cabeza++);
    gDPSetTexturePersp(display_list_cabeza++, G_TP_NONE);
    gDPSetTextureFilter(display_list_cabeza++, G_TF_BILERP);
}

void renderizar_bandera_a_cuadros(struct GfxPool* parametro0, SIN_USO s32 parametro1) {
    u16 norma_persp;
    mover_tabla_segmento_a_dmem();
    guPerspective(&parametro0->mtx_persp[0], &norma_persp, 45.0f, 1.3333334f, 100.0f, 12800.0f, 1.0f);
    gSPPerspNormalize(display_list_cabeza++, norma_persp);
    guLookAt(&parametro0->mtx_mirar_a[1], 0.0f, 0.0f, (f32) ojo_modelo_z_intro, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    guRotate(&parametro0->objeto_mtx[0], rot_x_modelo_intro, 1.0f, 0, 0);
    guRotate(&parametro0->objeto_mtx[1], rot_y_modelo_intro, 0, 1.0f, 0);
    guRotate(&parametro0->objeto_mtx[2], rot_z_modelo_intro, 0, 0, 1.0f);
    guScale(&parametro0->objeto_mtx[3], escala_modelo_intro, escala_modelo_intro, escala_modelo_intro);
    guTranslate(&parametro0->objeto_mtx[4], pos_x_modelo_intro, pos_y_modelo_intro, pos_z_modelo_intro);
    gSPMatrix(display_list_cabeza++, &parametro0->mtx_persp[0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, &parametro0->mtx_mirar_a[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(display_list_cabeza++, &parametro0->objeto_mtx[0], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPMatrix(display_list_cabeza++, &parametro0->objeto_mtx[1], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPMatrix(display_list_cabeza++, &parametro0->objeto_mtx[2], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPMatrix(display_list_cabeza++, &parametro0->objeto_mtx[3], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPMatrix(display_list_cabeza++, &parametro0->objeto_mtx[4], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPDisplayList(display_list_cabeza++, dato_02007FC8);
    funcion_800B0004();
    gSPDisplayList(display_list_cabeza++, dato_02007650);
}

void funcion_80094A64(struct GfxPool* pool) {
    cantidad_hud_matriz = 0;
    cantidad_efecto_matriz = 0;
    gSPViewport(display_list_cabeza++, VIRTUAL_A_FISICO(&dato_802B8880));
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA, ALTURA_PANTALLA);
    guOrtho(&pool->pantalla_mtx, 0.0f, ANCHO_PANTALLA - 1, ALTURA_PANTALLA - 1, 0.0f, -100.0f, 100.0f, 1.0f);
    gSPMatrix(display_list_cabeza++, &pool->pantalla_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(display_list_cabeza++, dato_02007650);
    preparar_menus();
    funcion_80092290(4, dato_8018E850, dato_8018E858);
    funcion_80092290(5, &dato_8018E850[1], &dato_8018E858[1]);
    funcion_80099A70();
    funcion_8009C918();
    switch (seleccion_menu) {
        case MENU_INICIO:
            funcion_80095574();
            funcion_80093E40();
            break;
        case MENU_OPCIONES:
        case MENU_DATOS:
        case MENU_DATOS_CIRCUITO:
        case LOGO_INTRO_MENU:
        case CONTROLLER_PAK_MENU:
        case MENU_PRINCIPAL:
        case MENU_SELECCION_PERSONAJE:
        case MENU_SELECCION_CIRCUITO:
            manejar_predeterminado_menus();
            funcion_80099AEC();
            break;
    }
    funcion_8009CA2C();
    menu_destello_ciclo += 1;
    gDPPipeSync(display_list_cabeza++);
    gSPDisplayList(display_list_cabeza++, dato_020076B0);
}

void preparar_menus(void) {
    if (seleccion_modo_fundido != NINGUNO_MODO_FUNDIDO) {
        borrar_texturas_menu();
        funcion_8009A344();
        borrar_menus();
        funcion_8009B938();
        funcion_80092258();
        funcion_800B5F30();
        funcion_800B6014();
        cargar_estados_menu(seleccion_menu);
        switch (seleccion_menu) {
            case MENU_OPCIONES:
                agregar_item_menu(MENU_PRINCIPAL_FONDO, 0, 0, PRIORIDAD_ITEM_MENU_2);
                agregar_item_menu(TIPO_ITEM_MENU_0F1, 0, 0, PRIORIDAD_ITEM_MENU_4);
                agregar_item_menu(TIPO_ITEM_MENU_0F0, 0, 0, PRIORIDAD_ITEM_MENU_2);
                break;
            case MENU_DATOS:
                agregar_item_menu(MENU_PRINCIPAL_FONDO, 0, 0, PRIORIDAD_ITEM_MENU_2);
                agregar_item_menu(TIPO_ITEM_MENU_08C, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_07C, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_07D, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_07E, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_07F, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_080, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_081, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_082, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_083, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_084, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_085, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_086, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_087, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_088, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_089, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_08A, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_08B, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_08D, 0, 0, PRIORIDAD_ITEM_MENU_8);
                break;
            case MENU_DATOS_CIRCUITO:
                agregar_item_menu(MENU_ITEM_DATOS_CIRCUITO_IMAGEN, 0, 0, PRIORIDAD_ITEM_MENU_8);
                agregar_item_menu(MENU_ITEM_DATOS_CIRCUITO_INFO, 0, 0, PRIORIDAD_ITEM_MENU_8);
                agregar_item_menu(MENU_ITEM_DATOS_CIRCUITO_SELECCIONABLE, 0, 0, PRIORIDAD_ITEM_MENU_8);
                agregar_item_menu(TIPO_ITEM_MENU_0E9, 0, 0, PRIORIDAD_ITEM_MENU_8);
                agregar_item_menu(TIPO_ITEM_MENU_0EA, 0, 0, PRIORIDAD_ITEM_MENU_8);
                break;
            case LOGO_INTRO_MENU:
                agregar_item_menu(MENU_ITEM_IU_LOGO_INTRO, 0, 0, PRIORIDAD_ITEM_MENU_0);
                break;
            case CONTROLLER_PAK_MENU:
                agregar_item_menu(TIPO_ITEM_MENU_0DA, 0, 0, PRIORIDAD_ITEM_MENU_0);
                agregar_item_menu(TIPO_ITEM_MENU_0D2, 0, 0, PRIORIDAD_ITEM_MENU_4);
                agregar_item_menu(TIPO_ITEM_MENU_0D4, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_0D3, 0, 0, PRIORIDAD_ITEM_MENU_8);
                agregar_item_menu(TIPO_ITEM_MENU_0D5, 0, 0, PRIORIDAD_A_ITEM_MENU);
                agregar_item_menu(TIPO_ITEM_MENU_0D6, 0, 0, PRIORIDAD_A_ITEM_MENU);
                agregar_item_menu(TIPO_ITEM_MENU_0D7, 0, 0, PRIORIDAD_A_ITEM_MENU);
                agregar_item_menu(TIPO_ITEM_MENU_0D8, 0, 0, PRIORIDAD_A_ITEM_MENU);
                agregar_item_menu(TIPO_ITEM_MENU_0D9, 0, 0, PRIORIDAD_A_ITEM_MENU);
                break;
            case MENU_INICIO:
                agregar_item_menu(MENU_ITEM_IU_LOGO_Y_COPYRIGHT, 0, 0, PRIORIDAD_ITEM_MENU_4);
                agregar_item_menu(MENU_ITEM_IU_INICIO_FONDO, 0, 0, PRIORIDAD_ITEM_MENU_0);
                agregar_item_menu(MENU_INICIO_BANDERA, 0, 0, PRIORIDAD_ITEM_MENU_0);
                if (bits_mando & 1) {
                    agregar_item_menu(MENU_ITEM_IU_EMPUJE_INICIO_BOTON, 0, 0, PRIORIDAD_ITEM_MENU_2);
                } else {
                    agregar_item_menu(MENU_ITEM_IU_SIN_MANDO, 0, 0, PRIORIDAD_ITEM_MENU_2);
                }
                agregar_item_menu(MENU_ITEM_IU_INICIO_REGISTRO_TIEMPO, 0, 0, PRIORIDAD_ITEM_MENU_6);
                modo_demo = 0;
                mando_usar_demo = 0;
                break;
            case MENU_PRINCIPAL:
                agregar_item_menu(MENU_PRINCIPAL_FONDO, 0, 0, PRIORIDAD_ITEM_MENU_2);
                agregar_item_menu(MENU_ITEM_IU_JUEGO_SELECCION, 0x0000015E, 0x00000011, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_ITEM_IU_4J_JUEGO, 0x0000015E, 0x0000003E, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_ITEM_IU_3J_JUEGO, 0x0000015E, 0x0000003E, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_ITEM_IU_2J_JUEGO, 0x0000015E, 0x0000003E, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_ITEM_IU_1J_JUEGO, 0x0000015E, 0x0000003E, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_ITEM_IU_OK, 0x0000015E, 0x000000C8, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_PRINCIPAL_GFX_DATOS, 0x0000015E, 0x000000C8, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_PRINCIPAL_GFX_OPCION, 0x0000015E, 0x000000C8, PRIORIDAD_ITEM_MENU_6);
                if (tiene_modo_extra_desbloqueado() != 0) {
                    agregar_item_menu(MENU_PRINCIPAL_CC_EXTRA, 0, 0, PRIORIDAD_ITEM_MENU_6);
                }
                agregar_item_menu(MENU_PRINCIPAL_150CC, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_PRINCIPAL_100CC, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_PRINCIPAL_50CC, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_PRINCIPAL_CONTRARRELOJ_DATOS, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_PRINCIPAL_CONTRARRELOJ_EMPEZAR, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_01B, 0, 0, PRIORIDAD_C_ITEM_MENU);
                break;
            case MENU_SELECCION_PERSONAJE:
                agregar_item_menu(FONDO_SELECCION_PERSONAJE, 0, 0, PRIORIDAD_ITEM_MENU_2);
                agregar_item_menu(PERSONAJE_SELECCION_MENU_JUGADOR_SELECCION_CARTEL, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(PERSONAJE_SELECCION_MENU_OK, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_SELECCION_PERSONAJE_MARIO, 0, 0, PRIORIDAD_ITEM_MENU_8);
                agregar_item_menu(MENU_SELECCION_PERSONAJE_LUIGI, 0, 0, PRIORIDAD_ITEM_MENU_8);
                agregar_item_menu(MENU_SELECCION_PERSONAJE_TOAD, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_SELECCION_PERSONAJE_PEACH, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_SELECCION_PERSONAJE_YOSHI, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_SELECCION_PERSONAJE_DK, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_SELECCION_PERSONAJE_WARIO, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(MENU_SELECCION_PERSONAJE_BOWSER, 0, 0, PRIORIDAD_ITEM_MENU_8);
                agregar_item_menu(PERSONAJE_SELECCION_MENU_1J_CURSOR, 0, 0, PRIORIDAD_C_ITEM_MENU);
                agregar_item_menu(PERSONAJE_SELECCION_MENU_2J_CURSOR, 0, 0, PRIORIDAD_C_ITEM_MENU);
                agregar_item_menu(PERSONAJE_SELECCION_MENU_3J_CURSOR, 0, 0, PRIORIDAD_C_ITEM_MENU);
                agregar_item_menu(PERSONAJE_SELECCION_MENU_4J_CURSOR, 0, 0, PRIORIDAD_C_ITEM_MENU);
                break;
            case MENU_SELECCION_CIRCUITO:
                agregar_item_menu(FONDO_SELECCION_CIRCUITO, 0, 0, PRIORIDAD_ITEM_MENU_2);
                agregar_item_menu(CIRCUITO_SELECCION_MAPA_SELECCION, 0, 0, PRIORIDAD_ITEM_MENU_6);
                if (seleccion_modo != BATALLA) {
                    agregar_item_menu(SELECCION_CIRCUITO_COPA_HONGO, 0, 0, PRIORIDAD_ITEM_MENU_4);
                    agregar_item_menu(SELECCION_CIRCUITO_COPA_FLOR, 0, 0, PRIORIDAD_ITEM_MENU_4);
                    agregar_item_menu(SELECCION_CIRCUITO_COPA_ESTRELLA, 0, 0, PRIORIDAD_ITEM_MENU_4);
                    agregar_item_menu(SELECCION_CIRCUITO_COPA_ESPECIAL, 0, 0, PRIORIDAD_ITEM_MENU_4);
                    agregar_item_menu(TIPO_ITEM_MENU_058, 0, 0, PRIORIDAD_ITEM_MENU_6);
                    agregar_item_menu(CIRCUITO_SELECCION_CIRCUITO_NOMBRES, 0, 0, PRIORIDAD_ITEM_MENU_6);
                    agregar_item_menu(TIPO_ITEM_MENU_05A, 0, 0, PRIORIDAD_ITEM_MENU_6);
                    agregar_item_menu(TIPO_ITEM_MENU_05B, 0, 0, PRIORIDAD_ITEM_MENU_6);
                } else {
                    agregar_item_menu(CIRCUITO_SELECCION_BATALLA_NOMBRES, 0, 0, PRIORIDAD_ITEM_MENU_6);
                    agregar_item_menu(TIPO_ITEM_MENU_06E, 0, 0, PRIORIDAD_ITEM_MENU_6);
                }
                agregar_item_menu(TIPO_ITEM_MENU_064, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_05F, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_060, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_061, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_062, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(OK_SELECCION_CIRCUITO, 0, 0, PRIORIDAD_ITEM_MENU_6);
                agregar_item_menu(TIPO_ITEM_MENU_05E, 0, 0, PRIORIDAD_ITEM_MENU_8);
                if (seleccion_modo == CONTRARRELOJ) {
                    agregar_item_menu(TIPO_ITEM_MENU_065, 0, 0, PRIORIDAD_ITEM_MENU_8);
                    agregar_item_menu(TIPO_ITEM_MENU_066, 0, 0, PRIORIDAD_ITEM_MENU_8);
                    agregar_item_menu(TIPO_ITEM_MENU_069, 0, 0, PRIORIDAD_ITEM_MENU_8);
                }
                if (seleccion_modo == GRAN_PREMIO) {
                    agregar_item_menu(TIPO_ITEM_MENU_068, 0, 0, PRIORIDAD_ITEM_MENU_8);
                    agregar_item_menu(TIPO_ITEM_MENU_067, 0, 0, PRIORIDAD_ITEM_MENU_5);
                }
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            default:
                break;
        }
        if (seleccion_modo_fundido != LOGO_MODO_FUNDIDO) {
            funcion_8009DF4C(0x00000014);
        } else {
            funcion_8009DF6C(0x00000014);
        }
        seleccion_modo_fundido = NINGUNO_MODO_FUNDIDO;
    }
}

void funcion_80095574(void) {
    s32 variable_v0;

    if ((sin_ref_8018EE0C < 3) || (tipo_transicion[4] != 0)) {
        manejar_predeterminado_menus();
    }
    if (seleccion_menu_depuracion > DEPURACION_MENU_DESACTIVADO) {
        cargar_fuente_depuracion();
        imprimir_cad2_depuracion(0x00000050, 0x00000064, "debug_mode");
        switch (seleccion_menu_depuracion) {
            case DEPURACION_MENU_DEPURACION_MODO:
                imprimir_cad2_depuracion(0x00000046, 0x00000064, "*");
                break;
            case CIRCUITO_MENU_DEPURACION:
                imprimir_cad2_depuracion(0x00000046, 0x0000006E, "*");
                break;
            case DEPURACION_MENU_PANTALLA_MODO:
                imprimir_cad2_depuracion(0x00000046, 0x00000078, "*");
                break;
            case JUGADOR_MENU_DEPURACION:
                imprimir_cad2_depuracion(0x00000046, 0x00000082, "*");
                break;
            case DEPURACION_MENU_SONIDO_MODO:
                imprimir_cad2_depuracion(0x00000046, 0x0000008C, "*");
                break;
            case DEPURACION_MENU_DAR_TODOS_ORO_COPA:
                imprimir_cad2_depuracion(0x00000046, 0x00000096, "*");
                break;
        }
        if (modo_depuracion_activacion) {
            imprimir_cad2_depuracion(0x000000AA, 0x00000064, "on");
        } else {
            imprimir_cad2_depuracion(0x000000AA, 0x00000064, "off");
        }
        if ((id_circuito_actual >= (CIRCUITOS_NUM - 1)) || (id_circuito_actual < 0)) {
            id_circuito_actual = 0;
        }
        imprimir_num_cad(0x00000050, 0x0000006E, "map_number", id_circuito_actual);
        if (id_circuito_actual < 0xA) {
            variable_v0 = 0;
        } else {
            variable_v0 = 8;
        }
        imprimir_cad2_depuracion(variable_v0 + 0xB9, 0x0000006E, obtener_circuito_depuracion_nombre);
        imprimir_cad2_depuracion(0x00000050, 0x00000078, "screen_mode");
        imprimir_cad2_depuracion(0x000000AA, 0x00000078, depuracion_pantalla_modo_nombres[pantalla_modo_lista_indice]);
        imprimir_cad2_depuracion(0x00000050, 0x00000082, "player");
        imprimir_cad2_depuracion(0x000000AA, 0x00000082, nombres_personaje_depuracion[selecciones_personaje[0]]);
        imprimir_cad2_depuracion(0x00000050, 0x0000008C, "sound mode");
        imprimir_cad2_depuracion(0x000000AA, 0x0000008C, depuracion_sonido_modo_nombres[sonido_modo]);
        if (seleccion_menu_depuracion == DEPURACION_MENU_DAR_TODOS_ORO_COPA) {
            imprimir_cad2_depuracion(0x00000050, 0x00000096, "push b to get all goldcup");
        }
        funcion_80057778();
    }
    if (seleccion_menu_depuracion == DEPURACION_MENU_DESACTIVADO) {
        contador_tiempos_menu += 1;
    } else {
        contador_tiempos_menu = 3;
    }
    if (contador_tiempos_menu == 2) {
        reproducir_sonido2(SONIDO_BIENVENIDA_INTRO);
    }
#ifdef AVOID_UB
    if ((contador_tiempos_menu > 300) && (es_pantalla_siendo_fundido() == 0)) {
#else
    if (contador_tiempos_menu > 300) {
#endif
        funcion_8009E230();
        funcion_800CA0A0();
    }
    gSPDisplayList(display_list_cabeza++, dato_020076E0);
}

Gfx* seleccionar_case_destello_dibujo(SIN_USO Gfx* display_list_cabeza_2, s32 ulx, s32 uly, s32 lrx, s32 lry, s32 rapidez) {
    s32 escala_grises;

    escala_grises = ((menu_destello_ciclo % rapidez) << 9) / rapidez;
    if (escala_grises > 0x100) {
        escala_grises = 0x200 - escala_grises;
    }

    if (escala_grises > 0xFF) {
        escala_grises = 0xFF;
    }

#if AVOID_UB
    return display_list_cabeza =
               dibujar_relleno_caja(display_list_cabeza, ulx, uly, lrx, lry, escala_grises, escala_grises, escala_grises, 0xFF);
#else
    display_list_cabeza = dibujar_relleno_caja(display_list_cabeza, ulx, uly, lrx, lry, escala_grises, escala_grises, escala_grises, 0xFF);
#endif
}

Gfx* seleccionar_lento_case_destello_dibujo(Gfx* display_list_cabeza_2, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    return seleccionar_case_destello_dibujo(display_list_cabeza_2, ulx, uly, lrx, lry, 64);
}

Gfx* seleccionar_rapido_case_destello_dibujo(Gfx* display_list_cabeza_2, s32 ulx, s32 uly, s32 lrx, s32 lry) {
    return seleccionar_case_destello_dibujo(display_list_cabeza_2, ulx, uly, lrx, lry, 4);
}

Gfx* funcion_800959F8(Gfx* display_list_cabeza_2, Vtx* parametro1) {
    s32 index;

    if ((s32) g_color_texto < TEXTO_AZUL_VERDE_ROJO_CICLO_1) {
        index = g_color_texto;
    } else {
        index = ((g_color_texto * 2) + ((s32) temporizador_global % 2)) - 4;
    }
#ifdef AVOID_UB
    gSPVertex(display_list_cabeza_2++, parametro1, 2, 0);
    gSPVertex(display_list_cabeza_2++, &parametro1[(index + 1) * 2], 2, 2);
    gSPDisplayList(display_list_cabeza_2++, pantalla_rectangulo_comun);
#else
    if (parametro1 == dato_02007BB8) {
        gSPDisplayList(display_list_cabeza_2++, dato_800E84CC[index]);
    } else if (parametro1 == dato_02007CD8) {
        gSPDisplayList(display_list_cabeza_2++, dato_800E84EC[index]);
    } else if (parametro1 == dato_02007DF8) {
        gSPDisplayList(display_list_cabeza_2++, dato_800E850C[index]);
    }
#endif

    return display_list_cabeza_2;
}
