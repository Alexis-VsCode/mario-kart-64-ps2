#include <ultra64.h>
#include <juego/macros.h>
#include <juego/segmentos.h>

#ifdef TARGET_PS2
#define TAMANIO_POOL_MEMORIA (0xAB630 + 0x80000)
#else
#define TAMANIO_POOL_MEMORIA 0xAB630
#endif

u8 pool_memoria[TAMANIO_POOL_MEMORIA];
