ENTRY(boot_start)

SECTIONS
{
    . = 0x1000;
    .text : {
        *(.text.entry*)
        *(.text .text.*)
    }
    .rodata : {
        *(.rodata .rodata.*)
    }
    .data : {
        *(.data .data.*)
    }
    .bss : {
        *(.bss .bss.*)
    }
    /DISCARD/ : {
        *(.eh_frame)
        *(.comment)
        *(.note.gnu*)
    }
}
