// Aspecto y cono de visibilidad de la vista panorámica (vista_panoramica.h)
#include <math.h>
#include <stdio.h>

#include "graficos/vista_panoramica.h"

static int s_fallos, s_comprobaciones;

static void comprobar_aspecto(f32 base, int formato, f32 esperado) {
    f32 obtenido = aspecto_panoramico(base, formato);

    s_comprobaciones++;
    if (fabsf(obtenido - esperado) > 0.001f) {
        s_fallos++;
        printf("FALLO aspecto %.4f formato %d: %.4f, se esperaba %.4f\n", base, formato, obtenido, esperado);
    }
}

static void comprobar_cono(unsigned angulo, int formato, unsigned esperado) {
    unsigned obtenido = cono_visibilidad(angulo, formato);

    s_comprobaciones++;
    if (obtenido != esperado) {
        s_fallos++;
        printf("FALLO cono %#x formato %d: %#x, se esperaba %#x\n", angulo, formato, obtenido, esperado);
    }
}

int main(void) {
    // Pantalla completa, dos jugadores uno encima de otro y uno al lado de otro
    comprobar_aspecto(1.33333334f, FORMATO_PANORAMICO, 1.7777778f);
    comprobar_aspecto(0.66666667f, FORMATO_PANORAMICO, 0.8888889f);
    comprobar_aspecto(2.66666667f, FORMATO_PANORAMICO, 3.5555556f);
    // Los otros formatos no cambian la proyección
    comprobar_aspecto(1.33333334f, FORMATO_NORMAL, 1.33333334f);
    comprobar_aspecto(0.66666667f, FORMATO_NORMAL, 0.66666667f);
    comprobar_aspecto(1.33333334f, FORMATO_CON_BANDAS, 1.33333334f);
    comprobar_aspecto(2.66666667f, FORMATO_CON_BANDAS, 2.66666667f);

    // Cono: 4/3 del ángulo en PANORÁMICO, sin pasar de una vuelta
    comprobar_cono(0x2AAB, FORMATO_PANORAMICO, 0x38E4);
    comprobar_cono(0x5555, FORMATO_PANORAMICO, 0x71C6);
    comprobar_cono(0xBFFF, FORMATO_PANORAMICO, 0xFFFE);
    comprobar_cono(0xC000, FORMATO_PANORAMICO, 0xFFFF);
    comprobar_cono(0xFFFF, FORMATO_PANORAMICO, 0xFFFF);
    comprobar_cono(0, FORMATO_PANORAMICO, 0);
    comprobar_cono(0x2AAB, FORMATO_NORMAL, 0x2AAB);
    comprobar_cono(0xFFFF, FORMATO_NORMAL, 0xFFFF);
    comprobar_cono(0x2AAB, FORMATO_CON_BANDAS, 0x2AAB);

    printf("%d comprobaciones, %d fallo%s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "" : "s");
    return s_fallos != 0;
}
