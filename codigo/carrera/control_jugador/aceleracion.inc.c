// Aceleracion

void alternativo_acelerar_jugador(Jugador* jugador) {
    s32 jugador_indice;

    jugador_indice = obtener_indice_jugador_para_jugador(jugador);
    if (es_jugador_triple_a_boton_combo[jugador_indice] == false) {
        if ((0.0 <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.1))) {
            jugador->actual_rapidez +=
                tablas_aceleracion_kart[jugador->id_personaje][0] + (0.05 * (jugador->acel_pendiente / GRADOS(1)));
        }
        if (((jugador->arriba_rapidez * 0.1) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.2))) {
            jugador->actual_rapidez +=
                tablas_aceleracion_kart[jugador->id_personaje][1] + (0.05 * (jugador->acel_pendiente / GRADOS(1)));
        }
        if (((jugador->arriba_rapidez * 0.2) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.3))) {
            jugador->actual_rapidez +=
                tablas_aceleracion_kart[jugador->id_personaje][2] + (0.05 * (jugador->acel_pendiente / GRADOS(1)));
        }
        if (((jugador->arriba_rapidez * 0.3) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.4))) {
            jugador->actual_rapidez +=
                tablas_aceleracion_kart[jugador->id_personaje][3] + (0.05 * (jugador->acel_pendiente / GRADOS(1)));
        }
        if (((jugador->arriba_rapidez * 0.4) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.5))) {
            jugador->actual_rapidez +=
                tablas_aceleracion_kart[jugador->id_personaje][4] + (0.05 * (jugador->acel_pendiente / GRADOS(1)));
        }
        if (((jugador->arriba_rapidez * 0.5) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.6))) {
            jugador->actual_rapidez +=
                tablas_aceleracion_kart[jugador->id_personaje][5] + (0.05 * (jugador->acel_pendiente / GRADOS(1)));
        }
        if (((jugador->arriba_rapidez * 0.6) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.7))) {
            jugador->actual_rapidez +=
                tablas_aceleracion_kart[jugador->id_personaje][6] + (0.05 * (jugador->acel_pendiente / GRADOS(1)));
        }
        if (((jugador->arriba_rapidez * 0.7) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.8))) {
            jugador->actual_rapidez +=
                tablas_aceleracion_kart[jugador->id_personaje][7] + (0.05 * (jugador->acel_pendiente / GRADOS(1)));
        }
        if (((jugador->arriba_rapidez * 0.8) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.9))) {
            jugador->actual_rapidez +=
                tablas_aceleracion_kart[jugador->id_personaje][8] + (0.05 * (jugador->acel_pendiente / GRADOS(1)));
        }
        if (((jugador->arriba_rapidez * 0.9) <= jugador->actual_rapidez) && (jugador->actual_rapidez <= (jugador->arriba_rapidez * 1.0))) {
            jugador->actual_rapidez +=
                tablas_aceleracion_kart[jugador->id_personaje][9] + (0.05 * (jugador->acel_pendiente / GRADOS(1)));
        }
    } else {
        if ((0.0 <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.1))) {
            jugador->actual_rapidez +=
                (tablas_aceleracion_kart[jugador->id_personaje][0] + (0.05 * (jugador->acel_pendiente / GRADOS(1)))) *
                impulso_triple_a_kart[jugador->id_personaje];
        }
        if (((jugador->arriba_rapidez * 0.1) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.2))) {
            jugador->actual_rapidez +=
                (tablas_aceleracion_kart[jugador->id_personaje][1] + (0.05 * (jugador->acel_pendiente / GRADOS(1)))) *
                impulso_triple_a_kart[jugador->id_personaje];
        }
        if (((jugador->arriba_rapidez * 0.2) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.3))) {
            jugador->actual_rapidez +=
                (tablas_aceleracion_kart[jugador->id_personaje][2] + (0.05 * (jugador->acel_pendiente / GRADOS(1)))) *
                impulso_triple_a_kart[jugador->id_personaje];
        }
        if (((jugador->arriba_rapidez * 0.3) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.4))) {
            jugador->actual_rapidez +=
                (tablas_aceleracion_kart[jugador->id_personaje][3] + (0.05 * (jugador->acel_pendiente / GRADOS(1)))) *
                impulso_triple_a_kart[jugador->id_personaje];
        }
        if (((jugador->arriba_rapidez * 0.4) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.5))) {
            jugador->actual_rapidez +=
                (tablas_aceleracion_kart[jugador->id_personaje][4] + (0.05 * (jugador->acel_pendiente / GRADOS(1)))) *
                impulso_triple_a_kart[jugador->id_personaje];
        }
        if (((jugador->arriba_rapidez * 0.5) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.6))) {
            jugador->actual_rapidez +=
                (tablas_aceleracion_kart[jugador->id_personaje][5] + (0.05 * (jugador->acel_pendiente / GRADOS(1)))) *
                impulso_triple_a_kart[jugador->id_personaje];
        }
        if (((jugador->arriba_rapidez * 0.6) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.7))) {
            jugador->actual_rapidez +=
                (tablas_aceleracion_kart[jugador->id_personaje][6] + (0.05 * (jugador->acel_pendiente / GRADOS(1)))) *
                impulso_triple_a_kart[jugador->id_personaje];
        }
        if (((jugador->arriba_rapidez * 0.7) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.8))) {
            jugador->actual_rapidez +=
                (tablas_aceleracion_kart[jugador->id_personaje][7] + (0.05 * (jugador->acel_pendiente / GRADOS(1)))) *
                impulso_triple_a_kart[jugador->id_personaje];
        }
        if (((jugador->arriba_rapidez * 0.8) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.9))) {
            jugador->actual_rapidez +=
                (tablas_aceleracion_kart[jugador->id_personaje][8] + (0.05 * (jugador->acel_pendiente / GRADOS(1)))) *
                impulso_triple_a_kart[jugador->id_personaje];
        }
        if (((jugador->arriba_rapidez * 0.9) <= jugador->actual_rapidez) && (jugador->actual_rapidez <= (jugador->arriba_rapidez * 1.0))) {
            jugador->actual_rapidez +=
                (tablas_aceleracion_kart[jugador->id_personaje][9] + (0.05 * (jugador->acel_pendiente / GRADOS(1)))) *
                impulso_triple_a_kart[jugador->id_personaje];
        }
    }
    if (jugador->actual_rapidez < 0.0f) {
        jugador->actual_rapidez = 0.0f;
    }
    if (jugador->arriba_rapidez <= jugador->actual_rapidez) {
        jugador->actual_rapidez = jugador->arriba_rapidez;
    }
    if (!((jugador->efectos & EFECTO_EN_EL_AIRE)) || ((jugador->efectos & EFECTO_RAYO))) {
        jugador->desconocido_08C = (jugador->actual_rapidez * jugador->actual_rapidez) / 25.0f;
    }
    jugador->kart_props |= ACELERADOR;
    if ((jugador->disparadores * 8) < 0) {
        funcion_8008F104(jugador, jugador_indice);
        jugador->disparadores &= ~DISPARADOR_TROMPO_INICIO;
    }
}

