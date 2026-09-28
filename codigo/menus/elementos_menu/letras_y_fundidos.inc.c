// Letras y fundidos

Gfx* imprimir_letra(Gfx* parametro0, TexturaMenu* textura_glifo, f32 parametro2, f32 parametro3, s32 mode, f32 escalar_x, f32 escalar_y) {
    s32 variable_v0;
    u8* temporal_v0_2;
    f32 cosa0;
    f32 cosa1;
    TexturaMenu* variable_s0;
    s32 letra_dibujada = 0;

    variable_s0 = segmentado_a_duplicado_virtual(textura_glifo);
    while (variable_s0->textura_datos != NULL) {
        // El signo de una letra del espanol va encima de la letra que se acaba de dibujar
        if (variable_s0->height == ALTO_DIACRITICO) {
            temporal_v0_2 = (u8*) funcion_8009B8C4(variable_s0->textura_datos);
            if (letra_dibujada && (temporal_v0_2 != NULL)) {
                parametro0 = dibujar_diacritico_glifo(parametro0, temporal_v0_2);
            }
            variable_s0++;
            continue;
        }
        variable_v0 = 0;
        letra_dibujada = 0;

        cosa0 = variable_s0->d_x + parametro2;
        if (cosa0 > 320.0f) {
            variable_v0 = 1;
        }
        cosa0 += variable_s0->width * escalar_x;
        if (cosa0 < 0.0f) {
            variable_v0 += 1;
        }
        cosa1 = variable_s0->d_y + parametro3;
        if (cosa1 < 0.0f) {
            variable_v0 += 1;
        }
        cosa1 -= variable_s0->height * escalar_y;
        if (cosa1 > 240.0f) {
            variable_v0 += 1;
        }

        if (variable_v0 != 0) {
            variable_s0++;
        } else {
            temporal_v0_2 = (u8*) funcion_8009B8C4(variable_s0->textura_datos);
            if (temporal_v0_2 != 0) {
                switch (mode) { /* irregular */
                    case 1:
                        gSPDisplayList(parametro0++, dato_020077F8);
                        parametro0 = funcion_80095BD0(parametro0, temporal_v0_2, variable_s0->d_x + parametro2, variable_s0->d_y + parametro3, variable_s0->width,
                                             variable_s0->height, escalar_x, escalar_y);
                        break;
                    case 2:
                        gSPDisplayList(parametro0++, dato_02007818);
                        parametro0 = funcion_80095BD0(parametro0, temporal_v0_2, variable_s0->d_x + parametro2, variable_s0->d_y + parametro3, variable_s0->width,
                                             variable_s0->height, escalar_x, escalar_y);
                        break;
                }
                letra_dibujada = 1;
            }
            variable_s0++;
        }
    }
    return parametro0;
}

Gfx* funcion_8009C204(Gfx* parametro0, TexturaMenu* parametro1, s32 parametro2, s32 parametro3, s32 parametro4) {
    s32 variable_s2;
    u8* temporal_t0;
    TexturaMenu* variable_s1;

    variable_s1 = segmentado_a_duplicado_virtual(parametro1);
    while (variable_s1->textura_datos != NULL) {
        variable_s2 = 0;
        switch (variable_s1->type) {
            case 0:
                gSPDisplayList(parametro0++, dato_02007708);
                break;
            case 1:
                gSPDisplayList(parametro0++, dato_02007728);
                break;
            case 3:
                gSPDisplayList(parametro0++, dato_02007768);
                variable_s2 = 3;
                break;
            default:
                gSPDisplayList(parametro0++, dato_02007728);
                break;
        }
        temporal_t0 = (u8*) funcion_8009B8C4(variable_s1->textura_datos);
        switch (parametro4) {
            case 2:
                parametro0 =
                    funcion_800963F0(parametro0, variable_s2, 0x00000400, 0x00000400, 0.5f, 0.5f, 0, 0, variable_s1->width, variable_s1->height,
                                  variable_s1->d_x + parametro2, variable_s1->d_y + parametro3, temporal_t0, variable_s1->width, variable_s1->height);
                break;
            case 3:
                parametro0 = funcion_800963F0(parametro0, variable_s2, 0x00000400, 0x00000400, 0.457f, 0.5f, 0, 0, variable_s1->width,
                                     variable_s1->height, variable_s1->d_x + parametro2, variable_s1->d_y + parametro3, temporal_t0, variable_s1->width,
                                     variable_s1->height);
                break;
        }
        variable_s1++;
    }
    return parametro0;
}

