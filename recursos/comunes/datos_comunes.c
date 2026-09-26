#include <juego/macros.h>
#include <juego/definiciones.h>
#include <recursos/datos_comunes.h>

u16 tlut_comun_linea_meta_cartel[] = {
	#include "recursos/comunes/texturas/tlut_linea_meta_cartel.rgba16.inc.c"
};

u16 comun_textura_particula_fuego[] = {
	#include "recursos/comunes/texturas/fuego_particula.rgba16.inc.c"
};

Vtx dato_0D001200[] = {
    {{{   -80,    100,      0}, 0, {     0,    900}, {255, 255, 255, 255}}},
};

Vtx dato_0D001210[] = {
    {{{     4,      0,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{     0,     20,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{    -4,      0,      0}, 0, {     0,      0}, {254,   2,   0,   0}}},
};

Vtx dato_0D001240[] = {
    {{{     4,      0,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{     0,     20,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{    -4,      0,      0}, 0, {     0,      0}, {244, 137,   0,   0}}},
};

Vtx dato_0D001270[] = {
    {{{     4,      0,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{     0,     20,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{    -4,      0,      0}, 0, {     0,      0}, {231, 243,   0,   0}}},
};

Vtx dato_0D0012A0[] = {
    {{{     4,      0,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{     0,     20,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{    -4,      0,      0}, 0, {     0,      0}, {166, 254,  35,   0}}},
};

Vtx dato_0D0012D0[] = {
    {{{     4,      0,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{     0,     20,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{    -4,      0,      0}, 0, {     0,      0}, {  0, 156,  35,   0}}},
};

Vtx dato_0D001300[] = {
    {{{     4,      0,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{     0,     20,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{    -4,      0,      0}, 0, {     0,      0}, {  0, 148, 165,   0}}},
};

Vtx dato_0D001330[] = {
    {{{     4,      0,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{     0,     20,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{    -4,      0,      0}, 0, {     0,      0}, {  0,  80, 157,   0}}},
};

Vtx dato_0D001360[] = {
    {{{     4,      0,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{     0,     20,      0}, 0, {     0,      0}, {  0,   0,   0,   0}}},
    {{{    -4,      0,      0}, 0, {     0,      0}, {  0,   0, 155,   0}}},
};

Vtx vtx_comun_linea_meta_cartel[] = {
    {{{   -80,    100,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{   -40,    100,      0}, 0, {  2012,    990}, {255, 255, 255, 255}}},
    {{{   -40,    115,      0}, 0, {  2012,      0}, {255, 255, 255, 255}}},
    {{{   -80,    115,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{   -80,     85,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{   -40,     85,      0}, 0, {  2012,    990}, {255, 255, 255, 255}}},
    {{{   -40,    100,      0}, 0, {  2012,      0}, {255, 255, 255, 255}}},
    {{{   -80,    100,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{   -40,    100,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{     0,    100,      0}, 0, {  2012,    990}, {255, 255, 255, 255}}},
    {{{     0,    115,      0}, 0, {  2012,      0}, {255, 255, 255, 255}}},
    {{{   -40,    115,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{   -40,     85,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{     0,     85,      0}, 0, {  2012,    990}, {255, 255, 255, 255}}},
    {{{     0,    100,      0}, 0, {  2012,      0}, {255, 255, 255, 255}}},
    {{{   -40,    100,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     0,    100,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{    40,    100,      0}, 0, {  2012,    990}, {255, 255, 255, 255}}},
    {{{    40,    115,      0}, 0, {  2012,      0}, {255, 255, 255, 255}}},
    {{{     0,    115,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     0,     85,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{    40,     85,      0}, 0, {  2012,    990}, {255, 255, 255, 255}}},
    {{{    40,    100,      0}, 0, {  2012,      0}, {255, 255, 255, 255}}},
    {{{     0,    100,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    40,    100,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{    80,    100,      0}, 0, {  2012,    990}, {255, 255, 255, 255}}},
    {{{    80,    115,      0}, 0, {  2012,      0}, {255, 255, 255, 255}}},
    {{{    40,    115,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    40,     85,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{    80,     85,      0}, 0, {  2012,    990}, {255, 255, 255, 255}}},
    {{{    80,    100,      0}, 0, {  2012,      0}, {255, 255, 255, 255}}},
    {{{    40,    100,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
};

Vtx publicar_meta_vtx_comun[] = {
    {{{   -92,      0,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{   -89,      0,      0}, 0, {   990,    990}, {255, 255, 255, 255}}},
    {{{   -89,    115,      0}, 0, {   990,      0}, {255, 255, 255, 255}}},
    {{{   -92,    115,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    89,      0,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{    92,      0,      0}, 0, {   990,    990}, {255, 255, 255, 255}}},
    {{{    92,    115,      0}, 0, {   990,      0}, {255, 255, 255, 255}}},
    {{{    89,    115,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{   -88,    110,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{   -80,    110,      0}, 0, {   990,    990}, {255, 255, 255, 255}}},
    {{{   -80,    115,      0}, 0, {   990,    290}, {255, 255, 255, 255}}},
    {{{   -88,    115,      0}, 0, {     0,    290}, {255, 255, 255, 255}}},
    {{{   -88,     82,      0}, 0, {     0,    660}, {255, 255, 255, 255}}},
    {{{   -80,     85,      0}, 0, {   990,    990}, {255, 255, 255, 255}}},
    {{{   -80,     90,      0}, 0, {   990,    116}, {255, 255, 255, 255}}},
    {{{   -88,     87,      0}, 0, {     0,   -296}, {255, 255, 255, 255}}},
    {{{    80,    110,      0}, 0, {   990,    990}, {255, 255, 255, 255}}},
    {{{    88,    110,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{    88,    115,      0}, 0, {     0,    224}, {255, 255, 255, 255}}},
    {{{    80,    115,      0}, 0, {   990,    224}, {255, 255, 255, 255}}},
    {{{    80,     85,      0}, 0, {     0,    990}, {255, 255, 255, 255}}},
    {{{    88,     82,      0}, 0, {   990,    990}, {255, 255, 255, 255}}},
    {{{    88,     87,      0}, 0, {   990,     22}, {255, 255, 255, 255}}},
    {{{    80,     90,      0}, 0, {     0,      2}, {255, 255, 255, 255}}},
};

Vtx dato_0D001710[] = {
    {{{    80,     85,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{   -80,     85,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{   -80,    115,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    80,    115,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
};

Gfx dato_0D001750[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

Gfx dato_0D001780[] = {
    gsSPVertex(dato_0D001210, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D001798[] = {
    gsSPVertex(dato_0D001240, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D0017B0[] = {
    gsSPVertex(dato_0D001270, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D0017C8[] = {
    gsSPVertex(dato_0D0012A0, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D0017E0[] = {
    gsSPVertex(dato_0D0012D0, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D0017F8[] = {
    gsSPVertex(dato_0D001300, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D001810[] = {
    gsSPVertex(dato_0D001330, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D001828[] = {
    gsSPVertex(dato_0D001360, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D001840[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(tlut_comun_linea_meta_cartel),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x00FC, 0x007C),
    gsDPLoadTextureBlock(0x03004000, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(vtx_comun_linea_meta_cartel, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureBlock(0x03004800, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPLoadTextureBlock(0x03005000, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsDPLoadTextureBlock(0x03005800, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsDPLoadTextureBlock(0x03006000, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsDPLoadTextureBlock(0x03006800, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsDPLoadTextureBlock(0x03007000, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsDPLoadTextureBlock(0x03007800, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx publicar_meta_modelo_comun[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0x03008000),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x007C),
    gsSPVertex(publicar_meta_vtx_comun, 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0x03008800),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x007C),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx dato_0D001B68[] = {
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPVertex(dato_0D001710, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D001B90[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(dato_0D001840),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPDisplayList(publicar_meta_modelo_comun),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx dato_0D001BD8[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPDisplayList(publicar_meta_modelo_comun),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(dato_0D001B68),
    gsSPEndDisplayList(),
};

Gfx dato_0D001C20[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(dato_0D001840),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsSPDisplayList(publicar_meta_modelo_comun),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx dato_0D001C88[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsSPDisplayList(publicar_meta_modelo_comun),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_PASS2),
    gsSPDisplayList(dato_0D001B68),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Vtx caja_item_vtx_comun[] = {
    {{{    -5,      0,     -5}, 0, {     0,      0}, {  0,   0,   0, 128}}},
    {{{    -5,      0,      5}, 0, {     0,      0}, {  0,   0,   0, 128}}},
    {{{     5,      0,      5}, 0, {     0,      0}, {  0,   0,   0, 128}}},
    {{{     5,      0,     -5}, 0, {     0,      0}, {  0,   0,   0, 128}}},
    {{{     3,     -5,      0}, 0, {  1024,   1945}, {255, 255, 255, 255}}},
    {{{     3,      5,      0}, 0, {  1024,   -102}, {255, 255, 255, 255}}},
    {{{    -3,      5,      0}, 0, {     0,   -102}, {255, 255, 255, 255}}},
    {{{    -3,     -5,      0}, 0, {     0,   1945}, {255, 255, 255, 255}}},
    {{{     5,      0,      5}, 0, {     0,      0}, {  0,   0, 255, 153}}},
    {{{     5,      0,     -5}, 0, {     0,      0}, {  0, 255, 255, 153}}},
    {{{     0,      7,      0}, 0, {     0,      0}, {  0, 255,   0, 153}}},
    {{{     5,      0,     -5}, 0, {     0,      0}, {  0, 255, 255, 153}}},
    {{{    -5,      0,     -5}, 0, {     0,      0}, {255, 130,   0, 153}}},
    {{{     0,      7,      0}, 0, {     0,      0}, {  0, 255,   0, 153}}},
    {{{    -5,      0,     -5}, 0, {     0,      0}, {255, 130,   0, 153}}},
    {{{    -5,      0,      5}, 0, {     0,      0}, {255, 255,   0, 153}}},
    {{{     0,      7,      0}, 0, {     0,      0}, {  0, 255,   0, 153}}},
    {{{    -5,      0,      5}, 0, {     0,      0}, {255, 255,   0, 153}}},
    {{{     5,      0,      5}, 0, {     0,      0}, {  0,   0, 255, 153}}},
    {{{     0,      7,      0}, 0, {     0,      0}, {  0, 255,   0, 153}}},
    {{{     5,      0,      5}, 0, {     0,      0}, {  0,   0, 255, 153}}},
    {{{    -5,      0,      5}, 0, {     0,      0}, {255, 255,   0, 153}}},
    {{{     0,     -7,      0}, 0, {     0,      0}, {255,   0,   4, 153}}},
    {{{     5,      0,     -5}, 0, {     0,      0}, {  0, 255, 255, 153}}},
    {{{     5,      0,      5}, 0, {     0,      0}, {  0,   0, 255, 153}}},
    {{{     0,     -7,      0}, 0, {     0,      0}, {255,   0,   4, 153}}},
    {{{    -5,      0,     -5}, 0, {     0,      0}, {255, 130,   0, 153}}},
    {{{     5,      0,     -5}, 0, {     0,      0}, {  0, 255, 255, 153}}},
    {{{     0,     -7,      0}, 0, {     0,      0}, {255,   0,   4, 153}}},
    {{{    -5,      0,      5}, 0, {     0,      0}, {255, 255,   0, 153}}},
    {{{    -5,      0,     -5}, 0, {     0,      0}, {255, 130,   0, 153}}},
    {{{     0,     -7,      0}, 0, {     0,      0}, {255,   0,   4, 153}}},
};

u16 textura_comun_caja_item_signo_pregunta[] = {
	#include "recursos/comunes/texturas/caja_item_signo_pregunta.rgba16.inc.c"
};

Gfx dato_0D002EE8[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 1, 1, G_OFF),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPNoOp(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    gsSPVertex(caja_item_vtx_comun, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Vtx comun_caja_item_falsa_signo_pregunta_vertices[] = {
    {{{    -3,      5,      0}, 0, {  1024,   2048}, {255, 255, 255, 255}}},
    {{{    -3,     -5,      0}, 0, {  1024,      0}, {255, 255, 255, 255}}},
    {{{     3,     -5,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     3,      5,      0}, 0, {     0,   2048}, {255, 255, 255, 255}}},
};

Gfx comun_modelo_falso_caja_item[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x00FC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, textura_comun_caja_item_signo_pregunta),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 2047, 256),
    gsSPVertex(comun_caja_item_falsa_signo_pregunta_vertices, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx caja_item_signo_pregunta_modelo[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x00FC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, textura_comun_caja_item_signo_pregunta),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 2047, 256),
    gsSPVertex(&caja_item_vtx_comun[4], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx dato_0D003090[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&caja_item_vtx_comun[8], 24, 0),
    gsSP1Triangle(9, 10, 11, 0),
    gsSP1Triangle(6, 7, 8, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsSP1Triangle(15, 16, 17, 0),
    gsSP1Triangle(18, 19, 20, 0),
    gsSP1Triangle(21, 22, 23, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D0030F8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&caja_item_vtx_comun[8], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D003128[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&caja_item_vtx_comun[11], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D003158[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&caja_item_vtx_comun[14], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D003188[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&caja_item_vtx_comun[17], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D0031B8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&caja_item_vtx_comun[20], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D0031E8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&caja_item_vtx_comun[23], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D003218[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&caja_item_vtx_comun[26], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D003248[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsSPVertex(&caja_item_vtx_comun[29], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D003278[] = {
    gsSPDisplayList(dato_0D003090),
    gsSPEndDisplayList(),
};

Gfx dato_0D003288[] = {
    gsSPDisplayList(dato_0D003278),
    gsSPEndDisplayList(),
};

Vtx banana_vtx_comun[] = {
    {{{     4,     -3,      0}, 0, {  1228,   1024}, {255, 254, 254, 255}}},
    {{{     0,      4,      0}, 0, {   512,   -204}, {193, 255,   0, 255}}},
    {{{    -4,     -3,      0}, 0, {  -204,   1024}, {255, 254, 254, 255}}},
    {{{     0,     -3,      4}, 0, {  1228,   1024}, {211, 218, 173, 255}}},
    {{{     0,     -3,     -4}, 0, {  -204,   1024}, {211, 218, 173, 255}}},
};

Vtx comun_vtx_plano_banana[] = {
    {{{     6,     -3,      0}, 0, {  2048,   1024}, {255, 254, 254, 255}}},
    {{{     0,      4,      0}, 0, {  1023,   -409}, {193, 255,   0, 255}}},
    {{{    -6,     -3,      0}, 0, {     0,   1024}, {255, 254, 254, 255}}},
    {{{     0,     -3,      6}, 0, {  2048,   1024}, {211, 218, 173, 255}}},
    {{{     0,      4,      0}, 0, {  1024,   -409}, {193, 255,   0, 255}}},
    {{{     0,     -3,     -6}, 0, {     0,   1024}, {211, 218, 173, 255}}},
};

u16 banana_textura_comun[] = {
	#include "recursos/comunes/texturas/banana.rgba16.inc.c"
};

u16 comun_textura_plano_banana[] = {
	#include "recursos/comunes/texturas/banana_plano.rgba16.inc.c"
};

Gfx banana_modelo_comun[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x007C),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, banana_textura_comun),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 256),
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPVertex(banana_vtx_comun, 5, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 1, 4, 0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx comun_modelo_plano_banana[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x00FC, 0x007C),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, comun_textura_plano_banana),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 2047, 128),
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPVertex(comun_vtx_plano_banana, 6, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(3, 4, 5, 0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

u16 comun_tlut_arboles_importar[] = {
	#include "recursos/comunes/texturas/tlut_importar_arboles.rgba16.inc.c"
};

u16 tlut_comun_caparazon_verde[] = {
	#include "recursos/comunes/texturas/tlut_caparazon_verde.rgba16.inc.c"
};

u16 tlut_comun_caparazon_azul[] = {
	#include "recursos/comunes/texturas/tlut_caparazon_azul.rgba16.inc.c"
};

Vtx comun_datos_seg13_vtx_5238[] = {
    {{{     3,      6,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
    {{{    -3,      6,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    -3,      0,      0}, 0, {     0,   1920}, {255, 255, 255, 255}}},
    {{{     3,      0,      0}, 0, {  1984,   1920}, {255, 255, 255, 255}}},
};

Vtx comun_datos_seg13_vtx_5278[] = {
    {{{     3,      6,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    -3,      6,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
    {{{    -3,      0,      0}, 0, {  1984,   1920}, {255, 255, 255, 255}}},
    {{{     3,      0,      0}, 0, {     0,   1920}, {255, 255, 255, 255}}},
};

Gfx dato_0D0052B8[] = {
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x007C, 0x007C),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 1, 1, G_OFF),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx dato_0D005308[] = {
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA), AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPEndDisplayList(),
};

Gfx dato_0D005338[] = {
    gsSPDisplayList(dato_0D005308),
    gsSPVertex(comun_datos_seg13_vtx_5238, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx dato_0D005368[] = {
    gsSPDisplayList(dato_0D005308),
    gsSPVertex(comun_datos_seg13_vtx_5278, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx d_toads_turnpike_0D005398[] = {
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPEndDisplayList(),
};

Gfx d_toads_turnpike_0D0053B0[] = {
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPEndDisplayList(),
};

Gfx d_toads_turnpike_0D0053C8[] = {
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPSetGeometryMode(G_FOG | G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_MODULATEI, G_CC_PASS2),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPEndDisplayList(),
};

Gfx d_toads_turnpike_0D0053F0[] = {
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPSetGeometryMode(G_FOG | G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_MODULATEI, G_CC_PASS2),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPEndDisplayList(),
};

Gfx d_toads_turnpike_0D005418[] = {
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_FOG),
    gsSPEndDisplayList(),
};

Vtx dato_0D005430[] = {
    {{{    -2,     -2,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     1,     -2,      0}, 0, {   192,      0}, {255, 255, 255, 255}}},
    {{{     1,      1,      0}, 0, {   192,    192}, {255, 255, 255, 255}}},
    {{{    -2,      1,      0}, 0, {     0,    192}, {255, 255, 255, 255}}},
};

Vtx comun_vtx_jugador_minimapa_icono[] = {
    {{{    -4,     -4,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     3,     -4,      0}, 0, {   448,      0}, {255, 255, 255, 255}}},
    {{{     3,      3,      0}, 0, {   448,    448}, {255, 255, 255, 255}}},
    {{{    -4,      3,      0}, 0, {     0,    448}, {255, 255, 255, 255}}},
};

Vtx dato_0D0054B0[] = {
    {{{    -4,     -8,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     3,     -8,      0}, 0, {   448,      0}, {255, 255, 255, 255}}},
    {{{     3,      7,      0}, 0, {   448,    960}, {255, 255, 255, 255}}},
    {{{    -4,      7,      0}, 0, {     0,    960}, {255, 255, 255, 255}}},
    {{{    -4,     -8,      0}, 0, {     0,      0}, {255, 255, 128, 255}}},
    {{{     3,     -8,      0}, 0, {   448,      0}, {255, 255, 128, 255}}},
    {{{     3,      7,      0}, 0, {   448,    960}, {255, 128,   0, 255}}},
    {{{    -4,      7,      0}, 0, {     0,    960}, {255, 128,   0, 255}}},
    {{{    -3,     -7,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
    {{{     4,     -7,      0}, 0, {   448,      0}, {  0,   0,   0, 255}}},
    {{{     4,      8,      0}, 0, {   448,    960}, {  0,   0,   0, 255}}},
    {{{    -3,      8,      0}, 0, {     0,    960}, {  0,   0,   0, 255}}},
    {{{    -4,    -80,      0}, 0, {     0,      0}, {255, 255, 128, 255}}},
    {{{     3,    -80,      0}, 0, {   448,      0}, {255, 255, 128, 255}}},
    {{{     3,     79,      0}, 0, {   448,  10176}, {255, 128,   0, 255}}},
    {{{    -4,     79,      0}, 0, {     0,  10176}, {255, 128,   0, 255}}},
    {{{    -6,     -6,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     5,     -6,      0}, 0, {   704,      0}, {255, 255, 255, 255}}},
    {{{     5,      5,      0}, 0, {   704,    704}, {255, 255, 255, 255}}},
    {{{    -6,      5,      0}, 0, {     0,    704}, {255, 255, 255, 255}}},
    {{{    -6,     -8,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     5,     -8,      0}, 0, {   704,      0}, {255, 255, 255, 255}}},
    {{{     5,      7,      0}, 0, {   704,    960}, {255, 255, 255, 255}}},
    {{{    -6,      7,      0}, 0, {     0,    960}, {255, 255, 255, 255}}},
    {{{    -6,     -8,      0}, 0, {     0,      0}, {255, 255, 128, 255}}},
    {{{     5,     -8,      0}, 0, {   704,      0}, {255, 255, 128, 255}}},
    {{{     5,      7,      0}, 0, {   704,    960}, {255, 128,   0, 255}}},
    {{{    -6,      7,      0}, 0, {     0,    960}, {255, 128,   0, 255}}},
    {{{    -5,     -7,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
    {{{     6,     -7,      0}, 0, {   704,      0}, {  0,   0,   0, 255}}},
    {{{     6,      8,      0}, 0, {   704,    960}, {  0,   0,   0, 255}}},
    {{{    -5,      8,      0}, 0, {     0,    960}, {  0,   0,   0, 255}}},
    {{{    -6,    -80,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     5,    -80,      0}, 0, {   704,      0}, {255, 255, 255, 255}}},
    {{{     5,     79,      0}, 0, {   704,  10176}, {255, 255, 255, 255}}},
    {{{    -6,     79,      0}, 0, {     0,  10176}, {255, 255, 255, 255}}},
    {{{    -6,    -80,      0}, 0, {     0,      0}, {255, 255, 128, 255}}},
    {{{     5,    -80,      0}, 0, {   704,      0}, {255, 255, 128, 255}}},
    {{{     5,     79,      0}, 0, {   704,  10176}, {255, 128,   0, 255}}},
    {{{    -6,     79,      0}, 0, {     0,  10176}, {255, 128,   0, 255}}},
    {{{    -6,    -96,      0}, 0, {     0,      0}, {255, 255, 128, 255}}},
    {{{     5,    -96,      0}, 0, {   704,      0}, {255, 255, 128, 255}}},
    {{{     5,     95,      0}, 0, {   704,  12224}, {255, 128,   0, 255}}},
    {{{    -6,     95,      0}, 0, {     0,  12224}, {255, 128,   0, 255}}},
};

Vtx rectangulo_vtx_comun[] = {
    {{{    -8,     -8,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     7,     -8,      0}, 0, {   960,      0}, {255, 255, 255, 255}}},
    {{{     7,      7,      0}, 0, {   960,    960}, {255, 255, 255, 255}}},
    {{{    -8,      7,      0}, 0, {     0,    960}, {255, 255, 255, 255}}},
};

Vtx dato_0D0057B0[] = {
    {{{    -8,     -8,      0}, 0, {   960,      0}, {255, 255, 255, 255}}},
    {{{     7,     -8,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     7,      7,      0}, 0, {     0,    960}, {255, 255, 255, 255}}},
    {{{    -8,      7,      0}, 0, {   960,    960}, {255, 255, 255, 255}}},
};

Vtx dato_0D0057F0[] = {
    {{{    -8,      0,     -8}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     7,      0,     -8}, 0, {   960,      0}, {255, 255, 255, 255}}},
    {{{     7,      0,      7}, 0, {   960,    960}, {255, 255, 255, 255}}},
    {{{    -8,      0,      7}, 0, {     0,    960}, {255, 255, 255, 255}}},
    {{{    -8,     -8,      0}, 0, {     0,      0}, {255, 255, 128, 255}}},
    {{{     7,     -8,      0}, 0, {   960,      0}, {255, 255, 128, 255}}},
    {{{     7,      7,      0}, 0, {   960,    960}, {255, 128,   0, 255}}},
    {{{    -8,      7,      0}, 0, {     0,    960}, {255, 128,   0, 255}}},
    {{{    -6,     -6,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
    {{{     9,     -6,      0}, 0, {   960,      0}, {  0,   0,   0, 255}}},
    {{{     9,      9,      0}, 0, {   960,    960}, {  0,   0,   0, 255}}},
    {{{    -6,      9,      0}, 0, {     0,    960}, {  0,   0,   0, 255}}},
    {{{     0,     -8,      0}, 0, {   448,      0}, {  0,   0,   0, 255}}},
    {{{     8,      8,      0}, 0, {   960,    960}, {  0,   0,   0, 255}}},
    {{{    -8,      8,      0}, 0, {     0,    960}, {  0,   0,   0, 255}}},
};

Vtx comun_datos_seg_13_vtx_58E0[] = {
    {{{    -8,     -8,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     7,     -8,      0}, 0, {   960,      0}, {255, 255, 255, 255}}},
    {{{     7,      7,      0}, 0, {   960,    960}, {255, 255, 255, 255}}},
    {{{    -8,      7,      0}, 0, {     0,    960}, {255, 255, 255, 255}}},
};

Vtx dato_0D005920[] = {
    {{{    -4,    -32,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     3,    -32,      0}, 0, {   960,      0}, {255, 255, 255, 255}}},
    {{{     3,     31,      0}, 0, {   960,    960}, {255, 255, 255, 255}}},
    {{{    -4,     31,      0}, 0, {     0,    960}, {255, 255, 255, 255}}},
    {{{    -8,    -80,      0}, 0, {     0,      0}, {255, 255, 128, 255}}},
    {{{     7,    -80,      0}, 0, {   960,      0}, {255, 255, 128, 255}}},
    {{{     7,     79,      0}, 0, {   960,  10176}, {255, 128,   0, 255}}},
    {{{    -8,     79,      0}, 0, {     0,  10176}, {255, 128,   0, 255}}},
    {{{   -10,    -10,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     9,    -10,      0}, 0, {  1216,      0}, {255, 255, 255, 255}}},
    {{{     9,      9,      0}, 0, {  1216,   1216}, {255, 255, 255, 255}}},
    {{{   -10,      9,      0}, 0, {     0,   1216}, {255, 255, 255, 255}}},
    {{{   -12,    -12,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    11,    -12,      0}, 0, {  1472,      0}, {255, 255, 255, 255}}},
    {{{    11,     11,      0}, 0, {  1472,   1472}, {255, 255, 255, 255}}},
    {{{   -12,     11,      0}, 0, {     0,   1472}, {255, 255, 255, 255}}},
    {{{   -12,    -24,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    11,    -24,      0}, 0, {  1472,      0}, {255, 255, 255, 255}}},
    {{{    11,     23,      0}, 0, {  1472,   3008}, {255, 255, 255, 255}}},
    {{{   -12,     23,      0}, 0, {     0,   3008}, {255, 255, 255, 255}}},
    {{{   -14,    -14,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    13,    -14,      0}, 0, {  1728,      0}, {255, 255, 255, 255}}},
    {{{    13,     13,      0}, 0, {  1728,   1728}, {255, 255, 255, 255}}},
    {{{   -14,     13,      0}, 0, {     0,   1728}, {255, 255, 255, 255}}},
};

Vtx dato_0D005AA0[] = {
    {{{   -16,     -8,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    15,     -8,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
    {{{    15,      7,      0}, 0, {  1984,    960}, {255, 255, 255, 255}}},
    {{{   -16,      7,      0}, 0, {     0,    960}, {255, 255, 255, 255}}},
};

Vtx dato_0D005AE0[] = {
    {{{   -16,    -16,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    15,    -16,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
    {{{    15,     15,      0}, 0, {  1984,   1984}, {255, 255, 255, 255}}},
    {{{   -16,     15,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
};

Vtx dato_0D005B20[] = {
    {{{   -16,    -16,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
    {{{    15,    -16,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    15,     15,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -16,     15,      0}, 0, {  1984,   1984}, {255, 255, 255, 255}}},
};

Vtx dato_0D005B60[] = {
    {{{   -16,      0,    -16}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    15,      0,    -16}, 0, {  1984,      0}, {255, 255, 255, 255}}},
    {{{    15,      0,     15}, 0, {  1984,   1984}, {255, 255, 255, 255}}},
    {{{   -16,      0,     15}, 0, {     0,   1984}, {255, 255, 255, 255}}},
};

Vtx dato_0D005BA0[] = {
    {{{     0,     18,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    16,     -9,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
    {{{   -16,     -9,      0}, 0, {  1984,   1984}, {255, 255, 255, 255}}},
};

Vtx dato_0D005BD0[] = {
    {{{     0,     18,      0}, 0, {     0,      0}, {  0,   0, 120, 255}}},
    {{{    16,     -9,      0}, 0, {  1984,      0}, {  0,   0, 120, 255}}},
    {{{   -16,     -9,      0}, 0, {  1984,   1984}, {  0,   0, 120, 255}}},
};

Vtx dato_0D005C00[] = {
    {{{     0,     18,      0}, 0, {     0,      0}, {213,  44, 102, 255}}},
    {{{    16,     -9,      0}, 0, {  1984,      0}, {102, 211,  43, 255}}},
    {{{   -16,     -9,      0}, 0, {  1984,   1984}, { 42, 153, 214, 255}}},
};

Vtx dato_0D005C30[] = {
    {{{   -20,    -15,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    19,    -15,      0}, 0, {  2496,      0}, {255, 255, 255, 255}}},
    {{{    19,     16,      0}, 0, {  2496,   1984}, {255, 255, 255, 255}}},
    {{{   -20,     16,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -20,    -19,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    19,    -19,      0}, 0, {  2496,      0}, {255, 255, 255, 255}}},
    {{{    19,     20,      0}, 0, {  2496,   2496}, {255, 255, 255, 255}}},
    {{{   -20,     20,      0}, 0, {     0,   2496}, {255, 255, 255, 255}}},
    {{{   -24,     -8,      0}, 0, {     0,      0}, {255, 255, 128, 255}}},
    {{{    23,     -8,      0}, 0, {  3008,      0}, {255, 255, 128, 255}}},
    {{{    23,      7,      0}, 0, {  3008,    960}, {255, 128,   0, 255}}},
    {{{   -24,      7,      0}, 0, {     0,    960}, {255, 128,   0, 255}}},
    {{{   -24,     -8,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
    {{{    23,     -8,      0}, 0, {  3008,      0}, {  0,   0,   0, 255}}},
    {{{    23,      7,      0}, 0, {  3008,    960}, {  0,   0,   0, 255}}},
    {{{   -24,      7,      0}, 0, {     0,    960}, {  0,   0,   0, 255}}},
    {{{   -24,    -19,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    23,    -19,      0}, 0, {  3008,      0}, {255, 255, 255, 255}}},
    {{{    23,     20,      0}, 0, {  3008,   2496}, {255, 255, 255, 255}}},
    {{{   -24,     20,      0}, 0, {     0,   2496}, {255, 255, 255, 255}}},
    {{{   -24,    -19,      0}, 0, {  3008,      0}, {255, 255, 255, 255}}},
    {{{    23,    -19,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    23,     20,      0}, 0, {     0,   2496}, {255, 255, 255, 255}}},
    {{{   -24,     20,      0}, 0, {  3008,   2496}, {255, 255, 255, 255}}},
    {{{   -24,    -19,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
    {{{    23,    -19,      0}, 0, {  3008,      0}, {  0,   0,   0, 255}}},
    {{{    23,      0,      0}, 0, {  3008,   1216}, {  0,   0,   0, 255}}},
    {{{   -24,      0,      0}, 0, {     0,   1216}, {  0,   0,   0, 255}}},
    {{{   -24,      0,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
    {{{    23,      0,      0}, 0, {  3008,      0}, {  0,   0,   0, 255}}},
    {{{    23,     19,      0}, 0, {  3008,   1216}, {  0,   0,   0, 255}}},
    {{{   -24,     19,      0}, 0, {     0,   1216}, {  0,   0,   0, 255}}},
    {{{   -24,    -23,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    23,    -23,      0}, 0, {  3008,      0}, {255, 255, 255, 255}}},
    {{{    23,      0,      0}, 0, {  3008,   1472}, {255, 255, 255, 255}}},
    {{{   -24,      0,      0}, 0, {     0,   1472}, {255, 255, 255, 255}}},
    {{{   -24,      0,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
};

Vtx dato_0D005E80[] = {
    {{{    23,      0,      0}, 0, {  3008,      0}, {255, 255, 255, 255}}},
    {{{    23,     23,      0}, 0, {  3008,   1472}, {255, 255, 255, 255}}},
    {{{   -24,     23,      0}, 0, {     0,   1472}, {255, 255, 255, 255}}},
};

Vtx vtx_comun_lakitu[] = {
    {{{   -28,    -35,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    27,    -35,      0}, 0, {  3520,      0}, {255, 255, 255, 255}}},
    {{{    27,      0,      0}, 0, {  3520,   2240}, {255, 255, 255, 255}}},
    {{{   -28,      0,      0}, 0, {     0,   2240}, {255, 255, 255, 255}}},
    {{{   -28,      0,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    27,      0,      0}, 0, {  3520,      0}, {255, 255, 255, 255}}},
    {{{    27,     35,      0}, 0, {  3520,   2240}, {255, 255, 255, 255}}},
    {{{   -28,     35,      0}, 0, {     0,   2240}, {255, 255, 255, 255}}},
};

Vtx dato_0D005F30[] = {
    {{{   -10,    -35,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    45,    -35,      0}, 0, {  3520,      0}, {255, 255, 255, 255}}},
    {{{    45,      0,      0}, 0, {  3520,   2240}, {255, 255, 255, 255}}},
    {{{   -10,      0,      0}, 0, {     0,   2240}, {255, 255, 255, 255}}},
    {{{   -10,      0,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    45,      0,      0}, 0, {  3520,      0}, {255, 255, 255, 255}}},
    {{{    45,     35,      0}, 0, {  3520,   2240}, {255, 255, 255, 255}}},
    {{{   -10,     35,      0}, 0, {     0,   2240}, {255, 255, 255, 255}}},
};

Vtx dato_0D005FB0[] = {
    {{{   -32,    -16,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,    -16,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,     15,      0}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
    {{{   -32,     15,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
};

Vtx dato_0D005FF0[] = {
    {{{   -53,    -16,      0}, 0, {     0,      0}, {255,   0,   0, 255}}},
    {{{    10,    -16,      0}, 0, {  4032,      0}, {255,   0,   0, 255}}},
    {{{    10,     15,      0}, 0, {  4032,   1984}, {255,   0,   0, 255}}},
    {{{   -53,     15,      0}, 0, {     0,   1984}, {255,   0,   0, 255}}},
};

Vtx dato_0D006030[] = {
    {{{   -32,    -32,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,    -32,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,     31,      0}, 0, {  4032,   4032}, {255, 255, 255, 255}}},
    {{{   -32,     31,      0}, 0, {     0,   4032}, {255, 255, 255, 255}}},
    {{{   -32,    -32,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
    {{{    31,    -32,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
    {{{    31,     31,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
    {{{   -32,     31,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
};

Vtx erizo_vtx_comun[] = {
    {{{   -32,    -31,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,    -31,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,      0,      0}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
    {{{   -32,      0,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -32,      0,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,      0,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,     31,      0}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
    {{{   -32,     31,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
};

Vtx dato_0D006130[] = {
    {{{   -32,    -31,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,    -31,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,      0,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -32,      0,      0}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
    {{{   -32,      0,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,      0,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,     31,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -32,     31,      0}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
};

Vtx dato_0D0061B0[] = {
    {{{   -32,    -31,    -12}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,    -31,    -12}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,      0,    -12}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
    {{{   -32,      0,    -12}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -32,      0,    -12}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,      0,    -12}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,     31,    -12}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
    {{{   -32,     31,    -12}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -32,    -31,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,    -31,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,      0,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -32,      0,      0}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
    {{{   -32,      0,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,      0,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,     31,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -32,     31,      0}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
};

Vtx dato_0D0062B0[] = {
    {{{   -32,    -32,     20}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,    -32,     20}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,     31,     20}, 0, {  4032,   4032}, {255, 255, 255, 255}}},
    {{{   -32,     31,     20}, 0, {     0,   4032}, {255, 255, 255, 255}}},
    {{{   -31,    -32,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     0,    -32,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
    {{{     0,     31,      0}, 0, {  1984,   4032}, {255, 255, 255, 255}}},
    {{{   -31,     31,      0}, 0, {     0,   4032}, {255, 255, 255, 255}}},
    {{{     1,    -32,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    32,    -32,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
    {{{    32,     31,      0}, 0, {  1984,   4032}, {255, 255, 255, 255}}},
    {{{     1,     31,      0}, 0, {     0,   4032}, {255, 255, 255, 255}}},
    {{{   -32,    -31,      0}, 0, {    64,     64}, {255, 255, 255, 255}}},
    {{{    31,    -31,      0}, 0, {  4096,     64}, {255, 255, 255, 255}}},
    {{{    31,      0,      0}, 0, {  4096,   2048}, {255, 255, 255, 255}}},
    {{{   -32,      0,      0}, 0, {    64,   2048}, {255, 255, 255, 255}}},
    {{{   -32,      1,      0}, 0, {    64,     64}, {255, 255, 255, 255}}},
    {{{    31,      1,      0}, 0, {  4096,     64}, {255, 255, 255, 255}}},
    {{{    31,     32,      0}, 0, {  4096,   2048}, {255, 255, 255, 255}}},
    {{{   -32,     32,      0}, 0, {    64,   2048}, {255, 255, 255, 255}}},
    {{{   -32,    -48,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,    -48,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,    -16,      0}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
    {{{   -32,    -16,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -32,    -16,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,    -16,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,     15,      0}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
    {{{   -32,     15,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -32,     15,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,     15,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,     47,      0}, 0, {  4032,   1984}, {255, 255, 255, 255}}},
    {{{   -32,     47,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
};

Vtx dato_0D0064B0[] = {
    {{{   -32,    -47,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,    -47,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,      0,      0}, 0, {  4032,   3008}, {255, 255, 255, 255}}},
    {{{   -32,      0,      0}, 0, {     0,   3008}, {255, 255, 255, 255}}},
    {{{   -32,      0,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    31,      0,      0}, 0, {  4032,      0}, {255, 255, 255, 255}}},
    {{{    31,     47,      0}, 0, {  4032,   3008}, {255, 255, 255, 255}}},
    {{{   -32,     47,      0}, 0, {     0,   3008}, {255, 255, 255, 255}}},
    {{{   -36,    -23,      0}, 0, {     0,     32}, {255, 255, 255, 255}}},
    {{{    35,    -23,      0}, 0, {  4544,     32}, {255, 255, 255, 255}}},
    {{{    35,      0,      0}, 0, {  4544,   1504}, {255, 255, 255, 255}}},
    {{{   -36,      0,      0}, 0, {     0,   1504}, {255, 255, 255, 255}}},
    {{{   -36,      0,      0}, 0, {     0,     32}, {255, 255, 255, 255}}},
    {{{    35,      0,      0}, 0, {  4544,     32}, {255, 255, 255, 255}}},
    {{{    35,     23,      0}, 0, {  4544,   1504}, {255, 255, 255, 255}}},
    {{{   -36,     23,      0}, 0, {     0,   1504}, {255, 255, 255, 255}}},
    {{{   -36,    -23,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    35,    -23,      0}, 0, {  4544,      0}, {255, 255, 255, 255}}},
    {{{    35,      0,      0}, 0, {  4544,   1472}, {255, 255, 255, 255}}},
    {{{   -36,      0,      0}, 0, {     0,   1472}, {255, 255, 255, 255}}},
    {{{   -36,      0,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    35,      0,      0}, 0, {  4544,      0}, {255, 255, 255, 255}}},
    {{{    35,     23,      0}, 0, {  4544,   1472}, {255, 255, 255, 255}}},
    {{{   -36,     23,      0}, 0, {     0,   1472}, {255, 255, 255, 255}}},
    {{{   -36,    -23,      0}, 0, {     0,     16}, {255, 255, 255, 255}}},
    {{{    35,    -23,      0}, 0, {  4544,     16}, {255, 255, 255, 255}}},
    {{{    35,      0,      0}, 0, {  4544,   1488}, {255, 255, 255, 255}}},
    {{{   -36,      0,      0}, 0, {     0,   1488}, {255, 255, 255, 255}}},
    {{{   -36,      0,      0}, 0, {     0,     16}, {255, 255, 255, 255}}},
    {{{    35,      0,      0}, 0, {  4544,     16}, {255, 255, 255, 255}}},
    {{{    35,     23,      0}, 0, {  4544,   1488}, {255, 255, 255, 255}}},
    {{{   -36,     23,      0}, 0, {     0,   1488}, {255, 255, 255, 255}}},
    {{{   -36,    -23,      0}, 0, {     0,     32}, {255, 255, 255, 255}}},
    {{{    35,    -23,      0}, 0, {  4544,     32}, {255, 255, 255, 255}}},
    {{{    35,      0,      0}, 0, {  4544,   1504}, {255, 255, 255, 255}}},
    {{{   -36,      0,      0}, 0, {     0,   1504}, {255, 255, 255, 255}}},
    {{{   -36,      0,      0}, 0, {     0,     32}, {255, 255, 255, 255}}},
    {{{    35,      0,      0}, 0, {  4544,     32}, {255, 255, 255, 255}}},
    {{{    35,     23,      0}, 0, {  4544,   1504}, {255, 255, 255, 255}}},
    {{{   -36,     23,      0}, 0, {     0,   1504}, {255, 255, 255, 255}}},
};

Vtx tambien_vtx_comun_lakitu[] = {
    {{{   -36,    -27,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    35,    -27,      0}, 0, {  4544,      0}, {255, 255, 255, 255}}},
    {{{    35,      0,      0}, 0, {  4544,   1728}, {255, 255, 255, 255}}},
    {{{   -36,      0,      0}, 0, {     0,   1728}, {255, 255, 255, 255}}},
    {{{   -36,      0,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    35,      0,      0}, 0, {  4544,      0}, {255, 255, 255, 255}}},
    {{{    35,     27,      0}, 0, {  4544,   1728}, {255, 255, 255, 255}}},
    {{{   -36,     27,      0}, 0, {     0,   1728}, {255, 255, 255, 255}}},
    {{{   -40,    -24,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    40,    -24,      0}, 0, {  5056,      0}, {255, 255, 255, 255}}},
    {{{    40,      0,      0}, 0, {  5056,   1472}, {255, 255, 255, 255}}},
    {{{   -40,      0,      0}, 0, {     0,   1472}, {255, 255, 255, 255}}},
    {{{   -40,      0,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    40,      0,      0}, 0, {  5056,      0}, {255, 255, 255, 255}}},
    {{{    40,     24,      0}, 0, {  5056,   1472}, {255, 255, 255, 255}}},
    {{{   -40,     24,      0}, 0, {     0,   1472}, {255, 255, 255, 255}}},
    {{{   -48,     -8,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    47,     -8,      0}, 0, {  6080,      0}, {255, 255, 255, 255}}},
    {{{    47,      7,      0}, 0, {  6080,    960}, {255, 255, 255, 255}}},
    {{{   -48,      7,      0}, 0, {     0,    960}, {255, 255, 255, 255}}},
    {{{   -56,    -16,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    55,    -16,      0}, 0, {  7104,      0}, {255, 255, 255, 255}}},
    {{{    55,     15,      0}, 0, {  7104,   1984}, {255, 255, 255, 255}}},
    {{{   -56,     15,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{   -56,    -16,      0}, 0, {     0,      0}, {  0,   0,   0, 255}}},
    {{{    55,    -16,      0}, 0, {  7104,      0}, {  0,   0,   0, 255}}},
    {{{    55,     15,      0}, 0, {  7104,   1984}, {  0,   0,   0, 255}}},
    {{{   -56,     15,      0}, 0, {     0,   1984}, {  0,   0,   0, 255}}},
};

Vtx dato_0D0068F0[] = {
    {{{   -64,    -32,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{    63,    -32,      0}, 0, {  8128,      0}, {255, 255, 255, 255}}},
    {{{    63,     31,      0}, 0, {  8128,   4032}, {255, 255, 255, 255}}},
    {{{   -64,     31,      0}, 0, {     0,   4032}, {255, 255, 255, 255}}},
};

Gfx dato_0D006930[] = {
    gsSP1Triangle(0, 2, 1, 0),
    gsSPEndDisplayList(),
};

Gfx pantalla_rectangulo_comun[] = {
    gsSP2Triangles(0, 2, 1, 0, 0, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D006950[] = {
    gsSPVertex(comun_vtx_jugador_minimapa_icono, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

Gfx dato_0D006968[] = {
    gsSPVertex(dato_0D0054B0, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

Gfx dato_0D006980[] = {
    gsSPVertex(rectangulo_vtx_comun, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

Gfx dato_0D006998[] = {
    gsSPVertex(dato_0D0057B0, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

Gfx dato_0D0069B0[] = {
    gsSPVertex(dato_0D0057F0, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

Gfx dato_0D0069C8[] = {
    gsSPVertex(dato_0D005AA0, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

Gfx dato_0D0069E0[] = {
    gsSPVertex(dato_0D005AE0, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

Gfx dato_0D0069F8[] = {
    gsSPVertex(dato_0D005B20, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

Gfx dato_0D006A10[] = {
    gsSPVertex(dato_0D005B60, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

Gfx dato_0D006A28[] = {
    gsSPVertex(comun_datos_seg_13_vtx_58E0, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

Gfx dato_0D006A40[] = {
    gsSPVertex(dato_0D005920, 4, 0),
    gsSPDisplayList(pantalla_rectangulo_comun),
    gsSPEndDisplayList(),
};

u8 sombra_comun_i4[] = {
	#include "recursos/comunes/texturas/sombra_i4.i4.inc.c"
};

u8 dato_0D006AD8[] = {
	#include "recursos/comunes/texturas/dato_0D006AD8.i4.inc.c"
};

u16 comun_tlut_depuracion_fuente[] = {
	#include "recursos/comunes/texturas/tlut_fuente_depuracion.tlut.inc.c"
};

u16 comun_textura_depuracion_fuente[] = {
	#include "recursos/comunes/texturas/fuente_depuracion.tlut.inc.c"
};

Gfx dato_0D0076F8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPNoOp(),
    gsDPSetColorDither(G_CD_DISABLE),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

Gfx dato_0D007780[] = {
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx dato_0D0077A0[] = {
    gsSPDisplayList(dato_0D007780),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

Gfx dato_0D0077D0[] = {
    gsSPDisplayList(dato_0D007780),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx dato_0D0077F8[] = {
    gsSPDisplayList(dato_0D007780),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx dato_0D007828[] = {
    gsSPDisplayList(dato_0D007780),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx dato_0D007850[] = {
    gsSPDisplayList(dato_0D007780),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx dato_0D007878[] = {
    gsSPDisplayList(dato_0D007780),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx dato_0D0078A0[] = {
    gsSPDisplayList(dato_0D007780),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

Gfx dato_0D0078D0[] = {
    gsSPDisplayList(dato_0D007780),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx dato_0D0078F8[] = {
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx dato_0D007928[] = {
    gsSPDisplayList(dato_0D0078F8),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx dato_0D007948[] = {
    gsSPDisplayList(dato_0D0078F8),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx dato_0D007968[] = {
    gsSPDisplayList(dato_0D0078F8),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx dato_0D007988[] = {
    gsSPDisplayList(dato_0D0078F8),
    gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx dato_0D0079A8[] = {
    gsSPDisplayList(dato_0D0078F8),
    gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx dato_0D0079C8[] = {
    gsSPDisplayList(dato_0D0078F8),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx dato_0D0079E8[] = {
    gsSPDisplayList(dato_0D0078F8),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA), AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx dato_0D007A08[] = {
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx dato_0D007A40[] = {
    gsSPDisplayList(dato_0D007A08),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007A60[] = {
    gsSPDisplayList(dato_0D007A08),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007A80[] = {
    gsSPDisplayList(dato_0D007A08),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007AA0[] = {
    gsSPDisplayList(dato_0D007A08),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007AC0[] = {
    gsSPDisplayList(dato_0D007A08),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007AE0[] = {
    gsSPDisplayList(dato_0D007A08),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007B00[] = {
    gsSPDisplayList(dato_0D007A08),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007B20[] = {
    gsSPDisplayList(dato_0D007A08),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetPrimColor(0, 0, 0x14, 0x14, 0x14, 0x00),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPLoadTextureBlock_4b(sombra_comun_i4, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(dato_0D006980),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

Gfx dato_0D007B98[] = {
    gsSPDisplayList(dato_0D007A08),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetPrimColor(0, 0, 0x14, 0x14, 0x14, 0x00),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPLoadTextureBlock_4b(sombra_comun_i4, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(dato_0D0069B0),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

Gfx dato_0D007C10[] = {
    gsSPDisplayList(dato_0D007A08),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetPrimColor(0, 0, 0x1E, 0x0A, 0x00, 0xC8),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPLoadTextureBlock(dato_0D006AD8, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(dato_0D006A10),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

Gfx dato_0D007C88[] = {
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx dato_0D007CB8[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007CD8[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007CF8[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_AVERAGE),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007D18[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx dato_0D007D38[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007D58[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007D78[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007D98[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007DB8[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007DD8[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007DF8[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007E18[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007E38[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007E58[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007E78[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA), AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsSPEndDisplayList(),
};

Gfx dato_0D007E98[] = {
    gsSPDisplayList(dato_0D007C88),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA), AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsSPEndDisplayList(),
};

Gfx dato_0D007EB8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx dato_0D007ED8[] = {
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPEndDisplayList(),
};

Gfx dato_0D007EF8[] = {
    gsSPDisplayList(dato_0D007ED8),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

Gfx dato_0D007F18[] = {
    gsSPDisplayList(dato_0D007ED8),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx dato_0D007F38[] = {
    gsSPDisplayList(dato_0D007ED8),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D007F58[] = {
    gsSPDisplayList(dato_0D007ED8),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx dato_0D007F78[] = {
    gsSPDisplayList(dato_0D007ED8),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx dato_0D007F98[] = {
    gsSPDisplayList(dato_0D007ED8),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA), AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | ZMODE_XLU | CVG_X_ALPHA | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

Gfx dato_0D007FB8[] = {
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx dato_0D007FE0[] = {
    gsSPDisplayList(dato_0D007FB8),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D008000[] = {
    gsSPDisplayList(dato_0D007FB8),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx dato_0D008020[] = {
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPEndDisplayList(),
};

Gfx dato_0D008040[] = {
    gsSPDisplayList(dato_0D008020),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsSPEndDisplayList(),
};

Gfx dato_0D008060[] = {
    gsSPDisplayList(dato_0D008020),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsSPEndDisplayList(),
};

Gfx dato_0D008080[] = {
    gsSPDisplayList(dato_0D007EF8),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(0, comun_tlut_depuracion_fuente),
    gsDPLoadSync(),
    gsDPLoadTextureBlock_4b(comun_textura_depuracion_fuente, G_IM_FMT_CI, 128, 32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPEndDisplayList(),
};

Gfx dato_0D008108[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsSPEndDisplayList(),
};

Gfx dato_0D008120[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

Gfx dato_0D008138[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPEndDisplayList(),
};

u8 comun_gran_premio_curva_item_humano[][100] = {
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
    {
        GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
    {
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
    {
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
    {
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
    {
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
    {
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
    {
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO,
        AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
};

u8 comun_gran_premio_curva_item_cpu[][100] = {
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO,
    },
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
        ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, RAYO_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
};

u8 comun_versus_curva_item_2_jugador[][100] = {
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BOO, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM,
        GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, ITEM_BOO, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_BOO, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_BOO, TRIPLE_ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_BOO,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
    {
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, GRUPO_BANANA_ITEM, TRIPLE_ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_ROJO, AZUL_ITEM_CAPARAZON_ESPINOSO, ITEM_SUPER_HONGO,
        ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, TRIPLE_ITEM_CAPARAZON_VERDE,
        AZUL_ITEM_CAPARAZON_ESPINOSO, ITEM_CAPARAZON_ROJO, GRUPO_BANANA_ITEM, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_ROJO, AZUL_ITEM_CAPARAZON_ESPINOSO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, GRUPO_BANANA_ITEM, AZUL_ITEM_CAPARAZON_ESPINOSO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
        ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, GRUPO_BANANA_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_ROJO, AZUL_ITEM_CAPARAZON_ESPINOSO, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_VERDE, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, GRUPO_BANANA_ITEM,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
};

u8 comun_versus_curva_item_3_jugador[][100] = {
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
    {
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
};

u8 comun_versus_curva_item_4_jugador[][100] = {
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
    },
    {
        ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM,
        ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO,
        HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
    },
    {
        GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
        ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM, HONGO_ITEM,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
    {
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO, TRIPLE_ITEM_CAPARAZON_ROJO,
        AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO, AZUL_ITEM_CAPARAZON_ESPINOSO,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM,
        RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, RAYO_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
        ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO, ITEM_TRIPLE_HONGO,
        ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO, ITEM_SUPER_HONGO,
    },
};

u8 comun_batalla_item_curva[][100] = {
    {
    ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA, ITEM_BANANA,
    GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, GRUPO_BANANA_ITEM, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE, ITEM_CAPARAZON_VERDE,
    TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
    TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE, TRIPLE_ITEM_CAPARAZON_VERDE,
    ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
    ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO, ITEM_CAPARAZON_ROJO,
    ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA,
    ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ITEM_CAJA_ITEM_FALSA, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
    ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM,
    ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ESTRELLA_ITEM, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO, ITEM_BOO,
    },
};

Vtx dato_0D008B78[] = {
    {{{     2,      2,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     2,     -2,      0}, 0, {     0,    960}, {255, 255, 255, 255}}},
    {{{    -2,     -2,      0}, 0, {   960,    960}, {255, 255, 255, 255}}},
    {{{    -2,      2,      0}, 0, {   960,      0}, {255, 255, 255, 255}}},
};

Vtx dato_0D008BB8[] = {
    {{{     2,      4,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     2,      0,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{    -2,      0,      0}, 0, {  1984,   1984}, {255, 255, 255, 255}}},
    {{{    -2,      4,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
};

Vtx dato_0D008BF8[] = {
    {{{     2,      2,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
    {{{     2,     -2,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{    -2,     -2,      0}, 0, {  1984,   1984}, {255, 255, 255, 255}}},
    {{{    -2,      2,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
};

Vtx dato_0D008C38[] = {
    {{{     2,      2,      0}, 0, {  1984,      0}, {255, 255, 255, 255}}},
    {{{     2,     -2,      0}, 0, {  1984,   1984}, {255, 255, 255, 255}}},
    {{{    -2,     -2,      0}, 0, {     0,   1984}, {255, 255, 255, 255}}},
    {{{    -2,      2,      0}, 0, {     0,      0}, {255, 255, 255, 255}}},
};

Gfx renderizar_simple_cuadrado_comun[] = {
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx dato_0D008C90[] = {
    gsDPPipeSync(),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),
};

Gfx renderizar_personaje_ajuste_comun[] = {
    gsDPPipeSync(),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),
};

Gfx dato_0D008D10[] = {
    gsDPPipeSync(),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA), AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),
};

Gfx dato_0D008D58[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPNoOp(),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPEndDisplayList(),
};

Gfx dato_0D008DA0[] = {
    gsSPDisplayList(renderizar_simple_cuadrado_comun),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

Gfx dato_0D008DB8[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPNoOp(),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx dato_0D008DF8[] = {
    gsDPSetRenderMode(G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    gsSPVertex(dato_0D008B78, 4, 0),
    gsSPDisplayList(dato_0D008DA0),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx dato_0D008E20[] = {
    gsDPSetRenderMode(G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    gsSPVertex(dato_0D008BB8, 4, 0),
    gsSPDisplayList(dato_0D008DA0),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx dato_0D008E48[] = {
    gsDPSetRenderMode(G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    gsSPVertex(dato_0D008BF8, 4, 0),
    gsSPDisplayList(dato_0D008DA0),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx dato_0D008E70[] = {
    gsDPSetRenderMode(G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2),
    gsSPVertex(dato_0D008C38, 4, 0),
    gsSPDisplayList(dato_0D008DA0),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Mtx dato_0D008E98 = {
    a_matriz_punto_fijo(1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                       0.0, 0.0, 0.0, 1.0),
};

Mtx dato_0D008ED8 = {
    a_matriz_punto_fijo(0.0, 410.0, 0.0, 0.0,
                       0.999985, 0.000046, 0.0, 0.0,
                       0.999985, 0.000046, 0.999985, 546.000061,
                       0.999985, 0.000046, 0.0000153, 0.0),
};

ComportamientoCPU dato_0D008F18[] = {
    {     1,      3,      2},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D008F28[] = {
    {     1,      2,      6},
    {    11,     30,      1},
    {    55,     74,      1},
    {    90,    105,      1},
    {   139,    155,      1},
    {   177,    205,      1},
    {   225,    242,      1},
    {   292,    313,      1},
    {   352,    373,      1},
    {   452,    465,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D008F80[] = {
    {     1,      2,      6},
    {    10,     25,      1},
    {   190,    210,      1},
    {   270,    290,      1},
    {   410,    440,      1},
    {   540,    550,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D008FB8[] = {
    {     1,      2,      6},
    {    60,     80,      1},
    {   125,    140,      1},
    {   170,    185,      1},
    {   230,    240,      1},
    {   275,    285,      1},
    {   310,    320,      1},
    {   321,    349,      3},
    {   350,    360,      1},
    {   385,    415,      1},
    {   450,    468,      1},
    {   470,    477,      9},
    {   480,    485,     11},
    {   543,    546,      9},
    {   548,    550,     11},
    {   565,    568,      2},
    {   630,    631,      6},
    {   635,    640,     10},
    {   645,    655,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D009058[] = {
    {     1,      2,      6},
    {    15,     30,      1},
    {    55,     65,      1},
    {   125,    150,      1},
    {   265,    270,      1},
    {   275,    285,      1},
    {   305,    320,      2},
    {   330,    340,      1},
    {   375,    385,      1},
    {   547,    570,      1},
    {   582,    600,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D0090B8[] = {
    {     1,      2,      6},
    {    70,     94,      1},
    {   120,    133,      1},
    {   150,    170,      1},
    {   249,    265,      1},
    {   360,    395,      1},
    {   635,    655,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D0090F8[] = {
    {     1,      2,      6},
    {    15,     30,      1},
    {    41,     63,      1},
    {   115,    155,      1},
    {   200,    215,      1},
    {   240,    241,      9},
    {   264,    265,     10},
    {   270,    290,      1},
    {   345,    375,      1},
    {   493,    544,      1},
    {   583,    605,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D009158[] = {
    {     1,      2,      6},
    {    75,    100,      1},
    {   135,    150,      1},
    {   355,    390,      1},
    {   505,    525,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D009188[] = {
    {     1,      2,      6},
    {    65,     80,      1},
    {   165,    166,      9},
    {   180,    210,      1},
    {   220,    221,     10},
    {   250,    275,      1},
    {   360,    380,      1},
    {   440,    480,      1},
    {   600,    601,      9},
    {   689,    690,     10},
    {   695,    725,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D0091E8[] = {
    {     1,      2,      6},
    {   128,    275,      1},
    {   320,    345,      1},
    {   465,    565,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D009210[] = {
    {     1,      2,      6},
    {    75,    100,      1},
    {   175,    210,      1},
    {   275,    300,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D009238[] = {
    {     1,      2,      6},
    {   106,    188,      1},
    {   220,    386,      1},
    {   583,    765,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D009260[] = {
    {     1,      2,      6},
    {   245,    262,      1},
    {   585,    606,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D009280[] = {
    {     1,      2,      6},
    {     7,     38,      1},
    {    36,     54,      1},
    {   129,    150,      1},
    {   380,    410,      1},
    {   425,    445,      1},
    {   456,    500,      1},
    {   594,    625,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D0092C8[] = {
    {     1,      2,      6},
    {     4,      5,      9},
    {   129,    130,     10},
    {   555,    560,      9},
    {   827,    832,     10},
    {   810,    845,      1},
    {   910,    993,      1},
    {  1390,   1600,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D009310[] = {
    {     1,      2,      6},
    {    80,    120,      1},
    {   200,    250,      1},
    {   252,    253,      9},
    {   273,    295,      1},
    {   300,    315,      1},
    {   333,    384,      1},
    {   400,    401,     10},
    {   405,    435,      1},
    {   445,    475,      1},
    {   485,    525,      1},
    {   585,    615,      1},
    {   685,    735,      1},
    {   783,    820,      1},
    {   956,    984,      1},
    {  1005,   1050,      1},
    {  1063,   1088,      1},
    {  1130,   1131,      9},
    {  1169,   1170,     10},
    {  1195,   1240,      1},
    {  1262,   1300,      1},
    {    -1,     -1,      0},
};

ComportamientoCPU dato_0D0093C0[] = {
    {     1,      2,      6},
    {    20,     40,      1},
    {   190,    191,      9},
    {   259,    260,     10},
    {   315,    335,      1},
    {   353,    370,      1},
    {   398,    430,      1},
    {   458,    485,      1},
    {   510,    535,      1},
    {   580,    660,      3},
    {    -1,     -1,      0},
};

Vec4f cpu_curva_objetivo_rapidez[] = {
    #include "recursos/pistas/metadatos/cpu_curva_objetivo_rapidez.inc.c"
};

Vec4f cpu_normal_objetivo_rapidez[] = {
    #include "recursos/pistas/metadatos/cpu_normal_objetivo_rapidez.inc.c"
};

Vec4f dato_0D0096B8[] = {
    #include "recursos/pistas/metadatos/dato_0D0096B8.inc.c"
};

Vec4f cpu_apagado_pista_objetivo_rapidez[] = {
    #include "recursos/pistas/metadatos/cpu_apagado_pista_objetivo_rapidez.inc.c"
};

u8 velocimetro_textura_comun[] = {
	#include "recursos/comunes/texturas/velocimetro.i4.inc.c"
};

u8 comun_textura_velocimetro_aguja[] = {
	#include "recursos/comunes/texturas/aguja_velocimetro.i4.inc.c"
};

u16 comun_textura_hud_vuelta[] = {
	#include "recursos/comunes/texturas/vuelta_hud.rgba16.inc.c"
};

u16 hud_textura_comun_123[] = {
	#include "recursos/comunes/texturas/hud_123.rgba16.inc.c"
};

u16 comun_textura_hud_vuelta_tiempo[] = {
	#include "recursos/comunes/texturas/tiempo_vuelta_hud.rgba16.inc.c"
};

u16 comun_textura_hud_vuelta_1_en_3[] = {
	#include "recursos/comunes/texturas/vuelta_1_hud_en_3.rgba16.inc.c"
};

u16 comun_textura_hud_vuelta_2_en_3[] = {
	#include "recursos/comunes/texturas/vuelta_2_hud_en_3.rgba16.inc.c"
};

u16 comun_textura_hud_vuelta_3_en_3[] = {
	#include "recursos/comunes/texturas/vuelta_3_hud_en_3.rgba16.inc.c"
};

u16 comun_textura_hud_total_tiempo[] = {
	#include "recursos/comunes/texturas/tiempo_total_hud.rgba16.inc.c"
};

u16 comun_textura_hud_tiempo[] = {
	#include "recursos/comunes/texturas/tiempo_hud.rgba16.inc.c"
};

u16 comun_textura_hud_normal_digito[] = {
	#include "recursos/comunes/texturas/digito_normal_hud.rgba16.inc.c"
};

u8 comun_textura_hud_lugar[][4096] = {
	{
		#include "recursos/comunes/texturas/hud_1ro.i4.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_2do.i4.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_3ro.i4.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_4to.i4.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_5to.i4.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_6to.i4.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_7mo.i4.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_8vo.i4.inc.c"
	},
};
u8 dato_0D015258[][2048] = {
	{
		#include "recursos/comunes/texturas/primer_lugar.i4.inc.c"
	},
	{
		#include "recursos/comunes/texturas/segundo_lugar.i4.inc.c"
	},
	{
		#include "recursos/comunes/texturas/tercer_lugar.i4.inc.c"
	},
	{
		#include "recursos/comunes/texturas/cuarto_lugar.i4.inc.c"
	},
};
u16 comun_tlut_jugador_emblema[] = {
	#include "recursos/comunes/texturas/tlut_emblema_jugador.tlut.inc.c"
};

u8 comun_textura_jugador_emblema[][2048] = {
	{
		#include "recursos/comunes/texturas/emblema_1j_jugador.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/emblema_2j_jugador.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/emblema_3j_jugador.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/emblema_4j_jugador.ci8.inc.c"
	},
};
u16 comun_tlut_hud_tipo_c_puesto_fuente[] = {
	#include "recursos/comunes/texturas/tlut_hud_tipo_c_puesto_fuente.tlut.inc.c"
};

u8 comun_textura_hud_tipo_c_puesto_fuente[][256] = {
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_fuente_1.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_fuente_2.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_fuente_3.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_fuente_4.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_fuente_5.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_fuente_6.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_fuente_7.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_fuente_8.ci8.inc.c"
	},
};
u16 comun_tlut_hud_tipo_c_puesto_diminuto_fuente[] = {
	#include "recursos/comunes/texturas/tlut_hud_tipo_c_puesto_diminuto_fuente.tlut.inc.c"
};

u8 comun_textura_hud_tipo_c_puesto_diminuto_fuente[][64] = {
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_diminuto_fuente_0.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_diminuto_fuente_1.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_diminuto_fuente_2.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_diminuto_fuente_3.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_diminuto_fuente_4.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_diminuto_fuente_5.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_diminuto_fuente_6.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_diminuto_fuente_7.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_diminuto_fuente_8.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/hud_tipo_c_puesto_diminuto_fuente_9.ci8.inc.c"
	},
};
u8 comun_textura_personaje_retrato_borde[] = {
	#include "recursos/comunes/texturas/borde_retrato_personaje.ia4.inc.c"
};

u16 retrato_tlut_comun_mario[] = {
	#include "recursos/comunes/texturas/tlut_retrato_mario.tlut.inc.c"
};

u16 retrato_tlut_comun_luigi[] = {
	#include "recursos/comunes/texturas/tlut_retrato_luigi.tlut.inc.c"
};

u16 retrato_tlut_comun_peach[] = {
	#include "recursos/comunes/texturas/tlut_retrato_peach.tlut.inc.c"
};

u16 retrato_tlut_comun_toad[] = {
	#include "recursos/comunes/texturas/tlut_retrato_toad.tlut.inc.c"
};

u16 retrato_tlut_comun_yoshi[] = {
	#include "recursos/comunes/texturas/tlut_retrato_yoshi.tlut.inc.c"
};

u16 retrato_tlut_comun_donkey_kong[] = {
	#include "recursos/comunes/texturas/tlut_retrato_donkey_kong.tlut.inc.c"
};

u16 retrato_tlut_comun_wario[] = {
	#include "recursos/comunes/texturas/tlut_retrato_wario.tlut.inc.c"
};

u16 retrato_tlut_comun_bowser[] = {
	#include "recursos/comunes/texturas/tlut_retrato_bowser.tlut.inc.c"
};

u16 retrato_tlut_comun_kart_bomba_y_signo_pregunta[] = {
	#include "recursos/comunes/texturas/tlut_retrato_kart_bomba_y_signo_pregunta.tlut.inc.c"
};

u8 retrato_textura_comun_mario[] = {
	#include "recursos/comunes/texturas/retrato_mario.ci8.inc.c"
};

u8 retrato_textura_comun_luigi[] = {
	#include "recursos/comunes/texturas/retrato_luigi.ci8.inc.c"
};

u8 retrato_textura_comun_peach[] = {
	#include "recursos/comunes/texturas/retrato_peach.ci8.inc.c"
};

u8 retrato_textura_comun_toad[] = {
	#include "recursos/comunes/texturas/retrato_toad.ci8.inc.c"
};

u8 retrato_textura_comun_yoshi[] = {
	#include "recursos/comunes/texturas/retrato_yoshi.ci8.inc.c"
};

u8 retrato_textura_comun_donkey_kong[] = {
	#include "recursos/comunes/texturas/retrato_donkey_kong.ci8.inc.c"
};

u8 retrato_textura_comun_wario[] = {
	#include "recursos/comunes/texturas/retrato_wario.ci8.inc.c"
};

u8 retrato_textura_comun_bowser[] = {
	#include "recursos/comunes/texturas/retrato_bowser.ci8.inc.c"
};

u8 retrato_textura_comun_kart_bomba[] = {
	#include "recursos/comunes/texturas/retrato_kart_bomba.ci8.inc.c"
};

u8 retrato_textura_comun_signo_pregunta[] = {
	#include "recursos/comunes/texturas/retrato_signo_pregunta.ci8.inc.c"
};

u16 tlut_comun_ventana_item_ninguno[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_ninguno.tlut.inc.c"
};

u16 tlut_comun_ventana_item_banana[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_banana.tlut.inc.c"
};

u16 tlut_comun_ventana_item_grupo_banana[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_grupo_banana.tlut.inc.c"
};

u16 tlut_comun_ventana_item_hongo[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_hongo.tlut.inc.c"
};

u16 tlut_comun_ventana_item_doble_hongo[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_doble_hongo.tlut.inc.c"
};

u16 tlut_comun_ventana_item_triple_hongo[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_triple_hongo.tlut.inc.c"
};

u16 tlut_comun_ventana_item_super_hongo[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_super_hongo.tlut.inc.c"
};

u16 tlut_comun_ventana_item_caparazon_azul[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_caparazon_azul.tlut.inc.c"
};

u16 tlut_comun_ventana_item_boo[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_boo.tlut.inc.c"
};

u16 tlut_comun_ventana_item_caparazon_verde[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_caparazon_verde.tlut.inc.c"
};

u16 tlut_comun_ventana_item_triple_caparazon_verde[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_triple_caparazon_verde.tlut.inc.c"
};

u16 tlut_comun_ventana_item_caparazon_rojo[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_caparazon_rojo.tlut.inc.c"
};

u16 tlut_comun_ventana_item_triple_caparazon_rojo[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_triple_caparazon_rojo.tlut.inc.c"
};

u16 tlut_comun_ventana_item_estrella[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_estrella.tlut.inc.c"
};

u16 tlut_comun_ventana_item_rayo[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_rayo.tlut.inc.c"
};

u16 tlut_comun_ventana_item_caja_item_falsa[] = {
	#include "recursos/comunes/texturas/tlut_ventana_item_caja_item_falsa.tlut.inc.c"
};

u8 textura_comun_ventana_item_ninguno[] = {
	#include "recursos/comunes/texturas/ventana_item_ninguno.ci8.inc.c"
};

u8 textura_comun_ventana_item_banana[] = {
	#include "recursos/comunes/texturas/ventana_item_banana.ci8.inc.c"
};

u8 textura_comun_ventana_item_grupo_banana[] = {
	#include "recursos/comunes/texturas/ventana_item_grupo_banana.ci8.inc.c"
};

u8 textura_comun_ventana_item_hongo[] = {
	#include "recursos/comunes/texturas/ventana_item_hongo.ci8.inc.c"
};

u8 textura_comun_ventana_item_doble_hongo[] = {
	#include "recursos/comunes/texturas/ventana_item_doble_hongo.ci8.inc.c"
};

u8 textura_comun_ventana_item_triple_hongo[] = {
	#include "recursos/comunes/texturas/ventana_item_triple_hongo.ci8.inc.c"
};

u8 textura_comun_ventana_item_super_hongo[] = {
	#include "recursos/comunes/texturas/ventana_item_super_hongo.ci8.inc.c"
};

u8 textura_comun_ventana_item_caparazon_azul[] = {
	#include "recursos/comunes/texturas/ventana_item_caparazon_azul.ci8.inc.c"
};

u8 textura_comun_ventana_item_boo[] = {
	#include "recursos/comunes/texturas/ventana_item_boo.ci8.inc.c"
};

u8 textura_comun_ventana_item_caparazon_verde[] = {
	#include "recursos/comunes/texturas/ventana_item_caparazon_verde.ci8.inc.c"
};

u8 textura_comun_ventana_item_triple_caparazon_verde[] = {
	#include "recursos/comunes/texturas/ventana_item_triple_caparazon_verde.ci8.inc.c"
};

u8 textura_comun_ventana_item_caparazon_rojo[] = {
	#include "recursos/comunes/texturas/ventana_item_caparazon_rojo.ci8.inc.c"
};

u8 textura_comun_ventana_item_triple_caparazon_rojo[] = {
	#include "recursos/comunes/texturas/ventana_item_triple_caparazon_rojo.ci8.inc.c"
};

u8 textura_comun_ventana_item_estrella[] = {
	#include "recursos/comunes/texturas/ventana_item_estrella.ci8.inc.c"
};

u8 textura_comun_ventana_item_rayo[] = {
	#include "recursos/comunes/texturas/ventana_item_rayo.ci8.inc.c"
};

u8 textura_comun_ventana_item_caja_item_falsa[] = {
	#include "recursos/comunes/texturas/ventana_item_caja_item_falsa.ci8.inc.c"
};

u16 tlut_comun_lakitu_cuenta_regresiva[][256] = {
	{
		#include "recursos/comunes/texturas/tlut_lakitu_sin_luces.tlut.inc.c"
	},
	{
		#include "recursos/comunes/texturas/tlut_lakitu_luces_rojo.tlut.inc.c"
	},
	{
		#include "recursos/comunes/texturas/tlut_lakitu_luces_azul.tlut.inc.c"
	},
};
u16 tlut_comun_lakitu_bandera_a_cuadros[] = {
	#include "recursos/comunes/texturas/tlut_lakitu_bandera_a_cuadros.rgba16.inc.c"
};

u16 tlut_comun_lakitu_segundo_vuelta[] = {
	#include "recursos/comunes/texturas/tlut_lakitu_segundo_vuelta.rgba16.inc.c"
};

u16 tlut_comun_lakitu_vuelta_final[] = {
	#include "recursos/comunes/texturas/tlut_lakitu_vuelta_final.rgba16.inc.c"
};

u16 tlut_comun_lakitu_reversa[] = {
	#include "recursos/comunes/texturas/tlut_lakitu_reversa.rgba16.inc.c"
};

u16 tlut_comun_lakitu_pesca[] = {
	#include "recursos/comunes/texturas/tlut_lakitu_pesca.rgba16.inc.c"
};

u16 tlut_comun_semaforo[] = {
	#include "recursos/comunes/texturas/tlut_semaforo.tlut.inc.c"
};

u8 textura_comun_semaforo_01[] = {
	#include "recursos/comunes/texturas/semaforo_01.ci8.inc.c"
};

u8 textura_comun_semaforo_02[] = {
	#include "recursos/comunes/texturas/semaforo_02.ci8.inc.c"
};

u8 textura_comun_semaforo_03[] = {
	#include "recursos/comunes/texturas/semaforo_03.ci8.inc.c"
};

u8 textura_comun_semaforo_04[] = {
	#include "recursos/comunes/texturas/semaforo_04.ci8.inc.c"
};

u8 textura_comun_semaforo_05[] = {
	#include "recursos/comunes/texturas/semaforo_05.ci8.inc.c"
};

u8 textura_comun_semaforo_06[] = {
	#include "recursos/comunes/texturas/semaforo_06.ci8.inc.c"
};

u8 textura_comun_semaforo_07[] = {
	#include "recursos/comunes/texturas/semaforo_07.ci8.inc.c"
};

u8 textura_comun_semaforo_08[] = {
	#include "recursos/comunes/texturas/semaforo_08.ci8.inc.c"
};

u8 textura_comun_semaforo_09[] = {
	#include "recursos/comunes/texturas/semaforo_09.ci8.inc.c"
};

u8 textura_comun_semaforo_10[] = {
	#include "recursos/comunes/texturas/semaforo_10.ci8.inc.c"
};

u16 comun_textura_particula_hoja[] = {
	#include "recursos/comunes/texturas/hoja_particula.rgba16.inc.c"
};

u16 comun_textura_sin_uso_particula_hoja[] = {
	#include "recursos/comunes/texturas/hoja_particula_sin_uso.rgba16.inc.c"
};

u8 dato_0D0293D8[] = {
	#include "recursos/comunes/texturas/dato_0D0293D8.i4.inc.c"
};

u8 dato_0D029458[] = {
	#include "recursos/comunes/texturas/dato_0D029458.i8.inc.c"
};

u8 bomba_textura_comun[][1024] = {
	{
		#include "recursos/comunes/texturas/bomba_1.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/bomba_2.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/bomba_3.ci8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/bomba_4.ci8.inc.c"
	},
};
u16 bomba_tlut_comun[] = {
	#include "recursos/comunes/texturas/tlut_bomba.tlut.inc.c"
};

u16 dato_0D02AA58[] = {
	#include "recursos/comunes/texturas/dato_0D02AA58.rgba16.inc.c"
};

u8 comun_textura_particula_chispa[][1024] = {
	{
		#include "recursos/comunes/texturas/chispa_particula_1.i8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/chispa_particula_2.i8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/chispa_particula_3.i8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/chispa_particula_4.i8.inc.c"
	},
};
u8 comun_textura_particula_humo[][1024] = {
	{
		#include "recursos/comunes/texturas/humo_particula_1.i8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/humo_particula_2.i8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/humo_particula_3.i8.inc.c"
	},
	{
		#include "recursos/comunes/texturas/humo_particula_4.i8.inc.c"
	},
};
u16 minimapa_textura_comun_linea_meta[] = {
	#include "recursos/comunes/texturas/minimapa_linea_meta.rgba16.inc.c"
};

u16 comun_textura_minimapa_kart_mario[] = {
	#include "recursos/comunes/texturas/kart_minimapa_mario.rgba16.inc.c"
};

u16 comun_textura_minimapa_kart_luigi[] = {
	#include "recursos/comunes/texturas/kart_minimapa_luigi.rgba16.inc.c"
};

u16 comun_textura_minimapa_kart_yoshi[] = {
	#include "recursos/comunes/texturas/kart_minimapa_yoshi.rgba16.inc.c"
};

u16 comun_textura_minimapa_kart_toad[] = {
	#include "recursos/comunes/texturas/kart_minimapa_toad.rgba16.inc.c"
};

u16 comun_textura_minimapa_kart_donkey_kong[] = {
	#include "recursos/comunes/texturas/kart_minimapa_donkey_kong.rgba16.inc.c"
};

u16 comun_textura_minimapa_kart_wario[] = {
	#include "recursos/comunes/texturas/kart_minimapa_wario.rgba16.inc.c"
};

u16 comun_textura_minimapa_kart_peach[] = {
	#include "recursos/comunes/texturas/kart_minimapa_peach.rgba16.inc.c"
};

u16 comun_textura_minimapa_kart_bowser[] = {
	#include "recursos/comunes/texturas/kart_minimapa_bowser.rgba16.inc.c"
};

u16 comun_textura_minimapa_progreso_punto[] = {
	#include "recursos/comunes/texturas/punto_progreso_minimapa.rgba16.inc.c"
};
