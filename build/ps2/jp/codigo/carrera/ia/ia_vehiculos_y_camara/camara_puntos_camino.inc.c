// Camara puntos camino

void inicializar_punto_camino_circuito(void) {

    struct _struct_g_circuito_camino_tamanios_0_x10* ptr = &obtener_circuito_camino_tamanios;
    s32 temporal_;
    s32 i;

    camino_tamanio[0] = (s32) ptr->primer_camino;
    camino_tamanio[1] = (s32) ptr->segundo_camino;
    camino_tamanio[2] = (s32) ptr->tercer_camino;
    camino_tamanio[3] = (s32) ptr->cuarto_camino;

    temporal_ = ptr->desconocido8;
    punto_camino_vehiculo_2d = obtener_siguiente_disponible_memoria_direccion(temporal_ * 4);

    for (i = 0; i < 4; i++) {
        caminos_pista[i] = obtener_siguiente_disponible_memoria_direccion(camino_tamanio[i] * sizeof(PuntoCaminoPista));
        caminos_izquierda_pista[i] = obtener_siguiente_disponible_memoria_direccion(camino_tamanio[i] * sizeof(PuntoCaminoPista));
        caminos_derecha_pista[i] = obtener_siguiente_disponible_memoria_direccion(camino_tamanio[i] * sizeof(PuntoCaminoPista));
        tipos_seccion_pista[i] = obtener_siguiente_disponible_memoria_direccion(camino_tamanio[i] * sizeof(s16));
        rotacion_esperado_camino[i] = obtener_siguiente_disponible_memoria_direccion(camino_tamanio[i] * sizeof(s16));
        pista_consecutivo_curva_cantidades[i] = obtener_siguiente_disponible_memoria_direccion(camino_tamanio[i] * sizeof(s16));
    }

    camino_pista_actual = caminos_pista[0];
    actual_pista_izquierda_camino = caminos_izquierda_pista[0];
    actual_pista_derecha_camino = caminos_derecha_pista[0];
    actual_pista_seccion_tipos_camino = tipos_seccion_pista[0];
    actual_camino_punto_esperado_rotacion_camino = rotacion_esperado_camino[0];
    actual_pista_consecutivo_curva_cantidades_camino = pista_consecutivo_curva_cantidades[0];

    for (i = 0; i < 4; i++) {
        borrar_punto_camino(caminos_pista[i], camino_tamanio[i]);
        borrar_punto_camino(caminos_izquierda_pista[i], camino_tamanio[i]);
        borrar_punto_camino(caminos_derecha_pista[i], camino_tamanio[i]);
    }

    for (i = 0; i < 4; i++) {}

    for (i = 0; i < 4; i++) {
        if (camino_tamanio[i] >= 2) {
            cargar_camino_pista(i);
            calcular_limites_pista(i);
            analizar_secciones_pista(i);
            analizar_angulo_camino(i);
            analizar_camino_curvo(i);
        }
    }
    MARCAR_TIEMPOS_PS2("caminos de la IA");

    cantidad_camino_seleccionado = *cantidad_camino_por_indice_camino;
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_KALAMARI_DESERT:
            generar_camino_tren();
            MARCAR_TIEMPOS_PS2("camino del tren");
            inicializar_trenes_vehiculos();
            MARCAR_TIEMPOS_PS2("trenes");
            break;
        case CIRCUITO_DK_JUNGLE:
            generar_camino_ferry();
            MARCAR_TIEMPOS_PS2("camino del barco");
            inicializar_ferry_vehiculos();
            MARCAR_TIEMPOS_PS2("barco");
            break;
        case CIRCUITO_TOADS_TURNPIKE:
            inicializar_camiones_caja_vehiculos();
            inicializar_omnibus_escuela_vehiculos();
            inicializar_camiones_vehiculos();
            inicializar_automoviles_vehiculos();
            break;
    }
#else

#endif
    aparecer_posiciones_conjunto_kart_bomba();
    funcion_8000EEDC();
}

