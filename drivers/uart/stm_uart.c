#include <stdint.h>
#include "stm_uart_ll.h"

int uart_init()
{
    set_rcc_configs();
    set_gpio_alt_func();
    set_uart_configs();
    start_xfer();
    return 0;
}

