// SDK de PS2 simulado para el PC: una Memory Card en memoria con órdenes que
// tardan, o que no vuelven nunca, un reloj que solo avanza con DelayThread y
// semáforos sin hilos. Se incluye en la unidad de la prueba antes del código
// que se prueba.
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "delaythread.h"
#include "kernel.h"
#include "libmc.h"
#include "osd_config.h"

#define SIM_ARCHIVOS 16
#define SIM_TAM_ARCHIVO 40000
#define SIM_SEMAS 8
#define SIM_TRAZA 256
#define SIM_INFOS 8
#define SIM_NUNCA UINT64_MAX

typedef struct {
    int usado;
    char nombre[64];
    int largo;
    unsigned char datos[SIM_TAM_ARCHIVO];
} SimArchivo;

static SimArchivo sim_archivos[SIM_ARCHIVOS];
static int sim_carpeta;     // existe /BASLUS-99999SMK64
static uint64_t sim_us;     // reloj simulado
static int sim_retraso_us;  // lo que DelayThread tarda de más
static int sim_ms_orden;    // lo que tarda cada orden en contestar
static int sim_tipo_tele = TV_SCREEN_43;

// Respuestas de mcGetInfo en orden: 0 la misma tarjeta, -1 otra; después, 0
static int sim_infos[SIM_INFOS];
static int sim_n_infos, sim_i_info;

// La orden número sim_colgar_vez que contiene sim_colgar_texto no vuelve
static const char *sim_colgar_texto;
static int sim_colgar_vez, sim_colgar_vistas;

static char sim_traza[SIM_TRAZA][96];
static int sim_n_traza;
static int sim_ordenes_ocupado; // órdenes pedidas con otra sin terminar

static int sim_pendiente;
static uint64_t sim_fin_us;
static int sim_resultado;
static int *sim_info_tipo, *sim_info_formato;

static int sim_semas[SIM_SEMAS];
static int sim_n_semas;
static void (*sim_func_hilo)(void *);
static jmp_buf sim_bloqueo;
static void (*sim_al_esperar)(void); // se llama una vez cuando el hilo se queda esperando

static void sim_reiniciar(void)
{
    memset(sim_archivos, 0, sizeof(sim_archivos));
    sim_carpeta = 0;
    sim_us = 0;
    sim_retraso_us = 0;
    sim_ms_orden = 1;
    sim_tipo_tele = TV_SCREEN_43;
    sim_n_infos = sim_i_info = 0;
    sim_colgar_texto = NULL;
    sim_colgar_vez = 1;
    sim_colgar_vistas = 0;
    sim_n_traza = 0;
    sim_ordenes_ocupado = 0;
    sim_pendiente = 0;
    sim_n_semas = 0;
    sim_func_hilo = NULL;
    sim_al_esperar = NULL;
}

static SimArchivo *sim_buscar(const char *nombre)
{
    int i;

    for (i = 0; i < SIM_ARCHIVOS; i++) {
        if (sim_archivos[i].usado && strcmp(sim_archivos[i].nombre, nombre) == 0) {
            return &sim_archivos[i];
        }
    }
    return NULL;
}

static SimArchivo *sim_crear(const char *nombre)
{
    SimArchivo *a = sim_buscar(nombre);
    int i;

    for (i = 0; a == NULL && i < SIM_ARCHIVOS; i++) {
        if (!sim_archivos[i].usado) {
            a = &sim_archivos[i];
            a->usado = 1;
            strncpy(a->nombre, nombre, sizeof(a->nombre) - 1);
            a->largo = 0;
        }
    }
    return a;
}

static void sim_poner_archivo(const char *nombre, const void *datos, int largo)
{
    SimArchivo *a = sim_crear(nombre);

    memcpy(a->datos, datos, (size_t) largo);
    a->largo = largo;
}

static void sim_programar_info(int resultado)
{
    sim_infos[sim_n_infos++] = resultado;
}

static void sim_colgar(const char *texto, int vez)
{
    sim_colgar_texto = texto;
    sim_colgar_vez = vez;
    sim_colgar_vistas = 0;
}

// 1 si alguna orden de la traza contiene el texto
static int sim_en_traza(const char *texto)
{
    int i;

    for (i = 0; i < sim_n_traza; i++) {
        if (strstr(sim_traza[i], texto)) {
            return 1;
        }
    }
    return 0;
}

// Como libmc: una orden a la vez; con otra en curso se rechaza
static int sim_orden(const char *orden, const char *nombre, int resultado)
{
    char texto[96];

    if (sim_pendiente) {
        sim_ordenes_ocupado++;
        return -1;
    }
    snprintf(texto, sizeof(texto), "%s %s", orden, nombre ? nombre : "");
    if (sim_n_traza < SIM_TRAZA) {
        strcpy(sim_traza[sim_n_traza++], texto);
    }
    sim_pendiente = 1;
    sim_resultado = resultado;
    sim_fin_us = sim_us + (uint64_t) sim_ms_orden * 1000;
    if (sim_colgar_texto && strstr(texto, sim_colgar_texto) && ++sim_colgar_vistas == sim_colgar_vez) {
        sim_fin_us = SIM_NUNCA;
    }
    return 0;
}

int mcInit(int type)
{
    (void) type;
    return 0;
}

