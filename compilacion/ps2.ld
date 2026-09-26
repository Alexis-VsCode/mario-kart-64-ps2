ENTRY(__start);

PHDRS {
  text PT_LOAD;
  rom PT_LOAD;
}

SECTIONS {
	.text 0x00100000: {
		_ftext = . ;
		*(.text)
		*(.text.*)
		*(.gnu.linkonce.t*)
		KEEP(*(.init))
		KEEP(*(.fini))
		QUAD(0)
	} :text

	PROVIDE(_etext = .);
	PROVIDE(etext = .);

	.ctors ALIGN(16): {
		KEEP(*crtbegin*.o(.ctors))
		KEEP(*(EXCLUDE_FILE(*crtend*.o) .ctors))
		KEEP(*(SORT(.ctors.*)))
		KEEP(*(.ctors))
	}
	.dtors ALIGN(16): {
		KEEP(*crtbegin*.o(.dtors))
		KEEP(*(EXCLUDE_FILE(*crtend*.o) .dtors))
		KEEP(*(SORT(.dtors.*)))
		KEEP(*(.dtors))
	}

	.reginfo : { *(.reginfo) }

	/* Datos del segmento "racing" y "ending" */
	.racing_data ALIGN(128): {
		_inicio_datos_carreras = . ;
		*codigo/carrera/logica_carrera.o(.data .data.*)
		*codigo/graficos/dibujar_pistas.o(.data .data.*)
		*codigo/carrera/actores.o(.data .data.*)
		*codigo/graficos/cielo_y_pantalla_dividida.o(.data .data.*)
		*codigo/memoria/memoria_carrera.o(.data .data.*)
		*codigo/carrera/colision.o(.data .data.*)
		*codigo/carrera/actores_extendidos.o(.data .data.*)
		*codigo/sistema/matematicas.o(.data .data.*)
		*codigo/carrera/ia/caminos_vehiculos.o(.data .data.*)
		*codigo/datos/tabla_pistas.o(.data .data.*)
		. = ALIGN(16);
		_fin_datos_carreras = . ;
	}
	.ending_data ALIGN(128): {
		_inicio_datos_final = . ;
		*codigo/ceremonia/bucle_creditos.o(.data .data.*)
		*codigo/ceremonia/actores_podio.o(.data .data.*)
		*codigo/ceremonia/camara_ceremonia.o(.data .data.*)
		*codigo/ceremonia/carga_ceremonia.o(.data .data.*)
		*codigo/ceremonia/dibujar_podio.o(.data .data.*)
		*codigo/ceremonia/ceremonia_y_creditos.o(.data .data.*)
		*codigo/ceremonia/inicio_rdp_ceremonia.o(.data .data.*)
		*codigo/ceremonia/creditos.o(.data .data.*)
		. = ALIGN(16);
		_fin_datos_final = . ;
	}

	/* Tablas trigonometricas */
	.trig_tables ALIGN(128): {
		_trigTablesSegmentStart = . ;
		_trigTablesSegmentRomStart = . ;
		*codigo/memoria/tablas_trigonometricas.o(.data .data.*)
		. = ALIGN(16);
		_trigTablesSegmentEnd = . ;
		_trigTablesSegmentRomEnd = . ;
	}
	_trigTablesSegmentSize = SIZEOF(.trig_tables);

	.data ALIGN(128): {
		_fdata = . ;
		*(.data)
		*(.data.*)
		*(.gnu.linkonce.d*)
		SORT(CONSTRUCTORS)
	}

	.rodata ALIGN(128): {
		*(.rodata)
		*(.rodata.*)
		*(.gnu.linkonce.r*)
	}

	.rdata ALIGN(128): { *(.rdata) }
	.gcc_except_table ALIGN(128): { *(.gcc_except_table) }

	_gp = ALIGN(128) + 0x7ff0;
	.lit4 ALIGN(128): { *(.lit4) }
	.lit8 ALIGN(128): { *(.lit8) }

	.sdata ALIGN(128): {
		*(.sdata)
		*(.sdata.*)
		*(.gnu.linkonce.s*)
	}

	_edata = .;
	PROVIDE(edata = .);

	.sbss ALIGN(128) : {
		_fbss = . ;
		*(.sbss)
		*(.sbss.*)
		*(.gnu.linkonce.sb*)
		*(.scommon)
	}

	.racing_bss ALIGN(128) (NOLOAD) : {
		_inicio_bss_carreras = . ;
		*codigo/carrera/logica_carrera.o(.bss .bss.* COMMON)
		*codigo/graficos/dibujar_pistas.o(.bss .bss.* COMMON)
		*codigo/carrera/actores.o(.bss .bss.* COMMON)
		*codigo/graficos/cielo_y_pantalla_dividida.o(.bss .bss.* COMMON)
		*codigo/memoria/memoria_carrera.o(.bss .bss.* COMMON)
		*codigo/carrera/colision.o(.bss .bss.* COMMON)
		*codigo/carrera/actores_extendidos.o(.bss .bss.* COMMON)
		*codigo/sistema/matematicas.o(.bss .bss.* COMMON)
		*codigo/carrera/ia/caminos_vehiculos.o(.bss .bss.* COMMON)
		*codigo/memoria/aleatorio.o(.bss .bss.* COMMON)
		. = ALIGN(16);
		_fin_bss_carreras = . ;
	}
	.ending_bss ALIGN(128) (NOLOAD) : {
		_inicio_bss_final = . ;
		*codigo/ceremonia/bucle_creditos.o(.bss .bss.* COMMON)
		*codigo/ceremonia/actores_podio.o(.bss .bss.* COMMON)
		*codigo/ceremonia/camara_ceremonia.o(.bss .bss.* COMMON)
		*codigo/ceremonia/carga_ceremonia.o(.bss .bss.* COMMON)
		*codigo/ceremonia/dibujar_podio.o(.bss .bss.* COMMON)
		*codigo/ceremonia/ceremonia_y_creditos.o(.bss .bss.* COMMON)
		*codigo/ceremonia/inicio_rdp_ceremonia.o(.bss .bss.* COMMON)
		*codigo/ceremonia/creditos.o(.bss .bss.* COMMON)
		. = ALIGN(16);
		_fin_bss_final = . ;
	}

	/* El heap del juego, con la misma forma que en N64 */
	.memory_pool ALIGN(128) (NOLOAD) : {
		_memoryPoolSegmentNoloadStart = . ;
		KEEP(*codigo/memoria/pool_memoria.o(.bss .bss.* COMMON))
		. = ALIGN(16);
		_memoryPoolSegmentNoloadEnd = . ;
		_endingSegmentStart = . ;
		. += 0xDF00;
		_endingSegmentNoloadEnd = . ;
		_racingSegmentStart = . ;
		. += 0x2C470 + 0x8000;
		_racingSegmentNoloadEnd = . ;
	}
	_endingSegmentRomStart = _inicio_datos_final;
	_endingSegmentRomEnd = _inicio_datos_final;
	_racingSegmentRomStart = _inicio_datos_carreras;
	_racingSegmentRomEnd = _inicio_datos_carreras;

	.bss ALIGN(128) : {
		*(.bss)
		*(.bss.*)
		*(.gnu.linkonce.b*)
		*(COMMON)
	}
	_end_bss = .;

	/* crt0 pone a cero de _fbss a _end y arranca el heap en _end. */
	_end = . ;
	PROVIDE(end = .);
	_heap_size = 0x01000000 - _end;

	ASSERT(_end <= 0x00F00000, "codigo+datos+bss pasan de 15 MB: no caben por debajo de la ROM")

	/* La ROM */
	.rom 0x01000000 : {
		__rom_start = . ;
		KEEP(*(.rom_blob))
		. = ALIGN(16);
		__rom_head_end = . ;
		BYTE(0);
		. = ALIGN(16) + 0x10000;
	} :rom
	__rom_end = __rom_start + __rom_total_size;

	/* + 64 KB de relleno de SMK64ROM.BIN y otros 64 KB de margen. */
	ASSERT(__rom_end + 0x20000 <= 0x01F00000, "la ROM invade la zona de la pila")
	ASSERT(__rom_head_end <= __rom_end, "la cabecera de la ROM es mayor que la ROM")

	.spad 0x70000000: {
		*(.spad)
	}

	/* Microcodigo del RSP */
	rspF3DBootStart = 0; rspF3DBootEnd = 0;
	gspF3DEXTextStart = 0; gspF3DEXDataStart = 0;
	gspF3DLXTextStart = 0; gspF3DLXDataStart = 0;
	rspAspMainStart = 0;

	/* De undefined_syms.txt del proyecto original */
	dato_0B002A00 = 0x0B002A00;

	PROVIDE(_stack = -1);
	PROVIDE(_stack_size = 128 * 1024);

	/* Simbolos de los segmentos de la ROM */
	INCLUDE rom_syms.ld
}
