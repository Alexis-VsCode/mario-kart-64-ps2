// Secuencias musica

void funcion_800C86D8(u8 id_jugador) {
    if (((jugadores[id_jugador].efectos & EFECTO_RAYO) != EFECTO_RAYO) && (dato_800E9F24[id_jugador] == 1)) {
        funcion_800C90F4(id_jugador, (jugadores[id_jugador].id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x08));
    }
}

void funcion_800C8770(u8 id_jugador) {
    if ((jugadores[id_jugador].efectos & EFECTO_RAYO) == EFECTO_RAYO) {
        dato_800E9F24[id_jugador] = 1;
        if (dato_800E9F2C[id_jugador] < 0xFA) {
            dato_800E9F2C[id_jugador]++;
        }
    } else {
        dato_800E9F2C[id_jugador] = 0;
        if (dato_800E9F24[id_jugador] == 1) {
            dato_800E9F24[id_jugador] = 2;
        }
    }
    switch (dato_800E9F24[id_jugador]) { /* irregular */
        case 1:
            if (dato_800E9F34[id_jugador] < 0.7f) {
                dato_800E9F34[id_jugador] += 0.1f;
                dato_800E9F54[id_jugador] += 0.03f;
            }
            break;
        case 2:
            if (dato_800E9F34[id_jugador] > 0.16f) {
                dato_800E9F34[id_jugador] -= 0.15f;
                dato_800E9F54[id_jugador] -= 0.03f;
            } else {
                dato_800E9F34[id_jugador] = 0.0f;
                dato_800E9F54[id_jugador] = 0.0f;
                dato_800E9F24[id_jugador] = 0;
            }
            break;
    }
}

void funcion_800C8920(void) {
    if (((u8) dato_800EA168 != 0) && ((jugadores[0].efectos & EFECTO_RAYO) != EFECTO_RAYO) &&
        ((jugadores[1].efectos & EFECTO_RAYO) != EFECTO_RAYO) &&
        ((jugadores[2].efectos & EFECTO_RAYO) != EFECTO_RAYO) &&
        ((jugadores[3].efectos & EFECTO_RAYO) != EFECTO_RAYO) &&
        ((jugadores[4].efectos & EFECTO_RAYO) != EFECTO_RAYO) &&
        ((jugadores[5].efectos & EFECTO_RAYO) != EFECTO_RAYO) &&
        ((jugadores[6].efectos & EFECTO_RAYO) != EFECTO_RAYO) &&
        ((jugadores[7].efectos & EFECTO_RAYO) != EFECTO_RAYO)) {
        funcion_800CAC08();
    }
}

void funcion_800C89E4(void) {
    if (dato_800EA180 != 0) {
        dato_800EA180++;
        if (dato_800EA180 == 2) {
            dato_800EA17C = 1.0f;
        }
        if (dato_800EA180 < 0xF) {
            dato_800EA178 = 1.0f - (dato_800EA180 * 0.012f);
        }
        if ((dato_800EA180 >= 0x33) && (dato_800EA180 < 0x96)) {
            dato_800EA17C = 1.0f - ((dato_800EA180 - 0x32) / 110.0f);
        }
        if (dato_800EA180 == 0x12D) {
            dato_800EA17C = 0.0f;
        }
        if (dato_800EA180 == 0x321) {
            dato_800EA178 = 1.0f;
            dato_800EA17C = 0.85f;
            dato_800EA180 = 0;
        }
    }
}

void funcion_800C8AE4(void) {
    if (id_circuito_actual == CIRCUITO_LUIGI_RACEWAY) {
        if (dato_800EA184 != 0) {
            if ((u8) dato_800EA16C == 0) {
                dato_800EA184 += 1;
            }
            if (dato_800EA184 == 0x012C) {
                dato_800EA17C = 0.85f;
                dato_800EA184 = 0;
            }
        } else {
            switch (dato_800EA1C0) { /* irregular */
                case 0:
                    if (dato_800E9F7C[0].desconocido_14 != 0) {
                        dato_800EA17C = 0.0f;
                        dato_800EA184 = 1;
                    }
                    break;
                case 1:
                    if ((dato_800E9F7C[0].desconocido_14 != 0) || (dato_800E9F7C[1].desconocido_14 != 0)) {
                        dato_800EA17C = 0.0f;
                        dato_800EA184 = 1;
                    }
                    break;
                case 2:
                    if ((dato_800E9F7C[0].desconocido_14 != 0) || (dato_800E9F7C[1].desconocido_14 != 0) || (dato_800E9F7C[2].desconocido_14 != 0)) {
                        dato_800EA17C = 0.0f;
                        dato_800EA184 = 1;
                    }
                    break;
                case 3:
                    if ((dato_800E9F7C[0].desconocido_14 != 0) || (dato_800E9F7C[1].desconocido_14 != 0) || (dato_800E9F7C[2].desconocido_14 != 0) ||
                        (dato_800E9F7C[3].desconocido_14 != 0)) {
                        dato_800EA17C = 0.0f;
                        dato_800EA184 = 1;
                    }
                    break;
            }
        }
    }
}

