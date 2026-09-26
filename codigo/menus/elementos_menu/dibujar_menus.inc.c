// Dibujar menus

void renderizar_menus(MenuItem* parametro0) {
    s32 variable_a1;
    s32 variable_v1;
    SIN_USO s32 relleno[2];
    TexturaMenu* textura;
    s32 temporal_a0;
    s32 temporal_t2;
    s32 temporal_t5;
    s32 temporal_t9;
    s32 temporal_v1;
    SIN_USO s32 relleno2;
    char sp80[3];
    f32 por_que = 0.75f;
    s32 one = 1;
    SIN_USO s32 relleno3;

    if (parametro0->visible) {
        gDPPipeSync(display_list_cabeza++);
        switch (parametro0->type) {
            case MENU_ITEM_IU_LOGO_INTRO:
                funcion_80094660(gfx_pool, parametro0->param1);
                break;
            case MENU_INICIO_BANDERA:
                renderizar_bandera_a_cuadros(gfx_pool, parametro0->param1);
                break;
            case TIPO_ITEM_MENU_0D2:
                display_list_cabeza = funcion_8009B9D0(display_list_cabeza, dato_020014C8);
                break;
            case TIPO_ITEM_MENU_0D3:
                display_list_cabeza = funcion_8009B9D0(display_list_cabeza, dato_02001540);
                break;
            case TIPO_ITEM_MENU_0D4:
                funcion_800A09E0(parametro0);
                funcion_800A0AD0(parametro0);
                funcion_800A0B80(parametro0);
                break;
            case TIPO_ITEM_MENU_0D5:
                gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, 0xFF);
                display_list_cabeza = funcion_8009B9D0(display_list_cabeza, dato_020015A4);
                gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x32, 0x00, 0x00, 0xFF);
                display_list_cabeza = funcion_8009B9D0(display_list_cabeza, dato_020015CC);
                gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x32, 0x00, 0xFF);
                display_list_cabeza = funcion_8009B9D0(display_list_cabeza, dato_02001630);
                gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x32, 0x32, 0x00, 0xFF);
                display_list_cabeza = funcion_8009B9D0(display_list_cabeza, dato_02001658);
                break;
            case TIPO_ITEM_MENU_0D6:
                funcion_8009A76C(parametro0->d_8018DEE0_indice, parametro0->column, parametro0->row, -1);
                break;
            case TIPO_ITEM_MENU_0D7:
                funcion_800A0DFC();
                break;
            case TIPO_ITEM_MENU_0D8:
            case TIPO_ITEM_MENU_0D9:
                funcion_800A0EB8(parametro0, parametro0->type - 0xD8);
                break;
            case MENU_ITEM_IU_INICIO_FONDO:
                display_list_cabeza = renderizar_texturas_menu(
                    display_list_cabeza, fondo_texturas_menu[tiene_modo_extra_desbloqueado()], parametro0->column, parametro0->row);
                break;
            case MENU_ITEM_IU_LOGO_Y_COPYRIGHT:
                renderizar_logo_juego((parametro0->column + 0xA0), (parametro0->row + 0x47));
                display_list_cabeza =
                    renderizar_texturas_menu(display_list_cabeza, textura_copyright_1996_seg2, parametro0->column, parametro0->row);
                break;
            case MENU_ITEM_IU_EMPUJE_INICIO_BOTON:
                if (((temporizador_global / 8) % 3) != 0) {
                    display_list_cabeza =
                        renderizar_texturas_menu(display_list_cabeza, empujar_textura_boton_inicio_seg2, parametro0->column, parametro0->row);
                }
                break;
            case MENU_ITEM_IU_INICIO_REGISTRO_TIEMPO: {
                s32 ancho_cad;
                ancho_cad = (s32) ((f32) (obtener_ancho_cadena(duplicar_nombres_circuito[0]) + 5) * 0.9f) / 2;
                display_list_cabeza = dibujar_caja(display_list_cabeza, 0xA0 - ancho_cad, 0x0000007B, ancho_cad + 0xA0, 0x000000A4,
                                            0, 0, 0, 0x00000096);
                fijar_color_texto(VERDE_TEXTO);
                imprimir_modo_centro_texto1_1(0x0000009B, 0x0000008C, duplicar_nombres_circuito[0], 0, 0.9f, 0.9f);
                temporal_v1 = funcion_800B4EB4(0, 7) & 0xFFFFF;
                if (temporal_v1 < 0x1EAA) {
                    fijar_color_texto((s32) temporizador_global % 2);
                } else if (temporal_v1 < 0x2329) {
                    fijar_color_texto((s32) temporizador_global % 3);
                } else {
                    fijar_color_texto(AMARILLO_TEXTO);
                }
                obtener_minutos_registro_tiempo(temporal_v1, sp80);
                funcion_800939C8(0x00000077, 0x000000A0, sp80, 0, 1.0f, 1.0f);
                imprimir_modo_texto_1(0x0000008B, 0x000000A0, "'", 0, 1.0f, 1.0f);
                obtener_segundos_registro_tiempo(temporal_v1, sp80);
                funcion_800939C8(0x00000094, 0x000000A0, sp80, 0, 1.0f, 1.0f);
                imprimir_modo_texto_1(0x000000A7, 0x000000A0, "\"", 0, 1.0f, 1.0f);
                obtener_centesimas_registro_tiempo(temporal_v1, sp80);
                funcion_800939C8(0x000000B4, 0x000000A0, sp80, 0, 1.0f, 1.0f);
                break;
            }
            case MENU_ITEM_IU_SIN_MANDO: {
                s32 ancho_cad;
                SIN_USO s32 cont_relleno[2];
                ancho_cad = obtener_ancho_cadena(mando_sin_texto[0]);
                temporal_v1 = obtener_ancho_cadena(mando_sin_texto[1]);
                if (ancho_cad < temporal_v1) {
                    ancho_cad = temporal_v1;
                }
                temporal_t2 = (s32) (ancho_cad * por_que) / 2;
                temporal_t5 = (s32) (((por_que * 2) + 0.5) * 16.0) / 2;
                display_list_cabeza = dibujar_caja(display_list_cabeza, 0xA0 - temporal_t2, 0xB6 - temporal_t5, temporal_t2 + 0xA0,
                                            temporal_t5 + 0xB6, 0, 0, 0, 0x00000096);
                fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_1);
                for (ancho_cad = 0; ancho_cad < 2; ancho_cad++) {
                    imprimir_modo_centro_texto1_1(0xA0 * one - 1 * por_que,
                                              (s32) (0xB4 * one + ((f32) (ancho_cad * 0x12) * por_que)),
                                              mando_sin_texto[ancho_cad], 0, por_que, por_que);
                }
                break;
            }
            case MENU_PRINCIPAL_FONDO:
            case FONDO_SELECCION_PERSONAJE:
            case FONDO_SELECCION_CIRCUITO:
                display_list_cabeza = funcion_8009BC9C(display_list_cabeza, fondo_texturas_menu[tiene_modo_extra_desbloqueado()],
                                                 parametro0->column, parametro0->row, 3, 0);
                break;
            case MENU_ITEM_IU_JUEGO_SELECCION:
                display_list_cabeza =
                    renderizar_texturas_menu(display_list_cabeza, seleccionar_textura_juego_seg2, parametro0->column, parametro0->row);
                break;
            case MENU_ITEM_IU_1J_JUEGO:
            case MENU_ITEM_IU_2J_JUEGO:
            case MENU_ITEM_IU_3J_JUEGO:
            case MENU_ITEM_IU_4J_JUEGO:
                variable_a1 = parametro0->type - MENU_ITEM_IU_1J_JUEGO;
                funcion_800A8270(variable_a1, parametro0);
                funcion_800A0FA4(parametro0, variable_a1);
                break;
            case MENU_ITEM_IU_OK:
                funcion_800A8564(parametro0);
                display_list_cabeza =
                    funcion_8009BC9C(display_list_cabeza, dato_0200487C, parametro0->column, parametro0->row, 2, parametro0->param1);
                break;
            case MENU_PRINCIPAL_GFX_OPCION:
            case MENU_PRINCIPAL_GFX_DATOS:
                variable_a1 = parametro0->type - 0xF;
                if (parametro0->param1 < 0x20) {
                    temporal_t9 = (parametro0->param1 * 0x3A) / 64;
                    if (variable_a1 == menu_principal_seleccion) {
                        display_list_cabeza =
                            seleccionar_rapido_case_destello_dibujo(display_list_cabeza, parametro0->column + temporal_t9, (u32) parametro0->row,
                                                        (parametro0->column - temporal_t9) + 0x39, parametro0->row + 0x12);
                    } else {
                        display_list_cabeza =
                            dibujar_relleno_caja(display_list_cabeza, parametro0->column + temporal_t9, parametro0->row,
                                          (parametro0->column - temporal_t9) + 0x39, parametro0->row + 0x12, 1, 1, 1, 0x000000FF);
                    }
                }
                variable_v1 = parametro0->type - 0xA;
                display_list_cabeza =
                    funcion_8009BC9C(display_list_cabeza, dato_800E8254[variable_v1], parametro0->column, parametro0->row, 2, parametro0->param1);
                break;
            case MENU_PRINCIPAL_50CC:
            case MENU_PRINCIPAL_100CC:
            case MENU_PRINCIPAL_150CC:
            case MENU_PRINCIPAL_CC_EXTRA:
            case TIPO_ITEM_MENU_016:
            case TIPO_ITEM_MENU_017:
            case MENU_PRINCIPAL_CONTRARRELOJ_EMPEZAR:
            case MENU_PRINCIPAL_CONTRARRELOJ_DATOS:
                variable_a1 = juego_modo_sub_menu_columna[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]];
                variable_v1 = juego_modo_jugador_seleccion[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]];
                switch (parametro0->type) {
                    case MENU_PRINCIPAL_50CC:
                    case MENU_PRINCIPAL_100CC:
                    case MENU_PRINCIPAL_150CC:
                    case MENU_PRINCIPAL_CC_EXTRA:
                        switch (variable_v1) {
                            case 0:
                            case 2:
                                break;
                            default:
                                variable_a1 = -1;
                                break;
                        }

                        variable_v1 = MENU_PRINCIPAL_50CC;
                        textura = segmentado_a_duplicado_virtual(dato_800E8294[parametro0->type - MENU_PRINCIPAL_50CC]);
                        break;
                    case TIPO_ITEM_MENU_016:
                    case TIPO_ITEM_MENU_017:
                        if (variable_v1 != 2) {
                            variable_a1 = -1;
                            break;
                        } else {
                            variable_v1 = TIPO_ITEM_MENU_016;
                            textura = segmentado_a_duplicado_virtual(dato_800E82A4[parametro0->type - TIPO_ITEM_MENU_016]);
                        }
                        break;
                    case MENU_PRINCIPAL_CONTRARRELOJ_EMPEZAR:
                    case MENU_PRINCIPAL_CONTRARRELOJ_DATOS:
                        if (variable_v1 != 1) {
                            variable_a1 = -1;
                            break;
                        } else {
                            variable_v1 = MENU_PRINCIPAL_CONTRARRELOJ_EMPEZAR;
                            textura = segmentado_a_duplicado_virtual(dato_800E82AC[parametro0->type - MENU_PRINCIPAL_CONTRARRELOJ_EMPEZAR]);
                        }
                        break;
                    default:
                        break;
                }
                if (variable_a1 == -1) {
                    break;
                }
                if ((menu_principal_seleccion >= MENU_PRINCIPAL_SELECCION_SUB_MODO) && (variable_a1 == (parametro0->type - variable_v1))) {
                    if (menu_principal_seleccion > MENU_PRINCIPAL_SELECCION_SUB_MODO) {
                        display_list_cabeza =
                            dibujar_relleno_caja(display_list_cabeza, parametro0->column, parametro0->row, parametro0->column + 0x3F,
                                          parametro0->row + 0x11, 0x000000FF, 0x000000F9, 0x000000DC, 0x000000FF);
                    } else {
                        display_list_cabeza = seleccionar_lento_case_destello_dibujo(
                            display_list_cabeza, parametro0->column ^ 0, parametro0->row ^ 0, parametro0->column + 0x3F, parametro0->row + 0x11);
                    }
                } else {
                    display_list_cabeza = dibujar_relleno_caja(display_list_cabeza, parametro0->column, parametro0->row, parametro0->column + 0x3F,
                                                     parametro0->row + 0x11, 1, 1, 1, 0x000000FF);
                }
                display_list_cabeza = renderizar_texturas_menu(display_list_cabeza, textura, parametro0->column, parametro0->row);
                break;
            case TIPO_ITEM_MENU_01B:
                funcion_800A10CC(parametro0);
                break;
            case PERSONAJE_SELECCION_MENU_JUGADOR_SELECCION_CARTEL:
                display_list_cabeza = renderizar_texturas_menu(display_list_cabeza, dato_02004B4C, parametro0->column, parametro0->row);
                break;
            case PERSONAJE_SELECCION_MENU_1J_CURSOR:
            case PERSONAJE_SELECCION_MENU_2J_CURSOR:
            case PERSONAJE_SELECCION_MENU_3J_CURSOR:
            case PERSONAJE_SELECCION_MENU_4J_CURSOR:
                temporal_a0 = parametro0->type - PERSONAJE_SELECCION_MENU_1J_CURSOR;
                if (selecciones_cuadricula_personaje[temporal_a0]) {
                    if (personaje_cuadricula_es_seleccionado[temporal_a0] == 0) {
                        temporal_t2 = 255;
                    } else {
                        temporal_t2 = temporizador_global % 16;
                        if (temporal_t2 >= 8) {
                            temporal_t2 = (-temporal_t2 * 8) + 0x80;
                        } else {
                            temporal_t2 *= 8;
                        }
                        temporal_t2 += 191;
                    }
                    renderizar_jugador_cursor(parametro0, temporal_a0, temporal_t2);
                }
                break;
            case PERSONAJE_SELECCION_MENU_OK:
                funcion_800A8564(parametro0);
                display_list_cabeza =
                    funcion_8009BC9C(display_list_cabeza, dato_02004B74, parametro0->column, parametro0->row, 2, parametro0->param1);
                break;
            case MENU_SELECCION_PERSONAJE_MARIO:
            case MENU_SELECCION_PERSONAJE_LUIGI:
            case MENU_SELECCION_PERSONAJE_TOAD:
            case MENU_SELECCION_PERSONAJE_PEACH:
            case MENU_SELECCION_PERSONAJE_YOSHI:
            case MENU_SELECCION_PERSONAJE_DK:
            case MENU_SELECCION_PERSONAJE_WARIO:
            case MENU_SELECCION_PERSONAJE_BOWSER:
                funcion_800A12BC(parametro0, segmentado_a_duplicado_virtual(dato_800E7D54[parametro0->type - 0x2B]));
            case TIPO_ITEM_MENU_0A0:
            case TIPO_ITEM_MENU_0A1:
                funcion_8009A76C(parametro0->d_8018DEE0_indice, parametro0->column, parametro0->row, parametro0->param1);
                break;
            case TIPO_ITEM_MENU_058:
            case CIRCUITO_SELECCION_CIRCUITO_NOMBRES:
            case TIPO_ITEM_MENU_05A:
            case TIPO_ITEM_MENU_05B:
            case CIRCUITO_SELECCION_BATALLA_NOMBRES:
                funcion_800A8A98(parametro0);
                display_list_cabeza = renderizar_texturas_menu(
                    display_list_cabeza,
                    segmentado_a_duplicado_virtual(menu_texturas_pista_seleccion[parametro0->type - CIRCUITO_SELECCION_MAPA_SELECCION]),
                    parametro0->column, parametro0->row);
                funcion_800A8CA4(parametro0);
                break;
            case CIRCUITO_SELECCION_MAPA_SELECCION:
                display_list_cabeza = renderizar_texturas_menu(
                    display_list_cabeza,
                    segmentado_a_duplicado_virtual(menu_texturas_pista_seleccion[parametro0->type - CIRCUITO_SELECCION_MAPA_SELECCION]),
                    parametro0->column, parametro0->row);
                break;
            case TIPO_ITEM_MENU_05F:
            case TIPO_ITEM_MENU_060:
            case TIPO_ITEM_MENU_061:
            case TIPO_ITEM_MENU_062:
                funcion_800A1500(parametro0);
                break;
            case SELECCION_CIRCUITO_COPA_HONGO:
            case SELECCION_CIRCUITO_COPA_FLOR:
            case SELECCION_CIRCUITO_COPA_ESTRELLA:
            case SELECCION_CIRCUITO_COPA_ESPECIAL:
                variable_a1 = parametro0->type - SELECCION_CIRCUITO_COPA_HONGO;
                funcion_800A890C(variable_a1, parametro0);
                funcion_800A143C(parametro0, variable_a1);
                break;
            case OK_SELECCION_CIRCUITO:
                funcion_800A8564(parametro0);
                display_list_cabeza =
                    funcion_8009BC9C(display_list_cabeza, dato_02004E80, parametro0->column, parametro0->row, 2, parametro0->param1);
                break;
            case TIPO_ITEM_MENU_065:
            case TIPO_ITEM_MENU_066: {
                f32 escalar_x;
                if (parametro0->type == TIPO_ITEM_MENU_065) {
                    escalar_x = 0.6f;
                } else {
                    escalar_x = 0.8f;
                }
                funcion_800A86E8(parametro0);
                fijar_color_texto(AMARILLO_TEXTO);
                imprimir_modo_texto_1(parametro0->column + 8, parametro0->row + 0x10, texto_tiempo_mejor[parametro0->type - 0x65], 0, escalar_x,
                                  0.8f);
                funcion_800A874C(parametro0);
                break;
            }
            case TIPO_ITEM_MENU_06E:
                renderizar_introduccion_batalla(parametro0);
                break;
            case TIPO_ITEM_MENU_067:
                funcion_800A8EC0(parametro0);
                break;
            case TIPO_ITEM_MENU_068:
                display_list_cabeza = dibujar_relleno_caja(display_list_cabeza, parametro0->column, parametro0->row, parametro0->column + 0x3F,
                                                 parametro0->row + 0x11, 1, 1, 1, 0x000000FF);
                display_list_cabeza = renderizar_texturas_menu(
                    display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E8294[seleccion_cc]), parametro0->column, parametro0->row);
                break;
            case TIPO_ITEM_MENU_069:
                funcion_800A8F48(parametro0);
                break;
            case TIPO_ITEM_MENU_078:
            case TIPO_ITEM_MENU_079:
            case TIPO_ITEM_MENU_07A:
            case TIPO_ITEM_MENU_07B:
                variable_a1 = parametro0->type - TIPO_ITEM_MENU_078;
                funcion_800A90D4(variable_a1, parametro0);
                funcion_800A143C(parametro0, variable_a1);
                break;
            case TIPO_ITEM_MENU_08C:
                if ((menu_principal_seleccion >= MENU_PRINCIPAL_SELECCION_SUB_MODO) && (variable_a1 == (parametro0->type - variable_v1))) {
                    if (menu_principal_seleccion > MENU_PRINCIPAL_SELECCION_SUB_MODO) {
                        display_list_cabeza =
                            dibujar_relleno_caja(display_list_cabeza, parametro0->column, parametro0->row, parametro0->column + 0x3F,
                                          parametro0->row + 0x11, 0x000000FF, 0x000000F9, 0x000000DC, 0x000000FF);
                    } else {
                        display_list_cabeza =
                            seleccionar_lento_case_destello_dibujo(display_list_cabeza, parametro0->column ^ 0, one = parametro0->row ^ 0,
                                                        parametro0->column + 0x3F, parametro0->row + 0x11);
                    }
                } else {
                    display_list_cabeza = dibujar_relleno_caja(display_list_cabeza, parametro0->column, parametro0->row, parametro0->column + 0x3F,
                                                     parametro0->row + 0x11, 1, 1, 1, 0x000000FF);
                }
                display_list_cabeza = renderizar_texturas_menu(display_list_cabeza, textura_datos_seg2, parametro0->column, parametro0->row);
                fijar_color_texto(AMARILLO_TEXTO);
                imprimir_izquierda_texto1(0x00000125, 0x0000001C, datos_menu_texto, 0, 0.55f, 0.55f);
                break;
            case TIPO_ITEM_MENU_08D:
                funcion_800A1780(parametro0);
                break;
            case TIPO_ITEM_MENU_07C:
            case TIPO_ITEM_MENU_07D:
            case TIPO_ITEM_MENU_07E:
            case TIPO_ITEM_MENU_07F:
            case TIPO_ITEM_MENU_080:
            case TIPO_ITEM_MENU_081:
            case TIPO_ITEM_MENU_082:
            case TIPO_ITEM_MENU_083:
            case TIPO_ITEM_MENU_084:
            case TIPO_ITEM_MENU_085:
            case TIPO_ITEM_MENU_086:
            case TIPO_ITEM_MENU_087:
            case TIPO_ITEM_MENU_088:
            case TIPO_ITEM_MENU_089:
            case TIPO_ITEM_MENU_08A:
            case TIPO_ITEM_MENU_08B:
                funcion_800A15EC(parametro0);
                break;
            case TIPO_ITEM_MENU_096:
                fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_1);
                imprimir_izquierda_texto1(parametro0->column, parametro0->row, nombres_copa[dato_800DC540], parametro0->param1, parametro0->paramf, 1.0f);
                break;
            case TIPO_ITEM_MENU_097:
                fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_2);
                imprimir_modo_texto_1(parametro0->column, parametro0->row, nombres_circuito[id_circuito_actual], parametro0->param1, parametro0->paramf,
                                  1.0f);
                break;
            case TIPO_ITEM_MENU_098:
                funcion_800A2D1C(parametro0);
                break;
            case TIPO_ITEM_MENU_05E:
                display_list_cabeza = funcion_80096CD8(display_list_cabeza, 0x00000019, 0x00000072, 0x0000007CU, 0x0000004AU);
                break;
            case TIPO_ITEM_MENU_0AA:
                funcion_800A2EB8(parametro0);
                break;
            case TIPO_ITEM_MENU_0AB:
                funcion_800A34A8(parametro0);
                break;
            case TIPO_ITEM_MENU_0AC:
                funcion_800A6154(parametro0);
                break;
            case TIPO_ITEM_MENU_0AF:
                funcion_800A6034(parametro0);
                break;
            case TIPO_ITEM_MENU_0B0:
                funcion_800A638C(parametro0);
                break;
            case TIPO_ITEM_MENU_0B1:
            case TIPO_ITEM_MENU_0B2:
            case TIPO_ITEM_MENU_0B3:
            case TIPO_ITEM_MENU_0B4:
                if (parametro0->state != 0) {
                    variable_v1 = parametro0->type - TIPO_ITEM_MENU_0B1;
                    one = dato_800EFD64[selecciones_personaje[variable_v1]];
                    display_list_cabeza = renderizar_texturas_menu(
                        display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E7D54[one]), parametro0->column, parametro0->row);
                    funcion_8009A7EC(parametro0->d_8018DEE0_indice, parametro0->column, parametro0->row, variable_v1, parametro0->param1);
                    renderizar_jugador_cursor(parametro0, variable_v1, 0x000000FF);
                }
                break;
            case TIPO_ITEM_MENU_0B9:
                renderizar_contrarreloj_texto_meta(parametro0);
                break;
            case TIPO_ITEM_MENU_0BA:
                funcion_800A3E60(parametro0);
                break;
            case MENU_ITEM_ANUNCIO_FANTASMA:
                renderizar_menu_item_anuncio_fantasma(parametro0);
                break;
            case PAUSA_ITEM_MENU:
                renderizar_menu_pausa(parametro0);
                break;
            case MENU_ITEM_FIN_CIRCUITO_OPCION:
                renderizar_menu_item_fin_circuito_opcion(parametro0);
                break;
            case MENU_ITEM_DATOS_CIRCUITO_IMAGEN:
                renderizar_menu_item_datos_circuito_imagen(parametro0);
                break;
            case MENU_ITEM_DATOS_CIRCUITO_INFO:
                renderizar_menu_item_datos_circuito_info(parametro0);
                break;
            case MENU_ITEM_DATOS_CIRCUITO_SELECCIONABLE:
                menu_item_datos_circuito_seleccionable(parametro0);
                break;
            case TIPO_ITEM_MENU_0E9:
                funcion_800A1DE0(parametro0);
                break;
            case TIPO_ITEM_MENU_0EA:
                funcion_800A1F30(parametro0);
                break;
            case TIPO_ITEM_MENU_0F0:
                funcion_800A1FB0(parametro0);
                break;
            case TIPO_ITEM_MENU_0F1:
                display_list_cabeza = renderizar_texturas_menu(display_list_cabeza, dato_02004638, parametro0->column, parametro0->row);
                break;
            case TIPO_ITEM_MENU_10E:
                funcion_800A70E8(parametro0);
                break;
            case TIPO_ITEM_MENU_12B:
                funcion_800A7258(parametro0);
                break;
            case TIPO_ITEM_MENU_12C:
                funcion_800A72FC(parametro0);
                break;
            case TIPO_ITEM_MENU_12D:
                funcion_800A7448(parametro0);
                break;
            case TIPO_ITEM_MENU_12E:
                funcion_800A75A0(parametro0);
                break;
            case TIPO_ITEM_MENU_12F:
                funcion_800A761C(parametro0);
                break;
            case TIPO_ITEM_MENU_130:
                if (parametro0->state != 0) {
                    variable_a1 = dato_800EFD64[dato_802874D8.desconocido_1e];
                    display_list_cabeza = renderizar_texturas_menu(
                        display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E7D54[variable_a1]), parametro0->column, parametro0->row);
                    funcion_8009A7EC(parametro0->d_8018DEE0_indice, parametro0->column, parametro0->row, 0, parametro0->param1);
                }
                break;
            case TIPO_ITEM_MENU_190:
            case TIPO_ITEM_MENU_191:
            case TIPO_ITEM_MENU_192:
            case TIPO_ITEM_MENU_193:
            case TIPO_ITEM_MENU_194:
            case TIPO_ITEM_MENU_195:
            case TIPO_ITEM_MENU_196:
            case TIPO_ITEM_MENU_197:
            case TIPO_ITEM_MENU_198:
            case TIPO_ITEM_MENU_199:
            case TIPO_ITEM_MENU_19A:
            case TIPO_ITEM_MENU_19B:
            case TIPO_ITEM_MENU_19C:
            case TIPO_ITEM_MENU_19D:
            case TIPO_ITEM_MENU_19E:
            case TIPO_ITEM_MENU_19F:
            case TIPO_ITEM_MENU_1A0:
            case TIPO_ITEM_MENU_1A1:
            case TIPO_ITEM_MENU_1A2:
            case TIPO_ITEM_MENU_1A3:
            case TIPO_ITEM_MENU_1A4:
            case TIPO_ITEM_MENU_1A5:
            case TIPO_ITEM_MENU_1A6:
            case TIPO_ITEM_MENU_1A7:
            case TIPO_ITEM_MENU_1A8:
            case TIPO_ITEM_MENU_1A9:
            case TIPO_ITEM_MENU_1AA:
            case TIPO_ITEM_MENU_1AB:
            case TIPO_ITEM_MENU_1AC:
            case TIPO_ITEM_MENU_1AD:
            case TIPO_ITEM_MENU_1AE:
            case TIPO_ITEM_MENU_1AF:
            case TIPO_ITEM_MENU_1B0:
            case TIPO_ITEM_MENU_1B1:
            case TIPO_ITEM_MENU_1B2:
            case TIPO_ITEM_MENU_1B3:
            case TIPO_ITEM_MENU_1B4:
            case TIPO_ITEM_MENU_1B5:
            case TIPO_ITEM_MENU_1B6:
            case TIPO_ITEM_MENU_1B7:
            case TIPO_ITEM_MENU_1B8:
            case TIPO_ITEM_MENU_1B9:
            case TIPO_ITEM_MENU_1BA:
            case TIPO_ITEM_MENU_1BB:
            case TIPO_ITEM_MENU_1BC:
            case TIPO_ITEM_MENU_1BD:
            case TIPO_ITEM_MENU_1BE:
            case TIPO_ITEM_MENU_1BF:
            case TIPO_ITEM_MENU_1C0:
            case TIPO_ITEM_MENU_1C1:
            case TIPO_ITEM_MENU_1C2:
            case TIPO_ITEM_MENU_1C3:
            case TIPO_ITEM_MENU_1C4:
            case TIPO_ITEM_MENU_1C5:
            case TIPO_ITEM_MENU_1C6:
            case TIPO_ITEM_MENU_1C7:
            case TIPO_ITEM_MENU_1C8:
            case TIPO_ITEM_MENU_1C9:
            case TIPO_ITEM_MENU_1CA:
            case TIPO_ITEM_MENU_1CB:
            case TIPO_ITEM_MENU_1CC:
            case TIPO_ITEM_MENU_1CD:
            case TIPO_ITEM_MENU_1CE:
                renderizar_creditos_item_menu(parametro0);
                break;
        }
    }
}

