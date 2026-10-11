// Truco DESBLOQUEAR TODO (juego/trucos.h)
#include <stdio.h>

#include "juego/trucos.h"

static int s_fallos, s_comprobaciones;

static void comprobar(const char *caso, int obtenido, int esperado) {
    s_comprobaciones++;
    if (obtenido != esperado) {
        s_fallos++;
        printf("FALLO %s: %d, se esperaba %d\n", caso, obtenido, esperado);
    }
}

int main(void) {
    // EXTRA: hace falta el oro en las 4 copas de 150cc (0xFF) o el truco
    comprobar("extra 0x00 sin truco", truco_extra_desbloqueado(0x00, 0), 0);
    comprobar("extra 0x00 con truco", truco_extra_desbloqueado(0x00, 1), 1);
    comprobar("extra 0xFF sin truco", truco_extra_desbloqueado(0xFF, 0), 1);
    comprobar("extra 0xFF con truco", truco_extra_desbloqueado(0xFF, 1), 1);
    comprobar("extra 0xFE sin truco", truco_extra_desbloqueado(0xFE, 0), 0);

    // Fantasma del staff: el umbral cuenta como superado
    comprobar("fantasma igual al umbral", fantasma_staff_disponible(10700, 10700, 0), 1);
    comprobar("fantasma umbral+1", fantasma_staff_disponible(10701, 10700, 0), 0);
    comprobar("fantasma umbral+1 con truco", fantasma_staff_disponible(10701, 10700, 1), 1);
    comprobar("fantasma sin tiempo con truco", fantasma_staff_disponible(0xFFFFF, 9000, 1), 1);

    // Cursor de cilindrada: si EXTRA desaparece, baja a la última fila que queda
    comprobar("cursor en EXTRA sin EXTRA", truco_recortar_cursor(3, 2), 2);
    comprobar("cursor en el máximo", truco_recortar_cursor(2, 2), 2);
    comprobar("cursor por debajo", truco_recortar_cursor(1, 2), 1);
    comprobar("cursor en columna de una fila", truco_recortar_cursor(3, 0), 0);

    printf("%d comprobaciones, %d %s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "fallo" : "fallos");
    return s_fallos != 0;
}
