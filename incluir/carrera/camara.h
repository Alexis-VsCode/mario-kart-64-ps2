#ifndef CARRERA_CAMARA_H
#define CARRERA_CAMARA_H

#include <juego/estructuras_comunes.h>

#ifdef AVOID_UB
#define RETORNO_MALO(cmd) void
#else
#define RETORNO_MALO(cmd) cmd
#endif

typedef struct {
    f32 desconocido_0;
    s16 desconocido_4;
    s16 desconocido_6;
    s16 desconocido_8;
} InteriorCamaraDesconocido;

typedef struct {
     Vec3f pos;
     Vec3f mirar_a;
     Vec3f arriba;
     Vec3s rot;
     u16 algun_banderas_bit;
     s16 desconocido_2C;
     s16 desconocido_2E;
     Vec3f desconocido_30;
     Vec3f desconocido_3C;
     s32 desconocido_48;
     s32 desconocido_4C;
     s32 desconocido_50;
     Colision colision;
     InteriorCamaraDesconocido desconocido_94;
     f32 desconocido_A0;
     s32 desconocido_A4;
     s32 desconocido_A8;
     s16 desconocido_ac;
     s16 id_jugador;
     s16 desconocido_B0;
     s16 desconocido_B2;
     f32 desconocido_B4;
} Camara;

void inicializar_camara(f32, f32, f32, s16, u32, s32);
void funcion_8001CA10(Camara*);
void funcion_8001CA24(Jugador*, f32);
void funcion_8001CA78(Jugador*, Camara*, Vec3f, f32*, f32*, f32*, s32, s32);
void funcion_8001CCEC(Jugador*, Camara*, Vec3f, f32*, f32*, f32*, s32*, s16, s16);
void funcion_8001D53C(Jugador*, Camara*, Vec3f, f32*, f32*, f32*, s16, s16);
void funcion_8001D794(Jugador*, Camara*, Vec3f, f32*, f32*, f32*, s16);
void funcion_8001D944(Jugador*, Camara*, Vec3f, f32*, f32*, f32*, s32*, s16, s16);
void funcion_8001E0C4(Camara*, Jugador*, s8);
void funcion_8001E45C(Camara*, Jugador*, s8);
void funcion_8001E8E8(Camara*, Jugador*, s8);
void funcion_8001EA0C(Camara*, Jugador*, s8);
void funcion_8001EE98(Jugador*, Camara*, s8);
void funcion_8001F394(Jugador*, f32*);
void funcion_8001F87C(s32);

extern f32 dato_800DDB30[];

extern Camara camaras[];
extern Camara* camara1;
extern Camara* camara2;
extern Camara* camara3;
extern Camara* camara4;

extern s8 dato_80164A89;

extern s32 dato_80164A08[4];

extern s32 dato_80164A28;
extern s32 dato_80164A2C;
extern f32 dato_80164A30;
extern f32 dato_80164A90[];
extern f32 dato_80164AA0[];

#endif