void inicializar_jugadores(void) {

    SIN_USO Camara* camara;
    s32 temporal_v0_3;
    s32 i;
    PistaPosicionFactorInstruccion* variable_s5;
    SIN_USO s32 temporal_v1;
    SIN_USO s32 relleno;

    for (i = 0; i < JUGADORES_NUM; i++) {
        Jugador* jugador = &jugador_uno[i];

        direccion_angulo_anterior[i] = 0;
        dato_80162FF8[i] = 0;
        dato_80163010[i] = 0;
        if (id_circuito_actual < (CIRCUITOS_NUM - 1)) {
            actualizar_factor_posicion_jugador(i, 0, 0);
        }
        cpu_objetivo_rapidez[i] = obtener_circuito_cpu_curva_objetivo_rapidez(seleccion_cc);
        dato_801630E8[i] = 0;
        dato_80163100[i] = 0;
        anterior_jugador_ai_desplazamiento_x[i] = 0.0f;
        anterior_jugador_ai_desplazamiento_z[i] = 0.0f;
        anterior_cpu_objetivo_rapidez[i] = 0.0f;
        cantidad_vuelta_por_id_jugador[i] = -1;
        porciento_finalizacion_circuito_por_id_jugador[i] = 0.0f;
        tiempo_jugador_ultimo_tocado_linea_meta[i] = 0.0f;
        if (seleccion_modo == GRAN_PREMIO) {
            if (1) {};
            if (1) {};
            gp_actual_carrera_puesto_por_id_jugador[i] = (s32) dato_80165270[i];
            anterior_gp_actual_carrera_puesto_por_id_jugador[i] = (s32) dato_80165270[i];
        } else {
            gp_actual_carrera_puesto_por_id_jugador[i] = i;
            anterior_gp_actual_carrera_puesto_por_id_jugador[i] = i;
        }
        temporal_v0_3 = gp_actual_carrera_puesto_por_id_jugador[i];
        gp_actual_carrera_jugador_id_por_puesto[temporal_v0_3] = (s16) i;
        id_jugador_ant_por_puesto[temporal_v0_3] = (s16) i;
        gp_actual_carrera_puesto_por_duplicar_id_jugador[i] = temporal_v0_3;
        contador_sentido_incorrecto[i] = 0;
        es_sentido_incorrecto_jugador[i] = 0;
        dato_801631E0[i] = false;
        dato_801631F8[i] = 0;
        num_camino_puntos_recorrido[i] = -20;
        anterior_vuelta_progreso_puntaje[i] = -20;
        jugador_obtener_por_id_personaje[jugadores[i].id_personaje] = (s16) i;
        factor_posicion_pista[i] = 0.0f;
        dato_80163090[i] = 0.0f;
        variable_s5 = &jugador_pista_posicion_factor_instruccion[i];
        variable_s5->desconocido_c = obtener_circuito_ai_minimo_separacion * (f32) (((i + 1) % 3) - 1);
        variable_s5->target = variable_s5->desconocido_c;
        variable_s5->current = 0.0f;
        variable_s5->paso = 0.015f;
        reiniciar_ninguno_comportamiento_cpu(i);
        comportamiento_cpu_rapidez[i] = 0;
        b_en_multi_seccion_camino[i] = 0;
        dato_80163398[i] = 0;
        dato_801633B0[i] = 0;
        temporizador_intercambio_posicion[i] = 0;
        dato_801633F8[i] = 0;
        jugadores_pista_seccion_id[i] = 0;
        g_jugador_z_anterior[i] = jugador->pos[2];
        actual_jugador_mirada_adelante[i] = 6;
        if (jugadores[i].type & HUMANO_JUGADOR) {
            dato_80163330[i] = 3;

        } else {
            dato_80163330[i] = 0;
        }

        cpu_entrando_camino_interseccion[i] = 0;
        cpu_saliendo_camino_interseccion[i] = 0;
        dato_80163128[i] = -1;
        dato_80163150[i] = -1;
        dato_80164538[i] = -1;
        dato_801634C0[i] = 0;
        b_parada_ai_cruce[i] = 0;
        es_jugador_en_curva[i] = true;
    }

#ifdef AVOID_UB
    for (i = 0; i < CRUCES_NUM; i++) {
        temporizador_activo_cruce[i] = 0;
    }
#else
    temporizador_activo_cruce[0] = 0;
    temporizador_activo_cruce[1] = 0;
#endif
    if (modo_demo == INACTIVO_MODO_DEMO) {

        if (seleccion_modo == GRAN_PREMIO) {
            for (i = 0; i < 2; i++) {
                dato_80163344[i] = jugador_obtener_por_id_personaje[dato_80163348[i]];
                dato_80163330[dato_80163344[i]] = 1;
                dato_8016334C[dato_80163344[i]] = i;
            }
        }
    }
    if ((mando_usar_demo == 1) && (id_circuito_actual != CEREMONIA_PREMIO_CIRCUITO)) {
        for (i = 0; i < JUGADORES_NUM; i++) {
            dato_80163330[i] = 0;
        }
        if (seleccion_modo == VERSUS) {

            dato_80163344[0] = camaras->id_jugador;
            dato_80163330[dato_80163344[0]] = 1;
            dato_8016334C[dato_80163344[0]] = 0;

            for (i = 1; i < 2; i++) {
                dato_80163344[i] = camaras[i].id_jugador;
                dato_80163330[dato_80163344[i]] = 1;
                dato_8016334C[dato_80163344[i]] = i;
            }
        }
    }

    for (i = 0; i < JUGADORES_NUM; i++) {
        if (1) {};
        indice_camino_por_id_jugador[i] = 0;
        punto_camino_mas_cercano_por_id_jugador[i] =
            cantidad_camino_por_indice_camino[indice_camino_por_id_jugador[i]] - gp_actual_carrera_puesto_por_id_jugador[i] - 4;
    }

    es_en_extra = false;
    if (seleccion_cc == CC_EXTRA) {
        es_en_extra = true;
    }

    for (i = 0; i < 30; i++) {
        dato_80162F10[i] = -1;
        dato_80162F50[i] = -1;
    }

    dato_801631CC = 100000;
    dato_80164698 = 0.0f;
    dato_8016469C = 100.0f;
    dato_801646A0 = 0.0f;
    dato_80164358 = 0;
    dato_8016435A = 1;
    dato_8016435C = 1;
    mejor_clasificado_humano_jugador = JUGADOR_UNO;
    jugador_actualizacion_incrementar = 0;
    dato_8016337C = 0;
    inicio_z_camino = (f32) caminos_pista[0][0].pos_z;
    dato_801634F0 = 0;
    dato_801634F4 = 0;
    dato_80163488 = 0;
    dato_8016348C = 0;
    dato_801634EC = 0;
    funcion_8001AB00();
    if (mando_usar_demo == 1) {
        if (modo_demo == 1) {

            for (i = 0; i < JUGADORES_NUM; i++) {
                if (dato_80163330[i] == 1) {
                    jugadores[i].disparadores |= DISPARADOR_IMPULSO_INICIO;
                }
            }
        }
    }
    copiar_comportamiento_cpu_circuitos();
}

