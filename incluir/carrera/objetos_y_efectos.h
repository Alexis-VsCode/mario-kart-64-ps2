#ifndef CARRERA_OBJETOS_Y_EFECTOS_H
#define CARRERA_OBJETOS_Y_EFECTOS_H

#include <juego/estructuras_comunes.h>
#include "juego/objetos.h"
#include "camara.h"

#define RENDER_PANTALLA_MODO_1J_JUGADOR_UNO JUGADOR_UNO + MODO_PANTALLA_1P
#define RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_UNO JUGADOR_UNO + PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL
#define RENDER_PANTALLA_MODO_2J_HORIZONTAL_JUGADOR_DOS JUGADOR_DOS + PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_HORIZONTAL
#define RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_UNO JUGADOR_UNO + PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL + 1
#define RENDER_PANTALLA_MODO_2J_VERTICAL_JUGADOR_DOS JUGADOR_DOS + PANTALLA_MODO_2J_PANTALLA_DIVIDIDA_VERTICAL + 1
#define RENDER_PANTALLA_MODO_3J_4J_JUGADOR_UNO JUGADOR_UNO + PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA + 5
#define RENDER_PANTALLA_MODO_3J_4J_JUGADOR_DOS JUGADOR_DOS + PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA + 5
#define RENDER_PANTALLA_MODO_3J_4J_JUGADOR_TRES JUGADOR_TRES + PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA + 5
#define RENDER_PANTALLA_MODO_3J_4J_JUGADOR_CUATRO JUGADOR_CUATRO + PANTALLA_DIVIDIDA_MODO_3J_4J_PANTALLA + 5

#define RGB32(r, g, b) ((r << 16) | (g << 8) | (b))

typedef struct {
    char desconocido_00[0x4];
    Vec3f desconocido_04;
    char desconocido_10[0x4];
    s32 indice_objeto;
    char desconocido_18[0x8];
} struct_d_8018CE10;

void funcion_8005C674(s8, s16*, s16*, s16*);
void funcion_80057C60(void);
void funcion_80057CE4(void);
void funcion_80057DD0(void);
void funcion_80057FC4(u32);

void renderizar_objeto(u32);
void renderizar_objeto_p1(void);
void renderizar_objeto_p2(void);
void renderizar_objeto_p3(void);
void renderizar_objeto_p4(void);
void renderizar_efecto_nieve_jugador(u32);
void renderizar_efecto_uno_nieve_jugador(void);
void renderizar_efecto_dos_nieve_jugador(void);
void renderizar_efecto_tres_nieve_jugador(void);
void renderizar_efecto_cuatro_nieve_jugador(void);
void renderizar_objeto_para_jugador(s32);
void renderizar_efecto_nevando(s32);
void funcion_80058BF4(void);
void funcion_80058C20(u32);
void renderizar_hud(u32);
void funcion_80058F48(void);
void funcion_80058F78(void);
void funcion_80059AC8(void);

void funcion_80059024(void);
void funcion_8005902C(void);
void funcion_800590D4(void);
void funcion_800591B4(void);
void funcion_80059358(void);
void renderizar_hud_2j_horizontal_jugador_dos_horizontal_jugador_uno(void);
void funcion_800593F0(void);
void renderizar_jugador_dos_horizontal_hud_2j(void);
void dibujar_hud_simplificado(s32);
void funcion_800594F0(void);
void renderizar_jugador_uno_vertical_hud_2j(void);
void funcion_80059528(void);
void renderizar_jugador_dos_vertical_hud_2j(void);
void renderizar_vuelta_3j_4j_hud(s32);
void funcion_800596A8(void);
void renderizar_multi_hud_1j(void);
void funcion_80059710(void);
void renderizar_multi_hud_2j(void);
void funcion_80059750(void);
void renderizar_multi_hud_3j(void);
void funcion_800597B8(void);
void renderizar_multi_hud_4j(void);
void funcion_80059820(s32);
void aleatorizar_semilla_desde_mando(s32);
void funcion_8005994C(void);
void funcion_8005995C(void);
void funcion_80059A88(s32);
void funcion_80059C50(void);
void funcion_80059D00(void);