int mcGetInfo(int port, int slot, int *type, int *free, int *format)
{
    int r = sim_i_info < sim_n_infos ? sim_infos[sim_i_info++] : 0;

    (void) port;
    (void) slot;
    (void) free;
    if (sim_orden("mcGetInfo", NULL, r) != 0) {
        return -1;
    }
    sim_info_tipo = type;
    sim_info_formato = format;
    return 0;
}

// Cada apertura lee o escribe desde el principio; el descriptor es el índice
int mcOpen(int port, int slot, const char *name, int mode)
{
    SimArchivo *a = (mode & sceMcFileCreateFile) ? sim_crear(name) : sim_buscar(name);

    (void) port;
    (void) slot;
    return sim_orden("mcOpen", name, a ? (int) (a - sim_archivos) : -4);
}

int mcClose(int fd)
{
    return sim_orden("mcClose", sim_archivos[fd].nombre, 0);
}

int mcRead(int fd, void *buffer, int size)
{
    SimArchivo *a = &sim_archivos[fd];
    int n = size < a->largo ? size : a->largo;

    if (sim_pendiente) {
        return sim_orden("mcRead", a->nombre, 0);
    }
    memcpy(buffer, a->datos, (size_t) n);
    return sim_orden("mcRead", a->nombre, n);
}

int mcWrite(int fd, const void *buffer, int size)
{
    SimArchivo *a = &sim_archivos[fd];

    // Una escritura que no vuelve no llega a la tarjeta
    if (sim_orden("mcWrite", a->nombre, size) != 0) {
        return -1;
    }
    if (sim_fin_us == SIM_NUNCA) {
        return 0;
    }
    memcpy(a->datos, buffer, (size_t) size);
    if (size > a->largo) {
        a->largo = size;
    }
    return 0;
}

int mcMkDir(int port, int slot, const char *name)
{
    int r = sim_carpeta ? -4 : 0;

    (void) port;
    (void) slot;
    if (sim_pendiente) {
        return sim_orden("mcMkDir", name, 0);
    }
    sim_carpeta = 1;
    return sim_orden("mcMkDir", name, r);
}

int mcDelete(int port, int slot, const char *name)
{
    SimArchivo *a = sim_buscar(name);

    (void) port;
    (void) slot;
    if (sim_pendiente) {
        return sim_orden("mcDelete", name, 0);
    }
    if (a) {
        a->usado = 0;
    }
    return sim_orden("mcDelete", name, a ? 0 : -4);
}

// 0 mientras la orden no termina, 1 al terminar y -1 si no había orden
int mcSync(int mode, int *cmd, int *result)
{
    (void) mode;
    *cmd = 0;
    if (!sim_pendiente) {
        return -1;
    }
    if (sim_us < sim_fin_us) {
        return 0;
    }
    sim_pendiente = 0;
    if (sim_info_tipo) {
        *sim_info_tipo = sceMcTypePS2;
        *sim_info_formato = 1;
        sim_info_tipo = sim_info_formato = NULL;
    }
    *result = sim_resultado;
    return 1;
}

int DelayThread(int microsegundos)
{
    sim_us += (uint64_t) (microsegundos + sim_retraso_us);
    return 0;
}

static uint32_t sim_ciclos(void)
{
    return (uint32_t) (sim_us * 294912u / 1000u);
}

int DI(void)
{
    return 1;
}

int EI(void)
{
    return 1;
}

int32_t CreateSema(ee_sema_t *sema)
{
    sim_semas[sim_n_semas] = sema->init_count;
    return sim_n_semas++;
}

int32_t SignalSema(int32_t id)
{
    sim_semas[id]++;
    return id;
}

int32_t iSignalSema(int32_t id)
{
    return SignalSema(id);
}

int32_t PollSema(int32_t id)
{
    if (sim_semas[id] == 0) {
        return -1;
    }
    sim_semas[id]--;
    return id;
}

// Sin hilos: si el semáforo está a 0, el hilo simulado deja de correr salvo
// que sim_al_esperar prepare el paso siguiente
int32_t WaitSema(int32_t id)
{
    if (sim_semas[id] == 0 && sim_al_esperar) {
        void (*f)(void) = sim_al_esperar;

        sim_al_esperar = NULL;
        f();
    }
    if (sim_semas[id] == 0) {
        longjmp(sim_bloqueo, 1);
    }
    sim_semas[id]--;
    return id;
}

int32_t CreateThread(ee_thread_t *th)
{
    sim_func_hilo = (void (*)(void *)) th->func;
    return 1;
}

int32_t StartThread(int32_t id, void *args)
{
    (void) id;
    (void) args;
    return 0;
}

// Corre el hilo creado hasta que espera un semáforo que nadie va a dar
static void sim_correr_hilo(void)
{
    if (setjmp(sim_bloqueo) == 0) {
        sim_func_hilo(NULL);
    }
}

int32_t ChangeThreadPriority(int32_t id, int32_t prio)
{
    (void) id;
    (void) prio;
    return 0;
}

int32_t GetThreadId(void)
{
    return 1;
}

// La alarma salta en el acto
int32_t SetAlarm(uint16_t time, void (*handler)(int32_t, uint16_t, void *), void *arg)
{
    handler(0, time, arg);
    return 0;
}

void ExitHandler(void)
{
}

int configGetTvScreenType(void)
{
    return sim_tipo_tele;
}
