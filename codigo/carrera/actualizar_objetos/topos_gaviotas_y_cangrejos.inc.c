// Topos gaviotas y cangrejos

void funcion_80081848(s32 indice_objeto) {
    inicializar_objeto_textura(indice_objeto, d_circuito_moo_moo_farm_tlut_topo, (u8*) d_circuito_moo_moo_farm_frames_topo, 0x20U,
                        (u16) 0x00000040);
    lista_objeto[indice_objeto].escalado_tamanio = 0.15f;
    lista_objeto[indice_objeto].textura_indice_lista = 0;
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0U, 0U);
    fijar_orientacion_obj(indice_objeto, 0U, 0U, 0x8000U);
    lista_objeto[indice_objeto].tamanio_caja_envolvente = 6;
    lista_objeto[indice_objeto].velocidad[1] = 4.0f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000000);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80081924(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 1:
            if (arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 9.0f, 0.7f) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            funcion_800871AC(indice_objeto, 0x0000000A);
            break;
        case 3:
            if (abajo_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 3.0f, 1.0f) != 0) {
                funcion_80086F60(indice_objeto);
            }
            break;
        case 4:
            funcion_80087D24(indice_objeto, 3.6f, 0.25f, 0.0f);
            break;
        case 5:
            funcion_80086F60(indice_objeto);
            break;
        case 10:
            lista_objeto[indice_objeto].orientacion[2] += 0x1000;
            lista_objeto[indice_objeto].velocidad[1] -= 0.184;
            funcion_8008751C(indice_objeto);
            agregar_desplazamiento_xyz_velocidad_objeto(indice_objeto);
            if (lista_objeto[indice_objeto].pos[1] <= -10.0) {
                funcion_80086F60(indice_objeto);
            }
            break;
        case 0:
        default:
            break;
    }
}

void funcion_80081A88(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0DD) { /* irregular */
        case 0:
            break;
        case 1:
            funcion_8008B724(indice_objeto);
            break;
        case 2:
            funcion_80081924(indice_objeto);
            break;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_80081AFC(s32 indice_objeto, s32 parametro1) {
    s8* sp2_c;
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->state) { /* irregular */
        case 0x1:
            funcion_80081848(indice_objeto);
            break;
        case 0x2:
            if (objeto->desconocido_04C == 0) {
                funcion_80086EAC(indice_objeto, 2, 1);
                estado_siguiente_objeto(indice_objeto);
                fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000200);
            } else {
                objeto->desconocido_04C--;
            }
            break;
        case 0x3:
            if (objeto->desconocido_0AE == 0) {
                funcion_80086EAC(indice_objeto, 2, 4);
                funcion_8008153C(indice_objeto);
                estado_siguiente_objeto(indice_objeto);
                funcion_800C98B8(objeto->pos, objeto->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x07));
            }
            break;
        case 0x4:
            if (funcion_80072E54(indice_objeto, 1, 6, 1, 2, 0) != 0) {
                funcion_800726CC(indice_objeto, 0x00000064);
            }
            break;
        case 0xA:
            funcion_80072E54(indice_objeto, 1, 6, 1, 0, -1);
            if (objeto->desconocido_0AE == 0) {
                funcion_800726CC(indice_objeto, 0x00000064);
            }
            break;
        case 0x64:
            if (objeto->desconocido_0AE == 0) {
                fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000200);
                funcion_80072428(indice_objeto);
                switch (parametro1) {
                    case 1:
                        sp2_c = dato_8018D198;
                        break;
                    case 2:
                        sp2_c = dato_8018D1A8;
                        break;
                    case 3:
                        sp2_c = dato_8018D1B8;
                        break;
                }
                sp2_c[objeto->type] = 0;
            }
            break;
        case 0:
        default:
            break;
    }
    if (objeto->state >= 2) {
        funcion_80073514(indice_objeto);
    }
}

