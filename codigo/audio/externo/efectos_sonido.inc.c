// Efectos sonido

u8 funcion_800C357C(s32 parametro0) {
    u8 variable_v1;
    u8 i;

    i = dato_800EA1E8;
    variable_v1 = true;
    for (i = dato_800EA1E8; i < (s32) dato_800EA1E4; i++) {
        if ((u32) parametro0 == dato_80192CD0[i]) {
            variable_v1 = false;
            i = dato_800EA1E4;
        }
    }
    return variable_v1;
}

#ifdef VERSION_EU
u8 func_800C357C_eu(s32 parametro0, s32 parametro1) {
    u8 variable_v1;
    u8 i;

    i = dato_800EA1E8;
    variable_v1 = 1;
    for (i = dato_800EA1E8; i < (s32) dato_800EA1E4; i++) {
        if (parametro0 == (dato_80192CD0[i] & parametro1)) {
            variable_v1 = 0;
            i = dato_800EA1E4;
        }
    }
    return variable_v1;
}
#endif

void funcion_800C35E8(u8 parametro0) {
    dato_80192CC6[parametro0] = 0;
}

void funcion_800C3608(u8 parametro0, u8 parametro1) {
    u8 variable_v0;
    u8 cosa;

    for (variable_v0 = 0; variable_v0 < dato_801930D0[parametro0].desconocido_041; variable_v0++) {
        cosa = (dato_801930D0[parametro0].desconocido_02C[variable_v0] & 0xF00000) >> 0x14;
        if (cosa == parametro1) {
            dato_801930D0[parametro0].desconocido_02C[variable_v0] = 0xFF000000;
        }
    }
}

void funcion_800C36C4(u8 parametro0, u8 parametro1, u8 parametro2, u8 parametro3) {
    dato_801930D0[parametro0].desconocido_00E[parametro1] = parametro2;
    dato_801930D0[parametro0].desconocido_011 = parametro3;
    dato_801930D0[parametro0].desconocido_012 = 1;
}

