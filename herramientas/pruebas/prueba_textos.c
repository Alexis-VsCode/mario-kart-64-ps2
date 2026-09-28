// Textos que se dibujan con la fuente del menu y con la de depuracion: se
// revisan las tablas reales, en la copia EUC-JP que compila el build, con el
// decodificador del juego (glifos.inc.c). Las tablas de datos de la prueba:
//   prueba_textos_tablas.inc.c      tablas, entradas originales y estado
//   prueba_textos_lugares.inc.c     donde se dibuja cada tabla y sus limites
//   prueba_textos_lista_negra.inc.c palabras en ingles y sin tilde
//   prueba_textos_esperados.inc.c   texto esperado de cada entrada traducida
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <PR/ultratypes.h>
#include "juego/macros.h"
#include "juego/definiciones.h"
#include "sistema/caracteres_es.h"

s32 funcion_80092DF8(char*);
s32 funcion_80092E1C(char*);
s32 funcion_80092EE4(char*);
s32 car_a_indice_glifo(char*);
s32 obtener_ancho_cadena(char*);
s32 leer_glifo(char*, s32*);

const s16 ancho_pantalla_glifo[] = {
#define GLIFO(textura, ancho) ancho,
#include "menus/elementos_menu/lista_glifos.inc.c"
#undef GLIFO
};

#include "menus/elementos_menu/glifos.inc.c"
#include "prueba_textos_tinta.h"

// Las tablas del juego ya convertidas (-iquote build/ps2/jp)
#include "codigo/menus/elementos_menu/textos_menu.inc.c"
#include "codigo/ceremonia/creditos.c"

static int s_fallos, s_comprobaciones, s_detalle;

#define COMPROBACION(cond, ...)                                                                                        \
    do {                                                                                                               \
        s_comprobaciones++;                                                                                            \
        if (!(cond)) {                                                                                                 \
            s_fallos++;                                                                                                \
            printf("FALLO %s:%d: ", __FILE__, __LINE__);                                                               \
            printf(__VA_ARGS__);                                                                                       \
            printf("\n");                                                                                              \
        }                                                                                                              \
    } while (0)

#define GLIFOS_EN_LISTA ((s32) CANTIDAD_ARREGLO(ancho_pantalla_glifo))
#define GLIFO_B 0x01
#define GLIFO_C 0x02
#define GLIFO_DOLAR 0x1E
#define GLIFO_ASTERISCO 0x2B
#define GLIFO_CC 0x2D
#define GLIFO_JAPONES_PRIMERO 0x30
#define GLIFO_RAYA 0xD4
#define GLIFO_SUFIJO_PRIMERO 0xE1
#define GLIFO_SUFIJO_ULTIMO 0xE5
#define GLIFO_ES_PRIMERO 0xEC
#define GLIFO_ES_ULTIMA_LETRA 0xF2 // de 0xEC a 0xF2 llevan signo encima

// Zona segura: el borde de la imagen se pierde en muchos televisores
#define ZONA_SEGURA_IZQ 16
#define ZONA_SEGURA_DER 296
#define ANCHO_ESPACIO 7
// El signo de una letra del espanol llega a 20.6 px sobre la linea base a escala 1
#define ALTO_SIGNO 20.6f
// Fuente de depuracion: celdas de 8 px desde x + 20; salta de linea en x >= 296
#define DEPURACION_MARGEN 20
#define DEPURACION_CELDA 8
#define DEPURACION_SALTO 296

enum { PENDIENTE, ES };
enum { FUENTE_MENU, FUENTE_DEPURACION };
enum { IZQ, DER, CENTRO, MONO, DEPURACION };

#define PERMITE_CC 1        // '(' se dibuja "cc"
#define PERMITE_ASTERISCO 2 // separador de 28 px
#define PERMITE_RAYA 4      // la raya larga japonesa
#define PERMITE_SUFIJO 8    // sufijos de ordinal en ingles de la N64

typedef struct {
    const char* nombre;
    char** cadenas;
    s32 cantidad;
    s32 original;
    s32 desde, hasta; // entradas con texto de la fuente; el resto no se revisa
    s32 fuente;
    s32 permisos;
    s32 estado;
} TablaTexto;

