// Llamas humo y hojas

void funcion_8007601C(s32 indice_objeto) {
    if (lista_objeto[indice_objeto].desconocido_04C > 0) {
        lista_objeto[indice_objeto].desconocido_04C--;
        if (lista_objeto[indice_objeto].desconocido_04C == 0) {
            funcion_800722CC(indice_objeto, 1);
        }
    }

    if (lista_objeto[indice_objeto].desconocido_048 > 0) {
        lista_objeto[indice_objeto].desconocido_048--;
        if (lista_objeto[indice_objeto].desconocido_048 == 0) {
            funcion_800C9EF4(lista_objeto[indice_objeto].pos, SONIDO_CARGA_PARAMETRO(0x51, 0x02, 0x80, 0x0A));
        }
    }

    if (lista_objeto[indice_objeto].desconocido_04C == 0) {
        funcion_8008A6DC(indice_objeto, 300.0f);
        if ((es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) && (funcion_80072354(indice_objeto, 1) != 0)) {
            funcion_800722A4(indice_objeto, 1);
            funcion_80075F98(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].angulo_sentido[1], 1.0f);
            funcion_800C9D80(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].velocidad,
                          SONIDO_CARGA_PARAMETRO(0x51, 0x02, 0x80, 0x0A));
            if (lista_objeto[indice_objeto].type > 0) {
                lista_objeto[indice_objeto].type--;
                lista_objeto[indice_objeto].desconocido_04C = 0x5A;
            } else {
                lista_objeto[indice_objeto].desconocido_04C = 0x12C;
            }

            lista_objeto[indice_objeto].desconocido_048 = 0x3C;
        }
    }

    if (funcion_8008A8B0(9, 0xB) == 0) {
        lista_objeto[indice_objeto].type = 2;
    }
}

void funcion_8007614C(void) {
    s32 algun_indice;

    for (algun_indice = 0; algun_indice < 4; algun_indice++) {
        funcion_8007601C(lista_objeto_indice_3[algun_indice]);
    }
}

void funcion_80076194(s32 indice_objeto, Vec3f parametro1, f32 parametro2, s32 parametro3) {
    Objeto* objeto;

    inicializar_objeto(indice_objeto, 0);
    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0D5 = 4;
    objeto->escalado_tamanio = 1.0f;
    objeto->pos_origen[0] = parametro1[0];
    objeto->pos_origen[1] = parametro1[1];
    objeto->pos_origen[2] = parametro1[2];
    objeto->angulo_sentido[0] = 0x0C00;
    objeto->angulo_sentido[2] = 0;
    objeto->angulo_sentido[1] = 0x2100;
    if (es_modo_espejo != 0) {
        objeto->angulo_sentido[1] += -0x4000;
    }
    objeto->type = 0x00FF;
    objeto->desconocido_0A2 = 0x00FF;
    objeto->desconocido_048 = parametro3 * 2;
    objeto->desconocido_034 = parametro2 * 8.0;
}

s32 funcion_80076278(Vec3f parametro0, f32 parametro1, s32 parametro2) {
    s32 indice_objeto;

    indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_1, &siguiente_libre_objeto_particula_1, objeto_particula_1_tamanio);
    if (indice_objeto != ID_OBJETO_NULO) {
        funcion_80076194(indice_objeto, parametro0, parametro1, parametro2);
    }
    return indice_objeto;
}

void funcion_800762DC(Vec3f parametro0, f32 parametro1) {
    s32 algun_indice;

    for (algun_indice = 0; algun_indice < 0x14; algun_indice++) {
        if (funcion_80076278(parametro0, parametro1, algun_indice) == -1) {
            break;
        }
    }
}

void funcion_8007634C(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->textura_activo = comun_textura_particula_humo[0];
    objeto->textura_lista = comun_textura_particula_humo[0];
    objeto->prim_alpha = 0x00FF;
    fijar_orientacion_obj(indice_objeto, 0U, 0U, 0U);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_800763CC(s32 indice_objeto) {
    Objeto* objeto;

    if (indice_objeto) {}
    objeto = &lista_objeto[indice_objeto];
    switch (objeto->state) {
        case 1:
            funcion_8007634C(indice_objeto);
            break;
        case 2:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, objeto->desconocido_048) != 0) {
                funcion_80086E70(indice_objeto);
            }
            break;
        case 3:
            if (objeto->desconocido_0D5 == 4) {
                paso_f32_hacia(&objeto->escalado_tamanio, 4.0f, 0.1f);
                paso_s16_hacia(&objeto->type, 0, 0x0018);
                paso_s16_hacia(&objeto->desconocido_0A2, 0x0080, 0x000C);
            } else {
                paso_f32_hacia(&objeto->escalado_tamanio, 1.0f, 0.1f);
                paso_s16_hacia(&objeto->type, 0, 0x0018);
                paso_s16_hacia(&objeto->desconocido_0A2, 0x0080, 0x000C);
            }
            if ((objeto->desconocido_0AE >= 2) &&
                (funcion_80073B00(indice_objeto, &objeto->prim_alpha, 0x000000FF, 0x00000050, 0x00000020, 0, 0) != 0)) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 4:
            funcion_80072428(indice_objeto);
            funcion_80086F60(indice_objeto);
            break;
        case 0:
        default:
            break;
    }
}