void funcion_8005A070(void);
void funcion_8005A14C(s32);
void funcion_8005A380(void);
void funcion_8005A3C0(void);
void funcion_8005A71C(void);
void actualizar_objeto(void);
void funcion_8005A99C(void);
void funcion_8005AA34(void);
void funcion_8005AA4C(void);
void funcion_8005AA6C(s32);
void funcion_8005AA80(void);
void funcion_8005AA94(s32);
void funcion_8005AAF0(void);
void funcion_8005AB20(void);
void funcion_8005AB60(void);

void funcion_8005B7A0(void);

void funcion_8005B914(void);

void funcion_8005C360(f32);
void funcion_8005C64C(s32*);
void funcion_8005C654(s32*);
void funcion_8005C65C(s32);
void funcion_8005C6B4(s8, s16*, s16*, s16*);
void funcion_8005C728(void);
void funcion_8005C980(void);
void funcion_8005CB60(s32, s32);

void funcion_8005D0FC(s32);
void funcion_8005D18C(void);
void funcion_8005D1F4(s32);

void funcion_8005D290(void);
void reiniciar_pool_particula_jugador(Jugador*);
void fijar_posicion_particula_y_rotacion(Jugador*, Particula*, f32, f32, f32, s8, s8);
s32 inicializar_jugador_particula(Particula*, s8, f32);
s32 fijar_color_particula(Particula*, s32, s16);
s32 fijar_particula_color_al_azar_variado(Particula*, s32, s16);
void fijar_particulas_derrape(Jugador*, s16, s32, s8, s8);
void preparar_valido_particulas_derrape_comprobacion(Jugador*, s16, s32, s8, s8);
void funcion_8005DAD0(void);
void funcion_8005DAD8(Particula*, s16, s16, s16);
void preparar_particulas_rueda(Jugador*, s16, s32, s8, s8);
void funcion_8005EA94(Jugador*, s16, s32, s8, s8);
void funcion_8005ED48(Jugador*, s16, s32, s8, s8);

void funcion_8005F90C(Jugador*, s16, s32, s8, s8);

void funcion_80060504(Jugador*, s16, s32, s8, s8);
void funcion_800608E0(Jugador*, s16, s32, s8, s8);
void funcion_80060B14(Jugador*, s16, s32, s8, s8);
void funcion_80060BCC(Jugador*, s16, s32, s8, s8);
void funcion_80060F50(Jugador*, s16, s32, s8, s8);

void funcion_80061094(Jugador*, s16, s32, s8, s8);
void funcion_80061130(Jugador*, s16, s32, s8, s8);
void funcion_80061224(Jugador*, s16, s32, s8, s8);
void funcion_800612F8(Jugador*, s32, s32, s8, s8);
void funcion_80061430(Jugador*, s32, s32, s8, s8);
void funcion_800615AC(Jugador*, s16, s32, s8, s8);
void funcion_80061754(Jugador*, s16, s32, s32, s32);
void funcion_8006199C(Jugador*, s16, s32, s8, s8);
void funcion_80061A34(Jugador*, s16, s32, s8, s8);
void funcion_80061D4C(Jugador*, s16, s32, s8, s8);
void funcion_80061EF4(Jugador*, s16, s32, s8, s8);

void funcion_800621BC(Jugador*, s16, s32, s8, s8);
void funcion_80062484(Jugador*, Particula*, s32);
void funcion_800624D8(Jugador*, s32, s32, s8, s8);
void funcion_800628C0(Jugador*, s8, s8, s8);
void funcion_80062914(Jugador*, s8, s8, s8);
void funcion_80062968(Jugador*, s8, s8, s8);
void funcion_800629BC(Jugador*, s8, s8, s8);
void funcion_80062A18(Jugador*, s8, s8, s8);
void funcion_80062AA8(Jugador*, s8, s8, s8);
void funcion_80062B18(f32*, f32*, f32*, f32, f32, f32, u16, u16);
void funcion_80062C74(Jugador*, s16, s32, s32);
void funcion_80062F98(Jugador*, s16, s8, s8);

void fijar_oob_salpicadura_particula_posicion(Jugador*, s16, s8, s8);
void funcion_800631A8(Jugador*, s16, s8, s8);
void funcion_80063268(Jugador*, s16, s8, s8);
void funcion_80063408(Jugador*, s16, s8, s8);
void funcion_800635D4(Jugador*, s16, s8, s8);
void funcion_800639DC(Jugador*, s16, s8, s8);
void funcion_80063BD4(Jugador*, s16, s8, s8);
void funcion_80063D58(Jugador*, s16, s8, s8);
void funcion_80063FBC(Jugador*, s16, s32, s32);