#define TABLA(t, n, d, h, ...) { #t, t, CANTIDAD_ARREGLO(t), n, d, h, __VA_ARGS__ },
#define PUNTERO(t, ...) { #t, &t, 1, 1, 0, 0, __VA_ARGS__ },
#define ARREGLO(t, ...) { #t, (char*[]) { t }, 1, 1, 0, 0, __VA_ARGS__ },
static const TablaTexto tablas[] = {
#include "prueba_textos_tablas.inc.c"
};
#undef TABLA
#undef PUNTERO
#undef ARREGLO

typedef struct {
    const char* nombre;
    const char* tabla;
    s32 desde, hasta, lineas;
    s32 impresora;
    f32 x, escala_x, escala_y;
    s32 tracking, paso;
    f32 x_min, x_max;
    const char* origen;
} Lugar;

typedef struct {
    const char* tabla_a;
    s32 desde_a, hasta_a;
    const char* tabla_b;
    s32 desde_b, hasta_b;
    f32 x, escala;
    s32 hueco;
    f32 x_min, x_max;
    const char* origen;
} Pareja;

typedef struct {
    s32 izquierdo, derecho, margen;
    const char* origen;
} SinSolape;

enum {
#define LUGAR(id, ...) id,
#define PAREJA(...)
#define SIN_SOLAPE(...)
#include "prueba_textos_lugares.inc.c"
#undef LUGAR
#undef PAREJA
#undef SIN_SOLAPE
    LUGARES_TOTAL
};

static const Lugar lugares[] = {
#define LUGAR(id, t, ...) { #id, #t, __VA_ARGS__ },
#define PAREJA(...)
#define SIN_SOLAPE(...)
#include "prueba_textos_lugares.inc.c"
#undef LUGAR
#undef PAREJA
#undef SIN_SOLAPE
};

static const Pareja parejas[] = {
#define LUGAR(...)
#define PAREJA(ta, da, ha, tb, ...) { #ta, da, ha, #tb, __VA_ARGS__ },
#define SIN_SOLAPE(...)
#include "prueba_textos_lugares.inc.c"
#undef LUGAR
#undef PAREJA
#undef SIN_SOLAPE
    { NULL },
};

static const SinSolape sin_solapes[] = {
#define LUGAR(...)
#define PAREJA(...)
#define SIN_SOLAPE(a, b, m, o) { a, b, m, o },
#include "prueba_textos_lugares.inc.c"
#undef LUGAR
#undef PAREJA
#undef SIN_SOLAPE
    { -1 },
};

typedef struct {
    const char* palabra;
    const char* motivo;
} Prohibida;

static const Prohibida prohibidas[] = {
#define INGLES(p) { p, "en ingles" },
#define SIN_TILDE(p) { p, "sin tilde" },
#include "prueba_textos_lista_negra.inc.c"
#undef INGLES
#undef SIN_TILDE
};

typedef struct {
    const char* tabla;
    s32 indice;
    const char* texto;
} Esperado;

// Copia en EUC-JP de prueba_textos_esperados.inc.c (la convierte el Makefile)
static const Esperado esperados[] = {
#define ESPERADO(t, i, s) { #t, i, s },
#include "prueba_textos_esperados.eucjp.inc.c"
#undef ESPERADO
    { NULL },
};

static const TablaTexto* buscar_tabla(const char* nombre) {
    u32 i;
    for (i = 0; i < CANTIDAD_ARREGLO(tablas); i++) {
        if (strcmp(tablas[i].nombre, nombre) == 0) {
            return &tablas[i];
        }
    }
    return NULL;
}

// Glifos con tinta de una cadena dibujada (pluma e indice) y bordes de la tinta
#define GLIFOS_MAX 128
typedef struct {
    s32 n;
    f32 pluma[GLIFOS_MAX];
    s32 indice[GLIFOS_MAX];
    f32 izq, der;
} Medida;

