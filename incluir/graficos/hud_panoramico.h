#ifndef GRAFICOS_HUD_PANORAMICO_H
#define GRAFICOS_HUD_PANORAMICO_H

#include "juego/definiciones.h"
#include "sistema/opciones_port.h"

// Marcador de la carrera en PANORÁMICO. La tele estira la imagen 4:3 a 16:9: el
// 3D sale bien con la vista Hor+ (vista_panoramica.h) pero el marcador, que se
// dibuja en las 320 columnas de siempre, sale 4/3 más ancho. Se estrecha a 3/4
// en X alrededor del centro de su cuadrante (el de la pantalla con 1 jugador o
// con las pantallas apiladas; el de cada mitad con las pantallas lado a lado).
//
// Cómo se distingue el marcador de lo demás, de menos a más fino:
//  - formato PANORÁMICO: con los otros nunca se toca nada;
//  - estado del juego CARRERA: ningún menú, ceremonia ni créditos;
//  - proyección ortográfica de guOrtho(0, W, H, 0, -1, 1), la que carga
//    fijar_pantalla_hud_matriz(): no es la del cielo (y invertida, 0 a 5) ni las
//    de los textos de menús y de pausa (-100 a 100), y el 3D es perspectiva;
//  - los rectángulos con color que cubren (casi) todo el cuadrante son
//    fundidos y no se estrechan (ver hud_panoramico_rect_estrechable).

#define HUD_PANORAMICO_NUM 3.0f
#define HUD_PANORAMICO_DEN 4.0f
#define HUD_PANORAMICO_ANCHO 320.0f

// x (en columnas de 320) estrechada a 3/4 alrededor de centro. Con un cuadrante
// sin ancho no se toca.
static inline float hud_panoramico_x(float x, float centro, float ancho_cuadrante)
{
    if (ancho_cuadrante <= 0.0f) {
        return x;
    }
    return centro + (x - centro) * (HUD_PANORAMICO_NUM / HUD_PANORAMICO_DEN);
}

// Columnas de cuadrantes del modo de pantalla: dos lado a lado con 2 jugadores
// en vertical y con 3 o 4; una con 1 jugador y con 2 apilados.
static inline int hud_panoramico_columnas(int modo_pantalla)
{
    return (modo_pantalla == PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL ||
            modo_pantalla == PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA) ? 2 : 1;
}

static inline float hud_panoramico_ancho_cuadrante(int columnas)
{
    return HUD_PANORAMICO_ANCHO / (float) (columnas < 1 ? 1 : columnas);
}

// Estrecha una x del marcador (columnas de 320) alrededor del centro del
// cuadrante donde cae: 160 con una columna, 80 o 240 con dos.
// El cuadrante lo da ref: un rectángulo pasa el centro de sus bordes para que los
// dos se estrechen alrededor del mismo centro aunque cruce la mitad.
static inline float hud_panoramico_estrechar_ref(float x, float ref, int columnas)
{
    float ancho = hud_panoramico_ancho_cuadrante(columnas);
    float centro = HUD_PANORAMICO_ANCHO / 2.0f;

    if (columnas >= 2) {
        centro = ref < HUD_PANORAMICO_ANCHO / 2.0f ? ancho / 2.0f : HUD_PANORAMICO_ANCHO - ancho / 2.0f;
    }
    return hud_panoramico_x(x, centro, ancho);
}

static inline float hud_panoramico_estrechar(float x, int columnas)
{
    return hud_panoramico_estrechar_ref(x, x, columnas);
}

// ¿Lo que se dibuja ahora es el marcador de la carrera en PANORÁMICO? m00, m11,
// m22 y m33 son los elementos de la proyección cargada; el marcador es la
// ortográfica de profundidad -1 a 1 (m22 = -1) con la Y hacia abajo (m11 < 0).
static inline int hud_panoramico_activo(int formato, int estado, float m00, float m11, float m22, float m33)
{
    if (formato != FORMATO_PANORAMICO || estado != CARRERA) {
        return 0;
    }
    return m33 == 1.0f && m00 > 0.0f && m11 < 0.0f && m22 > -1.001f && m22 < -0.999f;
}

// Un rectángulo con color del marcador se estrecha; el que cubre casi todo el
// cuadrante (un fundido) no.
static inline int hud_panoramico_rect_estrechable(float ulx, float lrx, int columnas)
{
    return (lrx - ulx) < 0.9f * hud_panoramico_ancho_cuadrante(columnas);
}

#endif
