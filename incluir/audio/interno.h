#ifndef AUDIO_INTERNO_H
#define AUDIO_INTERNO_H

#include <ultra64.h>

#define JUGADORES_SECUENCIA 4
#define CANALES_SECUENCIA 48
#define CAPAS_SECUENCIA 64

#define MAX_CAPAS 4
#define MAX_CANALES 16

#define SIN_CAPA ((struct CapaCanalSecuencia*) (-1))

#define SILENCIO_COMPORTAMIENTO_PARADA_GUION 0x80
#define SILENCIO_COMPORTAMIENTO_PARADA_NOTAS 0x40
#define SUAVIZAR_COMPORTAMIENTO_SILENCIO 0x20

#define ESTADO_JUGADOR_SECUENCIA_0 0
#define SECUENCIA_JUGADOR_ESTADO_FUNDIDO_SALIDA 1
#define ESTADO_JUGADOR_SECUENCIA_2 2
#define ESTADO_JUGADOR_SECUENCIA_3 3
#define ESTADO_JUGADOR_SECUENCIA_4 4

#define NOTA_PRIORIDAD_DESACTIVADO 0
#define DETENIENDO_PRIORIDAD_NOTA 1
#define MIN_PRIORIDAD_NOTA 2
#define PREDETERMINADO_PRIORIDAD_NOTA 3

#define TATUMS_POR_PULSO 48

#define CODEC_ADPCM 0
#define CODEC_S8 1
#define SALTEAR_CODEC 2

#define ESCALA_TEMPO TATUMS_POR_PULSO

#define FLOTANTE_US(x) x##f
#define US_FLOAT2(x) x

#define CONVERSION_FLOTANTE(x) (f32)(s32)(x)

#ifdef __sgi
#define printf_vacio
#else
#define printf_vacio(...)
#endif

#define printf_vacio_eu_0(mens) printf_vacio(mens)
#define printf_vacio_eu_1(mens, a) printf_vacio(mens, a)
#define printf_vacio_eu_2(mens, a, b) printf_vacio(mens, a, b)
#define printf_vacio_eu_3(mens, a, b, c) printf_vacio(mens, a, b, c)

struct PoolNota;

struct ItemListaAudio {
    struct ItemListaAudio* prev;
    struct ItemListaAudio* next;
    union {
        void* value;
        s32 count;
    } u;
    struct PoolNota* pool;
};

struct PoolNota {
    struct ItemListaAudio desactivado;
    struct ItemListaAudio decayendo;
    struct ItemListaAudio soltando;
    struct ItemListaAudio active;
};

struct EstadoVibrato {
     struct CanalSecuencia* sec_canal;
     u32 time;
     s16* curva;
     f32 extension;
     f32 tasa;
     u8 active;
     u16 temporizador_cambio_tasa;
     u16 temporizador_cambio_extension;
     u16 delay;
};

struct Portamento {
    u8 mode;
    f32 act;
    f32 speed;
    f32 extension;
};

struct EnvolventeAdsr {
    s16 delay;
    s16 arg;
};

struct BucleAdpcm {
    u32 start;
    u32 end;
    u32 count;
    u32 pad;
    s16 state[16];
};

struct LibroAdpcm {
    s32 orden;
    s32 npredictors;
    s16 libro[1];
};

struct MuestraBancoAudio {
    u8 unused;
    u8 cargado;
    u8* direccion_muestra;
    struct BucleAdpcm* loop;
    struct LibroAdpcm* libro;
    u32 tamanio_muestra;
};

struct SonidoBancoAudio {
    struct MuestraBancoAudio* muestra;
    f32 ajuste;
};

struct Instrumento {
     u8 cargado;
     u8 rango_lo_normal;
     u8 rango_hi_normal;
     u8 tasa_suelta;
     struct EnvolventeAdsr* envelope;
     struct SonidoBancoAudio sonido_notas_bajo;
     struct SonidoBancoAudio sonido_notas_normal;
     struct SonidoBancoAudio sonido_notas_alto;
};