void funcion_80081D34(s32 indice_objeto) {
    Jugador* jugador;
    Camara* variable_s4;
    s32 indice_jugador;
    s32 variable_s5;
    Objeto* objeto;

    variable_s5 = 0;
    jugador = jugador_uno;
    variable_s4 = camara1;
    for (indice_jugador = 0; indice_jugador < dato_8018D158; indice_jugador++, jugador++, variable_s4++) {
        if ((es_obj_bandera_situacion_activo(indice_objeto, 0x00000200) != 0) && !(jugador->efectos & BOO_EFECTO) &&
            (tiene_chocado_con_jugador(indice_objeto, jugador) != 0)) {
            if ((jugador->type & EXISTE_JUGADOR) && !(jugador->type & INVISIBLE_JUGADOR_O_BOMBA)) {
                variable_s5 = 1;
                objeto = &lista_objeto[indice_objeto];
                if (es_obj_bandera_situacion_activo(indice_objeto, 0x04000000) != 0) {
                    funcion_80072180();
                }
                if (jugador->efectos & EFECTO_ESTRELLA) {
                    funcion_800C9060(indice_jugador, 0x1900A046U);
                } else {
                    jugador->disparadores |= DISPARADOR_VUELCO_ALTO;
                }
                objeto->angulo_sentido[1] = variable_s4->rot[1];
                objeto->velocidad[1] = (jugador->speed / 2) + 3.0;
                objeto->desconocido_034 = jugador->speed + 1.0;
                if (objeto->velocidad[1] >= 5.0) {
                    objeto->velocidad[1] = 5.0f;
                }
                if (objeto->desconocido_034 >= 4.0) {
                    objeto->velocidad[1] = 4.0f;
                }
            }
        }
    }
    if (variable_s5 != 0) {
        objeto = &lista_objeto[indice_objeto];
        fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000200);
        funcion_80086F60(indice_objeto);
        fijar_pos_origen_obj(indice_objeto, objeto->pos[0], objeto->pos[1], objeto->pos[2]);
        fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
        funcion_80086EAC(indice_objeto, 2, 0x000A);
        funcion_800726CC(indice_objeto, 0x0000000A);
    }
}

void funcion_80081FF4(s32 indice_objeto, s32 parametro1) {
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    s32 cantidad_topo;
    s16 variable_v1;
    s16 desplazamiento;
    s32 variable_a0;
    s8* variable_a2;

    inicializar_objeto(indice_objeto, 0);
    lista_objeto[indice_objeto].desconocido_04C = int_aleatorio(0x001EU) + 5;
    switch (parametro1) { /* irregular */
        case 1:
            variable_a2 = dato_8018D198;
            cantidad_topo = TOPOS_GROUP1_NUM;
            desplazamiento = 0;
            break;
        case 2:
            variable_a2 = dato_8018D1A8;
            cantidad_topo = TOPOS_GROUP2_NUM;
            desplazamiento = 24;
            break;
        case 3:
            variable_a2 = dato_8018D1B8;
            cantidad_topo = TOPOS_GROUP3_NUM;
            desplazamiento = 57;
            break;
    }
    variable_v1 = int_aleatorio(cantidad_topo);
    for (variable_a0 = 0; variable_a0 < cantidad_topo; variable_a0++) {
        if (variable_a2[variable_v1] != 0) {
            variable_v1++;
            if (variable_v1 == cantidad_topo) {
                variable_v1 = 0;
            }
        } else {
            variable_a2[variable_v1] = 1;
            lista_objeto[indice_objeto].type = variable_v1;
            break;
        }
    }
    lista_objeto[indice_objeto].pos_origen[0] = apariciones_topo.como_lista_plano[desplazamiento + (variable_v1 * 3) + 0] * orientacion_x;
    lista_objeto[indice_objeto].pos_origen[1] = apariciones_topo.como_lista_plano[desplazamiento + (variable_v1 * 3) + 1] - 9.0;
    lista_objeto[indice_objeto].pos_origen[2] = apariciones_topo.como_lista_plano[desplazamiento + (variable_v1 * 3) + 2];
}

void funcion_800821AC(s32 indice_objeto, s32 parametro1) {
    if (lista_objeto[indice_objeto].state != 0) {
        funcion_80081AFC(indice_objeto, parametro1);
        funcion_80081A88(indice_objeto);
        funcion_80081D34(indice_objeto);
    }
}

