// Info pistas y tiempos

void renderizar_menu_item_datos_circuito_info(MenuItem* parametro0) {
    s16 id_circuito;
    s32 grabar_tipo;
    s32 desplazamiento_renglon;

    id_circuito = orden_circuito_copa[contrarreloj_indice_circuito_datos / 4][contrarreloj_indice_circuito_datos % 4];
    parametro0->column = 0x14;
    fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_1);
    imprimir_modo_centro_texto1_1(0x69, parametro0->row + 0x19, duplicar_nombres_circuito[id_circuito], 0, 0.75f, 0.75f);

    fijar_color_texto(TEXTO_ROJO);
    imprimir_modo_texto_1(0x2D, parametro0->row + 0x28, (char*) &distancia_texto, 0, 0.75f, 0.75f);
    imprimir_izquierda_texto1(0xA5, parametro0->row + 0x28, longitudes_circuito[id_circuito], 1, 0.75f, 0.75f);

    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_texto_1(0xA0, parametro0->row + 0x86, texto_tiempo_mejor[0], 0, 0.75f, 0.75f);
    for (grabar_tipo = CONTRARRELOJ_3LAP_REGISTRO_1, desplazamiento_renglon = 0; grabar_tipo < CONTRARRELOJ_1LAP_REGISTRO;
         grabar_tipo++, desplazamiento_renglon += 0xD) {
        fijar_color_texto(TEXTO_ROJO);
        renderizar_veces_vuelta(grabar_tipo, 0x96, parametro0->row + desplazamiento_renglon + 0x92);
    }
    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_texto_1(0xA0, parametro0->row + 0xD5, texto_tiempo_mejor[1], 0, 0.75f, 0.75f);
    renderizar_veces_vuelta(CONTRARRELOJ_1LAP_REGISTRO, 0x96, parametro0->row + 0xE1);
}

void menu_item_datos_circuito_seleccionable(MenuItem* parametro0) {
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    SIN_USO char* wut;
    desconocido_d_800E70A0 sp78;
    s32 i;
    s32 variable_s1;
    s32 variable_s2;
    SIN_USO s32 cosa;
    CircuitoContrarrelojRegistros* temporal_s6;

    temporal_s6 = &datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[contrarreloj_indice_circuito_datos / 4]
                   .registros_circuito[contrarreloj_indice_circuito_datos % 4];
    for (i = 0; i < CANTIDAD_ARREGLO(opcion_menu_texto); i++) {
        wut = opcion_menu_texto[i];
        variable_s1 = 0;
        if (i == circuito_registros_menu_seleccion) {
            variable_s2 = TEXTO_AZUL_VERDE_ROJO_CICLO_2;
        } else {
            variable_s2 = VERDE_TEXTO;
            switch (i) { /* irregular */
                case CIRCUITO_REGISTROS_MENU_BORRAR_REGISTROS:
                    if (temporal_s6->bytes_desconocido[0] == 0) {
                        variable_s1 = 1;
                    }
                    break;
                case CIRCUITO_REGISTROS_MENU_BORRAR_FANTASMA:
                    if (funcion_800B639C((s32) contrarreloj_indice_circuito_datos) < 0) {
                        variable_s1 = 1;
                    }
                    break;
            }
        }
        if (variable_s1 != 0) {
            fijar_color_texto(AZUL_TEXTO);
            gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, 0x96);
            imprimir_modo_texto_2(0x00000025, 0x3F + (0xD * i), opcion_menu_texto[i], 0, 0.6f, 0.6f);
        } else {
            fijar_color_texto(variable_s2);
            imprimir_modo_texto_1(0x00000025, 0x3F + (0xD * i), opcion_menu_texto[i], 0, 0.6f, 0.6f);
        }
    }
    sp78.column = 0x001F;
    sp78.row = (circuito_registros_menu_seleccion * 0xD) + 0x3A;
    funcion_800A66A8(parametro0, (desconocido_d_800E70A0*) &sp78);
}

void funcion_800A1DE0(MenuItem* parametro0) {
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    SIN_USO s32 margen_pila_3;
    desconocido_d_800E70A0 sp58;
    s32 variable_a0;
    SIN_USO s32 variable_s0;
    s32 variable_s1;
    SIN_USO char* wut;

    fijar_color_texto(VERDE_TEXTO);
    for (variable_s1 = 0; variable_s1 < 3; variable_s1++) {
        wut = borrar_mejor_fantasma_texto[(circuito_registros_menu_seleccion - 1) * 3 + variable_s1];
        imprimir_modo_texto_1(0x0000001B, 0x3C + (0xD * variable_s1),
                          borrar_mejor_fantasma_texto[(circuito_registros_menu_seleccion - 1) * 3 + variable_s1], 0, 0.65f, 0.65f);
    }

    for (variable_s1 = 0; variable_s1 < CANTIDAD_ARREGLO(dato_800E7840); variable_s1++) {
        wut = dato_800E7840[variable_s1];
        if (variable_s1 == circuito_registros_sub_menu_seleccion) {
            variable_a0 = 5;
        } else {
            variable_a0 = 1;
        }
        fijar_color_texto(variable_a0);
        imprimir_modo_texto_1(0x00000043, 0x6E + (0xD * variable_s1), dato_800E7840[variable_s1], 0, 0.65f, 0.65f);
    }

    sp58.column = 0x003B;
    sp58.row = (circuito_registros_sub_menu_seleccion * 0xD) + 0x66;
    funcion_800A66A8(parametro0, &sp58);
}

void funcion_800A1F30(SIN_USO MenuItem* unused) {
    s32 renglon;
    s32 text;

    fijar_color_texto(TEXTO_ROJO);
    for (renglon = 0x49, text = 0; renglon < 0x69; renglon += 0x10, text++) {
        imprimir_modo_texto_1(0x2A, renglon, dato_800E7860[text], 0, 0.75f, 0.75f);
    }
}

