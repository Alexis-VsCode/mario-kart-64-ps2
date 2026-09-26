// Cursor y personajes

void funcion_800A97BC(MenuItem* parametro0) {
    s32 i;

    switch (controller_pak_sentido_desplazamiento) {
        case CONTROLLER_PAK_ABAJO_DIR_DESPLAZAMIENTO:
            parametro0->row -= 2;
            if (parametro0->row < 0x60) {
                parametro0->row = 0x69;
                controller_pak_sentido_desplazamiento = CONTROLLER_PAK_NINGUNO_DIR_DESPLAZAMIENTO;
                for (i = 0; i < 8; i++) {
                    if (i < 7) {
                        controller_pak_renglones_tabla_visible[i] = controller_pak_renglones_tabla_visible[i + 1];
                    } else {
                        if ((controller_pak_renglones_tabla_visible[i - 1] == 0x10) ||
                            (controller_pak_renglones_tabla_visible[i - 1] == 0)) {
                            controller_pak_renglones_tabla_visible[i] = 0;
                        } else {
                            controller_pak_renglones_tabla_visible[i] = controller_pak_renglones_tabla_visible[i - 1] + 1;
                        }
                    }
                }
                controller_pak_renglones_tabla_visible[0] = controller_pak_renglones_tabla_visible[8] = 0;
            }

            break;
        case CONTROLLER_PAK_ARRIBA_DIR_DESPLAZAMIENTO:
            parametro0->row += 2;
            if (parametro0->row >= 0x73) {
                parametro0->row = 0x69;
                controller_pak_sentido_desplazamiento = CONTROLLER_PAK_NINGUNO_DIR_DESPLAZAMIENTO;
                for (i = 8; i > 0; i--) {
                    if (i > 1) {
                        controller_pak_renglones_tabla_visible[i] = controller_pak_renglones_tabla_visible[i - 1];
                    } else {
                        if ((controller_pak_renglones_tabla_visible[i + 1] == 1) ||
                            (controller_pak_renglones_tabla_visible[i + 1] == 0)) {
                            controller_pak_renglones_tabla_visible[i] = 0;
                        } else {
                            controller_pak_renglones_tabla_visible[i] = controller_pak_renglones_tabla_visible[i + 1] - 1;
                        }
                    }
                }
                controller_pak_renglones_tabla_visible[0] = controller_pak_renglones_tabla_visible[8] = 0;
                break;
                default:
                    controller_pak_sentido_desplazamiento = CONTROLLER_PAK_NINGUNO_DIR_DESPLAZAMIENTO;
                    break;
            }
    }
}

const s8 dato_800F0CA0[] = { 0x03, 0x03, 0x03, 0x02, 0x00, 0x02, 0x02, 0x01 };

const s8 dato_800F0CA8[] = { 0x03, 0x02, 0x00 };

const s8 dato_800F0CAC[] = { 0x03, 0x03, 0x02 };

void actualizar_item_menu_ok(MenuItem* parametro0) {
    s32 sp4;
    s32 variable_v0;

    switch (parametro0->type) {
        default:
            variable_v0 = sp4;
            break;
        case MENU_ITEM_IU_OK:
            variable_v0 = dato_800F0CA0[menu_principal_seleccion - 1];
            break;
        case OK_SELECCION_CIRCUITO:
            variable_v0 = dato_800F0CAC[seleccion_menu_sub - 1];
            break;
        case PERSONAJE_SELECCION_MENU_OK:
            variable_v0 = dato_800F0CA8[jugador_seleccion_menu_seleccion - 1];
            break;
    }
    switch (variable_v0) {
        case 0:
            parametro0->param1 = 0;
            break;
        case 1:
            parametro0->param1 = 0x00000020;
            break;
        case 2:
            if (parametro0->param1 > 0) {
                parametro0->param1 = (parametro0->param1 - (parametro0->param1 / 12)) - 2;
                if (parametro0->param1 < 0) {
                    parametro0->param1 = 0;
                }
            }
            break;
        case 3:
            if (parametro0->param1 < 0x20) {
                parametro0->param1 += 2;
                if (parametro0->param1 >= 0x20) {
                    parametro0->param1 = 0x00000020;
                }
            }
            break;
    }
}

