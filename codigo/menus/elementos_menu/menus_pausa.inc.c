// Menus pausa

void renderizar_veces_vuelta(s32 grabar_tipo, s32 columna, s32 renglon) {
    SIN_USO s32 relleno;
    u32 registro_tiempo;
    SIN_USO s32 relleno2;
    s32 color_texto;
    s32 temporal_t0;
    char sp38[3];
    MenuItem* item;
    s32 sp30;

    if (estado_juego == CARRERA) {
        sp30 = 0;
    } else {
        sp30 = 1;
    }
    if (grabar_tipo < 5) {
        if (sp30 == 0) {
            registro_tiempo = funcion_800B4E24(grabar_tipo);
        } else {
            registro_tiempo = funcion_800B4EB4(grabar_tipo, contrarreloj_indice_circuito_datos);
        }
        fijar_color_texto(VERDE_TEXTO);
    } else {
        if (sp30 == 0) {
            registro_tiempo = funcion_800B4F2C();
        } else {
            registro_tiempo = funcion_800B4FB0(contrarreloj_indice_circuito_datos);
        }
    }
    funcion_800939C8(columna + 0x14, renglon, dato_800E7744[grabar_tipo], 2, 0.65f, 0.65f);
    if (sp30 == 0) {
        item = buscar_duplicado_items_menu(0x000000BB);
        if (grabar_tipo < 5) {
            if (grabar_tipo == item->param1) {
                color_texto = temporizador_global % 3;
            } else {
                color_texto = AMARILLO_TEXTO;
            }
        } else if (item->param2 != 0) {
            color_texto = temporizador_global % 3;
        } else {
            color_texto = AMARILLO_TEXTO;
        }
    } else {
        color_texto = AMARILLO_TEXTO;
    }
    fijar_color_texto(color_texto);
    temporal_t0 = registro_tiempo & 0xFFFFF;
    obtener_minutos_registro_tiempo(temporal_t0, sp38);
    funcion_800939C8(columna + 0x27, renglon, sp38, 0, 0.65f, 0.65f);
    imprimir_modo_texto_1(columna + 0x32, renglon, "'", 0, 0.65f, 0.65f);
    obtener_segundos_registro_tiempo(temporal_t0, sp38);
    funcion_800939C8(columna + 0x3B, renglon, sp38, 0, 0.65f, 0.65f);
    imprimir_modo_texto_1(columna + 0x46, renglon, "\"", 0, 0.65f, 0.65f);
    obtener_centesimas_registro_tiempo(temporal_t0, sp38);
    funcion_800939C8(columna + 0x50, renglon, sp38, 0, 0.65f, 0.65f);
    if ((u32) temporal_t0 < 600000U) {
        color_texto = registro_tiempo >> 0x14;
    } else {
        color_texto = 8;
    }
    imprimir_modo_centro_texto1_1(columna + 0x78, renglon, dato_800E76A8[color_texto], 0, 0.65f, 0.65f);
}

void renderizar_menu_item_anuncio_fantasma(MenuItem* parametro0) {
    SIN_USO s32 margen_pila_0;
    s32 temporal_t0;
    s32 temporal_t1;
    s32 temporal_t2;
    f32 algun_multiplicador = 0.85f;
    s32 cosa = 24.0f * algun_multiplicador;

    temporal_t0 = 0x140 - parametro0->column;
    temporal_t1 = parametro0->row;
    temporal_t2 = (s32) ((obtener_ancho_cadena(texto_menu_anuncio_fantasma) + 8) * algun_multiplicador) / 2;
    display_list_cabeza = dibujar_caja(display_list_cabeza, temporal_t0 - temporal_t2, (temporal_t1 - cosa) + 4, temporal_t2 + temporal_t0,
                                temporal_t1 + 4, 0, 0, 0, 0x00000064);
    fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_1);
    imprimir_modo_centro_texto1_1(parametro0->column - 3, parametro0->row, texto_menu_anuncio_fantasma, 0, 0.85f, 0.85f);
}

void renderizar_menu_pausa(MenuItem* parametro0) {
    if (juego_en_pausa != 0) {
        switch (seleccion_modo) {
            case CONTRARRELOJ:
                renderizar_menu_pausa_contrarreloj(parametro0);
                break;
            case VERSUS:
                renderizar_menu_pausa_versus(parametro0);
                break;
            case GRAN_PREMIO:
                renderizar_pausa_gran_premio(parametro0);
                break;
            case BATALLA:
                renderizar_batalla_pausa(parametro0);
                break;
        }
    }
}