#include "calculo_camino.inc.c"

#include "utilidades_comportamiento.inc.c"

#include "utilidades_vehiculos.inc.c"

void funcion_80014D30(s32 id_camara, s32 indice_camino) {
    s16 punto_camino_camara;
    PuntoCaminoPista* temporal_v0;

    punto_camino_camara = punto_camino_mas_cercano_por_id_camara[id_camara];
    temporal_v0 = &caminos_pista[indice_camino][punto_camino_camara];
    comprobar_colision_envolvente(&camaras[id_camara].colision, 10.0f, (f32) temporal_v0->pos_x, (f32) temporal_v0->pos_y + 30.0f,
                             (f32) temporal_v0->pos_z);
}

void funcion_80014DE4(s32 indice_camara) {
    s32 id_camara;

    dato_801646CC = 0;
    dato_80164678[indice_camara] = dato_80164670[indice_camara];
    if ((seleccion_modo != 1) && ((indice_circuito_en_copa == CIRCUITO_UNO) || (modo_demo == (u16) 1))) {
        dato_80164678[indice_camara] = 0;
    } else if ((dato_80164678[indice_camara] != 0) && (dato_80164678[indice_camara] != (s16) 1) &&
               (dato_80164678[indice_camara] != 2) && (dato_80164678[indice_camara] != 3)) {
        dato_80164678[indice_camara] = 0;
    }
    dato_80164680[indice_camara] = -1;
    dato_80163238 = 0;
    dato_801646C0[indice_camara] = 0;
    dato_801646C8 = 0;
    dato_801646D0[indice_camara].desconocido0 = 0;
    dato_801646D0[indice_camara].desconocido2 = 0;
    dato_801646D0[indice_camara].desconocido4 = 0;
    if ((seleccion_modo == 1) && (inicializacion_mapa_circuito == 0)) {
        dato_80164678[indice_camara] = 0;
    }

    for (id_camara = 0; id_camara < 4; id_camara++) {
        punto_camino_mas_cercano_por_id_camara[id_camara] = 0;
    }
}

f32 funcion_80014EE4(f32 parametro0, s32 parametro1) {
    f32 temporal_f0;
    f64 temporal_f2;

    temporal_f0 = dato_80164498[parametro1];
    switch (dato_80164678[parametro1]) { /* irregular */
        default:
            parametro0 = 40.0f;
            break;
        case 0:
            temporal_f2 = 40.0;
            temporal_f2 += temporal_f0;
            if (temporal_f2 < parametro0) {
                parametro0 -= 1.0;
                if (parametro0 < temporal_f2) {
                    parametro0 = temporal_f2;
                }
            }
            if (parametro0 < temporal_f2) {
                parametro0 += 1.0;
                if (temporal_f2 < parametro0) {
                    parametro0 = temporal_f2;
                    ;
                }
            }
            break;
        case 1:
            temporal_f2 = 60.0;
            temporal_f2 += temporal_f0;
            if (parametro0 < temporal_f2) {
                parametro0 += 1.0;
                if (temporal_f2 < parametro0) {
                    parametro0 = temporal_f2;
                }
            }
            if (temporal_f2 < parametro0) {
                parametro0 -= 1.0;
                if (parametro0 < temporal_f2) {
                    parametro0 = temporal_f2;
                    ;
                }
            }
            break;
        case 3:
            temporal_f2 = 60.0;
            temporal_f2 += temporal_f0;
            if (parametro0 < temporal_f2) {
                parametro0 += 0.5;
                if (temporal_f2 < parametro0) {
                    parametro0 = temporal_f2;
                }
            }
            if (temporal_f2 < parametro0) {
                parametro0 -= 0.5;
                if (parametro0 < temporal_f2) {
                    parametro0 = temporal_f2;
                }
            }
            break;
        case 2:
            temporal_f2 = 60.0;
            temporal_f2 += temporal_f0;
            if (parametro0 < temporal_f2) {
                parametro0 += 1.0;
                if (temporal_f2 < parametro0) {
                    parametro0 = temporal_f2;
                }
            }
            if (temporal_f2 < parametro0) {
                parametro0 -= 1.0;
                if (parametro0 < temporal_f2) {
                    parametro0 = temporal_f2;
                }
            }
            break;
    }
    return parametro0;
}