void funcion_800A9B9C(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 0:
            funcion_800AA280(parametro0);
            break;
        case 1:
            funcion_800AA280(parametro0);
            parametro0->state = 4;
        case 4:
            if (parametro0->param1 > 0) {
                parametro0->param1 = (parametro0->param1 - (parametro0->param1 / 12)) - 2;
                if (parametro0->param1 < 0) {
                    parametro0->param1 = 0;
                }
            } else {
                parametro0->param1 = 0;
                parametro0->state = 0;
            }
            break;
        case 2:
            parametro0->state = 3;
            break;
        case 3:
        default:
            break;
    }
}

void funcion_800A9C40(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 0:
            funcion_800AA280(parametro0);
            if ((cantidad_jugador + 0xA) == parametro0->type) {
                parametro0->state = 2;
            } else {
                parametro0->state = 1;
            }
            break;
        case 4:
            if ((cantidad_jugador + 0xA) == parametro0->type) {
                parametro0->state = 2;
                parametro0->param1 = 0;
                break;
            }
            parametro0->state = 1;
        case 1:
            funcion_800AA280(parametro0);
            if ((menu_principal_seleccion == MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS) ||
                (menu_principal_seleccion == MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS)) {
                parametro0->param1 = 0x00000020;
            } else {
                if (parametro0->param1 < 0x20) {
                    parametro0->param1 += 2;
                    if (parametro0->param1 >= 0x20) {
                        parametro0->param1 = 0x00000020;
                    }
                }
            }
            break;
        case 3:
            if ((cantidad_jugador + 0xA) == parametro0->type) {
                parametro0->state = 2;
            }
            break;
        case 2:
        default:
            break;
    }
}

void funcion_800A9D5C(MenuItem* parametro0) {
    desconocido_d_800E70A0* temporal_v0;

    if ((cantidad_jugador + 0xA) == parametro0->type) {
        parametro0->priority = 0x0A;
    } else {
        parametro0->priority = 6;
    }

    switch (parametro0->state) {
        case 2:
            if ((menu_principal_seleccion == MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS) ||
                (menu_principal_seleccion == MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS)) {
                parametro0->column = 0x00000080;
                parametro0->row = 0x0000003E;
            } else {
                funcion_800A91D8(parametro0, 0x00000080, 0x0000003E);
            }
            break;
        case 3:
            temporal_v0 = &dato_800E70A0[parametro0->type - 0xA];
            funcion_800A91D8(parametro0, temporal_v0->column, temporal_v0->row);
            if ((parametro0->column == temporal_v0->column) && (parametro0->row == temporal_v0->row)) {
                parametro0->state = 0;
            }
        case 0:
        case 1:
        case 4:
        default:
            break;
    }
}

