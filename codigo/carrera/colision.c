#include <ultra64.h>
#include <juego/macros.h>
#include <PR/gbi.h>
#include <juego/estructuras_comunes.h>
#include <juego/mk64.h>
#include <juego/tipos_actores.h>
#include <juego/pista.h>

#include "sistema/bucle_principal.h"
#include "memoria/memoria_carrera.h"
#include "carrera/colision.h"
#include "sistema/matematicas.h"
#include "carrera/preparacion_carrera.h"
#include <juego/definiciones.h>
#include "colision/superficies.inc.c"
#include "colision/paredes_y_triangulos.inc.c"
#include "colision/cuadricula_colision.inc.c"