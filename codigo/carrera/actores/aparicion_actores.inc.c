// Aparicion actores

#include "carrera/actores/roca_que_cae/actualizar.inc.c"

void aparecer_follaje(struct DatosAparicionActor* parametro0) {
    SIN_USO s32 relleno[4];
    Vec3f posicion;
    Vec3f velocidad;
    Vec3s rotacion;
    SIN_USO s16 relleno2;
    s16 tipo_actor;
    struct Actor* temporal_s0;
    struct DatosAparicionActor* variable_s3;
    s32 segmento = SEGMENT_NUMBER2(parametro0);
    s32 desplazamiento = SEGMENT_OFFSET(parametro0);

    variable_s3 = (struct DatosAparicionActor*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    fijar_vec3f(velocidad, 0.0f, 0.0f, 0.0f);
    rotacion[0] = GRADOS(90);
    rotacion[1] = 0;
    rotacion[2] = 0;

    while (variable_s3->pos[0] != FIN_DE_DATOS_APARICION) {
        posicion[0] = variable_s3->pos[0] * sentido_circuito;
        posicion[2] = variable_s3->pos[2];
        posicion[1] = variable_s3->pos[1];

        switch (id_circuito_actual) {
            case CIRCUITO_MARIO_RACEWAY:
                tipo_actor = 2;
                break;
            case CIRCUITO_BOWSER_CASTLE:
                tipo_actor = 0x0021;
                break;
            case CIRCUITO_YOSHI_VALLEY:
                tipo_actor = 3;
                break;
            case CIRCUITO_FRAPPE_SNOWLAND:
                tipo_actor = 0x001D;
                break;
            case CIRCUITO_ROYAL_RACEWAY:
                switch (variable_s3->id_algun_con_signo) {
                    case 6:
                        tipo_actor = 0x001C;
                        break;
                    case 7:
                        tipo_actor = 4;
                        break;
                }
                break;
            case CIRCUITO_LUIGI_RACEWAY:
                tipo_actor = 0x001A;
                break;
            case CIRCUITO_MOO_MOO_FARM:
                tipo_actor = 0x0013;
                break;
            case CIRCUITO_KALAMARI_DESERT:
                switch (variable_s3->id_algun_con_signo) {
                    case 5:
                        tipo_actor = 0x001E;
                        break;
                    case 6:
                        tipo_actor = 0x001F;
                        break;
                    case 7:
                        tipo_actor = 0x0020;
                        break;
                }
                break;
        }

        temporal_s0 = &lista_actor[agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, tipo_actor)];
        if (estado_juego == SECUENCIA_CREDITOS) {
            funcion_802976D8(temporal_s0->rot);
        } else {
            comprobar_colision_envolvente(&temporal_s0->desconocido30, 5.0f, temporal_s0->pos[0], temporal_s0->pos[1], temporal_s0->pos[2]);
            if (temporal_s0->desconocido30.distancia_superficie[2] < 0.0f) {
                temporal_s0->pos[1] = calcular_altura_superficie(temporal_s0->pos[0], temporal_s0->pos[1], temporal_s0->pos[2],
                                                           temporal_s0->desconocido30.indice_zx_malla);
            }
            funcion_802976EC(&temporal_s0->desconocido30, temporal_s0->rot);
        }
        variable_s3++;
    }
}

void aparecer_todos_cajas_item(struct DatosAparicionActor* aparecer_datos) {
    s32 segmento = SEGMENT_NUMBER2(aparecer_datos);
    s32 desplazamiento = SEGMENT_OFFSET(aparecer_datos);
    s16 temporal_s1;
    f32 temporal_f0;
    Vec3f pos_inicial;
    Vec3f velocidad_inicial;
    Vec3s rot_inicial;
    struct DatosAparicionActor* temporal_s0 = (struct DatosAparicionActor*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);

    if ((seleccion_modo == CONTRARRELOJ) || (cajas_item_lugar == 0)) {
        return;
    }

    fijar_vec3f(velocidad_inicial, 0, 0, 0);
    while (temporal_s0->pos[0] != FIN_DE_DATOS_APARICION) {
        pos_inicial[0] = temporal_s0->pos[0] * sentido_circuito;
        pos_inicial[1] = temporal_s0->pos[1];
        pos_inicial[2] = temporal_s0->pos[2];
        rot_inicial[0] = aleatorio_u16();
        rot_inicial[1] = aleatorio_u16();
        rot_inicial[2] = aleatorio_u16();
        temporal_s1 = agregar_actor_a_ranura_vacio(pos_inicial, rot_inicial, velocidad_inicial, ACTOR_CAJA_ITEM);
        temporal_f0 = obtener_altura_superficie(pos_inicial[0], pos_inicial[1] + 10.0f, pos_inicial[2]);

        lista_actor[temporal_s1].desconocido_08 = temporal_f0;

        lista_actor[temporal_s1].velocidad[0] = pos_inicial[1];

        lista_actor[temporal_s1].pos[1] = temporal_f0 - 20.0f;

        temporal_s0++;
    }
}

