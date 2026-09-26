#include <ultra64.h>
#include <juego/macros.h>
#include "sistema/perfilador.h"
#include <juego/mk64.h>
#include "sistema/bucle_principal.h"

struct DatosFramePerfilador datos_frame_perfilador[2];

s32 metros_recurso_activacion = 0;

s16 dato_800DC664 = 0;
s16 dato_800DC668 = 1;
s16 dato_800DC66C = 0;

void perfilador_registro_hilo5_tiempo(enum EventoJuegoPerfilador id_evento) {
    datos_frame_perfilador[dato_800DC668].veces_juego[id_evento] = osGetTime();

    if (id_evento == FIN_THREAD5) {
        dato_800DC668 ^= 1;
        datos_frame_perfilador[dato_800DC668].veces_sonido_num = 0;
    }
}

void perfilador_registro_hilo4_tiempo(void) {
    struct DatosFramePerfilador* perfilador = &datos_frame_perfilador[dato_800DC668];

    if (perfilador->veces_sonido_num < CANTIDAD_ARREGLO(perfilador->sonido_veces)) {
        perfilador->sonido_veces[perfilador->veces_sonido_num++] = osGetTime();
    }
}

void perfilador_registro_gfx_tiempo(enum EventoGfxPerfilador id_evento) {
    if (id_evento == TAREAS_EN_COLA) {
        dato_800DC66C ^= 1;
        datos_frame_perfilador[dato_800DC66C].veces_vblank_num = 0;
    }
    datos_frame_perfilador[dato_800DC66C].gfx_veces[id_evento] = osGetTime();
}

void perfilador_registro_vblank_tiempo(void) {
    struct DatosFramePerfilador* perfilador = &datos_frame_perfilador[dato_800DC66C];

    if (perfilador->veces_vblank_num < CANTIDAD_ARREGLO(perfilador->veces_vblank)) {
        perfilador->veces_vblank[perfilador->veces_vblank_num++] = osGetTime();
    }
}

void dibujar_barra_perfilador(OSTime base_reloj, OSTime inicio_reloj, OSTime fin_reloj, s16 pos_y, u16 color) {
    s64 inicio_duracion, fin_duracion;
    s32 rect_x1, rect_x2;

    if ((inicio_duracion = inicio_reloj - base_reloj) < 0) {
        inicio_duracion = 0;
    }
    if ((fin_duracion = fin_reloj - base_reloj) < 0) {
        fin_duracion = 0;
    }

    rect_x1 = ((((inicio_duracion * 1000000) / osClockRate * 3) / 1000) + 30);
    rect_x2 = ((((fin_duracion * 1000000) / osClockRate * 3) / 1000) + 30);

    if (rect_x1 > 319) {
        inicio_reloj = 319;
    }
    if (rect_x2 > 319) {
        fin_reloj = 319;
    }

    if (rect_x1 < rect_x2) {
        gDPPipeSync(display_list_cabeza++);
        gDPSetFillColor(display_list_cabeza++, color << 16 | color);
        gDPFillRectangle(display_list_cabeza++, rect_x1, pos_y, rect_x2, pos_y + 2);
    }
}

void dibujar_barras_perfilador_referencia(void) {

    gDPPipeSync(display_list_cabeza++);
    gDPSetFillColor(display_list_cabeza++, GPACK_RGBA5551(40, 80, 255, 1) << 16 | GPACK_RGBA5551(40, 80, 255, 1));
    gDPFillRectangle(display_list_cabeza++, 30, 220, 79, 222);

    gDPPipeSync(display_list_cabeza++);
    gDPSetFillColor(display_list_cabeza++, GPACK_RGBA5551(255, 255, 40, 1) << 16 | GPACK_RGBA5551(255, 255, 40, 1));
    gDPFillRectangle(display_list_cabeza++, 79, 220, 128, 222);

    gDPPipeSync(display_list_cabeza++);
    gDPSetFillColor(display_list_cabeza++, GPACK_RGBA5551(255, 120, 40, 1) << 16 | GPACK_RGBA5551(255, 120, 40, 1));
    gDPFillRectangle(display_list_cabeza++, 128, 220, 177, 222);

    gDPPipeSync(display_list_cabeza++);
    gDPSetFillColor(display_list_cabeza++, GPACK_RGBA5551(255, 40, 40, 1) << 16 | GPACK_RGBA5551(255, 40, 40, 1));
    gDPFillRectangle(display_list_cabeza++, 177, 220, 226, 222);
}

