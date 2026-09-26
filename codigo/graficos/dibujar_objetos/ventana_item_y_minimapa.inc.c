// Ventana item y minimapa

SIN_USO void funcion_8004CC24(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004C628(parametro0, parametro1, 32, 32, textura);
}

SIN_USO void dibujar_textura_40x_hud_2d_32(s32 x, s32 y, u8* textura) {
    dibujar_textura_hud_2d(x, y, 40, 32, textura);
}

SIN_USO void funcion_8004CC84(s32 x, s32 y, u8* textura) {
    funcion_8004C91C(x, y, textura, 48, 48, 24);
}

SIN_USO void funcion_8004CCB4(s32 x, s32 y, u8* textura) {
    dibujar_textura_hud_2d(x, y, 64, 32, textura);
}

SIN_USO void funcion_8004CCE4(s32 parametro0, s32 parametro1, f32 parametro2, u8* textura) {
    funcion_8004CA58(parametro0, parametro1, parametro2, textura, 64, 32);
}

SIN_USO void funcion_8004CD18(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004C91C(parametro0, parametro1, textura, 64, 64, 32);
}

SIN_USO void funcion_8004CD48(s32 parametro0, s32 parametro1, SIN_USO u8* textura, s32 ancho, s32 parametro4, s32 altura) {
    SIN_USO s32 relleno;
    s32 variable_s0;
    s32 i;
    u8* img;

    variable_s0 = parametro1 - (parametro4 / 2);
    gSPDisplayList(display_list_cabeza++, dato_0D007FE0);

    for (i = 0; i < parametro4 / altura; i++) {
        cargar_nomirror_bloque_ia16_textura(img, ancho, altura);
        funcion_8004B97C(parametro0 - (ancho / 2), variable_s0, ancho, altura, 1);
        img += ancho * altura * 2;
        variable_s0 += altura;
    }
}

SIN_USO void funcion_8004CE8C(s32 parametro0, s32 parametro1, u8* textura, s32 ancho, s32 parametro4, s32 altura) {
    s32 variable_s0 = parametro1 - (parametro4 / 2);
    s32 i;
    u8* img = textura;

    for (i = 0; i < parametro4 / altura; i++) {
        cargar_nomirror_bloque_ia8_textura(img, ancho, altura);
        funcion_8004B97C(parametro0 - (ancho / 2), variable_s0, ancho, altura, 1);
        img += ancho * altura;
        variable_s0 += altura;
    }
}

SIN_USO void funcion_8004CF9C(s32 parametro0, s32 parametro1, u8* textura, s32 parametro3, s32 parametro4, SIN_USO s32 parametro5, s32 parametro6) {
    gSPDisplayList(display_list_cabeza++, dato_0D007FE0);
    funcion_8004CE8C(parametro0, parametro1, textura, parametro3, parametro4, parametro6);
}

SIN_USO void funcion_8004CFF0(s32 parametro0, s32 parametro1, u8* textura, s32 parametro3, s32 parametro4, SIN_USO s32 parametro5, s32 parametro6) {
    gSPDisplayList(display_list_cabeza++, dato_0D008000);
    funcion_8004CE8C(parametro0, parametro1, textura, parametro3, parametro4, parametro6);
}

SIN_USO void funcion_8004D044(s32 parametro0, s32 parametro1, u8* textura, s32 rojo, s32 verde, s32 azul, s32 alpha, s32 parametro7, s32 parametro8,
                          SIN_USO s32 parametro9, s32 parametro_a) {
    gSPDisplayList(display_list_cabeza++, dato_0D007FE0);
    funcion_8004B35C(rojo, verde, azul, alpha);
    funcion_8004CE8C(parametro0, parametro1, textura, parametro7, parametro8, parametro_a);
}

SIN_USO void funcion_8004D0CC(void) {
}

SIN_USO void funcion_8004D0D4(s32 parametro0, s32 parametro1, u8* textura, s32 ancho, s32 parametro4, s32 altura) {
    s32 variable_s0;
    u8* img;
    s32 i;

    variable_s0 = parametro1 - (parametro4 / 2);
    img = textura;
    gSPDisplayList(display_list_cabeza++, dato_0D007FE0);

    for (i = 0; i < parametro4 / altura; i++) {
        funcion_80044924(img, ancho, altura);
        funcion_8004B97C(parametro0 - (ancho / 2), variable_s0, ancho, altura, 1);
        img += ancho * altura;
        variable_s0 += altura;
    }
}

void funcion_8004D210(s32 parametro0, s32 parametro1, u8* textura, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6, s32 ancho, s32 parametro8,
                   SIN_USO s32 parametro9, s32 altura) {
    s32 variable_s3;
    u8* img;
    s32 i;

    variable_s3 = parametro1 - (parametro8 / 2);
    img = textura;
    gSPDisplayList(display_list_cabeza++, dato_0D007FE0);
    funcion_8004B35C(parametro3, parametro4, parametro5, parametro6);

    for (i = 0; i < parametro8 / altura; i++) {
        funcion_80044924(img, ancho, altura);
        funcion_8004B97C(parametro0 - (ancho / 2), variable_s3, ancho, altura, 1);
        img += (ancho * altura) / 2;
        variable_s3 += altura;
    }
}

void funcion_8004D37C(s32 parametro0, s32 parametro1, u8* textura, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6, s32 ancho, s32 parametro8,
                   SIN_USO s32 parametro9, s32 altura) {
    s32 variable_s3;
    u8* img;
    s32 i;

    variable_s3 = parametro1 - (parametro8 / 2);
    img = textura;
    gSPDisplayList(display_list_cabeza++, dato_0D007FE0);
    funcion_8004B414(parametro3, parametro4, parametro5, parametro6);

    for (i = 0; i < parametro8 / altura; i++) {
        funcion_80044F34(img, ancho, altura);
        funcion_8004B97C(parametro0 - (ancho / 2), variable_s3, ancho, altura, 1);
        img += (ancho * altura) / 2;
        variable_s3 += altura;
    }
}

