#ifndef SISTEMA_OPCIONES_PORT_H
#define SISTEMA_OPCIONES_PORT_H

#include <PR/ultratypes.h>

#include "sistema/crc32.h"

// Ajustes de imagen y trucos del port, guardados en SMK64CFG.DAT aparte de la
// partida. Flujo: el menú CONFIGURACIÓN Y TRUCOS escribe opciones_port y llama a
// opciones_cambiadas() en cada cambio, y al salir a pedir_guardado_opciones();
// el GS relee opciones_port en el retrazo cuando cambia version_opciones_port;
// los trucos leen opciones_port directamente.

enum FormatoPantalla {
    FORMATO_NORMAL = 0,     // 4:3 a pantalla completa
    FORMATO_CON_BANDAS = 1, // 4:3 con bandas negras en una tele 16:9
    FORMATO_PANORAMICO = 2  // imagen estirada a 16:9
};

typedef struct OpcionesPort {
    u8 antiparpadeo;
    s8 desplaz_x;     // en unidades de ajuste; el GS las pasa a píxeles
    s8 desplaz_y;
    u8 formato;       // enum FormatoPantalla
    u8 truco_desbloquear;
    u8 truco_objeto;  // 0 = ruleta normal; si no, el valor de enum ITEMS
    u8 truco_200cc;
    u8 truco_rivales;
} OpcionesPort;

#define DESPLAZ_X_MAX 32
#define DESPLAZ_Y_MAX 16
#define TRUCO_OBJETO_MAX 15 // ITEM_SUPER_HONGO
// HONGO_DOBLE_ITEM: solo existe como lo que queda tras usar un triple, la
// ruleta nunca lo da
#define TRUCO_OBJETO_PROHIBIDO 13

#define TAM_OPCIONES_PORT 32
#define VERSION_OPCIONES_PORT 1

// Estado global; lo define el código de Memory Card. Solo se usa en la PS2:
// la prueba del PC no lo toca y el inline sin usar no deja referencias.
extern OpcionesPort opciones_port;
extern volatile u32 version_opciones_port;
extern int pantalla_osd_169; // la BIOS tiene la tele configurada en 16:9
void pedir_guardado_opciones(void); // encola la escritura en el hilo de guardado

static inline void opciones_cambiadas(void)
{
    // Los campos tienen que estar escritos antes de que el retrazo vea la versión nueva
    __asm__ volatile("" ::: "memory");
    version_opciones_port++;
}

// Antiparpadeo apagado: suaviza el texto pero emborrona la imagen
static inline void opciones_por_defecto(OpcionesPort *o, int osd_169)
{
    o->antiparpadeo = 0;
    o->desplaz_x = 0;
    o->desplaz_y = 0;
    o->formato = osd_169 ? FORMATO_CON_BANDAS : FORMATO_NORMAL;
    o->truco_desbloquear = 0;
    o->truco_objeto = 0;
    o->truco_200cc = 0;
    o->truco_rivales = 0;
}

static inline s8 opciones_recortar(s8 v, s8 max)
{
    if (v < -max) {
        return -max;
    }
    if (v > max) {
        return max;
    }
    return v;
}

// Deja cada campo dentro de su rango: los interruptores en 0/1, la posición
// recortada, y el formato o el objeto no válidos en su valor por defecto
static inline void opciones_sanear(OpcionesPort *o)
{
    o->antiparpadeo = o->antiparpadeo != 0;
    o->desplaz_x = opciones_recortar(o->desplaz_x, DESPLAZ_X_MAX);
    o->desplaz_y = opciones_recortar(o->desplaz_y, DESPLAZ_Y_MAX);
    if (o->formato > FORMATO_PANORAMICO) {
        o->formato = FORMATO_NORMAL;
    }
    o->truco_desbloquear = o->truco_desbloquear != 0;
    if (o->truco_objeto > TRUCO_OBJETO_MAX || o->truco_objeto == TRUCO_OBJETO_PROHIBIDO) {
        o->truco_objeto = 0;
    }
    o->truco_200cc = o->truco_200cc != 0;
    o->truco_rivales = o->truco_rivales != 0;
}

// Formato del archivo, little endian: «MKCF», versión u16, tamaño u16, los 8
// campos en el orden del struct, 12 bytes reservados a 0 y el CRC32 de los
// bytes 0 a 27 en los 28 a 31
static inline void opciones_serializar(const OpcionesPort *o, unsigned char buf[TAM_OPCIONES_PORT])
{
    u32 crc;
    int i;

    buf[0] = 'M';
    buf[1] = 'K';
    buf[2] = 'C';
    buf[3] = 'F';
    buf[4] = VERSION_OPCIONES_PORT & 0xFF;
    buf[5] = VERSION_OPCIONES_PORT >> 8;
    buf[6] = TAM_OPCIONES_PORT & 0xFF;
    buf[7] = TAM_OPCIONES_PORT >> 8;
    buf[8] = o->antiparpadeo;
    buf[9] = (unsigned char) o->desplaz_x;
    buf[10] = (unsigned char) o->desplaz_y;
    buf[11] = o->formato;
    buf[12] = o->truco_desbloquear;
    buf[13] = o->truco_objeto;
    buf[14] = o->truco_200cc;
    buf[15] = o->truco_rivales;
    for (i = 16; i < TAM_OPCIONES_PORT - 4; i++) {
        buf[i] = 0;
    }
    crc = crc32(buf, TAM_OPCIONES_PORT - 4);
    buf[28] = crc & 0xFF;
    buf[29] = (crc >> 8) & 0xFF;
    buf[30] = (crc >> 16) & 0xFF;
    buf[31] = crc >> 24;
}

// 1 si el archivo es íntegro y de esta versión; los valores leídos se sanean.
// Si no, deja los valores por defecto y devuelve 0. Una versión mayor también
// se rechaza: no se sabe qué significan sus campos.
static inline int opciones_deserializar(const unsigned char buf[TAM_OPCIONES_PORT], OpcionesPort *o, int osd_169)
{
    u32 crc = buf[28] | ((u32) buf[29] << 8) | ((u32) buf[30] << 16) | ((u32) buf[31] << 24);

    opciones_por_defecto(o, osd_169);
    if (buf[0] != 'M' || buf[1] != 'K' || buf[2] != 'C' || buf[3] != 'F' ||
        (buf[4] | (buf[5] << 8)) != VERSION_OPCIONES_PORT || (buf[6] | (buf[7] << 8)) != TAM_OPCIONES_PORT ||
        crc != crc32(buf, TAM_OPCIONES_PORT - 4)) {
        return 0;
    }
    o->antiparpadeo = buf[8];
    o->desplaz_x = (s8) buf[9];
    o->desplaz_y = (s8) buf[10];
    o->formato = buf[11];
    o->truco_desbloquear = buf[12];
    o->truco_objeto = buf[13];
    o->truco_200cc = buf[14];
    o->truco_rivales = buf[15];
    opciones_sanear(o);
    return 1;
}

#endif