void dibujar_modo_perfilador_1(void) {
}

void dibujar_modo_perfilador_0(void) {
    s32 i;
    struct DatosFramePerfilador* perfilador;

    u64 inicio_reloj;
    u64 duracion_guion_nivel;
    u64 renderizar_duracion;
    u64 inicio_tarea;
    u64 duracion_rsp;
    u64 duracion_rdp;
    u64 vblank;
    u64 sonido_duracion;

    perfilador = &datos_frame_perfilador[dato_800DC668 ^ 1];

    inicio_reloj = perfilador->veces_juego[0] <= perfilador->sonido_veces[0] ? perfilador->veces_juego[0] : perfilador->sonido_veces[0];

    duracion_guion_nivel = perfilador->veces_juego[1] - inicio_reloj;
    renderizar_duracion = perfilador->veces_juego[2] - perfilador->veces_juego[1];
    inicio_tarea = 0;
    duracion_rsp = perfilador->gfx_veces[1] - perfilador->gfx_veces[0];
    duracion_rdp = perfilador->gfx_veces[2] - perfilador->gfx_veces[0];
    vblank = 0;

    perfilador->veces_sonido_num &= 0xFFFE;

    for (i = 0; i < perfilador->veces_sonido_num; i += 2) {
        sonido_duracion = perfilador->sonido_veces[i + 1] - perfilador->sonido_veces[i];
        inicio_tarea += sonido_duracion;
        if (perfilador->sonido_veces[i] < perfilador->veces_juego[1]) {
            duracion_guion_nivel -= sonido_duracion;
        } else if (perfilador->sonido_veces[i] < perfilador->veces_juego[2]) {
            renderizar_duracion -= sonido_duracion;
        }
    }

    perfilador->veces_sonido_num &= 0xFFFE;

    for (i = 0; i < perfilador->veces_sonido_num; i += 2) {
        vblank += (perfilador->veces_vblank[i + 1] - perfilador->veces_vblank[i]);
    }

    inicio_reloj = 0;
    dibujar_barra_perfilador(0, inicio_reloj, inicio_reloj + inicio_tarea, 212, GPACK_RGBA5551(255, 40, 40, 1));

    inicio_reloj += inicio_tarea;
    dibujar_barra_perfilador(0, inicio_reloj, inicio_reloj + duracion_guion_nivel, 212, GPACK_RGBA5551(255, 255, 40, 1));

    inicio_reloj += duracion_guion_nivel;
    dibujar_barra_perfilador(0, inicio_reloj, inicio_reloj + renderizar_duracion, 212, GPACK_RGBA5551(255, 120, 40, 1));

    dato_800DC568 = (s32) (inicio_reloj + renderizar_duracion);
    dato_800DC56C[0] = duracion_rdp;

    dibujar_barra_perfilador(0, 0, duracion_rdp, 216, GPACK_RGBA5551(255, 120, 40, 1));
    dibujar_barra_perfilador(0, 0, duracion_rsp, 216, GPACK_RGBA5551(255, 255, 40, 1));
    dibujar_barra_perfilador(0, 0, vblank, 216, GPACK_RGBA5551(255, 40, 40, 1));

    dibujar_barras_perfilador_referencia();
}

void pantalla_recurso(void) {
    gDPPipeSync(display_list_cabeza++);
    gDPSetScissor(display_list_cabeza++, G_SC_NON_INTERLACE, 0, 0, ANCHO_PANTALLA, ALTURA_PANTALLA);
    gDPSetRenderMode(display_list_cabeza++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCycleType(display_list_cabeza++, G_CYC_FILL);
    gDPSetFillColor(display_list_cabeza++, GPACK_RGBA5551(0, 0, 0, 0) << 16 | GPACK_RGBA5551(0, 0, 0, 0));

    if ((mando_uno->boton_pulsado & L_TRIG) != 0) {
        dato_800DC664 ^= 1;
    }
    dibujar_modo_perfilador_0();
}
