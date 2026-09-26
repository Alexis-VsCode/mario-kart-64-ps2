// Menus principales

void controller_pak_act_menu(struct Mando* mando, SIN_USO u16 idx_mando) {
    u16 boton_y_palanca;
    OSPfsState* estado_pfs_os;
    s32 renglon_tabla_seleccionado;
    SIN_USO s8 relleno;

    boton_y_palanca = mando->boton_pulsado | mando->palanca_pulsado;
    if (es_pantalla_siendo_fundido() == 0) {
        switch (controller_pak_seleccion_menu) {
            case CONTROLLER_PAK_REGISTRO_SELECCION_MENU:
                if ((boton_y_palanca & (A_BUTTON | START_BUTTON)) != 0) {
                    controller_pak_seleccion_menu = CONTROLLER_PAK_MENU_TABLA_JUEGO_DATOS;
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                    return;
                }
                if ((boton_y_palanca & (L_JPAD | R_JPAD)) != 0) {
                    controller_pak_seleccion_menu = CONTROLLER_PAK_FIN_MENU;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    return;
                }
                break;
            case CONTROLLER_PAK_FIN_MENU:
                if ((boton_y_palanca & (A_BUTTON | START_BUTTON)) != 0) {
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                    funcion_8009E1C0();
                    controller_pak_1_estado = MALO;
                    return;
                }
                if ((boton_y_palanca & (L_JPAD | R_JPAD)) != 0) {
                    controller_pak_seleccion_menu = CONTROLLER_PAK_REGISTRO_SELECCION_MENU;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    return;
                }
                break;
            case CONTROLLER_PAK_MENU_TABLA_JUEGO_DATOS:
                if ((boton_y_palanca & (A_BUTTON | START_BUTTON)) != 0) {
                    renglon_tabla_seleccionado = controller_pak_renglones_tabla_visible[controller_pak_renglon_tabla_seleccionado + 2] - 1;
                    if (pfs_error[renglon_tabla_seleccionado] == 0) {
                        controller_pak_seleccion_menu = CONTROLLER_PAK_ABANDONAR_MENU;
                        reproducir_sonido2(SONIDO_SELECCION_MENU);
                        return;
                    }
                } else if ((boton_y_palanca & B_BUTTON) != 0) {
                    if (controller_pak_sentido_desplazamiento == CONTROLLER_PAK_NINGUNO_DIR_DESPLAZAMIENTO) {
                        controller_pak_seleccion_menu = CONTROLLER_PAK_REGISTRO_SELECCION_MENU;
                        reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                        return;
                    }
                } else if ((boton_y_palanca & U_JPAD) != 0) {
                    if (controller_pak_sentido_desplazamiento == CONTROLLER_PAK_NINGUNO_DIR_DESPLAZAMIENTO) {
                        --controller_pak_renglon_tabla_seleccionado;
                        if (controller_pak_renglon_tabla_seleccionado < 0) {
                            controller_pak_renglon_tabla_seleccionado = 0;
                            if (controller_pak_renglones_tabla_visible[controller_pak_renglon_tabla_seleccionado + 2] != 1) {
                                controller_pak_sentido_desplazamiento = CONTROLLER_PAK_ARRIBA_DIR_DESPLAZAMIENTO;
                                reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                                return;
                            }
                        } else {
                            reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                            return;
                        }
                    }
                } else if (((boton_y_palanca & D_JPAD) != 0) &&
                           (controller_pak_sentido_desplazamiento == CONTROLLER_PAK_NINGUNO_DIR_DESPLAZAMIENTO)) {
                    ++controller_pak_renglon_tabla_seleccionado;
                    if (controller_pak_renglon_tabla_seleccionado >= CONTROLLER_PAK_MENU_TABLA_JUEGO_DATOS) {
                        controller_pak_renglon_tabla_seleccionado = CONTROLLER_PAK_ABANDONAR_MENU;
                        if (controller_pak_renglones_tabla_visible[controller_pak_renglon_tabla_seleccionado + 2] != 16) {
                            controller_pak_sentido_desplazamiento = CONTROLLER_PAK_ABAJO_DIR_DESPLAZAMIENTO;
                            reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                            return;
                        }
                    } else {
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        return;
                    }
                }
                break;
            case CONTROLLER_PAK_ABANDONAR_MENU:
                if ((boton_y_palanca & (A_BUTTON | B_BUTTON | START_BUTTON)) != 0) {
                    controller_pak_seleccion_menu = CONTROLLER_PAK_MENU_TABLA_JUEGO_DATOS;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    return;
                }
                if ((boton_y_palanca & (L_JPAD | R_JPAD)) != 0) {
                    controller_pak_seleccion_menu = CONTROLLER_PAK_BORRAR_MENU;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    return;
                }
                break;
            case CONTROLLER_PAK_BORRAR_MENU:
                if ((boton_y_palanca & (A_BUTTON | START_BUTTON)) != 0) {
                    controller_pak_seleccion_menu = CONTROLLER_PAK_IR_MENU_A_BORRANDO;
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                    return;
                }
                if ((boton_y_palanca & B_BUTTON) != 0) {
                    controller_pak_seleccion_menu = CONTROLLER_PAK_MENU_TABLA_JUEGO_DATOS;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    return;
                }
                if ((boton_y_palanca & (L_JPAD | R_JPAD)) != 0) {
                    controller_pak_seleccion_menu = CONTROLLER_PAK_ABANDONAR_MENU;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    return;
                }
                break;
            case CONTROLLER_PAK_IR_MENU_A_BORRANDO:
                controller_pak_seleccion_menu = CONTROLLER_PAK_BORRANDO_MENU;
                return;
            case CONTROLLER_PAK_BORRANDO_MENU:
                renglon_tabla_seleccionado = controller_pak_renglones_tabla_visible[controller_pak_renglon_tabla_seleccionado + 2] - 1;
                estado_pfs_os = &estado_pfs[renglon_tabla_seleccionado];

                switch (osPfsDeleteFile(&controller_pak_manejador_1_archivo, estado_pfs_os->company_code, estado_pfs_os->game_code,
                                        (u8*) &estado_pfs_os->game_name, (u8*) &estado_pfs_os->ext_name)) {
                    default:
                        controller_pak_seleccion_menu = CONTROLLER_PAK_ERROR_BORRAR_MENU_NO_BORRADO;
                        return;
                    case 0:
                        pfs_error[renglon_tabla_seleccionado] = -1;
                        controller_pak_libre_paginas_1_num += (((estado_pfs_os->file_size + 0xFF) >> 8) & 0xFF);
                        controller_pak_seleccion_menu = CONTROLLER_PAK_MENU_TABLA_JUEGO_DATOS;
                        return;
                    case PFS_ERR_NOPACK:
                        controller_pak_seleccion_menu = CONTROLLER_PAK_MENU_BORRAR_ERROR_SIN_PAK;
                        return;
                    case PFS_ERR_NEW_PACK:
                        controller_pak_seleccion_menu = CONTROLLER_PAK_MENU_BORRAR_ERROR_PAK_CAMBIADO;
                        return;
                }
                break;
            case CONTROLLER_PAK_ERROR_BORRAR_MENU_NO_BORRADO:
            case CONTROLLER_PAK_MENU_BORRAR_ERROR_SIN_PAK:
            case CONTROLLER_PAK_MENU_BORRAR_ERROR_PAK_CAMBIADO:
                if ((boton_y_palanca & (A_BUTTON | START_BUTTON)) != 0) {
                    controller_pak_seleccion_menu = CONTROLLER_PAK_MENU_TABLA_JUEGO_DATOS;
                }
                break;
        }
    }
}