void calcular_vector_arriba_camara(Camara* camara, s32 indice_camara) {
    f32 xnorm;
    f32 ynorm;
    f32 znorm;
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    f32 distancia;
    f32 sp28;
    u16 cosa;

    cosa = dato_801646C0[indice_camara];
    if (cosa == 0) {
        camara->arriba[0] = 0.0f;
        camara->arriba[2] = 0.0f;
        camara->arriba[1] = 1.0f;
    } else {
        xdiff = camara->mirar_a[0] - camara->pos[0];
        ydiff = camara->mirar_a[1] - camara->pos[1];
        zdiff = camara->mirar_a[2] - camara->pos[2];
        distancia = sqrtf((xdiff * xdiff) + (ydiff * ydiff) + (zdiff * zdiff));
        xnorm = xdiff / distancia;
        ynorm = ydiff / distancia;
        znorm = zdiff / distancia;
        sp28 = 1.0 - coss(cosa);
        camara->arriba[0] = (sp28 * xnorm * ynorm) - (senos(cosa) * znorm);
        camara->arriba[1] = coss(cosa) + (sp28 * ynorm * ynorm);
        camara->arriba[2] = (senos(cosa) * xnorm) + (sp28 * ynorm * znorm);
    }
}

SIN_USO void funcion_8001530C(void) {
}

void funcion_80015314(s32 id_jugador, SIN_USO f32 parametro1, s32 id_camara) {
    Camara* temporal_a0;
    Jugador* temporal_a1;

    temporal_a1 = jugador_uno;
    temporal_a0 = camara1;
    temporal_a1 += id_jugador;
    temporal_a0 += id_camara;
    temporal_a0->desconocido_2C = temporal_a1->rotacion[1];
    funcion_80015390(temporal_a0, temporal_a1, 0);
}

void funcion_80015390(Camara* camara, SIN_USO Jugador* jugador, SIN_USO s32 parametro2) {
    SIN_USO s32 relleno[6];
    f32 temporal_f12;
    f32 sp90;
    f32 temporal_f14;
    Jugador* temporal_s1;
    f32 sp84;
    f32 sp80;
    f32 sp7_c;
    SIN_USO Vec3f relleno2;
    Vec3f sp64;
    SIN_USO s32 relleno3[9];
    s16 variable_a2;

    temporal_s1 = jugador_uno;
    temporal_s1 += camara->id_jugador;
    if (temporal_s1->desconocido_078 == 0) {
        variable_a2 = 0x0064;
    } else if (temporal_s1->desconocido_078 < 0) {
        variable_a2 = 0xA0 - (temporal_s1->desconocido_078 / 16);
    } else {
        variable_a2 = 0xA0 + (temporal_s1->desconocido_078 / 16);
    }
    if (!((temporal_s1->efectos & EFECTO_TROMPO_BANANA) || (temporal_s1->efectos & EFECTO_TROMPO_CONDUCIENDO))) {
        ajustar_angulo(&camara->desconocido_2C, temporal_s1->rotacion[1], variable_a2);
    }
    funcion_8001D794(temporal_s1, camara, sp64, &sp84, &sp80, &sp7_c, camara->desconocido_2C);
    comprobar_colision_envolvente(&camara->colision, 10.0f, sp84, sp80, sp7_c);
    camara->mirar_a[0] = sp64[0];
    camara->mirar_a[1] = sp64[1];
    camara->mirar_a[2] = sp64[2];
    camara->pos[0] = sp84;
    camara->pos[1] = sp80;
    camara->pos[2] = sp7_c;
    temporal_f12 = camara->mirar_a[0] - camara->pos[0];
    sp90 = camara->mirar_a[1] - camara->pos[1];
    temporal_f14 = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(temporal_f12, temporal_f14);
    camara->rot[0] = atan2s(sqrtf((temporal_f12 * temporal_f12) + (temporal_f14 * temporal_f14)), sp90);
    camara->rot[2] = 0;
}

void funcion_80015544(s32 id_jugador, f32 parametro1, s32 id_camara, s32 indice_camino) {
    Camara* camara;

    f32 temporal_f12;
    f32 temporal_f2;
    s32 probar = cantidad_camino_por_indice_camino[indice_camino];

    dato_80164688[id_camara] = parametro1;
    camara = camaras + id_camara;
    punto_camino_mas_cercano_por_id_camara[id_camara] = (punto_camino_mas_cercano_por_id_jugador[id_jugador] + 10) % probar;

    fijar_posicion_desplazamiento_pista(punto_camino_mas_cercano_por_id_camara[id_camara], parametro1, indice_camino);

    dato_801645F8[id_camara] = posicion_desplazamiento[0];
    dato_80164638[id_camara] = posicion_desplazamiento[2];

    temporal_f2 = (f32) caminos_pista[indice_camino][punto_camino_mas_cercano_por_id_camara[id_camara]].pos_y;

    temporal_f12 = obtener_altura_superficie(posicion_desplazamiento[0], (f32) (temporal_f2 + 30.0), posicion_desplazamiento[2]);
    if ((temporal_f12 < (temporal_f2 - 20.0)) || (temporal_f12 >= 3000.0)) {
        dato_80164618[id_camara] = (f32) (temporal_f2 + 10.0);
    } else {
        dato_80164618[id_camara] = (f32) (temporal_f12 + 10.0);
    }
    dato_80164648[id_camara] = 0.0f;
    camara->pos[0] = dato_801645F8[id_camara];
    camara->pos[1] = dato_80164618[id_camara];
    camara->pos[2] = dato_80164638[id_camara];
}

