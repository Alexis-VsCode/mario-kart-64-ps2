// Sonidos jugadores

void funcion_800C5CB8(void) {
    funcion_800C2474();
    funcion_800C3F70();
    sonido_inicializacion();
    funcion_800C284C(2, 0, 0xFF, 1);
}

void funcion_800C5D04(u8 id_jugador) {
    if ((jugadores[id_jugador].kart_props & ACELERADOR) == ACELERADOR) {
        dato_800E9E34[id_jugador] = 0;
        if (dato_800E9E24[id_jugador] < 0x4E20) {
            if ((u8) dato_800EA16C == 0) {
                dato_800E9E24[id_jugador]++;
            }
        }
        if (dato_800E9E24[id_jugador] == 1) {
            switch (dato_800EA0EC[id_jugador]) {
                case 2:
                    dato_800EA0EC[id_jugador] = 1;
                case 0:
                    funcion_800C97C4(id_jugador);
                    funcion_800C94A4(id_jugador);
                    break;
                default:
                    break;
            }
        }
    } else {
        dato_800E9E24[id_jugador] = 0;
        if ((dato_800E9E34[id_jugador] < 0x4E20) && ((u8) dato_800EA16C == 0)) {
            dato_800E9E34[id_jugador]++;
        }
    }
}

void funcion_800C5E38(u8 id_jugador) {
    if (dato_800EA108 == 0) {
        if (((jugadores[id_jugador].kart_props & ACELERADOR) != ACELERADOR) && (jugadores[id_jugador].desconocido_098 > 400.0f)) {
            dato_800E9E14[id_jugador] = 1;
            if (dato_800EA0EC[id_jugador] == 0) {
                dato_800E9F7C[id_jugador].desconocido_10 = 0.6f - dato_800E9F54[id_jugador];
            }
            dato_800E9DC4[id_jugador] = dato_800E9F7C[id_jugador].desconocido_30;
            dato_800E9DD4[id_jugador] = dato_800E9F7C[id_jugador].desconocido_24;
            if ((dato_800E9E34[id_jugador] == 1) && ((u8) dato_800EA16C == 0)) {
                switch (dato_800EA0EC[id_jugador]) {
                    case 2:
                        dato_800EA0EC[id_jugador] = 1;
                    case 0:
                        if ((dato_800E9F74[id_jugador] == 0) && (jugadores[id_jugador].id_personaje != 3)) {
                            if ((s32) dato_800EA1C0 < 2) {
                                reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF9, 0x26), &dato_800E9F7C[id_jugador].pos, id_jugador,
                                           &dato_800E9F7C[id_jugador].desconocido_38, &dato_800E9F04[id_jugador],
                                           (s8*) &dato_800E9F7C[id_jugador].desconocido_14);
                            } else {
                                reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0x80, 0x26), &dato_800E9F7C[id_jugador].pos, id_jugador,
                                           &dato_800E9F7C[id_jugador].desconocido_38, &dato_800E9F04[id_jugador],
                                           (s8*) &dato_800E9F7C[id_jugador].desconocido_14);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        } else {
            if (dato_800E9E24[id_jugador] == 0x0000000A) {
                if ((s32) dato_800EA1C0 < 2) {
                    funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF9, 0x26));
                } else {
                    funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0x80, 0x26));
                }
            }
            dato_800E9E14[id_jugador] = 0;
            dato_800E9F7C[id_jugador].desconocido_10 = (1.0f - dato_800E9F54[id_jugador]) - dato_800EA130[id_jugador];
            if ((1.0f - dato_800E9F54[id_jugador]) < dato_800EA130[id_jugador]) {
                dato_800E9F7C[id_jugador].desconocido_10 = 0.0f;
            }
            dato_800E9DC4[id_jugador] = dato_800E9F7C[id_jugador].desconocido_2C;
            dato_800E9DD4[id_jugador] = dato_800E9F7C[id_jugador].desconocido_20;
        }
    }
}

