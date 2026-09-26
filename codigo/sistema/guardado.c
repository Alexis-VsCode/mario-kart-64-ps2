#include <ultra64.h>
#include <juego/macros.h>
#include <juego/definiciones.h>
#include "stddef.h"

#include "sistema/guardado.h"

#include "menus/elementos_menu.h"
#include "menus/menus.h"
#include "juego/datos_guardado.h"
#include "carrera/repeticiones.h"
#include "carrera/objetos_y_efectos.h"

/* * macros ** */
#define CODIGO_EMPRESA_PFS(c0, c1) ((u16) (((c0) << 8) | ((c1))))
#define CODIGO_JUEGO_PFS(c0, c1, c2, c3) ((u32) (((c0) << 24) | ((c1) << 16) | ((c2) << 8) | (c3)))
#define DIRECCION_EEPROM(ptr) (((uintptr_t) (ptr) - (uintptr_t) (&datos_guardado)) / 8)

struct_8018EE10_entrada dato_8018EE10[2];

u16 codigo_empresa = CODIGO_EMPRESA_PFS('0', '1');
u32 codigo_juego = CODIGO_JUEGO_PFS('N', 'K', 'T', 'J');
s8 controller_pak_1_estado = MALO;
s8 controller_pak_2_estado = MALO;

const u8 dato_800F2E60[4] = { 0xc0, 0x27, 0x09, 0x00 };
const u8 nombre_juego[] = {
    0x26, 0x1a, 0x2b, 0x22, 0x28, 0x24, 0x1a, 0x2b, 0x2d, 0x16, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00
};
const u8 codigo_ext[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void funcion_800B45E0(s32 parametro0) {
    CircuitoContrarrelojRegistros* circuito_contrarreloj_ptr_registros =
        &datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[parametro0 / 4].registros_circuito[parametro0 % 4];

    circuito_contrarreloj_ptr_registros->checksum = suma_control_contrarreloj_registros(parametro0);
    osEepromLongWrite(&si_evento_msj_cola, DIRECCION_EEPROM(circuito_contrarreloj_ptr_registros), (u8*) circuito_contrarreloj_ptr_registros,
                      sizeof(CircuitoContrarrelojRegistros));
}

void guardar_datos_gran_premio_puntos_y_modo_sonido_escritura(void) {
    Cosas* main = &datos_guardado.main;
    main->checksum[1] = guardar_suma_control_datos_calcular_1();
    main->checksum[2] = guardar_suma_control_datos_calcular_2();
    osEepromLongWrite(&si_evento_msj_cola, DIRECCION_EEPROM(main), (u8*) main, sizeof(Cosas));
}

void funcion_800B46D0(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        funcion_800B4728(i);
        funcion_800B559C(i);
    }

    guardar_datos_gran_premio_puntos_y_modo_sonido_reinicio();
    guardar_respaldo_datos_actualizacion();
}

void funcion_800B4728(s32 parametro0) {
    s32 i, j;
    CircuitoContrarrelojRegistros* circuito_contrarreloj_registros;

    circuito_contrarreloj_registros = &datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[parametro0 / 4].registros_circuito[parametro0 % 4];

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            circuito_contrarreloj_registros->registros[i][j] = dato_800F2E60[j];
        }
    }

    for (i = 0; i < 3; i++) {
        circuito_contrarreloj_registros->registros[5][i] = dato_800F2E60[i];
    }

    circuito_contrarreloj_registros->bytes_desconocido[0] = 0;
    circuito_contrarreloj_registros->checksum = suma_control_contrarreloj_registros(parametro0);
    funcion_800B45E0(parametro0);
}

void guardar_datos_gran_premio_puntos_y_modo_sonido_reinicio(void) {
    s32 indice_copa;
    Cosas* main = &datos_guardado.main;
    for (indice_copa = 0; indice_copa < 4; indice_copa++) {
        main->info_guardado.gran_premio_puntos[indice_copa] = 0;
    }
    main->info_guardado.sonido_modo = SONIDO_ESTEREO;
    sonido_modo = SONIDO_ESTEREO;
    fijar_modo_sonido();
    guardar_datos_gran_premio_puntos_y_modo_sonido_escritura();
}

u8 suma_control_contrarreloj_registros(s32 idx_circuito) {
    s32 j;
    s32 i;
    s32 devuelto;
    u8* registros = datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[idx_circuito / 4].registros_circuito[idx_circuito % 4].registros[0];

    devuelto = 0;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 3; j++) {
            devuelto += *(registros + i * 3 + j) * (j + 1) + i;
        }
    }

    return devuelto % 256;
}

u8 guardar_suma_control_datos_calcular_1(void) {
    u8* gran_premio_puntos = (u8*) &datos_guardado.main.info_guardado.gran_premio_puntos;
    u32 i;
    s32 crc = 0;

    for (i = 0; i < sizeof(InfoGuardado); i++) {
        crc += ((gran_premio_puntos[i] + 1) * (i + 1)) + i;
    }

    return crc % 0x100;
}

