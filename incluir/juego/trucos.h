#ifndef JUEGO_TRUCOS_H
#define JUEGO_TRUCOS_H

// Truco DESBLOQUEAR TODO (CC-22). Las consultas aceptan el truco sin escribir
// nunca el desbloqueo en la partida guardada.

// puntos_150cc: los 2 bits por copa de la partida; 0xFF es oro en las cuatro
static inline int truco_extra_desbloqueado(unsigned char puntos_150cc, int activo) {
    return activo || puntos_150cc == 0xFF;
}

// El fantasma del staff sale si el mejor tiempo iguala o mejora el umbral
static inline int fantasma_staff_disponible(unsigned tiempo, unsigned umbral, int activo) {
    return activo || tiempo <= umbral;
}

// Cursor de cilindrada recortado a la última fila del menú cuando EXTRA desaparece
static inline signed char truco_recortar_cursor(signed char cursor, signed char maximo) {
    return cursor > maximo ? maximo : cursor;
}

// Copia de opciones_port.truco_desbloquear que leen las consultas. Solo cambia
// en truco_desbloquear_aplicar(), al volver al título o al reconstruir el menú:
// el fondo del menú se carga una vez y se vuelve a consultar en cada imagen,
// así que un cambio en caliente mezclaría texturas.
extern int truco_desbloquear_aplicado;
void truco_desbloquear_aplicar(void);

#endif