void alternativo_desacelerar_jugador(Jugador* jugador, f32 rapidez) {
    s32 jugador_indice;
    jugador_indice = obtener_indice_jugador_para_jugador(jugador);

    jugador->actual_rapidez -= rapidez;
    if (jugador->actual_rapidez <= 0.0f) {
        jugador->actual_rapidez = 0.0f;
    }
    if (jugador->speed < 0.2) {
        jugador->desconocido_08C = 0.0f;
    }
    if (jugador->arriba_rapidez <= jugador->actual_rapidez) {
        jugador->actual_rapidez = jugador->arriba_rapidez;
    }
    if ((jugador->efectos & EFECTO_EN_EL_AIRE) != EFECTO_EN_EL_AIRE) {
        jugador->desconocido_08C = (jugador->actual_rapidez * jugador->actual_rapidez) / 25.0f;
    }
    jugador->kart_props &= ~ACELERADOR;
    if ((jugador->disparadores * 8) < 0) {
        funcion_8008F104(jugador, jugador_indice);
        jugador->disparadores &= ~DISPARADOR_TROMPO_INICIO;
    }
}

void detectar_triple_b_combo_b_soltado(Jugador* jugador) {
    s32 indice_jugador;

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
    if (jugador == jugador_cinco) {
        indice_jugador = 4;
    }
    if (jugador == jugador_seis) {
        indice_jugador = 5;
    }
    if (jugador == jugador_siete) {
        indice_jugador = 6;
    }
    if (jugador == jugador_ocho) {
        indice_jugador = 7;
    }

    if (es_jugador_triple_b_boton_combo[indice_jugador] == false) {
        if (jugador_es_freno_activo[indice_jugador] == true) {
            if ((frame_desde_ultimo_combo_b[indice_jugador] < 2) || (frame_desde_ultimo_combo_b[indice_jugador] >= 9)) {
                cambio_cantidad_b[indice_jugador] = 0;
            }
            frame_desde_ultimo_combo_b[indice_jugador] = 0;
            dato_801654C0[indice_jugador] = 0;
        }
        jugador_es_freno_activo[indice_jugador] = false;
        frame_desde_ultimo_combo_b[indice_jugador]++;
        if (frame_desde_ultimo_combo_b[indice_jugador] >= 9) {
            frame_desde_ultimo_combo_b[indice_jugador] = 9;
        }
        if ((frame_desde_ultimo_combo_b[indice_jugador] >= 2) && (frame_desde_ultimo_combo_b[indice_jugador] < 9)) {
            if (dato_801654C0[indice_jugador] == 0) {
                cambio_cantidad_b[indice_jugador]++;
            }
            dato_801654C0[indice_jugador] = 1;
        }
        if (cambio_cantidad_b[indice_jugador] == 5) {
            es_jugador_triple_b_boton_combo[indice_jugador] = true;
            temporizador_impulso_triple_b_combo[indice_jugador] = 120;
            cambio_cantidad_b[indice_jugador] = 0;
            frame_desde_ultimo_combo_b[indice_jugador] = 0;
        }
    } else {
        temporizador_impulso_triple_b_combo[indice_jugador]--;
        if (temporizador_impulso_triple_b_combo[indice_jugador] <= 0) {
            es_jugador_triple_b_boton_combo[indice_jugador] = false;
        }
    }
}

