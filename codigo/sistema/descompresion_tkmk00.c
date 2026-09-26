#include <stdint.h>
#include <string.h>

#include "sistema/descompresion_tkmk00.h"
#include "sistema/utilidades.h"
#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <fcntl.h>
#endif

#define TKMK00_VERSION "0.1"

static int32_t t1, t7, t8, t9, s0, s1, s3, s4, s6, s7, v0, v1;

static uint16_t rgba_buf[0x40];
static uint16_t buffer80_u16[0x3F];
static uint16_t buffer_fe_u16[0x3F];
static uint8_t  byte_buffer[0x20];
static uint8_t *algun_ptrs[8];
static uint16_t algun_u16s[8];
static uint32_t algun_u32s[0x80];

static int32_t cabecera6;
static int algun_desplazamiento;
static int algun_banderas;
static const uint8_t *en_ptr;

static void proc_80040A60(void);
static void proc_80040AC8(void);
static void proc_80040BC0(uint32_t, uint32_t*);
static void proc_80040C54(void);
static void proc_80040C94(void);

static int32_t SRL(int32_t val, int monto)
{
   uint32_t v_u = (uint32_t)val;
   v_u >>= monto;
   return (int32_t)v_u;
}

void decodificar_tkmk00(uint8_t *tkmk, uint8_t *tmp_buf, uint8_t *rgba16, int32_t alpha_color)
{
   unsigned desplazamiento;
   unsigned probar_bits;
   int ancho, altura;
   int col, renglon;
   int pixeles;
   int alpha;
   unsigned i;
   uint16_t rgba0;
   uint16_t rgba1;
   uint8_t rojo0, rojo1, verde0, verde1, azul0, azul1;

   ancho = leer_be_u16(&tkmk[0x8]);
   altura = leer_be_u16(&tkmk[0xA]);
   alpha = alpha_color;
   cabecera6 = tkmk[0x6];
   pixeles = ancho * altura;
   memset(rgba_buf, 0xFF, sizeof(rgba_buf));
   memset(rgba16, 0x0, 2 * pixeles);
   memset(tmp_buf, 0x0, pixeles);

   for (i = 0; i < 8; i++) {
       desplazamiento = leer_be_u32(&tkmk[0xC + i*4]);
       if (0 == (cabecera6 & (0x1 << i))) {
          desplazamiento -= 4;
       }
       algun_ptrs[i] = tkmk + desplazamiento;
   }

   memset(algun_u16s, 0, sizeof(algun_u16s));
   algun_desplazamiento = 0x0;
   algun_banderas = leer_be_u32(&tkmk[0x2C]);
   en_ptr = &tkmk[0x30];
   uint32_t val = 0x20;
   proc_80040BC0(DIM(algun_u32s)-4, &val);

   t1 = v0;
   t7 = 0;

   for (renglon = 0; renglon != altura; renglon++) {
      for (col = 0; col != ancho; col++) {
         t9 = leer_be_u16(rgba16);

         if (t9 != 0) {
            s3 = t9 & 0xFFFE;
            t7 = t9;
            if (alpha == s3) {
               escribir_be_u16(rgba16, s3);
               t7 = s3;
            }
         } else {
            v1 = tmp_buf[0];
            v1 += 1;
            proc_80040AC8();

            if (v0 == 0) {
               escribir_be_u16(rgba16, t7);
            } else {
               v1 = 1;
               proc_80040A60();

               if (v0 != 0) {
                  proc_80040C54();

                  s0 = s4;
                  proc_80040C54();

                  s1 = s4;
                  proc_80040C54();

                  rgba0 = 0;
                  rgba1 = 0;
                  if (renglon != 0) {
                     rgba0 = leer_be_u16(rgba16 - (ancho * 2));
                     rgba1 = leer_be_u16(rgba16 - 2);
                  } else {
                     if (col != 0) {
                        rgba1 = leer_be_u16(rgba16 - 2);
                     }
                  }

                  rojo0 = (rgba0 & 0x7C0) >> 6;
                  rojo1 = (rgba1 & 0x7C0) >> 6;
                  t8 = (rojo0 + rojo1) / 2;
                  t9 = s0;
                  proc_80040C94();
                  s0 = t9;

                  v1 = t9 - t8;
                  verde0 = (rgba0 & 0xF800) >> 11;
                  verde1 = (rgba1 & 0xF800) >> 11;
                  t8 = v1 + (verde0 + verde1) / 2;
                  if (t8 >= 0x20) {
                     t8 = 0x1F;
                  } else if (t8 < 0) {
                     t8 = 0;
                  }
                  t9 = s1;
                  proc_80040C94();
                  s1 = t9;

                  azul0 = (rgba0 & 0x3E) >> 1;
                  azul1 = (rgba1 & 0x3E) >> 1;
                  t8 = v1 + (azul0 + azul1) / 2;
                  if (t8 >= 0x20) {
                     t8 = 0x1F;
                  } else if (t8 < 0) {
                     t8 = 0;
                  }
                  t9 = s4;
                  proc_80040C94();

                  t7 = (s1 << 11) | (s0 << 6) | (t9 << 1);
                  if (t7 != alpha) {
                     t7 |= 0x1;
                  }

                  for (i = DIM(rgba_buf) - 1; i > 0; i--) {
                     rgba_buf[i] = rgba_buf[i - 1];
                  }
                  rgba_buf[0] = t7;
               } else {
                  v1 = 6;
                  proc_80040A60();
                  t7 = rgba_buf[v0];
                  if (v0 != 0) {
                     for (i = v0; i > 0; i--) {
                        rgba_buf[i] = rgba_buf[i - 1];
                     }
                     rgba_buf[0] = t7;
                  }
               }
               escribir_be_u16(rgba16, t7);
               probar_bits = 0;
               if (col != 0) {
                  probar_bits |= 0x01;
               }
               if (col < (ancho - 1)) {
                  probar_bits |= 0x02;
               }
               if (col < (ancho - 2)) {
                  probar_bits |= 0x04;
               }
               if (renglon < (altura - 1)) {
                  probar_bits |= 0x08;
               }
               if (renglon < (altura - 2)) {
                  probar_bits |= 0x10;
               }

               if (0x2 == (probar_bits & 0x2)) {
                  tmp_buf[1]++;
               }
               if (0x4 == (probar_bits & 0x4)) {
                  tmp_buf[2]++;
               }
               if (0x9 == (probar_bits & 0x9))  {
                  tmp_buf[ancho - 1]++;
               }
               if (0x8 == (probar_bits & 0x8)) {
                  tmp_buf[ancho]++;
               }
               if (0xA == (probar_bits & 0xA)) {
                  tmp_buf[ancho + 1]++;
               }
               if (0x10 == (probar_bits & 0x10)) {
                  tmp_buf[2*ancho]++;
               }

               v1 = 1;
               proc_80040A60();

               if (v0 != 0) {
                  uint8_t *salida = rgba16;
                  s0 = ancho * 2;
                  s3 = t7 | 0x1;

                  do {
                     v1 = 2;
                     proc_80040A60();
                     if (v0 == 0) {
                        v1 = 1;
                        proc_80040A60();

                        if (v0 == 0) {
                           break;
                        } else {
                           v1 = 1;
                           proc_80040A60();
                           salida += 4;
                           if (v0 == 0) {
                              salida -= 8;
                           }
                        }
                     } else if (v0 == 1) {
                        salida -= 2;
                     } else if (v0 == 3) {
                        salida += 2;
                     }
                     salida += s0;
                     escribir_be_u16(salida, s3);
                  } while (1);
               }
            }
         }
         tmp_buf += 1;
         rgba16 += 2;
      }
   }
}

