#ifndef SISTEMA_UTILIDADES_H
#define SISTEMA_UTILIDADES_H

#include <stdio.h>
#include <stdint.h>

#if defined(_MSC_VER) || defined(__MINGW32__)
  #define FORMATO_TAMANIO_T "%Iu"
#else
  #define FORMATO_TAMANIO_T "%zu"
#endif

#define KB 1024
#define MB (1024 * KB)

#define DIM(S_ARR_) (sizeof(S_ARR_) / sizeof(S_ARR_[0]))

#define MIN(A_, B_) ((A_) < (B_) ? (A_) : (B_))
#define MAX(A_, B_) ((A_) > (B_) ? (A_) : (B_))

#define ALIGN(VAL_, ALINEACION) (((VAL_) + ((ALINEACION) - 1)) & ~((ALINEACION) - 1))

#define leer_be_u32(buf) (unsigned int)(((buf)[0] << 24) + ((buf)[1] << 16) + ((buf)[2] << 8) + ((buf)[3]))
#define leer_le_u32(buf) (unsigned int)(((buf)[1] << 24) + ((buf)[0] << 16) + ((buf)[3] << 8) + ((buf)[2]))
#define escribir_be_u32(buf, val) do { \
   (buf)[0] = ((val) >> 24) & 0xFF; \
   (buf)[1] = ((val) >> 16) & 0xFF; \
   (buf)[2] = ((val) >> 8) & 0xFF; \
   (buf)[3] = (val) & 0xFF; \
} while(0)
#define leer_be_u16(buf) (((buf)[0] << 8) + ((buf)[1]))
#define escribir_be_u16(buf, val) do { \
   (buf)[0] = ((val) >> 8) & 0xFF; \
   (buf)[1] = ((val)) & 0xFF; \
} while(0)

#define fprint_nibble(FP, NIB_) fputc((NIB_) < 10 ? ('0' + (NIB_)) : ('A' + (NIB_) - 0xA), FP)
#define fprint_byte(FP, BYTE_) do { \
    fprint_nibble(FP, (BYTE_) >> 4); \
    fprint_nibble(FP, (BYTE_) & 0x0F); \
  } while(0)
#define imprimir_nibble(NIB_) fprint_nibble(stdout, NIB_)
#define imprimir_byte(BYTE_) fprint_byte(stdout, BYTE_)

#if defined(_MSC_VER) || defined(__MINGW32__)
  #include <direct.h>
  #define mkdir(DIR_, PERM_) _mkdir(DIR_)
  #ifndef strcasecmp
    #define strcasecmp(A, B) stricmp(A, B)
  #endif
#endif

#define ARCHIVOS_DIR_MAX 128
typedef struct
{
   char *archivos[ARCHIVOS_DIR_MAX];
   int count;
} lista_dir;

typedef enum
{
   CRUDO_CODIFICACION,
   CODIFICACION_U8,
   CODIFICACION_U16,
   CODIFICACION_U32,
   CODIFICACION_U64,
} escribir_codificacion;

extern int detalle_g;

#define ERROR(...) fprintf(stderr, __VA_ARGS__)
#define INFO(...) if (detalle_g) printf(__VA_ARGS__)
#define INFO_HEX(...) if (detalle_g) imprimir_hex(__VA_ARGS__)

int leer_be_s16(unsigned char *buf);

float leer_be_f32(unsigned char *buf);

void *llenar_memoria_16_safe(void *m, uint16_t val, size_t cantidad);

int es_potencia2(unsigned int val);

int escribir_salida_fprint(FILE *fp, escribir_codificacion, const uint8_t *buf, int longitud);
void fprint_hex(FILE *fp, const unsigned char *buf, int longitud);
void origen_hex_fprint(FILE *fp, const unsigned char *buf, int longitud);
extern void imprimir_hex(const unsigned char *buf, int longitud);

void intercambiar_bytes(unsigned char *datos, long longitud);

void endian_reversa(unsigned char *datos, long longitud);

long tamanio_archivo_2(const char *nombre_archivo);

void tocar_archivo(const char *nombre_archivo_2);

long leer_archivo(const char *nombre_archivo, unsigned char **datos);

long escribir_archivo(const char *nombre_archivo, unsigned char *datos, long longitud);

void generar_nombre_archivo(const char *en_nombre, char *nombre_salida, char *extension);

char *basename(const char *nombre);

void hacer_dir(const char *nombre_dir);

long copiar_archivo(const char *nombre_orig, const char *nombre_dst);

void ext_lista_dir(const char *dir, const char *extension, lista_dir *lista);

void liberar_lista_dir(lista_dir *lista);

int fines_cad_con(const char *cad, const char *sufijo);

#endif
