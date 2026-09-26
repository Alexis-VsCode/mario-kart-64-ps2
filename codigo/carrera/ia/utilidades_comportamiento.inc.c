void copiar_comportamiento_cpu_circuitos(void) {
    s32 i;
    for (i = 0; i < CIRCUITOS_NUM - 1; i++) {
        comportamiento_cpu_circuitos[i] = obtener_circuito_ai_comportamiento;
    }
}

void reiniciar_ninguno_comportamiento_cpu(s32 indice_jugador) {
    actual_cpu_comportamiento_id[indice_jugador] = 0;
    anterior_cpu_comportamiento_id[indice_jugador] = 0;
    cpu_comportamiento_estado[indice_jugador] = CPU_COMPORTAMIENTO_ESTADO_NINGUNO;
}

void reiniciar_comportamiento_cpu(s32 indice_jugador) {
    actual_cpu_comportamiento_id[indice_jugador] = 0;
    anterior_cpu_comportamiento_id[indice_jugador] = 0;
    cpu_comportamiento_estado[indice_jugador] = CPU_COMPORTAMIENTO_ESTADO_INICIO;
}

void empezar_comportamiento_cpu(s32 id_jugador, Jugador* jugador) {
    u16 punto_camino_jugador;
    s16 inicio_punto_camino;
    s16 fin_punto_camino;
    s32 tipo_comportamiento;
    SIN_USO s32 probar;

    comportamiento_cpu_actual = &comportamiento_cpu_circuitos[id_circuito_actual][actual_cpu_comportamiento_id[id_jugador]];

    punto_camino_jugador = punto_camino_mas_cercano_por_id_jugador[id_jugador];

    inicio_punto_camino = comportamiento_cpu_actual->inicio_punto_camino;
    fin_punto_camino = comportamiento_cpu_actual->fin_punto_camino;
    tipo_comportamiento = comportamiento_cpu_actual->type;

    if ((inicio_punto_camino == -1) && (fin_punto_camino == -1)) {
        comportamiento_cpu_actual = &comportamiento_cpu_circuitos[id_circuito_actual][0];
        reiniciar_ninguno_comportamiento_cpu(id_jugador);
        return;
    }
    if ((u32) punto_camino_jugador == (u32) inicio_punto_camino) {
        cpu_comportamiento_estado[id_jugador] = CPU_COMPORTAMIENTO_ESTADO_EJECUTANDO;
        anterior_cpu_comportamiento_id[id_jugador] = actual_cpu_comportamiento_id[id_jugador];
        actual_cpu_comportamiento_id[id_jugador]++;
        switch (tipo_comportamiento) {
            case COMPORTAMIENTO_1:
                funcion_80011EC0(id_jugador, jugador, jugador->posicion_giro >> 16, punto_camino_jugador);
                break;
            case SALTO_COMPORTAMIENTO:
                salto_kart(jugador);
                jugador->efectos &= ~EFECTO_DERRAPANDO;
                dato_801630E8[id_jugador] = 0;
                break;
            case CENTRO_CONDUCIR_COMPORTAMIENTO:
                jugador_pista_posicion_factor_instruccion[id_jugador].target = 0.0f;
                break;
            case IZQUIERDA_CONDUCIR_COMPORTAMIENTO:
                jugador_pista_posicion_factor_instruccion[id_jugador].target = -0.6f;
                break;
            case EXTERIOR_CONDUCIR_COMPORTAMIENTO:
                jugador_pista_posicion_factor_instruccion[id_jugador].target = 0.6f;
                break;
            case COMPORTAMIENTO_NORMAL_RAPIDEZ:
                comportamiento_cpu_rapidez[id_jugador] = RAPIDEZ_CPU_COMPORTAMIENTO_NORMAL;
                break;
            case COMPORTAMIENTO_RAPIDO_RAPIDEZ:
                comportamiento_cpu_rapidez[id_jugador] = RAPIDEZ_CPU_COMPORTAMIENTO_RAPIDO;
                break;
            case COMPORTAMIENTO_LENTO_RAPIDEZ:
                comportamiento_cpu_rapidez[id_jugador] = RAPIDEZ_CPU_COMPORTAMIENTO_LENTO;
                break;
            case COMPORTAMIENTO_MAX_RAPIDEZ:
                comportamiento_cpu_rapidez[id_jugador] = RAPIDEZ_CPU_COMPORTAMIENTO_MAX;
                break;
            case COMPORTAMIENTO_9:
                dato_801633F8[id_jugador] = 1;
                dato_801631E0[id_jugador] = false;
                jugadores[id_jugador].efectos &= ~EFECTO_CARRERA_PERDIDO;
                break;
            case COMPORTAMIENTO_10:
                dato_801633F8[id_jugador] = 0;
                break;
        }
    }
}