void funcion_8001577C(Camara* camara, SIN_USO Jugador* parametro_jugador, SIN_USO s32 parametro2, s32 id_camara) {
    s16 punto_camino_camara;
    s16 punto_camino_jugador;
    SIN_USO s32 relleno;
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    SIN_USO s32 relleno2;
    s32 id_jugador;
    SIN_USO s32 relleno3[9];
    Jugador* jugador;
    s32 dif_punto_camino;
    s32 indice_camino;

    id_jugador = camara->id_jugador;
    indice_camino = indice_camino_por_id_jugador[id_jugador];
    jugador = jugador_uno;
    jugador += id_jugador;
    punto_camino_mas_cercano_por_id_camara[id_camara] =
        funcion_8000D33C(camara->pos[0], camara->pos[1], camara->pos[2], punto_camino_mas_cercano_por_id_camara[id_camara], indice_camino);
    punto_camino_jugador = punto_camino_mas_cercano_por_id_jugador[id_jugador];
    punto_camino_camara = punto_camino_mas_cercano_por_id_camara[id_camara];
    if (es_punto_camino_en_rango(punto_camino_jugador, punto_camino_camara, 0x0032U, 0x000FU, cantidad_camino_por_indice_camino[indice_camino]) <=
        0) {
        funcion_8001A348(id_camara, dato_80164688[id_camara], dato_80164680[id_camara]);
    } else {
        if (factor_posicion_pista[id_jugador] < (-0.7)) {
            dif_punto_camino = punto_camino_jugador - punto_camino_camara;
            if ((dato_80164688[id_camara] < (-0.5)) && ((dif_punto_camino * dif_punto_camino) < 5)) {
                funcion_8001A348(id_camara, 1.0f, 3);
                goto alable;
            }
        }
        if (factor_posicion_pista[id_jugador] > 0.7) { dif_punto_camino = punto_camino_jugador - punto_camino_camara; if ((dato_80164688[id_camara] > 0.5) && ((dif_punto_camino * dif_punto_camino) < 5)) {
                funcion_8001A348(id_camara, -1.0f, 2);
            }
        }
    }
alable:
    camara->pos[0] = dato_801645F8[id_camara];
    camara->pos[1] = dato_80164618[id_camara];
    camara->pos[2] = dato_80164638[id_camara];
    camara->mirar_a[0] = jugador->pos[0];
    camara->mirar_a[1] = jugador->pos[1] + 6.0;
    camara->mirar_a[2] = jugador->pos[2];
    funcion_80014D30(id_camara, indice_camino);
    xdiff = camara->mirar_a[0] - camara->pos[0];
    ydiff = camara->mirar_a[1] - camara->pos[1];
    zdiff = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(xdiff, zdiff);
    camara->rot[0] = atan2s(sqrtf((xdiff * xdiff) + (zdiff * zdiff)), ydiff);
    camara->rot[2] = 0;
}

void funcion_80015A9C(s32 id_jugador, f32 parametro1, s32 id_camara, s16 indice_camino) {
    Camara* camara = camaras + id_camara;

    dato_80164688[id_camara] = parametro1;
    punto_camino_mas_cercano_por_id_camara[id_camara] = punto_camino_mas_cercano_por_id_jugador[id_jugador] + 10;
    punto_camino_mas_cercano_por_id_camara[id_camara] = (punto_camino_mas_cercano_por_id_camara[id_camara]) % cantidad_camino_por_indice_camino[indice_camino];

    fijar_posicion_desplazamiento_pista(punto_camino_mas_cercano_por_id_camara[id_camara], parametro1, indice_camino);

    dato_801645F8[id_camara] = posicion_desplazamiento[0];
    dato_80164618[id_camara] = (f32) caminos_pista[indice_camino][punto_camino_mas_cercano_por_id_camara[id_camara]].pos_y;
    dato_80164638[id_camara] = posicion_desplazamiento[2];

    dato_80164648[id_camara] = jugadores[id_jugador].speed / 5.0f;
    if ((f64) dato_80164648[id_camara] < 0.0) {
        dato_80164648[id_camara] = 0.0f;
    }

    camara->pos[0] = dato_801645F8[id_camara];
    camara->pos[1] = dato_80164618[id_camara];
    camara->pos[2] = dato_80164638[id_camara];
}