void funcion_8004D4E8(s32 parametro0, s32 parametro1, u8* textura, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6, s32 ancho, s32 parametro8,
                   SIN_USO s32 parametro9, s32 altura) {
    s32 variable_s3;
    u8* img;
    s32 i;

    variable_s3 = parametro1 - (parametro8 / 2);
    img = textura;
    gSPDisplayList(display_list_cabeza++, dato_0D007FE0);
    funcion_8004B414(parametro3, parametro4, parametro5, parametro6);

    for (i = 0; i < parametro8 / altura; i++) {
        funcion_800450C8(img, ancho, altura);
        funcion_8004BA08(parametro0 - (ancho / 2), variable_s3, ancho, altura, 1);
        img += (ancho * altura) / 2;
        variable_s3 += altura;
    }
}

void funcion_8004D654(s32 parametro0, s32 parametro1, u8* textura, f32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6, SIN_USO s32 parametro7, s32 ancho,
                   s32 parametro9, SIN_USO s32 parametro_a, s32 altura) {
    s32 i;
    s32 variable_s3;
    u8* textura_copia;

    variable_s3 = parametro1 - (parametro9 / 2);
    textura_copia = textura;
    gSPDisplayList(display_list_cabeza++, dato_0D008000);
    funcion_8004B480(parametro4, parametro5, parametro6);
    for (i = 0; i < (parametro9 / altura); i++) {
        funcion_80044F34(textura_copia, ancho, altura);
        funcion_8004BB3C(parametro0, parametro1, ancho, parametro9, parametro3);
        textura_copia += (ancho * altura) / 2;
        variable_s3 += altura;
    }
}

void funcion_8004D7B4(s32 parametro0, s32 parametro1, u8* textura, s32 parametro3, s32 parametro4) {
    s32 sp5_c;
    f32 temporal_f20;
    s16 temporal_s7;
    s16 variable_s1;
    u16 temporal_s0;
    s32 temporal_s5;
    s32 variable_s3;
    u8* img;
    SIN_USO s32 probar[3];
    s32 i;

    dato_801656B0 += dato_80165710;
    temporal_f20 = dato_8018D00C;
    temporal_s7 = dato_80165708;
    variable_s1 = dato_801656B0;
    img = textura;
    variable_s3 = parametro1 - (parametro4 / 2);
    gSPDisplayList(display_list_cabeza++, dato_0D007FE0);

    sp5_c = parametro3 * 2;
    for (i = 0; i < parametro4; i++) {
        temporal_s0 = variable_s1;
        temporal_s5 = (s32) ((senos(temporal_s0) * temporal_f20) + (f32) (parametro0 - (parametro3 / 2)));
        senos(temporal_s0);
        cargar_nomirror_bloque_ia16_textura(img, parametro3, 1);
        funcion_8004B97C(temporal_s5, variable_s3, parametro3, 1, 1);

        variable_s1 += temporal_s7;
        variable_s3 += 1;
        img += sp5_c;
    }
}

void funcion_8004D93C(s32 parametro0, s32 parametro1, u8* textura, s32 parametro3, s32 parametro4) {
    f32 temporal_f20;
    s16 temporal_s7;
    s16 variable_s1;
    u16 temporal_s0;
    s32 temporal_s6;
    s32 variable_s4;
    u8* img;
    s32 i;
    s32 variable_;

    dato_801656B0 += dato_80165710;
    temporal_f20 = dato_8018D00C;
    temporal_s7 = dato_80165708;
    variable_s1 = dato_801656B0;
    img = textura;
    variable_ = parametro3 / 2;
    variable_s4 = parametro1 - (parametro4 / 2);

    gSPDisplayList(display_list_cabeza++, dato_0D007FE0);

    for (i = 0; i < parametro4; i++) {
        temporal_s0 = variable_s1;
        temporal_s6 = (s32) ((senos(temporal_s0) * temporal_f20) + (f32) (parametro0 - (variable_)));
        senos(temporal_s0);
        cargar_nomirror_bloque_ia8_textura(img, parametro3, 1);
        funcion_8004B97C(temporal_s6, variable_s4, parametro3, 1, 1);
        variable_s1 += temporal_s7;
        img = &img[parametro3];
        variable_s4 += 1;
    }
}

SIN_USO void funcion_8004DAB8(s32 parametro0, s32 parametro1, u8* textura, s32 parametro3, s32 parametro4) {
    f32 temporal_f20;
    s16 temporal_s7;
    s16 variable_s1;
    u16 temporal_s0;
    s32 temporal_s6;
    u8* img;
    s32 variable_s4;
    s32 variable_;
    s32 i;

    dato_801656B0 += dato_80165710;
    temporal_f20 = dato_8018D00C;
    temporal_s7 = dato_80165708;
    variable_s1 = (s16) dato_801656B0;
    img = textura;
    variable_ = parametro3 / 2;
    variable_s4 = parametro1 - (parametro4 / 2);

    gSPDisplayList(display_list_cabeza++, dato_0D007FE0);
    for (i = 0; i < parametro4; i++) {
        temporal_s0 = variable_s1;
        temporal_s6 = (s32) ((senos(temporal_s0) * temporal_f20) + (f32) (parametro0 - (variable_)));
        senos(temporal_s0);
        funcion_80044924(img, parametro3, 1);
        funcion_8004B97C(temporal_s6, variable_s4, parametro3, 1, 1);
        variable_s1 += temporal_s7;
        img += parametro3;
        variable_s4 += 1;
    }
}