struct Tambor {
     u8 tasa_suelta;
     u8 paneo;
     u8 cargado;
    struct SonidoBancoAudio sonido;
    struct EnvolventeAdsr* envelope;
};

struct BancoAudio {
    struct Tambor** tambores;
    struct Instrumento* instrumentos[1];
};

struct EntradaCtl {
    u8 unused;
    u8 instrumentos_num;
    u8 tambores_num;
    struct Instrumento** instrumentos;
    struct Tambor** tambores;
};

struct EstadoGuionM64 {
    u8* pc;
    u8* stack[4];
    u8 iters_bucle_resto[4];
    u8 profundidad;
};

struct JugadorSecuencia {
     u8 activado : 1;
     u8 terminado : 1; // never read
     u8 silenciado : 1;
     u8 sec_dma_en_progreso : 1;
     u8 dma_banco_en_progreso : 1;
     u8 volumen_recalcular : 1;
     u8 state;
     u8 politica_reserva_nota;
     u8 comportamiento_silencio;
     u8 sec_id;
     u8 banco_predeterminado[1];
     u8 id_banco_cargando;
     s8 sec_eu_variacion[1];
     u16 tempo;
     u16 tempo_acc;
     s16 trasposicion;
     u16 delay;
     u16 frames_restante_fundido;
     u16 fundido_temporizador_desconocido_eu;
     u8* sec_datos;
     f32 volumen_fundido;
     f32 velocidad_fundido;
     f32 volumen;
     f32 escala_volumen_silencio;
     f32 escala_volumen_fundido;
     f32 volumen_fundido_aplicado;
     struct CanalSecuencia* channels[MAX_CANALES];
     struct EstadoGuionM64 estado_guion;
     u8* corto_nota_velocidad_tabla;
     u8* corto_nota_duracion_tabla;
     struct PoolNota pool_nota;
     OSMesgQueue sec_cola_msj_dma;
     OSMesg sec_msj_dma;
     OSIoMesg sec_msj_io_dma;
     OSMesgQueue banco_dma_msj_cola;
     OSMesg msj_dma_banco;
     OSIoMesg banco_dma_io_msj;
     u8* banco_dma_act_mem_direccion;
     uintptr_t banco_dma_act_dev_direccion;
     ssize_t restante_dma_banco;
};

struct AjustesAdsr {
    u8 tasa_suelta;
    u8 sostenido;
    struct EnvolventeAdsr* envelope;
};

struct EstadoAdsr {
     u8 accion;
     u8 state;
     s16 indice_amb;
     s16 delay;
     f32 sostenido;
     f32 velocidad;
     f32 vel_salida_fundido;
     f32 current;
     f32 target;
    s32 relleno_1c;
     struct EnvolventeAdsr* envelope;
};

struct DatosBitsReverb {
     u8 bit0 : 1;
     u8 bit1 : 1;
     u8 bit2 : 1;
     u8 usa_auriculares_paneo_efectos : 1;
     u8 efectos_auriculares_estereo : 2;
     u8 derecha_fuerte : 1;
     u8 izquierda_fuerte : 1;
};

union ReverbBits {
     struct DatosBitsReverb s;
     u8 como_byte;
};
struct ReverbInfo {
    u8 reverb_vol;
    u8 volumen_sintesis;
    u8 paneo;
    union ReverbBits reverb_bits;
    f32 escala_frec;
    f32 velocidad;
    s32 unused;
    s16* filtro;
};

struct AtributosNota {
    u8 reverb_vol;
    u8 paneo;
    f32 escala_frec;
    f32 velocidad;
};

