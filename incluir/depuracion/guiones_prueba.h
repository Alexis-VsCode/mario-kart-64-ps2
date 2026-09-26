#ifndef DEPURACION_GUIONES_PRUEBA_H
#define DEPURACION_GUIONES_PRUEBA_H

#include <ultra64.h>

#ifdef SMK64_DEV
void inicializar_guiones_prueba(void);
int guion_prueba_activo(void);
void avanzar_guion_prueba(OSContPad *rellenos);
#else
#define inicializar_guiones_prueba() ((void) 0)
#define guion_prueba_activo() 0
#define avanzar_guion_prueba(rellenos) ((void) 0)
#endif

#endif
