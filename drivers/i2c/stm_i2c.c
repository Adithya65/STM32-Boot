#include <stdint.h>
#include <errno.h>
#include "stm_reg_access.h"
#include "stm_i2c.h"

#define TIMEOUT 1000

void i2c_init(void)
{
    uint32_t reg_val;
 
    reg_val = REG_RD(RCC_BASE_ADDR + RCC_APB1ENR1_OFFSET);
    reg_val |= (1 << 21);   
    REG_WR(RCC_BASE_ADDR + RCC_APB1ENR1_OFFSET, reg_val);

    reg_val = REG_RD(RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET);
    reg_val |= (1 << 1);    
    REG_WR(RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET, reg_val);

    reg_val = REG_RD(GPIOB_BASE_ADDR + GPIO_MODER_OFFSET);
    reg_val &= ~((3 << 16) | (3 << 18));
    reg_val |=  (2 << 16) | (2 << 18);   
    REG_WR(GPIOB_BASE_ADDR + GPIO_MODER_OFFSET, reg_val);

    reg_val = REG_RD(GPIOB_BASE_ADDR + GPIO_OTYPER_OFFSET);
    reg_val |= (1 << 8) | (1 << 9);  
    REG_WR(GPIOB_BASE_ADDR + GPIO_OTYPER_OFFSET, reg_val);

    reg_val = REG_RD(GPIOB_BASE_ADDR + GPIO_PUPDR_OFFSET);
    reg_val &= ~((3 << 16) | (3 << 18));
    reg_val |=  ((1 << 16) | (1 << 18));   
    REG_WR(GPIOB_BASE_ADDR + GPIO_PUPDR_OFFSET, reg_val);

    reg_val = REG_RD(GPIOB_BASE_ADDR + GPIO_AFRH_OFFSET);
    reg_val &= ~((0xF << 0) | (0xF << 4));
    reg_val |= (0x4 << 0) | (0x4 << 4);   
    REG_WR(GPIOB_BASE_ADDR + GPIO_AFRH_OFFSET, reg_val);

    REG_WR(I2C1_BASE_ADDR + I2C_TIMINGR_OFFSET, 0x00303D5B);

    REG_WR(I2C1_BASE_ADDR + I2C_CR1_OFFSET, 1);
}

int i2c_write_byte(uint8_t addr, uint8_t data)
{
    uint32_t reg_val, timeout;

    reg_val = (addr << 1) | (1 << 16) | (1 << 13); 
    REG_WR(I2C1_BASE_ADDR + I2C_CR2_OFFSET, reg_val);

    timeout = TIMEOUT;
    while (!(REG_RD(I2C1_BASE_ADDR + I2C_ISR_OFFSET) & (1 << 0)))
    {
        if (--timeout == 0) 
            return -1;
    }

    REG_WR(I2C1_BASE_ADDR + I2C_TXDR_OFFSET, data);

    timeout = TIMEOUT;
    while (!(REG_RD(I2C1_BASE_ADDR + I2C_ISR_OFFSET) & (1 << 6)))
    {
        if (--timeout == 0)
             return -2;
    }
 
    REG_WR(I2C1_BASE_ADDR + I2C_CR2_OFFSET, (1 << 14));
 
    timeout = TIMEOUT;
    while (!(REG_RD(I2C1_BASE_ADDR + I2C_ISR_OFFSET) & (1 << 5)))
    {
        if (--timeout == 0) 
            return -3;
    }
    REG_WR(I2C1_BASE_ADDR + I2C_ICR_OFFSET, (1 << 5));

    return 0;
}