void funcion_80015C94(Camara* camara, SIN_USO Jugador* jugador_sin_uso, SIN_USO s32 parametro2, s32 id_camara) {
    s16 punto_camino_jugador;
    s16 punto_camino_camara;
    SIN_USO s32 margen_pila_0;
    f32 xdiff2;
    f32 ydiff2;
    f32 zdiff2;
    Jugador* jugador;
    s32 id_jugador;
    f32 medio_x;
    f32 medio_y;
    f32 medio_z;
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    f32 distancia;
    SIN_USO s32 margen_pila_1;
    s16 punto_camino_1;
    s16 punto_camino_2;
    SIN_USO f32 variable_f18;
    SIN_USO f32 variable_f20;
    f32 temporal_f2_2;
    s32 indice_camino;

    id_jugador = camara->id_jugador;
    jugador = jugador_uno;
    jugador += id_jugador;
    dato_80163238 = id_jugador;
    indice_camino = indice_camino_por_id_jugador[id_jugador];
    punto_camino_mas_cercano_por_id_camara[id_camara] =
        funcion_8000D33C(camara->pos[0], camara->pos[1], camara->pos[2], punto_camino_mas_cercano_por_id_camara[id_camara], indice_camino);
    punto_camino_jugador = punto_camino_mas_cercano_por_id_jugador[id_jugador];
    punto_camino_camara = punto_camino_mas_cercano_por_id_camara[id_camara];
    if (es_punto_camino_en_rango(punto_camino_jugador, punto_camino_camara, 0x0032U, 0x000FU, cantidad_camino_por_indice_camino[indice_camino]) <=
        0) {
        funcion_8001A348(id_camara, dato_80164688[id_camara], dato_80164680[id_camara]);
    } else if ((factor_posicion_pista[id_jugador] < -0.5) && (dato_80164688[id_camara] < -0.5)) {
        funcion_8001A348(id_camara, 1.0f, 7);
    } else if ((factor_posicion_pista[id_jugador] > 0.5) && (dato_80164688[id_camara] > 0.5)) {
        funcion_8001A348(id_camara, -1.0f, 6);
    }
    punto_camino_1 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 1) % cantidad_camino_por_indice_camino[indice_camino];
    punto_camino_2 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 2) % cantidad_camino_por_indice_camino[indice_camino];
    fijar_posicion_desplazamiento_pista(punto_camino_1, dato_80164688[id_camara], indice_camino);
    medio_x = posicion_desplazamiento[0] * 0.5;
    medio_z = posicion_desplazamiento[2] * 0.5;
    fijar_posicion_desplazamiento_pista(punto_camino_2, dato_80164688[id_camara], indice_camino);
    medio_x += posicion_desplazamiento[0] * 0.5;
    medio_z += posicion_desplazamiento[2] * 0.5;
    medio_y = (caminos_pista[indice_camino][punto_camino_1].pos_y + caminos_pista[indice_camino][punto_camino_2].pos_y) / 2.0;
    xdiff = medio_x - dato_801645F8[id_camara];
    ydiff = medio_y - dato_80164618[id_camara];
    zdiff = medio_z - dato_80164638[id_camara];
    distancia = sqrtf((xdiff * xdiff) + (ydiff * ydiff) + (zdiff * zdiff));
    if (distancia != 0.0) {
        medio_x = dato_801645F8[id_camara] + ((dato_80164648[id_camara] * xdiff) / distancia);
        medio_y = dato_80164618[id_camara] + ((dato_80164648[id_camara] * ydiff) / distancia);
        medio_z = dato_80164638[id_camara] + ((dato_80164648[id_camara] * zdiff) / distancia);
    } else {
        medio_x = dato_801645F8[id_camara];
        medio_y = dato_80164618[id_camara];
        medio_z = dato_80164638[id_camara];
    }
    camara->pos[0] = medio_x;
    camara->pos[2] = medio_z;
    temporal_f2_2 = obtener_altura_superficie(medio_x, medio_y + 30.0, medio_z);
    if ((temporal_f2_2 < (medio_y - 20.0)) || (temporal_f2_2 >= 3000.0)) {
        camara->pos[1] = medio_y + 10.0;
    } else {
        camara->pos[1] = temporal_f2_2 + 8.0;
    }
    dato_801645F8[id_camara] = medio_x;
    dato_80164618[id_camara] = medio_y;
    dato_80164638[id_camara] = medio_z;
    camara->mirar_a[0] = jugador->pos[0];
    camara->mirar_a[1] = jugador->pos[1] + 6.0;
    camara->mirar_a[2] = jugador->pos[2];
    funcion_80014D30(id_camara, indice_camino);
    xdiff2 = camara->mirar_a[0] - camara->pos[0];
    ydiff2 = camara->mirar_a[1] - camara->pos[1];
    zdiff2 = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(xdiff2, zdiff2);
    camara->rot[0] = atan2s(sqrtf((xdiff2 * xdiff2) + (zdiff2 * zdiff2)), ydiff2);
    camara->rot[2] = 0;
}

