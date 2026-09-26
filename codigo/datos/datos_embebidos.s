    .section .rodata
    .balign 16
    .globl irx_libsd
irx_libsd:
    .incbin "libsd.irx"
ps2_irx_libsd_fin:
    .balign 4
    .globl tamanio_irx_libsd
tamanio_irx_libsd:
    .word ps2_irx_libsd_fin - irx_libsd

    .balign 16
    .globl irx_audsrv
irx_audsrv:
    .incbin "audsrv.irx"
ps2_irx_audsrv_fin:
    .balign 4
    .globl tamanio_irx_audsrv
tamanio_irx_audsrv:
    .word ps2_irx_audsrv_fin - irx_audsrv

    .balign 16
    .globl rspAspMainDataStart
    .globl datos_microcodigo_audio
rspAspMainDataStart:
datos_microcodigo_audio:
    .incbin "recursos/sonido/tabla_microcodigo_audio.bin"
    .globl rspAspMainDataEnd
rspAspMainDataEnd:

    .balign 16
    .globl icono_partida
icono_partida:
    .incbin "icono_partida.ico"
guardar_fin_icono_ps2:
    .balign 4
    .globl tamanio_icono_partida
tamanio_icono_partida:
    .word guardar_fin_icono_ps2 - icono_partida