void actualizar_topos(void) {
    s32 variable_s1;
    s32 indice_objeto;
    SIN_USO s32 margen_pila;

    for (variable_s1 = 0; variable_s1 < dato_8018D1C8; variable_s1++) {
        indice_objeto = lista_objeto_indice_1[variable_s1];
        if (lista_objeto[indice_objeto].state == 0) {
            if (funcion_8008A8B0(8, 9) != 0) {
                funcion_80081FF4(indice_objeto, 1);
            }
        } else {
            funcion_800821AC(indice_objeto, 1);
        }
    }

    for (variable_s1 = 0; variable_s1 < dato_8018D1D0; variable_s1++) {
        indice_objeto = lista_objeto_indice_2[variable_s1];
        if (lista_objeto[indice_objeto].state == 0) {
            if (funcion_8008A8B0(0x0010, 0x0013) != 0) {
                funcion_80081FF4(indice_objeto, 2);
            }
        } else {
            funcion_800821AC(indice_objeto, 2);
        }
    }

    for (variable_s1 = 0; variable_s1 < dato_8018D1D8; variable_s1++) {
        indice_objeto = lista_objeto_indice_3[variable_s1];
        if (lista_objeto[indice_objeto].state == 0) {
            if (funcion_8008A8B0(0x0011, 0x0014) != 0) {
                funcion_80081FF4(indice_objeto, 3);
            }
        } else {
            funcion_800821AC(indice_objeto, 3);
        }
    }

    for (variable_s1 = 0; variable_s1 < objeto_particula_2_tamanio; variable_s1++) {
        indice_objeto = particula_objeto_2[variable_s1];
        if (lista_objeto[indice_objeto].state != 0) {
            funcion_80081790(indice_objeto);
        }
    }
}

void funcion_8008241C(s32 indice_objeto, s32 parametro1) {
    SIN_USO s16 margen_pila_0;
    s16 temporal_f4;
    s16 sp22;
    s16 sp20;

    lista_objeto[indice_objeto].desconocido_0D8 = 1;
    lista_objeto[indice_objeto].model = (Gfx*) d_circuito_koopa_troopa_beach_desconocido4;
    lista_objeto[indice_objeto].vertice = (Vtx*) d_circuito_koopa_troopa_beach_datos5_desconocido;
    lista_objeto[indice_objeto].escalado_tamanio = 0.2f;
    lista_objeto[indice_objeto].desconocido_0DD = 1;
    sp22 = int_aleatorio(0x00C8) + -100.0;
    sp20 = int_aleatorio(0x0014);
    temporal_f4 = int_aleatorio(0x00C8) + -100.0;
    if (estado_juego == 9) {
        fijar_pos_origen_obj(indice_objeto, sp22 + -360.0, sp20 + 60.0, temporal_f4 + -1300.0);
    } else if (lista_objeto[indice_objeto].desconocido_0D5 != 0) {
        fijar_pos_origen_obj(indice_objeto, (sp22 + 328.0) * orientacion_x, sp20 + 20.0, temporal_f4 + 2541.0);
    } else {
        fijar_pos_origen_obj(indice_objeto, (sp22 + -985.0) * orientacion_x, sp20 + 15.0, temporal_f4 + 1200.0);
    }
    fijar_angulo_sentido_obj(indice_objeto, 0U, 0U, 0U);
    lista_objeto[indice_objeto].desconocido_034 = 1.0f;
    funcion_80086EF0(indice_objeto);
    lista_objeto[indice_objeto].spline = dato_800E633C[parametro1 % 4];
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000800);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80082714(s32 indice_objeto, s32 parametro1) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_8008241C(indice_objeto, parametro1);
            break;
        case 0:
        default:
            break;
    }
}

void funcion_8008275C(s32 indice_objeto) {
    SIN_USO s32 margen_pila;
    switch (lista_objeto[indice_objeto].desconocido_0DD) { /* irregular */
        case 1:
            funcion_8008B78C(indice_objeto);
            calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
            break;
        case 2:
            funcion_8008B78C(indice_objeto);
            copiar_vec3f(lista_objeto[indice_objeto].desconocido_01C, lista_objeto[indice_objeto].pos);
            funcion_8000D940(lista_objeto[indice_objeto].pos_origen, (s16*) &lista_objeto[indice_objeto].desconocido_0C6,
                          lista_objeto[indice_objeto].desconocido_034, 0.0f, 0);
            lista_objeto[indice_objeto].offset[0] *= 2.0;
            lista_objeto[indice_objeto].offset[1] *= 2.5;
            lista_objeto[indice_objeto].offset[2] *= 2.0;
            calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
            lista_objeto[indice_objeto].angulo_sentido[1] =
                obtener_angulo_xz_entre_puntos(lista_objeto[indice_objeto].desconocido_01C, lista_objeto[indice_objeto].pos);
            break;
    }
    funcion_800873F4(indice_objeto);
}

