#include <carrera/actores.h>

void actualizar_actor_caja_item_globo_aerostatico(struct CajaItem* caja_item) {
    switch (caja_item->state) {
        case 5:
            caja_item->rot[0] += GRADOS(1);
            caja_item->rot[1] -= GRADOS(2);
            caja_item->rot[2] += GRADOS(1);
            break;
        case 3:
            if (caja_item->algun_temporizador == 0x14) {
                caja_item->state = 5;
                caja_item->flags = -0x4000;
            } else {
                caja_item->algun_temporizador++;
                caja_item->rot[0] += GRADOS(6);
                caja_item->rot[1] -= GRADOS(4);
                caja_item->rot[2] += GRADOS(2);
            }
            break;
    }
}

void actualizar_actor_caja_item(struct CajaItem* caja_item) {
    switch (caja_item->state) {
        case 0:
            caja_item->state = 1;
            break;
        case 1:
            if ((caja_item->pos[1] - caja_item->orig_y) < 8.66f) {
                caja_item->pos[1] += 0.45f;
            } else {
                caja_item->pos[1] = caja_item->orig_y + 8.66f;
                caja_item->state = 2;
                caja_item->flags = 0xC000;
            }
            break;
        case 2:
            caja_item->rot[0] += GRADOS(1);
            caja_item->rot[1] -= GRADOS(2);
            caja_item->rot[2] += GRADOS(1);
            break;
        case 3:
            if (caja_item->algun_temporizador == 20) {
                caja_item->state = 0;
                caja_item->pos[1] = caja_item->distancia_reinicio - 20.0f;
                caja_item->flags = 0xC000;
            } else {
                caja_item->algun_temporizador++;
                caja_item->rot[0] += GRADOS(6);
                caja_item->rot[1] -= GRADOS(4);
                caja_item->rot[2] += GRADOS(2);
            }
            break;
    }
}