void funcion_800A1FB0(MenuItem* parametro0) {
    desconocido_d_800E70A0 sp_e0;
    s32 variable_s1;
    SIN_USO s32 relleno[2];
    SIN_USO s32 temporal_;
    SIN_USO s32 relleno2[2];
    s32 variable_s5;
    s32 variable_s4;
    s32 j;
    char sp_b8[3];
    SIN_USO s32 relleno3[2];
    s32 i;
    char sp_a8[3];
    SIN_USO s32 relleno4[3];
    char sp98[3];
    struct_8018EE10_entrada* variable_v1;

    display_list_cabeza = dibujar_caja(display_list_cabeza, 0, 0, 0x00000140, 0x000000F0, 0, 0, 0, 0x00000064);
    switch (seleccion_menu_sub) {
        case SUB_MENU_OPCION_RETORNO_JUEGO_SELECCION:
        case SUB_MENU_OPCION_SONIDO_MODO:
        case SUB_MENU_OPCION_COPIA_CONTROLLER_PAK:
        case SUB_MENU_OPCION_BORRAR_TODOS_DATOS:
            for (i = 0; i < CANTIDAD_ARREGLO(menu_opcion_texto); i++) {
                fijar_rainbow_color_texto_si_seleccionado(seleccion_menu_sub - SUB_MENU_OPCION_MIN, i, 3);
                imprimir_modo_texto_1(0x00000032, 0x55 + (0x23 * i), menu_opcion_texto[i], 0, 0.9f, 1.0f);
                if (i == (seleccion_menu_sub - SUB_MENU_OPCION_MIN)) {
                    sp_e0.column = 0x0032;
                    sp_e0.row = 0x55 + (0x23 * i);
                }
            }
            fijar_color_texto(VERDE_TEXTO);
            imprimir_modo_centro_texto1_1(0x000000E4, 0x55 + 0x23, sonido_nombres_modo[sonido_modo], 0, 1.0f, 1.0f);
            break;
        case SUB_MENU_BORRAR_ABANDONAR:
        case SUB_MENU_BORRAR_BORRAR:
            fijar_color_texto(AMARILLO_TEXTO);
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7878); i++) {
                imprimir_modo_texto_1(0x00000028, 0x55 + (0x14 * i), dato_800E7878[i], 0, 1.0f, 1.0f);
            }
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7840); i++) {
                fijar_rainbow_color_texto_si_seleccionado(seleccion_menu_sub - SUB_MENU_BORRAR_MIN, i, 1);
                imprimir_modo_texto_1(0x00000084, 0x96 + (0x19 * i), dato_800E7840[i], 0, 1.0f, 1.0f);
                if (i == (seleccion_menu_sub - SUB_MENU_BORRAR_MIN)) {
                    sp_e0.column = 0x0084;
                    sp_e0.row = 0x96 + (0x19 * i);
                }
            }
            break;
        case SUB_MENU_GUARDADO_DATOS_BORRADO:
            fijar_color_texto(AMARILLO_TEXTO);
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7884); i++) {
                imprimir_modo_texto_1(0x00000032, 0x55 + (0x14 * i), dato_800E7884[i], 0, 1.0f, 1.0f);
            }
            break;
        case SUB_MENU_COPIA_PAK_ERROR_SIN_FANTASMA_DATOS:
        case SUB_MENU_COPIA_PAK_ERROR_SIN_JUEGO_DATOS:
        case SUB_MENU_COPIA_PAK_ERROR_SIN_PAK_2P:
        case SUB_MENU_COPIA_PAK_ERROR_MALO_LECTURA_2P:
            fijar_color_texto(TEXTO_ROJO);
            variable_s1 = seleccion_menu_sub - SUB_MENU_COPIA_PAK_ERROR_2J_MIN;
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E78D0) / 4; i++) {
                imprimir_modo_texto_1(0x00000032, 0x55 + (0x14 * i), dato_800E78D0[(variable_s1 * 3) + i], 0, 0.9f, 0.9f);
            }
            break;
        case SUB_MENU_COPIA_PAK_ERROR_SIN_PAK_1P:
        case SUB_MENU_COPIA_PAK_ERROR_MALO_LECTURA_1P:
        case SUB_MENU_COPIA_PAK_ERROR_NO_PUEDE_CREAR_1P:
        case SUB_MENU_COPIA_PAK_ERROR_SIN_PAGINAS_1P:
            j++;
            j--;
            fijar_color_texto(TEXTO_ROJO);
            variable_s1 = seleccion_menu_sub - SUB_MENU_COPIA_PAK_ERROR_1J_MIN;
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7890) / 4; i++) {
                imprimir_modo_texto_1(0x00000023, 0x55 + (0x14 * i), dato_800E7890[(variable_s1 * 4) + i], 0, 0.8f, 0.8f);
            }
            break;
        case SUB_MENU_COPIA_PAK_INCAPAZ_COPIA_DESDE_1P:
        case SUB_MENU_COPIA_PAK_INCAPAZ_LECTURA_DESDE_2P:
            fijar_color_texto(TEXTO_ROJO);
            variable_s1 = seleccion_menu_sub - SUB_MENU_COPIA_PAK_INCAPAZ_ERROR_MIN;
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7900) / 2; i++) {
                imprimir_modo_texto_1(0x00000041, 0x55 + (0x14 * i), dato_800E7900[(variable_s1 * 3) + i], 0, 0.9f, 0.9f);
            }
            break;
        case SUB_MENU_COPIA_PAK_CREAR_JUEGO_DATOS_INICIALIZACION:
        case SUB_MENU_COPIA_PAK_CREAR_JUEGO_DATOS_HECHO:
            fijar_color_texto(AMARILLO_TEXTO);
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7A48); i++) {
                imprimir_modo_texto_1(0x00000050, 0x55 + (0x14 * i), dato_800E7A48[i], 0, 1.0f, 1.0f);
            }
            break;
        case SUB_MENU_COPIA_PAK_DESDE_GHOST1_1P:
        case SUB_MENU_COPIA_PAK_DESDE_GHOST2_1P:
        case SUB_MENU_COPIA_PAK_A_GHOST1_2P:
        case SUB_MENU_COPIA_PAK_A_GHOST2_2P:
            switch (seleccion_menu_sub) {
                case SUB_MENU_COPIA_PAK_DESDE_GHOST1_1P:
                case SUB_MENU_COPIA_PAK_DESDE_GHOST2_1P:
                    variable_s5 = SUB_MENU_COPIA_PAK_DESDE_MIN_FANTASMA;
                    variable_s4 = 0;
                    break;
                case SUB_MENU_COPIA_PAK_A_GHOST1_2P:
                case SUB_MENU_COPIA_PAK_A_GHOST2_2P:
                    variable_s5 = SUB_MENU_COPIA_PAK_A_MIN_FANTASMA;
                    variable_s4 = 1;
                default:
                    break;
            }
            temporal_ = variable_s4;
            fijar_color_texto(temporal_ + 1);
            imprimir_modo_centro_texto1_1(0x000000A0, 0x00000055, dato_800E7920[temporal_], 0, 0.6f, 0.6f);
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7918); i++) {
                fijar_color_texto(AMARILLO_TEXTO);
                imprimir_modo_centro_texto1_1(0x5C + (0x82 * i), 0x0000007D, dato_800E7918[i], 0, 0.75f, 0.75f);
                for (j = 0; j < 2; j++) {
                    if (i != temporal_) {
                        efecto_rainbow_texto(seleccion_menu_sub - variable_s5, j, VERDE_TEXTO);
                        if (j == (seleccion_menu_sub - variable_s5)) {
                            sp_e0.column = 0x20 + (0x89 * i);
                            sp_e0.row = 0x96 + (0x1E * j);
                        }
                    } else if ((temporal_ != 0) && (j == parametro0->param2)) {
                        fijar_color_texto((s32) temporizador_global % 3);
                    } else {
                        fijar_color_texto(VERDE_TEXTO);
                    }
                    convertir_numero_a_ascii(j + 1, &sp_b8[0]);
                    imprimir_modo_texto_1(0x20 + (0x89 * i), 0x96 + (0x1E * j), &sp_b8[1], 0, 0.6f, 0.6f);
                    if (i == 0) {
                        variable_v1 = &dato_8018EE10[j];
                    } else {
                        variable_v1 = &((struct_8018EE10_entrada*) algun_buffer_dl)[j];
                    }
                    if (variable_v1->fantasma_datos_guardado == 0) {
                        imprimir_modo_texto_1(0x2A + (i * 0x89), 0x96 + (0x1E * j), dato_800E7A44, 0, 0.5f, 0.5f);
                    } else {
                        imprimir_modo_texto_1(
                            0x2A + (i * 0x89), 0x96 + (0x1E * j),
                            duplicar_nombres_circuito_2[orden_circuito_copa[variable_v1->indice_circuito / 4][variable_v1->indice_circuito % 4]], 0,
                            0.5f, 0.5f);
                    }
                }
            }
            break;
        case SUB_MENU_COPIA_PAK_AVISO_ABANDONAR:
        case SUB_MENU_COPIA_PAK_AVISO_COPIA:
            fijar_color_texto(TEXTO_ROJO);
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7928); i++) {
                imprimir_modo_centro_texto1_1(0x000000A0, 0x4D + (0x14 * i), dato_800E7928[i], 0, 0.8f, 0.8f);
            }
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7918); i++) {
                fijar_color_texto(AMARILLO_TEXTO);
                imprimir_modo_centro_texto1_1(0x5C + (0x82 * i), 0x0000007D, dato_800E7918[i], 0, 0.75f, 0.75f);
                for (j = 0; j != 2; j++) {
                    if (i == 0) {
                        if (j == parametro0->param1) {
                            fijar_color_texto((s32) temporizador_global % 3);
                        } else {
                            fijar_color_texto(VERDE_TEXTO);
                        }
                    } else if (j == parametro0->param2) {
                        fijar_color_texto((s32) temporizador_global % 3);
                    } else {
                        fijar_color_texto(VERDE_TEXTO);
                    }
                    convertir_numero_a_ascii(j + 1, &sp_a8[0]);
                    imprimir_modo_texto_1(0x20 + (0x89 * i), 0x96 + (0x1E * j), &sp_a8[1], 0, 0.6f, 0.6f);
                    if (i == 0) {
                        do {
                        } while (0);
                        variable_v1 = &dato_8018EE10[j];
                    } else {
                        variable_v1 = &((struct_8018EE10_entrada*) algun_buffer_dl)[j];
                    }
                    if (variable_v1->fantasma_datos_guardado == 0) {
                        imprimir_modo_texto_1(0x2A + (i * 0x89), 0x96 + (0x1E * j), dato_800E7A44, 0, 0.5f, 0.5f);
                    } else {
                        imprimir_modo_texto_1(
                            0x2A + (i * 0x89), 0x96 + (0x1E * j),
                            duplicar_nombres_circuito_2[orden_circuito_copa[variable_v1->indice_circuito / 4][variable_v1->indice_circuito % 4]], 0,
                            0.5f, 0.5f);
                    }
                }
            }
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7930); i++) {
                if (i == (seleccion_menu_sub - SUB_MENU_COPIA_PAK_AVISO_MIN)) {
                    sp_e0.column = 0x6E + (0x32 * i);
                    sp_e0.row = 0x00D2;
                }
                efecto_rainbow_texto((seleccion_menu_sub - SUB_MENU_COPIA_PAK_AVISO_MIN), j, AMARILLO_TEXTO);
                imprimir_modo_texto_1(0x6E + (0x32 * i), 0x000000D2, dato_800E7930[i], 0, 0.75f, 0.75f);
            }
            break;
        case SUB_MENU_COPIA_PAK_INICIO:
        case SUB_MENU_COPIA_PAK_COPIANDO:
        case SUB_MENU_COPIA_PAK_COMPLETADO:
            variable_s5 = (seleccion_menu_sub - SUB_MENU_COPIA_PAK_ACCION_MIN) / 2;
            fijar_color_texto(TEXTO_ROJO);
            imprimir_modo_centro_texto1_1(0x000000A0, 0x00000055, dato_800E7938[variable_s5], 0, 1.0f, 1.0f);
            for (i = 0; i < CANTIDAD_ARREGLO(dato_800E7918); i++) {
                fijar_color_texto(AMARILLO_TEXTO);
                imprimir_modo_centro_texto1_1(0x5C + (0x82 * i), 0x0000007D, dato_800E7918[i], 0, 0.75f, 0.75f);
                for (j = 0; j < 2; j++) {
                    if (i == 0) {
                        if (j == parametro0->param1) {
                            if (variable_s5 == 0) {
                                fijar_color_texto(TEXTO_ROJO);
                            } else {
                                fijar_color_texto(temporizador_global % 3);
                            }
                        } else {
                            fijar_color_texto(VERDE_TEXTO);
                        }
                    } else if (j == parametro0->param2) {
                        fijar_color_texto(TEXTO_ROJO);
                    } else {
                        fijar_color_texto(VERDE_TEXTO);
                    }
                    convertir_numero_a_ascii(j + 1, &sp98[0]);
                    imprimir_modo_texto_1(0x20 + (0x89 * i), 0x96 + (0x1E * j), &sp98[1], 0, 0.6f, 0.6f);
                    if (i == 0) {
                        variable_v1 = &dato_8018EE10[j];
                    } else {
                        variable_v1 = &((struct_8018EE10_entrada*) algun_buffer_dl)[j];
                    }
                    if (variable_v1->fantasma_datos_guardado == 0) {
                        imprimir_modo_texto_1(0x2A + (i * 0x89), 0x96 + (0x1E * j), dato_800E7A44, 0, 0.5f, 0.5f);
                    } else {
                        imprimir_modo_texto_1(
                            0x2A + (i * 0x89), 0x96 + (0x1E * j),
                            duplicar_nombres_circuito_2[orden_circuito_copa[variable_v1->indice_circuito / 4][variable_v1->indice_circuito % 4]], 0,
                            0.5f, 0.5f);
                    }
                }
            }
            break;
    }
    switch (seleccion_menu_sub) {
        case SUB_MENU_COPIA_PAK_DESDE_GHOST1_1P:
        case SUB_MENU_COPIA_PAK_DESDE_GHOST2_1P:
        case SUB_MENU_COPIA_PAK_A_GHOST1_2P:
        case SUB_MENU_COPIA_PAK_A_GHOST2_2P:
        case SUB_MENU_COPIA_PAK_AVISO_ABANDONAR:
        case SUB_MENU_COPIA_PAK_AVISO_COPIA:
            sp_e0.column -= 5;
            sp_e0.row -= 6;
            break;
        default:
            sp_e0.column -= 0xA;
            sp_e0.row -= 8;
            break;
    }
    funcion_800A66A8(parametro0, (desconocido_d_800E70A0*) &sp_e0);
}