Gfx* funcion_8009C434(Gfx* parametro0, struct_8018DEE0_entrada* parametro1, s32 parametro2, s32 parametro3, s32 parametro4) {
    s32 variable_t0;
    s32 variable_t1;
    Gfx* temporal_;
    TexturaMenu* variable_s0;

    variable_s0 = segmentado_a_duplicado_virtual(parametro1->textura_secuencia[parametro1->indice_secuencia].textura_mk64);
    temporal_ = dato_02007728;
    while (variable_s0->textura_datos != NULL) {
        variable_t1 = 0;
        switch (variable_s0->type) { /* irregular */
            default:
                gSPDisplayList(parametro0++, temporal_);
                break;
            case 0:
                gSPDisplayList(parametro0++, dato_02007708);
                break;
            case 1:
                gSPDisplayList(parametro0++, temporal_);
                break;
            case 3:
                gSPDisplayList(parametro0++, dato_02007768);
                variable_t1 = 3;
                break;
        }
        if (parametro1->unk14 != 0) {
            variable_t0 = mapa_textura_menu[parametro1->indice_textura_menu + 1].offset;
        } else {
            variable_t0 = mapa_textura_menu[parametro1->indice_textura_menu].offset;
            if (1) {}
            if (1) {}
            if (1) {}
        }
        if (parametro4 >= 0) {
            parametro0 =
                funcion_80097E58(parametro0, variable_t1, 0, 0U, variable_s0->width, variable_s0->height, variable_s0->d_x + parametro2, variable_s0->d_y + parametro3,
                              (u8*) &buffer_textura_menu[variable_t0], variable_s0->width, variable_s0->height, (u32) parametro4);
        } else {
            switch (parametro4) {
                case -1:
                    parametro0 = funcion_80095E10(parametro0, variable_t1, 0x00000400, 0x00000400, 0, 0, variable_s0->width, variable_s0->height,
                                         variable_s0->d_x + parametro2, variable_s0->d_y + parametro3, (u8*) &buffer_textura_menu[variable_t0],
                                         variable_s0->width, variable_s0->height);
                    break;
                case -2:
                    parametro0 = funcion_800963F0(parametro0, variable_t1, 0x00000400, 0x00000400, 0.5f, 0.5f, 0, 0, variable_s0->width,
                                         variable_s0->height, variable_s0->d_x + parametro2, variable_s0->d_y + parametro3,
                                         (u8*) &buffer_textura_menu[variable_t0], variable_s0->width, variable_s0->height);
                    break;
            }
        }
        variable_s0++;
    }
    return parametro0;
}

Gfx* funcion_8009C708(Gfx* parametro0, struct_8018DEE0_entrada* parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5) {
    s32 variable_t0;
    SIN_USO s32 cosa;
    Gfx* temporal_;
    TexturaMenu* variable_s1;

    variable_s1 = segmentado_a_duplicado_virtual(parametro1->textura_secuencia[parametro1->indice_secuencia].textura_mk64);
    temporal_ = dato_02007728;
    while (variable_s1->textura_datos != NULL) {
        variable_t0 = 0;
        switch (variable_s1->type) { /* irregular */
            case 0:
                gSPDisplayList(parametro0++, dato_02007708);
                break;
            case 1:
                gSPDisplayList(parametro0++, temporal_);
                break;
            case 2:
                gSPDisplayList(parametro0++, dato_02007748);
                break;
            case 3:
                gSPDisplayList(parametro0++, dato_02007768);
                variable_t0 = 3;
                break;
            default:
                gSPDisplayList(parametro0++, temporal_);
                break;
        }
        if (parametro5 >= 0) {
            parametro0 =
                funcion_80097E58(parametro0, variable_t0, 0, 0U, variable_s1->width, variable_s1->height, variable_s1->d_x + parametro2, variable_s1->d_y + parametro3,
                              dato_802BFB80.tamanio_arreglo_4[parametro1->unk14][parametro4 / 2][(parametro4 % 2) + 2].arreglo_indice_pixel,
                              variable_s1->width, variable_s1->height, (u32) parametro5);
        }
        variable_s1++;
    }
    return parametro0;
}

