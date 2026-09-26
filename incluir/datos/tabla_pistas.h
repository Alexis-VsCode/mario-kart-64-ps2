#ifndef DATOS_TABLA_PISTAS_H
#define DATOS_TABLA_PISTAS_H

#include <ultra64.h>
#include <juego/macros.h>

struct TablaCircuito {
    u8* dl_inicio_rom;
    u8* dl_fin_rom;
    u8* inicio_rom_vertice;
    u8* fin_rom_vertice;
    u8* inicio_rom_desplazamiento;
    u8* fin_rom_desplazamiento;
    VtxCircuito* inicio_vertice;
    u32 cantidad_vertice;
    u8* inicio_empaquetado;
    u8* desplazamiento_displaylist_final;
    u32* texturas;
    u16 unknown1;
    u16 padding;
};

extern struct TablaCircuito tabla_circuito[];

extern u8 _course_mario_raceway_dl_mio0SegmentRomStart[];
extern u8 _course_mario_raceway_dl_mio0SegmentRomEnd[];
extern u8 _mario_raceway_vertexSegmentRomStart[];
extern u8 _mario_raceway_vertexSegmentRomEnd[];
extern u8 _course_mario_raceway_offsetsSegmentRomStart[];
extern u8 _course_mario_raceway_offsetsSegmentRomEnd[];
extern u8 d_circuito_mario_raceway_empaquetado[];
extern u32 mario_raceway_texturas[];

extern u8 _course_choco_mountain_dl_mio0SegmentRomStart[];
extern u8 _course_choco_mountain_dl_mio0SegmentRomEnd[];
extern u8 _choco_mountain_vertexSegmentRomStart[];
extern u8 _choco_mountain_vertexSegmentRomEnd[];
extern u8 _course_choco_mountain_offsetsSegmentRomStart[];
extern u8 _course_choco_mountain_offsetsSegmentRomEnd[];
extern u8 d_circuito_choco_mountain_empaquetado[];
extern u32 choco_mountain_texturas[];

extern u8 _course_bowsers_castle_dl_mio0SegmentRomStart[];
extern u8 _course_bowsers_castle_dl_mio0SegmentRomEnd[];
extern u8 _bowsers_castle_vertexSegmentRomStart[];
extern u8 _bowsers_castle_vertexSegmentRomEnd[];
extern u8 _course_bowsers_castle_offsetsSegmentRomStart[];
extern u8 _course_bowsers_castle_offsetsSegmentRomEnd[];
extern u8 d_circuito_bowsers_castle_empaquetado[];
extern u32 bowsers_castle_texturas[];

extern u8 _course_banshee_boardwalk_dl_mio0SegmentRomStart[];
extern u8 _course_banshee_boardwalk_dl_mio0SegmentRomEnd[];
extern u8 _banshee_boardwalk_vertexSegmentRomStart[];
extern u8 _banshee_boardwalk_vertexSegmentRomEnd[];
extern u8 _course_banshee_boardwalk_offsetsSegmentRomStart[];
extern u8 _course_banshee_boardwalk_offsetsSegmentRomEnd[];
extern u8 d_circuito_banshee_boardwalk_empaquetado[];
extern u32 banshee_boardwalk_texturas[];

extern u8 _course_yoshi_valley_dl_mio0SegmentRomStart[];
extern u8 _course_yoshi_valley_dl_mio0SegmentRomEnd[];
extern u8 _yoshi_valley_vertexSegmentRomStart[];
extern u8 _yoshi_valley_vertexSegmentRomEnd[];
extern u8 _course_yoshi_valley_offsetsSegmentRomStart[];
extern u8 _course_yoshi_valley_offsetsSegmentRomEnd[];
extern u8 d_circuito_yoshi_valley_empaquetado[];
extern u32 yoshi_valley_texturas[];

extern u8 _course_frappe_snowland_dl_mio0SegmentRomStart[];
extern u8 _course_frappe_snowland_dl_mio0SegmentRomEnd[];
extern u8 _frappe_snowland_vertexSegmentRomStart[];
extern u8 _frappe_snowland_vertexSegmentRomEnd[];
extern u8 _course_frappe_snowland_offsetsSegmentRomStart[];
extern u8 _course_frappe_snowland_offsetsSegmentRomEnd[];
extern u8 d_circuito_frappe_snowland_empaquetado[];
extern u32 frappe_snowland_texturas[];

