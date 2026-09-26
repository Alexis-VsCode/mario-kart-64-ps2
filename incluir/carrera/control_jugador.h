#ifndef CARRERA_CONTROL_JUGADOR_H
#define CARRERA_CONTROL_JUGADOR_H

#include <juego/estructuras_comunes.h>
#include "camara.h"

void funcion_8002E594(Jugador*, Camara*, s8, s8);

s32 obtener_indice_jugador_para_jugador(Jugador*);
void funcion_80027DA8(Jugador*, s8);
void funcion_80027EDC(Jugador*, s8);

void funcion_80029B4C(Jugador*, f32, f32, f32);
void funcion_8002F730(Jugador* jugador, Camara* camara, s8 parametro2, s8 id_jugador);

void funcion_80028864(Jugador*, Camara*, s8, s8);
void funcion_80028C44(Jugador*, Camara*, s8, s8);
void funcion_80028D3C(Jugador*, Camara*, s8, s8);
void funcion_80028E70(Jugador*, Camara*, s8, s8);
void funcion_80028F5C(s32, s32, s32, s32);
void funcion_80028F70(void);

void funcion_80029060(void);
void funcion_80029150(void);
void funcion_80029158(void);
void funcion_800291E8(void);
void funcion_800291F0(void);
void funcion_800291F8(void);
void funcion_80029200(Jugador*, s8);
void funcion_8002934C(Jugador*, Camara*, s8, s8);

void funcion_8002A194(Jugador*, f32, f32, f32);
void funcion_8002A5F4(Vec3f, f32, Vec3f, f32, f32);
void funcion_8002A704(Jugador*, s8);
void funcion_8002A79C(Jugador*, s8);
void actualizar_contador_estado_derrape(Jugador*, s8);
void salto_kart(Jugador*);
void funcion_8002AAC0(Jugador*);
void funcion_8002AB70(Jugador*);
void funcion_8002AE20(void);
void funcion_8002AE28(void);
void funcion_8002AE30(void);
void funcion_8002AE38(Jugador*, s8, f32, f32, f32, f32);

void funcion_8002B218(Jugador*);
void aplicar_disparadores(Jugador*, s8, s8);
void funcion_8002B5C0(Jugador*, s8, s8);
void funcion_8002B830(Jugador*, s8, s8);
void funcion_8002B8A4(Jugador*, Jugador*);
void funcion_8002B9CC(Jugador*, s8, s32);
void funcion_8002BD58(Jugador*);
void funcion_8002BF4C(Jugador*, s8);

void actualizar_duracion_derrape_jugador(Jugador*);
void funcion_8002C17C(Jugador*, s8);
void funcion_8002C4F8(Jugador*, s8);
void funcion_8002C7E4(Jugador*, s8, s8);
void funcion_8002C954(Jugador*, s8, Vec3f);
void aplicar_efecto(Jugador*, s8, s8);

void funcion_8002D028(Jugador*, s8);
void funcion_8002D268(Jugador*, Camara*, s8, s8);

void funcion_8002E4C4(Jugador*);
void movimiento_cpu_control(Jugador*, Camara*, s8, s8);

void funcion_8002FCA8(Jugador*, s8);
void funcion_8002FE84(Jugador*, f32);

f32 funcion_80030150(Jugador*, s8);
void funcion_80030A34(Jugador*);
void detectar_triple_a_combo_a_soltado(Jugador*);
void detectar_triple_a_combo_a_pulsado(Jugador*);
void alternativo_acelerar_jugador(Jugador*);
void alternativo_desacelerar_jugador(Jugador*, f32);
void detectar_triple_b_combo_b_soltado(Jugador*);
void detectar_triple_b_combo_b_pulsado(Jugador*);
void funcion_800323E4(Jugador*);
void empezar_secuencia_acelerar_jugador_durante(Jugador*);
void empezar_secuencia_desacelerar_jugador_durante(Jugador*, f32);
void acelerar_jugador(Jugador*);
void desacelerar_jugador(Jugador*, f32);
void global_acelerar_jugador(Jugador*, s32);
void global_desacelerar_jugador(Jugador*, f32, s32);
void funcion_80033850(Jugador*, f32);
void actualizar_grande_direccion(Jugador*, s32*, s32*, s32, s32, s32, s32);
void funcion_80033940(Jugador*, s32*, s32, s32, f32);
void funcion_800339C4(Jugador*, s32*, s32, s32, f32);
void actualizar_chico_direccion(Jugador*, s32*, s32*, s32, s32, s32, f32);
void funcion_80033AE0(Jugador*, struct Mando*, s8);

void aplicar_giro_cpu(Jugador*, s16);
void funcion_80036C5C(Jugador*);
void cancelar_efecto_derrape(Jugador*);
void funcion_80036DB4(Jugador*, Vec3f, Vec3f);

