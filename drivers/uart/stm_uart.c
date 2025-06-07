#include <stdint.h>
#include "stm_uart_ll.h"

int uart_init()
{
    set_rcc_configs();
    set_uart_isr();
    set_gpio_alt_func();
    set_uart_configs();
    start_xfer();
    return 0;
}

int32_t uart_write()
{
    write_data();
    return 0;
}

int32_t uart_read()
{
    read_data();
    return 0;
}


