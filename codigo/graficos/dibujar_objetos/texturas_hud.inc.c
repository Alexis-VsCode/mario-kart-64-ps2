// Texturas hud

SIN_USO void funcion_80048AB4(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 parametro4, u8* tlut, u8* textura, Vtx* parametro7) {
    funcion_80047B9C(parametro0, parametro1, parametro2, parametro3, parametro4, tlut, textura, parametro7, 64, 64, 64, 32);
}

SIN_USO void funcion_80048B24(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 parametro4, u8* tlut, u8* textura, Vtx* parametro7) {
    funcion_80047CB4(parametro0, parametro1, parametro2, parametro3, parametro4, tlut, textura, parametro7, 64, 64, 64, 32);
}

SIN_USO void funcion_80048B94(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5) {
    funcion_80047E48(parametro0, parametro1, parametro2, tlut, textura, parametro5, 64, 64, 64, 32);
}

SIN_USO void funcion_80048BE8(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5) {
    funcion_80047F40(parametro0, parametro1, parametro2, tlut, textura, parametro5, 64, 64, 64, 32);
}

SIN_USO void funcion_80048C3C(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5) {
    dibujar_2d_textura_en(parametro0, parametro1, parametro2, tlut, textura, parametro5, 64, 64, 64, 32);
}

SIN_USO void funcion_80048C90(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_800482AC(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 64, 64, 64, 32);
}

SIN_USO void funcion_80048CEC(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_800483B4(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 64, 64, 64, 32);
}

SIN_USO void funcion_80048D48(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_800484BC(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 64, 64, 64, 32);
}

SIN_USO void funcion_80048DA4(Vec3f parametro0, Vec3su parametro1, f32 parametro2, s32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_80048540(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 64, 64, 64, 32);
}

SIN_USO void funcion_80048E00(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_80047910(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 72, 48, 72, 24);
}

SIN_USO void funcion_80048E68(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_80047A18(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 72, 48, 72, 24);
}

SIN_USO void funcion_80048ED0(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* tlut, u8* textura, Vtx* parametro6) {
    funcion_80047A9C(parametro0, parametro1, parametro2, parametro3, tlut, textura, parametro6, 72, 48, 72, 24);
}

SIN_USO void funcion_80048F38(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* tlut, u8* textura, Vtx* parametro5) {
    dibujar_2d_textura_en(parametro0, parametro1, parametro2, tlut, textura, parametro5, 72, 48, 72, 24);
}