void inicializar_kiwano_fruta(void) {
    Vec3f sp64;
    Vec3f sp58;
    Vec3s sp50;
    Jugador* phi_s1;
    struct Actor* actor;
    s16 phi_s0;
    s32 i;

    for (i = 0; i < 4; i++) {
        phi_s1 = &jugadores[i];
        if ((phi_s1->type & HUMANO_JUGADOR) == 0) {
            continue;
        }
        if ((phi_s1->type & INVISIBLE_JUGADOR_O_BOMBA) != 0) {
            continue;
        }

        phi_s0 = agregar_actor_a_ranura_vacio(sp64, sp50, sp58, ACTOR_KIWANO_FRUTA);
        actor = &lista_actor[phi_s0];
        actor->desconocido_04 = i;
    }
}

void destruir_todos_actores(void) {
    s32 i;
    actores_num = 0;
    for (i = 0; i < TAMANIO_LISTA_ACTOR; i++) {
        lista_actor[i].flags = 0;
        lista_actor[i].type = 0;
        lista_actor[i].desconocido_04 = 0;
        lista_actor[i].state = 0;
        lista_actor[i].desconocido_08 = 0.0f;
        lista_actor[i].tamanio_caja_envolvente = 0.0f;
    }
}

void aparecer_actores_circuito(void) {
    SIN_USO s32 relleno;
    Vec3f posicion;
    Vec3f velocidad = { 0.0f, 0.0f, 0.0f };
    Vec3s rotacion = { 0, 0, 0 };
    struct Actor* actor;
    struct PasoANivel* rrxing;

    actores_permanente_num = 0;
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            aparecer_follaje(d_circuito_mario_raceway_apariciones_arbol);
            aparecer_plantas_piranha(d_circuito_mario_raceway_planta_piranha_apariciones);
            aparecer_todos_cajas_item(d_circuito_mario_raceway_caja_item_apariciones);
            fijar_vec3f(posicion, 150.0f, 40.0f, -1300.0f);
            posicion[0] *= sentido_circuito;
            agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, ACTOR_MARIO_CARTEL);
            fijar_vec3f(posicion, 2520.0f, 0.0f, 1240.0f);
            posicion[0] *= sentido_circuito;
            actor = &lista_actor[agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, ACTOR_MARIO_CARTEL)];
            actor->flags |= 0x4000;
            break;
        case CIRCUITO_CHOCO_MOUNTAIN:
            aparecer_todos_cajas_item(d_circuito_choco_mountain_caja_item_apariciones);
            aparecer_rocas_cayendo(d_circuito_choco_mountain_apariciones_roca_cayendo);
            break;
        case CIRCUITO_BOWSER_CASTLE:
            aparecer_follaje(d_circuito_bowsers_castle_aparicion_arbol);
            aparecer_todos_cajas_item(d_circuito_bowsers_castle_caja_item_apariciones);
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            aparecer_todos_cajas_item(d_circuito_banshee_boardwalk_caja_item_apariciones);
            break;
        case CIRCUITO_YOSHI_VALLEY:
            aparecer_follaje(d_circuito_yoshi_valley_aparicion_arbol);
            aparecer_todos_cajas_item(d_circuito_yoshi_valley_caja_item_apariciones);
            fijar_vec3f(posicion, -2300.0f, 0.0f, 634.0f);
            posicion[0] *= sentido_circuito;
            agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, ACTOR_YOSHI_HUEVO);
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            aparecer_follaje(d_circuito_frappe_snowland_apariciones_arbol);
            aparecer_todos_cajas_item(d_circuito_frappe_snowland_caja_item_apariciones);
            break;
        case CIRCUITO_KOOPA_BEACH:
            inicializar_actor_globo_aerostatico_caja_item(328.0f * sentido_circuito, 70.0f, 2541.0f);
            aparecer_todos_cajas_item(d_circuito_koopa_troopa_beach_caja_item_apariciones);
            aparecer_arboles_palmera(d_circuito_koopa_troopa_beach_aparicion_arbol);
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            aparecer_follaje(d_circuito_royal_raceway_aparicion_arbol);
            aparecer_todos_cajas_item(d_circuito_royal_raceway_caja_item_apariciones);
            aparecer_plantas_piranha(d_circuito_royal_raceway_planta_piranha_aparicion);
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            aparecer_follaje(d_circuito_luigi_raceway_aparicion_arbol);
            aparecer_todos_cajas_item(d_circuito_luigi_raceway_caja_item_apariciones);
            break;
        case CIRCUITO_MOO_MOO_FARM:
            if (seleccion_cantidad_jugador_1 != 4) {
                aparecer_follaje(d_circuito_moo_moo_farm_aparicion_arbol);
            }
            aparecer_todos_cajas_item(d_circuito_moo_moo_farm_caja_item_apariciones);
            break;
        case CIRCUITO_TOADS_TURNPIKE:
            aparecer_todos_cajas_item(d_circuito_toads_turnpike_caja_item_apariciones);
            break;
        case CIRCUITO_KALAMARI_DESERT:
            aparecer_follaje(d_circuito_kalimari_desert_aparicion_cactus);
            aparecer_todos_cajas_item(d_circuito_kalimari_desert_caja_item_apariciones);
            fijar_vec3f(posicion, -1680.0f, 2.0f, 35.0f);
            posicion[0] *= sentido_circuito;
            rrxing = (struct PasoANivel*) &lista_actor[agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad,
                                                                                    ACTOR_PASO_A_NIVEL)];
            rrxing->id_cruce = 1;
            fijar_vec3f(posicion, -1600.0f, 2.0f, 35.0f);
            posicion[0] *= sentido_circuito;
            rrxing = (struct PasoANivel*) &lista_actor[agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad,
                                                                                    ACTOR_PASO_A_NIVEL)];
            rrxing->id_cruce = 1;
            fijar_vec3s(rotacion, 0, -GRADOS(45), 0);
            fijar_vec3f(posicion, -2459.0f, 2.0f, 2263.0f);
            posicion[0] *= sentido_circuito;
            rrxing = (struct PasoANivel*) &lista_actor[agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad,
                                                                                    ACTOR_PASO_A_NIVEL)];
            rrxing->id_cruce = 0;
            fijar_vec3f(posicion, -2467.0f, 2.0f, 2375.0f);
            posicion[0] *= sentido_circuito;
            rrxing = (struct PasoANivel*) &lista_actor[agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad,
                                                                                    ACTOR_PASO_A_NIVEL)];
            rrxing->id_cruce = 0;
            break;
        case CIRCUITO_SHERBET_LAND:
            aparecer_todos_cajas_item(d_circuito_sherbet_land_caja_item_apariciones);
            break;
        case CIRCUITO_RAINBOW_ROAD:
            aparecer_todos_cajas_item(d_circuito_rainbow_road_caja_item_apariciones);
            break;
        case CIRCUITO_WARIO_STADIUM:
            aparecer_todos_cajas_item(d_circuito_wario_stadium_caja_item_apariciones);
            fijar_vec3f(posicion, -131.0f, 83.0f, 286.0f);
            posicion[0] *= sentido_circuito;
            agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, ACTOR_WARIO_CARTEL);
            fijar_vec3f(posicion, -2353.0f, 72.0f, -1608.0f);
            posicion[0] *= sentido_circuito;
            agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, ACTOR_WARIO_CARTEL);
            fijar_vec3f(posicion, -2622.0f, 79.0f, 739.0f);
            posicion[0] *= sentido_circuito;
            agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, ACTOR_WARIO_CARTEL);
            break;
        case CIRCUITO_BLOCK_FORT:
            aparecer_todos_cajas_item(d_circuito_block_fort_caja_item_apariciones);
            break;
        case CIRCUITO_SKYSCRAPER:
            aparecer_todos_cajas_item(d_circuito_skyscraper_caja_item_apariciones);
            break;
        case CIRCUITO_DOUBLE_DECK:
            aparecer_todos_cajas_item(d_circuito_double_deck_caja_item_apariciones);
            break;
        case CIRCUITO_DK_JUNGLE:
            aparecer_todos_cajas_item(d_circuito_dks_jungle_parkway_caja_item_apariciones);
            inicializar_kiwano_fruta();
            funcion_80298D10();
            break;
        case CIRCUITO_BIG_DONUT:
            aparecer_todos_cajas_item(d_circuito_big_donut_caja_item_apariciones);
            break;
    }
