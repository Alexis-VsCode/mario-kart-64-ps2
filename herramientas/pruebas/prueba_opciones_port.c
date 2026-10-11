// Archivo de opciones del port SMK64CFG.DAT (opciones_port.h)
#include <stdio.h>
#include <string.h>

#include "sistema/crc32.h"
#include "sistema/opciones_port.h"

static int s_fallos, s_comprobaciones;

static void comprobar(int correcto, const char *que) {
    s_comprobaciones++;
    if (!correcto) {
        s_fallos++;
        printf("FALLO %s\n", que);
    }
}

static int iguales(const OpcionesPort *a, const OpcionesPort *b) {
    return a->antiparpadeo == b->antiparpadeo && a->desplaz_x == b->desplaz_x && a->desplaz_y == b->desplaz_y &&
           a->formato == b->formato && a->truco_desbloquear == b->truco_desbloquear &&
           a->truco_objeto == b->truco_objeto && a->truco_200cc == b->truco_200cc &&
           a->truco_rivales == b->truco_rivales;
}

// Todos los campos distintos del defecto y en los extremos de su rango
static OpcionesPort ejemplo(void) {
    OpcionesPort o;

    o.antiparpadeo = 1;
    o.desplaz_x = -32;
    o.desplaz_y = 16;
    o.formato = FORMATO_PANORAMICO;
    o.truco_desbloquear = 1;
    o.truco_objeto = 15;
    o.truco_200cc = 1;
    o.truco_rivales = 1;
    return o;
}

// Vuelve a calcular el CRC tras tocar el archivo, para que solo falle lo que se prueba
static void rehacer_crc(unsigned char *buf) {
    u32 crc = crc32(buf, TAM_OPCIONES_PORT - 4);

    buf[28] = (unsigned char) crc;
    buf[29] = (unsigned char) (crc >> 8);
    buf[30] = (unsigned char) (crc >> 16);
    buf[31] = (unsigned char) (crc >> 24);
}

// Un archivo rechazado da 0 y deja los valores por defecto de OSD 16:9
static void comprobar_rechazo(const unsigned char *buf, const char *que) {
    OpcionesPort leidas = ejemplo(), defecto;

    opciones_por_defecto(&defecto, 1);
    comprobar(opciones_deserializar(buf, &leidas, 1) == 0, que);
    comprobar(iguales(&leidas, &defecto), que);
}

static void comprobar_saneado(OpcionesPort o, const OpcionesPort *esperado, const char *que) {
    opciones_sanear(&o);
    comprobar(iguales(&o, esperado), que);
}

