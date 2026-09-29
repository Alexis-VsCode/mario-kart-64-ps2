#ifndef GRAFICOS_DIBUJAR_OBJETOS_H
#define GRAFICOS_DIBUJAR_OBJETOS_H

#include <juego/estructuras_comunes.h>
#include "sistema/bucle_principal.h"

void funcion_80045738(u8*, u8*, s32, s32);
void funcion_80057114(s32);
void funcion_800431B0(Vec3f, Vec3su, f32, Vtx*);
void funcion_80043220(Vec3f, Vec3su, f32, Gfx*);
void funcion_80043328(Vec3f, Vec3su, f32, Gfx*);
void funcion_80043288(Vec3f, Vec3su, f32, Gfx*);
void funcion_80043390(Vec3f, Vec3su, f32, Gfx*);
void funcion_800433F8(Vec3f, Vec3su, f32, Gfx*);
void funcion_80043460(Vec3f, Vec3su, f32, Gfx*);
void funcion_80043500(Vec3f, Vec3su, f32, Gfx*);
void funcion_800435A0(Vec3f, Vec3su, f32, Gfx*, s32);
void funcion_80043668(Vec3f, Vec3su, f32, Gfx*);
void funcion_800436D0(s32, s32, u16, f32, Vtx*);
void funcion_80043764(s32, s32, u16, f32, Vtx*);
void funcion_800437F8(s32, s32, u16, f32, Vtx*, s32);
void funcion_800438C4(s32, s32, u16, f32, Vtx*, s32);
void funcion_8004398C(s32, s32, u16, f32, Vtx*, s32);
s32 funcion_80043A54(s32);
void cargar_textura_bloque_rgba32_nomirror(u8*, s32, s32);
void cargar_textura_tile_rgba32_nomirror(u8*, s32, s32);
void cargar_textura_bloque_rgba16_espejo(u8*, s32, s32);
void cargar_textura_bloque_rgba16_nomirror(u8*, s32, s32, s32);

void cargar_textura_tile_rgba16_nomirror(u8*, s32, s32);
void cargar_nomirror_bloque_ia16_textura(u8*, s32, s32);
void cargar_nomirror_tile_ia16_textura(u8*, s32, s32);
void cargar_nomirror_bloque_ia8_textura(u8*, s32, s32);
void cargar_nomirror_tile_ia8_textura(u8*, s32, s32);
void cargar_nomirror_bloque_i8_textura(u8*, s32, s32);
void funcion_80044AB8(u8*, s32, s32);
void funcion_80044BF8(u8*, s32, s32);

void cargar_textura_rsp(u8*, s32, s32);
void cargar_mascara_textura_rsp(u8*, s32, s32, s32);
void funcion_80045614(u8*, s32, s32);
void funcion_80045B2C(Vtx*);
void funcion_80045B74(Vtx*);
void funcion_80045BBC(Vec3f, Vec3su, f32, Vtx*);
void funcion_80045C48(Vec3f, Vec3su, f32, Vtx*);
void funcion_80045D0C(u8*, Vtx*, s32, s32, s32);
void funcion_80045E10(u8*, Vtx*, s32, s32, s32);
void funcion_80045F18(u8*, Vtx*, s32, s32, s32, s32);

