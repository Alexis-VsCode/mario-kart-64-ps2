// Trenes y barcos

#define LONGITUD_CAMINO_OBTENER(punto_camino)               \
    for (i = 0;; i++) {                          \
        if ((u16) punto_camino[i].pos_x == 0x8000) { \
            break;                               \
        }                                        \
    }

void generar_camino_tren(void) {
    s32 i;
    Camino2D* temporal_;
    PuntoCaminoPista* punto_camino =
        (PuntoCaminoPista*) VIRTUAL_A_PHYSICAL2(tabla_segmento[SEGMENT_NUMBER2(d_circuito_kalimari_desert_camino_tren)] +
                                               SEGMENT_OFFSET(d_circuito_kalimari_desert_camino_tren));

    LONGITUD_CAMINO_OBTENER(punto_camino)

    temporal_ = punto_camino_vehiculo_2d;
    longitud_camino_vehiculo_2d = generar_2d_camino(temporal_, punto_camino, i - 1);
    dato_80162EB0 = obtener_altura_superficie(temporal_[0].x, 2000.0f, temporal_[0].z);
}

void generar_camino_ferry(void) {
    PuntoCaminoPista* punto_camino;
    s32 i;

    punto_camino =
        (PuntoCaminoPista*) VIRTUAL_A_PHYSICAL2(tabla_segmento[SEGMENT_NUMBER2(d_circuito_dks_jungle_parkway_camino_ferry)] +
                                               (SEGMENT_OFFSET(d_circuito_dks_jungle_parkway_camino_ferry)));

    LONGITUD_CAMINO_OBTENER(punto_camino)

    longitud_camino_vehiculo_2d = generar_2d_camino(punto_camino_vehiculo_2d, punto_camino, i - 1);
    dato_80162EB2 = -40;
}

void aparecer_vehiculo_en_ruta(CosasVehiculo* vehiculo) {
    f32 orig_x_pos;
    SIN_USO f32 relleno;
    f32 orig_z_pos;

    orig_x_pos = vehiculo->position[0];
    orig_z_pos = vehiculo->position[2];
    if (es_en_extra == false) {
        funcion_8000D6D0(vehiculo->position, (s16*) &vehiculo->indice_punto_camino, vehiculo->speed,
                      vehiculo->algun_secuela_el_multiplicador, 0, 3);
        vehiculo->rotacion[0] = 0;
        vehiculo->rotacion[1] = -GRADOS(180);
        vehiculo->rotacion[2] = 0;
    } else {
        funcion_8000D940(vehiculo->position, (s16*) &vehiculo->indice_punto_camino, vehiculo->speed,
                      vehiculo->algun_secuela_el_multiplicador, 0);
        vehiculo->rotacion[0] = 0;
        vehiculo->rotacion[1] = 0;
        vehiculo->rotacion[2] = 0;
    }
    vehiculo->velocidad[0] = vehiculo->position[0] - orig_x_pos;
    vehiculo->velocidad[2] = vehiculo->position[2] - orig_z_pos;
}

