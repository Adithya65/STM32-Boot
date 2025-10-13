#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

#include <stdint.h>

void flash_erase_page(uint32_t page_number);
int flash_write_doubleword(uint32_t addr, uint64_t data);

#endif /* FLASH_DRIVER_H */