extern u8 _course_koopa_troopa_beach_dl_mio0SegmentRomStart[];
extern u8 _course_koopa_troopa_beach_dl_mio0SegmentRomEnd[];
extern u8 _koopa_troopa_beach_vertexSegmentRomStart[];
extern u8 _koopa_troopa_beach_vertexSegmentRomEnd[];
extern u8 _course_koopa_troopa_beach_offsetsSegmentRomStart[];
extern u8 _course_koopa_troopa_beach_offsetsSegmentRomEnd[];
extern u8 d_circuito_koopa_troopa_beach_empaquetado[];
extern u32 koopa_troopa_beach_texturas[];

extern u8 _course_royal_raceway_dl_mio0SegmentRomStart[];
extern u8 _course_royal_raceway_dl_mio0SegmentRomEnd[];
extern u8 _royal_raceway_vertexSegmentRomStart[];
extern u8 _royal_raceway_vertexSegmentRomEnd[];
extern u8 _course_royal_raceway_offsetsSegmentRomStart[];
extern u8 _course_royal_raceway_offsetsSegmentRomEnd[];
extern u8 d_circuito_royal_raceway_empaquetado[];
extern u32 royal_raceway_texturas[];

extern u8 _course_luigi_raceway_dl_mio0SegmentRomStart[];
extern u8 _course_luigi_raceway_dl_mio0SegmentRomEnd[];
extern u8 _luigi_raceway_vertexSegmentRomStart[];
extern u8 _luigi_raceway_vertexSegmentRomEnd[];
extern u8 _course_luigi_raceway_offsetsSegmentRomStart[];
extern u8 _course_luigi_raceway_offsetsSegmentRomEnd[];
extern u8 d_circuito_luigi_raceway_empaquetado[];
extern u32 luigi_raceway_texturas[];

extern u8 _course_moo_moo_farm_dl_mio0SegmentRomStart[];
extern u8 _course_moo_moo_farm_dl_mio0SegmentRomEnd[];
extern u8 _moo_moo_farm_vertexSegmentRomStart[];
extern u8 _moo_moo_farm_vertexSegmentRomEnd[];
extern u8 _course_moo_moo_farm_offsetsSegmentRomStart[];
extern u8 _course_moo_moo_farm_offsetsSegmentRomEnd[];
extern u8 d_circuito_moo_moo_farm_empaquetado[];
extern u32 moo_moo_farm_texturas[];

extern u8 _course_toads_turnpike_dl_mio0SegmentRomStart[];
extern u8 _course_toads_turnpike_dl_mio0SegmentRomEnd[];
extern u8 _toads_turnpike_vertexSegmentRomStart[];
extern u8 _toads_turnpike_vertexSegmentRomEnd[];
extern u8 _course_toads_turnpike_offsetsSegmentRomStart[];
extern u8 _course_toads_turnpike_offsetsSegmentRomEnd[];
extern u8 d_circuito_toads_turnpike_empaquetado[];
extern u32 toads_turnpike_texturas[];

extern u8 _course_kalimari_desert_dl_mio0SegmentRomStart[];
extern u8 _course_kalimari_desert_dl_mio0SegmentRomEnd[];
extern u8 _kalimari_desert_vertexSegmentRomStart[];
extern u8 _kalimari_desert_vertexSegmentRomEnd[];
extern u8 _course_kalimari_desert_offsetsSegmentRomStart[];
extern u8 _course_kalimari_desert_offsetsSegmentRomEnd[];
extern u8 d_circuito_kalimari_desert_empaquetado[];
extern u32 kalimari_desert_texturas[];

extern u8 _course_sherbet_land_dl_mio0SegmentRomStart[];
extern u8 _course_sherbet_land_dl_mio0SegmentRomEnd[];
extern u8 _sherbet_land_vertexSegmentRomStart[];
extern u8 _sherbet_land_vertexSegmentRomEnd[];
extern u8 _course_sherbet_land_offsetsSegmentRomStart[];
extern u8 _course_sherbet_land_offsetsSegmentRomEnd[];
extern u8 d_circuito_sherbet_land_empaquetado[];
extern u32 sherbet_land_texturas[];