u8 guardar_suma_control_datos_calcular_2(void) {
    s32 tmp = datos_guardado.main.checksum[1] + 90;
    return (tmp % 256);
}

void guardar_datos_carga(void) {
    s32 i;

    osEepromLongRead(&si_evento_msj_cola, DIRECCION_EEPROM(&datos_guardado), (u8*) &datos_guardado, sizeof(DatosGuardado));
    for (i = 0; i < 16; i++) {
        funcion_800B4A9C(i);
    }

    guardar_datos_validar();

    sonido_modo = datos_guardado.main.info_guardado.sonido_modo;
    if (sonido_modo >= MODOS_SONIDO_NUM) {
        sonido_modo = SONIDO_MONO;
    }
}

void funcion_800B4A9C(s32 circuito) {
    MejorSoloContrarrelojRegistros* probar;
    CircuitoContrarrelojRegistros* sp24;
    s32 i;

    if ((funcion_800B4EB4(0, circuito) & 0xFFFFF) < 0x927C0U) {
        datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[circuito / 4].registros_circuito[circuito % 4].bytes_desconocido[0] = 1;
    }
    sp24 = &datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[circuito / 4].registros_circuito[circuito % 4];

    funcion_800B4FB0(circuito);
    if (sp24) {}

    if (sp24->checksum != suma_control_contrarreloj_registros(circuito)) {
        funcion_800B4728(circuito);
        if (funcion_800B58C4(circuito) == 0) {
            s32 a3 = 0;

            probar = &datos_guardado.mejor_solo_contrarreloj_registros[circuito / 8];
            for (i = 0; i < 3; i++) {
                sp24->registros[CONTRARRELOJ_3LAP_REGISTRO_1][i] = probar->tres_vueltas_mejor[circuito % 8][i];
                sp24->registros[CONTRARRELOJ_1LAP_REGISTRO][i] = probar->vueltas_simples_mejor[circuito % 8][i];

                if (sp24->registros[CONTRARRELOJ_3LAP_REGISTRO_1][i] == dato_800F2E60[i]) {
                    if (sp24->registros[CONTRARRELOJ_1LAP_REGISTRO][i] == dato_800F2E60[i]) {
                        a3 += 1;
                    }
                }
            }

            if (a3 == 3) {
                sp24->bytes_desconocido[0] = 0;
            } else {
                sp24->bytes_desconocido[0] = 1;
            }
            funcion_800B45E0(circuito);
        }
        funcion_800B559C(circuito);
    } else if (funcion_800B58C4(circuito)) {
        funcion_800B559C(circuito);
    }
}

void guardar_datos_validar(void) {
    s32 indice_copa;
    Cosas* main = &datos_guardado.main;
    Cosas* respaldo = &datos_guardado.respaldo;
    if (main->checksum[1] != (guardar_suma_control_datos_calcular_1()) ||
        (main->checksum[2] != guardar_suma_control_datos_calcular_2())) {
        guardar_datos_gran_premio_puntos_y_modo_sonido_reinicio();

        if (guardar_respaldo_suma_control_datos_validar() == 0) {
            for (indice_copa = 0; indice_copa < 4; indice_copa++) {
                main->info_guardado.gran_premio_puntos[indice_copa] = respaldo->info_guardado.gran_premio_puntos[indice_copa];
            }

            main->info_guardado.sonido_modo = respaldo->info_guardado.sonido_modo;
            main->checksum[1] = guardar_respaldo_suma_control_datos_calcular_1();
            main->checksum[2] = guardar_respaldo_suma_control_datos_calcular_2();
            osEepromLongWrite(&si_evento_msj_cola, DIRECCION_EEPROM(main), (u8*) main, sizeof(Cosas));
        }
        guardar_respaldo_datos_actualizacion();
        return;
    }

    if (guardar_respaldo_suma_control_datos_validar() != 0) {
        guardar_respaldo_datos_actualizacion();
    }
}

void poblar_contrarreloj_registro(u8* contrarreloj_registro, u32 time, s32 id_personaje) {
    u32 desplaz_derecha_tiempo_8 = time >> 8;
    u32 desplaz_derecha_tiempo_16 = desplaz_derecha_tiempo_8 >> 8;
    s16 tiempo_derecha_desplaz_8_duplicar;
    u16 tiempo_derecha_desplaz_16_duplicar;

    tiempo_derecha_desplaz_16_duplicar = desplaz_derecha_tiempo_16;

    contrarreloj_registro[0] = time & 0xFF;
    contrarreloj_registro[1] = (tiempo_derecha_desplaz_8_duplicar = desplaz_derecha_tiempo_8);
    contrarreloj_registro[2] = (tiempo_derecha_desplaz_16_duplicar & 0xF) + ((id_personaje & 7) << 4);
}

u32 funcion_800B4DF4(u8* arr) {
    s32 a, b, c;
    a = arr[0];
    b = arr[1];
    c = arr[2];

    return (a + (b << 8) + (c << 16)) & 0x00FFFFFF;
}

