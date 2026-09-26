#include <ultra64.h>
#include <juego/macros.h>
#include <juego/definiciones.h>

#include "graficos/vertices_luces_800AF9B0.h"

#include "menus/elementos_menu.h"
#include "memoria/memoria_carrera.h"
#include "sistema/bucle_principal.h"
#include "sistema/matematicas.h"

Ambient dato_800E8680 = { {
    { 31, 31, 31 },
    0,
    { 31, 31, 31 },
    0,
} };

Light dato_800E8688 = { {
    { 255, 255, 255 },
    0,
    { 255, 255, 255 },
    0,
    { 40, 40, 20 },
    0,
} };

s16 dato_8018EDB0;
s16 dato_8018EDB2;
s16 dato_8018EDB4;
Vtx* dato_8018EDB8;
Vtx* dato_8018EDBC;

void funcion_800AF9B0(void) {
    dato_8018EDB8 = (void*) obtener_siguiente_disponible_memoria_direccion(480 * sizeof(Vtx));
    dato_8018EDBC = (void*) obtener_siguiente_disponible_memoria_direccion(480 * sizeof(Vtx));
}

void funcion_800AF9E4(Vtx* parametro0, s32 parametro1, s32 parametro2, s32 parametro3, s16 parametro4, s16 parametro5, s32 parametro6, s32 parametro7) {
    s32 r, g, b;
    s32 i;

    for (i = 0; i < 4; i++) {
        (parametro0 + i)->v.ob[0] = ((i % 2) * parametro7) + parametro6 - 504;
        if (i / 2 == 0) {
            (parametro0 + i)->v.ob[1] = (parametro2 * parametro3) - 420;
        } else {
            (parametro0 + i)->v.ob[1] = (parametro2 * parametro3) + parametro3 - 420;
        }
        if (i % 2 == 0) {
            (parametro0 + i)->v.ob[1] += (f32) CUAD(parametro1) * -0.07f;
        } else {
            (parametro0 + i)->v.ob[1] += (f32) CUAD(parametro1 + 1) * -0.07f;
        }

        (parametro0 + i)->v.cn[0] = 0;
        (parametro0 + i)->v.cn[1] = 0;
        (parametro0 + i)->v.cn[2] = 120;
        (parametro0 + i)->v.cn[3] = 255;

        if (i % 2 == 0) {
            (parametro0 + i)->v.ob[2] = parametro4;
        } else {
            (parametro0 + i)->v.ob[2] = parametro5;
        }
    }

    if ((((parametro1 / 2) + (parametro2 / 2)) & 1) == 0) {
        r = g = b = 0;
    } else {
        r = g = b = 255;
    }

    gDPSetPrimColor(display_list_cabeza++, 0, 0, r, g, b, 255);
    gDPPipeSync(display_list_cabeza++);
    gSPVertex(display_list_cabeza++, VIRTUAL_A_PHYSICAL2(parametro0), 4, 0);
    gSP1Triangle(display_list_cabeza++, 1, 2, 0, 0);
    gSP1Triangle(display_list_cabeza++, 3, 2, 1, 0);
}

void funcion_800AFC54(Vtx* vtx, s32 a, s32 b, s32 c, Vec3s salida) {
    s32 variable_a0;
    s32 variable_a2;
    s32 variable_a4;
    s32 variable_b0;
    s32 variable_b2;
    s32 variable_b4;
    s32 variable_c0;
    s32 variable_c2;
    s32 variable_c4;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 longitud;

    variable_a0 = (vtx + a)->v.ob[0];
    variable_a2 = (vtx + a)->v.ob[1];
    variable_a4 = (vtx + a)->v.ob[2];

    variable_b0 = (vtx + b)->v.ob[0];
    variable_b2 = (vtx + b)->v.ob[1];
    variable_b4 = (vtx + b)->v.ob[2];

    variable_c0 = (vtx + c)->v.ob[0];
    variable_c2 = (vtx + c)->v.ob[1];
    variable_c4 = (vtx + c)->v.ob[2];

    dx = ((variable_b2 - variable_a2) * (variable_c4 - variable_b4)) - ((variable_b4 - variable_a4) * (variable_c2 - variable_b2));
    dy = ((variable_b4 - variable_a4) * (variable_c0 - variable_b0)) - ((variable_b0 - variable_a0) * (variable_c4 - variable_b4));
    dz = ((variable_b0 - variable_a0) * (variable_c2 - variable_b2)) - ((variable_b2 - variable_a2) * (variable_c0 - variable_b0));

    longitud = sqrtf((dx * dx) + (dy * dy) + (dz * dz));

    if (longitud < 0.001) {
        longitud = 0.001;
    }
    longitud = 1.0 / longitud;
    salida[0] = (dx * longitud) * 120.0f;
    salida[1] = (dy * longitud) * 120.0f;
    salida[2] = (dz * longitud) * 120.0f;
}

