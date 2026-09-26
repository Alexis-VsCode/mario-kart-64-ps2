#ifndef CARRERA_IA_VEHICULOS_Y_CAMARA_H
#define CARRERA_IA_VEHICULOS_Y_CAMARA_H

#include "juego/vehiculos.h"
#include "camara.h"
#include "juego/camino.h"
#include <recursos/datos_comunes.h>

struct actores_vigente {
     s32 desconocido0;
     s32 desconocido4;
     s32 desconocido8;
     u16 desconocido_c;
     u16 indice_actor;
     s16 unk10;
     u32 unk14;
     s32 unk18;
};

typedef struct {
     f32 current;
     f32 target;
     f32 paso;
     f32 desconocido_c;
} PistaPosicionFactorInstruccion;

typedef struct {
     s16 rama;
     s16 indice_actor;
     s16 temporizador;
     s16 usar_item_num;
     s16 num_soltado_banana_grupo;
     s16 desconocido_0A;
     s16 desconocido_0C;
     s16 tiempo_antes_lanzamiento;
} CpuItemEstrategiaDatos;

typedef struct {
    s16 desconocido0;
    s16 desconocido2;
    s16 desconocido4;
    u16 desconocido6;
} desconocido_struct_46D0;

typedef struct {
    s16 x;
    s16 z;
} Camino2D;

enum CpuItemEstrategiaEnum {
    CPU_ESTRATEGIA_ESPERA_SIGUIENTE_ITEM = 0,

    CPU_ESTRATEGIA_ITEM_BANANA,
    CPU_ESTRATEGIA_MANTENIDO_BANANA,
    CPU_ESTRATEGIA_CAIDA_BANANA,

    ITEM_ESTRATEGIA_CPU_CAPARAZON_VERDE,
    MANTENIDO_ESTRATEGIA_CPU_CAPARAZON_VERDE,
    LANZAMIENTO_ESTRATEGIA_CPU_CAPARAZON_VERDE,

    ITEM_ESTRATEGIA_CPU_CAPARAZON_ROJO,
    MANTENIDO_ESTRATEGIA_CPU_CAPARAZON_ROJO,
    LANZAMIENTO_ESTRATEGIA_CPU_CAPARAZON_ROJO,

    CPU_ESTRATEGIA_ITEM_BANANA_GRUPO,
    CPU_ESTRATEGIA_ESPERA_INICIALIZACION_BANANA_GRUPO,
    CPU_ESTRATEGIA_CAIDA_BANANA_GRUPO,

    ITEM_ESTRATEGIA_CPU_CAJA_ITEM_FALSA,
    MANTENIDO_ESTRATEGIA_CPU_CAJA_ITEM_FALSA,
    LANZAMIENTO_ESTRATEGIA_CPU_CAJA_ITEM_FALSA,

    CPU_ESTRATEGIA_ITEM_RAYO = 0x16,
    CPU_ESTRATEGIA_FIN_RAYO,

    CPU_ESTRATEGIA_ITEM_ESTRELLA = 0x19,
    CPU_ESTRATEGIA_FIN_ITEM_ESTRELLA,

    ITEM_ESTRATEGIA_CPU_BOO,
    CPU_ESTRATEGIA_ESPERA_FIN_BOO,

    CPU_ESTRATEGIA_ITEM_HONGO,
    CPU_ESTRATEGIA_ITEM_DOBLE_HONGO,
    ITEM_ESTRATEGIA_CPU_TRIPLE_HONGO,
    ITEM_ESTRATEGIA_CPU_SUPER_HONGO,
    USAR_ESTRATEGIA_CPU_SUPER_HONGO,

    CPU_ESTRATEGIA_LANZAMIENTO_BANANA,
    CPU_ESTRATEGIA_MANTENIDO_LANZAMIENTO_BANANA,
    CPU_ESTRATEGIA_FIN_LANZAMIENTO_BANANA
};

s16 obtener_angulo_entre_camino(Vec3f, Vec3f);

s32 chocar_con_vehiculo_es(f32, f32, f32, f32, f32, f32, f32, f32);
void ajustar_posicion_por_angulo(Vec3f, Vec3f, s16);
s32 renderizar_banderas_distancia_vehiculo_conjunto(Vec3f, f32, s32);
void detectar_sentido_jugador_incorrecto(s32, Jugador*);
void fijar_puestos(void);

