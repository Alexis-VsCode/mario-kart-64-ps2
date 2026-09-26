// Aparecer jugadores

f32 dato_80165210[8];
f32 dato_80165230[8];
SIN_USO f32 dato_80165250[8];
s16 dato_80165270[8];
f32 jugador_actual_rapidez[8];
f32 dato_801652A0[8];
s32 dato_801652C0[8];
s32 dato_801652E0[8];
s16 dato_80165300[8];
u16 indice_camino_copia_por_id_jugador[8];
s16 copia_mas_cercano_camino_punto_por_id_jugador[8];
s16 dato_80165330[8];
s16 dato_80165340;
SIN_USO s32 dato_80165348[29];
Jugador* dato_801653C0[8];

bool jugador_es_acelerador_activo[8];
s32 dato_80165400[8];
s32 frame_desde_ultimo_combo_a[8];
s32 interruptor_cantidad_a[8];
bool es_jugador_triple_a_boton_combo[8];
s32 temporizador_impulso_triple_a_combo[8];

bool jugador_es_freno_activo[8];
s32 dato_801654C0[8];
s32 frame_desde_ultimo_combo_b[8];
s32 cambio_cantidad_b[8];
bool es_jugador_triple_b_boton_combo[8];
s32 temporizador_impulso_triple_b_combo[8];

s16 cpu_elegir_personajes[7];

s16 dato_8016556E;
s16 dato_80165570;
s16 dato_80165572;
s16 dato_80165574;
s16 dato_80165576;
s16 dato_80165578;
s16 dato_8016557A;
s16 dato_8016557C;
s16 dato_8016557E;
s16 dato_80165580;
s16 dato_80165582;

