#include <stdint.h>
#include <errno.h>
#include "stm_uart.h"
#include "stm_uart_ll.h"


int32_t uart_init()
{
    set_gpio_alt_func();
    set_rcc_configs();

}


int32_t uart_write_sync()
{
}


int32_t uart_read_sync()
{
}





