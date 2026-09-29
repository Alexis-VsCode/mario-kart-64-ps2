#include <ultra64.h>
#include <juego/macros.h>
#include <juego/mk64.h>

#include "carrera/preparacion_carrera.h"
#include "memoria/memoria_carrera.h"
#include "juego/camino.h"
#include "carrera/actores.h"
#include "juego/tipos_actores.h"
#include "sistema/matematicas.h"
#include "audio/externo.h"
#include <juego/definiciones.h>
#include "carrera/colision.h"
#include "memoria/memoria_carrera.h"
#include "menus/elementos_menu.h"
#include "graficos/cielo_y_pantalla_dividida.h"
#include "carrera/inicio_hud_y_objetos.h"
#include "carrera/aparicion_jugadores.h"
#include "carrera/repeticiones.h"
#include "graficos/dibujar_pistas.h"
#include "sistema/bucle_principal.h"
#include "recursos/pistas/todos_datos_pistas.h"
#include "recursos/pistas/todas_listas_empaquetadas.h"
#include "menus/menus.h"
#include "datos/otras_texturas.h"

extern s32 temporizador_demo;
extern s16 dato_802BA048;
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
s16 id_circuito_actual = 0;
#endif
s16 ahora_cargado_circuito_id = 0xFF;
u16 dato_800DC5A8 = 0;
s32 dato_800DC5AC = 0;
u16 dato_800DC5B0 = 1;
u16 dato_800DC5B4 = 0;
u16 dato_800DC5B8 = 0;
u16 dato_800DC5BC = 0;
u16 es_en_abandonar_a_transicion_menu = 0;
u16 abandonar_a_contador_transicion_menu = 0;
u16 dato_800DC5C8 = 0;
SIN_USO u16 dato_800DC5CC = 0;
s32 dato_800DC5D0 = 0;
s32 dato_800DC5D4 = 0;
s32 dato_800DC5D8 = 0;
s32 dato_800DC5DC = 64;

s32 dato_800DC5E0 = 32;

u16 dato_800DC5E4 = 0;

s32 indice_ganador_jugador = 0;

ALIGNED16 struct desconocido_struct_800DC5EC dato_8015F480[4];
struct desconocido_struct_800DC5EC* dato_800DC5EC = &dato_8015F480[0];
struct desconocido_struct_800DC5EC* dato_800DC5F0 = &dato_8015F480[1];
struct desconocido_struct_800DC5EC* dato_800DC5F4 = &dato_8015F480[2];
struct desconocido_struct_800DC5EC* dato_800DC5F8 = &dato_8015F480[3];
u16 juego_en_pausa = 0;
u8* p_app_nmi_buffer = (u8*) &osAppNmiBuffer;

s32 es_modo_espejo = 0;
f32 vtx_estirar_y = 1.0f;
Lights1 dato_800DC610[] = {
    gdSPDefLights1(175, 175, 175, 255, 255, 255, 0, 0, 120),
    gdSPDefLights1(115, 115, 115, 255, 255, 255, 0, 0, 120),
};
SIN_USO s32 relleno_800029B0 = 0x80000000;
s16 id_circuito_creditos = CIRCUITO_LUIGI_RACEWAY;
s16 cajas_item_lugar = 1;

TrianguloColision* malla_colision;
u16* indices_colision;
u16 cantidad_malla_colision;
u16 triangulos_colision_num;
u32 dato_8015F58C;

Vec3f dato_8015F590;
s32 dato_8015F59C;
s32 dato_8015F5A0;
s32 dato_8015F5A4;
s32 codigo_800029B0_bss_relleno[48];
Vtx* vtx_buffer[32];

s16 max_x_circuito;
s16 min_x_circuito;

s16 max_y_circuito;
s16 min_y_circuito;

s16 max_z_circuito;
s16 min_z_circuito;

s16 dato_8015F6F4;
s16 dato_8015F6F6;
u16 dato_8015F6F8;
s16 dato_8015F6FA;
s16 dato_8015F6FC;
u16 caparazones_aparecido_num;

