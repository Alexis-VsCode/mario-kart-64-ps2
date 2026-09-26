#include <ultra64.h>
#include <juego/macros.h>
#include <juego/pista.h>
#include <juego/estructuras_comunes.h>

#include "ceremonia/camara_ceremonia.h"
#include "carrera/camara.h"
#include "sistema/matematicas.h"
#include "ceremonia/ceremonia_y_creditos.h"
#include "sistema/bucle_principal.h"

void actualizar_ceremonia_podio_camara(void) {
    Camara* camara;
    f32 x_dist;
    f32 y_dist;
    f32 z_dist;

    camara = &camaras[0];
    funcion_80283648(camara);

    x_dist = camara->mirar_a[0] - camara->pos[0];
    y_dist = camara->mirar_a[1] - camara->pos[1];
    z_dist = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(x_dist, z_dist);
    camara->rot[0] = atan2s(sqrtf((x_dist * x_dist) + (z_dist * z_dist)), y_dist);
    camara->rot[2] = 0;
}

void inicializar_ceremonia_podio_camara(void) {
    camaras[0].pos[0] = -3133.0f;
    camaras[0].pos[1] = 19.0f;
    camaras[0].pos[2] = -467.0f;
    camaras[0].mirar_a[0] = -3478.0f;
    camaras[0].mirar_a[1] = 21.0f;
    camaras[0].mirar_a[2] = -528.0f;
    camaras[0].arriba[0] = 0.0f;
    camaras[0].arriba[1] = 1.0f;
    camaras[0].arriba[2] = 0.0f;
    acercar_camara[0] = 40.0f;
    aspecto_pantalla = 1.33333333f;
    circuito_cerca_persp = 3.0f;
    persp_lejos_circuito = 6800.0f;
    inicializar_camara_cinematica();
}
