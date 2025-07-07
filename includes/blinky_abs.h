#ifndef __BLINKY_ABS__
#define __BLINKY_ABS__

void stm_blinky_init();
void wait_for_timer();
void toggle_led();
void unset_timer_flag();

#include "stm_reg_access.h"

#define GPIOA_BASE_ADD                  ( 0x48000000 )
#define RCC_BASE_ADD                    ( 0X40021000 )
#define TIM6_BASE_ADD                   ( 0x40001000 )

#define GPIOA_MODER_OFFSET              ( 0x00 )
#define TIM6_CR1_OFFSET                 ( 0x00 )
#define RCC_AHB2ENR_OFFSET              ( 0x4C )
#define GPIO_MODER_OFFSET               ( 0x0 )
#define GPIOA_ODR_OFFSET                ( 0x14 )
#define TIM6_DIER_OFFSET                ( 0x0C )
#define TIM6_SR_OFFSET                  ( 0x10 )
#define TIM6_ARR_OFFSET                 ( 0x2C )
#define RCC_APB1ENR1_OFFSET             ( 0x58 )
#define TIM6_EGR_OFFSET                 ( 0x14 )
#define TIM6_CNT_OFFSET                 ( 0x24 )
#define TIM6_PSC_OFFSET                 ( 0x28 )

#define TIM6_EGR                        ( TIM6_BASE_ADD + TIM6_EGR_OFFSET  )
#define GPIOA_MODER                     ( GPIOA_BASE_ADD + GPIO_MODER_OFFSET )
#define RCC_AHB2ENR                     ( RCC_BASE_ADD + RCC_AHB2ENR_OFFSET )
#define TIM6_CR1                        ( TIM6_BASE_ADD + TIM6_CR1_OFFSET )
#define GPIOA_ODR                       ( GPIOA_BASE_ADD + GPIOA_ODR_OFFSET )
#define TIM6_DIER                       ( TIM6_BASE_ADD + TIM6_DIER_OFFSET )
#define TIM6_ARR                        ( TIM6_BASE_ADD + TIM6_ARR_OFFSET )
#define TIM6_SR                         ( TIM6_BASE_ADD + TIM6_SR_OFFSET )
#define RCC_APB1ENR1                    ( RCC_BASE_ADD + RCC_APB1ENR1_OFFSET )
#define TIM6_CNT                        ( TIM6_BASE_ADD + TIM6_CNT_OFFSET )
#define TIM6_PSC                        ( TIM6_BASE_ADD + TIM6_PSC_OFFSET )

#define TRUE                            ( 1 )
#define ARR_VALUE                       ( 0x270F )
#define PSC_VALUE                       ( 0x1C1F )
#define EN_GPIOA_CLK                    ( 1 << 0 )
#define EN_TIM6_CLK                     ( 1 << 4 )
#define CLR_PORT5_BITS                 ~( 3 << 10 )
#define GPIOA_PORT_OP_MODE              ( 1 << 10 )
#define CLR_CTR_EN                     ~( 1 << 0 )
#define SET_ARPE                        ( 1 << 7 )
#define EN_CTR                          ( 1 << 0 )
#define GPIOA_P5_OP_DATA                ( 1 << 5 )
#define IS_FLAG_SET                     ( 1 )
#define FLAG_NOT_SET                    ( 0 )

#endif /* __BLINKY_ABS__ */
