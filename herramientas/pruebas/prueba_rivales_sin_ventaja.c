// Truco RIVALES SIN VENTAJA (carrera/rivales_sin_ventaja.h)
#include <stdio.h>

#include "carrera/rivales_sin_ventaja.h"

static int s_fallos, s_comprobaciones;

static void comprobar(const char *caso, double obtenido, double esperado) {
    s_comprobaciones++;
    if (obtenido != esperado) {
        s_fallos++;
        printf("FALLO %s: %g, se esperaba %g\n", caso, obtenido, esperado);
    }
}

int main(void) {
    // Sin el impulso, la CPU acelera solo mientras no llega al objetivo
    comprobar("acelera por debajo", cpu_acelera_sin_ventaja(5.0f, 5.75f), 1);
    comprobar("no acelera en el objetivo", cpu_acelera_sin_ventaja(5.75f, 5.75f), 0);
    comprobar("no acelera por encima", cpu_acelera_sin_ventaja(6.0f, 5.75f), 0);

    // La velocidad fija de recuperación se sustituye por el objetivo base
    comprobar("objetivo con truco", objetivo_cpu_sin_ventaja(8.333333f, 5.75f, 1), 5.75f);
    comprobar("objetivo sin truco", objetivo_cpu_sin_ventaja(8.333333f, 5.75f, 0), 8.333333f);

    printf("%d comprobaciones, %d %s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "fallo" : "fallos");
    return s_fallos != 0;
}
