#ifndef DEPURACION_FUENTE_5X7_H
#define DEPURACION_FUENTE_5X7_H

#include <stdint.h>

/* Fuente del panel de rendimiento. Cada celda tiene 8 filas: la fila 0 es
   para el signo que va encima de la letra y las filas 1-7, para la letra.
   En cada fila, el bit 4 es la columna de la izquierda. */
#define FUENTE_5X7_FILAS  8
#define FUENTE_5X7_ANCHO  5
#define FUENTE_5X7_AVANCE 6 /* 5 de glifo + 1 de separacion */

/* Deja en filas la celda del caracter de c y devuelve los bytes que ocupa:
   1 en ASCII y 2 o 3 en los caracteres del espanol (UTF-8 o EUC-JP, ver
   caracteres_es.h). Las minusculas dan la mayuscula; lo que no esta en la
   fuente, la celda vacia. */
int glifo_5x7(const char *c, unsigned char filas[FUENTE_5X7_FILAS]);

/* Escribe cadena en pixeles (ancho_textura por fila), un caracter por
   columna: la columna n empieza en x0 + n * FUENTE_5X7_AVANCE, la letra va
   en las filas y0..y0+6 y el signo en y0-1 (y0 >= 1). Se corta en
   columnas_max y devuelve las columnas escritas. */
int escribir_linea_5x7(uint32_t *pixeles, int ancho_textura, int x0, int y0, const char *cadena, int columnas_max,
                       uint32_t color);

#endif
