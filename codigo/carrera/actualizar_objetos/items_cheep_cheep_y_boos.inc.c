// Items cheep cheep y boos

void funcion_8007AA44(s32 id_jugador) {
    s32 indice_objeto;

    funcion_8007A910(id_jugador);
    indice_objeto = indice_lakitu_lista[id_jugador];
    lakitu_ptr_textura = dato_80183FA8[id_jugador];
    switch (lista_objeto[indice_objeto].desconocido_0D8) {
        case 1:
            funcion_80079114(indice_objeto, id_jugador, 2);
            funcion_8007A66C(indice_objeto, dato_8018CF1C, dato_8018CF14);
            break;
        case 2:
            funcion_80079114(indice_objeto, id_jugador, 0);
            funcion_8007A66C(indice_objeto, dato_8018CF1C, dato_8018CF14);
            break;
        case 3:
            funcion_80079114(indice_objeto, id_jugador, 0);
            funcion_8007A778(indice_objeto, dato_8018CF1C, dato_8018CF14);
            break;
        case 4:
            funcion_80079114(indice_objeto, id_jugador, 0);
            funcion_8007A66C(indice_objeto, dato_8018CF1C, dato_8018CF14);
            break;
        case 5:
            funcion_80079114(indice_objeto, id_jugador, 0);
            funcion_8007A66C(indice_objeto, dato_8018CF1C, dato_8018CF14);
            break;
        case 6:
            funcion_80079114(indice_objeto, id_jugador, 0);
            funcion_8007A66C(indice_objeto, dato_8018CF1C, dato_8018CF14);
            break;
        case 7:
            funcion_80079114(indice_objeto, id_jugador, 0);
            funcion_8007A778(indice_objeto, dato_8018CF1C, dato_8018CF14);
            break;
        case 0:
        default:
            break;
    }
}

void funcion_8007ABFC(s32 id_jugador, bool parametro1) {
    s32 ventana_item;

    if (h_ud_jugador[id_jugador].bool_completo_carrera == false) {
        ventana_item = ventana_item_objeto_por_id_jugador[id_jugador];
        if (funcion_80072354(ventana_item, 4) != 0) {
            inicializar_objeto(ventana_item, 0);
            if (parametro1 != 0) {
                h_ud_jugador[id_jugador].sobrescribir_item = parametro1;
            }
        }
        funcion_800C9060(id_jugador, 0x19008406U);
    }
}

void consumir_item(s32 id_jugador) {
    SIN_USO s32 relleno;
    Jugador* jugador;
    s32 indice_objeto;
    VentanaItemObjetos* ventana_item;

    jugador = &jugador_uno[id_jugador];
    indice_objeto = ventana_item_objeto_por_id_jugador[id_jugador];
    ventana_item = (VentanaItemObjetos*) &lista_objeto[indice_objeto];
    if (ventana_item->item_actual == ITEM_SUPER_HONGO) {
        if (funcion_80072354(indice_objeto, 2) != 0) {
            funcion_800722A4(indice_objeto, 2);
            ventana_item->hongo_dorado_temporizador = 0x0258;
            funcion_800726CC(indice_objeto, 0x00000032);
        }
        if (ventana_item->hongo_dorado_temporizador == 0) {
            funcion_800722CC(indice_objeto, 2);
            jugador->copia_item_actual = NINGUNO_ITEM;
            ventana_item->item_actual = NINGUNO_ITEM;
            fijar_estado_temporizador_objeto(indice_objeto, 0);
            funcion_800726CC(indice_objeto, 9);
        }
    } else {
        jugador->copia_item_actual = NINGUNO_ITEM;
        ventana_item->item_actual = NINGUNO_ITEM;
        fijar_estado_temporizador_objeto(indice_objeto, 0);
    }
}