void funcion_800C8C7C(u8 parametro0) {
    dato_800EA06C[parametro0].unk00[2] = (1.0f - dato_800E9F54[parametro0]) - dato_800EA130[parametro0];
}

void funcion_800C8CCC() {
    u8 variable_s0;

    for (variable_s0 = 0; variable_s0 < dato_800EA1C0 + 1; variable_s0++) {
        funcion_800C5D04(variable_s0);
        funcion_800C5E38(variable_s0);
        funcion_800C6108(variable_s0);
        funcion_800C64A0(variable_s0);
        funcion_800C6758(variable_s0);
        funcion_800C683C(variable_s0);
        funcion_800C70A8(variable_s0);
        funcion_800C76C0(variable_s0);
        funcion_800C847C(variable_s0);
        funcion_800C86D8(variable_s0);
    }
    if (seleccion_modo == GRAN_PREMIO) {
        for (variable_s0 = 0; variable_s0 < 8; variable_s0++) {
            funcion_800C8770(variable_s0);
            funcion_800C8C7C(variable_s0);
        }
    } else {
        for (variable_s0 = 0; variable_s0 < dato_800EA1C0 + 1; variable_s0++) {
            funcion_800C8770(variable_s0);
            funcion_800C8C7C(variable_s0);
        }
    }
    funcion_800C8920();
    funcion_800C89E4();
    funcion_800C8AE4();
}

void reproducir_sonido2(s32 sonido_bits) {
    if ((sonido_bits == SONIDO_MOTOR_REV_ACCION) && (id_circuito_actual == CIRCUITO_DK_JUNGLE)) {
        sonido_bits = SONIDO_CARGA_PARAMETRO(0x49, 0x00, 0x80, 0x27);
    }

    if ((sonido_bits == SONIDO_MOTOR_REV_ACCION_2) && (id_circuito_actual == CIRCUITO_DK_JUNGLE)) {
        sonido_bits = SONIDO_CARGA_PARAMETRO(0x49, 0x00, 0x80, 0x28);
    }
    reproducir_sonido(sonido_bits, &dato_800EA1C8, 4, &dato_800EA1D4, &dato_800EA1D4, &dato_800EA1DC);
}

void reproducir_secuencia(u16 index) {
    funcion_800C3448(index | 0x0010000);
    dato_800EA15C = index;
}

void reproducir_secuencia2(u16 index) {
    funcion_800C3448(index | 0x1010000);
    dato_800EA160 = index;
}

void funcion_800C8F44(u8 parametro0) {
    funcion_800C36C4(0, 0, parametro0, 1);
}

void funcion_800C8F80(u8 parametro0, u32 sonido_bits) {
    if (dato_800EA108 == 0) {
        switch (dato_800EA0EC[parametro0]) {
            case 2:
                dato_800EA0EC[parametro0] = 1;
            case 0:
                reproducir_sonido(sonido_bits, &dato_800E9F7C[parametro0].pos, parametro0, &dato_800EA1D4, &dato_800EA1D4, &dato_800EA1DC);
                break;
        }
    }
}

void funcion_800C9018(u8 indice_jugador, u32 sonido_bits) {
    funcion_800C5578(&dato_800E9F7C[indice_jugador].pos, sonido_bits);
}

void funcion_800C9060(u8 id_jugador, u32 sonido_bits) {
    if (dato_800EA108 == 0) {
        switch (dato_800EA0EC[id_jugador]) {
            case 2:
                dato_800EA0EC[id_jugador] = 1;
            case 0:
                reproducir_sonido(sonido_bits, &dato_800E9F7C[id_jugador].pos, id_jugador, &dato_800EA1D4, &dato_800EA1D4,
                           (s8*) &dato_800E9F7C[id_jugador].desconocido_14);
                break;
        }
    }
}

void funcion_800C90F4(u8 id_jugador, u32 sonido_bits) {
    if (dato_800EA108 == 0) {
        switch (dato_800EA0EC[id_jugador]) {
            case 2:
                dato_800EA0EC[id_jugador] = 1;
            case 0:
                if (((sonido_bits & ~0xF0) == SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x03)) ||
                    ((sonido_bits & ~0xF0) == SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x04)) ||
                    ((sonido_bits & ~0xF0) == SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x05))) {
                    dato_800EA180 = 1;
                }
                if (((jugadores[id_jugador].efectos & EFECTO_RAYO) == EFECTO_RAYO) &&
                    ((s32) dato_800E9F2C[id_jugador] >= 0x1F)) {
                    reproducir_sonido(sonido_bits, &dato_800E9F7C[id_jugador].pos, id_jugador, &dato_800EA150, &dato_800EA1D4,
                               (s8*) &dato_800E9F7C[id_jugador].desconocido_14);
                } else {
                    reproducir_sonido(sonido_bits, &dato_800E9F7C[id_jugador].pos, id_jugador, &dato_800EA1D4, &dato_800EA1D4,
                               (s8*) &dato_800E9F7C[id_jugador].desconocido_14);
                }
                break;
            default:
                break;
        }
    }
}

