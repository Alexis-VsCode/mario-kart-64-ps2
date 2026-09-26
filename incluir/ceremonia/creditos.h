#ifndef CEREMONIA_CREDITOS_H
#define CEREMONIA_CREDITOS_H

#include <PR/ultratypes.h>

#define DERECHA_DESLIZAMIENTO 0
#define IZQUIERDA_DESLIZAMIENTO 1

typedef struct {
     f32 escalado_texto;
     s16 columna_inicial;
     s16 row;
     s16 extra_columna;
     s16 desconocido;
     s8 sentido_deslizamiento;
     s8 color_texto;
     s16 padding;
} InfoRenderCreditos;

extern InfoRenderCreditos creditos_texto_render_info[];
extern char* texto_creditos[];

#endif
