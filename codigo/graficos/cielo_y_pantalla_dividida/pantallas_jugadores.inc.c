// Pantallas jugadores

void renderizar_vertical_pantalla_jugador_dos_2j(void) {
    Camara* camara = &camaras[1];
    SIN_USO s32 relleno[2];
    u16 norma_persp;
    Mat4 matriz;
#ifdef VERSION_EU
    f32 sp9_c;
#else
    SIN_USO f32 sp9_c;
#endif

    funcion_802A5004();
    inicializar_rdp();
    funcion_802A3730(dato_800DC5F0);
#ifdef VERSION_EU
    sp9_c = aspecto_pantalla * 1.2f;
#endif
    gSPSetGeometryMode(display_list_cabeza++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
#ifdef VERSION_EU
    guPerspective(&gfx_pool->mtx_persp[1], &norma_persp, acercar_camara[1], sp9_c, circuito_cerca_persp, persp_lejos_circuito, 1.0f);
#else
    guPerspective(&gfx_pool->mtx_persp[1], &norma_persp, acercar_camara[1], aspecto_pantalla, circuito_cerca_persp, persp_lejos_circuito,
                  1.0f);
#endif
    gSPPerspNormalize(display_list_cabeza++, norma_persp);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[1]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guLookAt(&gfx_pool->mtx_mirar_a[1], camara->pos[0], camara->pos[1], camara->pos[2], camara->mirar_a[0],
             camara->mirar_a[1], camara->mirar_a[2], camara->arriba[0], camara->arriba[1], camara->arriba[2]);

    if (dato_800DC5C8 == 0) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    } else {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    renderizar_circuito(dato_800DC5F0);
    if (dato_800DC5C8 == 1) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    }
    renderizar_actores_circuito(dato_800DC5F0);
    renderizar_objeto(RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS);
    renderizar_jugadores_en_pantalla_dos();
    funcion_8029122C(dato_800DC5F0, JUGADOR_DOS);
    funcion_80021C78();
    renderizar_cajas_item(dato_800DC5F0);
    funcion_80058BF4();
    renderizar_efecto_nieve_jugador(RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS);
    if (dato_800DC5B8 != 0) {
        funcion_80058C20(RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS);
    }
    funcion_80093A5C(RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS);
    if (dato_800DC5B8 != 0) {
        renderizar_hud(RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS);
    }
    dato_8015F788 += 1;
}

void renderizar_horizontal_pantalla_jugador_uno_2j(void) {
    Camara* camara = &camaras[0];
    SIN_USO s32 relleno[2];
    u16 norma_persp;
    Mat4 matriz;
#ifdef VERSION_EU
    f32 sp9_c;
#endif

    funcion_802A51D4();
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);
    inicializar_rdp();
    funcion_802A3730(dato_800DC5EC);
#ifdef VERSION_EU
    sp9_c = aspecto_pantalla * 1.2f;
#endif
    gSPSetGeometryMode(display_list_cabeza++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
#ifdef VERSION_EU
    guPerspective(&gfx_pool->mtx_persp[0], &norma_persp, acercar_camara[0], sp9_c, circuito_cerca_persp, persp_lejos_circuito, 1.0f);
#else
    guPerspective(&gfx_pool->mtx_persp[0], &norma_persp, acercar_camara[0], aspecto_pantalla, circuito_cerca_persp, persp_lejos_circuito,
                  1.0f);
#endif
    gSPPerspNormalize(display_list_cabeza++, norma_persp);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[0]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guLookAt(&gfx_pool->mtx_mirar_a[0], camara->pos[0], camara->pos[1], camara->pos[2], camara->mirar_a[0],
             camara->mirar_a[1], camara->mirar_a[2], camara->arriba[0], camara->arriba[1], camara->arriba[2]);

    if (dato_800DC5C8 == 0) {

        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    } else {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    renderizar_circuito(dato_800DC5EC);
    if (dato_800DC5C8 == 1) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    }
    renderizar_actores_circuito(dato_800DC5EC);
    renderizar_objeto(RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO);
    renderizar_jugadores_en_pantalla_uno();
    funcion_8029122C(dato_800DC5EC, JUGADOR_UNO);
    funcion_80021B0C();
    renderizar_cajas_item(dato_800DC5EC);
    renderizar_efecto_nieve_jugador(RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO);
    funcion_80058BF4();
    if (dato_800DC5B8 != 0) {
        funcion_80058C20(RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO);
    }
    funcion_80093A5C(RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO);
    if (dato_800DC5B8 != 0) {
        renderizar_hud(RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO);
    }
    dato_8015F788 += 1;
}

