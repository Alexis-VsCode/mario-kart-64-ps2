// Tono del motor con el truco 200CC (funcion_800C6108 y carrera/cilindrada_200cc.h)
//
// En funcion_800C6108 el tono con el acelerador pulsado es
//     desconocido_098 / dato_800E9DC4 + dato_800E9DD4
// donde desconocido_098 = rapidez² / 25 (aceleracion.inc.c), dato_800E9DC4 es
// desconocido_2C y dato_800E9DD4 es desconocido_20 de la tabla por personaje
// (secuencias_musica.inc.c). El truco multiplica la rapidez máxima por 35/32.
//
// Margen: el propio código deja que el tono suba hasta desconocido_18 + 0.4
// (el umbral de dato_800E9DE4 en funcion_800C6108), así que 0.4 sobre el tono
// que da la rapidez máxima original del personaje es lo que el original tolera.
//
// Resultado medido: sin limitar, con 35/32 el tono sube entre 0.38 y 0.56 sobre
// el original, por encima de 0.4 en 4 de los 5 grupos de personajes (los avisos
// que imprime la prueba). Por eso funcion_800C6108 limita el tono con
// tono_200cc_limitar; la prueba exige que el resultado limitado quede dentro del
// margen y que el 150cc original no cambie.
// Modo por defecto: estricto. El tono que sale de funcion_800C6108 con el truco
// activo no puede pasar de desconocido_18 + 0,4. Con el argumento
// 'aviso' los casos sobre el margen solo se informan.
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "audio/tono_200cc.h"
#include "carrera/cilindrada_200cc.h"

#define MARGEN_TABLA 0.4
#define COTA_MEDIDA 0.57

typedef struct {
    const char *personajes;
    double max_tono; // desconocido_18
    double suma;     // desconocido_20
    double divisor;  // desconocido_2C
} GrupoTono;

// secuencias_musica.inc.c, arranque del motor (case 0)
static const GrupoTono grupos[] = {
    { "Mario/Luigi", 2.8, 0.35, 1568.9796 },
    { "Peach/Yoshi", 3.2, 0.6, 1478.4615 },
    { "Toad", 2.8, 0.6, 1747.2728 },
    { "DK", 2.0, 0.2, 2135.5557 },
    { "Wario/Bowser", 2.4, 0.4, 1922.0 },
};

// Rapidez máxima a 150cc de los personajes de cada grupo (atributos_kart.c,
// arriba_rapidez_150_cc): 324 en Yoshi, Peach y Toad, 320 en el resto
static const double rapidez_150[] = { 320, 324, 324, 320, 320 };

static int s_fallos, s_comprobaciones;

static void comprobar(const char *caso, int cond) {
    s_comprobaciones++;
    if (!cond) {
        s_fallos++;
        printf("FALLO %s\n", caso);
    }
}

static double tono(const GrupoTono *g, double rapidez) {
    return (rapidez * rapidez / 25.0) / g->divisor + g->suma;
}

int main(int argc, char **argv) {
    int estricto = !(argc > 1 && strcmp(argv[1], "aviso") == 0);
    int fuera = 0;
    char caso[128];

    comprobar("el factor es 35/32", fabs(cilindrada_200cc_rapidez(320.0f, 1) - 350.0) < 1e-3);

    for (unsigned i = 0; i < sizeof(grupos) / sizeof(grupos[0]); i++) {
        const GrupoTono *g = &grupos[i];

        {
            double r150 = rapidez_150[i];
            double original = tono(g, r150);
            double con_truco = tono(g, cilindrada_200cc_rapidez((float) r150, 1));
            double exceso = con_truco - original;

            snprintf(caso, sizeof(caso), "%s %g: el 150cc original cabe en su tabla (%.3f <= %.3f)", g->personajes,
                     r150, original, g->max_tono + MARGEN_TABLA);
            comprobar(caso, original <= g->max_tono + MARGEN_TABLA);
            snprintf(caso, sizeof(caso), "%s %g: el truco sube el tono %.3f, cota %.2f", g->personajes, r150, exceso,
                     COTA_MEDIDA);
            comprobar(caso, exceso > 0.0 && exceso < COTA_MEDIDA);
            if (exceso > MARGEN_TABLA) {
                fuera++;
                printf("aviso: %s a %g: tono %.3f con 200cc contra %.3f original (+%.3f, margen de la tabla %.1f)\n",
                       g->personajes, r150, con_truco, original, exceso, MARGEN_TABLA);
            }
        }
    }
    // El tono que da funcion_800C6108: sin límite con 150cc, limitado con el truco
    for (unsigned i = 0; i < sizeof(grupos) / sizeof(grupos[0]); i++) {
        const GrupoTono *g = &grupos[i];
        double bruto = tono(g, cilindrada_200cc_rapidez((float) rapidez_150[i], 1));
        double con_truco = tono_200cc_limitar((float) bruto, (float) g->max_tono, 1);
        double sin_truco = tono(g, rapidez_150[i]);

        snprintf(caso, sizeof(caso), "%s: con 200cc el tono final %.3f no pasa de %.1f", g->personajes, con_truco,
                 g->max_tono + MARGEN_TABLA);
        comprobar(caso, !estricto || con_truco <= g->max_tono + MARGEN_TABLA + 1e-5);
        snprintf(caso, sizeof(caso), "%s: con 150cc el resultado no cambia", g->personajes);
        comprobar(caso, tono_200cc_limitar((float) sin_truco, (float) g->max_tono, 0) == (float) sin_truco);
        snprintf(caso, sizeof(caso), "%s: con 200cc no baja un tono que ya cabía", g->personajes);
        comprobar(caso, tono_200cc_limitar(1.0f, (float) g->max_tono, 1) == 1.0f);
    }

    printf("%d comprobaciones, %d %s (%d casos sobre el margen de la tabla)\n", s_comprobaciones, s_fallos,
           s_fallos == 1 ? "fallo" : "fallos", fuera);
    return s_fallos != 0;
}