void renderizar_menu_pausa_contrarreloj(MenuItem* parametro0) {
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    char sp68[3];
    s32 temporal_a0;
    s32 variable_s0;
    s32 zero = 0;

    display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x0000013F, 0x000000EF, 0, 0, 0, 0x0000008C);
    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_centro_texto1_1(0x000000A0, 0x00000050,
                              duplicar_nombres_circuito[orden_circuito_copa[seleccion_copa][indice_circuito_en_copa]], 0, 1.0f, 1.0f);
    fijar_color_texto(TEXTO_ROJO);
    imprimir_modo_centro_texto1_1(0x0000009D, 0x00000060, texto_tiempo_mejor[0], 0, 0.8f, 0.8f);
    temporal_a0 = funcion_800B4E24(CONTRARRELOJ_3LAP_REGISTRO_1);
    temporal_a0 &= 0xFFFFF;
    obtener_minutos_registro_tiempo(temporal_a0, sp68);
    funcion_800939C8(0x0000007F, 0x0000006D, sp68, 0, 0.8f, 0.8f);
    imprimir_modo_texto_1(0x0000008E, 0x0000006D, "'", 0, 0.8f, 0.8f);
    obtener_segundos_registro_tiempo(temporal_a0, sp68);
    funcion_800939C8(0x00000098, 0x0000006D, sp68, 0, 0.8f, 0.8f);
    imprimir_modo_texto_1(0x000000A7, 0x0000006D, "\"", 0, 0.8f, 0.8f);
    obtener_centesimas_registro_tiempo(temporal_a0, sp68);
    funcion_800939C8(0x000000B3, 0x0000006D, sp68, 0, 0.8f, 0.8f);
    imprimir_modo_centro_texto1_1(0x0000009D, 0x0000007C, texto_tiempo_mejor[1], 0, 0.8f, 0.8f);
    temporal_a0 = funcion_800B4F2C();
    temporal_a0 &= 0xFFFFF;
    obtener_minutos_registro_tiempo(temporal_a0, sp68);
    funcion_800939C8(0x0000007F, 0x00000089, sp68, 0, 0.8f, 0.8f);
    imprimir_modo_texto_1(0x0000008E, 0x00000089, "'", 0, 0.8f, 0.8f);
    obtener_segundos_registro_tiempo(temporal_a0, sp68);
    funcion_800939C8(0x00000098, 0x00000089, sp68, 0, 0.8f, 0.8f);
    imprimir_modo_texto_1(0x000000A7, 0x00000089, "\"", 0, 0.8f, 0.8f);
    obtener_centesimas_registro_tiempo(temporal_a0, sp68);
    funcion_800939C8(0x000000B3, 0x00000089, sp68, 0, 0.8f, 0.8f);
    for (variable_s0 = 0; variable_s0 < 5; variable_s0++) {
        efecto_rainbow_texto(parametro0->state - 11, variable_s0, VERDE_TEXTO);
        imprimir_modo_texto_1(dato_800E8538[zero].column, dato_800E8538[zero].row + (13 * variable_s0), boton_pausa_texto[variable_s0], 0,
                          0.75f, 0.75f);
    }
}

void renderizar_menu_pausa_versus(MenuItem* parametro0) {
    s16 temporal_t0;
    s16 temporal_v1;
    s32 temporal_t3;
    s32 temporal_t4;
    s32 variable_s0;
    s32 variable_s1;
    desconocido_d_800E70A0* temporal_s3;
    struct desconocido_struct_800DC5EC* temporal_v0;

    temporal_v0 = &dato_8015F480[juego_en_pausa - 1];
    temporal_v1 = temporal_v0->inicio_x_pantalla;
    temporal_t0 = temporal_v0->inicio_y_pantalla;
    temporal_t3 = temporal_v0->ancho_pantalla / 2;
    temporal_t4 = temporal_v0->altura_pantalla / 2;
    display_list_cabeza = dibujar_caja(display_list_cabeza, temporal_v1 - temporal_t3, temporal_t0 - temporal_t4, temporal_v1 + temporal_t3,
                                temporal_t0 + temporal_t4, 0, 0, 0, 0x0000008C);
    temporal_s3 = &dato_800E8540[(seleccion_modo_pantalla * 4) + (juego_en_pausa - 1)];
    for (variable_s0 = 0; variable_s0 < 4; variable_s0++) {
        if (variable_s0 > 0) {
            variable_s1 = variable_s0 + 1;
        } else {
            variable_s1 = variable_s0;
        }
        efecto_rainbow_texto(parametro0->state - 0x15, variable_s0, AMARILLO_TEXTO);
        imprimir_modo_texto_1(temporal_s3->column - 2, temporal_s3->row + (13 * variable_s0), boton_pausa_texto[variable_s1], 0, 0.75f, 0.75f);
    }
}

void renderizar_pausa_gran_premio(MenuItem* parametro0) {
    s32 temporal_t0;
    s32 temporal_v1;
    s32 temporal_s0;
    s32 temporal_s1;
    s32 temporal_t3;
    s32 temporal_t4;
    s32 variable_s0;
    desconocido_d_800E70A0* temporal_s3;
    struct desconocido_struct_800DC5EC* temporal_v0;
    f32 one = 1.0f;

    temporal_v0 = &dato_8015F480[juego_en_pausa - 1];
    temporal_v1 = temporal_v0->inicio_x_pantalla;
    temporal_t0 = temporal_v0->inicio_y_pantalla;
    temporal_t3 = temporal_v0->ancho_pantalla / 2;
    temporal_t4 = temporal_v0->altura_pantalla / 2;
    display_list_cabeza = dibujar_caja(display_list_cabeza, temporal_v1 - temporal_t3, temporal_t0 - temporal_t4, temporal_v1 + temporal_t3,
                                temporal_t0 + temporal_t4, 0, 0, 0, 140);
    temporal_s3 = &dato_800E85C0[(seleccion_modo_pantalla * 4) + (juego_en_pausa - 1)];
    temporal_s0 = ((obtener_ancho_cadena(nombres_copa[seleccion_copa]) * one) + 10.0f) / 2;
    temporal_s1 = ((obtener_ancho_cadena(dato_800E76CC[seleccion_cc]) * one) + 10.0f) / 2;
    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_centro_texto1_1(160 - temporal_s1, temporal_s3->row - 50, nombres_copa[seleccion_copa], 0, 1.0f, 1.0f);
    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_centro_texto1_1(160 + temporal_s0, temporal_s3->row - 50, dato_800E76CC[seleccion_cc], 0, 1.0f, 1.0f);
    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_centro_texto1_1(160, temporal_s3->row - 30,
                              duplicar_nombres_circuito[orden_circuito_copa[seleccion_copa][indice_circuito_en_copa]], 0, 1.0f, 1.0f);
    for (variable_s0 = 0; variable_s0 < 2; variable_s0++) {
        efecto_rainbow_texto(parametro0->state - 31, variable_s0, AMARILLO_TEXTO);
        imprimir_modo_texto_1(temporal_s3->column, temporal_s3->row + (variable_s0 * 13), boton_pausa_texto[variable_s0 * 4], 0, 0.75f, 0.75f);
    }
}