u8 generar_item_aleatorio(s16 puesto, s16 es_cpu) {
    u16 rand = int_aleatorio(100);
    u8* curva;
    u8 item_aleatorio;

    indice_item_aleatorio = ((u32) rand + (indice_item_aleatorio + aleatorio_mando) + contador_frame_carrera) % 100U;

    if (seleccion_modo == VERSUS) {
        switch (seleccion_cantidad_jugador_1) {
            case DOS_JUGADORES_SELECCIONADO:
                curva = segmentado_a_virtual((void*) comun_versus_curva_item_2_jugador);
                break;
            case TRES_JUGADORES_SELECCIONADO:
                curva = segmentado_a_virtual((void*) comun_versus_curva_item_3_jugador);
                break;
            case CUATRO_JUGADORES_SELECCIONADO:
                curva = segmentado_a_virtual((void*) comun_versus_curva_item_4_jugador);
                break;
        }
        item_aleatorio = *((puesto * 100) + curva + indice_item_aleatorio);

    } else if (seleccion_modo == BATALLA) {
        curva = segmentado_a_virtual((void*) comun_batalla_item_curva);
        item_aleatorio = curva[indice_item_aleatorio];
    } else {
        if (es_cpu == 0) {
            curva = segmentado_a_virtual((void*) comun_gran_premio_curva_item_humano);
        } else {
            curva = segmentado_a_virtual((void*) comun_gran_premio_curva_item_cpu);
        }
        item_aleatorio = *((puesto * 100) + curva + indice_item_aleatorio);
    }

    return item_aleatorio;
}

u8 generar_humano_item_aleatorio(SIN_USO s16 parametro0, s16 puesto) {
    return generar_item_aleatorio(puesto, false);
}

u8 cpu_gen_aleatorio_item(SIN_USO s32 parametro0, s16 puesto) {
    return generar_item_aleatorio(puesto, true);
}

s16 funcion_8007AFB0(s32 indice_objeto, s32 parametro1) {
    SIN_USO s32 relleno[3];
    s16 item_aleatorio;

    item_aleatorio = generar_humano_item_aleatorio(cantidad_vuelta_por_id_jugador[parametro1], gp_actual_carrera_puesto_por_id_jugador[parametro1]);

    if (h_ud_jugador[parametro1].sobrescribir_item != 0) {
        item_aleatorio = (s16) h_ud_jugador[parametro1].sobrescribir_item;
        h_ud_jugador[parametro1].sobrescribir_item = 0;
    }

    funcion_800729B4(indice_objeto, (s32) item_aleatorio);

    return item_aleatorio;
}

s32 funcion_8007B040(s32 indice_objeto, s32 id_jugador) {
    SIN_USO s16 margen_pila;
    s32 temporal_v1;
    s32 variable_a3;
    s32 variable_t3;
    s32 temporal_a0;
    s32 variable_v1;
    s32 sp50[4];
    s32 sp40[4];
    s32 variable_v1_2;
    Jugador* sp38;
    s16 temporal_a1;

    variable_a3 = 0;
    variable_t3 = 0;
    if (seleccion_modo == GRAN_PREMIO) {
        if (int_aleatorio(0x0064U) < 0x51) {
            variable_v1 = generar_humano_item_aleatorio(cantidad_vuelta_por_id_jugador[id_jugador], gp_actual_carrera_puesto_por_id_jugador[id_jugador]);
        } else {
            variable_v1 = 0;
            funcion_800C9060(id_jugador, 0x1900A058U);
        }
        variable_t3 = 1;
        lista_objeto[indice_objeto].textura_indice_lista = lista_objeto[indice_objeto].desconocido_0A2 = variable_v1;
    } else {
        for (variable_v1_2 = 0; variable_v1_2 < seleccion_cantidad_jugador_1; variable_v1_2++) {
            temporal_a0 = ventana_item_objeto_por_id_jugador[variable_v1_2];
            if (variable_v1_2 != id_jugador) {
                if (lista_objeto[temporal_a0].type != 0) {
                    sp50[variable_a3] = variable_v1_2;
                    sp40[variable_a3] = lista_objeto[temporal_a0].type;
                    variable_a3 += 1;
                }
            }
        }
        if (variable_a3 != 0) {
            variable_v1 = int_aleatorio(variable_a3);
            temporal_a1 = sp40[variable_v1];
            lista_objeto[indice_objeto].desconocido_0A2 = temporal_a1;
            lista_objeto[indice_objeto].textura_indice_lista = temporal_a1;
            temporal_v1 = sp50[variable_v1];
            lista_objeto[indice_objeto].desconocido_0D1 = temporal_v1;
            temporal_a0 = ventana_item_objeto_por_id_jugador[temporal_v1];
            sp38 = &jugador_uno[temporal_v1];
            funcion_800722A4(temporal_a0, 1);
            lista_objeto[temporal_a0].type = 0;
            sp38->copia_item_actual = 0;
            if (funcion_80072320(temporal_a0, 2) != 0) {
                funcion_800722CC(temporal_a0, 2);
                lista_objeto[temporal_a0].temporizador_animacion = 0;
            }
            variable_t3 = 1;
        }
    }
    return variable_t3;
}

