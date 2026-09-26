// Cielo y viewport

Vp dato_802B8880[] = {
    { { { 640, 480, 511, 0 }, { 640, 480, 511, 0 } } },
};

static Vtx cielo_p1[] = {
    { { { ANCHO_PANTALLA, ALTURA_PANTALLA, -1 }, 0, { 0, 0 }, { 0xC8, 0xC8, 0xFF, 0xFF } } },
    { { { ANCHO_PANTALLA, 120, -1 }, 0, { 0, 0 }, { 0x1E, 0x1E, 0xFF, 0xFF } } },
    { { { 0, 120, -1 }, 0, { 0, 0 }, { 0x1E, 0x1E, 0xFF, 0xFF } } },
    { { { 0, ALTURA_PANTALLA, -1 }, 0, { 0, 0 }, { 0xC8, 0xC8, 0xFF, 0xFF } } },
    { { { ANCHO_PANTALLA, 120, -1 }, 0, { 0, 0 }, { 0x00, 0xDC, 0x00, 0xFF } } },
    { { { ANCHO_PANTALLA, 0, -1 }, 0, { 0, 0 }, { 0x78, 0xFF, 0x78, 0xFF } } },
    { { { 0, 0, -1 }, 0, { 0, 0 }, { 0x78, 0xFF, 0x78, 0xFF } } },
    { { { 0, 120, -1 }, 0, { 0, 0 }, { 0x00, 0xDC, 0x00, 0xFF } } },
};

static Vtx cielo_p2[] = {
    { { { ANCHO_PANTALLA, ALTURA_PANTALLA, -1 }, 0, { 0, 0 }, { 0xC8, 0xC8, 0xFF, 0xFF } } },
    { { { ANCHO_PANTALLA, 120, -1 }, 0, { 0, 0 }, { 0x1E, 0x1E, 0xFF, 0xFF } } },
    { { { 0, 120, -1 }, 0, { 0, 0 }, { 0x1E, 0x1E, 0xFF, 0xFF } } },
    { { { 0, ALTURA_PANTALLA, -1 }, 0, { 0, 0 }, { 0xC8, 0xC8, 0xFF, 0xFF } } },
    { { { ANCHO_PANTALLA, 120, -1 }, 0, { 0, 0 }, { 0x00, 0xDC, 0x00, 0xFF } } },
    { { { ANCHO_PANTALLA, 0, -1 }, 0, { 0, 0 }, { 0x78, 0xFF, 0x78, 0xFF } } },
    { { { 0, 0, -1 }, 0, { 0, 0 }, { 0x78, 0xFF, 0x78, 0xFF } } },
    { { { 0, 120, -1 }, 0, { 0, 0 }, { 0x00, 0xDC, 0x00, 0xFF } } },
};

static Vtx cielo_p3[] = {
    { { { ANCHO_PANTALLA, ALTURA_PANTALLA, -1 }, 0, { 0, 0 }, { 0xC8, 0xC8, 0xFF, 0xFF } } },
    { { { ANCHO_PANTALLA, 120, -1 }, 0, { 0, 0 }, { 0x1E, 0x1E, 0xFF, 0xFF } } },
    { { { 0, 120, -1 }, 0, { 0, 0 }, { 0x1E, 0x1E, 0xFF, 0xFF } } },
    { { { 0, ALTURA_PANTALLA, -1 }, 0, { 0, 0 }, { 0xC8, 0xC8, 0xFF, 0xFF } } },
    { { { ANCHO_PANTALLA, 120, -1 }, 0, { 0, 0 }, { 0x00, 0xDC, 0x00, 0xFF } } },
    { { { ANCHO_PANTALLA, 0, -1 }, 0, { 0, 0 }, { 0x78, 0xFF, 0x78, 0xFF } } },
    { { { 0, 0, -1 }, 0, { 0, 0 }, { 0x78, 0xFF, 0x78, 0xFF } } },
    { { { 0, 120, -1 }, 0, { 0, 0 }, { 0x00, 0xDC, 0x00, 0xFF } } },
};

static Vtx cielo_p4[] = {
    { { { ANCHO_PANTALLA, ALTURA_PANTALLA, -1 }, 0, { 0, 0 }, { 0xC8, 0xC8, 0xFF, 0xFF } } },
    { { { ANCHO_PANTALLA, 120, -1 }, 0, { 0, 0 }, { 0x1E, 0x1E, 0xFF, 0xFF } } },
    { { { 0, 120, -1 }, 0, { 0, 0 }, { 0x1E, 0x1E, 0xFF, 0xFF } } },
    { { { 0, ALTURA_PANTALLA, -1 }, 0, { 0, 0 }, { 0xC8, 0xC8, 0xFF, 0xFF } } },
    { { { ANCHO_PANTALLA, 120, -1 }, 0, { 0, 0 }, { 0x00, 0xDC, 0x00, 0xFF } } },
    { { { ANCHO_PANTALLA, 0, -1 }, 0, { 0, 0 }, { 0x78, 0xFF, 0x78, 0xFF } } },
    { { { 0, 0, -1 }, 0, { 0, 0 }, { 0x78, 0xFF, 0x78, 0xFF } } },
    { { { 0, 120, -1 }, 0, { 0, 0 }, { 0x00, 0xDC, 0x00, 0xFF } } },
};