void aparecer_jugador(Jugador* jugador, s8 indice_jugador, f32 renglon_inicial, f32 columna_inicial, f32 parametro4, f32 parametro5,
                  u16 id_personaje, s16 tipo_jugador) {
    f32 devuelto;
    s8 idx;

    jugador->type = INACTIVO_JUGADOR;
    jugador->desconocido_08C = 0;
    jugador->id_personaje = id_personaje;
    jugador->graficos_kart = 0;
    jugador->friccion_kart = tabla_friccion_kart[jugador->id_personaje];
    jugador->tamanio_caja_envolvente = kart_envolvente_caja_tamanio_tabla[jugador->id_personaje];
    jugador->gravedad_kart = tabla_gravedad_kart[jugador->id_personaje];

    switch (seleccion_modo) {
        case GRAN_PREMIO:
        case VERSUS:
            jugador->desconocido_084 = dato_800E2400[seleccion_cc][jugador->id_personaje];
            jugador->desconocido_088 = dato_800E24B4[seleccion_cc][jugador->id_personaje];
            jugador->desconocido_210 = dato_800E2568[seleccion_cc][jugador->id_personaje];
            jugador->arriba_rapidez = tabla_rapidez_arriba[seleccion_cc][jugador->id_personaje];
            break;

        case CONTRARRELOJ:
            jugador->desconocido_084 = dato_800E2400[CC_100][jugador->id_personaje];
            jugador->desconocido_088 = dato_800E24B4[CC_100][jugador->id_personaje];
            jugador->desconocido_210 = dato_800E2568[CC_100][jugador->id_personaje];
            jugador->arriba_rapidez = tabla_rapidez_arriba[CC_100][jugador->id_personaje];
            break;

        case BATALLA:
            jugador->desconocido_084 = dato_800E2400[BATALLA_CC][jugador->id_personaje];
            jugador->desconocido_088 = dato_800E24B4[BATALLA_CC][jugador->id_personaje];
            jugador->desconocido_210 = dato_800E2568[BATALLA_CC][jugador->id_personaje];
            jugador->arriba_rapidez = tabla_rapidez_arriba[BATALLA_CC][jugador->id_personaje];
            break;
    }

    jugador->pos[0] = renglon_inicial;
    devuelto = obtener_altura_superficie(renglon_inicial, parametro4 + 50.0f, columna_inicial) + jugador->tamanio_caja_envolvente;
    jugador->pos[2] = columna_inicial;
    jugador->pos[1] = devuelto;
    jugador->pos_viejo[0] = renglon_inicial;
    jugador->pos_viejo[1] = devuelto;

    camino_y_jugador[indice_jugador] = devuelto;

    jugador->rotacion[0] = 0;
    jugador->pos_viejo[2] = columna_inicial;
    jugador->desconocido_05C = 1.0f;
    jugador->desconocido_058 = 0.0f;
    jugador->desconocido_060 = 0.0f;
    jugador->velocidad[0] = 0.0f;
    jugador->velocidad[1] = 0.0f;
    jugador->velocidad[2] = 0.0f;
    jugador->rotacion[1] = parametro5;
    jugador->rotacion[2] = 0;
    jugador->delta_posicion_giro = 0;
    jugador->desconocido_002 = 0;

    jugador->efectos = 0;
    jugador->desconocido_0C0 = 0;
    jugador->posicion_giro = 0;
    jugador->desconocido_07A = 0;
    jugador->desconocido_006 = 0;
    jugador->cantidad_vuelta = -1;
    jugador->desconocido_08C = 0.0f;
    jugador->desconocido_090 = 0.0f;
    jugador->speed = 0.0f;
    jugador->desconocido_074 = 0.0f;
    jugador->type = tipo_jugador;
    jugador->lakitu_props = 0;
    jugador->oob_props = 0;
    jugador->desconocido_10C = 0;
    jugador->desconocido_0E2 = 0;
    jugador->desconocido_0E8 = 0.0f;
    jugador->desconocido_0A0 = 0.0f;
    jugador->desconocido_104 = 0.0f;
    jugador->actual_rapidez = 0.0f;
    jugador->desconocido_20C = 0.0f;
    jugador->desconocido_dac = 0.0f;
    jugador->kart_props = 0;
    jugador->desconocido_046 = 0;
    jugador->disparadores = 0;
    jugador->alpha = ALPHA_MAX;

    jugador->desconocido_206 = 0;
    jugador->acel_pendiente = 0;
    jugador->desconocido_D98 = 0;
    jugador->desconocido_D9A = 0;
    jugador->desconocido_DA4 = 0;
    jugador->desconocido_DA6 = 0;
    jugador->desconocido_DB4.desconocido0 = 0;
    jugador->desconocido_DB4.desconocido2 = 0;
    jugador->desconocido_DB4.unk18 = 0;
    jugador->desconocido_DB4.desconocido_1a = 0;
    jugador->desconocido_DB4.desconocido_1c = 0;
    jugador->desconocido_DB4.desconocido_1e = 0;
    jugador->desconocido_DB4.unk20 = 0;

    jugador->desconocido_042 = 0;
    jugador->desconocido_078 = 0;
    jugador->desconocido_0A8 = 0;
    jugador->desconocido_0AA = 0;
    jugador->sentido_esquivar = 0;
    jugador->desconocido_0AE = 0;
    jugador->desconocido_0B0 = 0;
    jugador->desconocido_0B2 = 0;
    jugador->temporizador_esquivar = 0;
    jugador->desconocido_0C0 = 0;
    jugador->desconocido_0C2 = 0;
    jugador->desconocido_0C8 = 0;
    jugador->lakitu_props = 0;
    jugador->temporizador_impulso = 0;
    jugador->oob_props = 0;
    jugador->desconocido_0E0 = 0;
    jugador->desconocido_0E2 = 0;
    jugador->desconocido_10C = 0;
    jugador->incrementar_cambio_giro = 0;
    jugador->duracion_derrape = 0;
    jugador->mas_cercano_camino_punto_id = 0;
    jugador->contador_estado_derrape = 0;
    jugador->estado_derrape = 0;
    jugador->desconocido_234 = 0;
    jugador->desconocido_236 = 0;
    jugador->desconocido_238 = 0;
    jugador->desconocido_23A = 0;
    jugador->rueda_rapidez = 0;
    jugador->desconocido_256 = 0;

    jugador->size = 1.0f;
    jugador->desconocido_dac = 1.0f;

    jugador->desconocido_064[0] = 0.0f;
    jugador->desconocido_064[1] = 0.0f;
    jugador->desconocido_064[2] = 0.0f;
    jugador->potencia_impulso = 0.0f;
    jugador->desconocido_D9C = 0.0f;
    jugador->desconocido_DA0 = 0.0f;
    jugador->desconocido_DA8 = 0.0f;
    jugador->desconocido_DB0 = 0.0f;
    jugador->desconocido_DB4.desconocido4 = 0.0f;
    jugador->desconocido_DB4.desconocido8 = 0.0f;
    jugador->desconocido_DB4.desconocido_c = 0.0f;
    jugador->desconocido_DB4.unk10 = 0.0f;
    jugador->desconocido_DB4.unk14 = 0.0f;
    jugador->desconocido_084 = 0.0f;
    jugador->desconocido_088 = 0.0f;
    jugador->desconocido_08C = 0.0f;
    jugador->desconocido_090 = 0.0f;
    jugador->speed = 0.0f;
    jugador->desconocido_098 = 0.0f;
    jugador->actual_rapidez = 0.0f;
    jugador->desconocido_0A0 = 0.0f;
    jugador->desconocido_0A4 = 0.0f;
    jugador->inicializacion_acel_esquivar = 0.0f;
    jugador->desconocido_0E4 = 0.0f;
    jugador->desconocido_0E8 = 0.0f;
    jugador->velocidad_salto_kart = 0.0f;
    jugador->tiron_salto_kart = 0.0f;
    jugador->aceleracion_salto_kart = 0.0f;
    jugador->desconocido_104 = 0.0f;
    jugador->desconocido_108 = 0.0f;
    jugador->desconocido_1F8 = 0.0f;
    jugador->desconocido_1FC = 0.0f;
    jugador->desconocido_208 = 0.0f;
    jugador->desconocido_20C = 0.0f;
    jugador->desconocido_210 = 0.0f;
    jugador->desconocido_218 = 0.0f;
    jugador->desconocido_21C = 0.0f;
    jugador->anterior_rapidez = 0.0f;
    jugador->desconocido_230 = 0.0f;
    jugador->desconocido_23C = 0.0f;

    idx = indice_jugador;

    ultimo_selector_frame_anim[0][idx] = 0;
    ultimo_selector_frame_anim[1][idx] = 0;
    ultimo_selector_frame_anim[2][idx] = 0;
    ultimo_selector_frame_anim[3][idx] = 0;
    ultimo_selector_grupo_anim[0][idx] = 0;
    ultimo_selector_grupo_anim[1][idx] = 0;
    ultimo_selector_grupo_anim[2][idx] = 0;
    ultimo_selector_grupo_anim[3][idx] = 0;
    dato_80165190[0][idx] = 0;
    dato_80165190[1][idx] = 0;
    dato_80165190[2][idx] = 0;
    dato_80165190[3][idx] = 0;
    dato_801651D0[0][idx] = 0;
    dato_801651D0[1][idx] = 0;
    dato_801651D0[2][idx] = 0;
    dato_801651D0[3][idx] = 0;

    frame_desde_ultimo_combo_a[idx] = 0;
    interruptor_cantidad_a[idx] = 0;
    es_jugador_triple_a_boton_combo[idx] = false;
    temporizador_impulso_triple_a_combo[idx] = 0;
    frame_desde_ultimo_combo_b[idx] = 0;
    cambio_cantidad_b[idx] = 0;
    es_jugador_triple_b_boton_combo[idx] = false;
    temporizador_impulso_triple_b_combo[indice_jugador] = 0;
    dato_8018D900[0] = 0;

    dato_801652E0[indice_jugador] = 0;
    dato_801652C0[indice_jugador] = 0;
    dato_80165020[indice_jugador] = 0;
    velocidad_ultimo_jugador[indice_jugador][0] = 0.0f;
    velocidad_ultimo_jugador[indice_jugador][1] = 0.0f;
    velocidad_ultimo_jugador[indice_jugador][2] = 0.0f;
    jugador_actual_rapidez[indice_jugador] = 0.0f;
    dato_801652A0[indice_jugador] = 0.0f;
    jugador_es_acelerador_activo[indice_jugador] = 0;
    dato_80165400[indice_jugador] = 0;
    jugador_es_freno_activo[indice_jugador] = 0;
    dato_801654C0[indice_jugador] = 0;
    dato_80165340 = 0;

    jugador->ruedas[IZQUIERDA_FRENTE].tipo_superficie = 0;
    jugador->ruedas[DERECHA_FRENTE].tipo_superficie = 0;
    jugador->ruedas[IZQUIERDA_ATRAS].tipo_superficie = 0;
    jugador->ruedas[DERECHA_ATRAS].tipo_superficie = 0;

    jugador->ruedas[IZQUIERDA_FRENTE].banderas_superficie = 0;
    jugador->ruedas[DERECHA_FRENTE].banderas_superficie = 0;
    jugador->ruedas[IZQUIERDA_ATRAS].banderas_superficie = 0;
    jugador->ruedas[DERECHA_ATRAS].banderas_superficie = 0;

    jugador->ruedas[IZQUIERDA_FRENTE].indice_malla_colision = 0;
    jugador->ruedas[DERECHA_FRENTE].indice_malla_colision = 0;
    jugador->ruedas[IZQUIERDA_ATRAS].indice_malla_colision = 0;
    jugador->ruedas[DERECHA_ATRAS].indice_malla_colision = 0;

    jugador->ruedas[DERECHA_FRENTE].desconocido_14 = 0;
    jugador->ruedas[IZQUIERDA_FRENTE].desconocido_14 = 0;
    jugador->ruedas[IZQUIERDA_ATRAS].desconocido_14 = 0;
    jugador->ruedas[DERECHA_ATRAS].desconocido_14 = 0;

    jugador->colision.desconocido30 = 0;
    jugador->colision.desconocido32 = 0;
    jugador->colision.unk34 = 0;
    jugador->colision.indice_yx_malla = 0;
    jugador->colision.indice_zy_malla = 0;
    jugador->colision.indice_zx_malla = 0;

    jugador->ruedas[IZQUIERDA_FRENTE].pos[0] = 0.0f;
    jugador->ruedas[IZQUIERDA_FRENTE].pos[1] = 0.0f;
    jugador->ruedas[IZQUIERDA_FRENTE].pos[2] = 0.0f;

    jugador->ruedas[DERECHA_FRENTE].pos[0] = 0.0f;
    jugador->ruedas[DERECHA_FRENTE].pos[1] = 0.0f;
    jugador->ruedas[DERECHA_FRENTE].pos[2] = 0.0f;

    jugador->ruedas[IZQUIERDA_ATRAS].pos[0] = 0.0f;
    jugador->ruedas[IZQUIERDA_ATRAS].pos[1] = 0.0f;
    jugador->ruedas[IZQUIERDA_ATRAS].pos[2] = 0.0f;

    jugador->ruedas[DERECHA_ATRAS].pos[0] = 0.0f;
    jugador->ruedas[DERECHA_ATRAS].pos[1] = 0.0f;
    jugador->ruedas[DERECHA_ATRAS].pos[2] = 0.0f;

    jugador->ruedas[IZQUIERDA_FRENTE].altura_base = 0.0f;
    jugador->ruedas[DERECHA_FRENTE].altura_base = 0.0f;
    jugador->ruedas[IZQUIERDA_ATRAS].altura_base = 0.0f;
    jugador->ruedas[DERECHA_ATRAS].altura_base = 0.0f;

    jugador->colision.distancia_superficie[0] = 0.0f;
    jugador->colision.distancia_superficie[1] = 0.0f;
    jugador->colision.distancia_superficie[2] = 0.0f;
    jugador->colision.desconocido48[0] = 0.0f;
    jugador->colision.desconocido48[1] = 0.0f;
    jugador->colision.desconocido48[2] = 0.0f;
    jugador->colision.desconocido54[0] = 0.0f;
    jugador->colision.desconocido54[1] = 0.0f;
    jugador->colision.desconocido54[2] = 0.0f;
    jugador->colision.vector_orientacion[0] = 0.0f;
    jugador->colision.vector_orientacion[1] = 0.0f;
    jugador->colision.vector_orientacion[2] = 0.0f;

    dato_80165300[indice_jugador] = 0;
    dato_8018CE10[indice_jugador].desconocido_04[0] = 0.0f;
    dato_8018CE10[indice_jugador].desconocido_04[2] = 0.0f;
    funcion_80295BF8(indice_jugador);
    reiniciar_pool_particula_jugador(jugador);
    borrar_todos_globos_jugador(jugador, indice_jugador);
    if (seleccion_modo == BATALLA) {
        inicializar_todos_globos_jugador(jugador, indice_jugador);
    }
    calcular_matriz_orientacion(jugador->desconocido_150, jugador->desconocido_058, jugador->desconocido_05C, jugador->desconocido_060,
                                 jugador->rotacion[1]);
    calcular_matriz_orientacion(jugador->matriz_orientacion, jugador->desconocido_058, jugador->desconocido_05C, jugador->desconocido_060,
                                 jugador->rotacion[1]);
}

