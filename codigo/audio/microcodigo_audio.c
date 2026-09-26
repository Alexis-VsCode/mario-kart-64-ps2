#include <stdio.h>
#include <string.h>

#include <ultra64.h>
#include <PR/abi.h>

#include "audio/microcodigo_audio.h"
#ifdef SMK64_DEV
#include "sistema/sistema_ps2.h"
#endif
#include "microcodigo_audio/mezcla_y_adpcm.inc.c"
#include "microcodigo_audio/ejecutar_tareas.inc.c"