s32 funcion_800B4E24(s32 grabar_indice) {
    return funcion_800B4DF4(datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[(((seleccion_copa * 4) + indice_circuito_en_copa) / 4)]
                             .registros_circuito[(((seleccion_copa * 4) + indice_circuito_en_copa) % 4)]
                             .registros[grabar_indice]);
}

u32 funcion_800B4EB4(s32 grabar_indice, s32 indice_circuito) {
    return funcion_800B4DF4(datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[(indice_circuito / 4)]
                             .registros_circuito[(indice_circuito % 4)]
                             .registros[grabar_indice]);
}

s32 funcion_800B4F2C(void) {
    return funcion_800B4DF4(datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[(((seleccion_copa * 4) + indice_circuito_en_copa) / 4)]
                             .registros_circuito[(((seleccion_copa * 4) + indice_circuito_en_copa) % 4)]
                             .registros[CONTRARRELOJ_1LAP_REGISTRO]);
}

s32 funcion_800B4FB0(s32 indice_circuito) {
    return funcion_800B4DF4(datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[(indice_circuito / 4)]
                             .registros_circuito[(indice_circuito % 4)]
                             .registros[CONTRARRELOJ_1LAP_REGISTRO]);
}

s32 funcion_800B5020(u32 time, s32 id_car) {
    SIN_USO s32 margen_pila[3];
    s32 circuito;
    s32 i;
    s32 j;
    CircuitoContrarrelojRegistros* tt;

    circuito = seleccion_copa * 4 + indice_circuito_en_copa;
    tt = &datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[circuito / 4].registros_circuito[circuito % 4];

    i = 0;
    for (; i < 5; i++) {
        if (time < (funcion_800B4DF4(tt->registros[i]) & 0x000FFFFF)) {
            break;
        }
    }

    if (i >= 5) {
        return -1;
    }

    for (j = CONTRARRELOJ_3LAP_REGISTRO_5; j > i; j--) {
        tt->registros[j][0] = tt->registros[j - 1][0];
        tt->registros[j][1] = tt->registros[j - 1][1];
        tt->registros[j][2] = tt->registros[j - 1][2];
    }

    poblar_contrarreloj_registro(tt->registros[i], time, id_car);
    tt->bytes_desconocido[0] = 1;
    funcion_800B45E0(circuito);

    return i;
}

s32 funcion_800B5218(void) {
    u8* grabar_puntero;
    SIN_USO s32 relleno;
    s32 indice_vuelta_mas_rapido;
    s32 grabar_indice;
    SIN_USO s32 relleno2[2];
    s32 comprobar_indice_vuelta;
    s32 character;
    s32 mascara_bits_vuelta;
    grabar_indice = (seleccion_copa * 4) + indice_circuito_en_copa;
    grabar_puntero =
        &datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[grabar_indice / 4].registros_circuito[grabar_indice % 4].registros[0][0];
    mascara_bits_vuelta = 1;
    indice_vuelta_mas_rapido = 0;
    character = *selecciones_personaje;
    for (comprobar_indice_vuelta = 1; comprobar_indice_vuelta != 3; comprobar_indice_vuelta++) {
        if ((s32)h_ud_jugador->duraciones_vuelta[comprobar_indice_vuelta] < (s32)h_ud_jugador->duraciones_vuelta[indice_vuelta_mas_rapido]) {
            mascara_bits_vuelta = 1 << comprobar_indice_vuelta;
            indice_vuelta_mas_rapido = comprobar_indice_vuelta;
        } else if ((s32)h_ud_jugador->duraciones_vuelta[indice_vuelta_mas_rapido] == (s32)h_ud_jugador->duraciones_vuelta[comprobar_indice_vuelta]) {
            mascara_bits_vuelta |= 1 << comprobar_indice_vuelta;
        }
    }

    if (h_ud_jugador->duraciones_vuelta[indice_vuelta_mas_rapido] < (funcion_800B4F2C() & 0xFFFFF)) {
        poblar_contrarreloj_registro(grabar_puntero + 0xF, h_ud_jugador->duraciones_vuelta[indice_vuelta_mas_rapido], character);
        grabar_puntero[0x12] = 1;
        funcion_800B45E0(grabar_indice);
        return mascara_bits_vuelta;
    } else {
        return 0;
    }
}

void funcion_800B536C(s32 parametro0) {
    u8* puntos;
    u8 tmp;
    s32 tmp2;

    if (parametro0 >= 0) {
        puntos = &datos_guardado.main.info_guardado.gran_premio_puntos[seleccion_cc];
        tmp = funcion_800B54EC(seleccion_copa, *puntos);
        tmp2 = 3 - parametro0;
        if ((parametro0 < 3) && (tmp < (3 - parametro0))) {
            *puntos = funcion_800B5508(seleccion_copa, *puntos, tmp2);
            guardar_datos_gran_premio_puntos_y_modo_sonido_escritura();
            guardar_respaldo_datos_actualizacion();
        }
    }
}

