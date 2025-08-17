#ifndef __STM_I2C__
#define __STM_I2C__

#define RCC_BASE_ADDR                   0x40021000
#define GPIOB_BASE_ADDR                 0x48000400
#define I2C1_BASE_ADDR                  0x40005400

#define RCC_APB1ENR1_OFFSET             0x58
#define RCC_AHB2ENR_OFFSET              0x4C
#define GPIO_MODER_OFFSET               0x0
#define GPIO_OTYPER_OFFSET              0x4
#define GPIO_PUPDR_OFFSET               0xC
#define GPIO_AFRH_OFFSET                0x24
#define GPIO_AFRL_OFFSET                0x20

#define I2C_CR1_OFFSET                  0x0
#define I2C_CR2_OFFSET                  0x4
#define I2C_TIMINGR_OFFSET              0x10
#define I2C_ISR_OFFSET                  0x18
#define I2C_TXDR_OFFSET                 0x28
#define I2C_ICR_OFFSET                  0x1C



#endif