#else

#endif
    actores_permanente_num = actores_num;
}

void cargar_texturas_actores_inicializacion_y(void) {
    fijar_direccion_base_segmento(3, (void*) siguiente_libre_memoria_direccion);
    dato_802BA050 = texturas_dma(textura_caparazon_verde_0, 0x00000257U, 0x00000400U);
    texturas_dma(textura_caparazon_verde_1, 0x00000242U, 0x00000400U);
    texturas_dma(textura_caparazon_verde_2, 0x00000259U, 0x00000400U);
    texturas_dma(textura_caparazon_verde_3, 0x00000256U, 0x00000400U);
    texturas_dma(textura_caparazon_verde_4, 0x00000246U, 0x00000400U);
    texturas_dma(textura_caparazon_verde_5, 0x0000025EU, 0x00000400U);
    texturas_dma(textura_caparazon_verde_6, 0x0000025CU, 0x00000400U);
    texturas_dma(textura_caparazon_verde_7, 0x00000254U, 0x00000400U);
    dato_802BA054 = texturas_dma(textura_caparazon_azul_0, 0x0000022AU, 0x00000400U);
    texturas_dma(textura_caparazon_azul_1, 0x00000237U, 0x00000400U);
    texturas_dma(textura_caparazon_azul_2, 0x0000023EU, 0x00000400U);
    texturas_dma(textura_caparazon_azul_3, 0x00000243U, 0x00000400U);
    texturas_dma(textura_caparazon_azul_4, 0x00000255U, 0x00000400U);
    texturas_dma(textura_caparazon_azul_5, 0x00000259U, 0x00000400U);
    texturas_dma(textura_caparazon_azul_6, 0x00000239U, 0x00000400U);
    texturas_dma(textura_caparazon_azul_7, 0x00000236U, 0x00000400U);
    texturas_dma(textura_linea_meta_cartel_1, 0x0000028EU, 0x00000800U);
    texturas_dma(textura_linea_meta_cartel_2, 0x000002FBU, 0x00000800U);
    texturas_dma(textura_linea_meta_cartel_3, 0x00000302U, 0x00000800U);
    texturas_dma(textura_linea_meta_cartel_4, 0x000003B4U, 0x00000800U);
    texturas_dma(textura_linea_meta_cartel_5, 0x0000031EU, 0x00000800U);
    texturas_dma(textura_linea_meta_cartel_6, 0x0000036EU, 0x00000800U);
    texturas_dma(textura_linea_meta_cartel_7, 0x0000029CU, 0x00000800U);
    texturas_dma(textura_linea_meta_cartel_8, 0x0000025BU, 0x00000800U);
    texturas_dma(textura_671A88, 0x00000400U, 0x00000800U);
    texturas_dma(textura_6774D8, 0x00000400U, 0x00000800U);
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            texturas_dma(textura_arboles_1, 0x0000035BU, 0x00000800U);
            dato_802BA058 = texturas_dma(textura_planta_piranha_1, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_2, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_3, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_4, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_5, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_6, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_7, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_8, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_9, 0x000003E8U, 0x00000800U);
            break;
        case CIRCUITO_BOWSER_CASTLE:
            texturas_dma(textura_arbusto, 0x000003FFU, 0x00000800U);
            break;
        case CIRCUITO_YOSHI_VALLEY:
            texturas_dma(textura_arboles_2, 0x000003E8U, 0x00000800U);
            break;
        case CIRCUITO_FRAPPE_SNOWLAND:
            texturas_dma(textura_frappe_snowland_izquierda_arbol, 0x00000454U, 0x00000800U);
            texturas_dma(textura_frappe_snowland_derecha_arbol, 0x00000432U, 0x00000800U);
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            texturas_dma(textura_arboles_3, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_arboles_7, 0x000003E8U, 0x00000800U);
            dato_802BA058 = texturas_dma(textura_planta_piranha_1, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_2, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_3, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_4, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_5, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_6, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_7, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_8, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_planta_piranha_9, 0x000003E8U, 0x00000800U);
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            texturas_dma(textura_izquierda_arboles_5, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_derecha_arboles_5, 0x000003E8U, 0x00000800U);
            break;
        case CIRCUITO_MOO_MOO_FARM:
            texturas_dma(textura_izquierda_arboles_4, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_derecha_arboles_4, 0x000003E8U, 0x00000800U);
            texturas_dma(textura_izquierda_vaca_01, 0x00000400U, 0x00000800U);
            texturas_dma(textura_derecha_vaca_01, 0x00000400U, 0x00000800U);
            texturas_dma(textura_izquierda_vaca_02, 0x00000400U, 0x00000800U);
            texturas_dma(textura_derecha_vaca_02, 0x00000400U, 0x00000800U);
            texturas_dma(textura_izquierda_vaca_03, 0x00000400U, 0x00000800U);
            texturas_dma(textura_derecha_vaca_03, 0x00000400U, 0x00000800U);
            texturas_dma(textura_izquierda_vaca_04, 0x00000400U, 0x00000800U);
            texturas_dma(textura_derecha_vaca_04, 0x00000400U, 0x00000800U);
            texturas_dma(textura_izquierda_vaca_05, 0x00000400U, 0x00000800U);
            texturas_dma(textura_derecha_vaca_05, 0x00000400U, 0x00000800U);
            break;
        case CIRCUITO_KALAMARI_DESERT:
            texturas_dma(textura_izquierda_cactus_1, 0x0000033EU, 0x00000800U);
            texturas_dma(textura_derecha_cactus_1, 0x000002FBU, 0x00000800U);
            texturas_dma(textura_izquierda_cactus_2, 0x000002A8U, 0x00000800U);
            texturas_dma(textura_derecha_cactus_2, 0x00000374U, 0x00000800U);
            texturas_dma(textura_cactus_3, 0x000003AFU, 0x00000800U);
            break;
        case CIRCUITO_DK_JUNGLE:
            texturas_dma(textura_dks_jungle_parkway_kiwano_fruta_1, 0x0000032FU, 0x00000400U);
            texturas_dma(textura_dks_jungle_parkway_kiwano_fruta_2, 0x00000369U, 0x00000400U);
            texturas_dma(textura_dks_jungle_parkway_kiwano_fruta_3, 0x00000364U, 0x00000400U);
            break;
    }
