#include <stdint.h>
#include <errno.h>
#include "stm_reg_access.h"
#include "stm_uart_ll.h"

void set_rcc_configs()
{
}

/*USART1_
 **TX mapped to port A9 with AF7
 **RX mapped to port A10 with AF7
 */
void set_gpio_alt_func()
{
    uint32_t reg_val = 0;

    reg_val = REG_RD(( uint32_t * )( GPIO_A_REG_BASE_ADDR + GPIO_MODER_OFFSET ));
    reg_val &= ~(( 3 << 18 ) | ( 3 << 20 ));
    reg_val |= ( 2 << 18 ) | ( 2 << 20 );
    REG_WR(( uint32_t* )( GPIO_A_REG_BASE_ADDR + GPIO_MODER_OFFSET ) , reg_val );

    reg_val = REG_RD(( uint32_t* )( GPIO_A_REG_BASE_ADDR + GPIO_AFRH_OFFSET ) );
    reg_val &= ~(( 7 << 4 ) | ( 7 << 8 ));
    REG_WR(( uint32_t* )( GPIO_A_REG_BASE_ADDR + GPIO_AFRH_OFFSET ) , reg_val ); 
}



