#ifndef __STM32_UART_LL__
#define __STM32_UART_LL__

#include <stdint.h>
#include <errno.h>


/*REG BASE ADDR MACROS STARTS*/
#define GPIO_A_REG_BASE_ADDR            0x48000000

/*REG BASE ADDR MACROS ENDS*/

/*REG OFFSET MACROS OFFSET STARTS*/
#define GPIO_MODER_OFFSET               0x0
#define GPIO_AFRH_OFFSET                0x24

/*REG OFFSET MACROS OFFSET ENDS*/


void set_gpio_alt_func();
void set_rcc_configs();


#endif
