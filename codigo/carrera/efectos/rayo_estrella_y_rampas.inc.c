// Rayo estrella y rampas

void quitar_efecto_rayo(Jugador* jugador, SIN_USO s8 indice_jugador) {
    mover_f32_hacia(&jugador->size, 1.0f, 0.1f);
    mover_f32_hacia(&jugador->tamanio_caja_envolvente, kart_envolvente_caja_tamanio_tabla[jugador->id_personaje], 0.1f);

    jugador->efectos &= ~EFECTO_RAYO;
    jugador->size = 1.0f;
    jugador->tamanio_caja_envolvente = kart_envolvente_caja_tamanio_tabla[jugador->id_personaje];
    jugador->desconocido_DB4.unk10 = 3.0f;
    jugador->desconocido_DB4.desconocido2 = 0;
    jugador->efectos |= EFECTO_APLASTAMIENTO_PUBLICAR;

    if ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO) {
        jugador->rotacion[1] = jugador->desconocido_0AE;
    }

    jugador->efectos &= ~EFECTO_GOLPE_RAYO;
}

void funcion_8008E4A4(Jugador* jugador, s8 indice_jugador) {
    jugador->desconocido_206 = 0;
    jugador->acel_pendiente = 0;
    jugador->desconocido_0C0 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_0C2 = 0xF;
    jugador->desconocido_042 += GRADOS(15);
    jugador->desconocido_08C = 0.0f;
    jugador->actual_rapidez = 0.0f;
    jugador->velocidad[0] = 0.0f;
    jugador->velocidad[2] = 0.0f;
    jugador->efectos &= ~(EFECTO_TROMPO_BANANA | EFECTO_TROMPO_CONDUCIENDO);

    if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
        ++jugador->desconocido_0E0;
    }

    if (jugador->desconocido_0E0 == 3) {
        jugador->efectos &= ~EFECTO_ERROR_EXPLOSION;
        jugador->desconocido_0A8 = 0;
        jugador->desconocido_236 = 0;
        dato_80165190[0][indice_jugador] = 1;
        dato_80165190[1][indice_jugador] = 1;
        dato_80165190[2][indice_jugador] = 1;
        dato_80165190[3][indice_jugador] = 1;
        jugador->desconocido_042 = 0;
        jugador->type &= ~jugador_desconocido_0_x80;

        if ((es_jugador_triple_a_boton_combo[indice_jugador] == true) && ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) {
            jugador->actual_rapidez += 100.0f;
        }
        if (seleccion_modo == BATALLA) {
            sacar_globo_jugador(jugador, indice_jugador);
        }
    } else {
        jugador->desconocido_0A8 += 0x80;
        if (jugador->desconocido_0A8 >= 0x2000) {
            jugador->desconocido_0A8 = 0;
            --jugador->desconocido_236;
            if (jugador->desconocido_236 == 0) {
                jugador->efectos &= ~EFECTO_ERROR_EXPLOSION;
                jugador->desconocido_236 = 0;
                dato_80165190[0][indice_jugador] = 1;
                dato_80165190[1][indice_jugador] = 1;
                dato_80165190[2][indice_jugador] = 1;
                dato_80165190[3][indice_jugador] = 1;
                jugador->desconocido_042 = 0;

                if (seleccion_modo == BATALLA) {
                    sacar_globo_jugador(jugador, indice_jugador);
                }
                if ((es_jugador_triple_a_boton_combo[indice_jugador] == true) &&
                    ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) {
                    jugador->actual_rapidez += 100.0f;
                }

                jugador->type &= ~jugador_desconocido_0_x80;
            }
        }
    }
}

void vuelco_vertical_disparador(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);
    funcion_8008C310(jugador);

    jugador->desconocido_0A8 = 0;
    jugador->efectos |= EFECTO_ERROR_EXPLOSION;
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    jugador->tiron_salto_kart = 0.0f;
    jugador->aceleracion_salto_kart = 0.0f;
    jugador->velocidad_salto_kart = 0.0f;
    jugador->tiron_salto_kart = dato_800E3730[jugador->id_personaje];
    jugador->velocidad_salto_kart = dato_800E3710[jugador->id_personaje];
    jugador->desconocido_236 = 4;
    jugador->desconocido_042 = 0;
    jugador->desconocido_0E0 = 0;

    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        if (((seleccion_modo == VERSUS) && ((jugador->type & CPU_JUGADOR) != 0)) && (!modo_demo)) {
            funcion_800CA24C(indice_jugador);
        }

        if (1) {}

        funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008005);
        if (((seleccion_modo == VERSUS) && ((jugador->type & CPU_JUGADOR) != 0)) && (!modo_demo)) {
            funcion_800CA24C(indice_jugador);
        }
        funcion_800C9060(indice_jugador, SONIDO_EXPLOSION_ACCION);
    } else {
        reproducir_cpu_efecto_sonido(indice_jugador, jugador);
    }

    jugador->disparadores &= ~(DISPARADOR_VUELCO_VERTICAL | GOLPE_PALETA_BARCO_DISPARADOR);
    jugador->graficos_kart |= ERROR_;
    temporizador_impulso_triple_a_combo[indice_jugador] = 0;
    es_jugador_triple_a_boton_combo[indice_jugador] = false;
    interruptor_cantidad_a[indice_jugador] = 0;
    frame_desde_ultimo_combo_a[indice_jugador] = 0;
}