void funcion_80076538(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 0:
            break;
        case 1:
            if ((u8) lista_objeto[indice_objeto].desconocido_0D5 == 4) {
                if (funcion_80087060(indice_objeto, 0x0000000E) != 0) {
                    funcion_80086FD4(indice_objeto);
                }
            } else if (funcion_80087060(indice_objeto, 2) != 0) {
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            abajo_paso_u16_hacia(&lista_objeto[indice_objeto].angulo_sentido[0], 0, 0x00000400);
            break;
    }
    if (lista_objeto[indice_objeto].desconocido_0AE > 0) {
        funcion_80087844(indice_objeto);
        calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    }
}

void funcion_8007661C(void) {
    s32 indice_objeto;

    indice_objeto = lista_objeto_indice_2[0];
    if (lista_objeto[indice_objeto].desconocido_04C > 0) {
        lista_objeto[indice_objeto].desconocido_04C--;
        if (lista_objeto[indice_objeto].desconocido_04C == 0) {
            funcion_800722CC(indice_objeto, 1);
        }
    }
    if (lista_objeto[indice_objeto].desconocido_048 > 0) {
        lista_objeto[indice_objeto].desconocido_048--;
        if (lista_objeto[indice_objeto].desconocido_048 == 0) {
            funcion_800C9EF4(lista_objeto[indice_objeto].pos, SONIDO_CARGA_PARAMETRO(0x51, 0x03, 0x80, 0x09));
        }
    }
    if (lista_objeto[indice_objeto].desconocido_04C == 0) {
        funcion_8008A6DC(indice_objeto, 750.0f);
        if ((es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) && (funcion_80072354(indice_objeto, 1) != 0)) {
            funcion_800722A4(indice_objeto, 1);
            funcion_800762DC(lista_objeto[indice_objeto].pos, 1.0f);
            funcion_800C9D80(lista_objeto[indice_objeto].pos, lista_objeto[indice_objeto].velocidad, 0x51038009U);
            if (lista_objeto[indice_objeto].type > 0) {
                lista_objeto[indice_objeto].type--;
                lista_objeto[indice_objeto].desconocido_04C = 0x0000005A;
            } else {
                lista_objeto[indice_objeto].desconocido_04C = 0x0000012C;
            }
            lista_objeto[indice_objeto].desconocido_048 = 0x0000003C;
        }
    }
    if (funcion_8008A8B0(4, 5) == 0) {
        lista_objeto[indice_objeto].type = 2;
    }
}

void funcion_8007675C(s32 indice_objeto, Vec3s parametro1, s32 parametro2) {
    Objeto* objeto;

    inicializar_objeto(indice_objeto, 0);
    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0D5 = 9;
    objeto->escalado_tamanio = 1.0f;
    objeto->pos_origen[0] = parametro1[0];
    objeto->pos_origen[1] = parametro1[1];
    objeto->pos_origen[2] = parametro1[2];
    objeto->angulo_sentido[0] = 0x0C00;
    objeto->angulo_sentido[1] = 0x2100;
    objeto->angulo_sentido[2] = 0;
    objeto->type = 0x00FF;
    objeto->desconocido_0A2 = 0x00FF;
    objeto->desconocido_034 = 8.0f;
    objeto->velocidad[1] = 8.0f;
    objeto->desconocido_048 = parametro2;
}

s32 funcion_80076828(Vec3s parametro0, s32 parametro1) {
    s32 indice_objeto;

    indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_1, &siguiente_libre_objeto_particula_1, objeto_particula_1_tamanio);
    if (indice_objeto != ID_OBJETO_NULO) {
        funcion_8007675C(indice_objeto, parametro0, parametro1);
    }
    return indice_objeto;
}

