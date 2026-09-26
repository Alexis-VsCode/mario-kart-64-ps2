#include <kernel.h>
#include <stdio.h>
#include <string.h>

#include <ultra64.h>
#include <PR/gbi.h>
#include <gsKit.h>

#include "graficos/sintetizador_gs.h"
#include "sistema/sistema_ps2.h"
#include "graficos/memoria_texturas.h"
#include "graficos/pantallas_gigantes.h"
#include "sistema/perfilado.h"
#include "memoria_texturas/cargas_tmem.inc.c"
#include "memoria_texturas/decodificar_y_cache.inc.c"
#include "memoria_texturas/preparar_textura.inc.c"