// Registros del PCRTC según las opciones de imagen (registros_video.h)
#include <stdio.h>

#include "graficos/registros_video.h"

static int s_fallos, s_comprobaciones;

static void comprobar(const char *que, unsigned long long obtenido, unsigned long long esperado) {
    s_comprobaciones++;
    if (obtenido != esperado) {
        s_fallos++;
        printf("FALLO %s: %llx, se esperaba %llx\n", que, obtenido, esperado);
    }
}

#define CAMPO(v, bit, ancho) (((v) >> (bit)) & ((1ULL << (ancho)) - 1))

// Lo que deja gsKit_init_screen en NTSC 640x448 entrelazado por campos
static const BaseVideo base_gskit = { 652, 50, 3, 0, 2560, 448 };

static RegistrosVideo calcular(int antiparpadeo, int dx, int dy, int formato) {
    OpcionesPort o;
    RegistrosVideo r;

    opciones_por_defecto(&o, 0);
    o.antiparpadeo = antiparpadeo;
    o.desplaz_x = dx;
    o.desplaz_y = dy;
    o.formato = formato;
    calcular_registros_video(&base_gskit, &o, &r);
    return r;
}

int main(void) {
    RegistrosVideo r;
    int y;

    // Por defecto: lo mismo que escribe gsKit
    r = calcular(0, 0, 0, FORMATO_NORMAL);
    comprobar("PMODE por defecto", r.pmode, 0x8046);
    comprobar("DBY por defecto", r.dispfb2_extra, 0);
    comprobar("DISPLAY por defecto", r.display,
              652ULL | (50ULL << 12) | (3ULL << 23) | (0ULL << 27) | (2559ULL << 32) | (447ULL << 44));
    // PANORÁMICO no toca el PCRTC
    comprobar("DISPLAY panorámico", calcular(0, 0, 0, FORMATO_PANORAMICO).display, r.display);

    // Antiparpadeo: dos circuitos, el segundo una línea más abajo
    r = calcular(1, 0, 0, FORMATO_NORMAL);
    comprobar("PMODE antiparpadeo", r.pmode, 0x8027);
    comprobar("DBY antiparpadeo", r.dispfb2_extra, 1ULL << 43);

    // Bandas: 3/4 del ancho, centrado
    r = calcular(0, 0, 0, FORMATO_CON_BANDAS);
    comprobar("MAGH bandas", CAMPO(r.display, 23, 4), 2);
    comprobar("DW bandas", CAMPO(r.display, 32, 12), 1919);
    comprobar("DX bandas", CAMPO(r.display, 0, 12), 652 + 320);
    comprobar("DH bandas", CAMPO(r.display, 44, 11), 447);

    // Posición: 8 VCK y 2 líneas por paso
    r = calcular(0, 3, -2, FORMATO_NORMAL);
    comprobar("DX desplazado", CAMPO(r.display, 0, 12), 652 + 24);
    comprobar("DY desplazado", CAMPO(r.display, 12, 11), 46);
    for (y = -DESPLAZ_Y_MAX - 3; y <= DESPLAZ_Y_MAX + 3; y++) {
        comprobar("DY par", CAMPO(calcular(0, 0, y, FORMATO_NORMAL).display, 12, 11) & 1, 0);
    }

    // Límites: el desplazamiento se recorta al máximo de opciones_port.h
    comprobar("DX tope", CAMPO(calcular(0, 100, 0, FORMATO_NORMAL).display, 0, 12), 652 + 8 * DESPLAZ_X_MAX);
    comprobar("DX suelo", CAMPO(calcular(0, -100, 0, FORMATO_NORMAL).display, 0, 12), 652 - 8 * DESPLAZ_X_MAX);
    comprobar("DY tope", CAMPO(calcular(0, 0, 100, FORMATO_NORMAL).display, 12, 11), 50 + 2 * DESPLAZ_Y_MAX);
    comprobar("DY suelo", CAMPO(calcular(0, 0, -100, FORMATO_NORMAL).display, 12, 11), 50 - 2 * DESPLAZ_Y_MAX);
    // Una base en el borde no da valores negativos ni desborda el campo; DY
    // sigue par
    {
        BaseVideo alta = { 4090, 2040, 3, 0, 2560, 448 };
        BaseVideo baja = { 10, 4, 3, 0, 2560, 448 };
        OpcionesPort o;

        opciones_por_defecto(&o, 0);
        o.desplaz_x = DESPLAZ_X_MAX;
        o.desplaz_y = DESPLAZ_Y_MAX;
        calcular_registros_video(&alta, &o, &r);
        comprobar("DX campo", CAMPO(r.display, 0, 12), 0xFFF);
        comprobar("DY campo", CAMPO(r.display, 12, 11), 0x7FE);
        comprobar("MAGH intacto", CAMPO(r.display, 23, 4), 3);
        o.desplaz_x = -DESPLAZ_X_MAX;
        o.desplaz_y = -DESPLAZ_Y_MAX;
        calcular_registros_video(&baja, &o, &r);
        comprobar("DX cero", CAMPO(r.display, 0, 12), 0);
        comprobar("DY cero", CAMPO(r.display, 12, 11), 0);
    }

    printf("%d comprobaciones, %d fallo%s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "" : "s");
    return s_fallos != 0;
}