void funcion_800A9E58(MenuItem* parametro0) {
    MenuItem* temporal_v0;
    desconocido_d_800E70A0* temporal_v1_2;
    s32 sp24;
    s32 sp20;
    s32 sp1_c;
    s32 temporal_a1;

    switch (parametro0->type) {
        case 18:
        case 19:
        case 20:
        case 21:
            sp24 = 18;
            sp1_c = 2;
            sp20 = 0;
            break;
        case 22:
        case 23:
            sp24 = 22;
            sp20 = 2;
            sp1_c = 2;
            break;
        case 24:
        case 25:
            sp24 = 24;
            sp20 = 1;
            sp1_c = 1;
            break;
    }

    temporal_a1 = juego_modo_jugador_seleccion[cantidad_jugador - 1][juego_modo_menu_columna[cantidad_jugador - 1]];
    switch (parametro0->state) {
        case 0:
            if ((temporal_a1 != sp20) && (temporal_a1 != sp1_c)) {
                parametro0->visible = 0;
            } else {
                parametro0->param2 = juego_modo_menu_columna[cantidad_jugador - 1];
                switch (menu_principal_seleccion) {
                    case MENU_PRINCIPAL_SELECCION_MODO:
                    case MENU_PRINCIPAL_SELECCION_SUB_MODO:
                    case MENU_PRINCIPAL_SELECCION_OK:
                        parametro0->visible = 1;
                        temporal_v0 = obtener_menu_item_jugador_cantidad();
                        parametro0->column = temporal_v0->column;
                        parametro0->row = (juego_modo_menu_columna[cantidad_jugador - 1] * 0x12) + temporal_v0->row + 0x41;
                        parametro0->param1 = 0;
                        parametro0->state = 1;
                        break;
                    case MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS:
                    case MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS:
                        temporal_v0 = obtener_menu_item_jugador_cantidad();
                        temporal_v1_2 = &dato_800E70E8[parametro0->type - sp24];
                        parametro0->column = temporal_v0->column + temporal_v1_2->column;
                        parametro0->row = (juego_modo_menu_columna[cantidad_jugador - 1] * 0x12) + temporal_v0->row + temporal_v1_2->row;
                        parametro0->param1 = parametro0->row - temporal_v0->row;
                        parametro0->visible = 1;
                        parametro0->state = 2;
                        break;
                    default:
                        parametro0->visible = 0;
                        break;
                }
            }
            break;
        case 1:
            switch (menu_principal_seleccion) {
                case MENU_PRINCIPAL_SELECCION_MODO:
                case MENU_PRINCIPAL_SELECCION_SUB_MODO:
                case MENU_PRINCIPAL_SELECCION_OK:
                case MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS:
                case MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS:
                    if ((temporal_a1 != sp20) && (temporal_a1 != sp1_c)) {
                        parametro0->visible = 0;
                        parametro0->state = 0;
                    } else {
                        if (parametro0->param2 != juego_modo_menu_columna[cantidad_jugador - 1]) {
                            parametro0->state = 0;
                        }
                        temporal_v0 = obtener_menu_item_jugador_cantidad();
                        parametro0->column = temporal_v0->column + parametro0->param1;
                        temporal_v1_2 = &dato_800E70E8[parametro0->type - sp24];
                        funcion_800A92E8(parametro0, temporal_v0->column + temporal_v1_2->column);
                        parametro0->param1 = parametro0->column - temporal_v0->column;
                        if (parametro0->param1 == temporal_v1_2->column) {
                            parametro0->state = 2;
                            parametro0->param1 = parametro0->row - temporal_v0->row;
                        }
                    }
                    break;
                default:
                    parametro0->visible = 0;
                    parametro0->state = 0;
                    break;
            }
            break;
        case 2:
            switch (menu_principal_seleccion) {
                case MENU_PRINCIPAL_SELECCION_MODO:
                case MENU_PRINCIPAL_SELECCION_SUB_MODO:
                case MENU_PRINCIPAL_SELECCION_OK:
                case MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS:
                case MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS:
                    if ((temporal_a1 != sp20) && (temporal_a1 != sp1_c)) {
                        parametro0->visible = 0;
                        parametro0->state = 0;
                    } else {
                        if (parametro0->param2 != juego_modo_menu_columna[cantidad_jugador - 1]) {
                            parametro0->state = 0;
                        }
                        temporal_v0 = obtener_menu_item_jugador_cantidad();
                        temporal_v1_2 = &dato_800E70E8[parametro0->type - sp24];
                        parametro0->column = temporal_v0->column + temporal_v1_2->column;
                        parametro0->row = temporal_v0->row + parametro0->param1;
                        funcion_800A91D8(parametro0, parametro0->column,
                                      (juego_modo_menu_columna[cantidad_jugador - 1] * 0x12) + temporal_v0->row + temporal_v1_2->row);
                        parametro0->param1 = parametro0->row - temporal_v0->row;
                    }
                    break;
                default:
                    parametro0->visible = 0;
                    parametro0->state = 0;
                    break;
            }
            break;
    }
}