void funcion_800C9250(u8 indice_jugador) {
    funcion_800C90F4(indice_jugador, (jugadores[indice_jugador].id_personaje * 0x10) + (aleatorio_audio & 1) +
                                   SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x01));
}

void funcion_800C92CC(u8 id_jugador, u32 sonido_bits) {
    u8 variable_s0;
    struct desconocido_8018EFD8* temporal_v0;

    if ((dato_800EA108 == 0) && (dato_800EA0F0 == 0) && ((s32) dato_800EA1C0 < 2)) {
        for (variable_s0 = 0; variable_s0 < dato_800EA1C0 + 1; variable_s0++) {
            temporal_v0 = funcion_800C1C88(id_jugador, jugadores[id_jugador].pos, jugadores[id_jugador].velocidad, dato_800EA1C8,
                                    (u8) variable_s0, sonido_bits);
            if (temporal_v0 != NULL) {
                temporal_v0->unk34 = 170.0f;
                if (((jugadores[id_jugador].efectos & EFECTO_RAYO) == EFECTO_RAYO) &&
                    ((s32) dato_800E9F2C[id_jugador] >= 0x1F)) {
                    reproducir_sonido((jugadores[id_jugador].id_personaje * 0x10) + sonido_bits, &temporal_v0->unk18, variable_s0,
                               &dato_800EA150, &dato_800EA1D4, (s8*) &dato_800EA06C[id_jugador].desconocido_0c);
                } else {
                    reproducir_sonido((jugadores[id_jugador].id_personaje * 0x10) + sonido_bits, &temporal_v0->unk18, variable_s0,
                               &temporal_v0->desconocido_2c, &dato_800EA1D4, (s8*) &dato_800EA06C[id_jugador].desconocido_0c);
                }
            }
        }
    }
}

void funcion_800C94A4(u8 id_jugador) {
    u32 variable_a0;

    if (dato_800EA108 == 0) {
        switch (dato_800EA0EC[id_jugador]) {
            case 2:
                dato_800EA0EC[id_jugador] = 1;
            case 0:
                dato_800E9F7C[id_jugador].desconocido_0C = 1.0f;
                dato_800E9F7C[id_jugador].desconocido_10 = 0.0f;
                switch (jugadores[id_jugador].id_personaje) {
                    case 0:
                    case 1:
                        dato_800E9F7C[id_jugador].desconocido_18 = 2.8f;
                        dato_800E9F7C[id_jugador].desconocido_1C = 3844.0f;
                        dato_800E9F7C[id_jugador].desconocido_20 = 0.35f;
                        dato_800E9F7C[id_jugador].desconocido_24 = -0.8f;
                        dato_800E9F7C[id_jugador].desconocido_28 = 0.35f;
                        dato_800E9F7C[id_jugador].desconocido_2C = 1568.9796f;
                        dato_800E9F7C[id_jugador].desconocido_30 = 1067.7778f;
                        dato_800E9F7C[id_jugador].desconocido_34 = 2766.065f;
                        break;
                    case 2:
                    case 6:
                        dato_800E9F7C[id_jugador].desconocido_18 = 3.2f;
                        dato_800E9F7C[id_jugador].desconocido_1C = 3844.0f;
                        dato_800E9F7C[id_jugador].desconocido_20 = 0.6f;
                        dato_800E9F7C[id_jugador].desconocido_24 = -1.7f;
                        dato_800E9F7C[id_jugador].desconocido_28 = 0.6f;
                        dato_800E9F7C[id_jugador].desconocido_2C = 1478.4615f;
                        dato_800E9F7C[id_jugador].desconocido_30 = 784.4898f;
                        dato_800E9F7C[id_jugador].desconocido_34 = 12813.335f;
                        break;
                    case 3:
                        dato_800E9F7C[id_jugador].desconocido_18 = 2.8f;
                        dato_800E9F7C[id_jugador].desconocido_1C = 3844.0f;
                        dato_800E9F7C[id_jugador].desconocido_20 = 0.6f;
                        dato_800E9F7C[id_jugador].desconocido_24 = -0.6f;
                        dato_800E9F7C[id_jugador].desconocido_28 = 0.6f;
                        dato_800E9F7C[id_jugador].desconocido_2C = 1747.2728f;
                        dato_800E9F7C[id_jugador].desconocido_30 = 1130.5883f;
                        dato_800E9F7C[id_jugador].desconocido_34 = 3844.001f;
                        break;
                    case 4:
                        dato_800E9F7C[id_jugador].desconocido_18 = 2.0f;
                        dato_800E9F7C[id_jugador].desconocido_1C = 3844.0f;
                        dato_800E9F7C[id_jugador].desconocido_20 = 0.2f;
                        dato_800E9F7C[id_jugador].desconocido_24 = -0.4f;
                        dato_800E9F7C[id_jugador].desconocido_28 = 0.2f;
                        dato_800E9F7C[id_jugador].desconocido_2C = 2135.5557f;
                        dato_800E9F7C[id_jugador].desconocido_30 = 1601.6666f;
                        dato_800E9F7C[id_jugador].desconocido_34 = 3203.333f;
                        break;
                    case 5:
                    case 7:
                        dato_800E9F7C[id_jugador].desconocido_18 = 2.4f;
                        dato_800E9F7C[id_jugador].desconocido_1C = 3844.0f;
                        dato_800E9F7C[id_jugador].desconocido_20 = 0.4f;
                        dato_800E9F7C[id_jugador].desconocido_24 = -0.8f;
                        dato_800E9F7C[id_jugador].desconocido_28 = 0.4f;
                        dato_800E9F7C[id_jugador].desconocido_2C = 1922.0f;
                        dato_800E9F7C[id_jugador].desconocido_30 = 1201.25f;
                        dato_800E9F7C[id_jugador].desconocido_34 = 4805.0f;
                        break;
                }
                variable_a0 = jugadores[id_jugador].id_personaje + 0x0104FF00;
                switch (dato_800E9F74[id_jugador]) {
                    case 0:
                        if (dato_800EA1C0 != 0) {
                            variable_a0 += 0x14;
                        }
                        break;
                    case 1:
                        variable_a0 += 0x2E;
                        break;
                    case 2:
                        if (dato_800EA1C0 == 0) {
                            variable_a0 += 0x36;
                        } else {
                            variable_a0 += 0x3E;
                        }
                        break;
                }
                reproducir_sonido(variable_a0, &dato_800E9F7C[id_jugador].pos, id_jugador, &dato_800E9F7C[id_jugador].desconocido_0C,
                           &dato_800E9F7C[id_jugador].desconocido_10, (s8*) &dato_800E9F7C[id_jugador].desconocido_14);
                break;
            default:
                break;
        }
    }
}