void actualizar_gaviotas(void) {
    Objeto* objeto;
    SIN_USO s32* variable_s4;
    s32 temporal_s0;
    s32 variable_s3;

    for (variable_s3 = 0; variable_s3 < GAVIOTAS_NUM; variable_s3++) {
        temporal_s0 = lista_objeto_indice_2[variable_s3];

        objeto = &lista_objeto[temporal_s0];
        if (objeto->state == 0) {
            continue;
        }

        funcion_80082714(temporal_s0, variable_s3);
        funcion_8008275C(temporal_s0);
        if (funcion_80072320(temporal_s0, 2) != 0) {
            funcion_800722CC(temporal_s0, 2);
            if (dato_80165A90 != 0) {
                dato_80165A90 = 0;
                dato_80183E40[0] = 0.0f;
                dato_80183E40[1] = 0.0f;
                dato_80183E40[2] = 0.0f;
                if (estado_juego != SECUENCIA_CREDITOS) {
                    funcion_800C98B8(objeto->pos, dato_80183E40, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x43));
                } else {
                    temporal_s0 = lista_objeto_indice_2[1];
                    if (temporizador_disparo_cinematica < 0x97) {
                        objeto = &lista_objeto[temporal_s0];
                        funcion_800C98B8(objeto->pos, dato_80183E40, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x43));
                    }
                }
            }
        }
    }
    if (dato_80165900 != 0) {
        dato_80165900 -= 1;
    } else {
        if (estado_juego != 9) {
            dato_80165900 = 0x003C;
        } else {
            dato_80165900 = 0x000F;
        }
        if ((dato_80165908 != 0) && (dato_80165A90 == 0)) {
            dato_80165A90 = 1;
        }
    }
    dato_80165908 = 0;
}

void inicializar_cangrejo_ktb(s32 indice_objeto) {
    Objeto* objeto;

    inicializar_objeto_textura(indice_objeto, d_circuito_koopa_troopa_beach_tlut_cangrejo,
                        (u8*) d_circuito_koopa_troopa_beach_frames_cangrejo, 0x40U, (u16) 0x00000040);
    objeto = &lista_objeto[indice_objeto];
    objeto->escalado_tamanio = 0.15f;
    objeto->textura_indice_lista = 0;
    estado_siguiente_objeto(indice_objeto);
    objeto->tamanio_caja_envolvente = 1;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000420);
    funcion_80086EAC(indice_objeto, 0, 1);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    fijar_orientacion_obj(indice_objeto, 0U, 0U, 0x8000U);
    objeto->desconocido_034 = 1.5f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000200);
}

void funcion_80082B34(s32 indice_objeto, SIN_USO s32 unused) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 0:
            break;
        case 1:
            inicializar_cangrejo_ktb(indice_objeto);
            break;
        case 2:
            funcion_80072E54(indice_objeto, 0, 3, 1, 2, -1);
            break;
        case 3:
            funcion_80072E54(indice_objeto, 4, 6, 1, 2, -1);
            break;
    }
    if (lista_objeto[indice_objeto].state >= 2) {
        funcion_80073514(indice_objeto);
    }
}

