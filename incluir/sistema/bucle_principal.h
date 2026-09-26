#ifndef SISTEMA_BUCLE_PRINCIPAL_H
#define SISTEMA_BUCLE_PRINCIPAL_H

#define COMPLETO_SP_MSJ 100
#define COMPLETO_DP_MSJ 101
#define VBLANK_VI_MSJ 102
#define MSJ_INICIO_GFX_SPTASK 103
#define PEDIDO_NMI_MSJ 104

#define MTX_HUD_POOL_TAMANIO 800

#ifdef AVOID_UB
#define MTX_HUD_POOL_TAMANIO_MAX MTX_HUD_POOL_TAMANIO
#else
#define MTX_HUD_POOL_TAMANIO_MAX MTX_HUD_POOL_TAMANIO - 50
#endif

#define MTX_OBJETO_POOL_TAMANIO 128

#define MTX_SOMBRA_POOL_TAMANIO 8 * 4

#define MTX_KART_POOL_TAMANIO 8 * 4

#define MTX_EFECTO_POOL_TAMANIO 660

#ifdef AVOID_UB
#define MTX_EFECTO_POOL_TAMANIO_MAX MTX_EFECTO_POOL_TAMANIO
#else
#define MTX_EFECTO_POOL_TAMANIO_MAX MTX_EFECTO_POOL_TAMANIO + 100
#endif

#define GFX_TAMANIO_POOL 7500

struct GfxPool {
     Mtx pantalla_mtx;
     Mtx mtx_persp[4];
     Mtx orto_mtx;
     Mtx desconocido_mtx;
     Mtx mtx_mirar_a[4];
     Mtx mtx_hud[MTX_HUD_POOL_TAMANIO];
     Mtx objeto_mtx[MTX_OBJETO_POOL_TAMANIO];
     Mtx sombra_mtx[MTX_SOMBRA_POOL_TAMANIO];
     Mtx mtx_kart[MTX_KART_POOL_TAMANIO];
     Mtx efecto_mtx[MTX_EFECTO_POOL_TAMANIO];
     Mtx mtx_arr[4];
     Gfx gfx_pool[GFX_TAMANIO_POOL];
     struct TareaSP tarea_sp;
};

typedef struct {
    u16 triangulo;
    u16 triangulos_num;
} CuadriculaColision;

void crear_hilo(OSThread*, OSId, void (*entry)(void*), void*, void*, OSPri);
void funcion_principal(void);
void hilo1_inactivo(void*);
void preparar_colas_msj(void);
void empezar_sptask(s32);
void crear_estructura_tarea_gfx(void);
void inicializar_mandos(void);
void actualizar_mando(s32);
void leer_mandos(void);
void funcion_80000BEC(void);
void despachar_sptask_audio(struct TareaSP*);
void ejecutar_display_list(struct TareaSP*);
void inicializar_rcp(void);
void maestro_fin_display_list(void);
void* borrar_framebuffer(s32);
void inicializar_renderizado(void);
void config_gfx_pool(void);
void mostrar_y_esperar_retrazo(void);
void inicializar_secuencias_final_segmento(void);
void inicializar_carrera_segmento(void);
void copiar_dma(u8*, u8*, size_t);
void preparar_memoria_juego(void);
void inicializar_framebuffer_limpieza_juego(void);
void bucle_logica_carrera(void);
void manejador_estado_juego(void);
void interrumpir_sptask_gfx(void);
void recibir_tareas_nuevo(void);
void fijar_manejador_vblank(s32, struct ManejadorVblank*, OSMesgQueue*, OSMesg*);
void empezar_sptask_gfx(void);
void manejar_vblank(void);
void manejar_completo_dp(void);
void manejar_completo_sp(void);
void hilo3_video(void*);
void funcion_800025D4(void);
void funcion_80002600(void);
void funcion_8000262C(void);
void funcion_80002658(void);
void actualizar_estado_juego(void);
void hilo5_bucle_juego(void*);
void hilo4_audio(void*);

extern struct ManejadorVblank* manejador_vblank_1;
extern struct ManejadorVblank* manejador_vblank_2;

extern struct TareaSP* tarea_sp_activo;
extern struct TareaSP* actual_audio_sp_tarea;
extern struct TareaSP* actual_pantalla_sp_tarea;
extern struct TareaSP* siguiente_audio_sp_tarea;
extern struct TareaSP* siguiente_pantalla_sp_tarea;