void renderizar_batalla_pausa(MenuItem* parametro0) {
    struct desconocido_struct_800DC5EC* temporal_v0;
    s16 temporal_t0;
    s16 temporal_v1;
    s32 temporal_t3;
    s32 temporal_t4;
    s32 variable_a1;
    s32 variable_s1;
    desconocido_d_800E70A0* temporal_s3;

    temporal_v0 = &dato_8015F480[juego_en_pausa - 1];
    temporal_v1 = temporal_v0->inicio_x_pantalla;
    temporal_t0 = temporal_v0->inicio_y_pantalla;
    temporal_t3 = temporal_v0->ancho_pantalla / 2;
    temporal_t4 = temporal_v0->altura_pantalla / 2;
    display_list_cabeza = dibujar_caja(display_list_cabeza, temporal_v1 - temporal_t3, temporal_t0 - temporal_t4, temporal_v1 + temporal_t3,
                                temporal_t0 + temporal_t4, 0, 0, 0, 0x0000008C);
    temporal_s3 = &dato_800E8600[(seleccion_modo_pantalla * 4) + (juego_en_pausa - 1)];
    for (variable_a1 = 0; variable_a1 < 4; variable_a1++) {
        if (variable_a1 > 0) {
            variable_s1 = variable_a1 + 1;
        } else {
            variable_s1 = variable_a1;
        }
        efecto_rainbow_texto(parametro0->state - 0x29, variable_a1, AMARILLO_TEXTO);
        imprimir_modo_texto_1(temporal_s3->column - 2, temporal_s3->row + 13 * variable_a1, boton_pausa_texto[variable_s1], 0, 0.75f, 0.75f);
    }
}

void funcion_800A54EC(void) {
    desconocido_d_800E70A0 sp50;
    desconocido_d_800E70A0* variable_v1;
    MenuItem* sp48;
    s32 secuela_el_por_que;
    s32 por_que;
    SIN_USO desconocido_d_800E70A0* huh;

    if (juego_en_pausa == 0) {
        return;
    }

    por_que = seleccion_modo;
    sp48 = buscar_items_menu(PAUSA_ITEM_MENU);
    if (por_que) {}
    gSPViewport(display_list_cabeza++, VIRTUAL_A_FISICO(dato_802B8880));
    guOrtho(&gfx_pool->efecto_mtx[cantidad_efecto_matriz], 0.0f, 319.0f, 239.0f, 0.0f, -100.0f, 100.0f, 1.0f);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz++]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    switch (por_que) { /* irregular */
        default:
            break;
        case 1:
            variable_v1 = &dato_800E8538[0];
            break;
        case 2:
            variable_v1 = &dato_800E8540[(seleccion_modo_pantalla * 4) + (juego_en_pausa - 1)];
            break;
        case 0:
            variable_v1 = &dato_800E85C0[(seleccion_modo_pantalla * 4) + (juego_en_pausa - 1)];
            break;
        case 3:
            variable_v1 = &dato_800E8600[(seleccion_modo_pantalla * 4) + (juego_en_pausa - 1)];
            break;
    }
    secuela_el_por_que = dato_800F0B50[por_que];
    sp50.column = variable_v1->column - 8;
    sp50.row = (variable_v1->row + ((sp48->state - secuela_el_por_que) * 0xD)) - 8;
    funcion_800A66A8(sp48, &sp50);
}

