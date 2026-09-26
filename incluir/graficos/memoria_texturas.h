#ifndef GRAFICOS_MEMORIA_TEXTURAS_H
#define GRAFICOS_MEMORIA_TEXTURAS_H

#include <tamtypes.h>

typedef struct {
    u8 fmt, siz;
    u16 line;      /* en palabras de 64 bits */
    u16 tmem;      /* en palabras de 64 bits */
    u8 palette;
    u8 cms, cmt;
    u8 masks, maskt;
    u8 shifts, shiftt;
    u16 uls, ult, lrs, lrt;
} TileRdp;

extern TileRdp tiles_rdp[8];

/* Resultado de preparar una textura para el GS */
typedef struct {
    u64 tex0;      /* TBP/TBW/PSM/TW/TH listos; TFX/TCC los pone quien llama */
    u64 clamp;     /* modos y region ya en coordenadas de la textura del GS */
    u32 width, height;  /* region decodificada, en texels */
    float maceta_w, maceta_h;   /* tamano de la textura del GS (1.0 en s/t) */
    float maceta_w_inv, maceta_h_inv;
    float origen_s, origen_t;   /* origen del hueco dentro de la textura del GS */
    u8 envoltura_s, envoltura_t;    /* 1: el eje repite (REGION_REPEAT) */
} InfoTextura;

void tmem_inicializar(void);
void tmem_empezar_frame(void);
void tmem_fijar_imagen(const void *direccion, u32 fmt, u32 siz, u32 ancho);
void tmem_fijar_tile(u32 w0, u32 w1);
void tmem_fijar_tamanio_tile(u32 w0, u32 w1);
void tmem_cargar_bloque(u32 w0, u32 w1);
void tmem_cargar_tile(u32 w0, u32 w1);
void tmem_cargar_tlut(u32 w0, u32 w1);

#define BLANCO_RGB_TMEM 1 /* solo interesa el alfa del texel */
#define TMEM_PARA_RECT  2 /* la pide un rectangulo (G_TEXRECT): ver preparar_impl_tmem */
int preparar_textura(int tile, int tlut_modo, int banderas, InfoTextura *salida);

/* Pasadas */
#define NORMAL_PASADA_TMEM 0
#define REGISTRO_PASADA_TMEM 1
#define REPETICION_PASADA_TMEM 2
void pasada_empezar_tmem(int mode);
/* Cambia con cada carga y con cada pasada */
u32 cargar_serie_tmem(void);
int tmem_pasada_fallido(void);

typedef struct {
    u32 decodificaciones;
    u32 golpes;
    u32 entradas_cache;
    u32 bytes_carga;   /* bytes copiados a la TMEM (perfilado) */
    u32 hash_bytes;   /* bytes de TMEM pasados por el hash (perfilado) */
    u32 golpes_memo;
    u32 bytes_hash_paleta; /* de hash_bytes, los de paletas (perfilado) */
    u32 firmas_paleta_usadas;   /* paletas resueltas con la firma de su carga */
    u32 claves_calculadas;         /* claves calculadas (preparaciones sin memo) */
    u32 firmas_carga_usadas;  /* claves resueltas con la firma de una carga diferida */
    u32 bytes_firmas;     /* bytes de RAM pasados por el hash de firmas de carga */
    u32 golpes_memo_sig;  /* firmas de carga sacadas de la memoria de firmas */
    u32 malo_memo_sig;   /* SMK64_SIGMEMO_CHECK: firmas memorizadas que no coincidian */
} EstadisticasTmem;
extern EstadisticasTmem estadisticas_tmem;
extern u32 loads_malo_tmem;

/* Texturas del circuito (segmento 5) */
void ps2_tmem_estatico_rango(const void *empezar, u32 size);
void escribir_ram_tmem_ps2(const void *dst, u32 size);
/* Otro bloque de texturas descomprimidas con la misma regla */
void ps2_tmem_estatico_bloque(const void *empezar, u32 size, int permanente);
int estatico_origen_tmem(const void *orig_, u32 largo, u32 *generar);
const void *tmem_timg(u32 *ancho_siz_fmt);

#ifdef SMK64_MEDIDOR
void tmem_uso_cache(u32 *entradas, u32 *bytes, u32 *capacidad);
#endif

#endif
