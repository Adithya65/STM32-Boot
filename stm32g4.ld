MEMORY
{
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 64K
    ram   (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

_estack = ORIGIN(ram) + LENGTH(ram); 

SECTIONS
{
    .ivt :
    {
        KEEP(*(.ivt))
    } > flash

    .text : ALIGN(4)
    {
        *(.text*)
        . = ALIGN(4);
        _etext = .;
    } > flash

    _idata = LOADADDR(.data);
    .data : ALIGN(4)
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
        _end = .;   /* Heap starts here */
    } > ram

    .heap (NOLOAD) : ALIGN(8)
    {
        _heap_start = .;
        . = . + 0x400;  /* 8 KB heap */
        _heap_end = .;
    } > ram

    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        . = . + 0x400;
        . = ALIGN(8);
    } > ram

    _stack = _estack;
}