void funcion_800B5404(s32 parametro0, s32 parametro1) {
    u8* puntos;
    s32 temporal_a0;
    s32 temporal_;
    int temporal2;
    SIN_USO s32 relleno;

    if (parametro0 >= 0) {
        temporal2 = parametro1 / 4;
        puntos = &datos_guardado.main.info_guardado.gran_premio_puntos[parametro1 % 4];
        temporal_ = funcion_800B54EC(temporal2, *puntos);

        if ((parametro0 < 3) && (temporal_ < (temporal_a0 = 3 - parametro0))) {
            *puntos = funcion_800B5508(temporal2, *puntos, temporal_a0);

            guardar_datos_gran_premio_puntos_y_modo_sonido_escritura();
            guardar_respaldo_datos_actualizacion();
        }
    }
}

u8 funcion_800B54C0(s32 copa, s32 modo_cc) {
    return funcion_800B54EC(copa, datos_guardado.main.info_guardado.gran_premio_puntos[modo_cc]);
}

u8 funcion_800B54EC(s32 copa, s32 cc_gran_premio_puntos) {
    s32 indice_copa = copa * 2;
    u32 puntos_copa = cc_gran_premio_puntos;

    puntos_copa &= (3 << indice_copa);
    puntos_copa >>= indice_copa;
    puntos_copa &= 0xFF;

    return puntos_copa;
}

u8 funcion_800B5508(s32 copa, s32 cc_gran_premio_puntos, s32 puntos_anotado) {
    s32 indice_copa = copa * 2;

    puntos_anotado <<= indice_copa;
    cc_gran_premio_puntos &= ~(3 << indice_copa);

    return (cc_gran_premio_puntos | puntos_anotado);
}

bool es_completo_modo_cc(s32 modo_cc) {
    if (datos_guardado.main.info_guardado.gran_premio_puntos[modo_cc] == 0xFF) {
        return true;
    }
    return false;
}

s32 tiene_modo_extra_desbloqueado(void) {
    return es_completo_modo_cc(CC_150);
}

s32 tiene_modo_extra_completado(void) {
    return es_completo_modo_cc(CC_EXTRA);
}

void funcion_800B559C(s32 parametro0) {
    CircuitoContrarrelojRegistros* registro_circuito;
    MejorSoloContrarrelojRegistros* registro_mejor;
    s32 x = parametro0 / 8;
    s32 i;
    s32 j;
    for (i = x * 8; i < ((x * 8) + 8); i++) {
        registro_mejor = &datos_guardado.mejor_solo_contrarreloj_registros[x];
        registro_circuito = &datos_guardado.todos_circuito_contrarreloj_registros.registros_copa[i / 4].registros_circuito[i % 4];
        if (registro_circuito->checksum != suma_control_contrarreloj_registros(i)) {
            for (j = 0; j < 3; j++) {
                registro_mejor->tres_vueltas_mejor[i % 8][j] = dato_800F2E60[j];
                registro_mejor->vueltas_simples_mejor[i % 8][j] = dato_800F2E60[j];
            }
        } else {
            for (j = 0; j < 3; j++) {
                registro_mejor->tres_vueltas_mejor[i % 8][j] = registro_circuito->registros[0][j];
                registro_mejor->vueltas_simples_mejor[i % 8][j] = registro_circuito->registros[0][j + 0x0f];
            }
        }
    }
    registro_mejor = &datos_guardado.mejor_solo_contrarreloj_registros[x];
    registro_mejor->bytes_desconocido[6] = funcion_800B578C(x);
    registro_mejor->bytes_desconocido[7] = funcion_800B5888(x);
    osEepromLongWrite(&si_evento_msj_cola, ((u32) (((u8*) registro_mejor) - ((u8*) (&datos_guardado)))) >> 3,
                      registro_mejor->tres_vueltas_mejor[0], 0x38);
}

u8 funcion_800B578C(s32 parametro0) {
    u8* times = (u8*)&datos_guardado.mejor_solo_contrarreloj_registros[parametro0];
    s32 checksum = 0;
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 0x11; j++) {
            checksum += (times[i * 0x11 + j] + 1) * (i + 1) + j;
        }
    }
    return (checksum % 256);
}

s32 funcion_800B5888(s32 parametro0) {
    s32 tmp = datos_guardado.mejor_solo_contrarreloj_registros[parametro0].bytes_desconocido[6] + 90;
    return (tmp % 256) & 0xFF;
}

s32 funcion_800B58C4(s32 parametro0) {
    SIN_USO s32 relleno1;
    MejorSoloContrarrelojRegistros* temporal_v1;
    SIN_USO s32 relleno2;
    SIN_USO s32 relleno3;

    temporal_v1 = &datos_guardado.mejor_solo_contrarreloj_registros[parametro0 / 8];
    if ((temporal_v1->bytes_desconocido[6] != (funcion_800B578C(parametro0 / 8) ^ 0)) ||
        (temporal_v1->bytes_desconocido[7] != (funcion_800B5888(parametro0 / 8) ^ 0))) {
        return 1;
    }

    return 0;
}

