// Fuente 5x7 del panel de rendimiento (fuente_5x7.c) en el PC
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "depuracion/fuente_5x7.h"

static int s_fallos, s_comprobaciones;

#define COMPROBACION(cond, ...)                                                                                        \
    do {                                                                                                               \
        s_comprobaciones++;                                                                                            \
        if (!(cond)) {                                                                                                 \
            s_fallos++;                                                                                                \
            printf("FALLO %s:%d: ", __FILE__, __LINE__);                                                               \
            printf(__VA_ARGS__);                                                                                       \
            printf("\n");                                                                                              \
        }                                                                                                              \
    } while (0)

// FNV-1a de (bytes consumidos, 8 filas) de cada byte suelto 1..255, sacado
// de texto_pantalla.c antes de separar la fuente
#define HUELLA_ASCII 0x35BCAECCu

static void probar_ascii(void) {
    static const unsigned char letra_a[FUENTE_5X7_FILAS] = { 0x00, 0x0E, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11 };
    unsigned char filas[FUENTE_5X7_FILAS], otras[FUENTE_5X7_FILAS];
    unsigned huella = 2166136261u;
    int b, fila;

    for (b = 1; b < 256; b++) {
        char s[2] = { (char) b, 0 };
        int bytes = glifo_5x7(s, filas);
        huella = (huella ^ (unsigned) bytes) * 16777619u;
        for (fila = 0; fila < FUENTE_5X7_FILAS; fila++) {
            huella = (huella ^ filas[fila]) * 16777619u;
        }
    }
    COMPROBACION(huella == HUELLA_ASCII, "la fuente ASCII cambio (0x%08X)", huella);
    COMPROBACION(glifo_5x7("A", filas) == 1 && memcmp(filas, letra_a, sizeof(filas)) == 0, "celda de 'A'");
    glifo_5x7("z", otras);
    glifo_5x7("Z", filas);
    COMPROBACION(memcmp(filas, otras, sizeof(filas)) == 0, "minuscula = mayuscula");
}

#define ANCHO 128
#define ALTO 16
#define Y0 9 // la banda de la linea empieza en Y0 - 1
static uint32_t pixeles[ANCHO * ALTO];

// Lee de pixeles la celda de la columna n
static void leer_celda(int n, unsigned char filas[FUENTE_5X7_FILAS]) {
    int fila, col;
    for (fila = 0; fila < FUENTE_5X7_FILAS; fila++) {
        filas[fila] = 0;
        for (col = 0; col < FUENTE_5X7_ANCHO; col++) {
            if (pixeles[(Y0 - 1 + fila) * ANCHO + 1 + n * FUENTE_5X7_AVANCE + col] != 0) {
                filas[fila] |= 0x10 >> col;
            }
        }
    }
}

// Pixeles con tinta de la columna de pixeles x0 en adelante
static int pixeles_desde(int x0) {
    int x, y, n = 0;
    for (y = 0; y < ALTO; y++) {
        for (x = x0; x < ANCHO; x++) {
            n += pixeles[y * ANCHO + x] != 0;
        }
    }
    return n;
}

static int escribir(const char* cadena, int columnas_max) {
    memset(pixeles, 0, sizeof(pixeles));
    return escribir_linea_5x7(pixeles, ANCHO, 1, Y0, cadena, columnas_max, 0x80FFFFFFu);
}

static void probar_linea(void) {
    unsigned char filas[FUENTE_5X7_FILAS], esperado[FUENTE_5X7_FILAS];
    int n;

    n = escribir("AB", 10);
    leer_celda(1, filas);
    glifo_5x7("B", esperado);
    COMPROBACION(n == 2 && memcmp(filas, esperado, sizeof(filas)) == 0, "'B' en la segunda columna (%d)", n);
    n = escribir("ABCDEFGHIJ", 3);
    COMPROBACION(n == 3 && pixeles_desde(1 + 3 * FUENTE_5X7_AVANCE) == 0, "se corta en 3 columnas (%d)", n);
}

int main(void) {
    probar_ascii();
    probar_linea();
    printf("%d comprobaciones, %d fallos\n", s_comprobaciones, s_fallos);
    return s_fallos != 0;
}
