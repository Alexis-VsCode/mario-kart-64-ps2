#include <ultra64.h>
#include <juego/macros.h>
#include <PR/gu.h>
#include "sistema/bucle_principal.h"
#include <juego/mk64.h>

extern s16 dato_800E43A8;
extern Mtx dato_0D008E98;

SIN_USO void gfx_func_80040D00(void) {
    dato_800E43A8 = 0;

    gDPSetCombineMode(display_list_cabeza++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(display_list_cabeza++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPClearGeometryMode(display_list_cabeza++, G_LIGHTING);
    guOrtho(&gfx_pool->pantalla_mtx, 0.0f, ANCHO_PANTALLA, 0.0f, ALTURA_PANTALLA, -1.0f, 1.0f, 1.0f);
    gSPPerspNormalize(display_list_cabeza++, 0xFFFF);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(gfx_pool), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&dato_0D008E98), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}