SIN_USO void funcion_8004DC34(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004CF9C(parametro0, parametro1, textura, 8, 160, 8, 160);
}

SIN_USO void funcion_8004DC6C(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004CF9C(parametro0, parametro1, textura, 12, 160, 12, 160);
}

SIN_USO void funcion_8004DCA4(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004CF9C(parametro0, parametro1, textura, 12, 192, 12, 192);
}

SIN_USO void funcion_8004DCDC(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004CD48(parametro0, parametro1, textura, 16, 16, 16);
}

SIN_USO void funcion_8004DD0C(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004CF9C(parametro0, parametro1, textura, 16, 160, 16, 160);
}

SIN_USO void funcion_8004DD44(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004CD48(parametro0, parametro1, textura, 32, 32, 32);
}

SIN_USO void funcion_8004DD74(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004CF9C(parametro0, parametro1, textura, 32, 32, 32, 32);
}

SIN_USO void funcion_8004DDAC(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004D0D4(parametro0, parametro1, textura, 32, 32, 32);
}

SIN_USO void funcion_8004DDDC(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004D7B4(parametro0, parametro1, textura, 32, 32);
}

SIN_USO void funcion_8004DE04(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004D93C(parametro0, parametro1, textura, 32, 32);
}

SIN_USO void funcion_8004DE2C(s32 parametro0, s32 parametro1, u8* parametro2) {
    funcion_8004DAB8(parametro0, parametro1, parametro2, 32, 32);
}

SIN_USO void funcion_8004DE54(s32 parametro0, s32 parametro1, u8* parametro2) {
    funcion_8004CD48(parametro0, parametro1, parametro2, 64, 32, 32);
}

SIN_USO void funcion_8004DE84(s32 parametro0, s32 parametro1, u8* parametro2) {
    funcion_8004CD48(parametro0, parametro1, parametro2, 64, 64, 32);
}

SIN_USO void funcion_8004DEB4(s32 parametro0, s32 parametro1, u8* textura) {
    funcion_8004CF9C(parametro0, parametro1, textura, 64, 96, 64, 48);
}

SIN_USO void funcion_8004DEEC(s32 parametro0, s32 parametro1, u8* parametro2) {
    funcion_8004CF9C(parametro0, parametro1, parametro2, 112, 32, 112, 32);
}

SIN_USO void funcion_8004DF24(s32 parametro0, s32 parametro1, u8* parametro2) {
    funcion_8004CF9C(parametro0, parametro1, parametro2, 128, 32, 128, 32);
}

void funcion_8004DF5C(s32 parametro0, s32 parametro1, u8* textura, s32 ancho, s32 parametro4, s32 altura) {
    s32 variable_s0 = variable_s0 = parametro1 - (parametro4 / 2);
    u8* img = textura;
    s32 i;

    for (i = 0; i < parametro4 / altura; i++) {
        cargar_textura_rsp(img, ancho, altura);
        funcion_8004B97C(parametro0 - (ancho / 2), variable_s0, ancho, altura, 1);
        img += ancho * altura;
        variable_s0 += altura;
    }
}

void funcion_8004E06C(s32 parametro0, s32 parametro1, u8* textura, s32 parametro3, s32 parametro4) {
    f32 temporal_f20;
    s16 temporal_s7;
    s16 variable_s1;
    u16 temporal_s0;
    s32 variable_s4;
    u8* img;
    u32 temporal_s6;
    s32 i;
    s32 variable_;

    dato_801656B0 += dato_80165710;
    temporal_f20 = dato_8018D00C;
    variable_s1 = (s16) dato_801656B0;
    temporal_s7 = dato_80165708;
    img = textura;
    variable_ = parametro3 / 2;
    variable_s4 = parametro1 - (parametro4 / 2);

    for (i = 0; i < parametro4; i++) {
        temporal_s0 = variable_s1;
        temporal_s6 = (u32) ((senos(temporal_s0) * temporal_f20) + (f32) (parametro0 - variable_));
        senos(temporal_s0);
        cargar_textura_rsp(img, parametro3, 1);
        funcion_8004B97C(temporal_s6, variable_s4, parametro3, 1, 1);
        variable_s1 += temporal_s7;
        img += parametro3;
        variable_s4 += 1;
    }
}

SIN_USO void funcion_8004E238(void) {
}

void funcion_8004E240(s32 parametro0, s32 parametro1, u8* tlut, u8* textura, s32 parametro4, s32 parametro5, s32 parametro6) {
    gSPDisplayList(display_list_cabeza++, dato_0D007CB8);
    funcion_8004B05C(tlut);
    funcion_8004DF5C(parametro0, parametro1, textura, parametro4, parametro5, parametro6);
}

void funcion_8004E2B8(s32 parametro0, s32 parametro1, s32 parametro2, u8* tlut, u8* textura, s32 parametro5, s32 parametro6, s32 parametro7) {
    gSPDisplayList(display_list_cabeza++, dato_0D007DB8);
    fijar_transparencia(parametro2);
    funcion_8004B05C(tlut);
    funcion_8004DF5C(parametro0, parametro1, textura, parametro5, parametro6, parametro7);
}

void funcion_8004E338(s32 parametro0, s32 parametro1, u8* tlut, u8* textura, s32 parametro4, s32 parametro5) {
    gSPDisplayList(display_list_cabeza++, dato_0D007DB8);
    fijar_transparencia(dato_8016589C);
    funcion_8004B05C(tlut);
    funcion_8004E06C(parametro0, parametro1, textura, parametro4, parametro5);
}

SIN_USO void funcion_8004E3B8(void) {
}

