extern int main(void);
extern unsigned int _stack;
extern unsigned int _bss;
extern unsigned int _ebss;
extern unsigned int _data;
extern unsigned int _edata;
extern unsigned int _idata;

extern void vPortSVCHandler(void);
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);

#define IVT_ARRAY_SIZE (48U)
typedef void (*isr_t)(void);

void clear_bss()
{
    unsigned int *bss_start = &_bss;
    while(bss_start < & _ebss)
    {
        *bss_start =0;
        bss_start++;
    }
}

void copy_data()
{
    unsigned int *src_addr = &_idata;
    unsigned int *dest_addr = &_data;

    while(dest_addr < &_edata)
    {
        *dest_addr++ = *src_addr++;;
    }
}

void isr_reset(void) 
{
    clear_bss();
    copy_data();
    main();
    while(1);
}

void isr_hardfault(void) {
    while(1);
}


static const isr_t ivt[IVT_ARRAY_SIZE] __attribute__((used, section(".ivt"))) =
{
    (isr_t)&_stack,           // Initial Stack Pointer
    isr_reset,                // Reset Handler
    0,                        // NMI Handler (optional)
    isr_hardfault,           // HardFault Handler
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    vPortSVCHandler,         // SVC Handler (index 11)
    0,                        // DebugMon (optional)
    0,                        // Reserved
    xPortPendSVHandler,      // PendSV Handler (index 14)
    xPortSysTickHandler      // SysTick Handler (index 15) — only if you're using SysTick
};