void renderizar_menu_item_fin_circuito_opcion(MenuItem* parametro0) {
    desconocido_d_800E70A0 sp98;
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    f32 por_que;
    char sp84[3];
    SIN_USO s32 margen_pila_3;
    SIN_USO s32 margen_pila_4;
    s32 temporal_a0;
    SIN_USO s32 variable_v1;
    s32 variable_s1;
    s32 variable_s2;
    s32 temporal_v0;
    s32 zero = 0;
    desconocido_d_800E70A0* variable_v0_9;
    char sp5_c[3];

    if (parametro0->state == 0) {
        if ((parametro0->param1 >= 0x1E) && ((temporizador_global / 16) % 2)) {
            por_que = obtener_ancho_cadena(boton_pausa_texto[REPETICION]) * 0.8f;
            display_list_cabeza =
                dibujar_caja(display_list_cabeza, 0x000000C0, 0x00000021, (s32) (por_que) + 0xC6, 0x00000032, 0, 0, 0, 0x00000096);
            fijar_color_texto(VERDE_TEXTO);
            imprimir_modo_texto_1(0x000000BF, 0x00000030, boton_pausa_texto[REPETICION], 0, 0.8f, 0.8f);
        }
    } else {
        if (parametro0->state == 1) {
            variable_s1 = parametro0->param1;
            variable_s2 = (s32) (parametro0->param1 * 0xFF) / 140;
        } else {
            variable_s1 = 0x0000008C;
            variable_s2 = 0x000000FF;
        }
        display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x0000013F, 0x000000EF, 0, 0, 0, variable_s1);
        gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, variable_s2);
        fijar_color_texto(AMARILLO_TEXTO);
        imprimir_modo_centro_texto1_2(0x000000A0, 0x00000050,
                                  duplicar_nombres_circuito[orden_circuito_copa[seleccion_copa][indice_circuito_en_copa]], 0, 1.0f, 1.0f);
        switch (parametro0->state) {
            case 1:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
                fijar_color_texto(TEXTO_ROJO);
                imprimir_modo_centro_texto1_2(0x0000009D, 0x00000060, texto_tiempo_mejor[0], 0, 0.8f, 0.8f);
                temporal_a0 = funcion_800B4E24(0);
                temporal_a0 &= 0xFFFFF;
                obtener_minutos_registro_tiempo(temporal_a0, sp84);
                dibujar_texto(0x0000007F, 0x0000006D, sp84, 0, 0.8f, 0.8f);
                imprimir_modo_texto_2(0x0000008E, 0x0000006D, "'", 0, 0.8f, 0.8f);
                obtener_segundos_registro_tiempo(temporal_a0, sp84);
                dibujar_texto(0x00000098, 0x0000006D, sp84, 0, 0.8f, 0.8f);
                imprimir_modo_texto_2(0x000000A7, 0x0000006D, "\"", 0, 0.8f, 0.8f);
                obtener_centesimas_registro_tiempo(temporal_a0, sp84);
                dibujar_texto(0x000000B3, 0x0000006D, sp84, 0, 0.8f, 0.8f);
                imprimir_modo_centro_texto1_2(0x0000009D, 0x0000007C, texto_tiempo_mejor[1], 0, 0.8f, 0.8f);
                temporal_a0 = funcion_800B4F2C();
                temporal_a0 &= 0xFFFFF;
                obtener_minutos_registro_tiempo(temporal_a0, sp84);
                dibujar_texto(0x0000007F, 0x00000089, sp84, 0, 0.8f, 0.8f);
                imprimir_modo_texto_2(0x0000008E, 0x00000089, "'", 0, 0.8f, 0.8f);
                obtener_segundos_registro_tiempo(temporal_a0, sp84);
                dibujar_texto(0x00000098, 0x00000089, sp84, 0, 0.8f, 0.8f);
                imprimir_modo_texto_2(0x000000A7, 0x00000089, "\"", 0, 0.8f, 0.8f);
                obtener_centesimas_registro_tiempo(temporal_a0, sp84);
                dibujar_texto(0x000000B3, 0x00000089, sp84, 0, 0.8f, 0.8f);
                for (variable_s1 = 0; variable_s1 < 6; variable_s1++) {
                    efecto_rainbow_texto(parametro0->state - 0xB, variable_s1, VERDE_TEXTO);
                    imprimir_modo_texto_2(dato_800E8538[zero].column, dato_800E8538[zero].row + (0xD * variable_s1),
                                      boton_pausa_texto[variable_s1 + 1], 0, 0.75f, 0.75f);
                }
                break;
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
                fijar_color_texto(AMARILLO_TEXTO);
                temporal_v0 = parametro0->state - 0x15;
                for (variable_s1 = 0; variable_s1 < 7; variable_s1++) {
                    imprimir_modo_texto_1(0x0000004D, 0x6E + (0xD * variable_s1), dato_800E798C[(temporal_v0 * 7) + variable_s1], 0, 0.8f,
                                      0.8f);
                }
                break;
            case 30:
            case 31:
                fijar_color_texto(VERDE_TEXTO);
                for (variable_s1 = 0; variable_s1 < 2; variable_s1++) {
                    imprimir_modo_texto_1(0x0000005A, parametro0->row + (0xD * variable_s1) + 0x6E, dato_800E7A3C[variable_s1], 0, 0.8f, 0.8f);
                }
                for (variable_s1 = 0; variable_s1 < 2; variable_s1++) {
                    efecto_rainbow_texto(parametro0->state - 0x1E, variable_s1, VERDE_TEXTO);
                    convertir_numero_a_ascii(variable_s1 + 1, sp5_c);
                    imprimir_modo_texto_1(0x5A - parametro0->column, (0x96 + (0x14 * variable_s1)), &sp5_c[1], 0, 0.75f, 0.75f);
                    if (dato_8018EE10[variable_s1].fantasma_datos_guardado == 0) {
                        imprimir_modo_texto_1(0x69 - parametro0->column, (0x96 + (0x14 * variable_s1)), dato_800E7A44, 0, 0.75f, 0.75f);
                    } else {
                        imprimir_modo_texto_1(0x69 - parametro0->column, (0x96 + (0x14 * variable_s1)),
                                          duplicar_nombres_circuito_2[orden_circuito_copa[dato_8018EE10[variable_s1].indice_circuito / 4]
                                                                          [dato_8018EE10[variable_s1].indice_circuito % 4]],
                                          0, 0.75f, 0.75f);
                    }
                }
                break;
            case 32:
                fijar_color_texto(AMARILLO_TEXTO);
                for (variable_s1 = 0; variable_s1 < 3; variable_s1++) {
                    imprimir_modo_texto_1(0x00000064, (0xD * variable_s1) + 0x6E, dato_800E7A48[variable_s1], 0, 0.8f, 0.8f);
                }
                break;
            case 35:
            case 36:
                fijar_color_texto(AMARILLO_TEXTO);
                for (variable_s1 = 0; variable_s1 < 3; variable_s1++) {
                    imprimir_modo_texto_1(0x00000055, parametro0->row + (0xD * variable_s1) + 0x6E, dato_800E7A60[variable_s1], 0, 0.8f, 0.8f);
                }
                for (variable_s1 = 0; variable_s1 < 2; variable_s1++) {
                    efecto_rainbow_texto(parametro0->state - 0x23, variable_s1, VERDE_TEXTO);
                    imprimir_modo_texto_1(0x7D - parametro0->column, 0x9B + (0xF * variable_s1), dato_800E7A6C[variable_s1], 0, 0.8f, 0.8f);
                }
                break;
            case 40:
                fijar_color_texto(AMARILLO_TEXTO);
                for (variable_s1 = 0; variable_s1 < 3; variable_s1++) {
                    imprimir_modo_texto_1(0x00000055, (0xD * variable_s1) + 0x6E, dato_800E7A74[variable_s1], 0, 0.8f, 0.8f);
                }
                break;
            case 41:
                fijar_color_texto(AMARILLO_TEXTO);
                for (variable_s1 = 0; variable_s1 < 2; variable_s1++) {
                    imprimir_modo_texto_1(0x0000005D, (0xD * variable_s1) + 0x6E, dato_800E7A80[variable_s1], 0, 0.8f, 0.8f);
                }
                break;
        }
        switch (parametro0->state) {
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
                variable_v0_9 = &dato_800E73E0[parametro0->state - 11];
                break;
            case 30:
            case 31:
                variable_v0_9 = &dato_800E7410[parametro0->state - 30];
                break;
            case 35:
            case 36:
                if (0) {}
                variable_v0_9 = &dato_800E7420[parametro0->state - 35];
                break;
            default:
                return;
        }
        sp98.column = variable_v0_9->column;
        sp98.row = variable_v0_9->row;
        funcion_800A66A8(parametro0, &sp98);
    }
}

