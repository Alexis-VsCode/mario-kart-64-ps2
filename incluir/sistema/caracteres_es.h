#ifndef CARACTERES_ES_H
#define CARACTERES_ES_H

// Caracteres del espanol que no estan en ASCII. Las cadenas del juego los
// llevan en EUC-JP (JIS X 0212: 8F xx xx); el registro y el panel del port,
// en UTF-8 (C2/C3 xx). Minuscula y mayuscula son el mismo caracter.
typedef enum {
    CAR_ES_NINGUNO,
    CAR_ES_A_AGUDA,
    CAR_ES_E_AGUDA,
    CAR_ES_I_AGUDA,
    CAR_ES_O_AGUDA,
    CAR_ES_U_AGUDA,
    CAR_ES_ENIE,
    CAR_ES_U_DIERESIS,
    CAR_ES_ABRE_EXCLAMACION,
    CAR_ES_ABRE_INTERROGACION,
    CAR_ES_ORDINAL_O,
    CAR_ES_ORDINAL_A,
    CAR_ES_TOTAL
} CaracterEs;

// Signo que va sobre la letra base
typedef enum { MARCA_NINGUNA, MARCA_AGUDA, MARCA_VIRGULILLA, MARCA_DIERESIS } MarcaEs;

// Lee el caracter de c. Si es del espanol devuelve su CaracterEs y deja en
// *bytes lo que ocupa (2 o 3); si no, devuelve CAR_ES_NINGUNO y *bytes = 1.
// *minuscula (si no es NULL) queda en 1 para las minusculas. Nunca lee mas
// alla del 0 final.
int leer_caracter_es(const char* c, int* bytes, int* minuscula);

// Letra o signo ASCII en mayuscula del que sale el caracter: A_AGUDA -> 'A',
// ABRE_EXCLAMACION -> '!', ORDINAL_O -> 'O'
char caracter_es_base(int car);

int caracter_es_marca(int car);

// Copia origen en destino (tam bytes con el 0) sin diacriticos, para las
// salidas que solo tienen ASCII: las letras pierden la tilde, la virgulilla
// o la dieresis, los signos de apertura se omiten y los ordinales pasan a
// 'o'/'a'.
void quitar_diacriticos(char* destino, int tam, const char* origen);

#endif