void funcion_80076884(s32 parametro0) {
    SIN_USO s32 margen_pila_0;
    s32 i;
    s32 temporal_v0;
    s16* variable_s2;
    temporal_v0 = int_aleatorio(0x000FU);
    switch (parametro0) {
        case 0:
            variable_s2 = dato_800E5740 + (temporal_v0 * 3);
            break;

        case 1:
            variable_s2 = dato_800E579C + (temporal_v0 * 3);
            break;

        case 2:
            variable_s2 = dato_800E57F8 + (temporal_v0 * 3);
            break;
    }

    for (i = 0; i < 1; i++) {
        if (funcion_80076828(variable_s2, i) == (-1)) {
            break;
        }
    }
}

void funcion_80076958(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->textura_activo = comun_textura_particula_humo[0];
    objeto->textura_lista = comun_textura_particula_humo[0];
    objeto->prim_alpha = 0x00FF;
    fijar_orientacion_obj(indice_objeto, 0U, 0U, 0U);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_800769D8(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    switch (objeto->state) {
        case 0:
            break;
        case 1:
            funcion_80076958(indice_objeto);
            break;
        case 2:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, objeto->desconocido_048) != 0) {
                funcion_80086E70(indice_objeto);
            }
            break;
        case 3:
            paso_f32_hacia(&objeto->escalado_tamanio, 2.0f, 0.05f);
            paso_s16_hacia(&objeto->type, 0, 0x0018);
            if ((objeto->desconocido_0AE >= 2) &&
                (funcion_80073B00(indice_objeto, &objeto->prim_alpha, 0x000000FF, 0x00000050, 0x00000020, 0, 0) != 0)) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 4:
            funcion_80072428(indice_objeto);
            funcion_80086F60(indice_objeto);
            break;
    }
}

void funcion_80076AEC(s32 indice_objeto) {
    s32 cosa;
    cosa = lista_objeto[indice_objeto].desconocido_0AE;
    if (cosa) {}
    if (cosa != 0) {
        if (cosa == 1) {
            if (funcion_80087060(indice_objeto, 0x0000000A) != 0) {
                funcion_80086FD4(indice_objeto);
            }
        } else {
            cosa = lista_objeto[indice_objeto].desconocido_0AE;
        }
    }
    if (lista_objeto[indice_objeto].desconocido_0AE > 0) {
        agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
        calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    }
}

void funcion_80076B7C(void) {
}

void actualizar_particula_llama(void) {
    s32 algun_indice;
    s32 indice_objeto;
    Objeto* objeto;

    funcion_8007661C();
    funcion_8007614C();
    for (algun_indice = 0; algun_indice < objeto_particula_1_tamanio; algun_indice++) {
        indice_objeto = particula_objeto_1[algun_indice];
        if (indice_objeto != ID_OBJETO_ELIMINADO) {
            objeto = &lista_objeto[indice_objeto];
            if (objeto->state != 0) {
                if ((objeto->desconocido_0D5 == 4) || (objeto->desconocido_0D5 == 5)) {
                    funcion_800763CC(indice_objeto);
                    funcion_80076538(indice_objeto);
                } else if (objeto->desconocido_0D5 == 9) {
                    funcion_800769D8(indice_objeto);
                    funcion_80076AEC(indice_objeto);
                }
                if (objeto->state == 0) {
                    eliminar_envoltorio_objeto(&particula_objeto_1[algun_indice]);
                }
            }
        }
    }
}

void inicializar_objeto_humo_particula(s32 indice_objeto, Vec3f parametro1, s16 parametro2) {
    Objeto* objeto;

    inicializar_objeto(indice_objeto, (s32) parametro2);
    objeto = &lista_objeto[indice_objeto];
    objeto->desconocido_0D5 = 0x0A;
    objeto->textura_activo = comun_textura_particula_humo[0];
    objeto->textura_lista = comun_textura_particula_humo[0];
    objeto->escalado_tamanio = 0.3f;
    fijar_pos_origen_obj(indice_objeto, parametro1[0], parametro1[1], parametro1[2]);
    objeto->type = 0x00FF;
    objeto->desconocido_034 = 0.0f;
    fijar_orientacion_obj(indice_objeto, 0U, 0U, 0U);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
}

void inicializar_particula_humo(Vec3f parametro0, SIN_USO f32 parametro1, s16 parametro2) {
    s32 indice_objeto;

    indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_4, &siguiente_libre_objeto_particula_4, objeto_particula_4_tamanio);
    if (indice_objeto != ID_OBJETO_NULO) {
        inicializar_objeto_humo_particula(indice_objeto, parametro0, parametro2);
    }
}

void funcion_80076DC4(s32 indice_objeto) {
    estado_siguiente_objeto(indice_objeto);
    if (lista_objeto[indice_objeto].desconocido_0D5 != 0x0B) {
        funcion_80086E70(indice_objeto);
    }
}