void act_menu_salpicadura(struct Mando* mando, u16 idx_mando) {
    u16 boton_y_palanca;
    u16 i;
    s32 es_depuracion;

    es_depuracion = true;
    boton_y_palanca = mando->boton_pulsado | mando->palanca_pulsado;

    if (es_pantalla_siendo_fundido() == 0) {
        if (idx_mando == JUGADOR_UNO) {
            temporizador_retardo_menu += 1;
        }
        switch (seleccion_menu_depuracion) {
            case DEPURACION_MENU_DESACTIVADO: {
                es_depuracion = false;
                if ((temporizador_retardo_menu >= 46) && (boton_y_palanca & (A_BUTTON | START_BUTTON))) {
                    funcion_8009E1C0();
                    funcion_800CA330(0x19);
                    reproducir_sonido2(SONIDO_MENU_ENTRAR_INTRO);
                } else {
                    break;
                }
                break;
            }
            case DEPURACION_MENU_DEPURACION_MODO: {
                if (boton_y_palanca & (R_JPAD | L_JPAD)) {
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (modo_depuracion_activacion) {
                        modo_depuracion_activacion = ALTERNAR_MODO_DEPURACION;
                    } else {
                        modo_depuracion_activacion = true;
                    }
                }
                if (boton_y_palanca & D_JPAD) {
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    seleccion_menu_depuracion = CIRCUITO_MENU_DEPURACION;
                }
                break;
            }
            case CIRCUITO_MENU_DEPURACION: {
                if (boton_y_palanca & R_JPAD) {
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (id_circuito_actual < (CIRCUITOS_NUM - 2)) {
                        id_circuito_actual += 1;
                    } else {
                        id_circuito_actual = 0;
                    }
                }
                if (boton_y_palanca & L_JPAD) {
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (id_circuito_actual > 0) {
                        id_circuito_actual -= 1;
                    } else {
                        id_circuito_actual = (CIRCUITOS_NUM - 2);
                    }
                }
                if (boton_y_palanca & U_JPAD) {
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    seleccion_menu_depuracion = DEPURACION_MENU_DEPURACION_MODO;
                }
                if (boton_y_palanca & D_JPAD) {
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    seleccion_menu_depuracion = DEPURACION_MENU_PANTALLA_MODO;
                }
                break;
            }
            case DEPURACION_MENU_PANTALLA_MODO: {
                if ((boton_y_palanca & R_JPAD) && (pantalla_modo_lista_indice < 4)) {
                    pantalla_modo_lista_indice += 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    seleccion_modo_pantalla = pantalla_modo_jugador_tabla[pantalla_modo_lista_indice];
                }
                if ((boton_y_palanca & L_JPAD) && (pantalla_modo_lista_indice > 0)) {
                    pantalla_modo_lista_indice -= 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    seleccion_modo_pantalla = pantalla_modo_jugador_tabla[pantalla_modo_lista_indice];
                }
                if (boton_y_palanca & U_JPAD) {
                    seleccion_menu_depuracion = CIRCUITO_MENU_DEPURACION;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                if (boton_y_palanca & D_JPAD) {
                    seleccion_menu_depuracion = JUGADOR_MENU_DEPURACION;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                break;
            }
            case JUGADOR_MENU_DEPURACION: {
                if ((boton_y_palanca & R_JPAD) && (selecciones_personaje[0] < 7)) {
                    selecciones_personaje[0] += 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                if ((boton_y_palanca & L_JPAD) && (selecciones_personaje[0] > 0)) {
                    selecciones_personaje[0] -= 1;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                if (boton_y_palanca & U_JPAD) {
                    seleccion_menu_depuracion = DEPURACION_MENU_PANTALLA_MODO;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                if (boton_y_palanca & D_JPAD) {
                    seleccion_menu_depuracion = DEPURACION_MENU_SONIDO_MODO;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                break;
            }
            case DEPURACION_MENU_SONIDO_MODO: {
                if ((boton_y_palanca & R_JPAD) && (sonido_modo < 3)) {
                    sonido_modo += 1;
                    if (sonido_modo == SONIDO_SIN_USO) {
                        sonido_modo = SONIDO_MONO;
                    }
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    fijar_modo_sonido();
                    datos_guardado.main.info_guardado.sonido_modo = sonido_modo;
                    guardar_datos_gran_premio_puntos_y_modo_sonido_escritura();
                    guardar_respaldo_datos_actualizacion();
                }
                if ((boton_y_palanca & L_JPAD) && (sonido_modo > 0)) {
                    sonido_modo -= 1;
                    if (sonido_modo == SONIDO_SIN_USO) {
                        sonido_modo = SONIDO_AURICULARES;
                    }
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    fijar_modo_sonido();
                    datos_guardado.main.info_guardado.sonido_modo = sonido_modo;
                    guardar_datos_gran_premio_puntos_y_modo_sonido_escritura();
                }
                if (boton_y_palanca & U_JPAD) {
                    seleccion_menu_depuracion = JUGADOR_MENU_DEPURACION;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                if (boton_y_palanca & D_JPAD) {
                    seleccion_menu_depuracion = DEPURACION_MENU_DAR_TODOS_ORO_COPA;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                break;
            }
            case DEPURACION_MENU_DAR_TODOS_ORO_COPA: {
                if (boton_y_palanca & U_JPAD) {
                    seleccion_menu_depuracion = DEPURACION_MENU_SONIDO_MODO;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                if (boton_y_palanca & B_BUTTON) {
                    for (i = 0; i < 16; i++) {
                        funcion_800B5404(0, i);
                    }
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                    break;
                } else if (boton_y_palanca & L_TRIG) {
                    guardar_datos_gran_premio_puntos_y_modo_sonido_reinicio();
                    for (i = 0; i < 16; i++) {
                        funcion_800B5404(i / 4, i);
                    }
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                    break;
                } else if (boton_y_palanca & L_JPAD) {
                    guardar_datos_gran_premio_puntos_y_modo_sonido_reinicio();
                    for (i = 0; i < 16; i++) {
                        if (i % 4 == 2) {
                            funcion_800B5404(0, i);
                        } else {
                            funcion_800B5404(i / 4, i);
                        }
                    }
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                } else {
                    break;
                }
                break;
            }
            default:
                break;
        }

        seleccion_cantidad_jugador_1 = cantidad_jugador = pantalla_modo_jugador_cantidad[pantalla_modo_lista_indice];

        if (es_depuracion) {
            if (boton_y_palanca & (A_BUTTON | START_BUTTON)) {
                funcion_8009E1C0();
                funcion_800CA330(0x19);
                seleccion_menu_depuracion = DEPURACION_MENU_OPCION_SELECCIONADO;

                if (mando->button & L_TRIG) {
                    modo_demo = ACTIVO_MODO_DEMO;
                } else {
                    modo_demo = INACTIVO_MODO_DEMO;
                }

                if (mando->button & Z_TRIG) {
                    if (boton_y_palanca & A_BUTTON) {
                        escena_goto_depuracion = FINAL_GOTO_DEPURACION;
                    } else {
                        escena_goto_depuracion = DEPURACION_GOTO_CREDITOS_SECUENCIA_EXTRA;
                    }
                }
                reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
            } else if ((boton_y_palanca & B_BUTTON) && (mando->button & Z_TRIG)) {
                funcion_8009E1C0();
                funcion_800CA330(0x19);
                seleccion_menu_depuracion = DEPURACION_MENU_OPCION_SELECCIONADO;
                escena_goto_depuracion = DEPURACION_GOTO_CREDITOS_SECUENCIA_PREDETERMINADO;
                reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
            } else if (boton_y_palanca & R_TRIG) {
                seleccion_menu_depuracion = DEPURACION_MENU_DESACTIVADO;
                reproducir_sonido2(SONIDO_SELECCION_MENU);
            }
        }
    }
}

void preparar_modo_juego_seleccionado(void) {
    s8 modo_menu_sub = juego_modo_sub_menu_columna[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]];
    switch (juego_modo_jugador_seleccion[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]]) {
        case GRAN_PREMIO:
            seleccion_cc = modo_menu_sub;
            cajas_item_lugar = 1;
            es_modo_espejo = (modo_menu_sub == CC_EXTRA) ? 1 : 0;
            break;
        case VERSUS:
            seleccion_cc = modo_menu_sub;
            cajas_item_lugar = 1;
            es_modo_espejo = (modo_menu_sub == CC_EXTRA) ? 1 : 0;
            break;
        case BATALLA:
            cajas_item_lugar = 1;
            es_modo_espejo = 0;
            break;
        case CONTRARRELOJ:
            seleccion_cc = CC_100;
            es_modo_espejo = 0;
            cajas_item_lugar = 0;

            if ((modo_menu_sub && modo_menu_sub) && modo_menu_sub) {}

            break;
    }
}

void menu_principal_act(struct Mando* mando, u16 idx_mando) {
    u16 boton_y_palanca;
    s32 modo_sub;
    bool cursor_movido;

    boton_y_palanca = mando->boton_pulsado | mando->palanca_pulsado;
    if ((modo_depuracion_activacion == 0) && (boton_y_palanca & START_BUTTON)) {
        boton_y_palanca |= A_BUTTON;
    }

    if (es_pantalla_siendo_fundido() == 0) {
        switch (menu_principal_seleccion) {
            case MENU_PRINCIPAL_NINGUNO:
                break;
            case MENU_PRINCIPAL_SELECCION_JUGADOR:
                if ((boton_y_palanca & R_JPAD) && (cantidad_jugador < 4)) {
                    cantidad_jugador += 1;
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                if ((boton_y_palanca & L_JPAD) && (cantidad_jugador >= 2)) {
                    cantidad_jugador -= 1;
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                seleccion_cantidad_jugador_1 = cantidad_jugador;
                switch (seleccion_cantidad_jugador_1) {
                    case 1:
                        seleccion_modo_pantalla = MODO_PANTALLA_1P;
                        break;
                    case 2:
                        seleccion_modo_pantalla = PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL;
                        break;
                    case 3:
                    case 4:
                        seleccion_modo_pantalla = PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA;
                        break;
                }
                if (boton_y_palanca & B_BUTTON) {
                    funcion_8009E0F0(0x14);
                    funcion_800CA330(0x19);
                    tipo_fundido_menu = MENU_FUNDIDO_TIPO_ATRAS;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    break;
                }
                if (boton_y_palanca & A_BUTTON) {
                    menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_MODO;
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                    break;
                }
                if (boton_y_palanca & L_TRIG) {
                    menu_principal_seleccion = MENU_PRINCIPAL_OPCION;
                    funcion_8009E280();
                    reproducir_sonido2(SONIDO_OPCION_MENU);
                    break;
                }
                if (boton_y_palanca & R_TRIG) {
                    menu_principal_seleccion = MENU_PRINCIPAL_DATOS;
                    funcion_8009E258();
                    reproducir_sonido2(SONIDO_DATOS_MENU);
                    break;
                }
                break;
            case MENU_PRINCIPAL_SELECCION_MODO:
                if (boton_y_palanca & D_JPAD) {
                    if (juego_modo_menu_columna[cantidad_jugador - 1] < seleccion_modo_jugador[cantidad_jugador - 1]) {
                        juego_modo_menu_columna[cantidad_jugador - 1] += 1;
                        reiniciar_menu_destello_ciclo();
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    }
                }
                if (boton_y_palanca & U_JPAD) {
                    if (juego_modo_menu_columna[cantidad_jugador - 1] > 0) {
                        juego_modo_menu_columna[cantidad_jugador - 1] -= 1;
                        reiniciar_menu_destello_ciclo();
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    }
                }
                if (boton_y_palanca & B_BUTTON) {
                    menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_JUGADOR;
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    break;
                }

                if (boton_y_palanca & A_BUTTON) {
                    switch (juego_modo_jugador_seleccion[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]]) {
                        default:
                            menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_OK;
                            break;
                        case 0:
                            menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_SUB_MODO;
                            reproducir_sonido2(SONIDO_GP_MENU);
                            break;
                        case 2:
                            menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_SUB_MODO;
                            reproducir_sonido2(SONIDO_MENU_VERSUS);
                            break;
                        case 1:
                            menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_SUB_MODO;
                            reproducir_sonido2(SONIDO_MENU_CONTRARRELOJ);
                            break;
                        case 3:
                            menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_OK;
                            reproducir_sonido2(SONIDO_BATALLA_MENU);
                            break;
                    }
                    reiniciar_menu_destello_ciclo();
                    contador_tiempos_menu = 0;
                    break;
                }
                break;
            case MENU_PRINCIPAL_SELECCION_SUB_MODO:
            case MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS:
                if (idx_mando == JUGADOR_UNO) {
                    contador_tiempos_menu++;
                    if ((contador_tiempos_menu == 100) || !(contador_tiempos_menu % 300)) {
                        switch (juego_modo_jugador_seleccion[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]]) {
                            case 0:
                            case 2:
                                reproducir_sonido2(SONIDO_NIVEL_SELECCION_MENU);
                                break;
                            default:
                                break;
                        }
                    }
                }

                modo_sub = juego_modo_sub_menu_columna[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]];
                if ((boton_y_palanca & U_JPAD) && (modo_sub > 0)) {
                    juego_modo_sub_menu_columna[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]] -= 1;
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                if (boton_y_palanca & D_JPAD) {
                    cursor_movido = false;
                    if (tiene_modo_extra_desbloqueado()) {
                        if (modo_sub < juego_modo_jugador_columna_extra[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]]) {
                            cursor_movido = true;
                        }
                    } else {
                        if (modo_sub < juego_modo_jugador_columna_predeterminado[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]]) {
                            cursor_movido = true;
                        }
                    }
                    if (cursor_movido) {
                        juego_modo_sub_menu_columna[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]]++;
                        reiniciar_menu_destello_ciclo();
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    }
                }
                modo_sub = juego_modo_sub_menu_columna[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]];

                if (boton_y_palanca & B_BUTTON) {
                    menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_MODO;
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    break;
                }
                if (boton_y_palanca & A_BUTTON) {
                    reiniciar_menu_destello_ciclo();
                    if ((cantidad_jugador == 1) && ((juego_modo_menu_columna - 1)[cantidad_jugador] == 1) && (modo_sub == 1)) {
                        funcion_8009E258();
                        reproducir_sonido2(SONIDO_DATOS_MENU);
                    } else {
                        menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_OK;
                        reproducir_sonido2(SONIDO_SELECCION_MENU);
                        contador_tiempos_menu = 0;
                    }
                    break;
                }
                break;
            case MENU_PRINCIPAL_SELECCION_OK:
            case MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS:
                if (idx_mando == JUGADOR_UNO) {
                    contador_tiempos_menu++;
                    if ((contador_tiempos_menu == 60) || !(contador_tiempos_menu % 300)) {
                        reproducir_sonido2(SONIDO_OK_MENU);
                    }
                }
                if (boton_y_palanca & B_BUTTON) {
                    switch (juego_modo_jugador_seleccion[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]]) {
                        case 0:
                        case 1:
                        case 2:
                            menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_SUB_MODO;
                            break;
                        default:
                        case 3:
                            menu_principal_seleccion = MENU_PRINCIPAL_SELECCION_MODO;
                            break;
                    }
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    contador_tiempos_menu = 0;
                    break;
                }
                if (boton_y_palanca & A_BUTTON) {
                    funcion_8009E1C0();
                    reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
                    preparar_modo_juego_seleccionado();
                    break;
                }
                break;
            case MENU_PRINCIPAL_OPCION:
            case MENU_PRINCIPAL_DATOS:
                break;
            default:
                break;
        }
        seleccion_modo = juego_modo_jugador_seleccion[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]];
    }
}