SIN_USO void funcion_8004E3C0(s32 parametro0, s32 parametro1, u8* tlut, u8* textura, s32 parametro4, s32 parametro5, SIN_USO s32 parametro6, s32 parametro7) {
    funcion_8004E240(parametro0, parametro1, tlut, textura, parametro4, parametro5, parametro7);
}

SIN_USO void funcion_8004E3F4(s32 parametro0, s32 parametro1, s32 parametro2, u8* tlut, u8* textura, s32 parametro5, s32 parametro6, SIN_USO s32 parametro7,
                          s32 parametro8) {
    funcion_8004E2B8(parametro0, parametro1, parametro2, tlut, textura, parametro5, parametro6, parametro8);
}

SIN_USO void funcion_8004E430(s32 parametro0, s32 parametro1, u8* tlut, u8* textura) {
    funcion_8004E240(parametro0, parametro1, tlut, textura, 8, 128, 128);
}

SIN_USO void funcion_8004E464(s32 parametro0, s32 parametro1, u8* tlut, u8* textura) {
    funcion_8004E240(parametro0, parametro1, tlut, textura, 32, 32, 32);
}

SIN_USO void funcion_8004E498(s32 parametro0, s32 parametro1, u8* tlut, u8* textura) {
    funcion_8004E240(parametro0, parametro1, tlut, textura, 32, 64, 64);
}

void funcion_8004E4CC(s32 parametro0, s32 parametro1, u8* tlut, u8* textura) {
    funcion_8004E240(parametro0, parametro1, tlut, textura, 40, 32, 32);
}

SIN_USO void funcion_8004E500(s32 parametro0, s32 parametro1, u8* tlut, u8* textura) {
    funcion_8004E240(parametro0, parametro1, tlut, textura, 48, 48, 24);
}

SIN_USO void funcion_8004E534(s32 parametro0, s32 parametro1, u8* tlut, u8* textura) {
    funcion_8004E240(parametro0, parametro1, tlut, textura, 64, 32, 32);
}

SIN_USO void funcion_8004E568(s32 parametro0, s32 parametro1, u8* tlut, u8* textura) {
    funcion_8004E240(parametro0, parametro1, tlut, textura, 64, 64, 32);
}

SIN_USO void funcion_8004E59C(s32 parametro0, s32 parametro1, s32 parametro2, u8* tlut, u8* textura) {
    funcion_8004E2B8(parametro0, parametro1, parametro2, tlut, textura, 64, 64, 32);
}

SIN_USO void funcion_8004E5D8(s32 parametro0, s32 parametro1, u8* tlut, u8* parametro3) {
    funcion_8004E338(parametro0, parametro1, tlut, parametro3, 64, 64);
}

SIN_USO void funcion_8004E604(s32 parametro0, s32 parametro1, u8* tlut, u8* textura) {
    funcion_8004E240(parametro0, parametro1, tlut, textura, ANCHO_PANTALLA, ALTURA_PANTALLA, 6);
}

void dibujar_ventana_item(s32 id_jugador) {
    s32 indice_objeto;
    Objeto* objeto;
    jugador_hud* temporal_v0;

    indice_objeto = ventana_item_objeto_por_id_jugador[id_jugador];
    objeto = &lista_objeto[indice_objeto];
    if (objeto->state >= 2) {
        temporal_v0 = &h_ud_jugador[id_jugador];
        funcion_8004E4CC(temporal_v0->deslizamiento_caja_item_x + temporal_v0->caja_item_x, temporal_v0->deslizamiento_caja_item_y + temporal_v0->caja_item_y,
                      (u8*) objeto->t_lut_activo, objeto->textura_activo);
    }
}

void funcion_8004E6C4(s32 id_jugador) {
    s32 indice_objeto;
    Objeto* objeto;
    jugador_hud* temporal_v0;

    indice_objeto = ventana_item_objeto_por_id_jugador[id_jugador];
    objeto = &lista_objeto[indice_objeto];
    if (objeto->state >= 2) {
        temporal_v0 = &h_ud_jugador[id_jugador];
        funcion_80047910(temporal_v0->deslizamiento_caja_item_x + temporal_v0->caja_item_x, temporal_v0->deslizamiento_caja_item_y + temporal_v0->caja_item_y, 0U,
                      temporal_v0->escalado_desconocido, (u8*) objeto->t_lut_activo, (u8*) objeto->textura_activo, dato_0D005C30,
                      0x00000028, 0x00000020, 0x00000028, 0x00000020);
    }
}

void dibujar_cantidad_vuelta_simplificado(s32 id_jugador) {
    dibujar_textura_32x_hud_2d_8((s32) h_ud_jugador[id_jugador].vuelta_x, h_ud_jugador[id_jugador].vuelta_y + 3,
                             (u8*) comun_textura_hud_vuelta);
    dibujar_textura_32x_hud_2d_16(h_ud_jugador[id_jugador].vuelta_x + 0x1C, (s32) h_ud_jugador[id_jugador].vuelta_y,
                              (u8*) texturas_vuelta_hud[h_ud_jugador[id_jugador].cantidad_vuelta_tambien]);
}