void detectar_triple_b_combo_b_pulsado(Jugador* jugador) {
    s32 indice_jugador;

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
    if (jugador == jugador_cinco) {
        indice_jugador = 4;
    }
    if (jugador == jugador_seis) {
        indice_jugador = 5;
    }
    if (jugador == jugador_siete) {
        indice_jugador = 6;
    }
    if (jugador == jugador_ocho) {
        indice_jugador = 7;
    }

    if (es_jugador_triple_b_boton_combo[indice_jugador] == false) {
        if (jugador_es_freno_activo[indice_jugador] == false) {
            if ((frame_desde_ultimo_combo_b[indice_jugador] < 2) || (frame_desde_ultimo_combo_b[indice_jugador] >= 9)) {
                cambio_cantidad_b[indice_jugador] = 0;
            }
            frame_desde_ultimo_combo_b[indice_jugador] = 0;
            dato_801654C0[indice_jugador] = 0;
        }
        jugador_es_freno_activo[indice_jugador] = true;
        frame_desde_ultimo_combo_b[indice_jugador]++;
        if (frame_desde_ultimo_combo_b[indice_jugador] >= 9) {
            frame_desde_ultimo_combo_b[indice_jugador] = 9;
        }
        if ((frame_desde_ultimo_combo_b[indice_jugador] >= 2) && (frame_desde_ultimo_combo_b[indice_jugador] < 9)) {
            if (dato_801654C0[indice_jugador] == 0) {
                cambio_cantidad_b[indice_jugador]++;
            }
            dato_801654C0[indice_jugador] = 1;
        }
        if (cambio_cantidad_b[indice_jugador] == 5) {
            es_jugador_triple_b_boton_combo[indice_jugador] = true;
            temporizador_impulso_triple_b_combo[indice_jugador] = 120;
            cambio_cantidad_b[indice_jugador] = 0;
            frame_desde_ultimo_combo_b[indice_jugador] = 0;
        }
    } else {
        temporizador_impulso_triple_b_combo[indice_jugador]--;
        if (temporizador_impulso_triple_b_combo[indice_jugador] <= 0) {
            es_jugador_triple_b_boton_combo[indice_jugador] = false;
        }
    }
}