void funcion_800A08D8(u8 parametro0, s32 columna, s32 renglon) {
    if (parametro0 >= 0x10) {
        parametro0 -= 0x10;
        if (parametro0 < 0x85) {
            if (parametro0 >= 0x32) {
                parametro0 = 0x2B;
            }
            display_list_cabeza =
                renderizar_texturas_menu(display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E7AF8[parametro0]), columna, renglon);
        }
    }
}

s32 funcion_800A095C(char* algun_cadena, s32 largo, s32 columna, s32 renglon) {
    s32 columna_temporal;
    s32 no_cantidad_terminator;

    no_cantidad_terminator = 0;
    columna_temporal = columna;
    for (; largo != 0; largo--, columna_temporal += 8) {
        if (*algun_cadena != 0) {
            no_cantidad_terminator++;
        }
        funcion_800A08D8(*algun_cadena++, columna_temporal, renglon);
    }
    return no_cantidad_terminator;
}

void funcion_800A09E0(MenuItem* parametro0) {
    s32 renglon_tabla;

    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA - 1, 194);
    for (renglon_tabla = 0; renglon_tabla < 9; renglon_tabla++) {
        if (controller_pak_sentido_desplazamiento == CONTROLLER_PAK_NINGUNO_DIR_DESPLAZAMIENTO && (renglon_tabla == 0 || renglon_tabla == 8)) {
            continue;
        }
        display_list_cabeza = renderizar_texturas_menu(display_list_cabeza, dato_0200157C, 0x20, (renglon_tabla * 0xA) + parametro0->row);
    }
}

