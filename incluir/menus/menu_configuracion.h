#ifndef MENUS_MENU_CONFIGURACION_H
#define MENUS_MENU_CONFIGURACION_H

#include "sistema/opciones_port.h"

// Navegación y valores del menú CONFIGURACIÓN Y TRUCOS. Lógica pura:
// el menú la llama con la fila elegida y el sentido (+1 derecha o X, -1
// izquierda), y la prueba del PC la comprueba sin el juego.

enum FilaConfiguracion {
    CONFIG_FILA_ANTIPARPADEO = 0,
    CONFIG_FILA_POSICION_X,
    CONFIG_FILA_POSICION_Y,
    CONFIG_FILA_FORMATO,
    CONFIG_FILA_DESBLOQUEAR,
    CONFIG_FILA_OBJETO,
    CONFIG_FILA_200CC,
    CONFIG_FILA_RIVALES,
    CONFIG_FILA_VOLVER,
    CONFIG_FILAS
};

// Color de la columna de valores: AMARILLO_TEXTO (enum COLOR_ID), opaco
// como las etiquetas. VERDE_TEXTO sale semitransparente y no se leía.
#define CONFIG_COLOR_VALOR 3

// Columna izquierda de un valor alineado a la derecha en «derecha». El modo de
// texto alineado a la derecha del juego dibuja tenue; con esta columna el valor
// se dibuja en el modo opaco de las etiquetas.
static inline int config_columna_valor(int derecha, int ancho, float escala)
{
    return derecha - (int) (ancho * escala);
}

// Como OPCIONES: arriba y abajo se paran en la primera y la última fila
static inline int config_mover_fila(int fila, int delta, int num_filas)
{
    fila += delta;
    if (fila < 0) {
        return 0;
    }
    if (fila >= num_filas) {
        return num_filas - 1;
    }
    return fila;
}

// Los valores con nombre dan la vuelta en los dos sentidos
static inline int config_ciclar_valor(int v, int delta, int num_valores)
{
    v = (v + delta) % num_valores;
    return v < 0 ? v + num_valores : v;
}

static inline int config_limitar(int v, int min, int max)
{
    if (v < min) {
        return min;
    }
    if (v > max) {
        return max;
    }
    return v;
}

// 0 (ruleta normal) a TRUCO_OBJETO_MAX con vuelta, sin el objeto prohibido.
// No filtra por modo: el truco ya cae en la ruleta si no vale en batalla.
static inline unsigned char truco_objeto_siguiente_menu(unsigned char v, int dir)
{
    v = (unsigned char) config_ciclar_valor(v, dir, TRUCO_OBJETO_MAX + 1);
    if (v == TRUCO_OBJETO_PROHIBIDO) {
        v = (unsigned char) config_ciclar_valor(v, dir, TRUCO_OBJETO_MAX + 1);
    }
    return v;
}

// Cambia el valor de la fila en el sentido delta; 1 si cambió algo
static inline int config_cambiar(OpcionesPort *o, int fila, int delta)
{
    u8 *interruptor;
    int antes;

    switch (fila) {
        case CONFIG_FILA_POSICION_X:
            antes = o->desplaz_x;
            o->desplaz_x = (s8) config_limitar(antes + delta, -DESPLAZ_X_MAX, DESPLAZ_X_MAX);
            return o->desplaz_x != antes;
        case CONFIG_FILA_POSICION_Y:
            antes = o->desplaz_y;
            o->desplaz_y = (s8) config_limitar(antes + delta, -DESPLAZ_Y_MAX, DESPLAZ_Y_MAX);
            return o->desplaz_y != antes;
        case CONFIG_FILA_FORMATO:
            o->formato = (u8) config_ciclar_valor(o->formato, delta, FORMATO_PANORAMICO + 1);
            return 1;
        case CONFIG_FILA_OBJETO:
            o->truco_objeto = truco_objeto_siguiente_menu(o->truco_objeto, delta);
            return 1;
        case CONFIG_FILA_ANTIPARPADEO:
            interruptor = &o->antiparpadeo;
            break;
        case CONFIG_FILA_DESBLOQUEAR:
            interruptor = &o->truco_desbloquear;
            break;
        case CONFIG_FILA_200CC:
            interruptor = &o->truco_200cc;
            break;
        case CONFIG_FILA_RIVALES:
            interruptor = &o->truco_rivales;
            break;
        default:
            return 0;
    }
    *interruptor = (u8) config_ciclar_valor(*interruptor, delta, 2);
    return 1;
}

// Posición con signo explícito («+5», «-16», «0»): la fuente solo tiene - y +
static inline void config_texto_numero(int v, char buf[4])
{
    int i = 0;

    if (v != 0) {
        buf[i++] = v < 0 ? '-' : '+';
    }
    if (v < 0) {
        v = -v;
    }
    if (v >= 10) {
        buf[i++] = (char) ('0' + v / 10);
    }
    buf[i++] = (char) ('0' + v % 10);
    buf[i] = '\0';
}

#endif
