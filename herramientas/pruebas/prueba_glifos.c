// Decodificacion de glifos de la fuente del menu (glifos.inc.c) en el PC
#include <stdio.h>
#include <string.h>

#include <PR/ultratypes.h>
#include "juego/macros.h"
#include "sistema/caracteres_es.h"

s32 funcion_80092DF8(char*);
s32 funcion_80092E1C(char*);
s32 funcion_80092EE4(char*);
s32 car_a_indice_glifo(char*);
s32 obtener_ancho_cadena(char*);
s32 leer_glifo(char*, s32*);

const s16 ancho_pantalla_glifo[] = {
#define GLIFO(textura, ancho) ancho,
#include "menus/elementos_menu/lista_glifos.inc.c"
#undef GLIFO
};

#include "menus/elementos_menu/glifos.inc.c"

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

#define GLIFOS_EN_LISTA ((s32) CANTIDAD_ARREGLO(ancho_pantalla_glifo))

// FNV-1a de (indice, bytes) para toda entrada de dos bytes que no empieza por
// 0x8F, calculado con el codigo de la N64 antes de cambiar la regla de avance
#define HUELLA_N64 0x770E34E9u

static void probar_compatibilidad(void) {
    unsigned huella = 2166136261u;
    int c0, c1, fuera = 0;
    for (c0 = 1; c0 < 256; c0++) {
        if (c0 == 0x8F) {
            continue;
        }
        for (c1 = 0; c1 < 256; c1++) {
            char b[4] = { (char) c0, (char) c1, 0, 0 };
            s32 bytes;
            s32 indice = leer_glifo(b, &bytes);
            huella = (huella ^ (unsigned) (indice & 0xFFFF)) * 16777619u;
            huella = (huella ^ (unsigned) bytes) * 16777619u;
            if (indice >= GLIFOS_EN_LISTA) {
                fuera++;
            }
        }
    }
    COMPROBACION(huella == HUELLA_N64, "leer_glifo cambia algun indice o avance de la N64 (0x%08X)", huella);
    COMPROBACION(fuera == 0, "%d entradas dan un indice fuera de la lista de glifos", fuera);
}

static void probar_anchos(void) {
    COMPROBACION(obtener_ancho_cadena("MARIO") == 0x12 + 0xC + 0xC + 0x7 + 0xC, "ancho de MARIO: %d",
                 obtener_ancho_cadena("MARIO"));
    COMPROBACION(obtener_ancho_cadena("A B") == 0xC + 7 + 0xD, "el espacio mide 7");
    COMPROBACION(obtener_ancho_cadena("mario") == obtener_ancho_cadena("MARIO"), "minusculas = mayusculas");
}

// Cadenas tal como quedan en EUC-JP despues del conversor del build
#define E_A "\x8f\xaa\xa1"
#define E_O "\x8f\xaa\xd1"
#define E_ENIE "\x8f\xaa\xd0"
#define E_U_DIER "\x8f\xaa\xe4"
#define E_ABRE_EXCL "\x8f\xa2\xc2"
#define E_ABRE_INTER "\x8f\xa2\xc4"
#define E_ORD_O "\x8f\xa2\xeb"
#define E_O_MIN "\x8f\xab\xd1"

// Indices de glifo de una cadena y bytes recorridos; -9 marca el final
static s32 indices(char* cadena, s32* salida, s32* recorrido) {
    s32 n = 0, bytes;
    char* c = cadena;
    while (*c != 0 && n < 31) {
        salida[n++] = leer_glifo(c, &bytes);
        c += bytes;
    }
    salida[n] = -9;
    *recorrido = (s32) (c - cadena);
    return n;
}

static void probar_espanol(void) {
    s32 glifos[32], recorrido;
    s32 primero = 0xEC;

    indices("CAMPE" E_O "N", glifos, &recorrido);
    COMPROBACION(glifos[5] == primero + CAR_ES_O_AGUDA - 1 && glifos[6] == 13 && glifos[7] == -9, "CAMPEON: %d %d",
                 glifos[5], glifos[6]);
    COMPROBACION(recorrido == (s32) strlen("CAMPE" E_O "N"), "CAMPEON recorre %d bytes", recorrido);
    indices(E_ABRE_EXCL "GANADOR!", glifos, &recorrido);
    COMPROBACION(glifos[0] == primero + CAR_ES_ABRE_EXCLAMACION - 1 && glifos[8] == 0x1A, "exclamaciones");
    indices(E_ABRE_INTER "SEGURO?", glifos, &recorrido);
    COMPROBACION(glifos[0] == primero + CAR_ES_ABRE_INTERROGACION - 1, "apertura de interrogacion");
    indices("A" E_ENIE "O 1." E_ORD_O, glifos, &recorrido);
    COMPROBACION(glifos[1] == primero + CAR_ES_ENIE - 1 && glifos[5] == 0x1F && glifos[6] == primero + CAR_ES_ORDINAL_O - 1,
                 "ANO 1.o: %d %d %d", glifos[1], glifos[5], glifos[6]);
    indices("PING" E_U_DIER "INO", glifos, &recorrido);
    COMPROBACION(glifos[4] == primero + CAR_ES_U_DIERESIS - 1, "dieresis");
    indices("campe" E_O_MIN "n", glifos, &recorrido);
    COMPROBACION(glifos[5] == primero + CAR_ES_O_AGUDA - 1, "la minuscula usa el mismo glifo");
    // Los kana y la barra larga siguen como en la N64
    indices("\xa1\xbc\xa1\xbc", glifos, &recorrido);
    COMPROBACION(glifos[0] == 212 && glifos[1] == 212 && recorrido == 4, "barra larga: %d", glifos[0]);
}

static void probar_secuencias_rotas(void) {
    // Un 8F sin su letra: glifo invalido (-2), avanza 1 byte y no pasa del 0 final
    static char* rotas[] = { "\x8f", "\x8f\xaa", "\x8f\xaa\xa2", "\x8f\xa2\xc3" };
    s32 i, bytes;
    for (i = 0; i < 4; i++) {
        s32 indice = leer_glifo(rotas[i], &bytes);
        COMPROBACION(indice == -2 && bytes == 1, "secuencia rota %d: indice %d, %d bytes", i, indice, bytes);
    }
}

static void probar_anchos_espanol(void) {
    COMPROBACION(obtener_ancho_cadena("CAMPE" E_O "N") == obtener_ancho_cadena("CAMPEON"), "CAMPEON con tilde");
    COMPROBACION(obtener_ancho_cadena(E_A) == obtener_ancho_cadena("A"), "A con tilde");
    COMPROBACION(obtener_ancho_cadena(E_ABRE_EXCL) == obtener_ancho_cadena("!"), "apertura de exclamacion");
}

int main(void) {
    probar_compatibilidad();
    probar_anchos();
    probar_espanol();
    probar_secuencias_rotas();
    probar_anchos_espanol();
    printf("%d comprobaciones, %d fallos\n", s_comprobaciones, s_fallos);
    return s_fallos != 0;
}
