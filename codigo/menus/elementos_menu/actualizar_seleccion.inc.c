// Actualizar seleccion

void funcion_800AB314(MenuItem* item) {
    s32 i;
    SIN_USO s32 relleno[2];
    MenuItem* _items[4];

    for (i = 0; i < 4; i++) {
        _items[i] = buscar_duplicado_items_menu(i + 0x5F);
    }
    if (seleccion_modo != 0) {
        if (seleccion_menu_sub != SUB_MENU_MAPA_SELECCION_COPA) {
            item->state = 0;
            item->param2 = 0;

            for (i = 0; i < 4; i++) {
                if (indice_circuito_en_copa == i) {
                    _items[i]->visible = 1;
                    if (item->param1 != i) {
                        item->param1 = i;
                    }
                } else {
                    _items[i]->visible = 0;
                }
            }
        } else {
            item->state = 3;
            for (i = 0; i < 4; i++) {
                _items[i]->visible = 1;
                _items[i]->priority = 6;
            }
        }
    } else {
        switch (item->state) {
            case 0:
                if (seleccion_copa == (item->param1 / 4)) {
                    if (++item->param2 > 50) {
                        item->state = 1;
                        item->param2 = 0;
                        item->param1 = (seleccion_copa * 4) + 1;
                    }
                } else {
                    item->param2 = 0;
                    item->param1 = seleccion_copa * 4;
                }
                if (seleccion_menu_sub == SUB_MENU_MAPA_SELECCION_OK) {
                    item->state = 2;
                    item->param2 = 0;
                }
                break;
            case 1:
                if (seleccion_copa != (item->param1 / 4)) {
                    item->state = 0;
                    item->param2 = 0;
                    item->param1 = 0;
                    break;
                }

                if (++item->param2 > 30) {
                    item->param2 = 0;
                    item->param1 = (seleccion_copa * 4) + (((item->param1 % 4) + 1) % 4);
                    break;
                }
                if (seleccion_menu_sub == SUB_MENU_MAPA_SELECCION_OK) {
                    item->state = 2;
                    item->param2 = 0;
                }
                break;
            case 2:
                if (++item->param2 > 25) {
                    item->state = 3;
                    item->param2 = 0;
                }
                if (seleccion_menu_sub != SUB_MENU_MAPA_SELECCION_OK) {
                    item->state = 0;
                    item->param2 = 0;
                    item->param1 = 0;
                }
                break;
            case 3:
                if (seleccion_menu_sub != SUB_MENU_MAPA_SELECCION_OK) {
                    item->state = 0;
                    item->param2 = 0;
                    item->param1 = 0;
                }
                break;
        }

        switch (item->state) {
            case 0:
            case 1:
                for (i = 0; i < 4; i++) {
                    if ((item->param1 % 4) == i) {
                        _items[i]->visible = 1;
                    } else {
                        _items[i]->visible = 0;
                    }
                    _items[i]->priority = 6;
                }
                break;
            case 2:
                for (i = 0; i < 4; i++) {
                    if ((item->param1 % 4) == i) {
                        _items[i]->priority = 6;
                    } else if (item->param2 < (i * 5)) {
                        _items[i]->priority = 4;
                    } else {
                        _items[i]->priority = 8;
                    }
                    _items[i]->visible = 1;
                }
                break;
            case 3:
                for (i = 0; i < 4; i++) {
                    _items[i]->visible = 1;
                    _items[i]->priority = 6;
                }
                break;
        }
    }
}

void funcion_800AB904(MenuItem* parametro0) {
    desconocido_d_800E70A0* temporal_a1;

    switch (seleccion_menu_sub) { /* irregular */
        case SUB_MENU_MAPA_SELECCION_COPA:
            temporal_a1 = &dato_800E7248[parametro0->type - 0x65];
            if (parametro0->column != temporal_a1->column) {
                funcion_800A9208(parametro0, temporal_a1->column);
            }
            break;
        case SUB_MENU_MAPA_SELECCION_CIRCUITO:
        case SUB_MENU_MAPA_SELECCION_OK:
            temporal_a1 = &dato_800E7258[parametro0->type - 0x65];
            if (parametro0->column != temporal_a1->column) {
                funcion_800A9208(parametro0, temporal_a1->column);
            }
            break;
    }
}