void funcion_800AA280(MenuItem* parametro0) {
    desconocido_d_800E70A0* temporal_v0;

    temporal_v0 = &dato_800E70A0[parametro0->type - 0xA];
    if ((menu_principal_seleccion == MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS) ||
        (menu_principal_seleccion == MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS)) {
        parametro0->column = temporal_v0->column;
        parametro0->row = temporal_v0->row;
    } else {
        funcion_800A91D8(parametro0, temporal_v0->column, temporal_v0->row);
    }
}

void funcion_800AA2EC(MenuItem* parametro0) {
    s32 temporal_v0;
    s32 variable_t1;

    variable_t1 = 0;
    switch (menu_principal_seleccion) {
        case MENU_PRINCIPAL_OPCION:
        case MENU_PRINCIPAL_DATOS:
        case MENU_PRINCIPAL_SELECCION_JUGADOR:
        case MENU_PRINCIPAL_SELECCION_MODO:
            parametro0->state = 0;
            break;
        case MENU_PRINCIPAL_SELECCION_SUB_MODO:
        case MENU_PRINCIPAL_SELECCION_OK:
        case MENU_PRINCIPAL_OK_SELECCION_IR_ATRAS:
        case MENU_PRINCIPAL_MODO_SUB_SELECCION_IR_ATRAS:
            if (parametro0->state != 0) {
                break;
            }
            if (cantidad_jugador != 1) {
                break;
            }
            if (juego_modo_menu_columna[cantidad_jugador - 1] != 1) {
                break;
            }

            if (controller_pak_1_estado != 0) {
                variable_t1 = 0;
                switch (osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego,
                                      (u8*) codigo_ext, &controller_pak_nota_1_archivo)) {
                    case 5:
                        break;
                    case 0:
                        parametro0->state = 1;
                        variable_t1 = 1;
                        break;
                    case 2:
                        controller_pak_1_estado = 0;
                        break;
                    default:
                        controller_pak_1_estado = 0;
                        break;
                }
            }
            if (variable_t1 == 0) {
                if (controller_pak_1_estado == 0) {
                    if (comprobar_para_controller_pak(0) == 0) {
                        parametro0->state = 2;
                        break;
                    }
                    temporal_v0 = osPfsInit(&si_evento_msj_cola, &controller_pak_manejador_1_archivo, 0);
                    if (temporal_v0 != 0) {
                        switch (temporal_v0) {
                            case PFS_ERR_NOPACK:
                            case PFS_ERR_DEVICE:
                                parametro0->state = 2;
                                break;
                            case PFS_ERR_ID_FATAL:
                                parametro0->state = 3;
                                break;
                            case PFS_ERR_CONTRFAIL:
                            default:
                                parametro0->state = 3;
                                break;
                        }
                        return;
                    } else {
                        controller_pak_1_estado = 1;
                    }
                    if (osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego,
                                      (u8*) codigo_ext, &controller_pak_nota_1_archivo) == 0) {
                        parametro0->state = 1;
                        break;
                    }
                    if (osPfsNumFiles(&controller_pak_manejador_1_archivo, &controller_pak_1_num_archivos_usado,
                                      &controller_pak_archivos_escribible_1_max) != 0) {
                        parametro0->state = 3;
                        break;
                    }
                    if (osPfsFreeBlocks(&controller_pak_manejador_1_archivo, &controller_pak_libre_paginas_1_num) != 0) {
                        parametro0->state = 3;
                        break;
                    }
                    controller_pak_libre_paginas_1_num = (s32) controller_pak_libre_paginas_1_num >> 8;
                }
                if (controller_pak_archivos_escribible_1_max >= controller_pak_1_num_archivos_usado) {
                    parametro0->state = 5;
                    break;
                }
                if (controller_pak_libre_paginas_1_num >= 0x79) {
                    parametro0->state = 1;
                    break;
                }
                parametro0->state = 5;
            }
            break;
        default:
            break;
    }
}

