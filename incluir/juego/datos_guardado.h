#ifndef JUEGO_DATOS_GUARDADO_H
#define JUEGO_DATOS_GUARDADO_H

#include <juego/estructuras_comunes.h>

typedef struct {
    u8 registros[6][3];
    u8 bytes_desconocido[5];
    u8 checksum;
} CircuitoContrarrelojRegistros;

typedef struct {
    CircuitoContrarrelojRegistros registros_circuito[4];
} CopaContrarrelojRegistros;

typedef struct {
    CopaContrarrelojRegistros registros_copa[4];
} TodosCircuitoContrarrelojRegistros;

typedef struct {
    u8 tres_vueltas_mejor[8][3];
    u8 vueltas_simples_mejor[8][3];
    u8 bytes_desconocido[8];
} MejorSoloContrarrelojRegistros;

typedef struct {
    u8 gran_premio_puntos[4];
    u8 sonido_modo;
} InfoGuardado;

typedef struct {
    InfoGuardado info_guardado;
    u8 checksum[3];
} Cosas;

typedef struct {
     TodosCircuitoContrarrelojRegistros todos_circuito_contrarreloj_registros;
     Cosas main;
     MejorSoloContrarrelojRegistros mejor_solo_contrarreloj_registros[2];
     Cosas respaldo;
} DatosGuardado;

extern DatosGuardado datos_guardado;

#endif