void funcion_800A2D1C(MenuItem* parametro0) {
    switch (dato_80164A28) {
        case 1:
            display_list_cabeza = funcion_80098FC8(display_list_cabeza, 0, 0, 0x13F, 0x28);
            display_list_cabeza = funcion_80098FC8(display_list_cabeza, 0, 0xC7, 0x13F, 0xEF);
            parametro0->param1 = 0x28;
            break;
        case 2:
            parametro0->param1 -= 2;
            if (parametro0->param1 > 0) {
                display_list_cabeza = funcion_80098FC8(display_list_cabeza, 0, 0, 0x13F, parametro0->param1);
                display_list_cabeza = funcion_80098FC8(display_list_cabeza, 0, 0xEF - parametro0->param1, 0x13F, 0xEF);
            } else {
                parametro0->type = 0;
            }
            break;
        default:
            if ((seleccion_modo != GRAN_PREMIO) || (seleccion_cantidad_jugador_1 != 1) || (mando_usar_demo != 0)) {
                parametro0->type = 0;
            } else {
                parametro0->param1 -= 2;
                if (parametro0->param1 > 0) {
                    display_list_cabeza = funcion_80098FC8(display_list_cabeza, 0, 0, 0x13F, parametro0->param1);
                    display_list_cabeza = funcion_80098FC8(display_list_cabeza, 0, 0xEF - parametro0->param1, 0x13F, 0xEF);
                } else {
                    parametro0->type = 0;
                }
            }
            break;
    }
}

