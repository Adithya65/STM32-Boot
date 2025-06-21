#include <stdint.h>
#include <errno.h>
#include "stm_reg_access.h"
#include "stm_uart_ll.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xSemaphoreTx;
SemaphoreHandle_t xSemaphoreRx;

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
    reg_val = ( 1 << 3 ) | ( 1 << 2 )|(1 << 5)|( 1<< 7 );
    REG_WR( USART2_BASE_ADDR + USART_CR1_OFFSET , reg_val );
    REG_WR( USART2_BASE_ADDR + USART_BRR_OFFSET , 16000000 / 115200 );
    reg_val |= 1;
    REG_WR( USART2_BASE_ADDR + USART_CR1_OFFSET , reg_val );
}

/*PA 2 -> EXTI2[3:0]
 *PA 3 -> EXTI3[3:0]
 */
void set_uart_isr()
{
    uint32_t volatile reg_val = 0;

    xSemaphoreTx = xSemaphoreCreateBinary();
    configASSERT(xSemaphoreTx != NULL);

    xSemaphoreRx = xSemaphoreCreateBinary();
    configASSERT(xSemaphoreRx != NULL);
    
    reg_val = REG_RD( RCC_BASE_ADDR + RCC_APB2ENR_OFFSET );
    reg_val |= 1;
    REG_WR( RCC_BASE_ADDR + RCC_APB2ENR_OFFSET , reg_val);

    reg_val = (1 << (38 - 32)); 
    REG_WR(NVIC_ISER1, reg_val);

    reg_val = REG_RD(NVIC_IPR9);
    reg_val &= ~(0xFF << 16);         
    reg_val |=  (0x20 << 16);         
    REG_WR(NVIC_IPR9, reg_val);
}

uint32_t get_reg_val()
{
    return REG_RD( USART2_BASE_ADDR + USART_ISR_OFFSET );
}

int32_t write_data(uint8_t ch )
{
    REG_WR( USART2_BASE_ADDR + USART_TDR_OFFSET , ch );
    REG_WR(USART2_BASE_ADDR + USART_CR1_OFFSET,
            REG_RD(USART2_BASE_ADDR + USART_CR1_OFFSET) |(1 << 7));

    if (xSemaphoreTake(xSemaphoreTx, portMAX_DELAY) == pdTRUE)
    {
         return 0;
    }
    return -1;
}

uint32_t read_data()
{
    uint8_t character_data;
    REG_WR(USART2_BASE_ADDR + USART_CR1_OFFSET,REG_RD(USART2_BASE_ADDR + USART_CR1_OFFSET) |(1 << 5));

    if (xSemaphoreTake(xSemaphoreRx, portMAX_DELAY) == pdTRUE)
    { 
        character_data = REG_RD( USART2_BASE_ADDR + USART_RDR_OFFSET );
        return character_data;
    }
    return 0;
}
 
void USART2_IRQHandler(void)
{
    uint32_t volatile reg_val = get_reg_val();
    
    if (reg_val & (1 << 5))  
    {
        REG_WR(USART2_BASE_ADDR + USART_CR1_OFFSET, REG_RD(USART2_BASE_ADDR + USART_CR1_OFFSET) & ~(1 << 5));
        xSemaphoreGiveFromISR(xSemaphoreRx,NULL);
    }
    if (reg_val & (1 << 6))   
    {
        REG_WR(USART2_BASE_ADDR + 0x20, (1 << 6));   
    }
    if (reg_val & (1 << 4))  
    {
        REG_WR(USART2_BASE_ADDR + 0x20, (1 << 4));  
    }
    if (reg_val & (1 << 3))  
        REG_WR(USART2_BASE_ADDR + 0x20, (1 << 3));   

    if (reg_val & (1 << 2))  
        REG_WR(USART2_BASE_ADDR + 0x20, (1 << 2));  

    if (reg_val & (1 << 1))   
        REG_WR(USART2_BASE_ADDR + 0x20, (1 << 1));   

    if (reg_val & (1 << 0))  
        REG_WR(USART2_BASE_ADDR + 0x20, (1 << 0));   
    
    if (reg_val & (1 << 7))
    {
        REG_WR(USART2_BASE_ADDR + USART_CR1_OFFSET, REG_RD(USART2_BASE_ADDR + USART_CR1_OFFSET) & ~(1 << 7));
        xSemaphoreGiveFromISR(xSemaphoreTx,NULL);
    }
}