void funcion_8004E800(s32 id_jugador) {
    if (h_ud_jugador[id_jugador].desconocido_81 != 0) {
        if (h_ud_jugador[id_jugador].cantidad_vuelta != 3) {
            funcion_8004A384(h_ud_jugador[id_jugador].puesto_x + h_ud_jugador[id_jugador].puesto_x_deslizamiento,
                          h_ud_jugador[id_jugador].puesto_y + h_ud_jugador[id_jugador].puesto_y_deslizamiento, 0U,
                          h_ud_jugador[id_jugador].escalado_puesto, 0x000000FF, dato_800E55F8[dato_8018CF98[id_jugador]], 0, 0x000000FF,
                          comun_textura_hud_lugar[dato_8018CF98[id_jugador]], dato_0D0068F0, 0x00000080, 0x00000040,
                          0x00000080, 0x00000040);
        } else {
            funcion_8004A384(h_ud_jugador[id_jugador].puesto_x + h_ud_jugador[id_jugador].puesto_x_deslizamiento,
                          h_ud_jugador[id_jugador].puesto_y + h_ud_jugador[id_jugador].puesto_y_deslizamiento, 0U,
                          h_ud_jugador[id_jugador].escalado_puesto, 0x000000FF, dato_800E55F8[dato_80165594], 0, 0x000000FF,
                          comun_textura_hud_lugar[gp_actual_carrera_puesto_por_id_jugador[id_jugador]], dato_0D0068F0, 0x00000080,
                          0x00000040, 0x00000080, 0x00000040);
        }
    }
}

void funcion_8004E998(s32 id_jugador) {
    if (h_ud_jugador[id_jugador].desconocido_81 != 0) {
        if (h_ud_jugador[id_jugador].cantidad_vuelta != 3) {
            funcion_8004A384(h_ud_jugador[id_jugador].puesto_x + h_ud_jugador[id_jugador].puesto_x_deslizamiento,
                          h_ud_jugador[id_jugador].puesto_y + h_ud_jugador[id_jugador].puesto_y_deslizamiento, 0U,
                          h_ud_jugador[id_jugador].escalado_puesto, 0x000000FF,
                          dato_800E5618[gp_actual_carrera_puesto_por_id_jugador[id_jugador]], 0, 0x000000FF,
                          dato_0D015258[gp_actual_carrera_puesto_por_id_jugador[id_jugador]], dato_0D006030, 0x00000040, 0x00000040,
                          0x00000040, 0x00000040);
        } else {
            funcion_8004A384(h_ud_jugador[id_jugador].puesto_x + h_ud_jugador[id_jugador].puesto_x_deslizamiento,
                          h_ud_jugador[id_jugador].puesto_y + h_ud_jugador[id_jugador].puesto_y_deslizamiento, 0U,
                          h_ud_jugador[id_jugador].escalado_puesto, 0x000000FF, dato_800E5618[dato_80165598], 0, 0x000000FF,
                          dato_0D015258[gp_actual_carrera_puesto_por_id_jugador[id_jugador]], dato_0D006030, 0x00000040, 0x00000040,
                          0x00000040, 0x00000040);
        }
    }
}

void funcion_8004EB30(SIN_USO s32 parametro0) {
}

void funcion_8004EB38(s32 id_jugador) {
    jugador_hud* temporal_s0;

    temporal_s0 = &h_ud_jugador[id_jugador];
    if ((u8) temporal_s0->desconocido_7B != 0) {
        funcion_8004C9D8(temporal_s0->tiempo_x_finalizacion_vuelta_1 - 0x13, temporal_s0->temporizador_y + 8, 0x00000080,
                      (u8*) comun_textura_hud_tiempo, 0x00000020, 0x00000010, 0x00000020, 0x00000010);
        funcion_8004F950((s32) temporal_s0->tiempo_x_finalizacion_vuelta_1, (s32) temporal_s0->temporizador_y, 0x00000080, (s32) temporal_s0->algun_temporizador);
    }
    if ((u8) temporal_s0->desconocido_7C != 0) {
        funcion_8004C9D8(temporal_s0->tiempo_x_finalizacion_vuelta_2 - 0x13, temporal_s0->temporizador_y + 8, 0x00000050,
                      (u8*) comun_textura_hud_tiempo, 0x00000020, 0x00000010, 0x00000020, 0x00000010);
        funcion_8004F950((s32) temporal_s0->tiempo_x_finalizacion_vuelta_2, (s32) temporal_s0->temporizador_y, 0x00000050, (s32) temporal_s0->algun_temporizador);
    }
    if ((u8) temporal_s0->desconocido_7E != 0) {
        funcion_8004C9D8((s32) temporal_s0->vuelta_despues_imagen_1_x, temporal_s0->vuelta_y + 3, 0x00000080, (u8*) comun_textura_hud_vuelta,
                      0x00000020, 8, 0x00000020, 8);
        funcion_8004C9D8(temporal_s0->vuelta_despues_imagen_1_x + 0x1C, (s32) temporal_s0->vuelta_y, 0x00000080,
                      (u8*) texturas_vuelta_hud[temporal_s0->cantidad_vuelta_tambien], 0x00000020, 0x00000010, 0x00000020, 0x00000010);
    }
    if ((u8) temporal_s0->desconocido_7F != 0) {
        funcion_8004C9D8((s32) temporal_s0->vuelta_despues_imagen_2_x, temporal_s0->vuelta_y + 3, 0x00000050, (u8*) comun_textura_hud_vuelta,
                      0x00000020, 8, 0x00000020, 8);
        funcion_8004C9D8(temporal_s0->vuelta_despues_imagen_2_x + 0x1C, (s32) temporal_s0->vuelta_y, 0x00000050,
                      (u8*) texturas_vuelta_hud[temporal_s0->cantidad_vuelta_tambien], 0x00000020, 0x00000010, 0x00000020, 0x00000010);
    }
}

void funcion_8004ED40(s32 parametro0) {
    funcion_8004A2F4(h_ud_jugador[parametro0].velocimetro_x, h_ud_jugador[parametro0].velocimetro_y, 0U, 1.0f, dato_8018D300, dato_8018D308,
                  dato_8018D310, 0xFF, velocimetro_textura_comun, dato_0D0064B0, 64, 96, 64, 48);
    funcion_8004A258(dato_8018CFEC, dato_8018CFF4, dato_8016579E, 1.0f, comun_textura_velocimetro_aguja, dato_0D005FF0, 0x40, 0x20,
                  0x40, 0x20);
}