void funcion_800A0AD0(SIN_USO MenuItem* parametro0) {
    MenuItem* temporal_t1;
    temporal_t1 = buscar_duplicado_items_menu(TIPO_ITEM_MENU_0DA);
    if ((controller_pak_seleccion_menu != CONTROLLER_PAK_REGISTRO_SELECCION_MENU) &&
        (controller_pak_seleccion_menu != CONTROLLER_PAK_FIN_MENU)) {
        gDPSetPrimColor(display_list_cabeza++, 0, 0, 0xFF, temporal_t1->param2, 0x00, 0xFF);
        display_list_cabeza =
            renderizar_texturas_menu(display_list_cabeza, dato_02001874, 0x24, (controller_pak_renglon_tabla_seleccionado * 0xA) + 0x7C);
    }
}

void funcion_800A0B80(MenuItem* parametro0) {
    SIN_USO s32 temporal_a2;
    s32 temporal_s1;
    s32 temporal_s2;
    s32 variable_s1;
    s32 variable_s5;
    s32 variable_s0;
    OSPfsState* temporal_s4;

    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x32, 0xFF);
    for (variable_s5 = 0; variable_s5 < 9; variable_s5++) {
        if (controller_pak_renglones_tabla_visible[variable_s5] == 0) {
            continue;
        }

        temporal_s1 = variable_s5 * 0xA;
        variable_s0 = controller_pak_renglones_tabla_visible[variable_s5];
        if (variable_s0 < 0xA) {
            funcion_800A08D8(variable_s0 + 0x10, 0x00000032, parametro0->row + temporal_s1 + 1);
        } else {
            variable_s0 %= 10;
            funcion_800A08D8(variable_s0 + 0x10, 0x00000035, parametro0->row + temporal_s1 + 1);
            funcion_800A08D8(0x11U, 0x0000002F, parametro0->row + temporal_s1 + 1);
        }
        temporal_s2 = parametro0->row + temporal_s1 + 1;
        if (pfs_error[controller_pak_renglones_tabla_visible[variable_s5] - 1] == 0) {
            temporal_s4 = &estado_pfs[controller_pak_renglones_tabla_visible[variable_s5] - 1];
            variable_s0 = funcion_800A095C(temporal_s4->game_name, 0x00000010, 0x0000004F, temporal_s2);
            if (temporal_s4->ext_name[0] != 0) {
                funcion_800A08D8(0x3CU, (variable_s0 * 8) + 0x4F, temporal_s2);
                funcion_800A08D8(temporal_s4->ext_name[0], (variable_s0 * 8) + 0x57, temporal_s2);
            }
            variable_s1 = 0x10;
            variable_s0 = (temporal_s4->file_size + 0xFF) >> 8;
            do {
                funcion_800A08D8(((variable_s0 % 10) + 0x10), variable_s1 + 0xFD, temporal_s2);
                variable_s0 /= 10;
                variable_s1 -= 8;
            } while (variable_s0 != 0);
        }
    }
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA - 1, ALTURA_PANTALLA - 1);
}

