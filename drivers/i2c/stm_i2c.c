#include <stdint.h>
#include <errno.h>
#include "stm_reg_access.h"
#include "stm_i2c.h"

#define TIMEOUT 1000


/*TODO:I2c write api does not look good, replace arguments with struct
  * Handle void stop correctly
  */

static void init_rcc();
static void config_gpio();
static void init_i2c();
static int32_t i2c_write_byte(uint8_t addr, uint8_t* data, uint16_t len, uint8_t start,
                              uint8_t reload);

void i2c_init(void)
{
    init_rcc();
    config_gpio();
    init_i2c();
}

void i2c_stop()
{
    uint32_t volatile reg_val, timeout;

    reg_val  = REG_RD(I2C1_BASE_ADDR + I2C_CR2_OFFSET);
    reg_val |= 1 << 14;
    REG_WR(I2C1_BASE_ADDR + I2C_CR2_OFFSET, reg_val);

    timeout = TIMEOUT;
    while (!(REG_RD(I2C1_BASE_ADDR + I2C_ISR_OFFSET) & (1 << 5)))
    {
        if (--timeout == 0)
            return;
    }
    REG_WR(I2C1_BASE_ADDR + I2C_ICR_OFFSET, (1 << 5));
}


int32_t i2c_write_data(uint8_t addr, uint8_t* data, uint32_t len, uint8_t start, uint8_t reload)
{
    int32_t  ret  = 0;
    uint32_t sent = 0;

    while( sent < len )
    {
        uint16_t chunk = (((len - sent) < 255)?(len - sent):255);
        ret = i2c_write_byte(addr, data + sent, chunk, start, reload);
        if(ret != 0)
            return -EINVAL;
        sent += chunk;
    }

    return ret;
}


static int32_t i2c_write_byte(uint8_t addr, uint8_t* data, uint16_t len, uint8_t start,
                              uint8_t reload)
{
    uint32_t volatile reg_val, timeout;

    reg_val = (addr << 1) | (len << 16);
    if(start)
    {
        reg_val |= (1 << 13);
    }
    if(reload)
    {
        reg_val |= (1 << 24);
    }

    REG_WR(I2C1_BASE_ADDR + I2C_CR2_OFFSET, reg_val);

    for(uint32_t volatile i = 0; i < len; i++)
    {
        timeout = TIMEOUT;
        REG_WR(I2C1_BASE_ADDR + I2C_TXDR_OFFSET, data[i]);
        while (!(REG_RD(I2C1_BASE_ADDR + I2C_ISR_OFFSET) & (1 << 0)))
        {
            if (--timeout == 0)
                return -EINVAL;
        }
    }

    timeout = TIMEOUT;
    if(!reload)
    {

        while (!(REG_RD(I2C1_BASE_ADDR + I2C_ISR_OFFSET) & (1 << 6)))
        {
            if (--timeout == 0)
                return -EINVAL;
        }
    }
    else
    {
        while (!(REG_RD(I2C1_BASE_ADDR + I2C_ISR_OFFSET) & (1 << 7)))
        {
            if (--timeout == 0)
                return -EINVAL;
        }
    }

    return 0;
}

static void init_rcc()
{
    uint32_t reg_val;

    reg_val  = REG_RD(RCC_BASE_ADDR + RCC_APB1ENR1_OFFSET);
    reg_val |= (1 << 21);
    REG_WR(RCC_BASE_ADDR + RCC_APB1ENR1_OFFSET, reg_val);

    reg_val  = REG_RD(RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET);
    reg_val |= (1 << 1);
    REG_WR(RCC_BASE_ADDR + RCC_AHB2ENR_OFFSET, reg_val);
}

static void config_gpio()
{
    uint32_t reg_val;

    reg_val  = REG_RD(GPIOB_BASE_ADDR + GPIO_MODER_OFFSET);
    reg_val &= ~((3 << 16) | (3 << 18));
    reg_val |=  (2 << 16) | (2 << 18);
    REG_WR(GPIOB_BASE_ADDR + GPIO_MODER_OFFSET, reg_val);

    reg_val  = REG_RD(GPIOB_BASE_ADDR + GPIO_OTYPER_OFFSET);
    reg_val |= (1 << 8) | (1 << 9);
    REG_WR(GPIOB_BASE_ADDR + GPIO_OTYPER_OFFSET, reg_val);

    reg_val  = REG_RD(GPIOB_BASE_ADDR + GPIO_PUPDR_OFFSET);
    reg_val &= ~((3 << 16) | (3 << 18));
    reg_val |=  ((1 << 16) | (1 << 18));
    REG_WR(GPIOB_BASE_ADDR + GPIO_PUPDR_OFFSET, reg_val);

    reg_val  = REG_RD(GPIOB_BASE_ADDR + GPIO_AFRH_OFFSET);
    reg_val &= ~((0xF << 0) | (0xF << 4));
    reg_val |= (0x4 << 0) | (0x4 << 4);
    REG_WR(GPIOB_BASE_ADDR + GPIO_AFRH_OFFSET, reg_val);
}

static void init_i2c()
{
    REG_WR(I2C1_BASE_ADDR + I2C_TIMINGR_OFFSET, 0x00303D5B);
    REG_WR(I2C1_BASE_ADDR + I2C_CR1_OFFSET, 1);
}
