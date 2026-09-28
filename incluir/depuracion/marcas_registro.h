#ifndef DEPURACION_MARCAS_REGISTRO_H
#define DEPURACION_MARCAS_REGISTRO_H

/* Palabras que el registro busca en cada linea para volcarla al PC en el
   momento (depuracion.c). Quien las escribe en un mensaje y quien las busca
   usan estas macros. */
#define MARCA_PANICO  "PANICO"
#define MARCA_CUELGUE "cuelgue"
#define MARCA_GIF     "GIF"

/* Grupos del cronometro de fases: se abren con empezar_tiempos_ps2 y el
   panel los consulta por nombre */
#define GRUPO_ARRANQUE    "arranque"
#define GRUPO_CARGA_PISTA "carga de pista"

#endif
