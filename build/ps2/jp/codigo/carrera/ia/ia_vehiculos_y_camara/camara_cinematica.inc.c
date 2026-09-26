// Camara cinematica

void funcion_80017054(Camara* camara, SIN_USO Jugador* jugador, SIN_USO s32 index, s32 id_camara) {
    s32 margen_pila_0;
    s32 margen_pila_1;
    f32 sp_ac;
    f32 sp_a8;
    f32 sp_a4;
    s32 margen_pila_2;
    s32 margen_pila_3;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8_c;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7_c;
    f32 sp78;
    s32 margen_pila_7;
    s32 margen_pila_8;
    s16 sp6_e;
    s16 sp6_c;
    f32 margen_pila_9;
    s32 id_jugador;
    f32 temporal_f0;
    s32 indice_camino;
    s32 sp58;
    s16 sp56;

    id_jugador = camara->id_jugador;
    dato_80164648[id_camara] += (dato_80164658[id_camara] - dato_80164648[id_camara]) * 0.5f;
    indice_camino = dato_80163DD8[id_camara];
    sp58 = cantidad_camino_por_indice_camino[indice_camino];
    dato_80163238 = id_jugador;
    sp56 = punto_camino_mas_cercano_por_id_camara[id_camara];
    punto_camino_mas_cercano_por_id_camara[id_camara] = funcion_8000D33C(camara->pos[0], camara->pos[1], camara->pos[2], punto_camino_mas_cercano_por_id_camara[id_camara], indice_camino);
    if (id_circuito_actual == 4) {
        if ((sp56 != punto_camino_mas_cercano_por_id_camara[id_camara]) && (punto_camino_mas_cercano_por_id_camara[id_camara] == 1)) {
            dato_80163DD8[id_camara] = int_aleatorio(4);
            indice_camino = dato_80163DD8[id_camara];
            punto_camino_mas_cercano_por_id_camara[id_camara] = funcion_8000D33C(camara->pos[0], camara->pos[1], camara->pos[2], punto_camino_mas_cercano_por_id_camara[id_camara], indice_camino);
        }
    }
    sp6_e = (punto_camino_mas_cercano_por_id_camara[id_camara] + 0xA) % sp58;
    sp6_c = (punto_camino_mas_cercano_por_id_camara[id_camara] + 0xB) % sp58;
    fijar_posicion_desplazamiento_pista(sp6_e, dato_80164688[id_camara], indice_camino);
    sp8_c = posicion_desplazamiento[0] * 0.5;
    sp84 = posicion_desplazamiento[2] * 0.5;
    fijar_posicion_desplazamiento_pista(sp6_c, dato_80164688[id_camara], indice_camino);
    sp8_c += posicion_desplazamiento[0] * 0.5;
    sp84 += posicion_desplazamiento[2] * 0.5;

    sp6_e = (punto_camino_mas_cercano_por_id_camara[id_camara] + 5) % sp58;
    sp6_c = (punto_camino_mas_cercano_por_id_camara[id_camara] + 6) % sp58;
    sp88 = (caminos_pista[indice_camino][sp6_e].pos_y + caminos_pista[indice_camino][sp6_c].pos_y) * 0.5f;
    sp6_e = (punto_camino_mas_cercano_por_id_camara[id_camara] + 1) % sp58;
    sp6_c = (punto_camino_mas_cercano_por_id_camara[id_camara] + 2) % sp58;
    fijar_posicion_desplazamiento_pista(sp6_e, dato_80164688[id_camara], indice_camino);
    sp98 = posicion_desplazamiento[0] * 0.5;
    sp90 = posicion_desplazamiento[2] * 0.5;
    fijar_posicion_desplazamiento_pista(sp6_c, dato_80164688[id_camara], indice_camino);
    sp98 += posicion_desplazamiento[0] * 0.5;
    sp90 += posicion_desplazamiento[2] * 0.5;
    sp94 = (caminos_pista[indice_camino][sp6_e].pos_y + caminos_pista[indice_camino][sp6_c].pos_y) * 0.5f;

    sp80 = sp98 - dato_801645F8[id_camara];
    sp7_c = sp94 - dato_80164618[id_camara];
    sp78 = sp90 - dato_80164638[id_camara];
    temporal_f0 = sqrtf(((sp80 * sp80) + (sp7_c * sp7_c)) + (sp78 * sp78));

    if (temporal_f0 != 0.0) {
        sp98 = dato_801645F8[id_camara] + (((margen_pila_9 = dato_80164648[id_camara]) * sp80) / temporal_f0);
        sp94 = dato_80164618[id_camara] + ((dato_80164648[id_camara] * sp7_c) / temporal_f0);
        sp90 = dato_80164638[id_camara] + ((dato_80164648[id_camara] * sp78) / temporal_f0);
    } else {
        sp98 = dato_801645F8[id_camara];
        sp94 = dato_80164618[id_camara];
        sp90 = dato_80164638[id_camara];
    }

    if (sp98 < -10000.0 || sp98 > 10000.0) {
        if (sp8_c < -10000.0 || sp8_c > 10000.0) {}
    }
    camara->pos[0] = sp98;
    camara->pos[2] = sp90;
    camara->pos[1] = sp94 + 10.0;

    dato_801645F8[id_camara] = sp98;
    dato_80164618[id_camara] = sp94;
    dato_80164638[id_camara] = sp90;

    if (sp8_c < -10000.0 || sp8_c > 10000.0) {}
    if (sp84 < -10000.0 || sp84 > 10000.0) {}
    camara->mirar_a[0] = sp8_c;
    camara->mirar_a[1] = sp88 + 8.0;
    camara->mirar_a[2] = sp84;
    funcion_80014D30(id_camara, indice_camino);
    sp_ac = camara->mirar_a[0] - camara->pos[0];
    sp_a8 = camara->mirar_a[1] - camara->pos[1];
    sp_a4 = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(sp_ac, sp_a4);
    camara->rot[0] = atan2s(sqrtf((sp_ac * sp_ac) + (sp_a4 * sp_a4)), sp_a8);
    camara->rot[2] = 0;
}

