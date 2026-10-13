// Marcador de la carrera en PANORÁMICO (hud_panoramico.h): estrechado a 3/4 en X
// alrededor del centro de su cuadrante, solo en la carrera y solo con la
// proyección ortográfica del marcador.
#include <math.h>
#include <stdio.h>

#include "graficos/hud_panoramico.h"
#include "juego/definiciones.h"

static int s_fallos, s_comprobaciones;

static void comprobar_x(float x, float centro, float ancho, float esperado) {
    float obtenido = hud_panoramico_x(x, centro, ancho);

    s_comprobaciones++;
    if (fabsf(obtenido - esperado) > 0.001f) {
        s_fallos++;
        printf("FALLO x %.2f centro %.2f ancho %.2f: %.4f, se esperaba %.4f\n", x, centro, ancho, obtenido, esperado);
    }
}

static void comprobar_estrechar(float x, int columnas, float esperado) {
    float obtenido = hud_panoramico_estrechar(x, columnas);

    s_comprobaciones++;
    if (fabsf(obtenido - esperado) > 0.001f) {
        s_fallos++;
        printf("FALLO estrechar %.2f columnas %d: %.4f, se esperaba %.4f\n", x, columnas, obtenido, esperado);
    }
}

static void comprobar_ref(float x, float ref, int columnas, float esperado) {
    float obtenido = hud_panoramico_estrechar_ref(x, ref, columnas);

    s_comprobaciones++;
    if (fabsf(obtenido - esperado) > 0.001f) {
        s_fallos++;
        printf("FALLO estrechar_ref %.2f ref %.2f columnas %d: %.4f, se esperaba %.4f\n", x, ref, columnas, obtenido, esperado);
    }
}

static void comprobar_entero(const char *que, int obtenido, int esperado) {
    s_comprobaciones++;
    if (obtenido != esperado) {
        s_fallos++;
        printf("FALLO %s: %d, se esperaba %d\n", que, obtenido, esperado);
    }
}

// Matrices que guOrtho deja en el juego (m00, m11, m22, m33)
static int activo(int formato, int estado, float l, float r, float b, float t, float n, float f) {
    return hud_panoramico_activo(formato, estado, 2.0f / (r - l), 2.0f / (t - b), -2.0f / (f - n), 1.0f);
}

int main(void) {
    // Función pura: 3/4 alrededor del centro
    comprobar_x(160.0f, 160.0f, 320.0f, 160.0f);
    comprobar_x(0.0f, 160.0f, 320.0f, 40.0f);
    comprobar_x(320.0f, 160.0f, 320.0f, 280.0f);
    comprobar_x(80.0f, 80.0f, 160.0f, 80.0f);
    comprobar_x(0.0f, 80.0f, 160.0f, 20.0f);
    comprobar_x(160.0f, 80.0f, 160.0f, 140.0f);
    comprobar_x(160.0f, 240.0f, 160.0f, 180.0f);
    comprobar_x(320.0f, 240.0f, 160.0f, 300.0f);
    comprobar_x(-40.0f, 160.0f, 320.0f, 10.0f); // marcador que entra por la izquierda
    comprobar_x(100.0f, 160.0f, 0.0f, 100.0f);  // cuadrante sin ancho: no se toca

    // Cuadrante según las columnas del modo de pantalla
    comprobar_entero("columnas 1P", hud_panoramico_columnas(MODO_PANTALLA_1P), 1);
    comprobar_entero("columnas 2J horizontal", hud_panoramico_columnas(PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL), 1);
    comprobar_entero("columnas 2J vertical", hud_panoramico_columnas(PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL), 2);
    comprobar_entero("columnas 3J/4J", hud_panoramico_columnas(PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA), 2);
    comprobar_entero("ancho 1 columna", (int) hud_panoramico_ancho_cuadrante(1), 320);
    comprobar_entero("ancho 2 columnas", (int) hud_panoramico_ancho_cuadrante(2), 160);

    // Una columna: centro de la pantalla
    comprobar_estrechar(0.0f, 1, 40.0f);
    comprobar_estrechar(160.0f, 1, 160.0f);
    comprobar_estrechar(280.0f, 1, 250.0f);
    // Dos columnas: centro de cada cuadrante (80 y 240)
    comprobar_estrechar(10.0f, 2, 27.5f);
    comprobar_estrechar(80.0f, 2, 80.0f);
    comprobar_estrechar(150.0f, 2, 132.5f);
    comprobar_estrechar(170.0f, 2, 187.5f);
    comprobar_estrechar(240.0f, 2, 240.0f);
    comprobar_estrechar(310.0f, 2, 292.5f);

    // Un rectángulo usa el cuadrante de su centro para los dos bordes: uno que cruza la mitad no se parte
    comprobar_ref(150.0f, 170.0f, 2, 172.5f);
    comprobar_ref(190.0f, 170.0f, 2, 202.5f);
    comprobar_ref(190.0f, 100.0f, 2, 162.5f);
    comprobar_ref(10.0f, 10.0f, 1, 47.5f);

    // Cuándo se aplica: solo PANORÁMICO, en la carrera y con la ortográfica del marcador
    comprobar_entero("HUD 1J panorámico", activo(FORMATO_PANORAMICO, CARRERA, 0, 320, 240, 0, -1, 1), 1);
    comprobar_entero("HUD 2J vertical panorámico", activo(FORMATO_PANORAMICO, CARRERA, 0, 160, 120, 0, -1, 1), 1);
    comprobar_entero("HUD 2J horizontal panorámico", activo(FORMATO_PANORAMICO, CARRERA, 0, 320, 120, 0, -1, 1), 1);
    comprobar_entero("HUD formato normal", activo(FORMATO_NORMAL, CARRERA, 0, 320, 240, 0, -1, 1), 0);
    comprobar_entero("HUD formato con bandas", activo(FORMATO_CON_BANDAS, CARRERA, 0, 320, 240, 0, -1, 1), 0);
    comprobar_entero("HUD fuera de la carrera (menús)", activo(FORMATO_PANORAMICO, 1, 0, 320, 240, 0, -1, 1), 0);
    comprobar_entero("HUD en la ceremonia", activo(FORMATO_PANORAMICO, 5, 0, 320, 240, 0, -1, 1), 0);
    comprobar_entero("cielo ortográfico", activo(FORMATO_PANORAMICO, CARRERA, 0, 320, 0, 240, 0, 5), 0);
    comprobar_entero("texto de menús en carrera", activo(FORMATO_PANORAMICO, CARRERA, 0, 319, 239, 0, -100, 100), 0);
    comprobar_entero("3D en perspectiva", hud_panoramico_activo(FORMATO_PANORAMICO, CARRERA, 0.5f, 0.8f, -1.002f, 0.0f), 0);

    // Rectángulos con color: las cajas del marcador sí, los fundidos a pantalla completa no
    comprobar_entero("caja del marcador 1J", hud_panoramico_rect_estrechable(100.0f, 180.0f, 1), 1);
    comprobar_entero("fundido a pantalla completa 1J", hud_panoramico_rect_estrechable(0.0f, 320.0f, 1), 0);
    comprobar_entero("fundido de un cuadrante", hud_panoramico_rect_estrechable(0.0f, 160.0f, 2), 0);
    comprobar_entero("caja del marcador de un cuadrante", hud_panoramico_rect_estrechable(100.0f, 140.0f, 2), 1);

    printf("%d comprobaciones, %d fallo%s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "" : "s");
    return s_fallos != 0;
}
