// Donde se dibuja cada tabla y hasta donde puede llegar su tinta.
//   LUGAR(id, tabla, desde, hasta, lineas, impresora, x, escala_x, escala_y, tracking, paso, x_min, x_max, origen)
//     desde..hasta: entradas que se dibujan ahi; 'lineas' seguidas forman un
//     grupo (una debajo de otra, a 'paso' pixeles). x es la posicion final
//     (la de reposo si el item se desliza). La impresora es la de
//     imprimir_texto.inc.c: IZQ (texto0), DER y CENTRO (texto1), MONO (texto2),
//     DEPURACION (fuente de 8x8).
//   PAREJA(tabla_a, desde_a, hasta_a, tabla_b, desde_b, hasta_b, x, escala, hueco, x_min, x_max, origen)
//     dos textos centrados uno junto a otro alrededor de x.
//   SIN_SOLAPE(lugar a la izquierda, lugar a la derecha, margen, origen)
// Origen del limite: S = zona segura del televisor [16, 296]; G = geometria
// (caja, vecino o salto de linea); I = hasta donde llegaba el ingles, cuando
// la posicion depende de otro elemento que no se puede acotar mejor.

// --- Opciones y datos de las pistas --------------------------------------------

LUGAR(L_OPCIONES, menu_opcion_texto, 0, 3, 4, IZQ, 0x32, 0.9f, 1.0f, 0, 0x23, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:146")
LUGAR(L_OPCION_SONIDO, menu_opcion_texto, 1, 1, 1, IZQ, 0x32, 0.9f, 1.0f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:146")
LUGAR(L_SONIDO_VALOR, sonido_nombres_modo, 0, 3, 1, CENTRO, 0xE4, 1.0f, 1.0f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:153")
SIN_SOLAPE(L_OPCION_SONIDO, L_SONIDO_VALOR, 4, "G: el modo de sonido va en la fila de la opcion")
LUGAR(L_BORRAR_TODO, dato_800E7878, 0, 2, 3, IZQ, 0x28, 1.0f, 1.0f, 0, 0x14, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:159")
LUGAR(L_BORRAR_TODO_OPCION, dato_800E7840, 0, 1, 2, IZQ, 0x84, 1.0f, 1.0f, 0, 0x19, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:163")
LUGAR(L_BORRADO, dato_800E7884, 0, 2, 3, IZQ, 0x32, 1.0f, 1.0f, 0, 0x14, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:173")
LUGAR(L_DATOS_BOTONES, datos_menu_texto, 0, 0, 1, DER, 0x125, 0.55f, 0.55f, 0, 0, 78, 297,
      "I: el ingles iba de 78 a 297; dibujar_menus.inc.c:365")
LUGAR(L_DISTANCIA, distancia_texto, 0, 0, 1, IZQ, 0x2D, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:14")
LUGAR(L_LONGITUD, longitudes_circuito, 0, 19, 1, DER, 0xA5, 0.75f, 0.75f, 1, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:15")
SIN_SOLAPE(L_DISTANCIA, L_LONGITUD, 0, "G: la longitud va en la misma fila, alineada a la derecha en 0xA5")
LUGAR(L_REGISTROS_MENU, opcion_menu_texto, 0, 2, 3, IZQ, 0x25, 0.6f, 0.6f, 0, 0xD, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; los datos de la pista van debajo, desde y=0x86; info_pistas_y_tiempos.inc.c:66,69")
LUGAR(L_REGISTROS_CONFIRMAR, borrar_mejor_fantasma_texto, 0, 5, 3, IZQ, 0x1B, 0.65f, 0.65f, 0, 0xD, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; los datos de la pista van debajo, desde y=0x86; info_pistas_y_tiempos.inc.c:92")
LUGAR(L_REGISTROS_OPCION, dato_800E7840, 0, 1, 2, IZQ, 0x43, 0.65f, 0.65f, 0, 0xD, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:103")
LUGAR(L_REGISTROS_ERROR, dato_800E7860, 0, 1, 2, IZQ, 0x2A, 0.75f, 0.75f, 0, 0x10, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:117")

// --- Copas y cilindradas ------------------------------------------------------------

LUGAR(L_COPA_TITULO, nombres_copa, 0, 4, 1, CENTRO, 0xA0, 1.0f, 1.0f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; centrado en 160 al llegar (actualizar_seleccion.inc.c:242), dibujar_menus.inc.c:390")
LUGAR(L_COPA_PRESENTACION, nombres_copa, 0, 4, 1, CENTRO, 0xA0 + 0x3C, 0.85f, 1.0f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; columna final 0xA0 (actualizar_seleccion.inc.c:550), menus_pausa.inc.c:452")
LUGAR(L_COPA_TROFEO, texto_copa, 1, 3, 1, IZQ, 0x28 + 0x20, 0.7f, 0.7f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; columna dato_800E7268, manejar_menus.inc.c:641")
PAREJA(nombres_copa, 0, 3, dato_800E76CC, 0, 3, 0xA0, 1.0f, 10, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
       "S; pausa del gran premio, menus_pausa.inc.c:195-200")
PAREJA(nombres_copa, 0, 4, dato_800E76CC, 0, 3, 0xF5 - 0xA0, 0.6f, 8, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
       "S; resultados, columna final 0xA0 (actualizar_seleccion.inc.c:369), info_pistas_y_tiempos.inc.c:445")
PAREJA(nombres_copa, 0, 4, dato_800E76CC, 0, 3, 0xE0, 0.6f, 8, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
       "S; puntos, columna final 0 (entrada_menus.inc.c:3), info_pistas_y_tiempos.inc.c:563")
PAREJA(nombres_copa, 0, 3, dato_800E76DC, 0, 3, 0xA0, 1.0f, 10, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
       "S; ceremonia, posicion final dato_800E7480[0], menus_pausa.inc.c:756-762")

// --- Pausa y resultados --------------------------------------------------------------

LUGAR(L_PAUSA_CONTRARRELOJ, boton_pausa_texto, 0, 4, 5, IZQ, 0x69, 0.75f, 0.75f, 0, 13, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; dato_800E8538, menus_pausa.inc.c:141")
// Versus y batalla dibujan las entradas 0, 2, 3 y 4
LUGAR(L_PAUSA_4J_IZQUIERDA, boton_pausa_texto, 0, 0, 1, IZQ, 0x28 - 2, 0.75f, 0.75f, 0, 13, ZONA_SEGURA_IZQ, 160,
      "G: cuadrante del jugador 1 y 3 en 4 jugadores (x < 160), dato_800E8540, menus_pausa.inc.c:171,235")
LUGAR(L_PAUSA_4J_IZQUIERDA_2, boton_pausa_texto, 2, 4, 3, IZQ, 0x28 - 2, 0.75f, 0.75f, 0, 13, ZONA_SEGURA_IZQ, 160,
      "G: cuadrante del jugador 1 y 3 en 4 jugadores (x < 160), dato_800E8540, menus_pausa.inc.c:171,235")
LUGAR(L_PAUSA_4J_DERECHA, boton_pausa_texto, 0, 0, 1, IZQ, 0xB2 - 2, 0.75f, 0.75f, 0, 13, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; jugadores 2 y 4, dato_800E8540, menus_pausa.inc.c:171,235")
LUGAR(L_PAUSA_4J_DERECHA_2, boton_pausa_texto, 2, 4, 3, IZQ, 0xB2 - 2, 0.75f, 0.75f, 0, 13, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; jugadores 2 y 4, dato_800E8540, menus_pausa.inc.c:171,235")
// Gran premio: entradas 0 y 4
LUGAR(L_PAUSA_GRAN_PREMIO, boton_pausa_texto, 0, 0, 1, IZQ, 0x78, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; dato_800E85C0, menus_pausa.inc.c:206")
LUGAR(L_PAUSA_GRAN_PREMIO_2, boton_pausa_texto, 4, 4, 1, IZQ, 0x78, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; dato_800E85C0, menus_pausa.inc.c:206")
LUGAR(L_FIN_CONTRARRELOJ, boton_pausa_texto, 1, 6, 6, IZQ, 0x69, 0.75f, 0.75f, 0, 0xD, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; menus_pausa.inc.c:352")
LUGAR(L_FIN_CONTRARRELOJ_PANEL, boton_pausa_texto, 1, 6, 6, IZQ, 0xB2, 0.75f, 0.75f, 0, 0xD, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; columna final 0 (entrada_menus.inc.c:3), info_pistas_y_tiempos.inc.c:719-723")
LUGAR(L_REPETICION, boton_pausa_texto, 5, 5, 1, IZQ, 0xBF, 0.8f, 0.8f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; menus_pausa.inc.c:304")
// Fin del gran premio: entradas 1 y 4
LUGAR(L_FIN_GRAN_PREMIO, boton_pausa_texto, 1, 1, 1, IZQ, 0x8C, 1.0f, 1.0f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; menus_pausa.inc.c:474,480")
LUGAR(L_FIN_GRAN_PREMIO_2, boton_pausa_texto, 4, 4, 1, IZQ, 0x8C, 1.0f, 1.0f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; menus_pausa.inc.c:474,480")
LUGAR(L_FIN_VERSUS, boton_pausa_texto, 1, 4, 4, IZQ, 0x69, 0.8f, 0.8f, 0, 0xF, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; menus_pausa.inc.c:540")
LUGAR(L_CLASIFICACION, dato_800E7778, 0, 1, 1, CENTRO, 0xA0, 1.0f, 1.0f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; menus_pausa.inc.c:505,509")
LUGAR(L_VICTORIA_IZQUIERDA, texto_perder_victoria, 0, 1, 1, CENTRO, 0x30, 0.65f, 1.0f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; dato_800E7380[0], menus_pausa.inc.c:621")
LUGAR(L_VICTORIA_DERECHA, texto_perder_victoria, 0, 1, 1, CENTRO, 0x109, 0.65f, 1.0f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; dato_800E7380[1], menus_pausa.inc.c:621")
LUGAR(L_RECORDS_DATOS, texto_tiempo_mejor, 0, 1, 1, IZQ, 0xA0, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:18,25")
LUGAR(L_RECORDS_META, texto_tiempo_mejor, 0, 1, 1, IZQ, 0xB4 - 0xA0, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; columna final 0xA0 (actualizar_seleccion.inc.c:764), info_pistas_y_tiempos.inc.c:652,659")
LUGAR(L_RECORDS_PAUSA, texto_tiempo_mejor, 0, 1, 1, CENTRO, 0x9D, 0.8f, 0.8f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; menus_pausa.inc.c:117,128,328,339")
LUGAR(L_RECORDS_CAJA_1, texto_tiempo_mejor, 0, 0, 1, IZQ, 0x17 + 8, 0.6f, 0.8f, 0, 0, ZONA_SEGURA_IZQ, 0x17 + 0x64 - 2,
      "G: caja de 100 px en x=0x17 (dato_800E7258, manejar_menus.inc.c:518); dibujar_menus.inc.c:320")
LUGAR(L_RECORDS_CAJA_2, texto_tiempo_mejor, 1, 1, 1, IZQ, 0xC5 + 8, 0.8f, 0.8f, 0, 0, ZONA_SEGURA_IZQ, 0xC5 + 0x64 - 2,
      "G: caja de 100 px en x=0xC5 (dato_800E7258, manejar_menus.inc.c:518); dibujar_menus.inc.c:320")
LUGAR(L_VUELTAS_META, texto_tiempo_vuelta, 0, 0, 1, CENTRO, 0xA0 + 0x46, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; columna final 0xA0, info_pistas_y_tiempos.inc.c:645")
LUGAR(L_VUELTAS_PANEL, texto_tiempo_vuelta, 0, 0, 1, CENTRO, 0x55, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; columna final 0, info_pistas_y_tiempos.inc.c:688")
LUGAR(L_PREFIJO_META, texto_tiempo_prefijo, 0, 3, 1, DER, 0xA0 + 0x17 + 0x21, 0.7f, 0.7f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; columna final 0xA0, info_pistas_y_tiempos.inc.c:833")
LUGAR(L_PREFIJO_PANEL, texto_tiempo_prefijo, 0, 3, 1, DER, 0x26 + 0x21, 0.7f, 0.7f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; columna final 0, info_pistas_y_tiempos.inc.c:833")
LUGAR(L_PUESTO_RECORD, dato_800E7744, 0, 5, 1, MONO, 0x14, 0.65f, 0.65f, 2, 0, -1000, 37,
      "I: relativo a la columna; las cifras de los minutos empiezan en 0x27 (menus_pausa.inc.c:32-51)")

// --- Memory Card y fantasmas ---------------------------------------------------------

LUGAR(L_MC_RANURA_1, dato_800E7890, 0, 15, 4, IZQ, 0x23, 0.8f, 0.8f, 0, 0x14, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:195")
LUGAR(L_MC_RANURA_2, dato_800E78D0, 0, 11, 3, IZQ, 0x32, 0.9f, 0.9f, 0, 0x14, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:183")
LUGAR(L_MC_NO_SE_PUEDE, dato_800E7900, 0, 5, 3, IZQ, 0x41, 0.9f, 0.9f, 0, 0x14, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:203")
LUGAR(L_MC_CREANDO, dato_800E7A48, 0, 2, 3, IZQ, 0x50, 1.0f, 1.0f, 0, 0x14, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:210")
LUGAR(L_MC_PREGUNTA, dato_800E7920, 0, 1, 1, CENTRO, 0xA0, 0.6f, 0.6f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:232")
LUGAR(L_MC_TARJETA_1, dato_800E7918, 0, 1, 1, CENTRO, 0x5C, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ, 0xA0,
      "G: la segunda tarjeta se centra en 0xDE; info_pistas_y_tiempos.inc.c:235")
LUGAR(L_MC_TARJETA_2, dato_800E7918, 0, 1, 1, CENTRO, 0x5C + 0x82, 0.75f, 0.75f, 0, 0, 0xA0, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:235")
LUGAR(L_MC_AVISO, dato_800E7928, 0, 1, 2, CENTRO, 0xA0, 0.8f, 0.8f, 0, 0x14, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:270")
LUGAR(L_MC_SALIR, dato_800E7930, 0, 0, 1, IZQ, 0x6E, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ, 0x6E + 0x32 - 2,
      "G: la segunda opcion empieza en x=0xA0; info_pistas_y_tiempos.inc.c:312")
LUGAR(L_MC_COPIAR, dato_800E7930, 1, 1, 1, IZQ, 0x6E + 0x32, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:312")
LUGAR(L_MC_COPIANDO, dato_800E7938, 0, 1, 1, CENTRO, 0xA0, 1.0f, 1.0f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:320")
LUGAR(L_MC_SIN_DATOS_COPIA, dato_800E7A44, 0, 0, 1, IZQ, 0x2A + 0x89, 0.5f, 0.5f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; info_pistas_y_tiempos.inc.c:256")
LUGAR(L_MC_SIN_DATOS_META, dato_800E7A44, 0, 0, 1, IZQ, 0xBB, 0.45f, 0.45f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; columna final 0, info_pistas_y_tiempos.inc.c:750")
LUGAR(L_MC_SIN_DATOS_PAUSA, dato_800E7A44, 0, 0, 1, IZQ, 0x69, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; menus_pausa.inc.c:380")
LUGAR(L_MC_AVISO_GRABAR, dato_800E7940, 0, 15, 4, IZQ, 0x23, 0.65f, 0.65f, 0, 0xD, ZONA_SEGURA_IZQ, 0x122,
      "G: caja negra de 0x1E a 0x122 (dibujar_menus.inc.c:729); dibujar_menus.inc.c:733")
LUGAR(L_FANTASMA_PANEL, dato_800E798C, 0, 41, 7, IZQ, 0xA2, 0.6f, 0.6f, 0, 0xD, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:736")
LUGAR(L_FANTASMA_PAUSA, dato_800E798C, 0, 41, 7, IZQ, 0x4D, 0.8f, 0.8f, 0, 0xD, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; menus_pausa.inc.c:365")
LUGAR(L_ELEGIR_ARCHIVO_PANEL, dato_800E7A3C, 0, 1, 2, IZQ, 0xA5, 0.7f, 0.7f, 0, 0xD, ZONA_SEGURA_IZQ, 298,
      "I: el ingles llegaba a 298; info_pistas_y_tiempos.inc.c:743")
LUGAR(L_ELEGIR_ARCHIVO_PAUSA, dato_800E7A3C, 0, 1, 2, IZQ, 0x5A, 0.8f, 0.8f, 0, 0xD, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; menus_pausa.inc.c:373")
LUGAR(L_CREANDO_PANEL, dato_800E7A48, 0, 2, 3, IZQ, 0xAA, 0.8f, 0.8f, 0, 0xD, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:762")
LUGAR(L_CREANDO_PAUSA, dato_800E7A48, 0, 2, 3, IZQ, 0x64, 0.8f, 0.8f, 0, 0xD, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; menus_pausa.inc.c:392")
LUGAR(L_SOBRESCRIBIR_PANEL, dato_800E7A60, 0, 2, 3, IZQ, 0xA3, 0.67f, 0.67f, 0, 0xD, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; info_pistas_y_tiempos.inc.c:770")
LUGAR(L_SOBRESCRIBIR_PAUSA, dato_800E7A60, 0, 2, 3, IZQ, 0x55, 0.8f, 0.8f, 0, 0xD, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; menus_pausa.inc.c:399")
LUGAR(L_GRABAR_OPCION_PANEL, dato_800E7A6C, 0, 1, 2, IZQ, 0xC8, 0.75f, 0.75f, 0, 0xF, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; columna final 0, info_pistas_y_tiempos.inc.c:774")
LUGAR(L_GRABAR_OPCION_PAUSA, dato_800E7A6C, 0, 1, 2, IZQ, 0x7D, 0.8f, 0.8f, 0, 0xF, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; menus_pausa.inc.c:403")
LUGAR(L_GRABANDO_PANEL, dato_800E7A74, 0, 2, 3, IZQ, 0xA3, 0.67f, 0.67f, 0, 0xD, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; info_pistas_y_tiempos.inc.c:780")
LUGAR(L_GRABANDO_PAUSA, dato_800E7A74, 0, 2, 3, IZQ, 0x55, 0.8f, 0.8f, 0, 0xD, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; menus_pausa.inc.c:409")
LUGAR(L_ERROR_GRABAR_PANEL, dato_800E7A80, 0, 1, 2, IZQ, 0xAA, 0.75f, 0.75f, 0, 0xD, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; info_pistas_y_tiempos.inc.c:786")
LUGAR(L_ERROR_GRABAR_PAUSA, dato_800E7A80, 0, 1, 2, IZQ, 0x5D, 0.8f, 0.8f, 0, 0xD, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; menus_pausa.inc.c:415")
LUGAR(L_NO_SE_PUEDE_GRABAR, dato_800E7A34, 0, 1, 2, IZQ, 0xC0, 0.45f, 0.45f, 0, 0xA, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; menus_pausa.inc.c:741")

// --- Ceremonia -----------------------------------------------------------------------

PAREJA(dato_800E7A88, 0, 0, dato_800E7A88, 1, 3, 0x9B, 0.75f, 5, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
       "S; posicion final dato_800E7480[1], menus_pausa.inc.c:774-779")
LUGAR(L_SUERTE, dato_800E7A98, 0, 0, 1, CENTRO, 0x9B, 0.75f, 0.75f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; posicion final dato_800E7480[1], menus_pausa.inc.c:772")
LUGAR(L_FELICIDADES, dato_800E7A9C, 0, 1, 1, CENTRO, 0xA0, 1.3f, 1.3f, 0, 0, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; posicion final dato_800E7480[2], menus_pausa.inc.c:794")
PAREJA(texto_lugar, 0, 0, texto_lugar, 1, 8, 0x9B, 1.2f, 5, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
       "S; posicion final dato_800E7480[3], menus_pausa.inc.c:807-812")

// --- Intro de la batalla, avisos y banner --------------------------------------------

LUGAR(L_ANUNCIO_FANTASMA, texto_menu_anuncio_fantasma, 0, 0, 1, CENTRO, 0xA0, 0.85f, 0.85f, 0, 0, -1000, 1000,
      "cruza la pantalla de derecha a izquierda (entrada_menus.inc.c:705-732): sin limite")
LUGAR(L_SIN_MANDO, mando_sin_texto, 0, 1, 2, CENTRO, 0x9F, 0.75f, 0.75f, 0, 13, ZONA_SEGURA_IZQ, ZONA_SEGURA_DER,
      "S; escala 0.75 y paso 0x12 * 0.75, dibujar_menus.inc.c:15,112-116")
LUGAR(L_BATALLA_TITULO, introduccion_batalla_texto, 0, 0, 1, CENTRO, 0x98, 1.0f, 1.0f, 0, 0, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; manejar_menus.inc.c:632")
LUGAR(L_BATALLA_REGLAS, introduccion_batalla_texto, 1, 2, 2, IZQ, 0x17, 0.7f, 0.8f, 0, 0x12, ZONA_SEGURA_IZQ,
      ZONA_SEGURA_DER, "S; manejar_menus.inc.c:633-634")

// --- Fuente de depuracion --------------------------------------------------------------

LUGAR(L_DEPURACION_PERSONAJE, nombres_personaje_depuracion, 0, 7, 1, DEPURACION, 0xAA, 1.0f, 1.0f, 0, 0, 0, 303,
      "G: salto de linea en x >= 296 (kart_bomba_y_depuracion.inc.c:171); imprimir_texto.inc.c:658")
LUGAR(L_DEPURACION_PANTALLA, depuracion_pantalla_modo_nombres, 0, 4, 1, DEPURACION, 0xAA, 1.0f, 1.0f, 0, 0, 0, 303,
      "G: salto de linea en x >= 296; imprimir_texto.inc.c:656")
LUGAR(L_DEPURACION_SONIDO, depuracion_sonido_modo_nombres, 0, 3, 1, DEPURACION, 0xAA, 1.0f, 1.0f, 0, 0, 0, 303,
      "G: salto de linea en x >= 296; imprimir_texto.inc.c:660")
LUGAR(L_DEPURACION_PISTA, nombres_circuito_depuracion, 0, 9, 1, DEPURACION, 0xB9, 1.0f, 1.0f, 0, 0, 0, 303,
      "G: salto de linea en x >= 296; imprimir_texto.inc.c:653")
LUGAR(L_DEPURACION_PISTA_2, nombres_circuito_depuracion, 10, 19, 1, DEPURACION, 0xB9 + 8, 1.0f, 1.0f, 0, 0, 0, 303,
      "G: salto de linea en x >= 296; imprimir_texto.inc.c:653")
