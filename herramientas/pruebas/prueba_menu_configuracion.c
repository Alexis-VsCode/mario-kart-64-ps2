// Navegación y valores del menú CONFIGURACIÓN Y TRUCOS (menu_configuracion.h)
#include <stdio.h>
#include <string.h>

#include "menus/menu_configuracion.h"

static int s_fallos, s_comprobaciones;

static void comprobar(const char *que, int obtenido, int esperado) {
    s_comprobaciones++;
    if (obtenido != esperado) {
        s_fallos++;
        printf("FALLO %s: %d, se esperaba %d\n", que, obtenido, esperado);
    }
}

static void comprobar_numero(int v, const char *esperado) {
    char buf[4];

    config_texto_numero(v, buf);
    s_comprobaciones++;
    if (strcmp(buf, esperado) != 0) {
        s_fallos++;
        printf("FALLO número %d: «%s», se esperaba «%s»\n", v, buf, esperado);
    }
}

int main(void) {
    OpcionesPort o;
    int v, pasos;

    // Las filas se paran en los extremos
    comprobar("VOLVER +1", config_mover_fila(CONFIG_FILA_VOLVER, 1, CONFIG_FILAS), CONFIG_FILA_VOLVER);
    comprobar("fila 0 -1", config_mover_fila(0, -1, CONFIG_FILAS), 0);
    comprobar("fila 0 +1", config_mover_fila(0, 1, CONFIG_FILAS), 1);
    comprobar("VOLVER -1", config_mover_fila(CONFIG_FILA_VOLVER, -1, CONFIG_FILAS), CONFIG_FILA_VOLVER - 1);
    comprobar("VOLVER es la novena", CONFIG_FILA_VOLVER, 8);

    // Los valores con nombre dan la vuelta en los dos sentidos
    comprobar("NO +1", config_ciclar_valor(0, 1, 2), 1);
    comprobar("SÍ +1", config_ciclar_valor(1, 1, 2), 0);
    comprobar("NO -1", config_ciclar_valor(0, -1, 2), 1);
    comprobar("PANORÁMICO +1", config_ciclar_valor(FORMATO_PANORAMICO, 1, 3), FORMATO_NORMAL);
    comprobar("NORMAL -1", config_ciclar_valor(FORMATO_NORMAL, -1, 3), FORMATO_PANORAMICO);
    comprobar("CON BANDAS +1", config_ciclar_valor(FORMATO_CON_BANDAS, 1, 3), FORMATO_PANORAMICO);

    // La posición no da la vuelta
    comprobar("limitar 40", config_limitar(40, -32, 32), 32);
    comprobar("limitar -40", config_limitar(-40, -32, 32), -32);
    comprobar("limitar 32", config_limitar(32, -32, 32), 32);
    comprobar("limitar -5", config_limitar(-5, -32, 32), -5);

    // OBJETO: 0 a 15 sin el 13, con vuelta
    comprobar("objeto 0 -1", truco_objeto_siguiente_menu(0, -1), 15);
    comprobar("objeto 12 +1", truco_objeto_siguiente_menu(12, 1), 14);
    comprobar("objeto 14 -1", truco_objeto_siguiente_menu(14, -1), 12);
    comprobar("objeto 15 +1", truco_objeto_siguiente_menu(15, 1), 0);
    comprobar("objeto 0 +1", truco_objeto_siguiente_menu(0, 1), 1);
    // Una vuelta entera pasa por 15 valores y vuelve al principio
    v = 0;
    pasos = 0;
    do {
        v = truco_objeto_siguiente_menu((unsigned char) v, 1);
        pasos++;
        comprobar("la vuelta no pasa por el 13", v != TRUCO_OBJETO_PROHIBIDO, 1);
    } while (v != 0 && pasos < 40);
    comprobar("pasos de una vuelta", pasos, 15);

    // config_cambiar sobre cada fila
    opciones_por_defecto(&o, 0);
    comprobar("antiparpadeo cambia", config_cambiar(&o, CONFIG_FILA_ANTIPARPADEO, 1), 1);
    comprobar("antiparpadeo SÍ", o.antiparpadeo, 1);
    comprobar("antiparpadeo vuelve", (config_cambiar(&o, CONFIG_FILA_ANTIPARPADEO, 1), o.antiparpadeo), 0);
    o.desplaz_x = DESPLAZ_X_MAX;
    comprobar("X en el tope no cambia", config_cambiar(&o, CONFIG_FILA_POSICION_X, 1), 0);
    comprobar("X sigue en el tope", o.desplaz_x, DESPLAZ_X_MAX);
    comprobar("X baja", (config_cambiar(&o, CONFIG_FILA_POSICION_X, -1), o.desplaz_x), DESPLAZ_X_MAX - 1);
    o.desplaz_y = -DESPLAZ_Y_MAX;
    comprobar("Y en el tope no cambia", config_cambiar(&o, CONFIG_FILA_POSICION_Y, -1), 0);
    comprobar("Y sube", (config_cambiar(&o, CONFIG_FILA_POSICION_Y, 1), o.desplaz_y), -DESPLAZ_Y_MAX + 1);
    comprobar("formato -1", (config_cambiar(&o, CONFIG_FILA_FORMATO, -1), o.formato), FORMATO_PANORAMICO);
    comprobar("desbloquear", (config_cambiar(&o, CONFIG_FILA_DESBLOQUEAR, 1), o.truco_desbloquear), 1);
    o.truco_objeto = 12;
    comprobar("objeto salta el 13", (config_cambiar(&o, CONFIG_FILA_OBJETO, 1), o.truco_objeto), 14);
    comprobar("200cc", (config_cambiar(&o, CONFIG_FILA_200CC, -1), o.truco_200cc), 1);
    comprobar("rivales", (config_cambiar(&o, CONFIG_FILA_RIVALES, 1), o.truco_rivales), 1);
    comprobar("VOLVER no cambia nada", config_cambiar(&o, CONFIG_FILA_VOLVER, 1), 0);

    // Números de la posición: la fuente no tiene otro signo que - y +
    comprobar_numero(0, "0");
    comprobar_numero(5, "+5");
    comprobar_numero(32, "+32");
    comprobar_numero(-7, "-7");
    comprobar_numero(-16, "-16");

    printf("%d comprobaciones, %d %s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "fallo" : "fallos");
    return s_fallos != 0;
}