void funcion_800323E4(Jugador* jugador) {
    s32 indice_jugador;
    f32 probar;
    f32 variable_f2;

    variable_f2 = 0.0f;
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
    if (jugador == jugador_cinco) {
        indice_jugador = 4;
    }
    if (jugador == jugador_seis) {
        indice_jugador = 5;
    }
    if (jugador == jugador_siete) {
        indice_jugador = 6;
    }
    if (jugador == jugador_ocho) {
        indice_jugador = 7;
    }
    jugador->efectos |= EFECTO_FRENADO;
    if ((jugador->efectos & EFECTO_GIRO_AB) == EFECTO_GIRO_AB) {
        alternativo_desacelerar_jugador(jugador, 1.0f);
        jugador->desconocido_20C = variable_f2;
    } else {
        if ((s32) jugador->ruedas[DERECHA_ATRAS].tipo_superficie < 0xF) {
            variable_f2 += dato_800E3210[jugador->id_personaje][jugador->ruedas[DERECHA_ATRAS].tipo_superficie];
        }
        if ((s32) jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie < 0xF) {
            variable_f2 += dato_800E3210[jugador->id_personaje][jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie];
        }
        probar = jugador->anterior_rapidez - jugador->speed;
        if (probar <= 0.0f) {
            jugador->desconocido_20C = 0.0f;
        } else {
            jugador->desconocido_20C += 0.02;
            if (jugador->desconocido_20C >= 2.0f) {
                jugador->desconocido_20C = 2.0f;
            }
        }
        if (es_jugador_triple_b_boton_combo[indice_jugador] == true) {
            if (jugador->desconocido_20C >= 2.0f) {
                alternativo_desacelerar_jugador(jugador, (1.0f - variable_f2) * 5.0f);
            } else {
                alternativo_desacelerar_jugador(jugador, (1.0f - variable_f2) * 3.0f);
            }
        } else {
            if (((jugador->speed / 18.0f) * 216.0f) <= 20.0f) {
                alternativo_desacelerar_jugador(jugador, (1.0f - variable_f2) * 4.0f);
            }
            if (jugador->desconocido_20C >= 2.0f) {
                alternativo_desacelerar_jugador(jugador, (1.0f - variable_f2) * 2.5);
            } else {
                alternativo_desacelerar_jugador(jugador, (1.0f - variable_f2) * 1.2);
            }
        }
    }
}

void empezar_secuencia_acelerar_jugador_durante(Jugador* jugador) {
    s32 indice_jugador;
    s32 variable_v0;
    s32 delta_tiempo;

    indice_jugador = obtener_indice_jugador_para_jugador(jugador);
    if ((jugador->actual_rapidez >= 0.0) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.1))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][0] * 3.0;
    }
    if (((jugador->arriba_rapidez * 0.1) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.2))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][1] * 3.0;
    }
    if (((jugador->arriba_rapidez * 0.2) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.3))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][2] * 3.0;
    }
    if (((jugador->arriba_rapidez * 0.3) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.4))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][3] * 3.0;
    }
    if (((jugador->arriba_rapidez * 0.4) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.5))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][4] * 3.0;
    }
    if (((jugador->arriba_rapidez * 0.5) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.6))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][5] * 3.0;
    }
    if (((jugador->arriba_rapidez * 0.6) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.7))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][6] * 2.5;
    }
    if (((jugador->arriba_rapidez * 0.7) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.8))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][7] * 2.5;
    }
    if (((jugador->arriba_rapidez * 0.8) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.9))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][8] * 2.5;
    }
    if (((jugador->arriba_rapidez * 0.9) <= jugador->actual_rapidez) && (jugador->actual_rapidez <= jugador->arriba_rapidez * 1.0)) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][9] * 2.5;
    }
    if (dato_801656F0 == 1) {
        delta_tiempo = contador_frame_carrera - dato_801652E0[indice_jugador];
        if (seleccion_modo == CONTRARRELOJ) {
            variable_v0 = 0x14;
        } else {
            variable_v0 = 8;
        }
        if ((delta_tiempo < variable_v0) && ((jugador->kart_props & ACELERADOR) != ACELERADOR)) {
            jugador->disparadores |= DISPARADOR_IMPULSO_INICIO;
        } else if ((jugador->arriba_rapidez * 0.9f) <= jugador->actual_rapidez) {
            if ((jugador->disparadores & DISPARADOR_IMPULSO_INICIO) != DISPARADOR_IMPULSO_INICIO) {
                jugador->disparadores |= DISPARADOR_TROMPO_INICIO;
                jugador->disparadores &= ~DISPARADOR_IMPULSO_INICIO;
            }
        }
    }
    jugador->kart_props |= ACELERADOR;
    jugador->desconocido_098 = (jugador->actual_rapidez * jugador->actual_rapidez) / 25.0f;
}