void funcion_80048F8C(u8* textura, Vtx* parametro1, s32 parametro2, s32 parametro3, s32 ancho, s32 altura) {
    s32 indice_altura;
    s32 indice_ancho;
    s32 indice_vertice = 0;
    u8* img = textura;

    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        for (indice_ancho = 0; indice_ancho < parametro2 / ancho; indice_ancho++) {
            cargar_nomirror_bloque_ia16_textura(img, ancho, altura);
            gSPVertex(display_list_cabeza++, &parametro1[indice_vertice], 4, 0);
            gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
            img += ancho * altura * 2;
            indice_vertice += 4;
        }
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_80049130(u8* textura, Vtx* parametro1, s32 parametro2, s32 parametro3, s32 ancho, s32 altura) {
    s32 indice_altura;
    s32 indice_ancho;
    s32 indice_vertice = 0;
    u8* img = textura;

    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        for (indice_ancho = 0; indice_ancho < parametro2 / ancho; indice_ancho++) {
            cargar_nomirror_tile_ia16_textura(img, ancho, altura);
            gSPVertex(display_list_cabeza++, &parametro1[indice_vertice], 4, 0);
            gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
            img += ancho * altura * 2;
            indice_vertice += 4;
        }
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_800492D4(u8* textura, Vtx* parametro1, s32 parametro2, s32 parametro3, s32 ancho, s32 altura) {
    s32 indice_altura;
    s32 indice_ancho;
    s32 indice_vertice = 0;
    u8* img = textura;

    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        for (indice_ancho = 0; indice_ancho < parametro2 / ancho; indice_ancho++) {
            cargar_nomirror_bloque_ia8_textura(img, ancho, altura);
            gSPVertex(display_list_cabeza++, &parametro1[indice_vertice], 4, 0);
            gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
            img += ancho * altura;
            indice_vertice += 4;
        }
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_80049478(u8* textura, Vtx* parametro1, s32 parametro2, s32 parametro3, s32 ancho, s32 altura) {
    s32 indice_altura;
    s32 indice_ancho;
    s32 indice_vertice = 0;
    u8* img = textura;

    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        for (indice_ancho = 0; indice_ancho < parametro2 / ancho; indice_ancho++) {
            cargar_nomirror_tile_ia8_textura(img, ancho, altura);
            gSPVertex(display_list_cabeza++, &parametro1[indice_vertice], 4, 0);
            gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
            img += ancho * altura;
            indice_vertice += 4;
        }
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_8004961C(u8* textura, Vtx* parametro1, s32 parametro2, s32 parametro3, s32 ancho, s32 altura) {
    s32 i;
    s32 j;
    s32 variable_s2 = 0;
    u8* img = textura;

    for (i = 0; i < parametro3 / altura; i++) {
        for (j = 0; j < parametro2 / ancho; j++) {

            funcion_80044924(img, ancho, altura);
            gSPVertex(display_list_cabeza++, &parametro1[variable_s2], 4, 0);
            gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
            img += (ancho * altura) / 2;
            variable_s2 += 4;
        }
    }

    gSPTexture(display_list_cabeza++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_800497CC(u8* textura, Vtx* parametro1, s32 parametro2, s32 parametro3, s32 ancho, s32 altura) {
    s32 indice_altura;
    s32 indice_ancho;
    s32 indice_vertice = 0;
    u8* img = textura;

    for (indice_altura = 0; indice_altura < parametro3 / altura; indice_altura++) {
        for (indice_ancho = 0; indice_ancho < parametro2 / ancho; indice_ancho++) {
            funcion_80044BF8(img, ancho, altura);
            gSPVertex(display_list_cabeza++, &parametro1[indice_vertice], 4, 0);
            gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
            img += ancho * altura;
            indice_vertice += 4;
        }
    }
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_80049970(u8* textura, Vtx* parametro1, s32 parametro2, s32 parametro3, s32 ancho, s32 altura) {
    s32 i;
    s32 j;
    s32 variable_s2 = 0;
    u8* img = textura;

    for (i = 0; i < parametro3 / altura; i++) {
        for (j = 0; j < parametro2 / ancho; j++) {
            funcion_80044DA0(img, ancho, altura);
            gSPVertex(display_list_cabeza++, &parametro1[variable_s2], 4, 0);
            gSPDisplayList(display_list_cabeza++, pantalla_rectangulo_comun);
            img += (ancho * altura) / 2;
            variable_s2 += 4;
        }
    }
    gSPTexture(display_list_cabeza++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_80049B20(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A40);
    funcion_80048F8C(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

SIN_USO void funcion_80049B9C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                          s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A40);
    funcion_80049130(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void funcion_80049C18(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A40);
    funcion_800492D4(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void funcion_80049C94(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A60);
    funcion_800492D4(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void funcion_80049D10(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A80);
    funcion_800492D4(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void funcion_80049D8C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007AA0);
    funcion_800492D4(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

SIN_USO void funcion_80049E08(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 rojo, s32 verde, s32 azul, s32 alpha, u8* textura,
                          Vtx* parametro9, s32 parametro_a, s32 parametro_b, s32 parametro_c, s32 parametro_d) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A40);
    funcion_8004B35C(rojo, verde, azul, alpha);
    funcion_800492D4(textura, parametro9, parametro_a, parametro_b, parametro_c, parametro_d);
}

SIN_USO void funcion_80049E98(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 rojo, s32 verde, s32 azul, s32 alpha, u8* textura,
                          Vtx* parametro9, s32 parametro_a, s32 parametro_b, s32 parametro_c, s32 parametro_d) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A60);
    funcion_8004B35C(rojo, verde, azul, alpha);
    funcion_800492D4(textura, parametro9, parametro_a, parametro_b, parametro_c, parametro_d);
}

SIN_USO void funcion_80049F28(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 rojo, s32 verde, s32 azul, s32 alpha, u8* textura,
                          Vtx* parametro9, s32 parametro_a, s32 parametro_b, s32 parametro_c, s32 parametro_d) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007B00);
    funcion_8004B35C(rojo, verde, azul, alpha);
    funcion_800492D4(textura, parametro9, parametro_a, parametro_b, parametro_c, parametro_d);
}

SIN_USO void funcion_80049FB8(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                          s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A40);
    funcion_80049478(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

SIN_USO void funcion_8004A034(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                          s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A60);
    funcion_80049478(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void funcion_8004A0B0(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A40);
    funcion_8004961C(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

SIN_USO void funcion_8004A12C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 rojo, s32 verde, s32 azul, s32 alpha, u8* textura,
                          Vtx* parametro9, s32 parametro_a, s32 parametro_b, s32 parametro_c, s32 parametro_d) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A60);
    funcion_8004B35C(rojo, verde, azul, alpha);
    funcion_8004961C(textura, parametro9, parametro_a, parametro_b, parametro_c, parametro_d);
}
SIN_USO void funcion_8004A1BC(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                          s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A40);
    gDPSetCombineLERP(display_list_cabeza++, 1, 0, SHADE, 0, 0, 0, 0, TEXEL0, 1, 0, SHADE, 0, 0, 0, 0, TEXEL0);
    funcion_80049970(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void funcion_8004A258(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5, s32 parametro6, s32 parametro7, s32 parametro8,
                   s32 parametro9) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A60);
    gDPSetCombineLERP(display_list_cabeza++, 1, 0, SHADE, 0, 0, 0, 0, TEXEL0, 1, 0, SHADE, 0, 0, 0, 0, TEXEL0);
    funcion_80049970(textura, parametro5, parametro6, parametro7, parametro8, parametro9);
}

void funcion_8004A2F4(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 rojo, s32 verde, s32 azul, s32 alpha, u8* textura,
                   Vtx* parametro9, s32 parametro_a, s32 parametro_b, s32 parametro_c, s32 parametro_d) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A40);
    funcion_8004B414(rojo, verde, azul, alpha);
    funcion_80049970(textura, parametro9, parametro_a, parametro_b, parametro_c, parametro_d);
}

void funcion_8004A384(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, s32 rojo, s32 verde, s32 azul, s32 alpha, u8* textura,
                   Vtx* parametro9, s32 parametro_a, s32 parametro_b, s32 parametro_c, s32 parametro_d) {
    funcion_80042330(parametro0, parametro1, parametro2, parametro3);
    gSPDisplayList(display_list_cabeza++, dato_0D007A60);
    funcion_8004B414(rojo, verde, azul, alpha);
    funcion_80049970(textura, parametro9, parametro_a, parametro_b, parametro_c, parametro_d);
}

void funcion_8004A414(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6, s32 parametro7, s32 parametro8) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007A40);
    funcion_800492D4(textura, parametro4, parametro5, parametro6, parametro7, parametro8);
}

SIN_USO void funcion_8004A488(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6, s32 parametro7,
                          s32 parametro8) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007A60);
    funcion_800492D4(textura, parametro4, parametro5, parametro6, parametro7, parametro8);
}

