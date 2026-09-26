#include <carrera/actores.h>

void actualizar_actor_paso_a_nivel(struct PasoANivel* cruce) {
    if (es_cruce_disparado_por_indice[cruce->id_cruce] != 0) {
        // Timer++
        cruce->algun_temporizador++;
        // Reset timer
        if (cruce->algun_temporizador > 40) {
            cruce->algun_temporizador = 1;
        }
        if ((cruce->algun_temporizador == 1) || (cruce->algun_temporizador == 20)) {
            funcion_800C98B8(cruce->pos, cruce->velocidad, SONIDO_CARGA_PARAMETRO(0x19, 0x01, 0x70, 0x16));
        }
    }
}