void empezar_secuencia_desacelerar_jugador_durante(Jugador* jugador, f32 reduccion_rapidez) {
    jugador->actual_rapidez -= reduccion_rapidez;
    if (jugador->actual_rapidez <= 0.0f) {
        jugador->actual_rapidez = 0.0f;
    }
    if (jugador->speed < 0.2) {
        jugador->desconocido_08C = 0.0f;
    }
    if (jugador->arriba_rapidez <= jugador->actual_rapidez) {
        jugador->actual_rapidez = jugador->arriba_rapidez;
    }
    if ((f64) jugador->actual_rapidez <= (jugador->arriba_rapidez * 0.7)) {
        jugador->disparadores &= ~DISPARADOR_TROMPO_INICIO;
    }
    jugador->disparadores &= ~DISPARADOR_IMPULSO_INICIO;
    jugador->kart_props &= ~ACELERADOR;
    jugador->desconocido_098 = (jugador->actual_rapidez * jugador->actual_rapidez) / 25.0f;
}

void acelerar_jugador(Jugador* jugador) {
    SIN_USO s32 jugador_indice;

    jugador_indice = obtener_indice_jugador_para_jugador(jugador);
    if ((0.0 <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.1))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][0] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.1) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.2))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][1] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.2) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.3))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][2] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.3) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.4))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][3] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.4) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.5))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][4] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.5) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.6))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][5] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.6) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.7))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][6] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.7) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.8))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][7] * 2.8;
    }
    if (((jugador->arriba_rapidez * 0.8) <= jugador->actual_rapidez) && (jugador->actual_rapidez < (jugador->arriba_rapidez * 0.9))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][8] * 2.8;
    }
    if (((jugador->arriba_rapidez * 0.9) <= jugador->actual_rapidez) && (jugador->actual_rapidez <= (jugador->arriba_rapidez * 1.0))) {
        jugador->actual_rapidez += tablas_aceleracion_kart[jugador->id_personaje][9] * 2.8;
    }
    if (jugador->actual_rapidez < 0.0f) {
        jugador->actual_rapidez = 0.0f;
    }
    jugador->desconocido_098 = (jugador->actual_rapidez * jugador->actual_rapidez) / 25.0f;
}

void desacelerar_jugador(Jugador* jugador, f32 reduccion_rapidez) {
    jugador->actual_rapidez -= reduccion_rapidez;
    if (jugador->actual_rapidez <= 0.0f) {
        jugador->actual_rapidez = 0.0f;
    }
    if (jugador->arriba_rapidez <= jugador->actual_rapidez) {
        jugador->actual_rapidez = jugador->arriba_rapidez;
    }
    jugador->desconocido_098 = (jugador->actual_rapidez * jugador->actual_rapidez) / 25.0f;
}

