// Caminos y vehiculos

s32 actualizar_seleccion_camino_jugador(s32 jugador_id, s32 indice_camino) {
    f32 pos_x;
    f32 pos_y;
    f32 pos_z;
    Jugador* jugador;
    s32 id_seccion_pista;
    SIN_USO s32 margen_pila;

    jugador = &jugadores[jugador_id];
    pos_x = jugador->pos[0];
    pos_y = jugador->pos[1];
    pos_z = jugador->pos[2];
    margen_pila = indice_camino;
    id_seccion_pista = obtener_id_seccion_pista(jugador->colision.indice_zx_malla);
    jugadores_pista_seccion_id[jugador_id] = id_seccion_pista;
    algun_punto_camino_mas_cercano = buscar_mas_cercano_camino_punto_pista_seccion(pos_x, pos_y, pos_z, id_seccion_pista, &indice_camino);
    punto_camino_mas_cercano_por_id_jugador[jugador_id] = algun_punto_camino_mas_cercano;
    if (indice_camino) {};
    indice_camino_por_id_jugador[jugador_id] = indice_camino;
    fijar_camino_actual(indice_camino);
    if (margen_pila) {};
    return indice_camino;
}

void actualizar_finalizacion_jugador(s32 id_jugador) {
    f32 porciento;

    num_camino_puntos_recorrido[id_jugador] =
        (cantidad_vuelta_por_id_jugador[id_jugador] * cantidad_camino_por_indice_camino[0]) + algun_punto_camino_mas_cercano;

    porciento = (f32) punto_camino_mas_cercano_por_id_jugador[id_jugador] / (f32) cantidad_camino_por_indice_camino[indice_camino_por_id_jugador[id_jugador]];
    porciento_finalizacion_vuelta_por_id_jugador[id_jugador] = porciento;
    porciento_finalizacion_circuito_por_id_jugador[id_jugador] = porciento;
    porciento_finalizacion_circuito_por_id_jugador[id_jugador] += cantidad_vuelta_por_id_jugador[id_jugador];
}

void yoshi_valley_camino_cpu(s32 id_jugador) {
    s16 anterior;

    anterior = b_en_multi_seccion_camino[id_jugador];
    if (algun_punto_camino_mas_cercano >= 0x6D) {
        b_en_multi_seccion_camino[id_jugador] = true;
        switch (indice_camino_jugador) {
            case 0:
                if (algun_punto_camino_mas_cercano >= 0x20F) {
                    b_en_multi_seccion_camino[id_jugador] = false;
                }
                break;
            case 1:
                if (algun_punto_camino_mas_cercano >= 0x206) {
                    b_en_multi_seccion_camino[id_jugador] = false;
                }
                break;
            case 2:
                if (algun_punto_camino_mas_cercano >= 0x211) {
                    b_en_multi_seccion_camino[id_jugador] = false;
                }
                break;
            case 3:
                if (algun_punto_camino_mas_cercano >= 0x283) {
                    b_en_multi_seccion_camino[id_jugador] = false;
                }
                break;
        }
    }
    if ((anterior == false) && (b_en_multi_seccion_camino[id_jugador] == true)) {
        cpu_entrando_camino_interseccion[id_jugador] = true;
    }
    if ((anterior == true) && (b_en_multi_seccion_camino[id_jugador] == false)) {
        cpu_saliendo_camino_interseccion[id_jugador] = true;
    }
}

void actualizar_finalizacion_camino_cpu(s32 id_jugador, Jugador* jugador) {
    f32 pos_x;
    f32 pos_y;
    f32 pos_z;
    SIN_USO f32 relleno[2];

    pos_x = jugador->pos[0];
    pos_y = jugador->pos[1];
    pos_z = jugador->pos[2];
    if (cpu_entrando_camino_interseccion[id_jugador] == 1) {
        indice_camino_jugador = actualizar_seleccion_camino_jugador(id_jugador, int_aleatorio(4));
        algun_punto_camino_mas_cercano = actualizar_camino_jugador(pos_x, pos_y, pos_z, 0, jugador, id_jugador, indice_camino_jugador);
        punto_camino_mas_cercano_por_id_jugador[id_jugador] = algun_punto_camino_mas_cercano;
        actualizar_finalizacion_jugador(id_jugador);
        cpu_entrando_camino_interseccion[id_jugador] = 0;
    }
    if (cpu_saliendo_camino_interseccion[id_jugador] == 1) {
        indice_camino_jugador = actualizar_seleccion_camino_jugador(id_jugador, 0);
        algun_punto_camino_mas_cercano = actualizar_camino_jugador(pos_x, pos_y, pos_z, 0, jugador, id_jugador, indice_camino_jugador);
        punto_camino_mas_cercano_por_id_jugador[id_jugador] = algun_punto_camino_mas_cercano;
        actualizar_finalizacion_jugador(id_jugador);
        cpu_saliendo_camino_interseccion[id_jugador] = 0;
    }
}

