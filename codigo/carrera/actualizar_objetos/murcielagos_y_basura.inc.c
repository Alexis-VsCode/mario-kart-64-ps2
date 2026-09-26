// Murcielagos y basura

void funcion_8007CEDC(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->state) {
        case 0:
            break;
        case 1:
            funcion_8007CE0C(indice_objeto);
            break;
        case 2:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000001E);
            break;
        case 3:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x000003E8);
            break;
        case 4:
            funcion_80072428(indice_objeto);
            break;
        default:
            break;
    }
    if (objeto->state >= 2) {
        funcion_80072950(indice_objeto, (s32) objeto->desconocido_0DC, 0, 4);
        funcion_80073514(indice_objeto);
        switch (objeto->desconocido_0DC) {
            case 1:
                funcion_80073998(indice_objeto, &objeto->prim_alpha, 0x00000028, 0x00000050, 4, 0, 0);
                break;
            case 2:
                funcion_80073CB0(indice_objeto, &objeto->prim_alpha, 0x00000050, 0x000000B4, 2, 0, -1);
                if ((objeto->desconocido_0AE == 0) || (objeto->state == 3)) {
                    objeto->desconocido_0DC += 1;
                }
                break;
            case 3:
                funcion_80073DC0(indice_objeto, &objeto->prim_alpha, 0, 4);
                break;
            case 4:
                funcion_80073884(indice_objeto);
                break;
            case 0:
            default:
                break;
        }
    }
}

void funcion_8007D070(void) {
    SIN_USO s32 margen_pila;
    SIN_USO s32 margen_pila_2;
    u16 temporal_s3;
    s16 temporal_t5;
    s16 temporal_s2;
    u16 temporal_t2;
    s32 variable_v0;
    s32 indice_objeto;

    variable_v0 = 0;
    if ((dato_8016559C == 0) && (dato_8018D2A4 != 0) && (dato_8018CF68[0] < 0x1D) && (dato_800E5DB4[dato_8018CF68[0]] == 1)) {
        while (lista_objeto[particula_objeto_1[variable_v0 + 10]].state != 0) {
            variable_v0++;
            if (variable_v0 == 30) {
                break;
            }
        }
        indice_objeto = particula_objeto_1[variable_v0 + 10];
        if (variable_v0 != 30) {
            if (lista_objeto[indice_objeto].state == 0) {
                inicializar_objeto(indice_objeto, 1);
                temporal_s2 = int_aleatorio(0x012CU);
                temporal_s3 = int_aleatorio(0x1000U) - 0x800;
                temporal_t5 = int_aleatorio(0x000FU) - 5;
                lista_objeto[indice_objeto].angulo_sentido[1] = dato_8018CF1C->rotacion[1] + GRADOS(180);
                temporal_t2 = (dato_8018CF14->rot[1] + temporal_s3);
                lista_objeto[indice_objeto].pos_origen[0] = dato_8018CF1C->pos[0] + (senos(temporal_t2) * temporal_s2);
                lista_objeto[indice_objeto].pos_origen[1] = temporal_t5;
                lista_objeto[indice_objeto].pos_origen[2] = dato_8018CF1C->pos[2] + (coss(temporal_t2) * temporal_s2);
                lista_objeto[indice_objeto].spline = &dato_800E5D54;
            }
        }
    }
    for (variable_v0 = 0; variable_v0 < 30; variable_v0++) {
        indice_objeto = particula_objeto_1[variable_v0 + 10];
        if (lista_objeto[indice_objeto].state != 0) {
            funcion_8007CEDC(indice_objeto);
            funcion_8008B724(indice_objeto);
            lista_objeto[indice_objeto].pos[0] =
                lista_objeto[indice_objeto].pos_origen[0] + lista_objeto[indice_objeto].offset[0];
            lista_objeto[indice_objeto].pos[1] =
                dato_8018CF1C->desconocido_074 + lista_objeto[indice_objeto].pos_origen[1] + lista_objeto[indice_objeto].offset[1];
            lista_objeto[indice_objeto].pos[2] =
                lista_objeto[indice_objeto].pos_origen[2] + lista_objeto[indice_objeto].offset[2];
            funcion_8007C420(indice_objeto, dato_8018CF1C, dato_8018CF14);
            if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000080) != 0) {
                lista_objeto[indice_objeto].vertice = dato_800E44B0;
            } else {
                lista_objeto[indice_objeto].vertice = dato_800E4470;
            }
        }
    }
}

