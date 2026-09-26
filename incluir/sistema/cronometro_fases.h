#ifndef SISTEMA_CRONOMETRO_FASES_H
#define SISTEMA_CRONOMETRO_FASES_H

#include <tamtypes.h>

#define CICLOS_PS2_POR_MS 294912u

static inline u32 ciclos_ps2(void)
{
    u32 c;

    __asm__ __volatile__("mfc0 %0, $9" : "=r"(c));
    return c;
}

void empezar_tiempos_ps2(const char *group);
void marcar_tiempos_ps2(const char *paso);
void fin_tiempos_ps2(void);

/* Primer frame tras la carga */
void ps2_tiempos_esperado_frame(const void *dl);
void ps2_tiempos_frame_shown(const void *dl);

const char *ps2_tiempos_activo_grupo(void);
const char *ps2_tiempos_ultimo_paso(void);

int informe_tiempos_ps2(const char *group, char lineas_2[][96], int lineas_max);

int summary_tiempos_ps2(const char *group, u32 *total_us, const char **paso_mas_largo, u32 *us_mas_largo);

#endif