extern struct Mando mandos[];
extern struct Mando* mando_uno;
extern struct Mando* mando_dos;
extern struct Mando* mando_tres;
extern struct Mando* mando_cuatro;
extern struct Mando* mando_cinco;
extern struct Mando* mando_seis;
extern struct Mando* mando_siete;
extern struct Mando* mando_ocho;

extern Jugador jugadores[];
extern Jugador* jugador_uno;
extern Jugador* jugador_dos;
extern Jugador* jugador_tres;
extern Jugador* jugador_cuatro;
extern Jugador* jugador_cinco;
extern Jugador* jugador_seis;
extern Jugador* jugador_siete;
extern Jugador* jugador_ocho;

extern Jugador* copia_jugador_uno;
extern Jugador* copia_jugador_dos;

extern struct GfxPool gfx_pools[];
extern struct GfxPool* gfx_pool;

extern struct ManejadorVblank manejador_vblank_juego;
extern struct ManejadorVblank sonido_manejador_vblank;
extern OSMesgQueue cola_msj_dma, cola_vblank_juego, gfx_cola_vblank, sin_uso_g_mens_cola, cola_msj_intr, sp_tarea_msj_cola;
extern OSMesgQueue sonido_cola_msj;
extern OSMesg sonido_buf_msj[1];
extern OSMesg buf_msj_dma[1], buf_msj_juego;
extern OSMesg gfx_buf_msj[];
extern OSMesg buf_msj_intr[16], sp_tarea_msj_buf[16];
extern OSMesg msj_recibido_principal;
extern OSIoMesg msj_io_dma;
extern OSMesgQueue si_evento_msj_cola;
extern OSMesg si_evento_msj_buf[3];

extern OSContStatus situaciones_mando[];

extern OSContPad rellenos_mando[];
extern u8 bits_mando;

extern CuadriculaColision cuadricula_colision[];
extern u16 actores_num;
extern u16 cantidad_objeto_matriz;
extern s32 pasos_por_frame;
extern f32 dato_80150118;
extern u16 reinicio_suave_was;
extern u16 dato_8015011E;

extern s32 dato_80150120;
extern s32 modo_goto;
extern f32 acercar_camara[];

extern f32 aspecto_pantalla;

extern struct dato_80150158 g_d_80150158[];
extern uintptr_t tabla_segmento[];
extern Gfx* display_list_cabeza;
extern struct TareaSP* gfx_tarea_sp;
extern s32 dato_801502A0;
extern s32 dato_801502A4;
extern u16* framebuffers_fisico[];
extern uintptr_t fisico_zbuffer;
extern Mat4 dato_801502C0;

extern s32 margen[];

extern u16 dato_80152300[];
extern u16 dato_80152308;

extern OSThread hilo_inactivo;
extern u8 pila_hilo_inactivo[];
extern OSThread hilo_video;
extern u8 pila_hilo_video[];
extern OSThread hilo_bucle_juego;
extern u8 juego_bucle_hilo_pila[];
extern OSThread hilo_audio;
extern u8 pila_hilo_audio[];

extern u8 gfx_sp_tarea_cesion_buffer[];
extern u32 gfx_pila_tarea_sp[];
extern OSMesg buf_msj_pi[];
extern OSMesgQueue cola_msj_pi;
void bucle_logica_carrera(void);
extern s32 estado_juego;
#ifndef carrera_estado_as_u16
#ifdef GCC
extern u16 estado_carrera;
#else
extern s32 estado_carrera;
#endif
#endif

extern u16 dato_800DC514;
extern u16 modo_render_creditos;
extern u16 modo_demo;
extern u16 modo_depuracion_activacion;
extern s32 siguiente_estado_juego;
extern s32 modo_pantalla_activo;
extern s32 seleccion_modo_pantalla;
extern s32 seleccion_cantidad_jugador_1;

extern s32 seleccion_modo;
extern s32 dato_800DC540;
extern s32 dato_800DC544;
extern s32 seleccion_cc;
extern s32 temporizador_global;
extern u16 s_framebuffer_renderizado;
extern u16 framebuffer_renderizado;
extern s32 dato_800DC568;
extern s32 dato_800DC56C[];
extern s16 num_vblanks;
extern f32 temporizador_vblank;
extern f32 temporizador_circuito;

#endif
