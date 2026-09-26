#ifndef SISTEMA_PERFILADOR_H
#define SISTEMA_PERFILADOR_H

extern u64 osClockRate;

struct DatosFramePerfilador {
     s16 veces_sonido_num;
     s16 veces_vblank_num;
     OSTime veces_juego[5];
     OSTime gfx_veces[3];
     OSTime sonido_veces[8];
     OSTime veces_vblank[8];
};

enum EventoJuegoPerfilador { INICIO_THREAD5, EJECUTAR_GUION_NIVEL, ANTES_DISPLAY_LISTS, DESPUES_DISPLAY_LISTS, FIN_THREAD5 };

enum EventoGfxPerfilador { TAREAS_EN_COLA, COMPLETO_RSP, COMPLETO_RDP };

void perfilador_registro_hilo5_tiempo(enum EventoJuegoPerfilador id_evento);
void perfilador_registro_hilo4_tiempo(void);
void perfilador_registro_gfx_tiempo(enum EventoGfxPerfilador id_evento);
void perfilador_registro_vblank_tiempo(void);
void dibujar_perfilador(void);
void pantalla_recurso(void);

extern s32 metros_recurso_activacion;

#endif