void funcion_8007D360(s32 indice_objeto, s32 parametro1) {
    if (parametro1 == 1) {
        lista_objeto[indice_objeto].pos_origen[0] = (f32) ((-1775.0 - int_aleatorio(0x001EU)) * (f64) orientacion_x);
        lista_objeto[indice_objeto].pos_origen[1] = (f32) (int_aleatorio(0x0019U) + 25.0);
        lista_objeto[indice_objeto].pos_origen[2] = (f32) (int_aleatorio(0x001EU) + 130.0);
        lista_objeto[indice_objeto].desconocido_01C[0] = (f32) ((f64) orientacion_x * -2500.0);
        lista_objeto[indice_objeto].desconocido_01C[1] = 0.0f;
        lista_objeto[indice_objeto].desconocido_01C[2] = (f32) (220.0 - int_aleatorio(0x0096U));
        lista_objeto[indice_objeto].angulo_sentido[0] = 0xDC00;
        lista_objeto[indice_objeto].desconocido_0C6 = 0x0800;
    }
    if (parametro1 == 2) {
        lista_objeto[indice_objeto].pos_origen[0] = (f32) (-0x55B - int_aleatorio(0x001EU)) * orientacion_x;
        lista_objeto[indice_objeto].pos_origen[1] = (f32) (int_aleatorio(0x0019U) + 0xF);
        lista_objeto[indice_objeto].pos_origen[2] = (f32) (int_aleatorio(0x001EU) - 0xE8);
        lista_objeto[indice_objeto].desconocido_01C[0] = (f32) ((f64) orientacion_x * -2100.0);
        lista_objeto[indice_objeto].desconocido_01C[1] = 0.0f;
        lista_objeto[indice_objeto].desconocido_01C[2] = (f32) (int_aleatorio(0x00C8U) + -290.0);
        lista_objeto[indice_objeto].angulo_sentido[0] = 0;
        lista_objeto[indice_objeto].desconocido_0C6 = 0;
    }
    lista_objeto[indice_objeto].angulo_sentido[1] =
        obtener_angulo_entre_xy(lista_objeto[indice_objeto].pos_origen[0], lista_objeto[indice_objeto].desconocido_01C[0],
                             lista_objeto[indice_objeto].pos_origen[2], lista_objeto[indice_objeto].desconocido_01C[2]);
    lista_objeto[indice_objeto].angulo_sentido[2] = 0;
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    lista_objeto[indice_objeto].desconocido_0B0 = 0;
    if (seleccion_cc < CC_150) {
        lista_objeto[indice_objeto].desconocido_034 = (int_aleatorio(4U) + 4.0);
    } else {
        lista_objeto[indice_objeto].desconocido_034 = (int_aleatorio(4U) + 5.0);
    }
}

void funcion_8007D6A8(s32 indice_objeto, s32 parametro1) {
    SIN_USO s32 relleno[2];
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0D5 = 0x0D;
    funcion_8007D360(indice_objeto, parametro1);
    objeto->escalado_tamanio = 0.1f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000200);
    objeto->tamanio_caja_envolvente = 3;
}

void funcion_8007D714(s32 parametro0) {
    s32 indice_objeto;

    if (parametro0 == 1) {
        indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_2, &siguiente_libre_objeto_particula_2, 0x28);
    } else {
        indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_3, &siguiente_libre_objeto_particula_3, 0x1E);
    }
    if (indice_objeto != ID_OBJETO_NULO) {
        inicializar_objeto(indice_objeto, 0);
        funcion_8007D6A8(indice_objeto, parametro0);
    }
}