void aparecer_vehiculos_circuito(void) {
    s16 rot_automovil_y_tren;
    SIN_USO Vec3f relleno;
    CosasAutomovilTren* locomotora_temporal;
    CosasAutomovilTren* tender_temporal;
    CosasAutomovilTren* automovil_pasajero_temporal;
    Vec3s rot_automovil_tren;
    CosasVehiculo* camion_caja_temporal;
    CosasVehiculo* omnibus_escuela_temporal;
    CosasVehiculo* camion_cisterna_temporal;
    CosasVehiculo* automovil_temporal;
    CosasBarcoPaleta* temporal_paleta_rueda_barco;
    Vec3s paleta_rueda_barco_rot;
    s32 indice_bucle;
    s32 indice_bucle_2;
    f32 orig_x_pos;
    f32 orig_z_pos;

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_KALAMARI_DESERT:
            for (indice_bucle = 0; indice_bucle < TRENES_NUM; indice_bucle++) {
                locomotora_temporal = &lista_tren[indice_bucle].locomotora;
                orig_x_pos = locomotora_temporal->position[0];
                orig_z_pos = locomotora_temporal->position[2];
                rot_automovil_y_tren = actualizar_camino_siguiente_vehiculo(
                    locomotora_temporal->position, (s16*) &locomotora_temporal->indice_punto_camino, lista_tren[indice_bucle].speed);
                locomotora_temporal->velocidad[0] = locomotora_temporal->position[0] - orig_x_pos;
                locomotora_temporal->velocidad[2] = locomotora_temporal->position[2] - orig_z_pos;
                fijar_vec3s(rot_automovil_tren, 0, rot_automovil_y_tren, 0);
                locomotora_temporal->indice_actor = agregar_actor_a_ranura_vacio(locomotora_temporal->position, rot_automovil_tren,
                                                                     locomotora_temporal->velocidad, MOTOR_TREN_ACTOR);

                tender_temporal = &lista_tren[indice_bucle].tender;
                if (tender_temporal->activo_es == 1) {
                    orig_x_pos = tender_temporal->position[0];
                    orig_z_pos = tender_temporal->position[2];
                    rot_automovil_y_tren = actualizar_camino_siguiente_vehiculo(
                        tender_temporal->position, (s16*) &tender_temporal->indice_punto_camino, lista_tren[indice_bucle].speed);
                    tender_temporal->velocidad[0] = tender_temporal->position[0] - orig_x_pos;
                    tender_temporal->velocidad[2] = tender_temporal->position[2] - orig_z_pos;
                    fijar_vec3s(rot_automovil_tren, 0, rot_automovil_y_tren, 0);
                    tender_temporal->indice_actor = agregar_actor_a_ranura_vacio(tender_temporal->position, rot_automovil_tren,
                                                                     tender_temporal->velocidad, TENDER_TREN_ACTOR);
                }

                for (indice_bucle_2 = 0; indice_bucle_2 < NUM_PASAJERO_AUTOMOVIL_ENTRADAS; indice_bucle_2++) {
                    automovil_pasajero_temporal = &lista_tren[indice_bucle].automoviles_pasajero[indice_bucle_2];
                    if (automovil_pasajero_temporal->activo_es == 1) {
                        orig_x_pos = automovil_pasajero_temporal->position[0];
                        orig_z_pos = automovil_pasajero_temporal->position[2];
                        rot_automovil_y_tren = actualizar_camino_siguiente_vehiculo(automovil_pasajero_temporal->position,
                                                                     (s16*) &automovil_pasajero_temporal->indice_punto_camino,
                                                                     lista_tren[indice_bucle].speed);
                        automovil_pasajero_temporal->velocidad[0] = automovil_pasajero_temporal->position[0] - orig_x_pos;
                        automovil_pasajero_temporal->velocidad[2] = automovil_pasajero_temporal->position[2] - orig_z_pos;
                        fijar_vec3s(rot_automovil_tren, 0, rot_automovil_y_tren, 0);
                        automovil_pasajero_temporal->indice_actor =
                            agregar_actor_a_ranura_vacio(automovil_pasajero_temporal->position, rot_automovil_tren, automovil_pasajero_temporal->velocidad,
                                                    ACTOR_TREN_PASAJERO_AUTOMOVIL);
                    }
                }
            }
            break;
        case CIRCUITO_DK_JUNGLE:
            for (indice_bucle = 0; indice_bucle < NUM_ACTIVO_PALETA_BARCOS; indice_bucle++) {
                temporal_paleta_rueda_barco = &barcos_paleta[indice_bucle];
                if (temporal_paleta_rueda_barco->activo_es == 1) {
                    orig_x_pos = temporal_paleta_rueda_barco->position[0];
                    orig_z_pos = temporal_paleta_rueda_barco->position[2];
                    temporal_paleta_rueda_barco->rot_y = actualizar_camino_siguiente_vehiculo(
                        temporal_paleta_rueda_barco->position, (s16*) &temporal_paleta_rueda_barco->indice_punto_camino,
                        temporal_paleta_rueda_barco->speed);
                    temporal_paleta_rueda_barco->velocidad[0] = temporal_paleta_rueda_barco->position[0] - orig_x_pos;
                    temporal_paleta_rueda_barco->velocidad[2] = temporal_paleta_rueda_barco->position[2] - orig_z_pos;
                    fijar_vec3s(paleta_rueda_barco_rot, 0, temporal_paleta_rueda_barco->rot_y, 0);
                    temporal_paleta_rueda_barco->indice_actor =
                        agregar_actor_a_ranura_vacio(temporal_paleta_rueda_barco->position, paleta_rueda_barco_rot,
                                                temporal_paleta_rueda_barco->velocidad, BARCO_PALETA_ACTOR);
                }
            }
            break;
        case CIRCUITO_TOADS_TURNPIKE:
            for (indice_bucle = 0; indice_bucle < NUM_CARRERA_CAJA_CAMIONES; indice_bucle++) {
                camion_caja_temporal = &lista_camion_caja[indice_bucle];
                aparecer_vehiculo_en_ruta(camion_caja_temporal);
                camion_caja_temporal->indice_actor = agregar_actor_a_ranura_vacio(camion_caja_temporal->position, camion_caja_temporal->rotacion,
                                                                   camion_caja_temporal->velocidad, CAMION_CAJA_ACTOR);
            }
            for (indice_bucle = 0; indice_bucle < NUM_CARRERA_ESCUELA_OMNIBUS; indice_bucle++) {
                omnibus_escuela_temporal = &lista_omnibus_escuela[indice_bucle];
                aparecer_vehiculo_en_ruta(omnibus_escuela_temporal);
                omnibus_escuela_temporal->indice_actor = agregar_actor_a_ranura_vacio(omnibus_escuela_temporal->position, omnibus_escuela_temporal->rotacion,
                                                                    omnibus_escuela_temporal->velocidad, OMNIBUS_ESCUELA_ACTOR);
            }
            for (indice_bucle = 0; indice_bucle < NUM_CARRERA_CISTERNA_CAMIONES; indice_bucle++) {
                camion_cisterna_temporal = &lista_camion_cisterna[indice_bucle];
                aparecer_vehiculo_en_ruta(camion_cisterna_temporal);
                camion_cisterna_temporal->indice_actor =
                    agregar_actor_a_ranura_vacio(camion_cisterna_temporal->position, camion_cisterna_temporal->rotacion,
                                            camion_cisterna_temporal->velocidad, CAMION_CISTERNA_ACTOR);
            }
            for (indice_bucle = 0; indice_bucle < AUTOMOVILES_CARRERA_NUM; indice_bucle++) {
                automovil_temporal = &lista_automovil[indice_bucle];
                aparecer_vehiculo_en_ruta(automovil_temporal);
                automovil_temporal->indice_actor =
                    agregar_actor_a_ranura_vacio(automovil_temporal->position, automovil_temporal->rotacion, automovil_temporal->velocidad, AUTOMOVIL_ACTOR);
            }
            break;
    }
#else

#endif
}

void fijar_vehiculo_pos_camino_punto(CosasAutomovilTren* automovil_tren, Camino2D* pos_xz, u16 punto_camino) {
    automovil_tren->position[0] = (f32) pos_xz->x;
    automovil_tren->position[1] = (f32) dato_80162EB0;
    automovil_tren->position[2] = (f32) pos_xz->z;
    automovil_tren->indice_actor = -1;
    automovil_tren->indice_punto_camino = punto_camino;
    automovil_tren->activo_es = 0;
    automovil_tren->velocidad[0] = 0.0f;
    automovil_tren->velocidad[1] = 0.0f;
    automovil_tren->velocidad[2] = 0.0f;
}

