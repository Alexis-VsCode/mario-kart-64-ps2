void funcion_80007D04(s32 id_jugador, Jugador* jugador) {
    s16 temporal_t1;
    s16 temporal_t2;
    s32 variable_v0;

    temporal_t1 = num_camino_puntos_recorrido[mejor_clasificado_humano_jugador];
    temporal_t2 = num_camino_puntos_recorrido[id_jugador];

    if (gp_actual_carrera_puesto_por_id_jugador[id_jugador] < 2) {
        s16 val1 = gp_actual_carrera_puesto_por_id_jugador[mejor_clasificado_humano_jugador];
        s16 val2 = temporal_t2 - temporal_t1;

        if (val2 > 400 && val1 >= 6) {
            jugador->efectos &= ~EFECTO_RAPIDO_CPU;
            alternativo_acelerar_jugador(jugador);
            dato_801634C0[id_jugador] = 4;
            return;
        }
    } else {
        jugador->efectos |= EFECTO_RAPIDO_CPU;
        alternativo_acelerar_jugador(jugador);
        dato_801634C0[id_jugador] = 3;
        return;
    }

    switch (seleccion_cc) {
        case CC_EXTRA:
            break;
    }

    switch (seleccion_cc) {
        case CC_50:
            variable_v0 = 0;
            if (id_jugador == dato_80163344[0]) {
                variable_v0 = 0x14;
            }
            break;

        case CC_100:
            variable_v0 = 8;
            if (id_jugador == dato_80163344[0]) {
                variable_v0 = 0x18;
            }
            break;

        case CC_150:
            variable_v0 = 0x12;
            if (id_jugador == dato_80163344[0]) {
                variable_v0 = 0x24;
            }
            break;

        case CC_EXTRA:
            variable_v0 = 8;
            if (id_jugador == dato_80163344[0]) {
                variable_v0 = 0x18;
            }
            break;

        default:
            variable_v0 = 0;
            break;
    }

    if (temporal_t2 < temporal_t1) {
        jugador->efectos |= EFECTO_RAPIDO_CPU;
        alternativo_acelerar_jugador(jugador);
        dato_801634C0[id_jugador] = 1;
    } else if (temporal_t2 < (temporal_t1 + variable_v0 + 0x32)) {
        jugador->efectos &= ~EFECTO_RAPIDO_CPU;
        alternativo_acelerar_jugador(jugador);
        dato_801634C0[id_jugador] = 3;
    } else if (dato_801631E0[id_jugador] == false) {
        jugador->efectos &= ~EFECTO_RAPIDO_CPU;
        alternativo_acelerar_jugador(jugador);
        dato_801634C0[id_jugador] = 2;
    } else {
        jugador->efectos &= ~EFECTO_RAPIDO_CPU;
        alternativo_desacelerar_jugador(jugador, 1.0f);
        dato_801634C0[id_jugador] = -1;
    }
}

void funcion_80007FA4(s32 id_jugador, Jugador* jugador, f32 parametro2) {
    f32 temporal_f0;
    f32 dist;
    f32 temporal_f2;
    s32 probar;

    temporal_f0 = dato_80163418[id_jugador] - jugador->pos[0];
    temporal_f2 = dato_80163438[id_jugador] - jugador->pos[2];
    dist = (temporal_f0 * temporal_f0) + (temporal_f2 * temporal_f2);
    if (id_jugador == 3) {
        if ((dist < 25.0f) && (dato_80163410[id_jugador] < 5)) {
            dato_80163410[id_jugador] = 4;
            (parametro2 < ((2.0 * 18.0) / 216.0)) ? funcion_80038BE4(jugador, 1) : alternativo_desacelerar_jugador(jugador, 1.0f);
        } else if ((dist < 3600.0f) && (dato_80163410[id_jugador] < 4)) {
            dato_80163410[id_jugador] = 3;
            (parametro2 < ((5.0 * 18.0) / 216.0)) ? funcion_80038BE4(jugador, 1) : alternativo_desacelerar_jugador(jugador, 5.0f);
        } else {
            (parametro2 < ((20.0 * 18.0) / 216.0)) ? funcion_80038BE4(jugador, 10) : alternativo_desacelerar_jugador(jugador, 1.0f);
        }
    } else {
        if ((dist < 25.0f) && (dato_80163410[id_jugador] < 5)) {
            dato_80163410[id_jugador] = 4;
            probar = 2;
            (parametro2 < ((probar * 18.0) / 216.0)) ? funcion_80038BE4(jugador, 1) : alternativo_desacelerar_jugador(jugador, 1.0f);
        } else if ((dist < 4900.0f) && (dato_80163410[id_jugador] < 4)) {
            dato_80163410[id_jugador] = 3;
            probar = 5;
            (parametro2 < ((probar * 18.0) / 216.0)) ? funcion_80038BE4(jugador, 1) : alternativo_desacelerar_jugador(jugador, 15.0f);
        } else if ((dist < 22500.0f) && (dato_80163410[id_jugador] < 3)) {
            dato_80163410[id_jugador] = 2;
            probar = 20;
            (parametro2 < ((probar * 18.0) / 216.0)) ? funcion_80038BE4(jugador, 5) : alternativo_desacelerar_jugador(jugador, 1.0f);
        } else if ((dist < 90000.0f) && (dato_80163410[id_jugador] < 2)) {
            dato_80163410[id_jugador] = 1;
            probar = 30;
            (parametro2 < ((probar * 18.0) / 216.0)) ? funcion_80038BE4(jugador, 6) : alternativo_desacelerar_jugador(jugador, 1.0f);
        } else if (dato_80163410[id_jugador] == 0) {
            probar = 35;
            (parametro2 < (((probar ^ 0) * 18.0) / 216.0)) ? funcion_80038BE4(jugador, 2) : alternativo_desacelerar_jugador(jugador, 1.0f);
        } else {
            alternativo_desacelerar_jugador(jugador, 1.0f);
        }
    }
}