void funcion_800A0DFC(void) {
    s32 temporal_t6;
    s32 variable_s0;
    s32 variable_s1;

    variable_s0 = controller_pak_libre_paginas_1_num;
    variable_s1 = 0x00000110;
    do {
        temporal_t6 = variable_s0 % 10;
        variable_s0 /= 10;
        display_list_cabeza =
            renderizar_texturas_menu(display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E7D0C[temporal_t6]), variable_s1, 0x000000B8);
        variable_s1 -= 9;
    } while (variable_s0 != 0);
}

void funcion_800A0EB8(SIN_USO MenuItem* parametro0, s32 parametro1) {
    s32 variable_t1;
    s32 cosa;
    desconocido_d_800E70A0* temporal_v0;
    MenuItem* temporal_t3;

    temporal_t3 = buscar_duplicado_items_menu(TIPO_ITEM_MENU_0DA);
    if (parametro1 == 0) {
        if (controller_pak_seleccion_menu == CONTROLLER_PAK_FIN_MENU) {
            variable_t1 = 1;
        } else {
            variable_t1 = 0;
        }
    } else {
        cosa = controller_pak_seleccion_menu;
        if ((cosa == CONTROLLER_PAK_BORRAR_MENU) || (cosa == CONTROLLER_PAK_ABANDONAR_MENU)) {
            variable_t1 = ((parametro1 * 2) + controller_pak_seleccion_menu) - CONTROLLER_PAK_BORRAR_MENU;
        } else {
            return;
        }
    }
    temporal_v0 = &dato_800E7278[variable_t1];
    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0xFF, temporal_t3->param2, 0x00, 0xFF);
    display_list_cabeza = renderizar_texturas_menu(display_list_cabeza, dato_0200184C, (s32) temporal_v0->column, (s32) temporal_v0->row);
}