void renderizar_horizontal_pantalla_jugador_dos_2j(void) {
    Camara* camara = &camaras[1];
    SIN_USO s32 relleno[2];
    u16 norma_persp;
    Mat4 matriz;
#ifdef VERSION_EU
    f32 sp9_c;
#endif

    funcion_802A52BC();
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);
    inicializar_rdp();
    funcion_802A3730(dato_800DC5F0);
#ifdef VERSION_EU
    sp9_c = aspecto_pantalla * 1.2f;
#endif
    gSPSetGeometryMode(display_list_cabeza++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
#ifdef VERSION_EU
    guPerspective(&gfx_pool->mtx_persp[1], &norma_persp, acercar_camara[1], sp9_c, circuito_cerca_persp, persp_lejos_circuito, 1.0f);
#else
    guPerspective(&gfx_pool->mtx_persp[1], &norma_persp, acercar_camara[1], aspecto_pantalla, circuito_cerca_persp, persp_lejos_circuito,
                  1.0f);
#endif
    gSPPerspNormalize(display_list_cabeza++, norma_persp);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[1]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guLookAt(&gfx_pool->mtx_mirar_a[1], camara->pos[0], camara->pos[1], camara->pos[2], camara->mirar_a[0],
             camara->mirar_a[1], camara->mirar_a[2], camara->arriba[0], camara->arriba[1], camara->arriba[2]);

    if (dato_800DC5C8 == 0) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    } else {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    renderizar_circuito(dato_800DC5F0);
    if (dato_800DC5C8 == 1) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    }
    renderizar_actores_circuito(dato_800DC5F0);
    renderizar_objeto(RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS);
    renderizar_jugadores_en_pantalla_dos();
    funcion_8029122C(dato_800DC5F0, JUGADOR_DOS);
    funcion_80021C78();
    renderizar_cajas_item(dato_800DC5F0);
    renderizar_efecto_nieve_jugador(RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS);
    funcion_80058BF4();
    if (dato_800DC5B8 != 0) {
        funcion_80058C20(RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS);
    }
    funcion_80093A5C(RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS);
    if (dato_800DC5B8 != 0) {
        renderizar_hud(RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS);
    }
    dato_8015F788 += 1;
}

void renderizar_pantalla_jugador_uno_3j_4j(void) {
    Camara* camara = camara1;
    SIN_USO s32 relleno[2];
    u16 norma_persp;
    Mat4 matriz;
#ifdef VERSION_EU
    f32 sp9_c;
    sp9_c = aspecto_pantalla * 1.2f;
#endif

    funcion_802A54A8();
    inicializar_rdp();
    funcion_802A3730(dato_800DC5EC);
    gSPSetGeometryMode(display_list_cabeza++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
#ifdef VERSION_EU
    guPerspective(&gfx_pool->mtx_persp[0], &norma_persp, acercar_camara[0], sp9_c, circuito_cerca_persp, persp_lejos_circuito, 1.0f);
#else
    guPerspective(&gfx_pool->mtx_persp[0], &norma_persp, acercar_camara[0], aspecto_pantalla, circuito_cerca_persp, persp_lejos_circuito,
                  1.0f);
#endif
    gSPPerspNormalize(display_list_cabeza++, norma_persp);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[0]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guLookAt(&gfx_pool->mtx_mirar_a[0], camara->pos[0], camara->pos[1], camara->pos[2], camara->mirar_a[0],
             camara->mirar_a[1], camara->mirar_a[2], camara->arriba[0], camara->arriba[1], camara->arriba[2]);

    if (dato_800DC5C8 == 0) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    } else {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    renderizar_circuito(dato_800DC5EC);
    if (dato_800DC5C8 == 1) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    }
    renderizar_actores_circuito(dato_800DC5EC);
    renderizar_objeto(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO);
    renderizar_jugadores_en_pantalla_uno();
    funcion_8029122C(dato_800DC5EC, JUGADOR_UNO);
    funcion_80021B0C();
    renderizar_cajas_item(dato_800DC5EC);
    renderizar_efecto_nieve_jugador(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO);
    funcion_80058BF4();
    if (dato_800DC5B8 != 0) {
        funcion_80058C20(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO);
    }
    funcion_80093A5C(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO);
    if (dato_800DC5B8 != 0) {
        renderizar_hud(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO);
    }
    dato_8015F788 += 1;
}

