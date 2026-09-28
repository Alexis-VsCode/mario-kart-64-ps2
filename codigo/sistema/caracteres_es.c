#include <stddef.h>

#include "sistema/caracteres_es.h"

// Codigos de cada caracter en mayuscula. La minuscula es la misma fila de
// JIS X 0212 con el segundo byte + 1 (AA -> AB) y, en UTF-8, el ultimo byte
// + 0x20; los signos (fila A2 / C2) no tienen minuscula.
typedef struct {
    unsigned char euc2, euc3;   // 8F euc2 euc3
    unsigned char utf1, utf2;   // utf1 utf2
    char base;
    unsigned char marca;
} CodigoEs;

static const CodigoEs codigos[CAR_ES_TOTAL] = {
    [CAR_ES_A_AGUDA] = { 0xAA, 0xA1, 0xC3, 0x81, 'A', MARCA_AGUDA },
    [CAR_ES_E_AGUDA] = { 0xAA, 0xB1, 0xC3, 0x89, 'E', MARCA_AGUDA },
    [CAR_ES_I_AGUDA] = { 0xAA, 0xBF, 0xC3, 0x8D, 'I', MARCA_AGUDA },
    [CAR_ES_O_AGUDA] = { 0xAA, 0xD1, 0xC3, 0x93, 'O', MARCA_AGUDA },
    [CAR_ES_U_AGUDA] = { 0xAA, 0xE2, 0xC3, 0x9A, 'U', MARCA_AGUDA },
    [CAR_ES_ENIE] = { 0xAA, 0xD0, 0xC3, 0x91, 'N', MARCA_VIRGULILLA },
    [CAR_ES_U_DIERESIS] = { 0xAA, 0xE4, 0xC3, 0x9C, 'U', MARCA_DIERESIS },
    [CAR_ES_ABRE_EXCLAMACION] = { 0xA2, 0xC2, 0xC2, 0xA1, '!', MARCA_NINGUNA },
    [CAR_ES_ABRE_INTERROGACION] = { 0xA2, 0xC4, 0xC2, 0xBF, '?', MARCA_NINGUNA },
    [CAR_ES_ORDINAL_O] = { 0xA2, 0xEB, 0xC2, 0xBA, 'O', MARCA_NINGUNA },
    [CAR_ES_ORDINAL_A] = { 0xA2, 0xEC, 0xC2, 0xAA, 'A', MARCA_NINGUNA },
};

#define EUC_SS3 0x8F
#define FILA_MAYUSCULAS 0xAA
#define DESPLAZAMIENTO_MINUSCULA_UTF8 0x20

static int es_letra(int car) {
    return codigos[car].base >= 'A' && codigos[car].base <= 'Z' && codigos[car].euc2 == FILA_MAYUSCULAS;
}

int leer_caracter_es(const char* c, int* bytes, int* minuscula) {
    const unsigned char* b = (const unsigned char*) c;
    int car;

    for (car = CAR_ES_NINGUNO + 1; car < CAR_ES_TOTAL; car++) {
        const CodigoEs* k = &codigos[car];
        int letra = es_letra(car);
        // Paso 1: EUC-JP, tres bytes (b[1] y b[2] no se leen si hay un 0 antes)
        if (b[0] == EUC_SS3 && b[1] != 0 && b[2] == k->euc3 &&
            (b[1] == k->euc2 || (letra && b[1] == k->euc2 + 1))) {
            *bytes = 3;
            if (minuscula != NULL) {
                *minuscula = (b[1] != k->euc2);
            }
            return car;
        }
        // Paso 2: UTF-8, dos bytes
        if (b[0] == k->utf1 && (b[1] == k->utf2 || (letra && b[1] == k->utf2 + DESPLAZAMIENTO_MINUSCULA_UTF8))) {
            *bytes = 2;
            if (minuscula != NULL) {
                *minuscula = (b[1] != k->utf2);
            }
            return car;
        }
    }
    *bytes = 1;
    if (minuscula != NULL) {
        *minuscula = 0;
    }
    return CAR_ES_NINGUNO;
}

char caracter_es_base(int car) {
    return (car > CAR_ES_NINGUNO && car < CAR_ES_TOTAL) ? codigos[car].base : '?';
}

int caracter_es_marca(int car) {
    return (car > CAR_ES_NINGUNO && car < CAR_ES_TOTAL) ? codigos[car].marca : MARCA_NINGUNA;
}

void quitar_diacriticos(char* destino, int tam, const char* origen) {
    int escritos = 0;

    while (*origen != 0 && escritos < tam - 1) {
        int bytes, minuscula;
        int car = leer_caracter_es(origen, &bytes, &minuscula);
        if (car == CAR_ES_NINGUNO) {
            destino[escritos++] = *origen;
        } else if (car == CAR_ES_ORDINAL_O || car == CAR_ES_ORDINAL_A) {
            destino[escritos++] = codigos[car].base - 'A' + 'a';
        } else if (car != CAR_ES_ABRE_EXCLAMACION && car != CAR_ES_ABRE_INTERROGACION) {
            destino[escritos++] = minuscula ? codigos[car].base - 'A' + 'a' : codigos[car].base;
        }
        origen += bytes;
    }
    if (tam > 0) {
        destino[escritos] = 0;
    }
}
