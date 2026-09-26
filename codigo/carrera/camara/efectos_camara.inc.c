// Efectos camara

void funcion_8001EE98(Jugador* jugador, Camara* camara, s8 index) {
    s32 indice_camara;

    if (camara == camara1) {
        indice_camara = 0;
    }
    if (camara == camara2) {
        indice_camara = 1;
    }
    if (camara == camara3) {
        indice_camara = 2;
    }
    if (camara == camara4) {
        indice_camara = 3;
    }
    switch (seleccion_modo) {
        case GRAN_PREMIO:
            if (((jugador->type & MODO_CINEMATICA_JUGADOR) == MODO_CINEMATICA_JUGADOR) || (modo_demo == 1)) { dato_80152300[indice_camara] = 3;
            } else if (juego_en_pausa == 1) {
                funcion_8001A0A4(&dato_80152300[indice_camara], camara, jugador, index, indice_camara);
            } else {
                funcion_8001A0DC(&dato_80152300[indice_camara], camara, jugador, index, indice_camara);
            }
            break;
        case BATALLA:
            if ((modo_demo == 1) || ((dato_8015F894 == 2) && (dato_80164A89 == 1))) {
                if (dato_80164A88 == 0) {
                    funcion_80019ED0();
                }
                dato_80164A88 = 1;
                dato_80152300[0] = 3;
                dato_80152300[1] = 3;
                dato_80152300[2] = 3;
                dato_80152300[3] = 3;
            } else {
                dato_80164A88 = 0;
                if (juego_en_pausa == 1) {
                    funcion_8001A0A4(&dato_80152300[indice_camara], camara, jugador, index, indice_camara);
                } else {
                    funcion_8001A0DC(&dato_80152300[indice_camara], camara, jugador, index, indice_camara);
                }
                dato_80152300[indice_camara] = 9;
            }
            break;
        case CONTRARRELOJ:
            if (((jugador_uno->type & MODO_CINEMATICA_JUGADOR) == MODO_CINEMATICA_JUGADOR) || (modo_demo == 1)) {
                dato_80152300[0] = 3;
                dato_80152300[1] = 3;
                dato_80152300[2] = 3;
                dato_80152300[3] = 3;
            } else {
                if (juego_en_pausa == 1) {
                    funcion_8001A0A4(&dato_80152300[indice_camara], camara, jugador, index, indice_camara);
                } else {
                    funcion_8001A0DC(&dato_80152300[indice_camara], camara, jugador, index, indice_camara);
                }
                dato_80152300[indice_camara] = 1;
            }
            break;
        case VERSUS:
            if (((jugador->type & MODO_CINEMATICA_JUGADOR) == MODO_CINEMATICA_JUGADOR) || (modo_demo == 1) ||
                (dato_8015F894 == 2)) {
                dato_80152300[indice_camara] = 3;
            } else {
                if (juego_en_pausa == 1) {
                    funcion_8001A0A4(&dato_80152300[indice_camara], camara, jugador, index, indice_camara);
                } else {
                    funcion_8001A0DC(&dato_80152300[indice_camara], camara, jugador, index, indice_camara);
                }
                dato_80152300[indice_camara] = 1;
            }
            break;
    }
    if (juego_en_pausa == 0) {
        switch (dato_80152300[indice_camara]) {
            case 3:
                funcion_8001A588(&dato_80152300[indice_camara], camara, jugador, index, indice_camara);
                break;
            case 1:
                if (((jugador->lakitu_props & LAKITU_RECUPERACION) == LAKITU_RECUPERACION) ||
                    ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU)) {
                    funcion_8001E8E8(camara, jugador, index);
                    break;
                }
                funcion_8001E45C(camara, jugador, index);
                break;
            case 8:
                funcion_8001E0C4(camara, jugador, index);
                funcion_8001F87C(indice_camara);
                break;
            case 9:
                if (((jugador->lakitu_props & LAKITU_RECUPERACION) == LAKITU_RECUPERACION) ||
                    ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == MANTENIDO_POR_LAKITU)) {
                    funcion_8001E8E8(camara, jugador, index);
                    break;
                }
                funcion_8001EA0C(camara, jugador, index);
                break;
        }
    }
}