void funcion_80082C30(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 1:
            if (funcion_80087A0C(indice_objeto, lista_objeto[indice_objeto].pos_origen[0], lista_objeto[indice_objeto].desconocido_01C[0],
                              lista_objeto[indice_objeto].pos_origen[2], lista_objeto[indice_objeto].desconocido_01C[2]) != 0) {
                funcion_800726CC(indice_objeto, 3);
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            if (funcion_80087104(indice_objeto, 0x003CU) != 0) {
                lista_objeto[indice_objeto].desconocido_034 = 0.8f;
                funcion_800726CC(indice_objeto, 2);
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 3:
            if (funcion_80087954(indice_objeto, 0x0000003C) != 0) {
                funcion_80086FD4(indice_objeto);
                funcion_800726CC(indice_objeto, 3);
            }
            break;
        case 4:
            if (funcion_80087104(indice_objeto, 0x003CU) != 0) {
                funcion_800726CC(indice_objeto, 2);
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 5:
            if (funcion_8008789C(indice_objeto, 0x0000003C) != 0) {
                funcion_800726CC(indice_objeto, 3);
                funcion_8008701C(indice_objeto, 2);
            }
            break;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
        funcion_80088538(indice_objeto);
        lista_objeto[indice_objeto].pos[1] = (f32) (lista_objeto[indice_objeto].altura_superficie + 2.5);
    }
}

void funcion_80082E18(s32 indice_objeto) {
    if (lista_objeto[indice_objeto].state >= 2) {
        funcion_80089F24(indice_objeto);
    }
}

void actualizar_cangrejos(void) {
    s32 indice_objeto;
    s32 variable_s1;

    for (variable_s1 = 0; variable_s1 < CANGREJOS_NUM; variable_s1++) {
        indice_objeto = lista_objeto_indice_1[variable_s1];
        if (lista_objeto[indice_objeto].state != 0) {
            funcion_80082B34(indice_objeto, variable_s1);
            funcion_8008A6DC(indice_objeto, 500.0f);
            funcion_80082C30(indice_objeto);
            funcion_80082E18(indice_objeto);
        }
    }
}

void funcion_80082F1C(s32 indice_objeto, s32 parametro1) {
    lista_objeto[indice_objeto].model = (Gfx*)d_circuito_yoshi_valley_desconocido5;
    lista_objeto[indice_objeto].vertice = (Vtx*)d_circuito_yoshi_valley_desconocido4;
    lista_objeto[indice_objeto].escalado_tamanio = 0.027f;
    estado_siguiente_objeto(indice_objeto);
    fijar_pos_origen_obj(indice_objeto, dato_800E5DF4[parametro1 * 4 + 0] * orientacion_x, dato_800E5DF4[parametro1 * 4 + 1], dato_800E5DF4[parametro1 * 4 + 2]);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    fijar_angulo_sentido_obj(indice_objeto, 0U, dato_800E5DF4[parametro1 * 4 + 3], 0U);
}

void funcion_80083018(s32 indice_objeto, s32 parametro1) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_80082F1C(indice_objeto, parametro1);
            break;
        case 0:
        default:
            break;
    }
}

void funcion_80083060(s32 indice_objeto) {
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_80083080(void) {
    s32 indice_objeto;
    s32 variable_s1;

    for (variable_s1 = 0; variable_s1 < NUM_YV_BANDERA_POSTES; variable_s1++) {
        indice_objeto = lista_objeto_indice_1[variable_s1];
        if (lista_objeto[indice_objeto].state != 0) {
            funcion_80083018(indice_objeto, variable_s1);
            funcion_80083060(indice_objeto);
        }
    }
}

void funcion_8008311C(s32 indice_objeto, s32 parametro1) {
    Objeto* objeto;

    inicializar_objeto_textura(indice_objeto, d_circuito_yoshi_valley_tlut_erizo, d_circuito_yoshi_valley_erizo, 0x40U,
                        (u16) 0x00000040);
    objeto = &lista_objeto[indice_objeto];
    objeto->t_lut_activo = d_circuito_yoshi_valley_tlut_erizo;
    objeto->textura_activo = d_circuito_yoshi_valley_erizo;
    objeto->vertice = erizo_vtx_comun;
    objeto->escalado_tamanio = 0.2f;
    objeto->textura_indice_lista = 0;
    estado_siguiente_objeto(indice_objeto);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    fijar_orientacion_obj(indice_objeto, 0U, 0U, 0x8000U);
    objeto->desconocido_034 = ((parametro1 % 6) * 0.1) + 0.5;
    funcion_80086E70(indice_objeto);
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000600);
    objeto->tamanio_caja_envolvente = 2;
}

