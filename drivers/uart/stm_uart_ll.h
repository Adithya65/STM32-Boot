#ifndef __STM32_UART_LL__
#define __STM32_UART_LL__

#include <stdint.h>
#include <errno.h>

/*REG BASE ADDR MACROS STARTS*/
#define GPIO_A_REG_BASE_ADDR            0x48000000
#define RCC_BASE_ADDR                   0x40021000
#define USART2_BASE_ADDR                0x40004400
#define EXTI_BASE_ADDR                  0x40010400 
#define SYSCFG_BASE_ADDR                0x40010000
/*REG BASE ADDR MACROS ENDS*/

/*REG OFFSET MACROS OFFSET STARTS*/
#define GPIO_MODER_OFFSET               0x0
#define GPIO_AFRH_OFFSET                0x24
#define GPIO_AFRL_OFFSET                0x20
#define RCC_AHB2ENR_OFFSET              0x4C
#define RCC_APB2ENR_OFFSET              0x60
#define RCC_APB1ENR_OFFSET              0x58
#define USART_CR1_OFFSET                0x0
#define USART_BRR_OFFSET                0xC
#define USART_RDR_OFFSET                0x24
#define USART_TDR_OFFSET                0x28
#define USART_ISR_OFFSET                0x1C
#define SYSCFG_EXTICR1_OFFSET           0x8
#define EXTI_IMR1_OFFSET                0x0
#define EXTI_RTSR1_OFFSET               0x8 

/*REG OFFSET MACROS OFFSET ENDS*/

#define NVIC_ISER1  0xE000E104
#define NVIC_IPR    0xE000E400
#define NVIC_IPR9   (NVIC_IPR + 0x4*9) 

void set_gpio_alt_func();
void set_rcc_configs();
void set_uart_configs();
void start_xfer();
int32_t write_data(uint8_t ch);
int32_t read_data();
void set_uart_isr();


#endif