int main(void) {
    OpcionesPort o, leidas, esperado;
    unsigned char buf[TAM_OPCIONES_PORT], malo[TAM_OPCIONES_PORT];
    u32 crc;
    int i, ceros;

    comprobar(crc32((const u8 *) "123456789", 9) == 0xCBF43926u, "CRC32 de «123456789»");

    opciones_por_defecto(&o, 0);
    comprobar(o.antiparpadeo == 0 && o.desplaz_x == 0 && o.desplaz_y == 0 && o.formato == FORMATO_NORMAL &&
                  o.truco_desbloquear == 0 && o.truco_objeto == 0 && o.truco_200cc == 0 && o.truco_rivales == 0,
              "defectos con OSD 4:3");
    opciones_por_defecto(&o, 1);
    comprobar(o.antiparpadeo == 0 && o.desplaz_x == 0 && o.desplaz_y == 0 && o.formato == FORMATO_CON_BANDAS &&
                  o.truco_desbloquear == 0 && o.truco_objeto == 0 && o.truco_200cc == 0 && o.truco_rivales == 0,
              "defectos con OSD 16:9");

    // Ida y vuelta y forma del archivo
    o = ejemplo();
    memset(buf, 0xAA, sizeof(buf));
    opciones_serializar(&o, buf);
    comprobar(memcmp(buf, "MKCF", 4) == 0, "magia");
    comprobar(buf[4] == 1 && buf[5] == 0, "versión 1 en little endian");
    comprobar(buf[6] == TAM_OPCIONES_PORT && buf[7] == 0, "tamaño 32 en little endian");
    comprobar(buf[8] == 1 && buf[9] == 0xE0 && buf[10] == 16 && buf[11] == 2 && buf[12] == 1 && buf[13] == 15 &&
                  buf[14] == 1 && buf[15] == 1,
              "campos en los bytes 8 a 15");
    for (i = 16, ceros = 1; i < 28; i++) {
        ceros &= buf[i] == 0;
    }
    comprobar(ceros, "reservados a 0");
    crc = crc32(buf, 28);
    comprobar(buf[28] == (crc & 0xFF) && buf[29] == ((crc >> 8) & 0xFF) && buf[30] == ((crc >> 16) & 0xFF) &&
                  buf[31] == (crc >> 24),
              "CRC de los bytes 0 a 27 en little endian");
    memset(&leidas, 0, sizeof(leidas));
    comprobar(opciones_deserializar(buf, &leidas, 0) == 1, "ida y vuelta válida");
    comprobar(iguales(&o, &leidas), "ida y vuelta da lo mismo");

    // Archivos rechazados
    memcpy(malo, buf, sizeof(buf));
    malo[0] = 'X';
    rehacer_crc(malo);
    comprobar_rechazo(malo, "magia errónea");
    memcpy(malo, buf, sizeof(buf));
    malo[4] = 0;
    rehacer_crc(malo);
    comprobar_rechazo(malo, "versión 0");
    memcpy(malo, buf, sizeof(buf));
    malo[4] = 2;
    rehacer_crc(malo);
    comprobar_rechazo(malo, "versión mayor");
    memcpy(malo, buf, sizeof(buf));
    malo[6] = 16;
    rehacer_crc(malo);
    comprobar_rechazo(malo, "tamaño erróneo");
    memcpy(malo, buf, sizeof(buf));
    malo[28] ^= 1;
    comprobar_rechazo(malo, "CRC erróneo");
    memcpy(malo, buf, sizeof(buf));
    malo[12] = 0;
    comprobar_rechazo(malo, "campo cambiado sin rehacer el CRC");

    // Saneado directo
    opciones_por_defecto(&esperado, 0);
    o = esperado;
    o.desplaz_x = 100;
    esperado.desplaz_x = 32;
    comprobar_saneado(o, &esperado, "desplaz_x 100 pasa a 32");
    o.desplaz_x = 33;
    comprobar_saneado(o, &esperado, "desplaz_x 33 pasa a 32");
    o.desplaz_x = -100;
    esperado.desplaz_x = -32;
    comprobar_saneado(o, &esperado, "desplaz_x -100 pasa a -32");
    opciones_por_defecto(&esperado, 0);
    o = esperado;
    o.desplaz_y = 17;
    esperado.desplaz_y = 16;
    comprobar_saneado(o, &esperado, "desplaz_y 17 pasa a 16");
    o.desplaz_y = -17;
    esperado.desplaz_y = -16;
    comprobar_saneado(o, &esperado, "desplaz_y -17 pasa a -16");
    o = ejemplo();
    comprobar_saneado(o, &o, "los extremos válidos no cambian");
    o.desplaz_x = 32;
    o.desplaz_y = -16;
    comprobar_saneado(o, &o, "los otros extremos válidos no cambian");
    opciones_por_defecto(&esperado, 0);
    o = esperado;
    o.truco_objeto = 13;
    comprobar_saneado(o, &esperado, "objeto 13 pasa a 0");
    o.truco_objeto = 16;
    comprobar_saneado(o, &esperado, "objeto 16 pasa a 0");
    o.truco_objeto = 12;
    esperado.truco_objeto = 12;
    comprobar_saneado(o, &esperado, "objeto 12 se queda");
    o.truco_objeto = 14;
    esperado.truco_objeto = 14;
    comprobar_saneado(o, &esperado, "objeto 14 se queda");
    opciones_por_defecto(&esperado, 0);
    o = esperado;
    o.formato = 3;
    comprobar_saneado(o, &esperado, "formato 3 pasa a NORMAL");
    o.antiparpadeo = 2;
    o.truco_desbloquear = 7;
    o.truco_200cc = 9;
    o.truco_rivales = 255;
    esperado.antiparpadeo = 1;
    esperado.truco_desbloquear = 1;
    esperado.truco_200cc = 1;
    esperado.truco_rivales = 1;
    comprobar_saneado(o, &esperado, "interruptores distintos de 0 pasan a 1");

    // Archivo íntegro con valores fuera de rango: se acepta y se sanea
    opciones_por_defecto(&o, 0);
    opciones_serializar(&o, buf);
    buf[9] = 100;
    buf[11] = 3;
    buf[13] = 13;
    rehacer_crc(buf);
    comprobar(opciones_deserializar(buf, &leidas, 1) == 1, "archivo íntegro con valores fuera de rango");
    comprobar(leidas.desplaz_x == 32 && leidas.formato == FORMATO_NORMAL && leidas.truco_objeto == 0,
              "se sanea tras leer");

    printf("%d comprobaciones, %d %s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "fallo" : "fallos");
    return s_fallos != 0;
}