void funcion_80017720(s32 id_jugador, SIN_USO f32 parametro1, s32 id_camara, s16 indice_camino) {
    Camara* camara = camaras + id_camara;
    SIN_USO s32 relleno;

    dato_80164688[id_camara] = factor_posicion_pista[id_jugador];
    punto_camino_mas_cercano_por_id_camara[id_camara] = punto_camino_mas_cercano_por_id_jugador[id_jugador] + 3;
    punto_camino_mas_cercano_por_id_camara[id_camara] = punto_camino_mas_cercano_por_id_camara[id_camara] % cantidad_camino_por_indice_camino[indice_camino];

    fijar_posicion_desplazamiento_pista(punto_camino_mas_cercano_por_id_camara[id_camara], factor_posicion_pista[id_jugador], indice_camino);

    dato_801645F8[id_camara] = posicion_desplazamiento[0];
    dato_80164618[id_camara] = (f32) caminos_pista[indice_camino][punto_camino_mas_cercano_por_id_camara[id_camara]].pos_y;
    dato_80164638[id_camara] = posicion_desplazamiento[2];

    dato_80164658[id_camara] = jugadores[id_jugador].speed;
    dato_80164648[id_camara] = jugadores[id_jugador].speed;

    camara->pos[0] = dato_801645F8[id_camara];
    camara->pos[1] = dato_80164618[id_camara];
    camara->pos[2] = dato_80164638[id_camara];
}

void funcion_800178F4(Camara* camara, SIN_USO Jugador* jugador_sin_uso, SIN_USO s32 parametro2, s32 id_camara) {
    s16 punto_camino_camara;
    s16 punto_camino_jugador;
    SIN_USO f32 margen_pila_0;
    f32 xdiff2;
    f32 ydiff2;
    f32 zdiff2;
    Jugador* jugador;
    f32 distancia;
    f32 medio_x;
    f32 medio_y;
    f32 medio_z;
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    SIN_USO f32 variable_f2;
    SIN_USO f32 variable_f18;
    s16 punto_camino_1;
    s16 punto_camino_2;
    SIN_USO f32 margen_pila_1;
    SIN_USO f32 variable_f14;
    s32 id_jugador;
    s32 indice_camino;
    s32 cantidad_punto_camino;

    id_jugador = camara->id_jugador;
    jugador = jugador_uno;
    dato_80164688[id_camara] = factor_posicion_pista[id_jugador];
    dato_80164648[id_camara] += ((dato_80164658[id_camara] - dato_80164648[id_camara]) / 2.0f);
    dato_80163238 = id_jugador;
    indice_camino = indice_camino_por_id_jugador[id_jugador];
    jugador += id_jugador;
    cantidad_punto_camino = cantidad_camino_por_indice_camino[indice_camino];
    punto_camino_mas_cercano_por_id_camara[id_camara] =
        funcion_8000D33C(camara->pos[0], camara->pos[1], camara->pos[2], punto_camino_mas_cercano_por_id_camara[id_camara], indice_camino);
    punto_camino_jugador = (punto_camino_mas_cercano_por_id_jugador[id_jugador] + 3) % cantidad_punto_camino;
    punto_camino_camara = punto_camino_mas_cercano_por_id_camara[id_camara];
    if (es_punto_camino_en_rango(punto_camino_jugador, punto_camino_camara, 0x000DU, 1U, cantidad_punto_camino) <= 0) {
        funcion_8001A348(id_camara, dato_80164688[id_camara], dato_80164680[id_camara]);
    } else {
        if ((punto_camino_camara < punto_camino_jugador) && ((punto_camino_jugador - punto_camino_camara) < 3)) {
            dato_80164658[id_camara] = jugadores[id_jugador].speed + 0.1;
        }
        if ((punto_camino_jugador < punto_camino_camara) && ((punto_camino_camara - punto_camino_jugador) < 3)) {
            dato_80164658[id_camara] = jugadores[id_jugador].speed - 0.1;
        }
        if (dato_80164658[id_camara] > 10.0) {
            dato_80164658[id_camara] = 10.0f;
        }
        if (dato_80164658[id_camara] < 0.0) {
            dato_80164658[id_camara] = 0.0f;
        }
    }
    punto_camino_1 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 1) % cantidad_punto_camino;
    punto_camino_2 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 2) % cantidad_punto_camino;
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
    camara->pos[1] = medio_y + 10.0;
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

