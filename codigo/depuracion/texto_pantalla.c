#include <string.h>

#include <gsKit.h>

#include "graficos/sintetizador_gs.h"
#include "depuracion/fuente_5x7.h"
#include "depuracion/texto_pantalla.h"

void texto_limpiar(TexturaTexto *tex)
{
    memset(tex->pixeles, 0, sizeof(tex->pixeles));
    tex->pendiente_subir = 1;
}

void texto_escribir_linea(TexturaTexto *tex, int linea, const char *cadena, u32 color)
{
    if (linea < 0 || linea >= TEXTO_LINEAS) {
        return;
    }
    memset(&tex->pixeles[linea * TEXTO_ALTO_LINEA * TEXTO_ANCHO_TEXTURA], 0,
           TEXTO_ALTO_LINEA * TEXTO_ANCHO_TEXTURA * sizeof(u32));
    /* La primera fila de la linea queda para el signo de encima de la letra */
    escribir_linea_5x7((uint32_t *) tex->pixeles, TEXTO_ANCHO_TEXTURA, 1, linea * TEXTO_ALTO_LINEA + 1, cadena,
                       TEXTO_COLUMNAS, color);
    tex->pendiente_subir = 1;
}

void texto_dibujar(TexturaTexto *tex, float x, float y, int lineas)
{
    EstadoGs estado;
    VerticeGs a, b;
    float alto;

    if (lineas <= 0) {
        return;
    }
    if (lineas > TEXTO_LINEAS) {
        lineas = TEXTO_LINEAS;
    }
    if (tex->pendiente_subir) {
        gs_subir_textura(tex->vram / 256, TEXTO_ANCHO_TEXTURA / 64, tex->pixeles, TEXTO_ANCHO_TEXTURA,
                          TEXTO_ALTO_TEXTURA);
        tex->pendiente_subir = 0;
    }
    alto = (float) (lineas * TEXTO_ALTO_LINEA);

    memset(&estado, 0, sizeof(estado));
    estado.zbuf = gs_valor_zbuf(0);
    estado.tijera = GS_SETREG_SCISSOR(0, GS_ANCHO - 1, 0, GS_ALTO - 1);
    memset(&a, 0, sizeof(a));
    a.niebla = 0xFF;
    b = a;

    estado.prueba = GS_SETREG_TEST(0, 0, 0, 0, 0, 0, 1, 1);
    estado.alpha = GS_SETREG_ALPHA(0, 1, 0, 1, 0);
    estado.prim = 1 << 6;
    estado.texturizado = 0;
    gs_aplicar_estado(&estado);
    a.x = x - 4.0f;
    a.y = y - 2.0f;
    a.a = 0x60;
    b.x = x + TEXTO_ANCHO_TEXTURA * 2.0f + 4.0f;
    b.y = y + alto * 2.0f + 2.0f;
    b.a = 0x60;
    gs_sprite(&a, &b);

    /* Texto: los texels transparentes no pasan la prueba de alfa. */
    estado.prueba = GS_SETREG_TEST(1, 5, 0x40, 0, 0, 0, 1, 1);
    estado.alpha = 0;
    estado.tex0 = GS_SETREG_TEX0(tex->vram / 256, TEXTO_ANCHO_TEXTURA / 64, GS_PSM_CT32, 8, TEXTO_ALTO_GS_LOG2, 1, 1,
                                 0, 0, 0, 0, 0);
    estado.tex1 = GS_SETREG_TEX1(1, 0, 0, 0, 0, 0, 0); /* sin filtro: la escala es entera */
    estado.clamp = GS_SETREG_CLAMP(1, 1, 0, 0, 0, 0);
    estado.prim = 1 << 4; /* TME, coordenadas ST */
    estado.texturizado = 1;
    gs_aplicar_estado(&estado);
    a.x = x;
    a.y = y;
    a.s = 0.0f;
    a.t = 0.0f;
    a.q = 1.0f;
    a.a = 0x80;
    b.x = x + TEXTO_ANCHO_TEXTURA * 2.0f;
    b.y = y + alto * 2.0f;
    b.s = 1.0f;
    b.t = alto / (float) (1 << TEXTO_ALTO_GS_LOG2);
    b.q = 1.0f;
    b.a = 0x80;
    gs_sprite(&a, &b);
}