void funcion_8008E884(Jugador* jugador, s8 indice_jugador) {
    jugador->efectos &= ~EFECTO_ERROR_EXPLOSION;
    jugador->desconocido_0A8 = 0;
    jugador->desconocido_236 = 0;
    dato_80165190[0][indice_jugador] = 1;
    dato_80165190[1][indice_jugador] = 1;
    dato_80165190[2][indice_jugador] = 1;
    dato_80165190[3][indice_jugador] = 1;
    jugador->desconocido_042 = 0;
}

void aplicar_golpe_por_efecto_estrella(Jugador* jugador, s8 indice_jugador) {
    jugador->desconocido_206 = 0;
    jugador->acel_pendiente = 0;
    jugador->desconocido_0C0 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_0C2 = 0xF;
    jugador->desconocido_042 += GRADOS(15);
    jugador->desconocido_08C /= 2;
    jugador->actual_rapidez = 0.0f;
    jugador->efectos &= ~(EFECTO_TROMPO_BANANA | EFECTO_TROMPO_CONDUCIENDO);

    if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
        ++jugador->desconocido_0E0;
    }

    if (jugador->desconocido_0E0 == 4) {
        jugador->efectos &= ~GOLPE_POR_EFECTO_ESTRELLA;
        jugador->desconocido_0A8 = 0;
        jugador->desconocido_236 = 0;
        dato_80165190[3][indice_jugador] = 1;
        dato_80165190[0][indice_jugador] = 1;
        dato_80165190[1][indice_jugador] = 1;
        dato_80165190[2][indice_jugador] = 1;
        jugador->desconocido_042 = 0;

        if ((es_jugador_triple_a_boton_combo[indice_jugador] == true) && ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) {
            jugador->actual_rapidez += 100.0f;
        }

        if (seleccion_modo == BATALLA) {
            sacar_globo_jugador(jugador, indice_jugador);
        }
    } else {
        jugador->desconocido_0A8 = (s16) (jugador->desconocido_0A8 + 0x90);
        if (((s32) jugador->desconocido_0A8) >= 0x2000) {
            jugador->desconocido_0A8 = 0;
            --jugador->desconocido_236;
            if (jugador->desconocido_236 == 0) {
                jugador->efectos &= ~GOLPE_POR_EFECTO_ESTRELLA;
                jugador->desconocido_236 = 0;
                dato_80165190[0][indice_jugador] = 1;
                dato_80165190[1][indice_jugador] = 1;
                dato_80165190[2][indice_jugador] = 1;
                dato_80165190[3][indice_jugador] = 1;
                jugador->desconocido_042 = 0;
                if ((es_jugador_triple_a_boton_combo[indice_jugador] == true) &&
                    ((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR)) {
                    jugador->actual_rapidez += 100.0f;
                }

                if (seleccion_modo == BATALLA) {
                    sacar_globo_jugador(jugador, indice_jugador);
                }
            }
        }
    }
}

void vuelco_alto_disparador(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);
    funcion_8008C310(jugador);

    jugador->desconocido_0A8 = 0;
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    jugador->tiron_salto_kart = 0.0f;
    jugador->aceleracion_salto_kart = 0.0f;
    jugador->velocidad_salto_kart = 0.0f;
    jugador->tiron_salto_kart = dato_800E3730[jugador->id_personaje];
    jugador->velocidad_salto_kart = dato_800E3710[jugador->id_personaje];
    jugador->desconocido_236 = 4;
    jugador->desconocido_042 = 0;
    jugador->desconocido_0E0 = 0;

    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008005);
        funcion_800C9060(indice_jugador, SONIDO_EXPLOSION_ACCION);
    } else {
        reproducir_cpu_efecto_sonido(indice_jugador, jugador);
    }

    jugador->efectos |= GOLPE_POR_EFECTO_ESTRELLA;
    jugador->graficos_kart |= ERROR_;
    jugador->disparadores &= ~(GOLPE_POR_DISPARADOR_ESTRELLA | DISPARADOR_VUELCO_ALTO);

    temporizador_impulso_triple_a_combo[indice_jugador] = 0;
    es_jugador_triple_a_boton_combo[indice_jugador] = false;
    interruptor_cantidad_a[indice_jugador] = 0;
    frame_desde_ultimo_combo_a[indice_jugador] = 0;
}

void quitar_golpe_por_efecto_estrella(Jugador* jugador, s8 indice_jugador) {
    jugador->efectos &= ~GOLPE_POR_EFECTO_ESTRELLA;
    jugador->desconocido_0A8 = 0;
    jugador->desconocido_236 = 0;
    dato_80165190[0][indice_jugador] = 1;
    dato_80165190[1][indice_jugador] = 1;
    dato_80165190[2][indice_jugador] = 1;
    dato_80165190[3][indice_jugador] = 1;
    jugador->desconocido_042 = 0;
}