void funcion_800C3724(void) {
    u8 sec_indice_jugador;
    f32 volumen;
    u8 tempo_op;
    u16 objetivo_tempo;
    u8 indice_canal;
    u8 j;
    u32 tempo_cmd;
    u16 ant_tempo;
    u8 temporizador_tempo;
    u8 preparar_op;
    u8 objetivo_sec_jugador_indice;
    u8 preparar_val_1;
    u8 preparar_val_2;
    u16 sec_id;

    for (sec_indice_jugador = 0; sec_indice_jugador < 3; sec_indice_jugador++) {
        if (dato_801930D0[sec_indice_jugador].desconocido_012) {
            volumen = 1.0f;
            for (j = 0; j < 3; j++) {
                volumen *= dato_801930D0[sec_indice_jugador].desconocido_00E[j] / 127.0f;
            }

            funcion_800C3448(0x40000000 | (((u8) sec_indice_jugador) << 0x18) |
                          (((u8) dato_801930D0[sec_indice_jugador].desconocido_011) << 0x10) | ((u16) (u8) (volumen * 127.0f)));

            dato_801930D0[sec_indice_jugador].desconocido_012 = 0;
        }
        if (dato_801930D0[sec_indice_jugador].desconocido_00C != 0) {
            dato_801930D0[sec_indice_jugador].desconocido_00C--;
            if (dato_801930D0[sec_indice_jugador].desconocido_00C) {
                dato_801930D0[sec_indice_jugador].desconocido_000 -= dato_801930D0[sec_indice_jugador].desconocido_008;
            } else {
                dato_801930D0[sec_indice_jugador].desconocido_000 = dato_801930D0[sec_indice_jugador].desconocido_004;
            }
            funcion_800CBB88(0x41000000 | (((u32) sec_indice_jugador & 0xFF) << 0x10), dato_801930D0[sec_indice_jugador].desconocido_000);
        }
        if (dato_801930D0[sec_indice_jugador].desconocido_014 != 0) {
            tempo_cmd = dato_801930D0[sec_indice_jugador].desconocido_014;
            temporizador_tempo = (tempo_cmd & 0xFF0000) >> 0xF;
            objetivo_tempo = tempo_cmd & 0xFFF;
            if (temporizador_tempo == 0) {
                temporizador_tempo++;
            }
            if (jugadores_secuencia[sec_indice_jugador].activado != 0) {
                ant_tempo = jugadores_secuencia[sec_indice_jugador].tempo / 48;
                tempo_op = (tempo_cmd & 0xF000) >> 0xC;
                switch (tempo_op) {
                    case 1:
                        objetivo_tempo += ant_tempo;
                        break;

                    case 2:
                        if (objetivo_tempo < ant_tempo) {
                            objetivo_tempo = ant_tempo - objetivo_tempo;
                        }
                        break;

                    case 3:
                        objetivo_tempo = ant_tempo * (objetivo_tempo / 100.0f);
                        break;

                    case 4:
                        objetivo_tempo =
                            (dato_801930D0[sec_indice_jugador].desconocido_018 != 0) ? dato_801930D0[sec_indice_jugador].desconocido_018 : ant_tempo;
                        break;
                    default:
                        break;
                }

                if (objetivo_tempo > 300) {
                    objetivo_tempo = 300;
                }
                if (dato_801930D0[sec_indice_jugador].desconocido_018 == 0) {
                    dato_801930D0[sec_indice_jugador].desconocido_018 = ant_tempo;
                }
                dato_801930D0[sec_indice_jugador].desconocido_020 = objetivo_tempo;
                dato_801930D0[sec_indice_jugador].desconocido_01C = jugadores_secuencia[sec_indice_jugador].tempo / 48;
                dato_801930D0[sec_indice_jugador].desconocido_024 =
                    (dato_801930D0[sec_indice_jugador].desconocido_01C - dato_801930D0[sec_indice_jugador].desconocido_020) / temporizador_tempo;
                dato_801930D0[sec_indice_jugador].desconocido_028 = temporizador_tempo;
            }
            dato_801930D0[sec_indice_jugador].desconocido_014 = 0;
        }
        if (dato_801930D0[sec_indice_jugador].desconocido_028 != 0) {
            dato_801930D0[sec_indice_jugador].desconocido_028--;
            if (dato_801930D0[sec_indice_jugador].desconocido_028) {
                dato_801930D0[sec_indice_jugador].desconocido_01C -= dato_801930D0[sec_indice_jugador].desconocido_024;
            } else {
                dato_801930D0[sec_indice_jugador].desconocido_01C = dato_801930D0[sec_indice_jugador].desconocido_020;
            }
            funcion_800CBBB8(0x47000000 | (((u32) sec_indice_jugador & 0xFF) << 0x10),
                          (s32) dato_801930D0[sec_indice_jugador].desconocido_01C);
        }

        if (dato_801930D0[sec_indice_jugador].desconocido_246 != 0) {
            for (indice_canal = 0; indice_canal < 0x10; indice_canal++) {
                if (dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_0C != 0) {
                    dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_0C--;
                    if (dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_0C) {
                        dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_00 -=
                            dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_08;
                    } else {
                        dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_00 =
                            dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_04;
                        dato_801930D0[sec_indice_jugador].desconocido_246 ^= 1 << indice_canal;
                    }
                    funcion_800CBB88(0x01000000 | ((sec_indice_jugador & 0xFF) << 0x10) | (((u32) indice_canal & 0xFF) << 8),
                                  dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_00);
                }
            }
        }
        if (dato_801930D0[sec_indice_jugador].desconocido_244 != 0) {
            for (indice_canal = 0; indice_canal < 0x10; indice_canal++) {
                if (dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_1C != 0) {
                    dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_1C--;
                    if (dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_1C) {
                        dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_10 -=
                            dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_18;
                    } else {
                        dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_10 =
                            dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_14;
                        dato_801930D0[sec_indice_jugador].desconocido_244 ^= 1 << indice_canal;
                    }
                    funcion_800CBB88(0x04000000 | ((sec_indice_jugador & 0xFF) << 0x10) | (((u32) indice_canal & 0xFF) << 8),
                                  dato_801930D0[sec_indice_jugador].desconocido_044[indice_canal].desconocido_10);
                }
            }
        }
        if (dato_801930D0[sec_indice_jugador].desconocido_041) {
#ifdef VERSION_EU
            if (func_800C357C_eu(-0x10000000, -0x10000000) == 0) {
                dato_801930D0[sec_indice_jugador].desconocido_041 = 0;
                return;
            }
#endif
            if (dato_801930D0[sec_indice_jugador].desconocido_040 != 0) {
                dato_801930D0[sec_indice_jugador].desconocido_040--;
                continue;
            }

            if (jugadores_secuencia[sec_indice_jugador].activado != 0) {
                continue;
            }

            for (j = 0; j < dato_801930D0[sec_indice_jugador].desconocido_041; j++) {
                preparar_op = (dato_801930D0[sec_indice_jugador].desconocido_02C[j] & 0xF00000) >> 0x14;
                objetivo_sec_jugador_indice = (dato_801930D0[sec_indice_jugador].desconocido_02C[j] & 0xF0000) >> 0x10;
                preparar_val_2 = (dato_801930D0[sec_indice_jugador].desconocido_02C[j] & 0xFF00) >> 8;
                preparar_val_1 = dato_801930D0[sec_indice_jugador].desconocido_02C[j] & 0xFF;
                switch (preparar_op) {
                    case 0:
                        dato_801930D0[objetivo_sec_jugador_indice].desconocido_012 = 1;
                        dato_801930D0[objetivo_sec_jugador_indice].desconocido_00E[1] = 0x7F;
                        break;

                    case 1:
                        funcion_800C3448(0x30000000 | ((u8) sec_indice_jugador) << 0x18 |
                                      (dato_801930D0[sec_indice_jugador].desconocido_248));
                        break;

                    case 2:
                        funcion_800C3448((((u8) objetivo_sec_jugador_indice) << 0x18) | 0x10000 |
                                      (u16) (dato_801930D0[objetivo_sec_jugador_indice].desconocido_248));
                        dato_801930D0[objetivo_sec_jugador_indice].desconocido_012 = 1;
                        dato_801930D0[objetivo_sec_jugador_indice].desconocido_00E[1] = 0x7F;
                        break;

                    case 3:
                        funcion_800C3448(0xB0003000 | (((u8) objetivo_sec_jugador_indice) << 0x18) | (((u8) preparar_val_2) << 0x10) |
                                      (u16) preparar_val_1);
                        break;

                    case 4:
                        funcion_800C3448(0xB0004000 | (((u8) objetivo_sec_jugador_indice) << 0x18) | (((u8) preparar_val_1) << 0x10));
                        break;

                    case 5:
                        sec_id = dato_801930D0[sec_indice_jugador].desconocido_02C[j] & 0xFFFF;
                        funcion_800C3448((((u8) objetivo_sec_jugador_indice) << 0x18) |
                                      (((u8) dato_801930D0[objetivo_sec_jugador_indice].desconocido_042) << 0x10) | ((u16) sec_id));

                        funcion_800C36C4(objetivo_sec_jugador_indice, 1, 0x7F, 0);
                        dato_801930D0[objetivo_sec_jugador_indice].desconocido_042 = 0;
                        break;

                    case 6:
                        dato_801930D0[sec_indice_jugador].desconocido_042 = preparar_val_2;
                        break;
                }
            }

            dato_801930D0[sec_indice_jugador].desconocido_041 = 0;
        }
    }
}