struct CanalSecuencia {
     u8 activado : 1;
     u8 terminado : 1;
     u8 guion_parada : 1;
     u8 algo_parada_2 : 1; // sets CapaCanalSecuencia.algo_parada
     u8 instrumento_tiene : 1;
     u8 efectos_auriculares_estereo : 1;
     u8 notas_grande : 1;
     u8 unused : 1;
     union {
        struct {
            u8 escala_frec : 1;
            u8 volumen : 1;
            u8 paneo : 1;
        } como_bitfields;
        u8 as_u8;
    } cambios;
     u8 politica_reserva_nota;
     u8 comportamiento_silencio;
     u8 reverb_vol;
     u8 prioridad_nota;
     u8 id_banco;
     u8 indice_reverb;
     u8 desplazamiento_libro;
     u8 paneo_nuevo;
     u8 peso_canal_paneo;
     u16 inicio_tasa_vibrato;
     u16 inicio_extension_vibrato;
     u16 objetivo_tasa_vibrato;
     u16 objetivo_extension_vibrato;
     u16 vibrato_tasa_cambio_retardo;
     u16 vibrato_extension_cambio_retardo;
     u16 retardo_vibrato;
     u16 delay;
     s16 inst_o_ola;
     s16 trasposicion;
     f32 escala_volumen;
     f32 volumen;
     s32 paneo;
     f32 volumen_aplicado;
     f32 escala_frec;
     u8 (*tabla_din)[][2];
     struct Nota* nota_sin_uso;                  // never read
     struct CapaCanalSecuencia* capa_sin_uso; // never read
     struct Instrumento* instrumento;
     struct JugadorSecuencia* sec_jugador;
     struct CapaCanalSecuencia* capas[MAX_CAPAS];
     s8 sonido_io_guion[8];
     struct EstadoGuionM64 estado_guion;
     struct AjustesAdsr adsr;
     struct PoolNota pool_nota;
};

struct CapaCanalSecuencia {
     u8 activado : 1;
     u8 terminado : 1;
     u8 algo_parada : 1;
     u8 notas_continuo : 1;
     u8 eu_0_b_sin_uso_8 : 1;
     u8 nota_propiedades_necesitar_inicializacion : 1;
     u8 paneo_tambor_ignorar : 1;
     u8 inst_o_ola;
     u8 status;
     u8 duracion_nota;
     u8 nota_objetivo_portamento;
     u8 paneo;
     u8 paneo_nota;
     struct Portamento portamento;
     struct AjustesAdsr adsr;
     u16 tiempo_portamento;
     s16 trasposicion;
     f32 escala_frec;
     f32 cuadrado_velocidad;
     f32 velocidad_nota;
     f32 escala_frec_nota;
     s16 corto_nota_predeterminado_juego_porcentaje;
     s16 porcentaje_juego;
     s16 delay;
     s16 duration;
     s16 retardo_sin_uso;
     struct Nota* nota;
     struct Instrumento* instrumento;
     struct SonidoBancoAudio* sonido;
     struct CanalSecuencia* sec_canal;
     struct EstadoGuionM64 estado_guion;
     struct ItemListaAudio item_lista;
    u8 pad2[4];
};

struct EstadoSintesisNota {
     u8 reinicio;
     u8 indice_dma_muestra;
     u8 ant_auriculares_paneo_derecha;
     u8 ant_auriculares_paneo_izquierda;
     u16 frac_pos_muestra;
     s32 int_pos_muestra;
     struct BuffersSintesisNota* buffers_sintesis;
     s16 izquierda_vol_act;
     s16 derecha_vol_act;
};
struct EstadoReproduccionNota {
     u8 priority;
     u8 id_ola;
     u8 indice_cantidad_muestra;
     s16 escala_vol_adsr;
     f32 escala_frec_portamento;
     f32 escala_frec_vibrato;
     struct CapaCanalSecuencia* capa_padre_ant;
     struct CapaCanalSecuencia* capa_padre;
     struct CapaCanalSecuencia* capa_padre_buscado;
     struct AtributosNota atributos;
     struct EstadoAdsr adsr;
     struct Portamento portamento;
     struct EstadoVibrato estado_vibrato;
};
struct EuSubNota {
     volatile u8 activado : 1;
     u8 inicializacion_necesita : 1;
     u8 terminado : 1;
     u8 amb_mezclador_necesita_inicializacion : 1;
     u8 derecha_fuerte_estereo : 1;
     u8 izquierda_fuerte_estereo : 1;
     u8 efectos_auriculares_estereo : 1;
     u8 usa_auriculares_paneo_efectos : 1;
     u8 indice_reverb : 3;
     u8 desplazamiento_libro : 3;
     u8 ola_sintetico_es : 1;
     u8 partes_adpcm_tiene_dos : 1;
     u8 id_banco;
     u8 derecha_paneo_auriculares;
     u8 izquierda_paneo_auriculares;
     u8 reverb_vol;
     u16 izquierda_vol_objetivo;
     u16 derecha_vol_objetivo;
     u16 remuestreo_tasa_fijo_punto;
     union {
        s16* muestras;
        struct SonidoBancoAudio* sonido_banco_audio;
    } sonido;
};
struct Nota {
     struct ItemListaAudio item_lista;
     struct EstadoSintesisNota estado_sintesis;
#ifdef TARGET_N64
    u8 pad0[12];
#endif

