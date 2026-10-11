// Truco OBJETO (carrera/truco_objeto.h)
#include <stdio.h>

#include "carrera/truco_objeto.h"

static int s_fallos, s_comprobaciones;

static void comprobar(const char *caso, int obtenido, int esperado) {
    s_comprobaciones++;
    if (obtenido != esperado) {
        s_fallos++;
        printf("FALLO %s: %d, se esperaba %d\n", caso, obtenido, esperado);
    }
}

int main(void) {
    int i;

    // Sin truco sale la ruleta; con truco, el elegido en GP y VS
    comprobar("GP sin truco", truco_objeto_resolver(7, 0, GRAN_PREMIO), 7);
    comprobar("GP estrella", truco_objeto_resolver(7, ESTRELLA_ITEM, GRAN_PREMIO), ESTRELLA_ITEM);
    comprobar("VS super hongo", truco_objeto_resolver(7, ITEM_SUPER_HONGO, VERSUS), ITEM_SUPER_HONGO);
    comprobar("VS espinoso", truco_objeto_resolver(1, AZUL_ITEM_CAPARAZON_ESPINOSO, VERSUS), AZUL_ITEM_CAPARAZON_ESPINOSO);

    // Batalla: solo los objetos que la ruleta de batalla puede dar
    comprobar("batalla rayo", truco_objeto_resolver(3, RAYO_ITEM, BATALLA), 3);
    comprobar("batalla boo", truco_objeto_resolver(3, ITEM_BOO, BATALLA), ITEM_BOO);
    comprobar("batalla hongo", truco_objeto_resolver(3, HONGO_ITEM, BATALLA), 3);
    comprobar("batalla banana", truco_objeto_resolver(3, ITEM_BANANA, BATALLA), ITEM_BANANA);
    for (i = 1; i <= TRUCO_OBJETO_MAX; i++) {
        int valido = i <= ITEM_CAPARAZON_ROJO || i == ITEM_CAJA_ITEM_FALSA || i == ESTRELLA_ITEM || i == ITEM_BOO;

        s_comprobaciones++;
        if (truco_objeto_valido(i, BATALLA) != valido) {
            s_fallos++;
            printf("FALLO válido en batalla %d: se esperaba %d\n", i, valido);
        }
    }

    // Contrarreloj y modos desconocidos: siempre la ruleta
    comprobar("contrarreloj", truco_objeto_resolver(4, ESTRELLA_ITEM, CONTRARRELOJ), 4);
    comprobar("modo 7", truco_objeto_resolver(4, ESTRELLA_ITEM, 7), 4);

    // Inválidos: el hongo doble, fuera de rango y ninguno
    comprobar("GP hongo doble", truco_objeto_resolver(4, HONGO_DOBLE_ITEM, GRAN_PREMIO), 4);
    comprobar("VS 16", truco_objeto_resolver(4, 16, VERSUS), 4);
    comprobar("GP 255", truco_objeto_resolver(4, 255, GRAN_PREMIO), 4);
    comprobar("GP ninguno", truco_objeto_valido(NINGUNO_ITEM, GRAN_PREMIO), 0);

    printf("%d comprobaciones, %d %s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "fallo" : "fallos");
    return s_fallos != 0;
}