static void proc_80040A60(void)
{
   unsigned este_desplazamiento;
   este_desplazamiento = algun_desplazamiento + v1;
   t8 = 0x20 - v1;
   v0 = SRL(algun_banderas, t8);
   if (este_desplazamiento < 0x21) {
      if (este_desplazamiento != 0x20) {
         algun_banderas <<= v1;
         algun_desplazamiento += v1;
      } else {
         algun_banderas = leer_be_u32(en_ptr);
         algun_desplazamiento = 0;
         en_ptr += 4;
      }
   } else {
      este_desplazamiento = 0x40;
      algun_banderas = leer_be_u32(en_ptr);
      este_desplazamiento -= v1;
      este_desplazamiento -= algun_desplazamiento;
      algun_desplazamiento -= t8;
      t8 = SRL(algun_banderas, este_desplazamiento);
      v0 |= t8;
      en_ptr += 4;
      algun_banderas <<= algun_desplazamiento;
   }
}

static void proc_80040AC8(void)
{
   uint8_t *s6ptr;
   t8 = SRL(cabecera6, v1);
   t9 = t8 & 0x1;
   s7 = algun_u16s[v1];
   if (t9 == 0) {
      s6ptr = algun_ptrs[v1];
      if (s7 == 0) {
         s6ptr += 4;
         s7 = 0x20;
         algun_ptrs[v1] = s6ptr;
      }
      t9 = leer_be_u32(s6ptr);
      s7 -= 1;
      algun_u16s[v1] = s7;
      v0 = SRL(t9, s7);
      v0 &= 0x1;
   } else {
      s6ptr = algun_ptrs[v1];
      if (s7 == 0) {
         s7 = *s6ptr;
         v0 = 0x100;
         v0 <<= v1;
         if ((s7 & 0x80) == 0x00) {
            v0 = ~v0;
            s7 += 3;
            cabecera6 &= v0;
         } else {
            s7 &= 0x7F;
            s7 += 1;
            cabecera6 |= v0;
         }
         v0 = s6ptr[1];
         s6ptr += 2;
         s7 <<= 3;
         byte_buffer[v1] = v0;
         algun_ptrs[v1] = s6ptr;
      }
      v0 = byte_buffer[v1];
      s7 -= 1;
      algun_u16s[v1] = s7;
      t8 = s7 & 0x7;
      v0 = SRL(v0, t8);
      v0 &= 0x1;
      if (t8 == 0 && s7 != 0) {
         t8 = 0x100;
         s7 = t8 << v1;
         s7 &= cabecera6;
         if (s7 != 0) {
            s7 = s6ptr[0];
            s6ptr += 1;
            byte_buffer[v1] = s7;
            algun_ptrs[v1] = s6ptr;
         }
      }
   }
}