void disparador_asfalto_rampa_impulso(Jugador* jugador, s8 id_jugador) {
    limpiar_efecto(jugador, id_jugador);

    jugador->efectos |= IMPULSO_RAMPA_ASFALTO_EFECTO;
    jugador->disparadores &= ~IMPULSO_RAMPA_ASFALTO_DISPARADOR;
    jugador->desconocido_DB4.desconocido0 = 0;
    jugador->desconocido_DB4.desconocido8 = 8.0f;
    if (dato_8015F890 != 1) {
        if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) && ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) == 0)) {
            funcion_800C90F4(id_jugador, (jugador->id_personaje * 0x10) + 0x29008001);
            funcion_800C9060(id_jugador, 0x1900A40B);
        }
    } else if (jugador == jugador_uno) {
        funcion_800C90F4(id_jugador, (jugador->id_personaje * 0x10) + 0x29008001);
        funcion_800C9060(id_jugador, 0x1900A40B);
    }
    jugador->kart_props &= ~ARRIBA_ATRAS;
    jugador->efectos &= ~EFECTO_GIRO_AB;
}

void aplicar_impulso_rampa_asfalto_efecto(Jugador* jugador) {
    f64 temporal_f0;

    jugador->actual_rapidez = jugador->arriba_rapidez;
    if ((u16) jugador->desconocido_256 > 0) {
        jugador->actual_rapidez = 0.0f;
    }
    if ((jugador->tipo_superficie != ASFALTO_RAMPA_IMPULSO) && ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE)) {
        mover_f32_hacia(&jugador->potencia_impulso, 0, 1.0f);
    } else {
        mover_f32_hacia(&jugador->potencia_impulso, 400.0f, 0.01f);
    }
    if (jugador->potencia_impulso <= 1.0f) {
        jugador->efectos &= ~IMPULSO_RAMPA_ASFALTO_EFECTO;
        jugador->potencia_impulso = 0.0f;
        if (jugador->desconocido_0C2 >= 0x33) {
            temporal_f0 = 0.7;
            jugador->actual_rapidez = (jugador->actual_rapidez * temporal_f0);
            jugador->desconocido_08C = (jugador->desconocido_08C * temporal_f0);
        }
    }
}

void quitar_impulso_rampa_asfalto_efecto(Jugador* jugador) {
    jugador->efectos &= ~IMPULSO_RAMPA_ASFALTO_EFECTO;
    jugador->potencia_impulso = 0.0f;
}

void disparador_madera_rampa_impulso(Jugador* jugador, s8 id_jugador) {
    limpiar_efecto(jugador, id_jugador);

    jugador->efectos |= IMPULSO_RAMPA_MADERA_EFECTO;
    jugador->disparadores &= ~IMPULSO_RAMPA_MADERA_DISPARADOR;

    if (dato_8015F890 != 1) {
        if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) && ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) == 0)) {
            funcion_800C90F4(id_jugador, (jugador->id_personaje * 0x10) + 0x29008001);
            funcion_800C9060(id_jugador, 0x1900A40B);
        }
    } else if (jugador == jugador_uno) {
        funcion_800C90F4(id_jugador, (jugador->id_personaje * 0x10) + 0x29008001);
        funcion_800C9060(id_jugador, 0x1900A40B);
    }

    jugador->kart_props &= ~ARRIBA_ATRAS;
    jugador->efectos &= ~EFECTO_GIRO_AB;
}

void aplicar_impulso_rampa_madera_efecto(Jugador* jugador) {
    jugador->actual_rapidez = tabla_rapidez_arriba[0][jugador->id_personaje];

    if ((jugador->tipo_superficie != MADERA_RAMPA_IMPULSO) && ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE)) {
        mover_f32_hacia(&jugador->potencia_impulso, 0, 1.0f);
    } else {
        mover_f32_hacia(&jugador->potencia_impulso, 300.0f, 0.1f);
    }

    if (jugador->potencia_impulso <= 1.0f) {
        jugador->efectos &= ~IMPULSO_RAMPA_MADERA_EFECTO;
        jugador->potencia_impulso = 0.0f;
        jugador->actual_rapidez /= 2;
        jugador->desconocido_08C /= 2;
    }
}

void quitar_impulso_rampa_madera_efecto(Jugador* jugador) {
    jugador->efectos &= ~IMPULSO_RAMPA_MADERA_EFECTO;
    jugador->potencia_impulso = 0.0f;
}

void funcion_8008F104(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);

    jugador->desconocido_0AE = jugador->rotacion[1];
    jugador->desconocido_0B2 = 2;
    jugador->desconocido_0C0 = 0;
    jugador->posicion_giro = 0;
    jugador->efectos |= TEMPRANO_INICIO_TROMPO_EFECTO;
    jugador->desconocido_078 = 0;
    dato_8018D920[indice_jugador] = -0x8000;

    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008003);
    }
}