void funcion_800A0FA4(MenuItem* parametro0, s32 parametro1) {
    switch (parametro0->state) {
        case 0:
        case 2:
        case 3:
            display_list_cabeza = renderizar_texturas_menu(
                display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E8234[(parametro1 * 2) + 0]), parametro0->column, parametro0->row);
            display_list_cabeza = renderizar_texturas_menu(
                display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E8234[(parametro1 * 2) + 1]), parametro0->column, parametro0->row);
            break;
        case 1:
        case 4:
            display_list_cabeza = funcion_8009BC9C(display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E8234[(parametro1 * 2) + 0]),
                                             parametro0->column, parametro0->row, 2, parametro0->param1);
            display_list_cabeza = funcion_8009BC9C(display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E8234[(parametro1 * 2) + 1]),
                                             parametro0->column, parametro0->row, 2, parametro0->param1);
            break;
    }
}

void funcion_800A10CC(MenuItem* parametro0) {
    s32 variable_s1;
    s32 index;

    switch (parametro0->state) {
        case 2:
        case 3:
        case 4:
        case 5:
            display_list_cabeza =
                dibujar_relleno_caja(display_list_cabeza, 0x0000001E, 0x00000032, 0x00000122, 0x0000006E, 0, 0, 0, 0x000000FF);
            index = parametro0->state - 2;
            fijar_color_texto(AMARILLO_TEXTO);
            for (variable_s1 = 0; variable_s1 < 4; variable_s1++) {
                imprimir_modo_texto_1(0x00000023, 0x41 + (0xD * variable_s1), dato_800E7940[(index * 4) + variable_s1], 0, 0.65f, 0.65f);
            }
            break;
        default:
            break;
    }
}