void funcion_800A2EB8(MenuItem* parametro0) {
    s8 sp70[8];
    SIN_USO s32 margen_pila_0;
    char sp68[3];
    s32 temporal_s0;
    s32 variable_a0;
    s32 variable_s2;

    for (variable_s2 = 0; variable_s2 < JUGADORES_NUM; variable_s2++) {
        sp70[variable_s2] = jugadores[gp_actual_carrera_jugador_id_por_puesto[variable_s2]].id_personaje;
    }
    fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_1);
    imprimir_modo_texto_1(parametro0->column + 0x1E, parametro0->row + 0x19, "results", 0, 1.0f, 1.0f);
    fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_2);
    imprimir_modo_texto_1(parametro0->column + 0x2C, parametro0->row + 0x28, "round", 0, 0.7f, 0.7f);
    convertir_numero_a_ascii(indice_circuito_en_copa + 1, sp68);
    imprimir_modo_texto_1(parametro0->column + 0x57, parametro0->row + 0x28, &sp68[1], 0, 0.7f, 0.7f);
    for (variable_s2 = 0; variable_s2 < 4; variable_s2++) {
        if (gp_actual_carrera_jugador_id_por_puesto[variable_s2] < cantidad_jugador) {
            variable_a0 = (s32) temporizador_global % 3;
        } else {
            variable_a0 = AMARILLO_TEXTO;
        }
        fijar_color_texto(variable_a0);
        funcion_800A32B4(parametro0->column + 7, parametro0->row + (0x10 * variable_s2) + 0x38, (s32) sp70[variable_s2], variable_s2);
    }
    for (variable_s2 = 4; variable_s2 < 8; variable_s2++) {
        if (gp_actual_carrera_jugador_id_por_puesto[variable_s2] < cantidad_jugador) {
            variable_a0 = (s32) temporizador_global % 3;
        } else {
            variable_a0 = AMARILLO_TEXTO;
        }
        fijar_color_texto(variable_a0);
        funcion_800A32B4(0xBE - parametro0->column, parametro0->row + (0x10 * variable_s2) + 0x5A, sp70[variable_s2], variable_s2);
    }
    fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_2);
    temporal_s0 = (s32) (((f32) (obtener_ancho_cadena(nombres_copa[seleccion_copa]) + 8) * 0.6f) / 2);
    imprimir_modo_centro_texto1_1(
        (-(s32) (((f32) (obtener_ancho_cadena(dato_800E76CC[seleccion_cc]) + 8) * 0.6f) / 2) - parametro0->column) + 0xF5,
        parametro0->row + 0xE1, nombres_copa[dato_800DC540], 0, 0.6f, 0.6f);
    imprimir_modo_centro_texto1_1(
        (temporal_s0 - parametro0->column) + 0xF5, parametro0->row + 0xE1,
        dato_800E76CC[juego_modo_sub_menu_columna[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]]], 0, 0.6f, 0.6f);
}