void funcion_80017F10(s32 id_jugador, SIN_USO f32 parametro1, s32 id_camara, s16 indice_camino) {
    Camara* camara = camaras + id_camara;
    s32 probar = cantidad_camino_por_indice_camino[indice_camino];

    dato_80164688[id_camara] = factor_posicion_pista[id_jugador];
    punto_camino_mas_cercano_por_id_camara[id_camara] = (punto_camino_mas_cercano_por_id_jugador[id_jugador] + probar) - 2;
    punto_camino_mas_cercano_por_id_camara[id_camara] = punto_camino_mas_cercano_por_id_camara[id_camara] % probar;

    fijar_posicion_desplazamiento_pista(punto_camino_mas_cercano_por_id_camara[id_camara], factor_posicion_pista[id_jugador], indice_camino);

    dato_801645F8[id_camara] = posicion_desplazamiento[0];
    dato_80164618[id_camara] = (f32) caminos_pista[indice_camino][punto_camino_mas_cercano_por_id_camara[id_camara]].pos_y;
    dato_80164638[id_camara] = posicion_desplazamiento[2];

    dato_80164658[id_camara] = jugadores[id_jugador].speed;
    dato_80164648[id_camara] = jugadores[id_jugador].speed;

    camara->pos[0] = dato_801645F8[id_camara];
    camara->pos[1] = dato_80164618[id_camara];
    camara->pos[2] = dato_80164638[id_camara];
}

void funcion_800180F0(Camara* camara, SIN_USO Jugador* jugador_sin_uso, SIN_USO s32 parametro2, s32 id_camara) {
    s16 punto_camino_camara;
    s16 punto_camino_jugador;
    SIN_USO s32 margen_pila_3;
    f32 sp94;
    f32 sp90;
    f32 sp8_c;
    SIN_USO s32 margen_pila_4;
    f32 distancia;
    f32 medio_x;
    f32 medio_y;
    f32 medio_z;
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    Jugador* jugador;
    s32 id_jugador;
    s16 punto_camino_1;
    s16 punto_camino_2;
    SIN_USO f32 variable_f2;
    SIN_USO f32 variable_f18;
    SIN_USO f32 variable_f14;
    s32 indice_camino;
    s32 cantidad_punto_camino;

    id_jugador = camara->id_jugador;
    jugador = jugador_uno;
    dato_80164688[id_camara] = factor_posicion_pista[id_jugador];
    dato_80164648[id_camara] += ((dato_80164658[id_camara] - dato_80164648[id_camara]) * 0.5f);
    dato_80163238 = id_jugador;
    indice_camino = indice_camino_por_id_jugador[id_jugador];
    cantidad_punto_camino = cantidad_camino_por_indice_camino[indice_camino];
    jugador += id_jugador;
    punto_camino_mas_cercano_por_id_camara[id_camara] =
        funcion_8000D33C(camara->pos[0], camara->pos[1], camara->pos[2], punto_camino_mas_cercano_por_id_camara[id_camara], indice_camino);
    punto_camino_jugador = ((punto_camino_mas_cercano_por_id_jugador[id_jugador] + cantidad_punto_camino) - 2) % cantidad_punto_camino;
    punto_camino_camara = punto_camino_mas_cercano_por_id_camara[id_camara];
    if (es_punto_camino_en_rango(punto_camino_jugador, punto_camino_camara, 1U, 0x000AU, cantidad_punto_camino) <= 0) {
        funcion_8001A348(id_camara, dato_80164688[id_camara], dato_80164680[id_camara]);
    } else {
        if ((punto_camino_camara < punto_camino_jugador) && ((punto_camino_jugador - punto_camino_camara) < 3)) {
            dato_80164658[id_camara] = jugadores[id_jugador].speed + 0.1;
        }
        if ((punto_camino_jugador < punto_camino_camara) && ((punto_camino_camara - punto_camino_jugador) < 3)) {
            dato_80164658[id_camara] = jugadores[id_jugador].speed - 0.1;
        }
        if (dato_80164658[id_camara] > 10.0) {
            dato_80164658[id_camara] = 10.0f;
        }
        if (dato_80164658[id_camara] < 0.0) {
            dato_80164658[id_camara] = 0.0f;
        }
    }
    punto_camino_1 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 1) % cantidad_punto_camino;
    punto_camino_2 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 2) % cantidad_punto_camino;
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
    camara->pos[1] = jugador->pos[1] + 10.0;
    dato_801645F8[id_camara] = medio_x;
    dato_80164618[id_camara] = medio_y;
    dato_80164638[id_camara] = medio_z;
    camara->mirar_a[0] = jugador->pos[0];
    camara->mirar_a[1] = jugador->pos[1] + 6.0;
    camara->mirar_a[2] = jugador->pos[2];
    funcion_80014D30(id_camara, indice_camino);
    sp94 = camara->mirar_a[0] - camara->pos[0];
    sp90 = camara->mirar_a[1] - camara->pos[1];
    sp8_c = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(sp94, sp8_c);
    camara->rot[0] = atan2s(sqrtf((sp94 * sp94) + (sp8_c * sp8_c)), sp90);
    camara->rot[2] = 0;
}