static void proc_80040BC0(uint32_t u32idx, uint32_t *val)
{
   u32idx--;
   v1 = 0;
   proc_80040AC8();

   if (v0 != 0) {
      uint32_t idx;
      algun_u32s[u32idx] = *val;
      (*val)++;
      proc_80040BC0(u32idx, val);
      idx = algun_u32s[u32idx];
      buffer80_u16[idx] = v0;
      proc_80040BC0(u32idx, val);
      idx = algun_u32s[u32idx];
      u32idx++;
      s6 = idx;
      buffer_fe_u16[idx] = v0;
      v0 = s6;
   } else {
      s0 = 0;
      for (s1 = 5; s1 != 0; s1--) {
         v1 = 0;
         proc_80040AC8();
         s0 = v0 + s0 * 2;
      }
      u32idx++;
      v0 = s0;
   }
}

static void proc_80040C54(void)
{
   s4 = t1;
   while (s4 >= 0x20) {
      v1 = 0;
      proc_80040AC8();
      if (v0 == 0) {
         s4 = buffer80_u16[s4];
      } else {
         s4 = buffer_fe_u16[s4];
      }
   }
}

static void proc_80040C94(void)
{
   if (t8 >= 0x10) {
      v0 = (0x1F - t8) * 2;
      if (v0 < t9) {
         v0 = 0x1F;
         t9 = v0 - t9;
      } else {
         v0 = t9 & 0x1;
         t9 = SRL(t9, 1);
         if (v0 != 0) {
            t9 += t8 + 1;
         } else {
            t9 = t8 - t9;
         }
      }
   } else {
      v0 = t8 << 1;
      if (v0 >= t9) {
         v0 = t9 & 0x1;
         t9 = SRL(t9, 1);
         if (v0 != 0) {
            t9 += t8 + 1;
         } else {
            t9 = t8 - t9;
         }
      }
   }
}

#ifdef TKMK00_STANDALONE

#include <stdlib.h>

typedef struct
{
   char *en_nombre_archivo;
   char *nombre_archivo_salida;
   char *nombre_archivo_tmp;
   unsigned int offset;
   int comprimir;
   uint32_t alpha_color;
} config_parametro;

static config_parametro config_predeterminado =
{
   .en_nombre_archivo = NULL,
   .nombre_archivo_salida = NULL,
   .nombre_archivo_tmp = NULL,
   .offset = 0x0,
   .comprimir = 0,
   .alpha_color = 0x01
};