f32 tiempo_cruzado_linea_meta(SIN_USO s32 id_jugador, f32 jugador_z_anterior, f32 jugador_z) {
    f32 cambio_z_despues_cruce = inicio_z_camino - jugador_z;
    f32 cambio_z_antes_cruce = jugador_z_anterior - inicio_z_camino;
    return temporizador_circuito - ((circuito_temporizador_iter_f * cambio_z_despues_cruce) / (cambio_z_despues_cruce + cambio_z_antes_cruce));
}

void actualizar_finalizacion_camino_jugador(s32 id_jugador, Jugador* jugador) {
    f32 jugador_x;
    f32 jugador_y;
    f32 jugador_z;
    s32 variable_v0;
    SIN_USO s16 relleno;
    f32 jugador_z_anterior;

    jugador_x = jugador->pos[0];
    jugador_y = jugador->pos[1];
    jugador_z = jugador->pos[2];
    jugador_z_anterior = g_jugador_z_anterior[id_jugador];
    es_jugador_nuevo_camino_punto = false;
    cruzado_linea_meta[id_jugador] = 0;
    algun_punto_camino_mas_cercano = actualizar_camino_jugador(jugador_x, jugador_y, jugador_z, punto_camino_mas_cercano_por_id_jugador[id_jugador], jugador,
                                               id_jugador, indice_camino_jugador);
    actual_mas_cercano_camino_punto = algun_punto_camino_mas_cercano;
    if (punto_camino_mas_cercano_por_id_jugador[id_jugador] != algun_punto_camino_mas_cercano) {
        punto_camino_mas_cercano_por_id_jugador[id_jugador] = algun_punto_camino_mas_cercano;
        es_jugador_nuevo_camino_punto = true;
        actualizar_finalizacion_jugador(id_jugador);
    }
    if (id_circuito_actual == CEREMONIA_PREMIO_CIRCUITO) {
        actualizar_factor_posicion_jugador(id_jugador, algun_punto_camino_mas_cercano, indice_camino_jugador);
        return;
    }
    if ((algun_punto_camino_mas_cercano < 0x14) || ((cantidad_camino_por_indice_camino[indice_camino_jugador] - 0x14) < algun_punto_camino_mas_cercano) ||
        (id_circuito_actual == CIRCUITO_KALAMARI_DESERT)) {
        s16 variable_v1 = 0;
        s16 variable_t0 = 0;
        if (id_circuito_actual == CIRCUITO_KALAMARI_DESERT) {
            dato_801634EC = 0;
            if (jugador->efectos & EFECTO_ESTRELLA) {
                dato_801634EC = 1;
            }
            if (es_modo_espejo != 0) {
                if (jugador_x < 300.0f) {
                    variable_v1 = 1;
                    variable_t0 = 1;
                } else if ((jugador_x < 1300.0f) && (cantidad_vuelta_por_id_jugador[id_jugador] < 2) && ((dato_801634EC == 1))) {
                    variable_v1 = 1;
                    variable_t0 = 1;
                }
            } else {
                if (jugador_x > -300.0f) {
                    variable_v1 = 1;
                    variable_t0 = 1;
                } else {
                    if ((jugador_x > -1300.0f) && (cantidad_vuelta_por_id_jugador[id_jugador] < 2) && (dato_801634EC == 1)) {
                        variable_v1 = 1;
                        variable_t0 = 1;
                    }
                }
            }
        } else {
            variable_v1 = 1;
            variable_t0 = 1;
        }
        jugador_z_anterior = g_jugador_z_anterior[id_jugador];
        if ((variable_v1 != 0) && (jugador_z <= inicio_z_camino)) {
            if (inicio_z_camino < jugador_z_anterior) {
                cantidad_vuelta_por_id_jugador[id_jugador]++;
                if ((seleccion_modo == GRAN_PREMIO) && (cantidad_vuelta_por_id_jugador[id_jugador] == 5)) {
                    if (gp_actual_carrera_puesto_por_duplicar_id_jugador[id_jugador] == 7) {
                        for (variable_v0 = 0; variable_v0 < JUGADORES_NUM; variable_v0++) { cantidad_vuelta_por_id_jugador[variable_v0]--; }
                    }
                }
                cruzado_linea_meta[id_jugador] = 1;
                actualizar_finalizacion_jugador(id_jugador);
                reiniciar_comportamiento_cpu(id_jugador);
                cpu_item_estrategia[id_jugador].usar_item_num = 0;
                if ((dato_8016348C == 0) && !(jugador->type & MODO_CINEMATICA_JUGADOR)) {
                    tiempo_jugador_ultimo_tocado_linea_meta[id_jugador] = tiempo_cruzado_linea_meta(id_jugador, jugador_z_anterior, jugador_z);
                }
            }
        }
        if ((variable_t0 != 0) && (jugador_z_anterior <= inicio_z_camino) && (inicio_z_camino < jugador_z)) {
            cantidad_vuelta_por_id_jugador[id_jugador]--;
            actualizar_finalizacion_jugador(id_jugador);
        }
    }
    g_jugador_z_anterior[id_jugador] = jugador_z;
    if ((id_circuito_actual == CIRCUITO_YOSHI_VALLEY) && (es_jugador_nuevo_camino_punto == true)) {
        yoshi_valley_camino_cpu(id_jugador);
        if (((jugador->type & HUMANO_JUGADOR) == 0) || (jugador->type & CPU_JUGADOR)) {
            actualizar_finalizacion_camino_cpu(id_jugador, jugador);
        }
    }
    if ((jugador->type & HUMANO_JUGADOR) && !(jugador->type & CPU_JUGADOR)) {
        detectar_sentido_jugador_incorrecto(id_jugador, jugador);
        if ((seleccion_modo == GRAN_PREMIO) && (cantidad_jugador == 2) && (id_jugador == 0)) {
            if (gp_actual_carrera_puesto_por_duplicar_id_jugador[JUGADOR_UNO] < gp_actual_carrera_puesto_por_duplicar_id_jugador[JUGADOR_DOS]) {
                mejor_clasificado_humano_jugador = JUGADOR_UNO;
            } else {
                mejor_clasificado_humano_jugador = JUGADOR_DOS;
            }
        }
    } else {
    }
    actualizar_factor_posicion_jugador(id_jugador, algun_punto_camino_mas_cercano, indice_camino_jugador);
}

