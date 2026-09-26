#ifndef DATOS_TEXTURAS_H
#define DATOS_TEXTURAS_H

#include <PR/ultratypes.h>

typedef struct {
     s16 type;
     u64* textura_datos;
     u16 width;
     u16 height;
     u16 d_x;
     u16 d_y;
     u16 size;
     s16 unused2;
} TexturaMenu;

typedef struct {
     TexturaMenu* textura_mk64;
     s32 longitud_frame;
} AnimacionMk;

#include "datos/texturas/segmento_2.h"

#include "datos/texturas/menus_y_personajes.h"

#endif