void global_acelerar_jugador(Jugador* jugador, s32 indice_jugador) {
    if ((jugador_actual_rapidez[indice_jugador] >= 0.0) && (jugador_actual_rapidez[indice_jugador] < ((f64) jugador->arriba_rapidez * 0.1))) {
        jugador_actual_rapidez[indice_jugador] += tablas_aceleracion_kart[jugador->id_personaje][0] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.1) <= jugador_actual_rapidez[indice_jugador]) &&
        (jugador_actual_rapidez[indice_jugador] < (jugador->arriba_rapidez * 0.2))) {
        jugador_actual_rapidez[indice_jugador] += tablas_aceleracion_kart[jugador->id_personaje][1] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.2) <= jugador_actual_rapidez[indice_jugador]) &&
        (jugador_actual_rapidez[indice_jugador] < (jugador->arriba_rapidez * 0.3))) {
        jugador_actual_rapidez[indice_jugador] += tablas_aceleracion_kart[jugador->id_personaje][2] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.3) <= jugador_actual_rapidez[indice_jugador]) &&
        (jugador_actual_rapidez[indice_jugador] < (jugador->arriba_rapidez * 0.4))) {
        jugador_actual_rapidez[indice_jugador] += tablas_aceleracion_kart[jugador->id_personaje][3] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.4) <= jugador_actual_rapidez[indice_jugador]) &&
        (jugador_actual_rapidez[indice_jugador] < (jugador->arriba_rapidez * 0.5))) {
        jugador_actual_rapidez[indice_jugador] += tablas_aceleracion_kart[jugador->id_personaje][4] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.5) <= jugador_actual_rapidez[indice_jugador]) && (jugador_actual_rapidez[indice_jugador] < (jugador->arriba_rapidez * 0.6))) {
        jugador_actual_rapidez[indice_jugador] += tablas_aceleracion_kart[jugador->id_personaje][5] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.6) <= jugador_actual_rapidez[indice_jugador]) && (jugador_actual_rapidez[indice_jugador] < (jugador->arriba_rapidez * 0.7))) {
        jugador_actual_rapidez[indice_jugador] += tablas_aceleracion_kart[jugador->id_personaje][6] * 3.2;
    }
    if (((jugador->arriba_rapidez * 0.7) <= jugador_actual_rapidez[indice_jugador]) && (jugador_actual_rapidez[indice_jugador] < (jugador->arriba_rapidez * 0.8))) {
        jugador_actual_rapidez[indice_jugador] += tablas_aceleracion_kart[jugador->id_personaje][7] * 2.8;
    }
    if (((jugador->arriba_rapidez * 0.8) <= jugador_actual_rapidez[indice_jugador]) && (jugador_actual_rapidez[indice_jugador] < (jugador->arriba_rapidez * 0.9))) {
        jugador_actual_rapidez[indice_jugador] += tablas_aceleracion_kart[jugador->id_personaje][8] * 2.8;
    }
    if (((jugador->arriba_rapidez * 0.9) <= jugador_actual_rapidez[indice_jugador]) && (jugador_actual_rapidez[indice_jugador] <= (jugador->arriba_rapidez * 1.0))) {
        jugador_actual_rapidez[indice_jugador] += tablas_aceleracion_kart[jugador->id_personaje][9] * 2.8;
    }
    jugador->kart_props |= ACELERADOR;
    if (jugador_actual_rapidez[indice_jugador] < 0.0f) {
        jugador_actual_rapidez[indice_jugador] = 0.0f;
    }
    jugador->desconocido_098 = (jugador_actual_rapidez[indice_jugador] * jugador_actual_rapidez[indice_jugador]) / 25.0f;
}

void global_desacelerar_jugador(Jugador* jugador, f32 reduccion_rapidez, s32 indice_jugador) {
    jugador->kart_props &= ~ACELERADOR;
    jugador_actual_rapidez[indice_jugador] -= reduccion_rapidez;
    if (jugador_actual_rapidez[indice_jugador] <= 0.0f) {
        jugador_actual_rapidez[indice_jugador] = 0.0f;
    }
    if (jugador->arriba_rapidez <= jugador_actual_rapidez[indice_jugador]) {
        jugador_actual_rapidez[indice_jugador] = jugador->arriba_rapidez;
    }
    jugador->desconocido_098 = (jugador_actual_rapidez[indice_jugador] * jugador_actual_rapidez[indice_jugador]) / 25.0f;
}

void funcion_80033850(Jugador* parametro0, f32 parametro1) {
    parametro0->desconocido_090 += parametro1;
    if (parametro0->desconocido_090 >= 0.0f) {
        parametro0->desconocido_090 = 0.0f;
    }
}