void funcion_800AB9B0(MenuItem* parametro0) {
    desconocido_d_800E70A0* temporal_v1;

    if (parametro0->param1 != seleccion_copa) {
        parametro0->param1 = seleccion_copa;
        parametro0->param2 = funcion_800B54C0((s32) seleccion_copa, seleccion_cc);
        funcion_8009A594(parametro0->d_8018DEE0_indice, 0,
                      segmentado_a_duplicado_virtual_2(dato_800E7E20[((seleccion_cc / 2) * 4) - parametro0->param2]));
        parametro0->column = (s32) dato_800E7268->column;
        parametro0->row = dato_800E7268->row;
    }
    temporal_v1 = &dato_800E7268[parametro0->state];
    switch (parametro0->state) { /* irregular */
        case 0:
            funcion_800A91D8(parametro0, (s32) temporal_v1->column, (s32) temporal_v1->row);
            if (seleccion_menu_sub == SUB_MENU_MAPA_SELECCION_OK) {
                parametro0->state = 1;
            }
            break;
        case 1:
            funcion_800A91D8(parametro0, (s32) temporal_v1->column, (s32) temporal_v1->row);
            if (seleccion_menu_sub == SUB_MENU_MAPA_SELECCION_COPA) {
                parametro0->state = 0;
            }
            break;
    }
}

void funcion_800ABAE8(MenuItem* parametro0) {
    s32 index;

    if (parametro0->type == 0x8C) {
        index = 4;
    } else {
        index = parametro0->type - 0x78;
    }
    parametro0->column = dato_800E7430[index].column;
    parametro0->row = dato_800E7430[index].row;
}

void funcion_800ABB24(MenuItem* parametro0) {
    desconocido_d_800E70A0* temporal_v1;
    s32 cosa = contrarreloj_indice_circuito_datos;

    temporal_v1 = &dato_800E7430[cosa / 4];
    parametro0->column = temporal_v1->column - 2;
    parametro0->row = temporal_v1->row + ((cosa % 4) * 0x32) + 0x13;
    parametro0->param1 += 0x10;
    if (parametro0->param1 >= 0x100) {
        parametro0->param1 -= 0x100;
        parametro0->param2 = (s32) (parametro0->param2 + 1) % 3;
    }
}

void funcion_800ABBCC(MenuItem* parametro0) {
    s32 temporal_v0;
    desconocido_d_800E70A0* temporal_v1;

    temporal_v0 = parametro0->type - 0x7C;
    temporal_v1 = &dato_800E7430[temporal_v0 / 4];
    parametro0->column = (s32) temporal_v1->column;
    parametro0->row = temporal_v1->row + ((temporal_v0 % 4) * 0x32) + 0x14;
}

void funcion_800ABC38(MenuItem* parametro0) {
    s32 one = 1;
    funcion_800ABCF4(parametro0);
    switch (dato_80164A28) { /* irregular */
        case 1:
            parametro0->visible = one;
            break;
        case 2:
            if (parametro0->row >= -0x13) {
                parametro0->row -= 2;
            } else {
                parametro0->type = 0;
            }
            break;
        default:
            if ((seleccion_modo != GRAN_PREMIO) || (seleccion_cantidad_jugador_1 != (s32) 1U) || (mando_usar_demo != 0)) {
                parametro0->type = 0;
            } else {
                if (parametro0->row >= -0x13) {
                    parametro0->row -= 2;
                } else {
                    parametro0->type = 0;
                }
            }
            break;
    }
}

