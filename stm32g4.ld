MEMORY
{
    flash (rx) : ORIGIN =0x08000000, LENGTH = 32K
    ram (rwx) : ORIGIN = 0x20000000,LENGTH = 64K
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
    .heap (NOLOAD) : ALIGN(8)
    {
        _heap_start = .;
        . = . + 0x200;  
        _heap_end = .;
    } > ram

    .stack (NOLOAD) : ALIGN(8)
    {
        _stack_start = .;
        . = . + 0x1200;  
        _stack_end = .;
    } > ram

    _stack = _stack_end;
}