SIN_USO void funcion_8004A4FC(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6, s32 parametro7,
                          s32 parametro8) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007AC0);
    funcion_800492D4(textura, parametro4, parametro5, parametro6, parametro7, parametro8);
}

SIN_USO void funcion_8004A570(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6, s32 parametro7,
                          s32 parametro8) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007AE0);
    funcion_800492D4(textura, parametro4, parametro5, parametro6, parametro7, parametro8);
}

SIN_USO void funcion_8004A5E4(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4) {
    funcion_8004A414(parametro0, parametro1, parametro2, textura, parametro4, 16, 16, 16, 16);
}

void funcion_8004A630(Colision* parametro0, Vec3f parametro1, f32 parametro2) {
    if (funcion_80041924(parametro0, parametro1) != 0) {
        dato_80183E50[0] = parametro1[0];
        dato_80183E50[1] = calcular_altura_superficie(parametro1[0], 0.0f, parametro1[2], parametro0->indice_zx_malla) + 0.8;
        dato_80183E50[2] = parametro1[2];
        fijar_matriz_trasl_rot_escala_rsp(dato_80183E50, parametro0->vector_orientacion, parametro2);
        gSPDisplayList(display_list_cabeza++, dato_0D007B98);
    }
}

void funcion_8004A6EC(s32 indice_objeto, f32 escalar) {
    Objeto* objeto;

    if ((es_obj_bandera_situacion_activo(indice_objeto, 0x00000020) != 0) &&
        (es_obj_bandera_situacion_activo(indice_objeto, 0x00800000) != 0)) {
        objeto = &lista_objeto[indice_objeto];
        dato_80183E50[0] = objeto->pos[0];
        dato_80183E50[1] = objeto->altura_superficie + 0.8;
        dato_80183E50[2] = objeto->pos[2];
        fijar_transformacion_matriz_rsp(dato_80183E50, objeto->desconocido_0B8, escalar);
        gSPDisplayList(display_list_cabeza++, dato_0D007B20);
    }
}

void funcion_8004A7AC(s32 indice_objeto, f32 parametro1) {
    Objeto* objeto;

    if (es_obj_bandera_situacion_activo(indice_objeto, 0x00000020) != 0) {
        objeto = &lista_objeto[indice_objeto];
        dato_80183E50[0] = objeto->pos[0];
        dato_80183E50[1] = objeto->altura_superficie + 0.8;
        dato_80183E50[2] = objeto->pos[2];
        dato_80183E98[0] = 0x4000;
        dato_80183E98[1] = 0;
        dato_80183E98[2] = 0;
        fijar_transformacion_matriz_rsp(dato_80183E50, dato_80183E98, parametro1);
        gSPDisplayList(display_list_cabeza++, dato_0D007B20);
    }
}