void funcion_800371F4(Jugador*, Vec3f, Vec3f);
void funcion_80037614(Jugador*, Vec3f, Vec3f);
void funcion_8003777C(Jugador*, Vec3f, Vec3f);
void funcion_800378E8(Jugador*, Vec3f, Vec3f);
void funcion_80037A4C(Jugador*, Vec3f, Vec3f);
void funcion_80037BB4(Jugador* jugador, Vec3f);
void funcion_80037CFC(Jugador*, struct Mando*, s8);

void manejar_pulsacion_a_para_jugador_durante_carrera(Jugador*, struct Mando*, s8);
void manejar_pulsacion_a_para_todos_jugadores_durante_carrera(void);
s16 obtener_limitado_palanca_x_con_zona_muerta(struct Mando*);
s16 obtener_limitado_palanca_y_con_zona_muerta(struct Mando*);
void funcion_80038BE4(Jugador*, s16);
void funcion_80038C6C(Jugador*, Camara*, s8, s8);

extern s16 cpu_para_mario[];
extern s16 cpu_para_luigi[];
extern s16 cpu_para_yoshi[];
extern s16 cpu_para_toad[];
extern s16 cpu_para_dk[];
extern s16 cpu_para_wario[];
extern s16 cpu_para_peach[];
extern s16 cpu_para_bowser[];
extern s16* cpu_para_jugador[];

extern s16 cpu_para_mario_y_luigi[];
extern s16 cpu_para_mario_y_yoshi[];
extern s16 cpu_para_mario_y_toad[];
extern s16 cpu_para_mario_y_dk[];
extern s16 cpu_para_mario_y_wario[];
extern s16 cpu_para_mario_y_peach[];
extern s16 cpu_para_mario_y_bowser[];
extern s16 cpu_para_luigi_y_mario[];
extern s16 cpu_para_luigi_y_yoshi[];
extern s16 cpu_para_luigi_y_toad[];
extern s16 cpu_para_luigi_y_dk[];
extern s16 cpu_para_luigi_y_wario[];
extern s16 cpu_para_luigi_y_peach[];
extern s16 cpu_para_luigi_y_bowser[];
extern s16 cpu_para_yoshi_y_mario[];
extern s16 cpu_para_yoshi_y_luigi[];
extern s16 cpu_para_yoshi_y_toad[];
extern s16 cpu_para_yoshi_y_dk[];
extern s16 cpu_para_yoshi_y_wario[];
extern s16 cpu_para_yoshi_y_peach[];
extern s16 cpu_para_yoshi_y_bowser[];
extern s16 cpu_para_toad_y_mario[];
extern s16 cpu_para_toad_y_luigi[];
extern s16 cpu_para_toad_y_yoshi[];
extern s16 cpu_para_toad_y_dk[];
extern s16 cpu_para_toad_y_wario[];
extern s16 cpu_para_toad_y_peach[];
extern s16 cpu_para_toad_y_bowser[];
extern s16 cpu_para_dk_y_mario[];
extern s16 cpu_para_dk_y_luigi[];
extern s16 cpu_para_dk_y_toad[];
extern s16 cpu_para_dk_y_yoshi[];
extern s16 cpu_para_dk_y_wario[];
extern s16 cpu_para_dk_y_peach[];
extern s16 cpu_para_dk_y_bowser[];
extern s16 cpu_para_wario_y_mario[];
extern s16 cpu_para_wario_y_luigi[];
extern s16 cpu_para_wario_y_yoshi[];
extern s16 cpu_para_wario_y_dk[];
extern s16 cpu_para_wario_y_toad[];
extern s16 cpu_para_wario_y_peach[];
extern s16 cpu_para_wario_y_bowser[];
extern s16 cpu_para_peach_y_mario[];
extern s16 cpu_para_peach_y_luigi[];
extern s16 cpu_para_peach_y_yoshi[];
extern s16 cpu_para_peach_y_dk[];
extern s16 cpu_para_peach_y_wario[];
extern s16 cpu_para_peach_y_toad[];
extern s16 cpu_para_peach_y_bowser[];
extern s16 cpu_para_bowser_y_mario[];
extern s16 cpu_para_bowser_y_luigi[];
extern s16 cpu_para_bowser_y_yoshi[];
extern s16 cpu_para_bowser_y_dk[];
extern s16 cpu_para_bowser_y_wario[];
extern s16 cpu_para_bowser_y_toad[];
extern s16 cpu_para_bowser_y_peach[];
extern s16* ufor_cp_lista_mario[];
extern s16* ufor_cp_lista_luigi[];
extern s16* ufor_cp_lista_yoshi[];
extern s16* ufor_cp_lista_toad[];
extern s16* ufor_cp_lista_dk[];
extern s16* ufor_cp_lista_wario[];
extern s16* ufor_cp_lista_peach[];
extern s16* ufor_cp_lista_bowser[];
extern s16** cpu_para_dos_jugador[];

extern s16 dato_801656F0;

#endif
