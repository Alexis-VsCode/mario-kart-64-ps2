// Región de la consola leída de rom0:ROMVER (region_ps2.h)
#include <stdio.h>
#include <string.h>

#include "sistema/region_ps2.h"

static int s_fallos, s_comprobaciones;

static const char *nombre_region(RegionPs2 region) {
    switch (region) {
        case REGION_NTSC:
            return "NTSC";
        case REGION_PAL:
            return "PAL";
        default:
            return "desconocida";
    }
}

// texto se pasa sin el 0 final, como sale de fread()
static void comprobar(const char *texto, RegionPs2 esperada) {
    RegionPs2 obtenida = region_de_romver(texto, (int) strlen(texto));

    s_comprobaciones++;
    if (obtenida != esperada) {
        s_fallos++;
        printf("FALLO «%s»: región %s, se esperaba %s\n", texto, nombre_region(obtenida), nombre_region(esperada));
    }
}

int main(void) {
    // ROMVER reales: europea, americana y japonesa
    comprobar("0160EC20010704", REGION_PAL);
    comprobar("0220AC20060905", REGION_NTSC);
    comprobar("0100JC20000117", REGION_NTSC);
    // Asia y China también son NTSC; el tipo D (máquina de desarrollo) vale igual que C
    comprobar("0190HC20020207", REGION_NTSC);
    comprobar("0220CC20060905", REGION_NTSC);
    comprobar("0230ED20080220", REGION_PAL);
    // El archivo acaba en salto de línea: lo que sigue a los 14 caracteres no cuenta
    comprobar("0160EC20010704\n", REGION_PAL);

    // Inválidos: vacío, corto, región o tipo que no existen, cifras que faltan
    comprobar("", REGION_DESCONOCIDA);
    comprobar("0160EC2001070", REGION_DESCONOCIDA);
    comprobar("0160E", REGION_DESCONOCIDA);
    comprobar("0160XC20010704", REGION_DESCONOCIDA);
    comprobar("0160EX20010704", REGION_DESCONOCIDA);
    comprobar("01A0EC20010704", REGION_DESCONOCIDA);
    comprobar("0160EC2001070A", REGION_DESCONOCIDA);
    comprobar("0160ec20010704", REGION_DESCONOCIDA);
    s_comprobaciones++;
    if (region_de_romver(NULL, 14) != REGION_DESCONOCIDA) {
        s_fallos++;
        printf("FALLO texto NULL: se esperaba región desconocida\n");
    }
    // Un ROMVER válido del que solo se leyeron 13 bytes: la guarda de largo
    // tiene que bastar sola, aunque el byte 14 del búfer sea una cifra
    s_comprobaciones++;
    if (region_de_romver("0160EC20010704", 13) != REGION_DESCONOCIDA) {
        s_fallos++;
        printf("FALLO largo 13: se esperaba región desconocida\n");
    }

    printf("%d comprobaciones, %d %s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "fallo" : "fallos");
    return s_fallos != 0;
}
