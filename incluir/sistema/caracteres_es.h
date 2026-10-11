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
// o la dieresis, los signos de apertura se omiten, los ordinales pasan a
// 'o'/'a' y cada byte >= 0x80 que no es del espanol pasa a '?'.
void quitar_diacriticos(char* destino, int tam, const char* origen);

// Como quitar_diacriticos, pero para la fuente de libdebug (scr_putchar),
// que trae la tabla CP437: los caracteres que tienen glifo en ella pasan a
// su codigo y el resto (A, I, O y U con tilde) a la letra sin tilde. Los
// codigos >= 0x80 se pasan a scr_putchar como unsigned char.
void a_cp437(char* destino, int tam, const char* origen);

// Lector con la forma de leer_glifo (glifos.inc.c): indice del glifo que
// empieza en car (-1 espacio, -2 invalido) y, en *bytes, lo que ocupa
typedef int (*LectorGlifo)(char* car, int* bytes);

// Posicion del primer glifo de cadena que la fuente no dibuja: leer lo da
// por invalido, empieza por C2 o C3 (byte guia de UTF-8 sin pasar a EUC-JP)
// u ocuparia el 0 final. -1 si no hay ninguno. Avanza lo que dice leer, asi
// que un C2/C3 que es el segundo byte de un kana no cuenta. Nunca lee mas
// alla del 0 final.
int primer_byte_invalido(char* cadena, LectorGlifo leer);

#endif