void funcion_800C3F70(void) {
    u8 variable_v0;

    for (variable_v0 = 0; variable_v0 < 3; variable_v0++) {
        dato_80192CC6[variable_v0] = 0;
        dato_801930D0[variable_v0].desconocido_248 = 0xFFFF;
        dato_801930D0[variable_v0].desconocido_000 = 1.0f;
        dato_801930D0[variable_v0].desconocido_00C = 0;
        dato_801930D0[variable_v0].desconocido_028 = 0;
        dato_801930D0[variable_v0].desconocido_018 = 0;
        dato_801930D0[variable_v0].desconocido_014 = 0;
        dato_801930D0[variable_v0].desconocido_24A = 0;
        dato_801930D0[variable_v0].desconocido_041 = 0;
        dato_801930D0[variable_v0].desconocido_042 = 0;
        dato_801930D0[variable_v0].desconocido_012 = 0;
        dato_801930D0[variable_v0].desconocido_00E[0] = 0x7F;
        dato_801930D0[variable_v0].desconocido_00E[1] = 0x7F;
        dato_801930D0[variable_v0].desconocido_00E[2] = 0x7F;
        dato_801930D0[variable_v0].desconocido_244 = 0;
        dato_801930D0[variable_v0].desconocido_246 = 0;
    }
}

void funcion_800C400C(void) {
    u8 variable_v0;

    for (variable_v0 = 0; variable_v0 < 3; variable_v0++) {
        dato_80192CC6[variable_v0] = 0;
        dato_801930D0[variable_v0].desconocido_248 = 0xFFFF;
        dato_801930D0[variable_v0].desconocido_028 = 0;
        dato_801930D0[variable_v0].desconocido_018 = 0;
        dato_801930D0[variable_v0].desconocido_014 = 0;
        dato_801930D0[variable_v0].desconocido_24A = 0;
        dato_801930D0[variable_v0].desconocido_041 = 0;
        dato_801930D0[variable_v0].desconocido_042 = 0;
        dato_801930D0[variable_v0].desconocido_244 = 0;
        dato_801930D0[variable_v0].desconocido_246 = 0;
    }
}

void funcion_800C4084(u16 mascara_banco) {
    u8 banco;

    for (banco = 0; banco < SONIDO_CANTIDAD_BANCO; banco++) {
        if (mascara_banco & 1) {
            sonido_banco_desactivado[banco] = true;
        } else {
            sonido_banco_desactivado[banco] = false;
        }
        mascara_banco = mascara_banco >> 1;
    }
}

void funcion_800C40F0(u8 parametro0) {
    dato_800EA1C4 &= ((1 << (parametro0)) ^ (u16) -1);
    if (!dato_800EA1C4) {
        dato_801930D0[0].desconocido_012 = 1;
        dato_801930D0[0].desconocido_00E[2] = 0x7F;
    }
}

void reproducir_sonido(u32 sonido_bits, Vec3f* posicion, u8 id_camara, f32* parametro3, f32* parametro4, s8* parametro5) {
    u8 banco;
    struct Sonido* temporal_v0;

    banco = sonido_bits >> 0x1C;
    if (sonido_banco_desactivado[banco] == false) {
        temporal_v0 = &sonido_pedidos[sonido_cantidad_pedido];
        temporal_v0->sonido_bits = sonido_bits;
        temporal_v0->position = posicion;
        temporal_v0->id_camara = id_camara;
        temporal_v0->desconocido_0c = parametro3;
        temporal_v0->unk10 = parametro4;
        temporal_v0->unk14 = parametro5;
        sonido_cantidad_pedido += 1;
    }
}

