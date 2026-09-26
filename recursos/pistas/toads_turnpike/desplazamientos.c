#include <PR/ultratypes.h>
#include <PR/mbi.h>
#include <recursos/datos_comunes.h>
#include "juego/desplazamientos_pista.h"
#include "datos_pista.h"

extern u8 textura_645134[];
extern u8 textura_64FE68[];
extern u8 textura_6607C0[];
extern u8 textura_6608C8[];
extern u8 textura_pasto_11[];
extern u8 textura_cartel_nintendo_rojo_0[];
extern u8 textura_cartel_nintendo_rojo_1[];
extern u8 textura_671A88[];
extern u8 textura_ruta_2[];
extern u8 textura_ruta_3[];
extern u8 textura_ruta_4[];
extern u8 textura_meta_ruta_0[];
extern u8 textura_cartel_toad_amarillo[];
extern u8 textura_cartel_toad_verde[];
extern u8 textura_cartel_carriles_fusion[];
extern u8 textura_65127C[];
extern u8 textura_ruta_5[];
extern u8 textura_cartel_toad_rojo[];
extern u8 textura_668228[];

const textura_circuito toads_turnpike_texturas[] = {
    { textura_645134, 0x052C, 0x0800, 0x0 },
    { textura_64FE68, 0x0258, 0x1000, 0x0 },
    { textura_6607C0, 0x0105, 0x0800, 0x0 },
    { textura_6608C8, 0x0106, 0x0800, 0x0 },
    { textura_pasto_11, 0x01F8, 0x0800, 0x0 },
    { textura_cartel_nintendo_rojo_0, 0x02A6, 0x1000, 0x0 },
    { textura_cartel_nintendo_rojo_1, 0x02F7, 0x1000, 0x0 },
    { textura_671A88, 0x012D, 0x0800, 0x0 },
    { textura_ruta_2, 0x02AE, 0x1000, 0x0 },
    { textura_ruta_3, 0x0286, 0x1000, 0x0 },
    { textura_ruta_4, 0x0282, 0x1000, 0x0 },
    { textura_meta_ruta_0, 0x0338, 0x1000, 0x0 },
    { textura_cartel_toad_amarillo, 0x0723, 0x1000, 0x0 },
    { textura_cartel_toad_verde, 0x071F, 0x1000, 0x0 },
    { textura_cartel_carriles_fusion, 0x0118, 0x0800, 0x0 },
    { textura_65127C, 0x01AB, 0x0800, 0x0 },
    { textura_ruta_5, 0x02B9, 0x1000, 0x0 },
    { textura_cartel_toad_rojo, 0x0610, 0x1000, 0x0 },
    { textura_668228, 0x0130, 0x0800, 0x0 },
    { 0x00000000, 0x0000, 0x0000, 0x0 },
};

const Gfx toads_turnpike_dl_0[] = {
    gsSPDisplayList(d_toads_turnpike_0D005398),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_19518),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053B0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_19020),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_1[] = {
    gsSPDisplayList(d_toads_turnpike_0D005398),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1A068),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053B0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_19DF0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_2[] = {
    gsSPDisplayList(d_toads_turnpike_0D0053C8),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1A6C8),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053F0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1A5F8),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D005418),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_3[] = {
    gsSPDisplayList(d_toads_turnpike_0D005398),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1BE48),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053B0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1B778),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_4[] = {
    gsSPDisplayList(d_toads_turnpike_0D005398),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1CAA8),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053B0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1C700),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_5[] = {
    gsSPDisplayList(d_toads_turnpike_0D0053C8),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1D018),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053F0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1CE70),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D005418),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_6[] = {
    gsSPDisplayList(d_toads_turnpike_0D005398),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1EB48),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053B0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1E458),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_7[] = {
    gsSPDisplayList(d_toads_turnpike_0D005398),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_20008),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053B0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_1F9D0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_8[] = {
    gsSPDisplayList(d_toads_turnpike_0D0053C8),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_205A8),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053F0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_20510),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D005418),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_9[] = {
    gsSPDisplayList(d_toads_turnpike_0D005398),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_21E28),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053B0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_21780),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_10[] = {
    gsSPDisplayList(d_toads_turnpike_0D005398),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_23078),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053B0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_22BA0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

const Gfx toads_turnpike_dl_11[] = {
    gsSPDisplayList(d_toads_turnpike_0D0053C8),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_23848),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D0053F0),
    gsSPDisplayList(d_circuito_toads_turnpike_dl_237F8),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPDisplayList(d_toads_turnpike_0D005418),
    gsSPEndDisplayList(),
};