void funcion_80039AE4(void) {
    switch (modo_pantalla_activo) {
        case MODO_PANTALLA_1P:
            if (estado_juego == FINAL) {
                dato_80165578 = 0x898;
                dato_8016557A = 0;
                dato_8016557C = 0x384;
                dato_8016557E = 0;
                dato_80165574 = 0x384;
                dato_80165576 = 0;
                dato_80165570 = 0x35C;
                dato_80165572 = 0;
                dato_80165580 = 0x1F4;
                dato_80165582 = 0;
            } else {
                dato_80165578 = 0x4B0;
                dato_8016557A = -0xA;
                dato_8016557C = 0x384;
                dato_8016557E = 0x32;
                dato_80165574 = 0x1F4;
                dato_80165576 = 0;
                dato_80165570 = 0x15E;
                dato_80165572 = 0;
                dato_80165580 = 0xFA;
                dato_80165582 = 0;
            }
            break;

        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            if (seleccion_modo == BATALLA) {
                dato_80165578 = 0x898;
                dato_8016557A = 0;
                dato_8016557C = 0x320;
                dato_8016557E = 0;
                dato_80165574 = 0x190;
                dato_80165576 = 0;
                dato_80165570 = 0xC8;
                dato_80165572 = 0;
                dato_80165580 = 0xC8;
                dato_80165582 = 0;
            } else {
                dato_80165578 = 0x4B0;
                dato_8016557A = 0x32;
                dato_8016557C = 0x320;
                dato_8016557E = 0x32;
                dato_80165574 = 0x190;
                dato_80165576 = 0;
                dato_80165570 = 0x96;
                dato_80165572 = 0;
                dato_80165580 = 0x96;
                dato_80165582 = 0;
            }
            break;

        default:
            if (seleccion_modo == BATALLA) {
                dato_80165578 = 0x898;
                dato_8016557A = 0;
                dato_8016557C = 0x320;
                dato_8016557E = 0;
                dato_80165574 = 0x190;
                dato_80165576 = 0;
                dato_80165570 = 0xC8;
                dato_80165572 = 0;
                dato_80165580 = 0xC8;
                dato_80165582 = 0;
            } else {
                dato_80165578 = 0x3E8;
                dato_8016557A = 0;
                dato_8016557C = 0x258;
                dato_8016557E = 0;
                dato_80165574 = 0x15E;
                dato_80165576 = 0;
                dato_80165570 = 0x96;
                dato_80165572 = 0;
                dato_80165580 = 0x96;
                dato_80165582 = 0;
            }
            break;
    }
}