void funcion_800C41CC(u8 parametro0, struct SonidoCaracteristicas* parametro1) {
    s32 encontrado;
    u8 sonido_id;
    struct Sonido* sonido;

    for (sonido_id = num_procesado_sonido_pedidos; sonido_id != sonido_cantidad_pedido; sonido_id++) {
        encontrado = false;
        sonido = &sonido_pedidos[sonido_id];
        switch (parametro0) {
            case 0:
                if ((sonido->sonido_bits & 0xF0000000) == (parametro1->sonido_bits & 0xF0000000)) {
                    encontrado = true;
                }
                break;
            case 1:
                if (((sonido->sonido_bits & 0xF0000000) == (parametro1->sonido_bits & 0xF0000000)) &&
                    (sonido->position == parametro1->unk00)) {
                    encontrado = true;
                }
                break;
            case 2:
                if (sonido->position == parametro1->unk00) {
                    encontrado = true;
                }
                break;
            case 3:
                if ((sonido->position == parametro1->unk00) && (sonido->sonido_bits == parametro1->sonido_bits)) {
                    encontrado = true;
                }
                break;
            case 4:
                if ((sonido->id_camara == parametro1->id_camara) && (sonido->sonido_bits == parametro1->sonido_bits)) {
                    encontrado = true;
                }
                break;
            case 5:
                if (sonido->sonido_bits == parametro1->sonido_bits) {
                    encontrado = true;
                }
                break;
        }
        if (encontrado) {
            sonido->sonido_bits = 0;
            if (*sonido->position != dato_800EA1C8) {
                (*sonido->position)[1] = 100000.0f;
            }
        }
    }
}

void funcion_800C4398(void) {
    u8 banco;
    u8 sonido_indice;
    u8 variable_a3;
    struct Sonido* variable_a2;
    SIN_USO s32 relleno;
    u8 variable_t2;
    u32 variable_t3;

    variable_a2 = &sonido_pedidos[num_procesado_sonido_pedidos];
    if (variable_a2->sonido_bits == 0) {
        return;
    }

    banco = ((u32) (variable_a2->sonido_bits & 0xF0000000) >> 0x1C);
    sonido_indice = sonido_bancos[banco][0].next;
    variable_a3 = 0;
    while ((sonido_indice != 0xFF) && (sonido_indice != 0)) {
        if (variable_a2->position == sonido_bancos[banco][sonido_indice].unk00) {
            if (variable_a2->sonido_bits == sonido_bancos[banco][sonido_indice].sonido_bits) {
                variable_a3 = dato_800EA1A0[dato_800EA1C0][banco];
            } else {
                if (variable_a3 == 0) {
                    variable_t2 = sonido_indice;
                    variable_t3 = sonido_bancos[banco][sonido_indice].sonido_bits;
                } else if ((u32) (sonido_bancos[banco][sonido_indice].sonido_bits & 0xFF00) < (u32) (variable_t3 & 0xFF00)) {
                    variable_t2 = sonido_indice;
                    variable_t3 = sonido_bancos[banco][sonido_indice].sonido_bits;
                }
                variable_a3++;
                if (variable_a3 == dato_800EA1A0[dato_800EA1C0][banco]) {
                    if ((u32) (variable_a2->sonido_bits & 0xFF00) >= (u32) (variable_t3 & 0xFF00)) {
                        sonido_indice = variable_t2;
                    } else {
                        sonido_indice = 0;
                    }
                }
            }
            if (variable_a3 == dato_800EA1A0[dato_800EA1C0][banco]) {
                if ((variable_a2->sonido_bits & 0x08000000) || (variable_a2->sonido_bits & 0x40000) || (sonido_indice == variable_t2)) {
                    if ((sonido_bancos[banco][sonido_indice].sonido_bits & 0x80000) &&
                        (sonido_bancos[banco][sonido_indice].sonido_situacion != 1)) {
                        funcion_800C40F0(sonido_bancos[banco][sonido_indice].desconocido_2c);
                    }
                    sonido_bancos[banco][sonido_indice].id_camara = variable_a2->id_camara;
                    sonido_bancos[banco][sonido_indice].sonido_bits = variable_a2->sonido_bits;
                    sonido_bancos[banco][sonido_indice].sonido_situacion = ((variable_a2->sonido_bits & 0x01000000) >> 0x18);
                    sonido_bancos[banco][sonido_indice].frescura = 2;
                    sonido_bancos[banco][sonido_indice].unk10 = variable_a2->desconocido_0c;
                    sonido_bancos[banco][sonido_indice].unk14 = variable_a2->unk10;
                    sonido_bancos[banco][sonido_indice].unk18 = variable_a2->unk14;
                }
                sonido_indice = 0;
            }
        }
        if (sonido_indice != 0) {
            sonido_indice = sonido_bancos[banco][sonido_indice].next;
        }
    }
    if ((sonido_bancos[banco][sonido_banco_libre_lista_frente[banco]].next != 0xFF) && (sonido_indice != 0)) {
        variable_t2 = sonido_indice = sonido_banco_libre_lista_frente[banco];
        sonido_bancos[banco][sonido_indice].unk00 = (Vec3f*) &(*variable_a2->position)[0];
        sonido_bancos[banco][sonido_indice].desconocido04 = &(*variable_a2->position)[1];
        sonido_bancos[banco][sonido_indice].desconocido08 = &(*variable_a2->position)[2];
        sonido_bancos[banco][sonido_indice].id_camara = variable_a2->id_camara;
        sonido_bancos[banco][sonido_indice].unk10 = variable_a2->desconocido_0c;
        sonido_bancos[banco][sonido_indice].unk14 = variable_a2->unk10;
        sonido_bancos[banco][sonido_indice].unk18 = variable_a2->unk14;
        sonido_bancos[banco][sonido_indice].sonido_bits = variable_a2->sonido_bits;
        sonido_bancos[banco][sonido_indice].sonido_situacion = (u8) ((u32) (variable_a2->sonido_bits & 0x01000000) >> 0x18);
        sonido_bancos[banco][sonido_indice].frescura = 2;
        sonido_bancos[banco][sonido_indice].prev = sonido_banco_usado_lista_atras[banco];
        sonido_bancos[banco][sonido_banco_usado_lista_atras[banco]].next = sonido_banco_libre_lista_frente[banco];
        sonido_banco_usado_lista_atras[banco] = sonido_banco_libre_lista_frente[banco];
        sonido_banco_libre_lista_frente[banco] = sonido_bancos[banco][sonido_banco_libre_lista_frente[banco]].next;
        sonido_bancos[banco][sonido_banco_libre_lista_frente[banco]].prev = 0xFF;
        sonido_bancos[banco][variable_t2].next = 0xFF;
    } else if (sonido_bancos[banco][sonido_banco_libre_lista_frente[banco]].next == 0xFF) {
        if (dato_800EA1C8 != *variable_a2->position) {
            (*variable_a2->position)[1] = 100000.0f;
        }
    }
}

