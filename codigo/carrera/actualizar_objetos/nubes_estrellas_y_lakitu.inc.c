// Nubes estrellas y lakitu

void funcion_800786EC(s32 indice_objeto) {
    switch (lista_objeto[indice_objeto].state) { /* irregular */
        case 0:
            break;
        case 1:
            funcion_80078220(indice_objeto);
            break;
        case 2:
            funcion_80078288(indice_objeto);
            if (lista_objeto[indice_objeto].desconocido_0AE == 0) {
                estado_siguiente_objeto(indice_objeto);
            }
            break;
        case 3:
            funcion_80072428(indice_objeto);
            break;
    }
}

void funcion_80078790(void) {
    s32 algun_indice;

    for (algun_indice = 0; algun_indice < COPOS_NUM; algun_indice++) {
        dato_8018D174 += 1;
        if (dato_8018D174 >= COPOS_NUM) {
            dato_8018D174 = 0;
        }
        if (lista_objeto[particula_objeto_1[dato_8018D174]].state == 0) {
            inicializar_objeto(particula_objeto_1[dato_8018D174], 1);
            break;
        }
    }
}

void actualizar_copos(void) {
    s32 algun_indice;
    s32 indice_copo;

    if (estado_juego != SECUENCIA_CREDITOS) {
        funcion_80078790();
    } else {
        funcion_80078790();
        funcion_80078790();
        funcion_80078790();
        funcion_80078790();
    }
    for (algun_indice = 0; algun_indice < COPOS_NUM; algun_indice++) {
        indice_copo = particula_objeto_1[algun_indice];
        if (lista_objeto[indice_copo].state != 0) {
            funcion_800786EC(indice_copo);
        }
    }
}

void funcion_800788F8(s32 indice_objeto, u16 rot, Camara* camara) {
    s16 temporal_v0;

    temporal_v0 = camara->rot[1] + rot;
    if ((temporal_v0 >= dato_8018D210) && (dato_8018D208 >= temporal_v0)) {
        lista_objeto[indice_objeto].desconocido_09C = (dato_8018D218 + (dato_8018D1E8 * temporal_v0));
        fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
        return;
    }
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000010);
}

void actualizar_nubes(s32 parametro0, Camara* parametro1, DatosNube* lista_nube) {
    s32 indice_nube;
    s32 indice_objeto;
    DatosNube* nube;

    for (indice_nube = 0; indice_nube < dato_8018D1F0; indice_nube++) {
        nube = &lista_nube[indice_nube];
        indice_objeto = dato_8018CC80[parametro0 + indice_nube];
        funcion_800788F8(indice_objeto, nube->rot_y, parametro1);
    }
}

void actualizar_estrellas(s32 parametro0, Camara* camara, DatosEstrella* lista_estrella) {
    s32 indice_estrella;
    s32 indice_objeto;
    DatosEstrella* estrella;

    for (indice_estrella = 0; indice_estrella < dato_8018D1F0; indice_estrella++) {
        estrella = &lista_estrella[indice_estrella];
        indice_objeto = dato_8018CC80[parametro0 + indice_estrella];
        funcion_800788F8(indice_objeto, estrella->rot_y, camara);
        switch (indice_estrella % 5U) {
            case 0:
                funcion_80073CB0(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0x00000028, 0x000000B4, 0x000000FF, 0,
                              -1);
                break;
            case 1:
                funcion_80073CB0(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0x00000080, 0x000000FF, 0x000000FF, 0,
                              -1);
                break;
            case 2:
                funcion_80073CB0(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0x00000050, 0x000000C8, 0x000000FF, 0,
                              -1);
                break;
            case 3:
                funcion_80073CB0(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0, 0x0000009B, 0x000000FF, 0, -1);
                break;
            case 4:
                funcion_80073CB0(indice_objeto, &lista_objeto[indice_objeto].prim_alpha, 0x0000005A, 0x00000080, 0x000000FF, 0,
                              -1);
                break;
        }
    }
}

SIN_USO void funcion_80078C68() {
}