void funcion_80039DA4(void) {
    s32 i;

    s32 sp2_c[] = {
        7, 6, 5, 4, 3, 2, 1, 0,
    };

    s32 sp_c[] = {
        0, 1, 2, 3, 4, 5, 6, 7,
    };

    if (((indice_circuito_en_copa == CIRCUITO_UNO) && (dato_8016556E == 0)) || (modo_demo == 1) ||
        (seleccion_menu_depuracion == DEPURACION_MENU_OPCION_SELECCIONADO)) {
        for (i = 0; i < JUGADORES_NUM; i++) {
            dato_80165270[i] = sp2_c[i];
        }
    } else {
        for (i = 0; i < JUGADORES_NUM; i++) {
            dato_80165270[i] = sp_c[gp_actual_carrera_puesto_por_id_jugador[i]];
        }
    }
}

SIN_USO f32 dato_800E43A0 = 1.0f;
SIN_USO s16 dato_800E43A4 = 1;
SIN_USO s16 dato_800E43A8 = 0;

void aparecer_jugador_gp_uno_jugadores(f32* parametro0, f32* parametro1, f32 parametro2) {
    funcion_80039DA4();
    if (((indice_circuito_en_copa == CIRCUITO_UNO) && (dato_8016556E == 0)) || (modo_demo == 1) ||
        (seleccion_menu_depuracion == DEPURACION_MENU_OPCION_SELECCIONADO)) {
        s16 rand;
        s16 i;

        do {
            rand = int_aleatorio(7);
        } while (rand == selecciones_personaje[0]);

        cpu_elegir_personajes[0] = rand;

        for (i = 1; i < 7; i++) {
            u16* arr = (u16*) cpu_para_jugador[selecciones_personaje[0]];
            if (rand == arr[i]) {
                cpu_elegir_personajes[i] = arr[0];
            } else {
                cpu_elegir_personajes[i] = arr[i];
            }
        }
    }

    dato_8016556E = 0;
    if (modo_demo == 1) {
        aparecer_jugador(copia_jugador_uno, 0, parametro0[dato_80165270[0]], parametro1[dato_80165270[0]], parametro2, 32768.0f,
                     selecciones_personaje[0], HUMANO_JUGADOR_Y_CPU);
        aparecer_jugador(jugador_dos, 1, parametro0[dato_80165270[1]], parametro1[dato_80165270[1]], parametro2, 32768.0f, cpu_elegir_personajes[0],
                     EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
        aparecer_jugador(jugador_tres, 2, parametro0[dato_80165270[2]], parametro1[dato_80165270[2]], parametro2, 32768.0f, cpu_elegir_personajes[1],
                     EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
        aparecer_jugador(jugador_cuatro, 3, parametro0[dato_80165270[3]], parametro1[dato_80165270[3]], parametro2, 32768.0f, cpu_elegir_personajes[2],
                     EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
        aparecer_jugador(jugador_cinco, 4, parametro0[dato_80165270[4]], parametro1[dato_80165270[4]], parametro2, 32768.0f, cpu_elegir_personajes[3],
                     EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
        aparecer_jugador(jugador_seis, 5, parametro0[dato_80165270[5]], parametro1[dato_80165270[5]], parametro2, 32768.0f, cpu_elegir_personajes[4],
                     EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
        aparecer_jugador(jugador_siete, 6, parametro0[dato_80165270[6]], parametro1[dato_80165270[6]], parametro2, 32768.0f, cpu_elegir_personajes[5],
                     EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
        aparecer_jugador(jugador_ocho, 7, parametro0[dato_80165270[7]], parametro1[dato_80165270[7]], parametro2, 32768.0f, cpu_elegir_personajes[6],
                     EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
        dato_80164A28 = 0;
    } else {
        aparecer_jugador(copia_jugador_uno, 0, parametro0[dato_80165270[0]], parametro1[dato_80165270[0]] + 250.0f, parametro2, 32768.0f,
                     selecciones_personaje[0], EXISTE_JUGADOR | PREPARACION_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_dos, 1, parametro0[dato_80165270[1]], parametro1[dato_80165270[1]] + 250.0f, parametro2, 32768.0f,
                     cpu_elegir_personajes[0], EXISTE_JUGADOR | PREPARACION_JUGADOR | SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        aparecer_jugador(jugador_tres, 2, parametro0[dato_80165270[3]], parametro1[dato_80165270[2]] + 250.0f, parametro2, 32768.0f,
                     cpu_elegir_personajes[1], EXISTE_JUGADOR | PREPARACION_JUGADOR | SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        aparecer_jugador(jugador_cuatro, 3, parametro0[dato_80165270[2]], parametro1[dato_80165270[3]] + 250.0f, parametro2, 32768.0f,
                     cpu_elegir_personajes[2], EXISTE_JUGADOR | PREPARACION_JUGADOR | SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        aparecer_jugador(jugador_cinco, 4, parametro0[dato_80165270[5]], parametro1[dato_80165270[4]] + 250.0f, parametro2, 32768.0f,
                     cpu_elegir_personajes[3], EXISTE_JUGADOR | PREPARACION_JUGADOR | SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        aparecer_jugador(jugador_seis, 5, parametro0[dato_80165270[4]], parametro1[dato_80165270[5]] + 250.0f, parametro2, 32768.0f,
                     cpu_elegir_personajes[4], EXISTE_JUGADOR | PREPARACION_JUGADOR | SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        aparecer_jugador(jugador_siete, 6, parametro0[dato_80165270[7]], parametro1[dato_80165270[6]] + 250.0f, parametro2, 32768.0f,
                     cpu_elegir_personajes[5], EXISTE_JUGADOR | PREPARACION_JUGADOR | SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        aparecer_jugador(jugador_ocho, 7, parametro0[dato_80165270[6]], parametro1[dato_80165270[7]] + 250.0f, parametro2, 32768.0f,
                     cpu_elegir_personajes[6], EXISTE_JUGADOR | PREPARACION_JUGADOR | SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        dato_80164A28 = 1;
    }
    funcion_80039AE4();
}

void aparecer_jugadores_versus_un_jugador(f32* parametro0, f32* parametro1, f32 parametro2) {
    aparecer_jugador(jugador_cuatro, 3, parametro0[2], parametro1[2], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_cinco, 4, parametro0[3], parametro1[3], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_seis, 5, parametro0[4], parametro1[4], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_siete, 6, parametro0[5], parametro1[5], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_ocho, 7, parametro0[6], parametro1[6], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    if (modo_demo == 1) {
        aparecer_jugador(copia_jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                     HUMANO_JUGADOR_Y_CPU);
        aparecer_jugador(jugador_dos, 1, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                     SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        aparecer_jugador(jugador_tres, 2, parametro0[1], parametro1[1], parametro2, 32768.0f, selecciones_personaje[0],
                     SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    } else if (dato_8015F890 != 1) {
        aparecer_jugador(copia_jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        if (b_jugador_fantasma_desactivado == 0) {
            aparecer_jugador(jugador_dos, 1, parametro0[0], parametro1[0], parametro2, 32768.0f, dato_80162DE0,
                         EXISTE_JUGADOR | HUMANO_JUGADOR | SECUENCIA_INICIO_JUGADOR | INVISIBLE_JUGADOR_O_BOMBA);
        } else {
            aparecer_jugador(jugador_dos, 1, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                         SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        }
        if (b_circuito_fantasma_desactivado == 0) {
            aparecer_jugador(jugador_tres, 2, parametro0[0], parametro1[0], parametro2, 32768.0f, dato_80162DE4,
                         EXISTE_JUGADOR | HUMANO_JUGADOR | SECUENCIA_INICIO_JUGADOR | INVISIBLE_JUGADOR_O_BOMBA);
        } else {
            aparecer_jugador(jugador_tres, 2, parametro0[1], parametro1[1], parametro2, 32768.0f, selecciones_personaje[0],
                         SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        }
    } else {
        aparecer_jugador(copia_jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, dato_80162DE8,
                     EXISTE_JUGADOR | HUMANO_JUGADOR | SECUENCIA_INICIO_JUGADOR | INVISIBLE_JUGADOR_O_BOMBA);
        if (dato_80162DD8 == 0) {
            aparecer_jugador(jugador_dos, 1, parametro0[0], parametro1[0], parametro2, 32768.0f, dato_80162DE0,
                         EXISTE_JUGADOR | HUMANO_JUGADOR | SECUENCIA_INICIO_JUGADOR | INVISIBLE_JUGADOR_O_BOMBA);
        } else {
            aparecer_jugador(jugador_dos, 1, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                         SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        }
        if (b_circuito_fantasma_desactivado == 0) {
            aparecer_jugador(jugador_tres, 2, parametro0[0], parametro1[0], parametro2, 32768.0f, dato_80162DE4,
                         EXISTE_JUGADOR | HUMANO_JUGADOR | SECUENCIA_INICIO_JUGADOR | INVISIBLE_JUGADOR_O_BOMBA);
        } else {
            aparecer_jugador(jugador_tres, 2, parametro0[1], parametro1[1], parametro2, 32768.0f, selecciones_personaje[0],
                         SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
        }
    }
    dato_80164A28 = 0;
    funcion_80039AE4();
}

void aparecer_jugador_gp_dos_jugadores(f32* parametro0, f32* parametro1, f32 parametro2) {
    funcion_80039DA4();
    if ((indice_circuito_en_copa == CIRCUITO_UNO) || (modo_demo == 1) || (seleccion_menu_depuracion == DEPURACION_MENU_OPCION_SELECCIONADO)) {
        s16 rand;
        s16 i;

    obtener_azar:
        rand = int_aleatorio(7);
        if (selecciones_personaje[0] == rand) {
            goto obtener_azar;
        }
        if (selecciones_personaje[1] == rand) {
            goto obtener_azar;
        }

        cpu_elegir_personajes[0] = rand;

        for (i = 1; i < 6; i++) {
            u16* arr = (u16*) cpu_para_dos_jugador[selecciones_personaje[0]][selecciones_personaje[1]];
            if (rand == arr[i]) {
                cpu_elegir_personajes[i] = arr[0];
            } else {
                cpu_elegir_personajes[i] = arr[i];
            }
        }
    }

    aparecer_jugador(jugador_tres, 2, parametro0[dato_80165270[2]], parametro1[dato_80165270[2]], parametro2, 32768.0f, cpu_elegir_personajes[0],
                 EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    aparecer_jugador(jugador_cuatro, 3, parametro0[dato_80165270[3]], parametro1[dato_80165270[3]], parametro2, 32768.0f, cpu_elegir_personajes[1],
                 EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    aparecer_jugador(jugador_cinco, 4, parametro0[dato_80165270[4]], parametro1[dato_80165270[4]], parametro2, 32768.0f, cpu_elegir_personajes[2],
                 EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    aparecer_jugador(jugador_seis, 5, parametro0[dato_80165270[5]], parametro1[dato_80165270[5]], parametro2, 32768.0f, cpu_elegir_personajes[3],
                 EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    aparecer_jugador(jugador_siete, 6, parametro0[dato_80165270[6]], parametro1[dato_80165270[6]], parametro2, 32768.0f, cpu_elegir_personajes[4],
                 EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    aparecer_jugador(jugador_ocho, 7, parametro0[dato_80165270[7]], parametro1[dato_80165270[7]], parametro2, 32768.0f, cpu_elegir_personajes[5],
                 EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);

    if (modo_demo == 1) {
        aparecer_jugador(copia_jugador_uno, 0, parametro0[dato_80165270[0]], parametro1[dato_80165270[0]], parametro2, 32768.0f,
                     selecciones_personaje[0], HUMANO_JUGADOR_Y_CPU);
    } else {
        aparecer_jugador(copia_jugador_uno, 0, parametro0[dato_80165270[0]], parametro1[dato_80165270[0]], parametro2, 32768.0f,
                     selecciones_personaje[0], EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    }
    if (modo_demo == 1) {
        aparecer_jugador(jugador_dos, 1, parametro0[dato_80165270[1]], parametro1[dato_80165270[1]], parametro2, 32768.0f, selecciones_personaje[1],
                     EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    } else {
        aparecer_jugador(jugador_dos, 1, parametro0[dato_80165270[1]], parametro1[dato_80165270[1]], parametro2, 32768.0f, selecciones_personaje[1],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    }

    dato_80164A28 = 0;
    funcion_80039AE4();
}

void aparecer_jugadores_versus_dos_jugador(f32* parametro0, f32* parametro1, f32 parametro2) {
    aparecer_jugador(jugador_tres, 2, parametro0[1], parametro1[1], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_cuatro, 3, parametro0[2], parametro1[2], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_cinco, 4, parametro0[3], parametro1[3], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_seis, 5, parametro0[4], parametro1[4], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_siete, 6, parametro0[5], parametro1[5], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_ocho, 7, parametro0[6], parametro1[6], parametro2, 32768.0f, selecciones_personaje[0],
                 SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    if (modo_demo == 1) {
        aparecer_jugador(copia_jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                     HUMANO_JUGADOR_Y_CPU);
    } else {
        aparecer_jugador(copia_jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    }
    if (modo_demo == 1) {
        aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 32768.0f, selecciones_personaje[1], HUMANO_JUGADOR_Y_CPU);
    } else {
        aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 32768.0f, selecciones_personaje[1],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    }
    dato_80164A28 = 0;
    funcion_80039AE4();
}

void aparecer_batalla_jugadores_2j(f32* parametro0, f32* parametro1, f32 parametro2) {
    if (id_circuito_actual == CIRCUITO_BIG_DONUT) {
        aparecer_jugador(jugador_uno, 0, parametro0[0], parametro1[0], parametro2, -16384.0f, selecciones_personaje[0],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 16384.0f, selecciones_personaje[1],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    } else {
        aparecer_jugador(jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 0.0f, selecciones_personaje[1],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    }
    aparecer_jugador(jugador_tres, 2, parametro0[2], parametro1[2], parametro2, 32768.0f, selecciones_personaje[2],
                 SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    aparecer_jugador(jugador_cuatro, 3, parametro0[3], parametro1[3], parametro2, 32768.0f, selecciones_personaje[3],
                 SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    aparecer_jugador(jugador_cinco, 4, parametro0[4], parametro1[4], parametro2, 32768.0f, 4, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_seis, 5, parametro0[5], parametro1[5], parametro2, 32768.0f, 5, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_siete, 6, parametro0[6], parametro1[6], parametro2, 32768.0f, 6, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_ocho, 7, parametro0[0], parametro1[0], parametro2, 32768.0f, 7, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    dato_80164A28 = 0;
    funcion_80039AE4();
}

void funcion_8003B318(f32* parametro0, f32* parametro1, f32 parametro2) {
    aparecer_jugador(jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                 EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 32768.0f, selecciones_personaje[1],
                 EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    aparecer_jugador(jugador_tres, 2, parametro0[2], parametro1[2], parametro2, 32768.0f, selecciones_personaje[2],
                 EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    if (modo_demo == 1) {
        aparecer_jugador(jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0], HUMANO_JUGADOR_Y_CPU);
        aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 32768.0f, selecciones_personaje[1], HUMANO_JUGADOR_Y_CPU);
        aparecer_jugador(jugador_tres, 2, parametro0[2], parametro1[2], parametro2, 32768.0f, selecciones_personaje[2], HUMANO_JUGADOR_Y_CPU);
    }

    aparecer_jugador(jugador_cuatro, 3, parametro0[3], parametro1[3], parametro2, 32768.0f, 3, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_cinco, 4, parametro0[4], parametro1[4], parametro2, 32768.0f, 4, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_seis, 5, parametro0[5], parametro1[5], parametro2, 32768.0f, 5, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_siete, 6, parametro0[6], parametro1[6], parametro2, 32768.0f, 6, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_ocho, 7, parametro0[0], parametro1[0], parametro2, 32768.0f, 7, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    dato_80164A28 = 0;
    funcion_80039AE4();
}

void aparecer_batalla_jugadores_3j(f32* parametro0, f32* parametro1, f32 parametro2) {
    if (id_circuito_actual == CIRCUITO_BIG_DONUT) {
        aparecer_jugador(jugador_uno, 0, parametro0[0], parametro1[0], parametro2, -16384.0f, selecciones_personaje[0],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 16384.0f, selecciones_personaje[1],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_tres, 2, parametro0[2], parametro1[2], parametro2, 0.0f, selecciones_personaje[2],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    } else {
        aparecer_jugador(jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 0.0f, selecciones_personaje[1],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_tres, 2, parametro0[2], parametro1[2], parametro2, -16384.0f, selecciones_personaje[2],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    }
    aparecer_jugador(jugador_cuatro, 3, parametro0[3], parametro1[3], parametro2, 32768.0f, 3, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_cinco, 4, parametro0[4], parametro1[4], parametro2, 32768.0f, 4, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_seis, 5, parametro0[5], parametro1[5], parametro2, 32768.0f, 5, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_siete, 6, parametro0[6], parametro1[6], parametro2, 32768.0f, 6, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_ocho, 7, parametro0[0], parametro1[0], parametro2, 32768.0f, 7, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    dato_80164A28 = 0;
    funcion_80039AE4();
}

void funcion_8003B870(f32* parametro0, f32* parametro1, f32 parametro2) {
    aparecer_jugador(jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                 EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 32768.0f, selecciones_personaje[1],
                 EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    aparecer_jugador(jugador_tres, 2, parametro0[2], parametro1[2], parametro2, 32768.0f, selecciones_personaje[2],
                 EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    aparecer_jugador(jugador_cuatro, 3, parametro0[3], parametro1[3], parametro2, 32768.0f, selecciones_personaje[3],
                 EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    if (modo_demo == 1) {
        aparecer_jugador(jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0], HUMANO_JUGADOR_Y_CPU);
        aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 32768.0f, selecciones_personaje[1], HUMANO_JUGADOR_Y_CPU);
        aparecer_jugador(jugador_tres, 2, parametro0[2], parametro1[2], parametro2, 32768.0f, selecciones_personaje[2], HUMANO_JUGADOR_Y_CPU);
        aparecer_jugador(jugador_cuatro, 3, parametro0[3], parametro1[3], parametro2, 32768.0f, selecciones_personaje[3], HUMANO_JUGADOR_Y_CPU);
    }
    aparecer_jugador(jugador_cinco, 4, parametro0[4], parametro1[4], parametro2, 32768.0f, 4, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_seis, 5, parametro0[5], parametro1[5], parametro2, 32768.0f, 5, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_siete, 6, parametro0[6], parametro1[6], parametro2, 32768.0f, 6, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_ocho, 7, parametro0[0], parametro1[0], parametro2, 32768.0f, 7, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    dato_80164A28 = 0;
    funcion_80039AE4();
}

void aparecer_batalla_jugadores_4j(f32* parametro0, f32* parametro1, f32 parametro2) {
    if (id_circuito_actual == CIRCUITO_BIG_DONUT) {
        aparecer_jugador(jugador_uno, 0, parametro0[0], parametro1[0], parametro2, -16384.0f, selecciones_personaje[0],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 16384.0f, selecciones_personaje[1],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_tres, 2, parametro0[2], parametro1[2], parametro2, 0.0f, selecciones_personaje[2],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_cuatro, 3, parametro0[3], parametro1[3], parametro2, 32768.0f, selecciones_personaje[3],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    } else {
        aparecer_jugador(jugador_uno, 0, parametro0[0], parametro1[0], parametro2, 32768.0f, selecciones_personaje[0],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_dos, 1, parametro0[1], parametro1[1], parametro2, 0.0f, selecciones_personaje[1],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_tres, 2, parametro0[2], parametro1[2], parametro2, -16384.0f, selecciones_personaje[2],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
        aparecer_jugador(jugador_cuatro, 3, parametro0[3], parametro1[3], parametro2, 16384.0f, selecciones_personaje[3],
                     EXISTE_JUGADOR | SECUENCIA_INICIO_JUGADOR | HUMANO_JUGADOR);
    }
    aparecer_jugador(jugador_cinco, 4, parametro0[4], parametro1[4], parametro2, 32768.0f, 4, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_seis, 5, parametro0[5], parametro1[5], parametro2, 32768.0f, 5, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_siete, 6, parametro0[6], parametro1[6], parametro2, 32768.0f, 6, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    aparecer_jugador(jugador_ocho, 7, parametro0[0], parametro1[0], parametro2, 32768.0f, 7, SECUENCIA_INICIO_JUGADOR | CPU_JUGADOR);
    dato_80164A28 = 0;
    funcion_80039AE4();
}

void funcion_8003BE30(void) {
    aparecer_jugador(jugador_uno, 0, -2770.774f, -345.187f, -34.6f, 0.0f, id_personaje_por_puesto_total_gp[0],
                 EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    aparecer_jugador(jugador_dos, 1, -3691.506f, -6.822f, -6.95f, (f32) (200 * GRADOS(1)), id_personaje_por_puesto_total_gp[1],
                 EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    aparecer_jugador(jugador_tres, 2, -3475.028f, -998.485f, -8.059f, (f32) (250 * GRADOS(1)), id_personaje_por_puesto_total_gp[2],
                 EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    if (dato_802874D8.desconocido_1d >= 3) {
        aparecer_jugador(jugador_cuatro, 3, -3025.772f, 110.039f, -23.224f, (f32) (155 * GRADOS(1)), dato_802874D8.desconocido_1e,
                     EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    } else {
        aparecer_jugador(jugador_cuatro, 3, -3025.772f, 110.039f, -23.224f, (f32) (155 * GRADOS(1)), id_personaje_por_puesto_total_gp[3],
                     EXISTE_JUGADOR | CPU_JUGADOR | SECUENCIA_INICIO_JUGADOR);
    }
    aparecer_jugador(jugador_cinco, 4, -2770.774f, -345.187f, -34.6f, 0.0f, 0, 0x7000);
    aparecer_jugador(jugador_seis, 5, -3691.506f, -6.822f, -6.95f, (f32) (200 * GRADOS(1)), 0, 0x7000);
    aparecer_jugador(jugador_siete, 6, -3475.028f, -998.485f, -8.059f, (f32) (250 * GRADOS(1)), 0, 0x7000);
    aparecer_jugador(jugador_ocho, 7, -3025.772f, 110.039f, -23.224f, (f32) (155 * GRADOS(1)), 0, 0x7000);
    dato_80164A28 = 0;
    funcion_80039AE4();
}
