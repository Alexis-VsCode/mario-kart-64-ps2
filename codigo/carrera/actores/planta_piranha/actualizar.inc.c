#include <carrera/actores.h>

void actualizar_actor_planta_piranha(struct PlantaPiranha* parametro0) {
    if ((parametro0->flags & 0x800) == 0) {
        if ((parametro0->flags & 0x400) != 0) {
            parametro0->pos[1] += 4.0f;
            if (parametro0->pos[1] > 800.0f) {
                parametro0->flags |= 0x800;
            }
        } else {
            if (parametro0->estados_visibilidad[0] == 1) {
                parametro0->temporizadores[0]++;
                if (parametro0->temporizadores[0] > 60) {
                    parametro0->temporizadores[0] = 6;
                }
            } else {
                parametro0->temporizadores[0] = 0;
            }
            if (parametro0->estados_visibilidad[1] == 1) {
                parametro0->temporizadores[1]++;
                if (parametro0->temporizadores[1] > 60) {
                    parametro0->temporizadores[1] = 6;
                }
            } else {
                parametro0->temporizadores[1] = 0;
            }
            if (parametro0->estados_visibilidad[2] == 1) {
                parametro0->temporizadores[2]++;
                if (parametro0->temporizadores[2] > 60) {
                    parametro0->temporizadores[2] = 6;
                }
            } else {
                parametro0->temporizadores[2] = 0;
            }
            if (parametro0->estados_visibilidad[3] == 1) {
                parametro0->temporizadores[3]++;
                if (parametro0->temporizadores[3] > 60) {
                    parametro0->temporizadores[3] = 6;
                }
            } else {
                parametro0->temporizadores[3] = 0;
            }
        }
    }
}