void funcion_8009C918(void) {
    s32 algun_indice;

    for (algun_indice = 0; algun_indice < 4; algun_indice++) {
        dato_8018E7E8[algun_indice].x = dato_8015F480[algun_indice].inicio_x_pantalla;
        dato_8018E7E8[algun_indice].y = dato_8015F480[algun_indice].inicio_y_pantalla;
        dato_8018E810[algun_indice].x = dato_8015F480[algun_indice].ancho_pantalla;
        dato_8018E810[algun_indice].y = dato_8015F480[algun_indice].altura_pantalla;
    }

    dato_8018E7E8[4].x = 0x00A0;
    dato_8018E7E8[4].y = 0x0078;
    dato_8018E810[4].x = 0x0140;
    dato_8018E810[4].y = 0x00F0;
}

void funcion_8009CA2C(void) {
    s32 variable_s0;

    for (variable_s0 = 0; variable_s0 < 5; variable_s0++) {
        funcion_8009CA6C(variable_s0);
    }
}

void funcion_8009CA6C(s32 parametro0) {
    s32 variable_a1;

    if ((parametro0 == 4) || ((buscar_items_menu(0x000000AA) == NULL) && (buscar_items_menu(0x000000AB) == NULL) &&
                        (buscar_items_menu(0x000000B9) == NULL) && (buscar_items_menu(0x000000BA) == NULL) &&
                        (buscar_items_menu(0x000000AC) == NULL) && (buscar_items_menu(0x000000B0) == NULL))) {
        variable_a1 = 0;
        gSPDisplayList(display_list_cabeza++, dato_0D0076F8);
        if ((parametro0 != 4) && (juego_en_pausa != 0)) {
            variable_a1 = 1;
        }
        switch (tipo_transicion[parametro0]) {
            case 1:
                dibujar_fundido_negro_en(parametro0, variable_a1);
                return;
            case 2:
                funcion_8009D958(parametro0, variable_a1);
                return;
            case 3:
                funcion_8009DB8C();
                return;
            case 4:
                funcion_8009DAA8();
                return;
            case 5:
                funcion_8009D998(parametro0);
                return;
            case 7:
                funcion_8009D978(parametro0, variable_a1);
                return;
            case 8:
                dibujar_fundido_blanco_en(parametro0, variable_a1);
                break;
            case 0:
            default:
                break;
        }
    }
}

void dibujar_fundido_en(s32 parametro0, s32 parametro1, s32 parametro2) {
    RGBA16* color;
    s16 x, y, w, h;
    SIN_USO s32 relleno[3];
    struct desconocido_struct_800DC5EC* desconocido;
    struct desconocido_struct_8018E7E8 *size, *empezar;

    if ((seleccion_modo == GRAN_PREMIO) || (seleccion_modo == CONTRARRELOJ)) {
        empezar = &(dato_8018E7E8[parametro0]);
        size = &(dato_8018E810[parametro0]);
        x = empezar->x;
        y = empezar->y;
        w = size->x;
        h = size->y;
    } else if (parametro0 >= 4) {
        empezar = &(dato_8018E7E8[parametro0]);
        size = &(dato_8018E810[parametro0]);
        x = empezar->x;
        y = empezar->y;
        w = size->x;
        h = size->y;
    } else {
        desconocido = &dato_8015F480[parametro0];
        x = desconocido->inicio_x_pantalla;
        y = desconocido->inicio_y_pantalla;
        w = desconocido->ancho_pantalla;
        h = desconocido->altura_pantalla;
    }
    color = &dato_800E7AE8[parametro2];
    display_list_cabeza =
        dibujar_caja(display_list_cabeza, x - (w / 2), y - (h / 2), (w / 2) + x, (h / 2) + y, color->rojo, color->verde,
                 color->azul, 0xFF - (tiempo_transicion_actual[parametro0] * 0xFF / duracion_transicion[parametro0]));

    if ((parametro1 == 0) &&
        (tiempo_transicion_actual[parametro0] += 1, (tiempo_transicion_actual[parametro0] >= duracion_transicion[parametro0]))) {
        if (estado_juego == CARRERA) {
            tipo_transicion[parametro0] = 6;
            return;
        }
        tipo_transicion[parametro0] = 0;
        sin_ref_8018EE0C = 0;
    }
}

void dibujar_fundido_negro_en(s32 parametro0, s32 parametro1) {
    dibujar_fundido_en(parametro0, parametro1, 0);
}

