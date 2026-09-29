// Glifos de la fuente del menu: de caracter a indice de glifo y ancho de una cadena

#include "sistema/caracteres_es.h"

s32 car_a_indice_glifo(char* character) {
    s32 index;
    s8 temporal_v0;

    temporal_v0 = *character;
    index = 1;
    if ((temporal_v0 >= 'a') && (temporal_v0 <= 'z')) {
        index = temporal_v0 - 0x61;
    } else if ((temporal_v0 >= 'A') && (temporal_v0 <= 'Z')) {
        index = temporal_v0 - 0x41;
    } else if ((temporal_v0 >= '0') && (temporal_v0 <= '9')) {
        index = temporal_v0 - 0x10;
    } else if (temporal_v0 == ' ') {
        index = -1;
    } else if (temporal_v0 < 0) {
        switch (temporal_v0) { /* irregular */
            case -92:
                index = funcion_80092E1C(character + 1);
                break;
            case -91:
                index = funcion_80092DF8(character + 1);
                break;
            case -95:
            case -93:
            case -85:
                index = funcion_80092EE4(character);
                break;
        }
    } else {
        switch (temporal_v0) {
            case '!':
                index = 0x0000001A;
                break;
            case '-':
                index = 0x0000001B;
                break;
            case '?':
                index = 0x0000001C;
                break;
            case '\'':
                index = 0x0000001D;
                break;
            case '$':
                index = 0x0000001E;
                break;
            case '.':
                index = 0x0000001F;
                break;
            case '\"':
                index = 0x0000002A;
                break;
            case '*':
                index = 0x0000002B;
                break;
            case '+':
                index = 0x0000002C;
                break;
            // Displayed as "cc"
            case '(':
                index = 0x0000002D;
                break;
            case ',':
                index = 0x0000002E;
                break;
            default:
                index = -2;
                break;
        }
    }
    return index;
}

s32 funcion_80092DF8(char* parametro) {
    return funcion_80092E1C(parametro) + 0x50;
}

s32 funcion_80092E1C(char* character) {
    s32 devuelto;
    SIN_USO s32 probar;
    u8 temporal_t6;
    u8 temporal_;

    temporal_t6 = (*character + 0x80);
    temporal_ = temporal_t6;
    if (temporal_) {}
    if ((temporal_ > 0x20) && (temporal_ < 0x2B)) {
        if (temporal_ % 2) {
            devuelto = ((temporal_ - 0x21) / 2) + 0x7B;
        } else {
            devuelto = ((temporal_ - 0x21) / 2) + 0x30;
        }
    } else if ((temporal_ > 0x2A) && (temporal_ < 0x6E)) {
        devuelto = temporal_ + 0xA;
    } else {
        switch (temporal_) { /* irregular */
            case 0x6F:
                devuelto = 0x00000078;
                break;
            case 0x72:
            case 0x73:
                devuelto = temporal_ + 7;
                break;
            default:
                devuelto = -2;
                break;
        }
    }
    return devuelto;
}

s32 funcion_80092EE4(char* character) {
    u8 temporal_t6;
    s32 variable_v1;

    temporal_t6 = (character[1] + 0x80);
    variable_v1 = 2;
    switch (character[0]) {
        case -95:
            switch (temporal_t6) {
                case 0x22:
                case 0x24:
                    variable_v1 = 0x000000EA;
                    break;
                case 0x23:
                    variable_v1 = 0x000000E9;
                    break;
                case 0x25:
                    variable_v1 = 0x000000D0;
                    break;
                case 0x2A:
                    variable_v1 = 0x000000E8;
                    break;
                case 0x30:
                    variable_v1 = 0x000000EB;
                    break;
                case 0x47:
                    variable_v1 = 0x000000D1;
                    break;
                case 0x49:
                    variable_v1 = 0x000000D2;
                    break;
                case 0x5C:
                    variable_v1 = 0x000000D3;
                    break;
                case 0x3C:
                case 0x3D:
                case 0x5D:
                    variable_v1 = 0x000000D4;
                    break;
                default:
                    break;
            }
            break;
        case -93:
            if ((temporal_t6 >= 0x30) && (temporal_t6 < 0x3A)) {
                variable_v1 = temporal_t6 + 0xA5;
            } else {
                switch (temporal_t6) {
                    case 0x44:
                        variable_v1 = 0x000000DF;
                        break;
                    case 0x43:
                    case 0x63:
                        variable_v1 = 0x000000E0;
                        break;
                    case 0x4E:
                    case 0x6E:
                        variable_v1 = 0x000000E1;
                        break;
                    case 0x50:
                    case 0x70:
                        variable_v1 = 0x000000E2;
                        break;
                    case 0x52:
                    case 0x72:
                        variable_v1 = 0x000000E3;
                        break;
                    case 0x73:
                        variable_v1 = 0x000000E4;
                        break;
                    case 0x54:
                    case 0x74:
                        variable_v1 = 0x000000E5;
                        break;
                    case 0x53:
                        variable_v1 = 0x000000E6;
                        break;
                    case 0x56:
                    case 0x76:
                        variable_v1 = 0x000000E7;
                        break;
                    default:
                        break;
                }
            }
            break;
        case -85:
            if (temporal_t6 == 0x2E) {
                variable_v1 = 0x000000E0;
            }
            break;
        default:
            variable_v1 = 2;
    }
    return variable_v1;
}

// Primer glifo del espanol en la lista; siguen en el orden de CaracterEs
#define GLIFO_ES_PRIMERO 0xEC
#define EUC_SS3 0x8F

// Indice del glifo que empieza en car y, en *bytes, cuanto ocupa en la
// cadena. Es la unica regla de avance: todas las impresoras la usan.
s32 leer_glifo(char* car, s32* bytes) {
    s32 indice;
    int caracter;
    int ocupa;

    // Paso 1: letras y signos del espanol (EUC-JP de 3 bytes, 8F xx xx)
    if ((u8) car[0] == EUC_SS3) {
        caracter = leer_caracter_es(car, &ocupa, NULL);
        *bytes = ocupa;
        return (caracter != CAR_ES_NINGUNO) ? GLIFO_ES_PRIMERO + caracter - 1 : -2;
    }
    // Paso 2: ASCII, kana y signos japoneses, como en la N64
    indice = car_a_indice_glifo(car);
    *bytes = (indice >= 0x30) ? 2 : 1;
    return indice;
}

s32 obtener_ancho_cadena(char* buffer) {
    s32 indice_glifo;
    s32 bytes;
    s32 ancho_cadena = 0;

    if (*buffer != 0) {
        do {
            indice_glifo = leer_glifo(buffer, &bytes);
            if (indice_glifo >= 0) {
                ancho_cadena += ancho_pantalla_glifo[indice_glifo];
            } else if (indice_glifo == -1) {
                ancho_cadena += 7;
            }
            buffer += bytes;
        } while (*buffer != 0);
    }
    return ancho_cadena;
}