void funcion_8007B254(s32 indice_objeto, s32 parametro1) {
    s8 probar;

    funcion_80072428(indice_objeto);
    lista_objeto[indice_objeto].state = 2;
    lista_objeto[indice_objeto].type = 0;
    lista_objeto[indice_objeto].tlut_lista = (u8*) tlut_comun_ventana_item_ninguno;
    lista_objeto[indice_objeto].textura_lista = textura_comun_ventana_item_ninguno;
    lista_objeto[indice_objeto].textura_ancho = 0x28;
    lista_objeto[indice_objeto].textura_altura = 0x20;
    lista_objeto[indice_objeto].desconocido_04C = 0x00000032;
    lista_objeto[indice_objeto].desconocido_0D6 = 1;
    lista_objeto[indice_objeto].temporizador_animacion = 0;
    funcion_800722A4(indice_objeto, 4);
    if (dato_80165888 != 0) {
        funcion_800726CC(indice_objeto, 8);
        lista_objeto[indice_objeto].desconocido_0D6 = 2;
        lista_objeto[indice_objeto].type = 0x000E;
        probar = lista_objeto[indice_objeto].type;
        lista_objeto[indice_objeto].textura_indice_lista = probar;
        lista_objeto[indice_objeto].desconocido_0A2 = probar;
        h_ud_jugador[JUGADOR_UNO].deslizamiento_caja_item_y = 0;
        dato_80165888 = 0;
    } else {
        funcion_800C8F80(parametro1, 0x0100FE1CU);
    }
}