void funcion_802A3730(struct desconocido_struct_800DC5EC* parametro0) {
    s32 ulx;
    s32 uly;
    s32 lrx;
    s32 lry;
    s32 ancho_pantalla = parametro0->ancho_pantalla * 2;
    s32 altura_pantalla = parametro0->altura_pantalla * 2;
    s32 inicio_x_pantalla = parametro0->inicio_x_pantalla * 4;
    s32 inicio_y_pantalla = parametro0->inicio_y_pantalla * 4;

    parametro0->viewport.vp.vscale[0] = ancho_pantalla;
    parametro0->viewport.vp.vscale[1] = altura_pantalla;
    parametro0->viewport.vp.vscale[2] = 511;
    parametro0->viewport.vp.vscale[3] = 0;

    parametro0->viewport.vp.vtrans[0] = inicio_x_pantalla;
    parametro0->viewport.vp.vtrans[1] = inicio_y_pantalla;
    parametro0->viewport.vp.vtrans[2] = 511;
    parametro0->viewport.vp.vtrans[3] = 0;

    gSPViewport(display_list_cabeza++, VIRTUAL_A_FISICO(&parametro0->viewport));

    ancho_pantalla /= 4;
    altura_pantalla /= 4;

    inicio_x_pantalla /= 4;
    inicio_y_pantalla /= 4;

    lrx = inicio_x_pantalla + ancho_pantalla;
    if (lrx > ANCHO_PANTALLA) {
        lrx = ANCHO_PANTALLA;
    }

    lry = inicio_y_pantalla + altura_pantalla;
    if (lry > ALTURA_PANTALLA) {
        lry = ALTURA_PANTALLA;
    }
    ulx = 0;
    uly = 0;

    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, ulx, uly, lrx, lry);
}

SIN_USO void funcion_802A38AC(void) {
}

void funcion_802A38B4(void) {
    inicializar_rdp();
    seleccionar_framebuffer();

    gDPFullSync(display_list_cabeza++);
    gSPEndDisplayList(display_list_cabeza++);

    if (abandonar_a_contador_transicion_menu != 0) {
        abandonar_a_contador_transicion_menu--;
        return;
    }
    siguiente_estado_juego = modo_goto;
    estado_juego = 255;
    es_en_abandonar_a_transicion_menu = 0;
    abandonar_a_contador_transicion_menu = 0;
    seleccion_modo_fundido = PRINCIPAL_MODO_FUNDIDO;

    switch (modo_goto) {
        case MENU_INICIO_DESDE_ABANDONAR:
            if (seleccion_menu != LOGO_INTRO_MENU) {
                seleccion_menu = MENU_INICIO;
            }
            break;
        case MENU_PRINCIPAL_DESDE_ABANDONAR:
            seleccion_menu = MENU_PRINCIPAL;
            break;
        case MENU_SELECCION_JUGADOR_DESDE_ABANDONAR:
            seleccion_menu = MENU_SELECCION_PERSONAJE;
            break;
        case MENU_SELECCION_CIRCUITO_DESDE_ABANDONAR:
            seleccion_menu = MENU_SELECCION_CIRCUITO;
            break;
    }
}