void funcion_8008F1B8(Jugador* jugador, s8 parametro1) {
    s16 temporal_;

    jugador->desconocido_08C = (jugador->desconocido_210 * 0.05);
    if (jugador->desconocido_0B2 < 0) {
        if ((jugador->kart_props & IZQUIERDA_TROMPO_TEMPRANO) == IZQUIERDA_TROMPO_TEMPRANO) {
            jugador->rotacion[1] += GRADOS(1);
            dato_8018D920[parametro1] += GRADOS(1);

            temporal_ = ((u16) dato_8018D920[parametro1] / GRADOS(1));
            if (temporal_ == 180) {
                jugador->efectos &= ~TEMPRANO_INICIO_TROMPO_EFECTO;
                jugador->type &= ~jugador_desconocido_0_x80;
                jugador->actual_rapidez /= 3.0f;
            }
        } else {

            jugador->rotacion[1] -= GRADOS(1);
            dato_8018D920[parametro1] -= GRADOS(1);
            temporal_ = ((u16) dato_8018D920[parametro1] / GRADOS(1));
            if (temporal_ == 180) {
                jugador->efectos &= ~TEMPRANO_INICIO_TROMPO_EFECTO;
                jugador->type &= ~jugador_desconocido_0_x80;
                jugador->actual_rapidez /= 3.0f;
            }
        }
    } else {
        if ((jugador->desconocido_0B2 & 1) != 0) {
            jugador->rotacion[1] -= GRADOS(2);
            dato_8018D920[parametro1] -= GRADOS(2);
            temporal_ = ((u16) dato_8018D920[parametro1] / GRADOS(2));
            if (temporal_ < 71) {
                --jugador->desconocido_0B2;
            }
            jugador->kart_props |= IZQUIERDA_TROMPO_TEMPRANO;
            jugador->kart_props &= ~DERECHA_TROMPO_TEMPRANO;
            return;
        }
        jugador->rotacion[1] += GRADOS(2);
        dato_8018D920[parametro1] += GRADOS(2);
        temporal_ = ((u16) dato_8018D920[parametro1] / GRADOS(2));
        if (temporal_ >= 110) {
            --jugador->desconocido_0B2;
        }
        jugador->kart_props |= DERECHA_TROMPO_TEMPRANO;
        jugador->kart_props &= ~IZQUIERDA_TROMPO_TEMPRANO;
    }
}

void funcion_8008F3E0(Jugador* jugador) {
    jugador->efectos &= ~TEMPRANO_INICIO_TROMPO_EFECTO;
}

void funcion_8008F3F4(Jugador* jugador, SIN_USO s8 parametro1) {
    jugador->desconocido_0A8 += 0x80;
    jugador->desconocido_042 += GRADOS(10);
    jugador->posicion_giro = 0;
    jugador->actual_rapidez = 0.0f;
    jugador->desconocido_08C /= 2;
    if (jugador->desconocido_0A8 >= 0x2000) {
        jugador->desconocido_0A8 = 0;
        --jugador->desconocido_236;
        if (jugador->desconocido_236 == 0) {
            jugador->efectos &= ~EFECTO_VUELCO_TERRENO;
            funcion_80090778(jugador);
            funcion_80090868(jugador);
        }
    }
}

void funcion_8008F494(Jugador* jugador, s8 indice_jugador) {
    if ((((jugador->efectos & EFECTO_TROMPO_BANANA) != 0) || ((jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) != 0) ||
         ((jugador->efectos & EFECTO_ERROR_EXPLOSION)) || ((jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA)) ||
         ((jugador->efectos & GOLPE_POR_CAPARAZON_VERDE_EFECTO) != 0)) &&
        (seleccion_modo == BATALLA)) {
        jugador->kart_props |= VARIABLE_BATALLA_DESCONOCIDO;
    }

    limpiar_efecto(jugador, indice_jugador);
    funcion_8008F86C(jugador, indice_jugador);

    jugador->desconocido_0A8 = 0;
    jugador->efectos |= EFECTO_VUELCO_TERRENO;
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    jugador->desconocido_236 = 0x1E;
    jugador->desconocido_042 = 0;

    if (((jugador->type & HUMANO_JUGADOR) != 0) && ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) == 0) &&
        ((jugador->lakitu_props & MANTENIDO_POR_LAKITU) == 0) && ((jugador->oob_props & BAJO_OOB_O_NIVEL_FLUIDO) == 0) &&
        ((jugador->oob_props & OOB_PASADA_O_NIVEL_FLUIDO) == 0)) {
        funcion_800C90F4(indice_jugador, (jugador->id_personaje * 0x10) + 0x29008004);
    }
}

void funcion_8008F5A4(Jugador* jugador, s8 indice_jugador) {

    if ((jugador->kart_props & VARIABLE_BATALLA_DESCONOCIDO) != 0) {
        sacar_globo_jugador(jugador, indice_jugador);
        jugador->kart_props &= ~VARIABLE_BATALLA_DESCONOCIDO;
    }

    jugador->desconocido_206 = 0;
    jugador->acel_pendiente = 0;
    jugador->efectos &= ~EFECTO_VUELCO_TERRENO;
    jugador->desconocido_0A8 = 0;
    jugador->desconocido_0C0 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_236 = 0;
    jugador->desconocido_078 = 0;
    jugador->actual_rapidez = 0.0f;

    dato_80165190[0][indice_jugador] = 1;
    dato_80165190[1][indice_jugador] = 1;
    dato_80165190[2][indice_jugador] = 1;
    dato_80165190[3][indice_jugador] = 1;
    jugador->desconocido_042 = 0;
}

