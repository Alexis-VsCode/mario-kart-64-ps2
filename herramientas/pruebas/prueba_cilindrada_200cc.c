// Truco 200CC (carrera/cilindrada_200cc.h)
#include <math.h>
#include <stdio.h>

#include "carrera/cilindrada_200cc.h"

static int s_fallos, s_comprobaciones;

static void comprobar(const char *caso, double obtenido, double esperado, double tolerancia) {
    s_comprobaciones++;
    if (fabs(obtenido - esperado) > tolerancia) {
        s_fallos++;
        printf("FALLO %s: %g, se esperaba %g\n", caso, obtenido, esperado);
    }
}

int main(void) {
    // La fórmula del empuje reproduce las tablas originales (atributos_kart.c)
    comprobar("empuje 320", cilindrada_200cc_empuje(320.0f), 4096.0, 0.0);
    comprobar("empuje 290", cilindrada_200cc_empuje(290.0f), 3364.0, 0.0);
    comprobar("empuje 310", cilindrada_200cc_empuje(310.0f), 3844.0, 0.0);
    comprobar("empuje 324", cilindrada_200cc_empuje(324.0f), 4199.0, 1.0);
    comprobar("empuje 294", cilindrada_200cc_empuje(294.0f), 3457.0, 1.0);

    // Factor 35/32 en la rapidez máxima y su cuadrado en el objetivo de la CPU
    comprobar("rapidez 320", cilindrada_200cc_rapidez(320.0f, 1), 350.0, 0.0);
    comprobar("rapidez 324", cilindrada_200cc_rapidez(324.0f, 1), 354.375, 0.0);
    comprobar("empuje 350", cilindrada_200cc_empuje(cilindrada_200cc_rapidez(320.0f, 1)), 4900.0, 0.0);
    comprobar("objetivo 5.75", cilindrada_200cc_objetivo(5.75f, 1), 5.75 * 35.0 * 35.0 / (32.0 * 32.0), 1e-5);
    comprobar("rapidez sin truco", cilindrada_200cc_rapidez(320.0f, 0), 320.0, 0.0);
    comprobar("objetivo sin truco", cilindrada_200cc_objetivo(5.75f, 0), 5.75, 0.0);

    // Peor caso de velocidad por paso (el kart más rápido, con turbo): por
    // debajo de 8.8 deja margen para las pendientes, que la cuenta no incluye
    {
        double peor = (cilindrada_200cc_empuje(cilindrada_200cc_rapidez(324.0f, 1)) + 580.0 + 400.0) / 696.0;

        s_comprobaciones++;
        if (!(peor < 8.8)) {
            s_fallos++;
            printf("FALLO peor caso: %g, tiene que ser menor que 8.8\n", peor);
        }
    }

    // Solo Gran Premio y Versus a 150cc
    comprobar("aplica GP 150", cilindrada_200cc_aplica(1, GRAN_PREMIO, CC_150), 1, 0);
    comprobar("aplica VS 150", cilindrada_200cc_aplica(1, VERSUS, CC_150), 1, 0);
    comprobar("apagado", cilindrada_200cc_aplica(0, GRAN_PREMIO, CC_150), 0, 0);
    comprobar("contrarreloj", cilindrada_200cc_aplica(1, CONTRARRELOJ, CC_150), 0, 0);
    comprobar("batalla", cilindrada_200cc_aplica(1, BATALLA, BATALLA_CC), 0, 0);
    comprobar("GP 100", cilindrada_200cc_aplica(1, GRAN_PREMIO, CC_100), 0, 0);
    comprobar("GP extra", cilindrada_200cc_aplica(1, GRAN_PREMIO, CC_EXTRA), 0, 0);

    printf("%d comprobaciones, %d %s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "fallo" : "fallos");
    return s_fallos != 0;
}