void funcion_802A39E0(struct desconocido_struct_800DC5EC* parametro0) {
    s32 ulx = parametro0->inicio_x_pantalla - (parametro0->ancho_pantalla / 2);
    s32 uly = parametro0->inicio_y_pantalla - (parametro0->altura_pantalla / 2);
    s32 lrx = parametro0->inicio_x_pantalla + (parametro0->ancho_pantalla / 2);
    s32 lry = parametro0->inicio_y_pantalla + (parametro0->altura_pantalla / 2);

    if (ulx < 0) {
        ulx = 0;
    }
    if (uly < 0) {
        uly = 0;
    }
    if (lrx > ANCHO_PANTALLA) {
        lrx = ANCHO_PANTALLA;
    }
    if (lry > ALTURA_PANTALLA) {
        lry = ALTURA_PANTALLA;
    }
    if (ulx >= lrx) {
        lrx = ulx + 2;
    }
    if (uly >= lry) {
        lry = uly + 2;
    }

    gDPPipeSync(display_list_cabeza++);
    gDPSetCycleType(display_list_cabeza++, G_CYC_FILL);
    gDPSetDepthImage(display_list_cabeza++, fisico_zbuffer);
    gDPSetColorImage(display_list_cabeza++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ANCHO_PANTALLA, fisico_zbuffer);
    gDPSetFillColor(display_list_cabeza++, 0xFFFCFFFC);
    gDPPipeSync(display_list_cabeza++);
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, ulx, uly, lrx, lry);

    gDPFillRectangle(display_list_cabeza++, ulx, uly, lrx - 1, lry - 1);

    gDPPipeSync(display_list_cabeza++);
    gDPSetColorImage(display_list_cabeza++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ANCHO_PANTALLA,
                     VIRTUAL_A_FISICO(framebuffers_fisico[framebuffer_renderizado]));
    gDPSetCycleType(display_list_cabeza++, G_CYC_1CYCLE);
    gDPSetDepthSource(display_list_cabeza++, G_ZS_PIXEL);
}

void inicializar_zbuffer(void) {
    gDPPipeSync(display_list_cabeza++);
    gDPSetCycleType(display_list_cabeza++, G_CYC_FILL);
    gDPSetDepthImage(display_list_cabeza++, fisico_zbuffer);
    gDPSetColorImage(display_list_cabeza++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ANCHO_PANTALLA, fisico_zbuffer);
    gDPSetFillColor(display_list_cabeza++, 0xFFFCFFFC);
    gDPPipeSync(display_list_cabeza++);
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA, ALTURA_PANTALLA);
    gDPFillRectangle(display_list_cabeza++, 0, 0, 319, 239);
    gDPPipeSync(display_list_cabeza++);
    gDPSetColorImage(display_list_cabeza++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ANCHO_PANTALLA,
                     VIRTUAL_A_FISICO(framebuffers_fisico[framebuffer_renderizado]));
    gDPSetCycleType(display_list_cabeza++, G_CYC_1CYCLE);
    gDPSetDepthSource(display_list_cabeza++, G_ZS_PIXEL);
}

void inicializar_rdp(void) {
    gDPPipeSync(display_list_cabeza++);
    gDPPipelineMode(display_list_cabeza++, G_PM_1PRIMITIVE);
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA, ALTURA_PANTALLA);
    gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
    gDPSetTextureLOD(display_list_cabeza++, G_TL_TILE);
    gDPSetTextureLUT(display_list_cabeza++, G_TT_NONE);
    gDPSetTextureDetail(display_list_cabeza++, G_TD_CLAMP);
    gDPSetTexturePersp(display_list_cabeza++, G_TP_PERSP);
    gDPSetTextureFilter(display_list_cabeza++, G_TF_BILERP);
    gDPSetTextureConvert(display_list_cabeza++, G_TC_FILT);
    gDPSetCombineKey(display_list_cabeza++, G_CK_NONE);
    gDPSetAlphaCompare(display_list_cabeza++, G_AC_NONE);
    gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetBlendMask(display_list_cabeza++, 0xFF);
    gDPSetColorDither(display_list_cabeza++, G_CD_DISABLE);
    gDPPipeSync(display_list_cabeza++);
    gSPClipRatio(display_list_cabeza++, FRUSTRATIO_1);
}

SIN_USO void funcion_802A40A4(void) {
}
SIN_USO void funcion_802A40AC(void) {
}
SIN_USO void funcion_802A40B4(void) {
}
SIN_USO void funcion_802A40BC(void) {
}
SIN_USO void funcion_802A40C4(void) {
}
SIN_USO void funcion_802A40CC(void) {
}
SIN_USO void funcion_802A40D4(void) {
}
SIN_USO void funcion_802A40DC(void) {
}

SIN_USO s32 fijar_viewport2(void) {
    gSPViewport(display_list_cabeza++, VIRTUAL_A_FISICO(&dato_800DC5EC->viewport));
    gSPClearGeometryMode(display_list_cabeza++, G_LIMPIEZA_TODOS_MODOS);
    gSPSetGeometryMode(display_list_cabeza++,
                       G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH | G_CLIPPING);
}

void fijar_viewport(void) {
    gSPViewport(display_list_cabeza++, VIRTUAL_A_FISICO(&dato_802B8880));
    gSPClearGeometryMode(display_list_cabeza++, G_LIMPIEZA_TODOS_MODOS);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
}

