#ifndef CARRERA_INICIO_HUD_Y_OBJETOS_H
#define CARRERA_INICIO_HUD_Y_OBJETOS_H

#include <juego/estructuras_comunes.h>
#include "actualizar_objetos.h"

void inicializar_hud(void);
void reiniciar_variable_objeto(void);
void funcion_8006EB10(void);
void borrar_lista_objeto(void);
u8* copiar_texturas_varios_base_dma(u8*, u8*, u32, u32);
void cargar_mario_kart_64_logo(void);
void inicializar_ventana_item(s32);
void funcion_8006EEE8(s32);
void funcion_8006EF60(void);
void ajustes_minimapa_pista(void);
void funcion_8006F824(s32);
void funcion_8006F8CC(void);
void funcion_8006FA94(void);
void funcion_80070148(void);
void inicializar_indice_lista_objeto(void);
void inicializar_objeto_nube(s32, s32, DatosNube*);
void inicializar_nubes(DatosNube*);
void inicializar_objeto_estrella(s32, s32, DatosEstrella*);
void inicializar_estrellas(DatosEstrella*);
void inicializar_nube_circuito(void);
void funcion_80070714(void);
void inicializar_objetos_circuito(void);
void inicializar_jugador_hud_uno(void);
void inicializar_vertical_jugador_hud_dos(void);
void inicializar_jugador_hud_tres_cuatro(void);
void inicializar_horizontal_jugador_hud_dos(void);

extern s16 dato_800E5520[];
extern s16 dato_800E5548[];
extern u8* texturas_contorno_circuito[0x14];

#endif