void guardar_respaldo_datos_actualizacion(void) {
    s32 indice_copa;
    Cosas* main = &datos_guardado.main;
    Cosas* respaldo = &datos_guardado.respaldo;
    for (indice_copa = 0; indice_copa < COPAS_NUM - 1; indice_copa++) {
        respaldo->info_guardado.gran_premio_puntos[indice_copa] = main->info_guardado.gran_premio_puntos[indice_copa];
    }
    respaldo->info_guardado.sonido_modo = main->info_guardado.sonido_modo;
    respaldo->checksum[1] = guardar_respaldo_suma_control_datos_calcular_1();
    respaldo->checksum[2] = guardar_respaldo_suma_control_datos_calcular_2();
    osEepromLongWrite(&si_evento_msj_cola, DIRECCION_EEPROM(respaldo), (u8*) respaldo, sizeof(Cosas));
}

u8 guardar_respaldo_suma_control_datos_calcular_1(void) {
    u8* respaldo_gran_premio_puntos = datos_guardado.respaldo.info_guardado.gran_premio_puntos;
    u32 i;
    s32 crc = 0;

    for (i = 0; i < sizeof(InfoGuardado); i++) {
        crc += ((respaldo_gran_premio_puntos[i] + 1) * (i + 1)) + i;
    }

    return crc % 0x100;
}

u8 guardar_respaldo_suma_control_datos_calcular_2(void) {
    s32 tmp = datos_guardado.respaldo.checksum[1] + 90;
    return (tmp % 256);
}

s32 guardar_respaldo_suma_control_datos_validar(void) {
    u8* suma_control_respaldo = datos_guardado.respaldo.checksum;
    if (suma_control_respaldo[1] != guardar_respaldo_suma_control_datos_calcular_1() ||
        suma_control_respaldo[2] != guardar_respaldo_suma_control_datos_calcular_2()) {
        return 1;
    }

    return 0;
}

s32 comprobar_para_controller_pak(s32 mando) {
    u8 bitpattern_mando;
    SIN_USO s32 phi_v0;

    if ((mando >= MAXCONTROLLERS) || (mando < 0)) {
        return SIN_PAK;
    }

    osPfsIsPlug(&si_evento_msj_cola, &bitpattern_mando);

    if ((bitpattern_mando & (1 << mando)) != 0) {
        return PAK;
    }

    return SIN_PAK;
}

s32 controller_pak_1_situacion(void) {
    if (controller_pak_1_estado) {
        switch (osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego, (u8*) codigo_ext,
                              &controller_pak_nota_1_archivo)) {
            case ERROR_SIN_PFS:
                return ERROR_SIN_PFS;
            case PFS_ERR_INVALID:
                break;
            case PFS_ERR_NEW_PACK:
                controller_pak_1_estado = MALO;
                break;
            default:
                controller_pak_1_estado = MALO;
                break;
        }
    }

    if (!controller_pak_1_estado) {
        s32 codigo_error;
        if (comprobar_para_controller_pak(MANDO_1) == SIN_PAK) {
            return PFS_SIN_PAK_INSERTADO;
        }
        codigo_error = osPfsInit(&si_evento_msj_cola, &controller_pak_manejador_1_archivo, MANDO_1);

        if (codigo_error) {
            switch (codigo_error) {
                case PFS_ERR_NOPACK:
                case PFS_ERR_DEVICE:
                    return PFS_SIN_PAK_INSERTADO;
                case PFS_ERR_ID_FATAL:
                    return PFS_PAK_MALO_LECTURA;
                default:
                case PFS_ERR_CONTRFAIL:
                    return PFS_PAK_MALO_LECTURA;
            }
        }

        controller_pak_1_estado = OK;
        if (osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego, (u8*) codigo_ext,
                          &controller_pak_nota_1_archivo) == ERROR_SIN_PFS) {
            return ERROR_SIN_PFS;
        }
        if (osPfsNumFiles(&controller_pak_manejador_1_archivo, &controller_pak_1_num_archivos_usado,
                          &controller_pak_archivos_escribible_1_max) != ERROR_SIN_PFS) {
            return PFS_PAK_MALO_LECTURA;
        }
        if (osPfsFreeBlocks(&controller_pak_manejador_1_archivo, &controller_pak_libre_paginas_1_num) != ERROR_SIN_PFS) {
            return PFS_PAK_MALO_LECTURA;
        }
        controller_pak_libre_paginas_1_num = controller_pak_libre_paginas_1_num >> 8;
    }

    if (controller_pak_archivos_escribible_1_max >= controller_pak_1_num_archivos_usado) {
        return DESBORDE_ARCHIVO_PFS;
    }
    if (controller_pak_libre_paginas_1_num >= 0x79) {
        return DATOS_INVALIDO_PFS;
    }
    return DESBORDE_ARCHIVO_PFS;
}