void actualizar_nubes_circuito(s32 parametro0) {
    s32 sp1_c;
    Camara* camara;

    if (dato_801657C8 == 0) {
        switch (parametro0) {
            case 0:
                sp1_c = 0;
                camara = camara1;
                dato_8018D200 = acercar_camara[0] + 40.0f;
                break;
            case 1:
                sp1_c = 0;
                camara = camara1;
                dato_8018D200 = acercar_camara[0] + 40.0f;
                break;
            case 2:
                camara = camara2;
                sp1_c = dato_8018D1F0;
                dato_8018D200 = acercar_camara[1] + 40.0f;
                break;
            case 3:
                sp1_c = 0;
                camara = camara1;
                dato_8018D200 = acercar_camara[0] + 40.0f;
                break;
            case 4:
                camara = camara2;
                sp1_c = dato_8018D1F0;
                dato_8018D200 = acercar_camara[1] + 40.0f;
                break;
        }

        dato_8018D208 = ((dato_8018D200 / 2) * GRADOS(1)) + GRADOS(10);
        dato_8018D210 = (-(dato_8018D200 / 2) * GRADOS(1)) - GRADOS(10);
        dato_8018D1E8 = 1.7578125 / dato_8018D200;
        dato_8018D218 = 0xA0;
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
        switch (id_circuito_actual) {
            case CIRCUITO_MARIO_RACEWAY:
                actualizar_nubes(sp1_c, camara, luigi_raceway_nubes);
                break;
            case CIRCUITO_YOSHI_VALLEY:
                actualizar_nubes(sp1_c, camara, yoshi_valley_moo_moo_farm_nubes);
                break;
            case CIRCUITO_FRAPPE_SNOWLAND:
                funcion_80078170(sp1_c, camara);
                break;
            case CIRCUITO_KOOPA_BEACH:
                actualizar_nubes(sp1_c, camara, koopa_troopa_beach_nubes);
                break;
            case CIRCUITO_ROYAL_RACEWAY:
                actualizar_nubes(sp1_c, camara, royal_raceway_nubes);
                break;
            case CIRCUITO_LUIGI_RACEWAY:
                actualizar_nubes(sp1_c, camara, luigi_raceway_nubes);
                break;
            case CIRCUITO_MOO_MOO_FARM:
                actualizar_nubes(sp1_c, camara, yoshi_valley_moo_moo_farm_nubes);
                break;
            case CIRCUITO_TOADS_TURNPIKE:
                actualizar_estrellas(sp1_c, camara, toads_turnpike_rainbow_road_estrellas);
                break;
            case CIRCUITO_KALAMARI_DESERT:
                actualizar_nubes(sp1_c, camara, kalimari_desert_nubes);
                break;
            case CIRCUITO_SHERBET_LAND:
                actualizar_nubes(sp1_c, camara, sherbet_land_nubes);
                break;
            case CIRCUITO_RAINBOW_ROAD:
                actualizar_estrellas(sp1_c, camara, toads_turnpike_rainbow_road_estrellas);
                break;
            case CIRCUITO_WARIO_STADIUM:
                actualizar_estrellas(sp1_c, camara, wario_stadium_estrellas);
                break;
        }
    }
#else

#endif
}

void funcion_80078F64(void) {
    switch (seleccion_modo_pantalla) { /* irregular */
        case MODO_PANTALLA_1P:
            inicializar_objeto(indice_lakitu_lista[0], 1);
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            inicializar_objeto(indice_lakitu_lista[0], 1);
            inicializar_objeto(indice_lakitu_lista[1], 1);
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            inicializar_objeto(indice_lakitu_lista[0], 1);
            inicializar_objeto(indice_lakitu_lista[1], 1);
            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            inicializar_objeto(indice_lakitu_lista[0], 1);
            inicializar_objeto(indice_lakitu_lista[1], 1);
            inicializar_objeto(indice_lakitu_lista[2], 1);
            inicializar_objeto(indice_lakitu_lista[3], 1);
            break;
    }
}

void funcion_80079054(s32 id_jugador) {
    inicializar_objeto(indice_lakitu_lista[id_jugador], 2);
}

void funcion_80079084(s32 id_jugador) {
    inicializar_objeto(indice_lakitu_lista[id_jugador], 4);
}

void funcion_800790B4(s32 id_jugador) {
    inicializar_objeto(indice_lakitu_lista[id_jugador], 5);
}

void funcion_800790E4(s32 id_jugador) {
    inicializar_objeto(indice_lakitu_lista[id_jugador], 6);
}

