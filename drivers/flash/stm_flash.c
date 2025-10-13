#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "stm_reg_access.h"

#define FLASH_BASE      0x40022000

#define FLASH_SR_OFFSET     0x10
#define FLASH_CR_OFFSET     0x14
#define FLASH_KEYR_OFFSET   0x8

#define FLASH_SR        FLASH_BASE + FLASH_SR_OFFSET
#define FLASH_CR        FLASH_BASE + FLASH_CR_OFFSET
#define FLASH_KEYR      FLASH_BASE + FLASH_KEYR_OFFSET

#define FLASH_KEY1      0x45670123U
#define FLASH_KEY2      0xCDEF89ABU

#define FLASH_SR_EOP    (1U << 0)
#define FLASH_SR_PGSERR (1U << 7)
#define FLASH_SR_SIZERR (1U << 6)
#define FLASH_SR_PGAERR (1U << 5)
#define FLASH_SR_BSY    (1U << 16)

#define FLASH_CR_PG     (1U << 0)
#define FLASH_CR_PER    (1U << 1)
#define FLASH_CR_PNB_Pos 3U
#define FLASH_CR_PNB_Msk (0xFFU << FLASH_CR_PNB_Pos)
#define FLASH_CR_STRT   (1U << 16)
#define FLASH_CR_LOCK   (1U << 31)


static void flash_wait_not_busy(void)
{
    while(1)
    {
        uint32_t reg_val = REG_RD(FLASH_BASE + FLASH_SR_OFFSET);
        if((reg_val & FLASH_SR_BSY) == 0)
            break;
    }
}

static void flash_clear_flags(void)
{
    uint32_t reg_val = 0;
    reg_val  = REG_RD(FLASH_BASE + FLASH_SR_OFFSET);
    reg_val |= FLASH_SR_EOP | FLASH_SR_PGSERR | FLASH_SR_SIZERR | FLASH_SR_PGAERR;
    REG_WR(FLASH_BASE + FLASH_SR_OFFSET, reg_val);
}

static void flash_unlock(void)
{
    uint32_t reg_val;
    reg_val = REG_RD(FLASH_BASE + FLASH_CR_OFFSET);
    if (reg_val & FLASH_CR_LOCK)
    {
        REG_WR(FLASH_BASE + FLASH_KEYR_OFFSET, FLASH_KEY1);
        REG_WR(FLASH_BASE + FLASH_KEYR_OFFSET, FLASH_KEY2);
    }
}

static void flash_lock(void)
{
    uint32_t reg_val = REG_RD(FLASH_BASE + FLASH_CR_OFFSET);
    reg_val |= FLASH_CR_LOCK;
    REG_WR(FLASH_BASE + FLASH_CR_OFFSET, FLASH_CR_LOCK);
}

void flash_erase_page(uint32_t page_number)
{
    uint32_t reg_val = 0;
    flash_wait_not_busy();
    flash_clear_flags();
    flash_unlock();

    reg_val  = REG_RD(FLASH_BASE + FLASH_CR_OFFSET);
    reg_val &= ~FLASH_CR_PNB_Msk;
    reg_val |= FLASH_CR_PER | ((page_number << FLASH_CR_PNB_Pos) & FLASH_CR_PNB_Msk);
    REG_WR(FLASH_BASE + FLASH_CR_OFFSET, reg_val);

    reg_val  = REG_RD(FLASH_BASE + FLASH_CR_OFFSET);
    reg_val |= FLASH_CR_STRT;
    REG_WR(FLASH_BASE + FLASH_CR_OFFSET, reg_val);

    flash_wait_not_busy();
    flash_clear_flags();

    reg_val  = REG_RD(FLASH_BASE + FLASH_CR_OFFSET);
    reg_val &= ~FLASH_CR_PER;
    REG_WR(FLASH_BASE + FLASH_CR_OFFSET, reg_val);
}

int flash_write_doubleword(uint32_t addr, uint64_t data)
{
    uint32_t reg_val = 0;
    if (addr % 8 != 0)
        return -1;

    flash_wait_not_busy();
    flash_clear_flags();
    flash_unlock();

    reg_val  = REG_RD(FLASH_BASE + FLASH_CR_OFFSET);
    reg_val |= FLASH_CR_PG;
    reg_val &= ~(1 << 1);
    REG_WR(FLASH_BASE + FLASH_CR_OFFSET, reg_val);

    *(volatile uint32_t*)addr       = (uint32_t)(data & 0xFFFFFFFFU);
    *(volatile uint32_t*)(addr + 4) = (uint32_t)(data >> 32);

    flash_wait_not_busy();

    reg_val = REG_RD(FLASH_BASE + FLASH_SR_OFFSET);

    if (reg_val & (FLASH_SR_PGSERR | FLASH_SR_SIZERR | FLASH_SR_PGAERR))
    {
        flash_clear_flags();
        reg_val  = REG_RD(FLASH_BASE + FLASH_CR_OFFSET);
        reg_val &= ~FLASH_CR_PG;
        REG_WR(FLASH_BASE + FLASH_CR_OFFSET, reg_val);
        flash_lock();
        return -2;
    }

    flash_clear_flags();
    reg_val  = REG_RD(FLASH_BASE + FLASH_CR_OFFSET);
    reg_val &= ~FLASH_CR_PG;
    REG_WR(FLASH_BASE + FLASH_CR_OFFSET, reg_val);

    flash_lock();

    uint64_t read_back = *((volatile uint64_t*)addr);
    if (read_back != data)
        return -3;

    return 0;
}