void funcion_80083248(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 0:
            break;
        case 1:
            if (funcion_80087A0C(indice_objeto, lista_objeto[indice_objeto].pos_origen[0], lista_objeto[indice_objeto].desconocido_09C,
                              lista_objeto[indice_objeto].pos_origen[2], lista_objeto[indice_objeto].desconocido_09E) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            funcion_800871AC(indice_objeto, 0x0000003C);
            break;
        case 3:
            if (funcion_80087A0C(indice_objeto, lista_objeto[indice_objeto].desconocido_09C, lista_objeto[indice_objeto].pos_origen[0],
                              lista_objeto[indice_objeto].desconocido_09E, lista_objeto[indice_objeto].pos_origen[2]) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 4:
            if (funcion_80087060(indice_objeto, 0x0000003C) != 0) {
                funcion_8008701C(indice_objeto, 1);
            }
            break;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00200000) != 0) {
        if (es_obj_bandera_situacion_activo(indice_objeto, 0x00400000) != 0) {
            funcion_8008861C(indice_objeto);
        }
        lista_objeto[indice_objeto].pos[1] = lista_objeto[indice_objeto].altura_superficie + 6.0;
    }
}

void funcion_800833D0(s32 indice_objeto, s32 parametro1) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 0:
            break;
        case 1:
            funcion_8008311C(indice_objeto, parametro1);
            break;
        case 2:
            funcion_80072D3C(indice_objeto, 0, 1, 4, -1);
            break;
    }
    if (lista_objeto[indice_objeto].textura_indice_lista == 0) {
        lista_objeto[indice_objeto].vertice = erizo_vtx_comun;
    } else {
        lista_objeto[indice_objeto].vertice = dato_0D006130;
    }
}

void funcion_80083474(s32 indice_objeto) {
    if (lista_objeto[indice_objeto].state >= 2) {
        funcion_80089F24(indice_objeto);
    }
}

void actualizar_erizos(void) {
    s32 temporal_s1;
    s32 variable_s0;

    for (variable_s0 = 0; variable_s0 < ERIZOS_NUM; variable_s0++) {
        temporal_s1 = lista_objeto_indice_2[variable_s0];
        funcion_800833D0(temporal_s1, variable_s0);
        funcion_80083248(temporal_s1);
        funcion_80083474(temporal_s1);
    }
    funcion_80072120(lista_objeto_indice_2, 0x0000000F);
}

void funcion_80083538(s32 indice_objeto, Vec3f parametro1, s32 parametro2, s32 parametro3) {
    Objeto* objeto;

    inicializar_objeto(indice_objeto, 0);
    objeto = &lista_objeto[indice_objeto];
    objeto->textura_activo = d_circuito_frappe_snowland_nieve;
    objeto->textura_lista = d_circuito_frappe_snowland_nieve;
    objeto->t_lut_activo = d_circuito_frappe_snowland_tlut_nieve;
    objeto->tlut_lista = d_circuito_frappe_snowland_tlut_nieve;
    objeto->escalado_tamanio = int_aleatorio(0x0064U);
    objeto->escalado_tamanio = (objeto->escalado_tamanio * 0.001) + 0.05;
    objeto->velocidad[1] = int_aleatorio(0x0014U);
    objeto->velocidad[1] = (objeto->velocidad[1] * 0.5) + 2.6;
    objeto->desconocido_034 = int_aleatorio(0x000AU);
    objeto->desconocido_034 = (objeto->desconocido_034 * 0.1) + 4.5;
    objeto->angulo_sentido[1] = (parametro2 << 0x10) / parametro3;
    objeto->pos_origen[0] = parametro1[0];
    objeto->pos_origen[1] = parametro1[1];
    objeto->pos_origen[2] = parametro1[2];
    objeto->prim_alpha = int_aleatorio(0x4000U) + 0x1000;
}

void funcion_800836F0(Vec3f parametro0) {
    s32 indice_objeto;
    s32 i;

    for (i = 0; i < dato_8018D3BC; i++) {
        indice_objeto = agregar_indice_obj_sin_uso(&particula_objeto_2[0], &siguiente_libre_objeto_particula_2, objeto_particula_2_tamanio);
        if (indice_objeto == ID_OBJETO_NULO) {
            break;
        }
        funcion_80083538(indice_objeto, parametro0, i, dato_8018D3BC);
    }
}

