#ifndef DEPURACION_TEXTO_PANTALLA_H
#define DEPURACION_TEXTO_PANTALLA_H

#include <tamtypes.h>

#include "depuracion/fuente_5x7.h"

#define TEXTO_ANCHO_TEXTURA 256
/* 96 filas */
#define TEXTO_ALTO_TEXTURA  96
#define TEXTO_ALTO_GS_LOG2  7
#define TEXTO_ANCHO_LETRA   FUENTE_5X7_AVANCE
#define TEXTO_ALTO_LINEA    FUENTE_5X7_FILAS /* fila del signo + 7 de letra */
#define TEXTO_COLUMNAS      (TEXTO_ANCHO_TEXTURA / TEXTO_ANCHO_LETRA)
#define TEXTO_LINEAS        (TEXTO_ALTO_TEXTURA / TEXTO_ALTO_LINEA)

/* Colores CT32 (A en el byte alto */
#define TEXTO_BLANCO   0x80FFFFFFu
#define TEXTO_VERDE    0x8040FF40u
#define TEXTO_AMARILLO 0x8000E0FFu
#define TEXTO_ROJO     0x804040FFu

typedef struct {
    u32 pixeles[TEXTO_ANCHO_TEXTURA * TEXTO_ALTO_TEXTURA] __attribute__((aligned(16)));
    u32 vram;          /* direccion en bytes de la copia en VRAM */
    int pendiente_subir;
} TexturaTexto;

void texto_limpiar(TexturaTexto *tex);
/* Escribe una linea, un caracter por columna (se corta en TEXTO_COLUMNAS) */
void texto_escribir_linea(TexturaTexto *tex, int linea, const char *cadena, u32 color);
void texto_dibujar(TexturaTexto *tex, float x, float y, int lineas);

#endif
