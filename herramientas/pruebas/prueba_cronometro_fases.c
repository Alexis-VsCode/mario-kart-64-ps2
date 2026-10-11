// Grupos del cronómetro de fases (cronometro_fases.c) en el PC
#include <stdio.h>
#include <string.h>

#include <PR/ultratypes.h>
#include "depuracion/marcas_registro.h"

// cronometro_fases.h lee el contador de ciclos del EE con mfc0 y trae
// tamtypes.h del SDK: la prueba lo sustituye por un contador que avanza a mano
#define SISTEMA_CRONOMETRO_FASES_H
#define CICLOS_PS2_POR_MS 294912u
static u32 ciclos_falsos;
static u32 ciclos_ps2(void) {
    return ciclos_falsos;
}
u32 contador_vblank(void) {
    return 0;
}

#include "sistema/cronometro_fases.c"

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

// Los grupos de marcas_registro.h y dos mas, que no existen todavia
static const char *const nombres_grupo[] = {
    GRUPO_ARRANQUE, GRUPO_CARGA_PISTA, GRUPO_CARGA_CEREMONIA, GRUPO_CARGA_CREDITOS, "quinto grupo", "sexto grupo",
};
#define GRUPOS_PRUEBA ((int) (sizeof(nombres_grupo) / sizeof(nombres_grupo[0])))
static const char *const nombres_paso[GRUPOS_PRUEBA] = {
    "paso 1", "paso 2", "paso 3", "paso 4", "paso 5", "paso 6",
};

int main(void) {
    char lineas[PASOS_MAX + 1][96];
    char cabecera[64];
    int g, p;

    // Paso 1: el grupo g se mide una vez y anota g + 1 pasos
    for (g = 0; g < GRUPOS_PRUEBA; g++) {
        empezar_tiempos_ps2(nombres_grupo[g]);
        for (p = 0; p <= g; p++) {
            ciclos_falsos += CICLOS_PS2_POR_MS;
            marcar_tiempos_ps2(nombres_paso[p]);
        }
        fin_tiempos_ps2();
    }
    // Paso 2: cada grupo conserva su nombre, sus pasos y una sola medida
    for (g = 0; g < GRUPOS_PRUEBA; g++) {
        int n = informe_tiempos_ps2(nombres_grupo[g], lineas, PASOS_MAX + 1);

        snprintf(cabecera, sizeof(cabecera), "%s (1): ", nombres_grupo[g]);
        COMPROBACION(n == g + 2, "'%s': %d líneas en el informe, se esperaban %d", nombres_grupo[g], n, g + 2);
        COMPROBACION(n > 0 && strncmp(lineas[0], cabecera, strlen(cabecera)) == 0, "'%s': el informe dice '%s'",
                     nombres_grupo[g], n > 0 ? lineas[0] : "");
    }
    printf("%d comprobaciones, %d fallos\n", s_comprobaciones, s_fallos);
    return s_fallos != 0;
}
