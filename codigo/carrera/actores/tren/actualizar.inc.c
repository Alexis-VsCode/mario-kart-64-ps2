#include <carrera/actores.h>

void actualizar_motor_tren_actor(struct AutomovilTren* parametro0) {
    parametro0->rot_rueda -= GRADOS(9);

    if (parametro0->desconocido_08 != 0.0f) {
        parametro0->desconocido_08 = 0.0f;
        funcion_800C9D80(parametro0->pos, parametro0->velocidad, SONIDO_CARGA_PARAMETRO(0x51, 0x01, 0x80, 0x00));
    }
}

void actualizar_tender_tren_actor(struct AutomovilTren* tender) {
    tender->rot_rueda -= GRADOS(7);
}

void actualizar_actor_tren_pasajero_automovil(struct AutomovilTren* parametro0) {
    parametro0->rot_rueda -= GRADOS(9);
}
