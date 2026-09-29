// Kart bomba y depuracion

void renderizar_objeto_kart_bomba(s32 id_camara) {
    Jugador* temporal_v0;
    s32 temporal_s1;
    s32 temporal_s0;
    s32 jugador_id;
    Objeto* objeto;

    for (jugador_id = 0; jugador_id < NUM_KARTS_BOMBA_BATALLA; jugador_id++) {
        temporal_s0 = objeto_indice_kart_bomba[jugador_id];
        objeto = &lista_objeto[temporal_s0];
        if (objeto->state != 0) {
            temporal_s1 = objeto->prim_alpha;
            temporal_v0 = &jugador_uno[jugador_id];
            objeto->pos[0] = temporal_v0->pos[0];
            objeto->pos[1] = temporal_v0->pos[1] - 2.0;
            objeto->pos[2] = temporal_v0->pos[2];
            objeto->altura_superficie = temporal_v0->desconocido_074;
            funcion_800563DC(temporal_s0, id_camara, temporal_s1);
            funcion_8005669C(temporal_s0, id_camara, temporal_s1);
            funcion_800568A0(temporal_s0, id_camara);
        }
    }
}

void funcion_80056BF0(s32 indice_bomba) {
    SIN_USO s32 margen_pila;
    u8 cosa;
    s32 temporal_s0;
    s32 temporal_v0;
    u8* frame_bomba;
    KartBomba sp40 = karts_bomba[indice_bomba];

    temporal_v0 = dato_801655CC % 6U;
    cosa = dato_800E471C[temporal_v0];
    frame_bomba = bomba_textura_comun[cosa];
    dato_80183E40[0] = sp40.pos_bomba[0];
    dato_80183E40[1] = sp40.pos_bomba[1] + 1.0;
    dato_80183E40[2] = sp40.pos_bomba[2];
    dibujar_2d_textura_en(dato_80183E40, dato_80183E80, 0.25f, (u8*) bomba_tlut_comun, frame_bomba, dato_0D005AE0, 0x20, 0x20, 0x20,
                       0x20);
    temporal_s0 = dato_8018D400;
    gSPDisplayList(display_list_cabeza++, dato_0D007B00);
    funcion_8004B414(0, 0, 0, 0xFF);
    dato_80183E40[1] = sp40.pos_bomba[1] + 5.0;
    dato_80183E80[2] = 0;
    funcion_800562E4((s32) temporal_s0 % 3, temporal_s0 % 4, 0xFFU);
    temporal_v0 = temporal_s0 + 1;
    dato_80183E80[2] = 0x6000;
    funcion_800562E4(temporal_v0 % 3, temporal_v0 % 4, 0xFFU);
    temporal_v0 = temporal_s0 + 2;
    dato_80183E80[2] = 0xA000;
    funcion_800562E4(temporal_v0 % 3, temporal_v0 % 4, 0xFFU);
}

void funcion_80056E24(s32 indice_bomba, Vec3f parametro1) {
    SIN_USO s32 margen_pila[2];
    KartBomba sp2_c = karts_bomba[indice_bomba];

    dato_80183E80[0] = 0;
    dato_80183E80[2] = 0x8000;
    gSPDisplayList(display_list_cabeza++, dato_0D0079C8);
    cargar_textura_bloque_rgba16_espejo((u8*) dato_0D02AA58, 0x00000010, 0x00000010);
    dato_80183E80[1] = funcion_800418AC(sp2_c.pos_rueda_1[0], sp2_c.pos_rueda_1[2], parametro1);
    funcion_800431B0(sp2_c.pos_rueda_1, dato_80183E80, 0.15f, rectangulo_vtx_comun);
    dato_80183E80[1] = funcion_800418AC(sp2_c.pos_rueda_2[0], sp2_c.pos_rueda_2[2], parametro1);
    funcion_800431B0(sp2_c.pos_rueda_2, dato_80183E80, 0.15f, rectangulo_vtx_comun);
    dato_80183E80[1] = funcion_800418AC(sp2_c.pos_rueda_3[0], sp2_c.pos_rueda_3[2], parametro1);
    funcion_800431B0(sp2_c.pos_rueda_3, dato_80183E80, 0.15f, rectangulo_vtx_comun);
    dato_80183E80[1] = funcion_800418AC(sp2_c.pos_rueda_4[0], sp2_c.pos_rueda_4[2], parametro1);
    funcion_800431B0(sp2_c.pos_rueda_4, dato_80183E80, 0.15f, rectangulo_vtx_comun);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

void funcion_80056FCC(s32 indice_bomba) {
    Mat4 mat;
    KartBomba* temporal_v0;

    temporal_v0 = &karts_bomba[indice_bomba];
    dato_80183E50[0] = temporal_v0->pos_bomba[0];
    dato_80183E50[1] = temporal_v0->y_pos + 1.0;
    dato_80183E50[2] = temporal_v0->pos_bomba[2];
    transformar_matriz_conjunto(mat, dato_80164038[indice_bomba].vector_orientacion, dato_80183E50, 0U, 0.5f);
    convertir_a_matriz_punto_fijo(&gfx_pool->mtx_hud[cantidad_hud_matriz], mat);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_hud[cantidad_hud_matriz++]),
              G_MTX_LOAD | G_MTX_NOPUSH | G_MTX_MODELVIEW);
    gSPDisplayList(display_list_cabeza++, dato_0D007B98);
}

