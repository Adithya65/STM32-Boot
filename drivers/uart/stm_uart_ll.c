#include <stdint.h>
#include <errno.h>
#include "stm_reg_access.h"
#include "stm_uart_ll.h"

void set_rcc_configs()
{
    uint32_t volatile reg_val = 0;

    reg_val = REG_RD( RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET );
    reg_val |= 1;
    REG_WR( RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET , reg_val );

    reg_val = REG_RD( RCC_BASE_ADDR + RCC_APB1ENR_OFFSET );
    reg_val |= 1 << 17;
    REG_WR( RCC_BASE_ADDR + RCC_APB1ENR_OFFSET , reg_val );
}

void set_gpio_alt_func()
{
    uint32_t volatile reg_val = 0;

    reg_val = REG_RD( GPIO_A_REG_BASE_ADDR + GPIO_MODER_OFFSET );
    reg_val &= ~(( 3 << 4 ) | ( 3 << 6 ));
    reg_val |= ( 2 << 4 ) | ( 2 << 6 );
    REG_WR( GPIO_A_REG_BASE_ADDR + GPIO_MODER_OFFSET , reg_val );

    reg_val = REG_RD( GPIO_A_REG_BASE_ADDR + GPIO_AFRL_OFFSET );
    reg_val &= ~(( 0xF << 8 ) | ( 0xF << 12 ));
    reg_val |= ( 7 << 8 ) | ( 7 << 12 );
    REG_WR( GPIO_A_REG_BASE_ADDR + GPIO_AFRL_OFFSET , reg_val ); 

}

void set_uart_configs()
{
    uint32_t volatile reg_val = 0; ;
    reg_val = ( 1 << 3 ) | ( 1 << 2 );
    REG_WR( USART2_BASE_ADDR + USART_CR1_OFFSET , reg_val );
    REG_WR( USART2_BASE_ADDR + USART_BRR_OFFSET , 16000000 / 115200 );
    reg_val |= 1;
    REG_WR( USART2_BASE_ADDR + USART_CR1_OFFSET , reg_val );


}
void start_xfer()
{
    uint32_t volatile reg_val = 0; ;
    do 
    {
        reg_val = REG_RD( USART2_BASE_ADDR + USART_ISR_OFFSET );
        if ( reg_val & ( 1 << 5 ) )
        {
            uint8_t ch = REG_RD( USART2_BASE_ADDR + USART_RDR_OFFSET );
            do 
            {
                reg_val = REG_RD( USART2_BASE_ADDR + USART_ISR_OFFSET );
            }
            while (!( reg_val & (1 << 7)));
            REG_WR( USART2_BASE_ADDR + USART_TDR_OFFSET , ch );
        }
    }
    while(1);
}