void funcion_8007D794(s32 indice_objeto) {
    if (seleccion_cc == CC_50) {
        funcion_80089A04(indice_objeto, 0.5f, 0.2f);
    } else if (seleccion_cc == CC_100) {
        funcion_80089A04(indice_objeto, 0.4f, 0.15f);
    } else {
        funcion_80089A04(indice_objeto, 0.25f, 0.1f);
    }
}

s32 funcion_8007D804(s32 indice_objeto) {
    s32 indice_bucle;
    s32 algun_cantidad;

    algun_cantidad = 0;
    for (indice_bucle = 0; indice_bucle < seleccion_cantidad_jugador_1; indice_bucle++) {
        if (es_visible_objeto_en_camara(indice_objeto, &camara1[indice_bucle], 0x4000U) != 0) {
            algun_cantidad += 1;
        }
    }
    return algun_cantidad;
}

void funcion_8007D8AC(s32 parametro0) {
    estado_siguiente_objeto(parametro0);
    funcion_80086E70(parametro0);
}

void funcion_8007D8D4(s32 indice_objeto, s32 parametro1) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_8007D8AC(indice_objeto);
            break;
        case 2:
            if (funcion_8007D804(indice_objeto) == 0) {
                funcion_80072428(indice_objeto);
            }
            if (parametro1 == 1) {
                if (es_modo_espejo != 0) {
                    if (lista_objeto[indice_objeto].pos[0] >= 2540.0) {
                        funcion_80072428(indice_objeto);
                    }
                } else if (lista_objeto[indice_objeto].pos[0] <= -2540.0) {
                    funcion_80072428(indice_objeto);
                }
            } else if (es_modo_espejo != 0) {
                if (lista_objeto[indice_objeto].pos[0] >= 2150.0) {
                    funcion_80072428(indice_objeto);
                }
            } else {
                if (lista_objeto[indice_objeto].pos[0] <= -2150.0) {
                    funcion_80072428(indice_objeto);
                }
            }
            break;
        case 0:
            break;
    }
}