void funcion_800A32B4(s32 parametro0, s32 parametro1, s32 id_personaje, s32 puesto) {
    SIN_USO s32 margen_pila_0;
    f32 sp50;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    SIN_USO s32 margen_pila_3;
    SIN_USO s32 margen_pila_4;
    char sp3_c[4];

    sp50 = tiempo_jugador_ultimo_tocado_linea_meta[gp_actual_carrera_jugador_id_por_puesto[puesto]];
    convertir_numero_a_ascii(puesto + 1, sp3_c);
    sp3_c[2] = '.';
    sp3_c[3] = '\0';
    funcion_800939C8(parametro0 - 1, parametro1, &sp3_c[1], -4, 0.7f, 0.7f);
    imprimir_modo_texto_1(parametro0 + 0xA, parametro1, dato_800E76A8[id_personaje], 0, 0.65f, 0.7f);
    convertir_numero_a_ascii((s32) (sp50 / 60.0f), sp3_c);
    funcion_800939C8(parametro0 + 0x42, parametro1, sp3_c, 0, 0.7f, 0.7f);
    convertir_numero_a_ascii((s32) sp50 % 60, sp3_c);
    imprimir_modo_texto_1(parametro0 + 0x4E, parametro1, "'", 0, 0.7f, 0.7f);
    funcion_800939C8(parametro0 + 0x56, parametro1, sp3_c, 0, 0.7f, 0.7f);
    convertir_numero_a_ascii((s32) ((f64) sp50 * 100.0) % 100, sp3_c);
    imprimir_modo_texto_1(parametro0 + 0x62, parametro1, "\"", 0, 0.7f, 0.7f);
    funcion_800939C8(parametro0 + 0x6A, parametro1, sp3_c, 0, 0.7f, 0.7f);
}