void actualizar_clasificacion_jugador(void);
void fijar_circuito_fin_puestos_con_tiempo(void);
s32 es_punto_camino_en_rango(u16, u16, u16, u16, u16);
void funcion_80007D04(s32, Jugador*);
void funcion_80007FA4(s32, Jugador*, f32);

void regular_cpu_rapidez(s32, f32, Jugador*);
bool funcion_800088D8(s32, s16, s16);
void fijar_camino_actual(s32);
s32 actualizar_seleccion_camino_jugador(s32, s32);
void actualizar_finalizacion_jugador(s32);

void yoshi_valley_camino_cpu(s32);
void actualizar_finalizacion_camino_cpu(s32, Jugador*);
f32 tiempo_cruzado_linea_meta(s32, f32, f32);
void actualizar_finalizacion_camino_jugador(s32, Jugador*);
void actualizar_vehiculos(void);
void reproducir_cpu_efecto_sonido(s32, Jugador*);
void actualizar_sonido_temporizador_jugador(s32, Jugador*);
void actualizar_jugador(s32);

void funcion_8000B140(s32);
s32 son_en_curva(s32, u16);
bool es_lejos_desde_camino(s32);
f32 calcular_factor_posicion_pista(f32, f32, u16, s32);
void actualizar_factor_posicion_jugador(s32, u16, s32);
void calcular_posicion_desplazamiento_pista(u16, f32, f32, s16);
void fijar_posicion_desplazamiento_pista(u16, f32, s16);
s16 funcion_8000BD94(f32, f32, f32, s32);

s16 buscar_mas_cercano_camino_punto_pista_seccion(f32, f32, f32, u16, s32*);
s16 actualizar_indice_camino_con_pista(f32, f32, f32, s16, s32, u16);
s16 actualizar_indice_camino(f32, f32, f32, s16, s32);
void ajustar_indice_camino_wario_stadium(f32, f32, f32, s16*, s32);
void empezar_linea_camino_ajustar_en(f32, f32, f32, s16*, s32);
s16 actualizar_camino_indice_pista_seccion(f32, f32, f32, Jugador*, s32, s32*);
s16 actualizar_camino_jugador(f32, f32, f32, s16, Jugador*, s32, s32);

s16 buscar_mas_cercano_vehiculos_camino_punto(f32, f32, f32, s16);
s16 funcion_8000D24C(f32, f32, f32, s32*);
s16 funcion_8000D2B4(f32, f32, f32, s16, s32);
s16 funcion_8000D33C(f32, f32, f32, s16, s32);
f32 cpu_pista_posicion_factor(s32);
void determinar_ideal_cpu_posicion_desplazamiento(s32, u16);
s16 funcion_8000D6D0(Vec3f, s16*, f32, f32, s16, s16);
s16 funcion_8000D940(Vec3f, s16*, f32, f32, s16);
s16 actualizar_camino_siguiente_vehiculo(Vec3f, s16*, f32);
void aparecer_posiciones_conjunto_kart_bomba(void);
void actualizar_karts_bomba(s32);

s32 agregar_actor_en_lista_actor_vigente(s32, s16);
s32 agregar_caparazon_rojo_en_lista_actor_vigente(s32);
s32 agregar_caparazon_verde_en_lista_actor_vigente(s32);
s32 agregar_caparazon_azul_en_lista_actor_vigente(s32);
void eliminar_actor_en_lista_actor_vigente(s32);
void funcion_8000EEDC(void);
void generar_humo_jugador(void);

void funcion_8000F0E0(void);
void funcion_8000F124(void);
void borrar_punto_camino(PuntoCaminoPista*, size_t);
void inicializar_punto_camino_circuito(void);
void inicializar_jugadores(void);

void cargar_camino_pista(s32);
void calcular_limites_pista(s32);
f32 calcular_curvatura_pista(s32, u16);
void analizar_secciones_pista(s32);
s16 calcular_camino_angulo(s32, s32);
void analizar_angulo_camino(s32);
void analizar_camino_curvo(s32);
f32 funcion_80010F40(f32, f32, f32, s32, s32);
f32 funcion_80010FA0(f32, f32, f32, s32, s32);