void seleccionar_framebuffer(void) {
    gDPSetColorImage(display_list_cabeza++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ANCHO_PANTALLA,
                     VIRTUAL_A_FISICO(framebuffers_fisico[framebuffer_renderizado]));
    gDPSetFillColor(display_list_cabeza++, GPACK_RGBA5551(dato_800DC5D0, dato_800DC5D4, dato_800DC5D8, 1) << 0x10 |
                                            GPACK_RGBA5551(dato_800DC5D0, dato_800DC5D4, dato_800DC5D8, 1));
    gDPPipeSync(display_list_cabeza++);
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA, ALTURA_PANTALLA);
    gDPFillRectangle(display_list_cabeza++, 0, 0, ANCHO_PANTALLA - 1, ALTURA_PANTALLA - 1);
    gDPPipeSync(display_list_cabeza++);
    gDPSetCycleType(display_list_cabeza++, G_CYC_1CYCLE);
}

void funcion_802A4300(void) {

    if (modo_pantalla_activo == MODO_PANTALLA_1P) {
        return;
    }
    if (dato_800DC5B0 != 0) {
        return;
    }

    gDPPipeSync(display_list_cabeza++);
    gDPSetCycleType(display_list_cabeza++, G_CYC_FILL);
    gDPSetColorImage(display_list_cabeza++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ANCHO_PANTALLA,
                     VIRTUAL_A_FISICO(framebuffers_fisico[framebuffer_renderizado]));
    gDPSetFillColor(display_list_cabeza++, 0x00010001);
    gSPViewport(display_list_cabeza++, VIRTUAL_A_FISICO(&dato_802B8880));
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA, ALTURA_PANTALLA);
    gDPPipeSync(display_list_cabeza++);

    switch (modo_pantalla_activo) {
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            gDPFillRectangle(display_list_cabeza++, 157, 0, 159, 239);
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            gDPFillRectangle(display_list_cabeza++, 0, 119, 319, 121);
            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            gDPFillRectangle(display_list_cabeza++, 157, 0, 159, 239);
            gDPFillRectangle(display_list_cabeza++, 0, 119, 319, 121);
            break;
    }
    gDPPipeSync(display_list_cabeza++);
    gDPSetCycleType(display_list_cabeza++, G_CYC_1CYCLE);
}
struct Cielo {
    s16 arriba_rojo;
    s16 verde_arriba;
    s16 azul_arriba;
    s16 abajo_rojo;
    s16 verde_abajo;
    s16 azul_abajo;
};