void funcion_80079114(s32 indice_objeto, s32 parametro1, s32 parametro2) {
    s32 a;
    if (lista_objeto[indice_objeto].state >= 2) {
        if ((u8) lista_objeto[indice_objeto].desconocido_0D8 == 1) {
            if (parametro1 == 0) {
                funcion_80074894(indice_objeto, lakitu_ptr_textura);
                return;
            }
            a = indice_lakitu_lista[0];
            lista_objeto[indice_objeto].t_lut_activo = lista_objeto[a].t_lut_activo;
            lista_objeto[indice_objeto].textura_activo = lista_objeto[a].textura_activo;
            if (0) {}
            return;
        }
        switch (parametro2) {
            case 0:
                funcion_800748F4(indice_objeto, lakitu_ptr_textura);
                break;
            case 1:
                funcion_800748C4(indice_objeto, lakitu_ptr_textura);
                break;
            case 2:
                funcion_80074894(indice_objeto, lakitu_ptr_textura);
                break;
        }
    }
}

void funcion_800791F0(s32 indice_objeto, s32 id_jugador) {
    Jugador* jugador = &jugador_uno[id_jugador];

    if ((lista_objeto[indice_objeto].desconocido_0D8 != 3) && (lista_objeto[indice_objeto].desconocido_0D8 != 7)) {
        funcion_800722CC(indice_objeto, 1);
        if (id_circuito_actual == CIRCUITO_SHERBET_LAND) {
            jugador->lakitu_props &= ~EFECTO_HELADO;
        }
    } else {
    }
    if (id_circuito_actual == CIRCUITO_SHERBET_LAND) {
        funcion_800722CC(indice_objeto, 0x00000010);
        jugador->lakitu_props &= ~EFECTO_DESHIELO;
    }
    funcion_800C9018(id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFA, 0x28));
}

void inicializar_obj_lakitu_cuenta_regresiva_bandera_rojo(s32 indice_objeto, s32 parametro1) {
    if (parametro1 == 0) {
        dato_801656F0 = 0;
        dato_8018D168 = 0;
    }
    inicializar_objeto_textura(indice_objeto, (u8*) tlut_comun_lakitu_cuenta_regresiva, textura_lakitu_sin_luces_1, 0x38U,
                        (u16) 0x00000048);
    lista_objeto[indice_objeto].vertice = vtx_comun_lakitu;
    lista_objeto[indice_objeto].escalado_tamanio = 0.15f;
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000010);
    estado_siguiente_objeto(indice_objeto);
    lista_objeto[indice_objeto].desconocido_048 = dato_8018D180;
}

void actualizar_objeto_lakitu_cuenta_regresiva(s32 indice_objeto, s32 parametro1) {
    SIN_USO s32 relleno;
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            inicializar_obj_lakitu_cuenta_regresiva_bandera_rojo(indice_objeto, parametro1);
            break;
        case 2:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, lista_objeto[indice_objeto].desconocido_048);
            if ((lista_objeto[indice_objeto].temporizador == 0x00000055) && (cantidad_jugador == 3) && (parametro1 == 0)) {
                dato_8018D168 = 1;
            }
            break;
        case 3:
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
            funcion_80086F10(indice_objeto, 1, &dato_800E67B8);
            estado_siguiente_objeto(indice_objeto);
            break;
        case 4:
            if ((ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000001E) != false) && (cantidad_jugador != 3) && (parametro1 == 0)) {
                dato_8018D168 = 1;
            }
            break;
        case 5:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000001E);
            break;
        case 6:
            funcion_80072E54(indice_objeto, 1, 7, 1, 2, 0);
            break;
        case 7:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x00000014) != 0) {
                lista_objeto[indice_objeto].tlut_lista += 0x200;
                if (parametro1 == 0) {
                    reproducir_sonido2(SONIDO_LUZ_CUENTA_REGRESIVA_ACCION);
                }
            }
            break;
        case 8:
            funcion_80072E54(indice_objeto, 8, 0x0000000F, 1, 6, 0);
            break;
        case 9:
            if ((ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 8) != 0) && (parametro1 == 0)) {
                reproducir_sonido2(SONIDO_LUZ_CUENTA_REGRESIVA_ACCION);
            }
            break;
        case 10:
            if ((funcion_80072E54(indice_objeto, 0x00000010, 0x00000017, 1, 6, 0) != 0) && (parametro1 == 0)) {
                dato_801656F0 = 1;
            }
            break;
        case 11:
            if (ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 8) != 0) {
                lista_objeto[indice_objeto].tlut_lista += 0x200;
                if (parametro1 == 0) {
                    reproducir_sonido2(SONIDO_LUZ_VERDE_ACCION);
                }
            }
            break;
        case 12:
            funcion_80072E54(indice_objeto, 0x00000018, 0x0000001B, 1, 6, 0);
            break;
        case 13:
            if (parametro1 == 0) {
                funcion_800729EC(indice_objeto);
                dato_8018D160 = 1;
                break;
            }
            estado_siguiente_objeto(indice_objeto);
            break;
        case 14:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x00000078);
            break;
        case 15:
            funcion_80072428(indice_objeto);
            break;
    }
}