void funcion_800A6034(MenuItem* parametro0) {
    char* text;

    if (dato_801657E8 != true) {
        gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, parametro0->param1);
        text = nombres_copa[dato_800DC540];
        fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_2);
        imprimir_modo_centro_texto1_2(parametro0->column + 0x41, parametro0->row + 0xA0, text, 0, 0.85f, 1.0f);
        text = nombres_circuito[id_circuito_actual];
        fijar_color_texto((s32) id_circuito_actual % 4);
        imprimir_modo_centro_texto1_2(parametro0->column + 0x41, parametro0->row + 0xC3, text, 0, 0.65f, 0.85f);
    }
}

void funcion_800A6154(MenuItem* parametro0) {
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    desconocido_d_800E70A0 sp6_c;
    SIN_USO s32 margen_pila_3;
    s32 variable_s0;
    s32 variable_s1;

    if (parametro0->state == 0) {
        display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x0000013F, 0x000000EF, 0, 0, 0, parametro0->param1);
        fijar_color_texto(AMARILLO_TEXTO);
        gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, (parametro0->param1 * 0xFF) / 100);
        for (variable_s1 = 0, variable_s0 = 0x96; variable_s0 < 0xBE; variable_s1++, variable_s0 += 0x14) {
            imprimir_modo_texto_2(0x0000008C, variable_s0, boton_pausa_texto[(variable_s1 * 3) + 1], 0, 1.0f, 1.0f);
        }
    } else {
        display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x0000013F, 0x000000EF, 0, 0, 0, 0x00000064);
        for (variable_s1 = 0, variable_s0 = 0x96; variable_s1 < 2; variable_s1++, variable_s0 += 0x14) {
            efecto_rainbow_texto(parametro0->state - 0xB, variable_s1, AMARILLO_TEXTO);
            imprimir_modo_texto_1(0x0000008C, variable_s0, boton_pausa_texto[(variable_s1 * 3) + 1], 0, 1.0f, 1.0f);
        }
    }
    if (parametro0->state >= 0xB) {
        sp6_c.column = 0x0084;
        sp6_c.row = (parametro0->state * 0x14) - 0x4E;
        funcion_800A66A8(parametro0, &sp6_c);
    }
    if (parametro0->param2 > 0) {
        display_list_cabeza = funcion_80098FC8(display_list_cabeza, 0, 0, 0x0000013F, parametro0->param2);
        display_list_cabeza = funcion_80098FC8(display_list_cabeza, 0, 0xEF - parametro0->param2, 0x0000013F, 0x000000EF);
    }
}

void funcion_800A638C(MenuItem* parametro0) {
    SIN_USO s32 temporal_a0;
    s32 variable_a1;
    SIN_USO s32 variable_s0;
    s32 variable_s1;
    SIN_USO s8** variable_s2;

    if (parametro0->state == 0) {
        display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x0000013F, 0x000000EF, 0, 0, 0, parametro0->param1);
        fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_2);
        gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, (parametro0->param1 * 0xFF) / 100);
        imprimir_modo_centro_texto1_2(0x000000A0, parametro0->row + 0x1E, dato_800E7778[seleccion_modo / 3], 0, 1.0f, 1.0f);
    } else {
        display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x0000013F, 0x000000EF, 0, 0, 0, 0x00000064);
        fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_2);
        imprimir_modo_centro_texto1_1(0x000000A0, parametro0->row + 0x1E, dato_800E7778[seleccion_modo / 3], 0, 1.0f, 1.0f);
    }
    switch (parametro0->state) { /* irregular */
        default:
            variable_a1 = 0x000000FF;
            break;
        case 0:
        case 1:
            variable_a1 = 0;
            break;
        case 2:
            variable_a1 = parametro0->param1;
            break;
    }
    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, variable_a1);
    switch (cantidad_jugador) {
        case 2:
            funcion_800A69C8(parametro0);
            break;
        case 3:
            funcion_800A6BEC(parametro0);
            break;
        case 4:
            funcion_800A6CC0(parametro0);
            break;
        default:
            break;
    }
    if (parametro0->state >= 10) {
        for (variable_s1 = 0; variable_s1 < 4; variable_s1++) {
            efecto_rainbow_texto(parametro0->state - 0xA, variable_s1, VERDE_TEXTO);
            imprimir_modo_texto_1(0x00000069, 0xAE + (0xF * variable_s1), boton_pausa_texto[variable_s1 + 1], 0, 0.8f, 0.8f);
        }
        funcion_800A66A8(parametro0, &dato_800E7360[parametro0->state - 10]);
    }
}