void dibujar_fundido_blanco_en(s32 parametro0, s32 parametro1) {
    dibujar_fundido_en(parametro0, parametro1, 1);
}

void funcion_8009CE1C(void) {
    if ((sonido_modo != 3) && (seleccion_cantidad_jugador_1 >= 2)) {
        funcion_800C3448(0xE0000002);
    }
}

void funcion_8009CE64(s32 parametro0) {
    s32 cosa;
    s32 variable_a1;
    SIN_USO s32 margen_pila_0;
    MenuItem* temporal_v0;

    variable_a1 = 0;
    if (estado_juego == 5) {
        if (2 != seleccion_cc) {
            cosa = seleccion_cc;
            if (cosa != 3) {
                goto func_8009CE64_etiqueta_1;
            }
            goto func_8009CE64_etiqueta_2;
        }
    func_8009CE64_etiqueta_2:
        if ((dato_802874D8.desconocido_1d < 3) && (seleccion_copa == 3)) {
            variable_a1 = 1;
        }
    func_8009CE64_etiqueta_1:
        if (variable_a1) {
            goto_menu = 9;
            id_circuito_creditos = 8;
        } else {
            goto_menu = 1;
            seleccion_menu = 0x0000000B;
        }
    } else if (estado_juego == CARRERA) {
        if (tipo_transicion[parametro0] == 2) {
            if (parametro0 != 4) {
                tipo_transicion[parametro0] = 5;
            } else {
                variable_a1 = 0;
                temporal_v0 = buscar_items_menu(0x000000B0);
                if (temporal_v0 != NULL) {
                    switch (temporal_v0->state) {
                        case 10:
                            funcion_802903B0();
                            break;
                        case 11:
                            funcion_80290388();
                            break;
                        case 12:
                            funcion_80290360();
                            break;
                        default:
                        case 13:
                            funcion_80290338();
                            break;
                    }
                } else {
                    variable_a1 = 0;
                    temporal_v0 = buscar_items_menu(0x000000AC);
                    if (temporal_v0 != NULL) {
                        switch (temporal_v0->state) {
                            case 11:
                                funcion_802903B0();
                                dato_8016556E = 1;
                                break;
                            default:
                            case 12:
                                funcion_80290338();
                                break;
                        }
                    } else {
                        variable_a1 = 0;
                        temporal_v0 = buscar_items_menu(0x000000C7);
                        if (temporal_v0 != NULL) {
                            switch (temporal_v0->state) {
                                case 12:
                                    funcion_802903B0();
                                    variable_a1 = 1;
                                    break;
                                case 13:
                                case 22:
                                case 42:
                                    funcion_80290388();
                                    variable_a1 = 1;
                                    break;
                                case 14:
                                case 23:
                                case 43:
                                    funcion_80290360();
                                    variable_a1 = 1;
                                    break;
                                case 15:
                                case 24:
                                case 32:
                                case 44:
                                    funcion_80290338();
                                    variable_a1 = 1;
                                    break;
                                default:
                                    tipo_transicion[parametro0] = 5;
                                    break;
                            }
                            if (variable_a1 != 0) {
                                juego_en_pausa = 0;
                            }
                        }
                        temporal_v0 = buscar_items_menu(0x000000BD);
                        if (temporal_v0 != NULL) {
                            switch (temporal_v0->state) {
                                case 11:
                                    dato_8015F892 = 1;
                                    dato_8015F890 = 0;
                                    funcion_802903B0();
                                    break;
                                case 12:
                                    dato_8015F892 = 0;
                                    dato_8015F890 = 0;
                                    funcion_80290388();
                                    break;
                                case 13:
                                    dato_8015F892 = 0;
                                    dato_8015F890 = 0;
                                    funcion_80290360();
                                    break;
                                case 14:
                                    dato_8015F892 = 0;
                                    dato_8015F890 = 0;
                                    funcion_80290338();
                                    break;
                                case 15:
                                    dato_8015F892 = 0;
                                    dato_8015F890 = 1;
                                    funcion_802903B0();
                                    break;
                                default:
                                    break;
                            }
                        } else {
                            tipo_transicion[parametro0] = 5;
                        }
                    }
                }
            }
        }
    } else {
        tipo_transicion[parametro0] = 0;
        if (seleccion_menu_depuracion != DEPURACION_MENU_OPCION_SELECCIONADO) {
            switch (tipo_fundido_menu) {
                case MENU_FUNDIDO_TIPO_PRINCIPAL:
                    if (seleccion_menu == LOGO_INTRO_MENU) {
                        seleccion_menu = MENU_INICIO;
                        seleccion_modo_fundido = LOGO_MODO_FUNDIDO;
                    } else {
                        seleccion_menu++;
                    }
                    break;
                case MENU_FUNDIDO_TIPO_ATRAS:
                    seleccion_menu -= 1;
                    break;
                case MENU_FUNDIDO_TIPO_DEMO:
                    modo_demo = 1;
                    mando_usar_demo = 1;
                    siguiente_estado_juego = 4;
                    seleccion_cc = (s32) 1;
                    switch (id_demo_siguiente) {
                        case 0:
                            id_circuito_actual = CIRCUITO_MARIO_RACEWAY;
                            seleccion_modo_pantalla = 0;
                            seleccion_cantidad_jugador_1 = 1;
                            cantidad_jugador = 1;
                            selecciones_personaje[0] = 0;
                            seleccion_modo = 0;
                            break;
                        case 1:
                            id_circuito_actual = CIRCUITO_CHOCO_MOUNTAIN;
                            seleccion_modo_pantalla = (s32) 1;
                            seleccion_cantidad_jugador_1 = 2;
                            cantidad_jugador = (s8) 2;
                            selecciones_personaje[0] = (s8) 2;
                            selecciones_personaje[1] = (s8) 4;
                            seleccion_modo = 2;
                            break;
                        case 2:
                            id_circuito_actual = CIRCUITO_KALAMARI_DESERT;
                            seleccion_modo_pantalla = 0;
                            seleccion_cantidad_jugador_1 = (s32) 1;
                            cantidad_jugador = 1;
                            selecciones_personaje[0] = 1;
                            seleccion_modo = 0;
                            break;
                        case 3:
                            id_circuito_actual = CIRCUITO_WARIO_STADIUM;
                            seleccion_modo_pantalla = 3;
                            seleccion_cantidad_jugador_1 = 3;
                            cantidad_jugador = (s8) 3;
                            selecciones_personaje[0] = 5;
                            selecciones_personaje[1] = 2;
                            selecciones_personaje[2] = 7;
                            seleccion_modo = (s32) 2;
                            break;
                        case 4:
                            id_circuito_actual = CIRCUITO_BOWSER_CASTLE;
                            seleccion_modo_pantalla = 0;
                            seleccion_cantidad_jugador_1 = (s32) 1;
                            cantidad_jugador = 1;
                            selecciones_personaje[0] = 7;
                            seleccion_modo = 0;
                            break;
                        case 5:
                            id_circuito_actual = CIRCUITO_SHERBET_LAND;
                            seleccion_modo_pantalla = 3;
                            seleccion_cantidad_jugador_1 = 4;
                            cantidad_jugador = 4;
                            selecciones_personaje[0] = 0;
                            selecciones_personaje[1] = 1;
                            selecciones_personaje[2] = 6;
                            selecciones_personaje[3] = 3;
                            seleccion_modo = 2;
                            break;
                        default:
                            break;
                    }
                    id_demo_siguiente += 1;
                    if (id_demo_siguiente >= 6) {
                        id_demo_siguiente = 0;
                    }
                    seleccion_copa = seleccion_copa_por_id_circuito[id_circuito_actual];
                    dato_800DC540 = (s32) seleccion_copa;
                    indice_circuito_en_copa = (s8) por_indice_copa_por_id_circuito[id_circuito_actual];
                    break;
                case MENU_FUNDIDO_TIPO_DATOS:
                    switch (seleccion_menu) {
                        case 11:
                            seleccion_menu = 6;
                            break;
                        case 6:
                            seleccion_menu = 11;
                            break;
                    }
                    break;
                case MENU_FUNDIDO_TIPO_OPCION:
                    switch (seleccion_menu) {
                        case 11:
                            seleccion_menu = 5;
                            break;
                        case 5:
                            seleccion_menu = 11;
                            break;
                    }
                    break;
            }
            if (seleccion_modo_fundido == NINGUNO_MODO_FUNDIDO) {
                seleccion_modo_fundido = PRINCIPAL_MODO_FUNDIDO;
            }
            if (seleccion_menu >= 0xE) {
                siguiente_estado_juego = 4;
                if (seleccion_modo == 1) {
                    inicializacion_jugador_fantasma = (s8) 1;
                }
                funcion_8009CE1C();
            }
            sin_ref_8018EE0C = 0;
        } else {
            switch (escena_goto_depuracion) {
                case FINAL_GOTO_DEPURACION:
                    siguiente_estado_juego = (s32) 5;
                    break;
                case DEPURACION_GOTO_CREDITOS_SECUENCIA_PREDETERMINADO:
                case DEPURACION_GOTO_CREDITOS_SECUENCIA_EXTRA:
                    siguiente_estado_juego = 9;
                    id_circuito_creditos = 8;
                    break;
                default:
                    siguiente_estado_juego = 4;
                    if (seleccion_modo == (s32) 1) {
                        inicializacion_jugador_fantasma = 1;
                    }
                    break;
            }
            funcion_8000F124();
            if (seleccion_modo_pantalla == 3) {
                switch (seleccion_modo) {
                    case 0:
                    case 1:
                        seleccion_modo = 2;
                        break;
                }
            }
            switch (id_circuito_actual) {
                case CIRCUITO_BLOCK_FORT:
                case CIRCUITO_SKYSCRAPER:
                case CIRCUITO_DOUBLE_DECK:
                case CIRCUITO_BIG_DONUT:
                    seleccion_modo = 3;
                    if (seleccion_cantidad_jugador_1 == 1) {
                        cantidad_jugador = 2;
                        seleccion_modo_pantalla = 1;
                        seleccion_cantidad_jugador_1 = cantidad_jugador;
                    }
                    break;
                default:
                    if (seleccion_modo == 3) {
                        seleccion_modo = 0;
                    }
                    if ((seleccion_modo == 2) && (seleccion_cantidad_jugador_1 == 1)) {
                        seleccion_modo = 0;
                    }
            }
            seleccion_copa = seleccion_copa_por_id_circuito[id_circuito_actual];
            dato_800DC540 = seleccion_copa;
            indice_circuito_en_copa = por_indice_copa_por_id_circuito[id_circuito_actual];
            switch (escena_goto_depuracion) {
                case FINAL_GOTO_DEPURACION:
                    break;
                case DEPURACION_GOTO_CREDITOS_SECUENCIA_PREDETERMINADO:
                    seleccion_cc = 0;
                    break;
                case DEPURACION_GOTO_CREDITOS_SECUENCIA_EXTRA:
                    seleccion_cc = 3;
                    break;
                default:
                    if (seleccion_cc == 3) {
                        es_modo_espejo = 1;
                    } else {
                        es_modo_espejo = 0;
                    }
                    break;
            }
        }
    }
}