void inicializar_obj_lakitu_bandera_rojo(s32 indice_objeto, s32 indice_jugador) {
    Objeto* objeto;

    funcion_800791F0(indice_objeto, indice_jugador);
    inicializar_objeto_textura(indice_objeto, (u8*) tlut_comun_lakitu_bandera_a_cuadros, textura_lakitu_bandera_a_cuadros_01, 0x48U,
                        (u16) 0x00000038);
    objeto = &lista_objeto[indice_objeto];
    objeto->textura_activo = lakitu_ptr_textura;
    objeto->vertice = tambien_vtx_comun_lakitu;
    objeto->pos[2] = 5000.0f;
    objeto->pos[1] = 5000.0f;
    objeto->pos[0] = 5000.0f;
    objeto->escalado_tamanio = 0.15f;
    funcion_80086F10(indice_objeto, 2, &dato_800E6834);
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000010);
    estado_siguiente_objeto(indice_objeto);
}

void actualizar_objeto_lakitu_bandera_rojo(s32 indice_objeto, s32 indice_jugador) {
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            inicializar_obj_lakitu_bandera_rojo(indice_objeto, indice_jugador);
            break;
        case 2:
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
            estado_siguiente_objeto(indice_objeto);
            break;
        case 3:
            funcion_80072E54(indice_objeto, 0, 0x0000001F, 1, 2, -1);
            break;
        case 4:
            funcion_80072428(indice_objeto);
            break;
    }
}

void funcion_800797AC(s32 id_jugador) {
    s32 indice_objeto;
    Jugador* jugador;

    indice_objeto = indice_lakitu_lista[id_jugador];
    jugador = &jugador_uno[id_jugador];
    if ((id_circuito_actual == CIRCUITO_SHERBET_LAND) && (jugador->lakitu_props & LAKITU_RECUPERACION)) {
        inicializar_objeto(indice_objeto, 7);
        jugador->lakitu_props |= EFECTO_HELADO;
    } else {
        inicializar_objeto(indice_objeto, 3);
    }
    funcion_800722A4(indice_objeto, 1);
}

void funcion_80079860(s32 id_jugador) {
    s32 indice_objeto;
    Jugador* jugador;

    indice_objeto = indice_lakitu_lista[id_jugador];
    jugador = &jugador_uno[id_jugador];
    if ((funcion_80072354(indice_objeto, 1) != 0) &&
        (((funcion_802ABDF4(jugador->colision.indice_zx_malla) != 0) && (jugador->colision.distancia_superficie[2] <= 3.0f)) ||
         (jugador->lakitu_props & LAKITU_RECUPERACION) ||
         ((jugador->tipo_superficie == SALIDA_DE_LIMITES) && !(jugador->efectos & EFECTO_EN_EL_AIRE)))) {
        funcion_80090778(jugador);
        funcion_800797AC(id_jugador);
    }
}

void funcion_8007993C(s32 indice_objeto, Jugador* jugador) {
    if (jugador->lakitu_props & LAKITU_APAGAR) {
        funcion_800722A4(indice_objeto, 2);
        lista_objeto[indice_objeto].prim_alpha = jugador->alpha;
        return;
    }
    funcion_800722CC(indice_objeto, 2);
}