void funcion_800C97C4(u8 parametro0) {
    funcion_800C5578(&dato_800E9F7C[parametro0].pos, jugadores[parametro0].id_personaje + SONIDO_CARGA_PARAMETRO(0x01, 0x04, 0xFF, 0x00));
    funcion_800C5578(&dato_800E9F7C[parametro0].pos, jugadores[parametro0].id_personaje + SONIDO_CARGA_PARAMETRO(0x01, 0x04, 0xFF, 0x14));
    funcion_800C5578(&dato_800E9F7C[parametro0].pos, jugadores[parametro0].id_personaje + SONIDO_CARGA_PARAMETRO(0x01, 0x04, 0xFF, 0x2E));
    funcion_800C5578(&dato_800E9F7C[parametro0].pos, jugadores[parametro0].id_personaje + SONIDO_CARGA_PARAMETRO(0x01, 0x04, 0xFF, 0x36));
    funcion_800C5578(&dato_800E9F7C[parametro0].pos, jugadores[parametro0].id_personaje + SONIDO_CARGA_PARAMETRO(0x01, 0x04, 0xFF, 0x3E));
}

void funcion_800C98B8(Vec3f posicion, Vec3f velocidad, u32 sonido_bits) {
    u8 variable_s0;
    struct desconocido_8018EFD8* temporal_v0;

    if ((dato_800EA108 == 0) && (dato_800EA0F0 == 0)) {
        for (variable_s0 = 0; variable_s0 < (dato_800EA1C0 + 1); variable_s0++) {
            temporal_v0 = funcion_800C1C88(0U, posicion, velocidad, dato_800EA1C8, (u8) variable_s0, sonido_bits);
            if (temporal_v0 != 0) {
                temporal_v0->unk34 = 170.0f;
                reproducir_sonido(sonido_bits, &temporal_v0->unk18, variable_s0, &temporal_v0->desconocido_2c, &dato_800EA1D4, &dato_800EA1DC);
            }
        }
    }
}

void funcion_800C99E0(Vec3f parametro0, s32 sonido_bits) {
    Vec3f* temporal_v0;
    u8 temporal_t9;

    if (dato_800EA108 == 0) {
        for (temporal_t9 = 0; temporal_t9 < dato_800EA1C0 + 1; temporal_t9++) {
            temporal_v0 = funcion_800C21E8(parametro0, sonido_bits);
            if (temporal_v0 != NULL) {
                funcion_800C5578(temporal_v0, sonido_bits);
            }
        }
    }
}

