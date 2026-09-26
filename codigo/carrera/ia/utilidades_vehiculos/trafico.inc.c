// Trafico

f32 jugador_pista_posicion_factor_vehiculo(s16 algun_tipo, f32 parametro1, s16 indice_camino) {
    if (indice_camino < 0x28A) {
        switch (algun_tipo) {
            case 0:
                if (parametro1 < 0.0) {
                    parametro1 = 0.0f;
                }
                break;
            case 1:
                if (parametro1 < 0.0) {
                    parametro1 = -0.8f;
                } else {
                    parametro1 = 0.8f;
                }
                break;
            case 2:
                if (parametro1 >= 0.0) {
                    parametro1 = 0.0f;
                }
                break;
            default:
                break;
        }
    } else {
        switch (algun_tipo) {
            case 0:
            case 1:
                parametro1 = 0.5f;
                break;
            case 2:
                parametro1 = -0.5f;
                break;
            default:
                break;
        }
    }
    return parametro1;
}

void actualizar_jugador_pista_posicion_factor_desde_vehiculo(s32 id_jugador, s32 cantidad_vehiculo, CosasVehiculo* vehiculo) {
    SIN_USO s32 variable_v1;
    s32 desplazamiento_punto_camino;
    s32 variable_s2;
    s32 cantidad_punto_camino;
    u16 punto_camino_vehiculo;
    SIN_USO CosasVehiculo* vehiculo_temporal;

    cantidad_punto_camino = cantidad_camino_por_indice_camino[0];
    if (!(jugadores[id_jugador].speed < 1.6666666666666667)) {
        for (variable_s2 = 0; variable_s2 < cantidad_vehiculo; variable_s2++, vehiculo++) {
            punto_camino_vehiculo = vehiculo->indice_punto_camino;
            for (desplazamiento_punto_camino = 0; desplazamiento_punto_camino < 0x18; desplazamiento_punto_camino += 3) {
                if (((algun_punto_camino_mas_cercano + desplazamiento_punto_camino) % cantidad_punto_camino) == punto_camino_vehiculo) {
                    jugador_pista_posicion_factor_instruccion[id_jugador].target = jugador_pista_posicion_factor_vehiculo(
                        vehiculo->algun_tipo, factor_posicion_pista[id_jugador], punto_camino_vehiculo);
                    return;
                }
            }
        }
    }
}

void inicializar_camiones_caja_vehiculos(void) {
    f32 a = ((seleccion_cc * 90.0) / 216.0f) + 4.583333333333333;
    f32 b = ((seleccion_cc * 90.0) / 216.0f) + 2.9166666666666665;
    s32 camiones_num = NUM_CARRERA_CAJA_CAMIONES;
    if (seleccion_modo == CONTRARRELOJ) {
        camiones_num = NUM_CONTRARRELOJ_CAMIONES_CAJA;
    }
    inicializar_toads_turnpike_vehiculo(a, b, camiones_num, 0, lista_camion_caja, &caminos_pista[0][0]);
}

void actualizar_camiones_caja_vehiculo(void) {
    s32 indice_bucle;
    for (indice_bucle = 0; indice_bucle < NUM_CARRERA_CAJA_CAMIONES; indice_bucle++) {
        actualizar_vehiculo_seguir_camino_punto(&lista_camion_caja[indice_bucle]);
    }
}

void manejar_interacciones_camiones_caja(s32 id_jugador, Jugador* jugador) {
    manejar_interacciones_vehiculo(id_jugador, jugador, lista_camion_caja, 55.0f, 12.5f, NUM_CARRERA_CAJA_CAMIONES,
                                SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x03));
}

void actualizar_jugador_pista_posicion_factor_desde_camiones_caja(s32 id_jugador) {
    actualizar_jugador_pista_posicion_factor_desde_vehiculo(id_jugador, NUM_CARRERA_CAJA_CAMIONES, lista_camion_caja);
}

void inicializar_omnibus_escuela_vehiculos(void) {
    s32 omnibus_num;
    f32 a = ((seleccion_cc * 90.0) / 216.0f) + 4.583333333333333;
    f32 b = ((seleccion_cc * 90.0) / 216.0f) + 2.9166666666666665;

    omnibus_num = NUM_CARRERA_ESCUELA_OMNIBUS;
    if (seleccion_modo == CONTRARRELOJ) {
        omnibus_num = NUM_CONTRARRELOJ_OMNIBUS_ESCUELA;
    }
    inicializar_toads_turnpike_vehiculo(a, b, omnibus_num, 75, lista_omnibus_escuela, &caminos_pista[0][0]);
}