void funcion_8007DA4C(s32 indice_objeto) {
    funcion_8008781C(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_8007DA74(s32 indice_objeto) {
    SIN_USO s32 relleno;
    if ((lista_objeto[indice_objeto].desconocido_0AE != 0) && (lista_objeto[indice_objeto].desconocido_0AE == 1)) {
        if (funcion_80087060(indice_objeto, 0x0000001E) != 0) {
            lista_objeto[indice_objeto].desconocido_0C6 = 0U;
        }
    }
    lista_objeto[indice_objeto].angulo_sentido[0] =
        funcion_800417B4(lista_objeto[indice_objeto].angulo_sentido[0], lista_objeto[indice_objeto].desconocido_0C6);
    funcion_80087844(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_8007DAF8(s32 indice_objeto, s32 parametro1) {
    switch (parametro1) { /* irregular */
        case 1:
            funcion_8007DA74(indice_objeto);
            return;
        case 2:
            funcion_8007DA4C(indice_objeto);
            return;
    }
}

void actualizar_murcielago(void) {
    s32 variable_s2;
    s32 temporal_s0;
    Objeto* objeto;

    if (dato_8018CFC8 != 0) {
        dato_8018CFC8 -= 1;
    }
    if (dato_8018D000 != 0) {
        dato_8018D000 -= 1;
    }
    temporal_s0 = lista_objeto_indice_1[0];
    funcion_80072E54(temporal_s0, 0, 3, 1, 0, -1);
    funcion_80073514(temporal_s0);
    objeto = &lista_objeto[temporal_s0];
    funcion_80073CB0(temporal_s0, &objeto->prim_alpha, -0x00001000, 0x00001000, 0x00000400, 0, -1);
    objeto->orientacion[2] = objeto->prim_alpha + 0x8000;
    if ((dato_8018CFB0 != 0) || (dato_8018CFC8 != 0)) {
        dato_8018CFD8 = 0;
        for (variable_s2 = 0; variable_s2 < 40; variable_s2++) {
            temporal_s0 = particula_objeto_2[variable_s2];
            if (temporal_s0 == -1) {
                continue;
            }

            objeto = &lista_objeto[temporal_s0];
            if (objeto->state == 0) {
                continue;
            }

            funcion_8007D8D4(temporal_s0, 1);
            funcion_8007DAF8(temporal_s0, 1);
            funcion_8007D794(temporal_s0);
            if (objeto->state == 0) {
                eliminar_envoltorio_objeto(&particula_objeto_2[variable_s2]);
            }
            dato_8018CFD8 += 1;
        }
        if (dato_8018CFD8 != 0) {
            dato_8018CFC8 = 0x012C;
        }
    }
    if ((dato_8018CFE8 != 0) || (dato_8018D000 != 0)) {
        dato_8018D010 = 0;
        for (variable_s2 = 0; variable_s2 < 30; variable_s2++) {
            temporal_s0 = particula_objeto_3[variable_s2];
            if (temporal_s0 == -1) {
                continue;
            }

            objeto = &lista_objeto[temporal_s0];
            if (objeto->state == 0) {
                continue;
            }

            funcion_8007D8D4(temporal_s0, 2);
            funcion_8007DAF8(temporal_s0, 2);
            funcion_8007D794(temporal_s0);
            if (objeto->state == 0) {
                eliminar_envoltorio_objeto(&particula_objeto_3[variable_s2]);
            }
            dato_8018D010 += 1;
        }
        if (dato_8018D010 != 0) {
            dato_8018D000 = 0x012C;
        }
    }
}

void funcion_8007DDC0(s32 indice_objeto) {
    f32 sp2_c;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    if (objeto->desconocido_04C > 0) {
        objeto->desconocido_04C--;
        if (objeto->desconocido_04C == 0) {
            funcion_800722CC(indice_objeto, 1);
        }
    }
    if (objeto->desconocido_048 > 0) {
        objeto->desconocido_048--;
        if (objeto->desconocido_048 == 0) {
            funcion_800C9EF4(objeto->pos, SONIDO_CARGA_PARAMETRO(0x51, 0x02, 0x80, 0x06));
        }
    }
    if (objeto->desconocido_04C == 0) {
        if ((seleccion_cc == CC_50) || (seleccion_cc == CC_100) || (seleccion_cc == CC_150) ||
            (seleccion_cc == CC_EXTRA)) {
            sp2_c = 1150.0f;
        }
        funcion_8008A6DC(indice_objeto, sp2_c);
        if ((es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) && (funcion_80072354(indice_objeto, 1) != 0)) {
            funcion_800722A4(indice_objeto, 1);
            funcion_800C9D80(objeto->pos, objeto->velocidad, SONIDO_CARGA_PARAMETRO(0x51, 0x02, 0x80, 0x06));
            funcion_800726CC(indice_objeto, 3);
            if (objeto->type > 0) {
                objeto->type--;
                objeto->desconocido_04C = 0x00000168;
            } else {
                objeto->desconocido_04C = 0x00000168;
            }
            objeto->desconocido_048 = 0x0000012C;
        }
    }
    if (funcion_8008A8B0(0x000F, 0x0012) == 0) {
        objeto->type = 2;
    }
}

void inicializar_bin_basura_bb(s32 indice_objeto) {
    lista_objeto[indice_objeto].escalado_tamanio = 1.0f;
    lista_objeto[indice_objeto].model = d_circuito_banshee_boardwalk_bin_basura_dl;
    lista_objeto[indice_objeto].desconocido_04C = 0;
    lista_objeto[indice_objeto].desconocido_084[7] = 0;
    fijar_orientacion_obj(indice_objeto, 0U, 0U, 0U);
    if (es_modo_espejo != 0) {
        lista_objeto[indice_objeto].pos[0] = 1765.0f;
        lista_objeto[indice_objeto].pos[2] = 195.0f;
        lista_objeto[indice_objeto].orientacion[1] = 0x8000;
    } else {
        lista_objeto[indice_objeto].pos[0] = -1765.0f;
        lista_objeto[indice_objeto].pos[2] = 70.0f;
    }
    lista_objeto[indice_objeto].pos[1] = 45.0f;
    fijar_velocidad_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    lista_objeto[indice_objeto].type = 0;
    estado_siguiente_objeto(indice_objeto);
}

void funcion_8007E00C(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            inicializar_bin_basura_bb(indice_objeto);
            break;
        case 3:
            dato_8018CFB0 = 1;
            estado_siguiente_objeto(indice_objeto);
            break;
        case 4:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x000000D2);
            if (dato_80165594 == 0) {
                if (seleccion_cc < CC_150) {
                    funcion_8007D714(1);
                    funcion_8007D714(1);
                } else {
                    funcion_8007D714(1);
                    funcion_8007D714(1);
                    funcion_8007D714(1);
                    funcion_8007D714(1);
                }
            }
            funcion_80073CB0(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, -0x00002000, 0, 0x00000400, 0, -1);
            lista_objeto[indice_objeto].orientacion[2] = lista_objeto[indice_objeto].prim_alpha;
            if (lista_objeto[indice_objeto].desconocido_084[7] == 0) {
                funcion_800C98B8(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].velocidad,
                              SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x4E));
                lista_objeto[indice_objeto].desconocido_084[7] = 0x0014;
            } else {
                lista_objeto[indice_objeto].desconocido_084[7]--;
            }
            break;
        case 5:
            lista_objeto[indice_objeto].orientacion[2] = funcion_800417B4(lista_objeto[indice_objeto].orientacion[2], 0U);
            if (lista_objeto[indice_objeto].orientacion[2] == 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 6:
            lista_objeto[indice_objeto].orientacion[2] = 0;
            lista_objeto[indice_objeto].desconocido_084[7] = 0;
            estado_siguiente_objeto(indice_objeto);
            dato_8018CFB0 = 0;
            break;
        case 0:
        case 2:
        default:
            break;
    }
}

void actualizar_bin_basura(void) {
    s32 indice_objeto = lista_objeto_indice_1[1];
    funcion_8007E00C(indice_objeto);
    if (seleccion_modo != CONTRARRELOJ) {
        funcion_8007DDC0(indice_objeto);
    }
}

void funcion_8007E1F4(s32 indice_objeto) {
    f32 sp2_c;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    if (objeto->desconocido_04C > 0) {
        objeto->desconocido_04C--;
        if (objeto->desconocido_04C == 0) {
            funcion_800722CC(indice_objeto, 1);
        }
    }
    if (objeto->desconocido_048 > 0) {
        objeto->desconocido_048--;
        if (objeto->desconocido_048 == 0) {
            funcion_800C9EF4(objeto->pos, SONIDO_CARGA_PARAMETRO(0x51, 0x02, 0x80, 0x06));
        }
    }
    if (objeto->desconocido_04C == 0) {
        if ((seleccion_cc == CC_50) || (seleccion_cc == CC_100) || (seleccion_cc == CC_150) ||
            (seleccion_cc == CC_EXTRA)) {
            sp2_c = 700.0f;
        }
        funcion_8008A6DC(indice_objeto, sp2_c);
        if ((es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) && (funcion_80072354(indice_objeto, 1) != 0)) {
            funcion_800722A4(indice_objeto, 1);
            funcion_800C9D80(objeto->pos, objeto->velocidad, SONIDO_CARGA_PARAMETRO(0x51, 0x02, 0x80, 0x06));
            funcion_800726CC(indice_objeto, 3);
            if (objeto->type > 0) {
                objeto->type--;
                objeto->desconocido_04C = 0x00000168;
            } else {
                objeto->desconocido_04C = 0x00000168;
            }
            objeto->desconocido_048 = 0x0000012C;
        }
    }
    if (funcion_8008A8B0(0x000F, 0x0013) == 0) {
        objeto->type = 2;
    }
}

void funcion_8007E358(s32 indice_objeto) {
    lista_objeto[indice_objeto].pos[0] = -1371.0f * orientacion_x;
    lista_objeto[indice_objeto].pos[1] = 31.0f;
    lista_objeto[indice_objeto].pos[2] = -217.0f;
    fijar_velocidad_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    lista_objeto[indice_objeto].type = 0;
    lista_objeto[indice_objeto].desconocido_04C = 0;
    lista_objeto[indice_objeto].desconocido_084[7] = 0;
    estado_siguiente_objeto(indice_objeto);
}

void funcion_8007E3EC(s32 indice_objeto) {

    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_8007E358(indice_objeto);
            break;
        case 3:
            dato_8018CFE8 = 1;
            estado_siguiente_objeto(indice_objeto);
            break;
        case 4:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x000000D2);
            if (dato_80165598 == 0) {
                if (seleccion_cc < CC_150) {
                    funcion_8007D714(2);
                } else {
                    funcion_8007D714(2);
                    funcion_8007D714(2);
                }
            }
            break;
        case 5:
            dato_8018CFE8 = 0;
            estado_siguiente_objeto(indice_objeto);
            break;
        case 0:
        case 2:
        default:
            break;
    }
}