void funcion_80064184(Jugador*, s16, s8, s8);
void funcion_800643A8(Jugador*, s16, s8, s8);
void funcion_800644E8(Jugador*, s16, s8, s8);
void funcion_80064664(Jugador*, s16, s8, s8);
void funcion_800647C8(Jugador*, s16, s8, s8);
void funcion_800648E4(Jugador*, s16, s8, s8);
void funcion_80064988(Jugador*, s16, s8, s8);
void funcion_800649F4(Jugador*, s16, s8, s8);
void funcion_80064B30(Jugador*, s16, s8, s8);
void funcion_80064C74(Jugador*, s16, s8, s8);
void funcion_80064DEC(Jugador*, s8, s8, s8);
void funcion_80064EA4(Jugador*, s8, s8, s8);
void funcion_80064F88(Jugador*, s8, s8, s8);

void funcion_80065030(Jugador*, s8, s8, s8);
void funcion_800650FC(Jugador*, s8, s8, s8);
void funcion_800651F4(Jugador*, s8, s8, s8);
void funcion_800652D4(Vec3f, Vec3s, f32);
void funcion_8006538C(Jugador*, s8, s16, s8);
void funcion_800658A0(Jugador*, s8, s16, s8);
void renderizar_particulas_derrape_jugador(Jugador*, s8, s16, s8);
void renderizar_particulas_suelo_jugador(Jugador*, s8, s16, s8);

void funcion_800664E0(Jugador*, s8, s16, s8);
void funcion_80066998(Jugador*, s8, s16, s8);
void funcion_80066BAC(Jugador*, s8, s16, s8);

void funcion_80067280(Jugador*, s8, s16, s8);
void renderizar_jugador_impulso_chispa_particulas(Jugador*, s8, s16, s8);
void renderizar_whrrrr_onomatopeya_jugador(Jugador*, s8, f32, s8, s8);
void renderizar_burbuja_voz_jugador(Jugador*, s8, u8*, s8, f32, s32);

void renderizar_nota_musica(Jugador*, s8, u8*, s8, f32, s32);
void renderizar_error_onomatopeya_jugador(Jugador*, s8, f32, s8, s8);
void funcion_80068724(Jugador*, s8, f32, s8, s8);
void renderizar_boing_onomatopeya_jugador(Jugador*, s8, f32, s8, s8);
void renderizar_pomp_onomatopeya_jugador(Jugador*, s8, f32, s8, s8);

void renderizar_particulas_golpe_actor(Jugador*, s8, s16, s8);
void funcion_80069444(Jugador*, s8, s16, s8);
void renderizar_pared_golpe_estrella_particulas(Jugador*, s8, s16, s8, f32);
void funcion_80069938(Jugador*, s8, s16, s8);
void funcion_80069BA8(Jugador*, s8, s16, s8);
void funcion_80069DB8(Jugador*, s8, s16, s8);

void funcion_8006A01C(Jugador*, s8, s16, s8);
void funcion_8006A280(Jugador*, s8, s16, s8);
void inicializar_globo(Jugador*, f32, f32, s8, s8, s16);
void actualizar_posicion_globo_jugador_uno(Jugador*, f32, f32, s8, s8);
void renderizar_globo_batalla(Jugador*, s8, s16, s8);

void inicializar_todos_globos_jugador(Jugador*, s8);
void borrar_todos_globos_jugador(Jugador*, s8);
void sacar_globo_jugador(Jugador*, s8);
void fijar_globo_jugador_a_ido(s32, s8, s8);
void actualizar_posicion_globos_jugador(Jugador*, s8);
void renderizar_globos_batalla_restante(Jugador*, s8, s8);
void renderizar_globo(Vec3f, f32, s16, s16);

void funcion_8006C0C8(Vec3f, f32, s32, s16);
void funcion_8006C294(Vec3f, f32, s32, s16);
void funcion_8006C4D4(Vec3f, f32, s32, s16, s16);
void funcion_8006C6AC(Jugador*, s16, s8, s8);
void funcion_8006C9B8(Jugador*, s16, s8, s8);
void funcion_8006CEC0(Jugador*, s16, s8, s8);