void renderizar_pantalla_jugador_dos_3j_4j(void) {
    Camara* camara = camara2;
    SIN_USO s32 relleno[2];
    u16 norma_persp;
    Mat4 matriz;
#ifdef VERSION_EU
    f32 sp9_c;
    sp9_c = aspecto_pantalla * 1.2f;
#endif

    funcion_802A5590();
    inicializar_rdp();
    funcion_802A3730(dato_800DC5F0);
    gSPSetGeometryMode(display_list_cabeza++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
#ifdef VERSION_EU
    guPerspective(&gfx_pool->mtx_persp[1], &norma_persp, acercar_camara[1], sp9_c, circuito_cerca_persp, persp_lejos_circuito, 1.0f);
#else
    guPerspective(&gfx_pool->mtx_persp[1], &norma_persp, acercar_camara[1], aspecto_pantalla, circuito_cerca_persp, persp_lejos_circuito,
                  1.0f);
#endif
    gSPPerspNormalize(display_list_cabeza++, norma_persp);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[1]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    guLookAt(&gfx_pool->mtx_mirar_a[1], camara->pos[0], camara->pos[1], camara->pos[2], camara->mirar_a[0],
             camara->mirar_a[1], camara->mirar_a[2], camara->arriba[0], camara->arriba[1], camara->arriba[2]);
    if (dato_800DC5C8 == 0) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    } else {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    renderizar_circuito(dato_800DC5F0);
    if (dato_800DC5C8 == 1) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[1]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    }
    renderizar_actores_circuito(dato_800DC5F0);
    renderizar_objeto(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS);
    renderizar_jugadores_en_pantalla_dos();
    funcion_8029122C(dato_800DC5F0, JUGADOR_DOS);
    funcion_80021C78();
    renderizar_cajas_item(dato_800DC5F0);
    renderizar_efecto_nieve_jugador(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS);
    funcion_80058BF4();
    if (dato_800DC5B8 != 0) {
        funcion_80058C20(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS);
    }
    funcion_80093A5C(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS);
    if (dato_800DC5B8 != 0) {
        renderizar_hud(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS);
    }
    dato_8015F788 += 1;
}

void renderizar_pantalla_jugador_tres_3j_4j(void) {
    Camara* camara = camara3;
    SIN_USO s32 relleno[2];
    u16 norma_persp;
    Mat4 matriz;
#ifdef VERSION_EU
    f32 sp9_c;
    sp9_c = aspecto_pantalla * 1.2f;
#endif

    funcion_802A5678();
    inicializar_rdp();
    funcion_802A3730(dato_800DC5F4);

    gSPSetGeometryMode(display_list_cabeza++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
#ifdef VERSION_EU
    guPerspective(&gfx_pool->mtx_persp[2], &norma_persp, acercar_camara[2], sp9_c, circuito_cerca_persp, persp_lejos_circuito, 1.0f);
#else
    guPerspective(&gfx_pool->mtx_persp[2], &norma_persp, acercar_camara[2], aspecto_pantalla, circuito_cerca_persp, persp_lejos_circuito,
                  1.0f);
#endif
    gSPPerspNormalize(display_list_cabeza++, norma_persp);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[2]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guLookAt(&gfx_pool->mtx_mirar_a[2], camara->pos[0], camara->pos[1], camara->pos[2], camara->mirar_a[0],
             camara->mirar_a[1], camara->mirar_a[2], camara->arriba[0], camara->arriba[1], camara->arriba[2]);
    if (dato_800DC5C8 == 0) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[2]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    } else {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[2]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    renderizar_circuito(dato_800DC5F4);
    if (dato_800DC5C8 == 1) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[2]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    }
    renderizar_actores_circuito(dato_800DC5F4);
    renderizar_objeto(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES);
    renderizar_jugadores_en_pantalla_tres();
    funcion_8029122C(dato_800DC5F4, JUGADOR_TRES);
    funcion_80021D40();
    renderizar_cajas_item(dato_800DC5F4);
    renderizar_efecto_nieve_jugador(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES);
    funcion_80058BF4();
    if (dato_800DC5B8 != 0) {
        funcion_80058C20(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES);
    }
    funcion_80093A5C(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES);
    if (dato_800DC5B8 != 0) {
        renderizar_hud(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES);
    }
    dato_8015F788 += 1;
}