void funcion_8009D77C(s32 parametro0, s32 parametro1, s32 parametro2) {
    s16 ra_variable;
    s16 variable_t3;
    s16 variable_t4;
    s32 temporal_t8;
    s32 temporal_v1;
    s32 variable_t2;
    s32 algun_matematica_0;
    s32 algun_matematica_1;
    RGBA16* temporal_v0_2;
    s32 sp44;
    SIN_USO s32 margen_pila_0;

    if ((seleccion_modo == 0) || (seleccion_modo == 1)) {
        variable_t3 = dato_8018E7E8[parametro0].x;
        variable_t4 = dato_8018E7E8[parametro0].y;
        ra_variable = dato_8018E810[parametro0].x;
        sp44 = dato_8018E810[parametro0].y;
    } else if (parametro0 >= 4) {
        variable_t3 = dato_8018E7E8[parametro0].x;
        variable_t4 = dato_8018E7E8[parametro0].y;
        ra_variable = dato_8018E810[parametro0].x;
        sp44 = dato_8018E810[parametro0].y;
    } else {
        variable_t3 = dato_8015F480[parametro0].inicio_x_pantalla;
        variable_t4 = dato_8015F480[parametro0].inicio_y_pantalla;
        ra_variable = dato_8015F480[parametro0].ancho_pantalla;
        sp44 = dato_8015F480[parametro0].altura_pantalla;
    }
    variable_t2 = (tiempo_transicion_actual[parametro0] * 0xFF) / duracion_transicion[parametro0];
    if (variable_t2 >= 0x100) {
        variable_t2 = 0x000000FF;
    }
    temporal_v1 = ra_variable / 2;
    temporal_t8 = sp44 / 2;
    temporal_v0_2 = &dato_800E7AE8[parametro2];
    algun_matematica_0 = temporal_v1;
    algun_matematica_0 += variable_t3;
    algun_matematica_1 = temporal_t8;
    algun_matematica_1 += variable_t4;
    display_list_cabeza = dibujar_caja(display_list_cabeza, variable_t3 - temporal_v1, variable_t4 - temporal_t8, algun_matematica_0, algun_matematica_1,
                                temporal_v0_2->rojo, temporal_v0_2->verde, temporal_v0_2->azul, variable_t2);
    if (parametro1 == 0) {
        tiempo_transicion_actual[parametro0]++;
        if ((duracion_transicion[parametro0] + 1) < tiempo_transicion_actual[parametro0]) {
            funcion_8009CE64(parametro0);
        }
    }
}

