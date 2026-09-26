#include <ultra64.h>
#include <juego/macros.h>
#include <juego/estructuras_comunes.h>
#include <juego/definiciones.h>
#include <libc/math.h>
#include <juego/mk64.h>

#include "carrera/camara.h"
#include "carrera/preparacion_carrera.h"
#include "sistema/matematicas.h"
#include "memoria/memoria_carrera.h"
#include "juego/camino.h"
#include "graficos/dibujar_jugador.h"
#include "carrera/colision.h"
#include "carrera/objetos_y_efectos.h"
#include "carrera/ia_vehiculos_y_camara.h"
#include "sistema/bucle_principal.h"
#include "carrera/aparicion_jugadores.h"

#include <juego/pista.h>
#include "camara/camara_jugador.inc.c"
#include "camara/efectos_camara.inc.c"