void eliminar_sonido_desde_banco(u8 id_banco, u8 sonido_id) {
    SIN_USO s32 margen_pila;
    struct SonidoCaracteristicas* temporal_ = &sonido_bancos[id_banco][sonido_id];
    if (*temporal_->unk00 != dato_800EA1C8) {
        *temporal_->desconocido04 = 100000.0f;
    }
    if (temporal_->sonido_bits & 0x80000) {
        funcion_800C40F0(temporal_->desconocido_2c);
    }
    if (sonido_id == sonido_banco_usado_lista_atras[id_banco]) {
        sonido_banco_usado_lista_atras[id_banco] = temporal_->prev;
    } else {
        sonido_bancos[id_banco][temporal_->next].prev = temporal_->prev;
    }
    sonido_bancos[id_banco][temporal_->prev].next = temporal_->next;
    temporal_->next = sonido_banco_libre_lista_frente[id_banco];
    temporal_->prev = 0xFF;
    sonido_bancos[id_banco][sonido_banco_libre_lista_frente[id_banco]].prev = sonido_id;
    sonido_banco_libre_lista_frente[id_banco] = sonido_id;
    temporal_->sonido_situacion = 0;
}

struct SfxActivo {
    u32 priority;
    u8 sonido_indice;
};
#define AUDIO_MK_CMD(b0, b1, b2, b3) \
    ((((b0) & 0xFF) << 0x18) | (((b1) & 0xFF) << 0x10) | (((b2) & 0xFF) << 0x8) | (((b3) & 0xFF) << 0))