void actualizar_omnibus_escuela_vehiculo(void) {
    s32 indice_bucle;
    for (indice_bucle = 0; indice_bucle < NUM_CARRERA_ESCUELA_OMNIBUS; indice_bucle++) {
        actualizar_vehiculo_seguir_camino_punto(&lista_omnibus_escuela[indice_bucle]);
    }
}

void manejar_interacciones_omnibus_escuela(s32 id_jugador, Jugador* jugador) {
    manejar_interacciones_vehiculo(id_jugador, jugador, lista_omnibus_escuela, 70.0f, 12.5f, NUM_CARRERA_ESCUELA_OMNIBUS,
                                SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x02));
}

void actualizar_jugador_pista_posicion_factor_desde_omnibus(s32 id_jugador) {
    actualizar_jugador_pista_posicion_factor_desde_vehiculo(id_jugador, NUM_CARRERA_ESCUELA_OMNIBUS, lista_omnibus_escuela);
}

void inicializar_camiones_vehiculos(void) {
    s32 camiones_num;
    f32 a = ((seleccion_cc * 90.0) / 216.0f) + 4.583333333333333;
    f32 b = ((seleccion_cc * 90.0) / 216.0f) + 2.9166666666666665;

    camiones_num = NUM_CARRERA_CISTERNA_CAMIONES;
    if (seleccion_modo == CONTRARRELOJ) {
        camiones_num = NUM_CONTRARRELOJ_CAMIONES_CISTERNA;
    }
    inicializar_toads_turnpike_vehiculo(a, b, camiones_num, 50, lista_camion_cisterna, &caminos_pista[0][0]);
}

void actualizar_camiones_cisterna_vehiculo(void) {
    s32 indice_bucle;
    for (indice_bucle = 0; indice_bucle < NUM_CARRERA_CISTERNA_CAMIONES; indice_bucle++) {
        actualizar_vehiculo_seguir_camino_punto(&lista_camion_cisterna[indice_bucle]);
    }
}

void manejar_interacciones_camiones_cisterna(s32 id_jugador, Jugador* jugador) {
    manejar_interacciones_vehiculo(id_jugador, jugador, lista_camion_cisterna, 55.0f, 12.5f, NUM_CARRERA_CISTERNA_CAMIONES,
                                SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x04));
}

void actualizar_jugador_pista_posicion_factor_desde_camion_cisterna(s32 id_jugador) {
    actualizar_jugador_pista_posicion_factor_desde_vehiculo(id_jugador, NUM_CARRERA_CISTERNA_CAMIONES, lista_camion_cisterna);
}

void inicializar_automoviles_vehiculos(void) {
    s32 automoviles_num;
    f32 a = ((seleccion_cc * 90.0) / 216.0f) + 4.583333333333333;
    f32 b = ((seleccion_cc * 90.0) / 216.0f) + 2.9166666666666665;

    automoviles_num = AUTOMOVILES_CARRERA_NUM;
    if (seleccion_modo == CONTRARRELOJ) {
        automoviles_num = NUM_CONTRARRELOJ_AUTOMOVILES;
    }
    inicializar_toads_turnpike_vehiculo(a, b, automoviles_num, 25, lista_automovil, &caminos_pista[0][0]);
}

void actualizar_automoviles_vehiculo(void) {
    s32 indice_bucle;
    for (indice_bucle = 0; indice_bucle < AUTOMOVILES_CARRERA_NUM; indice_bucle++) {
        actualizar_vehiculo_seguir_camino_punto(&lista_automovil[indice_bucle]);
    }
}

void manejar_interacciones_automoviles(s32 id_jugador, Jugador* jugador) {
    manejar_interacciones_vehiculo(id_jugador, jugador, lista_automovil, 11.5f, 8.5f, AUTOMOVILES_CARRERA_NUM,
                                SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x05));
}

void actualizar_jugador_pista_posicion_factor_desde_automoviles(s32 id_jugador) {
    actualizar_jugador_pista_posicion_factor_desde_vehiculo(id_jugador, AUTOMOVILES_CARRERA_NUM, lista_automovil);
}
