SECTIONS
{
    .data : {
        *(.data .data.* .rodata .rodata.* .sdata .sdata.* .bss .bss.* .sbss .sbss.* COMMON)
    }
    /DISCARD/ : { *(*) }
}