s32 funcion_80011014(PuntoCaminoPista*, PuntoCaminoPista*, s32, s32);
s32 procesar_datos_camino(PuntoCaminoPista*, PuntoCaminoPista*);
s32 generar_2d_camino(Camino2D*, PuntoCaminoPista*, s32);
void copiar_comportamiento_cpu_circuitos(void);
void reiniciar_ninguno_comportamiento_cpu(s32);
void reiniciar_comportamiento_cpu(s32);
void empezar_comportamiento_cpu(s32, Jugador*);
void fin_comportamiento_cpu(s32, Jugador*);
void comportamiento_cpu(s32);
void funcion_80011EC0(s32, Jugador*, s32, u16);

void generar_camino_tren(void);
void generar_camino_ferry(void);
void aparecer_vehiculo_en_ruta(CosasVehiculo*);
void aparecer_vehiculos_circuito(void);
void fijar_vehiculo_pos_camino_punto(CosasAutomovilTren*, Camino2D*, u16);
void inicializar_trenes_vehiculos(void);
void sincronizar_componentes_tren(CosasAutomovilTren*, s16);
void actualizar_trenes_vehiculo(void);
void manejar_interacciones_trenes(s32, Jugador*);

void funcion_80013054(void);
void comprobar_distancia_cruce_ai(s32);
void inicializar_ferry_vehiculos(void);
void actualizar_barcos_paleta_vehiculo(void);
void manejar_interacciones_barcos_paleta(Jugador*);
void inicializar_toads_turnpike_vehiculo(f32, f32, s32, s32, CosasVehiculo*, PuntoCaminoPista*);
f32 funcion_80013C74(s16, s16);
void actualizar_vehiculo_seguir_camino_punto(CosasVehiculo*);
void manejar_interacciones_vehiculo(s32, Jugador*, CosasVehiculo*, f32, f32, s32, u32);

f32 jugador_pista_posicion_factor_vehiculo(s16, f32, s16);
void actualizar_jugador_pista_posicion_factor_desde_vehiculo(s32, s32, CosasVehiculo*);
void inicializar_camiones_caja_vehiculos(void);
void actualizar_camiones_caja_vehiculo(void);
void manejar_interacciones_camiones_caja(s32, Jugador*);
void actualizar_jugador_pista_posicion_factor_desde_camiones_caja(s32);
void inicializar_omnibus_escuela_vehiculos(void);
void actualizar_omnibus_escuela_vehiculo(void);
void manejar_interacciones_omnibus_escuela(s32, Jugador*);
void actualizar_jugador_pista_posicion_factor_desde_omnibus(s32);
void inicializar_camiones_vehiculos(void);
void actualizar_camiones_cisterna_vehiculo(void);
void manejar_interacciones_camiones_cisterna(s32, Jugador*);
void actualizar_jugador_pista_posicion_factor_desde_camion_cisterna(s32);
void inicializar_automoviles_vehiculos(void);
void actualizar_automoviles_vehiculo(void);
void manejar_interacciones_automoviles(s32, Jugador*);
void actualizar_jugador_pista_posicion_factor_desde_automoviles(s32);
void funcion_80014D30(s32, s32);
void funcion_80014DE4(s32);
f32 funcion_80014EE4(f32, s32);

void calcular_vector_arriba_camara(Camara*, s32);
void funcion_8001530C(void);
void funcion_80015314(s32, f32, s32);
void funcion_80015390(Camara*, Jugador*, s32);
void funcion_80015544(s32, f32, s32, s32);
void funcion_8001577C(Camara*, SIN_USO Jugador*, s32, s32);
void funcion_80015A9C(s32, f32, s32, s16);
void funcion_80015C94(Camara*, Jugador*, s32, s32);

void funcion_800162CC(s32, f32, s32, s16);
void funcion_80016494(Camara*, Jugador*, s32, s32);
void funcion_80016C3C(s32, f32, s32);

void funcion_80017720(s32, f32, s32, s16);
void funcion_800178F4(Camara*, Jugador*, s32, s32);
void funcion_80017F10(s32, f32, s32, s16);

