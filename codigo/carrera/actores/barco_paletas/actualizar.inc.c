#include <ultra64.h>
#include <juego/tipos_actores.h>

void actualizar_barco_paleta_actor(struct BarcoRuedaPaleta* barco) {
    barco->rot_rueda += GRADOS(5);
}