void actualizar_vehiculos(void) {
    s32 i;
    generar_humo_jugador();
    dato_8016337C++;

    if (id_circuito_actual == CEREMONIA_PREMIO_CIRCUITO) {
        for (i = 0; i < 7; i++) {
            actualizar_karts_bomba(i);
        }
        return;
    }

    if (dato_8016337C & 1) {
        if (seleccion_modo == VERSUS) {
            for (i = 0; i < 7; i++) {
                actualizar_karts_bomba(i);
            }
        }
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
        switch (id_circuito_actual) {
            case CIRCUITO_KALAMARI_DESERT:
                actualizar_trenes_vehiculo();
                break;
            case CIRCUITO_DK_JUNGLE:
                actualizar_barcos_paleta_vehiculo();
                break;
            case CIRCUITO_TOADS_TURNPIKE:
                actualizar_camiones_caja_vehiculo();
                actualizar_omnibus_escuela_vehiculo();
                actualizar_camiones_cisterna_vehiculo();
                actualizar_automoviles_vehiculo();
                break;
        }
#else

#endif
    }
}

void reproducir_cpu_efecto_sonido(s32 parametro0, Jugador* jugador) {
    if (dato_80163398[parametro0] >= 0xB) {
        if ((jugador->efectos & EFECTO_TROMPO_BANANA) || (jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) ||
            (jugador->efectos & EFECTO_GOLPE_RAYO)) {
            funcion_800C92CC(parametro0, SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0A));
            dato_80163398[parametro0] = 0;
        }
    }
    if (dato_801633B0[parametro0] >= 0xB) {
        if ((jugador->disparadores & DISPARADOR_VUELCO_VERTICAL) || (jugador->disparadores & GOLPE_POR_DISPARADOR_ESTRELLA) ||
            (jugador->disparadores & DISPARADOR_VUELCO_ALTO) || (jugador->disparadores & DISPARADOR_VUELCO_BAJO) ||
            (jugador->efectos & EFECTO_APLASTAMIENTO)) {
            funcion_800C92CC(parametro0, SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0B));
            dato_801633B0[parametro0] = 0;
        }
    }
}

