#include <stdio.h>
#include <string.h>

#include "sistema/caracteres_es.h"

static int s_fallos, s_comprobaciones;

#define COMPROBACION(cond, ...)                                                                                        \
    do {                                                                                                               \
        s_comprobaciones++;                                                                                            \
        if (!(cond)) {                                                                                                 \
            s_fallos++;                                                                                                \
            printf("FALLO %s:%d: ", __FILE__, __LINE__);                                                               \
            printf(__VA_ARGS__);                                                                                       \
            printf("\n");                                                                                              \
        }                                                                                                              \
    } while (0)

typedef struct {
    const char* euc;
    const char* utf8;
    int car;
    int minuscula;
    char base;
    int marca;
} Caso;

static const Caso casos[] = {
    { "\x8f\xaa\xa1", "\xc3\x81", CAR_ES_A_AGUDA, 0, 'A', MARCA_AGUDA },
    { "\x8f\xaa\xb1", "\xc3\x89", CAR_ES_E_AGUDA, 0, 'E', MARCA_AGUDA },
    { "\x8f\xaa\xbf", "\xc3\x8d", CAR_ES_I_AGUDA, 0, 'I', MARCA_AGUDA },
    { "\x8f\xaa\xd1", "\xc3\x93", CAR_ES_O_AGUDA, 0, 'O', MARCA_AGUDA },
    { "\x8f\xaa\xe2", "\xc3\x9a", CAR_ES_U_AGUDA, 0, 'U', MARCA_AGUDA },
    { "\x8f\xaa\xd0", "\xc3\x91", CAR_ES_ENIE, 0, 'N', MARCA_VIRGULILLA },
    { "\x8f\xaa\xe4", "\xc3\x9c", CAR_ES_U_DIERESIS, 0, 'U', MARCA_DIERESIS },
    { "\x8f\xab\xa1", "\xc3\xa1", CAR_ES_A_AGUDA, 1, 'A', MARCA_AGUDA },
    { "\x8f\xab\xb1", "\xc3\xa9", CAR_ES_E_AGUDA, 1, 'E', MARCA_AGUDA },
    { "\x8f\xab\xbf", "\xc3\xad", CAR_ES_I_AGUDA, 1, 'I', MARCA_AGUDA },
    { "\x8f\xab\xd1", "\xc3\xb3", CAR_ES_O_AGUDA, 1, 'O', MARCA_AGUDA },
    { "\x8f\xab\xe2", "\xc3\xba", CAR_ES_U_AGUDA, 1, 'U', MARCA_AGUDA },
    { "\x8f\xab\xd0", "\xc3\xb1", CAR_ES_ENIE, 1, 'N', MARCA_VIRGULILLA },
    { "\x8f\xab\xe4", "\xc3\xbc", CAR_ES_U_DIERESIS, 1, 'U', MARCA_DIERESIS },
    { "\x8f\xa2\xc2", "\xc2\xa1", CAR_ES_ABRE_EXCLAMACION, 0, '!', MARCA_NINGUNA },
    { "\x8f\xa2\xc4", "\xc2\xbf", CAR_ES_ABRE_INTERROGACION, 0, '?', MARCA_NINGUNA },
    { "\x8f\xa2\xeb", "\xc2\xba", CAR_ES_ORDINAL_O, 0, 'O', MARCA_NINGUNA },
    { "\x8f\xa2\xec", "\xc2\xaa", CAR_ES_ORDINAL_A, 0, 'A', MARCA_NINGUNA },
};

static void probar_lectura(void) {
    int i, bytes, minuscula;
    for (i = 0; i < (int) (sizeof(casos) / sizeof(casos[0])); i++) {
        const Caso* c = &casos[i];
        int car = leer_caracter_es(c->euc, &bytes, &minuscula);
        COMPROBACION(car == c->car && bytes == 3 && minuscula == c->minuscula, "EUC caso %d: car %d bytes %d", i, car,
                     bytes);
        car = leer_caracter_es(c->utf8, &bytes, &minuscula);
        COMPROBACION(car == c->car && bytes == 2 && minuscula == c->minuscula, "UTF-8 caso %d: car %d bytes %d", i, car,
                     bytes);
        COMPROBACION(caracter_es_base(c->car) == c->base, "base del caso %d", i);
        COMPROBACION(caracter_es_marca(c->car) == c->marca, "marca del caso %d", i);
    }
    COMPROBACION(leer_caracter_es("\xc3\x81", &bytes, NULL) == CAR_ES_A_AGUDA, "minuscula puede ser NULL");
}

static void probar_no_espanol(void) {
    // ASCII, kana EUC-JP y secuencias cortadas: no son del espanol y ocupan 1 byte
    static const char* entradas[] = { "A", " ", "\xa4\xa2", "\xa1\xbc", "\x8f", "\x8f\xaa", "\x8f\xaa\xa2", "\xc3",
                                      "\xc3\xa0", "\xc2\xa2", "" };
    int i, bytes, minuscula;
    for (i = 0; i < (int) (sizeof(entradas) / sizeof(entradas[0])); i++) {
        int car = leer_caracter_es(entradas[i], &bytes, &minuscula);
        COMPROBACION(car == CAR_ES_NINGUNO && bytes == 1, "entrada %d: car %d bytes %d", i, car, bytes);
    }
}

static void probar_quitar_diacriticos(void) {
    char salida[64];
    quitar_diacriticos(salida, sizeof(salida), "despu\xc3\xa9s, \xc2\xbf" "cu\xc3\xa1ntos? \xc3\x91" "AND\xc3\x9a");
    COMPROBACION(strcmp(salida, "despues, cuantos? NANDU") == 0, "UTF-8: '%s'", salida);
    quitar_diacriticos(salida, sizeof(salida), "\x8f\xa2\xc2" "CAMPE\x8f\xaa\xd1N! 1.\x8f\xa2\xeb");
    COMPROBACION(strcmp(salida, "CAMPEON! 1.o") == 0, "EUC-JP: '%s'", salida);
    quitar_diacriticos(salida, 5, "ABCD\xc3\x89" "FG");
    COMPROBACION(strcmp(salida, "ABCD") == 0, "corte por tamanio: '%s'", salida);
    quitar_diacriticos(salida, sizeof(salida), "fin cortado \xc3");
    COMPROBACION(strcmp(salida, "fin cortado ?") == 0, "secuencia incompleta al final: '%s'", salida);
    quitar_diacriticos(salida, sizeof(salida), "a\xc3" "b \xe2\x82\xac");
    COMPROBACION(strcmp(salida, "a?b ???") == 0, "bytes que no son del espanol: '%s'", salida);
}

int main(void) {
    probar_lectura();
    probar_no_espanol();
    probar_quitar_diacriticos();
    printf("%d comprobaciones, %d fallos\n", s_comprobaciones, s_fallos);
    return s_fallos != 0;
}
