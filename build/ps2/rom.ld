/* Generado por herramientas/generar_rom_ld.py: no editar. */
OUTPUT_ARCH(mips:5900)
SECTIONS
{
    __romPos = 0;
    _data_segment2SegmentStart = ADDR(.data_segment2);
    __romseg_data_segment2_start = __romPos;
    .data_segment2 0x02000000 : AT(__romPos)
    {
        KEEP(build/ps2/codigo/datos/texturas.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        KEEP(build/ps2/codigo/datos/segmento_datos_2.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
    }
    _data_segment2SegmentEnd = ADDR(.data_segment2) + SIZEOF(.data_segment2);
    _data_segment2SegmentSize = SIZEOF(.data_segment2);
    __romseg_data_segment2_end = __romPos + SIZEOF(.data_segment2);
    __romPos += SIZEOF(.data_segment2);
    __romPos = ALIGN(__romPos, 16);
    _common_texturesSegmentStart = ADDR(.common_textures);
    __romseg_common_textures_start = __romPos;
    .common_textures 0x0D000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/comunes/datos_comunes.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _common_texturesSegmentEnd = ADDR(.common_textures) + SIZEOF(.common_textures);
    _common_texturesSegmentSize = SIZEOF(.common_textures);
    __romseg_common_textures_end = __romPos + SIZEOF(.common_textures);
    __romPos += SIZEOF(.common_textures);
    __romPos = ALIGN(__romPos, 16);
    _startupLogoSegmentStart = ADDR(.startupLogo);
    __romseg_startupLogo_start = __romPos;
    .startupLogo 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/logo_inicio/logo_inicio.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _startupLogoSegmentEnd = ADDR(.startupLogo) + SIZEOF(.startupLogo);
    _startupLogoSegmentSize = SIZEOF(.startupLogo);
    __romseg_startupLogo_end = __romPos + SIZEOF(.startupLogo);
    __romPos += SIZEOF(.startupLogo);
    __romPos = ALIGN(__romPos, 16);
    _audio_banksSegmentStart = ADDR(.audio_banks);
    __romseg_audio_banks_start = __romPos;
    .audio_banks 0x0 : AT(__romPos)
    {
        KEEP(build/ps2/sonido/bancos_instrumentos.o(.data));
    }
    _audio_banksSegmentEnd = ADDR(.audio_banks) + SIZEOF(.audio_banks);
    _audio_banksSegmentSize = SIZEOF(.audio_banks);
    __romseg_audio_banks_end = __romPos + SIZEOF(.audio_banks);
    __romPos += SIZEOF(.audio_banks);
    __romPos = ALIGN(__romPos, 16);
    _sequencesSegmentStart = ADDR(.sequences);
    __romseg_sequences_start = __romPos;
    .sequences 0x25FD00 : AT(__romPos)
    {
        KEEP(build/ps2/codigo/datos/secuencias_musica.o(.data));
        . = ALIGN(0x40);
    }
    _sequencesSegmentEnd = ADDR(.sequences) + SIZEOF(.sequences);
    _sequencesSegmentSize = SIZEOF(.sequences);
    __romseg_sequences_end = __romPos + SIZEOF(.sequences);
    __romPos += SIZEOF(.sequences);
    __romPos = ALIGN(__romPos, 16);
    _instrument_setsSegmentStart = ADDR(.instrument_sets);
    __romseg_instrument_sets_start = __romPos;
    .instrument_sets . : AT(__romPos)
    {
        KEEP(build/ps2/codigo/datos/conjuntos_instrumentos.o(.data));
    }
    _instrument_setsSegmentEnd = ADDR(.instrument_sets) + SIZEOF(.instrument_sets);
    _instrument_setsSegmentSize = SIZEOF(.instrument_sets);
    __romseg_instrument_sets_end = __romPos + SIZEOF(.instrument_sets);
    __romPos += SIZEOF(.instrument_sets);
    __romPos = ALIGN(__romPos, 16);
    __romPos = ALIGN(__romPos + 0x1000, 0x10000);
    __rom_stream_start = __romPos;
    _audio_tablesSegmentStart = ADDR(.audio_tables);
    __romseg_audio_tables_start = __romPos;
    .audio_tables 0x13840 : AT(__romPos)
    {
        KEEP(build/ps2/sonido/muestras_audio.o(.data));
    }
    _audio_tablesSegmentEnd = ADDR(.audio_tables) + SIZEOF(.audio_tables);
    _audio_tablesSegmentSize = SIZEOF(.audio_tables);
    __romseg_audio_tables_end = __romPos + SIZEOF(.audio_tables);
    __romPos += SIZEOF(.audio_tables);
    __romPos = ALIGN(__romPos, 16);
    _other_texturesSegmentStart = ADDR(.other_textures);
    __romseg_other_textures_start = __romPos;
    .other_textures 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/codigo/datos/otras_texturas.o(.data));
        . = ALIGN(0x10);
    }
    _other_texturesSegmentEnd = ADDR(.other_textures) + SIZEOF(.other_textures);
    _other_texturesSegmentSize = SIZEOF(.other_textures);
    __romseg_other_textures_end = __romPos + SIZEOF(.other_textures);
    __romPos += SIZEOF(.other_textures);
    __romPos = ALIGN(__romPos, 16);
    _textures_0aSegmentStart = ADDR(.textures_0a);
    __romseg_textures_0a_start = __romPos;
    .textures_0a 0x0A000000 : AT(__romPos)
    {
        KEEP(build/ps2/codigo/datos/texturas_seleccion.o(.data));
        KEEP(build/ps2/codigo/datos/texturas_fuentes.o(.data));
        KEEP(build/ps2/codigo/datos/texturas_fuentes_es.o(.data));
        . = ALIGN(0x10);
    }
    _textures_0aSegmentEnd = ADDR(.textures_0a) + SIZEOF(.textures_0a);
    _textures_0aSegmentSize = SIZEOF(.textures_0a);
    __romseg_textures_0a_end = __romPos + SIZEOF(.textures_0a);
    __romPos += SIZEOF(.textures_0a);
    __romPos = ALIGN(__romPos, 16);
    _textures_0bSegmentStart = ADDR(.textures_0b);
    __romseg_textures_0b_start = __romPos;
    .textures_0b 0x0B000000 : AT(__romPos)
    {
        KEEP(build/ps2/codigo/datos/texturas_tkmk00.o(.data));
        . = ALIGN(0x10);
    }
    _textures_0bSegmentEnd = ADDR(.textures_0b) + SIZEOF(.textures_0b);
    _textures_0bSegmentSize = SIZEOF(.textures_0b);
    __romseg_textures_0b_end = __romPos + SIZEOF(.textures_0b);
    __romPos += SIZEOF(.textures_0b);
    __romPos = ALIGN(__romPos, 16);
    _kart_texturesSegmentStart = ADDR(.kart_textures);
    __romseg_kart_textures_start = __romPos;
    .kart_textures 0x0F000000 : AT(__romPos) SUBALIGN(0x10)
    {
        KEEP(build/ps2/codigo/datos/karts/kart_luigi.o(.data));
        KEEP(build/ps2/codigo/datos/karts/kart_mario.o(.data));
        KEEP(build/ps2/codigo/datos/karts/kart_yoshi.o(.data));
        KEEP(build/ps2/codigo/datos/karts/kart_peach.o(.data));
        KEEP(build/ps2/codigo/datos/karts/kart_wario.o(.data));
        KEEP(build/ps2/codigo/datos/karts/kart_toad.o(.data));
        KEEP(build/ps2/codigo/datos/karts/kart_donkey_kong.o(.data));
        KEEP(build/ps2/codigo/datos/karts/kart_bowser.o(.data));
        KEEP(build/ps2/recursos/pistas/fantasmas_personal.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
    }
    _kart_texturesSegmentEnd = ADDR(.kart_textures) + SIZEOF(.kart_textures);
    _kart_texturesSegmentSize = SIZEOF(.kart_textures);
    __romseg_kart_textures_end = __romPos + SIZEOF(.kart_textures);
    __romPos += SIZEOF(.kart_textures);
    __romPos = ALIGN(__romPos, 16);
    _ceremonyDataSegmentStart = ADDR(.ceremonyData);
    __romseg_ceremonyData_start = __romPos;
    .ceremonyData 0x0B000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/ceremonia/datos_ceremonia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _ceremonyDataSegmentEnd = ADDR(.ceremonyData) + SIZEOF(.ceremonyData);
    _ceremonyDataSegmentSize = SIZEOF(.ceremonyData);
    __romseg_ceremonyData_end = __romPos + SIZEOF(.ceremonyData);
    __romPos += SIZEOF(.ceremonyData);
    __romPos = ALIGN(__romPos, 16);
    _course_mario_raceway_dl_mio0SegmentStart = ADDR(.course_mario_raceway_dl_mio0);
    __romseg_course_mario_raceway_dl_mio0_start = __romPos;
    .course_mario_raceway_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/mario_raceway/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_mario_raceway_dl_mio0SegmentEnd = ADDR(.course_mario_raceway_dl_mio0) + SIZEOF(.course_mario_raceway_dl_mio0);
    _course_mario_raceway_dl_mio0SegmentSize = SIZEOF(.course_mario_raceway_dl_mio0);
    __romseg_course_mario_raceway_dl_mio0_end = __romPos + SIZEOF(.course_mario_raceway_dl_mio0);
    __romPos += SIZEOF(.course_mario_raceway_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_choco_mountain_dl_mio0SegmentStart = ADDR(.course_choco_mountain_dl_mio0);
    __romseg_course_choco_mountain_dl_mio0_start = __romPos;
    .course_choco_mountain_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/choco_mountain/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_choco_mountain_dl_mio0SegmentEnd = ADDR(.course_choco_mountain_dl_mio0) + SIZEOF(.course_choco_mountain_dl_mio0);
    _course_choco_mountain_dl_mio0SegmentSize = SIZEOF(.course_choco_mountain_dl_mio0);
    __romseg_course_choco_mountain_dl_mio0_end = __romPos + SIZEOF(.course_choco_mountain_dl_mio0);
    __romPos += SIZEOF(.course_choco_mountain_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_bowsers_castle_dl_mio0SegmentStart = ADDR(.course_bowsers_castle_dl_mio0);
    __romseg_course_bowsers_castle_dl_mio0_start = __romPos;
    .course_bowsers_castle_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/bowsers_castle/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_bowsers_castle_dl_mio0SegmentEnd = ADDR(.course_bowsers_castle_dl_mio0) + SIZEOF(.course_bowsers_castle_dl_mio0);
    _course_bowsers_castle_dl_mio0SegmentSize = SIZEOF(.course_bowsers_castle_dl_mio0);
    __romseg_course_bowsers_castle_dl_mio0_end = __romPos + SIZEOF(.course_bowsers_castle_dl_mio0);
    __romPos += SIZEOF(.course_bowsers_castle_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_banshee_boardwalk_dl_mio0SegmentStart = ADDR(.course_banshee_boardwalk_dl_mio0);
    __romseg_course_banshee_boardwalk_dl_mio0_start = __romPos;
    .course_banshee_boardwalk_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/banshee_boardwalk/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_banshee_boardwalk_dl_mio0SegmentEnd = ADDR(.course_banshee_boardwalk_dl_mio0) + SIZEOF(.course_banshee_boardwalk_dl_mio0);
    _course_banshee_boardwalk_dl_mio0SegmentSize = SIZEOF(.course_banshee_boardwalk_dl_mio0);
    __romseg_course_banshee_boardwalk_dl_mio0_end = __romPos + SIZEOF(.course_banshee_boardwalk_dl_mio0);
    __romPos += SIZEOF(.course_banshee_boardwalk_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_yoshi_valley_dl_mio0SegmentStart = ADDR(.course_yoshi_valley_dl_mio0);
    __romseg_course_yoshi_valley_dl_mio0_start = __romPos;
    .course_yoshi_valley_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/yoshi_valley/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_yoshi_valley_dl_mio0SegmentEnd = ADDR(.course_yoshi_valley_dl_mio0) + SIZEOF(.course_yoshi_valley_dl_mio0);
    _course_yoshi_valley_dl_mio0SegmentSize = SIZEOF(.course_yoshi_valley_dl_mio0);
    __romseg_course_yoshi_valley_dl_mio0_end = __romPos + SIZEOF(.course_yoshi_valley_dl_mio0);
    __romPos += SIZEOF(.course_yoshi_valley_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_frappe_snowland_dl_mio0SegmentStart = ADDR(.course_frappe_snowland_dl_mio0);
    __romseg_course_frappe_snowland_dl_mio0_start = __romPos;
    .course_frappe_snowland_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/frappe_snowland/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_frappe_snowland_dl_mio0SegmentEnd = ADDR(.course_frappe_snowland_dl_mio0) + SIZEOF(.course_frappe_snowland_dl_mio0);
    _course_frappe_snowland_dl_mio0SegmentSize = SIZEOF(.course_frappe_snowland_dl_mio0);
    __romseg_course_frappe_snowland_dl_mio0_end = __romPos + SIZEOF(.course_frappe_snowland_dl_mio0);
    __romPos += SIZEOF(.course_frappe_snowland_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_koopa_troopa_beach_dl_mio0SegmentStart = ADDR(.course_koopa_troopa_beach_dl_mio0);
    __romseg_course_koopa_troopa_beach_dl_mio0_start = __romPos;
    .course_koopa_troopa_beach_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/koopa_troopa_beach/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_koopa_troopa_beach_dl_mio0SegmentEnd = ADDR(.course_koopa_troopa_beach_dl_mio0) + SIZEOF(.course_koopa_troopa_beach_dl_mio0);
    _course_koopa_troopa_beach_dl_mio0SegmentSize = SIZEOF(.course_koopa_troopa_beach_dl_mio0);
    __romseg_course_koopa_troopa_beach_dl_mio0_end = __romPos + SIZEOF(.course_koopa_troopa_beach_dl_mio0);
    __romPos += SIZEOF(.course_koopa_troopa_beach_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_royal_raceway_dl_mio0SegmentStart = ADDR(.course_royal_raceway_dl_mio0);
    __romseg_course_royal_raceway_dl_mio0_start = __romPos;
    .course_royal_raceway_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/royal_raceway/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_royal_raceway_dl_mio0SegmentEnd = ADDR(.course_royal_raceway_dl_mio0) + SIZEOF(.course_royal_raceway_dl_mio0);
    _course_royal_raceway_dl_mio0SegmentSize = SIZEOF(.course_royal_raceway_dl_mio0);
    __romseg_course_royal_raceway_dl_mio0_end = __romPos + SIZEOF(.course_royal_raceway_dl_mio0);
    __romPos += SIZEOF(.course_royal_raceway_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_luigi_raceway_dl_mio0SegmentStart = ADDR(.course_luigi_raceway_dl_mio0);
    __romseg_course_luigi_raceway_dl_mio0_start = __romPos;
    .course_luigi_raceway_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/luigi_raceway/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_luigi_raceway_dl_mio0SegmentEnd = ADDR(.course_luigi_raceway_dl_mio0) + SIZEOF(.course_luigi_raceway_dl_mio0);
    _course_luigi_raceway_dl_mio0SegmentSize = SIZEOF(.course_luigi_raceway_dl_mio0);
    __romseg_course_luigi_raceway_dl_mio0_end = __romPos + SIZEOF(.course_luigi_raceway_dl_mio0);
    __romPos += SIZEOF(.course_luigi_raceway_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_moo_moo_farm_dl_mio0SegmentStart = ADDR(.course_moo_moo_farm_dl_mio0);
    __romseg_course_moo_moo_farm_dl_mio0_start = __romPos;
    .course_moo_moo_farm_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/moo_moo_farm/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_moo_moo_farm_dl_mio0SegmentEnd = ADDR(.course_moo_moo_farm_dl_mio0) + SIZEOF(.course_moo_moo_farm_dl_mio0);
    _course_moo_moo_farm_dl_mio0SegmentSize = SIZEOF(.course_moo_moo_farm_dl_mio0);
    __romseg_course_moo_moo_farm_dl_mio0_end = __romPos + SIZEOF(.course_moo_moo_farm_dl_mio0);
    __romPos += SIZEOF(.course_moo_moo_farm_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_toads_turnpike_dl_mio0SegmentStart = ADDR(.course_toads_turnpike_dl_mio0);
    __romseg_course_toads_turnpike_dl_mio0_start = __romPos;
    .course_toads_turnpike_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/toads_turnpike/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_toads_turnpike_dl_mio0SegmentEnd = ADDR(.course_toads_turnpike_dl_mio0) + SIZEOF(.course_toads_turnpike_dl_mio0);
    _course_toads_turnpike_dl_mio0SegmentSize = SIZEOF(.course_toads_turnpike_dl_mio0);
    __romseg_course_toads_turnpike_dl_mio0_end = __romPos + SIZEOF(.course_toads_turnpike_dl_mio0);
    __romPos += SIZEOF(.course_toads_turnpike_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_kalimari_desert_dl_mio0SegmentStart = ADDR(.course_kalimari_desert_dl_mio0);
    __romseg_course_kalimari_desert_dl_mio0_start = __romPos;
    .course_kalimari_desert_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/kalimari_desert/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_kalimari_desert_dl_mio0SegmentEnd = ADDR(.course_kalimari_desert_dl_mio0) + SIZEOF(.course_kalimari_desert_dl_mio0);
    _course_kalimari_desert_dl_mio0SegmentSize = SIZEOF(.course_kalimari_desert_dl_mio0);
    __romseg_course_kalimari_desert_dl_mio0_end = __romPos + SIZEOF(.course_kalimari_desert_dl_mio0);
    __romPos += SIZEOF(.course_kalimari_desert_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_sherbet_land_dl_mio0SegmentStart = ADDR(.course_sherbet_land_dl_mio0);
    __romseg_course_sherbet_land_dl_mio0_start = __romPos;
    .course_sherbet_land_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/sherbet_land/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_sherbet_land_dl_mio0SegmentEnd = ADDR(.course_sherbet_land_dl_mio0) + SIZEOF(.course_sherbet_land_dl_mio0);
    _course_sherbet_land_dl_mio0SegmentSize = SIZEOF(.course_sherbet_land_dl_mio0);
    __romseg_course_sherbet_land_dl_mio0_end = __romPos + SIZEOF(.course_sherbet_land_dl_mio0);
    __romPos += SIZEOF(.course_sherbet_land_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_rainbow_road_dl_mio0SegmentStart = ADDR(.course_rainbow_road_dl_mio0);
    __romseg_course_rainbow_road_dl_mio0_start = __romPos;
    .course_rainbow_road_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/rainbow_road/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_rainbow_road_dl_mio0SegmentEnd = ADDR(.course_rainbow_road_dl_mio0) + SIZEOF(.course_rainbow_road_dl_mio0);
    _course_rainbow_road_dl_mio0SegmentSize = SIZEOF(.course_rainbow_road_dl_mio0);
    __romseg_course_rainbow_road_dl_mio0_end = __romPos + SIZEOF(.course_rainbow_road_dl_mio0);
    __romPos += SIZEOF(.course_rainbow_road_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_wario_stadium_dl_mio0SegmentStart = ADDR(.course_wario_stadium_dl_mio0);
    __romseg_course_wario_stadium_dl_mio0_start = __romPos;
    .course_wario_stadium_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/wario_stadium/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_wario_stadium_dl_mio0SegmentEnd = ADDR(.course_wario_stadium_dl_mio0) + SIZEOF(.course_wario_stadium_dl_mio0);
    _course_wario_stadium_dl_mio0SegmentSize = SIZEOF(.course_wario_stadium_dl_mio0);
    __romseg_course_wario_stadium_dl_mio0_end = __romPos + SIZEOF(.course_wario_stadium_dl_mio0);
    __romPos += SIZEOF(.course_wario_stadium_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_block_fort_dl_mio0SegmentStart = ADDR(.course_block_fort_dl_mio0);
    __romseg_course_block_fort_dl_mio0_start = __romPos;
    .course_block_fort_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/block_fort/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_block_fort_dl_mio0SegmentEnd = ADDR(.course_block_fort_dl_mio0) + SIZEOF(.course_block_fort_dl_mio0);
    _course_block_fort_dl_mio0SegmentSize = SIZEOF(.course_block_fort_dl_mio0);
    __romseg_course_block_fort_dl_mio0_end = __romPos + SIZEOF(.course_block_fort_dl_mio0);
    __romPos += SIZEOF(.course_block_fort_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_skyscraper_dl_mio0SegmentStart = ADDR(.course_skyscraper_dl_mio0);
    __romseg_course_skyscraper_dl_mio0_start = __romPos;
    .course_skyscraper_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/skyscraper/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_skyscraper_dl_mio0SegmentEnd = ADDR(.course_skyscraper_dl_mio0) + SIZEOF(.course_skyscraper_dl_mio0);
    _course_skyscraper_dl_mio0SegmentSize = SIZEOF(.course_skyscraper_dl_mio0);
    __romseg_course_skyscraper_dl_mio0_end = __romPos + SIZEOF(.course_skyscraper_dl_mio0);
    __romPos += SIZEOF(.course_skyscraper_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_double_deck_dl_mio0SegmentStart = ADDR(.course_double_deck_dl_mio0);
    __romseg_course_double_deck_dl_mio0_start = __romPos;
    .course_double_deck_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/double_deck/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_double_deck_dl_mio0SegmentEnd = ADDR(.course_double_deck_dl_mio0) + SIZEOF(.course_double_deck_dl_mio0);
    _course_double_deck_dl_mio0SegmentSize = SIZEOF(.course_double_deck_dl_mio0);
    __romseg_course_double_deck_dl_mio0_end = __romPos + SIZEOF(.course_double_deck_dl_mio0);
    __romPos += SIZEOF(.course_double_deck_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_dks_jungle_parkway_dl_mio0SegmentStart = ADDR(.course_dks_jungle_parkway_dl_mio0);
    __romseg_course_dks_jungle_parkway_dl_mio0_start = __romPos;
    .course_dks_jungle_parkway_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/dks_jungle_parkway/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_dks_jungle_parkway_dl_mio0SegmentEnd = ADDR(.course_dks_jungle_parkway_dl_mio0) + SIZEOF(.course_dks_jungle_parkway_dl_mio0);
    _course_dks_jungle_parkway_dl_mio0SegmentSize = SIZEOF(.course_dks_jungle_parkway_dl_mio0);
    __romseg_course_dks_jungle_parkway_dl_mio0_end = __romPos + SIZEOF(.course_dks_jungle_parkway_dl_mio0);
    __romPos += SIZEOF(.course_dks_jungle_parkway_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_big_donut_dl_mio0SegmentStart = ADDR(.course_big_donut_dl_mio0);
    __romseg_course_big_donut_dl_mio0_start = __romPos;
    .course_big_donut_dl_mio0 0x06000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/big_donut/datos_pista.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _course_big_donut_dl_mio0SegmentEnd = ADDR(.course_big_donut_dl_mio0) + SIZEOF(.course_big_donut_dl_mio0);
    _course_big_donut_dl_mio0SegmentSize = SIZEOF(.course_big_donut_dl_mio0);
    __romseg_course_big_donut_dl_mio0_end = __romPos + SIZEOF(.course_big_donut_dl_mio0);
    __romPos += SIZEOF(.course_big_donut_dl_mio0);
    __romPos = ALIGN(__romPos, 16);
    _course_mario_raceway_offsetsSegmentStart = ADDR(.course_mario_raceway_offsets);
    __romseg_course_mario_raceway_offsets_start = __romPos;
    .course_mario_raceway_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/mario_raceway/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_mario_raceway_offsetsSegmentEnd = ADDR(.course_mario_raceway_offsets) + SIZEOF(.course_mario_raceway_offsets);
    _course_mario_raceway_offsetsSegmentSize = SIZEOF(.course_mario_raceway_offsets);
    __romseg_course_mario_raceway_offsets_end = __romPos + SIZEOF(.course_mario_raceway_offsets);
    __romPos += SIZEOF(.course_mario_raceway_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_choco_mountain_offsetsSegmentStart = ADDR(.course_choco_mountain_offsets);
    __romseg_course_choco_mountain_offsets_start = __romPos;
    .course_choco_mountain_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/choco_mountain/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_choco_mountain_offsetsSegmentEnd = ADDR(.course_choco_mountain_offsets) + SIZEOF(.course_choco_mountain_offsets);
    _course_choco_mountain_offsetsSegmentSize = SIZEOF(.course_choco_mountain_offsets);
    __romseg_course_choco_mountain_offsets_end = __romPos + SIZEOF(.course_choco_mountain_offsets);
    __romPos += SIZEOF(.course_choco_mountain_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_bowsers_castle_offsetsSegmentStart = ADDR(.course_bowsers_castle_offsets);
    __romseg_course_bowsers_castle_offsets_start = __romPos;
    .course_bowsers_castle_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/bowsers_castle/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_bowsers_castle_offsetsSegmentEnd = ADDR(.course_bowsers_castle_offsets) + SIZEOF(.course_bowsers_castle_offsets);
    _course_bowsers_castle_offsetsSegmentSize = SIZEOF(.course_bowsers_castle_offsets);
    __romseg_course_bowsers_castle_offsets_end = __romPos + SIZEOF(.course_bowsers_castle_offsets);
    __romPos += SIZEOF(.course_bowsers_castle_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_banshee_boardwalk_offsetsSegmentStart = ADDR(.course_banshee_boardwalk_offsets);
    __romseg_course_banshee_boardwalk_offsets_start = __romPos;
    .course_banshee_boardwalk_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/banshee_boardwalk/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_banshee_boardwalk_offsetsSegmentEnd = ADDR(.course_banshee_boardwalk_offsets) + SIZEOF(.course_banshee_boardwalk_offsets);
    _course_banshee_boardwalk_offsetsSegmentSize = SIZEOF(.course_banshee_boardwalk_offsets);
    __romseg_course_banshee_boardwalk_offsets_end = __romPos + SIZEOF(.course_banshee_boardwalk_offsets);
    __romPos += SIZEOF(.course_banshee_boardwalk_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_yoshi_valley_offsetsSegmentStart = ADDR(.course_yoshi_valley_offsets);
    __romseg_course_yoshi_valley_offsets_start = __romPos;
    .course_yoshi_valley_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/yoshi_valley/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_yoshi_valley_offsetsSegmentEnd = ADDR(.course_yoshi_valley_offsets) + SIZEOF(.course_yoshi_valley_offsets);
    _course_yoshi_valley_offsetsSegmentSize = SIZEOF(.course_yoshi_valley_offsets);
    __romseg_course_yoshi_valley_offsets_end = __romPos + SIZEOF(.course_yoshi_valley_offsets);
    __romPos += SIZEOF(.course_yoshi_valley_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_frappe_snowland_offsetsSegmentStart = ADDR(.course_frappe_snowland_offsets);
    __romseg_course_frappe_snowland_offsets_start = __romPos;
    .course_frappe_snowland_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/frappe_snowland/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_frappe_snowland_offsetsSegmentEnd = ADDR(.course_frappe_snowland_offsets) + SIZEOF(.course_frappe_snowland_offsets);
    _course_frappe_snowland_offsetsSegmentSize = SIZEOF(.course_frappe_snowland_offsets);
    __romseg_course_frappe_snowland_offsets_end = __romPos + SIZEOF(.course_frappe_snowland_offsets);
    __romPos += SIZEOF(.course_frappe_snowland_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_koopa_troopa_beach_offsetsSegmentStart = ADDR(.course_koopa_troopa_beach_offsets);
    __romseg_course_koopa_troopa_beach_offsets_start = __romPos;
    .course_koopa_troopa_beach_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/koopa_troopa_beach/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_koopa_troopa_beach_offsetsSegmentEnd = ADDR(.course_koopa_troopa_beach_offsets) + SIZEOF(.course_koopa_troopa_beach_offsets);
    _course_koopa_troopa_beach_offsetsSegmentSize = SIZEOF(.course_koopa_troopa_beach_offsets);
    __romseg_course_koopa_troopa_beach_offsets_end = __romPos + SIZEOF(.course_koopa_troopa_beach_offsets);
    __romPos += SIZEOF(.course_koopa_troopa_beach_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_royal_raceway_offsetsSegmentStart = ADDR(.course_royal_raceway_offsets);
    __romseg_course_royal_raceway_offsets_start = __romPos;
    .course_royal_raceway_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/royal_raceway/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_royal_raceway_offsetsSegmentEnd = ADDR(.course_royal_raceway_offsets) + SIZEOF(.course_royal_raceway_offsets);
    _course_royal_raceway_offsetsSegmentSize = SIZEOF(.course_royal_raceway_offsets);
    __romseg_course_royal_raceway_offsets_end = __romPos + SIZEOF(.course_royal_raceway_offsets);
    __romPos += SIZEOF(.course_royal_raceway_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_luigi_raceway_offsetsSegmentStart = ADDR(.course_luigi_raceway_offsets);
    __romseg_course_luigi_raceway_offsets_start = __romPos;
    .course_luigi_raceway_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/luigi_raceway/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_luigi_raceway_offsetsSegmentEnd = ADDR(.course_luigi_raceway_offsets) + SIZEOF(.course_luigi_raceway_offsets);
    _course_luigi_raceway_offsetsSegmentSize = SIZEOF(.course_luigi_raceway_offsets);
    __romseg_course_luigi_raceway_offsets_end = __romPos + SIZEOF(.course_luigi_raceway_offsets);
    __romPos += SIZEOF(.course_luigi_raceway_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_moo_moo_farm_offsetsSegmentStart = ADDR(.course_moo_moo_farm_offsets);
    __romseg_course_moo_moo_farm_offsets_start = __romPos;
    .course_moo_moo_farm_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/moo_moo_farm/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_moo_moo_farm_offsetsSegmentEnd = ADDR(.course_moo_moo_farm_offsets) + SIZEOF(.course_moo_moo_farm_offsets);
    _course_moo_moo_farm_offsetsSegmentSize = SIZEOF(.course_moo_moo_farm_offsets);
    __romseg_course_moo_moo_farm_offsets_end = __romPos + SIZEOF(.course_moo_moo_farm_offsets);
    __romPos += SIZEOF(.course_moo_moo_farm_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_toads_turnpike_offsetsSegmentStart = ADDR(.course_toads_turnpike_offsets);
    __romseg_course_toads_turnpike_offsets_start = __romPos;
    .course_toads_turnpike_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/toads_turnpike/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_toads_turnpike_offsetsSegmentEnd = ADDR(.course_toads_turnpike_offsets) + SIZEOF(.course_toads_turnpike_offsets);
    _course_toads_turnpike_offsetsSegmentSize = SIZEOF(.course_toads_turnpike_offsets);
    __romseg_course_toads_turnpike_offsets_end = __romPos + SIZEOF(.course_toads_turnpike_offsets);
    __romPos += SIZEOF(.course_toads_turnpike_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_kalimari_desert_offsetsSegmentStart = ADDR(.course_kalimari_desert_offsets);
    __romseg_course_kalimari_desert_offsets_start = __romPos;
    .course_kalimari_desert_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/kalimari_desert/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_kalimari_desert_offsetsSegmentEnd = ADDR(.course_kalimari_desert_offsets) + SIZEOF(.course_kalimari_desert_offsets);
    _course_kalimari_desert_offsetsSegmentSize = SIZEOF(.course_kalimari_desert_offsets);
    __romseg_course_kalimari_desert_offsets_end = __romPos + SIZEOF(.course_kalimari_desert_offsets);
    __romPos += SIZEOF(.course_kalimari_desert_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_sherbet_land_offsetsSegmentStart = ADDR(.course_sherbet_land_offsets);
    __romseg_course_sherbet_land_offsets_start = __romPos;
    .course_sherbet_land_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/sherbet_land/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_sherbet_land_offsetsSegmentEnd = ADDR(.course_sherbet_land_offsets) + SIZEOF(.course_sherbet_land_offsets);
    _course_sherbet_land_offsetsSegmentSize = SIZEOF(.course_sherbet_land_offsets);
    __romseg_course_sherbet_land_offsets_end = __romPos + SIZEOF(.course_sherbet_land_offsets);
    __romPos += SIZEOF(.course_sherbet_land_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_rainbow_road_offsetsSegmentStart = ADDR(.course_rainbow_road_offsets);
    __romseg_course_rainbow_road_offsets_start = __romPos;
    .course_rainbow_road_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/rainbow_road/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_rainbow_road_offsetsSegmentEnd = ADDR(.course_rainbow_road_offsets) + SIZEOF(.course_rainbow_road_offsets);
    _course_rainbow_road_offsetsSegmentSize = SIZEOF(.course_rainbow_road_offsets);
    __romseg_course_rainbow_road_offsets_end = __romPos + SIZEOF(.course_rainbow_road_offsets);
    __romPos += SIZEOF(.course_rainbow_road_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_wario_stadium_offsetsSegmentStart = ADDR(.course_wario_stadium_offsets);
    __romseg_course_wario_stadium_offsets_start = __romPos;
    .course_wario_stadium_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/wario_stadium/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_wario_stadium_offsetsSegmentEnd = ADDR(.course_wario_stadium_offsets) + SIZEOF(.course_wario_stadium_offsets);
    _course_wario_stadium_offsetsSegmentSize = SIZEOF(.course_wario_stadium_offsets);
    __romseg_course_wario_stadium_offsets_end = __romPos + SIZEOF(.course_wario_stadium_offsets);
    __romPos += SIZEOF(.course_wario_stadium_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_block_fort_offsetsSegmentStart = ADDR(.course_block_fort_offsets);
    __romseg_course_block_fort_offsets_start = __romPos;
    .course_block_fort_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/block_fort/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_block_fort_offsetsSegmentEnd = ADDR(.course_block_fort_offsets) + SIZEOF(.course_block_fort_offsets);
    _course_block_fort_offsetsSegmentSize = SIZEOF(.course_block_fort_offsets);
    __romseg_course_block_fort_offsets_end = __romPos + SIZEOF(.course_block_fort_offsets);
    __romPos += SIZEOF(.course_block_fort_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_skyscraper_offsetsSegmentStart = ADDR(.course_skyscraper_offsets);
    __romseg_course_skyscraper_offsets_start = __romPos;
    .course_skyscraper_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/skyscraper/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_skyscraper_offsetsSegmentEnd = ADDR(.course_skyscraper_offsets) + SIZEOF(.course_skyscraper_offsets);
    _course_skyscraper_offsetsSegmentSize = SIZEOF(.course_skyscraper_offsets);
    __romseg_course_skyscraper_offsets_end = __romPos + SIZEOF(.course_skyscraper_offsets);
    __romPos += SIZEOF(.course_skyscraper_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_double_deck_offsetsSegmentStart = ADDR(.course_double_deck_offsets);
    __romseg_course_double_deck_offsets_start = __romPos;
    .course_double_deck_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/double_deck/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_double_deck_offsetsSegmentEnd = ADDR(.course_double_deck_offsets) + SIZEOF(.course_double_deck_offsets);
    _course_double_deck_offsetsSegmentSize = SIZEOF(.course_double_deck_offsets);
    __romseg_course_double_deck_offsets_end = __romPos + SIZEOF(.course_double_deck_offsets);
    __romPos += SIZEOF(.course_double_deck_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_dks_jungle_parkway_offsetsSegmentStart = ADDR(.course_dks_jungle_parkway_offsets);
    __romseg_course_dks_jungle_parkway_offsets_start = __romPos;
    .course_dks_jungle_parkway_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/dks_jungle_parkway/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_dks_jungle_parkway_offsetsSegmentEnd = ADDR(.course_dks_jungle_parkway_offsets) + SIZEOF(.course_dks_jungle_parkway_offsets);
    _course_dks_jungle_parkway_offsetsSegmentSize = SIZEOF(.course_dks_jungle_parkway_offsets);
    __romseg_course_dks_jungle_parkway_offsets_end = __romPos + SIZEOF(.course_dks_jungle_parkway_offsets);
    __romPos += SIZEOF(.course_dks_jungle_parkway_offsets);
    __romPos = ALIGN(__romPos, 16);
    _course_big_donut_offsetsSegmentStart = ADDR(.course_big_donut_offsets);
    __romseg_course_big_donut_offsets_start = __romPos;
    .course_big_donut_offsets 0x09000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/big_donut/desplazamientos.o(.data .data.* .rodata .rodata.* .bss .bss.* COMMON));
        . = ALIGN(0x10);
    }
    _course_big_donut_offsetsSegmentEnd = ADDR(.course_big_donut_offsets) + SIZEOF(.course_big_donut_offsets);
    _course_big_donut_offsetsSegmentSize = SIZEOF(.course_big_donut_offsets);
    __romseg_course_big_donut_offsets_end = __romPos + SIZEOF(.course_big_donut_offsets);
    __romPos += SIZEOF(.course_big_donut_offsets);
    __romPos = ALIGN(__romPos, 16);
    _mario_raceway_vertexSegmentStart = ADDR(.mario_raceway_vertex);
    __romseg_mario_raceway_vertex_start = __romPos;
    .mario_raceway_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/mario_raceway/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _mario_raceway_vertexSegmentEnd = ADDR(.mario_raceway_vertex) + SIZEOF(.mario_raceway_vertex);
    _mario_raceway_vertexSegmentSize = SIZEOF(.mario_raceway_vertex);
    __romseg_mario_raceway_vertex_end = __romPos + SIZEOF(.mario_raceway_vertex);
    __romPos += SIZEOF(.mario_raceway_vertex);
    __romPos = ALIGN(__romPos, 16);
    _choco_mountain_vertexSegmentStart = ADDR(.choco_mountain_vertex);
    __romseg_choco_mountain_vertex_start = __romPos;
    .choco_mountain_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/choco_mountain/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _choco_mountain_vertexSegmentEnd = ADDR(.choco_mountain_vertex) + SIZEOF(.choco_mountain_vertex);
    _choco_mountain_vertexSegmentSize = SIZEOF(.choco_mountain_vertex);
    __romseg_choco_mountain_vertex_end = __romPos + SIZEOF(.choco_mountain_vertex);
    __romPos += SIZEOF(.choco_mountain_vertex);
    __romPos = ALIGN(__romPos, 16);
    _bowsers_castle_vertexSegmentStart = ADDR(.bowsers_castle_vertex);
    __romseg_bowsers_castle_vertex_start = __romPos;
    .bowsers_castle_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/bowsers_castle/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _bowsers_castle_vertexSegmentEnd = ADDR(.bowsers_castle_vertex) + SIZEOF(.bowsers_castle_vertex);
    _bowsers_castle_vertexSegmentSize = SIZEOF(.bowsers_castle_vertex);
    __romseg_bowsers_castle_vertex_end = __romPos + SIZEOF(.bowsers_castle_vertex);
    __romPos += SIZEOF(.bowsers_castle_vertex);
    __romPos = ALIGN(__romPos, 16);
    _banshee_boardwalk_vertexSegmentStart = ADDR(.banshee_boardwalk_vertex);
    __romseg_banshee_boardwalk_vertex_start = __romPos;
    .banshee_boardwalk_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/banshee_boardwalk/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _banshee_boardwalk_vertexSegmentEnd = ADDR(.banshee_boardwalk_vertex) + SIZEOF(.banshee_boardwalk_vertex);
    _banshee_boardwalk_vertexSegmentSize = SIZEOF(.banshee_boardwalk_vertex);
    __romseg_banshee_boardwalk_vertex_end = __romPos + SIZEOF(.banshee_boardwalk_vertex);
    __romPos += SIZEOF(.banshee_boardwalk_vertex);
    __romPos = ALIGN(__romPos, 16);
    _yoshi_valley_vertexSegmentStart = ADDR(.yoshi_valley_vertex);
    __romseg_yoshi_valley_vertex_start = __romPos;
    .yoshi_valley_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/yoshi_valley/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _yoshi_valley_vertexSegmentEnd = ADDR(.yoshi_valley_vertex) + SIZEOF(.yoshi_valley_vertex);
    _yoshi_valley_vertexSegmentSize = SIZEOF(.yoshi_valley_vertex);
    __romseg_yoshi_valley_vertex_end = __romPos + SIZEOF(.yoshi_valley_vertex);
    __romPos += SIZEOF(.yoshi_valley_vertex);
    __romPos = ALIGN(__romPos, 16);
    _frappe_snowland_vertexSegmentStart = ADDR(.frappe_snowland_vertex);
    __romseg_frappe_snowland_vertex_start = __romPos;
    .frappe_snowland_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/frappe_snowland/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _frappe_snowland_vertexSegmentEnd = ADDR(.frappe_snowland_vertex) + SIZEOF(.frappe_snowland_vertex);
    _frappe_snowland_vertexSegmentSize = SIZEOF(.frappe_snowland_vertex);
    __romseg_frappe_snowland_vertex_end = __romPos + SIZEOF(.frappe_snowland_vertex);
    __romPos += SIZEOF(.frappe_snowland_vertex);
    __romPos = ALIGN(__romPos, 16);
    _koopa_troopa_beach_vertexSegmentStart = ADDR(.koopa_troopa_beach_vertex);
    __romseg_koopa_troopa_beach_vertex_start = __romPos;
    .koopa_troopa_beach_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/koopa_troopa_beach/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _koopa_troopa_beach_vertexSegmentEnd = ADDR(.koopa_troopa_beach_vertex) + SIZEOF(.koopa_troopa_beach_vertex);
    _koopa_troopa_beach_vertexSegmentSize = SIZEOF(.koopa_troopa_beach_vertex);
    __romseg_koopa_troopa_beach_vertex_end = __romPos + SIZEOF(.koopa_troopa_beach_vertex);
    __romPos += SIZEOF(.koopa_troopa_beach_vertex);
    __romPos = ALIGN(__romPos, 16);
    _royal_raceway_vertexSegmentStart = ADDR(.royal_raceway_vertex);
    __romseg_royal_raceway_vertex_start = __romPos;
    .royal_raceway_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/royal_raceway/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _royal_raceway_vertexSegmentEnd = ADDR(.royal_raceway_vertex) + SIZEOF(.royal_raceway_vertex);
    _royal_raceway_vertexSegmentSize = SIZEOF(.royal_raceway_vertex);
    __romseg_royal_raceway_vertex_end = __romPos + SIZEOF(.royal_raceway_vertex);
    __romPos += SIZEOF(.royal_raceway_vertex);
    __romPos = ALIGN(__romPos, 16);
    _luigi_raceway_vertexSegmentStart = ADDR(.luigi_raceway_vertex);
    __romseg_luigi_raceway_vertex_start = __romPos;
    .luigi_raceway_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/luigi_raceway/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _luigi_raceway_vertexSegmentEnd = ADDR(.luigi_raceway_vertex) + SIZEOF(.luigi_raceway_vertex);
    _luigi_raceway_vertexSegmentSize = SIZEOF(.luigi_raceway_vertex);
    __romseg_luigi_raceway_vertex_end = __romPos + SIZEOF(.luigi_raceway_vertex);
    __romPos += SIZEOF(.luigi_raceway_vertex);
    __romPos = ALIGN(__romPos, 16);
    _moo_moo_farm_vertexSegmentStart = ADDR(.moo_moo_farm_vertex);
    __romseg_moo_moo_farm_vertex_start = __romPos;
    .moo_moo_farm_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/moo_moo_farm/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _moo_moo_farm_vertexSegmentEnd = ADDR(.moo_moo_farm_vertex) + SIZEOF(.moo_moo_farm_vertex);
    _moo_moo_farm_vertexSegmentSize = SIZEOF(.moo_moo_farm_vertex);
    __romseg_moo_moo_farm_vertex_end = __romPos + SIZEOF(.moo_moo_farm_vertex);
    __romPos += SIZEOF(.moo_moo_farm_vertex);
    __romPos = ALIGN(__romPos, 16);
    _toads_turnpike_vertexSegmentStart = ADDR(.toads_turnpike_vertex);
    __romseg_toads_turnpike_vertex_start = __romPos;
    .toads_turnpike_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/toads_turnpike/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _toads_turnpike_vertexSegmentEnd = ADDR(.toads_turnpike_vertex) + SIZEOF(.toads_turnpike_vertex);
    _toads_turnpike_vertexSegmentSize = SIZEOF(.toads_turnpike_vertex);
    __romseg_toads_turnpike_vertex_end = __romPos + SIZEOF(.toads_turnpike_vertex);
    __romPos += SIZEOF(.toads_turnpike_vertex);
    __romPos = ALIGN(__romPos, 16);
    _kalimari_desert_vertexSegmentStart = ADDR(.kalimari_desert_vertex);
    __romseg_kalimari_desert_vertex_start = __romPos;
    .kalimari_desert_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/kalimari_desert/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _kalimari_desert_vertexSegmentEnd = ADDR(.kalimari_desert_vertex) + SIZEOF(.kalimari_desert_vertex);
    _kalimari_desert_vertexSegmentSize = SIZEOF(.kalimari_desert_vertex);
    __romseg_kalimari_desert_vertex_end = __romPos + SIZEOF(.kalimari_desert_vertex);
    __romPos += SIZEOF(.kalimari_desert_vertex);
    __romPos = ALIGN(__romPos, 16);
    _sherbet_land_vertexSegmentStart = ADDR(.sherbet_land_vertex);
    __romseg_sherbet_land_vertex_start = __romPos;
    .sherbet_land_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/sherbet_land/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _sherbet_land_vertexSegmentEnd = ADDR(.sherbet_land_vertex) + SIZEOF(.sherbet_land_vertex);
    _sherbet_land_vertexSegmentSize = SIZEOF(.sherbet_land_vertex);
    __romseg_sherbet_land_vertex_end = __romPos + SIZEOF(.sherbet_land_vertex);
    __romPos += SIZEOF(.sherbet_land_vertex);
    __romPos = ALIGN(__romPos, 16);
    _rainbow_road_vertexSegmentStart = ADDR(.rainbow_road_vertex);
    __romseg_rainbow_road_vertex_start = __romPos;
    .rainbow_road_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/rainbow_road/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _rainbow_road_vertexSegmentEnd = ADDR(.rainbow_road_vertex) + SIZEOF(.rainbow_road_vertex);
    _rainbow_road_vertexSegmentSize = SIZEOF(.rainbow_road_vertex);
    __romseg_rainbow_road_vertex_end = __romPos + SIZEOF(.rainbow_road_vertex);
    __romPos += SIZEOF(.rainbow_road_vertex);
    __romPos = ALIGN(__romPos, 16);
    _wario_stadium_vertexSegmentStart = ADDR(.wario_stadium_vertex);
    __romseg_wario_stadium_vertex_start = __romPos;
    .wario_stadium_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/wario_stadium/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _wario_stadium_vertexSegmentEnd = ADDR(.wario_stadium_vertex) + SIZEOF(.wario_stadium_vertex);
    _wario_stadium_vertexSegmentSize = SIZEOF(.wario_stadium_vertex);
    __romseg_wario_stadium_vertex_end = __romPos + SIZEOF(.wario_stadium_vertex);
    __romPos += SIZEOF(.wario_stadium_vertex);
    __romPos = ALIGN(__romPos, 16);
    _block_fort_vertexSegmentStart = ADDR(.block_fort_vertex);
    __romseg_block_fort_vertex_start = __romPos;
    .block_fort_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/block_fort/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _block_fort_vertexSegmentEnd = ADDR(.block_fort_vertex) + SIZEOF(.block_fort_vertex);
    _block_fort_vertexSegmentSize = SIZEOF(.block_fort_vertex);
    __romseg_block_fort_vertex_end = __romPos + SIZEOF(.block_fort_vertex);
    __romPos += SIZEOF(.block_fort_vertex);
    __romPos = ALIGN(__romPos, 16);
    _skyscraper_vertexSegmentStart = ADDR(.skyscraper_vertex);
    __romseg_skyscraper_vertex_start = __romPos;
    .skyscraper_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/skyscraper/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _skyscraper_vertexSegmentEnd = ADDR(.skyscraper_vertex) + SIZEOF(.skyscraper_vertex);
    _skyscraper_vertexSegmentSize = SIZEOF(.skyscraper_vertex);
    __romseg_skyscraper_vertex_end = __romPos + SIZEOF(.skyscraper_vertex);
    __romPos += SIZEOF(.skyscraper_vertex);
    __romPos = ALIGN(__romPos, 16);
    _double_deck_vertexSegmentStart = ADDR(.double_deck_vertex);
    __romseg_double_deck_vertex_start = __romPos;
    .double_deck_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/double_deck/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _double_deck_vertexSegmentEnd = ADDR(.double_deck_vertex) + SIZEOF(.double_deck_vertex);
    _double_deck_vertexSegmentSize = SIZEOF(.double_deck_vertex);
    __romseg_double_deck_vertex_end = __romPos + SIZEOF(.double_deck_vertex);
    __romPos += SIZEOF(.double_deck_vertex);
    __romPos = ALIGN(__romPos, 16);
    _dks_jungle_parkway_vertexSegmentStart = ADDR(.dks_jungle_parkway_vertex);
    __romseg_dks_jungle_parkway_vertex_start = __romPos;
    .dks_jungle_parkway_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/dks_jungle_parkway/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _dks_jungle_parkway_vertexSegmentEnd = ADDR(.dks_jungle_parkway_vertex) + SIZEOF(.dks_jungle_parkway_vertex);
    _dks_jungle_parkway_vertexSegmentSize = SIZEOF(.dks_jungle_parkway_vertex);
    __romseg_dks_jungle_parkway_vertex_end = __romPos + SIZEOF(.dks_jungle_parkway_vertex);
    __romPos += SIZEOF(.dks_jungle_parkway_vertex);
    __romPos = ALIGN(__romPos, 16);
    _big_donut_vertexSegmentStart = ADDR(.big_donut_vertex);
    __romseg_big_donut_vertex_start = __romPos;
    .big_donut_vertex 0x0F000000 : AT(__romPos)
    {
        KEEP(build/ps2/recursos/pistas/big_donut/geografia.mio0.o(.data));
        . = ALIGN(0x10);
    }
    _big_donut_vertexSegmentEnd = ADDR(.big_donut_vertex) + SIZEOF(.big_donut_vertex);
    _big_donut_vertexSegmentSize = SIZEOF(.big_donut_vertex);
    __romseg_big_donut_vertex_end = __romPos + SIZEOF(.big_donut_vertex);
    __romPos += SIZEOF(.big_donut_vertex);
    __romPos = ALIGN(__romPos, 16);
    __rom_size = __romPos;
    /DISCARD/ : { *(*) }
}