void fin_comportamiento_cpu(s32 indice_jugador, Jugador* jugador) {
    u16 punto_camino_mas_cercano;
    u32 fin_punto_camino;
    s32 tipo_comportamiento;

    comportamiento_cpu_actual = &comportamiento_cpu_circuitos[id_circuito_actual][anterior_cpu_comportamiento_id[indice_jugador]];
    punto_camino_mas_cercano = punto_camino_mas_cercano_por_id_jugador[indice_jugador];
    tipo_comportamiento = comportamiento_cpu_actual->type;
    fin_punto_camino = comportamiento_cpu_actual->fin_punto_camino;
    if (punto_camino_mas_cercano >= fin_punto_camino) {
        switch (tipo_comportamiento) {
            case COMPORTAMIENTO_1:
                jugador->efectos &= ~EFECTO_DERRAPANDO;
                dato_801630E8[indice_jugador] = 0;
                cpu_comportamiento_estado[indice_jugador] = CPU_COMPORTAMIENTO_ESTADO_INICIO;
                break;
            case CENTRO_CONDUCIR_COMPORTAMIENTO:
            case IZQUIERDA_CONDUCIR_COMPORTAMIENTO:
            case EXTERIOR_CONDUCIR_COMPORTAMIENTO:
                jugador_pista_posicion_factor_instruccion[indice_jugador].target =
                    jugador_pista_posicion_factor_instruccion[indice_jugador].desconocido_c;
                cpu_comportamiento_estado[indice_jugador] = CPU_COMPORTAMIENTO_ESTADO_INICIO;
                break;
            case SALTO_COMPORTAMIENTO:
            case COMPORTAMIENTO_NORMAL_RAPIDEZ:
            case COMPORTAMIENTO_RAPIDO_RAPIDEZ:
            case COMPORTAMIENTO_LENTO_RAPIDEZ:
            case COMPORTAMIENTO_9:
            case COMPORTAMIENTO_10:
            case COMPORTAMIENTO_MAX_RAPIDEZ:
                cpu_comportamiento_estado[indice_jugador] = CPU_COMPORTAMIENTO_ESTADO_INICIO;
                break;
            default:
                break;
        }
    }
}

void comportamiento_cpu(s32 indice_jugador) {
    Jugador* jugador = jugador_uno + indice_jugador;

    switch (cpu_comportamiento_estado[indice_jugador]) {
        case CPU_COMPORTAMIENTO_ESTADO_NINGUNO:
            break;
        case CPU_COMPORTAMIENTO_ESTADO_INICIO:
            empezar_comportamiento_cpu(indice_jugador, jugador);
            break;
        case CPU_COMPORTAMIENTO_ESTADO_EJECUTANDO:
            fin_comportamiento_cpu(indice_jugador, jugador);
            break;
    }
}

void funcion_80011EC0(s32 indice_jugador, Jugador* jugador, s32 parametro2, SIN_USO u16 parametro3) {
    if ((((jugador->speed / 18.0f) * 216.0f) >= 45.0f) && (dato_801630E8[indice_jugador] == 0)) {
        switch (actual_pista_seccion_tipos_camino[algun_punto_camino_mas_cercano]) {
            case CURVA_INCLINADO_DERECHA:
            case CURVA_DERECHA:
                if ((parametro2 >= -9) && (dato_80162FF8[indice_jugador] == 0)) {
                    if ((factor_posicion_pista[indice_jugador] > -0.8) && (factor_posicion_pista[indice_jugador] < 0.5)) {
                        salto_kart(jugador);
                        jugador->efectos |= EFECTO_DERRAPANDO;
                        dato_801630E8[indice_jugador] = 1;
                        break;
                    }
                }
                dato_801630E8[indice_jugador] = 2;
                break;
            case CURVA_INCLINADO_IZQUIERDA:
            case CURVA_IZQUIERDA:
                if ((parametro2 < 0xA) && (dato_80162FF8[indice_jugador] == 0)) {
                    if ((factor_posicion_pista[indice_jugador] > -0.5) && (factor_posicion_pista[indice_jugador] < 0.8)) {
                        salto_kart(jugador);
                        jugador->efectos |= EFECTO_DERRAPANDO;
                        dato_801630E8[indice_jugador] = -1;
                        break;
                    }
                }
                dato_801630E8[indice_jugador] = -2;
                break;
        }
    } else {
        dato_801630E8[indice_jugador] = 3;
    }
}
