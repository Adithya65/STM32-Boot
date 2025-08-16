#include <stdint.h>
#include <errno.h>
#include "stm_reg_access.h"
#include "stm_i2c.h"

int32_t i2c_init()
{
    uint32_t volatile reg_val;

    reg_val = REG_RD(RCC_BASE_ADDR + RCC_APB1ENR1_OFFSET);
    reg_val |= ( 1 << 21 );
    REG_WR(RCC_BASE_ADDR + RCC_APB1ENR1_OFFSET,reg_val);

    reg_val = REG_RD(RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET);
    reg_val |= ( 1 << 1 );
    REG_WR(RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET,reg_val);

    reg_val = REG_RD(GPIOB_BASE_ADDR + GPIO_MODER_OFFSET);
    reg_val &= ~((3 << 16) | (3 << 18));
    reg_val |= (2 << 16) | (2 << 18);
    REG_WR(GPIOB_BASE_ADDR + GPIO_MODER_OFFSET,reg_val);

    reg_val = REG_RD(GPIOB_BASE_ADDR + GPIO_OTYPER_OFFSET);
    reg_val &= ~((3 << 16) | (3 << 18));
    reg_val |= (1 << 16) | (1 << 18);
    REG_WR(GPIOB_BASE_ADDR + GPIO_OTYPER_OFFSET,reg_val);

    reg_val = REG_RD(GPIOB_BASE_ADDR + GPIO_PUPDR_OFFSET);
    reg_val &= ~((3 << 16) | (3 << 18));
    reg_val |= (1 << 16) | (1 << 18);
    REG_WR(GPIOB_BASE_ADDR + GPIO_PUPDR_OFFSET,reg_val);

    reg_val = REG_RD(GPIOB_BASE_ADDR + GPIO_AFRH_OFFSET);
    reg_val &= ~((0xF << 0)|(0xF << 4)); 
    reg_val |= (0x4 << 0)|(0x4 << 4);
    REG_WR(GPIOB_BASE_ADDR + GPIO_AFRH_OFFSET,reg_val);

    reg_val = REG_RD(I2C1_BASE_ADDR + I2C_TIMINGR_OFFSET);
    reg_val = 0x00303D5B;
    REG_WR(I2C1_BASE_ADDR + I2C_TIMINGR_OFFSET,reg_val);

    reg_val = REG_RD(I2C1_BASE_ADDR + I2C_CR1_OFFSET);
    reg_val = 1;
    REG_WR(I2C1_BASE_ADDR + I2C_CR1_OFFSET,reg_val);

    return 0;
}