void inicializar_trenes_vehiculos(void) {
    u16 desplazamiento_punto_camino;
    CosasAutomovilTren* ptr1;
    Camino2D* pos;
    s32 i;
    s32 j;

    for (i = 0; i < TRENES_NUM; i++) {
        desplazamiento_punto_camino = (((i * longitud_camino_vehiculo_2d) / TRENES_NUM) + 160) % longitud_camino_vehiculo_2d;

        lista_tren[i].speed = 5.0f;
        for (j = 0; j < NUM_PASAJERO_AUTOMOVIL_ENTRADAS; j++) {
            desplazamiento_punto_camino += 4;
            ptr1 = &lista_tren[i].automoviles_pasajero[j];
            pos = &punto_camino_vehiculo_2d[desplazamiento_punto_camino];
            fijar_vehiculo_pos_camino_punto(ptr1, pos, desplazamiento_punto_camino);
        }
        desplazamiento_punto_camino += 3;
        ptr1 = &lista_tren[i].tender;
        pos = &punto_camino_vehiculo_2d[desplazamiento_punto_camino];
        fijar_vehiculo_pos_camino_punto(ptr1, pos, desplazamiento_punto_camino);

        desplazamiento_punto_camino += 4;
        ptr1 = &lista_tren[i].locomotora;
        pos = &punto_camino_vehiculo_2d[desplazamiento_punto_camino];
        fijar_vehiculo_pos_camino_punto(ptr1, pos, desplazamiento_punto_camino);

        lista_tren[i].automoviles_num = SOLO_LOCOMOTORA;
    }

    switch (seleccion_modo_pantalla) {
        case MODO_PANTALLA_1P:
            for (i = 0; i < TRENES_NUM; i++) {
                lista_tren[i].tender.activo_es = 1;

                for (j = 0; j < NUM_PASAJERO_AUTOMOVIL_ENTRADAS; j++) { lista_tren[i].automoviles_pasajero[j].activo_es = 1; }

                lista_tren[i].automoviles_num = NUM_TENDERS + NUM_PASAJERO_AUTOMOVIL_ENTRADAS;
            }
            break;

        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL: // multiplayer fall-through
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            if (seleccion_modo != GRAN_PREMIO) {
                for (i = 0; i < TRENES_NUM; i++) {
                    lista_tren[i].tender.activo_es = 1;
                    lista_tren[i].automoviles_pasajero[4].activo_es = 1;
                    lista_tren[i].automoviles_num = NUM_TENDERS + AUTOMOVILES_PASAJERO_NUM_2J;
                }
            }
            break;
    }

    temporizador_humo_tren = 0;
}
void sincronizar_componentes_tren(CosasAutomovilTren* automovil_tren, s16 orientacion_y) {
    struct AutomovilTren* actor_automovil_tren;

    actor_automovil_tren = (struct AutomovilTren*) &lista_actor[automovil_tren->indice_actor];
    actor_automovil_tren->pos[0] = automovil_tren->position[0];
    actor_automovil_tren->pos[1] = automovil_tren->position[1];
    actor_automovil_tren->pos[2] = automovil_tren->position[2];
    if (es_modo_espejo != 0) {
        actor_automovil_tren->rot[1] = -orientacion_y;
    } else {
        actor_automovil_tren->rot[1] = orientacion_y;
    }
    actor_automovil_tren->velocidad[0] = automovil_tren->velocidad[0];
    actor_automovil_tren->velocidad[2] = automovil_tren->velocidad[2];
}

void actualizar_trenes_vehiculo(void) {
    SIN_USO s32 relleno[3];
    f32 temporal_f20;
    CosasAutomovilTren* automovil;
    u16 viejo_camino_punto_indice;
    s16 actualizacion_orientacion_y;
    f32 temporal_f22;
    s32 i;
    s32 j;
    Vec3f pos_humo;

    temporizador_humo_tren += 1;

    for (i = 0; i < TRENES_NUM; i++) {
        viejo_camino_punto_indice = (u16) lista_tren[i].locomotora.indice_punto_camino;

        temporal_f20 = lista_tren[i].locomotora.position[0];
        temporal_f22 = lista_tren[i].locomotora.position[2];

        actualizacion_orientacion_y = actualizar_camino_siguiente_vehiculo(
            lista_tren[i].locomotora.position, (s16*) &lista_tren[i].locomotora.indice_punto_camino, lista_tren[i].speed);

        lista_tren[i].locomotora.velocidad[0] = lista_tren[i].locomotora.position[0] - temporal_f20;
        lista_tren[i].locomotora.velocidad[2] = lista_tren[i].locomotora.position[2] - temporal_f22;

        sincronizar_componentes_tren(&lista_tren[i].locomotora, actualizacion_orientacion_y);

        if ((viejo_camino_punto_indice != lista_tren[i].locomotora.indice_punto_camino) &&
            ((lista_tren[i].locomotora.indice_punto_camino == 0x00BE) ||
             (lista_tren[i].locomotora.indice_punto_camino == 0x0140))) {
            funcion_800C98B8(lista_tren[i].locomotora.position, lista_tren[i].locomotora.velocidad,
                          SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x0E));
        } else if (int_aleatorio(100) == 0) {
            funcion_800C98B8(lista_tren[i].locomotora.position, lista_tren[i].locomotora.velocidad,
                          SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x0D));
        }

        lista_tren[i].algun_banderas = renderizar_banderas_distancia_vehiculo_conjunto(
            lista_tren[i].locomotora.position, TREN_HUMO_RENDER_DISTANCIA, lista_tren[i].algun_banderas);
        if ((((s16) temporizador_humo_tren % 5) == 0) && (lista_tren[i].algun_banderas != 0)) {
            pos_humo[0] = lista_tren[i].locomotora.position[0];
            pos_humo[1] = (f32) ((f64) lista_tren[i].locomotora.position[1] + 65.0);
            pos_humo[2] = (f32) ((f64) lista_tren[i].locomotora.position[2] + 25.0);
            ajustar_posicion_por_angulo(pos_humo, lista_tren[i].locomotora.position, actualizacion_orientacion_y);
            aparecer_humo_tren(i, pos_humo, 1.1f);
        }

        automovil = &lista_tren[i].tender;

        if (automovil->activo_es == 1) {
            temporal_f20 = automovil->position[0];
            temporal_f22 = automovil->position[2];
            actualizacion_orientacion_y =
                actualizar_camino_siguiente_vehiculo(automovil->position, (s16*) &automovil->indice_punto_camino, lista_tren[i].speed);
            automovil->velocidad[0] = automovil->position[0] - temporal_f20;
            automovil->velocidad[2] = automovil->position[2] - temporal_f22;
            sincronizar_componentes_tren(automovil, actualizacion_orientacion_y);
        }

        for (j = 0; j < NUM_PASAJERO_AUTOMOVIL_ENTRADAS; j++) {
            automovil = &lista_tren[i].automoviles_pasajero[j];
            if (automovil->activo_es == 1) {
                temporal_f20 = automovil->position[0];
                temporal_f22 = automovil->position[2];

                actualizacion_orientacion_y =
                    actualizar_camino_siguiente_vehiculo(automovil->position, (s16*) &automovil->indice_punto_camino, lista_tren[i].speed);
                automovil->velocidad[0] = automovil->position[0] - temporal_f20;
                automovil->velocidad[2] = automovil->position[2] - temporal_f22;
                sincronizar_componentes_tren(automovil, actualizacion_orientacion_y);
            }
        }
    }
}

