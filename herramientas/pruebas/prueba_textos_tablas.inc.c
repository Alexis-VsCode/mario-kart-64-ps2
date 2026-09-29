// Tablas de texto que revisa prueba_textos.c.
//   TABLA(tabla, entradas originales, primera y ultima entrada con texto, fuente, permisos, estado)
//   PUNTERO(char*, fuente, permisos, estado)   ARREGLO(char[], fuente, permisos, estado)
// Las entradas originales son las de la version en ingles: hay indices con
// paso fijo (grupos de 3, 4 o 7 lineas), asi que la cantidad no puede cambiar.
// PENDIENTE marca una tabla que falta traducir; cuenta como fallo esperado y
// TABLAS_PENDIENTES solo puede bajar. Una tabla ES pasa la lista negra y
// tiene un texto esperado por entrada.

#define TABLAS_PENDIENTES 0

// Copas, pistas y personajes
TABLA(nombres_copa, 9, 0, 8, FUENTE_MENU, 0, ES)
TABLA(nombres_circuito, 20, 0, 19, FUENTE_MENU, 0, ES)
TABLA(duplicar_nombres_circuito, 20, 0, 19, FUENTE_MENU, 0, ES)
TABLA(duplicar_nombres_circuito_2, 20, 0, 19, FUENTE_MENU, 0, ES)
TABLA(nombres_circuito_depuracion, 20, 0, 19, FUENTE_DEPURACION, 0, ES)
TABLA(texto_copa, 4, 0, 3, FUENTE_MENU, 0, ES)
TABLA(nombres_personaje_depuracion, 8, 0, 7, FUENTE_DEPURACION, 0, ES)
TABLA(dato_800E76A8, 9, 0, 8, FUENTE_MENU, PERMITE_RAYA, ES)
TABLA(dato_800E76CC, 4, 0, 3, FUENTE_MENU, PERMITE_CC, ES)
TABLA(dato_800E76DC, 4, 0, 3, FUENTE_MENU, PERMITE_CC, ES)
TABLA(depuracion_pantalla_modo_nombres, 5, 0, 4, FUENTE_DEPURACION, 0, ES)
TABLA(depuracion_sonido_modo_nombres, 4, 0, 3, FUENTE_DEPURACION, 0, ES)
TABLA(textos_menu_depuracion, 8, 0, 7, FUENTE_DEPURACION, 0, ES)

// Opciones, sonido y datos de las pistas
TABLA(sonido_nombres_modo, 4, 0, 3, FUENTE_MENU, 0, ES)
TABLA(menu_opcion_texto, 4, 0, 3, FUENTE_MENU, 0, ES)
TABLA(dato_800E7878, 3, 0, 2, FUENTE_MENU, 0, ES)
TABLA(dato_800E7884, 3, 0, 2, FUENTE_MENU, 0, ES)
ARREGLO(datos_menu_texto, FUENTE_MENU, PERMITE_ASTERISCO, ES)
ARREGLO(distancia_texto, FUENTE_MENU, 0, ES)
TABLA(longitudes_circuito, 20, 0, 19, FUENTE_MENU, 0, ES)
TABLA(opcion_menu_texto, 3, 0, 2, FUENTE_MENU, 0, ES)
TABLA(dato_800E7840, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(borrar_mejor_fantasma_texto, 6, 0, 5, FUENTE_MENU, 0, ES)
TABLA(dato_800E7860, 2, 0, 1, FUENTE_MENU, 0, ES)

// Pausa, tiempos y resultados
TABLA(texto_perder_victoria, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(texto_tiempo_mejor, 2, 0, 1, FUENTE_MENU, 0, ES)
PUNTERO(texto_tiempo_vuelta, FUENTE_MENU, 0, ES)
TABLA(texto_tiempo_prefijo, 4, 0, 3, FUENTE_MENU, 0, ES)
TABLA(dato_800E7744, 6, 0, 5, FUENTE_MENU, 0, ES)
TABLA(boton_pausa_texto, 7, 0, 6, FUENTE_MENU, 0, ES)
TABLA(dato_800E7778, 2, 0, 1, FUENTE_MENU, 0, ES)
PUNTERO(texto_resultados, FUENTE_MENU, 0, ES)
PUNTERO(texto_ronda, FUENTE_MENU, 0, ES)
PUNTERO(texto_puntos_piloto, FUENTE_MENU, 0, ES)
TABLA(texto_puesto_versus, 3, 0, 2, FUENTE_MENU, PERMITE_RAYA, ES)

// Intro de la batalla, avisos y banner del fantasma
ARREGLO(texto_menu_anuncio_fantasma, FUENTE_MENU, 0, ES)
TABLA(mando_sin_texto, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(introduccion_batalla_texto, 3, 0, 2, FUENTE_MENU, 0, ES)

// Memory Card y fantasmas
TABLA(dato_800E7890, 16, 0, 15, FUENTE_MENU, 0, ES)
TABLA(dato_800E78D0, 12, 0, 11, FUENTE_MENU, 0, ES)
TABLA(dato_800E7900, 6, 0, 5, FUENTE_MENU, 0, ES)
TABLA(dato_800E7918, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(dato_800E7920, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(dato_800E7928, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(dato_800E7930, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(dato_800E7938, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(dato_800E7940, 16, 0, 15, FUENTE_MENU, 0, ES)
TABLA(dato_800E7980, 3, 0, 2, FUENTE_MENU, 0, ES)
TABLA(dato_800E798C, 42, 0, 41, FUENTE_MENU, 0, ES)
TABLA(dato_800E7A34, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(dato_800E7A3C, 2, 0, 1, FUENTE_MENU, 0, ES)
PUNTERO(dato_800E7A44, FUENTE_MENU, 0, ES)
TABLA(dato_800E7A48, 3, 0, 2, FUENTE_MENU, 0, ES)
TABLA(dato_800E7A54, 3, 0, 2, FUENTE_MENU, 0, ES)
TABLA(dato_800E7A60, 3, 0, 2, FUENTE_MENU, 0, ES)
TABLA(dato_800E7A6C, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(dato_800E7A74, 3, 0, 2, FUENTE_MENU, 0, ES)
TABLA(dato_800E7A80, 2, 0, 1, FUENTE_MENU, 0, ES)

// Ceremonia y creditos (la segunda mitad de los creditos es la japonesa, que
// la version americana no dibuja)
TABLA(dato_800E7A88, 4, 0, 3, FUENTE_MENU, 0, ES)
PUNTERO(dato_800E7A98, FUENTE_MENU, 0, ES)
TABLA(dato_800E7A9C, 2, 0, 1, FUENTE_MENU, 0, ES)
TABLA(texto_lugar, 9, 0, 8, FUENTE_MENU, 0, ES)
TABLA(texto_creditos, 126, 0, 62, FUENTE_MENU, 0, ES)