extern u8 _course_rainbow_road_dl_mio0SegmentRomStart[];
extern u8 _course_rainbow_road_dl_mio0SegmentRomEnd[];
extern u8 _rainbow_road_vertexSegmentRomStart[];
extern u8 _rainbow_road_vertexSegmentRomEnd[];
extern u8 _course_rainbow_road_offsetsSegmentRomStart[];
extern u8 _course_rainbow_road_offsetsSegmentRomEnd[];
extern u8 d_circuito_rainbow_road_empaquetado[];
extern u32 rainbow_road_texturas[];

extern u8 _course_wario_stadium_dl_mio0SegmentRomStart[];
extern u8 _course_wario_stadium_dl_mio0SegmentRomEnd[];
extern u8 _wario_stadium_vertexSegmentRomStart[];
extern u8 _wario_stadium_vertexSegmentRomEnd[];
extern u8 _course_wario_stadium_offsetsSegmentRomStart[];
extern u8 _course_wario_stadium_offsetsSegmentRomEnd[];
extern u8 d_circuito_wario_stadium_empaquetado[];
extern u32 wario_stadium_texturas[];

extern u8 _course_block_fort_dl_mio0SegmentRomStart[];
extern u8 _course_block_fort_dl_mio0SegmentRomEnd[];
extern u8 _block_fort_vertexSegmentRomStart[];
extern u8 _block_fort_vertexSegmentRomEnd[];
extern u8 _course_block_fort_offsetsSegmentRomStart[];
extern u8 _course_block_fort_offsetsSegmentRomEnd[];
extern u8 d_circuito_block_fort_empaquetado[];
extern u32 block_fort_texturas[];

extern u8 _course_skyscraper_dl_mio0SegmentRomStart[];
extern u8 _course_skyscraper_dl_mio0SegmentRomEnd[];
extern u8 _skyscraper_vertexSegmentRomStart[];
extern u8 _skyscraper_vertexSegmentRomEnd[];
extern u8 _course_skyscraper_offsetsSegmentRomStart[];
extern u8 _course_skyscraper_offsetsSegmentRomEnd[];
extern u8 d_circuito_skyscraper_empaquetado[];
extern u32 skyscraper_texturas[];

extern u8 _course_double_deck_dl_mio0SegmentRomStart[];
extern u8 _course_double_deck_dl_mio0SegmentRomEnd[];
extern u8 _double_deck_vertexSegmentRomStart[];
extern u8 _double_deck_vertexSegmentRomEnd[];
extern u8 _course_double_deck_offsetsSegmentRomStart[];
extern u8 _course_double_deck_offsetsSegmentRomEnd[];
extern u8 d_circuito_double_deck_empaquetado[];
extern u32 double_deck_texturas[];

extern u8 _course_dks_jungle_parkway_dl_mio0SegmentRomStart[];
extern u8 _course_dks_jungle_parkway_dl_mio0SegmentRomEnd[];
extern u8 _dks_jungle_parkway_vertexSegmentRomStart[];
extern u8 _dks_jungle_parkway_vertexSegmentRomEnd[];
extern u8 _course_dks_jungle_parkway_offsetsSegmentRomStart[];
extern u8 _course_dks_jungle_parkway_offsetsSegmentRomEnd[];
extern u8 d_circuito_dks_jungle_parkway_empaquetado[];
extern u32 dks_jungle_parkway_texturas[];

extern u8 _course_big_donut_dl_mio0SegmentRomStart[];
extern u8 _course_big_donut_dl_mio0SegmentRomEnd[];
extern u8 _big_donut_vertexSegmentRomStart[];
extern u8 _big_donut_vertexSegmentRomEnd[];
extern u8 _course_big_donut_offsetsSegmentRomStart[];
extern u8 _course_big_donut_offsetsSegmentRomEnd[];
extern u8 d_circuito_big_donut_empaquetado[];
extern u32 big_donut_texturas[];

#endif
