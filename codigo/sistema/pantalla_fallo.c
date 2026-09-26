#include <ultra64.h>
#include <juego/macros.h>
#include <juego/mk64.h>
#include <stdarg.h>
#include <string.h>

#include "sistema/pantalla_fallo.h"
#include "sistema/bucle_principal.h"

#ifdef CRASH_SCREEN_ENHANCEMENT
#include "debug/crash_screen_enhancement.h"
#endif

OSThread dato_80162790;
ALIGNED8 u8 pila_hilo_depuracion[0x400];
OSMesgQueue dato_80162D40;
OSMesg dato_80162D58;
u16* p_framebuffer;
s32 indice_secuencia_boton;

#define CODIGO_DIBUJO 0xFFFF
#define GUION_PERSONAJE 16

extern void osSetEventMesg(OSEvent, OSMesgQueue*, OSMesg);
extern s32 osRecvMesg(OSMesgQueue*, OSMesg*, s32);

s32 contador = 0;

u8 fuente_pantalla_error[][8] = {
#include "recursos/texturas/fuente_pantalla_fallo.ia1.inc.c"
};

u16 error_pantalla_boton_secuencia[] = { L_TRIG, U_JPAD, L_JPAD,   D_JPAD,   R_JPAD,
                                     R_TRIG, L_TRIG, B_BUTTON, A_BUTTON, CODIGO_DIBUJO };

void dibujar_glifo_pantalla_error(u16* framebuffer, s32 x, s32 y, s32 glifo) {
    s32 datos;
    s32 ptr;
    s32 i, j;

    for (i = 0; i < 8; i++) {

        datos = fuente_pantalla_error[glifo][i];

        for (j = 5; j >= 0; j--) {

            ptr = (y + i) * 320 + (x + j);

            if (datos & 1) {
                framebuffer[ptr] = 0xffff;
            }
            datos = datos >> 1;
        }
    }
}

void dibujar_cuadrado_pantalla_error(u16* framebuffer);

#define COLOR_BLANCO 0xFFFF
#define COLOR_ROJO 0xF801

#define CUADRADO_X 40
#define CUADRADO_Y 40

#define TAMANIO_X_CUADRADO 6
#define TAMANIO_Y_CUADRADO 6

#define ANCHO_BORDE 1

#define CUADRADO_X2 CUADRADO_X + TAMANIO_Y_CUADRADO
#define CUADRADO_Y2 CUADRADO_Y + TAMANIO_X_CUADRADO

void dibujar_cuadrado_pantalla_error(u16* framebuffer) {
    s32 h;
    s32 i;
    s32 j;

    for (h = 0; h < 2; h++) {
        for (i = (h * ANCHO_BORDE) + CUADRADO_Y; i < (CUADRADO_Y2 - (h * ANCHO_BORDE)); i++) {
            for (j = (h * ANCHO_BORDE) + CUADRADO_X; j < (CUADRADO_X2 - (h * ANCHO_BORDE)); j++) {
                framebuffer[(i * 320) + j] = (h == 0) ? (COLOR_ROJO) : (COLOR_BLANCO);
            }
        }
    }

    osWritebackDCacheAll();
    osViSwapBuffer(framebuffer);
}

#define COLOR_NEGRO 0x0001

