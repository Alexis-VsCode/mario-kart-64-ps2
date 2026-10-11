// Elección de la copia que se pisa al guardar en una tarjeta recién leída
// (eleccion_guardado.h) en el PC
#include <stdint.h>
#include <stdio.h>

#include "sistema/eleccion_guardado.h"

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

static char letra(int copia)
{
    return copia == COPIA_GUARDADO_A ? 'A' : 'B';
}

// Comprueba la copia elegida, la generación mínima y la generación con la que
// se escribiría la partida de una sesión que va por generacion_sesion
static void comprobar(const char *caso, int valida_a, uint32_t gen_a, int valida_b, uint32_t gen_b,
                      uint32_t generacion_sesion, int copia_esperada, uint32_t minima_esperada)
{
    EleccionGuardado e = elegir_copia_guardado(valida_a, gen_a, valida_b, gen_b);
    uint32_t escrita = generacion_sesion + desplazamiento_generacion(generacion_sesion, e.generacion_minima);

    COMPROBACION(e.copia == copia_esperada, "%s: escribe la copia %c, se esperaba la %c", caso, letra(e.copia),
                 letra(copia_esperada));
    COMPROBACION(e.generacion_minima == minima_esperada, "%s: generación mínima %u, se esperaba %u", caso,
                 (unsigned) e.generacion_minima, (unsigned) minima_esperada);
    COMPROBACION(escrita >= minima_esperada, "%s: la sesión en %u escribe la generación %u, menor que %u", caso,
                 (unsigned) generacion_sesion, (unsigned) escrita, (unsigned) minima_esperada);
}

int main(void)
{
    // Las dos válidas: se pisa la más vieja y se escribe por encima de la más nueva
    comprobar("A 50, B 49, sesión 3", 1, 50, 1, 49, 3, COPIA_GUARDADO_B, 51);
    comprobar("A 49, B 50, sesión 3", 1, 49, 1, 50, 3, COPIA_GUARDADO_A, 51);
    // Empate: cargar_partida da por más nueva la A, así que se pisa la B
    comprobar("A 20, B 20", 1, 20, 1, 20, 0, COPIA_GUARDADO_B, 21);
    // Una sola válida: se pisa la otra; la generación de la inválida no cuenta
    comprobar("solo A válida", 1, 7, 0, 1000, 0, COPIA_GUARDADO_B, 8);
    comprobar("solo B válida", 0, 1000, 1, 7, 0, COPIA_GUARDADO_A, 8);
    // Ninguna válida: se empieza por la A y la generación de la sesión vale
    comprobar("ninguna válida", 0, 50, 0, 49, 3, COPIA_GUARDADO_A, 0);

    // La sesión ya va por encima de la tarjeta: no se desplaza
    COMPROBACION(desplazamiento_generacion(100, 51) == 0, "sesión 100 y mínima 51: desplazamiento %u, se esperaba 0",
                 (unsigned) desplazamiento_generacion(100, 51));
    COMPROBACION(desplazamiento_generacion(3, 51) == 48, "sesión 3 y mínima 51: desplazamiento %u, se esperaba 48",
                 (unsigned) desplazamiento_generacion(3, 51));

    printf("%d comprobaciones, %d fallos\n", s_comprobaciones, s_fallos);
    return s_fallos != 0;
}