void funcion_8007B34C(s32 id_jugador) {
    s32 temporal_s0;
    s32 sp40;
    Objeto* objeto;
    Jugador* sp38;
    struct Mando* variable_nuevo;

    temporal_s0 = ventana_item_objeto_por_id_jugador[id_jugador];
    sp38 = &jugador_uno[id_jugador];
    sp40 = 0;
    variable_nuevo = &mando_uno[id_jugador];
    if (variable_nuevo->boton_pulsado & Z_TRIG) {
        sp40 = 1;
    }
    if (dato_80165888 != 0) {
        inicializar_objeto(temporal_s0, 0);
    }
    objeto = &lista_objeto[temporal_s0];
    switch (objeto->state) {
        case 1:
            funcion_8007B254(temporal_s0, id_jugador);
            break;
        case 2:
            if (modo_pantalla_activo == 0) {
                arriba_paso_s16_hacia(&h_ud_jugador[id_jugador].deslizamiento_caja_item_y, 0x0040, 4);
                if (h_ud_jugador[id_jugador].deslizamiento_caja_item_y == 0x0040) {
                    estado_siguiente_objeto(temporal_s0);
                }
            } else if (modo_pantalla_activo == 3) {
                if ((id_jugador == 0) || (id_jugador == 2)) {
                    arriba_paso_s16_hacia(&h_ud_jugador[id_jugador].deslizamiento_caja_item_x, 0x0080, 8);
                    if (h_ud_jugador[id_jugador].deslizamiento_caja_item_x == 0x0080) {
                        estado_siguiente_objeto(temporal_s0);
                    }
                } else {
                    abajo_paso_s16_hacia(&h_ud_jugador[id_jugador].deslizamiento_caja_item_x, -0x0080, 8);
                    if (h_ud_jugador[id_jugador].deslizamiento_caja_item_x == -0x0080) {
                        estado_siguiente_objeto(temporal_s0);
                    }
                }
            } else {
                arriba_paso_s16_hacia(&h_ud_jugador[id_jugador].deslizamiento_caja_item_x, 0x0080, 8);
                if (h_ud_jugador[id_jugador].deslizamiento_caja_item_x == 0x0080) {
                    estado_siguiente_objeto(temporal_s0);
                }
            }
            break;
        case 3:
            funcion_80072E54(temporal_s0, 1, 0x0000000F, 1, 2, 2);
            break;
        case 4:
            funcion_80072E54(temporal_s0, 1, 6, 1, 8, 1);
            break;
        case 5:
            funcion_80072E54(temporal_s0, 1, 4, 1, 0x00000010, 1);
            break;
        case 6:
            objeto->textura_indice_lista = funcion_8007AFB0(temporal_s0, id_jugador);
            objeto->desconocido_04C = 8;
            objeto->desconocido_0D6 = 2;
            estado_siguiente_objeto(temporal_s0);
            funcion_800C9018((u8) id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFE, 0x1C));
            funcion_800C8F80((u8) id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFE, 0x47));
            break;
        case 7:
            funcion_80072D3C(temporal_s0, (s32) objeto->desconocido_0A2, 0, 8, 0x0000000A);
            break;
        case 9:
            funcion_800722CC(temporal_s0, 4);
            funcion_80073600(temporal_s0);
            objeto->textura_indice_lista = 0;
            estado_siguiente_objeto(temporal_s0);
            break;
        case 10:
            ejecutar_objeto_temporizador_conjunto_y(temporal_s0, 0x00000014);
            break;
        case 11:
            if (modo_pantalla_activo == 0) {
                if (abajo_paso_s16_hacia(&h_ud_jugador[id_jugador].deslizamiento_caja_item_y, 0, 4) != 0) {
                    estado_siguiente_objeto(temporal_s0);
                }
            } else if (modo_pantalla_activo == 3) {
                if ((id_jugador == 0) || (id_jugador == 2)) {
                    abajo_paso_s16_hacia(&h_ud_jugador[id_jugador].deslizamiento_caja_item_x, 0, 8);
                    if (h_ud_jugador[id_jugador].deslizamiento_caja_item_x == 0) {
                        estado_siguiente_objeto(temporal_s0);
                    }
                } else {
                    arriba_paso_s16_hacia(&h_ud_jugador[id_jugador].deslizamiento_caja_item_x, 0, 8);
                    if (h_ud_jugador[id_jugador].deslizamiento_caja_item_x == 0) {
                        estado_siguiente_objeto(temporal_s0);
                    }
                }
            } else if (abajo_paso_s16_hacia(&h_ud_jugador[id_jugador].deslizamiento_caja_item_x, 0, 8) != 0) {
                estado_siguiente_objeto(temporal_s0);
            }
            break;
        case 12:
            funcion_80072428(temporal_s0);
            break;
        case 20:
            if (objeto->desconocido_0A2 == 0x000B) {
                funcion_80072D3C(temporal_s0, objeto->desconocido_0A2, 0, 8, 0x0000000A);
            } else {
                funcion_80072D3C(temporal_s0, objeto->desconocido_0A2, 0x0000000B, 8, 0x0000000A);
            }
            break;
        case 21:
            funcion_800726CC(temporal_s0, 8);
            objeto->desconocido_0D6 = 2;
            break;
        case 30:
            if (objeto->desconocido_0A2 == 0x000B) {
                funcion_80072D3C(temporal_s0, objeto->desconocido_0A2, 0, 8, 0x0000000A);
            } else {
                funcion_80072D3C(temporal_s0, objeto->desconocido_0A2, 0x0000000B, 8, 0x0000000A);
            }
            break;
        case 31:
            funcion_800726CC(temporal_s0, 9);
            break;
        case 40:
            if (objeto->desconocido_0A2 == 0x000D) {
                funcion_80072D3C(temporal_s0, objeto->desconocido_0A2, 0x0000000E, 8, 0x0000000A);
            } else {
                funcion_80072D3C(temporal_s0, objeto->desconocido_0A2, 0x0000000D, 8, 0x0000000A);
            }
            break;
        case 41:
            funcion_800726CC(temporal_s0, 8);
            break;
        case 50:
            funcion_80072D3C(temporal_s0, (s32) objeto->desconocido_0A2, 0, 8, 0x00000064);
            break;
        case 0:
        default:
            break;
    }
    if (funcion_80072320(temporal_s0, 2) != 0) {
        if (objeto->temporizador_animacion == 0) {
            consumir_item(id_jugador);
        } else {
            objeto->temporizador_animacion--;
        }
    }
    if (objeto->desconocido_04C >= 0) {
        if (objeto->desconocido_04C > 0) {
            objeto->desconocido_04C--;
        } else {
            switch (objeto->desconocido_0D6) {
                case 1:
                    if (sp40 != 0) {
                        funcion_80073600(temporal_s0);
                        funcion_800726CC(temporal_s0, 6);
                    }
                    break;
                case 2:
                    fijar_objeto_tipo(temporal_s0, (s32) objeto->desconocido_0A2);
                    objeto->desconocido_0D6 = 3;
                    break;
                case 3:
                    if (objeto->type == 0) {
                        if (funcion_80072354(temporal_s0, 1) != 0) {
                            if (objeto->desconocido_0A2 == 0x000B) {
                                if (funcion_8007B040(temporal_s0, id_jugador) != 0) {
                                    funcion_800726CC(temporal_s0, 0x00000014);
                                    objeto->desconocido_0D6 = 0;
                                } else {
                                    funcion_800726CC(temporal_s0, 9);
                                }
                            } else if ((objeto->desconocido_0A2 == 0x000D) || (objeto->desconocido_0A2 == 0x000E)) {
                                objeto->desconocido_0A2--;
                                fijar_objeto_tipo(temporal_s0, (s32) objeto->desconocido_0A2);
                                objeto->desconocido_0D6 = 3;
                                funcion_800726CC(temporal_s0, 0x00000028);
                            } else {
                                funcion_800726CC(temporal_s0, 9);
                            }
                        } else {
                            funcion_800722CC(temporal_s0, 1);
                            funcion_800726CC(temporal_s0, 0x0000001E);
                            objeto->desconocido_0D6 = 0;
                        }
                    }
                    break;
            }
        }
    }
    objeto->t_lut_activo = (u8*) ventana_item_ts_tlu[objeto->textura_indice_lista];
    objeto->textura_activo = ventana_item_texturas[objeto->textura_indice_lista];
    sp38->copia_item_actual = objeto->type;
}