void funcion_8004EE54(s32 parametro0) {
    if (es_modo_espejo != 0) {
        funcion_8004D4E8(minimapa_linea_meta_x[parametro0] + dato_8018D2F0, minimapa_linea_meta_y[parametro0] + dato_8018D2F8, (u8*) dato_8018D240,
                      (s32) dato_8018D300, (s32) dato_8018D308, (s32) dato_8018D310, 0x000000FF, (s32) dato_8018D2B0,
                      (s32) dato_8018D2B8, (s32) dato_8018D2B0, (s32) dato_8018D2B8);
    } else {
        funcion_8004D37C(minimapa_linea_meta_x[parametro0] + dato_8018D2F0, minimapa_linea_meta_y[parametro0] + dato_8018D2F8, (u8*) dato_8018D240,
                      (s32) dato_8018D300, (s32) dato_8018D308, (s32) dato_8018D310, 0x000000FF, (s32) dato_8018D2B0,
                      (s32) dato_8018D2B8, (s32) dato_8018D2B0, (s32) dato_8018D2B8);
    }
}

void funcion_8004EF9C(s32 parametro0) {
    s16 temporal_t0;
    s16 temporal_v0;

    temporal_v0 = dato_800E5548[parametro0 * 2];
    temporal_t0 = dato_800E5548[parametro0 * 2 + 1];
    funcion_8004D37C(0x00000104, 0x0000003C, dato_8018D248[parametro0], 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, temporal_v0,
                  temporal_t0, temporal_v0, temporal_t0);
}

void renderizar_minimapa_linea_meta(s32 parametro0) {
    f32 variable_f0;
    f32 variable_f2;

    variable_f2 = ((minimapa_linea_meta_x[parametro0] + dato_8018D2F0) - (dato_8018D2B0 / 2)) + minimapa_x;
    variable_f0 = ((minimapa_linea_meta_y[parametro0] + dato_8018D2F8) - (dato_8018D2B8 / 2)) + minimapa_y;
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) { /* irregular */
        case CIRCUITO_MARIO_RACEWAY:
            variable_f0 = variable_f0 - 2.0;
            break;
        case CIRCUITO_CHOCO_MOUNTAIN:
            variable_f0 = variable_f0 - 16.0;
            break;
        case CIRCUITO_KALAMARI_DESERT:
            variable_f0 = variable_f0 + 4.0;
            break;
    }
    dibujar_textura_8x_hud_2d_8(variable_f2, variable_f0, (u8*) minimapa_textura_comun_linea_meta);
#else

#endif
}

void dibujar_personaje_minimapa(s32 parametro0, s32 id_jugador, s32 id_personaje) {
    f32 cosa0;
    f32 cosa1;
    s16 x;
    s16 y;
    Jugador *jugador = &jugador_uno[id_jugador];

    if (jugador->type & (1 << 15)) {
        cosa0 = jugador->pos[0] * minimapa_escala_marcador;
        cosa1 = jugador->pos[2] * minimapa_escala_marcador;
        x = ((minimapa_linea_meta_x[parametro0] + dato_8018D2F0) - (dato_8018D2B0 / 2)) + minimapa_x + (s16)(cosa0);
        y = ((minimapa_linea_meta_y[parametro0] + dato_8018D2F8) - (dato_8018D2B8 / 2)) + minimapa_y + (s16)(cosa1);
        if (id_personaje != 8) {
            if ((gp_actual_carrera_puesto_por_id_jugador[id_jugador] == 0) && (seleccion_modo != 3) && (seleccion_modo != 1)) {
                funcion_80046424(x, y, jugador->rotacion[1] + GRADOS(180), 1.0f, (u8*)&comun_textura_minimapa_kart_mario[id_personaje * 64], comun_vtx_jugador_minimapa_icono, 8, 8, 8, 8);
            } else {
                funcion_800463B0(x, y, jugador->rotacion[1] + GRADOS(180), 1.0f, (u8*)&comun_textura_minimapa_kart_mario[id_personaje * 64], comun_vtx_jugador_minimapa_icono, 8, 8, 8, 8);
            }
        } else {
            if (gp_actual_carrera_puesto_por_id_jugador[id_jugador] == 0) {
                funcion_8004C450(x, y, 8, 8, (u8 *) comun_textura_minimapa_progreso_punto);
            } else {
                dibujar_textura_hud_2d(x, y, 8, 8, (u8 *) comun_textura_minimapa_progreso_punto);
            }
        }
    }
}

void funcion_8004F3E4(s32 parametro0) {
    SIN_USO Jugador* jugador;
    s32 id_jugador;
    s32 idx;

    switch (seleccion_modo) { /* irregular */
        case GRAN_PREMIO:
            for (idx = dato_8018D158 - 1; idx >= 0; idx--) {
                id_jugador = gp_actual_carrera_jugador_id_por_puesto[idx];
                if ((jugador_uno + id_jugador)->type & CPU_JUGADOR) {
                    dibujar_personaje_minimapa(parametro0, id_jugador, 8);
                }
            }
            for (idx = dato_8018D158 - 1; idx >= 0; idx--) {
                id_jugador = gp_actual_carrera_jugador_id_por_puesto[idx];
                if (((jugador_uno + id_jugador)->type & CPU_JUGADOR) != CPU_JUGADOR) {
                    dibujar_personaje_minimapa(parametro0, id_jugador, (jugador_uno + id_jugador)->id_personaje);
                }
            }
            break;
        case CONTRARRELOJ:
            for (idx = 0; idx < 8; idx++) {
                if (((jugador_uno + idx)->type & INVISIBLE_JUGADOR_O_BOMBA) == INVISIBLE_JUGADOR_O_BOMBA) {
                    dibujar_personaje_minimapa(parametro0, idx, 8);
                }
            }
            dibujar_personaje_minimapa(parametro0, 0, jugador_uno->id_personaje);
            break;
        case VERSUS:
            for (idx = seleccion_cantidad_jugador_1 - 1; idx >= 0; idx--) {
                id_jugador = gp_actual_carrera_jugador_id_por_puesto[idx];
                dibujar_personaje_minimapa(parametro0, id_jugador, (jugador_uno + id_jugador)->id_personaje);
            }
            break;
        case BATALLA:
            for (idx = 0; idx < seleccion_cantidad_jugador_1; idx++) {
                if (!((jugador_uno + idx)->type & jugador_desconocido_0_x40)) {
                    dibujar_personaje_minimapa(parametro0, idx, (jugador_uno + idx)->id_personaje);
                }
            }
            break;
    }
}

