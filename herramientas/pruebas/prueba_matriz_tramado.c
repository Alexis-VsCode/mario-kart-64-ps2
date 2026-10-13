// Registro DIMX propio (matriz_tramado.h): la matriz de tramado estándar de la
// N64 convertida a las celdas con signo de 3 bits del GS.
#include <stdint.h>
#include <stdio.h>

#include "graficos/matriz_tramado.h"

static int s_fallos, s_comprobaciones;

static void comprobar_registro(const char *que, uint64_t obtenido, uint64_t esperado) {
    s_comprobaciones++;
    if (obtenido != esperado) {
        s_fallos++;
        printf("FALLO %s: %016llx, se esperaba %016llx\n", que, (unsigned long long) obtenido, (unsigned long long) esperado);
    }
}

static void comprobar_celda(int indice, int esperado) {
    int obtenido = matriz_tramado_celda_gs(indice);

    s_comprobaciones++;
    if (obtenido != esperado) {
        s_fallos++;
        printf("FALLO celda %d: %d, se esperaba %d\n", indice, obtenido, esperado);
    }
}

int main(void) {
    // Matriz mágica del RDP (0..7) menos 4: -4..3, el rango de una celda del GS
    static const int esperadas[16] = { -4, 2, -3, 3, 0, -2, 1, -1, -1, 1, -2, 0, 3, -3, 2, -4 };
    int i, suma = 0, usado[8] = { 0 };

    for (i = 0; i < 16; i++) {
        comprobar_celda(i, esperadas[i]);
        suma += matriz_tramado_celda_gs(i);
        usado[matriz_tramado_celda_gs(i) + 4]++;
    }
    // Cada fila y cada columna suma lo mismo que en la N64 (14 - 16 = -2) y cada valor sale dos veces
    for (i = 0; i < 4; i++) {
        int fila = 0, columna = 0, j;

        for (j = 0; j < 4; j++) {
            fila += matriz_tramado_celda_gs(i * 4 + j);
            columna += matriz_tramado_celda_gs(j * 4 + i);
        }
        s_comprobaciones += 2;
        if (fila != -2 || columna != -2) {
            s_fallos++;
            printf("FALLO suma de la fila/columna %d: %d/%d, se esperaba -2\n", i, fila, columna);
        }
    }
    s_comprobaciones += 9;
    for (i = 0; i < 8; i++) {
        if (usado[i] != 2) {
            s_fallos++;
            printf("FALLO el valor %d sale %d veces, se esperaban 2\n", i - 4, usado[i]);
        }
    }
    if (suma != -8) {
        s_fallos++;
        printf("FALLO suma total %d, se esperaba -8\n", suma);
    }

    // Registro completo: cuatro bits por celda, la celda i en los bits 4i a 4i+2
    comprobar_registro("DIMX completo", matriz_tramado_dimx(), 0x4253061771603524ULL);
    // La última celda (15) vale -4 y se escribe: bits 60 a 62 = 4
    comprobar_registro("celda 15", (matriz_tramado_dimx() >> 60) & 7, 4);
    // Lo que deja el bucle de gsKit (15 celdas): la celda 15 queda en 0
    comprobar_registro("gsKit sin celda 15", matriz_tramado_dimx_con_celdas(15), 0x0253061771603524ULL);
    comprobar_registro("sin celdas", matriz_tramado_dimx_con_celdas(0), 0);
    // El bit 3 de cada celda nunca se usa
    comprobar_registro("bits reservados", matriz_tramado_dimx() & 0x8888888888888888ULL, 0);

    printf("%d comprobaciones, %d fallo%s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "" : "s");
    return s_fallos != 0;
}