void actualizar_sonido_temporizador_jugador(s32 id_jugador, SIN_USO Jugador* unused) {
    s32 otro_id_jugador;

    if (temporizador_intercambio_posicion[id_jugador] >= 0x65) {
        for (otro_id_jugador = 0; otro_id_jugador < cantidad_jugador; otro_id_jugador++) {
            if ((gp_actual_carrera_puesto_por_id_jugador[id_jugador] < gp_actual_carrera_puesto_por_id_jugador[otro_id_jugador]) &&
                (gp_actual_carrera_puesto_por_id_jugador[id_jugador] == anterior_gp_actual_carrera_puesto_por_id_jugador[otro_id_jugador]) &&
                (gp_actual_carrera_puesto_por_id_jugador[otro_id_jugador] == anterior_gp_actual_carrera_puesto_por_id_jugador[id_jugador])) {
                funcion_800C92CC(id_jugador, SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
                temporizador_intercambio_posicion[id_jugador] = 0;
            }
        }
    }
    if (temporizador_intercambio_posicion[id_jugador] < 0x3E8) {
        temporizador_intercambio_posicion[id_jugador]++;
    }
    if (dato_80163398[id_jugador] < 0xC8) {
        dato_80163398[id_jugador]++;
    }
    if (dato_801633B0[id_jugador] < 0xC8) {
        dato_801633B0[id_jugador]++;
    }
}

void actualizar_jugador(s32 id_jugador) {
    SIN_USO s32 relleno[14];
    s16 variable_a0_2;
    s16 angulo_nuevo;
    u16 indice_camino;

    f32 dist_x;
    f32 angulo_min;

    s16 angulo;
    s16 sensibilidad_direccion;

    s32 angulo_max;
    Jugador* jugador;
    SIN_USO s32 relleno3[10];
    PuntoCaminoPista* punto_camino;
    f32 un_punto_cinco = 1.5f;

    jugador = &jugadores[id_jugador];
    if ((s32) obtener_circuito_ai_maximo_separacion >= 0) {
        dato_80163100[id_jugador] += 1;
        if (id_jugador == 0) {
            jugador_actualizacion_incrementar++;
            if (jugador_actualizacion_incrementar & 1) {
                dato_80163488 += 1;
            }
        }
        if (!(jugador->type & EXISTE_JUGADOR)) {
            num_camino_puntos_recorrido[id_jugador] = -0x00000014;
            porciento_finalizacion_circuito_por_id_jugador[id_jugador] = -1000.0f;
            porciento_finalizacion_vuelta_por_id_jugador[id_jugador] = -1000.0f;
            return;
        }
        dato_801633E0[id_jugador] = 0;
        if (jugador->pos[0] < min_x_circuito) {            dato_801633E0[id_jugador] = 1;        }
        if (max_x_circuito < jugador->pos[0]) {            dato_801633E0[id_jugador] = 2;        }
        if (jugador->pos[2] < min_z_circuito) {            dato_801633E0[id_jugador] = 3;        }
        if (max_z_circuito < jugador->pos[2]) {            dato_801633E0[id_jugador] = 4;        }

        if (!(jugador->lakitu_props & MANTENIDO_POR_LAKITU) && !(jugador->lakitu_props & LAKITU_ESCENA)) {
            indice_camino_jugador = indice_camino_por_id_jugador[id_jugador];
            fijar_camino_actual(indice_camino_jugador);
            switch (id_circuito_actual) { /* irregular */
                case CIRCUITO_KALAMARI_DESERT:
                    manejar_interacciones_trenes(id_jugador, jugador);
                    if (id_jugador == 0) {
                        funcion_80013054();
                    }
                    break;
                case CIRCUITO_DK_JUNGLE:
                    manejar_interacciones_barcos_paleta(jugador);
                    break;
                case CIRCUITO_TOADS_TURNPIKE:
                    manejar_interacciones_camiones_caja(id_jugador, jugador);
                    manejar_interacciones_omnibus_escuela(id_jugador, jugador);
                    manejar_interacciones_camiones_cisterna(id_jugador, jugador);
                    manejar_interacciones_automoviles(id_jugador, jugador);
                    break;
            }
            if (jugador->type & MODO_CINEMATICA_JUGADOR) {
                jugador->efectos &= ~EFECTO_REVERSA;
                jugador->kart_props &= ~ARRIBA_ATRAS;
            }
            actualizar_finalizacion_camino_jugador(id_jugador, jugador);

            if ((id_circuito_actual != CEREMONIA_PREMIO_CIRCUITO) && ((cruzado_linea_meta[id_jugador] == 1) || (id_jugador == 0))) {
                fijar_puestos();
            }
            if (jugador->type & CPU_JUGADOR) {
                if ((es_jugador_nuevo_camino_punto == true) && (id_circuito_actual != CEREMONIA_PREMIO_CIRCUITO)) {
                    comportamiento_cpu(id_jugador);
                }
                if ((id_jugador & 1) != (jugador_actualizacion_incrementar & 1)) {
                    cpu_usar_item_estrategia(id_jugador);
                }
                actualizar_sonido_temporizador_jugador(id_jugador, jugador);
                dato_80162FD0 = 0;
                switch (seleccion_modo) {
                    case 1:
                    case 2:
                    case 3:
                        break;
                    case 0:
                        break;
                }
                dato_801631E0[id_jugador] = false;
                if ((jugador->efectos & EFECTO_CARRERA_PERDIDO) && (id_circuito_actual != CEREMONIA_PREMIO_CIRCUITO)) {
                    dato_801631E0[id_jugador] = true;
                }
                if ((dato_801646CC == 1) || (jugador->type & MODO_CINEMATICA_JUGADOR) ||
                    (id_circuito_actual == CEREMONIA_PREMIO_CIRCUITO)) {
                    if (id_circuito_actual != CIRCUITO_TOADS_TURNPIKE) {
                        jugador_pista_posicion_factor_instruccion[id_jugador].target = 0.0f;
                    }
                    jugador_pista_posicion_factor_instruccion[id_jugador].desconocido_c = 0.0f;
                }
                if (indice_camino_jugador > 0) {
                    jugador_pista_posicion_factor_instruccion[id_jugador].target = 0.0f;
                    jugador_pista_posicion_factor_instruccion[id_jugador].desconocido_c = 0.0f;
                }
                camino_y_jugador[id_jugador] =
                    caminos_pista[indice_camino_jugador][punto_camino_mas_cercano_por_id_jugador[id_jugador]].pos_y + 4.3f;
                if ((dato_801631F8[id_jugador] == 1) && (dato_801631E0[id_jugador] == false)) {
                    funcion_8002E4C4(jugador);
                }
                if (dato_801631E0[id_jugador] == true) {
                    jugador->pos[1] = camino_y_jugador[id_jugador];
                }
                dato_801631F8[id_jugador] = dato_801631E0[id_jugador];
                switch (id_circuito_actual) {
                    case CIRCUITO_YOSHI_VALLEY:
                    case CEREMONIA_PREMIO_CIRCUITO:
                        jugador_pista_posicion_factor_instruccion[id_jugador].target = 0.0f;
                        break;
                    default:
                        break;
                    case CIRCUITO_TOADS_TURNPIKE:
                        actualizar_jugador_pista_posicion_factor_desde_camiones_caja(id_jugador);
                        actualizar_jugador_pista_posicion_factor_desde_omnibus(id_jugador);
                        actualizar_jugador_pista_posicion_factor_desde_camion_cisterna(id_jugador);
                        actualizar_jugador_pista_posicion_factor_desde_automoviles(id_jugador);
                        break;
                }
                if (dato_801631E0[id_jugador] == true) {
                    dato_801630E8[id_jugador] = 0;
                    jugador->efectos &= ~EFECTO_DERRAPANDO;
                    if ((id_jugador & 1) != (jugador_actualizacion_incrementar & 1)) {
                        aplicar_giro_cpu(jugador, 0);
                        regular_cpu_rapidez(id_jugador, anterior_cpu_objetivo_rapidez[id_jugador], jugador);
                        return;
                    }
                    if ((cantidad_jugador > 0) && (cantidad_jugador < 3) && (dato_80163330[id_jugador] == 1) &&
                        (dato_8016334C[id_jugador] < gp_actual_carrera_puesto_por_id_jugador[id_jugador])) {
                        anterior_cpu_objetivo_rapidez[id_jugador] = 8.333333f;
                    } else if (dato_80162FD0 == (s16) 1U) {
                        anterior_cpu_objetivo_rapidez[id_jugador] = CIRCUITO_D_OBTENER_0D0096B8(seleccion_cc);
                        jugador_pista_posicion_factor_instruccion[id_jugador].target = -0.5f;
                    } else if (actual_pista_consecutivo_curva_cantidades_camino[algun_punto_camino_mas_cercano] > 0) {
                        anterior_cpu_objetivo_rapidez[id_jugador] = obtener_circuito_cpu_curva_objetivo_rapidez(seleccion_cc);
                    } else {
                        anterior_cpu_objetivo_rapidez[id_jugador] = obtener_circuito_cpu_normal_objetivo_rapidez(seleccion_cc);
                    }
                    comprobar_distancia_cruce_ai(id_jugador);
                    cpu_pista_posicion_factor(id_jugador);
                    determinar_ideal_cpu_posicion_desplazamiento(id_jugador, actual_mas_cercano_camino_punto);
                    dist_x = posicion_desplazamiento[0] - jugador->pos[0];
                    angulo_min = posicion_desplazamiento[2] - jugador->pos[2];
                    if (!(jugador->efectos & EFECTO_TROMPO_BANANA) && !(jugador->efectos & EFECTO_TROMPO_CONDUCIENDO) &&
                        !(jugador->efectos & BANANA_CERCA_EFECTO_TROMPO)) {
                        if (((dist_x * dist_x) + (angulo_min * angulo_min)) > 6400.0f) {
                            if (indice_camino_jugador == 0) {
                                funcion_8000B140(id_jugador);
                                if (dato_80162FF8[id_jugador] > 0) {
                                    indice_camino = actual_mas_cercano_camino_punto + 5;
                                    indice_camino %= cantidad_camino_seleccionado;
                                    fijar_posicion_desplazamiento_pista(indice_camino, dato_80163090[id_jugador], indice_camino_jugador);
                                }
                            }
                            jugador->rotacion[1] = -obtener_angulo_xz_entre_puntos(jugador->pos, posicion_desplazamiento);
                        } else {
                            jugador->rotacion[1] =
                                rotacion_esperado_camino[indice_camino_jugador]
                                                     [(actual_mas_cercano_camino_punto + 4) % cantidad_camino_seleccionado];
                        }
                    }
                    aplicar_giro_cpu(jugador, 0);
                    regular_cpu_rapidez(id_jugador, anterior_cpu_objetivo_rapidez[id_jugador], jugador);
                    return;
                }
                if ((dato_801630E8[id_jugador] == 1) || (dato_801630E8[id_jugador] == -1)) {
                    jugador->efectos |= EFECTO_DERRAPANDO;
                }
                if (dato_801630E8[id_jugador] != 0) {
                    angulo_jugador[id_jugador] = -obtener_angulo_xz_entre_puntos(jugador->pos_viejo, jugador->pos);
                    variable_a0_2 =
                        (actual_camino_punto_esperado_rotacion_camino[(algun_punto_camino_mas_cercano + 2) % cantidad_camino_seleccionado] *
                         0x168) /
                        65535;
                    angulo_nuevo = (angulo_jugador[id_jugador] * 0x168) / 65535;
                    if (variable_a0_2 < -0xB4) {
                        variable_a0_2 += 0x168;
                    }
                    if (variable_a0_2 > 0xB4) {
                        variable_a0_2 -= 0x168;
                    }
                    if (angulo_nuevo < -0xB4) {
                        angulo_nuevo += 0x168;
                    }
                    if (angulo_nuevo > 0xB4) {
                        angulo_nuevo -= 0x168;
                    }
                    sensibilidad_direccion = variable_a0_2 - angulo_nuevo;
                    if (sensibilidad_direccion < -0xB4) {
                        sensibilidad_direccion += 0x168;
                    }
                    if (sensibilidad_direccion > 0xB4) {
                        sensibilidad_direccion -= 0x168;
                    }
                    switch (dato_801630E8[id_jugador]) {
                        case -1:
                            if (sensibilidad_direccion > 5) {
                                dato_801630E8[id_jugador] = 0;
                                jugador->efectos &= ~EFECTO_DERRAPANDO;
                            }
                            break;
                        case 1:
                            if (sensibilidad_direccion < -5) {
                                dato_801630E8[id_jugador] = 0;
                                jugador->efectos &= ~EFECTO_DERRAPANDO;
                            }
                            break;
                        default:
                            break;
                    }
                }

                if ((id_jugador & 1) != (jugador_actualizacion_incrementar & 1)) {
                    aplicar_giro_cpu(jugador, direccion_angulo_anterior[id_jugador]);
                    regular_cpu_rapidez(id_jugador, anterior_cpu_objetivo_rapidez[id_jugador], jugador);
                    return;
                }
                es_jugador_en_curva[id_jugador] = son_en_curva(id_jugador, algun_punto_camino_mas_cercano);
                determinar_ideal_cpu_posicion_desplazamiento(id_jugador, algun_punto_camino_mas_cercano);
                if (id_circuito_actual != CEREMONIA_PREMIO_CIRCUITO) {
                    if (num_camino_puntos_recorrido[id_jugador] < 0xB) {
                        indice_camino = actual_mas_cercano_camino_punto;
                        if ((num_camino_puntos_recorrido[id_jugador] > 0) && (id_circuito_actual == CIRCUITO_TOADS_TURNPIKE)) {
                            indice_camino += 0x14;
                            indice_camino %= cantidad_camino_seleccionado;
                            fijar_posicion_desplazamiento_pista(indice_camino, 0.0f, 0);
                            jugador_pista_posicion_factor_instruccion[id_jugador].target = 0.0f;
                        } else {
                            indice_camino += 8;
                            indice_camino %= cantidad_camino_seleccionado;
                            fijar_posicion_desplazamiento_pista(indice_camino, factor_posicion_pista[id_jugador], indice_camino_jugador);
                            jugador_pista_posicion_factor_instruccion[id_jugador].current = factor_posicion_pista[id_jugador];
                        }
                    }
                    if ((dato_80162FD0 == 1) && (dato_80162FF8[id_jugador] == 0)) {
                        indice_camino = actual_mas_cercano_camino_punto + 7;
                        indice_camino %= cantidad_camino_seleccionado;
                        fijar_posicion_desplazamiento_pista(indice_camino, -0.7f, indice_camino_jugador);
                    }
                    if (1) { } if (1) { } if (1) { } if (1) { } if (1) { } if (1) { }
                    if (indice_camino_jugador == 0) {
                        funcion_8000B140(id_jugador);
                        if (dato_80162FF8[id_jugador] > 0) {
                            indice_camino = actual_mas_cercano_camino_punto + 5;

                            indice_camino %= cantidad_camino_seleccionado;
                            fijar_posicion_desplazamiento_pista(indice_camino, dato_80163090[id_jugador], indice_camino_jugador);
                        }
                    }
                }
                if (id_circuito_actual == CEREMONIA_PREMIO_CIRCUITO) {
                    switch (dato_80163410[id_jugador]) {
                        case 3:
                            posicion_desplazamiento[0] = dato_80163418[id_jugador];
                            posicion_desplazamiento[2] = dato_80163438[id_jugador];
                            break;
                        case 4:
                            punto_camino = &caminos_pista[id_jugador][(punto_camino_mas_cercano_por_id_jugador[id_jugador] + 0xA) %
                                                               cantidad_camino_por_indice_camino[id_jugador]];
                            posicion_desplazamiento[0] = punto_camino->pos_x;
                            posicion_desplazamiento[2] = punto_camino->pos_z;
                            break;
                    }
                }
                posicion_desplazamiento[0] = (anterior_jugador_ai_desplazamiento_x[id_jugador] + posicion_desplazamiento[0]) * 0.5f;
                posicion_desplazamiento[2] = (anterior_jugador_ai_desplazamiento_z[id_jugador] + posicion_desplazamiento[2]) * 0.5f;
                anterior_jugador_ai_desplazamiento_x[id_jugador] = posicion_desplazamiento[0];
                anterior_jugador_ai_desplazamiento_z[id_jugador] = posicion_desplazamiento[2];
                angulo_min = un_punto_cinco * (f32) GRADOS(1);
                angulo_max = -un_punto_cinco * (f32) GRADOS(1);

                angulo = -obtener_angulo_xz_entre_puntos(jugador->pos, posicion_desplazamiento);
                angulo -= (angulo_nuevo = jugador->rotacion[1]);
                if ((s16) angulo_min < angulo) {
                    angulo = angulo_min;
                }
                if (angulo < (s16) angulo_max) {
                    angulo = angulo_max;
                }
                sensibilidad_direccion = obtener_circuito_ai_direccion_sensibilidad;
                switch (actual_pista_seccion_tipos_camino[id_jugador]) {
                    case CURVA_DERECHA:
                        if (factor_posicion_pista[id_jugador] > (0.5f * 1.0f)) {
                            sensibilidad_direccion = 0x0014;
                        }
                        if (factor_posicion_pista[id_jugador] < -0.5f) {
                            sensibilidad_direccion = 0x0035;
                        }
                        break;
                    case CURVA_IZQUIERDA:
                        if (factor_posicion_pista[id_jugador] > 0.5f) {
                            sensibilidad_direccion = 0x0035;
                        }
                        if (factor_posicion_pista[id_jugador] < -0.5f) {
                            sensibilidad_direccion = 0x0014;
                        }
                        break;
                }
                if ((cpu_comportamiento_estado[id_jugador] == CPU_COMPORTAMIENTO_ESTADO_EJECUTANDO) &&
                    ((factor_posicion_pista[id_jugador] > 0.9f) || (factor_posicion_pista[id_jugador] < -0.9f))) {
                    dato_801630E8[id_jugador] = 0;
                    jugador->efectos &= ~EFECTO_DERRAPANDO;
                }
                if (jugador->efectos & EFECTO_SALTO) {
                    switch (dato_801630E8[id_jugador]) {
                        case 1:
                            angulo_nuevo = 0x0035;
                            break;
                        case -1:
                            angulo_nuevo = -0x0035;
                            break;
                        default:
                            angulo_nuevo =
                                (direccion_angulo_anterior[id_jugador] + ((angulo * sensibilidad_direccion) / angulo_min)) / 2;
                            break;
                    }
                } else if (jugador->efectos & (desconocido_efecto_0_x_10000000 | EFECTO_EN_EL_AIRE | IMPULSO_RAMPA_MADERA_EFECTO)) {
                    angulo_nuevo = 0;
                } else {
                    angulo_nuevo = (direccion_angulo_anterior[id_jugador] + ((angulo * sensibilidad_direccion) / angulo_min)) / 2;
                }
                aplicar_giro_cpu(jugador, angulo_nuevo);
                direccion_angulo_anterior[id_jugador] = angulo_nuevo;
                if ((es_jugador_en_curva[id_jugador] == true) || (dato_801630E8[id_jugador] == 1) ||
                    (dato_801630E8[id_jugador] == -1) ||
                    (jugador->efectos & (desconocido_efecto_0_x_10000000 | EFECTO_EN_EL_AIRE | IMPULSO_RAMPA_MADERA_EFECTO))) {
                    cpu_objetivo_rapidez[id_jugador] = obtener_circuito_cpu_curva_objetivo_rapidez(seleccion_cc);
                } else {
                    cpu_objetivo_rapidez[id_jugador] = obtener_circuito_cpu_normal_objetivo_rapidez(seleccion_cc);
                }
                if ((factor_posicion_pista[id_jugador] > 0.9f) || (factor_posicion_pista[id_jugador] < -0.9f)) {
                    cpu_objetivo_rapidez[id_jugador] = obtener_circuito_cpu_apagado_pista_objetivo_rapidez(seleccion_cc);
                }
                if (dato_80162FD0 == 1) {
                    cpu_objetivo_rapidez[id_jugador] = CIRCUITO_D_OBTENER_0D0096B8(seleccion_cc);
                }
                if ((dato_801630E8[id_jugador] == 2) || (dato_801630E8[id_jugador] == -2) || (dato_801630E8[id_jugador] == 3)) {
                    cpu_objetivo_rapidez[id_jugador] = 3.3333333f;
                }
                actual_cpu_objetivo_rapidez = cpu_objetivo_rapidez[id_jugador];
                jugador->efectos &= ~EFECTO_RAPIDO_CPU;
                anterior_cpu_objetivo_rapidez[id_jugador] = actual_cpu_objetivo_rapidez;
                comprobar_distancia_cruce_ai(id_jugador);
                regular_cpu_rapidez(id_jugador, actual_cpu_objetivo_rapidez, jugador);
            }
        }
    }
}

void funcion_8000B140(s32 id_jugador) {
    s32 i;
    f32 temporal_f12;
    f32 temporal_f14;
    s32 j;
    f32 temporal_f16;
    f32 temporal_ft2;
    s16 punto_camino_act;
    s16 temporal_v1_2;
    f32 temporal_f22;
    f32 temporal_f0_2;
    f32 variable_f18;
    f32 variable_f20;
    SIN_USO s32 relleno[5];
    s16 sp_b0[8];
    SIN_USO f32 relleno2;
    s16 sp9_c[8];
    SIN_USO f32 relleno3;
    f32 temporal_f2;
    f32 sp74[8];
    s32 temporal_a1_2;
    Jugador* jugador;
    jugador = &jugadores[id_jugador];

    if (jugador->efectos & EFECTO_DERRAPANDO) {
        return;
    }

    if (dato_801630E8[id_jugador] == 1) {
        return;
    }

    if (dato_801630E8[id_jugador] == -1) {
        return;
    }

    if (factor_posicion_pista[id_jugador] < -1.0f) {
        return;
    }

    if (factor_posicion_pista[id_jugador] > 1.0f) {
        return;
    }

    if (jugador->id_personaje == WARIO) {
        return;
    }

    if (jugador->id_personaje == BOWSER) {
        return;
    }

    if (jugador->id_personaje == DK) {
        return;
    }

    if (jugador->efectos & EFECTO_ESTRELLA) {
        return;
    }

    punto_camino_act = punto_camino_mas_cercano_por_id_jugador[id_jugador];
    temporal_f22 = (jugador->speed / 18.0f) * 216.0f;
    for (i = 0; i < 8; i++) {
        sp9_c[i] = -1;
        sp_b0[i] = 0x03E8;
    }

    if (dato_80163010[id_jugador] > 0) {
        dato_80163010[id_jugador]--;
        if (dato_80163010[id_jugador] <= 0) {
            dato_80162FF8[id_jugador] = 0;
        }
    }
    j = 0;
    i = 0;
    while (i < 8) {
        if (i != id_jugador) {
            jugador = &jugadores[i];
            if ((jugador->type & EXISTE_JUGADOR)) {
                temporal_v1_2 = punto_camino_mas_cercano_por_id_jugador[i];
                temporal_f0_2 = (jugador->speed / 18.0f) * 216.0f;
                temporal_f2 = temporal_f22 - 5.0f;
                if (temporal_f0_2 < temporal_f2) {
                    if (es_punto_camino_en_rango(temporal_v1_2, punto_camino_act, 0, 0x0014U, cantidad_camino_seleccionado) > 0) {
                        temporal_a1_2 = temporal_v1_2 - punto_camino_act;
                        sp9_c[j] = i;
                        if (temporal_a1_2 > 0) {
                            sp_b0[j] = temporal_a1_2;
                        } else {
                            sp_b0[j] = (temporal_v1_2 + cantidad_camino_seleccionado) - punto_camino_act;
                        }
                        sp74[j] = temporal_f2 - temporal_f0_2;
                        j++;
                    }

                }
            }
        }
        i++;
        if (j >= 2) {
            break;
        }
    }

    if (j == 0) {
        return;
    }

    variable_f18 = 1.0f;
    variable_f20 = -1.0f;
    for (i = 0; i < j; i++) {
        temporal_f2 = factor_posicion_pista[sp9_c[i]];
        if ((temporal_f2 > (-1.0f)) && (temporal_f2 < 1.0f)) {

            temporal_f12 = temporal_ft2 = ((0.2f * (20.0f / (sp_b0[i] + 20.0f))) * ((sp74[i]) + 10.0f))  / 20.0f;

            if ((variable_f18 == 1.0f) && (variable_f20 == (-1.0f))) {
                variable_f18 = temporal_f2 - temporal_f12;
                variable_f20 = temporal_f2 + temporal_f12;
            } else {
                temporal_f14 = temporal_f2 - temporal_f12;
                temporal_f16 = temporal_f2 + temporal_f12;
                if ((temporal_f14 < variable_f18) && (temporal_f16 > variable_f18)) {
                    variable_f18 = temporal_f14;
                }
                if ((temporal_f16 > variable_f20) && (temporal_f14 < variable_f20)) {
                    variable_f20 = temporal_f16;
                }
            }
        }
    }

    if (variable_f20 < variable_f18) {
        return;
    }

    if (factor_posicion_pista[id_jugador] < variable_f18) {
        return;
    }

    if (variable_f20 < factor_posicion_pista[id_jugador]) {
        return;
    }

    if (variable_f20 > 1.0f) {
        variable_f20 = 1.0f;
    }
    if (variable_f18 < (-1.0f)) {
        variable_f18 = -1.0f;
    }
    if ((variable_f18 + 1.0f) < (1.0f - variable_f20)) {
        dato_80163010[id_jugador] = 0x003C;
        dato_80162FF8[id_jugador] = 1;
        dato_80163090[id_jugador] = variable_f20;
    } else {
        dato_80163010[id_jugador] = 0x003C;
        dato_80162FF8[id_jugador] = 2;
        dato_80163090[id_jugador] = variable_f18;
    }
}

#include "utilidades_camino.inc.c"

#include "kart_bomba.inc.c"

#include "utilidades_actores.inc.c"

void funcion_8000F0E0(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        dato_80164670[i] = 0;
        dato_80164678[i] = 0;
    }
}

void funcion_8000F124(void) {
    s32 debe_continuar;
    s32 i, j;

    for (j = 0; j < 2; j++) {
        dato_80163348[j] = 0;
    }

    if (modo_demo == 1) {
        return;
    }
    if (seleccion_modo != GRAN_PREMIO) {
        return;
    }

    for (i = 0; i < 2; i++) {

        while (1) {
            dato_80163348[i] = int_aleatorio(JUGADORES_NUM);

            if (cantidad_jugador > 2) {
                break;
            }
            if (cantidad_jugador < 1) {
                break;
            }

            debe_continuar = false;

            for (j = 0; j < cantidad_jugador; j++) {
                if (selecciones_personaje[j] == dato_80163348[i]) {
                    debe_continuar = true;
                }
            }
            for (j = 0; j < i; j++) {
                if (dato_80163348[j] == dato_80163348[i]) {
                    debe_continuar = true;
                }
            }
            if (debe_continuar == false) {
                break;
            }
        }
    }
}

void borrar_punto_camino(PuntoCaminoPista* parametro0, size_t size) {
    bzero((void*) parametro0, size * sizeof(PuntoCaminoPista));
}
