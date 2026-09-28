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

int main(void) {
    probar_compatibilidad();
    probar_anchos();
    printf("%d comprobaciones, %d fallos\n", s_comprobaciones, s_fallos);
    return s_fallos != 0;
}