void funcion_800C4888(u8 id_banco) {
    u8 j;
    u8 canales_num;
    u8 indice_entrada_elegido;
    u8 i;
    u8 k;
    u8 sfx_elegido_num;
    u8 necesitar_sfx_nuevo;
    u8 sonido_indice;
    u8 prioridad_pedido;
    u8 temporal_t8;
    f32 variable_f0;
    struct SfxActivo* sfx_activo;
    struct SfxActivo sfx_elegido[8];
    struct SonidoCaracteristicas* entry;

    sfx_elegido_num = 0;
    for (i = 0; i < 8; i++) {
        sfx_elegido[i].priority = 0x7FFFFFFF;
        sfx_elegido[i].sonido_indice = 0xFF;
    }

    sonido_indice = sonido_bancos[id_banco][0].next;
    k = 0;
    while (sonido_indice != 0xFF) {
        if ((sonido_bancos[id_banco][sonido_indice].sonido_situacion == 1) &&
            ((sonido_bancos[id_banco][sonido_indice].sonido_bits & 0x08000000) == 0x08000000)) {
            sonido_bancos[id_banco][sonido_indice].frescura -= 1;
        }

        if (sonido_bancos[id_banco][sonido_indice].frescura == 0) {
            eliminar_sonido_desde_banco(id_banco, sonido_indice);
        } else if (sonido_bancos[id_banco][sonido_indice].sonido_situacion != 0) {
            entry = &sonido_bancos[id_banco][sonido_indice];

            if (&dato_800EA1C8 == entry[0].unk00) {
                entry->distancia = 0.0f;
            } else {
                entry->distancia = (*entry->unk00[0] * *entry->unk00[0]) + (*entry->desconocido08 * *entry->desconocido08);
            }
            prioridad_pedido = (((u32) (entry->sonido_bits & 0xFF00)) >> 8);
            if (entry->sonido_bits & 0x100000) {
                entry->priority = ((0xFF - prioridad_pedido) * (0xFF - prioridad_pedido)) * (38 * 38);
            } else {
                entry->priority =
                    ((u32) entry->distancia) + (((0xFF - prioridad_pedido) * (0xFF - prioridad_pedido)) * (38 * 38));

                if ((*entry->desconocido08) > 0.0f) {
                    entry->priority += (s32) ((*entry->desconocido08) * 6.0f);
                }
            }
            temporal_t8 = (((u32) (entry->sonido_bits & 0x30000)) >> 0x10);
            if (temporal_t8) {
                variable_f0 = (2000.0f * 2000.0f) / ((f32) (temporal_t8 * temporal_t8));
            } else {
                variable_f0 = 1e5f * 1e5f;
            }
            if (variable_f0 < entry->distancia) {
                if (entry->sonido_situacion == 4) {
                    funcion_800CBBE8(AUDIO_MK_CMD(0x06, 2, entry->desconocido_2c, 0), 0);
                    if (entry->sonido_bits & 0x08000000) {
                        eliminar_sonido_desde_banco(id_banco, sonido_indice);
                        sonido_indice = k;
                    }
                }
            } else {
                canales_num = dato_800EA188[dato_800EA1C0][id_banco];
                for (i = 0; i < canales_num; i++) {
                    if (sfx_elegido[i].priority >= entry->priority) {
                        if (sfx_elegido_num < dato_800EA188[dato_800EA1C0][id_banco]) {
                            sfx_elegido_num++;
                        }
                        for (j = canales_num - 1; j > i; j--) {
                            sfx_elegido[j].priority = sfx_elegido[j - 1].priority;
                            sfx_elegido[j].sonido_indice = sfx_elegido[j - 1].sonido_indice;
                        }

                        sfx_elegido[i].priority = entry->priority;
                        sfx_elegido[i].sonido_indice = sonido_indice;
                        i = canales_num;
                    }
                }
            }
            k = sonido_indice;
        }
        sonido_indice = sonido_bancos[id_banco][k].next;
    }

    canales_num = dato_800EA188[dato_800EA1C0][id_banco];
    for (i = 0; i < sfx_elegido_num; i++) {
        if (sonido_bancos[id_banco][sfx_elegido[i].sonido_indice].sonido_situacion == 1) {
            sonido_bancos[id_banco][sfx_elegido[i].sonido_indice].sonido_situacion = 2;
        } else if (sonido_bancos[id_banco][sfx_elegido[i].sonido_indice].sonido_situacion == 4) {
            sonido_bancos[id_banco][sfx_elegido[i].sonido_indice].sonido_situacion = 3;
        }
    }

    for (i = 0; i < canales_num; i++) {
        necesitar_sfx_nuevo = false;
        sfx_activo = (struct SfxActivo*) &dato_80192AB8[id_banco][i];

        if (sfx_activo->sonido_indice == 0xFF) {
            necesitar_sfx_nuevo = true;
        } else {
            entry = &sonido_bancos[id_banco][sfx_activo->sonido_indice];
            if (entry->sonido_situacion == 4) {
                if (entry->sonido_bits & 0x08000000) {
                    eliminar_sonido_desde_banco(id_banco, sfx_activo->sonido_indice);
                } else {
                    entry->sonido_situacion = 1;
                }
                necesitar_sfx_nuevo = true;
            } else if (entry->sonido_situacion == 0) {
                sfx_activo->sonido_indice = 0xFF;
                necesitar_sfx_nuevo = true;
            } else {
                for (j = 0; j < canales_num; j++) {
                    if (sfx_activo->sonido_indice == sfx_elegido[j].sonido_indice) {
                        sfx_elegido[j].sonido_indice = 0xFF;
                        j = canales_num;
                    }
                }
                sfx_elegido_num--;
            }
        }

        if (necesitar_sfx_nuevo == true) {
            for (j = 0; j < canales_num; j++) {
                indice_entrada_elegido = sfx_elegido[j].sonido_indice;
                if ((indice_entrada_elegido != 0xFF) && (sonido_bancos[id_banco][indice_entrada_elegido].sonido_situacion != 3)) {
                    for (k = 0; k < canales_num; k++) {
                        if (indice_entrada_elegido == ((struct SfxActivo*) (dato_80192AB8[id_banco]))[k].sonido_indice) {
                            necesitar_sfx_nuevo = false;
                            k = canales_num;
                        }
                    }

                    if (necesitar_sfx_nuevo == true) {
                        sfx_activo->sonido_indice = indice_entrada_elegido;
                        sfx_elegido[j].sonido_indice = 0xFF;
                        j = canales_num + 1;
                        sfx_elegido_num--;
                    }
                }
            }

            if (j == canales_num) {
                sfx_activo->sonido_indice = 0xFF;
            }
        }
    }
}