void funcion_80076E14(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) {
        case 1:
            funcion_80076DC4(indice_objeto);
            break;
        case 2:
            if ((lista_objeto[indice_objeto].desconocido_0AE >= 2) &&
                (funcion_80073B00(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0x000000FF, 0x00000050, 0x00000020, 0,
                               0) != 0)) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 0:
            break;
        case 3:
            funcion_80072428(indice_objeto);
            funcion_80086F60(indice_objeto);
            break;
    }
}

void funcion_80076ED8(s32 indice_objeto) {
    if ((lista_objeto[indice_objeto].desconocido_0AE != 0) && (lista_objeto[indice_objeto].desconocido_0AE == 1)) {
        funcion_80086FD4(indice_objeto);
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_80076F2C(void) {
    s32 algun_indice;
    s32 indice_llama;
    Objeto* objeto;

    for (algun_indice = 0; algun_indice < objeto_particula_4_tamanio; algun_indice++) {
        indice_llama = particula_objeto_4[algun_indice];
        if (indice_llama != ID_OBJETO_ELIMINADO) {
            objeto = &lista_objeto[indice_llama];
            if (objeto->state != 0) {
                funcion_80076E14(indice_llama);
                funcion_80076ED8(indice_llama);
                if (objeto->state == 0) {
                    eliminar_envoltorio_objeto(&particula_objeto_4[algun_indice]);
                }
            }
        }
    }
}

void inicializar_particula_humo_objeto(s32 indice_objeto, s32 indice_llama) {
    inicializar_objeto(indice_objeto, 3);

    lista_objeto[indice_objeto].desconocido_0D5 = 0xB;
    lista_objeto[indice_objeto].textura_activo = comun_textura_particula_humo[0];
    lista_objeto[indice_objeto].textura_lista = comun_textura_particula_humo[0];
    lista_objeto[indice_objeto].escalado_tamanio = 0.8f;

    lista_objeto[indice_objeto].pos_origen[0] = (f32) * (apariciones_antorcha + (indice_llama * 3) + 0) * orientacion_x;
    lista_objeto[indice_objeto].pos_origen[1] = (f32) * (apariciones_antorcha + (indice_llama * 3) + 1);
    lista_objeto[indice_objeto].pos_origen[2] = (f32) * (apariciones_antorcha + (indice_llama * 3) + 2);
    lista_objeto[indice_objeto].desconocido_034 = 0;
    lista_objeto[indice_objeto].type = 255;
    lista_objeto[indice_objeto].desconocido_0A2 = 255;
    lista_objeto[indice_objeto].prim_alpha = 255;
    fijar_orientacion_obj(indice_objeto, 0, 0, 0);
    fijar_desplazamiento_origen_obj(indice_objeto, 0, 0, 0);
}

void inicializar_particulas_humo(s32 parametro0) {
    s32 indice_objeto;

    indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_4, &siguiente_libre_objeto_particula_4, objeto_particula_4_tamanio);
    if (indice_objeto != ID_OBJETO_NULO) {
        inicializar_particula_humo_objeto(indice_objeto, parametro0);
    }
}

void funcion_80077138(s32 indice_objeto, Vec3f parametro1, s32 parametro2) {
    s8 temporal_v0_3;
    Vec3s sp30;

    inicializar_objeto(indice_objeto, parametro2);
    lista_objeto[indice_objeto].desconocido_0D5 = 0x0C;
    lista_objeto[indice_objeto].escalado_tamanio = 0.05f;
    fijar_pos_origen_obj(indice_objeto, parametro1[0], parametro1[1], parametro1[2]);
    fijar_orientacion_obj(indice_objeto, 0U, 0U, 0U);
    fijar_desplazamiento_origen_obj(indice_objeto, 0.0f, 0.0f, 0.0f);
    switch (parametro2) {
        case 0:
            lista_objeto[indice_objeto].velocidad[1] = -1.0f;
            lista_objeto[indice_objeto].desconocido_034 = (f32) ((int_aleatorio(0x004BU) * 0.01) + 0.25);
            lista_objeto[indice_objeto].angulo_sentido[1] = int_aleatorio(0x0040U) << 0xA;
            funcion_8008751C(indice_objeto);
            lista_objeto[indice_objeto].desconocido_084[5] = 0x001E;
            break;
        case 1:
            lista_objeto[indice_objeto].velocidad[1] = 1.5f;
            lista_objeto[indice_objeto].desconocido_034 = (f32) ((int_aleatorio(0x0064U) * 0.01) + 0.5);
            lista_objeto[indice_objeto].angulo_sentido[1] = int_aleatorio(0x0040U) << 0xA;
            funcion_8008751C(indice_objeto);
            lista_objeto[indice_objeto].desconocido_084[5] = 0x0032;
            break;
    }
    temporal_v0_3 = int_aleatorio(0x000CU);
    if (temporal_v0_3 < 9) {
        funcion_8005C674(temporal_v0_3, &sp30[2], &sp30[1], sp30);
        lista_objeto[indice_objeto].desconocido_048 = 0;
        lista_objeto[indice_objeto].desconocido_084[0] = sp30[2];
        lista_objeto[indice_objeto].desconocido_084[1] = sp30[1];
        lista_objeto[indice_objeto].desconocido_084[2] = sp30[0];
    } else {
        temporal_v0_3 = int_aleatorio(3U);
        funcion_8005C6B4(temporal_v0_3, &sp30[2], &sp30[1], sp30);
        lista_objeto[indice_objeto].desconocido_084[0] = sp30[2];
        lista_objeto[indice_objeto].desconocido_084[1] = sp30[1];
        lista_objeto[indice_objeto].desconocido_084[2] = sp30[0];
        lista_objeto[indice_objeto].desconocido_084[4] = temporal_v0_3;
        lista_objeto[indice_objeto].desconocido_048 = 1;
    }
    lista_objeto[indice_objeto].prim_alpha = 0x00FF;
    lista_objeto[indice_objeto].desconocido_084[3] = int_aleatorio(0x0800U) + 0x400;
    if ((lista_objeto[indice_objeto].angulo_sentido[1] < 0x3000) ||
        (lista_objeto[indice_objeto].angulo_sentido[1] >= 0xB001)) {
        lista_objeto[indice_objeto].desconocido_084[3] = -lista_objeto[indice_objeto].desconocido_084[3];
    }
}

void funcion_800773D8(f32* parametro0, s32 parametro1) {
    s32 indice_objeto = agregar_indice_obj_sin_uso(particula_objeto_3, &siguiente_libre_objeto_particula_3, objeto_particula_3_tamanio);
    if (indice_objeto != ID_OBJETO_NULO) {
        funcion_80077138(indice_objeto, parametro0, parametro1);
    }
}

void funcion_80077428(s32 parametro0) {
    estado_siguiente_objeto(parametro0);
    funcion_80086E70(parametro0);
}

void funcion_80077450(s32 indice_objeto) {
    SIN_USO s16 margen_pila_0;
    s16 sp3_c;
    s16 sp3_a;
    s16 sp38;

    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            funcion_80077428(indice_objeto);
            break;
        case 2:
            arriba_paso_f32_hacia(&lista_objeto[indice_objeto].escalado_tamanio, 0.1f, 0.01f);
            if ((lista_objeto[indice_objeto].pos[1] <= lista_objeto[indice_objeto].desconocido_084[5]) &&
                (funcion_80073B00(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0x000000FF, 0, 0x00000010, 0, 0) !=
                 0)) {
                funcion_80086F60(indice_objeto);
                funcion_80072428(indice_objeto);
            }
            break;
    }
    if (lista_objeto[indice_objeto].desconocido_048 != 0) {
        lista_objeto[indice_objeto].desconocido_084[4] = (s16) ((s32) (lista_objeto[indice_objeto].desconocido_084[4] + 1) % 3);
        funcion_8005C6B4(lista_objeto[indice_objeto].desconocido_084[4], &sp3_c, &sp3_a, &sp38);
        lista_objeto[indice_objeto].desconocido_084[0] = sp3_c;
        lista_objeto[indice_objeto].desconocido_084[1] = sp3_a;
        lista_objeto[indice_objeto].desconocido_084[2] = sp38;
    }
}