SIN_USO Gfx dato_802B8A90[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(0x00000000),
    gsDPFillRectangle(0, 0, 319, 239),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

struct Cielo arriba_cielo_caja_colores[] = {
#include "recursos/pistas/metadatos/colores_cielo.inc.c"

};

struct Cielo abajo_cielo_caja_colores[] = {
#include "recursos/pistas/metadatos/colores_cielo_2.inc.c"
};

void fijar_colores_cielo_circuito(Vtx* cielo) {
    s32 i;

    if (dato_800DC5BC != 0) {

        if (dato_801625EC < 0) {
            dato_801625EC = 0;
        }

        if (dato_801625F4 < 0) {
            dato_801625F4 = 0;
        }

        if (dato_801625F0 < 0) {
            dato_801625F0 = 0;
        }

        if (dato_801625EC > 255) {
            dato_801625EC = 255;
        }

        if (dato_801625F4 > 255) {
            dato_801625F4 = 255;
        }

        if (dato_801625F0 > 255) {
            dato_801625F0 = 255;
        }

        for (i = 0; i < 8; i++) {

            cielo[i].v.cn[0] = (s16) dato_801625EC;
            cielo[i].v.cn[1] = (s16) dato_801625F4;
            cielo[i].v.cn[2] = (s16) dato_801625F0;
        }
        return;
    }

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    cielo[0].v.cn[0] = arriba_cielo_caja_colores[id_circuito_actual].arriba_rojo;
    cielo[0].v.cn[1] = arriba_cielo_caja_colores[id_circuito_actual].verde_arriba;
    cielo[0].v.cn[2] = arriba_cielo_caja_colores[id_circuito_actual].azul_arriba;

    cielo[1].v.cn[0] = arriba_cielo_caja_colores[id_circuito_actual].abajo_rojo;
    cielo[1].v.cn[1] = arriba_cielo_caja_colores[id_circuito_actual].verde_abajo;
    cielo[1].v.cn[2] = arriba_cielo_caja_colores[id_circuito_actual].azul_abajo;

    cielo[2].v.cn[0] = arriba_cielo_caja_colores[id_circuito_actual].abajo_rojo;
    cielo[2].v.cn[1] = arriba_cielo_caja_colores[id_circuito_actual].verde_abajo;
    cielo[2].v.cn[2] = arriba_cielo_caja_colores[id_circuito_actual].azul_abajo;

    cielo[3].v.cn[0] = arriba_cielo_caja_colores[id_circuito_actual].arriba_rojo;
    cielo[3].v.cn[1] = arriba_cielo_caja_colores[id_circuito_actual].verde_arriba;
    cielo[3].v.cn[2] = arriba_cielo_caja_colores[id_circuito_actual].azul_arriba;

    cielo[4].v.cn[0] = abajo_cielo_caja_colores[id_circuito_actual].arriba_rojo;
    cielo[4].v.cn[1] = abajo_cielo_caja_colores[id_circuito_actual].verde_arriba;
    cielo[4].v.cn[2] = abajo_cielo_caja_colores[id_circuito_actual].azul_arriba;

    cielo[5].v.cn[0] = abajo_cielo_caja_colores[id_circuito_actual].abajo_rojo;
    cielo[5].v.cn[1] = abajo_cielo_caja_colores[id_circuito_actual].verde_abajo;
    cielo[5].v.cn[2] = abajo_cielo_caja_colores[id_circuito_actual].azul_abajo;

    cielo[6].v.cn[0] = abajo_cielo_caja_colores[id_circuito_actual].abajo_rojo;
    cielo[6].v.cn[1] = abajo_cielo_caja_colores[id_circuito_actual].verde_abajo;
    cielo[6].v.cn[2] = abajo_cielo_caja_colores[id_circuito_actual].azul_abajo;

    cielo[7].v.cn[0] = abajo_cielo_caja_colores[id_circuito_actual].arriba_rojo;
    cielo[7].v.cn[1] = abajo_cielo_caja_colores[id_circuito_actual].verde_arriba;
    cielo[7].v.cn[2] = abajo_cielo_caja_colores[id_circuito_actual].azul_arriba;
#else

#endif
}

void funcion_802A487C(Vtx* parametro0, SIN_USO struct desconocido_struct_800DC5EC* parametro1, SIN_USO s32 parametro2, SIN_USO s32 parametro3,
                   SIN_USO f32* parametro4) {

    inicializar_rdp();
    if (id_circuito_actual != CIRCUITO_RAINBOW_ROAD) {

        gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gSPClearGeometryMode(display_list_cabeza++, G_ZBUFFER | G_LIGHTING);
        guOrtho(&gfx_pool->pantalla_mtx, 0.0f, ANCHO_PANTALLA, 0.0f, ALTURA_PANTALLA, 0.0f, 5.0f, 1.0f);
        gSPPerspNormalize(display_list_cabeza++, 0xFFFF);
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->pantalla_mtx),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&dato_0D008E98), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPVertex(display_list_cabeza++, &parametro0[4], 4, 0);
        gSP2Triangles(display_list_cabeza++, 0, 3, 1, 0, 1, 3, 2, 0);
    }
}

void renderizar_cielo(Vtx* cielo, struct desconocido_struct_800DC5EC* parametro1, SIN_USO s32 parametro2, SIN_USO s32 parametro3, SIN_USO f32* parametro4) {
    Camara* camara = parametro1->camara;
    s16 renglon_horizonte;
    f32 homog_factor;
    SIN_USO s32 relleno[2];
    SIN_USO u16 relleno2;
    u16 sp128;
    Mat4 mtx_proy;
    Mat4 mirar_a_mtx;
    Mat4 mirar_y_mtx_proy;
    Vec3f punto_horizonte;
    f32 escala_homog;

    fijar_colores_cielo_circuito(cielo);

    punto_horizonte[0] = 0.0f;
    punto_horizonte[1] = 0.0f;
    punto_horizonte[2] = 30000.0f;
    proyeccion_mtxf(mtx_proy, &sp128, camara->desconocido_B4, aspecto_pantalla, circuito_cerca_persp, persp_lejos_circuito, 1.0f);
    mirada_mtxf(mirar_a_mtx, camara->pos, camara->mirar_a);
    multiplicacion_mtxf(mirar_y_mtx_proy, mtx_proy, mirar_a_mtx);

    escala_homog = ((mirar_y_mtx_proy[0][3] * punto_horizonte[0]) + (mirar_y_mtx_proy[1][3] * punto_horizonte[1]) +
                  (mirar_y_mtx_proy[2][3] * punto_horizonte[2])) +
                 mirar_y_mtx_proy[3][3];
    transformar_mat4_vec3f_mtxf(punto_horizonte, mirar_y_mtx_proy);

    homog_factor = (1.0 / escala_homog);

    punto_horizonte[0] *= homog_factor;
    punto_horizonte[1] *= homog_factor;

    punto_horizonte[0] *= 160.0f;
    punto_horizonte[1] *= 120.0f;

    renglon_horizonte = 120 - (s16) punto_horizonte[1];
    parametro1->altura_camara = renglon_horizonte;

    cielo[1].v.ob[1] = renglon_horizonte;
    cielo[2].v.ob[1] = renglon_horizonte;
    cielo[4].v.ob[1] = renglon_horizonte;
    cielo[7].v.ob[1] = renglon_horizonte;

    inicializar_rdp();
    gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gSPClearGeometryMode(display_list_cabeza++, G_ZBUFFER | G_LIGHTING);
    guOrtho(&gfx_pool->pantalla_mtx, 0.0f, ANCHO_PANTALLA, 0.0f, ALTURA_PANTALLA, 0.0f, 5.0f, 1.0f);
    gSPPerspNormalize(display_list_cabeza++, 0xFFFF);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->pantalla_mtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&dato_0D008E98), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(display_list_cabeza++, &cielo[0], 4, 0);
    gSP2Triangles(display_list_cabeza++, 0, 3, 1, 0, 1, 3, 2, 0);
    if (id_circuito_actual == CIRCUITO_RAINBOW_ROAD) {
        gSPVertex(display_list_cabeza++, &cielo[4], 4, 0);
        gSP2Triangles(display_list_cabeza++, 0, 3, 1, 0, 1, 3, 2, 0);
    }
}