static void imprimir_uso(void)
{
   ERROR("Usage: tkmk00 [-c / -d] [-o OFFSET] FILE [OUTPUT]\n"
         "\n"
         "tkmk00 v" TKMK00_VERSION ": TKMK00 compression and decompression tool\n"
         "\n"
         "Optional arguments:\n"
         " -a           color to use for alpha (default: 0x%02X)\n"
         " -c           compress raw RGBA16 data into TKMK00 (Not functional)\n"
         " -d           decompress TKMK00 into RGBA16 raw data (default: decompress)\n"
         " -o OFFSET    starting offset in FILE (default: 0x%X)\n"
         " -t TMP_FILE  save temp buffer data to TMP_FILE (default: do not save)\n"
         "\n"
         "File arguments:\n"
         " FILE        input file\n"
         " [OUTPUT]    output file (default: FILE.offset.bin)\n",
         config_predeterminado.alpha_color,
         config_predeterminado.offset);
   exit(1);
}

static void analizar_argumentos(int argc, char *argv[], config_parametro *config)
{
   int cantidad_archivo = 0;
   for (int i = 1; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] != '\0') {
         switch (argv[i][1]) {
            case 'a':
               if (++i >= argc) {
                  imprimir_uso();
               }
               config->alpha_color = strtoul(argv[i], NULL, 0);
               break;
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
            case 't':
               if (++i >= argc) {
                  imprimir_uso();
               }
               config->nombre_archivo_tmp = argv[i];
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

static FILE *abrir_archivo_salida(const char *archivo_salida) {
   if (strcmp(archivo_salida, "-") == 0) {
#if defined(_WIN32) || defined(_WIN64)
      _setmode(_fileno(stdout), _BINARIO_O);
#endif
      return stdout;
   } else {
      return fopen(archivo_salida, "wb");
   }
}

static int extraer_tkmk00(const char *en_nombre_archivo, const char *nombre_archivo_salida, const char *nombre_archivo_tmp, uint32_t desplazamiento, uint32_t alpha_color)
{
   FILE *salida;
   uint8_t *en_buf = NULL;
   uint8_t *tmp_buf = NULL;
   uint8_t *buf_salida = NULL;
   size_t escrito_bytes;
   int w, h;
   size_t tamanio_tmp;
   size_t tamanio_salida;
   long en_tamanio;
   int val_devuelto = EXIT_SUCCESS;

   en_tamanio = leer_archivo(en_nombre_archivo, &en_buf);
   if (en_tamanio < 0) {
      ERROR("Error: reading input file \"%s\"\n", en_nombre_archivo);
      return EXIT_FAILURE;
   }

   if (memcmp(&en_buf[desplazamiento], "TKMK00", 6)) {
      ERROR("Error: offset 0x%X does not begin with \"TKMK00\"\n", desplazamiento);
      return EXIT_FAILURE;
   }

   w = leer_be_u16(&en_buf[desplazamiento + 0x8]);
   h = leer_be_u16(&en_buf[desplazamiento + 0xA]);

   tamanio_salida = 2 * w * h;
   tmp_buf = calloc(1, tamanio_salida);
   buf_salida = calloc(1, tamanio_salida);

   // run decoder
   decodificar_tkmk00(&en_buf[desplazamiento], tmp_buf, buf_salida, alpha_color);

   if (nombre_archivo_tmp) {
      tamanio_tmp = w * h;
      escrito_bytes = escribir_archivo(nombre_archivo_tmp, tmp_buf, tamanio_tmp);
      if (escrito_bytes < tamanio_tmp) {
         ERROR("Error writing to temp file \"%s\"\n", nombre_archivo_tmp);
         return EXIT_FAILURE;
      }
   }

   salida = abrir_archivo_salida(nombre_archivo_salida);
   if (salida == NULL) {
      val_devuelto = EXIT_FAILURE;
      goto liberar_all;
   }

   escrito_bytes = fwrite(buf_salida, 1, tamanio_salida, salida);
   if (escrito_bytes != tamanio_salida) {
      ERROR("Error writing to output file \"%s\"\n", nombre_archivo_salida);
      val_devuelto = EXIT_FAILURE;
   }

   if (salida != stdout) {
      fclose(salida);
   }

liberar_all:
   free(tmp_buf);
   free(buf_salida);
   free(en_buf);

   return val_devuelto;
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
      sprintf(config.nombre_archivo_salida, "%s.%06X.bin", config.en_nombre_archivo, config.offset);
   }

   if (config.comprimir) {
      ERROR("TKMK00 compression not implemented yet.\n");
      val_devuelto = EXIT_FAILURE;
   } else {
      val_devuelto = extraer_tkmk00(config.en_nombre_archivo, config.nombre_archivo_salida, config.nombre_archivo_tmp, config.offset, config.alpha_color);
   }

   return val_devuelto;
}
#endif