void dibujar_info_pantalla_error(u16* framebuffer, OSThread* hilo_2) {
    __OSThreadContext* contexto = &hilo_2->context;
    s32 i, j, x, y, h;
    uintptr_t direccion_con_falla;
    u32 excepcion;
    s32 matematica;
    u32 info_error;
    s32 temporal_;

    for (h = 0; h < 3; h++) {

        matematica = (48 + (contador * 24)) + h * 20;

        for (i = 0; i < 16; i++) {
            for (j = 0; j < 120; j++) {
                framebuffer[((i + matematica) * 320) + (j + 100)] = COLOR_NEGRO;
            }
        }
    }

    temporal_ = (contador * 24);
    y = temporal_ + 53;
    dibujar_glifo_pantalla_error(framebuffer, 108, y, hilo_2->id & 0xF);
    dibujar_glifo_pantalla_error(framebuffer, 116, y, GUION_PERSONAJE);

    info_error = contexto->pc;

    for (x = 180; x >= 124; x -= 8) {
        dibujar_glifo_pantalla_error(framebuffer, x, y, info_error & 0xF);
        info_error >>= 4;
    }

    excepcion = (contexto->cause >> 2) & 0x1F;
    dibujar_glifo_pantalla_error(framebuffer, 188, y, GUION_PERSONAJE);
    dibujar_glifo_pantalla_error(framebuffer, 196, y, excepcion >> 4);
    dibujar_glifo_pantalla_error(framebuffer, 204, y, excepcion & 0xF);

    info_error = contexto->ra;

    for (x = 180; x >= 124; x -= 8) {
        dibujar_glifo_pantalla_error(framebuffer, x, 73, info_error & 0xF);
        info_error >>= 4;
    }

    direccion_con_falla = contexto->pc & (~3);

    if ((direccion_con_falla > 0x80000000) && (direccion_con_falla < 0x803FFF7F)) {
        info_error = *(u32*) direccion_con_falla;
    }
    for (x = 180; x >= 124; x -= 4) {
        dibujar_glifo_pantalla_error(framebuffer, x, 93, info_error & 0xF);
        x -= 4;
        info_error >>= 4;
    }
    osWritebackDCacheAll();
    osViSwapBuffer(framebuffer);
}

OSThread* obtener_hilo_con_falla(void) {
    OSThread* hilo_2;

    hilo_2 = __osGetCurrFaultedThread();
    while (hilo_2->priority != -1) {
        if (hilo_2->priority > OS_PRIORITY_IDLE && hilo_2->priority <= OS_PRIORITY_APPMAX && (hilo_2->flags & 3) != 0) {
            return hilo_2;
        }
        hilo_2 = hilo_2->tlnext;
    }
    return NULL;
}

void hilo9_pantalla_error(SIN_USO void* parametro0) {
    static OSThread* hilo_2;
    OSMesg msj;

    osSetEventMesg(12, &dato_80162D40, (OSMesg) 16);
    osSetEventMesg(10, &dato_80162D40, (OSMesg) 16);
    indice_secuencia_boton = 0;

    while (true) {
        osRecvMesg(&dato_80162D40, &msj, 1);
        hilo_2 = obtener_hilo_con_falla();

        if (hilo_2) {
            if (contador == 0) {
                dibujar_cuadrado_pantalla_error(p_framebuffer);
#ifndef DEBUG
                while (true) {
                    leer_mandos();

                    if (!mando_uno->boton_pulsado) {
                        continue;
                    }

                    if (mando_uno->boton_pulsado == error_pantalla_boton_secuencia[indice_secuencia_boton]) {
                        indice_secuencia_boton++;
                    } else {
                        indice_secuencia_boton = 0;
                    }

                    if (error_pantalla_boton_secuencia[indice_secuencia_boton] == CODIGO_DIBUJO) {
                        break;
                    }
                }
#endif
#if DEBUG
                dibujar_pantalla_error(hilo_2);
#else
                dibujar_info_pantalla_error(p_framebuffer, hilo_2);
#endif
            }
            if (contador < 5) {
                contador++;
            }
        }
    }
}

void fijar_framebuffer_pantalla_error(u16* framebuffer) {
    p_framebuffer = framebuffer;
}

extern void hilo9_pantalla_error(void*);

void crear_hilo_depuracion(void) {
    osCreateMesgQueue(&dato_80162D40, &dato_80162D58, 1);
    osCreateThread((OSThread*) &dato_80162790, 9, (void*) hilo9_pantalla_error, 0, &dato_80162D40, 0x7F);
}

void empezar_hilo_depuracion(void) {
    osStartThread(&dato_80162790);
}