void funcion_800C9A88(u8 id_jugador) {
    u8 variable_s0;
    u32 sonido_bits;
    struct desconocido_8018EFD8* temporal_v0_6;

    if (dato_800EA108 == 0) {
        switch (dato_800EA0F0) {
            case 2:
                dato_800EA0F0 = 1;
            case 0:
                switch (jugadores[id_jugador].id_personaje) {
                    case 0:
                    case 1:
                        dato_800EA06C[id_jugador].unk00[0] = 0.35f;
                        dato_800EA06C[id_jugador].unk00[1] = 1568.9796f;
                        break;
                    case 2:
                    case 6:
                        dato_800EA06C[id_jugador].unk00[0] = 0.6f;
                        dato_800EA06C[id_jugador].unk00[1] = 1478.4615f;
                        break;
                    case 3:
                        dato_800EA06C[id_jugador].unk00[0] = 0.6f;
                        dato_800EA06C[id_jugador].unk00[1] = 1747.2728f;
                        break;
                    case 4:
                        dato_800EA06C[id_jugador].unk00[0] = 0.2f;
                        dato_800EA06C[id_jugador].unk00[1] = 2135.5557f;
                        break;
                    case 5:
                    case 7:
                        dato_800EA06C[id_jugador].unk00[0] = 0.4f;
                        dato_800EA06C[id_jugador].unk00[1] = 1922.0f;
                }
                if (dato_800EA1C0 < 2) {
                    for (variable_s0 = 0; variable_s0 < dato_800EA1C0 + 1; variable_s0++) {
                        sonido_bits = jugadores[id_jugador].id_personaje + SONIDO_CARGA_PARAMETRO(0x31, 0x02, 0x80, 0x00);
                        temporal_v0_6 = funcion_800C1C88(id_jugador, jugadores[id_jugador].pos, jugadores[id_jugador].velocidad,
                                                  &jugadores[id_jugador].desconocido_098, variable_s0, sonido_bits);
                        if (temporal_v0_6 != NULL) {
                            temporal_v0_6->unk34 = 40.0f;
                            reproducir_sonido(sonido_bits, &temporal_v0_6->unk18, variable_s0, &temporal_v0_6->desconocido_2c,
                                       &dato_800EA06C[id_jugador].unk00[2], (s8*) &dato_800EA06C[id_jugador].desconocido_0c);
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
}

void funcion_800C9D0C(u8 id_jugador) {
    funcion_800C550C(
        funcion_800C21E8(jugadores[id_jugador].pos, jugadores[id_jugador].id_personaje + SONIDO_CARGA_PARAMETRO(0x31, 0x02, 0x80, 0x00)));
}

void funcion_800C9D80(Vec3f posicion, Vec3f velocidad, u32 sonido_bits) {
    u8 variable_s0;
    struct desconocido_8018EFD8* temporal_v0;

    if ((dato_800EA108 == 0) && (dato_800EA0F0 == 0) && ((s32) dato_800EA1C0 < 4)) {
        for (variable_s0 = 0; variable_s0 < ((dato_800EA1C0 + 1)); variable_s0++) {
            temporal_v0 = funcion_800C1C88(0U, posicion, velocidad, dato_800EA1C8, (u8) variable_s0, sonido_bits);
            if (temporal_v0 != 0) {
                temporal_v0->unk34 = 170.0f;
                if (sonido_bits == SONIDO_CARGA_PARAMETRO(0x51, 0x03, 0x70, 0x0B)) {
                    reproducir_sonido(sonido_bits, &temporal_v0->unk18, variable_s0, &dato_800EA178, &dato_800EA17C, &dato_800EA1DC);
                } else {
                    reproducir_sonido(sonido_bits, &temporal_v0->unk18, variable_s0, &temporal_v0->desconocido_2c, &dato_800EA1D4, &dato_800EA1DC);
                }
            }
        }
    }
}

void funcion_800C9EF4(Vec3f parametro0, u32 sonido_bits) {
    Vec3f* temporal_;
    u8 i;

    for (i = 0; i < dato_800EA1C0 + 1; i++) {
        temporal_ = funcion_800C21E8(parametro0, sonido_bits);
        if (temporal_ != NULL) {
            funcion_800C5578(temporal_, sonido_bits);
        }
    }
}

void funcion_800C9F90(u8 parametro0) {
    if ((parametro0) != 0) {
        reproducir_sonido2(SONIDO_ATRAS_IR_ACCION_2);
        funcion_800CBBB8(0xF1000000, 0);
        dato_800EA16C = 1;
    } else {
        reproducir_sonido2(SONIDO_CONFIRMACION_DESCONOCIDO_ACCION);
        funcion_800CBBB8(0xF2000000, 0);
        dato_800EA16C = 0;
    }
}

void funcion_800CA008(u8 parametro0, u8 parametro1) {
    funcion_800C36C4(0, 0, 0x7F, 1);
    funcion_800C36C4(1, 0, 0x7F, 1);

    if (parametro1 >= 4) {
        if ((parametro1 == 0xC) || (parametro1 == 4)) {
            parametro1 = 5;
        } else {
            parametro1 = 4;
        }
    }
    funcion_800C3448((parametro0 << 8) | 0xF0000000 | parametro1);
}

void funcion_800CA0A0() {
    dato_800EA108 = 1;
}

void funcion_800CA0B8() {
    dato_800EA108 = 0;
}

void funcion_800CA0CC() {
    dato_800EA108 = 1;
}

void funcion_800CA0E4(void) {
    funcion_800C5278(3);
    funcion_800C5278(5);
}

void funcion_800CA118(u8 parametro0) {
    dato_800EA0EC[parametro0] = 1;
    dato_800E9EA4[parametro0] = 1;
    switch (dato_800EA1C0) { /* irregular */
        case 0:
            dato_800EA0F0 = 1;
            funcion_800CA0E4();
            break;
        case 1:
            if ((dato_800EA0EC[0] == (u8) 1) && (dato_800EA0EC[1] == (u8) 1)) {
                dato_800EA0F0 = 1;
                funcion_800CA0E4();
            }
            break;
        case 2:
            if ((dato_800EA0EC[0] == (u8) 1) && (dato_800EA0EC[1] == (u8) 1) && (dato_800EA0EC[2] == (u8) 1)) {
                dato_800EA0F0 = 1;
                funcion_800CA0E4();
            }
            break;
        case 3:
            if ((dato_800EA0EC[0] == (u8) 1) && (dato_800EA0EC[1] == (u8) 1) && (dato_800EA0EC[2] == (u8) 1) &&
                (dato_800EA0EC[3] == (u8) 1)) {
                dato_800EA0F0 = 1;
                funcion_800CA0E4();
            }
            break;
    }
}

void funcion_800CA24C(u8 indice_jugador) {
    dato_800EA0EC[indice_jugador] = 2;
}

void funcion_800CA270() {
    dato_800EA0F4 = 1;
}

void funcion_800CA288(u8 parametro0, s8 parametro1) {
    dato_800E9F7C[parametro0].desconocido_14 = parametro1;
}

void funcion_800CA2B8(u8 parametro0) {
    dato_800E9F7C[parametro0].desconocido_14 = 0;
}

void funcion_800CA2E4(u8 parametro0, s8 parametro1) {
    dato_800EA06C[parametro0].desconocido_0c = parametro1;
}

void funcion_800CA30C(u8 parametro0) {
    dato_800EA06C[parametro0].desconocido_0c = 0;
}

void funcion_800CA330(u8 parametro0) {
    funcion_800C3448(parametro0 << 0x10 | 0x100000FF);
    funcion_800C3448(parametro0 << 0x10 | 0x110000FF);
}

void funcion_800CA388(u8 parametro0) {
    parametro0 *= 2;
    escalar_volumen_canal_fundido(0, 0, parametro0);
    escalar_volumen_canal_fundido(1, 0, parametro0);
    escalar_volumen_canal_fundido(2, 0, parametro0);
    escalar_volumen_canal_fundido(3, 0, parametro0);
    escalar_volumen_canal_fundido(5, 0, parametro0);
}

void reproducir_secuencias(u16 primer, u16 segundo) {
    if (dato_800EA104 == 0) {
        funcion_800C3448(funcion_800C3508(0) | 0x30000000);
        funcion_800C35E8(0);
        funcion_800C3448(segundo | 0xC1510000);
        funcion_800C3448(primer | 0x01000000);
    }
    dato_800EA104 = 1;
}

void funcion_800CA49C(u8 indice_jugador) {
    if (dato_800EA108 == 0) {
        if (dato_800EA1C0 >= 2) {
            funcion_800C9060(indice_jugador, 0x1900FF3A);
        } else if (dato_800EA164 != 0) {
            funcion_800C3448(0x100100FF);
            funcion_800C3448(0x110100FF);
            reproducir_secuencia2(SEC_EVENTO_CARRERA_FINAL_VUELTA);
            funcion_800C3448(0xC1510011);
        } else {
            funcion_800C3448(0x100100FF);
            funcion_800C3448(0x110100FF);
            reproducir_secuencia2(SEC_EVENTO_CARRERA_FINAL_VUELTA);
            funcion_800C3448(dato_800EA15C | 0xC1500000);
            funcion_800C3448(0xC130017D);
        }
        dato_8018FC08 = dato_8018FC08 + 1;
    }
}

void funcion_800CA59C(u8 id_jugador) {
    if ((dato_800EA0EC[id_jugador] == 0) && (dato_800EA108 == 0)) {
        reproducir_sonido((jugadores[id_jugador].id_personaje * 0x10) + 0x29008001, &dato_800E9F7C[id_jugador].pos, id_jugador,
                   &dato_800EA1D4, &dato_800EA1D4, (s8*) &dato_800E9F7C[id_jugador].desconocido_14);
        dato_800EA164 = 1;
        if ((s32) dato_800EA1C0 >= 2) {
            funcion_800C8F80(id_jugador, 0x0100FF2C);
        } else {
            funcion_800C3448(0x100100FF);
            if (dato_800EA104 != 0) {
                funcion_800C8F80(id_jugador, 0x0100FF2C);
            } else if (dato_8018FC08 != 0) {
                if ((funcion_800C3508(1) == 0x000C) || (funcion_800C357C(0x0101000C) == 0)) {
                    funcion_800C3448(0xC1F00000);
                    funcion_800C3448(0xC1510011);
                } else {
                    reproducir_secuencia2(SEC_EVENTO_CARRERA_POTENCIADOR_ESTRELLA);
                }
            } else {
                if (1) {}
                reproducir_secuencia2(SEC_EVENTO_CARRERA_POTENCIADOR_ESTRELLA);
            }
        }
        dato_800EA10C[id_jugador] = 1;
    }
}

void funcion_800CA730(u8 indice_jugador) {
    if (dato_800EA0EC[indice_jugador] == 0) {
        if ((dato_800EA108 == 0) && (dato_800EA10C[indice_jugador] != 0)) {
            reproducir_sonido(jugadores[indice_jugador].id_personaje * 0x10 + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x08),
                       &dato_800E9F7C[indice_jugador].pos, indice_jugador, &dato_800EA1D4, &dato_800EA1D4,
                       (s8*) &dato_800E9F7C[indice_jugador].desconocido_14);
            if (dato_800EA10C[indice_jugador] != 0) {
                if ((s32) dato_800EA1C0 >= 2) {
                    funcion_800C9018(indice_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFF, 0x2C));
                } else {
                    dato_800EA10C[indice_jugador] = 0;
                    if (dato_800EA104 != 0) {
                        funcion_800C9018(indice_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFF, 0x2C));
                    } else if ((dato_800EA10C[0] == 0) && (dato_800EA10C[1] == 0)) {
                        if (dato_8018FC08 != 0) {
                            if (((u32) (jugadores_secuencia[1].activado)) == 0) {
                                funcion_800C3608(1, 5);
                                reproducir_secuencia(dato_800EA15C);
                                funcion_800C3448(0xB001307DU);
                            } else if ((funcion_800C3508(1) == 0xC) || (funcion_800C357C(0x0101000C) == 0)) {
                                funcion_800C3448(0xC1F00000U);
                                funcion_800C3448(dato_800EA15C | 0xC1500000);
                                funcion_800C3448(0xC130017DU);
                            } else {
                                funcion_800C3448(0x110100FFU);
                                reproducir_secuencia(dato_800EA15C);
                                funcion_800C3448(0xB001307DU);
                            }
                        } else {
                            funcion_800C3448(0x110100FFU);
                            reproducir_secuencia(dato_800EA15C);
                        }
                    }
                    dato_800EA164 = 0;
                }
            }
            dato_800EA10C[indice_jugador] = 0;
        }
    }
}

void funcion_800CA984(u8 indice_jugador) {
    u8 i;
    struct desconocido_8018EFD8* temporal_v0_2;

    if ((dato_800EA108 == 0) && (dato_800EA0F0 == 0)) {
        for (i = 0; i < dato_800EA1C0 + 1; i++) {
            temporal_v0_2 = funcion_800C1C88(indice_jugador, jugadores[indice_jugador].pos, dato_800EA1C8,
                                      &jugadores[indice_jugador].desconocido_098, (u8) i, SONIDO_ESTRELLA_ITEM);
            if (temporal_v0_2) {
                reproducir_sonido(SONIDO_ESTRELLA_ITEM, &temporal_v0_2->unk18, i, &dato_800EA1D4, &dato_800EA1D4, &dato_800EA1DC);
            }
        }
    }
}

void funcion_800CAACC(u8 id_jugador) {
    if ((u8) dato_800EA108 == 0) {
        funcion_800C5578(funcion_800C21E8(jugadores[id_jugador].pos, SONIDO_ESTRELLA_ITEM), SONIDO_ESTRELLA_ITEM);
    }
}

void funcion_800CAB4C(u8 indice_jugador) {
    SIN_USO u8* temporal_v1;
    SIN_USO u8 temporal_v0;

    if (dato_800EA108 == 0) {
        switch (dato_800EA0EC[indice_jugador]) {
            case 2:
                dato_800EA0EC[indice_jugador] = 1;
            case 0:
                funcion_800C36C4(0, 1U, 0x55U, 5);
                funcion_800C9060(indice_jugador, 0x1900F013U);
                reproducir_sonido(SONIDO_RAYO_ITEM, &dato_800EA1C8, 0U, &dato_800EA1D4, &dato_800EA1D4, &dato_800EA1DC);
                break;
            default:
                break;
        }
        dato_800EA168 = 1;
    }
}

void funcion_800CAC08() {
    if (dato_800EA108 == 0) {
        funcion_800C36C4(0, 1U, 0x7FU, 0x19);
        funcion_800C56F0(SONIDO_RAYO_ITEM);
        dato_800EA168 = 0;
    }
}

void funcion_800CAC60(SIN_USO u8 parametro0) {
    if ((dato_800EA108 == 0) && (dato_800EA0F0 == 0)) {
        reproducir_sonido(SONIDO_EXPLOSION_ACCION_2, &dato_800EA1C8, 0U, &dato_800EA1D4, &dato_800EA1D4, &dato_800EA1DC);
        if ((dato_800EA10C[0] != 1) && (dato_800EA10C[1] != 1)) {
            funcion_800C36C4(0, 1, 0x37U, 5);
            reproducir_sonido(SONIDO_RAYO_ITEM, &dato_800EA1C8, 0U, &dato_800EA1D4, &dato_800EA1D4, &dato_800EA1DC);
            dato_800EA168 = 1;
        }
    }
}

void funcion_800CAD40(SIN_USO s32 parametro0) {
    if (dato_800EA108 == 0) {
        if ((dato_800EA170[0] == 0) && (dato_800EA170[1] == 0) && (dato_800EA170[2] == 0) && (dato_800EA170[3] == 0)) {
            funcion_800C36C4(0, 1, 0x7FU, 0x19);
        }
        funcion_800C56F0(SONIDO_RAYO_ITEM);
        dato_800EA168 = 0;
    }
}

void funcion_800CADD0(u8 indice_jugador, f32 parametro1) {
    if (dato_800EA108 == 0) {
        switch (dato_800EA0EC[indice_jugador]) {
            case 2:
                dato_800EA0EC[indice_jugador] = 1;
            case 0:
                parametro1 = (parametro1 * 0.55f) + 0.45f;
                if (parametro1 > 1.0f) {
                    parametro1 = 1.0f;
                }
                if (parametro1 < 0.0f) {
                    parametro1 = 0.0f;
                }
                dato_800EA110[indice_jugador] = parametro1;
                reproducir_sonido(0x1900A209U, &dato_800E9F7C[indice_jugador].pos, indice_jugador, &dato_800EA1D4,
                           &dato_800EA110[indice_jugador], (s8*) &dato_800E9F7C[indice_jugador].desconocido_14);
                break;
            default:
                break;
        }
    }
}

void funcion_800CAEC4(u8 id_jugador, f32 parametro1) {
    if (dato_800EA108 == 0) {
        switch (dato_800EA0EC[id_jugador]) {
            case 2:
                dato_800EA0EC[id_jugador] = 1;
            case 0:
                parametro1 = (parametro1 * 0.7f) + 0.1f;
                if (parametro1 > 1.0f) {
                    parametro1 = 1.0f;
                }
                if (parametro1 < 0.0f) {
                    parametro1 = 0.0f;
                }
                dato_800EA120[id_jugador] = parametro1;
                reproducir_sonido(id_circuito_actual + 0x19007020, &dato_800E9F7C[id_jugador].pos, id_jugador, &dato_800EA1D4,
                           &dato_800EA120[id_jugador], (s8*) &dato_800E9F7C[id_jugador].desconocido_14);
                break;
            default:
                break;
        }
    }
}

void funcion_800CAFC0(u8 indice_jugador) {
    if (dato_800EA108 == 0) {
        switch (dato_800EA0EC[indice_jugador]) {
            case 2:
                dato_800EA0EC[indice_jugador] = 1;
            case 0:
                funcion_800C36C4(0, 1, 0x55U, 5);
                funcion_800C9060(indice_jugador, 0x19009E59U);
                funcion_800C8F80(indice_jugador, 0x0100FA4C);
                dato_800EA170[indice_jugador] = 1;
                break;
        }
    }
}

void funcion_800CB064(u8 indice_jugador) {
    if (dato_800EA108 == 0) {
        if (dato_800EA170[indice_jugador] == 1) {
            if ((u8) dato_800EA168 == 0) {
                funcion_800C36C4(0, 1U, 0x7FU, 0x19);
            }
            funcion_800C90F4(indice_jugador,
                          jugadores[indice_jugador].id_personaje * 0x10 + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x08));
            funcion_800C9018(indice_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFA, 0x4C));
            dato_800EA170[indice_jugador] = 0;
        }
    }
}