void funcion_8009D958(s32 parametro0, s32 parametro1) {
    funcion_8009D77C(parametro0, parametro1, 0);
}

void funcion_8009D978(s32 parametro0, s32 parametro1) {
    funcion_8009D77C(parametro0, parametro1, 1);
}

void funcion_8009D998(s32 parametro0) {
    s16 variable_t0;
    s16 variable_t1;
    s16 variable_t2;
    s16 variable_t3;
    s32 temporal_v0;
    s32 temporal_v1;
    s32 algun_matematica_0;
    s32 algun_matematica_1;

    if ((seleccion_modo == 0) || (seleccion_modo == 1)) {
        variable_t0 = dato_8018E7E8[parametro0].x;
        variable_t1 = dato_8018E7E8[parametro0].y;
        variable_t2 = dato_8018E810[parametro0].x;
        variable_t3 = dato_8018E810[parametro0].y;
    } else if (parametro0 >= 4) {
        variable_t0 = dato_8018E7E8[parametro0].x;
        variable_t1 = dato_8018E7E8[parametro0].y;
        variable_t2 = dato_8018E810[parametro0].x;
        variable_t3 = dato_8018E810[parametro0].y;
    } else {
        variable_t0 = dato_8015F480[parametro0].inicio_x_pantalla;
        variable_t1 = dato_8015F480[parametro0].inicio_y_pantalla;
        variable_t2 = dato_8015F480[parametro0].ancho_pantalla;
        variable_t3 = dato_8015F480[parametro0].altura_pantalla;
    }
    temporal_v0 = variable_t2 / 2;
    temporal_v1 = variable_t3 / 2;
    algun_matematica_0 = temporal_v0;
    algun_matematica_0 += variable_t0;
    algun_matematica_1 = temporal_v1;
    algun_matematica_1 += variable_t1;
    display_list_cabeza =
        dibujar_caja(display_list_cabeza, variable_t0 - temporal_v0, variable_t1 - temporal_v1, algun_matematica_0, algun_matematica_1, 0, 0, 0, 0x000000FF);
}

