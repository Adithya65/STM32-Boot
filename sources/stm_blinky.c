#include <stdint.h>
#include <errno.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "blinky_abs.h"
#include "stm_uart.h"
#include <stdio.h>

SemaphoreHandle_t xSemaphore;

static void led_task();
static void delay_task();

int a =0;

int main(void)
{
    (void)uart_init();
    a = 10;

    BaseType_t ret;
    xSemaphore = xSemaphoreCreateBinary();
    configASSERT(xSemaphore != NULL);

    ret = xTaskCreate(led_task,"LED Blink",256,NULL,7,NULL); 
    configASSERT(ret == pdPASS);

    ret = xTaskCreate(delay_task,"delay",256,NULL,6,NULL); 
    configASSERT(ret == pdPASS);

    stm_blinky_init();

    vTaskStartScheduler();       

    while (1);
}

void led_task()
{
    while(1)
    {
        printf("Hello world");
        toggle_led();
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            unset_timer_flag();
        }
    }
}

void delay_task()
{
    while(1)
    {
        wait_for_timer();
        xSemaphoreGive(xSemaphore);
    }
}

void HardFault_Handler(void)
{
    while(1); 
}