static void anotar(Medida* m, f32 pluma, s32 indice, f32 escala) {
    f32 izq = pluma + tinta_izquierda_glifo[indice] * escala;
    f32 der = pluma + tinta_derecha_glifo[indice] * escala;
    if (m->n < GLIFOS_MAX && tinta_derecha_glifo[indice] > 0) {
        m->pluma[m->n] = pluma;
        m->indice[m->n] = indice;
        if (m->n == 0 || izq < m->izq) {
            m->izq = izq;
        }
        if (m->n == 0 || der > m->der) {
            m->der = der;
        }
        m->n++;
    }
}

// imprimir_texto0: izquierda, la pluma avanza sin redondear
static void medir_texto0(Medida* m, char* c, s32 x, f32 ex, s32 tracking) {
    s32 acumulado = 0, bytes, indice;
    for (; *c != 0; c += bytes) {
        indice = leer_glifo(c, &bytes);
        if (indice >= 0) {
            anotar(m, x + (acumulado * ex), indice, ex);
            acumulado += ancho_pantalla_glifo[indice] + tracking;
        } else if (indice == -1) {
            acumulado += tracking + ANCHO_ESPACIO;
        } else {
            return;
        }
    }
}

// imprimir_texto1: mide la cadena, la alinea y avanza en enteros
static void medir_texto1(Medida* m, char* texto, s32 x, f32 ex, s32 tracking, s32 alineacion) {
    s32 ancho = 0, bytes, indice;
    char* c;
    for (c = texto; *c != 0; c += bytes) {
        indice = leer_glifo(c, &bytes);
        if (indice >= 0) {
            ancho += ((ancho_pantalla_glifo[indice] + tracking) * ex);
        } else if (indice == -1) {
            ancho += ((tracking + ANCHO_ESPACIO) * ex);
        } else {
            return; // el juego no dibuja nada
        }
    }
    x -= (alineacion == DER) ? ancho : ancho / 2;
    for (c = texto; *c != 0; c += bytes) {
        indice = leer_glifo(c, &bytes);
        if (indice >= 0) {
            anotar(m, x, indice, ex);
            x = x + (s32) ((ancho_pantalla_glifo[indice] + tracking) * ex);
        } else {
            x = x + (s32) ((tracking + ANCHO_ESPACIO) * ex);
        }
    }
}

// imprimir_texto2: cada glifo centrado en su celda de 12 (32 las cifras grandes)
static void medir_texto2(Medida* m, char* c, s32 x, f32 ex, s32 tracking) {
    s32 bytes, indice, celda;
    for (; *c != 0; c += bytes) {
        indice = leer_glifo(c, &bytes);
        if (indice >= 0) {
            anotar(m, x - (ancho_pantalla_glifo[indice] / 2), indice, ex);
            celda = (indice >= 0xD5 && indice < 0xE0) ? 0x20 : 0xC;
            x = x + (s32) ((celda + tracking) * ex);
        } else if (indice == -1) {
            x = x + (s32) ((tracking + ANCHO_ESPACIO) * ex);
        } else {
            return;
        }
    }
}

static Medida medir(char* texto, s32 impresora, f32 x, f32 ex, s32 tracking) {
    Medida m;
    memset(&m, 0, sizeof(m));
    switch (impresora) {
        case IZQ:
            medir_texto0(&m, texto, (s32) x, ex, tracking);
            break;
        case DER:
        case CENTRO:
            medir_texto1(&m, texto, (s32) x, ex, tracking, impresora);
            break;
        case MONO:
            medir_texto2(&m, texto, (s32) x, ex, tracking);
            break;
        case DEPURACION:
            m.izq = x + DEPURACION_MARGEN;
            m.der = m.izq + DEPURACION_CELDA * (f32) strlen(texto);
            m.n = (s32) strlen(texto);
            break;
    }
    return m;
}