void inicializar_obj_lakitu_pesca_bandera_rojo(s32 indice_objeto, s32 parametro1) {
    funcion_800791F0(indice_objeto, parametro1);
    inicializar_objeto_textura(indice_objeto, (u8*) tlut_comun_lakitu_pesca, textura_lakitu_pesca_1, 0x38U, (u16) 0x00000048);
    lista_objeto[indice_objeto].vertice = dato_0D005F30;
    lista_objeto[indice_objeto].escalado_tamanio = 0.15f;
    funcion_80086E70(indice_objeto);
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000010);
    funcion_80073720(indice_objeto);
    estado_siguiente_objeto(indice_objeto);
    funcion_800C8F80((u8) parametro1, 0x0100FA28);
}

void funcion_80079A5C(s32 indice_objeto, SIN_USO Jugador* jugador) {
    switch (lista_objeto[indice_objeto].desconocido_0AE) {
        case 0:
            break;
        case 1:
            lista_objeto[indice_objeto].pos_origen[2] = 0.0f;
            lista_objeto[indice_objeto].pos_origen[1] = 0.0f;
            lista_objeto[indice_objeto].pos_origen[0] = 0.0f;
            lista_objeto[indice_objeto].offset[2] = 0.0f;
            lista_objeto[indice_objeto].offset[0] = 0.0f;
            lista_objeto[indice_objeto].offset[1] = 80.0f;
            funcion_80086FD4(indice_objeto);
            break;
        case 2:
            if (abajo_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 5.0f, 1.0f) != 0) {
                funcion_80086F60(indice_objeto);
            }
            break;
        case 3:
            if (arriba_paso_f32_hacia(&lista_objeto[indice_objeto].offset[1], 100.0f, 1.0f) != 0) {
                funcion_80086F60(indice_objeto);
            }
            break;
    }
}

void actualizar_objeto_lakitu_pesca(s32 indice_objeto, s32 id_jugador) {
    Jugador* jugador = &jugador_uno[id_jugador];

    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            inicializar_obj_lakitu_pesca_bandera_rojo(indice_objeto, id_jugador);
            break;
        case 2:
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
            funcion_800736E0(indice_objeto);
            estado_siguiente_objeto(indice_objeto);
            break;
        case 3:
            funcion_800730BC(indice_objeto, 0, 3, 1, 2, -1);
            break;
    }
    switch (lista_objeto[indice_objeto].desconocido_0D6) {
        case 0:
            break;
        case 1:
            if (funcion_80086FA4(indice_objeto) != 0) {
                funcion_80073654(indice_objeto);
            }
            break;
        case 2:
            funcion_80090868(jugador);
            funcion_80073654(indice_objeto);
            break;
        case 3:
            if (!(jugador->lakitu_props & MANTENIDO_POR_LAKITU)) {
                funcion_80086EAC(indice_objeto, 0, 3);
                funcion_80073654(indice_objeto);
            }
            break;
        case 4:
            if (funcion_80086FA4(indice_objeto) != 0) {
                funcion_80073654(indice_objeto);
            }
            break;
        case 5:
            funcion_800722CC(indice_objeto, 1);
            funcion_800C9018((u8) id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFA, 0x28));
            funcion_80072428(indice_objeto);
            funcion_80073720(indice_objeto);
            break;
    }
    if (lista_objeto[indice_objeto].state >= 2) {
        funcion_8007993C(indice_objeto, jugador);
    }
    funcion_80079A5C(indice_objeto, jugador);
}