void funcion_800180F0(Camara*, Jugador*, s32, s32);
void funcion_80018718(s32, f32, s32, s16);
void funcion_800188F4(Camara*, Jugador*, s32, s32);

void funcion_80019118(s32, f32, s32, s16);
void funcion_8001933C(Camara*, SIN_USO Jugador*, s32, s32);
void funcion_8001968C(void);
void funcion_8001969C(s32, f32, s32, s16);
void funcion_80019760(Camara*, SIN_USO Jugador*, s32, s32);
void empezar_disparo_cinematica_camara(s32, s32);
void funcion_80019B50(s32, u16);
void funcion_80019C50(s32);
void funcion_80019D2C(Camara*, Jugador*, s32);
void funcion_80019DE4(void);
void funcion_80019DF4(void);
void funcion_80019E58(void);
void funcion_80019ED0(void);
void funcion_80019FB4(s32);

void funcion_8001A0A4(u16*, Camara*, Jugador*, s8, s32);
void funcion_8001A0DC(u16*, Camara*, Jugador*, s8, s32);
void funcion_8001A124(s32, s32);
s32 funcion_8001A310(s32, s32);
void funcion_8001A348(s32, f32, s32);
void funcion_8001A3D8(s32, f32, s32);
void funcion_8001A450(s32, s32, s32);
void funcion_8001A518(s32, s32, s32);
void funcion_8001A588(u16*, Camara*, Jugador*, s8, s32);
void funcion_8001AAAC(s16, s16, s16);
void funcion_8001AB00(void);
void cpu_decisiones_rama_item(s32, s16*, s32);
void funcion_8001ABE0(s32, CpuItemEstrategiaDatos*);
void borrar_estrategias_vencido(CpuItemEstrategiaDatos*);
void cpu_usar_item_estrategia(s32);

void funcion_8001BE78(void);

void funcion_8001C05C(void);
void funcion_8001C14C(void);
void renderizar_karts_bomba_envoltura(s32);
void funcion_8001C42C(void);

extern Colision dato_80162E70;
extern s16 dato_80162EB0;
extern s16 dato_80162EB2;
extern ComportamientoCPU* comportamiento_cpu_circuitos[];
extern s16 dato_80162F10[];
extern s16 dato_80162F50[];
extern Vec3f posicion_desplazamiento;
extern Vec3f dato_80162FB0;
extern Vec3f dato_80162FC0;
extern s16 temporizador_humo_tren;
extern s16 dato_80162FD0;
extern f32 porciento_finalizacion_circuito_por_puesto[];
extern s16 dato_80162FF8[];
extern s16 dato_80163010[];
extern f32 cpu_objetivo_rapidez[];
extern s16 direccion_angulo_anterior[];
extern f32 dato_80163090[];
extern bool es_jugador_en_curva[];
extern u16 actual_mas_cercano_camino_punto;
extern s16 es_jugador_nuevo_camino_punto;
extern s16 dato_801630E8[];
extern s16 temporizador_humo_ferry;
extern s32 dato_80163100[];
extern s32 dato_80163128[];
extern s32 dato_80163150[];
extern f32 anterior_jugador_ai_desplazamiento_x[];
extern f32 anterior_jugador_ai_desplazamiento_z[];
extern s16 vehiculo_sonido_render_contador;
extern s32 dato_801631CC;
extern u16 dato_801631E0[];
extern u16 dato_801631F8[];
extern f32 actual_cpu_objetivo_rapidez;
extern f32 anterior_cpu_objetivo_rapidez[];
extern s32 dato_80163238;
extern u16 cruzado_linea_meta[];
extern u16 contador_sentido_incorrecto[];
extern u16 es_sentido_incorrecto_jugador[];
extern s32 anterior_vuelta_progreso_puntaje[];
extern ComportamientoCPU* comportamiento_cpu_actual;
extern u16 actual_cpu_comportamiento_id[];
extern u16 anterior_cpu_comportamiento_id[];
extern u16 cpu_comportamiento_estado[];

enum { CPU_COMPORTAMIENTO_ESTADO_NINGUNO, CPU_COMPORTAMIENTO_ESTADO_INICIO, CPU_COMPORTAMIENTO_ESTADO_EJECUTANDO };

