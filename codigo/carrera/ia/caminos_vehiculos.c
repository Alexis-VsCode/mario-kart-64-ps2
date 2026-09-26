#include <ultra64.h>

#include "juego/camino.h"
#include "sistema/sistema_ps2.h"
#include "carrera/caminos_vehiculos.h"

typedef struct {
    s16 x;
    s16 z;
} Punto2D;

/* Por camino */
static const s16 tabla[] = {
#include "tabla_caminos_vehiculos.h" /* generado en build/ */
};

static const s16 *buscar(const PuntoCaminoPista *orig_, s32 puntos_camino_num, s32 *cantidad)
{
    const s16 *p = tabla;

    while (p[0] != 0) {
        s32 n = p[0], c = p[1], k;
        const s16 *orig = p + 2, *salida = orig + 2 * n;

        if (n == puntos_camino_num) {
            for (k = 0; k < n; k++) {
                if (orig_[k].pos_x != orig[2 * k] || orig_[k].pos_z != orig[2 * k + 1]) {
                    break;
                }
            }
            if (k == n) {
                *cantidad = c;
                return salida;
            }
        }
        p = salida + 2 * c;
    }
    return NULL;
}

s32 busqueda_camino_vehiculo_ps2(void *dest, const PuntoCaminoPista *orig_, s32 puntos_camino_num, s32 espejo)
{
    Punto2D *d = dest;
    s32 cantidad, k;
    const s16 *salida = buscar(orig_, puntos_camino_num, &cantidad);

    if (salida == NULL) {
        return -1;
    }
    /* En modo espejo el original guarda (s16) -x */
    for (k = 0; k < cantidad; k++) {
        d[k].x = espejo ? (s16) -salida[2 * k] : salida[2 * k];
        d[k].z = salida[2 * k + 1];
    }
    return cantidad;
}

void comprobar_camino_vehiculo_ps2(const void *computed, s32 cantidad, const PuntoCaminoPista *orig_, s32 puntos_camino_num,
                            s32 espejo)
{
    const Punto2D *c = computed;
    s32 cantidad_tabla, k, n, dif_ = 0, max_dx = 0, max_dz = 0;
    const s16 *salida = buscar(orig_, puntos_camino_num, &cantidad_tabla);

    if (salida == NULL) {
        registrar("PATH_CHECK: camino de %d puntos sin tabla", (int) puntos_camino_num);
        return;
    }
    n = (cantidad < cantidad_tabla) ? cantidad : cantidad_tabla;
    for (k = 0; k < n; k++) {
        s32 x = espejo ? -salida[2 * k] : salida[2 * k];
        s32 dx = c[k].x - x, dz = c[k].z - salida[2 * k + 1];

        dx = dx < 0 ? -dx : dx;
        dz = dz < 0 ? -dz : dz;
        dif_ += dx != 0 || dz != 0;
        max_dx = dx > max_dx ? dx : max_dx;
        max_dz = dz > max_dz ? dz : max_dz;
    }
    registrar("PATH_CHECK camino de %d puntos (espejo %d): EE %d puntos, tabla (N64) %d; distintos %d, dif. max x %d z %d",
            (int) puntos_camino_num, (int) espejo, (int) cantidad, (int) cantidad_tabla, (int) dif_, (int) max_dx, (int) max_dz);
}