void fijar_perspectiva_y_proporcion_aspecto(void) {
    if (estado_juego != 4) {
        persp_lejos_circuito = 6800.0f;
        circuito_cerca_persp = 3.0f;
    } else {
        switch (id_circuito_actual) {
            case CIRCUITO_BOWSER_CASTLE:
            case CIRCUITO_BANSHEE_BOARDWALK:
            case CIRCUITO_RAINBOW_ROAD:
            case CIRCUITO_BLOCK_FORT:
            case CIRCUITO_SKYSCRAPER:
                persp_lejos_circuito = 2700.0f;
                circuito_cerca_persp = 2.0f;
                break;
            case CIRCUITO_CHOCO_MOUNTAIN:
            case CIRCUITO_DOUBLE_DECK:
                persp_lejos_circuito = 1500.0f;
                circuito_cerca_persp = 2.0f;
                break;
            case CIRCUITO_KOOPA_BEACH:
                persp_lejos_circuito = 5000.0f;
                circuito_cerca_persp = 1.0f;
                break;
            case CIRCUITO_WARIO_STADIUM:
                persp_lejos_circuito = 4800.0f;
                circuito_cerca_persp = 10.0f;
                break;
            case CIRCUITO_MARIO_RACEWAY:
            case CIRCUITO_YOSHI_VALLEY:
            case CIRCUITO_FRAPPE_SNOWLAND:
            case CIRCUITO_ROYAL_RACEWAY:
            case CIRCUITO_LUIGI_RACEWAY:
            case CIRCUITO_MOO_MOO_FARM:
            case CIRCUITO_TOADS_TURNPIKE:
            case CIRCUITO_SHERBET_LAND:
            case CIRCUITO_DK_JUNGLE:
                persp_lejos_circuito = 4500.0f;
                circuito_cerca_persp = 9.0f;
                break;
            case CIRCUITO_KALAMARI_DESERT:
                persp_lejos_circuito = 7000.0f;
                circuito_cerca_persp = 10.0f;
                break;
            default:
                persp_lejos_circuito = 6800.0f;
                circuito_cerca_persp = 3.0f;
                break;
        }
    }
    switch (seleccion_modo_pantalla) {
        case MODO_PANTALLA_1P:
            aspecto_pantalla = 1.33333334f;
            return;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            aspecto_pantalla = 0.66666667f;
            return;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            aspecto_pantalla = 2.66666667f;
            return;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            aspecto_pantalla = 1.33333334f;
            return;
    }
}

