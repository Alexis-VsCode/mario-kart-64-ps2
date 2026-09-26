#ifndef JUEGO_VEHICULOS_H
#define JUEGO_VEHICULOS_H

#include <juego/estructuras_comunes.h>

#define AUTOMOVILES_PASAJERO_NUM_1J 4
#define AUTOMOVILES_PASAJERO_NUM_2J 1
#define NUM_PASAJERO_AUTOMOVIL_ENTRADAS 5
#define NUM_TENDERS 1
#define TRENES_NUM 2
#define SOLO_LOCOMOTORA 0

#define CRUCES_NUM 2
#define FRAMES_DESDE_CRUCE_ACTIVADO 240

#define NUM_ACTIVO_PALETA_BARCOS 1
#define BARCOS_PALETA_NUM 2

#define NUM_CARRERA_CAJA_CAMIONES 7
#define NUM_CARRERA_ESCUELA_OMNIBUS 7
#define NUM_CARRERA_CISTERNA_CAMIONES 7
#define AUTOMOVILES_CARRERA_NUM 7

#define NUM_CONTRARRELOJ_CAMIONES_CAJA (NUM_CARRERA_CAJA_CAMIONES + 1)
#define NUM_CONTRARRELOJ_OMNIBUS_ESCUELA (NUM_CARRERA_ESCUELA_OMNIBUS + 1)
#define NUM_CONTRARRELOJ_CAMIONES_CISTERNA (NUM_CARRERA_CISTERNA_CAMIONES + 1)
#define NUM_CONTRARRELOJ_AUTOMOVILES (AUTOMOVILES_CARRERA_NUM + 1)

#define TREN_HUMO_RENDER_DISTANCIA 2000.0f
#define TREN_CRUCE_AI_DISTANCIA 1000.0f
#define BARCO_HUMO_RENDER_DISTANCIA 2000.0f

#define VEHICULO_RENDER 1

typedef struct {
     s16 activo_es;
     s16 margen_compilador;
     Vec3f position;
     Vec3f velocidad;
     u16 indice_punto_camino;
     s16 indice_actor;
     s32 unused;
} CosasAutomovilTren;

typedef struct {
     CosasAutomovilTren locomotora;
     CosasAutomovilTren tender;
     CosasAutomovilTren automoviles_pasajero[NUM_PASAJERO_AUTOMOVIL_ENTRADAS];
     f32 speed;
     s32 algun_banderas;
     s32 automoviles_num;
     s32 unused;
} CosasTren;

typedef struct {
     s16 activo_es;
     Vec3f position;
     Vec3f velocidad;
     u16 indice_punto_camino;
     s16 indice_actor;
     f32 speed;
     s16 rot_y;
     s32 algun_banderas;
} CosasBarcoPaleta;

typedef struct {
     s16 unused;
     Vec3f position;
     Vec3f velocidad;
     u16 indice_punto_camino;
     s16 indice_actor;
     f32 speed;
     f32 algun_secuela_el_multiplicador;
     Vec3s rotacion;
     s16 algun_tipo;
     s8 algun_banderas;
     s8 algun_secuela_el_banderas;
} CosasVehiculo;

extern CosasTren lista_tren[];

extern CosasBarcoPaleta barcos_paleta[];

extern CosasVehiculo lista_camion_caja[];
extern CosasVehiculo lista_omnibus_escuela[];
extern CosasVehiculo lista_camion_cisterna[];
extern CosasVehiculo lista_automovil[];

#endif