void funcion_800CB134() {
    dato_800EA174 = 1;
}

void empezar_secuencia_ceremonia_perdiendo() {
    if (dato_800EA174 != 0) {
        dato_800EA174++;

        if (dato_800EA174 == 3) {
            reproducir_secuencia(SEC_EVENTO_CEREMONIA_PRESENTACION_PART1);
            funcion_800C3448(0x4000007F);
        }

        if (dato_800EA174 == 300) {
            reproducir_secuencia(SEC_EVENTO_CEREMONIA_PRESENTACION_PART2_VICTORIA);
            funcion_800C3448(0x4000007F);
            reproducir_secuencia2(SEC_EVENTO_CEREMONIA_PRESENTACION_PART2_PERDER);
            funcion_800C3448(0x41000000);
        }

        if (dato_800EA174 == 560) {
            funcion_800C3448(0x40640000);
            funcion_800C3448(0xB0640073);
            funcion_800C3448(0x4150007F);
            funcion_800C3448(0xB1640073);
        }

        if (dato_800EA174 == 680) {
            funcion_800C3448(0x100100FF);
        }

        if (dato_800EA174 == 1050) {
            funcion_800C3448(0xB1500001);
            funcion_800C3448(0x51500001);
        }

        if (dato_800EA174 == 1130) {
            funcion_800C3448(0x41320000);
        }

        if (dato_800EA174 == 1200) {
            funcion_800C3448(0x110100FF);
        }

        if (dato_800EA174 == 1230) {
            reproducir_secuencia(SEC_EVENTO_CEREMONIA_TROFEO_PERDER);
            funcion_800C3448(0x4000007F);
        }
    }
}

void funcion_800CB2C4() {
    funcion_800C1F8C();
    funcion_800C3724();
    funcion_800C3478();
    funcion_800C5848();
    funcion_800C59C4();
    funcion_800C8CCC();
    funcion_800C2274(0);
    funcion_800CBC24();
}