void funcion_800AA5C8(MenuItem* parametro0, s8 parametro1) {
    s32 temporal_v1;

    temporal_v1 = parametro0->type - 0x2B;
    switch (parametro0->estado_sub) { /* irregular */
        case 0:
            if (funcion_800AAFCC((s32) parametro1) >= 0) {
                parametro0->estado_sub = 2;
                funcion_8009A594(parametro0->d_8018DEE0_indice, 0, segmentado_a_duplicado_virtual_2(dato_800E8340[temporal_v1]));
            }
            break;
        case 2:
            if (funcion_800AAFCC((s32) parametro1) < 0) {
                parametro0->estado_sub = 0;
                funcion_8009A594(parametro0->d_8018DEE0_indice, 0, segmentado_a_duplicado_virtual_2(dato_800E8320[temporal_v1]));
            }
            break;
    }
}

void funcion_800AA69C(MenuItem* parametro0) {
    s32 temporal_v0;
    s32 variable_a0;
    s32 variable_v0;
    s32 temporal_a0;
    SIN_USO s32 margen_pila_0;

    temporal_a0 = parametro0->type - 0x2B;
    temporal_v0 = funcion_800AAFCC(parametro0->type - 0x2B);
    if (temporal_v0 >= 0) {
        variable_a0 = 1;
    } else {
        variable_a0 = 0;
    }
    switch (parametro0->estado_sub) {
        case 0:
            if ((personaje_cuadricula_es_seleccionado[temporal_v0] != 0) && (variable_a0 != 0)) {
                parametro0->estado_sub = 1;
                funcion_8009A594(parametro0->d_8018DEE0_indice, 0,
                              segmentado_a_duplicado_virtual_2(animacion_celebracion_personaje[temporal_a0]));
            } else {
                temporal_v0 = int_aleatorio(0x00C8U);
                if (temporal_v0 >= 0xC6) {
                    parametro0->estado_sub = 4;
                    funcion_8009A594(parametro0->d_8018DEE0_indice, 0,
                                  segmentado_a_duplicado_virtual_2(personaje_simple_parpadear_animacion[temporal_a0]));
                } else if (temporal_v0 >= 0xC5) {
                    parametro0->estado_sub = 5;
                    funcion_8009A594(parametro0->d_8018DEE0_indice, 0,
                                  segmentado_a_duplicado_virtual_2(personaje_doble_parpadear_animacion[temporal_a0]));
                }
            }
            break;
        case 1:
            if (dato_8018DEE0[parametro0->d_8018DEE0_indice].indice_secuencia >= dato_800E8440[temporal_a0]) {
                parametro0->estado_sub = 2;
                funcion_8009A594(parametro0->d_8018DEE0_indice, 0, segmentado_a_duplicado_virtual_2(dato_800E83A0[temporal_a0]));
            } else if ((personaje_cuadricula_es_seleccionado[temporal_v0] == 0) && (variable_a0 != 0)) {
                parametro0->estado_sub = 3;
                funcion_8009A594(parametro0->d_8018DEE0_indice,
                              dato_800E8460[temporal_a0] - dato_8018DEE0[parametro0->d_8018DEE0_indice].indice_secuencia,
                              segmentado_a_duplicado_virtual_2(animacion_deseleccionar_personaje[temporal_a0]));
            }
            break;
        case 2:
            if ((personaje_cuadricula_es_seleccionado[temporal_v0] == 0) && (variable_a0 != 0)) {
                parametro0->estado_sub = 3;
                funcion_8009A594(parametro0->d_8018DEE0_indice, 0,
                              segmentado_a_duplicado_virtual_2(animacion_deseleccionar_personaje[temporal_a0]));
            }
            break;
        case 3:
            if (dato_8018DEE0[parametro0->d_8018DEE0_indice].indice_secuencia >= dato_800E8460[temporal_a0]) {
                parametro0->estado_sub = 0;
                funcion_8009A594(parametro0->d_8018DEE0_indice, 0, segmentado_a_duplicado_virtual_2(dato_800E8360[temporal_a0]));
            } else if ((personaje_cuadricula_es_seleccionado[temporal_v0] != 0) && (variable_a0 != 0)) {
                parametro0->estado_sub = 1;
                funcion_8009A594(parametro0->d_8018DEE0_indice,
                              dato_800E8460[temporal_a0] - dato_8018DEE0[parametro0->d_8018DEE0_indice].indice_secuencia,
                              segmentado_a_duplicado_virtual_2(animacion_celebracion_personaje[temporal_a0]));
            }
            break;
        case 4:
        case 5:
            if ((personaje_cuadricula_es_seleccionado[temporal_v0] != 0) && (variable_a0 != 0)) {
                parametro0->estado_sub = 1;
                funcion_8009A594(parametro0->d_8018DEE0_indice, 0,
                              segmentado_a_duplicado_virtual_2(animacion_celebracion_personaje[temporal_a0]));
            } else {
                if (parametro0->estado_sub == 4) {
                    variable_v0 = dato_800E8480[temporal_a0];
                } else {
                    variable_v0 = dato_800E84A0[temporal_a0];
                }
                if (dato_8018DEE0[parametro0->d_8018DEE0_indice].indice_secuencia >= variable_v0) {
                    parametro0->estado_sub = 0;
                    funcion_8009A594(parametro0->d_8018DEE0_indice, 0, segmentado_a_duplicado_virtual_2(dato_800E8360[temporal_a0]));
                }
            }
            break;
        default:
            break;
    }
}