void funcion_8007E4C4(void) {
    s32 indice_objeto = lista_objeto_indice_1[2];
    funcion_8007E3EC(indice_objeto);
    if (seleccion_modo != CONTRARRELOJ) {
        funcion_8007E1F4(indice_objeto);
    }
}

s32 funcion_8007E50C(s32 indice_objeto, Jugador* jugador, Camara* camara) {
    s32 sp24;

    sp24 = 0;
    if ((funcion_80072354(indice_objeto, 4) != 0) &&
        (es_dentro_distancia_horizontal_de_jugador(indice_objeto, jugador, 300.0f) != 0) &&
        (funcion_8008A0B4(indice_objeto, jugador, camara, 0x4000U) != 0) &&
        (funcion_8008A060(indice_objeto, camara, 0x1555U) != 0)) {
        funcion_800722A4(indice_objeto, 4);
        sp24 = 1;
    }
    return sp24;
}

s32 funcion_8007E59C(s32 indice_objeto) {
    Camara* camara;
    Jugador* jugador;
    s32 temporal_v0;
    s32 algun_indice;

    temporal_v0 = 0;
    jugador = jugador_uno;
    camara = camara1;
    for (algun_indice = 0; algun_indice < seleccion_cantidad_jugador_1; algun_indice++) {
        temporal_v0 = funcion_8007E50C(indice_objeto, jugador++, camara++);
        if (temporal_v0 != 0) {
            break;
        }
    }
    return temporal_v0;
}