s32 controller_pak_2_situacion(void) {
    s32 prestamo_estado = controller_pak_2_estado;

    if (prestamo_estado) {
        switch (osPfsFindFile(&controller_pak_manejador_2_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego, (u8*) codigo_ext,
                              &controller_pak_nota_2_archivo)) {
            case ERROR_SIN_PFS:
                return ERROR_SIN_PFS;
            case PFS_ERR_INVALID:
                return DATOS_INVALIDO_PFS;
            default:
            case PFS_ERR_NEW_PACK:
                controller_pak_2_estado = MALO;
                prestamo_estado = MALO;
        }
    }
    if (!prestamo_estado) {
        s32 codigo_error;
        if (comprobar_para_controller_pak(MANDO_2) == SIN_PAK) {
            return PFS_SIN_PAK_INSERTADO;
        }

        codigo_error = osPfsInit(&si_evento_msj_cola, &controller_pak_manejador_2_archivo, MANDO_2);
        if (codigo_error) {
            switch (codigo_error) {
                case PFS_ERR_NOPACK:
                case PFS_ERR_DEVICE:
                    return PFS_SIN_PAK_INSERTADO;
                case PFS_ERR_ID_FATAL:
                    return PFS_PAK_MALO_LECTURA;
                case PFS_ERR_CONTRFAIL:
                default:
                    return PFS_PAK_MALO_LECTURA;
            }
        }

        controller_pak_2_estado = OK;

        switch (osPfsFindFile(&controller_pak_manejador_2_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego, (u8*) codigo_ext,
                              &controller_pak_nota_2_archivo)) {
            case ERROR_SIN_PFS:
                return ERROR_SIN_PFS;
            case PFS_ERR_INVALID:
                return DATOS_INVALIDO_PFS;
            case PFS_ERR_NEW_PACK:
            default:
                return PFS_PAK_MALO_LECTURA;
        }
    }
}

s32 funcion_800B5F30(void) {
    s32 codigo_error;

    if (controller_pak_1_estado) {
        return PFS_PAK_ESTADO_OK;
    }
    if (comprobar_para_controller_pak(MANDO_1) != SIN_PAK) {
        codigo_error = osPfsInit(&si_evento_msj_cola, &controller_pak_manejador_1_archivo, MANDO_1);
        if (osPfsNumFiles(&controller_pak_manejador_1_archivo, &controller_pak_1_num_archivos_usado,
                          &controller_pak_archivos_escribible_1_max) != ERROR_SIN_PFS) {
            controller_pak_1_estado = MALO;
            return PFS_NUM_ARCHIVOS_ERROR;
        }
        if (osPfsFreeBlocks(&controller_pak_manejador_1_archivo, &controller_pak_libre_paginas_1_num) != ERROR_SIN_PFS) {
            controller_pak_1_estado = MALO;
            return PFS_LIBRE_BLOQUES_ERROR;
        }
        controller_pak_libre_paginas_1_num = controller_pak_libre_paginas_1_num >> 8;
        if (codigo_error == ERROR_SIN_PFS) {
            controller_pak_1_estado = OK;
        }
        return codigo_error;
    }
    return PAK_NO_INSERTADO;
}

s32 funcion_800B6014(void) {
    s32 codigo_error;

    if (controller_pak_2_estado) {
        return PFS_PAK_ESTADO_OK;
    }
    if (comprobar_para_controller_pak(MANDO_2) != SIN_PAK) {
        codigo_error = osPfsInit(&si_evento_msj_cola, &controller_pak_manejador_2_archivo, MANDO_2);
        if (codigo_error == ERROR_SIN_PFS) {
            controller_pak_2_estado = OK;
        }
        return codigo_error;
    }
    return PAK_NO_INSERTADO;
}

s32 funcion_800B6088(s32 parametro0) {
    struct_8018EE10_entrada* temporal_v1;

    temporal_v1 = &dato_8018EE10[parametro0];
    temporal_v1->checksum = funcion_800B6828(parametro0);
    return osPfsReadWriteFile(&controller_pak_manejador_1_archivo, controller_pak_nota_1_archivo, PFS_WRITE,
                              parametro0 * 0x80 , sizeof(struct_8018EE10_entrada),
                              (u8*) temporal_v1);
}

u8 funcion_800B60E8(s32 pagina) {
    s32 i;
    u32 checksum = 0;
    u8* direccion;

    for (i = 0, direccion = (u8*) &((u8*) repeticion_fantasma_comprimido)[pagina * 256]; i < 256; i++) {
        checksum += (*direccion++ * (pagina + 1) + i);
    }
    return checksum;
}