void funcion_800C6108(u8 id_jugador) {
    Jugador* jugador;

    jugador = &jugadores[id_jugador];
    dato_800E9E64[id_jugador] = (jugador->desconocido_098 / dato_800E9DC4[id_jugador]) + dato_800E9DD4[id_jugador];
    if ((jugador->desconocido_098 < 1800.0f) && ((jugador->kart_props & ACELERADOR) != ACELERADOR)) {
        dato_800E9E64[id_jugador] = (jugador->desconocido_098 / dato_800E9F7C[id_jugador].desconocido_34) + dato_800E9F7C[id_jugador].desconocido_28;
        if (dato_800E9EC4) {}
    }
    if (jugador->speed > 4.75f) {
        if (dato_800E9EB4[id_jugador] < (dato_800E9F7C[id_jugador].desconocido_18 + 0.4f)) {
            dato_800E9DE4[id_jugador] += 0.005f;
        }
    } else {
        dato_800E9DE4[id_jugador] = 0.0f;
    }
    if (jugadores[id_jugador].desconocido_0C0 > 0) {
        dato_800E9E54[id_jugador] = (f32) jugador->desconocido_0C0;
    } else {
        dato_800E9E54[id_jugador] = (f32) -jugador->desconocido_0C0;
    }
    if ((jugador->efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
        dato_800E9EB4[id_jugador] = dato_800E9E64[id_jugador] + dato_800E9DE4[id_jugador];
    } else {
        dato_800E9EB4[id_jugador] = dato_800E9E64[id_jugador] + dato_800E9DE4[id_jugador] - (dato_800E9E54[id_jugador] / 12000.0f);
        if (dato_800E9EB4[id_jugador] < 0.01f) {
            dato_800E9EB4[id_jugador] = 0.01f;
        }
    }
    if ((dato_800E9F74[id_jugador]) || (dato_800E9F78[id_jugador])) {
        if (dato_800E9F74[id_jugador]) {
            if (dato_800E9F78[id_jugador] < 0xF) {
                dato_800E9F78[id_jugador]++;
                dato_800E9DF4[id_jugador] += 0.03f;
            }
        } else if (dato_800E9F78[id_jugador]) {
            dato_800E9F78[id_jugador]--;
            dato_800E9DF4[id_jugador] -= 0.03f;
        }
        dato_800E9EB4[id_jugador] -= dato_800E9DF4[id_jugador];
    }
    dato_800E9EE4[id_jugador] = dato_800E9EB4[id_jugador] - dato_800E9EC4[id_jugador];
#ifdef VERSION_EU
    if ((dato_800E9EE4[id_jugador] > 0.5f) || (dato_800E9EE4[id_jugador] < -0.5f))
#else
    if ((dato_800E9EE4[id_jugador] > 0.5f) || (dato_800E9EE4[id_jugador] < 0.5f))
#endif
    {
        dato_800E9ED4[id_jugador] = dato_800E9EE4[id_jugador] * 0.25f;
        dato_800E9F7C[id_jugador].desconocido_0C = dato_800E9EC4[id_jugador] + dato_800E9ED4[id_jugador] + dato_800E9F34[id_jugador];
    } else {
        dato_800E9F7C[id_jugador].desconocido_0C = dato_800E9EB4[id_jugador] + dato_800E9F34[id_jugador];
    }
#ifdef VERSION_EU
    if (dato_800E9F7C[id_jugador].desconocido_0C < 0.0f) {
        dato_800E9F7C[id_jugador].desconocido_0C = 0.0f;
    }
#endif
    if (dato_800E9F7C[id_jugador].desconocido_0C > 4.0f) {
        dato_800E9F7C[id_jugador].desconocido_0C = 4.0f;
    }
    dato_800E9EC4[id_jugador] = dato_800E9F7C[id_jugador].desconocido_0C;
    dato_800E9F7C[id_jugador].desconocido_38 = (dato_800E9F7C[id_jugador].desconocido_0C / 1.5f) + 0.4f;
}

void funcion_800C64A0(u8 id_jugador) {
    switch (dato_800E9E74[id_jugador]) {
        case 3:
            dato_800E9EF4[id_jugador] = (jugadores[id_jugador].speed / 5.0f) + 0.2f;
            break;
        case 1:
        case 13:
        case 14:
        case 17:
            dato_800E9EF4[id_jugador] = ((dato_800E9E54[id_jugador] - 3500.0f) / 3000.0f) + 0.4f;
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 22:
        case 23:
        case 24:
        case 29:
        case 30:
        case 31:
            dato_800E9EF4[id_jugador] = (jugadores[id_jugador].speed / 5.0f) + 0.2f;
            break;
        default:
            dato_800E9EF4[id_jugador] = 1.0f;
            break;
    }
    if (dato_800E9EF4[id_jugador] > 1.0f) {
        dato_800E9EF4[id_jugador] = 1.0f;
    }
    if (dato_800E9EF4[id_jugador] < 0.0f) {
        dato_800E9EF4[id_jugador] = 0.0f;
    }
    if ((jugadores[id_jugador].kart_props & ACELERADOR) == ACELERADOR) {
        dato_800E9F04[id_jugador] = 0.56f - (dato_800E9E24[id_jugador] * 0.06f);
    } else {
        dato_800E9F04[id_jugador] = (dato_800E9E34[id_jugador] / 50.0f) + 0.25f;
    }
    if (dato_800E9F24[id_jugador] != 0) {
        dato_800E9F04[id_jugador] = 0.0f;
    }
    if (dato_800E9F04[id_jugador] > 0.9f) {
        dato_800E9F04[id_jugador] = 0.9f;
    }
}

void funcion_800C6758(u8 id_jugador) {
    switch (dato_800E9E74[id_jugador]) { /* irregular */
        case 3:
            dato_800E9F14[id_jugador] = (jugadores[id_jugador].speed / 9.0f) + 0.6f;
            break;
        case 2:
        case 13:
        case 17:
            dato_800E9F14[id_jugador] = (dato_800E9E54[id_jugador] / 13000.0f) + 0.95f;
            break;
        default:
            dato_800E9F14[id_jugador] = 1.0f;
            break;
    }
}

void funcion_800C683C(u8 id_camara) {
    if ((dato_800EA108 == 0) && (dato_800EA0EC[id_camara] == 0)) {
        if (dato_800E9E74[id_camara] != dato_800E9E84[id_camara]) {
            funcion_800C5578(&dato_800E9F7C[id_camara].pos, dato_800E9E94[id_camara]);
            switch (dato_800E9E74[id_camara]) {
                case 3:
                    reproducir_sonido(SONIDO_CHIRRIDO_RUEDA_ACCION, &dato_800E9F7C[id_camara].pos, id_camara, &dato_800E9F14[id_camara],
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CHIRRIDO_RUEDA_ACCION;
                    break;
                case 18:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF8, 0x1D), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800EA1D4, (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF8, 0x1D);
                    break;
                case 19:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF8, 0x22), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800EA1D4, (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF8, 0x22);
                    break;
                case 1:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x09), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x09);
                    break;
                case 2:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF4, 0x0A), &dato_800E9F7C[id_camara].pos, id_camara,
                               &dato_800E9F14[id_camara], &dato_800EA1D4, (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF4, 0x0A);
                    break;
                case 17:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x1E), &dato_800E9F7C[id_camara].pos, id_camara,
                               &dato_800E9F14[id_camara], &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x1E);
                    break;
                case 15:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x1F), &dato_800E9F7C[id_camara].pos, id_camara,
                               &dato_800E9F14[id_camara], &dato_800EA1D4, (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x1F);
                    break;
                case 16:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x21), &dato_800E9F7C[id_camara].pos, id_camara,
                               &dato_800E9F14[id_camara], &dato_800EA1D4, (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x21);
                    break;
                case 20:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x27), &dato_800E9F7C[id_camara].pos, id_camara,
                               &dato_800E9F14[id_camara], &dato_800EA1D4, (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x27);
                    break;
                case 25:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x20), &dato_800E9F7C[id_camara].pos, id_camara,
                               &dato_800E9F14[id_camara], &dato_800EA1D4, (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x20);
                    break;
                case 26:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x23), &dato_800E9F7C[id_camara].pos, id_camara,
                               &dato_800E9F14[id_camara], &dato_800EA1D4, (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x23);
                    break;
                case 27:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0x80, 0x46), &dato_800E9F7C[id_camara].pos, id_camara,
                               &dato_800E9F14[id_camara], &dato_800EA1D4, (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0x80, 0x46);
                    break;
                case 28:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x25), &dato_800E9F7C[id_camara].pos, id_camara,
                               &dato_800E9F14[id_camara], &dato_800EA1D4, (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x25);
                    break;
                case 4:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x0B), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x0B);
                    break;
                case 5:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x0C), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x0C);
                    break;
                case 6:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x0D), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x0D);
                    break;
                case 7:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x0E), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x0E);
                    break;
                case 8:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x0F), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x0F);
                    break;
                case 9:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x10), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x10);
                    break;
                case 10:
                case 14:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x11), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x11);
                    break;
                case 11:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x12), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x12);
                    break;
                case 12:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x13), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x13);
                    break;
                case 29:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x48), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x48);
                    break;
                case 30:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x49), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x49);
                    break;
                case 31:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x4A), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x4A);
                    break;
                case 13:
                case 22:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x29), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x29);
                    break;
                case 23:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x2A), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x2A);
                    break;
                case 24:
                    reproducir_sonido(SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x2B), &dato_800E9F7C[id_camara].pos, id_camara, &dato_800EA1D4,
                               &dato_800E9EF4[id_camara], (s8*) &dato_800E9F7C[id_camara].desconocido_14);
                    dato_800E9E94[id_camara] = SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF0, 0x2B);
                    break;
                default:
                    funcion_800C5578(&dato_800E9F7C[id_camara].pos, dato_800E9E94[id_camara]);
                    break;
            }
        }
        dato_800E9E84[id_camara] = dato_800E9E74[id_camara];
    }
}