void funcion_80057114(s32 id_camara) {
    Camara* camara;
    s32 indice_objeto;
    s32 temporal_s4;
    s32 i;
    s32 estado;
    KartBomba* variable_s1_2;

    if (estado_juego == 5) {
        id_camara = 0;
    }
    camara = &camara1[id_camara];
    if (id_camara == JUGADOR_UNO) {
        for (i = 0; i < NUM_KARTS_BOMBA_VERSUS; i++) {
            indice_objeto = objeto_indice_kart_bomba[i];
            if (es_obj_bandera_situacion_activo(indice_objeto, 0x00200000) != 0) {
                karts_bomba[i].desconocido_4A = 0;
            } else if (estado_juego != 5) {
                karts_bomba[i].desconocido_4A = 1;
            }
            fijar_objeto_bandera_situacion_false(indice_objeto, 0x00200000);
        }
    }

    for (i = 0; i < NUM_KARTS_BOMBA_VERSUS; i++) {
        variable_s1_2 = &karts_bomba[i];
        estado = variable_s1_2->state;
        if (variable_s1_2->state != INACTIVO_ESTADO_BOMBA) {
            indice_objeto = objeto_indice_kart_bomba[i];
            lista_objeto[indice_objeto].pos[0] = variable_s1_2->pos_bomba[0];
            lista_objeto[indice_objeto].pos[1] = variable_s1_2->pos_bomba[1];
            lista_objeto[indice_objeto].pos[2] = variable_s1_2->pos_bomba[2];
            temporal_s4 = funcion_8008A364(indice_objeto, id_camara, 0x31C4U, 0x000001F4);
            if (es_obj_bandera_situacion_activo(indice_objeto, VISIBLE) != 0) {
                fijar_objeto_bandera_situacion_true(indice_objeto, 0x00200000);
                dato_80183E80[0] = 0;
                dato_80183E80[1] = funcion_800418AC(variable_s1_2->pos_bomba[0], variable_s1_2->pos_bomba[2], camara->pos);
                dato_80183E80[2] = 0x8000;
                funcion_800563DC(indice_objeto, id_camara, 0x000000FF);
                funcion_80056E24(i, camara->pos);
                if (((u32) temporal_s4 < 0x4E21U) && (estado != BOMBA_ESTADO_EXPLOTADO)) {
                    funcion_80056FCC(i);
                }
            }
        }
    }
}

SIN_USO void funcion_80057330(void) {
}

SIN_USO void funcion_80057338(void) {

    gSPDisplayList(display_list_cabeza++, dato_0D0079C8);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BOTH);
    gSPDisplayList(display_list_cabeza++, dato_0D007AE0);
    gSPTexture(display_list_cabeza++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
}

SIN_USO void funcion_800573BC(void) {
}

SIN_USO void funcion_800573C4(void) {
}

SIN_USO void funcion_800573CC(void) {
}
SIN_USO void funcion_800573D4(void) {
}

SIN_USO void funcion_800573DC(void) {
}

void funcion_800573E4(s32 x, s32 y, s8 cad) {
    renderizar_rectangulo_textura(x, y, 8, 8, (((cad % 16) * 8) << 16) >> 16, (((unsigned short) (cad / 16)) << 19) >> 16,
                             0);
}

#include "cadena_depuracion.inc.c"

void imprimir_numero_depuracion(s32* x, s32* y, s32 numero, u32 digitos_num) {
    s32 n;
    s8* ptr;
    s8 remainder;

    texto_envoltura_depuracion(x, y);
    n = numero;
    if (n < 0) {
        funcion_800573E4(*x, *y, dato_800E5628[0x2D]);
        texto_envoltura_depuracion(x, y);
        n = -numero;
    }

    *dato_801657B8 = -1;
    ptr = dato_801657B8;
    if (n != 0) {
        while (n != 0) {
            remainder = n % digitos_num;
            *++ptr = remainder;
            n = n / digitos_num;
        }
    } else {
        *++ptr = 0;
    }

    do {
        funcion_800573E4(*x, *y, *ptr--);
        texto_envoltura_depuracion(x, y);
    } while (*ptr != -1);
}