void funcion_800ABCF4(MenuItem* parametro0) {
    f64 temporal_f0;

    switch (parametro0->state) { /* irregular */
        case 0:
            parametro0->column = 0;
            parametro0->state = 1;
            parametro0->param2 = (obtener_ancho_cadena(nombres_copa[dato_800DC540]) / 2) + 0xA0;
        case 1:
            funcion_800A9208(parametro0, parametro0->param2);
            parametro0->param1 = (s32) (parametro0->param2 - parametro0->column) / 4;
            if (parametro0->param1 >= 9) {
                parametro0->param1 = 8;
            }
            parametro0->paramf = (f32) (((f64) parametro0->param1 * 0.05) + 1.0);
            if (parametro0->column >= (parametro0->param2 - 0x14)) {
                parametro0->state = 2;
                parametro0->d_8018DEE0_indice = 0;
            }
            break;
        case 2:
            funcion_800A9208(parametro0, parametro0->param2);
            parametro0->param1 = (s32) (parametro0->param2 - parametro0->column) / 4;
            parametro0->d_8018DEE0_indice++;
            temporal_f0 = (f64) (parametro0->d_8018DEE0_indice - 0xA);
            parametro0->paramf = (f32) ((temporal_f0 * 0.0085 * temporal_f0) + 0.4);
            if ((parametro0->d_8018DEE0_indice >= 9) && ((f64) parametro0->paramf > 1.0)) {
                parametro0->paramf = 1.0f;
            }
            break;
    }
}

void funcion_800ABEAC(MenuItem* parametro0) {
    s32 por_que = 1;
    funcion_800ABF68(parametro0);
    switch (dato_80164A28) {
        case 1:
            parametro0->visible = por_que;
            break;
        case 2:
            if (parametro0->row < 0x104) {
                parametro0->row += 2;
            } else {
                parametro0->type = 0;
            }
            break;
        default:
            if ((seleccion_modo != GRAN_PREMIO) || (seleccion_cantidad_jugador_1 != por_que) || (mando_usar_demo != 0)) {
                parametro0->type = 0;
            } else {
                if (parametro0->row < 0x104) {
                    parametro0->row += 2;
                } else {
                    parametro0->type = 0;
                }
            }
            break;
    }
}

void funcion_800ABF68(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 0:
            parametro0->column = 0x140;
            parametro0->state = 1;
            parametro0->param2 = 0xA0 - (obtener_ancho_cadena(nombres_circuito[id_circuito_actual]) / 2);
        case 1:
            funcion_800A9208(parametro0, parametro0->param2);
            parametro0->param1 = (parametro0->column - parametro0->param2) / 4;
            if (parametro0->param1 >= 9) {
                parametro0->param1 = 8;
            }
            parametro0->paramf = (parametro0->param1 * 0.05) + 1.0;
            if ((parametro0->param2 + 0x14) >= parametro0->column) {
                parametro0->state = 2;
                parametro0->d_8018DEE0_indice = 0;
            }
            break;
        case 2:
            funcion_800A9208(parametro0, parametro0->param2);
            parametro0->param1 = (parametro0->column - parametro0->param2) / 4;
            parametro0->d_8018DEE0_indice++;
            parametro0->paramf = ((parametro0->d_8018DEE0_indice - 0xA) * 0.0085 * (parametro0->d_8018DEE0_indice - 0xA)) + 0.4;
            if ((parametro0->d_8018DEE0_indice >= 9) && ((f64) parametro0->paramf > 1.0)) {
                parametro0->paramf = 1.0f;
            }
            break;
    }
}

