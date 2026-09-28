// Cadenas de la fuente de depuracion de la N64 (cadena_depuracion.inc.c) en el PC
#include <stdio.h>
#include <string.h>

#include <PR/ultratypes.h>

// La tabla real (vertices_jugadores_y_listas.c) se copia a una con una zona
// antes, para ver si alguien lee fuera de ella
extern s8 dato_800E5628[];
#define CELDAS_TABLA 256
#define CELDA_FUERA 0x05
static struct {
    s8 antes[CELDAS_TABLA];
    s8 tabla[CELDAS_TABLA];
} fuente;

// Celdas que se dibujan: (x, y, celda)
#define DIBUJADAS_MAX 64
static struct {
    s32 x, y, celda;
} dibujadas[DIBUJADAS_MAX];
static int n_dibujadas;

void funcion_800573E4(s32 x, s32 y, s8 cad) {
    if (n_dibujadas < DIBUJADAS_MAX) {
        dibujadas[n_dibujadas].x = x;
        dibujadas[n_dibujadas].y = y;
        dibujadas[n_dibujadas].celda = cad;
        n_dibujadas++;
    }
}

#define dato_800E5628 fuente.tabla
#include "graficos/dibujar_objetos/cadena_depuracion.inc.c"
#undef dato_800E5628

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

// Dibuja cadena desde (0, 0); devuelve la x final (20 de margen + 8 por celda)
static s32 dibujar(const char* cadena) {
    s32 x = 0, y = 0;
    n_dibujadas = 0;
    imprimir_cadena_depuracion(&x, &y, (char*) cadena);
    return x;
}

static s32 celda(char c) {
    return fuente.tabla[(u8) c];
}

static void probar_ascii(void) {
    s32 x = dibujar("AB");
    COMPROBACION(n_dibujadas == 2 && dibujadas[0].celda == celda('A') && dibujadas[1].celda == celda('B') &&
                     dibujadas[0].x == 20 && dibujadas[1].x == 28 && x == 36,
                 "AB: %d celdas, x final %d", n_dibujadas, (int) x);
    x = dibujar("a b");
    COMPROBACION(n_dibujadas == 2 && dibujadas[0].celda == celda('A') && dibujadas[1].x == 36 && x == 44,
                 "a b: el espacio avanza sin dibujar (%d celdas, x %d)", n_dibujadas, (int) x);
}

int main(void) {
    memset(fuente.antes, CELDA_FUERA, sizeof(fuente.antes));
    memcpy(fuente.tabla, dato_800E5628, sizeof(fuente.tabla));
    probar_ascii();
    printf("%d comprobaciones, %d fallos\n", s_comprobaciones, s_fallos);
    return s_fallos != 0;
}
