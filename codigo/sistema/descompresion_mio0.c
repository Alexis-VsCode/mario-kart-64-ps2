#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <fcntl.h>
#endif

#include "sistema/descompresion_mio0.h"
#include "sistema/utilidades.h"

#define MIO0_VERSION "0.1"

#define BIT_OBTENER(buf, bit) ((buf)[(bit) / 8] & (1 << (7 - ((bit) % 8))))

typedef struct
{
   int *indices;
   int reservado;
   int count;
   int start;
} mirada_atras;

#define CANTIDAD_MIRADA_ATRAS 256
#define TAMANIO_INICIALIZACION_MIRADA_ATRAS 128
static mirada_atras *inicializar_mirada_atras(void)
{
   mirada_atras *lb = malloc(CANTIDAD_MIRADA_ATRAS * sizeof(*lb));
   for (int i = 0; i < CANTIDAD_MIRADA_ATRAS; i++) {
      lb[i].reservado = TAMANIO_INICIALIZACION_MIRADA_ATRAS;
      lb[i].indices = malloc(lb[i].reservado * sizeof(*lb[i].indices));
      lb[i].count = 0;
      lb[i].start = 0;
   }
   return lb;
}

static void liberar_mirada_atras(mirada_atras *lb)
{
   for (int i = 0; i < CANTIDAD_MIRADA_ATRAS; i++) {
      free(lb[i].indices);
   }
   free(lb);
}

static inline void empujar_mirada_atras(mirada_atras *lkbk, unsigned char val, int index)
{
   mirada_atras *lb = &lkbk[val];
   if (lb->count == lb->reservado) {
      lb->reservado *= 4;
      lb->indices = realloc(lb->indices, lb->reservado * sizeof(*lb->indices));
   }
   lb->indices[lb->count++] = index;
}

static void BIT_PONER(unsigned char *buf, int bit, int val)
{
   unsigned char mascara = 1 << (7 - (bit % 8));
   unsigned int desplazamiento = bit / 8;
   buf[desplazamiento] = (buf[desplazamiento] & ~(mascara)) | (val ? mascara : 0);
}

static int buscar_mas_largo(const unsigned char *buf, int empezar_desplazamiento, int buscar_max, int *desplazamiento_encontrado, mirada_atras *lkbk)
{
   int longitud_mejor = 0;
   int desplazamiento_mejor = 0;
   int longitud_act;
   int buscar_largo;
   int mas_lejano, apagado, i;
   int lb_idx;
   const unsigned char primer = buf[empezar_desplazamiento];
   mirada_atras *lb = &lkbk[primer];

   mas_lejano = MAX(empezar_desplazamiento - 4096, 0);
   for (lb_idx = lb->start; lb_idx < lb->count && lb->indices[lb_idx] < mas_lejano; lb_idx++) {}
   lb->start = lb_idx;
   for ( ; lb_idx < lb->count && lb->indices[lb_idx] < empezar_desplazamiento; lb_idx++) {
      apagado = lb->indices[lb_idx];
      buscar_largo = MIN(buscar_max, empezar_desplazamiento - apagado);
      for (i = 0; i < buscar_largo; i++) {
         if (buf[empezar_desplazamiento + i] != buf[apagado + i]) {
            break;
         }
      }
      longitud_act = i;
      if (longitud_act == buscar_largo) {
         buscar_largo = buscar_max - longitud_act;
         for (i = 0; i < buscar_largo; i++) {
            if (buf[empezar_desplazamiento + longitud_act + i] != buf[apagado + i]) {
               break;
            }
         }
         longitud_act += i;
      }
      if (longitud_act > longitud_mejor) {
         desplazamiento_mejor = empezar_desplazamiento - apagado;
         longitud_mejor = longitud_act;
      }
   }

   *desplazamiento_encontrado = desplazamiento_mejor;
   return longitud_mejor;
}

int decodificar_cabecera_mio0(const unsigned char *buf, cabecera_t_mio0 *cabeza)
{
   if (!memcmp(buf, "MIO0", 4)) {
      cabeza->tamanio_dest = leer_be_u32(&buf[4]);
      cabeza->desplazamiento_comp = leer_be_u32(&buf[8]);
      cabeza->desplazamiento_sin_comp = leer_be_u32(&buf[12]);
      return 1;
   }
   return 0;
}