// (a) Cada caracter tiene su glifo y no cae en un comodin
static void probar_glifos_menu(const TablaTexto* t, s32 i) {
    char* c = t->cadenas[i];
    s32 bytes, indice;
    for (; *c != 0; c += bytes) {
        indice = leer_glifo(c, &bytes);
        COMPROBACION(indice != -2 && indice < GLIFOS_EN_LISTA, "%s[%d]: byte %02X sin glifo", t->nombre, i, (u8) *c);
        COMPROBACION(indice != GLIFO_B || *c == 'B' || *c == 'b', "%s[%d]: byte %02X se dibuja con el comodin 'B'",
                     t->nombre, i, (u8) *c);
        COMPROBACION(indice != GLIFO_C || *c == 'C' || *c == 'c', "%s[%d]: %02X %02X se dibuja con el comodin 'C'",
                     t->nombre, i, (u8) c[0], (u8) c[1]);
        COMPROBACION(indice != GLIFO_DOLAR, "%s[%d]: '$' es un glifo en blanco", t->nombre, i);
        COMPROBACION(indice != GLIFO_CC || (t->permisos & PERMITE_CC), "%s[%d]: '(' se dibuja \"cc\"", t->nombre, i);
        COMPROBACION(indice != GLIFO_ASTERISCO || (t->permisos & PERMITE_ASTERISCO), "%s[%d]: '*' es un separador",
                     t->nombre, i);
        if (indice >= GLIFO_JAPONES_PRIMERO && indice < GLIFO_ES_PRIMERO) {
            s32 raya = (indice == GLIFO_RAYA) && (t->permisos & PERMITE_RAYA);
            s32 sufijo =
                (indice >= GLIFO_SUFIJO_PRIMERO && indice <= GLIFO_SUFIJO_ULTIMO) && (t->permisos & PERMITE_SUFIJO);
            COMPROBACION(raya || sufijo, "%s[%d]: glifo japones 0x%02X", t->nombre, i, indice);
        }
        if (indice < 0 && indice != -1) {
            return;
        }
    }
}

static void probar_glifos_depuracion(const TablaTexto* t, s32 i) {
    const char* c;
    for (c = t->cadenas[i]; *c != 0; c++) {
        COMPROBACION(*c >= ' ' && *c <= '~' && strchr("$&\\{|}", *c) == NULL,
                     "%s[%d]: '%c' (%02X) no esta en la fuente de depuracion", t->nombre, i, *c, (u8) *c);
    }
}

// Palabras de la cadena: letras ASCII y cualquier byte >= 0x80
static s32 es_letra(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || ((u8) c >= 0x80);
}

// (d) Ni palabras en ingles ni palabras sin su tilde
static void probar_lista_negra(const TablaTexto* t, s32 i) {
    const char* c = t->cadenas[i];
    char palabra[64];
    u32 n, k;
    while (*c != 0) {
        for (n = 0; es_letra(*c); c++) {
            if (n < sizeof(palabra) - 1) {
                palabra[n++] = (*c >= 'a' && *c <= 'z') ? *c - 'a' + 'A' : *c;
            }
        }
        palabra[n] = 0;
        for (k = 0; n > 0 && k < CANTIDAD_ARREGLO(prohibidas); k++) {
            COMPROBACION(strcmp(palabra, prohibidas[k].palabra) != 0, "%s[%d]: \"%s\" %s", t->nombre, i, palabra,
                         prohibidas[k].motivo);
        }
        if (*c != 0) {
            c++;
        }
    }
}

// (e) Cada entrada traducida coincide byte a byte con su texto esperado
static void probar_esperados(void) {
    const Esperado* e;
    u32 i;
    s32 j, veces;
    for (e = esperados; e->tabla != NULL; e++) {
        const TablaTexto* t = buscar_tabla(e->tabla);
        COMPROBACION(t != NULL, "esperado de una tabla sin registrar: %s", e->tabla);
        if (t == NULL) {
            continue;
        }
        COMPROBACION(t->estado == ES, "%s tiene textos esperados pero sigue PENDIENTE", t->nombre);
        COMPROBACION(e->indice >= t->desde && e->indice <= t->hasta, "%s[%d]: esperado fuera de rango", t->nombre,
                     e->indice);
        if (e->indice >= t->desde && e->indice <= t->hasta) {
            COMPROBACION(strcmp(t->cadenas[e->indice], e->texto) == 0, "%s[%d] = \"%s\", se esperaba \"%s\"", t->nombre,
                         e->indice, t->cadenas[e->indice], e->texto);
        }
    }
    for (i = 0; i < CANTIDAD_ARREGLO(tablas); i++) {
        for (j = tablas[i].desde; tablas[i].estado == ES && j <= tablas[i].hasta; j++) {
            for (veces = 0, e = esperados; e->tabla != NULL; e++) {
                veces += strcmp(e->tabla, tablas[i].nombre) == 0 && e->indice == j;
            }
            COMPROBACION(veces == 1, "%s[%d]: %d textos esperados (tiene que haber uno)", tablas[i].nombre, j, veces);
        }
    }
}