void funcion_8008379C(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            if (funcion_80087E08(indice_objeto, lista_objeto[indice_objeto].velocidad[1], 0.74f,
                              lista_objeto[indice_objeto].desconocido_034, lista_objeto[indice_objeto].angulo_sentido[1],
                              0x00000064) != 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 2:
            funcion_80086F60(indice_objeto);
            funcion_80072428(indice_objeto);
            break;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    lista_objeto[indice_objeto].orientacion[2] += lista_objeto[indice_objeto].prim_alpha;
}

void funcion_80083868(s32 indice_objeto) {
    Objeto* objeto;

    inicializar_objeto_textura(indice_objeto, d_circuito_frappe_snowland_tlut_munieco_nieve, d_circuito_frappe_snowland_cabeza_munieco_nieve,
                        0x40U, (u16) 0x00000040);
    objeto = &lista_objeto[indice_objeto];
    objeto->vertice = dato_0D0061B0;
    objeto->escalado_tamanio = 0.1f;
    objeto->textura_indice_lista = 0;
    estado_siguiente_objeto(indice_objeto);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    objeto->orientacion[0] = 0;
    objeto->orientacion[1] = 0;
    objeto->orientacion[2] = 0x8000;
    objeto->prim_alpha = int_aleatorio(0x2000U) - 0x1000;
    funcion_80086E70(indice_objeto);
    objeto->desconocido_034 = 1.5f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000200);
}

void funcion_80083948(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 1:
            funcion_80086FD4(indice_objeto);
            break;
        case 2:
            funcion_800871AC(indice_objeto, 0x00000014);
            break;
        case 3:
            funcion_8008701C(indice_objeto, 1);
            break;
        case 10:
            funcion_80087C48(indice_objeto, 10.0f, 0.5f, 0x0000000A);
            break;
        case 11:
            funcion_80087D24(indice_objeto, 0.0f, 0.2f, -7.0f);
            break;
        case 20:
            if (arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 0.0f, 0.2f) != 0) {
                funcion_80073800(indice_objeto, 0);
                funcion_8008701C(indice_objeto, 1);
            }
            break;
        case 0:
        default:
            break;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    funcion_80073D0C(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, -0x00001000, 0x00001000, 0x00000400, 1, -1);
    lista_objeto[indice_objeto].orientacion[2] = lista_objeto[indice_objeto].prim_alpha + 0x8000;
}

void funcion_80083A94(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            funcion_80083868(indice_objeto);
            break;
    }
    if (lista_objeto[indice_objeto].state >= 2) {
        funcion_80073514(indice_objeto);
    }
    funcion_80083948(indice_objeto);
}

void funcion_80083B0C(s32 indice_objeto) {
    inicializar_objeto_textura(indice_objeto, d_circuito_frappe_snowland_tlut_munieco_nieve, d_circuito_frappe_snowland_cuerpo_munieco_nieve,
                        0x40U, (u16) 0x00000040);
    lista_objeto[indice_objeto].vertice = erizo_vtx_comun;
    lista_objeto[indice_objeto].escalado_tamanio = 0.1f;
    lista_objeto[indice_objeto].textura_indice_lista = 0;
    estado_siguiente_objeto(indice_objeto);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    lista_objeto[indice_objeto].orientacion[0] = 0;
    lista_objeto[indice_objeto].orientacion[1] = 0;
    lista_objeto[indice_objeto].orientacion[2] = 0x8000;
    lista_objeto[indice_objeto].tamanio_caja_envolvente = 2;
    lista_objeto[indice_objeto].desconocido_034 = 1.5f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x04000210);
}

void funcion_80083BE4(s32 indice_objeto) {
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_80083C04(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->state) {
        case 0:
            break;
        case 1:
            funcion_80083B0C(indice_objeto);
            break;
        case 2:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x00000096);
            break;
        case 10:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000012C) != 0) {
                funcion_800722A4(indice_objeto, 2);
            }
            break;
        case 11:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000000A) != 0) {
                fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
                objeto->escalado_tamanio = 0.001f;
            }
            break;
        case 12:
            if (funcion_80074118(indice_objeto, &objeto->escalado_tamanio, 0.001f, 0.1f, 0.0025f, 0, 0) != 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 13:
            funcion_800726CC(indice_objeto, 2);
            fijar_objeto_bandera_situacion_false(indice_objeto, 0x00001000);
            break;
    }
    if (objeto->state >= 2) {
        funcion_80073514(indice_objeto);
    }
    funcion_80083BE4(indice_objeto);
}