void codificar_cabecera_mio0(unsigned char *buf, const cabecera_t_mio0 *cabeza)
{
   memcpy(buf, "MIO0", 4);
   escribir_be_u32(&buf[4], cabeza->tamanio_dest);
   escribir_be_u32(&buf[8], cabeza->desplazamiento_comp);
   escribir_be_u32(&buf[12], cabeza->desplazamiento_sin_comp);
}

int decodificar_mio0(const unsigned char *in, unsigned char *salida, unsigned int *end)
{
   cabecera_t_mio0 cabeza;
   unsigned int escrito_bytes = 0;
   int bit_idx = 0;
   int comp_idx = 0;
   int idx_sin_comp = 0;
   int valido;

   // extract header
   valido = decodificar_cabecera_mio0(in, &cabeza);
   // verify MIO0 header
   if (!valido) {
      return -2;
   }

   while (escrito_bytes < cabeza.tamanio_dest) {
      if (BIT_OBTENER(&in[LONGITUD_CABECERA_MIO0], bit_idx)) {
         salida[escrito_bytes] = in[cabeza.desplazamiento_sin_comp + idx_sin_comp];
         escrito_bytes++;
         idx_sin_comp++;
      } else {
         int idx;
         int longitud;
         int i;
         const unsigned char *vals = &in[cabeza.desplazamiento_comp + comp_idx];
         comp_idx += 2;
         longitud = ((vals[0] & 0xF0) >> 4) + 3;
         idx = ((vals[0] & 0x0F) << 8) + vals[1] + 1;
         for (i = 0; i < longitud; i++) {
            salida[escrito_bytes] = salida[escrito_bytes - idx];
            escrito_bytes++;
         }
      }
      bit_idx++;
   }

   if (end) {
      *end = cabeza.desplazamiento_sin_comp + idx_sin_comp;
   }

   return escrito_bytes;
}

int codificar_mio0(const unsigned char *in, unsigned int longitud, unsigned char *salida)
{
   unsigned char *bit_buf;
   unsigned char *comp_buf;
   unsigned char *buf_sin_comp;
   unsigned int longitud_bit;
   unsigned int desplazamiento_comp;
   unsigned int desplazamiento_sin_comp;
   unsigned int bytes_proc = 0;
   int escrito_bytes;
   int bit_idx = 0;
   int comp_idx = 0;
   int idx_sin_comp = 0;
   mirada_atras *miradas_atras;

   // initialize lookback buffer
   miradas_atras = inicializar_mirada_atras();

   bit_buf = malloc((longitud + 7) / 8);
   comp_buf = malloc(longitud);
   buf_sin_comp = malloc(longitud);
   memset(bit_buf, 0, (longitud + 7) / 8);

   empujar_mirada_atras(miradas_atras, in[0], 0);
   buf_sin_comp[idx_sin_comp] = in[0];
   idx_sin_comp += 1;
   bytes_proc += 1;
   BIT_PONER(bit_buf, bit_idx++, 1);
   while (bytes_proc < longitud) {
      int desplazamiento;
      int longitud_max = MIN(longitud - bytes_proc, 18);
      int coincidencia_mas_largo = buscar_mas_largo(in, bytes_proc, longitud_max, &desplazamiento, miradas_atras);
      empujar_mirada_atras(miradas_atras, in[bytes_proc], bytes_proc);
      if (coincidencia_mas_largo > 2) {
         int desplazamiento_anticipacion;
         int longitud_anticipacion = MIN(longitud - bytes_proc - 1, 18);
         int coincidencia_anticipacion = buscar_mas_largo(in, bytes_proc + 1, longitud_anticipacion, &desplazamiento_anticipacion, miradas_atras);
         if ((coincidencia_mas_largo + 1) < coincidencia_anticipacion) {
            buf_sin_comp[idx_sin_comp] = in[bytes_proc];
            idx_sin_comp++;
            BIT_PONER(bit_buf, bit_idx, 1);
            bytes_proc++;
            coincidencia_mas_largo = coincidencia_anticipacion;
            desplazamiento = desplazamiento_anticipacion;
            bit_idx++;
            empujar_mirada_atras(miradas_atras, in[bytes_proc], bytes_proc);
         }
         for (int i = 1; i < coincidencia_mas_largo; i++) {
            empujar_mirada_atras(miradas_atras, in[bytes_proc + i], bytes_proc + i);
         }
         comp_buf[comp_idx] = (((coincidencia_mas_largo - 3) & 0x0F) << 4) |
                              (((desplazamiento - 1) >> 8) & 0x0F);
         comp_buf[comp_idx + 1] = (desplazamiento - 1) & 0xFF;
         comp_idx += 2;
         BIT_PONER(bit_buf, bit_idx, 0);
         bytes_proc += coincidencia_mas_largo;
      } else {
         buf_sin_comp[idx_sin_comp] = in[bytes_proc];
         idx_sin_comp++;
         BIT_PONER(bit_buf, bit_idx, 1);
         bytes_proc++;
      }
      bit_idx++;
   }

   longitud_bit = ((bit_idx + 7) / 8);

   desplazamiento_comp = ALIGN(LONGITUD_CABECERA_MIO0 + longitud_bit, 4);
   desplazamiento_sin_comp = desplazamiento_comp + comp_idx;
   escrito_bytes = desplazamiento_sin_comp + idx_sin_comp;

   // output header
   memcpy(salida, "MIO0", 4);
   escribir_be_u32(&salida[4], longitud);
   escribir_be_u32(&salida[8], desplazamiento_comp);
   escribir_be_u32(&salida[12], desplazamiento_sin_comp);
   memset(&salida[LONGITUD_CABECERA_MIO0], 0, LONGITUD_CABECERA_MIO0 + longitud_bit);
   memcpy(&salida[LONGITUD_CABECERA_MIO0], bit_buf, longitud_bit);

   memcpy(&salida[desplazamiento_comp], comp_buf, comp_idx);
   memcpy(&salida[desplazamiento_sin_comp], buf_sin_comp, idx_sin_comp);

   free(bit_buf);
   free(comp_buf);
   free(buf_sin_comp);
   liberar_mirada_atras(miradas_atras);

   return escrito_bytes;
}