void funcion_800C4FE4(u8 id_banco) {
    u8 sonido_id;
    u8 variable_s4;
    SIN_USO u32 cmd;
    struct SonidoCaracteristicas* temporal_s0;
    struct CanalSecuencia* cosa;

    for (variable_s4 = 0; variable_s4 < dato_800EA188[dato_800EA1C0][id_banco]; variable_s4++) {
        sonido_id = dato_80192AB8[id_banco][variable_s4][4];
        if (sonido_id != 0xFF) {
            temporal_s0 = &sonido_bancos[id_banco][sonido_id];
            cosa = jugadores_secuencia[2].channels[dato_80192C38];
            if (temporal_s0->sonido_situacion == 2) {
                temporal_s0->desconocido_2c = dato_80192C38;
                if (temporal_s0->sonido_bits & 0x80000) {
                    dato_800EA1C4 |= 1 << dato_80192C38;
                    dato_801930D0->desconocido_012 = 1;
                    dato_801930D0->desconocido_00E[2] = 0x28;
                }
                funcion_800C19D0(id_banco, sonido_id, dato_80192C38);
                funcion_800CBBE8(((dato_80192C38 & 0xFF) << 8) | 0x06020000, 1);
                funcion_800CBBE8(((dato_80192C38 & 0xFF) << 8) | 0x06020000 | 4, (u8) (temporal_s0->sonido_bits & 0xFF));
                temporal_s0->sonido_situacion = 4U;
            } else if (((u8) cosa->sonido_io_guion[7]) == 0x80) {
                funcion_800CBBE8(((dato_80192C38 & 0xFF) << 8) | 0x06020000 | 7, 0);
                eliminar_sonido_desde_banco(id_banco, sonido_id);
            } else if (temporal_s0->sonido_situacion == 3) {
                funcion_800C19D0(id_banco, sonido_id, dato_80192C38);
                temporal_s0->sonido_situacion = 4U;
            }
        }
        dato_80192C38 += 1;
    }
}

void funcion_800C5278(u8 id_banco) {
    SIN_USO s32 margen_pila_0;
    u8 sonido_id;
    struct SonidoCaracteristicas sp60;

    sonido_id = sonido_bancos[id_banco][0].next;
    while (sonido_id != 0xFF) {
        if (sonido_bancos[id_banco][sonido_id].sonido_situacion >= 3) {
            funcion_800CBBE8(((sonido_bancos[id_banco][sonido_id].desconocido_2c & 0xff) << 8) | 0x06020000, 0);
        }
        if (sonido_bancos[id_banco][sonido_id].sonido_situacion != 0) {
            eliminar_sonido_desde_banco(id_banco, sonido_id);
        }
        sonido_id = sonido_bancos[id_banco][0].next;
    }
    sp60.sonido_bits = id_banco << 0x1C;
    funcion_800C41CC(0, &sp60);
}

void funcion_800C5384(u8 parametro0, Vec3f* parametro1) {
    u8 act;
    u8 siguiente;

    act = 0;
    siguiente = sonido_bancos[parametro0][0].next;

    while (siguiente != 0xff) {
        if (*parametro1 == *sonido_bancos[parametro0][siguiente].unk00) {
            if (sonido_bancos[parametro0][siguiente].sonido_situacion >= 3) {
                funcion_800CBBE8((0x06020000 | ((sonido_bancos[parametro0][siguiente].desconocido_2c & 0xff) << 8)), 0);
            }

            if (sonido_bancos[parametro0][siguiente].sonido_situacion != 0) {
                eliminar_sonido_desde_banco(parametro0, siguiente);
            }
        } else {
            act = siguiente;
        }

        siguiente = sonido_bancos[parametro0][act].next;
    }
}

void funcion_800C54B8(u8 parametro0, Vec3f* parametro1) {
    struct SonidoCaracteristicas desconocido;
    funcion_800C5384(parametro0, parametro1);
    desconocido.sonido_bits = parametro0 << 0x1C;
    desconocido.unk00 = parametro1;
    funcion_800C41CC(1, &desconocido);
}

void funcion_800C550C(Vec3f* parametro0) {
    u8 i;
    struct SonidoCaracteristicas sp3_c;

    for (i = 0; i < 6; i++) {
        funcion_800C5384(i, parametro0);
    }

    sp3_c.unk00 = parametro0;
    funcion_800C41CC(2, &sp3_c);
}

void funcion_800C5578(Vec3f* parametro0, u32 sonido_bits) {
    SIN_USO s32 margen_pila_0;
    u8 id_banco;
    u8 siguiente;
    u8 act;
    struct SonidoCaracteristicas sp60;

    id_banco = (sonido_bits & 0xF0000000) >> 0x1C;
    siguiente = sonido_bancos[id_banco][0].next;
    act = 0;
    while (siguiente != 0xFF) {
        if ((parametro0 == sonido_bancos[id_banco][siguiente].unk00) && (sonido_bits == sonido_bancos[id_banco][siguiente].sonido_bits)) {
            if (sonido_bancos[id_banco][siguiente].sonido_situacion >= 3) {
                funcion_800CBBE8(((sonido_bancos[id_banco][siguiente].desconocido_2c & 0xff) << 8) | 0x06020000, 0);
            }
            if (sonido_bancos[id_banco][siguiente].sonido_situacion != 0) {
                eliminar_sonido_desde_banco(id_banco, siguiente);
            }
            siguiente = 0xFF;
        } else {
            act = siguiente;
        }
        if (siguiente != 0xFF) {
            siguiente = sonido_bancos[id_banco][act].next;
        }
    }
    sp60.unk00 = parametro0;
    sp60.sonido_bits = sonido_bits;
    funcion_800C41CC(3, &sp60);
}

