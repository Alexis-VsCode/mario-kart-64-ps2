#include <carrera/actores.h>

void actualizar_actor_yoshi_huevo(struct YoshiValleyHuevo* huevo) {
    huevo->rot_camino += 0x5B;
    huevo->pos[0] = huevo->centro_camino[0] + (senos(huevo->rot_camino) * huevo->radio_camino);
    huevo->pos[2] = huevo->centro_camino[2] + (coss(huevo->rot_camino) * huevo->radio_camino);
    if ((huevo->flags & 0x400) != 0) {
        huevo->centro_camino[1] -= 0.12;
        if (huevo->centro_camino[1] < -3.0f) {
            huevo->centro_camino[1] = -3.0f;
        }
        huevo->pos[1] += huevo->centro_camino[1];
        if (huevo->pos[1] < 0.0f) {
            huevo->pos[1] = 0.0f;
            huevo->centro_camino[1] = 0.0f;
            huevo->flags &= ~(1 << 10);
        }
        huevo->rot_huevo -= GRADOS(7);
    }
    huevo->rot_huevo -= GRADOS(3);
}