void actualizar_muniecos_nieve(void) {
    s32 variable_s0;
    s32 variable_s3;
    s32 variable_s4;
    s32 indice_objeto;
    Objeto* objeto;

    for (variable_s0 = 0; variable_s0 < objeto_particula_2_tamanio; variable_s0++) {
        indice_objeto = particula_objeto_2[variable_s0];

        if (indice_objeto == ID_OBJETO_ELIMINADO) {
            continue;
        }

        if (lista_objeto[indice_objeto].state == 0) {
            continue;
        }
        funcion_8008379C(indice_objeto);
        if (lista_objeto[indice_objeto].state != 0) {
            continue;
        }
        eliminar_envoltorio_objeto(&particula_objeto_2[variable_s0]);
        if (variable_s0) {}
    }

    for (variable_s0 = 0; variable_s0 < MUNIECOS_NIEVE_NUM; variable_s0++) {
        variable_s4 = lista_objeto_indice_1[variable_s0];
        variable_s3 = lista_objeto_indice_2[variable_s0];
        funcion_80083A94(variable_s3);
        funcion_80083C04(variable_s4);
        if (es_obj_indice_bandera_situacion_inactivo(variable_s4, 0x00001000) != 0) {
            objeto = &lista_objeto[variable_s4];
            if ((funcion_8008A8B0(objeto->desconocido_0D5 - 1, objeto->desconocido_0D5 + 1) != 0) && (funcion_80089B50(variable_s4) != 0)) {
                fijar_objeto_bandera_situacion_true(variable_s4, 0x00001000);
                fijar_objeto_bandera_situacion_false(variable_s4, 0x00000010);
                funcion_800726CC(variable_s4, 0x0000000A);
                funcion_8008701C(variable_s3, 0x0000000A);
                funcion_800836F0(objeto->pos);
            }
        } else if (funcion_80072320(variable_s4, 2) != 0) {
            funcion_800722CC(variable_s4, 2);
            funcion_8008701C(variable_s3, 0x00000014);
        }
    }
}

void funcion_80083F18(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            if (funcion_80087E08(indice_objeto, lista_objeto[indice_objeto].velocidad[1], 0.12f,
                              lista_objeto[indice_objeto].desconocido_034, lista_objeto[indice_objeto].angulo_sentido[1],
                              0x00000064) != 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
            break;
        case 2:
            funcion_80086F60(indice_objeto);
            funcion_80072428(indice_objeto);
            break;
    }
}

void funcion_80083FD0(s32 indice_objeto, s32 parametro1, s32 id_jugador) {
    Objeto* objeto;
    Jugador* sp20;

    objeto = &lista_objeto[indice_objeto];
    sp20 = &jugador_uno[id_jugador];
    objeto->desconocido_084[7] = id_jugador;
    inicializar_objeto(indice_objeto, 0);
    objeto->t_lut_activo = d_circuito_sherbet_land_hielo;
    objeto->tlut_lista = d_circuito_sherbet_land_hielo;
    objeto->escalado_tamanio = ((f32) int_aleatorio(0x01F4U) * 0.0002) + 0.04;
    objeto->velocidad[1] = ((f32) int_aleatorio(0x0032U) * 0.05) + 1.0;
    objeto->desconocido_034 = ((f32) int_aleatorio(0x000AU) * 0.1) + 1.0;
    objeto->angulo_sentido[1] = dato_801657A2 * parametro1;
    objeto->pos_origen[0] = (sp20->pos[0] + int_aleatorio(0x0014U)) - 10.0f;
    objeto->pos_origen[1] = (sp20->pos[1] - 10.0) + int_aleatorio(0x000AU);
    objeto->pos_origen[2] = (sp20->pos[2] + int_aleatorio(0x0014U)) - 10.0f;
}

void funcion_8008421C(SIN_USO s32 parametro0, s32 id_jugador) {
    s32 indice_objeto;
    s32 variable_s0;

    for (variable_s0 = 0; variable_s0 < dato_8018D3C0; variable_s0++) {
        indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_2, &siguiente_libre_objeto_particula_2, objeto_particula_2_tamanio);
        if (indice_objeto == ID_OBJETO_NULO) {
            break;
        }
        funcion_80083FD0(indice_objeto, variable_s0, id_jugador);
    }
}