void funcion_800162CC(s32 id_jugador, f32 parametro1, s32 id_camara, s16 indice_camino) {
    Camara* camara = camaras + id_camara;

    dato_80164688[id_camara] = parametro1;
    punto_camino_mas_cercano_por_id_camara[id_camara] = punto_camino_mas_cercano_por_id_jugador[id_jugador];
    punto_camino_mas_cercano_por_id_camara[id_camara] = (punto_camino_mas_cercano_por_id_camara[id_camara]) % cantidad_camino_por_indice_camino[indice_camino];

    fijar_posicion_desplazamiento_pista(punto_camino_mas_cercano_por_id_camara[id_camara], parametro1, indice_camino);

    dato_801645F8[id_camara] = posicion_desplazamiento[0];
    dato_80164618[id_camara] = (f32) caminos_pista[indice_camino][punto_camino_mas_cercano_por_id_camara[id_camara]].pos_y;
    dato_80164638[id_camara] = posicion_desplazamiento[2];

    dato_80164658[id_camara] = jugadores[id_jugador].speed;
    dato_80164648[id_camara] = jugadores[id_jugador].speed;

    camara->pos[0] = dato_801645F8[id_camara];
    camara->pos[1] = dato_80164618[id_camara];
    camara->pos[2] = dato_80164638[id_camara];
}

void funcion_80016494(Camara* camara, SIN_USO Jugador* jugador_sin_uso, SIN_USO s32 parametro2, s32 id_camara) {
    s16 punto_camino_camara;
    s16 punto_camino_jugador;
    SIN_USO s32 margen_pila_0;
    f32 xdiff2;
    f32 ydiff2;
    f32 zdiff2;
    Jugador* jugador;
    s32 id_jugador;
    f32 medio_x;
    f32 medio_y;
    f32 medio_z;
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    f32 distancia;
    SIN_USO f32 sp98;
    s16 punto_camino_1;
    s16 punto_camino_2;
    SIN_USO f32 sp94;
    SIN_USO f32 sp90;
    SIN_USO s32 margen_pila_1;
    s32 indice_camino;
    f32 temporal_f2_5;

    id_jugador = camara->id_jugador;
    jugador = jugador_uno;
    dato_80164648[id_camara] += ((dato_80164658[id_camara] - dato_80164648[id_camara]) * 0.5f);
    dato_80163238 = id_jugador;
    indice_camino = indice_camino_por_id_jugador[id_jugador];
    jugador += id_jugador;
    punto_camino_mas_cercano_por_id_camara[id_camara] =
        funcion_8000D33C(camara->pos[0], camara->pos[1], camara->pos[2], punto_camino_mas_cercano_por_id_camara[id_camara], indice_camino);
    temporal_f2_5 = (factor_posicion_pista[id_jugador] - dato_80164688[id_camara]);
    temporal_f2_5 *= temporal_f2_5;
    punto_camino_jugador = punto_camino_mas_cercano_por_id_jugador[id_jugador];
    punto_camino_camara = punto_camino_mas_cercano_por_id_camara[id_camara];
    if (es_punto_camino_en_rango(punto_camino_jugador, punto_camino_camara, 0x000FU, 0x000FU, cantidad_camino_por_indice_camino[indice_camino]) <=
        0) {
        funcion_8001A348(id_camara, dato_80164688[id_camara], dato_80164680[id_camara]);
    } else {
        if ((factor_posicion_pista[id_jugador] < 0.0) && (dato_80164688[id_camara] < 0.0) && (temporal_f2_5 < 0.01)) {
            funcion_8001A348(id_camara, 1.0f, 5);
        } else {
            if ((factor_posicion_pista[id_jugador] > 0.0) && (dato_80164688[id_camara] > 0.0) && (temporal_f2_5 < 0.01)) {
                funcion_8001A348(id_camara, -1.0f, 4);
            } else {
                if ((punto_camino_camara < punto_camino_jugador) && ((punto_camino_jugador - punto_camino_camara) < 0xA)) {
                    dato_80164658[id_camara] = jugadores[id_jugador].speed + 0.4;
                }
                if ((punto_camino_jugador < punto_camino_camara) && ((punto_camino_camara - punto_camino_jugador) < 0xA)) {
                    dato_80164658[id_camara] = jugadores[id_jugador].speed - 0.4;
                }
                if (dato_80164658[id_camara] > 10.0) {
                    dato_80164658[id_camara] = 10.0f;
                }
                if (dato_80164658[id_camara] < 0.0) {
                    dato_80164658[id_camara] = 0.0f;
                }
            }
        }
    }
    punto_camino_1 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 1) % cantidad_camino_por_indice_camino[indice_camino];
    punto_camino_2 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 2) % cantidad_camino_por_indice_camino[indice_camino];
    fijar_posicion_desplazamiento_pista(punto_camino_1, dato_80164688[id_camara], indice_camino);
    medio_x = posicion_desplazamiento[0] * 0.5;
    medio_z = posicion_desplazamiento[2] * 0.5;
    fijar_posicion_desplazamiento_pista(punto_camino_2, dato_80164688[id_camara], indice_camino);
    medio_x += posicion_desplazamiento[0] * 0.5;
    medio_z += posicion_desplazamiento[2] * 0.5;
    medio_y = (caminos_pista[indice_camino][punto_camino_1].pos_y + caminos_pista[indice_camino][punto_camino_2].pos_y) / 2.0;
    xdiff = medio_x - dato_801645F8[id_camara];
    ydiff = medio_y - dato_80164618[id_camara];
    zdiff = medio_z - dato_80164638[id_camara];
    distancia = sqrtf((xdiff * xdiff) + (ydiff * ydiff) + (zdiff * zdiff));
    if (distancia != 0.0) {
        medio_x = dato_801645F8[id_camara] + ((dato_80164648[id_camara] * xdiff) / distancia);
        medio_y = dato_80164618[id_camara] + ((dato_80164648[id_camara] * ydiff) / distancia);
        medio_z = dato_80164638[id_camara] + ((dato_80164648[id_camara] * zdiff) / distancia);
    } else {
        medio_x = dato_801645F8[id_camara];
        medio_y = dato_80164618[id_camara];
        medio_z = dato_80164638[id_camara];
    }
    camara->pos[0] = medio_x;
    camara->pos[2] = medio_z;
    temporal_f2_5 = obtener_altura_superficie(medio_x, medio_y + 30.0, medio_z);
    if ((temporal_f2_5 < (medio_y - 20.0)) || (temporal_f2_5 >= 3000.0)) {
        camara->pos[1] = medio_y + 10.0;
    } else {
        camara->pos[1] = temporal_f2_5 + 10.0;
    }
    dato_801645F8[id_camara] = medio_x;
    dato_80164618[id_camara] = medio_y;
    dato_80164638[id_camara] = medio_z;
    camara->mirar_a[0] = jugador->pos[0];
    camara->mirar_a[1] = jugador->pos[1] + 6.0;
    camara->mirar_a[2] = jugador->pos[2];
    funcion_80014D30(id_camara, indice_camino);
    xdiff2 = camara->mirar_a[0] - camara->pos[0];
    ydiff2 = camara->mirar_a[1] - camara->pos[1];
    zdiff2 = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(xdiff2, zdiff2);
    camara->rot[0] = atan2s(sqrtf((xdiff2 * xdiff2) + (zdiff2 * zdiff2)), ydiff2);
    camara->rot[2] = 0;
}

