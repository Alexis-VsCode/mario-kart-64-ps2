/* Pruebas del despacho de texturas de menu: TKMK00 o MIO0 segun la firma.
 *
 *   prueba_textura_menu <referencias_tkmk00.txt> <carpeta de las .tkmk00>
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sistema/descompresion_mio0.h"
#include "sistema/descompresion_textura_menu.h"
#include "sistema/utilidades.h"

#define GUARDA 16
#define RELLENO 0xA5

static int s_fails, s_checks;

#define COMPROBACION(cond, ...)                                                                                        \
    do {                                                                                                               \
        s_checks++;                                                                                                    \
        if (!(cond)) {                                                                                                 \
            s_fails++;                                                                                                 \
            printf("FALLO %s:%d: ", __FILE__, __LINE__);                                                               \
            printf(__VA_ARGS__);                                                                                       \
            printf("\n");                                                                                              \
        }                                                                                                              \
    } while (0)

static uint32_t rotar(uint32_t x, int n)
{
    return (x << n) | (x >> (32 - n));
}

/* SHA-1 (FIPS 180-1) en hexadecimal */
static void sha1_hex(const uint8_t *datos, size_t n, char salida[41])
{
    uint32_t h[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
    size_t total = ((n + 8) / 64 + 1) * 64;
    uint8_t *m = calloc(1, total);
    uint64_t bits = (uint64_t) n * 8;
    size_t bloque;
    int i;

    memcpy(m, datos, n);
    m[n] = 0x80;
    for (i = 0; i < 8; i++) {
        m[total - 1 - i] = (uint8_t) (bits >> (8 * i));
    }
    for (bloque = 0; bloque < total; bloque += 64) {
        uint32_t w[80], a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f, k, t;

        for (i = 0; i < 16; i++) {
            const uint8_t *p = &m[bloque + 4 * i];
            w[i] = ((uint32_t) p[0] << 24) | ((uint32_t) p[1] << 16) | ((uint32_t) p[2] << 8) | p[3];
        }
        for (i = 16; i < 80; i++) {
            w[i] = rotar(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }
        for (i = 0; i < 80; i++) {
            if (i < 20) {
                f = (b & c) | (~b & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
            t = rotar(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = rotar(b, 30);
            b = a;
            a = t;
        }
        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
    }
    free(m);
    for (i = 0; i < 5; i++) {
        sprintf(salida + 8 * i, "%08x", (unsigned) h[i]);
    }
}

static int guarda_intacta(const uint8_t *p)
{
    int i;

    for (i = 0; i < GUARDA; i++) {
        if (p[i] != RELLENO) {
            return 0;
        }
    }
    return 1;
}

/* Una textura: TKMK00 por el despacho contra su SHA-1, y la misma salida
   guardada como MIO0 tiene que volver igual con cualquier alfa */
static void probar_textura(const char *ruta, uint32_t ancho, uint32_t alto, int32_t alfa, const char *sha1)
{
    uint8_t *datos = NULL;
    long leidos = leer_archivo(ruta, &datos);
    uint32_t tamanio = ancho * alto * 2;
    uint8_t *tmp = malloc(ancho * alto);
    uint8_t *rgba = malloc(tamanio + GUARDA);
    uint8_t *otra = malloc(tamanio + GUARDA);
    uint8_t *mio0 = malloc(2 * tamanio + tamanio / 8 + 64);
    char hex[41];
    int longitud_mio0;
    int i;

    COMPROBACION(leidos > 0, "%s: no se pudo leer", ruta);
    if (leidos <= 0) {
        return;
    }
    COMPROBACION(tamanio_textura_menu(datos) == tamanio, "%s: tamanio TKMK00 %u, se esperaba %u", ruta,
                 (unsigned) tamanio_textura_menu(datos), (unsigned) tamanio);
    memset(rgba, RELLENO, tamanio + GUARDA);
    COMPROBACION(decodificar_textura_menu(datos, tmp, rgba, alfa) == TEXTURA_MENU_OK, "%s: TKMK00 no decodifica", ruta);
    sha1_hex(rgba, tamanio, hex);
    COMPROBACION(strcmp(hex, sha1) == 0, "%s: SHA-1 %s, la referencia es %s", ruta, hex, sha1);
    COMPROBACION(guarda_intacta(rgba + tamanio), "%s: TKMK00 escribe fuera de w*h*2", ruta);

    longitud_mio0 = codificar_mio0(rgba, tamanio, mio0);
    COMPROBACION(tamanio_textura_menu(mio0) == tamanio, "%s: tamanio MIO0 %u, se esperaba %u", ruta,
                 (unsigned) tamanio_textura_menu(mio0), (unsigned) tamanio);
    for (i = 0; i < 2; i++) {
        int32_t otro_alfa = i ? 0xBE : 0x01;

        memset(otra, RELLENO, tamanio + GUARDA);
        COMPROBACION(decodificar_textura_menu(mio0, tmp, otra, otro_alfa) == TEXTURA_MENU_OK,
                     "%s: MIO0 (%d bytes) no decodifica", ruta, longitud_mio0);
        COMPROBACION(memcmp(otra, rgba, tamanio) == 0, "%s: MIO0 con alfa 0x%02X no da los mismos bytes", ruta,
                     (unsigned) otro_alfa);
        COMPROBACION(guarda_intacta(otra + tamanio), "%s: MIO0 escribe fuera de w*h*2", ruta);
    }
    free(datos);
    free(tmp);
    free(rgba);
    free(otra);
    free(mio0);
}

static void probar_firma_desconocida(void)
{
    uint8_t datos[64] = "TKMK01";
    uint8_t salida[64];
    uint8_t tmp[64];

    datos[9] = 4;
    datos[11] = 4;
    memset(salida, RELLENO, sizeof(salida));
    COMPROBACION(tamanio_textura_menu(datos) == 0, "TKMK01 tiene que dar tamanio 0");
    COMPROBACION(decodificar_textura_menu(datos, tmp, salida, 1) == TEXTURA_MENU_FIRMA_DESCONOCIDA,
                 "TKMK01 tiene que dar error");
    memcpy(datos, "MIO1", 4);
    COMPROBACION(tamanio_textura_menu(datos) == 0, "MIO1 tiene que dar tamanio 0");
    COMPROBACION(decodificar_textura_menu(datos, tmp, salida, 1) == TEXTURA_MENU_FIRMA_DESCONOCIDA,
                 "MIO1 tiene que dar error");
    COMPROBACION(guarda_intacta(salida), "una firma desconocida no escribe la salida");
}

int main(int argc, char **argv)
{
    char linea[256], nombre[128], sha1[41], ruta[512], hex[41];
    unsigned ancho, alto;
    long alfa;
    int texturas = 0;
    FILE *f;

    if (argc != 3) {
        fprintf(stderr, "uso: %s <referencias_tkmk00.txt> <carpeta>\n", argv[0]);
        return 2;
    }
    sha1_hex((const uint8_t *) "abc", 3, hex);
    COMPROBACION(strcmp(hex, "a9993e364706816aba3e25717850c26c9cd0d89d") == 0, "SHA-1 de \"abc\": %s", hex);

    f = fopen(argv[1], "r");
    COMPROBACION(f != NULL, "no se pudo abrir %s", argv[1]);
    while (f != NULL && fgets(linea, sizeof(linea), f) != NULL) {
        char alfa_texto[16];

        if (linea[0] == '#' || linea[0] == '\n') {
            continue;
        }
        if (sscanf(linea, "%127s %u %u %15s %40s", nombre, &ancho, &alto, alfa_texto, sha1) != 5) {
            COMPROBACION(0, "linea mal formada: %s", linea);
            continue;
        }
        alfa = strtol(alfa_texto, NULL, 0);
        snprintf(ruta, sizeof(ruta), "%s/%s", argv[2], nombre);
        probar_textura(ruta, ancho, alto, (int32_t) alfa, sha1);
        texturas++;
    }
    if (f != NULL) {
        fclose(f);
    }
    COMPROBACION(texturas == 63, "se esperaban 63 texturas TKMK00, hay %d", texturas);
    probar_firma_desconocida();

    printf("%d comprobaciones, %d fallos\n", s_checks, s_fails);
    return s_fails != 0;
}