void funcion_80077584(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    if ((objeto->desconocido_0AE != 0) && (objeto->desconocido_0AE == 1) && ((u8) objeto->desconocido_0D8 != 0)) {
        if (objeto->velocidad[1] >= -0.5) {
            objeto->velocidad[1] -= 0.15;
        } else {
            objeto->velocidad[2] = 0.0f;
            objeto->velocidad[0] = 0.0f;
        }
    }
    objeto->orientacion[2] += objeto->desconocido_084[3];
    agregar_desplazamiento_xyz_velocidad_objeto(indice_objeto);
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
}

void funcion_80077640(void) {
    s32 algun_indice;
    s32 indice_objeto;
    Objeto* objeto;

    for (algun_indice = 0; algun_indice < objeto_particula_3_tamanio; algun_indice++) {
        indice_objeto = particula_objeto_3[algun_indice];
        if (indice_objeto != ID_OBJETO_ELIMINADO) {
            objeto = &lista_objeto[indice_objeto];
            if (objeto->state != 0) {
                funcion_80077450(indice_objeto);
                funcion_80077584(indice_objeto);
                if (objeto->state == 0) {
                    eliminar_envoltorio_objeto(&particula_objeto_3[algun_indice]);
                }
            }
        }
    }
}

void inicializar_particula_hoja_objeto(s32 indice_objeto, Vec3f parametro1, s32 num) {
    SIN_USO s32 margen_pila_1;
    SIN_USO u16 margen_pila_0;
    u16 temporal_s0;
    u16 sp3_e;
    u16 sp3_c;

    inicializar_objeto(indice_objeto, 0);
    lista_objeto[indice_objeto].desconocido_0D5 = 7;
    lista_objeto[indice_objeto].t_lut_activo = (u8*) comun_textura_particula_hoja;
    lista_objeto[indice_objeto].tlut_lista = (u8*) comun_textura_particula_hoja;
    lista_objeto[indice_objeto].escalado_tamanio = 0.1f;
    lista_objeto[indice_objeto].altura_superficie = parametro1[1];
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            objeto_origen_pos_aleatorizar_alrededor_xyz(indice_objeto, parametro1[0], parametro1[1] + 25.0, parametro1[2], 0x14, 0x1E, 0x14);
            lista_objeto[indice_objeto].desconocido_034 = 1.5f;
            lista_objeto[indice_objeto].velocidad[1] = 1.5f;
            break;
        case CIRCUITO_YOSHI_VALLEY:
            objeto_origen_pos_aleatorizar_alrededor_xyz(indice_objeto, parametro1[0], parametro1[1] + 25.0, parametro1[2], 0x14, 0x1E, 0x14);
            lista_objeto[indice_objeto].desconocido_034 = 2.0f;
            lista_objeto[indice_objeto].velocidad[1] = 2.0f;
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            objeto_origen_pos_aleatorizar_alrededor_xyz(indice_objeto, parametro1[0], parametro1[1] + 30.0, parametro1[2], 0x10, 0x28, 0x10);
            lista_objeto[indice_objeto].desconocido_034 = 2.0f;
            lista_objeto[indice_objeto].velocidad[1] = 2.0f;
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            objeto_origen_pos_aleatorizar_alrededor_xyz(indice_objeto, parametro1[0], parametro1[1] + 25.0, parametro1[2], 0x14, 0x1E, 0x14);
            lista_objeto[indice_objeto].desconocido_034 = 1.5f;
            lista_objeto[indice_objeto].velocidad[1] = 1.0f;
            break;
    }
    temporal_s0 = int_aleatorio(0x0010U) << 0xC;
    sp3_e = int_aleatorio(0x0010U) << 0xC;
    sp3_c = int_aleatorio(0x0010U) << 0xC;
    fijar_angulo_sentido_obj(indice_objeto, 0U, (num * 0xFFFF) / 20, 0U);
    fijar_orientacion_obj(indice_objeto, temporal_s0, sp3_e, sp3_c);
}