void funcion_800AAA9C(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 3:
            parametro0->state = 1;
        case 1:
            if (jugador_seleccion_menu_seleccion == JUGADOR_SELECCION_MENU_OK_IR_ATRAS) {
                parametro0->param1 = 0x00000020;
            } else {
                if (parametro0->param1 < 0x20) {
                    parametro0->param1 += (parametro0->param1 / 12) + 2;
                    if (parametro0->param1 >= 0x20) {
                        parametro0->param1 = 0x00000020;
                    }
                }
            }
        case 0:
            if (funcion_800AAFCC(parametro0->type - 0x2B) >= 0) {
                parametro0->state = 2;
                parametro0->param1 = 0;
            } else {
                parametro0->state = 1;
            }
            break;
        case 4:
            if (funcion_800AAFCC(parametro0->type - 0x2B) >= 0) {
                parametro0->state = 2;
                parametro0->param1 = 0;
            }
            break;
        case 2:
        default:
            break;
    }
}

void funcion_800AAB90(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 1:
            if (parametro0->param1 > 0) {
                parametro0->state = 3;
            }
            break;
        case 2:
            parametro0->state = 4;
            break;
        case 3:
            if (parametro0->param1 > 0) {
                parametro0->param1 = (parametro0->param1 - (parametro0->param1 / 12)) - 2;
                if (parametro0->param1 < 0) {
                    parametro0->param1 = 0;
                }
            } else {
                parametro0->param1 = 0;
                parametro0->state = 0;
            }
            break;
        case 0:
        case 4:
        default:
            break;
    }
}

