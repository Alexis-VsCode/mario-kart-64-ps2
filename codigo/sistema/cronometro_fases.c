#include <stdio.h>
#include <string.h>

#include <ultra64.h>

#include "sistema/sistema_ps2.h"
#include "sistema/cronometro_fases.h"

#define GRUPOS_MAX 4
#define PASOS_MAX  24

typedef struct {
    const char *name;
    u32 ciclos;
    u32 vblanks;
} Paso;

typedef struct {
    const char *name;
    Paso pasos[PASOS_MAX];
    int count;
    u32 ciclos_total, total_vblanks;
    u32 runs;           /* veces que se midio (el informe es del ultimo) */
    int done;           /* el ultimo informe esta completo */
} Grupo;

static Grupo grupos[GRUPOS_MAX];
static Grupo *activo;
static u32 ciclos_inicio, vblank_inicio;
static u32 ciclos_paso, vblank_paso;
static const char *volatile ultimo_paso;
static const char *volatile nombre_activo;
static const void *volatile dl_esperado;

static Grupo *buscar_grupo(const char *nombre, int crear)
{
    int i;

    for (i = 0; i < GRUPOS_MAX; i++) {
        if (grupos[i].name != NULL && strcmp(grupos[i].name, nombre) == 0) {
            return &grupos[i];
        }
    }
    if (!crear) {
        return NULL;
    }
    for (i = 0; i < GRUPOS_MAX; i++) {
        if (grupos[i].name == NULL) {
            grupos[i].name = nombre;
            return &grupos[i];
        }
    }
    return &grupos[GRUPOS_MAX - 1]; /* sin hueco: se reutiliza el ultimo */
}

/* Milesimas de ms: ciclos si caben, si no VBlanks (59,94 Hz). */
static u32 us_duracion(u32 leer_contador_ciclos, u32 vblanks)
{
    if (vblanks > 780) {
        return vblanks * 16683u;
    }
    return (u32) (((u64) leer_contador_ciclos * 1000u) / CICLOS_PS2_POR_MS);
}

void empezar_tiempos_ps2(const char *group)
{
    dl_esperado = NULL;
    activo = buscar_grupo(group, 1);
    activo->name = group;
    activo->count = 0;
    activo->runs++;
    activo->done = 0;
    ciclos_inicio = ciclos_paso = ciclos_ps2();
    vblank_inicio = vblank_paso = contador_vblank();
    ultimo_paso = "(inicio)";
    nombre_activo = group;
}

void marcar_tiempos_ps2(const char *paso)
{
    u32 ahora = ciclos_ps2();
    u32 vb = contador_vblank();

    if (activo == NULL) {
        return;
    }
    if (activo->count < PASOS_MAX) {
        Paso *s = &activo->pasos[activo->count++];

        s->name = paso;
        s->ciclos = ahora - ciclos_paso;
        s->vblanks = vb - vblank_paso;
    }
    ciclos_paso = ahora;
    vblank_paso = vb;
    ultimo_paso = paso;
}

void fin_tiempos_ps2(void)
{
    Grupo *g = activo;

    if (g == NULL) {
        return;
    }
    g->ciclos_total = ciclos_ps2() - ciclos_inicio;
    g->total_vblanks = contador_vblank() - vblank_inicio;
    g->done = 1;
    activo = NULL;
    nombre_activo = NULL;
#if defined(SMK64_DEV) || defined(SMK64_DEBUG)
    {
        char lineas_2[PASOS_MAX + 1][96];
        int i, n = informe_tiempos_ps2(g->name, lineas_2, PASOS_MAX + 1);

        for (i = 0; i < n; i++) {
            registrar("%s", lineas_2[i]);
        }
    }
#endif
}

void ps2_tiempos_esperado_frame(const void *dl)
{
    if (activo != NULL && dl_esperado == NULL) {
        marcar_tiempos_ps2("primer frame: logica");
        dl_esperado = dl;
    }
}

void ps2_tiempos_frame_shown(const void *dl)
{
    if (activo != NULL && dl_esperado != NULL && dl == dl_esperado) {
        dl_esperado = NULL;
        marcar_tiempos_ps2("primer frame: render");
        fin_tiempos_ps2();
    }
}

const char *ps2_tiempos_activo_grupo(void)
{
    return nombre_activo;
}

const char *ps2_tiempos_ultimo_paso(void)
{
    return ultimo_paso;
}

int informe_tiempos_ps2(const char *group, char lineas_2[][96], int lineas_max)
{
    const Grupo *g = buscar_grupo(group, 0);
    int i, n = 0;
    u32 total;

    if (g == NULL || lineas_max <= 0) {
        return 0;
    }
    total = us_duracion(g->ciclos_total, g->total_vblanks);
    snprintf(lineas_2[n++], 96, "%s (%u): %u.%03u ms, %u VBlanks", g->name, (unsigned) g->runs, (unsigned) (total / 1000),
             (unsigned) (total % 1000), (unsigned) g->total_vblanks);
    for (i = 0; i < g->count && n < lineas_max; i++) {
        u32 us = us_duracion(g->pasos[i].ciclos, g->pasos[i].vblanks);

        snprintf(lineas_2[n++], 96, "  %-26s %6u.%03u ms", g->pasos[i].name, (unsigned) (us / 1000),
                 (unsigned) (us % 1000));
    }
    return n;
}

int summary_tiempos_ps2(const char *group, u32 *total_us, const char **paso_mas_largo, u32 *us_mas_largo)
{
    const Grupo *g = buscar_grupo(group, 0);
    int i;

    if (g == NULL || !g->done) {
        return 0;
    }
    *total_us = us_duracion(g->ciclos_total, g->total_vblanks);
    *paso_mas_largo = NULL;
    *us_mas_largo = 0;
    for (i = 0; i < g->count; i++) {
        u32 us = us_duracion(g->pasos[i].ciclos, g->pasos[i].vblanks);

        if (us > *us_mas_largo) {
            *us_mas_largo = us;
            *paso_mas_largo = g->pasos[i].name;
        }
    }
    return 1;
}
