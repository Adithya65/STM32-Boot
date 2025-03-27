MEMORY
{
    flash (rx) : ORIGIN =0x08000000, LENGTH = 32K
    ram (rwx) : ORIGIN = 0x20000000,LENGTH = 6K
}

_eram = ORIGIN(ram) + LENGTH(ram);
_stack = _eram;

SECTIONS
{
    .text : ALIGN(4)
    {
        KEEP(*(.ivt))
        *(.text*)
        . = ALIGN(4);
        _etext = .;
    } > flash


    _idata = LOADADDR(.data);
    .data :ALIGN(4)
    {
        _data = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > ram AT > flash

    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;
    } > ram
}