void actualizar_objeto_lakitu_pesca2(s32 indice_objeto, s32 id_jugador) {
    Jugador* jugador = &jugador_uno[id_jugador];

    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            inicializar_obj_lakitu_pesca_bandera_rojo(indice_objeto, id_jugador);
            break;
        case 2:
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
            funcion_800736E0(indice_objeto);
            jugador->lakitu_props |= EFECTO_CONGELADO;
            estado_siguiente_objeto(indice_objeto);
            break;
        case 3:
            funcion_800730BC(indice_objeto, 0, 3, 1, 2, -1);
            break;
    }
    switch (lista_objeto[indice_objeto].desconocido_0D6) {
        case 1:
            if (funcion_80086FA4(indice_objeto) != 0) {
                funcion_800C9060((u8) id_jugador, 0x1900A055U);
                funcion_80073654(indice_objeto);
            }
            break;
        case 2:
            funcion_80090868(jugador);
            funcion_800722A4(indice_objeto, 4);
            funcion_80073654(indice_objeto);
            break;
        case 3:
            if ((jugador->tipo_superficie == HIELO) && !(jugador->lakitu_props & LAKITU_RECUPERACION) &&
                ((f64) jugador->colision.distancia_superficie[2] <= 30.0)) {
                funcion_800722A4(indice_objeto, 8);
            }
            if (!(jugador->lakitu_props & MANTENIDO_POR_LAKITU)) {
                funcion_80086EAC(indice_objeto, 0, 3);
                funcion_80073654(indice_objeto);
            }
            break;
        case 4:
            funcion_8007375C(indice_objeto, 0x0000001E);
            break;
        case 5:
            jugador->lakitu_props &= ~EFECTO_CONGELADO;
            funcion_800722A4(indice_objeto, 0x00000010);
            funcion_800722A4(indice_objeto, 0x00000020);
            funcion_800722CC(indice_objeto, 4);
            funcion_800722CC(indice_objeto, 8);
            funcion_80073654(indice_objeto);
            funcion_800C9060((u8) id_jugador, 0x1900A056U);
            break;
        case 6:
            if (funcion_8007375C(indice_objeto, 0x000000A0) != 0) {
                funcion_800722CC(indice_objeto, 0x00000010);
                jugador->lakitu_props &= ~EFECTO_HELADO;
                jugador->lakitu_props |= EFECTO_DESHIELO;
            }
            break;
        case 7:
            funcion_8007375C(indice_objeto, 0x0000003C);
            break;
        case 8:
            funcion_80073720(indice_objeto);
            funcion_80072428(indice_objeto);
            jugador->lakitu_props &= ~EFECTO_DESHIELO;
            funcion_800722CC(indice_objeto, 1);
            funcion_800C9018((u8) id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFA, 0x28));
            break;
    }

    if (lista_objeto[indice_objeto].state >= 2) {
        funcion_8007993C(indice_objeto, jugador);
    }
    funcion_80079A5C(indice_objeto, jugador);
}

void funcion_8007A060(s32 indice_objeto, s32 indice_jugador) {
    Objeto* objeto;

    funcion_800791F0(indice_objeto, indice_jugador);
    inicializar_objeto_textura(indice_objeto, (u8*) tlut_comun_lakitu_segundo_vuelta, textura_lakitu_segundo_vuelta_01, 0x48U,
                        (u16) 0x00000038);
    objeto = &lista_objeto[indice_objeto];
    objeto->textura_activo = lakitu_ptr_textura;
    objeto->vertice = tambien_vtx_comun_lakitu;
    objeto->pos[2] = 5000.0f;
    objeto->pos[1] = 5000.0f;
    objeto->pos[0] = 5000.0f;
    objeto->escalado_tamanio = 0.15f;
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000010);
    funcion_80086F10(indice_objeto, 5, &dato_800E694C);
    estado_siguiente_objeto(indice_objeto);
}

void actualizar_objeto_lakitu_segundo_vuelta(s32 indice_objeto, s32 indice_jugador) {
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            funcion_8007A060(indice_objeto, indice_jugador);
            break;
        case 2:
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
            estado_siguiente_objeto(indice_objeto);
            break;
        case 3:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x00000014);
            break;
        case 4:
            funcion_80072E54(indice_objeto, 0, 0x0000000F, 1, 2, 1);
            break;
        case 5:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000003C);
            break;
        case 6:
            funcion_80072F88(indice_objeto, 0x0000000F, 0, 1, 2, 1);
            break;
        case 7:
            if (lista_objeto[indice_objeto].desconocido_0AE == 0) {
                funcion_80072428(indice_objeto);
            }
            break;
    }
}