void funcion_802A4EF4(void) {
    switch (modo_pantalla_activo) {
        case MODO_PANTALLA_1P:
            funcion_8001F394(jugador_uno, &acercar_camara[0]);
            break;

        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL:
            funcion_8001F394(jugador_uno, &acercar_camara[0]);
            funcion_8001F394(jugador_dos, &acercar_camara[1]);
            break;
        case PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL:
            funcion_8001F394(jugador_uno, &acercar_camara[0]);
            funcion_8001F394(jugador_dos, &acercar_camara[1]);
            break;
        case PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA:
            funcion_8001F394(jugador_uno, &acercar_camara[0]);
            funcion_8001F394(jugador_dos, &acercar_camara[1]);
            funcion_8001F394(jugador_tres, &acercar_camara[2]);
            funcion_8001F394(jugador_cuatro, &acercar_camara[3]);
            break;
    }
}
void funcion_802A5004(void) {

    inicializar_rdp();
    funcion_802A3730(dato_800DC5F0);

    gSPClearGeometryMode(display_list_cabeza++, 0xFFFFFFFF);

    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH | G_CLIPPING);

    funcion_802A39E0(dato_800DC5F0);
    if (dato_800DC5B4 != 0) {
        renderizar_cielo((Vtx*) cielo_p2, dato_800DC5F0, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[1]);
        funcion_80057FC4(2);
        funcion_802A487C((Vtx*) cielo_p2, dato_800DC5F0, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[1]);
        funcion_80093A30(2);
    }
}
void funcion_802A50EC(void) {

    inicializar_rdp();
    funcion_802A3730(dato_800DC5EC);

    gSPClearGeometryMode(display_list_cabeza++, 0xFFFFFFFF);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH | G_CLIPPING);

    funcion_802A39E0(dato_800DC5EC);
    if (dato_800DC5B4 != 0) {
        renderizar_cielo((Vtx*) cielo_p1, dato_800DC5EC, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[0]);
        funcion_80057FC4(1);
        funcion_802A487C((Vtx*) cielo_p1, dato_800DC5EC, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[0]);
        funcion_80093A30(1);
    }
}
void funcion_802A51D4(void) {

    inicializar_rdp();
    funcion_802A39E0(dato_800DC5EC);
    funcion_802A3730(dato_800DC5EC);

    gSPClearGeometryMode(display_list_cabeza++, 0xFFFFFFFF);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH | G_CLIPPING);

    if (dato_800DC5B4 != 0) {
        renderizar_cielo((Vtx*) cielo_p1, dato_800DC5EC, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[0]);
        funcion_80057FC4(3);
        funcion_802A487C((Vtx*) cielo_p1, dato_800DC5EC, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[0]);
        funcion_80093A30(3);
    }
}
void funcion_802A52BC(void) {

    inicializar_rdp();
    funcion_802A39E0(dato_800DC5F0);
    funcion_802A3730(dato_800DC5F0);

    gSPClearGeometryMode(display_list_cabeza++, 0xFFFFFFFF);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH | G_CLIPPING);

    if (dato_800DC5B4 != 0) {
        renderizar_cielo((Vtx*) cielo_p2, dato_800DC5F0, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[1]);
        funcion_80057FC4(4);
        funcion_802A487C((Vtx*) cielo_p2, dato_800DC5F0, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[1]);
        funcion_80093A30(4);
    }
}
void funcion_802A53A4(void) {

    mover_tabla_segmento_a_dmem();
    inicializar_rdp();
    funcion_802A3730(dato_800DC5EC);

    gSPClearGeometryMode(display_list_cabeza++, 0xFFFFFFFF);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH | G_CLIPPING);

    inicializar_zbuffer();
    seleccionar_framebuffer();
    if (dato_800DC5B4 != 0) {
        renderizar_cielo((Vtx*) cielo_p1, dato_800DC5EC, 0x140, 0xF0, &acercar_camara[0]);
        if (estado_juego != SECUENCIA_CREDITOS) {
            funcion_80057FC4(0);
        }
        funcion_802A487C((Vtx*) cielo_p1, dato_800DC5EC, 0x140, 0xF0, &acercar_camara[0]);
        funcion_80093A30(0);
    }
}
void funcion_802A54A8(void) {

    inicializar_rdp();
    funcion_802A39E0(dato_800DC5EC);
    funcion_802A3730(dato_800DC5EC);

    gSPClearGeometryMode(display_list_cabeza++, 0xFFFFFFFF);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH | G_CLIPPING);

    if (dato_800DC5B4 != 0) {
        renderizar_cielo((Vtx*) cielo_p1, dato_800DC5EC, 0x140, 0xF0, &acercar_camara[0]);
        funcion_80057FC4(8);
        funcion_802A487C((Vtx*) cielo_p1, dato_800DC5EC, 0x140, 0xF0, &acercar_camara[0]);
        funcion_80093A30(8);
    }
}
void funcion_802A5590(void) {

    inicializar_rdp();
    funcion_802A39E0(dato_800DC5F0);
    funcion_802A3730(dato_800DC5F0);

    gSPClearGeometryMode(display_list_cabeza++, 0xFFFFFFFF);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH | G_CLIPPING);

    if (dato_800DC5B4 != 0) {
        renderizar_cielo((Vtx*) cielo_p2, dato_800DC5F0, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[1]);
        funcion_80057FC4(9);
        funcion_802A487C((Vtx*) cielo_p2, dato_800DC5F0, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[1]);
        funcion_80093A30(9);
    }
}
void funcion_802A5678(void) {

    inicializar_rdp();
    funcion_802A39E0(dato_800DC5F4);
    funcion_802A3730(dato_800DC5F4);

    gSPClearGeometryMode(display_list_cabeza++, 0xFFFFFFFF);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH | G_CLIPPING);

    if (dato_800DC5B4 != 0) {
        renderizar_cielo((Vtx*) cielo_p3, dato_800DC5F4, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[2]);
        funcion_80057FC4(10);
        funcion_802A487C((Vtx*) cielo_p3, dato_800DC5F4, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[2]);
        funcion_80093A30(10);
    }
}