void aplicar_efecto_estrella(Jugador* jugador, s8 indice_jugador) {
    if (((s32) temporizador_circuito - jugador_estrella_efecto_inicio_tiempo[indice_jugador]) >= DURACION_EFECTO_ESTRELLA - 1) {
        dato_8018D900[indice_jugador] = 1;

        if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
            ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
            if (dato_8018D900[indice_jugador] == 1) {
                funcion_800CA730(indice_jugador);
                dato_8018D900[indice_jugador] = 0;
            }
        } else if (dato_8018D900[indice_jugador] == 1) {
            funcion_800CAACC((u8) indice_jugador);
            dato_8018D900[indice_jugador] = 0;
        }
    }

    if (((s32) temporizador_circuito - jugador_estrella_efecto_inicio_tiempo[indice_jugador]) >= DURACION_EFECTO_ESTRELLA) {
        jugador->efectos &= ~EFECTO_ESTRELLA;
    }
}

// Star item
void estrella_disparador(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);

    jugador->efectos |= EFECTO_ESTRELLA;
    jugador->disparadores &= ~DISPARADOR_ESTRELLA;
    jugador_estrella_efecto_inicio_tiempo[indice_jugador] = temporizador_circuito;
    dato_8018D900[indice_jugador] = 1;

    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        if (dato_8018D900[indice_jugador] == 1) {
            funcion_800CA59C(indice_jugador);
            dato_8018D900[indice_jugador] = 2;
        }
    } else if (dato_8018D900[indice_jugador] == 1) {
        funcion_800CA984(indice_jugador);
        dato_8018D900[indice_jugador] = 2;
    }
}

void funcion_8008F86C(Jugador* jugador, s8 indice_jugador) {
    jugador->efectos &= ~EFECTO_ESTRELLA;
    if (((jugador->type & HUMANO_JUGADOR) == HUMANO_JUGADOR) &&
        ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) != INVISIBLE_JUGADOR_O_BOMBA)) {
        funcion_800CA730(indice_jugador);
        return;
    }
    funcion_800CAACC(indice_jugador);
}

void aplicar_boo_efecto(Jugador* jugador, s8 indice_jugador) {
    s32 tiempo_transcurrido;
    tiempo_transcurrido = ((s32) temporizador_circuito) - jugador_boo_tiempo_inicio_efecto[indice_jugador];
    if (tiempo_transcurrido < BOO_DURACION_EFECTO) {
        jugador->alpha -= 2;

        if (jugador->alpha <= ALPHA_BOO_EFECTO) {
            jugador->alpha = ALPHA_BOO_EFECTO;
        }
        jugador_otro_pantallas_alpha[indice_jugador] -= 2;
        if (jugador_otro_pantallas_alpha[indice_jugador] <= 0) {
            jugador_otro_pantallas_alpha[indice_jugador] = 0;
        }
    } else {
        jugador->alpha += 4;
        if (jugador->alpha >= 0xF0) {
            jugador->alpha = ALPHA_MAX;
            jugador_otro_pantallas_alpha[indice_jugador] = ALPHA_MAX;
            jugador->efectos &= ~BOO_EFECTO;
            if ((jugador->type & HUMANO_JUGADOR) != 0) {
                funcion_800CB064(indice_jugador);
            }
        }

        jugador_otro_pantallas_alpha[indice_jugador] += 8;
        if (jugador_otro_pantallas_alpha[indice_jugador] >= 0xF0) {
            jugador_otro_pantallas_alpha[indice_jugador] = ALPHA_MAX;
            jugador->alpha = ALPHA_MAX;
            jugador->efectos &= ~BOO_EFECTO;
            if ((jugador->type & HUMANO_JUGADOR) != 0) {
                funcion_800CB064(indice_jugador);
            }
        }
    }
}

void disparador_boo(Jugador* jugador, s8 indice_jugador) {
    s16 temporal_v1;
    if ((jugador->type & HUMANO_JUGADOR) != 0) {
        jugador->kart_props |= INVISIBLE_VOLVERSE;

        for (temporal_v1 = 0; temporal_v1 < 10; ++temporal_v1) {
            jugador->pool_particula_0[temporal_v1].vivo_es = 0;
            jugador->pool_particula_0[temporal_v1].temporizador = 0;
            jugador->pool_particula_0[temporal_v1].type = 0;
        }
    }

    limpiar_efecto(jugador, indice_jugador);

    jugador->efectos |= BOO_EFECTO;
    jugador->disparadores &= ~BOO_DISPARADOR;
    jugador_boo_tiempo_inicio_efecto[indice_jugador] = temporizador_circuito;
    jugador_otro_pantallas_alpha[indice_jugador] = ALPHA_MAX;

    if ((jugador->type & HUMANO_JUGADOR) != 0) {
        funcion_800CAFC0(indice_jugador);
    }
}