void funcion_80018718(s32 id_jugador, SIN_USO f32 parametro1, s32 id_camara, s16 indice_camino) {
    Camara* camara = camaras + id_camara;
    s32 probar = cantidad_camino_por_indice_camino[indice_camino];

    dato_80164688[id_camara] = factor_posicion_pista[id_jugador];
    punto_camino_mas_cercano_por_id_camara[id_camara] = ((punto_camino_mas_cercano_por_id_jugador[id_jugador] + probar) - 5) % probar;

    calcular_posicion_desplazamiento_pista(punto_camino_mas_cercano_por_id_camara[id_camara], factor_posicion_pista[id_jugador], 60.0f,
                                    indice_camino);

    dato_801645F8[id_camara] = posicion_desplazamiento[0];
    dato_80164618[id_camara] = (f32) caminos_pista[indice_camino][punto_camino_mas_cercano_por_id_camara[id_camara]].pos_y;
    dato_80164638[id_camara] = posicion_desplazamiento[2];

    dato_80164658[id_camara] = jugadores[id_jugador].speed;
    dato_80164648[id_camara] = jugadores[id_jugador].speed;
    dato_8016448C = 1;
    camara->pos[0] = dato_801645F8[id_camara];
    camara->pos[1] = dato_80164618[id_camara];
    camara->pos[2] = dato_80164638[id_camara];
}

void funcion_800188F4(Camara* camara, SIN_USO Jugador* jugador_unuse, SIN_USO s32 parametro2, s32 id_camara) {
    s16 punto_camino_camara;
    s16 punto_camino_jugador;
    SIN_USO s32 margen_pila_0;
    f32 sp_ac;
    f32 sp_a8;
    f32 sp_a4;
    Jugador* jugador;
    f32 distancia;
    f32 medio_x;
    f32 medio_y;
    f32 medio_z;
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    SIN_USO f32 sp64;
    SIN_USO f32 sp60;
    s16 punto_camino_1;
    s16 punto_camino_2;
    SIN_USO f32 sp5_c;
    f32 temporal_f2_4;
    s32 id_jugador;
    s32 indice_camino;
    s32 cantidad_punto_camino;

    jugador = jugador_uno;
    id_jugador = camara->id_jugador;
    indice_camino = indice_camino_por_id_jugador[id_jugador];
    cantidad_punto_camino = cantidad_camino_por_indice_camino[indice_camino];
    dato_80164648[id_camara] = jugadores[id_jugador].speed;
    if (dato_8016448C == 0) {
        if (punto_camino_mas_cercano_por_id_camara[id_camara] ==
            (((punto_camino_mas_cercano_por_id_jugador[id_jugador] + cantidad_punto_camino) - 6) % cantidad_punto_camino)) {
            dato_8016448C = 1;
        }
        if (dato_80164688[id_camara] < (factor_posicion_pista[id_jugador] - 0.2)) {
            dato_80164648[id_camara] = jugadores[id_jugador].speed * 0.7;
        }
        if ((factor_posicion_pista[id_jugador] - 0.5) < dato_80164688[id_camara]) {
            dato_80164688[id_camara] -= 0.01;
        }
        if (dato_80164688[id_camara] < -0.9) {
            dato_80164688[id_camara] = -0.9f;
            dato_80164648[id_camara] = jugadores[id_jugador].speed * 0.8;
        }
    } else {
        if (punto_camino_mas_cercano_por_id_camara[id_camara] == ((punto_camino_mas_cercano_por_id_jugador[id_jugador] + 6) % cantidad_punto_camino)) {
            dato_8016448C = 0;
        }
        if ((factor_posicion_pista[id_jugador] + 0.2) < dato_80164688[id_camara]) {
            dato_80164648[id_camara] = jugadores[id_jugador].speed * 1.3;
        }
        if (dato_80164688[id_camara] < (factor_posicion_pista[id_jugador] + 0.5)) {
            dato_80164688[id_camara] += 0.01;
        }
        if (dato_80164688[id_camara] > 0.9) {
            dato_80164688[id_camara] = 0.9f;
            dato_80164648[id_camara] = jugadores[id_jugador].speed * 1.2;
        }
    }
    dato_80163238 = id_jugador;
    jugador += id_jugador;
    punto_camino_mas_cercano_por_id_camara[id_camara] =
        funcion_8000D33C(camara->pos[0], camara->pos[1], camara->pos[2], punto_camino_mas_cercano_por_id_camara[id_camara], indice_camino);
    punto_camino_jugador = punto_camino_mas_cercano_por_id_jugador[id_jugador];
    punto_camino_camara = punto_camino_mas_cercano_por_id_camara[id_camara];
    if (es_punto_camino_en_rango(punto_camino_jugador, punto_camino_camara, 0x000FU, 0x000FU, cantidad_punto_camino) <= 0) {
        funcion_8001A348(id_camara, dato_80164688[id_camara], dato_80164680[id_camara]);
    }
    punto_camino_1 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 1) % cantidad_punto_camino;
    punto_camino_2 = (punto_camino_mas_cercano_por_id_camara[id_camara] + 2) % cantidad_punto_camino;
    calcular_posicion_desplazamiento_pista(punto_camino_1, dato_80164688[id_camara], 60.0f, indice_camino);
    medio_x = posicion_desplazamiento[0] * 0.5;
    medio_z = posicion_desplazamiento[2] * 0.5;
    calcular_posicion_desplazamiento_pista(punto_camino_2, dato_80164688[id_camara], 60.0f, indice_camino);
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
    temporal_f2_4 = obtener_altura_superficie(medio_x, medio_y + 30.0, medio_z);
    if ((temporal_f2_4 < (medio_y - 20.0)) || (temporal_f2_4 >= 3000.0)) {
        camara->pos[1] = medio_y + 10.0;
    } else {
        camara->pos[1] = temporal_f2_4 + 8.0;
    }
    dato_801645F8[id_camara] = medio_x;
    dato_80164618[id_camara] = medio_y;
    dato_80164638[id_camara] = medio_z;
    camara->mirar_a[0] = jugador->pos[0];
    camara->mirar_a[1] = jugador->pos[1] + 6.0;
    camara->mirar_a[2] = jugador->pos[2];
    funcion_80014D30(id_camara, indice_camino);
    sp_ac = camara->mirar_a[0] - camara->pos[0];
    sp_a8 = camara->mirar_a[1] - camara->pos[1];
    sp_a4 = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(sp_ac, sp_a4);
    camara->rot[0] = atan2s(sqrtf((sp_ac * sp_ac) + (sp_a4 * sp_a4)), sp_a8);
    camara->rot[2] = 0;
}