void funcion_8001F394(Jugador* jugador, f32* parametro1) {
    f32 variable_f0;
    SIN_USO s32 relleno;
    s32 indice_jugador;
    SIN_USO s32 relleno2;
    Camara* camara = &camaras[0];

    if (jugador == jugador_uno) {
        indice_jugador = 0;
    }
    if (jugador == jugador_dos) {
        indice_jugador = 1;
    }
    if (jugador == jugador_tres) {
        indice_jugador = 2;
    }
    if (jugador == jugador_cuatro) {
        indice_jugador = 3;
    }

    if (dato_80164A08[indice_jugador] == 0) {
        if (jugador->disparadores & EFECTO_ITEM_ARRASTRE) {
            dato_80164A08[indice_jugador] = 1;
        }
        if ((jugador->efectos & EFECTO_HONGO) == EFECTO_HONGO) {
            dato_80164A08[indice_jugador] = 2;
        }
        if ((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) == IMPULSO_RAMPA_ASFALTO_EFECTO) {
            dato_80164A08[indice_jugador] = 3;
        }
        if ((jugador->disparadores & THWOMP_DISPARADOR_APLASTAMIENTO) == THWOMP_DISPARADOR_APLASTAMIENTO) {
            dato_80164A08[indice_jugador] = 4;
        }
        if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
            ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO)) {
            dato_80164A08[indice_jugador] = 5;
        }
        dato_80164498[indice_jugador] = 0.0f;
    }
    switch (dato_80164A08[indice_jugador]) {
        case 1:
            if (jugador->disparadores & EFECTO_ITEM_ARRASTRE) {
                mover_f32_hacia(&dato_80164498[indice_jugador], 20.0f, 0.2f);
            } else {
                if (dato_80164498[indice_jugador] > 1.0f) {
                    dato_80164498[indice_jugador] -= 1.0f;
                } else {
                    dato_80164A08[indice_jugador] = 0;
                    dato_80164498[indice_jugador] = 0.0f;
                }
            }
            break;
        case 2:
            if ((jugador->efectos & EFECTO_HONGO) == EFECTO_HONGO) {
                if (jugador->temporizador_impulso != 0) {
                    mover_f32_hacia(&dato_80164498[indice_jugador], 8.0f, 0.2f);
                }
            } else {
                if (dato_80164498[indice_jugador] > 1.0f) {
                    dato_80164498[indice_jugador] -= 2.0f;
                } else {
                    dato_80164A08[indice_jugador] = 0;
                    dato_80164498[indice_jugador] = 0.0f;
                }
            }
            break;
        case 3:
            if (((jugador->efectos & IMPULSO_RAMPA_ASFALTO_EFECTO) == IMPULSO_RAMPA_ASFALTO_EFECTO) &&
                ((jugador->efectos & EFECTO_EN_EL_AIRE) == EFECTO_EN_EL_AIRE)) {
                mover_f32_hacia(&dato_80164498[indice_jugador], 20.0f, 0.1f);
            } else {
                if (dato_80164498[indice_jugador] > 1.0f) {
                    dato_80164498[indice_jugador] -= 1.0f;
                } else {
                    dato_80164A08[indice_jugador] = 0;
                    dato_80164498[indice_jugador] = 0.0f;
                }
            }
            break;
        case 4:
            if ((jugador->disparadores & THWOMP_DISPARADOR_APLASTAMIENTO) == THWOMP_DISPARADOR_APLASTAMIENTO) {
                mover_f32_hacia(&dato_80164498[indice_jugador], 25.0f, 1.0f);
            } else {
                if (dato_80164498[indice_jugador] > 1.0f) {
                    dato_80164498[indice_jugador] -= 2.0f;
                } else {
                    dato_80164A08[indice_jugador] = 0;
                    dato_80164498[indice_jugador] = 0.0f;
                }
            }
            break;
        case 5:
            if (((jugador->efectos & EFECTO_TROMPO_BANANA) == EFECTO_TROMPO_BANANA) ||
                ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) == EFECTO_TROMPO_CONDUCIENDO)) {
                mover_f32_hacia(&dato_80164498[indice_jugador], 18.0f, 0.2f);
            } else {
                if (dato_80164498[indice_jugador] > 1.0f) {
                    dato_80164498[indice_jugador] -= 2.0f;
                } else {
                    dato_80164A08[indice_jugador] = 0;
                    dato_80164498[indice_jugador] = 0.0f;
                }
            }
            break;
    }
    switch (modo_pantalla_activo) {
        case MODO_PANTALLA_1P:
            if (dato_80164A28 == 1) {
                dato_80164498[indice_jugador] = 40.0f;
            }
            if (dato_80164A28 == 2) {
                if (dato_80164498[indice_jugador] >= 0.0f) {
                    dato_80164498[indice_jugador] -= 0.8;
                }
                if (dato_80164498[indice_jugador] <= 0.0f) {
                    dato_80164A28 = 0;
                    dato_80164498[indice_jugador] = 0.0f;
                }
            }
            variable_f0 = funcion_80014EE4(*parametro1, indice_jugador);
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            variable_f0 = funcion_80014EE4(*parametro1, indice_jugador);
            break;
    }
    *parametro1 = variable_f0;
    camara += indice_jugador;
    camara->desconocido_B4 = variable_f0;
}

void funcion_8001F87C(s32 id_camara) {
    s32 indice_jugador;
    s32 id = id_camara;

    if (jugador_uno) {}
    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
        if (seleccion_modo == GRAN_PREMIO) {
            for (indice_jugador = 0; indice_jugador < JUGADORES_NUM; indice_jugador++) {
                if ((jugador_uno[indice_jugador].type & PREPARACION_JUGADOR) ||
                    (jugador_uno[indice_jugador].type & jugador_desconocido_0_x80)) {
                    break;
                }
                if (indice_jugador == 7) {
                    dato_80164A2C += 1;
                }
                if ((indice_jugador == 7) && (dato_80164A2C == 0x0000003C)) {
                    dato_80164A28 = 2;
                    dato_80152300[id] = 1;
                    camaras[id].rot[1] = jugador_uno[indice_jugador].rotacion[1];
                    camaras[id].desconocido_2C = jugador_uno[indice_jugador].rotacion[1];
                }
            }
        }
    }
}