void funcion_8008FB30(Jugador* jugador, s8 indice_jugador) {
    jugador->alpha += 8;
    if (jugador->alpha >= 0xF0) {
        jugador->alpha = ALPHA_MAX;
        jugador_otro_pantallas_alpha[indice_jugador] = ALPHA_MAX;

        jugador->efectos &= ~BOO_EFECTO;
        if ((jugador->type & HUMANO_JUGADOR) != 0) {
            funcion_800CB064(indice_jugador);
        }
    }

    jugador_otro_pantallas_alpha[indice_jugador] += 0x10;
    if (jugador_otro_pantallas_alpha[indice_jugador] >= 0xE0) {
        jugador_otro_pantallas_alpha[indice_jugador] = ALPHA_MAX;
        jugador->alpha = ALPHA_MAX;
        jugador->efectos &= ~BOO_EFECTO;
        if ((jugador->type & HUMANO_JUGADOR) != 0) {
            funcion_800CB064(indice_jugador);
        }
    }
}

void funcion_8008FC1C(Jugador* jugador) {
    s32 indice_jugador;

    if ((jugador->type & jugador_desconocido_0_x40) != 0) {
        indice_jugador = obtener_indice_jugador_para_jugador(jugador);
        jugador->type = (HUMANO_JUGADOR | SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        funcion_80056A94(indice_jugador);
    }
}

void funcion_8008FC64(Jugador* jugador, s8 parametro1) {
    jugador->alpha -= 4;
    if (jugador->alpha < 5) {
        jugador->alpha = ALPHA_MIN;
        jugador->disparadores &= ~EFECTO_BATALLA_PERDER;
        jugador->disparadores |= EFECTO_BOMBA_VOLVERSE;
        jugador->type |= jugador_desconocido_0_x40;

        funcion_8008FDA8(jugador, parametro1);
        funcion_800569F4(parametro1);
    }
}

void funcion_8008FCDC(Jugador* jugador, s8 indice_jugador) {
    jugador->alpha += 2;
    if (jugador->alpha >= 0xF0) {
        jugador->alpha = ALPHA_MAX;
        jugador->disparadores &= ~EFECTO_BOMBA_VOLVERSE;
    }

    funcion_80056A40(indice_jugador, (u32) jugador->alpha);
}

void funcion_8008FD4C(Jugador* jugador, SIN_USO s8 parametro1) {
    s16 temporal_v0;

    jugador->disparadores |= EFECTO_BATALLA_PERDER;
    jugador->kart_props |= INVISIBLE_VOLVERSE;

    for (temporal_v0 = 0; temporal_v0 < 10; ++temporal_v0) {
        jugador->pool_particula_0[temporal_v0].vivo_es = 0;
        jugador->pool_particula_0[temporal_v0].temporizador = 0;
        jugador->pool_particula_0[temporal_v0].type = 0;
    }
}
void funcion_8008FDA8(Jugador* jugador, SIN_USO s8 parametro1) {
    s16 temporal_v0;
    jugador->kart_props |= INVISIBLE_VOLVERSE;
    for (temporal_v0 = 0; temporal_v0 < 10; ++temporal_v0) {
        jugador->pool_particula_0[temporal_v0].vivo_es = 0;
        jugador->pool_particula_0[temporal_v0].temporizador = 0;
        jugador->pool_particula_0[temporal_v0].type = 0;
    }
}

void funcion_8008FDF4(Jugador* jugador, s8 indice_jugador) {
    limpiar_efecto(jugador, indice_jugador);

    jugador->efectos &= ~EFECTO_DERRAPANDO;
    jugador->tiron_salto_kart = dato_800E37F0[jugador->id_personaje];
    jugador->aceleracion_salto_kart = 0.0f;
    jugador->velocidad_salto_kart = dato_800E37D0[jugador->id_personaje];
    jugador->disparadores &= ~sin_uso_disparador_0_x_10000;
    jugador->efectos |= desconocido_efecto_0_x_10000000;
}

void funcion_8008FE84(Jugador* jugador, SIN_USO s8 indice_jugador) {
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
        jugador->efectos &= ~desconocido_efecto_0_x_10000000;
        jugador->actual_rapidez /= 2;
        jugador->desconocido_08C /= 2;
    }
}

void funcion_8008FEDC(Jugador* jugador, SIN_USO s8 indice_jugador) {
    jugador->efectos &= ~desconocido_efecto_0_x_10000000;
    jugador->tiron_salto_kart = 0.0f;
    jugador->velocidad_salto_kart = 0.0f;
    jugador->aceleracion_salto_kart = 0.0f;
}