void funcion_8007BB9C(s32 parametro0) {
    funcion_8007B34C(parametro0);
}

void funcion_8007BBBC(s32 indice_objeto) {
    f32 variable_f14;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->state) { /* irregular */
        case 1:
            funcion_800735BC(indice_objeto, d_circuito_banshee_boardwalk_dl_cheep_cheep, 2.0f);
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
            objeto->desconocido_0D5 = 0;
            break;
        case 2:
            if (es_modo_espejo != 0) {
                funcion_80087E08(indice_objeto, 18.0f, 0.7f, 25.0f, (s16) -0x00005800, 0x0000012C);
            } else {
                funcion_80087E08(indice_objeto, 18.0f, 0.7f, 25.0f, (s16) 0x00005800, 0x0000012C);
            }
            if (objeto->velocidad[2] < 0.0f) {
                variable_f14 = -objeto->velocidad[2];
            } else {
                variable_f14 = objeto->velocidad[2];
            }
            objeto->angulo_sentido[0] = funcion_80041658(objeto->velocidad[1], variable_f14);
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x00000046);
            break;
        case 3:
            funcion_80072428(indice_objeto);
            break;
        case 0:
            break;
    }
}

void funcion_8007BD04(s32 id_jugador) {
    s32 indice_objeto;

    indice_objeto = lista_objeto_indice_2[0];
    if (lista_objeto[indice_objeto].state == 0) {
        if (((s32) punto_camino_mas_cercano_por_id_jugador[id_jugador] >= 0xA0) &&
            ((s32) punto_camino_mas_cercano_por_id_jugador[id_jugador] < 0xAB)) {
            fijar_pos_origen_obj(indice_objeto, orientacion_x * -1650.0, -200.0f, -1650.0f);
            inicializar_objeto(indice_objeto, 1);
        }
    }
}

void actualizar_cheep_cheep_carrera(void) {
    SIN_USO s32 relleno;
    s32 indice_objeto;

    funcion_8007BD04(0);
    indice_objeto = lista_objeto_indice_2[0];
    funcion_8007BBBC(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void inicializar_variable_cheep_cheep(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0D5 = 1;
    objeto->status = 0;
    objeto->model = d_circuito_banshee_boardwalk_dl_cheep_cheep;
    objeto->escalado_tamanio = 0.2f;
    estado_siguiente_objeto(indice_objeto);
    fijar_pos_origen_obj(indice_objeto, dato_800E634C[0][0], dato_800E634C[0][1] + 55.0, dato_800E634C[0][2]);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 30.0f, 0.0f);
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0x3800U, 0U);
}

void funcion_8007BEC8(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->state) {
        case 1:
            inicializar_variable_cheep_cheep(indice_objeto);
            break;
        case 2:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000003C) != 0) {
                fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
                funcion_80086E70(indice_objeto);
            }
            break;
        case 3:
            if (objeto->desconocido_0AE == 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 4:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000000A) != 0) {
                funcion_8008701C(indice_objeto, 2);
            }
            break;
        case 5:
            if (objeto->desconocido_0AE == 0) {
                funcion_80072428(indice_objeto);
            }
            break;
        case 0:
        default:
            break;
    }
}