void manejar_interacciones_trenes(s32 id_jugador, Jugador* jugador) {
    CosasAutomovilTren* automovil_tren;
    f32 pos_x_jugador;
    f32 pos_z_jugador;
    f32 x_dist;
    f32 z_dist;
    s32 indice_tren;
    s32 indice_automovil_pasajero;

    if (dato_801631E0[id_jugador] != true) {
        if (!(jugador->efectos & EFECTO_ERROR_EXPLOSION)) {
            pos_x_jugador = jugador->pos[0];
            pos_z_jugador = jugador->pos[2];
            for (indice_tren = 0; indice_tren < TRENES_NUM; indice_tren++) {
                automovil_tren = &lista_tren[indice_tren].locomotora;
                x_dist = pos_x_jugador - automovil_tren->position[0];
                z_dist = pos_z_jugador - automovil_tren->position[2];
                if ((x_dist > -100.0) && (x_dist < 100.0)) {
                    if ((z_dist > -100.0) && (z_dist < 100.0)) {
                        if (chocar_con_vehiculo_es(automovil_tren->position[0], automovil_tren->position[2], automovil_tren->velocidad[0],
                                                    automovil_tren->velocidad[2], 60.0f, 20.0f, pos_x_jugador, pos_z_jugador) == 1) {
                            jugador->disparadores |= DISPARADOR_VUELCO_VERTICAL;
                        }
                        automovil_tren = &lista_tren[indice_tren].tender;
                        if (automovil_tren->activo_es == 1) {
                            if (chocar_con_vehiculo_es(automovil_tren->position[0], automovil_tren->position[2],
                                                        automovil_tren->velocidad[0], automovil_tren->velocidad[2], 30.0f, 20.0f,
                                                        pos_x_jugador, pos_z_jugador) == 1) {
                                jugador->disparadores |= DISPARADOR_VUELCO_VERTICAL;
                            }
                        }
                    }
                }

                for (indice_automovil_pasajero = 0; indice_automovil_pasajero < NUM_PASAJERO_AUTOMOVIL_ENTRADAS; indice_automovil_pasajero++) {
                    automovil_tren = &lista_tren[indice_tren].automoviles_pasajero[indice_automovil_pasajero];
                    x_dist = pos_x_jugador - automovil_tren->position[0];
                    z_dist = pos_z_jugador - automovil_tren->position[2];
                    if (automovil_tren->activo_es == 1) {
                        if ((x_dist > -100.0) && (x_dist < 100.0)) {
                            if ((z_dist > -100.0) && (z_dist < 100.0)) {
                                if (chocar_con_vehiculo_es(automovil_tren->position[0], automovil_tren->position[2],
                                                            automovil_tren->velocidad[0], automovil_tren->velocidad[2], 30.0f, 20.0f,
                                                            pos_x_jugador, pos_z_jugador) == 1) {
                                    jugador->disparadores |= DISPARADOR_VUELCO_VERTICAL;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void funcion_80013054(void) {
    f32 temporal_f16;
    f32 temporal_f18;
    f32 temporal_f12;
    s32 i;
    es_cruce_disparado_por_indice[0] = 0;
    es_cruce_disparado_por_indice[1] = 0;

    for (i = 0; i < TRENES_NUM; i++) {
        temporal_f16 = lista_tren[i].locomotora.indice_punto_camino / ((f32) longitud_camino_vehiculo_2d);
        temporal_f18 = 0.72017354f;
        temporal_f12 = 0.42299348f;

        if (((temporal_f12 - 0.1) < temporal_f16) &&
            (temporal_f16 < ((((f64) lista_tren[i].automoviles_num) * 0.01) + (temporal_f12 + 0.01)))) {

            es_cruce_disparado_por_indice[0] = 1;
        }
        if (((temporal_f18 - 0.1) < temporal_f16) &&
            (temporal_f16 < ((((f64) lista_tren[i].automoviles_num) * 0.01) + (temporal_f18 + 0.01)))) {

            es_cruce_disparado_por_indice[1] = 1;
        }
    }

    for (i = 0; i < CRUCES_NUM; i++) {
        if (es_cruce_disparado_por_indice[i] == 1) {
            temporizador_activo_cruce[i] += 1;
        } else {
            temporizador_activo_cruce[i] = 0;
        }
    }
}

void comprobar_distancia_cruce_ai(s32 id_jugador) {
    b_parada_ai_cruce[id_jugador] = 0;
    if (id_circuito_actual == CIRCUITO_KALAMARI_DESERT) {
        if ((!(dato_801631E0[id_jugador] != false)) ||
            (renderizar_banderas_distancia_vehiculo_conjunto(jugadores[id_jugador].pos, TREN_CRUCE_AI_DISTANCIA, 0))) {

            if ((es_cruce_disparado_por_indice[1] == 1) && ((temporizador_activo_cruce[1]) > FRAMES_DESDE_CRUCE_ACTIVADO)) {

                if ((algun_punto_camino_mas_cercano > 176) && (algun_punto_camino_mas_cercano < 182)) {
                    b_parada_ai_cruce[id_jugador] = 1;
                }
            }
            if ((es_cruce_disparado_por_indice[0] == 1) && ((temporizador_activo_cruce[0]) > FRAMES_DESDE_CRUCE_ACTIVADO)) {
                if ((algun_punto_camino_mas_cercano >= 306) && (algun_punto_camino_mas_cercano < 310)) {
                    b_parada_ai_cruce[id_jugador] = 1;
                }
            }
        }
    }
}

void inicializar_ferry_vehiculos(void) {
    CosasBarcoPaleta* barco_paleta;
    s32 i;
    Camino2D* temporal_a2;
    u16 temporal_;
    for (i = 0; i < NUM_ACTIVO_PALETA_BARCOS; i++) {
        temporal_ = i * 0xB4;
        barco_paleta = &barcos_paleta[i];
        temporal_a2 = &punto_camino_vehiculo_2d[temporal_];
        barco_paleta->position[0] = temporal_a2->x;
        barco_paleta->position[1] = dato_80162EB2;
        barco_paleta->position[2] = temporal_a2->z;
        barco_paleta->indice_punto_camino = i * 0xB4;
        barco_paleta->indice_actor = -1;

        if (cantidad_jugador >= 3) {
            barco_paleta->activo_es = 0;
        } else {
            barco_paleta->activo_es = 1;
        }
        barco_paleta->velocidad[0] = 0.0f;
        barco_paleta->velocidad[1] = 0.0f;
        barco_paleta->velocidad[2] = 0.0f;
        barco_paleta->speed = 1.6666666f;
        barco_paleta->rot_y = 0;
    }
    temporizador_humo_ferry = 0;
}

void actualizar_barcos_paleta_vehiculo(void) {
    CosasBarcoPaleta* barco_paleta;
    Camino2D* punto_camino;
    s32 i;
    struct Actor* actor_barco_paleta;
    f32 temporal_f26;
    f32 temporal_f28;
    f32 temporal_f30;
    s16 temporal_a1;
    s32 temporal_;
    s16 variable_v1;
    Vec3f sp94;
    Vec3f sp88;
    SIN_USO s32 relleno;
    Vec3f pos_humo;
    SIN_USO s32 relleno2;
    temporizador_humo_ferry += 1;
    for (i = 0; i < NUM_ACTIVO_PALETA_BARCOS; i++) {
        barco_paleta = &barcos_paleta[i];
        if (barco_paleta->activo_es == 1) {
            temporal_f26 = barco_paleta->position[0];
            temporal_f28 = barco_paleta->position[1];
            temporal_f30 = barco_paleta->position[2];
            actualizar_camino_siguiente_vehiculo(barco_paleta->position, (s16*) &barco_paleta->indice_punto_camino, barco_paleta->speed);
            barco_paleta->algun_banderas = renderizar_banderas_distancia_vehiculo_conjunto(barco_paleta->position, BARCO_HUMO_RENDER_DISTANCIA,
                                                                      barco_paleta->algun_banderas);
            if ((((s16) temporizador_humo_ferry % 10) == 0) && (barco_paleta->algun_banderas != 0)) {
                pos_humo[0] = (f32) ((f64) barco_paleta->position[0] - 30.0);
                pos_humo[1] = (f32) ((f64) barco_paleta->position[1] + 180.0);
                pos_humo[2] = (f32) ((f64) barco_paleta->position[2] + 45.0);
                ajustar_posicion_por_angulo(pos_humo, barco_paleta->position, barco_paleta->rot_y);
                aparecer_humo_ferry(i, pos_humo, 1.1f);
                pos_humo[0] = (f32) ((f64) barco_paleta->position[0] + 30.0);
                pos_humo[1] = (f32) ((f64) barco_paleta->position[1] + 180.0);
                pos_humo[2] = (f32) ((f64) barco_paleta->position[2] + 45.0);
                ajustar_posicion_por_angulo(pos_humo, barco_paleta->position, barco_paleta->rot_y);
                aparecer_humo_ferry(i, pos_humo, 1.1f);
            }
            if (int_aleatorio(100) == 0) {
                if (int_aleatorio(2) == 0) {
                    funcion_800C98B8(barco_paleta->position, barco_paleta->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x47));
                } else {
                    funcion_800C98B8(barco_paleta->position, barco_paleta->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x80, 0x48));
                }
            }
            sp94[0] = temporal_f26;
            sp94[1] = temporal_f28;
            sp94[2] = temporal_f30;
            punto_camino = &punto_camino_vehiculo_2d[(barco_paleta->indice_punto_camino + 5) % longitud_camino_vehiculo_2d];
            sp88[0] = (f32) punto_camino->x;
            sp88[1] = (f32) dato_80162EB0;
            sp88[2] = (f32) punto_camino->z;
            temporal_a1 = obtener_angulo_entre_camino(sp94, sp88);
            temporal_ = temporal_a1 - barco_paleta->rot_y;
            variable_v1 = temporal_;
            if (variable_v1 < 0) {
                variable_v1 = -variable_v1;
            }
            if (variable_v1 >= 0x1771) {
                if (barco_paleta->speed > 0.2) {
                    barco_paleta->speed -= 0.04;
                }
                if (variable_v1 >= 0x3D) {
                    variable_v1 = 0x003C;
                }
            } else {
                if (barco_paleta->speed < 2.0) {
                    barco_paleta->speed += 0.02;
                }
                if (variable_v1 >= 0x1F) {
                    variable_v1 = 0x001E;
                }
            }
            if (temporal_ >= 0x8000) {
                barco_paleta->rot_y -= variable_v1;
            } else if (temporal_ > 0) {
                barco_paleta->rot_y += variable_v1;
            } else if (temporal_ < -0x7FFF) {
                barco_paleta->rot_y += variable_v1;
            } else if (temporal_ < 0) {
                barco_paleta->rot_y -= variable_v1;
            }
            barco_paleta->velocidad[0] = barco_paleta->position[0] - temporal_f26;
            barco_paleta->velocidad[1] = barco_paleta->position[1] - temporal_f28;
            barco_paleta->velocidad[2] = barco_paleta->position[2] - temporal_f30;
            actor_barco_paleta = &lista_actor[barco_paleta->indice_actor];
            actor_barco_paleta->pos[0] = barco_paleta->position[0];
            actor_barco_paleta->pos[1] = barco_paleta->position[1];
            actor_barco_paleta->pos[2] = barco_paleta->position[2];
            if (es_modo_espejo != 0) {
                actor_barco_paleta->rot[1] = -barco_paleta->rot_y;
            } else {
                actor_barco_paleta->rot[1] = barco_paleta->rot_y;
            }
            actor_barco_paleta->velocidad[0] = barco_paleta->velocidad[0];
            actor_barco_paleta->velocidad[1] = barco_paleta->velocidad[1];
            actor_barco_paleta->velocidad[2] = barco_paleta->velocidad[2];
        }
    }
}

void manejar_interacciones_barcos_paleta(Jugador* jugador) {
    s32 algun_indice;
    CosasBarcoPaleta* temporal_paleta_rueda_barco;
    f32 dif_x;
    f32 dif_y;
    f32 dif_z;
    f32 jugador_x;
    f32 jugador_z;
    f32 jugador_y;

    if (!((jugador->efectos & EFECTO_ERROR_EXPLOSION)) && (!(jugador->efectos & GOLPE_POR_EFECTO_ESTRELLA))) {
        jugador_x = jugador->pos[0];
        jugador_y = jugador->pos[1];
        jugador_z = jugador->pos[2];
        for (algun_indice = 0; algun_indice < NUM_ACTIVO_PALETA_BARCOS; algun_indice++) {
            temporal_paleta_rueda_barco = &barcos_paleta[algun_indice];
            if (temporal_paleta_rueda_barco->activo_es == 1) {
                dif_x = jugador_x - temporal_paleta_rueda_barco->position[0];
                dif_y = jugador_y - temporal_paleta_rueda_barco->position[1];
                dif_z = jugador_z - temporal_paleta_rueda_barco->position[2];
                if ((dif_x > -300.0) && (dif_x < 300.0)) {
                    if ((dif_z > -300.0) && (dif_z < 300.0)) {
                        if ((chocar_con_vehiculo_es(temporal_paleta_rueda_barco->position[0], temporal_paleta_rueda_barco->position[2],
                                                     temporal_paleta_rueda_barco->velocidad[0], temporal_paleta_rueda_barco->velocidad[2],
                                                     200.0f, 60.0f, jugador_x, jugador_z) == 1) &&
                            (dif_y < 60.0)) {
                            jugador->disparadores |= GOLPE_PALETA_BARCO_DISPARADOR;
                        }
                    }
                }
            }
        }
    }
}

void inicializar_toads_turnpike_vehiculo(f32 rapidez_a, f32 rapidez_b, s32 vehiculos_num, s32 parametro3, CosasVehiculo* lista_vehiculo,
                                       PuntoCaminoPista* lista_punto_camino) {
    CosasVehiculo* veh;
    PuntoCaminoPista* temporal_v0;
    s32 i;
    u16 desplazamiento_punto_camino;
    s32 puntos_camino_num = cantidad_camino_por_indice_camino[0];
    for (i = 0; i < vehiculos_num; i++) {
        desplazamiento_punto_camino = (((i * puntos_camino_num) / vehiculos_num) + parametro3) % puntos_camino_num;
        veh = &lista_vehiculo[i];
        temporal_v0 = &lista_punto_camino[desplazamiento_punto_camino];
        veh->position[0] = (f32) temporal_v0->pos_x;
        veh->position[1] = (f32) temporal_v0->pos_y;
        veh->position[2] = (f32) temporal_v0->pos_z;
        veh->indice_actor = -1;
        veh->indice_punto_camino = desplazamiento_punto_camino;
        veh->unused = 0;
        veh->velocidad[0] = 0.0f;
        veh->velocidad[1] = 0.0f;
        veh->velocidad[2] = 0.0f;
        veh->algun_banderas = 0;
        veh->algun_secuela_el_banderas = 0;
        if (seleccion_modo == CONTRARRELOJ) {
            veh->algun_tipo = (i % 3);
        } else {
            veh->algun_tipo = int_aleatorio(3);
        }
        veh->algun_secuela_el_multiplicador = (f32) ((f64) (f32) (veh->algun_tipo - 1) * 0.6);
        if (((seleccion_cc > CC_50) || (seleccion_modo == CONTRARRELOJ)) && (veh->algun_tipo == 2)) {
            veh->speed = rapidez_a;
        } else {
            veh->speed = rapidez_b;
        }
        veh->rotacion[0] = 0;
        veh->rotacion[2] = 0;
        if (es_en_extra == false) {
            veh->rotacion[1] = funcion_8000D6D0(veh->position, (s16*) &veh->indice_punto_camino, veh->speed,
                                             veh->algun_secuela_el_multiplicador, 0, 3);
        } else {
            veh->rotacion[1] =
                funcion_8000D940(veh->position, (s16*) &veh->indice_punto_camino, veh->speed, veh->algun_secuela_el_multiplicador, 0);
        }
    }
    vehiculo_sonido_render_contador = 10;
}

f32 funcion_80013C74(s16 algun_tipo, s16 indice_punto_camino) {
    f32 variable_f2;

    variable_f2 = 0.0f;
    if (indice_punto_camino < 0x28A) {
        switch (algun_tipo) {
            case 0:
                variable_f2 = -0.7f;
                break;
            case 1:
                break;
            case 2:
                variable_f2 = 0.7f;
                break;
            default:
                break;
        }
    } else {
        switch (algun_tipo) {
            case 0:
            case 1:
                variable_f2 = -0.5f;
                break;
            case 2:
                variable_f2 = 0.5f;
                break;
            default:
                break;
        }
    }
    return variable_f2;
}

void actualizar_vehiculo_seguir_camino_punto(CosasVehiculo* vehiculo) {
    f32 temporal_f0_2;
    f32 temporal_f0_3;
    f32 sp5_c;
    f32 sp58;
    f32 sp54;
    f32 temporal_f2_2;
    s16 variable_a1;
    s16 cosa;
    Vec3f sp40;
    Vec3f sp34;
    struct Actor* actor_vehiculo;

    sp5_c = vehiculo->position[0];
    sp58 = vehiculo->position[1];
    sp54 = vehiculo->position[2];
    sp40[0] = sp58;
    sp40[1] = 0.0f;
    sp40[2] = 0.0f;
    temporal_f0_2 = funcion_80013C74(vehiculo->algun_tipo, vehiculo->indice_punto_camino);
    if (vehiculo->algun_secuela_el_multiplicador < temporal_f0_2) {
        vehiculo->algun_secuela_el_multiplicador = vehiculo->algun_secuela_el_multiplicador + 0.06;
        if (temporal_f0_2 < vehiculo->algun_secuela_el_multiplicador) {
            vehiculo->algun_secuela_el_multiplicador = temporal_f0_2;
        }
    }
    if (temporal_f0_2 < vehiculo->algun_secuela_el_multiplicador) {
        vehiculo->algun_secuela_el_multiplicador = vehiculo->algun_secuela_el_multiplicador - 0.06;
        if (vehiculo->algun_secuela_el_multiplicador < temporal_f0_2) {
            vehiculo->algun_secuela_el_multiplicador = temporal_f0_2;
        }
    }
    if (es_en_extra == false) {
        variable_a1 = funcion_8000D6D0(vehiculo->position, (s16*) &vehiculo->indice_punto_camino, vehiculo->speed,
                               vehiculo->algun_secuela_el_multiplicador, 0, 3);
    } else {
        variable_a1 = funcion_8000D940(vehiculo->position, (s16*) &vehiculo->indice_punto_camino, vehiculo->speed,
                               vehiculo->algun_secuela_el_multiplicador, 0);
    }
    ajustar_angulo(&vehiculo->rotacion[1], variable_a1, 100);
    temporal_f0_3 = vehiculo->position[0] - sp5_c;
    temporal_f2_2 = vehiculo->position[2] - sp54;
    sp34[0] = vehiculo->position[1];
    sp34[1] = 0.0f;
    sp34[2] = sqrtf((temporal_f0_3 * temporal_f0_3) + (temporal_f2_2 * temporal_f2_2));
    cosa = obtener_angulo_xz_entre_puntos(sp40, sp34);
    ajustar_angulo(&vehiculo->rotacion[0], -cosa, 100);
    vehiculo->velocidad[0] = vehiculo->position[0] - sp5_c;
    vehiculo->velocidad[1] = vehiculo->position[1] - sp58;
    vehiculo->velocidad[2] = vehiculo->position[2] - sp54;
    actor_vehiculo = &lista_actor[vehiculo->indice_actor];
    actor_vehiculo->pos[0] = vehiculo->position[0];
    actor_vehiculo->pos[1] = vehiculo->position[1];
    actor_vehiculo->pos[2] = vehiculo->position[2];
    actor_vehiculo->rot[0] = vehiculo->rotacion[0];
    if (es_modo_espejo != 0) {
        actor_vehiculo->rot[1] = -vehiculo->rotacion[1];
    } else {
        actor_vehiculo->rot[1] = vehiculo->rotacion[1];
    }
    actor_vehiculo->rot[2] = vehiculo->rotacion[2];
    actor_vehiculo->velocidad[0] = vehiculo->velocidad[0];
    actor_vehiculo->velocidad[1] = vehiculo->velocidad[1];
    actor_vehiculo->velocidad[2] = vehiculo->velocidad[2];
}

void manejar_interacciones_vehiculo(s32 id_jugador, Jugador* jugador, CosasVehiculo* vehiculo, f32 distancia_x, f32 distancia_y,
                                 s32 cantidad_vehiculo, u32 sonido_bits) {
    f32 delta_x;
    f32 delta_z;
    f32 delta_y;

    s32 i;

    f32 jugador_x;
    f32 jugador_y;
    f32 jugador_z;

    if (((dato_801631E0[id_jugador] != true) || ((((jugador->type & HUMANO_JUGADOR) != 0)) && !(jugador->type & CPU_JUGADOR))) &&
        !(jugador->efectos & EFECTO_ERROR_EXPLOSION)) {

        jugador_x = jugador->pos[0];
        jugador_y = jugador->pos[1];
        jugador_z = jugador->pos[2];

        for (i = 0; i < cantidad_vehiculo; i++) {
            delta_x = jugador_x - vehiculo->position[0];
            delta_y = jugador_y - vehiculo->position[1];
            delta_z = jugador_z - vehiculo->position[2];

            if (((delta_x) > -100.0) && ((delta_x) < 100.0)) {
                if ((delta_y > -20.0) && (delta_y < 20.0)) {
                    if (((delta_z) > -100.0) && ((delta_z) < 100.0)) {
                        if (chocar_con_vehiculo_es(vehiculo->position[0], vehiculo->position[2], vehiculo->velocidad[0],
                                                    vehiculo->velocidad[2], distancia_x, distancia_y, jugador_x,
                                                    jugador_z) == (s32) 1) {
                            jugador->disparadores |= DISPARADOR_VUELCO_VERTICAL;
                        }
                    }
                }
            }

            if ((jugador->type & HUMANO_JUGADOR) && !(jugador->type & CPU_JUGADOR)) {
                if (((delta_x) > -300.0) && ((delta_x) < 300.0) && ((delta_y > -20.0)) && (delta_y < 20.0) &&
                    (((delta_z) > -300.0)) && ((delta_z) < 300.0)) {
                    if ((vehiculo_sonido_render_contador > 0) && (vehiculo->algun_banderas == 0)) {
                        vehiculo_sonido_render_contador--;
                        vehiculo->algun_banderas |= (VEHICULO_RENDER << id_jugador);
                        funcion_800C9D80(vehiculo->position, vehiculo->velocidad, sonido_bits);
                    }
                } else {
                    if (vehiculo->algun_banderas != 0) {
                        vehiculo->algun_banderas &= ~(VEHICULO_RENDER << id_jugador);
                        if (vehiculo->algun_banderas == 0) {
                            vehiculo_sonido_render_contador++;
                            funcion_800C9EF4(vehiculo->position, sonido_bits);
                        }
                    }
                }

                if (((delta_x) > -200.0) && ((delta_x) < 200.0) && ((delta_y > -20.0)) && (delta_y < 20.0) &&
                    (((delta_z) > -200.0)) && ((delta_z) < 200.0)) {
                    if (!(vehiculo->algun_secuela_el_banderas & ((1 << id_jugador)))) {

                        bool debe_interactuar = false;
                        u16 path = cantidad_camino_por_indice_camino[0];
                        s32 t1;
                        s32 t2;

                        switch (es_en_extra) {
                            case false:
                                t1 = es_punto_camino_en_rango(vehiculo->indice_punto_camino,
                                                            punto_camino_mas_cercano_por_id_jugador[id_jugador], 10, 0, path);
                                if ((es_sentido_incorrecto_jugador[id_jugador] == 0) && (t1 > 0) &&
                                    (jugador->speed < vehiculo->speed)) {
                                    debe_interactuar = true;
                                }
                                if ((es_sentido_incorrecto_jugador[id_jugador] == 1) && (t1 > 0)) {
                                    debe_interactuar = true;
                                }
                                break;
                            case true:
                                t2 = es_punto_camino_en_rango(vehiculo->indice_punto_camino,
                                                            punto_camino_mas_cercano_por_id_jugador[id_jugador], 0, 10, path);
                                if (t2 > 0) {
                                    if (int_aleatorio(2) == 0) {
                                        if (es_sentido_incorrecto_jugador[id_jugador] == 0) {
                                            debe_interactuar = true;
                                        }
                                        if ((es_sentido_incorrecto_jugador[id_jugador] == 1) &&
                                            (jugador->speed < vehiculo->speed)) {
                                            debe_interactuar = true;
                                        }
                                    } else {
                                        vehiculo->algun_secuela_el_banderas |= ((1 << id_jugador));
                                    }
                                }
                                break;
                        }
                        if (debe_interactuar == true) {

                            u32 sonido_bits_2 = SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x3B);

                            switch (sonido_bits) {
                                case SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x05):
                                    sonido_bits_2 = SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x3B);
                                    if (int_aleatorio(4) == 0) {
                                        sonido_bits_2 = SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x3C);
                                    }
                                    break;
                                case SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x02):
                                    if (int_aleatorio(2) != 0) {
                                        sonido_bits_2 = SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x3D);
                                    } else {
                                        sonido_bits_2 = SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x3E);
                                    }
                                    break;
                                case SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x03):
                                    if (int_aleatorio(2) != 0) {
                                        sonido_bits_2 = SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x3F);
                                    } else {
                                        sonido_bits_2 = SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x40);
                                    }
                                    break;
                                case SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x04):
                                    if (int_aleatorio(2) != 0) {
                                        sonido_bits_2 = SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x41);
                                    } else {
                                        sonido_bits_2 = SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x42);
                                    }
                                    break;
                            }
                            vehiculo->algun_secuela_el_banderas |= ((1 << id_jugador));
                            funcion_800C98B8(vehiculo->position, vehiculo->velocidad, sonido_bits_2);
                        }
                    }
                } else {
                    if (vehiculo->algun_secuela_el_banderas & ((1 << id_jugador))) {
                        vehiculo->algun_secuela_el_banderas &= ~((1 << id_jugador));
                    }
                }
            }
            vehiculo++;
        }
    }
}