s32 inicializar_particula_hoja(Vec3f parametro0, s32 num) {
    s32 indice_objeto;

    indice_objeto = agregar_indice_obj_sin_uso(particula_hoja, &siguiente_libre_hoja_particula, hoja_particula_tamanio);
    if (indice_objeto != ID_OBJETO_NULO) {
        inicializar_particula_hoja_objeto(indice_objeto, parametro0, num);
    }
    return indice_objeto;
}

void aparecer_hoja(Vec3f parametro0, SIN_USO s32 parametro1) {
    s32 i;

    for (i = 0; i < hoja_particula_aparicion_tamanio; i++) {
        if (inicializar_particula_hoja(parametro0, i) == ID_OBJETO_NULO) {
            break;
        }
    }
}

void funcion_80077B14(s32 parametro0) {
    estado_siguiente_objeto(parametro0);
    funcion_80086E70(parametro0);
}

void funcion_80077B3C(s32 indice_objeto) {
    Objeto* objeto;
    objeto = &lista_objeto[indice_objeto];

    switch (objeto->state) {
        case 0:
            break;
        case 1:
            funcion_80077B14(indice_objeto);
            break;
        case 2:
            if (objeto->desconocido_0AE == 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 3:
            funcion_80072428(indice_objeto);
            break;
    }
}

void funcion_80077BCC(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 1:
            funcion_80087E08(indice_objeto, lista_objeto[indice_objeto].velocidad[1], 0.2f, lista_objeto[indice_objeto].desconocido_034,
                          (s16) (s32) lista_objeto[indice_objeto].angulo_sentido[1], 0x0000000A);
            break;
        case 2:
            if (funcion_80087B84(indice_objeto, 0.4f, lista_objeto[indice_objeto].altura_superficie) != 0) {
                funcion_80086F60(indice_objeto);
            }
            break;
    }
    calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
    lista_objeto[indice_objeto].orientacion[0] += 0x1000;
    lista_objeto[indice_objeto].orientacion[1] += 0x1000;
}