void funcion_8006D194(Jugador*, s8, s8);
void funcion_8006D474(Jugador*, s8, s8);
void funcion_8006DC54(Jugador*, s8, s8);
void funcion_8006DD3C(Jugador*, s8, s8);

void funcion_8006E058(void);
void funcion_8006E420(Jugador*, s8, s8);
void renderizar_particula_kart_en_pantalla_uno(Jugador*, s8, s8);
void renderizar_particula_kart_en_pantalla_dos(Jugador*, s8, s8);
void renderizar_particula_kart_en_pantalla_tres(Jugador*, s8, s8);
void renderizar_particula_kart_en_pantalla_cuatro(Jugador*, s8, s8);
void funcion_8006E7CC(Jugador*, s8, s8);
void funcion_8006E848(Jugador*, s8, s8);
void funcion_8006E8C4(Jugador*, s8, s8);
void funcion_8006E940(Jugador*, s8, s8);
void funcion_80075CA8(void);
void funcion_80085214();

extern s16 dato_800E4730[];
extern u8** dato_800E4770[];
extern u8** dato_800E47A0[];
extern s32 dato_800E47DC[];
extern s32 dato_800E480C[];

extern f32 dato_801652A0[];

extern s32 dato_80165590;
extern s32 dato_80165594;
extern s32 dato_80165598;
extern s32 dato_8016559C;
extern s32 dato_801655A4;
extern s32 dato_801655AC;
extern s32 dato_801655B4;
extern s32 dato_801655BC;
extern s32 dato_801655C0;
extern s32 dato_801655C4;
extern s32 dato_801655C8;
extern s32 dato_801655CC;
extern s32 dato_801655D8;
extern s32 dato_801655E8;
extern s32 dato_801655F0;
extern s32 dato_801655F8;

extern s32 dato_80165608;
extern s32 dato_80165618;
extern s32 dato_80165628;
extern u32 dato_80165638;
extern u32 dato_80165648;
extern u32 dato_80165658[];
extern s32 dato_80165678;
extern u16 dato_801656B0;
extern u16 dato_801656C0;
extern u16 dato_801656D0;
extern u16 dato_801656E0;
extern s16 dato_801656F0;
extern s16 dato_80165708;
extern s16 dato_80165710;

extern s16 dato_80165740;
extern s16 dato_80165748;
extern s16 dato_80165718;
extern s16 dato_80165720;
extern s16 dato_80165728;

extern s32 dato_80165754;

extern Vec4s dato_80165760;
extern s8 dato_8016576A;
extern Vec4s dato_80165770;
extern s16 dato_8016578C;
extern Vec4s dato_80165780;

extern s16 dato_80165790;
extern s16 dato_80165794;
extern s8 dato_8016579C;
extern u16 dato_8016579E;
extern u16 dato_801657A2;
extern s8 dato_801657AE;
extern s8 desactivar_hud;
extern s8 dato_801657B2;
extern s8 dato_801657B4;
extern s8 dato_801657B8[];
extern s8 dato_801657C8;
extern s8 dato_801657D0[];
extern s8 dato_801657D8;
extern s8 dato_801657E1;
extern s8 dato_801657E2;
extern s8 dato_801657E3;
extern s8 dato_801657E4;
extern s8 dato_801657E5;
extern bool8 dato_801657E6;
extern u8 dato_801657E7;
extern bool8 dato_801657E8;
extern bool8 dato_801657F0;
extern bool8 dato_801657F8;
extern s32 dato_801657FC;

extern s8 dato_80165800[2];
extern s32 dato_80165804;
extern s8 dato_80165808;
extern s32 dato_8016580C;
extern bool8 dato_80165810;
extern s32 dato_80165814;
extern bool8 dato_80165818;
extern s32 dato_8016581C;
extern s8 dato_80165820;
extern s8 dato_80165828;
extern Vec3su dato_8016582C;
extern s8 dato_80165832[2];
extern Vec3su dato_80165834;
extern s8 dato_80165840[];
extern s32 dato_80165860;
extern s32 dato_8016586C;
extern s32 dato_80165878;
extern s32 dato_8016587C;
extern u8* dato_80165880;
extern s8 dato_80165888;
extern s8 dato_80165890;
extern s8 dato_80165898;
extern s32 dato_8016589C;
extern s8 dato_801658A8;
extern s8 dato_801658BC;
extern s8 dato_801658C6;
extern s8 dato_801658CE;
extern s8 dato_801658D6;
extern s8 dato_801658DC;
extern s8 dato_801658E4;
extern s8 dato_801658EC;
extern s8 dato_801658F4;
extern u8 indice_item_aleatorio;
extern s8 dato_801658FE;
extern u8 aleatorio_mando;