void funcion_8007BFB0(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->desconocido_0AE) {
        case 0:
            break;
        case 1:
            objeto->velocidad[1] = -0.2f;
            if ((f64) objeto->offset[1] <= 0.0) {
                objeto->offset[1] = 0.0f;
                objeto->velocidad[1] = 0.0f;
                funcion_80086F60(indice_objeto);
            }
            break;
        case 2:
            if (funcion_800871AC(indice_objeto, 0x00000014) != 0) {
                objeto->desconocido_084[7] = 0x0040;
            }
            break;
        case 3:
            objeto->escalado_tamanio = (f32) ((f64) objeto->escalado_tamanio - 0.0015);
            if ((s32) objeto->angulo_sentido[0] >= 0xA01) {
                objeto->desconocido_084[7] -= 4;
            }
            if (arriba_paso_u16_hacia(objeto->angulo_sentido, 0x0C00U, (u16) objeto->desconocido_084[7]) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 4:
            objeto->escalado_tamanio = (f32) ((f64) objeto->escalado_tamanio - 0.0015);
            objeto->desconocido_034 = 0.001f;
            funcion_80086FD4(indice_objeto);
            objeto->desconocido_084[7] = 0;
            break;
        case 5:
            if (objeto->desconocido_034 <= 0.004) {
                objeto->desconocido_034 += 0.0002;
            }
            objeto->escalado_tamanio += objeto->desconocido_034;
            arriba_paso_s16_hacia(&objeto->desconocido_084[7], 0x0100, 0x0010);
            objeto->angulo_sentido[0] -= objeto->desconocido_084[7];
            if (funcion_80087060(indice_objeto, 0x00000035) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 6:
            if (funcion_80087060(indice_objeto, 0x0000000F) != 0) {
                funcion_80086FD4(indice_objeto);
                dato_801658CE = 1;
            }
            break;
        case 7:
            objeto->escalado_tamanio = (f32) ((f64) objeto->escalado_tamanio - 0.05);
            if ((f64) objeto->escalado_tamanio <= 0.01) {
                fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000010);
                objeto->escalado_tamanio = 0.000001f;
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 8:
            funcion_80086F60(indice_objeto);
            break;
    }
    if (objeto->desconocido_0AE < 0xA) {
        funcion_80074344(indice_objeto, &objeto->escalado_tamanio, 0.2f, 0.21f, 0.001f, 0, -1);
    }
    agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void actualizar_cheep_cheep_final(void) {
    s32 indice_objeto;

    indice_objeto = lista_objeto_indice_2[0];
    if (dato_801658BC == 1) {
        dato_801658BC = 0;
        inicializar_objeto(indice_objeto, 0);
    }
    if (lista_objeto[indice_objeto].state != 0) {
        funcion_8007BEC8(indice_objeto);
        funcion_8007BFB0(indice_objeto);
    }
}

void actualizar_cheep_cheep(s32 parametro0) {
    switch (parametro0) {
        case 0:
            actualizar_cheep_cheep_carrera();
            break;
        case 1:
            actualizar_cheep_cheep_final();
            break;
    }
}

void actualizar_boos_envoltorio(void) {
    actualizar_boos();
}

void funcion_8007C360(s32 indice_objeto, Camara* camara) {
    u16 rot = camara->rot[1];
    u16 temporal_ = ((u16) (lista_objeto[indice_objeto].angulo_sentido[1] - rot + GRADOS(180)) * 0x24) / 0x10000;

    if (temporal_ < 0x13) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 0x80);
        lista_objeto[indice_objeto].textura_indice_lista = temporal_;
    } else {
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x80);
        lista_objeto[indice_objeto].textura_indice_lista = 0x24 - temporal_;
    }
}

void funcion_8007C420(s32 indice_objeto, Jugador* jugador, Camara* camara) {
    f32 x;
    f32 z;

    x = jugador->pos[0] - lista_objeto[indice_objeto].pos[0];
    z = jugador->pos[2] - lista_objeto[indice_objeto].pos[2];
    lista_objeto[indice_objeto].angulo_sentido[1] =
        funcion_800417B4(lista_objeto[indice_objeto].angulo_sentido[1], atan2s(x, z));
    funcion_8007C360(indice_objeto, camara);
}

SIN_USO void funcion_8007C49C(void) {
}

void funcion_8007C4A4(s32 indice_objeto) {
    u16 variable_t9;

    variable_t9 = lista_objeto[indice_objeto].angulo_sentido[1] * 0x24 / 0x10000;

    if (variable_t9 < 0x13) {
        fijar_objeto_bandera_situacion_false(indice_objeto, 0x80);
        lista_objeto[indice_objeto].textura_indice_lista = variable_t9;
    } else {
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x80);
        lista_objeto[indice_objeto].textura_indice_lista = 0x24 - variable_t9;
    }
}

