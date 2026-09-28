/* Lectura y escritura de archivos para las herramientas del PC (utilidades.h) */
#include <stdio.h>
#include <stdlib.h>

#include "sistema/utilidades.h"

/* Devuelve el tamanio leido o -1; *datos queda en memoria nueva (liberar con free) */
long leer_archivo(const char *nombre_archivo, unsigned char **datos)
{
    FILE *f = fopen(nombre_archivo, "rb");
    long tamanio = -1;

    *datos = NULL;
    if (f == NULL) {
        return -1;
    }
    if (fseek(f, 0, SEEK_END) == 0 && (tamanio = ftell(f)) >= 0 && fseek(f, 0, SEEK_SET) == 0) {
        *datos = malloc(tamanio > 0 ? (size_t) tamanio : 1);
        if (*datos == NULL || fread(*datos, 1, (size_t) tamanio, f) != (size_t) tamanio) {
            free(*datos);
            *datos = NULL;
            tamanio = -1;
        }
    } else {
        tamanio = -1;
    }
    fclose(f);
    return tamanio;
}

/* Devuelve los bytes escritos o -1 */
long escribir_archivo(const char *nombre_archivo, unsigned char *datos, long longitud)
{
    FILE *f = fopen(nombre_archivo, "wb");
    long escritos;

    if (f == NULL) {
        return -1;
    }
    escritos = (long) fwrite(datos, 1, (size_t) longitud, f);
    if (fclose(f) != 0) {
        return -1;
    }
    return escritos;
}