s32 funcion_8004F674(s32* parametro0, s32 parametro1) {
    s32 temporal_v0;
    s32 devuelto;

    temporal_v0 = *parametro0;
    if (temporal_v0 != 0) {
        devuelto = temporal_v0 / parametro1;
        *parametro0 = temporal_v0 % parametro1;
    } else {
        *parametro0 = 0;
        devuelto = 0;
    }
    return devuelto;
}

void funcion_8004F6D0(s32 parametro0) {
    SIN_USO s32 margen_pila_0;
    SIN_USO s32 margen_pila_1;
    s32 sp24;

    sp24 = parametro0;
    if (parametro0 >= 599999) {
        sp24 = 599999;
    }
    dato_801657D0[0] = funcion_8004F674(&sp24, 60000);
    dato_801657D0[1] = funcion_8004F674(&sp24, 6000);
    dato_801657D0[3] = funcion_8004F674(&sp24, 1000);
    dato_801657D0[4] = funcion_8004F674(&sp24, 100);
    dato_801657D0[6] = funcion_8004F674(&sp24, 10);
    dato_801657D0[7] = sp24;
    dato_801657D0[2] = 10;
    dato_801657D0[5] = 11;
}

void funcion_8004F774(s32 parametro0, s32 parametro1) {
    s32 i;
    s32 phi_s1 = parametro0;

    for (i = 0; i < 8; i++) {
        funcion_8004BA98(phi_s1, parametro1, 8, 16, dato_801657D0[i] * 8, 0, 0);
        phi_s1 += 8;
    }
}

void imprimir_temporizador(s32 parametro0, s32 parametro1, s32 parametro2) {
    gSPDisplayList(display_list_cabeza++, dato_0D008108);
    gSPDisplayList(display_list_cabeza++, dato_0D007EF8);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_THRESHOLD);
    cargar_textura_bloque_rgba16_espejo((u8*) comun_textura_hud_normal_digito, 104, 16);
    funcion_8004F6D0(parametro2);
    funcion_8004F774(parametro0, parametro1);
    gSPDisplayList(display_list_cabeza++, dato_0D007EB8);
}

void funcion_8004F8CC(s32 parametro0, s32 parametro1) {
    s32 phi_s1 = parametro0;
    s32 i;

    for (i = 0; i < 8; i++) {
        funcion_8004BA98(phi_s1, parametro1, 8, 16, dato_801657D0[i] * 8, 0, 1);
        phi_s1 += 8;
    }
}

void funcion_8004F950(s32 parametro0, s32 parametro1, s32 parametro2, s32 parametro3) {
    gSPDisplayList(display_list_cabeza++, dato_0D007F38);
    fijar_transparencia(parametro2);
    cargar_textura_bloque_rgba16_espejo((u8*) comun_textura_hud_normal_digito, 104, 16);
    funcion_8004F6D0(parametro3);
    funcion_8004F8CC(parametro0, parametro1);
}

void imprimir_rainbow_temporizador(s32 parametro0, s32 parametro1, s32 parametro2) {
    gSPDisplayList(display_list_cabeza++, dato_0D007F38);
    funcion_8004B614(dato_801656C0, dato_801656D0, dato_801656E0, 128, 128, 128, 255);
    cargar_textura_bloque_rgba16_espejo((u8*) comun_textura_hud_normal_digito, 104, 16);
    funcion_8004F6D0(parametro2);
    funcion_8004F8CC(parametro0, parametro1);
}