static FILE *mio0_abierto_salida_archivo(const char *archivo_salida) {
   if (strcmp(archivo_salida, "-") == 0) {
#if defined(_WIN32) || defined(_WIN64)
      _setmode(_fileno(stdout), _BINARIO_O);
#endif
      return stdout;
   } else {
      return fopen(archivo_salida, "wb");
   }
}

int decodificar_archivo_mio0(const char *en_archivo, unsigned long desplazamiento, const char *archivo_salida)
{
   cabecera_t_mio0 cabeza;
   FILE *in;
   FILE *salida;
   unsigned char *en_buf = NULL;
   unsigned char *buf_salida = NULL;
   long tamanio_archivo;
   int val_devuelto = 0;
   size_t leer_bytes;
   int bytes_decodificado;
   int escrito_bytes;
   int valido;

   in = fopen(en_archivo, "rb");
   if (in == NULL) {
      return 1;
   }

   fseek(in, 0, SEEK_END);
   tamanio_archivo = ftell(in);
   en_buf = malloc(tamanio_archivo - desplazamiento);
   fseek(in, desplazamiento, SEEK_SET);

   leer_bytes = fread(en_buf, 1, tamanio_archivo - desplazamiento, in);
   if (leer_bytes != tamanio_archivo - desplazamiento) {
      val_devuelto = 2;
      goto liberar_all;
   }

   // verify header
   valido = decodificar_cabecera_mio0(en_buf, &cabeza);
   if (!valido) {
      val_devuelto = 3;
      goto liberar_all;
   }
   buf_salida = malloc(cabeza.tamanio_dest);

   bytes_decodificado = decodificar_mio0(en_buf, buf_salida, NULL);
   if (bytes_decodificado < 0) {
      val_devuelto = 3;
      goto liberar_all;
   }

   salida = mio0_abierto_salida_archivo(archivo_salida);
   if (salida == NULL) {
      val_devuelto = 4;
      goto liberar_all;
   }

   escrito_bytes = fwrite(buf_salida, 1, bytes_decodificado, salida);
   if (escrito_bytes != bytes_decodificado) {
      val_devuelto = 5;
   }

   if (salida != stdout) {
      fclose(salida);
   }
liberar_all:
   if (buf_salida) {
      free(buf_salida);
   }
   if (en_buf) {
      free(en_buf);
   }
   fclose(in);

   return val_devuelto;
}