void funcion_80019118(s32 id_jugador, f32 parametro1, s32 id_camara, SIN_USO s16 indice_camino) {
    Camara* camara = camaras + id_camara;
    s32 probar = cantidad_camino_por_indice_camino[0];
    f32 temporal_f12;
    f32 temporal_f2;

    dato_80164688[id_camara] = parametro1;
    punto_camino_mas_cercano_por_id_camara[id_camara] = punto_camino_mas_cercano_por_id_jugador[id_jugador] + 12;
    punto_camino_mas_cercano_por_id_camara[id_camara] = punto_camino_mas_cercano_por_id_camara[id_camara] % probar;

    fijar_posicion_desplazamiento_pista(punto_camino_mas_cercano_por_id_camara[id_camara], parametro1, 0);
    dato_801645F8[id_camara] = posicion_desplazamiento[0];
    dato_80164638[id_camara] = posicion_desplazamiento[2];
    temporal_f2 = (f32) caminos_pista[0][punto_camino_mas_cercano_por_id_camara[id_camara]].pos_y;

    temporal_f12 = obtener_altura_superficie(posicion_desplazamiento[0], (temporal_f2 + 30.0), posicion_desplazamiento[2]);

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

void funcion_8001933C(Camara* camara, SIN_USO Jugador* parametro_jugador, SIN_USO s32 parametro2, s32 id_camara) {
    s16 punto_camino_camara;
    s16 punto_camino_jugador;
    SIN_USO s32 relleno;
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    SIN_USO s32 relleno2;
    s32 id_jugador;
    SIN_USO s32 relleno3[10];
    Jugador* jugador;
    PuntoCaminoPista* punto_camino;
    s32 indice_camino;
    s32 cantidad_punto_camino;

    id_jugador = camara->id_jugador;
    indice_camino = indice_camino_por_id_jugador[id_jugador];
    jugador = jugador_uno;
    jugador += id_jugador;
    cantidad_punto_camino = cantidad_camino_por_indice_camino[indice_camino];
    punto_camino_mas_cercano_por_id_camara[id_camara] =
        funcion_8000D33C(camara->pos[0], camara->pos[1], camara->pos[2], punto_camino_mas_cercano_por_id_camara[id_camara], 0);
    punto_camino_jugador = punto_camino_mas_cercano_por_id_jugador[id_jugador];
    punto_camino_camara = punto_camino_mas_cercano_por_id_camara[id_camara];
    if (es_punto_camino_en_rango(punto_camino_jugador, punto_camino_camara, 0x0032U, 0x0014U, cantidad_punto_camino) <= 0) {
        funcion_8001A348(id_camara, dato_80164688[id_camara], dato_80164680[id_camara]);
    } else {
        if ((factor_posicion_pista[id_jugador] < -0.5) && ((f64) dato_80164688[id_camara] < -0.5)) {
            funcion_8001A348(id_camara, 1.0f, 0x0000000D);
        } else if ((factor_posicion_pista[id_jugador] > 0.5) && ((f64) dato_80164688[id_camara] > 0.5)) {
            funcion_8001A348(id_camara, -1.0f, 0x0000000C);
        }
    }
    camara->pos[0] = dato_801645F8[id_camara];
    camara->pos[1] = dato_80164618[id_camara];
    camara->pos[2] = dato_80164638[id_camara];
    punto_camino = &caminos_pista[indice_camino][punto_camino_camara];
    camara->mirar_a[0] = (jugador->pos[0] * 0.8) + (0.2 * punto_camino->pos_x);
    camara->mirar_a[1] = (jugador->pos[1] * 0.8) + (0.2 * punto_camino->pos_y);
    camara->mirar_a[2] = (jugador->pos[2] * 0.8) + (0.2 * punto_camino->pos_z);
    funcion_80014D30(id_camara, indice_camino);
    xdiff = camara->mirar_a[0] - camara->pos[0];
    ydiff = camara->mirar_a[1] - camara->pos[1];
    zdiff = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(xdiff, zdiff);
    camara->rot[0] = atan2s(sqrtf((xdiff * xdiff) + (zdiff * zdiff)), ydiff);
    camara->rot[2] = 0;
}

void funcion_8001968C(void) {
    dato_80164678[0] = 3;
}

void funcion_8001969C(SIN_USO s32 id_jugador, SIN_USO f32 parametro1, s32 id_camara, SIN_USO s16 indice_camino) {
    PuntoCaminoPista* punto_camino;

    punto_camino_mas_cercano_por_id_camara[id_camara] = cantidad_camino_por_indice_camino[0] - 18;

    punto_camino = &caminos_pista[0][punto_camino_mas_cercano_por_id_camara[id_camara]];

    dato_801645F8[id_camara] = punto_camino->pos_x;
    dato_80164618[id_camara] = punto_camino->pos_y + 10.0;
    dato_80164638[id_camara] = punto_camino->pos_z;
    dato_80164648[id_camara] = 0.0f;
    dato_80164678[id_camara] = 0;
}

void funcion_80019760(Camara* camara, SIN_USO Jugador* jugador, SIN_USO s32 parametro2, s32 id_camara) {
    SIN_USO s32 relleno[2];
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    PuntoCaminoPista* temporal_v1;

    camara->pos[0] = dato_801645F8[id_camara];
    camara->pos[1] = dato_80164618[id_camara];
    camara->pos[2] = dato_80164638[id_camara];
    temporal_v1 = &(*caminos_pista)[punto_camino_mas_cercano_por_id_camara[id_camara]];
    camara->mirar_a[0] = (f32) temporal_v1->pos_x;
    camara->mirar_a[1] = (f32) temporal_v1->pos_y;
    camara->mirar_a[2] = (f32) temporal_v1->pos_z;
    funcion_80014D30(id_camara, 0);
    xdiff = camara->mirar_a[0] - camara->pos[0];
    ydiff = camara->mirar_a[1] - camara->pos[1];
    zdiff = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(xdiff, zdiff);
    camara->rot[0] = atan2s(sqrtf((xdiff * xdiff) + (zdiff * zdiff)), ydiff);
    camara->rot[2] = 0;
}

void empezar_disparo_cinematica_camara(s32 id_jugador, s32 id_camara) {
    s32 indice_camino;
    Camara* camara = camara1;
    camara += id_camara;
    camara->id_jugador = id_jugador;

    dato_801646C0[id_camara] = 0;
    indice_camino = indice_camino_por_id_jugador[id_jugador];

    switch (dato_80164680[id_camara]) {
        case 0:
            funcion_80015314(id_jugador, 0.0f, id_camara);
            break;
        case 2:
            funcion_80015544(id_jugador, -1.0f, id_camara, indice_camino);
            break;
        case 3:
            funcion_80015544(id_jugador, 1.0f, id_camara, indice_camino);
            break;
        case 6:
            funcion_80015A9C(id_jugador, -0.6f, id_camara, (s16) indice_camino);
            break;
        case 7:
            funcion_80015A9C(id_jugador, 0.6f, id_camara, (s16) indice_camino);
            break;
        case 4:
            funcion_800162CC(id_jugador, -1.0f, id_camara, (s16) indice_camino);
            break;
        case 5:
            funcion_800162CC(id_jugador, 1.0f, id_camara, (s16) indice_camino);
            break;
        case 9:
            funcion_80016C3C(id_jugador, 0.0f, id_camara);
            break;
        case 1:
            funcion_80017720(id_jugador, 0.0f, id_camara, (s16) indice_camino);
            break;
        case 14:
            funcion_80017F10(id_jugador, 0.0f, id_camara, (s16) indice_camino);
            break;
        case 8:
            funcion_80018718(id_jugador, 0.0f, id_camara, (s16) indice_camino);
            break;
        case 12:
            funcion_80019118(id_jugador, -1.0f, id_camara, (s16) indice_camino);
            break;
        case 13:
            funcion_80019118(id_jugador, 1.0f, id_camara, (s16) indice_camino);
            break;
        case 15:
            funcion_8001969C(id_jugador, -1.0f, id_camara, (s16) indice_camino);
            break;
        case 16:
            funcion_8001969C(id_jugador, 1.0f, id_camara, (s16) indice_camino);
            break;
        default:
            funcion_80015314(id_jugador, 0.0f, id_camara);
            break;
    }
    punto_camino_mas_cercano_por_id_camara[id_camara] =
        funcion_8000BD94(camara->pos[0], camara->pos[1], camara->pos[2], (s32) indice_camino);
    if ((s16) dato_80164680[id_camara] == 9) {
        dato_80163DD8[id_camara] = (s32) indice_camino;
    }
}

void funcion_80019B50(s32 indice_camara, u16 parametro1) {
    u16 variable_v0;

    variable_v0 = dato_801646C0[indice_camara];
    if (variable_v0 < parametro1) {
        if ((parametro1 - variable_v0) < 0x8000) {
            variable_v0 += 0x5A;
            if (parametro1 < variable_v0) {
                variable_v0 = parametro1;
            }
            if (variable_v0 < 0x5A) {
                variable_v0 = 0;
            }
        } else if ((parametro1 - variable_v0) >= 0x8000) {
            variable_v0 -= 0x5A;
        }
    } else if (parametro1 < variable_v0) {
        if ((variable_v0 - parametro1) < 0x8000) {
            variable_v0 -= 0x5A;
            if (variable_v0 < parametro1) {
                variable_v0 = parametro1;
            }
            if (variable_v0 >= 0xFFA6) {
                variable_v0 = 0;
            }
        } else if ((variable_v0 - parametro1) >= 0x8000) {
            variable_v0 += 0x5A;
            if (!indice_camara) {}
        }
    }
    dato_801646C0[indice_camara] = (s16) variable_v0;
}

void funcion_80019C50(s32 indice_jugador) {
    switch (dato_80164678[indice_jugador]) {
        case 0:
            if (dato_80164608[indice_jugador] == 1) {
                dato_80164678[indice_jugador] = 1;
                funcion_800C9060(indice_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x90, 0x4F));
                dato_80164670[indice_jugador] = dato_80164678[indice_jugador];
            }
            break;
        case 1:
            if (dato_80164608[indice_jugador] == 1) {
                dato_80164678[indice_jugador] = 0;
                funcion_800C9060(indice_jugador, SONIDO_CARGA_PARAMETRO(0x19, 0x00, 0x90, 0x50));
                dato_80164670[indice_jugador] = dato_80164678[indice_jugador];
            }
            break;
    }
}

