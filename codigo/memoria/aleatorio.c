#include <juego/segmentos.h>

u16 aleatorio_semilla_16;

#ifdef VERSION_EU
u8 margen_semilla_aleatorio[16];
#else
u8 margen_semilla_aleatorio[216];
#endif