void actualizar_hoja(void) {
    s32 algun_indice;
    s32 indice_hoja;
    Objeto* objeto;

    for (algun_indice = 0; algun_indice < hoja_particula_tamanio; algun_indice++) {
        indice_hoja = particula_hoja[algun_indice];
        if (indice_hoja != ID_OBJETO_ELIMINADO) {
            objeto = &lista_objeto[indice_hoja];
            if (objeto->state != 0) {
                funcion_80077B3C(indice_hoja);
                funcion_80077BCC(indice_hoja);
                if (objeto->state == 0) {
                    eliminar_envoltorio_objeto(&particula_hoja[algun_indice]);
                }
            }
        }
    }
}

void funcion_80077D5C(s32 parametro0) {
    s32 indice_objeto;
    s32 variable_a1;

    if (dato_8016559C == 0) {
        for (variable_a1 = 0; variable_a1 < dato_8018D1F0; variable_a1++) {
            dato_8018D17C += 1;
            if (dato_8018D17C >= dato_8018D1F0) {
                dato_8018D17C = 0;
            }
            indice_objeto = dato_8018CC80[parametro0 + dato_8018D17C];
            if (lista_objeto[indice_objeto].state == 0) {
                inicializar_objeto(indice_objeto, 1);
                break;
            }
        }
    }
}

void funcion_80077E20(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->textura_activo = dato_0D0293D8;
    objeto->textura_lista = dato_0D0293D8;
    objeto->vertice = rectangulo_vtx_comun;
    objeto->textura_altura = 0x10;
    objeto->textura_ancho = objeto->textura_altura;
    objeto->escalado_tamanio = 0.15f;
    fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
    funcion_80086EF0(indice_objeto);
    objeto->prim_alpha = 0x00FF;
    objeto->desconocido_0D5 = 0;
    objeto->type = 0;
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80077EB8(s32 indice_objeto, u16 parametro1, Camara* camara) {
    s16 temporal_v0;

    temporal_v0 = camara->rot[1] - parametro1;
    if ((temporal_v0 >= dato_8018D210) || (dato_8018D208 >= temporal_v0)) {
        lista_objeto[indice_objeto].offset[0] = dato_8018D218 + (dato_8018D1E8 * (f32) temporal_v0);
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
        return;
    }
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000010);
}

void funcion_80077F64(s32 indice_objeto, Camara* camara) {

    f64 rand;

    switch (lista_objeto[indice_objeto].desconocido_0AE) { /* irregular */
        case 1:
            lista_objeto[indice_objeto].angulo_sentido[1] = (camara->rot[1] + int_aleatorio(0x4000U)) - GRADOS(45);
            objeto_origen_pos_aleatorizar_alrededor_y(indice_objeto, 0x00B4, 0x0014U);
            rand = int_aleatorio(0x0064U);

            lista_objeto[indice_objeto].velocidad[1] = (f32) (-0.75 - (f64) (f32) (rand * 0.01));
            lista_objeto[indice_objeto].offset[0] = 0.0f;
            lista_objeto[indice_objeto].offset[1] = 0.0f;
            funcion_80086FD4(indice_objeto);
            return;
        case 2:
            funcion_80077EB8(indice_objeto, lista_objeto[indice_objeto].angulo_sentido[1], camara);
            agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
            calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
            funcion_8008BFC0(indice_objeto);
            if (lista_objeto[indice_objeto].pos[1] <= 0.0f) {
                funcion_80086FD4(indice_objeto);
                return;
            }
        case 0:
            return;
        case 3:
            funcion_80086F60(indice_objeto);
            break;
    }
}

void funcion_800780CC(s32 indice_objeto, Camara* camara) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 1:
            funcion_80077E20(indice_objeto);
            return;
        case 2:
            funcion_80077F64(indice_objeto, camara);
            if (lista_objeto[indice_objeto].desconocido_0AE == 0) {
                estado_siguiente_objeto(indice_objeto);
                return;
            }
        case 0:
            return;
        case 3:
            funcion_80072428(indice_objeto);
            break;
    }
}