void funcion_80019D2C(Camara* camara, Jugador* jugador, s32 parametro2) {
    s32 id_jugador;
    s32 punto_camino_mas_cercano;

    id_jugador = camara->id_jugador;
    if ((jugador_actualizacion_incrementar != 0) && (id_circuito_actual == CIRCUITO_LUIGI_RACEWAY)) {
        calcular_vector_arriba_camara(camara, parametro2);
        punto_camino_mas_cercano = punto_camino_mas_cercano_por_id_jugador[id_jugador];
        if (((punto_camino_mas_cercano >= 0x65) && (punto_camino_mas_cercano < 0xFA)) ||
            ((punto_camino_mas_cercano >= 0x1AF) && (punto_camino_mas_cercano < 0x226))) {
            funcion_80019B50(parametro2, (jugador->desconocido_206 * 2));
        } else {
            funcion_80019B50(parametro2, 0U);
        }
    }
}

void funcion_80019DE4(void) {
    dato_801646CC = 1;
}

void funcion_80019DF4(void) {
    s32 i;
    s32 id_jugador = gp_actual_carrera_jugador_id_por_puesto[0];
    for (i = 0; i < 4; i++) { dato_80164670[i] = dato_80164678[i]; }
    camara1->id_jugador = id_jugador;
    dato_80164678[0] = 1;
    dato_801646CC = 2;
}