void funcion_800A66A8(MenuItem* parametro0, desconocido_d_800E70A0* parametro1) {
    Mtx* mtx;
    f32 tmp;
    static float x2, y2, z2;
    static float x1, y1, z1;

    mtx = &gfx_pool->efecto_mtx[cantidad_efecto_matriz];
    if (parametro0->paramf > 1.5) {
        parametro0->paramf *= 0.95;
    } else {
        parametro0->paramf = 1.5;
    }

    tmp = parametro0->paramf;
    x1 = (tmp * 3) * parametro0->estado_sub;
    y1 = tmp * 4;
    z1 = tmp * 2;
    x2 += x1;
    y2 += y1;
    z2 += z1;

    if (x2) {}; if (y2) {}; if (z2) {};

    guScale(mtx, 1.2f, 1.2f, 1.2f);
    guRotate(mtx + 1, y2, 0.0f, 1.0f, 0.0f);
    guMtxCatL(mtx, mtx + 1, mtx);
    guRotate(mtx + 1, z2, 0.0f, 0.0f, 1.0f);
    guMtxCatL(mtx, mtx + 1, mtx);
    guRotate(mtx + 1, x2, 1.0f, 0.0f, 0.0f);
    guMtxCatL(mtx, mtx + 1, mtx);
    guTranslate(mtx + 1, parametro1->column, parametro1->row, 0.0f);
    guMtxCatL(mtx, mtx + 1, mtx);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->efecto_mtx[cantidad_efecto_matriz++]),
              (G_MTX_NOPUSH | G_MTX_LOAD) | G_MTX_MODELVIEW);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPNoOp(display_list_cabeza++);
    gDPSetRenderMode(display_list_cabeza++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    gSPDisplayList(display_list_cabeza++, dato_0D003090);
}

void funcion_800A69C8(SIN_USO MenuItem* parametro0) {
    desconocido_d_800E70A0* cosa;
    SIN_USO s32 margen_pila_1;
    s32 variable_s0;
    char sp74[5];
    s32 variable_v1;
    char* temporal_s3;
    u8* variable_s4;

    for (variable_s0 = 0; variable_s0 < cantidad_jugador; variable_s0++) {
        variable_v1 = 0;
        cosa = &dato_800E7300[variable_s0];
        switch (seleccion_modo) { /* irregular */
            case VERSUS:
                if (gp_actual_carrera_puesto_por_id_jugador[variable_s0] != 0) {
                    variable_v1 = 1;
                }
                variable_s4 = &nmi_g_versus_resultados_2_p[variable_s0];
                break;
            case BATALLA:
                if (variable_s0 != indice_ganador_jugador) {
                    variable_v1 = 1;
                }
                variable_s4 = &desconocido_nmi_4[variable_s0];
                break;
        }
        temporal_s3 = texto_perder_victoria[variable_v1];
        if (variable_v1 != 0) {
            fijar_color_texto(AZUL_TEXTO);
        } else {
            fijar_color_texto((s32) temporizador_global % 3);
        }
        funcion_800A79F4(variable_s4[0], sp74);
        dibujar_texto(cosa->column + 0x10, cosa->row + 0x75, sp74, 0, 1.0f, 1.0f);
        imprimir_modo_centro_texto1_2(dato_800E7380[variable_s0].column, dato_800E7380[variable_s0].row, temporal_s3, 0, 0.65f, 1.0f);
    }
    fijar_color_texto(AZUL_TEXTO);
    dibujar_texto(0x0000009E, dato_800E7300[0].row + 0x6D, "ー", 0, 1.0f, 1.0f);
}

void funcion_800A6BEC(SIN_USO MenuItem* parametro0) {
    s32 variable_s0;

    for (variable_s0 = 0; variable_s0 < cantidad_jugador; variable_s0++) {
        switch (seleccion_modo) { /* irregular */
            case VERSUS:
                funcion_800A6E94(3, variable_s0, nmi_g_versus_resultados_3_p);
                break;
            case BATALLA:
                funcion_800A6D94(3, variable_s0, desconocido_nmi_5);
                break;
        }
    }
}

void funcion_800A6CC0(SIN_USO MenuItem* parametro0) {
    s32 variable_s0;

    for (variable_s0 = 0; variable_s0 < cantidad_jugador; variable_s0++) {
        switch (seleccion_modo) { /* irregular */
            case VERSUS:
                funcion_800A6E94(4, variable_s0, nmi_g_versus_resultados_4_p);
                break;
            case BATALLA:
                funcion_800A6D94(4, variable_s0, desconocido_nmi_6);
                break;
        }
    }
}