u16 dato_8015F700;
u16 dato_8015F702;
f32 dato_8015F704;
Vec3f dato_8015F708;
SIN_USO u32 dato_8015F718[3];
size_t tamanio_memoria_libre;
uintptr_t siguiente_libre_memoria_direccion;
uintptr_t ptr_fin_monton;
u32 dato_8015F730;
uintptr_t libre_memoria_reinicio_ancla;
Vec3f dato_8015F738;
Vec3f dato_8015F748;
Vec3f dato_8015F758;
Vec3f dato_8015F768;
Vec3f dato_8015F778;

f32 sentido_circuito;
s32 dato_8015F788;
s32 dato_8015F790[64];
u16 dato_8015F890;
u16 dato_8015F892;
u16 dato_8015F894;
f32 tiempo_jugador_ultimo_tocado_linea_meta[8];

u8* nmi_g_versus_resultados_2_p;
u8* nmi_g_versus_resultados_3_p;
u8* nmi_g_versus_resultados_4_p;
u8* desconocido_nmi_4;
u8* desconocido_nmi_5;
u8* desconocido_nmi_6;

Vec3f dato_8015F8D0;
s32 dato_8015F8DC;

s32 dato_8015F8E0;
f32 dato_8015F8E4;
f32 dato_8015F8E8;
s16 lut_posicion_jugador[8];
u16 actores_permanente_num;
s32 codigo_800029B0_bss_relleno_2[44];

struct Actor lista_actor[TAMANIO_LISTA_ACTOR];
SIN_USO u8 dato_80162578[sizeof(struct Actor)];

s16 cantidad_camino_depuracion;
s16 es_mando_1_desconectado;
s32 dato_801625EC;
s32 dato_801625F0;
s32 dato_801625F4;
s32 dato_801625F8;
f32 dato_801625FC;

void funcion_800029B0(void) {
    switch (dato_800DC5A8) {
        case 0:
            funcion_800C8F44(127);
            break;
        case 1:
            funcion_800C8F44(75);
            break;
        case 2:
            funcion_800C8F44(0);
            break;
    }
}

void preparar_carrera(void) {
    struct Mando* mando;
    int i;

    seleccion_cantidad_jugador_1 = cantidad_jugador;
    if (estado_juego != CARRERA) {
        es_modo_espejo = 0;
    }
    if (es_modo_espejo) {
        sentido_circuito = -1.0f;
    } else {
        sentido_circuito = 1.0f;
    }
    if (seleccion_modo == GRAN_PREMIO) {
        id_circuito_actual = orden_circuito_copa[seleccion_copa][indice_circuito_en_copa];
    }
    modo_pantalla_activo = seleccion_modo_pantalla;
    if (id_circuito_actual != ahora_cargado_circuito_id) {
        dato_80150120 = 0;
        ahora_cargado_circuito_id = id_circuito_actual;
        siguiente_libre_memoria_direccion = libre_memoria_reinicio_ancla;
#ifdef TARGET_PS2
        {
            void reiniciar_pantallas_gigantes(void);

            reiniciar_pantallas_gigantes();
        }
#endif
        cargar_circuito(id_circuito_actual);
        circuito_generar_colision_malla();
        MARCAR_TIEMPOS_PS2("colisión: vértices y fin");
        dato_8015F730 = siguiente_libre_memoria_direccion;
    } else {
        siguiente_libre_memoria_direccion = dato_8015F730;
    }
    funcion_802969F8();
    MARCAR_TIEMPOS_PS2("ajustes de la pista");
    funcion_80005310();
    MARCAR_TIEMPOS_PS2("fantasmas");
    funcion_8003D080();
    MARCAR_TIEMPOS_PS2("jugadores y cámaras");
    inicializar_hud();
    MARCAR_TIEMPOS_PS2("indicadores en pantalla");
    estado_carrera = NINGUNO_CARRERA;
    caparazones_aparecido_num = 0;
    dato_800DC5B8 = 0;
    dato_80152308 = 0;
    temporizador_demo = -1;
    dato_802BA048 = 0;
    funcion_802A74BC();
    fijar_perspectiva_y_proporcion_aspecto();
    funcion_80091FA4();
    MARCAR_TIEMPOS_PS2("cámaras y pantallas");
    cargar_texturas_actores_inicializacion_y();
    MARCAR_TIEMPOS_PS2("actores y texturas");

    if (seleccion_modo != BATALLA) {
        dato_8015F8D0[1] = (f32) (camino_pista_actual->pos_y - 15);
        dato_8015F8D0[2] = camino_pista_actual->pos_z;
        if (id_circuito_actual == CIRCUITO_TOADS_TURNPIKE) {
            dato_8015F8D0[0] = (es_modo_espejo != 0) ? camino_pista_actual->pos_x + 138.0f : camino_pista_actual->pos_x - 138.0f;
        } else if (id_circuito_actual == CIRCUITO_WARIO_STADIUM) {
            dato_8015F8D0[0] = (es_modo_espejo != 0) ? camino_pista_actual->pos_x + 12.0f : camino_pista_actual->pos_x - 12.0f;
        } else {
            dato_8015F8D0[0] = camino_pista_actual->pos_x;
        }
    }
    if (!modo_demo) {
        funcion_800CA008(seleccion_cantidad_jugador_1 - 1, id_circuito_actual + 4);
        funcion_800CB2C4();
    }
    MARCAR_TIEMPOS_PS2("audio: fundido y reinicio");

    mando = mando_uno;

    for (i = 0; i < 7; i++, mando++) {
        mando->palanca_x_crudo = 0;
        mando->palanca_y_crudo = 0;
        mando->boton_pulsado = 0;
        mando->boton_apretado = 0;
        mando->button = 0;
    }
}