void renderizar_temporizador_hud(s32 id_jugador) {
    s32 variable_s0;

    if ((seleccion_modo != 2) && (seleccion_modo != 3)) {
        if (dato_8018D320 == h_ud_jugador[id_jugador].cantidad_vuelta) {
            if (dato_8015F890 == 0) {
                for (variable_s0 = 0; variable_s0 < 3; variable_s0++) {
                    if (dato_80165658[variable_s0] == 0) {
                        imprimir_temporizador(h_ud_jugador[id_jugador].vuelta_finalizacion_tiempo_xs[variable_s0],
                                    h_ud_jugador[id_jugador].temporizador_y + (variable_s0 * 0x10),
                                    h_ud_jugador[id_jugador].duraciones_vuelta[variable_s0]);
                    } else {
                        imprimir_rainbow_temporizador(h_ud_jugador[id_jugador].vuelta_finalizacion_tiempo_xs[variable_s0],
                                            h_ud_jugador[id_jugador].temporizador_y + (variable_s0 * 0x10),
                                            h_ud_jugador[id_jugador].duraciones_vuelta[variable_s0]);
                    }
                }
                dibujar_textura_32x_hud_2d_16(h_ud_jugador[id_jugador].tiempo_x_total - 0x13, h_ud_jugador[id_jugador].temporizador_y + 0x38,
                                          (u8*) comun_textura_hud_total_tiempo);
                if (dato_801657E5 != 0) {
                    imprimir_rainbow_temporizador(h_ud_jugador[id_jugador].tiempo_x_total, h_ud_jugador[id_jugador].temporizador_y + 0x30,
                                        h_ud_jugador[id_jugador].algun_temporizador);
                } else {
                    imprimir_temporizador(h_ud_jugador[id_jugador].tiempo_x_total, h_ud_jugador[id_jugador].temporizador_y + 0x30,
                                h_ud_jugador[id_jugador].algun_temporizador);
                }
            }
        } else {
            if (h_ud_jugador[id_jugador].temporizador_parpadear == 0) {
                dibujar_textura_32x_hud_2d_16(h_ud_jugador[id_jugador].temporizador_x - 0x13, h_ud_jugador[id_jugador].temporizador_y + 8,
                                          (u8*) comun_textura_hud_tiempo);
                imprimir_temporizador(h_ud_jugador[id_jugador].temporizador_x, h_ud_jugador[id_jugador].temporizador_y, h_ud_jugador[id_jugador].algun_temporizador);
            } else {
                dibujar_textura_32x_hud_2d_16(h_ud_jugador[id_jugador].temporizador_x - 0x13, h_ud_jugador[id_jugador].temporizador_y + 8,
                                          (u8*) comun_textura_hud_vuelta_tiempo);
                if (dato_801657E3 != 0) {
                    imprimir_rainbow_temporizador(h_ud_jugador[id_jugador].temporizador_x, h_ud_jugador[id_jugador].temporizador_y,
                                        h_ud_jugador[id_jugador].algun_temporizador_1);
                } else if (h_ud_jugador[id_jugador].estado_parpadear == 0) {
                    imprimir_temporizador(h_ud_jugador[id_jugador].temporizador_x, h_ud_jugador[id_jugador].temporizador_y, h_ud_jugador[id_jugador].algun_temporizador_1);
                }
            }
        }
    }
}

void dibujar_cantidad_vuelta(s16 vuelta_x, s16 vuelta_y, s8 vuelta) {
    gSPDisplayList(display_list_cabeza++, dato_0D008108);
    gSPDisplayList(display_list_cabeza++, dato_0D007EF8);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_THRESHOLD);
    cargar_textura_bloque_rgba16_espejo((u8*) hud_textura_comun_123, 32, 8);

    funcion_8004BA98(vuelta_x, vuelta_y, 8, 8, vuelta * 8, 0, 0);
    funcion_8004BA98(vuelta_x + 8, vuelta_y, 8, 8, 24, 0, 0);
    funcion_8004BA98(vuelta_x + 16, vuelta_y, 8, 8, 16, 0, 0);
    gSPDisplayList(display_list_cabeza++, dato_0D007EB8);
}

void funcion_8004FDB4(f32 parametro0, f32 parametro1, s16 parametro2, s16 parametro3, s16 id_personaje, s32 parametro5, s32 parametro6, s32 parametro7, s32 parametro8) {
    if ((id_circuito_actual == CIRCUITO_YOSHI_VALLEY) && (parametro3 < 3) && (parametro8 == 0)) {
        funcion_80042330((s32) parametro0, (s32) parametro1, 0U, 1.0f);
        gSPDisplayList(display_list_cabeza++, dato_0D007DB8);
        funcion_8004B35C(0x000000FF, 0x000000FF, 0x000000FF, dato_8018D3E0);
        gDPLoadTLUT_pal256(display_list_cabeza++, retrato_tlut_comun_kart_bomba_y_signo_pregunta);
        cargar_textura_rsp(retrato_textura_comun_signo_pregunta, 0x00000020, 0x00000020);
        gSPDisplayList(display_list_cabeza++, dato_0D0069E0);
    } else {
        funcion_80042330(parametro0, parametro1, 0U, 1.0f);
        gSPDisplayList(display_list_cabeza++, dato_0D007DB8);
        funcion_8004B35C(0x000000FF, 0x000000FF, 0x000000FF, parametro5);
        gDPLoadTLUT_pal256(display_list_cabeza++, ts_tlu_retrato[id_personaje]);
        cargar_textura_rsp(texturas_retrato[id_personaje], 0x00000020, 0x00000020);
        if (parametro7 != 0) {
            gSPDisplayList(display_list_cabeza++, dato_0D0069F8);
        } else {
            gSPDisplayList(display_list_cabeza++, dato_0D0069E0);
        }
        if (parametro6 != 0) {
            funcion_80042330(parametro0, parametro1, 0U, 1.0f);
            gSPDisplayList(display_list_cabeza++, dato_0D007A60);
            funcion_8004B35C(dato_8018D3E4, dato_8018D3E8, dato_8018D3EC, 0x000000FF);
            funcion_80044924(comun_textura_personaje_retrato_borde, 0x20, 0x20);
            gSPDisplayList(display_list_cabeza++, dato_0D0069E0);
        }
        gSPDisplayList(display_list_cabeza++, dato_0D007DB8);
        funcion_8004B35C(0x000000FF, 0x000000FF, 0x000000FF, parametro5);
        gSPDisplayList(display_list_cabeza++, dato_0D007CB8);
        gDPLoadTLUT_pal256(display_list_cabeza++, comun_tlut_hud_tipo_c_puesto_fuente);
        cargar_textura_rsp(comun_textura_hud_tipo_c_puesto_fuente[parametro2], 0x00000010, 0x00000010);
        if (parametro7 != 0) {
            funcion_80042330((s32) (parametro0 + 9.0f), (s32) (parametro1 + 7.0f), 0U, 1.0f);
        } else {
            funcion_80042330((s32) (parametro0 - 9.0f), (s32) (parametro1 + 7.0f), 0U, 1.0f);
        }
        gSPDisplayList(display_list_cabeza++, dato_0D006980);
    }
}