void renderizar_jugador_cursor(MenuItem* parametro0, s32 parametro1, s32 parametro2) {
    RGBA16* temporal_v1;

    temporal_v1 = &dato_800E74A8[parametro1];
    gDPSetPrimColor(display_list_cabeza++, 0, 0, temporal_v1->rojo, temporal_v1->verde, temporal_v1->azul, temporal_v1->alpha);
    gDPSetEnvColor(display_list_cabeza++, parametro2, parametro2, parametro2, 0x00);
    display_list_cabeza = renderizar_texturas_menu(
        display_list_cabeza, segmentado_a_duplicado_virtual(menu_texturas_borde_jugador[parametro1]), parametro0->column, parametro0->row);
}

void funcion_800A12BC(MenuItem* parametro0, TexturaMenu* parametro1) {
    switch (parametro0->state) {
        case 0:
        case 2:
        case 4:
            display_list_cabeza = renderizar_texturas_menu(display_list_cabeza, parametro1, parametro0->column, parametro0->row);
            break;
        case 1:
        case 3:
            display_list_cabeza = funcion_8009BC9C(display_list_cabeza, parametro1, parametro0->column, parametro0->row, 2, parametro0->param1);
            break;
    }
}

void funcion_800A1350(MenuItem* parametro0) {
    s32 cosa;
    if (funcion_800AAFCC(parametro0->type - 0x2B) < 0) {
        switch (parametro0->state) {
            case 0:
            case 2:
            case 4:
                display_list_cabeza = dibujar_caja(display_list_cabeza, parametro0->column, parametro0->row, parametro0->column + 0x40,
                                            parametro0->row + 0x4C, 0, 0, 0, 0x00000064);
                break;
            case 1:
            case 3:
                cosa = parametro0->param1;
                display_list_cabeza = dibujar_caja(display_list_cabeza, parametro0->column + cosa, parametro0->row,
                                            (parametro0->column - cosa) + 0x40, parametro0->row + 0x4C, 0, 0, 0, 0x00000064);
                break;
        }
    }
}

