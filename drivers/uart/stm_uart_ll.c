#include <stdint.h>
#include <errno.h>
#include "stm_reg_access.h"
#include "stm_uart_ll.h"

#error "Deprecated layer at this commit"

void set_rcc_configs()
{
    uint32_t volatile reg_val = 0;

#if 1
    reg_val = REG_RD( RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET );
    reg_val |= 1;
    REG_WR( RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET , reg_val );

    reg_val = REG_RD( RCC_BASE_ADDR + RCC_APB2ENR_OFFSET );
    reg_val |= 1 << 14;
    REG_WR( RCC_BASE_ADDR + RCC_APB2ENR_OFFSET , reg_val );
#else 

    reg_val = REG_RD( RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET );
    reg_val |= 1 << 2;
    REG_WR( RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET , reg_val );

    reg_val = REG_RD( RCC_BASE_ADDR + RCC_APB2ENR_OFFSET );
    reg_val |= 1 << 14;
    REG_WR( RCC_BASE_ADDR + RCC_APB2ENR_OFFSET , reg_val );
#endif 
}

/*USART1
 **TX mapped to port A9 with AF7
 **RX mapped to port A10 with AF7
 */
void set_gpio_alt_func()
{
    uint32_t volatile reg_val = 0;

#if 1
    reg_val = REG_RD( GPIO_A_REG_BASE_ADDR + GPIO_MODER_OFFSET );
    reg_val &= ~(( 3 << 18 ) | ( 3 << 20 ));
    reg_val |= ( 2 << 18 ) | ( 2 << 20 );
    REG_WR( GPIO_A_REG_BASE_ADDR + GPIO_MODER_OFFSET , reg_val );

    reg_val = REG_RD( GPIO_A_REG_BASE_ADDR + GPIO_AFRH_OFFSET );
    reg_val &= ~(( 0xF << 4 ) | ( 0xF << 8 ));
    reg_val |= ( 7 << 4 ) | ( 7 << 8 );
    REG_WR( GPIO_A_REG_BASE_ADDR + GPIO_AFRH_OFFSET , reg_val ); 

    REG_WR( GPIO_A_REG_BASE_ADDR + 0x8   , (2 << 18)|(2 << 20) );
    REG_WR( GPIO_A_REG_BASE_ADDR + 0xC   , (1 << 18)|(1 << 20) );




#else
    reg_val = REG_RD( GPIO_C_REG_BASE_ADDR + GPIO_MODER_OFFSET );
    reg_val &= ~(( 3 << 8 ) | ( 3 << 10 ));
    reg_val |= ( 2 << 8 ) | ( 2 << 10 );
    REG_WR( GPIO_C_REG_BASE_ADDR + GPIO_MODER_OFFSET , reg_val );

    reg_val = REG_RD( GPIO_C_REG_BASE_ADDR + GPIO_AFRL_OFFSET );
    reg_val &= ~(( 0xF << 16 ) | ( 0xF << 20 ));
    reg_val |= ( 7 << 20 ) | ( 7 << 16 );
    REG_WR( GPIO_C_REG_BASE_ADDR + GPIO_AFRL_OFFSET , reg_val ); 

#endif
}