// (a), (b) y (d) sobre cada tabla; cuenta las que faltan por traducir
static s32 probar_tablas(void) {
    u32 i;
    s32 j, pendientes = 0;
    for (i = 0; i < CANTIDAD_ARREGLO(tablas); i++) {
        const TablaTexto* t = &tablas[i];
        COMPROBACION(t->cantidad == t->original, "%s: %d entradas, la original tiene %d (hay indices con paso fijo)",
                     t->nombre, t->cantidad, t->original);
        COMPROBACION(t->desde >= 0 && t->hasta < t->cantidad, "%s: rango %d..%d fuera de la tabla", t->nombre, t->desde,
                     t->hasta);
        for (j = t->desde; j <= t->hasta && j < t->cantidad; j++) {
            if (t->fuente == FUENTE_MENU) {
                probar_glifos_menu(t, j);
            } else {
                probar_glifos_depuracion(t, j);
            }
            if (t->estado == ES) {
                probar_lista_negra(t, j);
            }
        }
        if (t->estado == PENDIENTE) {
            pendientes++;
            if (s_detalle) {
                printf("  pendiente de traducir: %s\n", t->nombre);
            }
        }
    }
    return pendientes;
}

// El signo de la letra 'indice' dibujada en 'pluma' pisa la tinta de la linea anterior
static s32 pisa_linea_anterior(const Medida* anterior, f32 pluma, s32 indice, f32 escala) {
    f32 izq = pluma + tinta_izquierda_glifo[indice] * escala;
    f32 der = pluma + tinta_derecha_glifo[indice] * escala;
    return anterior->n > 0 && izq < anterior->der && der > anterior->izq;
}

// (f) Una letra con signo en la 2.a linea o siguientes no toca la anterior
static void probar_interlineado(const Lugar* l, const TablaTexto* t) {
    s32 i, k, minimo = (s32) ceilf(ALTO_SIGNO * l->escala_y);
    for (i = l->desde + 1; l->lineas > 1 && l->paso < minimo && i <= l->hasta; i++) {
        Medida linea, anterior;
        if ((i - l->desde) % l->lineas == 0) {
            continue;
        }
        linea = medir(t->cadenas[i], l->impresora, l->x, l->escala_x, l->tracking);
        anterior = medir(t->cadenas[i - 1], l->impresora, l->x, l->escala_x, l->tracking);
        for (k = 0; k < linea.n; k++) {
            if (linea.indice[k] >= GLIFO_ES_PRIMERO && linea.indice[k] <= GLIFO_ES_ULTIMA_LETRA) {
                COMPROBACION(!pisa_linea_anterior(&anterior, linea.pluma[k], linea.indice[k], l->escala_x),
                             "%s: %s[%d] lleva signo bajo \"%s\" con paso %d < %d (%s)", l->nombre, t->nombre, i,
                             t->cadenas[i - 1], l->paso, minimo, l->origen);
            }
        }
    }
}

// Tinta de todas las entradas de un lugar
static void medir_lugar(const Lugar* l, const TablaTexto* t, f32* izq, f32* der) {
    s32 i, hay = 0;
    for (i = l->desde; i <= l->hasta; i++) {
        Medida m = medir(t->cadenas[i], l->impresora, l->x, l->escala_x, l->tracking);
        if (m.n == 0) {
            continue;
        }
        if (!hay || m.izq < *izq) {
            *izq = m.izq;
        }
        if (!hay || m.der > *der) {
            *der = m.der;
        }
        hay = 1;
    }
    if (!hay) {
        *izq = l->x;
        *der = l->x;
    }
}