void funcion_80016C3C(SIN_USO s32 id_jugador, SIN_USO f32 parametro1, s32 id_camara) {
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    f32 temporal_f2;
    SIN_USO s32 margen_pila_2;
    f32 temporal_f12;
    PuntoCaminoPista** path;
    f32 sp54;
    s32 temporal_s0;
    s16 sp48;
    s16 sp44;
    Camara* camara;

    if (int_aleatorio(0x0064U) < 0x32) {
        dato_80164688[id_camara] = 0.1f;
    } else {
        dato_80164688[id_camara] = -0.1f;
    }
    dato_80163DD8[id_camara] = 0;
    if (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) {
        dato_80163DD8[id_camara] = int_aleatorio(4U);
        dato_80164688[id_camara] = 0.0f;
    }
    temporal_s0 = cantidad_camino_por_indice_camino[dato_80163DD8[id_camara]];
    punto_camino_mas_cercano_por_id_camara[id_camara] %= temporal_s0;
    fijar_posicion_desplazamiento_pista(punto_camino_mas_cercano_por_id_camara[id_camara], dato_80164688[id_camara], 0);
    dato_801645F8[id_camara] = posicion_desplazamiento[0];
    dato_80164618[id_camara] = caminos_pista[0][punto_camino_mas_cercano_por_id_camara[id_camara]].pos_y;
    path = caminos_pista;
    dato_80164638[id_camara] = posicion_desplazamiento[2];
    dato_80164658[id_camara] = 16.666666f;
    dato_80164648[id_camara] = 0.0f;
    sp48 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 0xA) % temporal_s0;
    sp44 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 0xB) % temporal_s0;
    fijar_posicion_desplazamiento_pista(sp48, dato_80164688[id_camara], 0);
    temporal_f2 = posicion_desplazamiento[0] * 0.5;
    temporal_f12 = posicion_desplazamiento[2] * 0.5;
    fijar_posicion_desplazamiento_pista(sp44, dato_80164688[id_camara], 0);
    temporal_f2 += posicion_desplazamiento[0] * 0.5;
    temporal_f12 += posicion_desplazamiento[2] * 0.5;
    sp48 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 0x5) % temporal_s0;
    sp44 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 0x6) % temporal_s0;
    sp54 = (path[0][sp48].pos_y + path[0][sp44].pos_y) * 0.5f;
    camara = camaras;
    camara += id_camara;
    camara->mirar_a[0] = temporal_f2;
    camara->mirar_a[2] = temporal_f12;
    camara->mirar_a[1] = sp54 + 8.0;
    camara->pos[0] = dato_801645F8[id_camara];
    camara->pos[1] = dato_80164618[id_camara];
    camara->pos[2] = dato_80164638[id_camara];
}

void funcion_80017054(Camara* camara, SIN_USO Jugador* jugador, SIN_USO s32 index, s32 id_camara);