void funcion_8007C550(s32 indice_objeto) {
    lista_objeto[indice_objeto].angulo_sentido[1] =
        funcion_800417B4(lista_objeto[indice_objeto].angulo_sentido[1],
                      atan2s(lista_objeto[indice_objeto].velocidad[0], lista_objeto[indice_objeto].velocidad[2]));
    funcion_8007C4A4(indice_objeto);
}

void funcion_8007C5B4(s32 indice_objeto) {
    Objeto* objeto;

    inicializar_objeto_textura(indice_objeto, d_circuito_banshee_boardwalk_boo_tlut, dato_80165880, 48, 40);
    objeto = &lista_objeto[indice_objeto];
    objeto->pos[0] = 0.0f;
    objeto->pos[1] = 0.0f;
    objeto->pos[2] = 0.0f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000020);
    estado_siguiente_objeto(indice_objeto);
    objeto->prim_alpha = 0;
    funcion_80073844(indice_objeto);
    objeto->escalado_tamanio = 0.15f;
    objeto->desconocido_034 = 1.0f;
    funcion_80073FD4(indice_objeto);
    funcion_80086EF0(indice_objeto);
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000800);
    objeto->orientacion[0] = 0;
    objeto->orientacion[2] = 0x8000;
}

void funcion_8007C684(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            funcion_8007C5B4(indice_objeto);
            break;
    }
    if (lista_objeto[indice_objeto].state >= 2) {
        switch (lista_objeto[indice_objeto].desconocido_0DC) {
            case 0:
                break;
            case 1:
                funcion_80073998(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0, 0x00000050, 2, 1, 0);
                break;
            case 2:
                funcion_80073CB0(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0x00000050, 0x00000078, 1, 0, -1);
                break;
            case 3:
                funcion_80073DC0(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0, 2);
                break;
            case 4:
                funcion_80072428(indice_objeto);
                funcion_80086F60(indice_objeto);
                funcion_80073884(indice_objeto);
                break;
        }
        funcion_80073514(indice_objeto);
    }
}

void funcion_8007C7B4(s32 algun_indice, s32 indice_jugador) {
    s32 temporal_a0;
    s32 indice_objeto;
    s16 temporal_s1_2;
    s16 temporal_s4;
    s16 temporal_s5;
    DatosSpline* algo_;

    for (temporal_a0 = 0; temporal_a0 < 5; temporal_a0++) {
        indice_objeto = lista_objeto_indice_3[algun_indice + temporal_a0];
        inicializar_objeto(indice_objeto, 1);
        lista_objeto[indice_objeto].desconocido_0D1 = indice_jugador;
        temporal_s1_2 = int_aleatorio(0x003CU) - 0x1E;
        temporal_s4 = int_aleatorio(0x0014U) - 0xA;
        temporal_s5 = int_aleatorio(0x0050U) - 0x28;
        int_aleatorio(0x1000U);
        algo_ = dato_800E5D9C[temporal_a0];
        lista_objeto[indice_objeto].spline = algo_;
        lista_objeto[indice_objeto].pos_origen[0] = (f32) temporal_s1_2;
        lista_objeto[indice_objeto].pos_origen[1] = (f32) temporal_s4;
        lista_objeto[indice_objeto].pos_origen[2] = (f32) temporal_s5;
    }
    funcion_800C9060(indice_jugador, 0x1900705AU);

    if (algun_indice == 0) {
        dato_8018CFF0 = 1;
    } else {
        dato_8018D048 = 1;
    }
}

void funcion_8007C91C(s32 algun_indice) {
    s32 temporal_a0;
    s32 indice_objeto;

    for (temporal_a0 = 0; temporal_a0 < 5; temporal_a0++) {
        indice_objeto = lista_objeto_indice_3[algun_indice + temporal_a0];
        lista_objeto[indice_objeto].desconocido_0DC += 1;
    }

    if (algun_indice == 0) {
        dato_8018CFF0 = 0;
    } else {
        dato_8018D048 = 0;
    }
}

s32 funcion_8007C9F8(void) {
    s32 devuelto;
    s32 primer, segundo;
    if (cantidad_jugador == 1) {
        devuelto = 0;
    } else {
        if (cantidad_jugador == 2) {
            if (seleccion_modo == 0) {
                primer = gp_actual_carrera_puesto_por_id_jugador[0];
                segundo = gp_actual_carrera_puesto_por_id_jugador[1];
                if (primer < segundo) {
                    devuelto = 0;
                } else {
                    devuelto = 1;
                }
            } else {
                devuelto = gp_actual_carrera_jugador_id_por_puesto[0];
            }
        } else {
            devuelto = gp_actual_carrera_jugador_id_por_puesto[0];
        }
    }
    return devuelto;
}