void regular_cpu_rapidez(s32 id_jugador, f32 objetivo_rapidez, Jugador* jugador) {
    f32 rapidez;
    f32 variable_f0;
    SIN_USO s32 cosa;
    s32 variable_a1;

    rapidez = jugador->speed;
    if (!(jugador->efectos & EFECTO_TROMPO_BANANA) && !(jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) &&
        !(jugador->efectos & EFECTO_GOLPE_RAYO) && !(jugador->disparadores & DISPARADOR_VUELCO_VERTICAL) &&
        !(jugador->disparadores & GOLPE_POR_DISPARADOR_ESTRELLA) && !(jugador->disparadores & DISPARADOR_VUELCO_ALTO) &&
        !(jugador->disparadores & DISPARADOR_VUELCO_BAJO)) {
        if (id_circuito_actual == CEREMONIA_PREMIO_CIRCUITO) {
            funcion_80007FA4(id_jugador, jugador, rapidez);
        } else if ((b_parada_ai_cruce[id_jugador] == true) && !(jugador->efectos & (EFECTO_ESTRELLA | BOO_EFECTO))) {
            alternativo_desacelerar_jugador(jugador, 10.0f);
            if (jugador->actual_rapidez == 0.0) {
                jugador->velocidad[0] = 0.0f;
                jugador->velocidad[2] = 0.0f;
            }
        } else {
            variable_f0 = 3.3333333f;
            switch (seleccion_cc) { /* irregular */
                case CC_100:
                case CC_EXTRA:
                    break;
                case CC_50:
                    variable_f0 = 2.5f;
                    break;
                case CC_150:
                    variable_f0 = 3.75f;
                    break;
            }
            if (rapidez < variable_f0) {
                jugador->efectos &= ~EFECTO_RAPIDO_CPU;
                alternativo_acelerar_jugador(jugador);
            } else if (jugador->type & MODO_CINEMATICA_JUGADOR) {
                if (rapidez < objetivo_rapidez) {
                    jugador->efectos &= ~EFECTO_RAPIDO_CPU;
                    alternativo_acelerar_jugador(jugador);
                } else {
                    jugador->efectos &= ~EFECTO_RAPIDO_CPU;
                    alternativo_desacelerar_jugador(jugador, 1.0f);
                }
            } else if ((dato_801631E0[id_jugador] == true) && (dato_80163330[id_jugador] != 1)) {
                if (funcion_800088D8(id_jugador, cantidad_vuelta_por_id_jugador[id_jugador], gp_actual_carrera_puesto_por_duplicar_id_jugador[id_jugador]) ==
                    1) {
                    jugador->efectos |= EFECTO_RAPIDO_CPU;
                    alternativo_acelerar_jugador(jugador);
                } else {
                    jugador->efectos &= ~EFECTO_RAPIDO_CPU;
                    alternativo_desacelerar_jugador(jugador, 1.0f);
                }
            } else {
                variable_a1 = 1;
                switch (comportamiento_cpu_rapidez[id_jugador]) {
                    case RAPIDEZ_CPU_COMPORTAMIENTO_RAPIDO:
                        jugador->efectos &= ~EFECTO_RAPIDO_CPU;
                        alternativo_acelerar_jugador(jugador);
                        break;
                    case RAPIDEZ_CPU_COMPORTAMIENTO_MAX:
                        jugador->efectos |= EFECTO_RAPIDO_CPU;
                        alternativo_acelerar_jugador(jugador);
                        break;
                    case RAPIDEZ_CPU_COMPORTAMIENTO_LENTO:
                        if (((rapidez / 18.0f) * 216.0f) > 20.0f) {
                            objetivo_rapidez = 1.6666666f;
                        }
                        variable_a1 = 0;
                        break;
                    case RAPIDEZ_CPU_COMPORTAMIENTO_NORMAL:
                    default:
                        variable_a1 = 0;
                        break;
                }
                if (variable_a1 != 1) {
                    if (rapidez < objetivo_rapidez) {
                        if ((modo_demo == 1) && (id_circuito_actual != CEREMONIA_PREMIO_CIRCUITO)) {
                            alternativo_acelerar_jugador(jugador);
                        } else if (dato_80163330[id_jugador] == 1) {
                            funcion_80007D04(id_jugador, jugador);
                        } else if (funcion_800088D8(id_jugador, cantidad_vuelta_por_id_jugador[id_jugador],
                                                 gp_actual_carrera_puesto_por_duplicar_id_jugador[id_jugador]) == true) {
                            jugador->efectos |= EFECTO_RAPIDO_CPU;
                            alternativo_acelerar_jugador(jugador);
                        } else {
                            jugador->efectos &= ~EFECTO_RAPIDO_CPU;
                            alternativo_desacelerar_jugador(jugador, 1.0f);
                        }
                    } else {
                        jugador->efectos &= ~EFECTO_RAPIDO_CPU;
                        if (objetivo_rapidez > 1.0f) {
                            alternativo_desacelerar_jugador(jugador, 2.0f);
                        } else {
                            alternativo_desacelerar_jugador(jugador, 5.0f);
                        }
                    }
                }
            }
        }
    }
}
