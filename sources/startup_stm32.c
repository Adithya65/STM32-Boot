#include <stdint.h>
#include "stm_uart.h"

#define ENABLE_DEBUG_REGS  0

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
extern void USART2_IRQHandler(void);

#define IVT_ARRAY_SIZE (60U)
typedef void (*isr_t)(void);

void clear_bss()
{
    unsigned int *bss_start = &_bss;
    while(bss_start < & _ebss)
    {
        *bss_start = 0;
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
    /*hardware inits*/
    uart_init();
    main();
    while(1);
}

void isr_hardfault(void)
{
    __asm volatile
    (
        "TST lr, #4\n"
        "ITE EQ\n"
        "MRSEQ r0, MSP\n"
        "MRSNE r0, PSP\n"
        "B hard_fault_handler_c\n"
    );
}

void hard_fault_handler_c(uint32_t *hardfault_args)
{
#if ENABLE_DEBUG_REGS
    volatile uint32_t stacked_r0  = hardfault_args[0];
    volatile uint32_t stacked_r1  = hardfault_args[1];
    volatile uint32_t stacked_r2  = hardfault_args[2];
    volatile uint32_t stacked_r3  = hardfault_args[3];
    volatile uint32_t stacked_r12 = hardfault_args[4];
    volatile uint32_t stacked_lr  = hardfault_args[5]; 
    volatile uint32_t stacked_pc  = hardfault_args[6]; 
    volatile uint32_t stacked_psr = hardfault_args[7];
#else
    (void)hardfault_args;
#endif
    while (1);
}


extern unsigned long _estack;
static const isr_t ivt[IVT_ARRAY_SIZE] __attribute__((used, section(".ivt"))) =
{
    [0]  = (isr_t)&_estack,
    [1]  = isr_reset,
    [3]  = isr_hardfault,
    [11] = vPortSVCHandler,
    [14] = xPortPendSVHandler,
    [15] = xPortSysTickHandler,
    [54] = USART2_IRQHandler,   
};
