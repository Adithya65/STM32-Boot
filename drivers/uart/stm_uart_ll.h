#ifndef __STM32_UART_LL__
#define __STM32_UART_LL__

#include <stdint.h>
#include <errno.h>

/*REG BASE ADDR MACROS STARTS*/
#define GPIO_A_REG_BASE_ADDR            0x48000000
#define GPIO_C_REG_BASE_ADDR            0x48000800
#define RCC_BASE_ADDR                   0x40021000
#define USART1_BASE_ADDR                0x40013800
/*REG BASE ADDR MACROS ENDS*/

/*REG OFFSET MACROS OFFSET STARTS*/
#define GPIO_MODER_OFFSET               0x0
#define GPIO_AFRH_OFFSET                0x24
#define GPIO_AFRL_OFFSET                0x20
#define RCC_AHB2ENR_OFFSET              0x4C
#define RCC_APB2ENR_OFFSET              0x60
#define USART_CR1_OFFSET                0x0
#define USART_BRR_OFFSET                0xC
#define USART_RDR_OFFSET                0x24
#define USART_TDR_OFFSET                0x28
#define USART_ISR_OFFSET                0x1C
/*REG OFFSET MACROS OFFSET ENDS*/


void set_gpio_alt_func();
void set_rcc_configs();
void set_uart_configs();


#endif
