#ifndef AUDIO_TONO_200CC_H
#define AUDIO_TONO_200CC_H

// Tono del motor con el truco de 200cc (CC-39). La rapidez máxima sube 35/32 y
// el tono con ella: hasta 0,56 sobre el original, más que el margen de 0,4 que
// deja la tabla del juego en 4 de 5 grupos de personajes. Con el truco activo el
// tono final no pasa de max_tono (desconocido_18) + 0,4; con 150cc no se toca.

#define TONO_200CC_MARGEN 0.4f

static inline float tono_200cc_limitar(float tono, float max_tono, int aplica) {
    float tope = max_tono + TONO_200CC_MARGEN;

    return (aplica && tono > tope) ? tope : tono;
}

#endif
