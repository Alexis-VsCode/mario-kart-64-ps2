#include <ultra64.h>
#include <juego/macros.h>
#include <juego/definiciones.h>
#include <juego/segmentos.h>
#include <juego/mk64.h>
#include <juego/pista.h>

#include "ceremonia/carga_ceremonia.h"
#include "memoria/memoria_carrera.h"
#include "carrera/camara.h"
#include "ceremonia/camara_ceremonia.h"
#include "carrera/aparicion_jugadores.h"
#include "graficos/cielo_y_pantalla_dividida.h"
#include "carrera/inicio_hud_y_objetos.h"
#include "ceremonia/actores_podio.h"
#include "carrera/ia_vehiculos_y_camara.h"
#include "carrera/colision.h"
#include "ceremonia/dibujar_podio.h"
#include "carrera/preparacion_carrera.h"
#include "menus/elementos_menu.h"
#include "sistema/bucle_principal.h"
#include "menus/menus.h"
#include "graficos/dibujar_pistas.h"

u8 ids_personaje_predeterminado[] = { 1, 2, 3, 4, 5, 6, 7, 0 };

void depuracion_interruptor_personaje_ceremonia_cinematica(void) {
    if (modo_depuracion_activacion) {
        if (mando_uno->button & DPAD_TODOS_MANTENIDO_Y_BOTONES_C) {
            if (mando_uno->button & U_CBUTTONS) {
                selecciones_personaje[0] = LUIGI;
            } else if (mando_uno->button & L_CBUTTONS) {
                selecciones_personaje[0] = YOSHI;
            } else if (mando_uno->button & R_CBUTTONS) {
                selecciones_personaje[0] = TOAD;
            } else if (mando_uno->button & D_CBUTTONS) {
                selecciones_personaje[0] = DK;
            } else if (mando_uno->button & U_JPAD) {
                selecciones_personaje[0] = WARIO;
            } else if (mando_uno->button & L_JPAD) {
                selecciones_personaje[0] = PEACH;
            } else if (mando_uno->button & R_JPAD) {
                selecciones_personaje[0] = BOWSER;
            } else {
                selecciones_personaje[0] = MARIO;
            }
            bcopy(&ids_personaje_predeterminado, &id_personaje_por_puesto_total_gp, 8);
        }
    }
}

s32 funcion_80281880(s32 parametro0) {
    s32 i;
    for (i = 0; i < JUGADORES_NUM; i++) {
        if (id_personaje_por_puesto_total_gp[i] == selecciones_personaje[parametro0]) {
            break;
        }
    }
    return i;
}

void funcion_802818BC(void) {
    s32 temporal_v0;
    SIN_USO s32 relleno;
    s32 sp1_c;
    s32 temporal_v0_2;

    if (cantidad_jugador != DOS_JUGADORES_SELECCIONADO) {
        dato_802874D8.desconocido_1d = funcion_80281880(0);
        dato_802874D8.desconocido_1e = selecciones_personaje[0];
        return;
    }
    temporal_v0 = sp1_c = funcion_80281880(0);
    temporal_v0_2 = funcion_80281880(1);
    if (sp1_c < temporal_v0_2) {
        dato_802874D8.desconocido_1e = selecciones_personaje[0];
        dato_802874D8.desconocido_1d = temporal_v0;
    } else {
        dato_802874D8.desconocido_1e = selecciones_personaje[1];
        dato_802874D8.desconocido_1d = temporal_v0_2;
    }
}

void cargar_cinematica_ceremonia(void) {
    Camara* camara = &camaras[0];

    id_circuito_actual = CIRCUITO_ROYAL_RACEWAY;
    dato_800DC5B4 = (u16) 1;
    es_modo_espejo = 0;
    goto_menu = 0xFFFF;
    dato_80287554 = 0;
    fijar_perspectiva_y_proporcion_aspecto();
    funcion_802A74BC();
    camara->desconocido_B4 = 60.0f;
    acercar_camara[0] = 60.0f;
    dato_800DC5EC->ancho_pantalla = ANCHO_PANTALLA;
    dato_800DC5EC->altura_pantalla = ALTURA_PANTALLA;
    dato_800DC5EC->inicio_x_pantalla = 160;
    dato_800DC5EC->inicio_y_pantalla = 120;
    seleccion_modo_pantalla = MODO_PANTALLA_1P;
    siguiente_libre_memoria_direccion = (s32) libre_memoria_reinicio_ancla;
    modo_pantalla_activo = MODO_PANTALLA_1P;
    seleccion_modo = GRAN_PREMIO;
    cargar_circuito(id_circuito_actual);
    dato_8015F730 = (s32) siguiente_libre_memoria_direccion;
    fijar_direccion_base_segmento(0xB, (void*) descomprimir_segmentos((u8*) CEREMONIA_DATOS_ROM_INICIO, (u8*) CEREMONIA_DATOS_ROM_FIN));
    fijar_direccion_base_segmento(6, (void*) descomprimir_segmentos((u8*) &_course_banshee_boardwalk_dl_mio0SegmentRomStart,
                                                         (u8*) &_course_yoshi_valley_dl_mio0SegmentRomStart));
    dato_8015F8E4 = -2000.0f;

    min_x_circuito = -0x15A1;
    min_y_circuito = -0x15A1;
    min_z_circuito = -0x15A1;

    max_x_circuito = 0x15A1;
    max_y_circuito = 0x15A1;
    max_z_circuito = 0x15A1;

    dato_8015F59C = 0;
    dato_8015F5A0 = 0;
    dato_8015F58C = 0;
    cantidad_malla_colision = (u16) 0;
    dato_800DC5BC = (u16) 0;
    dato_800DC5C8 = (u16) 0;
    malla_colision = (TrianguloColision*) siguiente_libre_memoria_direccion;
    generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x070067E8, -1);
    generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x0700AEF8, -1);
    generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x0700A970, 8);
    generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x0700AC30, 8);
    generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07000CE0, 0x10);
    generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07000E88, 0x10);
    generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x0700A618, -1);
    generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x0700A618, -1);
    generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x070023F8, 1);
    generar_malla_colision_con_id_seccion_predeterminado((Gfx*) 0x07002478, 1);
    funcion_80295C6C();
    depuracion_interruptor_personaje_ceremonia_cinematica();
    funcion_802818BC();
    funcion_8003D080();
    inicializar_hud();
    funcion_8001C05C();
    inicializar_globos_y_fuegos_artificiales();
    inicializar_ceremonia_podio_camara();
    funcion_80093E60();
    dato_801625F8 = (s32) ptr_fin_monton - siguiente_libre_memoria_direccion;
    dato_801625FC = ((f32) dato_801625F8 / 1000.0f);
}