     u8 priority;
     u8 id_ola;
     u8 indice_cantidad_muestra;
     s16 escala_vol_adsr;
     f32 escala_frec_portamento;
     f32 escala_frec_vibrato;
     struct CapaCanalSecuencia* capa_padre_ant;
     struct CapaCanalSecuencia* capa_padre;
     struct CapaCanalSecuencia* capa_padre_buscado;
     struct AtributosNota atributos;
     struct EstadoAdsr adsr;
     struct Portamento portamento;
     struct EstadoVibrato estado_vibrato;
    u8 pad3[8];
     struct EuSubNota eu_sub_nota;
};

struct BuffersSintesisNota {
    s16 estado_adpcmdec[0x10];
    s16 estado_remuestreo_final[0x10];
    s16 estado_remuestreo_paneo[0x10];
    s16 buffer_muestras_paneo[0x20];
};

struct EUAjustesReverb {
    u8 tasa_submuestreo;
    u8 tamanio_ventana;
    u16 gain;
};

struct AudioSesionAjustesEU {
     u32 frecuencia;
     u8 desconocido1;
     u8 notas_simultaneo_max;
     u8 num_reverbs;
     u8 desconocido2;
     struct EUAjustesReverb* ajustes_reverb;
     u16 volumen;
     u16 desconocido3;
     u32 mem_sec_persistente;
     u32 mem_banco_persistente;
     u32 desconocido_18;
     u32 mem_sec_provisorio;
     u32 mem_banco_provisorio;
     u32 desconocido_24;
};

struct AjustesSesionAudio {
     u32 frecuencia;
     u8 notas_simultaneo_max;
     u8 tasa_submuestreo_reverb;
     u16 tamanio_ventana_reverb;
     u16 ganancia_reverb;
     u16 volumen;
     u32 mem_sec_persistente;
     u32 mem_banco_persistente;
     u32 mem_sec_provisorio;
     u32 mem_banco_provisorio;
};

struct AudioBufferParametrosEU {
     s16 desconocido_ajuste_4;
     u16 frecuencia;
     u16 frecuencia_ai;
     s16 muestras_por_objetivo_frame;
     s16 max_ai_buffer_longitud;
     s16 min_ai_buffer_longitud;
     s16 actualizaciones_por_frame;
     s16 muestras_por_actualizacion;
     s16 muestras_por_max_actualizacion;
     s16 muestras_por_min_actualizacion;
     f32 tasa_remuestreo;
     f32 actualizaciones_por_inv_frame;
     f32 actualizaciones_desconocido_por_frame_escalado;
};

#ifdef TARGET_PS2
struct EuAudioCmd {
    union {
        struct {
            u8 parametro3;
            u8 arg2;
            u8 id_banco;
            u8 op;
        } s;
        u32 first;
    } u;
    union {
        s32 as_s32;
        u32 as_u32;
        f32 as_f32;
        struct {
            u8 pad0[3];
            u8 as_u8;
        };
        struct {
            u8 pad1[3];
            s8 as_s8;
        };
    } u2;
};
#else
struct EuAudioCmd {
    union {
        struct {
            u8 op;
            u8 id_banco;
            u8 arg2;
            u8 parametro3;
        } s;
        u32 first;
    } u;
    union {
        s32 as_s32;
        u32 as_u32;
        f32 as_f32;
        u8 as_u8;
        s8 as_s8;
    } u2;
};
#endif

#endif