void funcion_80019E58(void) {
    dato_80164680[0] = 1;
    empezar_disparo_cinematica_camara(0, 0);
    dato_80164670[0] = dato_80164678[0];
    dato_80164678[0] = 1;
    dato_80164680[1] = 9;
    empezar_disparo_cinematica_camara(0, 1);
    dato_80164670[1] = dato_80164678[1];
    dato_80164678[1] = 0;
}

void funcion_80019ED0(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        dato_80164670[i] = dato_80164678[i];
    }

    gp_actual_carrera_jugador_id_por_puesto[0] = (s16) indice_ganador_jugador;

    camara1->id_jugador = (s16) indice_ganador_jugador;

    for (i = 0; i < 4; i++) {
        dato_80164680[i] = 0;
        funcion_80015314(indice_ganador_jugador, 0, i);
        dato_80164678[i] = 1;
    }
}

void funcion_80019FB4(s32 id_camara) {
    struct Mando* mando;

    mando = &mando_uno[id_camara];
    if (mando->boton_pulsado & L_CBUTTONS) {
        dato_801645D0[id_camara] += 1;
    } else {
        dato_801645D0[id_camara] = 0;
    }
    if (mando->boton_pulsado & D_CBUTTONS) {
        dato_801645E8[id_camara] += 1;
    } else {
        dato_801645E8[id_camara] = 0;
    }
    if (mando->boton_pulsado & U_CBUTTONS) {
        dato_80164608[id_camara] += 1;
    } else {
        dato_80164608[id_camara] = 0;
    }
    if (mando->boton_pulsado & R_CBUTTONS) {
        dato_80164628[id_camara] += 1;
    } else {
        dato_80164628[id_camara] = 0;
    }
}

