#ifndef __STM32_REG_ACCESS_H__
#define __STM32_REG_ACCESS_H__

__attribute__((always_inline))inline void REG_WR(volatile uint32_t addr, uint32_t val)
{
    *(uint32_t*)addr = val;
}

__attribute__((always_inline))inline uint32_t REG_RD(volatile uint32_t addr)
{
    return *(uint32_t*)addr;
}

#endif /*__STM32_REG_ACCESS_H__*/