void funcion_8004A870(s32 indice_objeto, f32 parametro1) {
    Mat4 sp30;
    Objeto* objeto;

    if ((es_obj_bandera_situacion_activo(indice_objeto, 0x00000020) != 0) &&
        (es_obj_bandera_situacion_activo(indice_objeto, 0x00800000) != 0)) {
        objeto = &lista_objeto[indice_objeto];
        dato_80183E50[0] = objeto->pos[0];
        dato_80183E50[1] = objeto->altura_superficie + 0.8;
        dato_80183E50[2] = objeto->pos[2];
        transformar_matriz_conjunto(sp30, objeto->desconocido_01C, dato_80183E50, 0U, parametro1);
        convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], sp30);
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(display_list_cabeza++, dato_0D007B98);
    }
}

void funcion_8004A9B8(f32 parametro0) {
    fijar_matriz_trasl_rot_escala_rsp(dato_80183E50, dato_80183E70, parametro0);
    gSPDisplayList(display_list_cabeza++, dato_0D007C10);
}

SIN_USO void funcion_8004AA10(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4, s32 parametro5, s32 parametro6, s32 parametro7,
                          s32 parametro8) {
    fijar_transformacion_matriz_rsp(parametro0, parametro1, parametro2);
    gSPDisplayList(display_list_cabeza++, dato_0D007AE0);
    funcion_8004B6C4(dato_80165860, dato_8016586C, dato_80165878);
    funcion_800497CC(textura, parametro4, parametro5, parametro6, parametro7, parametro8);
}

SIN_USO void funcion_8004AAA0(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5) {
    funcion_80049B20(parametro0, parametro1, parametro2, parametro3, textura, parametro5, 16, 16, 16, 16);
}

SIN_USO void funcion_8004AB00(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5) {
    funcion_80049C18(parametro0, parametro1, parametro2, parametro3, textura, parametro5, 16, 16, 16, 16);
}

SIN_USO void funcion_8004AB60(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* parametro4, Vtx* parametro5) {
    funcion_8004A0B0(parametro0, parametro1, parametro2, parametro3, parametro4, parametro5, 16, 16, 16, 16);
}

SIN_USO void funcion_8004ABC0(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5) {
    funcion_80049B20(parametro0, parametro1, parametro2, parametro3, textura, parametro5, 32, 32, 32, 32);
}

SIN_USO void funcion_8004AC20(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* parametro4, Vtx* parametro5) {
    funcion_80049C18(parametro0, parametro1, parametro2, parametro3, parametro4, parametro5, 32, 32, 32, 32);
}

SIN_USO void funcion_8004AC80(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* parametro4, Vtx* parametro5) {
    funcion_8004A0B0(parametro0, parametro1, parametro2, parametro3, parametro4, parametro5, 32, 32, 32, 32);
}

SIN_USO void funcion_8004ACE0(Vec3f parametro0, Vec3su parametro1, f32 parametro2, u8* textura, Vtx* parametro4) {
    funcion_8004A414(parametro0, parametro1, parametro2, textura, parametro4, 32, 32, 32, 32);
}

SIN_USO void funcion_8004AD2C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5) {
    funcion_80049B20(parametro0, parametro1, parametro2, parametro3, textura, parametro5, 64, 32, 64, 32);
}

SIN_USO void funcion_8004AD8C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* parametro4, Vtx* parametro5) {
    funcion_80049C18(parametro0, parametro1, parametro2, parametro3, parametro4, parametro5, 64, 32, 64, 32);
}

SIN_USO void funcion_8004ADEC(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* parametro4, Vtx* parametro5) {
    funcion_80049C94(parametro0, parametro1, parametro2, parametro3, parametro4, parametro5, 64, 32, 64, 32);
}

SIN_USO void funcion_8004AE4C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5) {
    funcion_80049D10(parametro0, parametro1, parametro2, parametro3, textura, parametro5, 64, 32, 64, 32);
}

SIN_USO void funcion_8004AEAC(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5) {
    funcion_80049D8C(parametro0, parametro1, parametro2, parametro3, textura, parametro5, 64, 32, 64, 32);
}

SIN_USO void funcion_8004AF0C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5) {
    funcion_80049C18(parametro0, parametro1, parametro2, parametro3, textura, parametro5, 64, 64, 64, 64);
}

SIN_USO void funcion_8004AF6C(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5) {
    funcion_80049B20(parametro0, parametro1, parametro2, parametro3, textura, parametro5, 64, 64, 64, 32);
}

SIN_USO void funcion_8004AFCC(s32 parametro0, s32 parametro1, u16 parametro2, f32 parametro3, u8* textura, Vtx* parametro5) {
    funcion_80049C18(parametro0, parametro1, parametro2, parametro3, textura, parametro5, 64, 96, 64, 48);
}

SIN_USO void funcion_8004B02C(void) {
    gDPSetRenderMode(display_list_cabeza++,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                         GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA),
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
}

void funcion_8004B05C(u8* tlut) {
    gDPLoadTLUT_pal256(display_list_cabeza++, tlut);
    gDPLoadSync(display_list_cabeza++);
    gDPSetTexturePersp(display_list_cabeza++, G_TP_NONE);
}