void funcion_8001A0A4(SIN_USO u16* parametro0, SIN_USO Camara* parametro1, SIN_USO Jugador* parametro2, SIN_USO s8 parametro3, s32 parametro4) {
    funcion_80019FB4(parametro4);
    funcion_80019C50(parametro4);
}

void funcion_8001A0DC(u16* parametro0, Camara* parametro1, Jugador* parametro2, s8 parametro3, s32 parametro4) {
    funcion_8001A0A4(parametro0, parametro1, parametro2, parametro3, parametro4);
    funcion_80019D2C(parametro1, parametro2, parametro4);
}

void funcion_8001A124(s32 parametro0, s32 parametro1) {
    switch (gp_actual_carrera_puesto_por_id_jugador[parametro0]) { /* irregular */
        case 0:
            if (int_aleatorio(0x0064U) < 0x32) {
                dato_80164680[parametro1] = 0x000C;
            } else {
                dato_80164680[parametro1] = 0x000D;
            }
            funcion_800CA270();
            break;
        case 1:
        case 2:
        case 3:
            dato_80164680[parametro1] = 8;
            break;
        default:
            if (int_aleatorio(0x0064U) < 0x32) {
                dato_80164680[parametro1] = 0x000F;
            } else {
                dato_80164680[parametro1] = 0x0010;
            }
            break;
    }
}

void funcion_8001A220(SIN_USO s32 parametro0, s32 id_camara) {
    switch (int_aleatorio(6)) {
        case 0:
            dato_80164680[id_camara] = 4;
            break;
        case 1:
            dato_80164680[id_camara] = 5;
            break;
        case 2:
            dato_80164680[id_camara] = 6;
            break;
        case 3:
            dato_80164680[id_camara] = 7;
            break;
        case 4:
            dato_80164680[id_camara] = 8;
            break;
        case 5:
            dato_80164680[id_camara] = 1;
            break;
        default:
            dato_80164680[id_camara] = 8;
            break;
    }
}

s32 funcion_8001A310(s32 punto_camino, s32 parametro1) {
    if ((id_circuito_actual == CIRCUITO_BOWSER_CASTLE) && (parametro1 != 0) && (punto_camino >= 0xE7) && (punto_camino < 0x1C2)) {
        parametro1 = 0;
    }
    return parametro1;
}

void funcion_8001A348(s32 id_camara, f32 parametro1, s32 parametro2) {
    SIN_USO s32 relleno;
    s32 id_jugador;

    id_jugador = camaras[id_camara].id_jugador;
    dato_80164688[id_camara] = parametro1;
    dato_80164680[id_camara] = funcion_8001A310((s32) punto_camino_mas_cercano_por_id_camara[id_camara], parametro2);
    empezar_disparo_cinematica_camara(id_jugador, id_camara);
}

void funcion_8001A3D8(s32 parametro0, f32 parametro1, s32 parametro2) {
    s32 id_jugador;

    id_jugador = camaras[parametro0].id_jugador;
    dato_80164688[parametro0] = parametro1;
    if (parametro2 != dato_80164680[parametro0]) {
        dato_80164680[parametro0] = parametro2;
        empezar_disparo_cinematica_camara(id_jugador, parametro0);
    }
}

void funcion_8001A450(s32 id_jugador, s32 parametro1, s32 parametro2) {
    s32 temporal_v1;
    s16 punto_camino;
    s32 temporal_v0;

    if (!(jugadores[id_jugador].efectos & (desconocido_efecto_0_x_10000000 | EFECTO_EN_EL_AIRE | IMPULSO_RAMPA_MADERA_EFECTO))) {
        temporal_v1 = dato_80164680[parametro1];
        punto_camino = punto_camino_mas_cercano_por_id_camara[parametro1];
        temporal_v0 = funcion_8001A310(punto_camino, (temporal_v1 + 1) % 10);
        if ((temporal_v0 != temporal_v1) || (parametro2 != id_jugador)) {
            dato_80164680[parametro1] = temporal_v0;
            empezar_disparo_cinematica_camara(parametro2, parametro1);
        }
    }
}
