MEMORY
{
    flash (rx) : ORIGIN =0x08000000, LENGTH = 32K
    ram (rwx) : ORIGIN = 0x20000000,LENGTH = 16K
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
        /* Reserve heap space */
    .heap (NOLOAD) : ALIGN(8)
    {
        _heap_start = .;
        . = . + 0x0400;  /* Reserve 1280 bytes (adjust as needed) */
        _heap_end = .;
    } > ram

    /* Reserve stack space */
    .stack (NOLOAD) : ALIGN(8)
    {
        _stack_start = .;
        . = . + 0x0400;  /* Reserve 1280 bytes for stack (adjust as needed) */
        _stack_end = .;
    } > ram

    /* Optional: Reset _stack to top of stack */
    _stack = _stack_end;

}