void renderizar_pantalla_jugador_cuatro_3j_4j(void) {
    Camara* camara = camara4;
    SIN_USO s32 relleno[2];
    u16 norma_persp;
    Mat4 matriz;
#ifdef VERSION_EU
    f32 sp9_c;
    sp9_c = aspecto_pantalla * 1.2f;
#endif

    funcion_802A5760();
    if (seleccion_cantidad_jugador_1 == 3) {
        funcion_80093A5C(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO);
        if (dato_800DC5B8 != 0) {
            renderizar_hud(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO);
        }
        dato_8015F788 += 1;
        return;
    }

    inicializar_rdp();
    funcion_802A3730(dato_800DC5F8);

    gSPSetGeometryMode(display_list_cabeza++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
#ifdef VERSION_EU
    guPerspective(&gfx_pool->mtx_persp[3], &norma_persp, acercar_camara[3], sp9_c, circuito_cerca_persp, persp_lejos_circuito, 1.0f);
#else
    guPerspective(&gfx_pool->mtx_persp[3], &norma_persp, acercar_camara[3], aspecto_pantalla, circuito_cerca_persp, persp_lejos_circuito,
                  1.0f);
#endif
    gSPPerspNormalize(display_list_cabeza++, norma_persp);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[3]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guLookAt(&gfx_pool->mtx_mirar_a[3], camara->pos[0], camara->pos[1], camara->pos[2], camara->mirar_a[0],
             camara->mirar_a[1], camara->mirar_a[2], camara->arriba[0], camara->arriba[1], camara->arriba[2]);
    if (dato_800DC5C8 == 0) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[3]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    } else {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[3]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    renderizar_circuito(dato_800DC5F8);
    if (dato_800DC5C8 == 1) {
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[3]),
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        identidad_mtxf(matriz);
        fijar_posicion_render(matriz, 0);
    }
    renderizar_actores_circuito(dato_800DC5F8);
    renderizar_objeto(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO);
    renderizar_jugadores_en_pantalla_cuatro();
    funcion_8029122C(dato_800DC5F8, JUGADOR_CUATRO);
    funcion_80021DA8();
    renderizar_cajas_item(dato_800DC5F8);
    renderizar_efecto_nieve_jugador(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO);
    funcion_80058BF4();
    if (dato_800DC5B8 != 0) {
        funcion_80058C20(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO);
    }
    funcion_80093A5C(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO);
    if (dato_800DC5B8 != 0) {
        renderizar_hud(RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO);
    }
    dato_8015F788 += 1;
}

void funcion_802A74BC(void) {
    struct desconocido_struct_800DC5EC* envoltorio = &dato_8015F480[0];
    Jugador* jugador = &jugadores[0];
    Camara* camara = &camaras[0];
    struct Mando* mando = &mandos[0];

    s32* desconocido = &dato_8015F790[0];
    s32 i;

    for (i = 0; i < 4; i++) {
        envoltorio->mandos = mando;
        envoltorio->camara = camara;
        envoltorio->jugador = jugador;
        envoltorio->desconocido_c = desconocido;
        envoltorio->ancho_pantalla = 4;
        envoltorio->altura_pantalla = 4;
        envoltorio->contador_camino = 1;

        switch (modo_pantalla_activo) {
            case MODO_PANTALLA_1P:
                if (i == 0) {
                    envoltorio->inicio_x_pantalla = 160;
                }
                envoltorio->inicio_y_pantalla = 120;
                break;
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
                if (i == 0) {
                    envoltorio->inicio_x_pantalla = 80;
                    envoltorio->inicio_y_pantalla = 120;
                } else if (i == 1) {
                    envoltorio->inicio_x_pantalla = 240;
                    envoltorio->inicio_y_pantalla = 120;
                }
                break;
            case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
                if (i == 0) {
                    envoltorio->inicio_x_pantalla = 160;
                    envoltorio->inicio_y_pantalla = 60;
                } else if (i == 1) {
                    envoltorio->inicio_x_pantalla = 160;
                    envoltorio->inicio_y_pantalla = 180;
                }
                break;
            case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
                if (i == 0) {
                    envoltorio->inicio_x_pantalla = 80;
                    envoltorio->inicio_y_pantalla = 60;
                } else if (i == 1) {
                    envoltorio->inicio_x_pantalla = 240;
                    envoltorio->inicio_y_pantalla = 60;
                } else if (i == 2) {
                    envoltorio->inicio_x_pantalla = 80;
                    envoltorio->inicio_y_pantalla = 180;
                } else {
                    envoltorio->inicio_x_pantalla = 240;
                    envoltorio->inicio_y_pantalla = 180;
                }
                break;
        }
        jugador++;
        camara++;
        envoltorio++;
        desconocido += 0x10;
    }
}