void funcion_80002DAC(void) {
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            fijar_vec3f(dato_8015F748, -223.0f, 94.0f, -155.0f);
            funcion_800C9D80(dato_8015F748, dato_802B91C8, 0x5103700B);
            break;
        case CIRCUITO_ROYAL_RACEWAY:
            fijar_vec3f(dato_8015F748, 177.0f, 87.0f, -393.0f);
            funcion_800C9D80(dato_8015F748, dato_802B91C8, 0x5103700B);
            break;
        case CIRCUITO_LUIGI_RACEWAY:
            fijar_vec3f(dato_8015F748, 85.0f, 21.0f, -219.0f);
            funcion_800C9D80(dato_8015F748, dato_802B91C8, 0x5103700B);
            break;
        case CIRCUITO_WARIO_STADIUM:
            fijar_vec3f(dato_8015F748, 298.0f, 202.0f, -850.0f);
            funcion_800C9D80(dato_8015F748, dato_802B91C8, 0x5103700B);
            fijar_vec3f(dato_8015F758, -1600.0f, 202.0f, -2430.0f);
            funcion_800C9D80(dato_8015F758, dato_802B91C8, 0x5103700B);
            fijar_vec3f(dato_8015F768, -2708.0f, 202.0f, 1762.0f);
            funcion_800C9D80(dato_8015F768, dato_802B91C8, 0x5103700B);
            fijar_vec3f(dato_8015F778, -775.0f, 202.0f, 1930.0f);
            funcion_800C9D80(dato_8015F778, dato_802B91C8, 0x5103700B);
            break;
        case CIRCUITO_KOOPA_BEACH:
            fijar_vec3f(dato_8015F738, 153.0f, 0.0f, 2319.0f);
            funcion_800C9D80(dato_8015F738, dato_802B91C8, 0x51028001);
            break;
        case CIRCUITO_DK_JUNGLE:
            fijar_vec3f(dato_8015F738, -790.0f, -255.0f, -447.0f);
            funcion_800C9D80(dato_8015F738, dato_802B91C8, 0x51028001);
            break;
        default:
            break;
    }
#else

#endif
}

void borrar_buffer_nmi(void) {
    s32 i;
    for (i = 0; i < 16; i++) {
        osAppNmiBuffer[i] = 0;
    }
}

