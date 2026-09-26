#ifndef SISTEMA_DESCOMPRESION_MIO0_H
#define SISTEMA_DESCOMPRESION_MIO0_H

#define LONGITUD_CABECERA_MIO0 16

typedef struct
{
   unsigned int tamanio_dest;
   unsigned int desplazamiento_comp;
   unsigned int desplazamiento_sin_comp;
} cabecera_t_mio0;

int decodificar_cabecera_mio0(const unsigned char *buf, cabecera_t_mio0 *cabeza);

void codificar_cabecera_mio0(unsigned char *buf, const cabecera_t_mio0 *cabeza);

int decodificar_mio0(const unsigned char *in, unsigned char *salida, unsigned int *end);

int codificar_mio0(const unsigned char *in, unsigned int longitud, unsigned char *salida);

int decodificar_archivo_mio0(const char *en_archivo, unsigned long desplazamiento, const char *archivo_salida);

int codificar_archivo_mio0(const char *en_archivo, const char *archivo_salida);

#endif