void actualizar_grande_direccion(Jugador* jugador, s32* cambio_direccion_deseado, s32* direccion_actual, s32 direccion_deseado, s32 umbral_cambio_direccion, s32 minimo_cambio_direccion, s32 parametro6) {
    s32 incrementar_cambio_direccion_actual;

    if ((*cambio_direccion_deseado >= umbral_cambio_direccion) || (-umbral_cambio_direccion >= *cambio_direccion_deseado)) {
        incrementar_cambio_direccion_actual = jugador->incrementar_cambio_giro;
        jugador->incrementar_cambio_giro -= 1 << 11;
        if (jugador->incrementar_cambio_giro >= 0xF0000000) {
            jugador->incrementar_cambio_giro = incrementar_cambio_direccion_actual;
        }
        if (minimo_cambio_direccion >= (s32) jugador->incrementar_cambio_giro) {
            jugador->incrementar_cambio_giro = minimo_cambio_direccion;
        }

        *direccion_actual = (direccion_deseado < *direccion_actual) ? *direccion_actual - jugador->incrementar_cambio_giro : *direccion_actual + jugador->incrementar_cambio_giro;

        if (jugador->desconocido_090 < ((f32) parametro6)) {
            jugador->desconocido_090 = (f32) -parametro6;
        }
    }
}

SIN_USO void funcion_80033940(Jugador* jugador, s32* parametro1, s32 parametro2, s32 parametro3, f32 parametro4) {
    u32 temporal_v1;

    temporal_v1 = jugador->incrementar_cambio_giro;
    jugador->incrementar_cambio_giro -= 0x800;
    if (!(jugador->incrementar_cambio_giro < 0xF0000000)) {
        jugador->incrementar_cambio_giro = temporal_v1;
    }
    if (parametro3 >= (s32) jugador->incrementar_cambio_giro) {
        jugador->incrementar_cambio_giro = parametro3;
    }

    *parametro1 = (parametro2 < *parametro1) ? *parametro1 - jugador->incrementar_cambio_giro : *parametro1 + jugador->incrementar_cambio_giro;

    if (jugador->desconocido_090 < parametro4) {
        jugador->desconocido_090 = (f32) -parametro4;
    }
}

SIN_USO void funcion_800339C4(Jugador* jugador, s32* parametro1, s32 parametro2, s32 parametro3, f32 parametro4) {
    s32 temporal_v0;

    temporal_v0 = jugador->incrementar_cambio_giro;
    jugador->incrementar_cambio_giro -= 0x800;
    if (jugador->incrementar_cambio_giro >= 0xF0000000) {
        jugador->incrementar_cambio_giro = temporal_v0;
    }
    if (parametro3 >= (s32) jugador->incrementar_cambio_giro) {
        jugador->incrementar_cambio_giro = parametro3;
    }

    *parametro1 = (parametro2 < *parametro1) ? *parametro1 - jugador->incrementar_cambio_giro : *parametro1 + jugador->incrementar_cambio_giro;

    funcion_80033850(jugador, parametro4);
}

void actualizar_chico_direccion(Jugador* jugador, s32* cambio_direccion_deseado, s32* direccion_actual, s32 direccion_deseado, s32 umbral_cambio_direccion, s32 minimo_cambio_direccion, f32 parametro6) {
    s32 incrementar_cambio_direccion_actual;

    if ((*cambio_direccion_deseado >= umbral_cambio_direccion) || (-umbral_cambio_direccion >= *cambio_direccion_deseado)) {
        incrementar_cambio_direccion_actual = jugador->incrementar_cambio_giro;
        jugador->incrementar_cambio_giro -= 1 << 11;
        if (jugador->incrementar_cambio_giro >= 0xF0000000) {
            jugador->incrementar_cambio_giro = incrementar_cambio_direccion_actual;
        }
        if (minimo_cambio_direccion >= (s32) jugador->incrementar_cambio_giro) {
            jugador->incrementar_cambio_giro = minimo_cambio_direccion;
        }

        *direccion_actual = (direccion_deseado < *direccion_actual) ? *direccion_actual - jugador->incrementar_cambio_giro : *direccion_actual + jugador->incrementar_cambio_giro;

        funcion_80033850(jugador, parametro6);
    }
}