void funcion_80003040(void) {
    Vec3f posicion;
    Vec3f velocidad = { 0, 0, 0 };
    Vec3s rotacion = { 0, 0, 0 };

    dato_800DC5BC = 0;
    dato_800DC5C8 = 0;
    actores_num = 0;
    es_modo_espejo = 0;
    sentido_circuito = 1.0f;

    seleccion_cantidad_jugador_1 = 1;

    fijar_direccion_base_segmento(0x3, (void*) (siguiente_libre_memoria_direccion - 0x9000));
    destruir_todos_actores();
#if !ACTIVACION_PERSONALIZADO_CIRCUITO_MOTOR
    switch (id_circuito_actual) {
        case CIRCUITO_MARIO_RACEWAY:
            texturas_dma(textura_arboles_1, 0x35B, 0x800);
            aparecer_follaje(d_circuito_mario_raceway_apariciones_arbol);
            break;
        case CIRCUITO_BOWSER_CASTLE:
            fijar_colores_vtx_buscar_y(0x07001350, 0x32, 0, 0, 0);
            break;
        case CIRCUITO_BANSHEE_BOARDWALK:
            fijar_colores_vtx_buscar_y(0x07000878, 128, 0, 0, 0);
            break;
        case CIRCUITO_YOSHI_VALLEY:
            fijar_vec3f(posicion, -2300.0f, 0.0f, 634.0f);
            posicion[0] *= sentido_circuito;
            agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, ACTOR_YOSHI_HUEVO);
            break;
        case CIRCUITO_MOO_MOO_FARM:
            texturas_dma(textura_izquierda_arboles_4, 0x3E8, 0x800);
            texturas_dma(textura_derecha_arboles_4, 0x3E8, 0x800);
            texturas_dma(textura_izquierda_vaca_01, 0x400, 0x800);
            texturas_dma(textura_derecha_vaca_01, 0x400, 0x800);
            texturas_dma(textura_izquierda_vaca_02, 0x400, 0x800);
            texturas_dma(textura_derecha_vaca_02, 0x400, 0x800);
            texturas_dma(textura_izquierda_vaca_03, 0x400, 0x800);
            texturas_dma(textura_derecha_vaca_03, 0x400, 0x800);
            texturas_dma(textura_izquierda_vaca_04, 0x400, 0x800);
            texturas_dma(textura_derecha_vaca_04, 0x400, 0x800);
            texturas_dma(textura_izquierda_vaca_05, 0x400, 0x800);
            texturas_dma(textura_derecha_vaca_05, 0x400, 0x800);
            aparecer_follaje(d_circuito_moo_moo_farm_aparicion_arbol);
            break;
        case CIRCUITO_SHERBET_LAND:
            fijar_colores_vtx_buscar_y(0x07001EB8, 180, 0xFF, 0xFF, 0xFF);
            fijar_colores_vtx_buscar_y(0x07002308, 150, 0xFF, 0xFF, 0xFF);
            break;
        case CIRCUITO_RAINBOW_ROAD:
            fijar_colores_vtx_buscar_y(0x07002068, 150, 0xFF, 0xFF, 0xFF);
            fijar_colores_vtx_buscar_y(0x07001E18, 150, 0xFF, 0xFF, 0xFF);
            fijar_colores_vtx_buscar_y(0x07001318, 255, 0xFF, 0xFF, 0);
            break;
        case CIRCUITO_WARIO_STADIUM:
            fijar_vec3f(posicion, -131.0f, 83.0f, 286.0f);
            agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, ACTOR_WARIO_CARTEL);
            fijar_vec3f(posicion, -2353.0f, 72.0f, -1608.0f);
            agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, ACTOR_WARIO_CARTEL);
            fijar_vec3f(posicion, -2622.0f, 79.0f, 739.0f);
            agregar_actor_a_ranura_vacio(posicion, rotacion, velocidad, ACTOR_WARIO_CARTEL);
            fijar_colores_vtx_buscar_y(0x07000C50, 0x64, 0xFF, 0xFF, 0xFF);
            fijar_colores_vtx_buscar_y(0x07000BD8, 0x64, 0xFF, 0xFF, 0xFF);
            fijar_colores_vtx_buscar_y(0x07000B60, 0x64, 0xFF, 0xFF, 0xFF);
            fijar_colores_vtx_buscar_y(0x07000AE8, 0x64, 0xFF, 0xFF, 0xFF);
            fijar_colores_vtx_buscar_y(0x07000CC8, 0x64, 0xFF, 0xFF, 0xFF);
            fijar_colores_vtx_buscar_y(0x07000D50, 0x64, 0xFF, 0xFF, 0xFF);
            fijar_colores_vtx_buscar_y(0x07000DD0, 0x64, 0xFF, 0xFF, 0xFF);
            fijar_colores_vtx_buscar_y(0x07000E48, 0x64, 0xFF, 0xFF, 0xFF);
            break;
        case CIRCUITO_DK_JUNGLE:
            fijar_colores_vtx_buscar_y(0x07003FA8, 0x78, 0xFF, 0xFF, 0xFF);
            break;
        default:
            break;
    }
#else

#endif
    actores_permanente_num = actores_num;
}