void funcion_8007A228(s32 indice_objeto, s32 indice_jugador) {
    Objeto* objeto;

    funcion_800791F0(indice_objeto, indice_jugador);
    inicializar_objeto_textura(indice_objeto, (u8*) tlut_comun_lakitu_vuelta_final, textura_lakitu_vuelta_final_01, 0x48U,
                        (u16) 0x00000038);
    objeto = &lista_objeto[indice_objeto];
    objeto->textura_activo = lakitu_ptr_textura;
    objeto->vertice = tambien_vtx_comun_lakitu;
    objeto->pos[2] = 5000.0f;
    objeto->pos[1] = 5000.0f;
    objeto->pos[0] = 5000.0f;
    objeto->escalado_tamanio = 0.15f;
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000010);
    funcion_80086F10(indice_objeto, 5, &dato_800E694C);
    estado_siguiente_objeto(indice_objeto);
}

void actualizar_objeto_lakitu_vuelta_final(s32 indice_objeto, s32 indice_jugador) {
    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            funcion_8007A228(indice_objeto, indice_jugador);
            break;
        case 2:
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
            estado_siguiente_objeto(indice_objeto);
            break;
        case 3:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x00000014);
            break;
        case 4:
            funcion_80072E54(indice_objeto, 0, 0x0000000F, 1, 2, 1);
            break;
        case 5:
            ejecutar_objeto_temporizador_conjunto_y(indice_objeto, 0x0000003C);
            break;
        case 6:
            funcion_80072F88(indice_objeto, 0x0000000F, 0, 1, 2, 1);
            break;
        case 7:
            if (lista_objeto[indice_objeto].desconocido_0AE == 0) {
                funcion_80072428(indice_objeto);
            }
            break;
    }
}

void funcion_8007A3F0(s32 indice_objeto, s32 parametro1) {
    f32 variable_ = 5000.0f;
    funcion_800791F0(indice_objeto, parametro1);
    inicializar_objeto_textura(indice_objeto, (u8*) tlut_comun_lakitu_reversa, textura_lakitu_reversa_01, 0x48U,
                        (u16) 0x00000038);
    lista_objeto[indice_objeto].textura_activo = lakitu_ptr_textura;
    lista_objeto[indice_objeto].vertice = tambien_vtx_comun_lakitu;
    lista_objeto[indice_objeto].pos[2] = variable_;
    lista_objeto[indice_objeto].pos[1] = variable_;
    lista_objeto[indice_objeto].pos[0] = variable_;
    lista_objeto[indice_objeto].escalado_tamanio = 0.15f;
    fijar_objeto_bandera_situacion_false(indice_objeto, 0x00000010);
    funcion_80086F10(indice_objeto, 6, &dato_800E69B0);
    lista_objeto[indice_objeto].desconocido_0D6 = 0;
    estado_siguiente_objeto(indice_objeto);
    funcion_800C8F80((u8) parametro1, 0x0100FA28);
}

void actualizar_objeto_lakitu_reversa(s32 indice_objeto, s32 id_jugador) {
    Jugador* sp2_c = &jugador_uno[id_jugador];

    switch (lista_objeto[indice_objeto].state) {
        case 0:
            break;
        case 1:
            funcion_8007A3F0(indice_objeto, id_jugador);
            break;
        case 2:
            fijar_objeto_bandera_situacion_true(indice_objeto, 0x00000010);
            lista_objeto[indice_objeto].desconocido_0D6 = 1;
            estado_siguiente_objeto(indice_objeto);
            break;
        case 3:
            funcion_800730BC(indice_objeto, 0, 0x0000000F, 1, 2, -1);
            break;
        case 4:
            funcion_80072428(indice_objeto);
            break;
    }
    switch (lista_objeto[indice_objeto].desconocido_0D6) {
        case 1:
            if ((lista_objeto[indice_objeto].state >= 3) && (!(sp2_c->efectos & EFECTO_REVERSA))) {
                funcion_80086F10(indice_objeto, 6, &dato_800E69F4);
                lista_objeto[indice_objeto].desconocido_0D6 = 2;
                lista_objeto[indice_objeto].desconocido_04C = 0x00000050;
                funcion_800C9018((u8) id_jugador, SONIDO_CARGA_PARAMETRO(0x01, 0x00, 0xFA, 0x28));
                return;
            }
            return;
        case 2:
            lista_objeto[indice_objeto].desconocido_04C--;
            if (lista_objeto[indice_objeto].desconocido_04C == 0) {
                estado_siguiente_objeto(indice_objeto);
                lista_objeto[indice_objeto].desconocido_0D6 = 0;
            }
            break;
    }
}