extern s16 dato_80165900;
extern s8 dato_80165908;

extern s8 dato_80165A90;

extern s32 tamanio_lista_objeto;
extern Mtx dato_80183D60;

extern f32 dato_80183DA8[];

extern f32 dato_80183DC8[];

extern Vec3f dato_80183E40;

extern Vec3f dato_80183E50;

extern Vec3f dato_80183E70;

extern Vec3su dato_80183E80;

extern Vec3su dato_80183E98;

extern u8 dato_80183FA8[4][0x2000];

extern u8* lakitu_ptr_textura;

extern Colision dato_8018C3B0;

extern Colision dato_8018C830;

extern jugador_hud h_ud_jugador[];

extern struct_d_8018CE10 dato_8018CE10[];

extern Camara* dato_8018CF14;
extern s16 dato_8018CF18;
extern Jugador* dato_8018CF1C;
extern s16 dato_8018CF20;
extern Jugador* dato_8018CF28[];
extern s16 dato_8018CF48;
extern s16 dato_8018CF50[];
extern s16 dato_8018CF60;
extern s16 dato_8018CF68[];
extern s16 dato_8018CF78;
extern s16 gp_actual_carrera_personaje_id_por_puesto[];
extern f32 dato_8018CFCC;
extern f32 dato_8018CFD4;
extern s16 dato_8018CF90;
extern s16 dato_8018CF98[];
extern s16 dato_8018CFA8;
extern s16 dato_8018CFB0;
extern s16 dato_8018CFB8;
extern s16 dato_8018CFC0;
extern s16 dato_8018CFC8;
extern s16 dato_8018CFD0;
extern s16 dato_8018CFD8;
extern u8 dato_8018CFAC[];
extern u8 dato_8018CFB4[];
extern u8 dato_8018CFBC[];
extern u8 dato_8018CFC4[];
extern s16 dato_8018CFE0;
extern f32 dato_8018CFE4;
extern s16 dato_8018CFE8;
extern f32 dato_8018CFEC;
extern s16 dato_8018CFF0;
extern f32 dato_8018CFF4;
extern s16 dato_8018CFF8;
extern s16 dato_8018D000;
extern s16 dato_8018D008;
extern f32 dato_8018D00C;
extern s16 dato_8018D010;
extern s16 dato_8018D018;
extern f32 orientacion_x;
extern s16 dato_8018D020;
extern f32 dato_8018D028[];
extern s16 dato_8018D048;
extern f32 dato_8018D050[];
extern s16 dato_8018D070;
extern f32 dato_8018D078[];
extern s16 dato_8018D098;
extern f32 dato_8018D0A0[];
extern s16 dato_8018D0C0;
extern f32 dato_8018D0C8[];
extern s16 dato_8018D0E8;
extern f32 dato_8018D0F0[];
extern s16 dato_8018D110;
extern s32 dato_8018D114;
extern s32 cantidad_hud_matriz;
extern s32 dato_8018D140;
extern s32 dato_8018D150;
extern s32 dato_8018D158;
extern s32 dato_8018D160;
extern s32 dato_8018D168;
extern s16 dato_8018D16C;
extern s32 dato_8018D170;

extern s32 dato_8018D178;

extern s32 dato_8018D180;
extern s16 dato_8018D184;
extern s32 es_visible_hud;
extern s16 dato_8018D18C;
extern s32 dato_8018D190;

extern s32 dato_8018D1A0;

extern s32 dato_8018D1B4;

extern s32 dato_8018D1C4;

extern s32 dato_8018D1CC;

extern s32 dato_8018D1D4;

extern s32 dato_8018D1DC;
extern u8* direccion_logo_juego;
extern f32 dato_8018D1E8;
extern s32 dato_8018D1EC;

extern s32 dato_8018D1FC;
extern s16 dato_8018D200;
extern s32 dato_8018D204;
extern s16 dato_8018D208;
extern s32 dato_8018D20C;
extern s16 dato_8018D210;
extern bool dato_8018D214;
extern s16 dato_8018D218;
extern s32 dato_8018D21C;
extern u8 (*dato_8018D220)[1024];
extern s32 dato_8018D224;
extern u8 dato_8018D228;
extern s32 dato_8018D22C;