void funcion_800AAC18(MenuItem* parametro0) {
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    s32 temporal_a1;
    s32 temporal_v0;
    SIN_USO s32 margen_pila_2;
    desconocido_d_800E70A0* variable_t0;

    temporal_a1 = parametro0->type - 0x2B;
    switch (parametro0->state) {
        case 0:
            if (jugador_seleccion_menu_seleccion == JUGADOR_SELECCION_MENU_OK_IR_ATRAS) {
                temporal_v0 = funcion_800AAFCC(temporal_a1);
                if (temporal_v0 >= 0) {
                    variable_t0 = &dato_800E7188[(seleccion_modo_pantalla * 4) + temporal_v0];
                    parametro0->column = (s32) variable_t0->column;
                    parametro0->row = (s32) variable_t0->row;
                    parametro0->state = 2;
                    parametro0->estado_sub = 2;
                    funcion_8009A594(parametro0->d_8018DEE0_indice, 0, segmentado_a_duplicado_virtual_2(dato_800E8340[temporal_a1]));
                }
                break;
            }
        case 1:
        case 3:
            variable_t0 = &dato_800E7108[0][temporal_a1];
            parametro0->column = (s32) variable_t0->column;
            parametro0->row = (s32) variable_t0->row;
            break;
        case 2:
        case 4:
            if (parametro0->state == 2) {
                temporal_v0 = funcion_800AAFCC(temporal_a1);
                if (temporal_v0 >= 0) {
                    variable_t0 = &dato_800E7188[(seleccion_modo_pantalla * 4) + temporal_v0];
                }
            } else {
                variable_t0 = &dato_800E7108[0][temporal_a1];
                if ((variable_t0->column == parametro0->column) && (variable_t0->row == parametro0->row)) {
                    parametro0->state = 0;
                    return;
                }
            }
            if ((parametro0->state != 2) || (parametro0->estado_sub != 1)) {
                funcion_800A91D8(parametro0, (s32) variable_t0->column, (s32) variable_t0->row);
            }
            break;
        default:
            break;
    }
}

void actualizar_cursor(MenuItem* parametro0) {
    s32 id_jugador;
    s8 indice_seleccion_personaje;

    id_jugador = parametro0->type - PERSONAJE_SELECCION_MENU_1J_CURSOR;
    indice_seleccion_personaje = selecciones_cuadricula_personaje[id_jugador];
    parametro0->priority = 0xE - (id_jugador * 2);
    flotar_cursor_sobre_retrato_personaje(parametro0, indice_seleccion_personaje - 1);
}

void funcion_800AAE18(MenuItem* parametro0) {
    s32 temporal_v0;

    temporal_v0 = funcion_800AAFCC(parametro0->type - MENU_SELECCION_PERSONAJE_MARIO);
    if (temporal_v0 >= 0) {
        parametro0->priority = 0xE - (temporal_v0 * 2);
    } else {
        parametro0->priority = 6;
    }
}

MenuItem* obtener_menu_item_jugador_cantidad(void) {
    MenuItem* entry = menu_items;
    s32 jugador_nb = cantidad_jugador - 1;

    for (; !(entry > &menu_items[MENU_ITEMS_MAX]); entry++) {
        if ((jugador_nb + MENU_ITEM_IU_1J_JUEGO) == entry->type) {
            goto escape;
        }
    }

    while (true) {
        ;
    }
escape:
    return entry;
}

MenuItem* obtener_personaje_item_menu(s32 id_personaje) {
    MenuItem* entry = menu_items;

    for (; !(entry > &menu_items[MENU_ITEMS_MAX]); entry++) {
        if ((id_personaje + MENU_SELECCION_PERSONAJE_MARIO) == entry->type) {
            goto escape;
        }
    }

    while (true) {
        ;
    }
escape:
    return entry;
}

MenuItem* buscar_duplicado_items_menu(s32 type) {
    MenuItem* entry = menu_items;
    for (; !(entry > (&menu_items[MENU_ITEMS_MAX])); entry++) {
        if (entry->type == type) {
            goto escape;
        }
    }

    while (true) {
        ;
    }
escape:
    return entry;
}

MenuItem* buscar_items_menu(s32 type) {
    MenuItem* entry = menu_items;
    for (; !(entry > (&menu_items[MENU_ITEMS_MAX])); entry++) {
        if (entry->type == type) {
            goto escape;
        }
    }

    return NULL;
escape:
    return entry;
}

