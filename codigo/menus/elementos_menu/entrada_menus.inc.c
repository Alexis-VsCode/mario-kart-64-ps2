// Entrada menus

void funcion_800AD2E8(MenuItem* parametro0) {
    struct_8018EE10_entrada* cosa;
    s32 variable_v1;
    s32 variable_a1;
    s32 index;

    switch (parametro0->state) {
        case 0:
            parametro0->column = -0x000000A0;
            parametro0->state = 1;
            for (index = 0; index < CANTIDAD_ARREGLO(premios_punto_gp); index++) {
                copia_puntos_gp[index] = premios_punto_gp[index];
            }
            parametro0->param2 = parametro0->column;
            break;
            ;
        case 1:
            parametro0->column = parametro0->param2;
            if (dato_8018D9D8 != 0) {
                variable_a1 = 0x20;
            } else {
                variable_a1 = 0x10;
            }
            if ((parametro0->param2 + variable_a1) < 0) {
                parametro0->param2 += variable_a1;
                dato_800DC5EC->inicio_x_pantalla += variable_a1;
                dato_800DC5F0->inicio_x_pantalla -= variable_a1;
            } else {
                parametro0->param2 = 0;
                parametro0->column = 0;
                parametro0->state = contrarreloj_seleccion_cursor_resultado;
                if ((parametro0->state == 9) && (publicar_contrarreloj_guardado_no_puede_repeticion == 1)) {
                    parametro0->state--;
                }
                dato_800DC5EC->inicio_x_pantalla = 0x00F0;
                dato_800DC5F0->inicio_x_pantalla = 0x0050;
            }
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            if (es_pantalla_siendo_fundido() == 0) {
                if ((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & U_JPAD) {
                    if (parametro0->state >= 6) {
                        parametro0->state--;
                        if ((publicar_contrarreloj_guardado_no_puede_repeticion == 1) && (parametro0->state == 9)) {
                            parametro0->state--;
                        }
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        parametro0->estado_sub = -1;
                    }
                }
                if ((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & D_JPAD) {
                    if (parametro0->state < 0xA) {
                        parametro0->state++;
                        if ((publicar_contrarreloj_guardado_no_puede_repeticion == 1) && (parametro0->state == 9)) {
                            parametro0->state++;
                        }
                        if ((parametro0->state == 0x0000000A) && (b_jugador_fantasma_desactivado != 0)) {
                            parametro0->state -= 2;
                        } else {
                            reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                            if (parametro0->paramf < 4.2) {
                                parametro0->paramf += 4.0;
                            }
                            parametro0->estado_sub = 1;
                        }
                    }
                }
                if (mando_uno->boton_pulsado & (START_BUTTON | A_BUTTON)) {
                    if (parametro0->state == 0x0000000A) {
                        variable_v1 = 0;
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        if (controller_pak_1_estado != 0) {
                            variable_v1 = 0;
                            switch (osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego,
                                                  (u8*) codigo_ext, &controller_pak_nota_1_archivo)) {
                                case 5:
                                    break;
                                case 0:
                                    funcion_800B6708();
                                    parametro0->state = funcion_800B6348((seleccion_copa * 4) + indice_circuito_en_copa) + 0x11;
                                    variable_v1 = 1;
                                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                                    break;
                                case 2:
                                    controller_pak_1_estado = 0;
                                    break;
                                default:
                                    controller_pak_1_estado = 0;
                                    break;
                            }
                        }
                        if (variable_v1 == 0) {
                            if (controller_pak_1_estado == 0) {
                                switch (funcion_800B5F30()) {
                                    case -1:
                                        parametro0->state = 0x0000000B;
                                        variable_v1 = 1;
                                        break;
                                    case -3:
                                    case -2:
                                        parametro0->state = 0x0000000C;
                                        variable_v1 = 1;
                                        break;
                                    case 1:
                                    case 11:
                                        parametro0->state = 0x0000000B;
                                        variable_v1 = 1;
                                        break;
                                    case 10:
                                        parametro0->state = 0x0000000C;
                                        variable_v1 = 1;
                                        break;
                                    default:
                                        variable_v1 = 1;
                                        parametro0->state = 0x0000000C;
                                        break;
                                    case 0:
                                        break;
                                }
                                if (variable_v1 != 0) {
                                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                    return;
                                }
                                if (osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego,
                                                  (u8*) codigo_ext, &controller_pak_nota_1_archivo) == 0) {
                                    funcion_800B6708();
                                    parametro0->state = funcion_800B6348((seleccion_copa * 4) + indice_circuito_en_copa) + 0x11;
                                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                                    return;
                                }
                            }
                            if (controller_pak_archivos_escribible_1_max >= controller_pak_1_num_archivos_usado) {
                                parametro0->state = 0x0000000E;
                                reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                return;
                            }
                            if (controller_pak_libre_paginas_1_num >= 0x79) {
                                parametro0->state = 0x00000013;
                                parametro0->param1 = 0;
                                reproducir_sonido2(SONIDO_SELECCION_MENU);
                                return;
                            }
                            parametro0->state = 0x0000000E;
                            reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                        }
                    } else {
                        parametro0->param1 = parametro0->state;
                        contrarreloj_seleccion_cursor_resultado = parametro0->state;
                        parametro0->state = 0x0000001E;
                        parametro0->param2 = parametro0->row;
                        reproducir_sonido2(SONIDO_CIRCUITO_SIGUIENTE_ACCION);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                    }
                }
            }
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 26:
            if (mando_uno->boton_pulsado & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                parametro0->state = 0x0000000A;
                reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                if (parametro0->paramf < 4.2) {
                    parametro0->paramf += 4.0;
                }
            }
            break;
        case 17:
        case 18:
            parametro0->param2 = parametro0->state - 0x11;
            if (funcion_800B639C((seleccion_copa * 4) + indice_circuito_en_copa) != parametro0->param2) {
                if ((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & U_JPAD) {
                    if (parametro0->state >= 0x12) {
                        parametro0->state--;
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        parametro0->estado_sub = -1;
                    }
                }
                if ((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & D_JPAD) {
                    if (parametro0->state < 0x12) {
                        parametro0->state++;
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        parametro0->estado_sub = 1;
                    }
                }
            }
            if (mando_uno->boton_pulsado & B_BUTTON) {
                parametro0->state = 0x0000000A;
                reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                return;
            }
            if (mando_uno->boton_pulsado & (START_BUTTON | A_BUTTON)) {
                cosa = &dato_8018EE10[parametro0->param2];
                if (cosa->fantasma_datos_guardado == 0) {
                    parametro0->state = 0x00000019;
                    parametro0->param1 = 0;
                } else if (funcion_800B63F0(parametro0->param2) == 0) {
                    parametro0->state = 0x00000010;
                } else {
                    parametro0->state = 0x00000014;
                }
                reproducir_sonido2(SONIDO_SELECCION_MENU);
                if (parametro0->paramf < 4.2) {
                    parametro0->paramf += 4.0;
                }
            }
            break;
        case 19:
            if ((parametro0->param1 == 1) && (funcion_800B6A68() != 0)) {
                parametro0->state = 0x0000000F;
                return;
            } else {
                parametro0->param1++;
                if (parametro0->param1 >= 2) {
                    parametro0->state = 0x00000011;
                }
            }
            break;
        case 20:
        case 21:
            if (((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & U_JPAD) && (parametro0->state >= 0x15)) {
                parametro0->state--;
                reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                if (parametro0->paramf < 4.2) {
                    parametro0->paramf += 4.0;
                }
                parametro0->estado_sub = -1;
            }
            if ((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & D_JPAD) {
                if (parametro0->state < 0x15) {
                    parametro0->state++;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (parametro0->paramf < 4.2) {
                        parametro0->paramf += 4.0;
                    }
                    parametro0->estado_sub = 1;
                }
            }
            if (mando_uno->boton_pulsado & B_BUTTON) {
                parametro0->state = parametro0->param2 + 0x11;
                reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                return;
            }
            if (mando_uno->boton_pulsado & (START_BUTTON | A_BUTTON)) {
                if (parametro0->state == 0x00000015) {
                    parametro0->state = 0x00000019;
                    parametro0->param1 = 0;
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                    if (parametro0->paramf < 4.2) {
                        parametro0->paramf += 4.0;
                    }
                } else {
                    parametro0->state = parametro0->param2 + 0x11;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                    return;
                }
            }
            break;
        case 25:
            if (parametro0->param1 == 1) {
                if (osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego, (u8*) codigo_ext,
                                  &controller_pak_nota_1_archivo) != 0) {
                    parametro0->state = 0x0000001A;
                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                    return;
                }
                if (funcion_800B6178(parametro0->param2) != 0) {
                    parametro0->state = 0x0000001A;
                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                    return;
                }
            }
            parametro0->param1++;
            if (parametro0->param1 >= 2) {
                parametro0->state = 0x0000000A;
                return;
            }
            break;
        case 30:
            parametro0->row = parametro0->param2;
            if (parametro0->param2 < 0xF0) {
                parametro0->param2 += 0x10;
                dato_800DC5EC->inicio_y_pantalla += 0x10;
                dato_800DC5F0->inicio_y_pantalla -= 0x10;
                return;
            }
            switch (parametro0->param1) {
                case 5:
                    dato_8015F890 = 0;
                    dato_8015F892 = 1;
                    funcion_802903B0();
                    break;
                case 6:
                    funcion_80290388();
                    break;
                case 7:
                    funcion_80290360();
                    break;
                case 8:
                    funcion_80290338();
                    break;
                case 9:
                    dato_8015F890 = 1;
                    dato_8015F892 = 0;
                    funcion_802903B0();
                    break;
            }
            parametro0->param2 = 0;
            parametro0->state = 0x0000001F;
            dato_800DC5EC->inicio_y_pantalla = 0x012C;
            dato_800DC5F0->inicio_y_pantalla = -0x003C;
            dato_8015F894 = 4;
            funcion_800CA330(0x19U);
            break;
        case 31:
            parametro0->type = 0;
            break;
    }
}
#ifdef VERSION_EU
#define FUNC_800ADF48DEF 70
#else
#define FUNC_800ADF48DEF 60
#endif
void funcion_800ADF48(MenuItem* parametro0) {
    SIN_USO s32 margen_pila;
    struct Mando* mando;

    if (juego_en_pausa != 0) {
        switch (parametro0->state) {
            case 0:
                parametro0->state = dato_800F0B50[seleccion_modo];
                break;
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 21:
            case 22:
            case 23:
            case 24:
            case 31:
            case 32:
            case 41:
            case 42:
            case 43:
            case 44:
                if (es_pantalla_siendo_fundido() == 0) {
                    mando = &mandos[juego_en_pausa - 1];
                    if ((mando->boton_pulsado | mando->palanca_pulsado) & U_JPAD) {
                        if (dato_800F0B50[seleccion_modo] < parametro0->state) {
                            parametro0->state--;
                            reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                            if (parametro0->paramf < 4.2) {
                                parametro0->paramf += 4.0;
                            }
                            parametro0->estado_sub = -1;
                        }
                    }
                    if ((mando->boton_pulsado | mando->palanca_pulsado) & D_JPAD) {
                        if (parametro0->state < dato_800F0B54[seleccion_modo]) {
                            parametro0->state++;
                            reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                            if (parametro0->paramf < 4.2) {
                                parametro0->paramf += 4.0;
                            }
                            parametro0->estado_sub = 1;
                        }
                    }
                    if (mando->boton_pulsado & B_BUTTON) {
                        if (parametro0->state != dato_800F0B50[seleccion_modo]) {
                            parametro0->state = dato_800F0B50[seleccion_modo];
                            reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                            return;
                        }
                    }
                    if (mando->boton_pulsado & (START_BUTTON | A_BUTTON)) {
                        if (parametro0->state == dato_800F0B50[seleccion_modo]) {
                            parametro0->state = 0;
                            juego_en_pausa = 0;
                            funcion_8028DF38();
                            funcion_800C9F90(0U);
                        } else {
                            funcion_8009DFE0(30);
                            reproducir_sonido2(SONIDO_DESCONOCIDO_CONTINUAR_ACCION);
                            funcion_800CA330(FUNC_800ADF48DEF);
                            if (parametro0->paramf < 4.2) {
                                parametro0->paramf += 4.0;
                            }
                        }
                    }
                }
                break;
            default:
                break;
        }
    } else {
        parametro0->state = 0;
    }
}

void funcion_800AE218(MenuItem* parametro0) {
    struct_8018EE10_entrada* cosa;
    s32 variable_v1;

    if (parametro0->state != 0) {
        dato_800DC5B8 = 0;
    }
    switch (parametro0->state) {
        case 0:
            if (parametro0->param1 < 0x1E) {
                parametro0->param1++;
            }
            if (mando_uno->boton_pulsado & START_BUTTON) {
                parametro0->state = 0x0000000F;
                reproducir_sonido2(SONIDO_ATRAS_IR_ACCION_2);
            } else if (h_ud_jugador[JUGADOR_UNO].bool_completo_carrera != 0) {
                parametro0->state = 1;
                parametro0->param1 = 0;
            }
            break;
        default:
            break;
        case 1:
            parametro0->param1 += 3;
            if (parametro0->param1 >= 0x8D) {
                parametro0->state = 0x0000000F;
            }
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            if (es_pantalla_siendo_fundido() == 0) {
                if ((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & U_JPAD) {
                    if (parametro0->state >= 0xC) {
                        parametro0->state--;
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        parametro0->estado_sub = -1;
                    }
                }
                if ((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & D_JPAD) {
                    if (parametro0->state < 0x10) {
                        parametro0->state++;
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        parametro0->estado_sub = 1;
                    }
                }
                if (mando_uno->boton_pulsado & (START_BUTTON | A_BUTTON)) {
                    if (parametro0->state == 0x00000010) {
                        variable_v1 = 0;
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        if (controller_pak_1_estado != 0) {
                            variable_v1 = 0;
                            switch (osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego,
                                                  (u8*) codigo_ext, &controller_pak_nota_1_archivo)) {
                                case PFS_ERR_INVALID:
                                    break;
                                case ERROR_SIN_PFS:
                                    funcion_800B6708();
                                    parametro0->state = funcion_800B6348((seleccion_copa * 4) + indice_circuito_en_copa) + 0x1E;
                                    variable_v1 = 1;
                                    break;
                                case PFS_ERR_NEW_PACK:
                                    controller_pak_1_estado = 0;
                                    break;
                                default:
                                    controller_pak_1_estado = 0;
                                    break;
                            }
                        }
                        if (variable_v1 != 0) {
                            reproducir_sonido2(SONIDO_SELECCION_MENU);
                            return;
                        }
                        if (controller_pak_1_estado == 0) {
                            switch (funcion_800B5F30()) {
                                case DATOS_INVALIDO_PFS:
                                    parametro0->state = 0x00000015;
                                    variable_v1 = 1;
                                    break;
                                case PFS_LIBRE_BLOQUES_ERROR:
                                case PFS_NUM_ARCHIVOS_ERROR:
                                    parametro0->state = 0x00000016;
                                    variable_v1 = 1;
                                    break;
                                case PFS_ERR_NOPACK:
                                case PFS_ERR_DEVICE:
                                    parametro0->state = 0x00000015;
                                    variable_v1 = 1;
                                    break;
                                case PFS_ERR_ID_FATAL:
                                    parametro0->state = 0x00000016;
                                    variable_v1 = 1;
                                    break;
                                default:
                                    variable_v1 = 1;
                                    parametro0->state = 0x00000016;
                                    break;
                                case 0:
                                    break;
                            }
                            if (variable_v1 != 0) {
                                reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                                return;
                            }
                            if (osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego,
                                              (u8*) codigo_ext, &controller_pak_nota_1_archivo) == 0) {
                                funcion_800B6708();
                                parametro0->state = funcion_800B6348((seleccion_copa * 4) + indice_circuito_en_copa) + 0x1E;
                                reproducir_sonido2(SONIDO_SELECCION_MENU);
                                return;
                            }
                        }
                        if (controller_pak_archivos_escribible_1_max >= controller_pak_1_num_archivos_usado) {
                            parametro0->state = 0x00000018;
                            reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                        } else if (controller_pak_libre_paginas_1_num >= 0x79) {
                            parametro0->state = 0x00000020;
                            parametro0->param1 = 0;
                            reproducir_sonido2(SONIDO_SELECCION_MENU);
                        } else {
                            parametro0->state = 0x00000018;
                            reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                        }
                    } else {
                        funcion_8009DFE0(0x0000001E);
                        reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
                        funcion_800CA330(0x19U);
                        funcion_800CA388(0x19U);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                    }
                }
            }
            break;
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 41:
            if (mando_uno->boton_pulsado & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                parametro0->state = 0x00000010;
                reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                if (parametro0->paramf < 4.2) {
                    parametro0->paramf += 4.0;
                }
            }
            break;
        case 30:
        case 31:
            parametro0->param2 = (u32) parametro0->state - 0x1E;
            if (funcion_800B639C((seleccion_copa * 4) + indice_circuito_en_copa) != parametro0->param2) {
                if ((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & U_JPAD) {
                    if (parametro0->state >= 0x1F) {
                        parametro0->state--;
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        parametro0->estado_sub = -1;
                    }
                }
                if ((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & D_JPAD) {
                    if (parametro0->state < 0x1F) {
                        parametro0->state++;
                        reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                        if (parametro0->paramf < 4.2) {
                            parametro0->paramf += 4.0;
                        }
                        parametro0->estado_sub = 1;
                    }
                }
            }
            if (mando_uno->boton_pulsado & B_BUTTON) {
                parametro0->state = 0x00000010;
                reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
            } else if (mando_uno->boton_pulsado & (START_BUTTON | A_BUTTON)) {
                cosa = &dato_8018EE10[parametro0->param2];
                if (cosa->fantasma_datos_guardado == 0) {
                    parametro0->state = 0x00000028;
                    parametro0->param1 = 0;
                } else if (funcion_800B63F0(parametro0->param2) == 0) {
                    parametro0->state = 0x0000001A;
                } else {
                    parametro0->state = 0x00000023;
                }
                reproducir_sonido2(SONIDO_SELECCION_MENU);
                if (parametro0->paramf < 4.2) {
                    parametro0->paramf += 4.0;
                }
            }
            break;
        case 32:
            if ((parametro0->param1 == 1) && (funcion_800B6A68() != 0)) {
                parametro0->state = 0x00000019;
            } else {
                parametro0->param1++;
                if (parametro0->param1 >= 2) {
                    parametro0->state = 0x0000001E;
                }
            }
            break;
        case 35:
        case 36:
            if (((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & U_JPAD) &&
                ((s32) (u32) parametro0->state >= 0x24)) {
                parametro0->state--;
                reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                if (parametro0->paramf < 4.2) {
                    parametro0->paramf += 4.0;
                }
                parametro0->estado_sub = -1;
            }
            if ((mando_uno->boton_pulsado | mando_uno->palanca_pulsado) & D_JPAD) {
                if (parametro0->state < 0x24) {
                    parametro0->state++;
                    reproducir_sonido2(SONIDO_MOVIMIENTO_CURSOR_MENU);
                    if (parametro0->paramf < 4.2) {
                        parametro0->paramf += 4.0;
                    }
                    parametro0->estado_sub = 1;
                }
            }
            if (mando_uno->boton_pulsado & B_BUTTON) {
                parametro0->state = parametro0->param2 + 0x1E;
                reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
            } else if (mando_uno->boton_pulsado & (START_BUTTON | A_BUTTON)) {
                if (parametro0->state == 0x00000024) {
                    parametro0->state = 0x00000028;
                    parametro0->param1 = 0;
                    reproducir_sonido2(SONIDO_SELECCION_MENU);
                    if (parametro0->paramf < 4.2) {
                        parametro0->paramf += 4.0;
                    }
                } else {
                    parametro0->state = parametro0->param2 + 0x1E;
                    reproducir_sonido2(SONIDO_ATRAS_IR_MENU);
                }
            }
            break;
        case 40:
            if (parametro0->param1 == 1) {
                if (osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego, (u8*) codigo_ext,
                                  &controller_pak_nota_1_archivo) != 0) {
                    parametro0->state = 0x00000029;
                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                    return;
                }
                if (funcion_800B6178(parametro0->param2) != 0) {
                    parametro0->state = 0x00000029;
                    reproducir_sonido2(SONIDO_ARCHIVO_MENU_NO_ENCONTRADO);
                    return;
                }
            }
            parametro0->param1++;
            if (parametro0->param1 >= 2) {
                parametro0->state = 0x00000010;
            }
            break;
    }
}

void funcion_800AEC54(MenuItem* parametro0) {
    switch (parametro0->state) {
        case 0:
            parametro0->column = (obtener_ancho_cadena(texto_menu_anuncio_fantasma) / 2) + 0x140;
            parametro0->row = 0x000000DA;
            parametro0->state = 1;
            funcion_800C90F4(0U, (dato_80162DE4 * 0x10) + 0x29008001);
            break;
        case 1:
            funcion_800A9208(parametro0, 0x000000A0);
            if (parametro0->column == 0x000000A0) {
                parametro0->state = 2;
                parametro0->param1 = 0;
            }
            break;
        case 2:
            parametro0->param1++;
            if (parametro0->param1 >= 0x3D) {
                parametro0->state = 3;
                parametro0->param1 = 0;
            }
            break;
        case 4:
            parametro0->param1++;
            if (parametro0->param1 >= 6) {
                parametro0->type = 0;
                break;
            }
        case 3:
            funcion_800A94C8(parametro0, 0x000000A0, -1);
            if (((parametro0->column + 0x14) == -(obtener_ancho_cadena(texto_menu_anuncio_fantasma) / 2)) && (parametro0->state == 3)) {
                parametro0->state = 4;
            }
            break;
        default:
            break;
    }
}

void funcion_800AEDBC(MenuItem* parametro0) {
    if (parametro0->param1 != contrarreloj_indice_circuito_datos) {
        parametro0->param1 = (s32) contrarreloj_indice_circuito_datos;
        funcion_8009A594(parametro0->d_8018DEE0_indice, 0,
                      segmentado_a_duplicado_virtual_2(
                          dato_800E7E34[orden_circuito_copa[contrarreloj_indice_circuito_datos / 4][contrarreloj_indice_circuito_datos % 4]]));
        if (controller_pak_1_situacion() == ERROR_SIN_PFS) {
            funcion_800B6708();
        } else {
            dato_8018EE10[0].fantasma_datos_guardado = 0;
            dato_8018EE10[1].fantasma_datos_guardado = 0;
        }
    }
}

void funcion_800AEE90(MenuItem* parametro0) {
    if (seleccion_menu_sub != SUB_MENU_DATOS_OPCIONES) {
        parametro0->visible = 0;
    } else {
        parametro0->visible = 1;
    }
}

void funcion_800AEEBC(MenuItem* parametro0) {
    if (seleccion_menu_sub != SUB_MENU_DATOS_BORRAR_CONFIRMAR) {
        parametro0->visible = 0;
    } else {
        parametro0->visible = 1;
    }
}

void funcion_800AEEE8(MenuItem* parametro0) {
    if (seleccion_menu_sub != SUB_MENU_DATOS_NO_PUEDE_BORRAR) {
        parametro0->visible = 0;
    } else {
        parametro0->visible = 1;
    }
}

void funcion_800AEF14(MenuItem* parametro0) {
    if (h_ud_jugador[JUGADOR_UNO].bool_completo_carrera != 0) {
        if ((u32) h_ud_jugador[JUGADOR_UNO].algun_temporizador < (u32) (funcion_800B4E24(4) & 0xFFFFF)) {
            dato_8018ED90 = 1;
        }
        parametro0->type = 0;
    }
}

void funcion_800AEF74(MenuItem* parametro0) {
    switch (parametro0->state) { /* irregular */
        case 0:
            if (publicar_contrarreloj_guardado_no_puede_repeticion == 1) {
                parametro0->state = 1;
                parametro0->param1 = 0;
            } else if (h_ud_jugador[JUGADOR_UNO].bool_completo_carrera == (s8) 1) {
                parametro0->state = 2;
            }
            break;
        case 2:
            break;
        case 1:
            parametro0->param1 += 1;
            if (h_ud_jugador[JUGADOR_UNO].bool_completo_carrera == 1) {
                parametro0->state = 2;
            }
            break;
    }
}

void funcion_800AF004(MenuItem* parametro0) {
    SIN_USO s32 temporal_t1;

    switch (parametro0->state) {
        case 0:
            parametro0->param1 += 3;
            if (parametro0->param1 >= 0x65) {
                parametro0->param1 = 0;
                parametro0->state = 1;
                seleccion_copa %= 4;
                seleccion_cc %= 4;
                agregar_item_menu(TIPO_ITEM_MENU_12C, 0, 0, PRIORIDAD_ITEM_MENU_4);
            }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            parametro0->param1 += 1;
            if (parametro0->param1 >= 9) {
                parametro0->param1 = 0;
                parametro0->state++;
                agregar_item_menu(parametro0->state + TIPO_ITEM_MENU_12B, 0, 0, PRIORIDAD_ITEM_MENU_4);
            }
            break;
        case 5:
            parametro0->param1 += 1;
            if ((parametro0->param1 >= 0x65) &&
                ((mando_cinco->boton_pulsado != 0) || (mando_cinco->palanca_pulsado != 0))) {
                parametro0->state = 6;
                parametro0->param1 = 0;
                if (dato_802874D8.desconocido_1d < 3) {
                    reproducir_sonido2(SONIDO_MENU_OK_CLICKED);
                } else {
                    reproducir_sonido2(SONIDO_DESCONOCIDO_CONTINUAR_ACCION);
                }
            }
            break;
        case 6:
            funcion_8009DFE0(0x0000001E);
            funcion_800CA330(0x19U);
            funcion_800CA388(0x19U);
            parametro0->state = 7;
            break;
        case 7:
        default:
            break;
    }
}

void funcion_800AF1AC(MenuItem* parametro0) {
    desconocido_d_800E70A0* temporal_v0_2;
    s32 idx = parametro0->type - 0x12C;

    switch (parametro0->state) { /* irregular */
        case 0:
            temporal_v0_2 = &dato_800E7458[idx];
            parametro0->column = temporal_v0_2->column;
            parametro0->row = temporal_v0_2->row;
            parametro0->state = 1;
            break;
        case 1:
            temporal_v0_2 = &dato_800E7480[idx];
            funcion_800A91D8(parametro0, temporal_v0_2->column, temporal_v0_2->row);
            if ((parametro0->column == temporal_v0_2->column) && (parametro0->row == temporal_v0_2->row)) {
                parametro0->state = 2;
            }
            break;
        case 2:
            break;
    }
}
