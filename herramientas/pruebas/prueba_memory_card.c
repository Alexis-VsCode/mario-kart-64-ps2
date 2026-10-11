// memory_card.c en el PC con la libmc simulada de sdk_simulado/: carga,
// guardado, tarjeta nueva, tarjeta que deja de contestar y espera al arrancar
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <PR/ultratypes.h>
#include "sdk_simulado.c"

// cronometro_fases.h lee el contador de ciclos con mfc0: aquí sale del reloj simulado
#define SISTEMA_CRONOMETRO_FASES_H
#define CICLOS_PS2_POR_MS 294912u
static u32 ciclos_ps2(void) {
    return sim_ciclos();
}

#include "sistema/memory_card.c"
#include "sistema/opciones_port.h"

// Lo que memory_card.c toma del resto del port
ImagenGuardadoPs2 guardado_ps2;
u8 icono_partida[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
u32 tamanio_icono_partida = sizeof(icono_partida);
void *_gp;
static int partida_modificada;

#define REGISTRO_LINEAS 64
static char registro[REGISTRO_LINEAS][160];
static int n_registro;

void registrar(const char *fmt, ...) {
    va_list ap;

    if (n_registro == REGISTRO_LINEAS) {
        return;
    }
    va_start(ap, fmt);
    vsnprintf(registro[n_registro++], sizeof(registro[0]), fmt, ap);
    va_end(ap);
}

int cargar_modulo_iop(const char *camino) {
    (void) camino;
    return 1;
}

int modulos_mando_x_ps2(void) {
    return 0;
}

int tomar_partida_modificada(void) {
    int r = partida_modificada;

    partida_modificada = 0;
    return r;
}

void marcar_partida_modificada_sin_aviso(void) {
    partida_modificada = 1;
}

static int s_fallos, s_comprobaciones;

static void comprobar(int condicion, const char *caso, const char *que) {
    s_comprobaciones++;
    if (!condicion) {
        s_fallos++;
        printf("FALLO %s: %s\n", caso, que);
    }
}

static int en_registro(const char *texto) {
    int i;

    for (i = 0; i < n_registro; i++) {
        if (strstr(registro[i], texto)) {
            return 1;
        }
    }
    return 0;
}

// Estado de arranque: tarjeta vacía, libmc iniciada y el hilo creado sin correr
static void empezar_con_tele(int tele) {
    sim_reiniciar();
    sim_tipo_tele = tele;
    n_registro = 0;
    partida_modificada = 0;
    memset(&guardado_ps2, 0, sizeof(guardado_ps2));
    mc_ok = 0;
    estado_carga = PENDIENTE_CARGA;
    ranura_siguiente = 0;
    desplazamiento_gen = 0;
    archivos_legacy = 0;
    inicializar_memory_card();
}

static void empezar(void) {
    empezar_con_tele(TV_SCREEN_43);
}

static void poner_partida(const char *nombre, u32 generacion) {
    static ImagenGuardadoPs2 img;

    memset(&img, 0, sizeof(img));
    img.magic = MAGICO_GUARDADO_PS2;
    img.version = VERSION_GUARDADO_PS2;
    img.generacion = generacion;
    img.eeprom[0] = (u8) generacion;
    img.checksum = crc_imagen(&img);
    sim_poner_archivo(nombre, &img, sizeof(img));
}

// Generación de la partida guardada en la tarjeta; 0 si falta o está dañada
static u32 generacion_en_tarjeta(const char *nombre) {
    SimArchivo *a = sim_buscar(nombre);
    const ImagenGuardadoPs2 *img;

    if (a == NULL || a->largo != (int) sizeof(*img)) {
        return 0;
    }
    img = (const ImagenGuardadoPs2 *) a->datos;
    return valido_imagen(img) ? img->generacion : 0;
}

static void prueba_carga(void) {
    empezar();
    poner_partida(ARCHIVO_A_GUARDADO, 7);
    poner_partida(ARCHIVO_B_GUARDADO, 8);
    cargar_partida();
    comprobar(estado_carga == HECHO_CARGA, "carga", "la partida no se publicó");
    comprobar(guardado_ps2.generacion == 8, "carga", "no se cargó la copia más nueva (B)");
    comprobar(ranura_siguiente == COPIA_GUARDADO_A, "carga", "el próximo guardado no pisa la A");
    comprobar(sim_ordenes_ocupado == 0, "carga", "orden pedida con otra en curso");
}

// Tarjeta cambiada tras la carga: se pisa la copia más vieja con una
// generación por encima de las dos
static void prueba_tarjeta_nueva(void) {
    empezar();
    mc_ok = 1;
    estado_carga = HECHO_CARGA;
    poner_partida(ARCHIVO_A_GUARDADO, 50);
    poner_partida(ARCHIVO_B_GUARDADO, 49);
    sim_programar_info(-1);
    guardado_ps2.generacion = 3;
    comprobar(guardar_ahora() == 0, "tarjeta nueva", "el guardado falló");
    comprobar(generacion_en_tarjeta(ARCHIVO_B_GUARDADO) == 51, "tarjeta nueva", "la B no lleva la generación 51");
    comprobar(generacion_en_tarjeta(ARCHIVO_A_GUARDADO) == 50, "tarjeta nueva", "se pisó la copia más nueva");
    comprobar(ranura_siguiente == COPIA_GUARDADO_A, "tarjeta nueva", "el siguiente guardado no va a la A");
    comprobar(guardado_ps2.generacion == 3, "tarjeta nueva", "cambió la generación de la sesión");
    comprobar(en_registro("copia B con la generación 51"), "tarjeta nueva", "falta el registro de la copia elegida");
}

// La tarjeta deja de contestar a mitad: no se pide ninguna orden más y libmc
// queda desactivada
static void prueba_deja_de_contestar(void) {
    static const char *const colgadas[] = { "mcOpen " ARCHIVO_A_GUARDADO, "mcRead " ARCHIVO_A_GUARDADO, "mcMkDir",
                                            "mcWrite " ARCHIVO_B_GUARDADO };
    unsigned i;

    for (i = 0; i < sizeof(colgadas) / sizeof(colgadas[0]); i++) {
        empezar();
        mc_ok = 1;
        estado_carga = HECHO_CARGA;
        poner_partida(ARCHIVO_A_GUARDADO, 50);
        poner_partida(ARCHIVO_B_GUARDADO, 49);
        sim_programar_info(-1);
        sim_colgar(colgadas[i], 1);
        comprobar(guardar_ahora() != 0, colgadas[i], "el guardado no falló");
        comprobar(mc_ok == 0, colgadas[i], "libmc sigue activa");
        comprobar(sim_ordenes_ocupado == 0, colgadas[i], "orden pedida tras vencer la espera");
        comprobar(en_registro("no contestó en 5000 ms"), colgadas[i], "falta el registro del vencimiento");
        comprobar(generacion_en_tarjeta(ARCHIVO_B_GUARDADO) == 49, colgadas[i], "cambió la B");
    }
}

// Si una lectura de la carga vence, no se pide ninguna otra: ni la cabecera B
// ni las partidas
static void prueba_carga_deja_de_contestar(void) {
    static const char *const colgadas[] = { "mcOpen " ARCHIVO_A_GUARDADO, "mcRead " ARCHIVO_A_GUARDADO,
                                            "mcClose " ARCHIVO_A_GUARDADO };
    unsigned i;

    for (i = 0; i < sizeof(colgadas) / sizeof(colgadas[0]); i++) {
        empezar();
        mc_ok = 1;
        poner_partida(ARCHIVO_A_GUARDADO, 7);
        poner_partida(ARCHIVO_B_GUARDADO, 8);
        sim_colgar(colgadas[i], 1);
        cargar_partida();
        comprobar(mc_ok == 0, colgadas[i], "libmc sigue activa");
        comprobar(sim_ordenes_ocupado == 0, colgadas[i], "orden pedida tras vencer la espera");
        comprobar(!sim_en_traza(ARCHIVO_B_GUARDADO), colgadas[i], "se leyó la B");
        comprobar(estado_carga == PENDIENTE_CARGA, colgadas[i], "se publicó una partida");
    }

    // Vence la escritura del icono en una tarjeta sin la carpeta
    empezar();
    mc_ok = 1;
    estado_carga = HECHO_CARGA;
    sim_colgar("mcWrite " ARCHIVO_ICONO_SYS, 1);
    comprobar(guardar_ahora() != 0, "icono colgado", "el guardado no falló");
    comprobar(sim_ordenes_ocupado == 0, "icono colgado", "orden pedida tras vencer la espera");
}

// El juego espera la lectura como mucho 5 s de tiempo real, aunque
// DelayThread tarde más de lo pedido
static void prueba_espera_arranque(void) {
    empezar();
    estado_carga = HECHO_CARGA;
    esperar_cargado_memcard_ps2();
    comprobar(sim_us == 0 && n_registro == 0, "espera con la partida leída", "esperó o registró algo");

    empezar();
    sim_retraso_us = 2000;
    esperar_cargado_memcard_ps2();
    comprobar(estado_carga == CARGA_ABANDONED, "espera vencida", "la carga no quedó abandonada");
    comprobar(sim_us >= 5000000 && sim_us < 5003000, "espera vencida", "no esperó 5 s de reloj");
    comprobar(en_registro("no contestó en 5001 ms"), "espera vencida", "falta el registro con los ms reales");

    // Abandonada la carga, una lectura tardía ya no pisa la partida
    poner_partida(ARCHIVO_A_GUARDADO, 9);
    cargar_partida();
    comprobar(guardado_ps2.generacion == 0, "espera vencida", "la lectura tardía se publicó");
}

// Los archivos del formato anterior se borran tras guardar; el segundo
// borrado solo si la tarjeta contestó al primero
static void prueba_borrado_legacy(void) {
    empezar();
    poner_partida(ARCHIVO_GUARDADO_VIEJO, 4);
    poner_partida(ARCHIVO_TEMPORAL_VIEJO, 3);
    sim_carpeta = 1;
    mc_ok = 1;
    cargar_partida();
    comprobar(archivos_legacy && guardado_ps2.generacion == 4, "legacy", "no se cargó SMK64.SAV");
    comprobar(guardar_ahora() == 0, "legacy", "el guardado falló");
    comprobar(sim_buscar(ARCHIVO_GUARDADO_VIEJO) == NULL && sim_buscar(ARCHIVO_TEMPORAL_VIEJO) == NULL, "legacy",
              "quedan archivos viejos");
    comprobar(generacion_en_tarjeta(ARCHIVO_A_GUARDADO) == 4, "legacy", "la partida no pasó a la A");

    empezar();
    poner_partida(ARCHIVO_GUARDADO_VIEJO, 4);
    poner_partida(ARCHIVO_TEMPORAL_VIEJO, 3);
    sim_carpeta = 1;
    mc_ok = 1;
    cargar_partida();
    sim_colgar("mcDelete", 1);
    comprobar(guardar_ahora() == 0, "legacy colgado", "el guardado de la A no contó");
    comprobar(!sim_en_traza("mcDelete " ARCHIVO_GUARDADO_VIEJO), "legacy colgado", "se pidió el segundo borrado");
    comprobar(sim_ordenes_ocupado == 0, "legacy colgado", "orden pedida tras vencer la espera");
}

// El hilo: lee la partida, espera a que se pida guardar y guarda
static void pedir_guardar_partida(void) {
    guardado_ps2.generacion++;
    partida_modificada = 1;
    pedir_guardado();
}

// Se cambia la tarjeta por una con partidas más nuevas que la sesión
static void cambiar_tarjeta_y_guardar(void) {
    poner_partida(ARCHIVO_A_GUARDADO, 50);
    poner_partida(ARCHIVO_B_GUARDADO, 49);
    sim_programar_info(-1);
    guardado_ps2.generacion = 2;
    pedir_guardar_partida();
}

static void prueba_hilo(void) {
    empezar();
    poner_partida(ARCHIVO_A_GUARDADO, 5);
    sim_carpeta = 1;
    sim_al_esperar = pedir_guardar_partida;
    sim_correr_hilo();
    comprobar(guardado_ps2.generacion == 6, "hilo", "no se cargó la A");
    comprobar(generacion_en_tarjeta(ARCHIVO_B_GUARDADO) == 6, "hilo", "no se guardó en la B");
    comprobar(en_registro("partida guardada (generación 6)"), "hilo", "falta el registro del guardado");
    comprobar(!cargando_memcard_ps2(), "hilo", "la carga sigue pendiente");

    // Con otra tarjeta, el registro da la generación escrita, no la de la sesión
    empezar();
    sim_carpeta = 1;
    sim_al_esperar = cambiar_tarjeta_y_guardar;
    sim_correr_hilo();
    comprobar(generacion_en_tarjeta(ARCHIVO_B_GUARDADO) == 51, "hilo con otra tarjeta", "la B no lleva la 51");
    comprobar(en_registro("partida guardada (generación 51)"), "hilo con otra tarjeta",
              "el registro no da la generación escrita");

    // Sin tarjeta que conteste no se intenta guardar
    empezar();
    sim_colgar("mcGetInfo", 1);
    sim_al_esperar = pedir_guardar_partida;
    sim_correr_hilo();
    comprobar(!cargando_memcard_ps2() && mc_ok == 0, "hilo sin tarjeta", "la carga no terminó");
    comprobar(sim_n_traza == 1 && sim_ordenes_ocupado == 0, "hilo sin tarjeta", "se pidieron más órdenes");
}

// Opciones del port en SMK64CFG.DAT (CC-18): se leen en el hilo tras la
// partida y se escriben en él cuando el menú lo pide
static int opciones_iguales(const OpcionesPort *a, const OpcionesPort *b) {
    return memcmp(a, b, sizeof(*a)) == 0;
}

static OpcionesPort opciones_prueba(void) {
    OpcionesPort o;

    opciones_por_defecto(&o, 0);
    o.desplaz_x = -5;
    o.desplaz_y = 3;
    o.formato = FORMATO_PANORAMICO;
    o.truco_objeto = 8;
    o.truco_200cc = 1;
    return o;
}

static void poner_opciones(const OpcionesPort *o, int byte_danado) {
    unsigned char buf[TAM_OPCIONES_PORT];

    opciones_serializar(o, buf);
    if (byte_danado >= 0) {
        buf[byte_danado] ^= 0x40;
    }
    sim_poner_archivo(ARCHIVO_OPCIONES, buf, sizeof(buf));
}

static void prueba_opciones_carga(void) {
    OpcionesPort esperadas, defecto;
    u32 version;

    empezar_con_tele(TV_SCREEN_169);
    sim_correr_hilo();
    opciones_por_defecto(&defecto, 1);
    comprobar(pantalla_osd_169 == 1, "opciones sin archivo 16:9", "no se leyó la tele de la BIOS");
    comprobar(opciones_iguales(&opciones_port, &defecto), "opciones sin archivo 16:9", "no son las de por defecto");
    comprobar(opciones_port.formato == FORMATO_CON_BANDAS, "opciones sin archivo 16:9", "el formato no es con bandas");

    empezar_con_tele(TV_SCREEN_FULL);
    sim_correr_hilo();
    opciones_por_defecto(&defecto, 0);
    comprobar(pantalla_osd_169 == 0, "opciones sin archivo FULL", "FULL no es 16:9");
    comprobar(opciones_iguales(&opciones_port, &defecto), "opciones sin archivo FULL", "no son las de por defecto");

    empezar_con_tele(TV_SCREEN_43);
    esperadas = opciones_prueba();
    poner_opciones(&esperadas, -1);
    poner_partida(ARCHIVO_A_GUARDADO, 5);
    version = version_opciones_port;
    sim_correr_hilo();
    comprobar(opciones_iguales(&opciones_port, &esperadas), "opciones válidas", "no se cargaron");
    comprobar(version_opciones_port != version, "opciones válidas", "el GS no se entera del cambio");
    comprobar(guardado_ps2.generacion == 5, "opciones válidas", "la partida no se cargó");

    empezar_con_tele(TV_SCREEN_169);
    poner_opciones(&esperadas, 9);
    sim_correr_hilo();
    opciones_por_defecto(&defecto, 1);
    comprobar(opciones_iguales(&opciones_port, &defecto), "opciones dañadas", "no se quedaron las de por defecto");
}

static void cambiar_opciones(void) {
    opciones_port = opciones_prueba();
    pedir_guardado_opciones();
}

static void prueba_opciones_guardado(void) {
    unsigned char buf[TAM_OPCIONES_PORT];
    OpcionesPort leidas, esperadas = opciones_prueba();
    SimArchivo *a;

    // Tarjeta vacía: se crea la carpeta con el icono y solo se escribe el archivo de opciones
    empezar_con_tele(TV_SCREEN_43);
    sim_al_esperar = cambiar_opciones;
    sim_correr_hilo();
    a = sim_buscar(ARCHIVO_OPCIONES);
    comprobar(a != NULL && a->largo == TAM_OPCIONES_PORT, "guardar opciones", "no hay 32 bytes en la tarjeta");
    if (a != NULL) {
        memcpy(buf, a->datos, sizeof(buf));
        comprobar(opciones_deserializar(buf, &leidas, 0) && opciones_iguales(&leidas, &esperadas), "guardar opciones",
                  "lo escrito no da las opciones");
        comprobar((buf[28] | (buf[29] << 8) | (buf[30] << 16) | ((u32) buf[31] << 24)) == crc32(buf, 28),
                  "guardar opciones", "el CRC no es el de los 28 primeros bytes");
    }
    comprobar(sim_buscar(ARCHIVO_ICONO_SYS) != NULL, "guardar opciones", "la carpeta nueva no tiene icono");
    comprobar(sim_buscar(ARCHIVO_A_GUARDADO) == NULL && sim_buscar(ARCHIVO_B_GUARDADO) == NULL, "guardar opciones",
              "se escribió una partida");

    // Sin cambios respecto a lo leído no se escribe
    empezar_con_tele(TV_SCREEN_43);
    poner_opciones(&esperadas, -1);
    sim_al_esperar = cambiar_opciones;
    sim_correr_hilo();
    comprobar(!sim_en_traza("mcWrite " ARCHIVO_OPCIONES), "opciones sin cambios", "se reescribió el archivo");

    // Si la tarjeta no contesta a la escritura, libmc se desactiva y no se pide nada más
    empezar_con_tele(TV_SCREEN_43);
    sim_carpeta = 1;
    sim_colgar("mcWrite " ARCHIVO_OPCIONES, 1);
    sim_al_esperar = cambiar_opciones;
    sim_correr_hilo();
    comprobar(mc_ok == 0 && sim_ordenes_ocupado == 0, "opciones colgadas", "se siguió pidiendo órdenes");
}

// Si el guardado de opciones ve primero la tarjeta nueva, el de la partida
// tiene que releer sus cabeceras igualmente
static void guardar_partida_tras_opciones(void) {
    guardado_ps2.generacion = 2;
    pedir_guardar_partida();
}

static void cambiar_tarjeta_y_opciones(void) {
    poner_partida(ARCHIVO_A_GUARDADO, 50);
    poner_partida(ARCHIVO_B_GUARDADO, 49);
    sim_programar_info(-1);
    cambiar_opciones();
    sim_al_esperar = guardar_partida_tras_opciones;
}

static void prueba_opciones_tarjeta_nueva(void) {
    empezar_con_tele(TV_SCREEN_43);
    sim_carpeta = 1;
    sim_al_esperar = cambiar_tarjeta_y_opciones;
    sim_correr_hilo();
    comprobar(sim_buscar(ARCHIVO_OPCIONES) != NULL, "opciones y otra tarjeta", "no se escribieron las opciones");
    comprobar(generacion_en_tarjeta(ARCHIVO_B_GUARDADO) == 51, "opciones y otra tarjeta",
              "la partida no se escribió sobre la copia vieja con la 51");
    comprobar(generacion_en_tarjeta(ARCHIVO_A_GUARDADO) == 50, "opciones y otra tarjeta", "se pisó la copia más nueva");
}

int main(void) {
    prueba_carga();
    prueba_tarjeta_nueva();
    prueba_deja_de_contestar();
    prueba_carga_deja_de_contestar();
    prueba_espera_arranque();
    prueba_borrado_legacy();
    prueba_hilo();
    prueba_opciones_carga();
    prueba_opciones_guardado();
    prueba_opciones_tarjeta_nueva();

    printf("%d comprobaciones, %d %s\n", s_comprobaciones, s_fallos, s_fallos == 1 ? "fallo" : "fallos");
    return s_fallos != 0;
}