extern s32 dato_8018D240;
extern u8* dato_8018D248[];
extern f32 minimapa_escala_marcador;
extern s32 dato_8018D2A4;
extern s32 dato_8018D2AC;
extern s16 dato_8018D2B0;
extern s32 dato_8018D2B4;
extern s16 dato_8018D2B8;
extern s32 dato_8018D2BC;
extern s16 minimapa_linea_meta_x[];
extern s32 dato_8018D2C8[];
extern s16 minimapa_linea_meta_y[];
extern s16 minimapa_x;
extern s16 minimapa_y;
extern s16 dato_8018D2F0;
extern s16 dato_8018D2F8;
extern u16 dato_8018D300;
extern u16 dato_8018D308;
extern u16 dato_8018D310;
extern s32 dato_8018D314;
extern u16 dato_8018D318;
extern s32 dato_8018D320;
extern s32 dato_8018D380;
extern s32 dato_8018D384;
extern s32 dato_8018D388;

extern s32 dato_8018D3D4;
extern s32 dato_8018D3D8;
extern s32 dato_8018D3DC;
extern s32 dato_8018D3E0;
extern s32 dato_8018D3E4;
extern s32 dato_8018D3E8;
extern s32 dato_8018D3EC;
extern s32 dato_8018D3F0;
extern s32 dato_8018D3F4;
extern s32 dato_8018D3F8;
extern s32 contador_frame_carrera;
extern s32 dato_8018D400;
extern s32 dato_8018D40C;
extern s32 dato_8018D410;
extern u8* dato_8018D420;
extern u8* dato_8018D424;
extern u8* dato_8018D428;
extern u8* dato_8018D42C;
extern u8* dato_8018D430;
extern u8* dato_8018D434;
extern u8* dato_8018D438;
extern u8* dato_8018D43C;
extern u8* dato_8018D440;
extern u8* dato_8018D444;
extern u8* dato_8018D448;
extern u8* dato_8018D44C;
extern u8* dato_8018D450;
extern u8* dato_8018D454;
extern u8* dato_8018D458;
extern u8* dato_8018D45C;
extern u8* dato_8018D460;
extern u8* dato_8018D464;
extern u8* dato_8018D468;
extern u8* dato_8018D46C;
extern u8* dato_8018D470;
extern u8* cargado_textura_kart_sombra;
extern u8* dato_8018D478;
extern u8* dato_8018D480;
extern u8* dato_8018D484;
extern u8* dato_8018D488;
extern u8* dato_8018D48C;
extern u8* dato_8018D490;
extern u8* polvo_suelo_cargado;
extern u8* particula_pasto_cargado;
extern u8* dato_8018D49C;
extern u8* dato_8018D4A0;
extern u8* textura_poomp_onomatopeya_cargado_1;
extern u8* textura_poomp_onomatopeya_cargado_2;
extern u8* textura_whrrrr_onomatopeya_cargado_1;
extern u8* textura_whrrrr_onomatopeya_cargado_2;
extern u8* textura_error_onomatopeya_cargado_1;
extern u8* textura_error_onomatopeya_cargado_2;
extern u8* dato_8018D4BC;
extern u8* dato_8018D4C0;
extern u8* textura_cargado_rayo_0;
extern u8* textura_cargado_rayo_1;
extern Vec3f pos_x_globo_jugador[];
extern Vec3f pos_y_globo_jugador[];
extern Vec3f pos_z_globo_jugador[];
extern u16 situacion_globo_jugador[8][3];
extern Vec3s dato_8018D620[];
extern Vec3f dato_8018D650[];
extern Vec3f dato_8018D6B0[];

extern Vec3f dato_8018D710[];
extern Vec3s dato_8018D770[];
extern Vec3s dato_8018D7A0[];
extern Vec3s dato_8018D7D0[];

extern Vec3s dato_8018D800[];
extern Vec3s dato_8018D830[];
extern Vec3s rotacion_globo_jugador[];
extern Vec3s dato_8018D890[];
extern s16 cantidad_globo_jugador[];
extern Vec3s jugador_globo_partiendo_temporizador[];

#endif