void funcion_800AC128(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 0:
            parametro0->column = 0x00000140;
            parametro0->state = 1;
        case 1:
            funcion_800A940C(parametro0, 0x00000064);
            parametro0->param1 = (s32) (parametro0->column - 0x64) / 6;
            if (parametro0->param1 >= 9) {
                parametro0->param1 = 8;
            }
            parametro0->paramf = (f32) (((f64) parametro0->param1 * 0.07) + 0.6);
            if (parametro0->column == 0x00000064) {
                parametro0->state = 2;
                parametro0->d_8018DEE0_indice = 0;
            }
            break;
        case 2:
            parametro0->d_8018DEE0_indice++;
            parametro0->param1 = 0;
            parametro0->paramf = (f32) (1.5 - ((parametro0->d_8018DEE0_indice - 0xF) * 0.004 * (parametro0->d_8018DEE0_indice - 0xF)));
            if ((parametro0->d_8018DEE0_indice >= 0x10) && ((f64) parametro0->paramf < 0.8)) {
                parametro0->state = 3;
                parametro0->d_8018DEE0_indice = 0;
            }
            break;
        case 3:
            parametro0->d_8018DEE0_indice++;
            parametro0->param1 = 0;
            parametro0->paramf = (f32) (1.25 - ((parametro0->d_8018DEE0_indice - 0xF) * 0.002 * (parametro0->d_8018DEE0_indice - 0xF)));
            if ((parametro0->d_8018DEE0_indice >= 0xD) && ((f64) parametro0->paramf < 1.0)) {
                parametro0->paramf = 1.0f;
            }
            break;
    }
}

void funcion_800AC300(MenuItem* parametro0) {
    if (parametro0->param2 < ++parametro0->param1) {
        parametro0->type = 0;
    }
}

void funcion_800AC324(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 0:
            parametro0->column = 0x14A;
            parametro0->state = 1;
            funcion_800921B4();
            break;
        case 1:
            funcion_800A9208(parametro0, 0xA0);
            if (parametro0->column == 0xA0) {
                parametro0->state = 2;
                parametro0->param2 = 0;
            }
            break;
        case 2:
            parametro0->param2++;
            if (((dato_8018D9D8 != 0) || (parametro0->param2 >= 0x5B)) && (dato_800DDB24 != 0)) {
                parametro0->state = 3;
                parametro0->param1 = parametro0->column;
                agregar_item_menu(TIPO_ITEM_MENU_0AB, 0, 0, PRIORIDAD_ITEM_MENU_0);
            }
            break;
        case 3:
            parametro0->column = parametro0->param1;
            if (parametro0->param1 < 0x14A) {
                if (dato_8018D9D8 != 0) {
                    parametro0->param1 += 0x20;
                } else {
                    parametro0->param1 += 0x10;
                }
            } else {
                parametro0->type = 0;
            }
            break;
    }
}

