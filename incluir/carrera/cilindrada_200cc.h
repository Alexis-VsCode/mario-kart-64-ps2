#ifndef CARRERA_CILINDRADA_200CC_H
#define CARRERA_CILINDRADA_200CC_H

#include <juego/definiciones.h>

// Truco 200CC (CC-24): modificador de 150cc, no una cilindrada nueva; un valor
// 4 chocaría con BATALLA_CC y leería fuera de las tablas de la CPU.
// seleccion_cc sigue en CC_150, así que puntúa y se muestra como 150cc.

#define CILINDRADA_200CC_FACTOR (35.0f / 32.0f)

// Solo Gran Premio y Versus a 150cc: los fantasmas de contrarreloj guardan
// entradas y se desincronizarían
static inline int cilindrada_200cc_aplica(int activo, int modo, int cc) {
    return activo && (modo == GRAN_PREMIO || modo == VERSUS) && cc == CC_150;
}

static inline float cilindrada_200cc_rapidez(float base, int aplica) {
    return aplica ? base * CILINDRADA_200CC_FACTOR : base;
}

// Empuje (desconocido_210) de una rapidez máxima: las tablas son (rapidez/5)²
static inline float cilindrada_200cc_empuje(float rapidez) {
    return rapidez * rapidez / 25.0f;
}

// Objetivo de velocidad de la CPU: por el cuadrado del factor, como el empuje
static inline float cilindrada_200cc_objetivo(float base, int aplica) {
    return aplica ? base * CILINDRADA_200CC_FACTOR * CILINDRADA_200CC_FACTOR : base;
}

#endif