s32 funcion_800B6178(s32 parametro0) {
    s32 variable_v0;
    s32 variable_s0;
    struct_8018EE10_entrada* temporal_s3;

    switch (parametro0) {
        case 0:
        case 1:
            break;
        default:
            return -1;
    }
    if (estado_juego == CARRERA) {
        funcion_800051C4();
    }
    temporal_s3 = &dato_8018EE10[parametro0];
    temporal_s3->fantasma_datos_guardado = 0;
    variable_v0 = funcion_800B6088(parametro0);
    if (variable_v0 != 0) {
        temporal_s3->fantasma_datos_guardado = 0;
        for (variable_s0 = 0; variable_s0 < 0x3C; variable_s0++) {
            temporal_s3->desconocido_07[variable_s0] = variable_s0;
        }
    } else {
        variable_v0 = osPfsReadWriteFile(&controller_pak_manejador_1_archivo, controller_pak_nota_1_archivo, 1U, (parametro0 * 0x3C00) + 0x100,
                                    0x00003C00, (u8*) repeticion_fantasma_comprimido);
        if (variable_v0 == 0) {
            temporal_s3->fantasma_datos_guardado = 1;
            if (estado_juego == CARRERA) {
                temporal_s3->indice_circuito = (seleccion_copa * 4) + indice_circuito_en_copa;
            }
            temporal_s3->desconocido_00 = dato_80162DFC;
            temporal_s3->id_personaje = (u8) dato_80162DE0;
            for (variable_s0 = 0; variable_s0 < 0x3C; variable_s0++) {
                temporal_s3->desconocido_07[variable_s0] = funcion_800B60E8(variable_s0);
            }
            variable_v0 = funcion_800B6088(parametro0);
        }
        if (variable_v0 != 0) {
            temporal_s3->fantasma_datos_guardado = 0;
            for (variable_s0 = 0; variable_s0 < 0x3C; variable_s0++) {
                temporal_s3->desconocido_07[variable_s0] = variable_s0;
            }
        }
    }
    return variable_v0;
}

s32 funcion_800B6348(s32 parametro0) {
    if ((dato_8018EE10[0].fantasma_datos_guardado != 0) && (parametro0 == dato_8018EE10[0].indice_circuito)) {
        return 0;
    }
    if ((dato_8018EE10[1].fantasma_datos_guardado != 0) && (parametro0 == dato_8018EE10[1].indice_circuito)) {
        return 1;
    }
    return 0;
}

s32 funcion_800B639C(s32 parametro0) {
    if ((dato_8018EE10[0].fantasma_datos_guardado != 0) && (parametro0 == dato_8018EE10[0].indice_circuito)) {
        return 0;
    }
    if ((dato_8018EE10[1].fantasma_datos_guardado != 0) && (parametro0 == dato_8018EE10[1].indice_circuito)) {
        return 1;
    }
    return -1;
}

s32 funcion_800B63F0(s32 parametro0) {
    s32 temporal_s0;
    u8* phi_s1;
    s32 phi_s3;

    funcion_800051C4();
    b_circuito_fantasma_desactivado = 1;
    funcion_80005AE8(jugador_tres);

    phi_s3 = 0;
    if (((seleccion_copa * 4) + indice_circuito_en_copa) != dato_8018EE10[parametro0].indice_circuito) {
        phi_s3 = 2;
    } else if (dato_80162DFC != dato_8018EE10[parametro0].desconocido_00) {
        phi_s3 = 3;
    } else {
        if (dato_80162DE0 != (u8) dato_8018EE10[parametro0].id_personaje) {
            phi_s3 = 4;
        } else {
            temporal_s0 = 0;
            phi_s1 = (u8*) &dato_8018EE10[parametro0];

            while (temporal_s0 < 0x3C) {
                if (phi_s1[7] != funcion_800B60E8(temporal_s0)) {
                    phi_s3 = 1;
                    break;
                }

                ++phi_s1;
                ++temporal_s0;
            }
        }
    }

    return phi_s3;
}

s32 funcion_800B64EC(s32 parametro0) {
    s32 temporal_s0;
    s32 temporal_v0;
    u8* phi_s1;

    if ((parametro0 != 0) && (parametro0 != 1)) {
        return -1;
    }

    temporal_v0 = osPfsReadWriteFile(&controller_pak_manejador_1_archivo, controller_pak_nota_1_archivo, PFS_READ, (parametro0 * 0x3C00) + 0x100,
                                 0x3C00, (u8*) repeticion_fantasma_comprimido);
    if (temporal_v0 == 0) {
        phi_s1 = (u8 *) &dato_8018EE10[parametro0]; temporal_s0 = 0; while (1) {

            if (phi_s1[7] != funcion_800B60E8(temporal_s0)) {
                dato_8018EE10[parametro0].fantasma_datos_guardado = 0;
                return -2;
            }

            ++phi_s1;
            if ((++temporal_s0) == 0x3C) {
                funcion_8000522C();
                b_jugador_fantasma_desactivado = 0;
                dato_80162DE0 = (s32) dato_8018EE10[parametro0].id_personaje;
                dato_80162DFC = dato_8018EE10[parametro0].desconocido_00;
                break;
            }
        }
    }

    return temporal_v0;
}