void funcion_800A6D94(s32 parametro0, s32 parametro1, u8* parametro2) {
    SIN_USO s32 margen_pila_0;
    desconocido_d_800E70A0* margen_pila_1;
    char sp30[5];
    s32 variable_v0;
    f32 otro_cosa;
    s32 cosa;

    variable_v0 = 0;
    if (parametro1 != indice_ganador_jugador) {
        variable_v0 = 1;
    }
    cosa = parametro2[parametro1];
    if (variable_v0 != 0) {
        fijar_color_texto(AZUL_TEXTO);
    } else {
        fijar_color_texto(temporizador_global % 3);
    }
    margen_pila_1 = &dato_800E7300[((parametro0 - 2) * 4) + parametro1];
    funcion_800A79F4(cosa, sp30);
    otro_cosa = 0.75f;
    dibujar_texto((margen_pila_1->column + 0x20) - ((32.0f * otro_cosa) / 2), margen_pila_1->row + 0x75, sp30, 0, 0.75f,
              0.75f);
}

void funcion_800A6E94(s32 jugador_cantidad, s32 id_jugador, u8* colocar_ary) {
    SIN_USO s32 margen_pila_0;
    u8* temporal_v0;
    desconocido_d_800E70A0* temporal_s0;
    char sp40[3];
    s32 puesto;
    s32 idx_puesto = -1;

    temporal_s0 = &dato_800E7300[((jugador_cantidad - 2) * 4) + id_jugador];
    puesto = gp_actual_carrera_puesto_por_id_jugador[id_jugador];
    if (puesto == ++idx_puesto) {
        fijar_color_texto(temporizador_global % 3);
    } else {
        fijar_color_texto(AMARILLO_TEXTO);
    }
    dibujar_texto(temporal_s0->column + 4, temporal_s0->row + 0x5A, "1 ｓ ー", 0, 0.8f, 0.8f);
    temporal_v0 = colocar_ary + (id_jugador * 3);
    convertir_numero_a_ascii(temporal_v0[0], sp40);
    dibujar_texto(temporal_s0->column + 0x2D, temporal_s0->row + 0x5A, sp40, 0, 0.8f, 0.8f);
    if (puesto == ++idx_puesto) {
        fijar_color_texto(temporizador_global % 3);
    } else {
        fijar_color_texto(AZUL_TEXTO);
    }
    dibujar_texto(temporal_s0->column + 4, temporal_s0->row + 0x69, "2 ｎ ー", 0, 0.8f, 0.8f);
    convertir_numero_a_ascii(temporal_v0[1], sp40);
    dibujar_texto(temporal_s0->column + 0x2D, temporal_s0->row + 0x69, sp40, 0, 0.8f, 0.8f);
    if (++idx_puesto == puesto) {
        fijar_color_texto(temporizador_global % 3);
    } else {
        fijar_color_texto(TEXTO_ROJO);
    }
    dibujar_texto(temporal_s0->column + 4, temporal_s0->row + 0x78, "3 ｒ ー", 0, 0.8f, 0.8f);
    convertir_numero_a_ascii(temporal_v0[2], sp40);
    dibujar_texto(temporal_s0->column + 0x2D, temporal_s0->row + 0x78, sp40, 0, 0.8f, 0.8f);
}

void funcion_800A70E8(MenuItem* parametro0) {
    s32 variable_s0;
    s32 temporal_f6;
    s32 alpha;
    s32 indice_bucle;
    s32 indice_cadena;

    if (parametro0->state == 1) {
        variable_s0 = obtener_ancho_cadena(dato_800E7A34[0]) * 0.45f;
        temporal_f6 = obtener_ancho_cadena(dato_800E7A34[1]) * 0.45f;
        if (variable_s0 < temporal_f6) {
            variable_s0 = temporal_f6;
        }
        display_list_cabeza =
            dibujar_caja(display_list_cabeza, 0x000000C0, 0x00000022, variable_s0 + 0xC6, 0x00000039, 0, 0, 0, 0x00000096);
        alpha = 0x180 - ((parametro0->param1 % 32) * 8);
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, alpha);
        fijar_color_texto(TEXTO_ROJO);
        for (indice_bucle = 0x2C, indice_cadena = 0; indice_bucle < 0x40; indice_bucle += 0xA, indice_cadena++) {
            imprimir_modo_texto_2(0x000000C0, indice_bucle, dato_800E7A34[indice_cadena], 0, 0.45f, 0.45f);
        }
    }
}

void funcion_800A7258(MenuItem* parametro0) {
    if (parametro0->state == 0) {
        display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x13F, 0xEF, 0, 0, 0, parametro0->param1);
    } else {
        display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x13F, 0xEF, 0, 0, 0, 0x64);
    }
}

void funcion_800A72FC(MenuItem* parametro0) {
    SIN_USO s32 relleno;
    s32 longitud_nombre_copa = (((f32) obtener_ancho_cadena(nombres_copa[seleccion_copa]) * 1) + 10) / 2;
    s32 longitud_nombre_cc = (((f32) obtener_ancho_cadena(dato_800E76CC[seleccion_cc]) * 1) + 10) / 2;

    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_centro_texto1_1(parametro0->column - longitud_nombre_cc, parametro0->row, nombres_copa[seleccion_copa], 0, 1, 1);
    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_centro_texto1_1(parametro0->column + longitud_nombre_copa, parametro0->row, dato_800E76DC[seleccion_cc], 0, 1, 1);
}

