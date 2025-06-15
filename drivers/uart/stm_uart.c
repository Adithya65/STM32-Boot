#include <stdint.h>
#include "stm_uart_ll.h"

int uart_init()
{
    set_rcc_configs();
    set_uart_isr();
    set_gpio_alt_func();
    set_uart_configs();
   
    return 0;
}

int32_t uart_write(uint8_t ch)
{
    write_data(ch);
    return 0;
}

int32_t uart_read()
{
    read_data();
    return 0;
}