void funcion_8004B138(s32 rojo, s32 verde, s32 azul, s32 alpha) {
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, alpha);
}

SIN_USO void funcion_8004B180(s32 rojo, s32 verde, s32 azul, s32 alpha) {
    gDPSetEnvColor(display_list_cabeza++, rojo, verde, azul, alpha);
}

void renderizar_color_conjunto(s32 prim_rojo, s32 verde_prim, s32 azul_prim, s32 amb_rojo, s32 verde_amb, s32 azul_amb, s32 prim_alpha) {
    gDPSetPrimColor(display_list_cabeza++, 0, 0, prim_rojo, verde_prim, azul_prim, prim_alpha);
    gDPSetEnvColor(display_list_cabeza++, amb_rojo, verde_amb, azul_amb, 0xFF);
}

SIN_USO void funcion_8004B254(s32 rojo, s32 verde, s32 azul) {
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, 0xFF);
}

void fijar_transparencia(s32 alpha) {
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
}

void funcion_8004B310(s32 alpha) {
    gDPSetCombineLERP(display_list_cabeza++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0,
                      PRIMITIVE, 0);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, alpha);
}

void funcion_8004B35C(u32 rojo, u32 verde, u32 azul, u32 alpha) {
    gDPSetCombineMode(display_list_cabeza++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, alpha);
}

void funcion_8004B3C8(s32 alpha) {
    gDPSetCombineLERP(display_list_cabeza++, 0, 0, 0, 1, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, 1, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, alpha);
}

void funcion_8004B414(s32 rojo, s32 verde, s32 azul, s32 alpha) {
    gDPSetCombineLERP(display_list_cabeza++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, alpha);
}

void funcion_8004B480(s32 rojo, s32 verde, s32 azul) {
    gDPSetCombineLERP(display_list_cabeza++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, 0xFF);
}

SIN_USO void funcion_8004B4E8(s32 rojo, s32 verde, s32 azul, s32 alpha) {
    gDPSetCombineLERP(display_list_cabeza++, 1, 0, SHADE, PRIMITIVE, 0, 0, 0, TEXEL0, 1, 0, SHADE, PRIMITIVE, 0, 0, 0,
                      TEXEL0);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, alpha);
}

SIN_USO void funcion_8004B554(s32 alpha) {
    gDPSetCombineLERP(display_list_cabeza++, 0, 0, 0, SHADE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, SHADE, TEXEL0, 0, PRIMITIVE,
                      0);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
}

SIN_USO void funcion_8004B5A8(s32 rojo, s32 verde, s32 azul, s32 alpha) {
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, alpha);
    gDPSetCombineLERP(display_list_cabeza++, 1, PRIMITIVE_ALPHA, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0, 1, PRIMITIVE_ALPHA,
                      TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0);
}

void funcion_8004B614(s32 prim_rojo, s32 verde_prim, s32 azul_prim, s32 amb_rojo, s32 verde_amb, s32 azul_amb, s32 prim_alpha) {
    gDPSetPrimColor(display_list_cabeza++, 0, 0, prim_rojo, verde_prim, azul_prim, prim_alpha);
    gDPSetEnvColor(display_list_cabeza++, amb_rojo, verde_amb, azul_amb, 0xFF);
    gDPSetCombineLERP(display_list_cabeza++, 1, ENVIRONMENT, TEXEL0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 1, ENVIRONMENT,
                      TEXEL0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0);
}

void funcion_8004B6C4(s32 rojo, s32 verde, s32 azul) {
    gDPSetCombineLERP(display_list_cabeza++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, 0xFF);
}

