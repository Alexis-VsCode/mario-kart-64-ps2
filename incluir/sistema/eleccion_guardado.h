#ifndef SISTEMA_ELECCION_GUARDADO_H
#define SISTEMA_ELECCION_GUARDADO_H

#include <stdint.h>

/* Las dos copias de la partida en la tarjeta (SMK64A.SAV y SMK64B.SAV) */
#define COPIA_GUARDADO_A 0
#define COPIA_GUARDADO_B 1

typedef struct {
    int copia;                  /* la que se pisa en el próximo guardado */
    uint32_t generacion_minima; /* lo mínimo que tiene que llevar esa escritura; 0: sin mínimo */
} EleccionGuardado;

/* Con las cabeceras leídas de una tarjeta, elige la copia que se pisa: la más
   vieja de las válidas, para que la más nueva siga en la tarjeta si la escritura
   se corta. En un empate se pisa la B, porque la carga da por más nueva la A; sin
   ninguna válida, la A. La escritura tiene que quedar por encima de todas las
   válidas, o la carga siguiente elegiría la copia anterior. */
static inline EleccionGuardado elegir_copia_guardado(int valida_a, uint32_t gen_a, int valida_b, uint32_t gen_b)
{
    EleccionGuardado e;
    int a_mas_nueva = valida_a && (!valida_b || gen_a >= gen_b);

    e.copia = a_mas_nueva ? COPIA_GUARDADO_B : COPIA_GUARDADO_A;
    if (valida_a || valida_b) {
        e.generacion_minima = (a_mas_nueva ? gen_a : gen_b) + 1;
    } else {
        e.generacion_minima = 0;
    }
    return e;
}

/* Lo que se suma a la generación de la sesión para llegar a la mínima; 0 si ya llega */
static inline uint32_t desplazamiento_generacion(uint32_t generacion_sesion, uint32_t generacion_minima)
{
    return generacion_minima > generacion_sesion ? generacion_minima - generacion_sesion : 0;
}

#endif
