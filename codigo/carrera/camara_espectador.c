#include <juego/tipos_actores.h>
#include "sistema/bucle_principal.h"
#include "carrera/preparacion_carrera.h"
#include "carrera/camara_espectador.h"
#include "carrera/camara.h"
#include "sistema/matematicas.h"
#include "carrera/colision.h"

void funcion_800914A0(void) {
    dato_80152308 = copia_jugador_uno->desconocido_006 + 7;
    if ((s32) dato_8015F6F8 < dato_80152308) {
        dato_80152308 -= dato_8015F6F8;
    }
}

SIN_USO void funcion_800914E0(void) {
    SIN_USO Vec3f sp64 = { 0.0f, -20.0f, 150.0f };
    SIN_USO Vec3f sp58 = { 0.0f, -6.0f, 4.0f };
    uintptr_t segmento = SEGMENT_NUMBER2(dato_8015F718[0]);
    uintptr_t desplazamiento = SEGMENT_OFFSET(dato_8015F718[0]);
    Camara* camara = &camaras[0];
    struct DatosAparicionActor* sp48 = (struct DatosAparicionActor*) VIRTUAL_A_PHYSICAL2(tabla_segmento[segmento] + desplazamiento);
    struct DatosAparicionActor* datos_temporal;

    s16 temporal3 = (s16) dato_80152308;
    s16 temporal2 = (s16) copia_jugador_uno->desconocido_006;
    s16 temporal_;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    camara->arriba[0] = 0;
    camara->arriba[1] = 1;
    camara->arriba[2] = 0;

    if (1) {}

    temporal_ = temporal2 - temporal3;
    if (temporal_ == 7) {
        funcion_800914A0();
    } else if (temporal_ < 14) {
        temporal_ += (s16) dato_8015F6F8;
        if (temporal_ == 7) {
            funcion_800914A0();
        }
    }
    datos_temporal = sp48 + dato_80152308;

    camara->pos[0] = (f32) (datos_temporal->pos[0] + 10);
    camara->pos[1] = (f32) (datos_temporal->pos[1] + 7);
    camara->pos[2] = (f32) (datos_temporal->pos[2] - 20);
    camara->mirar_a[0] = copia_jugador_uno->pos[0];

    camara->mirar_a[1] = copia_jugador_uno->pos[1];
    camara->mirar_a[2] = copia_jugador_uno->pos[2];
    comprobar_colision_envolvente(&camara->colision, 20.0f, camara->pos[0], camara->pos[1], camara->pos[2]);
    sp38 = camara->mirar_a[0] - camara->pos[0];
    sp34 = camara->mirar_a[1] - camara->pos[1];
    sp30 = camara->mirar_a[2] - camara->pos[2];
    camara->rot[1] = atan2s(sp38, sp30);
    camara->rot[0] = atan2s(sqrtf((sp38 * sp38) + (sp30 * sp30)), sp34);
    camara->rot[2] = 0;
}