void funcion_800A7448(MenuItem* parametro0) {
    SIN_USO s32 relleno;
    s32 sp40;
    s32 sp3_c;
    s32 cosa = dato_802874D8.desconocido_1d;
    if (cosa >= 3) {
        fijar_color_texto(AMARILLO_TEXTO);
        imprimir_modo_centro_texto1_1(parametro0->column, parametro0->row, dato_800E7A98, 0, 0.75f, 0.75f);
    } else {
        sp40 = (s32) (((f32) (obtener_ancho_cadena(dato_800E7A88[0]) + 5) * 0.75f) / 2);
        sp3_c = (s32) (((f32) (obtener_ancho_cadena(dato_800E7A88[cosa + 1]) + 5) * 0.75f) / 2);
        fijar_color_texto(AMARILLO_TEXTO);
        imprimir_modo_centro_texto1_1(parametro0->column - sp3_c, parametro0->row, dato_800E7A88[0], 0, 0.75f, 0.75f);
        fijar_color_texto(AMARILLO_TEXTO);
        imprimir_modo_centro_texto1_1(parametro0->column + sp40, parametro0->row, dato_800E7A88[cosa + 1], 0, 0.75f, 0.75f);
    }
}

void funcion_800A75A0(MenuItem* parametro0) {
    SIN_USO s32 relleno;
    s32 arriba_tres;

    if (dato_802874D8.desconocido_1d < 3) {
        arriba_tres = 0;
    } else {
        arriba_tres = 1;
    }

    fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_1);
    imprimir_modo_centro_texto1_1(parametro0->column, parametro0->row, dato_800E7A9C[arriba_tres], 0, 1.3f, 1.3f);
}

void funcion_800A761C(MenuItem* parametro0) {
    SIN_USO s32 margen_pila_0;
    s32 sp48;
    s32 sp44;
    SIN_USO s32 margen_pila_1;
    char sp3_c[3];
    s32 temporal_a0;

    temporal_a0 = dato_802874D8.desconocido_1d + 1;
    funcion_800A79F4(temporal_a0, sp3_c);
    sp48 = ((obtener_ancho_cadena(texto_lugar[0]) + 5) * 1.2f) / 2;
    sp44 = ((obtener_ancho_cadena(texto_lugar[temporal_a0]) + 5) * 1.2f) / 2;
    fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_2);
    imprimir_modo_centro_texto1_1(parametro0->column - sp44, parametro0->row, texto_lugar[0], 0, 1.2f, 1.2f);
    fijar_color_texto((s32) temporizador_global % 3);
    imprimir_modo_centro_texto1_1(parametro0->column + sp48, parametro0->row, texto_lugar[temporal_a0], 0, 1.2f, 1.2f);
    convertir_numero_a_ascii(temporal_a0, sp3_c);
    funcion_800939C8((parametro0->column + sp48) - 0x18, parametro0->row, &sp3_c[1], 0, 2.0f, 2.0f);
}

void renderizar_creditos_item_menu(MenuItem* parametro0) {
    f32 algun_escalado;
    s32 indice_credit;
    s8 deslizar_sentido;
    SIN_USO s32 relleno;
    indice_credit = parametro0->type - 0x190;
    fijar_color_texto(creditos_texto_render_info[indice_credit].color_texto);
    deslizar_sentido = creditos_texto_render_info[indice_credit].sentido_deslizamiento;
    if ((deslizar_sentido == DERECHA_DESLIZAMIENTO) || (deslizar_sentido != IZQUIERDA_DESLIZAMIENTO)) {
        algun_escalado = creditos_texto_render_info[indice_credit].escalado_texto;
        imprimir_izquierda_texto1(parametro0->column, parametro0->row, texto_creditos[indice_credit], parametro0->param1 * algun_escalado,
                         parametro0->paramf * algun_escalado, algun_escalado);
    } else {
        algun_escalado = creditos_texto_render_info[indice_credit].escalado_texto;
        imprimir_modo_texto_1(parametro0->column, parametro0->row, texto_creditos[indice_credit], parametro0->param1 * algun_escalado,
                          parametro0->paramf * algun_escalado, algun_escalado);
    }
}

void convertir_numero_a_ascii(s32 numero, char* buffer) {
    buffer[0] = (numero / 0xA) + 0x30;
    buffer[1] = (numero % 0xA) + 0x30;
    buffer[2] = 0;
}

void escribir_guiones(char* buffer) {
    buffer[0] = 0x2D;
    buffer[1] = 0x2D;
    buffer[2] = '\0';
}

void obtener_minutos_registro_tiempo(s32 registro_tiempo, char* buffer) {
    if (registro_tiempo >= TIEMPO_MAX) {
        escribir_guiones(buffer);
        return;
    }
    convertir_numero_a_ascii(registro_tiempo / 0x1770, buffer);
}

void obtener_segundos_registro_tiempo(s32 registro_tiempo, char* buffer) {
    if (registro_tiempo >= TIEMPO_MAX) {
        escribir_guiones(buffer);
        return;
    }
    convertir_numero_a_ascii((registro_tiempo / 0x64) % 0x3C, buffer);
}

void obtener_centesimas_registro_tiempo(s32 registro_tiempo, char* buffer) {
    if (registro_tiempo >= TIEMPO_MAX) {
        escribir_guiones(buffer);
        return;
    }
    convertir_numero_a_ascii(registro_tiempo % 0x64, buffer);
}

void funcion_800A79F4(s32 parametro0, char* parametro1) {
    parametro1[0] = 0xA3;
    parametro1[1] = (parametro0 / 0xA) - 0x50;
    parametro1[2] = 0xA3;
    parametro1[3] = (parametro0 % 0xA) - 0x50;
    parametro1[4] = '\0';
}