bool liberar_punto_personaje_es(s32 id_cuadricula) {
    s32 i;
    for (i = 0; i < CANTIDAD_ARREGLO(selecciones_cuadricula_personaje); i++) {
        if (id_cuadricula == selecciones_cuadricula_personaje[i]) {
            return false;
        }
    }
    return true;
}

void seleccionar_act_menu_jugador(struct Mando* mando, u16 idx_mando) {
    s8 i;
    s8 j;
    s32 seleccionado;
    u16 boton_y_palanca;

    boton_y_palanca = (mando->boton_pulsado | mando->palanca_pulsado);
    if (!modo_depuracion_activacion && (boton_y_palanca & START_BUTTON)) {
        boton_y_palanca |= A_BUTTON;
    }

    if (!es_pantalla_siendo_fundido()) {
        switch (jugador_seleccion_menu_seleccion) {
            case JUGADOR_SELECCION_MENU_PRINCIPAL:
                if (selecciones_cuadricula_personaje[idx_mando] == 0) {
                    if (boton_y_palanca & B_BUTTON) {
                        funcion_8009E208();
                        reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    }
                    return;
                }

                if (boton_y_palanca & B_BUTTON) {
                    if (personaje_cuadricula_es_seleccionado[idx_mando] != false) {
                        personaje_cuadricula_es_seleccionado[idx_mando] = false;
                        reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    } else {
                        funcion_8009E208();
                        reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    }
                }

                if ((boton_y_palanca & A_BUTTON) && (personaje_cuadricula_es_seleccionado[idx_mando] == 0)) {
                    personaje_cuadricula_es_seleccionado[idx_mando] = true;
                    funcion_800C90F4(idx_mando, ((orden_cuadricula_personaje - 1)[selecciones_cuadricula_personaje[idx_mando]] * 0x10) + 0x2900800E);
                }

                seleccionado = false;
                for (i = 0; i < CANTIDAD_ARREGLO(selecciones_cuadricula_personaje); i++) {
                    if ((selecciones_cuadricula_personaje[i] != 0) && (personaje_cuadricula_es_seleccionado[i] == false)) {
                        seleccionado = true;
                        break;
                    }
                }

                if (!seleccionado) {
                    jugador_seleccion_menu_seleccion = JUGADOR_SELECCION_MENU_OK;
                    reiniciar_menu_destello_ciclo();
                    contador_tiempos_menu = 0;
                }

                if (personaje_cuadricula_es_seleccionado[idx_mando] != false) {
                    break;
                }
                j = selecciones_cuadricula_personaje[idx_mando];
                if ((boton_y_palanca & R_JPAD) && (boton_y_palanca & D_JPAD)) {
                    if ((selecciones_cuadricula_personaje[idx_mando] == 1U) || (selecciones_cuadricula_personaje[idx_mando] == 2U) || (selecciones_cuadricula_personaje[idx_mando] == 3U)) {
                        j = selecciones_cuadricula_personaje[idx_mando] + 5;
                        if (liberar_punto_personaje_es(j)) {
                            selecciones_cuadricula_personaje[idx_mando] = j;
                            reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        }
                    }
                    return;
                }
                if ((boton_y_palanca & L_JPAD) && (boton_y_palanca & D_JPAD)) {
                    if ((selecciones_cuadricula_personaje[idx_mando] == 2U) || (selecciones_cuadricula_personaje[idx_mando] == 3U) || (selecciones_cuadricula_personaje[idx_mando] == 4U)) {
                        j = selecciones_cuadricula_personaje[idx_mando] + 3;
                        if (liberar_punto_personaje_es(j)) {
                            selecciones_cuadricula_personaje[idx_mando] = j;
                            reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        }
                    }
                    return;
                }
                if ((boton_y_palanca & R_JPAD) && (boton_y_palanca & U_JPAD)) {
                    if ((selecciones_cuadricula_personaje[idx_mando] == 5U) || (selecciones_cuadricula_personaje[idx_mando] == 6U) || (selecciones_cuadricula_personaje[idx_mando] == 7U)) {
                        j = selecciones_cuadricula_personaje[idx_mando] - 3;
                        if (liberar_punto_personaje_es(j)) {
                            selecciones_cuadricula_personaje[idx_mando] = j;
                            reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        }
                    }
                    return;
                }

                if ((boton_y_palanca & L_JPAD) && (boton_y_palanca & U_JPAD)) {
                    if ((selecciones_cuadricula_personaje[idx_mando] == 6U) || (selecciones_cuadricula_personaje[idx_mando] == 7U) || (selecciones_cuadricula_personaje[idx_mando] == 8U)) {
                        j = selecciones_cuadricula_personaje[idx_mando] - 5;
                        if (liberar_punto_personaje_es(j)) {
                            selecciones_cuadricula_personaje[idx_mando] = j;
                            reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        }
                    }
                    return;

                }
                if (boton_y_palanca & R_JPAD) {
                    if ((selecciones_cuadricula_personaje[idx_mando] != 4U) && (selecciones_cuadricula_personaje[idx_mando] != 8U)) {
                        j = selecciones_cuadricula_personaje[idx_mando] + 1;
                        do {
                            if (liberar_punto_personaje_es(j)) {
                                selecciones_cuadricula_personaje[idx_mando] = j;
                                reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                                return;
                            }

                            j++;
                            if (j == 5 || j == 9) {
                                break;
                            }
                        } while (j < 10);
                    }
                    return;
                }
                if (boton_y_palanca & L_JPAD) {
                    if ((selecciones_cuadricula_personaje[idx_mando] != 1U) && (selecciones_cuadricula_personaje[idx_mando] != 5U)) {
                        j = selecciones_cuadricula_personaje[idx_mando] - 1;
                        do {
                            if (liberar_punto_personaje_es(j)) {
                                selecciones_cuadricula_personaje[idx_mando] = j;
                                reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                                return;
                            }

                            j--;
                            if (j == 0 || j == 4) {
                                break;
                            }
                        } while (j >= 0);
                    }
                    return;
                }

                if ((boton_y_palanca & U_JPAD) && (selecciones_cuadricula_personaje[idx_mando] >= 5)) {
                    j = selecciones_cuadricula_personaje[idx_mando] - 4;
                }
                if ((boton_y_palanca & D_JPAD) && (selecciones_cuadricula_personaje[idx_mando] < 5)) {
                    j = selecciones_cuadricula_personaje[idx_mando] + 4;
                }
                if (liberar_punto_personaje_es(j)) {
                    selecciones_cuadricula_personaje[idx_mando] = j;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                break;
            case JUGADOR_SELECCION_MENU_OK:
            case JUGADOR_SELECCION_MENU_OK_IR_ATRAS:
                if (idx_mando == 0) {
                    contador_tiempos_menu++;
                    if (contador_tiempos_menu == 0x3C || !(contador_tiempos_menu % 300)) {
                        reproducir_sonido2(SONIDO_OK_MENU);
                    }
                }
                if (boton_y_palanca & B_BUTTON) {
                    jugador_seleccion_menu_seleccion = JUGADOR_SELECCION_MENU_PRINCIPAL;
                    personaje_cuadricula_es_seleccionado[idx_mando] = false;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    break;
                }
                if (boton_y_palanca & A_BUTTON) {
                    funcion_8009E1C0();
                    reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
                    funcion_8000F124();
                }
                break;
            default:
                break;
        }

        if (selecciones_cuadricula_personaje[idx_mando] != 0) {
            selecciones_personaje[idx_mando] = (orden_cuadricula_personaje - 1)[selecciones_cuadricula_personaje[idx_mando]];
        }
    }
}

void seleccionar_act_menu_circuito(struct Mando* parametro0, u16 idx_mando) {
    u16 boton_y_palanca = (parametro0->boton_pulsado | parametro0->palanca_pulsado);

    if ((!modo_depuracion_activacion) && ((boton_y_palanca & START_BUTTON) != 0)) {
        boton_y_palanca |= A_BUTTON;
    }

    if (!es_pantalla_siendo_fundido()) {
        switch (seleccion_menu_sub) {
            case SUB_MENU_MAPA_SELECCION_COPA:
                if ((boton_y_palanca & R_JPAD) != 0) {
                    if (seleccion_copa < COPA_ESPECIAL) {
                        seleccion_copa_temporal = seleccion_copa;
                        ++seleccion_copa;
                        reiniciar_menu_destello_ciclo();
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    }
                }
                if (((boton_y_palanca & L_JPAD) != 0) && (seleccion_copa > COPA_HONGO)) {
                    seleccion_copa_temporal = seleccion_copa;
                    --seleccion_copa;
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }

                dato_800DC540 = seleccion_copa;
                id_circuito_actual = orden_circuito_copa[seleccion_copa][indice_circuito_en_copa];
                if ((boton_y_palanca & B_BUTTON) != 0) {
                    funcion_8009E208();
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                } else if ((boton_y_palanca & A_BUTTON) != 0) {
                    if (seleccion_modo != GRAN_PREMIO) {
                        seleccion_menu_sub = SUB_MENU_MAPA_SELECCION_CIRCUITO;
                        reproducir_sonido2(SONIDO_SELECCION_MENU);
                    } else {
                        seleccion_menu_sub = SUB_MENU_MAPA_SELECCION_OK;
                        reproducir_sonido2(SONIDO_SELECCION_MENU);
                        id_circuito_actual = orden_circuito_copa[seleccion_copa][CIRCUITO_UNO];
                        contador_tiempos_menu = 0;
                    }
                    reiniciar_menu_destello_ciclo();
                }
                break;
            case SUB_MENU_MAPA_SELECCION_CIRCUITO:
            case SUB_MENU_MAPA_SELECCION_BATALLA_CIRCUITO:
                if (((boton_y_palanca & D_JPAD) != 0) && (indice_circuito_en_copa < CIRCUITO_CUATRO)) {
                    ++indice_circuito_en_copa;
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }
                if (((boton_y_palanca & U_JPAD) != 0) && (indice_circuito_en_copa > CIRCUITO_UNO)) {
                    --indice_circuito_en_copa;
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                }

                id_circuito_actual = orden_circuito_copa[seleccion_copa][indice_circuito_en_copa];
                if ((boton_y_palanca & B_BUTTON) != 0) {
                    if (seleccion_menu_sub == SUB_MENU_MAPA_SELECCION_CIRCUITO) {
                        seleccion_menu_sub = SUB_MENU_MAPA_SELECCION_COPA;
                    } else {
                        funcion_8009E208();
                    }
                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    return;
                }
                if ((boton_y_palanca & A_BUTTON) != 0) {
                    seleccion_menu_sub = SUB_MENU_MAPA_SELECCION_OK;
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                    reiniciar_menu_destello_ciclo();
                    contador_tiempos_menu = 0;
                }
                break;
            case SUB_MENU_MAPA_SELECCION_OK:
                if ((idx_mando == JUGADOR_UNO) &&
                    ((++contador_tiempos_menu == 0x3C) || ((contador_tiempos_menu % 300) == 0))) {
                    reproducir_sonido2(SONIDO_OK_MENU);
                }

                if ((boton_y_palanca & B_BUTTON) != 0) {
                    switch (seleccion_modo) {
                        case GRAN_PREMIO:
                            seleccion_menu_sub = SUB_MENU_MAPA_SELECCION_COPA;
                            break;
                        case BATALLA:
                            seleccion_menu_sub = SUB_MENU_MAPA_SELECCION_BATALLA_CIRCUITO;
                            break;
                        default:
                            seleccion_menu_sub = SUB_MENU_MAPA_SELECCION_CIRCUITO;
                            break;
                    }

                    reiniciar_menu_destello_ciclo();
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    return;
                }
                if ((boton_y_palanca & A_BUTTON) != 0) {
                    funcion_8009E1C0();
                    funcion_800CA330(0x19);
                    reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
                }
                break;
        }
    }
}
