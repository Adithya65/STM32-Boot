#include <stdint.h>
#include "stm_uart_ll.h"

/*TODO:
  * Add apis to set and modify configs[ Baudrate, Start-Stop bits ]
  * update read/write wrappers more functional
  */


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
    return write_data(ch);
}

uint32_t uart_read()
{
    return read_data();
}