void funcion_8004B72C(u32 prim_rojo, u32 verde_prim, u32 azul_prim, u32 amb_rojo, u32 verde_amb, u32 azul_amb, u32 prim_alpha) {
    gDPSetPrimColor(display_list_cabeza++, 0, 0, prim_rojo, verde_prim, azul_prim, prim_alpha);
    gDPSetEnvColor(display_list_cabeza++, amb_rojo, verde_amb, azul_amb, 0xFF);
    gDPSetCombineLERP(display_list_cabeza++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                      PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
}

void renderizar_rectangulo_textura(s32 x, s32 y, s32 ancho, s32 altura, s32 s, s32 w, s32 mode) {

    s32 xh = (((x + ancho) - 1) << 2);
    s32 yh = (((y + altura) - 1) << 2);
    s32 xl = ((x * 4));
    s32 yl = y * 4;

    s32 xh2 = (((x + ancho)) << 2);
    s32 yh2 = ((y + altura) << 2);

    if (mode == 0) {
        gSPTextureRectangle(display_list_cabeza++, xl, yl, xh, yh, G_TX_RENDERTILE, s << 5, (w << 5), 4 << 10, 1 << 10);
        return;
    }
    gSPTextureRectangle(display_list_cabeza++, xl, yl, xh2, yh2, G_TX_RENDERTILE, s << 5, (w << 5), 1 << 10, 1 << 10);
}

void renderizar_envoltura_rectangulo_textura(s32 x, s32 y, s32 ancho, s32 altura, s32 mode) {
    renderizar_rectangulo_textura(x, y, ancho, altura, 0, 0, mode);
}

void funcion_8004B97C(s32 parametro0, s32 parametro1, s32 parametro2, s32 parametro3, s32 parametro4) {
    SIN_USO s32 relleno[2];
    s32 sp2_c;
    s32 variable_a1;
    s32 variable_v0;
    s32 variable_v1;

    if ((-parametro2 < parametro0) && (-parametro3 < parametro1)) {
        variable_v0 = 0;
        variable_v1 = 0;
        sp2_c = parametro0;
        variable_a1 = parametro1;
        if (parametro0 < 0) {
            variable_v1 = -parametro0;
            sp2_c = 0;
        }
        if (parametro1 < 0) {
            variable_v0 = -parametro1;
            variable_a1 = 0;
        }
        renderizar_rectangulo_textura(sp2_c, variable_a1, parametro2 - variable_v1, parametro3 - variable_v0, variable_v1, variable_v0, parametro4);
    }
}

void funcion_8004BA08(s32 parametro0, s32 parametro1, s32 parametro2, s32 parametro3, s32 parametro4) {
    SIN_USO s32 relleno[2];
    s32 sp2_c;
    s32 phi_a1;
    s32 phi_v1;
    s32 phi_v0;

    if ((-parametro2 < parametro0) && (-parametro3 < parametro1)) {
        phi_v0 = 0;
        phi_v1 = 0;
        sp2_c = parametro0;
        phi_a1 = parametro1;
        if (parametro0 < 0) {
            phi_v1 = -parametro0;
            sp2_c = 0;
        }
        if (parametro1 < 0) {
            phi_v0 = -parametro1;
            phi_a1 = 0;
        }
        renderizar_rectangulo_textura(sp2_c, phi_a1, parametro2 - phi_v1, parametro3 - phi_v0, phi_v1 + parametro2, phi_v0, parametro4);
    }
}

void funcion_8004BA98(s32 parametro0, s32 parametro1, s32 parametro2, s32 parametro3, s32 parametro4, s32 parametro5, s32 parametro6) {
    SIN_USO s32 relleno[2];
    s32 sp34;
    s32 sp30;
    s32 sp2_c;
    s32 phi_a3;
    s32 phi_v0;
    s32 phi_v1;

    if ((-parametro2 < parametro0) && (-parametro3 < parametro1)) {
        sp34 = parametro0;
        sp30 = parametro1;
        phi_v0 = parametro4;
        sp2_c = parametro2;
        phi_a3 = parametro3;
        phi_v1 = parametro5;
        if (parametro0 < 0) {
            phi_v0 = parametro4 - parametro0;
            sp34 = 0;
            sp2_c = parametro2 + parametro0;
        }
        if (parametro1 < 0) {
            phi_v1 = parametro5 - parametro1;
            sp30 = 0;
            phi_a3 = parametro3 + parametro1;
        }
        renderizar_rectangulo_textura(sp34, sp30, sp2_c, phi_a3, phi_v0, phi_v1, parametro6);
    }
}

SIN_USO void funcion_8004BB34(void) {
}

void funcion_8004BB3C(s32 parametro0, s32 parametro1, s32 parametro2, s32 parametro3, f32 parametro4) {
    s16 t;
    s16 s;
    s16 temporal_t9;
    s32 variable_t0;
    s32 variable_t1;
    s32 xl;
    s32 yl;
    SIN_USO s32 cosa0;
    SIN_USO s32 cosa1;

    variable_t0 = (parametro2 * 4 * parametro4) + 0.5;
    variable_t1 = (parametro3 * 4 * parametro4) + 0.5;
    xl = (parametro0 * 4) - (variable_t0 / 2);
    yl = (parametro1 * 4) - (variable_t1 / 2);
    if (-variable_t0 < xl) {
        t = 0;
        if (-variable_t1 < yl) {
            s = 0;
            if (xl < 0) {
                variable_t0 += xl;
                s = (-xl * 8) / parametro4;
                xl = 0;
            }
            if (yl < 0) {
                variable_t1 += yl;
                t = (-yl * 8) / parametro4;
                yl = 0;
            }
            temporal_t9 = (1024.0f / parametro4) + 0.5;
            gSPTextureRectangle(display_list_cabeza++, xl, yl, xl + variable_t0, yl + variable_t1, 0, s, t, temporal_t9, temporal_t9);
        }
    }
}

SIN_USO void funcion_8004BD14(s32 x, s32 y, u32 ancho, u32 altura, s32 alpha, u8* textura1, u8* textura2) {
    gSPDisplayList(display_list_cabeza++, dato_0D007F38);
    gSPDisplayList(display_list_cabeza++, dato_0D008138);
    gDPSetTextureLOD(display_list_cabeza++, G_TL_TILE);
    gDPSetPrimColor(display_list_cabeza++, 0, 0, 0x00, 0x00, 0x00, alpha);
    gDPSetCombineLERP(display_list_cabeza++, TEXEL1, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, TEXEL1, TEXEL0, PRIMITIVE, TEXEL0, 0,
                      0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPLoadMultiTile(display_list_cabeza++, textura1, 0, G_TX_RENDERTILE, G_IM_FMT_RGBA, G_IM_SIZ_16b, ancho, altura, 0, 0,
                     ancho - 1, altura - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                     G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadMultiTile(display_list_cabeza++, textura2, 256, G_TX_RENDERTILE + 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, ancho, altura,
                     0, 0, ancho - 1, altura - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                     G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    renderizar_envoltura_rectangulo_textura(x, y, ancho, altura, 2);
    gSPDisplayList(display_list_cabeza++, dato_0D008120);
}

void funcion_8004C024(s16 parametro0, s16 parametro1, s16 parametro2, u16 rojo, u16 verde, u16 azul, u16 alpha) {
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, alpha);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
    gDPSetTexturePersp(display_list_cabeza++, G_TP_NONE);
    gDPSetCombineMode(display_list_cabeza++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetRenderMode(display_list_cabeza++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    funcion_8004B97C(parametro0, parametro1, parametro2, 1, 1);
}

void funcion_8004C148(s16 parametro0, s16 parametro1, s16 parametro2, u16 rojo, u16 verde, u16 azul, u16 alpha) {
    gDPSetPrimColor(display_list_cabeza++, 0, 0, rojo, verde, azul, alpha);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
    gDPSetTexturePersp(display_list_cabeza++, G_TP_NONE);
    gDPSetCombineMode(display_list_cabeza++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetRenderMode(display_list_cabeza++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    funcion_8004B97C(parametro0, parametro1, 1, parametro2, 1);
}

void funcion_8004C268(u32 parametro0, u32 parametro1, u8* textura, u32 ancho, u32 parametro4, u32 altura, s32 parametro6) {
    s32 i;
    u8* img2;

    parametro0 -= (ancho / 2);
    parametro1 -= (parametro4 / 2);
    img2 = textura;

    for (i = 0; (u32) i < (parametro4 / altura); i++) {
        cargar_textura_bloque_rgba16_espejo(img2, ancho, altura);
        funcion_8004B97C(parametro0, parametro1, ancho, altura, parametro6);
#ifdef AVOID_UB
        img2 += (ancho * altura) * 2;
#else
        img2 += (ancho * altura) * 2 ^ ((parametro4 / altura) * 0);
#endif
        parametro1 += altura;
    }
}

SIN_USO void funcion_8004C354() {
}

SIN_USO void funcion_8004C35C() {
}

void dibujar_textura_hud_2d(s32 x, s32 y, u32 ancho, u32 altura, u8* textura) {
    gSPDisplayList(display_list_cabeza++, dato_0D008108);
    gSPDisplayList(display_list_cabeza++, dato_0D007EF8);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_THRESHOLD);
    cargar_textura_bloque_rgba16_espejo(textura, ancho, altura);
    funcion_8004B97C(x - (ancho >> 1), y - (altura >> 1), ancho, altura, 0);
    gSPDisplayList(display_list_cabeza++, dato_0D007EB8);
}

void funcion_8004C450(s32 x, s32 y, u32 ancho, u32 altura, u8* textura) {

    gSPDisplayList(display_list_cabeza++, dato_0D007F38);
    funcion_8004B614(dato_801656C0, dato_801656D0, dato_801656E0, 0x80, 0x80, 0x80, 0xFF);
    cargar_textura_bloque_rgba16_espejo(textura, ancho, altura);
    funcion_8004B97C(x - (ancho >> 1), y - (altura >> 1), ancho, altura, 1);
    gSPDisplayList(display_list_cabeza++, dato_0D007EB8);
}

SIN_USO void funcion_8004C53C(s32 parametro0, s32 parametro1, u32 parametro2, u32 parametro3, u8* textura) {

    gSPDisplayList(display_list_cabeza++, dato_0D008108);
    gSPDisplayList(display_list_cabeza++, dato_0D007EF8);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_THRESHOLD);
    cargar_textura_tile_rgba16_nomirror(textura, parametro2, parametro3);
    funcion_8004B97C(parametro0 - (parametro2 >> 1), parametro1 - (parametro3 >> 1), parametro2, parametro3, 0);
    gSPDisplayList(display_list_cabeza++, dato_0D007EB8);
}

void funcion_8004C628(s32 parametro0, s32 parametro1, u32 parametro2, u32 parametro3, u8* textura) {

    gSPDisplayList(display_list_cabeza++, dato_0D007EF8);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_THRESHOLD);
    cargar_textura_bloque_rgba32_nomirror(textura, parametro2, parametro3);
    funcion_8004B97C(parametro0 - (parametro2 >> 1), parametro1 - (parametro3 >> 1), parametro2, parametro3, 1);
    gSPDisplayList(display_list_cabeza++, dato_0D007EB8);
}

void renderizar_textura_tile_rgba32_bloque(s16 x, s16 y, u8* textura, u32 ancho, u32 altura) {
    s32 menos_tamanio_tex;
    s32 i;
    s32 centro_y;
    s32 centro_x;
    s32 bloques_textura_num;
    u32 tamanio_tex;
    s32 div_altura;
    s32 size;
    u8* textura_copia;

    centro_x = x - (ancho / 2);
    centro_y = y - (altura / 2);
    textura_copia = textura;
    gSPDisplayList(display_list_cabeza++, dato_0D007EF8);
    gDPSetRenderMode(display_list_cabeza++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    tamanio_tex = ancho * altura * 4;
    bloques_textura_num = tamanio_tex / 4096;
    if (tamanio_tex % 4096) {
        bloques_textura_num++;
    }
    div_altura = altura / bloques_textura_num;
    size = bloques_textura_num;
    for (i = 0; i < size; i++) {
        cargar_textura_tile_rgba32_nomirror(textura_copia, ancho, div_altura);
        renderizar_envoltura_rectangulo_textura(centro_x, centro_y, ancho, div_altura, 1);
        textura_copia += (ancho * div_altura * 4);
        menos_tamanio_tex = tamanio_tex - (ancho * div_altura * 4);
        if (menos_tamanio_tex < 0) {
            div_altura = tamanio_tex / ancho;
        } else {
            tamanio_tex -= (ancho * div_altura * 4);
        }

        centro_y += div_altura;
    }

    gSPDisplayList(display_list_cabeza++, dato_0D007EB8);
    centro_x++;
    centro_x--;
}

void renderizar_logo_juego(s16 x, s16 y) {
    renderizar_textura_tile_rgba32_bloque(x, y, direccion_logo_juego, 256, 128);
}

SIN_USO void funcion_8004C91C(s32 parametro0, s32 parametro1, u8* textura, s32 parametro3, s32 parametro4, s32 parametro5) {
    gSPDisplayList(display_list_cabeza++, dato_0D008108);
    gSPDisplayList(display_list_cabeza++, dato_0D007EF8);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_THRESHOLD);
    funcion_8004C268(parametro0, parametro1, textura, parametro3, parametro4, parametro5, 0);
    gSPDisplayList(display_list_cabeza++, dato_0D007EB8);
}

void funcion_8004C9D8(s32 parametro0, s32 parametro1, s32 parametro2, u8* textura, s32 parametro4, s32 parametro5, SIN_USO s32 parametro6, s32 parametro7) {
    gSPDisplayList(display_list_cabeza++, dato_0D007F38);
    fijar_transparencia(parametro2);
    funcion_8004C268(parametro0, parametro1, textura, parametro4, parametro5, parametro7, 1);
}

void funcion_8004CA58(s32 parametro0, s32 parametro1, f32 parametro2, u8* textura, s32 parametro4, s32 parametro5) {
    gSPDisplayList(display_list_cabeza++, dato_0D007F78);
    cargar_textura_bloque_rgba16_espejo(textura, parametro4, parametro5);
    funcion_8004BB3C(parametro0, parametro1, parametro4, parametro5, parametro2);
}

void dibujar_textura_8x_hud_2d_8(s32 x, s32 y, u8* textura) {
    dibujar_textura_hud_2d(x, y, 8, 8, textura);
}

SIN_USO void dibujar_textura_8x_hud_2d_16(s32 x, s32 y, u8* textura) {
    dibujar_textura_hud_2d(x, y, 8, 16, textura);
}

SIN_USO void dibujar_textura_16x_hud_2d_16(s32 x, s32 y, u8* textura) {
    dibujar_textura_hud_2d(x, y, 16, 16, textura);
}

void dibujar_textura_32x_hud_2d_8(s32 x, s32 y, u8* textura) {
    dibujar_textura_hud_2d(x, y, 32, 8, textura);
}

void dibujar_textura_32x_hud_2d_16(s32 x, s32 y, u8* textura) {
    dibujar_textura_hud_2d(x, y, 32, 16, textura);
}

SIN_USO void funcion_8004CBC0(s32 parametro0, s32 parametro1, f32 parametro2, u8* textura) {
    funcion_8004CA58(parametro0, parametro1, parametro2, textura, 32, 16);
}

SIN_USO void dibujar_textura_32x_hud_2d_32(s32 x, s32 y, u8* textura) {
    dibujar_textura_hud_2d(x, y, 32, 32, textura);
}