SIN_USO s32 obtener_estado_menu_personaje(s32 id_personaje) {
    MenuItem* temporal_;
    temporal_ = obtener_personaje_item_menu(id_personaje);
    return temporal_->state;
}

void flotar_cursor_sobre_retrato_personaje(MenuItem* parametro0, s32 id_personaje) {
    MenuItem* temporal_v0;

    temporal_v0 = obtener_personaje_item_menu(id_personaje);
    parametro0->column = temporal_v0->column;
    parametro0->row = temporal_v0->row;
}

s32 funcion_800AAFCC(s32 id_personaje) {
    s32 algun_indice = 0;
    bool devuelto = false;

    for (; algun_indice < CANTIDAD_ARREGLO(selecciones_cuadricula_personaje); algun_indice++) {
        if ((id_personaje + 1) == selecciones_cuadricula_personaje[algun_indice]) {
            devuelto = true;
            break;
        }
    }

    if (devuelto != false) {
        return algun_indice;
    }

    return -1;
}

void funcion_800AB020(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 1:
            parametro0->state = 4;
        case 4:
            if (parametro0->param1 > 0) {
                parametro0->param1 = (parametro0->param1 - (parametro0->param1 / 12)) - 2;
                if (parametro0->param1 < 0) {
                    parametro0->param1 = 0;
                }
            } else {
                parametro0->param1 = 0;
                parametro0->state = 0;
            }
            break;
        case 2:
            parametro0->state = 3;
            break;
        case 0:
        case 3:
        default:
            break;
    }
}

void funcion_800AB098(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 0:
            if ((seleccion_copa + 0x53) == parametro0->type) {
                parametro0->state = 2;
            } else {
                parametro0->state = 1;
            }
            break;
        case 4:
            if ((seleccion_copa + 0x53) == parametro0->type) {
                parametro0->state = 2;
                parametro0->param1 = 0;
                break;
            } else {
                parametro0->state = 1;
            }
        case 1:
            if (parametro0->param1 < 32) {
                parametro0->param1 += 2;
                if (parametro0->param1 >= 32) {
                    parametro0->param1 = 32;
                }
            }
            break;
        case 3:
            if ((seleccion_copa + 0x53) == parametro0->type) {
                parametro0->state = 2;
            }
            break;
        case 2:
        default:
            break;
    }
}

void funcion_800AB164(MenuItem* parametro0) {
    desconocido_d_800E70A0* cosa = &dato_800E7148[parametro0->type - 0x53];

    if ((seleccion_copa + 0x53) == parametro0->type) {
        parametro0->priority = 0x0A;
    } else {
        parametro0->priority = 4;
    }

    switch (parametro0->state) {
        case 0:
            cosa = &dato_800E7148[parametro0->type - 0x53];
            parametro0->column = cosa->column;
            parametro0->row = cosa->row;
            break;
        case 2:
            funcion_800A91D8(parametro0, 0x00000080, 0x0000003B);
            break;
        case 3:
            cosa = &dato_800E7148[parametro0->type - 0x53];
            funcion_800A91D8(parametro0, cosa->column, cosa->row);
            if ((parametro0->column == cosa->column) && (parametro0->row == cosa->row)) {
                parametro0->state = 0;
            }
            break;
        case 1:
        case 4:
        default:
            break;
    }
}

void funcion_800AB260(MenuItem* parametro0) {
    s32 temporal_ = (parametro0->type - 0x58);
    if (temporal_ == seleccion_copa) {
        parametro0->visible = 1;
    } else {
        parametro0->visible = 0;
    }
}

void funcion_800AB290(MenuItem* parametro0) {
    if (parametro0->param1 != seleccion_copa) {
        parametro0->param1 = seleccion_copa;
        funcion_8009A594(parametro0->d_8018DEE0_indice, 0,
                      segmentado_a_duplicado_virtual_2(dato_800E7E34[orden_circuito_copa[seleccion_copa][parametro0->type - 0x5F]]));
    }
}