// (c) Cada entrada cabe donde se dibuja
static void probar_lugares(void) {
    s32 i, j;
    for (i = 0; i < LUGARES_TOTAL; i++) {
        const Lugar* l = &lugares[i];
        const TablaTexto* t = buscar_tabla(l->tabla);
        COMPROBACION(t != NULL, "%s: la tabla %s no esta registrada", l->nombre, l->tabla);
        if (t == NULL) {
            continue;
        }
        COMPROBACION(l->desde >= t->desde && l->hasta <= t->hasta, "%s: %s[%d..%d] fuera del rango revisado", l->nombre,
                     t->nombre, l->desde, l->hasta);
        for (j = l->desde; j <= l->hasta && j <= t->hasta; j++) {
            Medida m = medir(t->cadenas[j], l->impresora, l->x, l->escala_x, l->tracking);
            if (s_detalle && m.n > 0) {
                printf("  %-26s %s[%d] %7.1f %7.1f  \"%s\"\n", l->nombre, t->nombre, j, m.izq, m.der, t->cadenas[j]);
            }
            COMPROBACION(m.n == 0 || (m.izq >= l->x_min && m.der <= l->x_max),
                         "%s: %s[%d] \"%s\" va de %.1f a %.1f, fuera de [%.0f, %.0f] (%s)", l->nombre, t->nombre, j,
                         t->cadenas[j], m.izq, m.der, l->x_min, l->x_max, l->origen);
        }
        probar_interlineado(l, t);
    }
}

// Un texto a la izquierda de otro en la misma fila no lo pisa
static void probar_sin_solapes(void) {
    const SinSolape* s;
    for (s = sin_solapes; s->izquierdo >= 0; s++) {
        const Lugar* a = &lugares[s->izquierdo];
        const Lugar* b = &lugares[s->derecho];
        const TablaTexto* ta = buscar_tabla(a->tabla);
        const TablaTexto* tb = buscar_tabla(b->tabla);
        f32 a_izq, a_der, b_izq, b_der;
        if (ta == NULL || tb == NULL) {
            continue;
        }
        medir_lugar(a, ta, &a_izq, &a_der);
        medir_lugar(b, tb, &b_izq, &b_der);
        COMPROBACION(a_der + s->margen <= b_izq, "%s termina en %.1f y %s empieza en %.1f (margen %d, %s)", a->nombre,
                     a_der, b->nombre, b_izq, s->margen, s->origen);
    }
}

// Mitad de una cadena como la calcula el juego para separar una pareja
static s32 mitad_pareja(char* cadena, s32 hueco, f32 escala) {
    return (s32) ((obtener_ancho_cadena(cadena) + hueco) * escala) / 2;
}

// Dos textos centrados uno junto a otro: el de la izquierda se corre la mitad
// del de la derecha y al reves
static void probar_parejas(void) {
    const Pareja* p;
    s32 a, b;
    for (p = parejas; p->tabla_a != NULL; p++) {
        const TablaTexto* ta = buscar_tabla(p->tabla_a);
        const TablaTexto* tb = buscar_tabla(p->tabla_b);
        COMPROBACION(ta != NULL && tb != NULL, "pareja %s + %s sin registrar", p->tabla_a, p->tabla_b);
        if (ta == NULL || tb == NULL) {
            continue;
        }
        for (a = p->desde_a; a <= p->hasta_a; a++) {
            for (b = p->desde_b; b <= p->hasta_b; b++) {
                char* ca = ta->cadenas[a];
                char* cb = tb->cadenas[b];
                Medida ma = medir(ca, CENTRO, p->x - mitad_pareja(cb, p->hueco, p->escala), p->escala, 0);
                Medida mb = medir(cb, CENTRO, p->x + mitad_pareja(ca, p->hueco, p->escala), p->escala, 0);
                if (s_detalle) {
                    printf("  pareja %s[%d] + %s[%d] %7.1f %7.1f\n", ta->nombre, a, tb->nombre, b, ma.izq, mb.der);
                }
                COMPROBACION(ma.izq >= p->x_min && mb.der <= p->x_max && ma.der <= mb.izq,
                             "\"%s\" + \"%s\" va de %.1f a %.1f, fuera de [%.0f, %.0f] o se pisan (%s)", ca, cb, ma.izq,
                             mb.der, p->x_min, p->x_max, p->origen);
            }
        }
    }
}