void funcion_8007E63C(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 0x32:
            if (arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], lista_objeto[indice_objeto].desconocido_01C[1] + 15.0,
                                    1.5f) != 0) {
                fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000200);
                funcion_800722A4(indice_objeto, 1);
                funcion_800722CC(indice_objeto, 2);
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 0x33:
            if (abajo_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 0.0f, 2.0f) != 0) {
                if (lista_objeto[indice_objeto].offset[1] >= 16.0f) {
                    lista_objeto[indice_objeto].textura_indice_lista = 0;
                } else if (lista_objeto[indice_objeto].offset[1] >= 8.0f) {
                    lista_objeto[indice_objeto].textura_indice_lista = 1;
                } else {
                    lista_objeto[indice_objeto].textura_indice_lista = 2;
                }
                funcion_800722CC(indice_objeto, 1);
                if (es_obj_bandera_situacion_activo(indice_objeto, 0x00010000) != 0) {
                    funcion_800722A4(indice_objeto, 0x00000010);
                    if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
                        funcion_800722A4(indice_objeto, 0x00000020);
                    }
                }
                if (funcion_80072320(indice_objeto, 2) != 0) {
                    funcion_800726CC(indice_objeto, 0x00000064);
                } else {
                    estado_siguiente_objeto(indice_objeto);
                }
            }
            break;
        case 0x34:
            funcion_80072AAC(indice_objeto, 3, 6);
            break;
        case 0x35:
            funcion_80072AAC(indice_objeto, 2, 0x00000032);
            break;
        case 0x36:
            if (lista_objeto[indice_objeto].offset[1] >= 20.0f) {
                lista_objeto[indice_objeto].textura_indice_lista = 0;
            } else if (lista_objeto[indice_objeto].offset[1] >= 18.0f) {
                lista_objeto[indice_objeto].textura_indice_lista = 1;
            }
            if (arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], lista_objeto[indice_objeto].desconocido_01C[1], 0.5f) !=
                0) {
                fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000200);
                funcion_8007266C(indice_objeto);
            }
            break;
        case 0x64:
            funcion_80072E54(indice_objeto, 3, 5, 1, 8, 0);
            break;
        case 0x65:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000001E);
            break;
        case 0x66:
            if (arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 20.0f, 1.5f) != 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 0x67:
            if (abajo_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 0.0f, 1.5f) != 0) {
                if (es_obj_bandera_situacion_activo(indice_objeto, 0x00020000) != 0) {
                    funcion_800722A4(indice_objeto, 0x00000010);
                    if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
                        funcion_800722A4(indice_objeto, 0x00000020);
                    }
                }
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 0x68:
            if (arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 12.0f, 1.5f) != 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 0x69:
            if (abajo_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 0.0f, 1.5f) != 0) {
                if (es_obj_bandera_situacion_activo(indice_objeto, 0x00020000) != 0) {
                    funcion_800722A4(indice_objeto, 0x00000010);
                    if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
                        funcion_800722A4(indice_objeto, 0x00000020);
                    }
                }
                funcion_800C98B8(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].velocidad,
                              SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x45));
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 0x6A:
            if (funcion_8007326C(indice_objeto, 5, 3, 1, 6, 3) != 0) {
                funcion_80080DE4(indice_objeto);
            }
            break;
        case 0x6B:
            if (lista_objeto[indice_objeto].offset[1] >= 22.0f) {
                lista_objeto[indice_objeto].textura_indice_lista = 0;
            } else if (lista_objeto[indice_objeto].offset[1] >= 20.0f) {
                lista_objeto[indice_objeto].textura_indice_lista = 1;
            } else if (lista_objeto[indice_objeto].offset[1] >= 18.0f) {
                lista_objeto[indice_objeto].textura_indice_lista = 2;
            } else if (lista_objeto[indice_objeto].offset[1] >= 16.0f) {
                lista_objeto[indice_objeto].textura_indice_lista = 3;
            } else if (lista_objeto[indice_objeto].offset[1] >= 14.0f) {
                lista_objeto[indice_objeto].textura_indice_lista = 4;
            } else {
                funcion_800730BC(indice_objeto, 3, 5, 1, 6, -1);
            }
            if (arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], lista_objeto[indice_objeto].desconocido_01C[1], 0.5f) !=
                0) {
                fijar_estado_temporizador_objeto(indice_objeto, 0);
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 0x6C:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x00000064) != 0) {
                funcion_800722CC(indice_objeto, 2);
                fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000200);
                funcion_8007266C(indice_objeto);
            }
            break;
        case 0xC8:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000012C) != 0) {
                funcion_80072320(indice_objeto, 0x00000080);
                funcion_80072428(indice_objeto);
                funcion_800726CC(indice_objeto, 1);
            }
            break;
        case 0x12C:
            if (funcion_80073E18(indice_objeto, &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00008000) != 0) {
                funcion_800722CC(indice_objeto, 4);
                funcion_8007266C(indice_objeto);
            }
            break;
    }
}