void funcion_800A34A8(MenuItem* parametro0) {
    s8 sp80[8];
    SIN_USO s32 margen_pila_0;
    char sp78[3];
    SIN_USO s32 margen_pila_1;
    s32 variable_a0;
    s32 variable_v0;
    s32 variable_v1;
    SIN_USO s32 margen_pila_2;
    s32 temporal_s0_3;
    s32 puesto;
    s32 probar;

    if (parametro0->state != 0) {
        if (parametro0->state < 9) {
            for (puesto = 0; puesto < JUGADORES_NUM; puesto++) {
                sp80[puesto] = jugadores[gp_actual_carrera_jugador_id_por_puesto[puesto]].id_personaje;
            }
        } else {
            funcion_800A3A10(sp80);
            funcion_800A3A10(id_personaje_por_puesto_total_gp);
        }
        fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_1);
        imprimir_modo_texto_1(parametro0->column + 0x19, 0x19 - parametro0->row, "driver's points", 0, 0.8f, 0.8f);
        fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_2);
        imprimir_modo_texto_1(parametro0->column + 0x36, 0x28 - parametro0->row, "round", 0, 0.7f, 0.7f);
        convertir_numero_a_ascii(indice_circuito_en_copa + 1, sp78);
        imprimir_modo_texto_1(parametro0->column + 0x61, (0x28 & 0xFFFFFFFF) - parametro0->row, &sp78[1], 0, 0.7f, 0.7f);
        for (puesto = 0; puesto < 4; puesto++) {
            probar = parametro0->state;
            if ((probar != 8) && (probar != 9)) {
                variable_v0 = 0;
            } else {
                if ((puesto * 5) < parametro0->param1) {
                    variable_v0 = 1;
                } else {
                    variable_v0 = 0;
                }
            }
            if (variable_v0 == 0) {
                if (parametro0->state < 9) {
                    variable_v0 = gp_actual_carrera_jugador_id_por_puesto[puesto];
                    variable_v1 = 0;
                } else {
                    variable_v1 = 0x0000000D;
                    variable_v0 = jugador_obtener_por_id_personaje[sp80[puesto]];
                }
                if (variable_v0 < cantidad_jugador) {
                    variable_a0 = (s32) temporizador_global % 3;
                } else {
                    variable_a0 = 3;
                }
                fijar_color_texto(variable_a0);
                funcion_800A3ADC(parametro0, parametro0->column + variable_v1 + 0x1C, ((puesto * 0x10) - parametro0->row) + 0x38, sp80[puesto], puesto,
                              sp80);
            }
        }
        for (puesto = 4; puesto < JUGADORES_NUM; puesto++) {
            probar = parametro0->state;
            if ((probar != 8) && (probar != 9)) {
                variable_v0 = 0;
            } else {
                if ((puesto * 5) < parametro0->param1) {
                    variable_v0 = 1;
                } else {
                    variable_v0 = 0;
                }
            }
            if (variable_v0 == 0) {
                if (parametro0->state < 9) {
                    variable_v0 = gp_actual_carrera_jugador_id_por_puesto[puesto];
                } else {
                    variable_v0 = jugador_obtener_por_id_personaje[sp80[puesto]];
                }
                if (variable_v0 < cantidad_jugador) {
                    variable_a0 = (s32) temporizador_global % 3;
                } else {
                    variable_a0 = 3;
                }
                fijar_color_texto(variable_a0);
                funcion_800A3ADC(parametro0, 0xBE - parametro0->column, parametro0->row + (puesto * 0x10) + 0x5A, sp80[puesto], puesto, sp80);
            }
        }
        fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_2);
        temporal_s0_3 = ((obtener_ancho_cadena(nombres_copa[seleccion_copa]) + 8) * 0.6f) / 2;
        imprimir_modo_centro_texto1_1(
            (-(s32) (((obtener_ancho_cadena(dato_800E76CC[seleccion_cc]) + 8) * 0.6f) / 2) - parametro0->column) + 0xE6,
            parametro0->row + 0xE1, nombres_copa[dato_800DC540], 0, 0.6f, 0.6f);
        imprimir_modo_centro_texto1_1(
            (temporal_s0_3 - parametro0->column) + 0xE6, parametro0->row + 0xE1,
            dato_800E76CC[juego_modo_sub_menu_columna[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]]], 0, 0.6f, 0.6f);
    }
}

