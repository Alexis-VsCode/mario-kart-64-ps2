#include "datos/metadatos_caminos.h"
#include "recursos/pistas/todos_datos_pistas.h"
#include <recursos/datos_ceremonia.h>

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
ComportamientoCPU* cpu_comportamiento_lut[] = {
#include "recursos/pistas/metadatos/cpu_comportamiento_lut.inc.c"

};
#else

#endif

PuntoCaminoPista camino_nulo = { 0x8000, 0x0000, 0x0000, 0x0000 };

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
PuntoCaminoPista* tabla_camino_circuito[][4] = {
#include "recursos/pistas/metadatos/circuito_camino_tabla_desconocido.inc.c"
};

PuntoCaminoPista* tabla_camino_circuito_2[][4] = {
#include "recursos/pistas/metadatos/tabla_camino_circuito.inc.c"
};

s16 cpu_direccion_sensibilidad[] = {
#include "recursos/pistas/metadatos/cpu_direccion_sensibilidad.inc.c"
};

f32 cpu_circuito_maximo_separacion[] = {
#include "recursos/pistas/metadatos/cpu_circuito_maximo_separacion.inc.c"
};

f32 cpu_circuito_minimo_separacion[] = {
#include "recursos/pistas/metadatos/cpu_circuito_minimo_separacion.inc.c"
};
#else

#endif

s16 dato_800DCAF4[] = {
    0x0014, 0x0005, 0x000a, 0x000f, 0x0014, 0x0019, 0x001e, 0x0023, 0x001e, 0x0019, 0x0032,
    0x004b, 0x0064, 0x007d, 0x0096, 0x00af, 0x0028, 0x001e, 0x003c, 0x005a, 0x0078, 0x0096,
    0x00b4, 0x00d2, 0x0032, 0x0028, 0x0050, 0x0078, 0x00a0, 0x00c8, 0x00f0, 0x0118,
};

s16 dato_800DCB34[] = {
    0x0014, 0x0005, 0x000a, 0x000f, 0x0014, 0x0019, 0x001e, 0x0023, 0x001e, 0x0019, 0x002d, 0x0041, 0x005a,
    0x0073, 0x008c, 0x00a5, 0x0028, 0x0003, 0x0006, 0x0010, 0x002e, 0x0031, 0x003b, 0x0059, 0x0032, 0x001e,
    0x003c, 0x003f, 0x0049, 0x004e, 0x006c, 0x008a, 0x000a, 0x0005, 0x000a, 0x000f, 0x0014, 0x0019, 0x001e,
    0x0023, 0x000a, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x000a, 0x0005, 0x0005, 0x0005,
    0x0005, 0x0005, 0x0005, 0x0005, 0x000a, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005,
};

s16* dato_800DCBB4[] = {
#include "recursos/pistas/metadatos/dato_800DCBB4.inc.c"
};

KartBombaAparicion kart_bomba_apariciones[][NUM_KARTS_BOMBA_MAX] = {
#include "recursos/pistas/metadatos/kart_bomba_apariciones.inc.c"
};

#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
struct _struct_g_circuito_camino_tamanios_0_x10 tamanios_camino_circuito[] = {
#include "recursos/pistas/metadatos/tamanios_camino_circuito.inc.c"
};
#else

#endif

s32 dato_800DDB20 = 0x00000000;

s32 dato_800DDB24 = 0x00000001;