void funcion_8007EC30(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->altura_superficie = 0.0f;
    objeto->pos_origen[1] = 0.0f;
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    if (es_modo_espejo != 0) {
        fijar_angulo_sentido_obj(indice_objeto, 0U, 0x4000U, 0U);
        fijar_orientacion_obj(indice_objeto, 0U, 0x4000U, 0U);
    } else {
        fijar_angulo_sentido_obj(indice_objeto, 0U, 0xC000U, 0U);
        fijar_orientacion_obj(indice_objeto, 0U, 0xC000U, 0U);
    }
    inicializar_objeto_textura(indice_objeto, d_circuito_bowsers_castle_thwomp_tlut, (u8*) d_circuito_bowsers_castle_thwomp_caras,
                        0x10U, (u16) 0x00000040);
    objeto->model = d_circuito_bowsers_castle_dl_thwomp;
    objeto->tamanio_caja_envolvente = 0x000C;
    objeto->escalado_tamanio = 1.0f;
    objeto->desconocido_01C[1] = 30.0f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x05000220);
    objeto->type = 0;
    objeto->desconocido_0DF = 6;
    funcion_800724DC(indice_objeto);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_8007ED6C(s32 indice_objeto) {
    SIN_USO s32 margen_pila[4];
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            funcion_8007EC30(indice_objeto);
            break;
        case 2:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000003C);
            break;
        case 3:
            funcion_80072568(indice_objeto, 0x00000032);
            break;
        case 4:
            if (funcion_8007E59C(indice_objeto) != 0) {
                funcion_800725E8(indice_objeto, 0x0000012C, 2);
            } else {
                funcion_800726CC(indice_objeto, 2);
            }
            break;
    }
    funcion_8007E63C(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    lista_objeto[indice_objeto].angulo_sentido[1] = lista_objeto[indice_objeto].orientacion[1];
    funcion_80073514(indice_objeto);
}

