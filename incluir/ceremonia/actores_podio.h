#ifndef CEREMONIA_ACTORES_PODIO_H
#define CEREMONIA_ACTORES_PODIO_H

#include <juego/estructuras_comunes.h>

enum TipoActorCeremonia { Inicial, Globo, ConoFuegoArtificial, RafagaFuegoArtificial };

typedef struct {
     s32 desconocido0;
     s32 desconocido4;
     s32 temporizador_actor;
     u8 desconocido[16];
     s8 desconocido_1c;
     s8 desconocido_1d;
     s8 desconocido_1e;
} struct_d_802874D8;

typedef struct {
    s16 type;
    Vec3s desconocido2;
    s8 desconocido8;
    s8 desconocido9;
    s8 desconocido_a;
    s8 desconocido_b;
} ParamsInicializacionActor;

typedef struct {
     s32 activo_es;
     s16 type;
     s16 desconocido6;
     s8 desconocido8;
     s8 desconocido9;
     s16 desconocido_a;
     s16 desconocido_c;
     s16 desconocido_e;
     Vec3f pos;
     f32 desconocido_1c;
     f32 unk20;
     f32 unk24;
     ParamsInicializacionActor* params_inicializacion;
     s16 desconocido_2c;
     s16 desconocido_2e;
     s16 desconocido30;
     s16 desconocido32;
     s16 unk34;
     s16 desconocido36;
     f32 unk38;
     s32 temporizador;
     s32 desconocido40;
     s32 desconocido44;
     s32 desconocido48;
} ActorCeremonia;

typedef struct {
     s32 activo_es;
     s16 type;
     s16 desconocido6;
     s8 desconocido8;
     s8 desconocido9;
     s16 desconocido_a;
     s16 desconocido_c;
     s16 desconocido_e;
     Vec3f pos;
     f32 desconocido_1c;
     f32 unk20;
     f32 unk24;
     ParamsInicializacionActor* params_inicializacion;
     s32 desconocido_2c;
     s32 desconocido30;
     f32 unk34;
     f32 unk38;
     s32 desconocido_3c;
     s32 desconocido40;
     s32 desconocido44;
     s32 desconocido48;
} FuegoArtificial;

void actualizar_bucle_actores(void);
void funcion_80280650(void);
void fijar_posicion_inicial(ActorCeremonia*);
ActorCeremonia* buscar_entrada_disponible(void);
ActorCeremonia* actor_nuevo(ParamsInicializacionActor*);
u16 creditos_aleatorio_u16(void);
f32 flotante_aleatorio_entre_0_y_1(void);
f32 sabe_quien_aleatorio(f32);
void funcion_80280884(void);
void actualizar_y_rafaga_aparicion_cono_fuego_artificial(FuegoArtificial*);
void funcion_80280A28(Vec3f, Vec3s, f32);
void renderizar_fuegos_artificiales(Vec3f, f32, s32, s16);
void inicializar_globos_y_fuegos_artificiales(void);
void funcion_80280FFC(void);
void funcion_8028100C(s32, s32, s32);
void funcion_8028150C(void);
void funcion_80281520(void);
void funcion_80281528(void);
void funcion_80281530(void);
void funcion_80281538(void);
void funcion_80281540(void);
void bucle_ceremonia_podio(void);

extern struct_d_802874D8 dato_802874D8;
extern ActorCeremonia* lista_actor_podio;
extern s32 dato_802874FC;

extern ParamsInicializacionActor inicializar_globo_2;
extern ParamsInicializacionActor inicializar_cono;
extern ParamsInicializacionActor inicializar_desconocido_inicializacion;
extern ParamsInicializacionActor inicializar_rafaga;

extern Gfx* dato_802874D4;
extern s32 dato_802874FC;
extern Mat4 dato_80287500;

#endif
