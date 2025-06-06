#include <stdint.h>

#warning "this is a test version"

#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x48000000
#define USART2_BASE     0x40004400

#define RCC_AHB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x4C))
#define RCC_APB1ENR1    (*(volatile uint32_t *)(RCC_BASE + 0x58))

#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL      (*(volatile uint32_t *)(GPIOA_BASE + 0x20))

#define USART2_CR1      (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_BRR      (*(volatile uint32_t *)(USART2_BASE + 0x0C))
#define USART2_ISR      (*(volatile uint32_t *)(USART2_BASE + 0x1C))
#define USART2_RDR      (*(volatile uint32_t *)(USART2_BASE + 0x24))
#define USART2_TDR      (*(volatile uint32_t *)(USART2_BASE + 0x28))

int uart_loopback_test(void)
{
    RCC_AHB2ENR |= (1 << 0);       
    RCC_APB1ENR1 |= (1 << 17);    

    GPIOA_MODER &= ~(0xF << (2 * 2));   
    GPIOA_MODER |= (0xA << (2 * 2));    
    GPIOA_AFRL &= ~(0xFF << (4 * 2));   
    GPIOA_AFRL |= (0x77 << (4 * 2));    

    USART2_CR1 = 0;               
    USART2_BRR = 16000000 / 115200;  
    USART2_CR1 |= (1 << 3) | (1 << 2);  
    USART2_CR1 |= (1 << 0);       

    while (1) 
    {
        if (USART2_ISR & (1 << 5)) 
        { 
            uint8_t ch = USART2_RDR;
            while (!(USART2_ISR & (1 << 7)));
            USART2_TDR = ch;
        }
    }

    return 0;
}