void funcion_8009DAA8(void) {
    u32 variable_t0;

    tiempo_transicion_actual[4]++;
    if (tiempo_transicion_actual[4] >= (duracion_transicion[4] + 1)) {
        funcion_8009CE64(4);
    }
    gDPPipeSync(display_list_cabeza++);
    variable_t0 = (tiempo_transicion_actual[4] * 255) / duracion_transicion[4];
    if ((s32) variable_t0 >= 0x100) {
        variable_t0 = 0x000000FF;
    }
    display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x00000140, 0x000000F0, 0, 0, 0, (s32) variable_t0);
}

void funcion_8009DB8C(void) {
    s32 temporal_t4;
    s32 temporal_t5;
    s32 variable_s0;
    u32 variable_s3;
    s32 variable_v1;

    tiempo_transicion_actual[4]++;
    variable_v1 = tiempo_transicion_actual[4];
    if ((u32) variable_v1 >= duracion_transicion[4]) {
        if ((u32) variable_v1 == duracion_transicion[4]) {
            for (variable_s0 = 0; variable_s0 < 0x4B0; variable_s0++) {
                tkmk_00_bajo_res_buffer[variable_s0] = 1;
            }
        } else {
            funcion_8009CE64(4);
        }
    } else {
        variable_s0 = 0;
        variable_s3 = 0;
        while (variable_s3 < (0x4B0U / duracion_transicion[4])) {
            if ((tkmk_00_bajo_res_buffer[variable_s0] == 0) &&
                (int_aleatorio((0x4B0U - tiempo_transicion_actual[4]) / duracion_transicion[4]) == 0)) {
                variable_s3 += 1;
                tkmk_00_bajo_res_buffer[variable_s0] = 1;
            }
            variable_s0 += 1;
            if (variable_s0 >= 0x4B0) {
                variable_s0 = 0;
            }
        }
    }
    gDPPipeSync(display_list_cabeza++);
    gDPSetRenderMode(display_list_cabeza++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, 0xFF);
    gDPSetCombineMode(display_list_cabeza++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    for (variable_s0 = 0; variable_s0 < 0x4B0; variable_s0++) {
        if (tkmk_00_bajo_res_buffer[variable_s0] != 0) {
            temporal_t4 = (variable_s0 % 40) * 8;
            temporal_t5 = (variable_s0 / 40) * 8;
            gDPFillRectangle(display_list_cabeza++, temporal_t4, temporal_t5, temporal_t4 + 8, temporal_t5 + 8);
        }
    }
    gDPPipeSync(display_list_cabeza++);
    variable_v1 = (tiempo_transicion_actual[4] * 255) / duracion_transicion[4];
    if (variable_v1 >= 0x100) {
        variable_v1 = 0x000000FF;
    }
    display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x00000140, 0x000000F0, 0, 0, 0, variable_v1);
}