void funcion_802A5760(void) {

    inicializar_rdp();

    gSPClearGeometryMode(display_list_cabeza++, 0xFFFFFFFF);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH | G_CLIPPING);

    if (seleccion_cantidad_jugador_1 == 3) {

        gDPPipeSync(display_list_cabeza++);
        funcion_802A39E0(dato_800DC5F8);
        gDPSetCycleType(display_list_cabeza++, G_CYC_FILL);
        gDPSetColorImage(display_list_cabeza++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ANCHO_PANTALLA,
                         VIRTUAL_A_FISICO(framebuffers_fisico[framebuffer_renderizado]));
        gDPSetFillColor(display_list_cabeza++, 0x00010001);
        gDPPipeSync(display_list_cabeza++);
        gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 160, 120, ANCHO_PANTALLA, ALTURA_PANTALLA);
        gDPFillRectangle(display_list_cabeza++, 160, 120, ANCHO_PANTALLA - 1, ALTURA_PANTALLA - 1);
        gDPPipeSync(display_list_cabeza++);
        gDPSetCycleType(display_list_cabeza++, G_CYC_1CYCLE);

        funcion_802A3730(dato_800DC5F8);

    } else {
        funcion_802A3730(dato_800DC5F8);
        funcion_802A39E0(dato_800DC5F8);

        if (dato_800DC5B4 != 0) {
            renderizar_cielo(cielo_p4, dato_800DC5F8, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[3]);
            funcion_80057FC4(11);
            funcion_802A487C(cielo_p4, dato_800DC5F8, ANCHO_PANTALLA, ALTURA_PANTALLA, &acercar_camara[3]);
            funcion_80093A30(11);
        }
    }
}

void renderizar_pantalla_jugador_uno_1j(void) {
    Camara* camara = &camaras[0];
    SIN_USO s32 relleno[4];
    u16 norma_persp;
    SIN_USO s32 relleno2[2];
#ifdef VERSION_EU
    f32 sp9_c;
#endif
    SIN_USO s32 relleno3;
    Mat4 matriz;

#ifdef VERSION_EU
    sp9_c = aspecto_pantalla * 1.2f;
#endif
    funcion_802A53A4();
    inicializar_rdp();
    funcion_802A3730(dato_800DC5EC);
    gSPSetGeometryMode(display_list_cabeza++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
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
    renderizar_objeto(RENDER_PANTALLA_MODO_1J_JUGADOR_UNO);
    renderizar_jugadores_en_pantalla_uno();
    funcion_8029122C(dato_800DC5EC, JUGADOR_UNO);
    funcion_80021B0C();
    renderizar_cajas_item(dato_800DC5EC);
    renderizar_efecto_nieve_jugador(RENDER_PANTALLA_MODO_1J_JUGADOR_UNO);
    funcion_80058BF4();
    if (dato_800DC5B8 != 0) {
        funcion_80058C20(RENDER_PANTALLA_MODO_1J_JUGADOR_UNO);
    }
    funcion_80093A5C(RENDER_PANTALLA_MODO_1J_JUGADOR_UNO);
    if (dato_800DC5B8 != 0) {
        renderizar_hud(RENDER_PANTALLA_MODO_1J_JUGADOR_UNO);
    }
}

void renderizar_vertical_pantalla_jugador_uno_2j(void) {
    Camara* camara = &camaras[0];
    SIN_USO s32 relleno[2];
    u16 norma_persp;
    Mat4 matriz;
#ifdef VERSION_EU
    f32 sp9_c;
#else
    SIN_USO f32 sp9_c;
#endif

    funcion_802A50EC();
#ifdef VERSION_EU
    sp9_c = aspecto_pantalla * 1.2f;
#endif
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
    renderizar_objeto(RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO);
    renderizar_jugadores_en_pantalla_uno();
    funcion_8029122C(dato_800DC5EC, JUGADOR_UNO);
    funcion_80021B0C();
    renderizar_cajas_item(dato_800DC5EC);
    renderizar_efecto_nieve_jugador(RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO);
    funcion_80058BF4();
    if (dato_800DC5B8 != 0) {
        funcion_80058C20(RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO);
    }
    funcion_80093A5C(RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO);
    if (dato_800DC5B8 != 0) {
        renderizar_hud(RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO);
    }
    dato_8015F788 += 1;
}