void funcion_800C70A8(u8 id_jugador) {
    if (dato_800EA0EC[id_jugador] == 0) {
        dato_800E9E74[id_jugador] = 0;
        if ((dato_800E9E54[id_jugador] > 3500.0f) || ((jugadores[id_jugador].efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO)) {
            dato_800E9E74[id_jugador] = 1;
            switch (jugadores[id_jugador].ruedas[RUEDA_IZQUIERDA_AUDIO].tipo_superficie) {
                case TIERRA:
                    dato_800E9E74[id_jugador] = 0x0000000D;
                    break;
                case ARENA:
                    dato_800E9E74[id_jugador] = 0x0000000E;
                    break;
                case PUENTE:
                    dato_800E9E74[id_jugador] = 0x00000011;
                    break;
                case PIEDRA:
                    dato_800E9E74[id_jugador] = 0x0000000F;
                    break;
                case NIEVE:
                    dato_800E9E74[id_jugador] = 0x00000010;
                    break;
                case HIELO:
                    dato_800E9E74[id_jugador] = 0x00000014;
                    break;
                case PUENTE_CUERDA:
                    dato_800E9E74[id_jugador] = 0x00000019;
                    break;
                case PUENTE_MADERA:
                    dato_800E9E74[id_jugador] = 0x0000001A;
                    break;
                case PISTA_TREN:
                    dato_800E9E74[id_jugador] = 0x0000001B;
                    break;
            }
        }
        if ((jugadores[id_jugador].efectos & EFECTO_DERRAPANDO) == EFECTO_DERRAPANDO) {
            dato_800E9E74[id_jugador] = 2;
            switch (jugadores[id_jugador].ruedas[RUEDA_IZQUIERDA_AUDIO].tipo_superficie) {
                case TIERRA:
                    dato_800E9E74[id_jugador] = 0x0000000D;
                    break;
                case ARENA:
                    dato_800E9E74[id_jugador] = 0x0000000E;
                    break;
                case PUENTE:
                    dato_800E9E74[id_jugador] = 0x00000011;
                    break;
                case PIEDRA:
                    dato_800E9E74[id_jugador] = 0x0000000F;
                    break;
                case NIEVE:
                    dato_800E9E74[id_jugador] = 0x00000010;
                    break;
                case HIELO:
                    dato_800E9E74[id_jugador] = 0x00000014;
                    break;
                case PUENTE_CUERDA:
                    dato_800E9E74[id_jugador] = 0x00000019;
                    break;
                case PUENTE_MADERA:
                    dato_800E9E74[id_jugador] = 0x0000001A;
                    break;
                case PISTA_TREN:
                    dato_800E9E74[id_jugador] = 0x0000001B;
                    break;
            }
        }
        switch (jugadores[id_jugador].ruedas[RUEDA_IZQUIERDA_AUDIO].tipo_superficie) {
            case PASTO:
                if (dato_800E9E74[id_jugador] == 6) {
                    dato_800E9E74[id_jugador] = 4;
                } else if (dato_800EA1C0 == 0) {
                    dato_800E9E74[id_jugador] = 5;
                } else {
                    dato_800E9E74[id_jugador] = 4;
                }
                break;
            case FUERA_PISTA_ARENA:
                if (dato_800E9E74[id_jugador] == 0x0000000C) {
                    dato_800E9E74[id_jugador] = 0x0000000A;
                } else if (dato_800EA1C0 == 0) {
                    dato_800E9E74[id_jugador] = 0x0000000B;
                } else {
                    dato_800E9E74[id_jugador] = 0x0000000A;
                }
                break;
            case FUERA_PISTA_TIERRA:
                if (dato_800E9E74[id_jugador] == 0x00000018) {
                    dato_800E9E74[id_jugador] = 0x00000016;
                } else if (dato_800EA1C0 == 0) {
                    dato_800E9E74[id_jugador] = 0x00000017;
                } else {
                    dato_800E9E74[id_jugador] = 0x00000016;
                }
                break;
            case FUERA_PISTA_NIEVE:
                if (dato_800E9E74[id_jugador] == 0x0000001F) {
                    dato_800E9E74[id_jugador] = 0x0000001D;
                } else if (dato_800EA1C0 == 0) {
                    dato_800E9E74[id_jugador] = 0x0000001E;
                } else {
                    dato_800E9E74[id_jugador] = 0x0000001D;
                }
                break;
            case ARENA_HUMEDO:
                if (dato_800E9F74[id_jugador] == 0) {
                    if (dato_800E9E74[id_jugador] == 9) {
                        dato_800E9E74[id_jugador] = 7;
                    } else if (dato_800EA1C0 == 0) {
                        dato_800E9E74[id_jugador] = 8;
                    } else {
                        dato_800E9E74[id_jugador] = 7;
                    }
                } else {
                    dato_800E9E74[id_jugador] = 0x0000001C;
                }
                break;
            case PUENTE_CUERDA:
                dato_800E9E74[id_jugador] = 0x00000019;
                break;
            case PUENTE_MADERA:
                dato_800E9E74[id_jugador] = 0x0000001A;
                break;
            case PISTA_TREN:
                dato_800E9E74[id_jugador] = 0x0000001B;
                break;
        }
        switch (jugadores[id_jugador].ruedas[RUEDA_DERECHA_AUDIO].tipo_superficie) {
            case PASTO:
                if (dato_800E9E74[id_jugador] == 5) {
                    dato_800E9E74[id_jugador] = 4;
                } else if (dato_800EA1C0 == 0) {
                    dato_800E9E74[id_jugador] = 6;
                } else {
                    dato_800E9E74[id_jugador] = 4;
                }
                break;
            case FUERA_PISTA_ARENA:
                if (dato_800E9E74[id_jugador] == 0x0000000B) {
                    dato_800E9E74[id_jugador] = 0x0000000A;
                } else if (dato_800EA1C0 == 0) {
                    dato_800E9E74[id_jugador] = 0x0000000C;
                } else {
                    dato_800E9E74[id_jugador] = 0x0000000A;
                }
                break;
            case FUERA_PISTA_TIERRA:
                if (dato_800E9E74[id_jugador] == 0x00000017) {
                    dato_800E9E74[id_jugador] = 0x00000016;
                } else if (dato_800EA1C0 == 0) {
                    dato_800E9E74[id_jugador] = 0x00000018;
                } else {
                    dato_800E9E74[id_jugador] = 0x00000016;
                }
                break;
            case FUERA_PISTA_NIEVE:
                if (dato_800E9E74[id_jugador] == 0x0000001E) {
                    dato_800E9E74[id_jugador] = 0x0000001D;
                } else if (dato_800EA1C0 == 0) {
                    dato_800E9E74[id_jugador] = 0x0000001F;
                } else {
                    dato_800E9E74[id_jugador] = 0x0000001D;
                }
                break;
            case ARENA_HUMEDO:
                if (dato_800E9F74[id_jugador] == 0) {
                    if (dato_800E9E74[id_jugador] == 8) {
                        dato_800E9E74[id_jugador] = 7;
                    } else if (dato_800EA1C0 == 0) {
                        dato_800E9E74[id_jugador] = 9;
                    } else {
                        dato_800E9E74[id_jugador] = 7;
                    }
                } else {
                    dato_800E9E74[id_jugador] = 0x0000001C;
                }
                break;
            case PUENTE_CUERDA:
                dato_800E9E74[id_jugador] = 0x00000019;
                break;
            case PUENTE_MADERA:
                dato_800E9E74[id_jugador] = 0x0000001A;
                break;
            case PISTA_TREN:
                dato_800E9E74[id_jugador] = 0x0000001B;
                break;
        }
        if (((jugadores[id_jugador].speed < 0.5f) || ((jugadores[id_jugador].efectos & EFECTO_EN_EL_AIRE) == EFECTO_EN_EL_AIRE)) &&
            (dato_800E9E74[id_jugador] != 0x0000001C)) {
            dato_800E9E74[id_jugador] = 0;
        }
        if ((((jugadores[id_jugador].efectos & TEMPRANO_INICIO_TROMPO_EFECTO) == TEMPRANO_INICIO_TROMPO_EFECTO) &&
             ((jugadores[id_jugador].type & SECUENCIA_INICIO_JUGADOR) != SECUENCIA_INICIO_JUGADOR)) ||
            ((jugadores[id_jugador].efectos & BANANA_CERCA_EFECTO_TROMPO) == BANANA_CERCA_EFECTO_TROMPO) ||
            ((jugadores[id_jugador].efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
            ((jugadores[id_jugador].efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO) ||
            ((jugadores[id_jugador].kart_props & CONDUCIENDO_CERCA_TROMPO) == CONDUCIENDO_CERCA_TROMPO)) {
            dato_800E9E74[id_jugador] = 0x00000012;
        }
        if ((((jugadores[id_jugador].efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) &&
             ((jugadores[id_jugador].type & SECUENCIA_INICIO_JUGADOR) != SECUENCIA_INICIO_JUGADOR)) ||
            ((jugadores[id_jugador].efectos & BANANA_CERCA_EFECTO_TROMPO) == BANANA_CERCA_EFECTO_TROMPO)) {
            dato_800E9E74[id_jugador] = 0x00000013;
        }
        if (jugadores[id_jugador].desconocido_20C != 0.0f) {
            dato_800E9E74[id_jugador] = 3;
        }
    }
}

void funcion_800C76C0(u8 id_jugador) {
    if (dato_800E9EA4[id_jugador] != 0) {
        if (dato_800E9EA4[id_jugador] < 0x2BC) {
            dato_800E9EA4[id_jugador]++;
        }
        if (dato_800E9EA4[id_jugador] == 2) {
            funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFA, 0x28));
            funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFF, 0x2C));
            funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFA, 0x4C));
            funcion_800C5578(&dato_800E9F7C[id_jugador].pos, dato_800E9E94[id_jugador]);
            dato_800E9E74[id_jugador] = 0;
            switch (seleccion_modo) { /* irregular */
                case GRAN_PREMIO:
                    dato_800EA0EC[id_jugador] = 2;
                    funcion_800C9060(id_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0xF1, 0x03));
                    if (dato_800EA1C0 == 0) {
                        funcion_800C3448(0x100100FF);
                        funcion_800C3448(0x110100FF);
                        funcion_800C5278(5U);
                        if (jugadores[id_jugador].puesto_actual == 0) {
                            funcion_800C97C4(id_jugador);
                            dato_800EA0F0 = 2;
                            funcion_800C9A88(id_jugador);
                            reproducir_secuencias(SEC_EVENTO_CARRERA_META_PRIMER, SEC_MENU_RESULTADOS_PANTALLA_VICTORIA);
                        } else if (jugadores[id_jugador].puesto_actual < 4) {
                            funcion_800C97C4(id_jugador);
                            dato_800EA0F0 = 2;
                            funcion_800C9A88(id_jugador);
                            reproducir_secuencias(SEC_EVENTO_CARRERA_META_OTRO, SEC_MENU_RESULTADOS_PANTALLA_VICTORIA);
                        } else {
                            funcion_800C3448(-0x3E9F9C00);
                            reproducir_secuencias(SEC_EVENTO_CARRERA_META_PERDER, SEC_MENU_RESULTADOS_PANTALLA_PERDER);
                        }
                    } else {
                        dato_800EA0EC[id_jugador] = 2;
                        funcion_800C9060(id_jugador, 0x1900F103U);
                        if (jugadores[id_jugador].puesto_actual == 0) {
                            funcion_800C3448(0x100100FF);
                            funcion_800C3448(0x110100FF);
                            funcion_800C97C4(id_jugador);
                            dato_800EA0F0 = 2;
                            funcion_800C9A88(id_jugador);
                            reproducir_secuencias(SEC_EVENTO_CARRERA_META_PRIMER, SEC_MENU_RESULTADOS_PANTALLA_VICTORIA);
                        } else if (jugadores[id_jugador].puesto_actual < 4) {
                            if (dato_800EA104 == 0) {
                                funcion_800C3448(0x100100FF);
                                funcion_800C3448(0x110100FF);
                            }
                            funcion_800C97C4(id_jugador);
                            dato_800EA0F0 = 2;
                            funcion_800C9A88(id_jugador);
                            reproducir_secuencias(SEC_EVENTO_CARRERA_META_OTRO, SEC_MENU_RESULTADOS_PANTALLA_VICTORIA);
                        } else if (dato_800EA104 == 0) {
                            funcion_800C3448(0x100100FF);
                            funcion_800C3448(0x110100FF);
                            funcion_800C3448(-0x3E9F9C00);
                            reproducir_secuencias(SEC_EVENTO_CARRERA_META_PERDER, SEC_MENU_RESULTADOS_PANTALLA_PERDER);
                        }
                        if ((dato_800EA104 != 0) || (dato_800EA0EC[id_jugador] != 1)) {
                            funcion_800C5278(5U);
                        }
                    }
                    break;
                case CONTRARRELOJ:
                    funcion_800C3448(0x100100FF);
                    funcion_800C3448(0x110100FF);
                    funcion_800C97C4(id_jugador);
                    dato_800EA0F0 = 2;
                    funcion_800C9A88(0U);
                    dato_800EA0EC[id_jugador] = 2;
                    funcion_800C9060(id_jugador, 0x1900F103U);
                    if (dato_801657E5 == 1) {
                        reproducir_secuencias(SEC_EVENTO_CARRERA_META_PRIMER, SEC_MENU_RESULTADOS_PANTALLA_VICTORIA);
                    } else if (dato_8018ED90 == 1) {
                        reproducir_secuencias(SEC_EVENTO_CARRERA_META_OTRO, SEC_MENU_RESULTADOS_PANTALLA_VICTORIA);
                    } else {
                        funcion_800C3448(0x01640010);
                    }
                    break;
                case VERSUS:
                    dato_800EA0EC[id_jugador] = 2;
                    funcion_800C9060(id_jugador, 0x1900F103U);
                    switch (dato_800EA1C0) {
                        case 1:
                            funcion_800C3448(0x100100FF);
                            funcion_800C3448(0x110100FF);
                            funcion_800C97C4(id_jugador);
                            dato_800EA0F0 = 2;
                            funcion_800C9A88(id_jugador);
                            reproducir_secuencias(SEC_EVENTO_CARRERA_META_PRIMER, SEC_MENU_RESULTADOS_PANTALLA_VICTORIA_VS);
                            break;
                        case 2:
                            if ((dato_800EA104 == 0) && (dato_800EA0EC[id_jugador] == 1)) {
                                funcion_800C3448(0x100100FF);
                                funcion_800C3448(0x110100FF);
#ifdef VERSION_EU
                                reproducir_secuencia2(SEC_EVENTO_CARRERA_META_PRIMER);
#else
                                reproducir_secuencias(SEC_EVENTO_CARRERA_META_PRIMER, SEC_MENU_RESULTADOS_PANTALLA_VICTORIA_VS);
#endif
                                dato_800EA104 = 1;
                            } else if ((dato_800EA104 == 1) && (dato_800EA0EC[id_jugador] == 1)) {
                                funcion_800C5278(5U);
#ifndef VERSION_EU
                                if (funcion_800C3508(1) != 0x000D)
#endif
                                {
                                    dato_800EA104 = 0;
                                    reproducir_secuencias(SEC_EVENTO_CARRERA_META_OTRO, SEC_MENU_RESULTADOS_PANTALLA_VICTORIA_VS);
                                }
                                dato_800EA104 = 2;
                            }
                            break;
                        case 3:
                            if ((dato_800EA104 == 0) && (dato_800EA0EC[id_jugador] == 1)) {
                                funcion_800C3448(0x100100FF);
                                funcion_800C3448(0x110100FF);
                                reproducir_secuencia2(SEC_EVENTO_CARRERA_META_PRIMER);
                                dato_800EA104 = 1;
                            } else if ((dato_800EA104 == 1) && (dato_800EA0EC[id_jugador] == 1)) {
                                if (funcion_800C3508(1) != 0x000D) {
                                    dato_800EA104 = 0;
                                    reproducir_secuencia2(SEC_EVENTO_CARRERA_META_OTRO);
                                }
                                dato_800EA104 = 2;
                            } else if ((dato_800EA104 == 2) && (dato_800EA0EC[id_jugador] == 1)) {
                                funcion_800C5278(5U);
#ifndef VERSION_EU
                                if (funcion_800C3508(1) != 0x000E)
#endif
                                {
                                    dato_800EA104 = 0;
                                    reproducir_secuencias(SEC_EVENTO_CARRERA_META_OTRO, SEC_MENU_RESULTADOS_PANTALLA_VICTORIA_VS);
                                }
                                dato_800EA104 = 3;
                            }
                            break;
                    }
                    break;
                case BATALLA:
                    switch (dato_800EA1C0) {
                        case 1:
                            funcion_800C3448(0x100100FF);
                            funcion_800C3448(0x110100FF);
                            funcion_800C5278(5U);
                            funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF9, 0x26));
                            reproducir_secuencia2(SEC_MENU_RESULTADOS_PANTALLA_VICTORIA_VS);
                            dato_800EA0EC[id_jugador] = 2;
                            funcion_800C90F4(id_jugador, (jugadores[indice_ganador_jugador].id_personaje * 0x10) +
                                                        SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
                            break;
                        case 2:
                            if ((dato_800EA0EC[0] == 1) && (dato_800EA0EC[1] == 1) && (dato_800EA0EC[2] == 1)) {
                                funcion_800C5278(5U);
                                funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0x80, 0x26));
                                reproducir_secuencia2(SEC_MENU_RESULTADOS_PANTALLA_VICTORIA_VS);
                                dato_800EA0EC[id_jugador] = 2;
                                funcion_800C90F4(id_jugador, (jugadores[indice_ganador_jugador].id_personaje * 0x10) +
                                                            SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
                            }
                            break;
                        case 3:
                            if ((dato_800EA0EC[0] == 1) && (dato_800EA0EC[1] == 1) && (dato_800EA0EC[2] == 1) &&
                                (dato_800EA0EC[3] == 1)) {
                                funcion_800C5278(5U);
                                funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0x80, 0x26));
                                reproducir_secuencia2(SEC_MENU_RESULTADOS_PANTALLA_VICTORIA_VS);
                                dato_800EA0EC[id_jugador] = 2;
                                funcion_800C90F4(id_jugador, (jugadores[indice_ganador_jugador].id_personaje * 0x10) +
                                                            SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
                            }
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        if (dato_800E9EA4[id_jugador] == 0x0000001E) {
            switch (seleccion_modo) {
                case BATALLA:
                    break;
                case GRAN_PREMIO:
                    if (jugadores[id_jugador].puesto_actual == 0) {
                        dato_800EA0EC[id_jugador] = 2;
                        funcion_800C90F4(id_jugador,
                                      (jugadores[id_jugador].id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x07));
                    } else if (jugadores[id_jugador].puesto_actual < 4) {
                        dato_800EA0EC[id_jugador] = 2;
                        funcion_800C90F4(id_jugador,
                                      (jugadores[id_jugador].id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
                    } else {
                        dato_800EA0EC[id_jugador] = 2;
                        funcion_800C90F4(id_jugador,
                                      (jugadores[id_jugador].id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x03));
                    }
                    break;
                case VERSUS:
                    if (jugadores[id_jugador].puesto_actual == 0) {
                        dato_800EA0EC[id_jugador] = 2;
                        funcion_800C90F4(id_jugador,
                                      (jugadores[id_jugador].id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
                    }
                    break;
                case CONTRARRELOJ:
                    if (dato_801657E5 == 1) {
                        dato_800EA0EC[id_jugador] = 2;
                        funcion_800C90F4(id_jugador,
                                      (jugadores[id_jugador].id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x07));
                    } else if (dato_8018ED90 == (u8) 1) {
                        dato_800EA0EC[id_jugador] = 2;
                        funcion_800C90F4(id_jugador,
                                      (jugadores[id_jugador].id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
                    }
                    break;
            }
        }
        switch (seleccion_modo) {
            case GRAN_PREMIO:
                if (jugadores[id_jugador].puesto_actual == 0) {
                    if (dato_800E9EA4[id_jugador] >= 0x15F) {
                        if (dato_800E9EA4[id_jugador] == 0x0000015F) {
                            funcion_800C9D0C(id_jugador);
                        }
                    } else {
                        dato_800EA130[id_jugador] = (f32) dato_800E9EA4[id_jugador] / 400.0f;
                    }
                } else if (jugadores[id_jugador].puesto_actual < 4) {
                    if (dato_800E9EA4[id_jugador] >= 0x15F) {
                        if (dato_800E9EA4[id_jugador] == 0x0000015F) {
                            funcion_800C9D0C(id_jugador);
                        }
                    } else {
                        dato_800EA130[id_jugador] = (f32) dato_800E9EA4[id_jugador] / 400.0f;
                    }
                } else if (dato_800E9EA4[id_jugador] >= 0x12D) {
                    if (dato_800E9EA4[id_jugador] == 0x0000012D) {
                        funcion_800C97C4(id_jugador);
                    }
                } else {
                    dato_800EA130[id_jugador] = (f32) dato_800E9EA4[id_jugador] / 330.0f;
                }
                break;
            case VERSUS:
                if (dato_800EA1C0 == (u8) 1) {
                    if (dato_800E9EA4[id_jugador] >= 0x65) {
                        if (dato_800E9EA4[id_jugador] == 0x00000065) {
                            funcion_800C9D0C(id_jugador);
                        }
                    } else {
                        dato_800EA130[id_jugador] = (f32) dato_800E9EA4[id_jugador] / 120.0f;
                    }
                } else if (dato_800E9EA4[id_jugador] >= 0x65) {
                    if (dato_800E9EA4[id_jugador] == 0x00000065) {
                        funcion_800C97C4(id_jugador);
                    }
                } else {
                    dato_800EA130[id_jugador] = (f32) dato_800E9EA4[id_jugador] / 120.0f;
                }
            case CONTRARRELOJ:
                if (dato_800E9EA4[id_jugador] >= 0x12D) {
                    if (dato_800E9EA4[id_jugador] == 0x0000012D) {
                        funcion_800C9D0C(0U);
                    }
                } else {
                    dato_800EA130[id_jugador] = (f32) dato_800E9EA4[id_jugador] / 350.0f;
                }
                break;
            case BATALLA:
                if (dato_800E9EA4[id_jugador] >= 0x65) {
                    if (dato_800E9EA4[id_jugador] == 0x00000065) {
                        funcion_800C97C4(id_jugador);
                    }
                } else {
                    dato_800EA130[id_jugador] = (f32) dato_800E9EA4[id_jugador] / 120.0f;
                }
                break;
        }
    }
}

void funcion_800C847C(u8 id_jugador) {
    if ((jugadores[id_jugador].oob_props & BAJO_OOB_O_NIVEL_FLUIDO) == BAJO_OOB_O_NIVEL_FLUIDO) {
        if (dato_800E9F74[id_jugador] == 0) {
            if ((s32) dato_800EA1C0 < 2) {
                funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xF9, 0x26));
            } else {
                funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0x80, 0x26));
            }
            funcion_800C97C4(id_jugador);
            dato_800E9F74[id_jugador] = 1;
            funcion_800C94A4(id_jugador);
            if (((id_circuito_actual == CIRCUITO_CHOCO_MOUNTAIN) || (id_circuito_actual == CIRCUITO_BOWSER_CASTLE) ||
                 (id_circuito_actual == CIRCUITO_BANSHEE_BOARDWALK) || (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) ||
                 (id_circuito_actual == CIRCUITO_FRAPPE_SNOWLAND) || (id_circuito_actual == CIRCUITO_KOOPA_BEACH) ||
                 (id_circuito_actual == CIRCUITO_ROYAL_RACEWAY) || (id_circuito_actual == CIRCUITO_SHERBET_LAND) ||
                 (id_circuito_actual == CIRCUITO_DK_JUNGLE) || (id_circuito_actual == CIRCUITO_BIG_DONUT)) &&
                (dato_800EA0EC[id_jugador] == 0)) {
                reproducir_sonido((jugadores[id_jugador].id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x05),
                           &dato_800E9F7C[id_jugador].pos, id_jugador, &dato_800EA1D4, &dato_800EA1D4,
                           (s8*) &dato_800E9F7C[id_jugador].desconocido_14);
            }
        }
    } else {
        if (dato_800E9F74[id_jugador] == 1) {
            funcion_800C97C4(id_jugador);
            dato_800E9F74[id_jugador] = 2;
            funcion_800C94A4(id_jugador);
            dato_800E9F74[id_jugador] = 0;
            if ((id_circuito_actual == CIRCUITO_KOOPA_BEACH) && (dato_800EA0EC[id_jugador] == 0)) {
                reproducir_sonido((jugadores[id_jugador].id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x08),
                           &dato_800E9F7C[id_jugador].pos, id_jugador, &dato_800EA1D4, &dato_800EA1D4,
                           (s8*) &dato_800E9F7C[id_jugador].desconocido_14);
            }
        }
    }
}
