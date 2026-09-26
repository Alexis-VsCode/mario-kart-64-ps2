#include <ultra64.h>
#include <PR/gu.h>
#include <juego/macros.h>
#include <juego/pista.h>

#include "ceremonia/dibujar_podio.h"
#include "sistema/bucle_principal.h"
#include "sistema/matematicas.h"
#include "graficos/cielo_y_pantalla_dividida.h"
#include "graficos/dibujar_objetos.h"
#include "carrera/objetos_y_efectos.h"
#include "menus/elementos_menu.h"
#include "ceremonia/actores_podio.h"
#include "ceremonia/ceremonia_y_creditos.h"
#include "ceremonia/actores_podio.h"
#include "graficos/dibujar_jugador.h"
#include "juego/definiciones.h"

struct StructDesconocido80287560 {
    s16 desconocido0;
    s16 desconocido2;
    s32 desconocido4;
    s32 desconocido8;
};

s32 goto_menu;
s32 dato_80287554;
s32 d_80281C40_relleno[2];
struct StructDesconocido80287560 dato_80287560[30];

void funcion_80281C40(void) {
    s32 i;

    for (i = 0; i < dato_802874FC; i++) {
        funcion_800579F8(dato_80287560[i].desconocido0, dato_80287560[i].desconocido2, (char*) dato_80287560[i].desconocido8, dato_80287560[i].desconocido4);
    }
}

void funcion_80281CB4(s32 parametro0, s32 parametro1, s32 parametro2, s32 parametro3) {
    if (dato_802874FC < 0x1E) {
        dato_80287560[dato_802874FC].desconocido0 = parametro0;
        dato_80287560[dato_802874FC].desconocido2 = parametro1;
        dato_80287560[dato_802874FC].desconocido4 = parametro3;
        dato_80287560[dato_802874FC].desconocido8 = parametro2;
        dato_802874FC++;
    }
}

extern Gfx dato_80284F70[];
extern Gfx dato_80284EE0[];

void renderizar_ceremonia_podio(void) {
    Camara* camara = &camaras[0];
    SIN_USO s32 relleno[3];
    u16 norma_persp;
    Mat4 matriz;
    SIN_USO s32 relleno2[3];

    funcion_802A53A4();
    inicializar_rdp();
    if (goto_menu != 0xFFFF) {
        borrar_framebuffer(0);
        if (dato_80287554 >= 4) {
            es_en_abandonar_a_transicion_menu = 0;
            siguiente_estado_juego = goto_menu;
        }
        dato_80287554++;
        return;
    }
    funcion_8028150C();
    gSPSetGeometryMode(display_list_cabeza++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    guPerspective((Mtx*) &gfx_pool->mtx_persp[0], &norma_persp, acercar_camara[0], aspecto_pantalla, circuito_cerca_persp,
                  persp_lejos_circuito, 1.0f);
    gSPPerspNormalize(display_list_cabeza++, norma_persp);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_persp[0]),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guLookAt((Mtx*) &gfx_pool->mtx_mirar_a[0], camara->pos[0], camara->pos[1], camara->pos[2], camara->mirar_a[0],
             camara->mirar_a[1], camara->mirar_a[2], camara->arriba[0], camara->arriba[1], camara->arriba[2]);
    gSPMatrix(display_list_cabeza++, VIRTUAL_A_FISICO(&gfx_pool->mtx_mirar_a[0]),
              G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    identidad_mtxf(matriz);
    fijar_posicion_render(matriz, 0);
    gSPDisplayList(display_list_cabeza++, VIRTUAL_A_PHYSICAL2(&dato_80284F70));
    renderizar_jugadores_en_pantalla_uno();
    gSPDisplayList(display_list_cabeza++, VIRTUAL_A_PHYSICAL2(&dato_80284EE0));
    actualizar_bucle_actores();
    renderizar_objeto(JUGADOR_UNO + MODO_PANTALLA_1P);
    funcion_80021B0C();
    gSPDisplayList(display_list_cabeza++, VIRTUAL_A_PHYSICAL2(&dato_80284EE0));
    funcion_80093F10();
    ceremonia_transicion_deslizando_bordes();
    funcion_80281C40();
    inicializar_rdp();
}