void funcion_8007CA70(void) {
    s32 id_jugador;
    u16* probar;

    if (dato_8018CFF0 == 0) {
        id_jugador = funcion_8007C9F8();
        dato_8018D018 = id_jugador;
        probar = &punto_camino_mas_cercano_por_id_jugador[id_jugador];
        if ((*probar >= 0xC9) && (*probar < 0xD2)) {
            funcion_8007C7B4(0, (s32) id_jugador);
        }
    }
    if (dato_8018CFF0 != 0) {
        id_jugador = dato_8018D018;
        probar = &punto_camino_mas_cercano_por_id_jugador[id_jugador];
        if ((*probar >= 0xB5) && (*probar < 0xBE)) {
            funcion_8007C91C(0);
        }
        if ((*probar >= 0x119) && (*probar < 0x122)) {
            funcion_8007C91C(0);
        }
    }
    if (dato_8018D048 == 0) {
        id_jugador = funcion_8007C9F8();
        dato_8018D110 = id_jugador;
        probar = &punto_camino_mas_cercano_por_id_jugador[id_jugador];
        if ((*probar >= 0x1FF) && (*probar < 0x208)) {
            funcion_8007C7B4(5, (s32) id_jugador);
        }
    }
    if (dato_8018D048 != 0) {
        id_jugador = dato_8018D110;
        probar = &punto_camino_mas_cercano_por_id_jugador[id_jugador];
        if ((*probar >= 0x1EB) && (*probar < 0x1F4)) {
            funcion_8007C91C(5);
        }
        if ((*probar >= 0x26D) && (*probar < 0x276)) {
            funcion_8007C91C(5);
        }
    }
}

void actualizar_boos(void) {
    u16 temporal_t4;
    s32 algun_indice;
    s32 indice_objeto;
    Jugador* jugador;
    Camara* camara;
    Objeto* objeto;

    funcion_8007CA70();
    for (algun_indice = 0; algun_indice < NUM_BOOS; algun_indice++) {
        indice_objeto = lista_objeto_indice_3[algun_indice];
        objeto = &lista_objeto[indice_objeto];
        if (objeto->state != 0) {
            funcion_8007C684(indice_objeto);
            funcion_8008B78C(indice_objeto);
            jugador = &jugador_uno[objeto->desconocido_0D1];
            camara = &camara1[objeto->desconocido_0D1];
            temporal_t4 = (0x8000 - camara->rot[1]);
            objeto->pos[0] = jugador->pos[0] + (coss(temporal_t4) * (objeto->pos_origen[0] + objeto->offset[0])) -
                             (senos(temporal_t4) * (objeto->pos_origen[2] + objeto->offset[2]));
            objeto->pos[1] = 6.5 + jugador->desconocido_074 + objeto->pos_origen[1] + objeto->offset[1];
            objeto->pos[2] = jugador->pos[2] + (senos(temporal_t4) * (objeto->pos_origen[0] + objeto->offset[0])) +
                             (coss(temporal_t4) * (objeto->pos_origen[2] + objeto->offset[2]));
            funcion_8007C550(indice_objeto);
            if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000080) != 0) {
                objeto->vertice = dato_800E44B0;
            } else {
                objeto->vertice = dato_800E4470;
            }
        }
    }
}

void funcion_8007CE0C(s32 indice_objeto) {
    Objeto* objeto;

    inicializar_objeto_textura(indice_objeto, d_circuito_banshee_boardwalk_boo_tlut, textura_fantasmas, 0x30U, (u16) 0x00000028);
    objeto = &lista_objeto[indice_objeto];
    objeto->textura_indice_lista = 0x1C;
    objeto->pos[0] = 0.0f;
    objeto->pos[1] = 0.0f;
    objeto->pos[2] = 0.0f;
    objeto->escalado_tamanio = 0.15f;
    estado_siguiente_objeto(indice_objeto);
    objeto->prim_alpha = 0;
    funcion_80073844(indice_objeto);
    funcion_80086EF0(indice_objeto);
    objeto->angulo_sentido[2] = 0x8000;
    objeto->angulo_sentido[1] =
        atan2s(dato_8018CF1C->pos[0] - objeto->pos_origen[0], dato_8018CF1C->pos[2] - objeto->pos_origen[2]);
}