void funcion_800AFE00(Vtx* parametro0, Vec3s* parametro1, s32 parametro2, s32 parametro3) {
    s32 idx1;
    s32 idx2;
    s32 i;
    Vtx* vtx;
    s16 sp14[2][3];

    idx1 = (parametro2 == 0) ? 0 : parametro2 - 1;
    idx2 = (parametro2 == parametro3) ? parametro3 : parametro2 + 1;

    for (i = 0; i < 3; i++) {
        sp14[0][i] = (parametro1[idx1][i] + parametro1[parametro2][i]) / 2;
        sp14[1][i] = (parametro1[idx2][i] + parametro1[parametro2][i]) / 2;
    }

    for (idx2 = 0; idx2 < 0x1E0; idx2 += 0x30) {
        for (i = 0; i < 4; i++) {
            vtx = &parametro0[i];
            vtx[idx2 / 1].v.cn[0] = sp14[i % 2][0];
            vtx[idx2 / 1].v.cn[1] = sp14[i % 2][1];
            vtx[idx2 / 1].v.cn[2] = sp14[i % 2][2];
        }
    }
}

void funcion_800AFF58(Vtx* parametro0) {
    SIN_USO u32 relleno88[26];
    s32 i, j;
    s16 sp40[12][3];

    for (i = 0, j = 0; i < CANTIDAD_ARREGLO(sp40); i++, j += 4) {
        funcion_800AFC54(&parametro0[j], 1, 2, 0, sp40[i]);
    }

    for (i = 0, j = 0; i < CANTIDAD_ARREGLO(sp40); i++, j += 4) {
        funcion_800AFE00(&parametro0[j], sp40, i, 11);
    }
}

void funcion_800B0004(void) {
    Vtx *vtxs;
    s32 res1;
    s32 res2;
    SIN_USO u32 relleno[0x4];
    s32 i;
    s32 j;
    s32 k;
    s16 idx;
    idx = 4;
    gSPLight(display_list_cabeza++, VIRTUAL_A_PHYSICAL2(&dato_800E8688), LIGHT_1);
    gSPLight(display_list_cabeza++, VIRTUAL_A_PHYSICAL2(&dato_800E8680), LIGHT_2);
    gSPNumLights(display_list_cabeza++, NUMLIGHTS_1);
    gSPSetGeometryMode(display_list_cabeza++, G_SHADE | G_SHADING_SMOOTH);
    gDPSetCombineLERP(display_list_cabeza++, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, SHADE, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, SHADE);
    gSPClearGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPSetGeometryMode(display_list_cabeza++, G_LIGHTING);
    vtxs = (dato_8018EDB4 % 2) ? (dato_8018EDB8) : (dato_8018EDBC);
    dato_8018EDB2 = 0x9C0;
    for (i = 0; i < 10; i++) {
        for (k = 0, j = 0; j < 12; j++, k += 84) {
        res1 = ((senos(dato_8018EDB0 - (j * dato_8018EDB2)) * 84.0f) * j) * 0.18f;
        res2 = ((senos(dato_8018EDB0 - ((j + 1) * dato_8018EDB2)) * 84.0f) * (j + 1)) * 0.18f;
        funcion_800AF9E4(&(&vtxs[j * idx])[i * 48], j, i, 84, res1, res2, k, 84);
        }
    }

    funcion_800AFF58(vtxs);
    dato_8018EDB0 += dato_8018EDB2;
    ++dato_8018EDB4;
    gSPSetGeometryMode(display_list_cabeza++, G_CULL_BACK);
    gSPNumLights(display_list_cabeza++, NUMLIGHTS_1);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
}
