#include <carrera/actores.h>

void actualizar_actor_mario_cartel(struct Actor* parametro0) {
    if ((parametro0->flags & 0x800) == 0) {
        if ((parametro0->flags & 0x400) != 0) {
            parametro0->pos[1] += 4.0f;
            if (parametro0->pos[1] > 800.0f) {
                parametro0->flags |= 0x800;
                parametro0->rot[1] += GRADOS(10);
            }
        } else {
            parametro0->rot[1] += GRADOS(1);
        }
    }
}
