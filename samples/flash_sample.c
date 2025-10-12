#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "FreeRTOS.h"
#include "task.h"
#include "stm_flash.h"

void flash_task(void *pvParameters);

void flash_sample(void)
{
    xTaskCreate(flash_task,
                "I2C_RTC",
                256,
                NULL,
                2,
                NULL);

    vTaskStartScheduler();

    while(1)
        ;
}

#define DEBUG 0

void flash_task(void *pvParameters)
{
    (void)pvParameters;
    uint32_t page_number = 127;
    uint32_t flash_addr  = 0x0803F800;
    uint64_t value       = 0x123456;

#if DEBUG
    uint64_t temp = *(volatile uint32_t*)flash_addr;
#endif
    flash_erase_page(page_number);

    int ret = flash_write_doubleword(flash_addr, value);
    if (ret == 0)
    {
        while (1)
            ;
    }
    else
    {
        while (1)
            ;
    }

}