s32 funcion_800B65F4(s32 parametro0, s32 parametro1) {
    SIN_USO s32 margen_pila;
    s32 i;
    s32 escribir_situacion;
    struct_8018EE10_entrada* temporal_s3;
    switch (parametro0) {
        case 0:
        case 1:
            break;
        default:
            return -1;
    }
    escribir_situacion = osPfsReadWriteFile(&controller_pak_manejador_2_archivo, controller_pak_nota_2_archivo, 0U, (parametro0 * 0x3C00) + 0x100,
                                     0x00003C00, (u8*) repeticion_fantasma_comprimido);
    if (escribir_situacion == 0) {
        temporal_s3 = &((struct_8018EE10_entrada*) algun_buffer_dl)[parametro0];
        for (i = 0; i < 0x3C; i++) {
            if (temporal_s3->desconocido_07[i] != funcion_800B60E8(i)) {
                temporal_s3->fantasma_datos_guardado = 0;
                return -2;
            }
        }
        dato_80162DE0 = temporal_s3->id_personaje;
        dato_80162DFC = temporal_s3->desconocido_00;
        dato_8018EE10[parametro1].indice_circuito = temporal_s3->indice_circuito;
    }
    return escribir_situacion;
}

void funcion_800B6708(void) {
    s32 temporal_s0;

    osPfsReadWriteFile(&controller_pak_manejador_1_archivo, controller_pak_nota_1_archivo, PFS_READ, 0,
                       0x100 , (u8*) &dato_8018EE10);

    for (temporal_s0 = 0; temporal_s0 < 2; ++temporal_s0) {
        if (dato_8018EE10[temporal_s0].checksum != funcion_800B6828(temporal_s0)) {
            dato_8018EE10[temporal_s0].fantasma_datos_guardado = 0;
        }
    }
}

void funcion_800B6798(void) {
    s32 temporal_s0;
    u8* tmp;

    tmp = (u8*) algun_buffer_dl;

    osPfsReadWriteFile(&controller_pak_manejador_2_archivo, controller_pak_nota_2_archivo, PFS_READ, 0,
                       0x100 , tmp);

    for (temporal_s0 = 0; temporal_s0 < 2; ++temporal_s0) {
        if (((struct_8018EE10_entrada*) (tmp + (temporal_s0 << 7)))->checksum != funcion_800B68F4(temporal_s0)) {
            ((struct_8018EE10_entrada*) (tmp + (temporal_s0 << 7)))->fantasma_datos_guardado = 0;
        }
    }
}

u8 funcion_800B6828(s32 parametro0) {
    u32 checksum = 0;
    u8* direccion = (u8*) &dato_8018EE10[parametro0];
    s32 i;
    for (i = 0; i < 0x43; i++) {
        checksum += ((direccion[i] * (parametro0 + 1)) + i);
    }
    return checksum;
}

u8 funcion_800B68F4(s32 parametro0) {
    struct_8018EE10_entrada* variable_v0 = algun_buffer_dl;
    u8 *direccion = (u8*)(variable_v0 + parametro0);
    s32 i = 0;
    u32 checksum = 0;

    for (i = 0; i < (s32)offsetof(struct_8018EE10_entrada, relleno_43); i++) {
        checksum += (direccion[i] * (parametro0 + 1)) + i;
    }

    return checksum;
}

s32 funcion_800B69BC(s32 parametro0) {
    u32 i;
    struct_8018EE10_entrada* plz = &dato_8018EE10[parametro0];

    plz->fantasma_datos_guardado = false;
    plz->indice_circuito = 0;
    plz->id_personaje = 0;
    for (i = 0; i < sizeof(plz->desconocido_07); i++) {
        plz->desconocido_07[i] = i;
    }
    plz->checksum = funcion_800B6828(parametro0);

    return osPfsReadWriteFile(&controller_pak_manejador_1_archivo, controller_pak_nota_1_archivo, PFS_WRITE,
                              (s32) sizeof(struct_8018EE10_entrada) * parametro0, sizeof(struct_8018EE10_entrada), (u8*) plz);
}

s32 funcion_800B6A68(void) {
    SIN_USO s32 relleno;
    s32 devuelto;
    s32 i;

    devuelto = osPfsAllocateFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) &nombre_juego, (u8*) &codigo_ext,
                            0x7900, &controller_pak_nota_1_archivo);
    if (devuelto == 0) {
        for (i = 0; i < 2; i++) {
            funcion_800B69BC(i);
        }
    }

    return devuelto;
}

void func_8800B6AF8(void) {
    if (comprobar_para_controller_pak(MANDO_1) && osPfsInit(&si_evento_msj_cola, &controller_pak_manejador_1_archivo, 0) == 0 &&
        osPfsFindFile(&controller_pak_manejador_1_archivo, codigo_empresa, codigo_juego, (u8*) nombre_juego, (u8*) codigo_ext,
                      &controller_pak_nota_1_archivo) &&
        osPfsNumFiles(&controller_pak_manejador_1_archivo, &controller_pak_1_num_archivos_usado, &controller_pak_archivos_escribible_1_max) ==
            0 &&
        controller_pak_archivos_escribible_1_max < controller_pak_1_num_archivos_usado &&
        osPfsFreeBlocks(&controller_pak_manejador_1_archivo, &controller_pak_libre_paginas_1_num) == 0) {
        controller_pak_libre_paginas_1_num >>= 8;
        if (controller_pak_libre_paginas_1_num >= 0x79) {
            funcion_800B6A68();
        }
    }
}