void funcion_800C56F0(u32 sonido_bits) {
    SIN_USO s32 margen_pila_0;
    u8 id_banco;
    u8 siguiente;
    u8 act;
    struct SonidoCaracteristicas sp68;

    id_banco = (sonido_bits & 0xF0000000) >> 0x1C;
    siguiente = sonido_bancos[id_banco][0].next;
    act = 0;
    while (siguiente != 0xFF) {
        if (sonido_bits == sonido_bancos[id_banco][siguiente].sonido_bits) {
            if (sonido_bancos[id_banco][siguiente].sonido_situacion >= 3) {
                funcion_800CBBE8(((sonido_bancos[id_banco][siguiente].desconocido_2c & 0xff) << 8) | 0x06020000, 0);
            }
            if (sonido_bancos[id_banco][siguiente].sonido_situacion != 0) {
                eliminar_sonido_desde_banco(id_banco, siguiente);
            }
        } else {
            act = siguiente;
        }
        siguiente = sonido_bancos[id_banco][act].next;
    }
    sp68.sonido_bits = sonido_bits;
    funcion_800C41CC(5, &sp68);
}

void funcion_800C5848(void) {
    while (sonido_cantidad_pedido != num_procesado_sonido_pedidos) {
        funcion_800C4398();
        num_procesado_sonido_pedidos++;
    }
}

void escalar_volumen_canal_fundido(u8 jugador, u8 escala_objetivo, u16 fundir_duracion) {
    struct CanalVolumenEscalaFundido* temporal_v0;

    if (fundir_duracion == 0) {
        fundir_duracion++;
    }
    temporal_v0 = &dato_80192C48[jugador];
    temporal_v0->target = escala_objetivo / FLOTANTE_US(127.0);
    temporal_v0->frames_restante = fundir_duracion;
    temporal_v0->velocidad = (temporal_v0->current - temporal_v0->target) / fundir_duracion;
}

void funcion_800C5968(u8 parametro0) {
    struct CanalVolumenEscalaFundido* temporal_v0;

    temporal_v0 = &dato_80192C48[parametro0];
    if (temporal_v0->frames_restante != 0) {
        temporal_v0->frames_restante--;
        if (temporal_v0->frames_restante != 0) {
            temporal_v0->current -= temporal_v0->velocidad;
        } else {
            temporal_v0->current = temporal_v0->target;
        }
    }
}

void funcion_800C59C4(void) {
    u8 i;

    if (jugadores_secuencia[2].channels[0] != &ninguno_canal_secuencia) {
        dato_80192C38 = 0;
        for (i = 0; i < 6; i++) {
            funcion_800C4888(i);
            funcion_800C4FE4(i);
            funcion_800C5968(i);
        }
    }
}

void sonido_inicializacion(void) {
    u8 variable_v0;
    u8 variable_v1;

    sonido_cantidad_pedido = 0;
    num_procesado_sonido_pedidos = 0;
    dato_800EA1C4 = 0;
    for (variable_v0 = 0; variable_v0 < SONIDO_CANTIDAD_BANCO; variable_v0++) {
        sonido_banco_usado_lista_atras[variable_v0] = 0;
        sonido_banco_libre_lista_frente[variable_v0] = 1;
        sonidos_num_en_banco[variable_v0] = 0;
        sonido_banco_desactivado[variable_v0] = false;
        dato_80192C48[variable_v0].current = 1.0f;
        dato_80192C48[variable_v0].frames_restante = 0;
    }
    for (variable_v0 = 0; variable_v0 < 6; variable_v0++) {
        for (variable_v1 = 0; variable_v1 < 8; variable_v1++) {
            dato_80192AB8[variable_v0][variable_v1][4] = 0xFF;
        }
    }
    for (variable_v0 = 0; variable_v0 < 6; variable_v0++) {
        sonido_bancos[variable_v0][0].prev = 0xFF;
        sonido_bancos[variable_v0][0].next = 0xFF;
        for (variable_v1 = 1; variable_v1 < 19; variable_v1++) {
            sonido_bancos[variable_v0][variable_v1].prev = variable_v1 - 1;
            sonido_bancos[variable_v0][variable_v1].next = variable_v1 + 1;
        }
        sonido_bancos[variable_v0][variable_v1].prev = variable_v1 - 1;
        sonido_bancos[variable_v0][variable_v1].next = 0xFF;
    }
}

void funcion_800C5BD0(void) {
    if (dato_800EA1C0 == 0) {
        funcion_800CBBE8(((dato_800EA154[jugadores[0].id_personaje] & 0xFFFF) << 8) | 0xF3000000, 0);
    } else {
        funcion_800CBBE8(0xF3004D00, 0);
    }
}

void funcion_800C5C40(void) {
    funcion_800C2474();
    if (dato_800E9DA0 != 0) {
        funcion_800C400C();
    } else {
        dato_800E9DA0++;
        funcion_800C3F70();
    }
    sonido_inicializacion();
    funcion_800C284C(2, 0, 0xFF, 1);
    funcion_800C5BD0();
}
