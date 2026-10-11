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

// Cuenta los «#define GRUPO_» de la cabecera; -1 si no se puede leer
static int contar_grupos_cabecera(const char *ruta) {
    char linea[256];
    int n = 0;
    FILE *f = fopen(ruta, "r");

    if (f == NULL) {
        return -1;
    }
    while (fgets(linea, sizeof(linea), f) != NULL) {
        n += strncmp(linea, "#define GRUPO_", strlen("#define GRUPO_")) == 0;
    }
    fclose(f);
    return n;
}

int main(void) {
    char lineas[PASOS_MAX + 1][96];
    char cabecera[64];
    int g, p;
    int grupos_cabecera = contar_grupos_cabecera("incluir/depuracion/marcas_registro.h");

    // Cada grupo de marcas_registro.h tiene su hueco y queda al menos uno libre
    COMPROBACION(grupos_cabecera > 0, "marcas_registro.h: no se leen sus grupos (%d)", grupos_cabecera);
    COMPROBACION(GRUPOS_MAX > grupos_cabecera, "GRUPOS_MAX es %d y marcas_registro.h define %d grupos", GRUPOS_MAX,
                 grupos_cabecera);

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
    printf("%d comprobaciones, %d %s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "fallo" : "fallos");
    return s_fallos != 0;
}
