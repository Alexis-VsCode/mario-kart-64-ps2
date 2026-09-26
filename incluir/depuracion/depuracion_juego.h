#ifndef DEPURACION_DEPURACION_JUEGO_H
#define DEPURACION_DEPURACION_JUEGO_H

#include <ultra64.h>
#include <juego/definiciones.h>

#define DVDL 0
#if DVDL

#define TAMANIO_BUFFER_PERSONAJE 200

#define POSICION_TEXTO_Y -0x8
#define POSICION_TEXTO_X -0x5

#define NUMERO_DECIMAL_PANTALLA 0x1
#define NUMERO_HEXADECIMAL_PANTALLA 0x2
#define NUMERO_OCTAL_PANTALLA 0x4
#define NUMERO_BINARIO_PANTALLA 0x8
#define NUMERO_CON_SIGNO_PANTALLA 0x10
#define FLOTANTE_PANTALLA_COMO_TIPO 0x20
#define FLOTANTE_PANTALLA_CON_REDONDEO 0x40
#define NUMERO_FLOTANTE_PANTALLA 0x80

#define HEXADECIMAL 16
#define DECIMAL 10
#define OCTAL 8
#define BINARIO 2

typedef struct {
    char* nombre_variable;
    void* puntero_variable;
    u8 tamanio_variable;
    u8 bandera_variable;
    char buffer[TAMANIO_BUFFER_PERSONAJE];
    char* buffer_personaje;
} atributos_vigilancia_variable;

extern atributos_vigilancia_variable principal_variable_vigilancia_lista[];

void mostrar_dvdl(void);

#endif

#endif
