#ifndef CARRERA_RIVALES_SIN_VENTAJA_H
#define CARRERA_RIVALES_SIN_VENTAJA_H

// Truco RIVALES SIN VENTAJA: la CPU del Gran Premio pierde el impulso
// que recibe al ir por detrás del jugador. Las órdenes de velocidad de cada
// pista (RAPIDO, MAX, LENTO) no cambian.

// Con el truco la CPU acelera solo hasta el objetivo de su tabla
static inline int cpu_acelera_sin_ventaja(float rapidez, float objetivo) {
    return rapidez < objetivo;
}

// La velocidad fija de recuperación se sustituye por el objetivo base
static inline float objetivo_cpu_sin_ventaja(float original, float base, int activo) {
    return activo ? base : original;
}

#endif
