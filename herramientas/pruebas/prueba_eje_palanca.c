// Conversión del eje del stick de la PS2 al recorrido de la N64 (eje_palanca.h) en el PC
#include <stdio.h>

#include <PR/ultratypes.h>
#include "entrada/eje_palanca.h"

// Zona muerta que el juego aplica después sobre el valor convertido
// (obtener_limitado_palanca_x_con_zona_muerta, mandos_carrera.inc.c)
#define ZONA_MUERTA_JUEGO 12
// Distancia máxima al centro a la que el kart tiene que empezar a girar
#define DISTANCIA_GIRO_MAX 28

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

int main(void) {
    int crudo, d, giro = -1;

    // Centro, ruido pequeño alrededor del centro y extremos
    COMPROBACION(convertir_eje(128) == 0, "centro 128 da %d, se esperaba 0", convertir_eje(128));
    for (d = 1; d <= 2; d++) {
        COMPROBACION(convertir_eje((u8) (128 + d)) == 0 && convertir_eje((u8) (128 - d)) == 0,
                     "ruido de %d alrededor del centro da %d y %d, se esperaba 0", d, convertir_eje((u8) (128 + d)),
                     convertir_eje((u8) (128 - d)));
    }
    COMPROBACION(convertir_eje(255) == 80, "255 da %d, se esperaba 80", convertir_eje(255));
    COMPROBACION(convertir_eje(0) == -80, "0 da %d, se esperaba -80", convertir_eje(0));

    // Simetría: a la misma distancia del centro, el mismo valor con el signo cambiado
    for (d = 0; d <= 127; d++) {
        int arriba = convertir_eje((u8) (128 + d));
        int abajo = convertir_eje((u8) (128 - d));

        COMPROBACION(arriba == -abajo, "distancia %d: %d y %d no son simétricos", d, arriba, abajo);
    }

    // Monotonía: la salida nunca baja cuando el valor crudo sube
    for (crudo = 1; crudo <= 255; crudo++) {
        COMPROBACION(convertir_eje((u8) crudo) >= convertir_eje((u8) (crudo - 1)), "%d da %d, menos que %d con %d",
                     crudo, convertir_eje((u8) crudo), convertir_eje((u8) (crudo - 1)), crudo - 1);
    }

    // El giro empieza cerca del centro: primer valor crudo que supera la zona muerta del juego
    for (crudo = 128; crudo <= 255 && giro < 0; crudo++) {
        if (convertir_eje((u8) crudo) > ZONA_MUERTA_JUEGO) {
            giro = crudo - 128;
        }
    }
    COMPROBACION(giro >= 0 && giro <= DISTANCIA_GIRO_MAX,
                 "el giro empieza a %d del centro, se esperaba como mucho %d", giro, DISTANCIA_GIRO_MAX);

    // La cruceta hace de stick mientras el izquierdo está en reposo: el reposo usa su propio
    // umbral, para que la deriva de un stick gastado no la anule
    COMPROBACION(eje_en_reposo(128), "el centro no cuenta como reposo");
    for (d = 1; d < ZONA_REPOSO_CRUCETA; d++) {
        COMPROBACION(eje_en_reposo((u8) (128 + d)) && eje_en_reposo((u8) (128 - d)),
                     "una deriva de %d no cuenta como reposo", d);
    }
    COMPROBACION(!eje_en_reposo((u8) (128 + ZONA_REPOSO_CRUCETA)) && !eje_en_reposo((u8) (128 - ZONA_REPOSO_CRUCETA)),
                 "a %d del centro el stick ya no está en reposo", ZONA_REPOSO_CRUCETA);
    COMPROBACION(!eje_en_reposo(255) && !eje_en_reposo(0), "los extremos cuentan como reposo");

    // Quién manda: sin modo analógico siempre la cruceta; con él, solo si los dos ejes del
    // stick izquierdo están en reposo, deriva incluida
    COMPROBACION(cruceta_manda_stick(0, 128, 128) && cruceta_manda_stick(0, 255, 0),
                 "sin modo analógico la cruceta no manda");
    COMPROBACION(cruceta_manda_stick(1, 128, 128), "con el stick en el centro la cruceta no manda");
    for (d = 10; d <= 25; d++) {
        COMPROBACION(cruceta_manda_stick(1, (u8) (128 + d), (u8) (128 - d)) &&
                         cruceta_manda_stick(1, (u8) (128 - d), (u8) (128 + d)),
                     "con una deriva de %d la cruceta no manda", d);
    }
    COMPROBACION(!cruceta_manda_stick(1, 128 + ZONA_REPOSO_CRUCETA, 128), "con el eje x fuera de reposo manda la cruceta");
    COMPROBACION(!cruceta_manda_stick(1, 128, 128 - ZONA_REPOSO_CRUCETA), "con el eje y fuera de reposo manda la cruceta");
    COMPROBACION(!cruceta_manda_stick(1, 255, 0), "con el stick al fondo manda la cruceta");

    printf("prueba_eje_palanca: %d comprobaciones, %d %s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "fallo" : "fallos");
    return s_fallos != 0;
}