void funcion_800461A4(u8*, Vtx*, s32, s32, s32);
void funcion_800462A8(u8*, Vtx*, s32, s32, s32);
void funcion_800463B0(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80046424(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_800464D0(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80046544(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_800465B8(s32, s32, u16, f32, s32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80046634(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_800466B0(s32, s32, u16, f32, u8*, Vtx*, s32, s32);
void funcion_80046720(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80046794(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80046808(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80046874(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_800468E0(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32, s32);
void funcion_80046954(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80046A00(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32);
void funcion_80046A68(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80046AD4(s32, s32, u16, f32, u8*);
void funcion_80046B38(s32, s32, u16, f32, u8*);
void funcion_80046B9C(Vec3f, Vec3su, f32, u8*);
void funcion_80046BEC(s32, s32, u16, f32, u8*, Vtx*);
void funcion_80046C3C(Vec3f, Vec3su, f32, u8*, Vtx*);
void funcion_80046C78(s32, s32, u16, f32, u8*);
void funcion_80046CDC(s32, s32, u16, f32, u8*);
void funcion_80046D40(Vec3f, Vec3su, f32, u8*);
void funcion_80046D90(s32, s32, u16, f32, u8*);
void funcion_80046DF4(s32, s32, u16, f32, s32, u8*);
void cargar_textura_y_tlut(u8*, u8*, s32, s32);
void funcion_80046F60(u8*, u8*, s32, s32, s32);

void funcion_80047068(u8*, u8*, Vtx*, s32, s32, s32, s32);
void dibujar_superponer_textura_rectangulo(u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004747C(u8*, u8*, Vtx*, s32, s32, s32, s32, s32);
void funcion_8004768C(u8*, u8*, Vtx*, s32, s32, s32);
void funcion_8004788C(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047910(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047994(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047A18(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047A9C(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047B20(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32);
void funcion_80047B9C(s32, s32, u16, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047C28(s32, s32, u16, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047CB4(s32, s32, u16, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047D40(s32, s32, u16, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047DCC(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047E48(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047EC4(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047F40(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80047FBC(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);

void funcion_80048038(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void dibujar_2d_textura_en(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80048130(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32, s32);
void funcion_800481B4(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32);
void funcion_80048228(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_800482AC(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80048330(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_800483B4(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80048438(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_800484BC(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80048540(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_800485C4(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void funcion_800486B0(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_80048718(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_80048780(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*);
void funcion_800487DC(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_80048844(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_800488AC(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_80048914(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_8004897C(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_800489E4(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_80048A4C(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_80048AB4(s32, s32, u16, f32, s32, u8*, u8*, Vtx*);
void funcion_80048B24(s32, s32, u16, f32, s32, u8*, u8*, Vtx*);
void funcion_80048B94(Vec3f, Vec3su, f32, u8*, u8*, Vtx*);
void funcion_80048BE8(Vec3f, Vec3su, f32, u8*, u8*, Vtx*);
void funcion_80048C3C(Vec3f, Vec3su, f32, u8*, u8*, Vtx*);
void funcion_80048C90(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*);
void funcion_80048CEC(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*);
void funcion_80048D48(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*);
void funcion_80048DA4(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*);
void funcion_80048E00(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_80048E68(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_80048ED0(s32, s32, u16, f32, u8*, u8*, Vtx*);
void funcion_80048F38(Vec3f, Vec3su, f32, u8*, u8*, Vtx*);
void funcion_80048F8C(u8*, Vtx*, s32, s32, s32, s32);
void funcion_80044924(u8*, s32, s32);
void funcion_80044DA0(u8*, s32, s32);

void funcion_80049130(u8*, Vtx*, s32, s32, s32, s32);
void funcion_800492D4(u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049478(u8*, Vtx*, s32, s32, s32, s32);
void funcion_800497CC(u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049B20(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049B9C(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049C18(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049C94(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049D10(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049D8C(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049E08(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049E98(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049F28(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_80049FB8(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);

void funcion_8004A034(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A0B0(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A12C(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A1BC(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A258(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A2F4(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A384(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A414(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A488(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A4FC(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A570(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004A5E4(Vec3f, Vec3su, f32, u8*, Vtx*);
void funcion_8004A630(Colision*, Vec3f, f32);
void funcion_8004A6EC(s32, f32);
void funcion_8004A7AC(s32, f32);
void funcion_8004A870(s32, f32);
void funcion_8004A9B8(f32);
void funcion_8004AA10(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void funcion_8004AAA0(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004AB00(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004AB60(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004ABC0(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004AC20(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004AC80(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004ACE0(Vec3f, Vec3su, f32, u8*, Vtx*);
void funcion_8004AD2C(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004AD8C(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004ADEC(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004AE4C(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004AEAC(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004AF0C(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004AF6C(s32, s32, u16, f32, u8*, Vtx*);
void funcion_8004AFCC(s32, s32, u16, f32, u8*, Vtx*);

void funcion_8004B02C(void);
void funcion_8004B05C(u8*);
void funcion_8004B138(s32, s32, s32, s32);
void funcion_8004B180(s32, s32, s32, s32);
void renderizar_color_conjunto(s32, s32, s32, s32, s32, s32, s32);
void funcion_8004B254(s32, s32, s32);
void fijar_transparencia(s32);
void funcion_8004B310(s32);
void funcion_8004B35C(u32, u32, u32, u32);
void funcion_8004B3C8(s32);
void funcion_8004B414(s32, s32, s32, s32);
void funcion_8004B480(s32, s32, s32);
void funcion_8004B4E8(s32, s32, s32, s32);
void funcion_8004B554(s32);
void funcion_8004B5A8(s32, s32, s32, s32);
void funcion_8004B614(s32, s32, s32, s32, s32, s32, s32);
void funcion_8004B6C4(s32, s32, s32);
void funcion_8004B72C(u32, u32, u32, u32, u32, u32, u32);
void renderizar_envoltura_rectangulo_textura(s32, s32, s32, s32, s32);
void funcion_8004BB34(void);
void funcion_8004BB3C(s32, s32, s32, s32, f32);
void funcion_8004BD14(s32, s32, u32, u32, s32, u8*, u8*);

void renderizar_textura_tile_rgba32_bloque(s16 x, s16 y, u8* textura, u32 ancho, u32 altura);

void funcion_8004C024(s16, s16, s16, u16, u16, u16, u16);
void funcion_8004C148(s16, s16, s16, u16, u16, u16, u16);
void funcion_8004C354(void);
void funcion_8004C35C(void);
void dibujar_textura_hud_2d(s32, s32, u32, u32, u8*);
void funcion_8004C450(s32, s32, u32, u32, u8*);
void funcion_8004C53C(s32, s32, u32, u32, u8*);
void funcion_8004C628(s32, s32, u32, u32, u8*);
void renderizar_logo_juego(s16, s16);
void funcion_8004C91C(s32, s32, u8*, s32, s32, s32);
void funcion_8004C9D8(s32, s32, s32, u8*, s32, s32, s32, s32);
void funcion_8004CA58(s32, s32, f32, u8*, s32, s32);
void dibujar_textura_8x_hud_2d_8(s32, s32, u8*);
void dibujar_textura_8x_hud_2d_16(s32, s32, u8*);
void dibujar_textura_16x_hud_2d_16(s32, s32, u8*);
void dibujar_textura_32x_hud_2d_8(s32, s32, u8*);
void dibujar_textura_32x_hud_2d_16(s32, s32, u8*);

// TIEMPO y VUELTA no entran en 32 columnas: sus texturas miden 64 y se dibujan
// corridas para terminar donde terminaban las de 32 (no se acercan a los digitos).
// La de VUELTA lleva debajo (filas 8 a 15) VTA., la de 3 y 4 jugadores.
#define PALABRA_HUD_ANCHO 64
#define PALABRA_HUD_X(x) ((x) - 16)
#define PALABRA_HUD_VUELTA_CORTA ((u8*) comun_textura_hud_vuelta + PALABRA_HUD_ANCHO * 8 * 2)
void funcion_8004CBC0(s32, s32, f32, u8*);
void dibujar_textura_32x_hud_2d_32(s32, s32, u8*);
void funcion_8004CC24(s32, s32, u8*);
void dibujar_textura_40x_hud_2d_32(s32, s32, u8*);
void funcion_8004CC84(s32, s32, u8*);
void funcion_8004CCB4(s32, s32, u8*);
void funcion_8004CCE4(s32, s32, f32, u8*);
void funcion_8004CD18(s32, s32, u8*);
void funcion_8004CF9C(s32, s32, u8*, s32, s32, s32, s32);
void funcion_8004CFF0(s32, s32, u8*, s32, s32, s32, s32);

void funcion_800552BC(s32);
void funcion_800450C8(u8*, s32, s32);
void funcion_80044F34(u8*, s32, s32);
void funcion_8004D044(s32, s32, u8*, s32, s32, s32, s32, s32, s32, s32, s32);
void funcion_8004D0CC(void);
void funcion_8004D0D4(s32, s32, u8*, s32, s32, s32);
void funcion_8004D210(s32, s32, u8*, s32, s32, s32, s32, s32, s32, s32, s32);
void funcion_8004D37C(s32, s32, u8*, s32, s32, s32, s32, s32, s32, s32, s32);
void funcion_8004D4E8(s32, s32, u8*, s32, s32, s32, s32, s32, s32, s32, s32);
void funcion_8004DC34(s32, s32, u8*);
void funcion_8004DC6C(s32, s32, u8*);
void funcion_8004DCA4(s32, s32, u8*);
void funcion_8004DCDC(s32, s32, u8*);
void funcion_8004DD0C(s32, s32, u8*);
void funcion_8004DD44(s32, s32, u8*);
void funcion_8004DD74(s32, s32, u8*);
void funcion_8004DDAC(s32, s32, u8*);
void funcion_8004DDDC(s32, s32, u8*);
void funcion_8004DE04(s32, s32, u8*);
void funcion_8004DE2C(s32, s32, u8*);
void funcion_8004DE54(s32, s32, u8*);
void funcion_8004DE84(s32, s32, u8*);
void funcion_8004DEB4(s32, s32, u8*);
void funcion_8004DEEC(s32, s32, u8*);
void funcion_8004DF24(s32, s32, u8*);

void funcion_8004F6D0(s32);
void funcion_8004E238(void);
void funcion_8004E240(s32, s32, u8*, u8*, s32, s32, s32);
void funcion_8004E2B8(s32, s32, s32, u8*, u8*, s32, s32, s32);
void funcion_8004E338(s32, s32, u8*, u8*, s32, s32);
void funcion_8004E3B8(void);
void funcion_8004E3C0(s32, s32, u8*, u8*, s32, s32, s32, s32);
void funcion_8004E3F4(s32, s32, s32, u8*, u8*, s32, s32, s32, s32);
void funcion_8004E430(s32, s32, u8*, u8*);
void funcion_8004E464(s32, s32, u8*, u8*);
void funcion_8004E498(s32, s32, u8*, u8*);
void funcion_8004E4CC(s32, s32, u8*, u8*);
void funcion_8004E500(s32, s32, u8*, u8*);
void funcion_8004E534(s32, s32, u8*, u8*);
void funcion_8004E568(s32, s32, u8*, u8*);
void funcion_8004E59C(s32, s32, s32, u8*, u8*);
void funcion_8004E5D8(s32, s32, u8*, u8*);
void funcion_8004E604(s32, s32, u8*, u8*);
void dibujar_ventana_item(s32);
void funcion_8004E6C4(s32);
void dibujar_cantidad_vuelta_simplificado(s32);
void funcion_8004E800(s32);
void funcion_8004E998(s32);
void funcion_8004EB30(s32);
void funcion_8004EB38(s32);
void funcion_8004EB38(s32);
void funcion_8004ED40(s32);
void funcion_8004EE54(s32);

void funcion_8004EF9C(s32);
void renderizar_minimapa_linea_meta(s32);
void dibujar_personaje_minimapa(s32, s32, s32);
void funcion_8004F3E4(s32);
s32 funcion_8004F674(s32*, s32);
void imprimir_temporizador(s32, s32, s32);
void funcion_8004F950(s32, s32, s32, s32);
void imprimir_rainbow_temporizador(s32, s32, s32);
void renderizar_temporizador_hud(s32);
void dibujar_cantidad_vuelta(s16, s16, s8);
void funcion_8004FDB4(f32, f32, s16, s16, s16, s32, s32, s32, s32);

void funcion_80050320(void);
s32 funcion_80050644(u16, s32*, s32*);
void funcion_800507D8(u16, s32*, s32*);
void funcion_800508C0(void);
void funcion_80050C68(void);
void funcion_80050E34(s32, s32);

void funcion_800514BC(void);
void renderizar_particula_hoja_objeto(s32);
void renderizar_particulas_copos_objeto(void);
void funcion_800518F8(s32, s16, s16);
void funcion_800519D4(s32, s16, s16);
void funcion_80051ABC(s16, s32);
void funcion_80051C60(s16, s32);
void funcion_80051EBC(void);
void funcion_80051EF8(void);
void funcion_80051F9C(void);

void funcion_80052044(void);
void funcion_80052080(void);
void funcion_800520C0(s32);
void funcion_8005217C(s32);
void funcion_800523B8(s32, s32, u32);
void renderizar_boos_objeto(s32);
void renderizar_murcielago_objeto(s32);
void renderizar_bin_basura_objeto(s32);
void funcion_8005285C(s32);
void funcion_800528EC(s32);
void renderizar_bloque_hielo(s32);
void funcion_80052D70(s32);
void funcion_80052E30(s32);
void renderizar_lista_muniecos_nieve_objeto_2(s32);

void renderizar_lista_muniecos_nieve_objeto_1(s32);
void renderizar_muniecos_nieve_objeto(s32);
void renderizar_lakitu(s32);
void funcion_800534A4(s32);
void funcion_800534E8(s32);
void renderizar_modelo_thwomps_objeto(s32);
void renderizar_thwomps_objeto(s32);
void funcion_80053D74(s32, s32, s32);
void renderizar_objeto_gran_premio_globos(s32);

void renderizar_objeto_tren_humo_particula(s32, s32);
void renderizar_objeto_trenes_humo_particulas(s32);
void renderizar_objeto_paleta_barco_humo_particula(s32, s32);
void renderizar_objeto_paleta_barco_humo_particulas(s32);
void renderizar_objeto_bowser_particula_llama(s32, s32);
void renderizar_objeto_bowser_llama(s32);
void funcion_8005477C(s32, u8, Vec3f);
void renderizar_particulas_humo_objeto(s32);
void funcion_80054AFC(s32, Vec3f);
void funcion_80054BE8(s32);
void funcion_80054D00(s32, s32);
void funcion_80054E10(s32);
void funcion_80054EB8(s32);
void funcion_80054F04(s32);

void renderizar_topos_objeto(s32);
void funcion_80055164(s32);
void funcion_80055228(s32);
void funcion_800552BC(s32);
void renderizar_gaviotas_objeto(s32);
void dibujar_cangrejos(s32, s32);
void renderizar_cangrejos_objeto(s32);
void funcion_800555BC(s32, s32);
void renderizar_erizos_objeto(s32);
void funcion_800557AC(void);
void funcion_800557B4(s32, u32, u32);
void renderizar_pinguinos_tren_objeto(s32);
void funcion_80055AB8(s32, s32);
void renderizar_chomps_cadena_objeto(s32);
void funcion_80055CCC(s32, s32);
void renderizar_objeto_globo_aerostatico(s32);
void funcion_80055EF4(s32, s32);
void funcion_80055F48(s32);
void funcion_80055FA0(s32, s32);

void funcion_80056160(s32);
void renderizar_neon_objeto(s32);
void funcion_800562E4(s32, s32, s32);
void funcion_800563DC(s32, s32, s32);
void funcion_800568A0(s32, s32);
void funcion_8005669C(s32, s32, s32);
void funcion_800569F4(s32);
void funcion_80056A40(s32, s32);
void funcion_80056A94(s32);
void renderizar_objeto_kart_bomba(s32);
void funcion_80056E24(s32, Vec3f);
void funcion_80056FCC(s32);

void funcion_80057114(s32);
void funcion_8005762C(s32*, s32*, s32, u32);
void funcion_80057330(void);
void funcion_80057338(void);
void funcion_800573BC(void);
void funcion_800573C4(void);
void funcion_800573CC(void);
void funcion_800573D4(void);
void funcion_800573DC(void);
void funcion_800573E4(s32, s32, s8);
void texto_envoltura_depuracion(s32*, s32*);
void imprimir_cadena_depuracion(s32*, s32*, char*);
void imprimir_numero_depuracion(s32*, s32*, s32, u32);
void funcion_80057708(void);
void cargar_fuente_depuracion(void);
void funcion_80057778(void);
void imprimir_cad2_depuracion(s32, s32, char*);
void imprimir_num_cad(s32, s32, char*, s32);
void funcion_80057814(s32, s32, char*, u32);
void funcion_80057858(s32, s32, char*, u32);
void funcion_800578B0(s32, s32, char*, u32);
void funcion_80057908(s32, s32, char*, u32);
void funcion_80057960(s32, s32, char*, u32);
void funcion_800579B8(s32, s32, char*);
void funcion_800579F8(s32, s32, char*, u32);
void funcion_80057A50(s32, s32, char*, u32);
void funcion_80057AA8(s32, s32, char*, u32);
void funcion_80057B14(s32, s32, char*, u32);
void funcion_80057B80(s32, s32, char*, u32);
void funcion_80057BEC(s32, s32, char*, u32);

extern f32 dato_801637C4;
extern s32 dato_801637E8;
extern f32 dato_801637F0;

extern s32 dato_80163814;

extern s32 dato_801655CC;

extern u16 dato_8016579E;

extern Vec3su dato_80183E80;

extern f32 dato_8018CFEC;
extern f32 dato_8018CFF4;
extern s16 minimapa_x;
extern s16 minimapa_y;

extern u8* dato_8018D4BC;
extern u8* dato_8018D4C0;

extern u8* texturas_retrato[];

extern Lights1 dato_800E4638;
extern Lights1 dato_800E4650;
extern Lights1 dato_800E4668;
extern Lights1 dato_800E4680;
extern Lights1 dato_800E4698;

extern u8 d_circuito_bowsers_castle_thwomp_tlut[];

#endif