void funcion_8009DEF8(u32 parametro0, u32 parametro1) {
    if (parametro0 == 0) {
        parametro0 = 1;
    }
    if ((tipo_transicion[4] != 1) && (tipo_transicion[4] != 6)) {
        tipo_transicion[4] = parametro1;
        duracion_transicion[4] = parametro0;
        if (duracion_transicion[4] >= 0x100U) {
            duracion_transicion[4] = 0xFFU;
        }
        dato_8018E7E0 = 0;
    }
}

void funcion_8009DF4C(s32 parametro0) {
    funcion_8009DEF8(parametro0, 1);
}

void funcion_8009DF6C(s32 parametro0) {
    funcion_8009DEF8(parametro0, 8);
}

void funcion_8009DF8C(u32 parametro0, u32 parametro1) {
    if (parametro0 == 0) {
        parametro0 = 1;
    }
    if ((tipo_transicion[4] != 2) && (tipo_transicion[4] != 5)) {
        tipo_transicion[4] = parametro1;
        duracion_transicion[4] = parametro0;
        if (duracion_transicion[4] >= 0x100U) {
            duracion_transicion[4] = 0xFFU;
        }
        dato_8018E7E0 = 0;
    }
}

void funcion_8009DFE0(s32 parametro0) {
    funcion_8009DF8C(parametro0, 2);
}

void funcion_8009E000(s32 parametro0) {
    funcion_8009DF8C(parametro0, 7);
}

void funcion_8009E020(s32 parametro0, s32 parametro1) {
    s32 temporal_;

    if (parametro1 == 0) {
        parametro1 = 1;
    }

    temporal_ = tipo_transicion[parametro0];
    if ((temporal_ != 1) && (temporal_ != 6)) {
        tipo_transicion[parametro0] = 1;
        duracion_transicion[parametro0] = parametro1;
        if ((u32) parametro1 >= 0x100U) {
            duracion_transicion[parametro0] = 0xFF;
        }
        tiempo_transicion_actual[parametro0] = 0;
    }
}

void funcion_8009E088(s32 parametro0, s32 parametro1) {
    s32 temporal_;

    if (parametro1 == 0) {
        parametro1 = 1;
    }

    temporal_ = tipo_transicion[parametro0];
    if ((temporal_ != 2) && (temporal_ != 5)) {
        tipo_transicion[parametro0] = 2;
        duracion_transicion[parametro0] = parametro1;
        if ((u32) parametro1 >= 0x100U) {
            duracion_transicion[parametro0] = 0xFF;
        }
        tiempo_transicion_actual[parametro0] = 0;
    }
}

void funcion_8009E0F0(s32 parametro0) {
    s32 variable_v0;

    if (tipo_transicion[4] != 3) {
        tipo_transicion[4] = 3;
        duracion_transicion[4] = parametro0;
        if (duracion_transicion[4] >= 0x100U) {
            duracion_transicion[4] = 0x000000FF;
        }
        dato_8018E7E0 = 0;
        for (variable_v0 = 0; variable_v0 < 0x4B0; variable_v0++) {
            tkmk_00_bajo_res_buffer[variable_v0] = 0;
        }
    }
}