void funcion_800AC458(MenuItem* parametro0) {
    s32 variable_a1;
    s32 variable_t1;
    s32 temporal_;

    switch (parametro0->state) {
        case 0:
            parametro0->column = -0x000000A0;
            parametro0->state = 1;
            for (variable_a1 = 0; variable_a1 < CANTIDAD_ARREGLO(premios_punto_gp); variable_a1++) {
                copia_puntos_gp[variable_a1] = premios_punto_gp[variable_a1];
            }
            parametro0->param2 = parametro0->column;
            break;
        case 1:
            parametro0->column = parametro0->param2;

            temporal_ = (dato_8018D9D8 != 0) ? 0x20 : 0x10;

            if ((parametro0->param2 + temporal_) < 0) {
                parametro0->param2 += temporal_;
                dato_800DC5EC->inicio_x_pantalla += temporal_;
                dato_800DC5F0->inicio_x_pantalla -= temporal_;
            } else {
                parametro0->param2 = 0;
                parametro0->column = 0;
                parametro0->state = 2;
                parametro0->param1 = 0;
                dato_800DC5EC->inicio_x_pantalla = 0x00F0;
                dato_800DC5F0->inicio_x_pantalla = 0x0050;
            }
            break;
        case 2:
            parametro0->column = 0;
            parametro0->param1++;
            if (((dato_8018D9D8 != 0) || (parametro0->param1 >= 0x1F)) && (dato_800DDB24 != 0)) {
                parametro0->state = 3;
                parametro0->param1 = 0;
                parametro0->param2 = 0;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
            variable_t1 = 0;
            variable_a1 = parametro0->state - 3;
            parametro0->param1++;
            if (((parametro0->param1 % 3) == 0) || (dato_8018D9D8 != 0)) {
                if (copia_puntos_gp[variable_a1] > 0) {
                    copia_puntos_gp[variable_a1]--;
                    puntos_gp_por_id_personaje[jugadores[gp_actual_carrera_jugador_id_por_puesto[variable_a1]].id_personaje] += 1;
                    reproducir_sonido2(SONIDO_PUNTAJE_CANTIDAD_ACCION);
                    variable_t1 = 0;
                    if ((copia_puntos_gp[variable_a1] == 0) && (parametro0->param2 == 0)) {
                        parametro0->param2 = 1;
                        parametro0->param1 = 0;
                    }
                }
            }
            if ((parametro0->param2 != 0) && ((parametro0->param1 > 0xA) || ((dato_8018D9D8 != 0) && (parametro0->param1 >= 4)))) {
                variable_t1 = 1;
            }
            if (variable_t1 != 0) {
                parametro0->param2 = 0;
                parametro0->param1 = 0;
                if (parametro0->state < 6) {
                    parametro0->state++;
                } else {
                    parametro0->state = 7;
                }
            }
            break;
        case 7:
            parametro0->param1++;
            if ((((dato_8018D9D8 != 0) && (parametro0->param1 >= 0xB)) || (parametro0->param1 >= 0x3D)) && (dato_800DDB24 != 0)) {
                parametro0->state = 8;
                parametro0->param1 = 0;
            }
            break;
        case 8:
            parametro0->param1++;
            if (dato_8018D9D8 != 0) {
                parametro0->param1 += 5;
            }
            if (parametro0->param1 >= 0x29) {
                parametro0->state = 9;
            }
            break;
        case 9:
            parametro0->param1--;
            if (dato_8018D9D8 != 0) {
                parametro0->param1 -= 5;
            }
            if (parametro0->param1 <= 0) {
                parametro0->state = 0x0000000A;
                parametro0->param1 = 0;
                if (indice_circuito_en_copa == 3) {
                    for (variable_a1 = 0; variable_a1 < 8; variable_a1++) {
                        if (jugador_obtener_por_id_personaje[id_personaje_por_puesto_total_gp[variable_a1]] < cantidad_jugador) {
                            funcion_800B536C(variable_a1);
                            break;
                        }
                    }
                }
            }
            break;
        case 10:
            parametro0->param1++;
            if (parametro0->param1 > 0) {
                parametro0->state = 0x0000000B;
                parametro0->param1 = 0;
                funcion_800921B4();
            }
            break;
        case 11:
            if ((dato_8018D9D8 != 0) && (dato_800DDB24 != 0)) {
                parametro0->state = 0x0000000C;
                parametro0->param2 = parametro0->row;
                reproducir_sonido2(SONIDO_CIRCUITO_SIGUIENTE_ACCION);
            }
            break;
        case 12:
            parametro0->row = parametro0->param2;
            if (parametro0->param2 < 0xF0) {
                parametro0->param2 += 0x10;
                dato_800DC5EC->inicio_y_pantalla += 0x10;
                dato_800DC5F0->inicio_y_pantalla -= 0x10;
            } else {
                parametro0->param2 = 0;
                parametro0->state = 0x0000000D;
                parametro0->param1 = 0;
                dato_800DC5EC->inicio_y_pantalla = 0x012C;
                dato_800DC5F0->inicio_y_pantalla = -0x003C;
                dato_8015F894 = 4;
                funcion_800CA330(0x19U);
            }
            break;
        case 13:
        default:
            break;
    }
}

void funcion_800AC978(MenuItem* parametro0) {
    switch (parametro0->state) { /* irregular */
        case 0:
            parametro0->column = 0x14A;
            parametro0->state = 1;
            parametro0->param1 = 0xFF;
            break;
        case 1:
            funcion_800A9208(parametro0, 0xA0);
            if (parametro0->column == 0xA0) {
                parametro0->state = 2;
            }
            break;
        case 2:
            break;
        case 3:
            if (parametro0->param1 != 0) {
                parametro0->param1 -= 0x33;
            }
            break;
    }
}

void funcion_800ACA14(MenuItem* parametro0) {
    switch (parametro0->state) { /* irregular */
        case 0:
            if (parametro0->param2 >= 0xB) {
                parametro0->param1 += 3;
            }
            if (parametro0->param1 >= 0x65) {
                parametro0->state = 0x0000000B;
                parametro0->param1 = 0;
            }
            break;
        case 11:
        case 12:
            if (es_pantalla_siendo_fundido()) {
                break;
            }

            if ((mando_cinco->boton_pulsado | mando_cinco->palanca_pulsado) & U_JPAD) {
                if (parametro0->state >= 0xC) {
                    parametro0->state--;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (parametro0->paramf < 4.2) {
                        parametro0->paramf += 4.0;
                    }
                    parametro0->estado_sub = -1;
                }
            }
            if ((mando_cinco->boton_pulsado | mando_cinco->palanca_pulsado) & D_JPAD) {
                if (parametro0->state < 0xC) {
                    parametro0->state++;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (parametro0->paramf < 4.2) {
                        parametro0->paramf += 4.0;
                    }
                    parametro0->estado_sub = 1;
                }
            }
            if (mando_cinco->boton_pulsado & (A_BUTTON | START_BUTTON)) {
                funcion_8009DFE0(0x0000001E);
                funcion_800CA330(0x19U);
                reproducir_sonido2(SONIDO_DESCONOCIDO_CONTINUAR_ACCION);
                if (parametro0->paramf < 4.2) {
                    parametro0->paramf += 4.0;
                }
            }
            break;
        default:
            break;
    }
    if (parametro0->param2 < 0x28) {
        parametro0->param2++;
    }
}

void funcion_800ACC50(MenuItem* parametro0) {
    s32 i;

    switch (parametro0->state) {
        case 0:
            parametro0->param1 += 3;
            if (parametro0->param1 >= 0x65) {
                parametro0->state = 1;
                parametro0->param1 = 0;
                for (i = 0; i < cantidad_jugador; i++) {
                    agregar_item_menu(i + TIPO_ITEM_MENU_0B1, 0, 0, (s8) (PRIORIDAD_ITEM_MENU_5 - i));
                }
            }
            break;
        case 1:
            if (buscar_duplicado_items_menu(0x000000B1)->state >= 2) {
                parametro0->state = 2;
            }
            break;
        case 2:
            parametro0->param1 += 0x20;
            if (parametro0->param1 >= 0x100) {
                if (seleccion_modo == VERSUS) {
                    parametro0->state = (s32) versus_seleccion_cursor_resultado;
                } else {
                    parametro0->state = (s32) batalla_resultado_cursor_seleccion;
                }
                parametro0->param1 = 0;
            }
            break;
        case 10:
        case 11:
        case 12:
        case 13:
            if (es_pantalla_siendo_fundido() == 0) {
                if ((mando_cinco->boton_pulsado | mando_cinco->palanca_pulsado) & U_JPAD) {
                    if (parametro0->state >= 0xB) {
                        parametro0->state--;
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        parametro0->estado_sub = -1;
                    }
                }
                if ((mando_cinco->boton_pulsado | mando_cinco->palanca_pulsado) & D_JPAD) {
                    if (parametro0->state < 0xD) {
                        parametro0->state++;
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        parametro0->estado_sub = 1;
                    }
                }
                if (mando_cinco->boton_pulsado & (START_BUTTON | A_BUTTON)) {
                    funcion_8009DFE0(0x0000001E);
                    reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
                    if (seleccion_modo == VERSUS) {
                        versus_seleccion_cursor_resultado = (s8) parametro0->state;
                    } else {
                        batalla_resultado_cursor_seleccion = (s8) parametro0->state;
                    }
                    if (parametro0->paramf < 4.2) {
                        parametro0->paramf += 4.0;
                    }
                }
            }
            break;
        default:
            break;
    }
}

void funcion_800ACF40(MenuItem* parametro0) {
    desconocido_d_800E70A0* temporal_v0_2;
    s32 algun_indice_jugador;
    s32 temporal_a1;
    s32 variable_v1;
    SIN_USO s32 margen_pila_0;

    algun_indice_jugador = parametro0->type - 0xB1;
    temporal_a1 = dato_800EFD64[selecciones_personaje[parametro0->type - 0xB1]];
    switch (parametro0->state) {
        case 0:
            parametro0->column = dato_800E72F8.column;
            parametro0->row = dato_800E72F8.row;
            parametro0->state = 1;
            break;
        case 1:
            temporal_v0_2 = &dato_800E7300[((cantidad_jugador - 2) * 4) + algun_indice_jugador];
            funcion_800A9208(parametro0, temporal_v0_2->column);
            funcion_800A9278(parametro0, temporal_v0_2->row);
            if (parametro0->column == temporal_v0_2->column) {
                parametro0->state = 2;
                parametro0->param2 = 0;
            }
            break;
        case 2:
            variable_v1 = 0;
            switch (seleccion_modo) {
                case 2:
                    if (gp_actual_carrera_puesto_por_id_jugador[algun_indice_jugador] != 0) {
                        variable_v1 = 1;
                    }
                    break;
                case 3:
                    if (algun_indice_jugador != indice_ganador_jugador) {
                        variable_v1 = 1;
                    }
                    break;
            }
            if (variable_v1 == 0) {
                parametro0->param2++;
                if (parametro0->param2 >= 0x1F) {
                    if (buscar_duplicado_items_menu(0x000000B0)->state >= 2) {
                        funcion_8009A640(parametro0->d_8018DEE0_indice, 0, algun_indice_jugador,
                                      segmentado_a_duplicado_virtual_2(animacion_celebracion_personaje[temporal_a1]));
                        parametro0->state = 3;
                        funcion_800CA24C(algun_indice_jugador);
                        funcion_800C90F4(algun_indice_jugador, (selecciones_personaje[algun_indice_jugador] * 0x10) + 0x29008007);
                    }
                }
            }
            break;
        case 3:
            if (dato_8018DEE0[parametro0->d_8018DEE0_indice].indice_secuencia >= dato_800E8440[temporal_a1]) {
                funcion_8009A640(parametro0->d_8018DEE0_indice, 0, algun_indice_jugador, segmentado_a_duplicado_virtual_2(dato_800E83A0[temporal_a1]));
                parametro0->state = 4;
            }
            break;
        case 4:
        default:
            break;
    }
}

void funcion_800AD1A4(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 0:
            parametro0->column = 0x0000014A;
            parametro0->state = 1;
            funcion_800921B4();
            agregar_item_menu(TIPO_ITEM_MENU_0BB, 0, 0, PRIORIDAD_ITEM_MENU_0);
            break;
        case 1:
            funcion_800A9208(parametro0, 0x000000A0);
            if (parametro0->column == 0x000000A0) {
                parametro0->state = 2;
                parametro0->param2 = 0;
            }
            break;
        case 2:
            parametro0->param2++;
            if (parametro0->param2 >= 0x15) {
                parametro0->state = 3;
            }
            break;
        case 3:
            if (dato_8018D9D8 != 0) {
                funcion_800921B4();
                parametro0->state = 4;
                parametro0->param1 = parametro0->column;
                agregar_item_menu(TIPO_ITEM_MENU_0BA, 0, 0, PRIORIDAD_ITEM_MENU_0);
            }
            break;
        case 4:
            parametro0->column = parametro0->param1;
            if (parametro0->param1 < 0x14A) {
                if (dato_8018D9D8 != 0) {
                    parametro0->param1 += 0x20;
                } else {
                    parametro0->param1 += 0x10;
                }
            } else {
                parametro0->type = 0;
            }
            break;
        default:
            break;
    }
}
