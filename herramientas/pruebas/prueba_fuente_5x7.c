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

// Pixeles con tinta en las filas y_desde..y_hasta
static int pixeles_en_filas(int y_desde, int y_hasta) {
    int x, y, n = 0;
    for (y = y_desde; y <= y_hasta; y++) {
        for (x = 0; x < ANCHO; x++) {
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

// Caracteres del espanol en UTF-8 y como los deja en EUC-JP el conversor del
// build, en mayuscula y en minuscula
typedef struct {
    const char* utf8[2];
    const char* euc[2];
    char base;
} CasoEs;

static const CasoEs letras_con_tilde[] = {
    { { "\xc3\x81", "\xc3\xa1" }, { "\x8f\xaa\xa1", "\x8f\xab\xa1" }, 'A' },
    { { "\xc3\x89", "\xc3\xa9" }, { "\x8f\xaa\xb1", "\x8f\xab\xb1" }, 'E' },
    { { "\xc3\x8d", "\xc3\xad" }, { "\x8f\xaa\xbf", "\x8f\xab\xbf" }, 'I' },
    { { "\xc3\x93", "\xc3\xb3" }, { "\x8f\xaa\xd1", "\x8f\xab\xd1" }, 'O' },
    { { "\xc3\x9a", "\xc3\xba" }, { "\x8f\xaa\xe2", "\x8f\xab\xe2" }, 'U' },
};
static const CasoEs u_dieresis = { { "\xc3\x9c", "\xc3\xbc" }, { "\x8f\xaa\xe4", "\x8f\xab\xe4" }, 'U' };
static const CasoEs enie = { { "\xc3\x91", "\xc3\xb1" }, { "\x8f\xaa\xd0", "\x8f\xab\xd0" }, 'N' };

// Celda de caso en sus cuatro formas; 0 si alguna difiere o no ocupa lo suyo
static int celda_es(const CasoEs* caso, unsigned char filas[FUENTE_5X7_FILAS]) {
    unsigned char otra[FUENTE_5X7_FILAS];
    int i;
    if (glifo_5x7(caso->utf8[0], filas) != 2) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        if (glifo_5x7(caso->utf8[i], otra) != 2 || memcmp(filas, otra, sizeof(otra)) != 0 ||
            glifo_5x7(caso->euc[i], otra) != 3 || memcmp(filas, otra, sizeof(otra)) != 0) {
            return 0;
        }
    }
    return 1;
}

// Filas 1-7 iguales a las de la letra c
static int misma_letra(const unsigned char filas[FUENTE_5X7_FILAS], char c) {
    unsigned char base[FUENTE_5X7_FILAS];
    char s[2] = { c, 0 };
    glifo_5x7(s, base);
    return memcmp(&filas[1], &base[1], FUENTE_5X7_FILAS - 1) == 0;
}

static unsigned char espejo(unsigned char fila) {
    unsigned char r = 0;
    int col;
    for (col = 0; col < FUENTE_5X7_ANCHO; col++) {
        if (fila & (1 << col)) {
            r |= 0x10 >> col;
        }
    }
    return r;
}

// La letra de c girada 180 grados (filas 1-7), sin signo
static void girada(const char* c, unsigned char filas[FUENTE_5X7_FILAS]) {
    unsigned char original[FUENTE_5X7_FILAS];
    int fila;
    glifo_5x7(c, original);
    filas[0] = 0;
    for (fila = 1; fila < FUENTE_5X7_FILAS; fila++) {
        filas[fila] = espejo(original[FUENTE_5X7_FILAS - fila]);
    }
}

static void probar_espanol(void) {
    unsigned char filas[FUENTE_5X7_FILAS], otra[FUENTE_5X7_FILAS], tilde = 0;
    int i;

    for (i = 0; i < (int) (sizeof(letras_con_tilde) / sizeof(letras_con_tilde[0])); i++) {
        const CasoEs* caso = &letras_con_tilde[i];
        COMPROBACION(celda_es(caso, filas), "%c con tilde: bytes o minuscula", caso->base);
        COMPROBACION(misma_letra(filas, caso->base) && filas[0] != 0, "%c con tilde = %c + marca", caso->base,
                     caso->base);
        COMPROBACION(i == 0 || filas[0] == tilde, "%c: la tilde es la misma en todas", caso->base);
        tilde = filas[0];
    }
    COMPROBACION(celda_es(&u_dieresis, filas), "U con dieresis: bytes o minuscula");
    COMPROBACION(misma_letra(filas, 'U') && filas[0] != 0 && filas[0] != tilde, "U con dieresis = U + dieresis");
    COMPROBACION(celda_es(&enie, filas), "enie: bytes o minuscula");
    glifo_5x7("N", otra);
    COMPROBACION(filas[0] != 0 && memcmp(filas, otra, sizeof(otra)) != 0, "la enie lleva virgulilla");

    girada("!", otra);
    COMPROBACION(glifo_5x7("\xc2\xa1", filas) == 2 && memcmp(filas, otra, sizeof(otra)) == 0, "apertura de !");
    COMPROBACION(glifo_5x7("\x8f\xa2\xc2", filas) == 3 && memcmp(filas, otra, sizeof(otra)) == 0, "apertura de ! (EUC)");
    girada("?", otra);
    COMPROBACION(glifo_5x7("\xc2\xbf", filas) == 2 && memcmp(filas, otra, sizeof(otra)) == 0, "apertura de ?");
    COMPROBACION(glifo_5x7("\x8f\xa2\xc4", filas) == 3 && memcmp(filas, otra, sizeof(otra)) == 0, "apertura de ? (EUC)");

    COMPROBACION(glifo_5x7("\xc2\xba", filas) == 2 && glifo_5x7("\x8f\xa2\xeb", otra) == 3 &&
                     memcmp(filas, otra, sizeof(otra)) == 0 && !misma_letra(filas, 'O') && !misma_letra(filas, ' '),
                 "ordinal masculino");
    COMPROBACION(glifo_5x7("\xc2\xaa", otra) == 2 && memcmp(filas, otra, sizeof(otra)) != 0 &&
                     !misma_letra(otra, 'A') && !misma_letra(otra, ' '),
                 "ordinal femenino");
}

static void probar_columnas(void) {
    static const char* const anio[] = { "A\xc3\x91O", "a\xc3\xb1o", "A\x8f\xaa\xd0O", "a\x8f\xab\xd0o" };
    unsigned char filas[FUENTE_5X7_FILAS], esperado[FUENTE_5X7_FILAS];
    int i, n;

    for (i = 0; i < 4; i++) {
        n = escribir(anio[i], 10);
        leer_celda(1, filas);
        glifo_5x7("\xc3\x91", esperado);
        COMPROBACION(n == 3 && memcmp(filas, esperado, sizeof(filas)) == 0, "caso %d: la enie en la columna 1", i);
        leer_celda(2, filas);
        glifo_5x7("O", esperado);
        COMPROBACION(memcmp(filas, esperado, sizeof(filas)) == 0 && pixeles_desde(1 + 3 * FUENTE_5X7_AVANCE) == 0,
                     "caso %d: la palabra de 3 letras ocupa 3 columnas", i);
    }
    // El signo va en la fila libre de encima de la letra, no en la linea anterior
    escribir("\xc3\x81", 10);
    COMPROBACION(pixeles_en_filas(Y0 - 1, Y0 - 1) > 0 && pixeles_en_filas(0, Y0 - 2) == 0, "la tilde va en y0-1");
    // Secuencias cortadas al final de la cadena: un byte y celda vacia
    COMPROBACION(glifo_5x7("\xc3", filas) == 1 && misma_letra(filas, ' ') && filas[0] == 0, "C3 al final");
    COMPROBACION(glifo_5x7("\x8f\xaa", filas) == 1 && misma_letra(filas, ' ') && filas[0] == 0, "8F AA al final");
    COMPROBACION(escribir("A\xc3", 10) == 2, "A + C3 cortado: 2 columnas");
}

int main(void) {
    probar_ascii();
    probar_linea();
    probar_espanol();
    probar_columnas();
    printf("%d comprobaciones, %d fallos\n", s_comprobaciones, s_fallos);
    return s_fallos != 0;
}