void funcion_8007EE5C(s32 indice_objeto) {
    Objeto* objeto;

    inicializar_objeto_textura(indice_objeto, d_circuito_bowsers_castle_thwomp_tlut, (u8*) d_circuito_bowsers_castle_thwomp_caras,
                        0x10U, (u16) 0x00000040);
    objeto = &lista_objeto[indice_objeto];
    objeto->escalado_tamanio = 1.0f;
    objeto->model = d_circuito_bowsers_castle_dl_thwomp;
    objeto->tamanio_caja_envolvente = 0x000C;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000220);
    objeto->type = 0;
    objeto->desconocido_0DF = 6;
    funcion_80086E70(indice_objeto);
    objeto->altura_superficie = 0.0f;
    objeto->pos_origen[1] = 0.0f;
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 20.0f, 0.0f);
    objeto->desconocido_01C[1] = 20.0f;
    if (es_modo_espejo != 0) {
        fijar_angulo_sentido_obj(indice_objeto, 0U, 0x4000U, 0U);
        fijar_orientacion_obj(indice_objeto, 0U, 0x4000U, 0U);
    } else {
        fijar_angulo_sentido_obj(indice_objeto, 0U, 0xC000U, 0U);
        fijar_orientacion_obj(indice_objeto, 0U, 0xC000U, 0U);
    }
    objeto->desconocido_0AE = 1;
    if (objeto->prim_alpha == 0) {
        objeto->desconocido_0DD = 1;
    } else {
        objeto->desconocido_0DD = 2;
    }
    estado_siguiente_objeto(indice_objeto);
}

void funcion_8007EFBC(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 1:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0800U, 0x00008000) != 0) {
                lista_objeto[indice_objeto].desconocido_01C[0] = (f32) ((f64) orientacion_x * 200.0);
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            if (paso_f32_hacia(lista_objeto[indice_objeto].offset, lista_objeto[indice_objeto].desconocido_01C[0], 4.0f) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 3:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00008000) != 0) {
                funcion_800726CC(indice_objeto, 3);
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 5:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x0000C000) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 6:
            if (abajo_paso_f32_hacia(&lista_objeto[indice_objeto].offset[2], -100.0f, 2.0f) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 7:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00004000) != 0) {
                funcion_80086FD4(indice_objeto);
                funcion_800726CC(indice_objeto, 3);
            }
            break;
        case 9:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00010000) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 10:
            if (paso_f32_hacia(lista_objeto[indice_objeto].offset, 0.0f, 4.0f) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 11:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00010000) != 0) {
                funcion_80086FD4(indice_objeto);
                funcion_800726CC(indice_objeto, 3);
            }
            break;
        case 13:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x00014000) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 14:
            if (arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[2], 0.0f, 2.0f) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 15:
            if (funcion_80073E18(indice_objeto, (u16*) &lista_objeto[indice_objeto].orientacion[1], 0x0400U, 0x0000C000) != 0) {
                funcion_80086FD4(indice_objeto);
                funcion_800726CC(indice_objeto, 3);
            }
            break;
        case 17:
            funcion_8008701C(indice_objeto, 1);
            break;
        case 0:
        default:
            break;
    }
}