void funcion_800A143C(MenuItem* parametro0, s32 parametro1) {
    switch (parametro0->state) {
        case 0:
        case 2:
        case 3:
            display_list_cabeza =
                renderizar_texturas_menu(display_list_cabeza, segmentado_a_duplicado_virtual(menu_texturas_pista_seleccion[parametro1 + 1]),
                                     parametro0->column, parametro0->row);
            break;
        case 1:
        case 4:
            display_list_cabeza =
                funcion_8009BC9C(display_list_cabeza, segmentado_a_duplicado_virtual(menu_texturas_pista_seleccion[parametro1 + 1]),
                              parametro0->column, parametro0->row, 2, parametro0->param1);
            break;
    }
}

void funcion_800A1500(MenuItem* parametro0) {
    MenuItem* temporal_v0;
    desconocido_d_800E70A0* temporal_v0_2;
    s32 variable_a1;

    variable_a1 = 0;
    temporal_v0 = buscar_duplicado_items_menu(TIPO_ITEM_MENU_064);
    switch (temporal_v0->state) { /* irregular */
        case 0:
        case 1:
            break;
        case 2:
            if (((temporal_v0->param1 % 4) + 0x5F) != parametro0->type) {
                variable_a1 = 1;
            }
            break;
        case 3:
            variable_a1 = 1;
            break;
    }
    switch (variable_a1) {
        case 0:
            funcion_8009A76C(parametro0->d_8018DEE0_indice, 0x00000017, 0x00000070, -1);
            break;
        case 1:
            temporal_v0_2 = &dato_800E7168[parametro0->type - 0x5F];
            funcion_8009A76C(parametro0->d_8018DEE0_indice, temporal_v0_2->column, temporal_v0_2->row, -2);
            break;
    }
}