// Creditos: cada uno centrado en extra_columna con su escala (items_creditos.inc.c)
static void probar_creditos(void) {
    const TablaTexto* t = buscar_tabla("texto_creditos");
    s32 i;
    COMPROBACION(CANTIDAD_ARREGLO(creditos_texto_render_info) == 63, "creditos_texto_render_info: %d entradas",
                 (s32) CANTIDAD_ARREGLO(creditos_texto_render_info));
    COMPROBACION(t != NULL && t->hasta + 1 == (s32) CANTIDAD_ARREGLO(creditos_texto_render_info),
                 "cada credito visible necesita su InfoRenderCreditos");
    for (i = 0; t != NULL && i <= t->hasta; i++) {
        const InfoRenderCreditos* info = &creditos_texto_render_info[i];
        Medida m = medir(t->cadenas[i], CENTRO, info->extra_columna, info->escalado_texto, 0);
        if (s_detalle && m.n > 0) {
            printf("  credito %2d %7.1f %7.1f  \"%s\"\n", i, m.izq, m.der, t->cadenas[i]);
        }
        COMPROBACION(m.n == 0 || (m.izq >= ZONA_SEGURA_IZQ && m.der <= ZONA_SEGURA_DER),
                     "credito %d \"%s\" va de %.1f a %.1f, fuera de la zona segura", i, t->cadenas[i], m.izq, m.der);
    }
}

// El numero grande del puesto (escala 2, 0x18 a la izquierda del centro del
// sufijo) no se mete en la primera letra del sufijo (menus_pausa.inc.c:807-814).
// En ingles la cifra y el sufijo ya se tocan hasta 1 px.
#define PUESTO_ESCALA_SUFIJO 1.2f
#define PUESTO_ESCALA_NUMERO 2.0f
#define PUESTO_DESPLAZAMIENTO_NUMERO 0x18
#define PUESTO_HUECO_MINIMO -1
static void probar_hueco_puesto(void) {
    const TablaTexto* t = buscar_tabla("texto_lugar");
    s32 i;
    for (i = 1; t != NULL && i <= t->hasta; i++) {
        char numero[2] = { (char) ('0' + i), 0 };
        Medida sufijo = medir(t->cadenas[i], CENTRO, 0, PUESTO_ESCALA_SUFIJO, 0);
        Medida cifra = medir(numero, MONO, -PUESTO_DESPLAZAMIENTO_NUMERO, PUESTO_ESCALA_NUMERO, 0);
        COMPROBACION(sufijo.n > 0 && sufijo.izq - cifra.der >= PUESTO_HUECO_MINIMO,
                     "texto_lugar[%d] \"%s\" empieza en %.1f y la cifra termina en %.1f", i, t->cadenas[i], sufijo.izq,
                     cifra.der);
    }
}

int main(int argc, char** argv) {
    s32 pendientes;
    s_detalle = (argc > 1 && strcmp(argv[1], "-v") == 0);
    pendientes = probar_tablas();
    probar_esperados();
    probar_lugares();
    probar_sin_solapes();
    probar_parejas();
    probar_creditos();
    probar_hueco_puesto();
    // Las tablas sin traducir son fallos esperados; su numero solo puede bajar
    COMPROBACION(pendientes == TABLAS_PENDIENTES, "hay %d tablas pendientes y TABLAS_PENDIENTES dice %d", pendientes,
                 TABLAS_PENDIENTES);
    printf("%d comprobaciones, %d fallos, %d fallos esperados (tablas sin traducir)\n", s_comprobaciones, s_fallos,
           pendientes);
    return s_fallos != 0;
}