void funcion_8007A66C(s32 indice_objeto, Jugador* jugador, Camara* camara) {
    u16 temporal_t8;

    temporal_t8 = 0x8000 - camara->rot[1];
    lista_objeto[indice_objeto].pos[0] =
        (jugador->pos[0] +
         (coss(temporal_t8) * (lista_objeto[indice_objeto].pos_origen[0] + lista_objeto[indice_objeto].offset[0]))) -
        (senos(temporal_t8) * (lista_objeto[indice_objeto].pos_origen[2] + lista_objeto[indice_objeto].offset[2]));
    lista_objeto[indice_objeto].pos[1] =
        jugador->desconocido_074 + lista_objeto[indice_objeto].pos_origen[1] + lista_objeto[indice_objeto].offset[1];
    lista_objeto[indice_objeto].pos[2] =
        (jugador->pos[2] +
         (senos(temporal_t8) * (lista_objeto[indice_objeto].pos_origen[0] + lista_objeto[indice_objeto].offset[0]))) +
        (coss(temporal_t8) * (lista_objeto[indice_objeto].pos_origen[2] + lista_objeto[indice_objeto].offset[2]));
}

void funcion_8007A778(s32 indice_objeto, Jugador* jugador, Camara* camara) {
    u16 temporal_t8;

    temporal_t8 = 0x8000 - camara->rot[1];
    lista_objeto[indice_objeto].pos[0] =
        (jugador->pos[0] +
         (coss(temporal_t8) * (lista_objeto[indice_objeto].pos_origen[0] + lista_objeto[indice_objeto].offset[0]))) -
        (senos(temporal_t8) * (lista_objeto[indice_objeto].pos_origen[2] + lista_objeto[indice_objeto].offset[2]));
    lista_objeto[indice_objeto].pos[1] =
        jugador->pos[1] + lista_objeto[indice_objeto].pos_origen[1] + lista_objeto[indice_objeto].offset[1];
    lista_objeto[indice_objeto].pos[2] =
        (jugador->pos[2] +
         (senos(temporal_t8) * (lista_objeto[indice_objeto].pos_origen[0] + lista_objeto[indice_objeto].offset[0]))) +
        (coss(temporal_t8) * (lista_objeto[indice_objeto].pos_origen[2] + lista_objeto[indice_objeto].offset[2]));
}

SIN_USO void funcion_8007A884(void) {
}

void funcion_8007A88C(s32 id_jugador) {
    s32 indice_objeto;
    Jugador* jugador;

    indice_objeto = indice_lakitu_lista[id_jugador];
    jugador = &jugador_uno[id_jugador];

    if ((lista_objeto[indice_objeto].state == 0) && (jugador->efectos & EFECTO_REVERSA)) {
        funcion_800790E4(id_jugador);
    }
}

void funcion_8007A910(s32 parametro0) {
    if (dato_801657B4 == 0) {
        funcion_8007A88C(parametro0);
    }
    funcion_80079860(parametro0);
}

void actualizar_objeto_lakitu(s32 id_jugador) {
    s32 indice_objeto = indice_lakitu_lista[id_jugador];

    switch (lista_objeto[indice_objeto].desconocido_0D8) {
        case 0:
            break;
        case 1:
            actualizar_objeto_lakitu_cuenta_regresiva(indice_objeto, id_jugador);
            funcion_8008BFFC(indice_objeto);
            break;
        case 2:
            actualizar_objeto_lakitu_bandera_rojo(indice_objeto, id_jugador);
            funcion_8008BFFC(indice_objeto);
            break;
        case 3:
            actualizar_objeto_lakitu_pesca(indice_objeto, id_jugador);
            break;
        case 4:
            actualizar_objeto_lakitu_segundo_vuelta(indice_objeto, id_jugador);
            funcion_8008BFFC(indice_objeto);
            break;
        case 5:
            actualizar_objeto_lakitu_vuelta_final(indice_objeto, id_jugador);
            funcion_8008BFFC(indice_objeto);
            break;
        case 6:
            actualizar_objeto_lakitu_reversa(indice_objeto, id_jugador);
            funcion_8008BFFC(indice_objeto);
            break;
        case 7:
            actualizar_objeto_lakitu_pesca2(indice_objeto, id_jugador);
            break;
    }
}