extern s16 angulo_jugador[];
extern u16 dato_80163330[];
extern u16 dato_80163344[];
extern u16 dato_80163348[];
extern u16 dato_8016334C[];
extern u16 comportamiento_cpu_rapidez[];

enum { RAPIDEZ_CPU_COMPORTAMIENTO_NORMAL, RAPIDEZ_CPU_COMPORTAMIENTO_RAPIDO, RAPIDEZ_CPU_COMPORTAMIENTO_LENTO, RAPIDEZ_CPU_COMPORTAMIENTO_MAX };

extern s32 jugador_actualizacion_incrementar;
extern s32 dato_8016337C;
extern s16 actual_jugador_mirada_adelante[];
extern s16 dato_80163398[];
extern s16 dato_801633B0[];
extern s16 dato_801633C8[];
extern s16 dato_801633E0[];
extern s16 dato_801633F8[];
extern s16 dato_80163410[];
extern f32 dato_80163418[];
extern f32 dato_80163428[];
extern f32 dato_80163438[];
extern f32 g_jugador_z_anterior[];
extern s16 mejor_clasificado_humano_jugador;
extern s16 es_en_extra;
extern s16 dato_8016347C;
extern s16 dato_8016347E;
extern s32 dato_80163480;
extern s32 dato_80163484;
extern s32 dato_80163488;
extern s16 dato_8016348C;
extern s16 dato_801634C0[];
extern s16 b_parada_ai_cruce[];
extern s16 dato_801634EC;
extern s32 dato_801634F0;
extern s32 dato_801634F4;
extern PistaPosicionFactorInstruccion jugador_pista_posicion_factor_instruccion[];
extern Camino2D* punto_camino_vehiculo_2d;
extern s32 longitud_camino_vehiculo_2d;
extern u16 es_cruce_disparado_por_indice[];
extern u16 temporizador_activo_cruce[];
extern s32 dato_80163DD8[];
extern struct actores_vigente lista_actores_vigente[];
extern CpuItemEstrategiaDatos cpu_item_estrategia[];
extern s16 dato_80164358;
extern s16 dato_8016435A;
extern s16 dato_8016435C;
extern s16 gp_actual_carrera_jugador_id_por_puesto[];
extern s16 id_jugador_ant_por_puesto[];
extern s32 cantidad_vuelta_por_id_jugador[];
extern s32 gp_actual_carrera_puesto_por_id_jugador[];
extern s32 anterior_gp_actual_carrera_puesto_por_id_jugador[];
extern s32 gp_actual_carrera_puesto_por_duplicar_id_jugador[];
extern s16 jugador_obtener_por_id_personaje[];
extern s32 dato_8016448C;
extern f32 dato_80164498[];
extern f32 porciento_finalizacion_vuelta_por_id_jugador[];
extern f32 porciento_finalizacion_circuito_por_id_jugador[];
extern f32 camino_y_jugador[];
extern s16 dato_80164538[];
extern s32 dato_801645D0[];
extern s32 dato_801645E8[];
extern f32 dato_801645F8[];
extern s32 dato_80164608[];
extern f32 dato_80164618[];
extern s32 dato_80164628[];
extern f32 dato_80164638[];
extern f32 dato_80164648[];
extern f32 dato_80164658[];
extern s16 dato_80164670[];
extern s16 dato_80164678[];
extern s16 dato_80164680[];
extern f32 dato_80164688[];
extern f32 dato_80164698;
extern f32 dato_8016469C;
extern f32 dato_801646A0;
extern s16 dato_801646C0[];
extern u32 dato_801646C8;
extern u16 dato_801646CC;
extern desconocido_struct_46D0 dato_801646D0[];

extern f32 porciento_finalizacion_circuito_por_puesto[JUGADORES_NUM];
extern s32 dato_8016448C;
extern u16 dato_801637BE;
extern u16 dato_80163E2A;

#define SEVERO_INCORRECTO_SENTIDO_MIN 136
#define SEVERO_INCORRECTO_SENTIDO_MAX 225
#define SEVERO_CORRECTO_SENTIDO_MIN 45
#define SEVERO_CORRECTO_SENTIDO_MAX 316
#define INCORRECTO_SENTIDO_FRAMES_LIMITE 5

#endif
