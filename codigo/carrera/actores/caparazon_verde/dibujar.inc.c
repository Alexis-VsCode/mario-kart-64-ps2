#include <carrera/actores.h>
#include <PR/gbi.h>
#include <sistema/bucle_principal.h>
#include <recursos/datos_comunes.h>

void renderizar_actor_caparazon_verde(Camara* camara, Mat4 matriz, struct ActorCaparazon* caparazon) {
    gDPLoadTLUT_pal256(display_list_cabeza++, tlut_comun_caparazon_verde);
    renderizar_caparazon_actor(camara, matriz, caparazon);
}