void actualizar_punto_camino_circuito(Jugador* jugador, s8 id_jugador) {
    s16 punto_camino;

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_BOWSER_CASTLE:
            punto_camino = punto_camino_mas_cercano_por_id_jugador[id_jugador];
            if ((punto_camino >= 0x235) && (punto_camino < 0x247)) {
                jugador->mas_cercano_camino_punto_id = 0x214;
            } else if ((punto_camino >= 0x267) && (punto_camino < 0x277)) {
                jugador->mas_cercano_camino_punto_id = 0x25B;
            } else {
                jugador->mas_cercano_camino_punto_id = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                if (jugador->mas_cercano_camino_punto_id < 0) {
                    jugador->mas_cercano_camino_punto_id = cantidad_camino_por_indice_camino[0] + jugador->mas_cercano_camino_punto_id;
                }
            }
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            punto_camino = punto_camino_mas_cercano_por_id_jugador[id_jugador];
            if ((punto_camino >= 0x12C) && (punto_camino < 0x13C)) {
                jugador->mas_cercano_camino_punto_id = 0x12CU;
            } else {
                jugador->mas_cercano_camino_punto_id = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                if (jugador->mas_cercano_camino_punto_id < 0) {
                    jugador->mas_cercano_camino_punto_id = cantidad_camino_por_indice_camino[0] + jugador->mas_cercano_camino_punto_id;
                }
            }
            break;
        case CIRCUITO_YOSHI_VALLEY:
        case CIRCUITO_RAINBOW_ROAD:
            jugador->mas_cercano_camino_punto_id = copia_mas_cercano_camino_punto_por_id_jugador[id_jugador];
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            punto_camino = punto_camino_mas_cercano_por_id_jugador[id_jugador];
#ifdef VERSION_EU
            if (((punto_camino >= 0xF0) && (punto_camino < 0x11E)) || ((copia_mas_cercano_camino_punto_por_id_jugador[id_jugador] >= 0xF0) &&
                                                                 (copia_mas_cercano_camino_punto_por_id_jugador[id_jugador] < 0x11E)))
#else
            if ((punto_camino >= 0xF0) && (punto_camino < 0x105))
#endif
            {
                jugador->mas_cercano_camino_punto_id = 0xF0U;
            } else {
                jugador->mas_cercano_camino_punto_id = copia_mas_cercano_camino_punto_por_id_jugador[id_jugador];
                if (jugador->mas_cercano_camino_punto_id < 0) {
                    jugador->mas_cercano_camino_punto_id = cantidad_camino_por_indice_camino[0] + jugador->mas_cercano_camino_punto_id;
                }
            }
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            punto_camino = punto_camino_mas_cercano_por_id_jugador[id_jugador];
            if ((punto_camino >= 0x258) && (punto_camino < 0x2A4)) {
                jugador->mas_cercano_camino_punto_id = 0x258U;
            } else {
                jugador->mas_cercano_camino_punto_id = copia_mas_cercano_camino_punto_por_id_jugador[id_jugador];
                if (jugador->mas_cercano_camino_punto_id < 0) {
                    jugador->mas_cercano_camino_punto_id = cantidad_camino_por_indice_camino[0] + jugador->mas_cercano_camino_punto_id;
                }
            }
            break;
        case CIRCUITO_DK_JUNGLE:
            punto_camino = punto_camino_mas_cercano_por_id_jugador[id_jugador];
            if ((punto_camino >= 0xB9) && (punto_camino < 0x119)) {
                jugador->mas_cercano_camino_punto_id = 0xB9U;
            } else {
                jugador->mas_cercano_camino_punto_id = punto_camino_mas_cercano_por_id_jugador[id_jugador];
                if (jugador->mas_cercano_camino_punto_id < 0) {
                    jugador->mas_cercano_camino_punto_id = cantidad_camino_por_indice_camino[0] + jugador->mas_cercano_camino_punto_id;
                }
            }
            break;
        case CIRCUITO_BLOCK_FORT:
        case CIRCUITO_SKYSCRAPER:
        case CIRCUITO_DOUBLE_DECK:
        case CIRCUITO_BIG_DONUT:
            jugador->mas_cercano_camino_punto_id = 0U;
            break;
        default:
            jugador->mas_cercano_camino_punto_id = punto_camino_mas_cercano_por_id_jugador[id_jugador];
            if (jugador->mas_cercano_camino_punto_id < 0) {
                jugador->mas_cercano_camino_punto_id = cantidad_camino_por_indice_camino[0] + jugador->mas_cercano_camino_punto_id;
            }
            break;
    }
#else

#endif
}