void funcion_800A15EC(MenuItem* parametro0) {
    s16 id_circuito = orden_circuito_copa[(parametro0->type - 0x7C) / 4][(parametro0->type - 0x7C) % 4];
    display_list_cabeza =
        funcion_8009C204(display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E7D74[id_circuito]), parametro0->column, parametro0->row, 2);
    display_list_cabeza = dibujar_caja(display_list_cabeza, parametro0->column, parametro0->row + 0x27, parametro0->column + 0x40, parametro0->row + 0x30,
                                0, 0, 0, 0xFF);
    display_list_cabeza = funcion_8009C204(display_list_cabeza, segmentado_a_duplicado_virtual(dato_800E7DC4[id_circuito]), parametro0->column,
                                     parametro0->row + 0x27, 3);
    if (funcion_800B639C(parametro0->type - 0x7C) >= 0) {
        display_list_cabeza = seleccionar_lento_case_destello_dibujo(display_list_cabeza, parametro0->column + 0x20, parametro0->row ^ 0,
                                                       parametro0->column + 0x3F, parametro0->row + 9);
        display_list_cabeza =
            funcion_8009C204(display_list_cabeza, segmentado_a_duplicado_virtual(&dato_02004A0C), parametro0->column + 0x20, parametro0->row, 2);
    }
}

void funcion_800A1780(MenuItem* parametro0) {
    RGBA16* temporal_a1;
    RGBA16* temporal_v1;
    s32 temporal_a2;
    u32 rojo;
    u32 verde;
    u32 azul;
    u32 alpha;

    temporal_v1 = &dato_800E74D0[parametro0->param2];
    temporal_a1 = &dato_800E74D0[(parametro0->param2 + 1) % 3];
    temporal_a2 = 256 - parametro0->param1;
    rojo = ((temporal_v1->rojo * temporal_a2) + (temporal_a1->rojo * parametro0->param1)) / 256;
    verde = ((temporal_v1->verde * temporal_a2) + (temporal_a1->verde * parametro0->param1)) / 256;
    azul = ((temporal_v1->azul * temporal_a2) + (temporal_a1->azul * parametro0->param1)) / 256;
    alpha = ((temporal_v1->alpha * temporal_a2) + (temporal_a1->alpha * parametro0->param1)) / 256;
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, alpha);
    display_list_cabeza =
        renderizar_texturas_menu(display_list_cabeza, segmentado_a_duplicado_virtual(dato_02001FA4), parametro0->column, parametro0->row);
}

void renderizar_menu_item_datos_circuito_imagen(MenuItem* parametro0) {
    funcion_8009A76C(parametro0->d_8018DEE0_indice, 0x17, 0x84, -1);
    if (funcion_800B639C(contrarreloj_indice_circuito_datos) >= CONTRARRELOJ_DATOS_LUIGI_RACEWAY) {
        display_list_cabeza = seleccionar_lento_case_destello_dibujo(display_list_cabeza, 0x57, 0x84, 0x96, 0x95);
        display_list_cabeza = renderizar_texturas_menu(display_list_cabeza, dato_02004A0C, 0x57, 0x84);
    }
    funcion_8004EF9C(orden_circuito_copa[contrarreloj_indice_circuito_datos / 4][contrarreloj_indice_circuito_datos % 4]);
    do {
        gDPSetTextureFilter(display_list_cabeza++, G_TF_BILERP);
    } while (0);
}
