#ifndef GRAFICOS_REGISTROS_VIDEO_H
#define GRAFICOS_REGISTROS_VIDEO_H

#include "sistema/opciones_port.h"

// Valores de PMODE, DISPFB2 y DISPLAY del PCRTC según las opciones de imagen
// (CC-20, CC-21). Función pura: el GS la llama en el retrazo y la prueba del PC
// la comprueba campo a campo.

// DISPLAY tal como lo deja gsKit_init_screen: dx en VCK, dw en VCK y dh en
// líneas, sin restar 1
typedef struct BaseVideo {
    u32 dx, dy, magh, magv, dw, dh;
} BaseVideo;

typedef struct RegistrosVideo {
    u64 pmode;
    u64 dispfb2_extra; // bits que se suman a DISPFB2 (DBY)
    u64 display;       // igual en DISPLAY1 y DISPLAY2
} RegistrosVideo;

#define VCK_POR_PASO_X 8   // un paso de posición horizontal
#define LINEAS_POR_PASO_Y 2 // en entrelazado DY tiene que ser par

// PMODE: EN1 b0, EN2 b1, CRTMD b2-4 (siempre 1), MMOD b5, AMOD b6, ALP b8-15.
// gsKit solo enciende el circuito 2; con antiparpadeo se encienden los dos,
// el 2 una línea más abajo (DBY), y se mezclan al 50 % con ALP=0x80.
#define PMODE_GSKIT 0x8046
#define PMODE_ANTIPARPADEO 0x8027
#define DISPFB_DBY_BIT 43

static inline u32 video_recortar(s32 v, s32 max)
{
    if (v < 0) {
        return 0;
    }
    return v > max ? (u32) max : (u32) v;
}

static inline void calcular_registros_video(const BaseVideo *base, const OpcionesPort *o, RegistrosVideo *r)
{
    u32 magh = base->magh;
    u32 dw = base->dw;
    s32 dx = (s32) base->dx;
    s32 dy;

    // CON_BANDAS: cada píxel ocupa 3/4 de los VCK de antes y la imagen se
    // centra; el negro de fuera del área de DISPLAY hace de bandas
    if (o->formato == FORMATO_CON_BANDAS) {
        magh = (magh + 1) * 3 / 4 - 1;
        dw = dw * 3 / 4;
        dx += (s32) (base->dw - dw) / 2;
    }
    dx += opciones_recortar(o->desplaz_x, DESPLAZ_X_MAX) * VCK_POR_PASO_X;
    dy = (s32) base->dy + opciones_recortar(o->desplaz_y, DESPLAZ_Y_MAX) * LINEAS_POR_PASO_Y;

    r->pmode = o->antiparpadeo ? PMODE_ANTIPARPADEO : PMODE_GSKIT;
    r->dispfb2_extra = o->antiparpadeo ? 1ULL << DISPFB_DBY_BIT : 0;
    r->display = (u64) video_recortar(dx, 0xFFF) | ((u64) (video_recortar(dy, 0x7FF) & ~1u) << 12) |
                 ((u64) magh << 23) | ((u64) base->magv << 27) | ((u64) (dw - 1) << 32) |
                 ((u64) (base->dh - 1) << 44);
}

#endif