void funcion_800A3A10(s8* parametro0) {
    s32 temporal_a3;
    s32 temporal_t1;
    s32 variable_a1;
    s32 variable_v0;
    SIN_USO s32 cosa1;
    SIN_USO s8* variable_nuevo;

    for (variable_v0 = 0; variable_v0 < 8; variable_v0++) {
        parametro0[variable_v0] = variable_v0;
        for (variable_a1 = variable_v0; variable_a1 > 0; variable_a1--) {
            variable_nuevo = &parametro0[variable_a1];
            temporal_a3 = parametro0[variable_a1 - 1];
            cosa1 = puntos_gp_por_id_personaje[temporal_a3];
            temporal_t1 = parametro0[variable_a1];
            if (puntos_gp_por_id_personaje[temporal_a3] < puntos_gp_por_id_personaje[temporal_t1]) {
                parametro0[variable_a1] = temporal_a3;
                parametro0[variable_a1 - 1] = temporal_t1;
            } else if (puntos_gp_por_id_personaje[temporal_t1] == puntos_gp_por_id_personaje[temporal_a3]) {
                if ((jugador_obtener_por_id_personaje[temporal_t1] < cantidad_jugador) &&
                    (jugador_obtener_por_id_personaje[temporal_t1] < jugador_obtener_por_id_personaje[temporal_a3])) {
                    parametro0[variable_a1] = temporal_a3;
                    parametro0[variable_a1 - 1] = temporal_t1;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }
}

void funcion_800A3ADC(MenuItem* parametro0, s32 parametro1, s32 parametro2, s32 id_personaje, s32 parametro4, s8* parametro5) {
    SIN_USO s32 margen_pila_0;
    s32 wut;
    char sp34[4];
    s32 phi_v1;

    if (parametro0->state < 9) {
        convertir_numero_a_ascii(parametro4 + 1, sp34);
    } else {
        for (phi_v1 = parametro4; phi_v1 > 0; phi_v1--) {
            wut = phi_v1 - 1;
            if (puntos_gp_por_id_personaje[parametro5[phi_v1]] != puntos_gp_por_id_personaje[parametro5[wut]]) {
                break;
            }
        }
        convertir_numero_a_ascii(phi_v1 + 1, sp34);
    }
    sp34[2] = '.';
    sp34[3] = '\0';
    funcion_800939C8(parametro1, parametro2, &sp34[1], -4, 0.7f, 0.7f);
    imprimir_modo_texto_1(parametro1 + 0xA, parametro2, dato_800E76A8[id_personaje], 0, 0.7f, 0.7f);
    convertir_numero_a_ascii(puntos_gp_por_id_personaje[id_personaje], sp34);
    funcion_800939C8(parametro1 + 0x47, parametro2, sp34, 0, 0.7f, 0.7f);
    if ((parametro4 < CANTIDAD_ARREGLO(premios_punto_gp)) && (parametro0->state < 9)) {
        convertir_numero_a_ascii(copia_puntos_gp[parametro4], sp34);
        sp34[0] = '+';
        imprimir_modo_texto_1(parametro1 + 0x5A, parametro2, sp34, 0, 0.7f, 0.7f);
    }
}

void renderizar_contrarreloj_texto_meta(MenuItem* parametro0) {
    s32 grabar_tipo;
    s32 desplazamiento_renglon;

    fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_1);
    imprimir_modo_centro_texto1_1(parametro0->column + 0x43, parametro0->row + 0x19,
                              duplicar_nombres_circuito[orden_circuito_copa[seleccion_copa][indice_circuito_en_copa]], 0, 0.6f, 0.6f);

    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_centro_texto1_1(parametro0->column + 0x46, parametro0->row + 0x28, texto_tiempo_vuelta, 0, 0.75f, 0.75f);

    for (grabar_tipo = 0, desplazamiento_renglon = 0; grabar_tipo < CONTRARRELOJ_3LAP_REGISTRO_5; grabar_tipo += 1, desplazamiento_renglon += 0xF) {
        renderizar_tiempo_vuelta(grabar_tipo, parametro0->column + 0x17, parametro0->row + desplazamiento_renglon + 0x37);
    }

    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_texto_1(0xB4 - parametro0->column, parametro0->row + 0x86, texto_tiempo_mejor[0], 0, 0.75f, 0.75f);

    for (grabar_tipo = 0, desplazamiento_renglon = 0; grabar_tipo < CONTRARRELOJ_1LAP_REGISTRO; grabar_tipo += 1, desplazamiento_renglon += 0xD) {
        fijar_color_texto(TEXTO_ROJO);
        renderizar_veces_vuelta(grabar_tipo, 0xAA - parametro0->column, parametro0->row + desplazamiento_renglon + 0x92);
    }
    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_texto_1(0xB4 - parametro0->column, parametro0->row + 0xD5, texto_tiempo_mejor[1], 0, 0.75f, 0.75f);
    renderizar_veces_vuelta(CONTRARRELOJ_1LAP_REGISTRO, 0xAA - parametro0->column, parametro0->row + 0xE1);
}

void funcion_800A3E60(MenuItem* parametro0) {
    SIN_USO s32 margen_pila_0;
    desconocido_d_800E70A0 sp84;
    SIN_USO s32 margen_pila_1;
    SIN_USO s32 margen_pila_2;
    SIN_USO s32 margen_pila_3;
    SIN_USO s32 margen_pila_4;
    s32 variable_v0;
    s32 variable_v1;
    s32 variable_s1;
    desconocido_d_800E70A0* variable_v0_5;
    char sp60[3];

    variable_v0 = parametro0->state;
    if (variable_v0 == 0) {
        return;
    }
    if (variable_v0 == 0x0000001F) {
        return;
    }

    fijar_color_texto(TEXTO_AZUL_VERDE_ROJO_CICLO_1);
    imprimir_modo_centro_texto1_1(parametro0->column + 0x55, 0x19 - parametro0->row,
                              duplicar_nombres_circuito[orden_circuito_copa[seleccion_copa][indice_circuito_en_copa]], 0, 0.6f, 0.6f);
    fijar_color_texto(AMARILLO_TEXTO);
    imprimir_modo_centro_texto1_1(parametro0->column + 0x55, 0x28 - parametro0->row, texto_tiempo_vuelta, 0, 0.75f, 0.75f);
    for (variable_s1 = 0; variable_s1 < 4; variable_s1++) {
        renderizar_tiempo_vuelta(variable_s1, parametro0->column + 0x26, ((0xF * variable_s1) - parametro0->row) + 0x37);
    }
    switch (parametro0->state) {
        case 1:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 30:
            for (variable_s1 = 0; variable_s1 < 6; variable_s1++) {
                variable_v1 = 0;
                efecto_rainbow_texto(parametro0->state - 5, variable_s1, 1);
                switch (variable_s1) {
                    case 4:
                        if (publicar_contrarreloj_guardado_no_puede_repeticion == 1) {
                            variable_v1 = 1;
                        }
                        break;
                    case 5:
                        if (b_jugador_fantasma_desactivado != 0) {
                            variable_v1 = 2;
                        }
                        break;
                }
                if (variable_v1 != 0) {
                    fijar_color_texto(AZUL_TEXTO);
                    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, 0x96);
                    imprimir_modo_texto_2(0xB2 - parametro0->column, parametro0->row + (0xD * variable_s1) + 0x93,
                                      boton_pausa_texto[variable_s1 + 1], 0, 0.75f, 0.75f);
                } else {
                    imprimir_modo_texto_1(0xB2 - parametro0->column, parametro0->row + (0xD * variable_s1) + 0x93,
                                      boton_pausa_texto[variable_s1 + 1], 0, 0.75f, 0.75f);
                }
            }
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            fijar_color_texto(AMARILLO_TEXTO);
            variable_v1 = parametro0->state - 11;
            for (variable_s1 = 0; variable_s1 < 7; variable_s1++) {
                imprimir_modo_texto_1(0x000000A2, 0x8C + (0xD * variable_s1), dato_800E798C[(variable_v1 * 7) + variable_s1], 0, 0.6f, 0.6f);
            }
            break;
        case 17:
        case 18:
            fijar_color_texto(VERDE_TEXTO);
            for (variable_s1 = 0; variable_s1 < 2; variable_s1++) {
                imprimir_modo_texto_1(0x000000A5, parametro0->row + (0xD * variable_s1) + 0x8C, dato_800E7A3C[variable_s1], 0, 0.7f, 0.7f);
            }
            for (variable_s1 = 0; variable_s1 < 2; variable_s1++) {
                efecto_rainbow_texto(parametro0->state - 0x11, variable_s1, 1);
                convertir_numero_a_ascii(variable_s1 + 1, sp60);
                imprimir_modo_texto_1(0xB1 - parametro0->column, 0xAA + (0x1E * variable_s1), &sp60[1], 0, 0.6f, 0.6f);
                if (dato_8018EE10[variable_s1].fantasma_datos_guardado == 0) {
                    imprimir_modo_texto_1(0xBB - parametro0->column, 0xAA + (0x1E * variable_s1), dato_800E7A44, 0, 0.45f, 0.45f);
                } else {
                    imprimir_modo_texto_1(0xBB - parametro0->column, 0xAA + (0x1E * variable_s1),
                                      duplicar_nombres_circuito_2[orden_circuito_copa[dato_8018EE10[variable_s1].indice_circuito / 4]
                                                                      [dato_8018EE10[variable_s1].indice_circuito % 4]],
                                      0, 0.45f, 0.45f);
                }
            }
            break;
        case 19:
            fijar_color_texto(AMARILLO_TEXTO);
            for (variable_s1 = 0; variable_s1 < 3; variable_s1++) {
                imprimir_modo_texto_1(0x000000AA, (0xD * variable_s1) + 0x93, dato_800E7A48[variable_s1], 0, 0.8f, 0.8f);
            }
            break;
        case 20:
        case 21:
            if (variable_s1 && variable_s1) {}
            fijar_color_texto(AMARILLO_TEXTO);
            for (variable_s1 = 0; variable_s1 < 3; variable_s1++) {
                imprimir_modo_texto_1(0x000000A3, parametro0->row + (0xD * variable_s1) + 0x8C, dato_800E7A60[variable_s1], 0, 0.67f, 0.67f);
            }
            for (variable_s1 = 0; variable_s1 < 2; variable_s1++) {
                efecto_rainbow_texto(parametro0->state - 0x14, variable_s1, 1);
                imprimir_modo_texto_1(0xC8 - parametro0->column, 0xB9 + (0xF * variable_s1), dato_800E7A6C[variable_s1], 0, 0.75f, 0.75f);
            }
            break;
        case 25:
            fijar_color_texto(AMARILLO_TEXTO);
            for (variable_s1 = 0; variable_s1 < 3; variable_s1++) {
                imprimir_modo_texto_1(0x000000A3, (0xD * variable_s1) + 0x93, dato_800E7A74[variable_s1], 0, 0.67f, 0.67f);
            }
            break;
        case 26:
            fijar_color_texto(AMARILLO_TEXTO);
            for (variable_s1 = 0; variable_s1 < 2; variable_s1++) {
                imprimir_modo_texto_1(0x000000AA, (0xD * variable_s1) + 0x93, dato_800E7A80[variable_s1], 0, 0.75f, 0.75f);
            }
            break;
    }
    switch (parametro0->state) {
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            variable_v0_5 = &dato_800E7390[parametro0->state - 5];
            break;
        case 17:
        case 18:
            variable_v0_5 = &dato_800E73C0[parametro0->state - 17];
            break;
        case 20:
        case 21:
            variable_v0_5 = &dato_800E73D0[parametro0->state - 20];
            break;
        case 30:
            variable_v0_5 = &dato_800E7390[parametro0->param1 - 5];
            break;
        default:
            return;
    }
    sp84.column = variable_v0_5->column - parametro0->column;
    sp84.row = variable_v0_5->row + parametro0->row;
    funcion_800A66A8(parametro0, &sp84);
}

void renderizar_tiempo_vuelta(s32 numero_vuelta, s32 columna, s32 renglon) {
    SIN_USO s32 margen_pila_0;
    s32 time;
    SIN_USO s32 margen_pila_1;
    s32 color_texto;
    char sp34[3];
    MenuItem* temporal_v0_2;

    if (numero_vuelta < 3) {
        time = h_ud_jugador[JUGADOR_UNO].duraciones_vuelta[numero_vuelta];
        fijar_color_texto(TEXTO_ROJO);
    } else {
        time = h_ud_jugador[JUGADOR_UNO].algun_temporizador;
        fijar_color_texto(VERDE_TEXTO);
    }
    imprimir_izquierda_texto1(columna + 0x21, renglon, texto_tiempo_prefijo[numero_vuelta], 0, 0.7f, 0.7f);
    temporal_v0_2 = buscar_duplicado_items_menu(TIPO_ITEM_MENU_0BB);
    if (numero_vuelta < 3) {
        if (temporal_v0_2->param2 & (1 << numero_vuelta)) {
            color_texto = (s32) temporizador_global % 3;
        } else {
            color_texto = AMARILLO_TEXTO;
        }
    } else {
        if (temporal_v0_2->param1 >= 0) {
            color_texto = (s32) temporizador_global % 3;
        } else {
            color_texto = AMARILLO_TEXTO;
        }
    }
    fijar_color_texto(color_texto);
    obtener_minutos_registro_tiempo(time, sp34);
    funcion_800939C8(columna + 0x2C, renglon, sp34, 0, 0.7f, 0.7f);
    imprimir_modo_texto_1(columna + 0x37, renglon, "'", 0, 0.7f, 0.7f);
    obtener_segundos_registro_tiempo(time, sp34);
    funcion_800939C8(columna + 0x40, renglon, sp34, 0, 0.7f, 0.7f);
    imprimir_modo_texto_1(columna + 0x4B, renglon, "\"", 0, 0.7f, 0.7f);
    obtener_centesimas_registro_tiempo(time, sp34);
    funcion_800939C8(columna + 0x55, renglon, sp34, 0, 0.7f, 0.7f);
}
