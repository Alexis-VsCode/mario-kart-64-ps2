#ifndef CARRERA_TRUCO_OBJETO_H
#define CARRERA_TRUCO_OBJETO_H

#include <juego/definiciones.h>
#include "sistema/opciones_port.h"

// Truco OBJETO: la caja de un jugador humano da siempre el objeto
// elegido. Se aplica después del sorteo para que el generador aleatorio avance
// igual; la CPU y el Boo no pasan por aquí.

// 1 si el objeto puede salir en ese modo. En batalla solo los de su ruleta;
// en contrarreloj y otros modos, ninguno.
static inline int truco_objeto_valido(int objeto, int modo) {
    if (objeto <= NINGUNO_ITEM || objeto > TRUCO_OBJETO_MAX || objeto == TRUCO_OBJETO_PROHIBIDO) {
        return 0;
    }
    switch (modo) {
        case GRAN_PREMIO:
        case VERSUS:
            return 1;
        case BATALLA:
            switch (objeto) {
                case ITEM_BANANA:
                case GRUPO_BANANA_ITEM:
                case ITEM_CAPARAZON_VERDE:
                case TRIPLE_ITEM_CAPARAZON_VERDE:
                case ITEM_CAPARAZON_ROJO:
                case ITEM_CAJA_ITEM_FALSA:
                case ESTRELLA_ITEM:
                case ITEM_BOO:
                    return 1;
                default:
                    return 0;
            }
        default:
            return 0;
    }
}

// Objeto final de la caja: el elegido si vale en el modo; si no, el sorteado
static inline s16 truco_objeto_resolver(s16 aleatorio, u8 elegido, s32 modo) {
    return truco_objeto_valido(elegido, modo) ? (s16) elegido : aleatorio;
}

#endif