void funcion_8005762C(s32* x, s32* y, s32 cantidad_camino, u32 digitos_num) {
    s8* ptr;
    s32 cantidad;
    s8 remainder;

    texto_envoltura_depuracion(x, y);
    *dato_801657B8 = -1;
    ptr = dato_801657B8;
    cantidad = cantidad_camino;
    if (cantidad != 0) {
        while (cantidad != 0) {
            remainder = cantidad % digitos_num;
            *++ptr = remainder;
            cantidad = cantidad / digitos_num;
        }
    } else {
        *++ptr = 0;
    }

    do {
        funcion_800573E4(*x, *y, *ptr--);
        texto_envoltura_depuracion(x, y);
    } while (*ptr != -1);
}

SIN_USO void funcion_80057708() {
}

void cargar_fuente_depuracion(void) {
    gSPDisplayList(display_list_cabeza++, dato_0D008108);
    gSPDisplayList(display_list_cabeza++, dato_0D008080);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_THRESHOLD);
}

void funcion_80057778(void) {
    gSPDisplayList(display_list_cabeza++, dato_0D007EB8);
}

void imprimir_cad2_depuracion(s32 x_pos, s32 y_pos, char* cad) {
    imprimir_cadena_depuracion(&x_pos, &y_pos, cad);
}

void imprimir_num_cad(s32 parametro0, s32 parametro1, char* parametro2, s32 parametro3) {
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    imprimir_numero_depuracion(&parametro0, &parametro1, parametro3, 10);
}

SIN_USO void funcion_80057814(s32 parametro0, s32 parametro1, char* parametro2, u32 parametro3) {
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    funcion_8005762C(&parametro0, &parametro1, parametro3, 10);
}

SIN_USO void funcion_80057858(s32 parametro0, s32 parametro1, char* parametro2, u32 parametro3) {
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    imprimir_numero_depuracion(&parametro0, &parametro1, parametro3, 16);
    funcion_800573E4(parametro0, parametro1, dato_800E5628[0x48]);
}

SIN_USO void funcion_800578B0(s32 parametro0, s32 parametro1, char* parametro2, u32 parametro3) {
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    funcion_8005762C(&parametro0, &parametro1, parametro3, 16);
    funcion_800573E4(parametro0, parametro1, dato_800E5628[0x48]);
}

SIN_USO void funcion_80057908(s32 parametro0, s32 parametro1, char* parametro2, u32 parametro3) {
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    imprimir_numero_depuracion(&parametro0, &parametro1, parametro3, 2);
    funcion_800573E4(parametro0, parametro1, dato_800E5628[0x42]);
}

SIN_USO void funcion_80057960(s32 parametro0, s32 parametro1, char* parametro2, u32 parametro3) {
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    funcion_8005762C(&parametro0, &parametro1, parametro3, 2);
    funcion_800573E4(parametro0, parametro1, dato_800E5628[0x42]);
}

SIN_USO void funcion_800579B8(s32 parametro0, s32 parametro1, char* parametro2) {
    cargar_fuente_depuracion();
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    funcion_80057778();
}

void funcion_800579F8(s32 parametro0, s32 parametro1, char* parametro2, u32 parametro3) {
    cargar_fuente_depuracion();
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    imprimir_numero_depuracion(&parametro0, &parametro1, parametro3, 10);
    funcion_80057778();
}

void funcion_80057A50(s32 x, s32 y, char* cad, u32 parametro3) {
    cargar_fuente_depuracion();
    imprimir_cadena_depuracion(&x, &y, cad);
    funcion_8005762C(&x, &y, parametro3, 10);
    funcion_80057778();
}

SIN_USO void funcion_80057AA8(s32 parametro0, s32 parametro1, char* parametro2, u32 parametro3) {
    cargar_fuente_depuracion();
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    imprimir_numero_depuracion(&parametro0, &parametro1, parametro3, 16);
    funcion_800573E4(parametro0, parametro1, dato_800E5628[0x48]);
    funcion_80057778();
}

SIN_USO void funcion_80057B14(s32 parametro0, s32 parametro1, char* parametro2, u32 parametro3) {
    cargar_fuente_depuracion();
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    funcion_8005762C(&parametro0, &parametro1, parametro3, 16);
    funcion_800573E4(parametro0, parametro1, dato_800E5628[0x48]);
    funcion_80057778();
}

SIN_USO void funcion_80057B80(s32 parametro0, s32 parametro1, char* parametro2, u32 parametro3) {
    cargar_fuente_depuracion();
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    imprimir_numero_depuracion(&parametro0, &parametro1, parametro3, 2);
    funcion_800573E4(parametro0, parametro1, dato_800E5628[0x42]);
    funcion_80057778();
}

SIN_USO void funcion_80057BEC(s32 parametro0, s32 parametro1, char* parametro2, u32 parametro3) {
    cargar_fuente_depuracion();
    imprimir_cadena_depuracion(&parametro0, &parametro1, parametro2);
    funcion_8005762C(&parametro0, &parametro1, parametro3, 2);
    funcion_800573E4(parametro0, parametro1, dato_800E5628[0x42]);
    funcion_80057778();
}