#ifdef TARGET_PS2
void copiar_pantalla_gigante(int x, int y, int w, int h, const void* objetivo);

void copiar_framebuffer(s32 parametro0, s32 parametro1, s32 ancho, s32 altura, SIN_USO u16* origen, u16* objetivo) {
    copiar_pantalla_gigante(parametro0, parametro1, ancho, altura, objetivo);
}
#else
void copiar_framebuffer(s32 parametro0, s32 parametro1, s32 ancho, s32 altura, u16* origen, u16* objetivo) {
    s32 variable_v1;
    s32 variable_a1;
    s32 indice_objetivo;
    s32 indice_origen;

    indice_objetivo = 0;
    for (variable_v1 = 0; variable_v1 < altura; variable_v1++) {
        indice_origen = ((parametro1 + variable_v1) * 320) + parametro0;
        for (variable_a1 = 0; variable_a1 < ancho; variable_a1++, indice_objetivo++, indice_origen++) {
            objetivo[indice_objetivo] = origen[indice_origen];
        }
    }
}
#endif

void funcion_802A7728(void) {
    s16 temporal_v0;

    if (modo_pantalla_activo == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        dato_800DC5DC = 0;
    } else {
        dato_800DC5DC = 128;
    }
    dato_800DC5E0 = 0;
    temporal_v0 = (s16) s_framebuffer_renderizado - 1;
    if (temporal_v0 < 0) {
        temporal_v0 = 2;
    } else if (temporal_v0 > 2) {
        temporal_v0 = 0;
    }
    copiar_framebuffer(dato_800DC5DC, dato_800DC5E0, 64, 32, (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x8800));
    copiar_framebuffer(dato_800DC5DC + 64, dato_800DC5E0, 64, 32, (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x9800));
    copiar_framebuffer(dato_800DC5DC, dato_800DC5E0 + 32, 64, 32, (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0xA800));
    copiar_framebuffer(dato_800DC5DC + 64, dato_800DC5E0 + 32, 64, 32,
                     (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0xB800));
    copiar_framebuffer(dato_800DC5DC, dato_800DC5E0 + 64, 64, 32, (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0xC800));
    copiar_framebuffer(dato_800DC5DC + 64, dato_800DC5E0 + 64, 64, 32,
                     (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0xD800));
}

void funcion_802A7940(void) {
    s16 temporal_v0;

    if (modo_pantalla_activo == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) {
        dato_800DC5DC = 0;
    } else {
        dato_800DC5DC = 128;
    }
    dato_800DC5E0 = 0;
    temporal_v0 = (s16) s_framebuffer_renderizado - 1;
    if (temporal_v0 < 0) {
        temporal_v0 = 2;
    } else if (temporal_v0 > 2) {
        temporal_v0 = 0;
    }
    copiar_framebuffer(dato_800DC5DC, dato_800DC5E0, 0x40, 0x20, (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0xF800));
    copiar_framebuffer(dato_800DC5DC + 0x40, dato_800DC5E0, 0x40, 0x20,
                     (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x10800));
    copiar_framebuffer(dato_800DC5DC, dato_800DC5E0 + 0x20, 0x40, 0x20,
                     (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x11800));
    copiar_framebuffer(dato_800DC5DC + 0x40, dato_800DC5E0 + 0x20, 0x40, 0x20,
                     (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x12800));
    copiar_framebuffer(dato_800DC5DC, dato_800DC5E0 + 0x40, 0x40, 0x20,
                     (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x13800));
    copiar_framebuffer(dato_800DC5DC + 0x40, dato_800DC5E0 + 0x40, 0x40, 0x20,
                     (u16*) FISICO_A_VIRTUAL(framebuffers_fisico[temporal_v0]),
                     (u16*) FISICO_A_VIRTUAL(tabla_segmento[5] + 0x14800));
}
