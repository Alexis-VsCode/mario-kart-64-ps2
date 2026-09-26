#ifndef JUEGO_MK64_H
#define JUEGO_MK64_H

#include <juego/configuracion.h>

#define TAMANIO_MONTON_AUDIO 0x48C00
#define AUDIO_MONTON_INICIALIZACION_TAMANIO 0x2600

#define DOBLE_TAMANIO_EN_64_BIT(size) ((size) * (sizeof(void*) / 4))

#define ANCHO_PANTALLA 320
#define ALTURA_PANTALLA 240

#define TAMANIO_PILA 0x2000

#define ALTURA_BORDE 1

#define NULO_CIRCUITO 0xFF

typedef enum {
     CONTRARRELOJ_DATOS_LUIGI_RACEWAY,
     CONTRARRELOJ_DATOS_MOO_MOO_FARM,
     CONTRARRELOJ_DATOS_KOOPA_BEACH,
     CONTRARRELOJ_DATOS_KALAMARI_DESERT,
     CONTRARRELOJ_DATOS_TOADS_TURNPIKE,
     CONTRARRELOJ_DATOS_FRAPPE_SNOWLAND,
     CONTRARRELOJ_DATOS_CHOCO_MOUNTAIN,
     CONTRARRELOJ_DATOS_MARIO_RACEWAY,
     CONTRARRELOJ_DATOS_WARIO_STADIUM,
     CONTRARRELOJ_DATOS_SHERBET_LAND,
     CONTRARRELOJ_DATOS_ROYAL_RACEWAY,
     CONTRARRELOJ_DATOS_BOWSER_CASTLE,
     CONTRARRELOJ_DATOS_DK_JUNGLE,
     CONTRARRELOJ_DATOS_YOSHI_VALLEY,
     CONTRARRELOJ_DATOS_BANSHEE_BOARDWALK,
     CONTRARRELOJ_DATOS_RAINBOW_ROAD,
     NUM_CONTRARRELOJ_DATOS
} CONTRARRELOJ_INDICE_DATOS;

enum TIPO_SUPERFICIE {
     PREDETERMINADO_SUPERFICIE = -1,
     EN_EL_AIRE,
     ASFALTO,
     TIERRA,
     ARENA,
     PIEDRA,
     NIEVE,
     PUENTE,
     FUERA_PISTA_ARENA,
     PASTO,
     HIELO,
     ARENA_HUMEDO,
     FUERA_PISTA_NIEVE,
     ACANTILADO,
     FUERA_PISTA_TIERRA,
     PISTA_TREN,
     CUEVA,
     PUENTE_CUERDA,
     PUENTE_MADERA,
     MADERA_RAMPA_IMPULSO = 0xFC,
     SALIDA_DE_LIMITES,
     ASFALTO_RAMPA_IMPULSO,
     RAMPA
};

#define GFX_OPCODE_OBTENER(variable_) ((s32) ((variable_) & 0xFF000000))

#ifdef AVOID_UB
#define ALTO_U16_OBTENER_DE_32(variable_) ((u16) ((variable_) >> 16))
#define ALTO_S16_OBTENER_DE_32(variable_) ((s16) ((variable_) >> 16))
#define BAJO_U16_OBTENER_DE_32(variable_) ((u16) ((variable_) & 0xFFFF))
#define BAJO_S16_OBTENER_DE_32(variable_) ((s16) ((variable_) & 0xFFFF))
#define ALTO_U16_CONJUNTO_DE_32(variable_, x) ((variable_) = ((variable_) & 0xFFFF) | ((x) << 16))
#define ALTO_S16_CONJUNTO_DE_32(variable_, x) ((variable_) = ((variable_) & 0xFFFF) | ((x) << 16))
#else
#define ALTO_U16_OBTENER_DE_32(variable_) (((u16*) &(variable_))[0])
#define ALTO_S16_OBTENER_DE_32(variable_) (((s16*) &(variable_))[0])
#define BAJO_U16_OBTENER_DE_32(variable_) (((u16*) &(variable_))[1])
#define BAJO_S16_OBTENER_DE_32(variable_) (((s16*) &(variable_))[1])
#define ALTO_U16_CONJUNTO_DE_32(variable_, x) ((((u16*) &(variable_))[0]) = (x))
#define ALTO_S16_CONJUNTO_DE_32(variable_, x) ((((s16*) &(variable_))[0]) = (x))
#endif

#define BANDERA_COLOR_MACRO(r, g, b, bandera) (r & ~0x3) | (bandera & 0x3), (g & ~0x3) | ((bandera >> 2) & 0x3), b

#endif