#else

#endif
    inicializar_caparazon_rojo_textura();
    destruir_todos_actores();
    aparecer_actores_circuito();
    aparecer_vehiculos_circuito();
}

void quitar_sonido_juego_antes(struct Actor* actor) {
    s16 banderas = actor->flags;

    if ((banderas & 0x200) != 0) {
        funcion_800C99E0(actor->pos, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x90, 0x53));
        return;
    }
    if ((banderas & 0x100) != 0) {
        funcion_800C99E0(actor->pos, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x10));
        return;
    }
    if ((banderas & 0x80) != 0) {
        funcion_800C99E0(actor->pos, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x80, 0x54));
    }
}

void destruir_actor(struct Actor* actor) {
    quitar_sonido_juego_antes(actor);
    actor->flags = 0;
    actor->type = 0;
    actores_num--;
}

s16 quitar_item_destructible_intentar(Vec3f pos, Vec3s rot, Vec3f velocidad, s16 tipo_actor) {
    s32 indice_actor;
    struct ActorCaparazon* comparar;

    for (indice_actor = actores_permanente_num; indice_actor < TAMANIO_LISTA_ACTOR; indice_actor++) {
        comparar = (struct ActorCaparazon*) &lista_actor[indice_actor];
        if (!(comparar->flags & ES_ACTOR_NO_VENCIDO)) {
            switch (comparar->type) {
                case ACTOR_CAPARAZON_ROJO:
                    switch (comparar->state) {
                        case CAPARAZON_MOVIENDO:
                        case CAPARAZON_ROJO_BLOQUEO_EN:
                        case TRIPLE_CAPARAZON_VERDE:
                        case CAPARAZON_VERDE_CORREDOR_GOLPE_A:
                        case CAPARAZON_AZUL_BLOQUEO_EN:
                        case CAPARAZON_AZUL_OBJETIVO_ELIMINADO:
                            eliminar_actor_en_lista_actor_vigente(indice_actor);
                        case CAPARAZON_DESTRUIDO:
                            quitar_sonido_juego_antes((struct Actor*) comparar);
                            inicializar_actor((struct Actor*) comparar, pos, rot, velocidad, tipo_actor);
                            return indice_actor;
                        default:
                            break;
                    }
                    break;
                case ACTOR_CAPARAZON_VERDE:
                    switch (comparar->state) {
                        case CAPARAZON_MOVIENDO:
                            eliminar_actor_en_lista_actor_vigente(indice_actor);
                        case CAPARAZON_DESTRUIDO:
                            quitar_sonido_juego_antes((struct Actor*) comparar);
                            inicializar_actor((struct Actor*) comparar, pos, rot, velocidad, tipo_actor);
                            return indice_actor;
                    }
                    break;
                case ACTOR_BANANA:
                    switch (comparar->state) {
                        case BANANA_SOLTADO:
                        case BANANA_EN_SUELO:
                        case BANANA_DESTRUIDO:
                            quitar_sonido_juego_antes((struct Actor*) comparar);
                            inicializar_actor((struct Actor*) comparar, pos, rot, velocidad, tipo_actor);
                            return indice_actor;
                    }
                    break;
                case ACTOR_CAJA_ITEM_FALSA:
                    switch (comparar->state) {
                        case CAJA_ITEM_FALSA_EN_SUELO:
                        case DESTRUIDO_CAJA_ITEM_FALSA:
                            quitar_sonido_juego_antes((struct Actor*) comparar);
                            inicializar_actor((struct Actor*) comparar, pos, rot, velocidad, tipo_actor);
                            return indice_actor;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    for (indice_actor = actores_permanente_num; indice_actor < TAMANIO_LISTA_ACTOR; indice_actor++) {
        comparar = (struct ActorCaparazon*) &lista_actor[indice_actor];
        switch (comparar->type) {
            case ACTOR_CAPARAZON_ROJO:
                switch (comparar->state) {
                    case CAPARAZON_MOVIENDO:
                    case CAPARAZON_ROJO_BLOQUEO_EN:
                    case TRIPLE_CAPARAZON_VERDE:
                    case CAPARAZON_VERDE_CORREDOR_GOLPE_A:
                    case CAPARAZON_AZUL_BLOQUEO_EN:
                    case CAPARAZON_AZUL_OBJETIVO_ELIMINADO:
                        eliminar_actor_en_lista_actor_vigente(indice_actor);
                    case CAPARAZON_DESTRUIDO:
                        quitar_sonido_juego_antes((struct Actor*) comparar);
                        inicializar_actor((struct Actor*) comparar, pos, rot, velocidad, tipo_actor);
                        return indice_actor;
                    default:
                        break;
                }
                break;
            case ACTOR_CAPARAZON_VERDE:
                switch (comparar->state) {
                    case CAPARAZON_MOVIENDO:
                        eliminar_actor_en_lista_actor_vigente(indice_actor);
                    case CAPARAZON_DESTRUIDO:
                        quitar_sonido_juego_antes((struct Actor*) comparar);
                        inicializar_actor((struct Actor*) comparar, pos, rot, velocidad, tipo_actor);
                        return indice_actor;
                }
                break;
            case ACTOR_BANANA:
                switch (comparar->state) {
                    case BANANA_SOLTADO:
                    case BANANA_EN_SUELO:
                    case BANANA_DESTRUIDO:
                        quitar_sonido_juego_antes((struct Actor*) comparar);
                        inicializar_actor((struct Actor*) comparar, pos, rot, velocidad, tipo_actor);
                        return indice_actor;
                }
                break;
            case ACTOR_CAJA_ITEM_FALSA:
                switch (comparar->state) {
                    case CAJA_ITEM_FALSA_EN_SUELO:
                    case DESTRUIDO_CAJA_ITEM_FALSA:
                        quitar_sonido_juego_antes((struct Actor*) comparar);
                        inicializar_actor((struct Actor*) comparar, pos, rot, velocidad, tipo_actor);
                        return indice_actor;
                }
                break;
            default:
                break;
        }
    }

    return -1;
}

s16 agregar_actor_a_ranura_vacio(Vec3f pos, Vec3s rot, Vec3f velocidad, s16 tipo_actor) {
    s32 index;

    if (actores_num >= TAMANIO_LISTA_ACTOR) {
        return quitar_item_destructible_intentar(pos, rot, velocidad, tipo_actor);
    }
    for (index = 0; index < TAMANIO_LISTA_ACTOR; index++) {
        if (lista_actor[index].flags == 0) {
            actores_num++;
            inicializar_actor(&lista_actor[index], pos, rot, velocidad, tipo_actor);
            return index;
        }
    }
    return -1;
}

SIN_USO s16 aparecer_actor_en_pos(Vec3f pos, s16 tipo_actor) {
    Vec3f vel;
    Vec3s rot;

    fijar_vec3f(vel, 0.0f, 0.0f, 0.0f);
    fijar_vec3s(rot, 0, 0, 0);
    return agregar_actor_a_ranura_vacio(pos, rot, vel, tipo_actor);
}

struct probar {
    Vec3s cosa;
};

SIN_USO void aparecer_datos_actor_prototipo(Jugador* jugador, uintptr_t parametro1) {
    Vec3f sp64;
    struct probar* variable_s0;
    s32 segmento = SEGMENT_NUMBER2(parametro1);
    s32 desplazamiento = SEGMENT_OFFSET(parametro1);

    variable_s0 = (struct probar*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    while (variable_s0->cosa[0] != FIN_DE_DATOS_APARICION) {
        sp64[0] = variable_s0->cosa[0] * sentido_circuito;
        sp64[1] = variable_s0->cosa[1];
        sp64[2] = variable_s0->cosa[2];
        if (parametro1 & parametro1) {}
        consultar_y_resolver_colision_jugador_actor(jugador, sp64, 5.0f, 40.0f, 0.8f);
        variable_s0++;
    }
}

bool consultar_y_resolver_colision_jugador_actor(Jugador* jugador, Vec3f pos, f32 min_dist, f32 dist, f32 parametro4) {
    f32 y_dist_2;
    f32 dist_raiz;
    f32 z_dist_2;
    f32 velocidad_x;
    f32 velocidad_z;
    f32 temporal_f0_4;
    f32 temporal_f0_5;
    f32 temporal_f0_6;
    f32 x_dist_2;
    f32 sp28;
    f32 temporal_f2_2;

    min_dist = jugador->tamanio_caja_envolvente + min_dist;
    dist = jugador->tamanio_caja_envolvente + dist;
    x_dist_2 = pos[0] - jugador->pos[0];
    if (min_dist < x_dist_2) {
        return SIN_COLISION;
    }
    if (x_dist_2 < -min_dist) {
        return SIN_COLISION;
    }
    y_dist_2 = pos[1] - jugador->pos[1];
    if (dist < y_dist_2) {
        return SIN_COLISION;
    }
    if (y_dist_2 < -dist) {
        return SIN_COLISION;
    }
    z_dist_2 = pos[2] - jugador->pos[2];
    if (min_dist < z_dist_2) {
        return SIN_COLISION;
    }
    if (z_dist_2 < -min_dist) {
        return SIN_COLISION;
    }
    dist = (x_dist_2 * x_dist_2) + (y_dist_2 * y_dist_2) + (z_dist_2 * z_dist_2);
    if (dist < 0.1f) {
        return SIN_COLISION;
    }
    if ((min_dist * min_dist) < dist) {
        return SIN_COLISION;
    }
    dist_raiz = sqrtf(dist);
    sp28 = dist_raiz - min_dist;
    velocidad_x = jugador->velocidad[0];
    velocidad_z = jugador->velocidad[2];
    if (jugador->efectos & EFECTO_ESTRELLA) {
        return COLISION;
    }
    if (dist_raiz < 0.1f) {
        temporal_f0_4 = sqrtf((velocidad_x * velocidad_x) + (velocidad_z * velocidad_z));
        if (temporal_f0_4 < 0.5f) {
            temporal_f0_4 = 0.5f;
        }
        jugador->velocidad[0] = 0;
        jugador->velocidad[2] = 0;
        jugador->pos[0] += (velocidad_x / temporal_f0_4) * min_dist;
        jugador->pos[2] += (velocidad_z / temporal_f0_4) * min_dist;
    } else {
        jugador->efectos |= EFECTO_GOLPE_ENEMIGO;
        x_dist_2 /= dist_raiz;
        z_dist_2 /= dist_raiz;
        temporal_f0_5 = sqrtf((velocidad_x * velocidad_x) + (velocidad_z * velocidad_z));
        if (temporal_f0_5 < 0.25f) {
            temporal_f0_6 = 1.2f;
            jugador->pos[0] = pos[0] - (x_dist_2 * min_dist * temporal_f0_6);
            jugador->pos[2] = pos[2] - (z_dist_2 * min_dist * temporal_f0_6);
            jugador->velocidad[0] = 0.0f;
            jugador->velocidad[2] = 0.0f;
            return COLISION;
        }
        temporal_f2_2 = ((x_dist_2 * velocidad_x) + (z_dist_2 * velocidad_z)) / temporal_f0_5;
        temporal_f2_2 = temporal_f0_5 * temporal_f2_2 * parametro4 * 1.3f;
        jugador->velocidad[0] -= x_dist_2 * temporal_f2_2;
        jugador->velocidad[2] -= z_dist_2 * temporal_f2_2;
        jugador->pos[0] += x_dist_2 * sp28 * 0.5f;
        jugador->pos[2] += z_dist_2 * sp28 * 0.5f;
    }
    return COLISION;
}

bool colision_mario_cartel(Jugador* jugador, struct Actor* mario_raceway_cartel) {
    if (consultar_y_resolver_colision_jugador_actor(jugador, mario_raceway_cartel->pos, 7.0f, 200.0f, 0.8f) == COLISION) {
        if ((jugador->type & HUMANO_JUGADOR) != 0) {
            if ((jugador->efectos & EFECTO_ESTRELLA) != 0) {
                mario_raceway_cartel->flags |= 0x400;
                funcion_800C98B8(jugador->pos, jugador->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x10));
                funcion_800C90F4(jugador - jugador_uno,
                              (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
            } else if ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) == 0) {
                funcion_800C9060(jugador - jugador_uno, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x70, 0x1A));
            }
        }
        return true;
    }
    return false;
}

bool colision_planta_piranha(Jugador* jugador, struct PlantaPiranha* planta) {
    if (consultar_y_resolver_colision_jugador_actor(jugador, planta->pos, planta->tamanio_caja_envolvente, planta->tamanio_caja_envolvente,
                                                 2.5f) == COLISION) {
        if ((jugador->type & HUMANO_JUGADOR) != 0) {
            if ((jugador->efectos & EFECTO_ESTRELLA) != 0) {
                planta->flags |= 0x400;
                funcion_800C98B8(jugador->pos, jugador->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0xA2, 0x4A));
                funcion_800C90F4(jugador - jugador_uno,
                              (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
            } else if ((jugador->type & INVISIBLE_JUGADOR_O_BOMBA) == 0) {
                funcion_800C9060(jugador - jugador_uno, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0xA0, 0x52));
            }
        }
        return true;
    }
    return false;
}

bool colision_yoshi_huevo(Jugador* jugador, struct YoshiValleyHuevo* huevo) {
    SIN_USO f32 relleno[5];
    f32 z_dist;
    f32 xz_dist;
    f32 x_dist;
    f32 y_dist;
    f32 caja_total;
    f32 max_dist = 60.0f;
    f32 min_dist = 0.0f;

    x_dist = huevo->pos[0] - jugador->pos[0];
    if ((x_dist < min_dist) && (x_dist < -max_dist)) {
        return false;
    }
    if (x_dist > max_dist) {
        return false;
    }

    z_dist = huevo->pos[2] - jugador->pos[2];
    if ((z_dist < min_dist) && (z_dist < -max_dist)) {
        return false;
    }
    if (z_dist > max_dist) {
        return false;
    }

    xz_dist = sqrtf((x_dist * x_dist) + (z_dist * z_dist));
    if (xz_dist > max_dist) {
        return false;
    }
    funcion_802977B0(jugador);

    y_dist = jugador->pos[1] - huevo->pos[1];
    if (y_dist < min_dist) {
        return false;
    }

    caja_total = jugador->tamanio_caja_envolvente + huevo->tamanio_caja_envolvente;
    if (caja_total < xz_dist) {
        return false;
    }

    if ((jugador->type & HUMANO_JUGADOR) != 0) {
        if ((jugador->efectos & EFECTO_ESTRELLA) != 0) {
            huevo->flags |= 0x400;
            huevo->centro_camino[1] = 8.0f;
            funcion_800C98B8(jugador->pos, jugador->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x10));
            funcion_800C90F4(jugador - jugador_uno, (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
        } else {
            aplastamiento_disparador(jugador, jugador - jugador_uno);
            if ((seleccion_modo == CONTRARRELOJ) && ((jugador->type & CPU_JUGADOR) == 0)) {
                publicar_contrarreloj_guardado_no_puede_repeticion = 1;
            }
        }
    } else {
        aplastamiento_disparador(jugador, jugador - jugador_uno);
    }

    return true;
}

bool arbol_colision(Jugador* jugador, struct Actor* actor) {
    f32 x_dist;
    f32 y_dist;
    f32 z_dist;
    f32 sp48;
    f32 sp44;
    f32 variable_f16;
    f32 xz_dist;
    SIN_USO f32 relleno[2];
    f32 temporal_f12;
    f32 temporal_f0_4;
    Vec3f actor_pos;
    f32 temporal_f2;

    variable_f16 = actor->desconocido_08;
    x_dist = actor->pos[0] - jugador->pos[0];
    if ((x_dist < 0.0f) && (x_dist < -variable_f16)) {
        return false;
    }
    if (variable_f16 < x_dist) {
        return false;
    }
    z_dist = actor->pos[2] - jugador->pos[2];
    if ((z_dist < 0.0f) && (z_dist < -variable_f16)) {
        return false;
    }
    if (variable_f16 < z_dist) {
        return false;
    }
    y_dist = jugador->pos[1] - actor->pos[1];
    if (y_dist < 0.0f) {
        return false;
    }
    if ((f32) actor->state < y_dist) {
        return false;
    }
    xz_dist = sqrtf((x_dist * x_dist) + (z_dist * z_dist));
    if (variable_f16 < xz_dist) {
        return false;
    }
    funcion_802977B0(jugador);
    variable_f16 = jugador->tamanio_caja_envolvente + actor->tamanio_caja_envolvente;
    if (variable_f16 < xz_dist) {
        return false;
    }
    sp48 = jugador->velocidad[0];
    sp44 = jugador->velocidad[2];
    if (jugador->type & HUMANO_JUGADOR) {
        if (jugador->efectos & EFECTO_ESTRELLA) {
            actor->flags |= 0x400;
            funcion_800C98B8(jugador->pos, jugador->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x10));
            funcion_800C90F4(jugador - jugador_uno, (jugador->id_personaje * 0x10) + SONIDO_CARGA_PARAMETRO(0x29, 0x00, 0x80, 0x0D));
            return true;
        }
        if (!(jugador->type & INVISIBLE_JUGADOR_O_BOMBA)) {
            funcion_800C9060(jugador - jugador_uno, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x70, 0x18));
        }
    }
    if (!(jugador->efectos & EFECTO_ESTRELLA)) {
        jugador->efectos |= EFECTO_GOLPE_ENEMIGO;
    }
    actor_pos[0] = actor->pos[0];
    actor_pos[1] = actor->pos[1];
    actor_pos[2] = actor->pos[2];
    if (((id_circuito_actual == CIRCUITO_MARIO_RACEWAY) || (id_circuito_actual == CIRCUITO_YOSHI_VALLEY) ||
         (id_circuito_actual == CIRCUITO_ROYAL_RACEWAY) || (id_circuito_actual == CIRCUITO_LUIGI_RACEWAY)) &&
        (jugador->speed > 1.0f)) {
        aparecer_hoja(actor_pos, 0);
    }
    if (xz_dist < 0.1f) {
        sqrtf((sp48 * sp48) + (sp44 * sp44));
        if (xz_dist) {}
        jugador->velocidad[0] = 0;
        jugador->velocidad[2] = 0;
        jugador->pos[0] = actor_pos[0] - (x_dist * variable_f16 * 1.2f);
        jugador->pos[2] = actor_pos[2] - (z_dist * variable_f16 * 1.2f);
    } else {
        temporal_f0_4 = sqrtf((sp48 * sp48) + (sp44 * sp44));
        x_dist /= xz_dist;
        z_dist /= xz_dist;
        if (temporal_f0_4 < 0.25f) {
            jugador->pos[0] = actor_pos[0] - (x_dist * variable_f16 * 1.2f);
            jugador->pos[2] = actor_pos[2] - (z_dist * variable_f16 * 1.2f);
            jugador->velocidad[0] = 0;
            jugador->velocidad[2] = 0;
            return true;
        }
        temporal_f12 = ((x_dist * sp48) + (z_dist * sp44)) / temporal_f0_4;
        temporal_f12 = temporal_f0_4 * temporal_f12 * 1.5f;
        jugador->velocidad[0] -= x_dist * temporal_f12;
        jugador->velocidad[2] -= z_dist * temporal_f12;
        temporal_f2 = xz_dist - variable_f16;
        jugador->pos[0] += x_dist * temporal_f2 * 0.5f;
        jugador->pos[2] += z_dist * temporal_f2 * 0.5f;
    }
    return true;
}

bool consultar_jugador_colision_vs_item_actor(Jugador* parametro0, struct Actor* parametro1) {
    f32 temporal_f0;
    f32 dist;
    f32 y_dist_2;
    f32 z_dist_2;
    f32 x_dist_2;

    temporal_f0 = parametro0->tamanio_caja_envolvente + parametro1->tamanio_caja_envolvente;
    x_dist_2 = parametro1->pos[0] - parametro0->pos[0];
    if (temporal_f0 < x_dist_2) {
        return SIN_COLISION;
    }
    if (x_dist_2 < -temporal_f0) {
        return SIN_COLISION;
    }
    y_dist_2 = parametro1->pos[1] - parametro0->pos[1];
    if (temporal_f0 < y_dist_2) {
        return SIN_COLISION;
    }
    if (y_dist_2 < -temporal_f0) {
        return SIN_COLISION;
    }
    z_dist_2 = parametro1->pos[2] - parametro0->pos[2];
    if (temporal_f0 < z_dist_2) {
        return SIN_COLISION;
    }
    if (z_dist_2 < -temporal_f0) {
        return SIN_COLISION;
    }
    dist = (x_dist_2 * x_dist_2) + (y_dist_2 * y_dist_2) + (z_dist_2 * z_dist_2);
    if (dist < 0.1f) {
        return SIN_COLISION;
    }
    if ((temporal_f0 * temporal_f0) < dist) {
        return SIN_COLISION;
    }
    return COLISION;
}