int codificar_archivo_mio0(const char *en_archivo, const char *archivo_salida)
{
   FILE *in;
   FILE *salida;
   unsigned char *en_buf = NULL;
   unsigned char *buf_salida = NULL;
   size_t tamanio_archivo;
   size_t leer_bytes;
   int bytes_codificado;
   int escrito_bytes;
   int val_devuelto = 0;

   in = fopen(en_archivo, "rb");
   if (in == NULL) {
      return 1;
   }

   fseek(in, 0, SEEK_END);
   tamanio_archivo = ftell(in);
   fseek(in, 0, SEEK_SET);
   en_buf = malloc(tamanio_archivo);

   leer_bytes = fread(en_buf, 1, tamanio_archivo, in);
   if (leer_bytes != tamanio_archivo) {
      val_devuelto = 2;
      goto liberar_all;
   }

   buf_salida = malloc(LONGITUD_CABECERA_MIO0 + ((tamanio_archivo+7)/8) + tamanio_archivo);

   bytes_codificado = codificar_mio0(en_buf, tamanio_archivo, buf_salida);

   salida = mio0_abierto_salida_archivo(archivo_salida);
   if (salida == NULL) {
      val_devuelto = 4;
      goto liberar_all;
   }

   escrito_bytes = fwrite(buf_salida, 1, bytes_codificado, salida);
   if (escrito_bytes != bytes_codificado) {
      val_devuelto = 5;
   }

   if (salida != stdout) {
      fclose(salida);
   }
liberar_all:
   if (buf_salida) {
      free(buf_salida);
   }
   if (en_buf) {
      free(en_buf);
   }
   fclose(in);

   return val_devuelto;
}

#ifdef MIO0_STANDALONE
typedef struct
{
   char *en_nombre_archivo;
   char *nombre_archivo_salida;
   unsigned int offset;
   int comprimir;
} config_parametro;

static config_parametro config_predeterminado =
{
   NULL,
   NULL,
   0,
   1
};

static void imprimir_uso(void)
{
   ERROR("Usage: mio0 [-c / -d] [-o OFFSET] FILE [OUTPUT]\n"
         "\n"
         "mio0 v" MIO0_VERSION ": MIO0 compression and decompression tool\n"
         "\n"
         "Optional arguments:\n"
         " -c           compress raw data into MIO0 (default: compress)\n"
         " -d           decompress MIO0 into raw data\n"
         " -o OFFSET    starting offset in FILE (default: 0)\n"
         "\n"
         "File arguments:\n"
         " FILE        input file\n"
         " [OUTPUT]    output file (default: FILE.out), \"-\" for stdout\n");
   exit(1);
}

static void analizar_argumentos(int argc, char *argv[], config_parametro *config)
{
   int i;
   int cantidad_archivo = 0;
   if (argc < 2) {
      imprimir_uso();
      exit(1);
   }
   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] != '\0') {
         switch (argv[i][1]) {
            case 'c':
               config->comprimir = 1;
               break;
            case 'd':
               config->comprimir = 0;
               break;
            case 'o':
               if (++i >= argc) {
                  imprimir_uso();
               }
               config->offset = strtoul(argv[i], NULL, 0);
               break;
            default:
               imprimir_uso();
               break;
         }
      } else {
         switch (cantidad_archivo) {
            case 0:
               config->en_nombre_archivo = argv[i];
               break;
            case 1:
               config->nombre_archivo_salida = argv[i];
               break;
            default:
               imprimir_uso();
               break;
         }
         cantidad_archivo++;
      }
   }
   if (cantidad_archivo < 1) {
      imprimir_uso();
   }
}

int main(int argc, char *argv[])
{
   char nombre_archivo_salida[FILENAME_MAX];
   config_parametro config;
   int val_devuelto;

   config = config_predeterminado;
   analizar_argumentos(argc, argv, &config);
   if (config.nombre_archivo_salida == NULL) {
      config.nombre_archivo_salida = nombre_archivo_salida;
      sprintf(config.nombre_archivo_salida, "%s.out", config.en_nombre_archivo);
   }

   if (config.comprimir) {
      val_devuelto = codificar_archivo_mio0(config.en_nombre_archivo, config.nombre_archivo_salida);
   } else {
      val_devuelto = decodificar_archivo_mio0(config.en_nombre_archivo, config.offset, config.nombre_archivo_salida);
   }

   switch (val_devuelto) {
      case 1:
         ERROR("Error opening input file \"%s\"\n", config.en_nombre_archivo);
         break;
      case 2:
         ERROR("Error reading from input file \"%s\"\n", config.en_nombre_archivo);
         break;
      case 3:
         ERROR("Error decoding MIO0 data. Wrong offset (0x%X)?\n", config.offset);
         break;
      case 4:
         ERROR("Error opening output file \"%s\"\n", config.nombre_archivo_salida);
         break;
      case 5:
         ERROR("Error writing bytes to output file \"%s\"\n", config.nombre_archivo_salida);
         break;
   }

   return val_devuelto;
}
#endif