void funcion_80090178(Jugador* jugador, s8 id_jugador, Vec3f parametro2, Vec3f parametro3) {
    u16 probar;
    PuntoCaminoPista* temporal_v1;
    f32 sp_f8[4] = { 0.0f, 0.0f, -700.0f, 700.0f };
    f32 sp_e8[4] = { 700.0f, -700.0f, 0.0f, 0.0f };
    f32 sp_d8[4] = { 0.0f, 0.0f, -650.0f, 650.0f };
    f32 sp_c8[4] = { 650.0f, -650.0f, 0.0f, 0.0f };
    f32 sp_b8[4] = { 0.0f, 0.0f, -400.0f, 400.0f };
    f32 sp_a8[4] = { 400.0f, -400.0f, 0.0f, 0.0f };
    f32 sp98[4] = { 0.0f, 0.0f, -350.0f, 350.0f };
    f32 sp88[4] = { 350.0f, -350.0f, 0.0f, 0.0f };
    f32 sp78[4] = { 0.0f, 0.0f, -675.0f, 675.0f };
    f32 sp68[4] = { 675.0f, -675.0f, 0.0f, 0.0f };
    f32 sp58[4] = { 0.0f, 0.0f, -550.0f, 550.0f };
    f32 sp48[4] = { 550.0f, -550.0f, 0.0f, 0.0f };
    f32 sp38[4] = { 0.0f, 0.0f, -575.0f, 575.0f };
    f32 sp28[4] = { 575.0f, -575.0f, 0.0f, 0.0f };
    f32 sp18[4] = { 10.0f, -10.0f, -575.0f, 575.0f };
    f32 sp08[4] = { 575.0f, -575.0f, 10.0f, -10.0f };

    switch (id_circuito_actual) {
        case CIRCUITO_YOSHI_VALLEY:
            probar = jugador->mas_cercano_camino_punto_id;
            temporal_v1 = &caminos_pista[indice_camino_copia_por_id_jugador[id_jugador]][probar];
            parametro2[0] = temporal_v1->pos_x;
            parametro2[1] = temporal_v1->pos_y;
            parametro2[2] = temporal_v1->pos_z;
            temporal_v1 = &caminos_pista[indice_camino_copia_por_id_jugador[id_jugador]]
                                  [(jugador->mas_cercano_camino_punto_id + 5) %
                                   (cantidad_camino_por_indice_camino[indice_camino_copia_por_id_jugador[id_jugador]] + 1)];
            parametro3[0] = temporal_v1->pos_x;
            parametro3[1] = temporal_v1->pos_y;
            parametro3[2] = temporal_v1->pos_z;
            break;
        case CIRCUITO_BLOCK_FORT:
            parametro2[0] = sp_f8[id_jugador];
            parametro2[1] = 0.0f;
            parametro2[2] = sp_e8[id_jugador];
            parametro3[0] = sp_d8[id_jugador];
            parametro3[1] = 0.0f;
            parametro3[2] = sp_c8[id_jugador];
            break;
        case CIRCUITO_SKYSCRAPER:
            parametro2[0] = sp_b8[id_jugador];
            parametro2[1] = 480.0f;
            parametro2[2] = sp_a8[id_jugador];
            parametro3[0] = sp98[id_jugador];
            parametro3[1] = 480.0f;
            parametro3[2] = sp88[id_jugador];
            break;
        case CIRCUITO_DOUBLE_DECK:
            parametro2[0] = sp78[id_jugador];
            parametro2[1] = 0.0f;
            parametro2[2] = sp68[id_jugador];
            parametro3[0] = sp58[id_jugador];
            parametro3[1] = 0.0f;
            parametro3[2] = sp48[id_jugador];
            break;
        case CIRCUITO_BIG_DONUT:
            parametro2[0] = sp38[id_jugador];
            parametro2[1] = 200.0f;
            parametro2[2] = sp28[id_jugador];
            parametro3[0] = sp18[id_jugador];
            parametro3[1] = 200.0f;
            parametro3[2] = sp08[id_jugador];
            break;
        default:
            probar = jugador->mas_cercano_camino_punto_id;
            temporal_v1 = &caminos_pista[0][probar];
            parametro2[0] = temporal_v1->pos_x;
            parametro2[1] = temporal_v1->pos_y;
            parametro2[2] = temporal_v1->pos_z;
            temporal_v1 = &caminos_pista[0][(jugador->mas_cercano_camino_punto_id + 5) % (cantidad_camino_por_indice_camino[0] + 1)];
            parametro3[0] = temporal_v1->pos_x;
            parametro3[1] = temporal_v1->pos_y;
            parametro3[2] = temporal_v1->pos_z;
            break;
    }
}

void funcion_80090778(Jugador* jugador) {
    s32 indice_jugador = obtener_indice_jugador_para_jugador(jugador);

    jugador->desconocido_078 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_0C0 = 0;
    jugador->lakitu_props |= LAKITU_ESCENA;
    jugador->efectos &= ~EFECTO_DERRAPANDO;
    jugador->desconocido_222 = 0;
    jugador->desconocido_08C = 0.0f;

    limpiar_efecto(jugador, indice_jugador);
    funcion_8008F86C(jugador, indice_jugador);

    jugador->desconocido_DB4.desconocido0 = 0;
    jugador->desconocido_0C2 = 0;
    jugador->desconocido_DB4.desconocido8 = 0.0f;
    if ((jugador->efectos & EFECTO_RAYO) == EFECTO_RAYO) {
        if ((jugador->efectos & EFECTO_GOLPE_RAYO) == EFECTO_GOLPE_RAYO) {
            jugador->efectos &= ~EFECTO_GOLPE_RAYO;
            jugador->desconocido_0A8 = 0;
            jugador->posicion_giro = 0;
            jugador->desconocido_0C0 = 0;
            jugador->rotacion[1] = jugador->desconocido_0AE;
        }
        quitar_efecto_rayo(jugador, indice_jugador);
    }
    jugador->efectos &= ~EFECTO_GIRO_AB;
}