void funcion_80078170(s32 parametro0, Camara* parametro1) {
    s32 indice_objeto;
    s32 i;

    funcion_80077D5C(parametro0);
    for (i = 0; i < dato_8018D1F0; i++) {
        indice_objeto = dato_8018CC80[parametro0 + i];
        if (lista_objeto[indice_objeto].state != 0) {
            funcion_800780CC(indice_objeto, parametro1);
        }
    }
}

void funcion_80078220(s32 indice_objeto) {
    Objeto* objeto;

    objeto = &lista_objeto[indice_objeto];
    objeto->textura_activo = dato_0D0293D8;
    objeto->textura_lista = dato_0D0293D8;
    objeto->vertice = rectangulo_vtx_comun;
    objeto->escalado_tamanio = 0.15f;
    funcion_80086EF0(indice_objeto);
    estado_siguiente_objeto(indice_objeto);
}

void funcion_80078288(s32 indice_objeto) {
    s16 sp3_e;
    s16 sp3_c;
    s16 sp3_a;
    SIN_USO u16 relleno;
    u16 temporal_t6;

    switch (lista_objeto[indice_objeto].desconocido_0AE) { /* irregular */
        case 0:
            break;
        case 1:
            if (estado_juego != 9) {
                sp3_a = ((copia_jugador_uno->speed / 18) * 216) / 2;
                sp3_e = (int_aleatorio(0x000FU) - sp3_a) + 0x2D;
                sp3_c = int_aleatorio(0x012CU) + 0x1E;
                temporal_t6 = camara1->rot[1] + ((s32) (int_aleatorio(0x3000U) - 0x1800) / (s16) ((sp3_a / 15) + 1));
                lista_objeto[indice_objeto].pos_origen[0] = copia_jugador_uno->pos[0] + (senos(temporal_t6) * sp3_c);
                lista_objeto[indice_objeto].pos_origen[1] = sp3_e + copia_jugador_uno->desconocido_074;
                lista_objeto[indice_objeto].pos_origen[2] = copia_jugador_uno->pos[2] + (coss(temporal_t6) * sp3_c);
                lista_objeto[indice_objeto].desconocido_0C4 = int_aleatorio(0x0400U) + 0x100;
                lista_objeto[indice_objeto].desconocido_01C[0] = (f32) (((f32) int_aleatorio(0x0064U) * 0.03) + 2.0);
                lista_objeto[indice_objeto].velocidad[1] = (f32) (-0.3 - (f64) (f32) (int_aleatorio(0x0032U) * 0.01));
                lista_objeto[indice_objeto].offset[0] = 0.0f;
                lista_objeto[indice_objeto].offset[1] = 0.0f;
                funcion_80086FD4(indice_objeto);
            } else {
                sp3_c = int_aleatorio(0x0064U) + 0x28;
                temporal_t6 = camara1->rot[1] + int_aleatorio(0x3000U) - 0x1800;
                lista_objeto[indice_objeto].pos_origen[0] = camara1->pos[0] + (senos(temporal_t6) * sp3_c);
                lista_objeto[indice_objeto].pos_origen[1] = camara1->pos[1] + 45.0;
                lista_objeto[indice_objeto].pos_origen[2] = camara1->pos[2] + (coss(temporal_t6) * sp3_c);
                lista_objeto[indice_objeto].desconocido_0C4 = int_aleatorio(0x0400U) + 0x100;
                lista_objeto[indice_objeto].desconocido_01C[0] = (f32) (((f32) int_aleatorio(0x0064U) * 0.03) + 2.0);
                lista_objeto[indice_objeto].velocidad[1] = (f32) (-0.6 - (f64) (f32) (int_aleatorio(0x0032U) * 0.01));
                lista_objeto[indice_objeto].offset[0] = 0.0f;
                lista_objeto[indice_objeto].offset[1] = 0.0f;
                funcion_80086FD4(indice_objeto);
            }
            break;
        case 2:
            agregar_desplazamiento_y_velocidad_objeto(indice_objeto);
            lista_objeto[indice_objeto].angulo_sentido[0] += lista_objeto[indice_objeto].desconocido_0C4;
            lista_objeto[indice_objeto].offset[0] =
                senos(lista_objeto[indice_objeto].angulo_sentido[0]) * lista_objeto[indice_objeto].desconocido_01C[0];
            calcular_desplazamiento_pos_nuevo_objeto(indice_objeto);
            if ((f64) lista_objeto[indice_objeto].pos[1] <= 0.0) {
                funcion_80086FD4(indice_objeto);
            }
            lista_objeto[indice_objeto].orientacion[1] = angulo_entre_camara_objeto(indice_objeto, camara1);
            break;
        case 3:
            funcion_80086F60(indice_objeto);
            break;
    }
}
