#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "blinky_abs.h"

SemaphoreHandle_t xSemaphore;

static void led_task();
static void delay_task();
static void print_task();

void stm_blinky_app()
{
    BaseType_t ret;
    xSemaphore = xSemaphoreCreateBinary();
    configASSERT(xSemaphore != NULL);

    ret = xTaskCreate(led_task,"LED Blink",256,NULL,7,NULL); 
    configASSERT(ret == pdPASS);

    ret = xTaskCreate(delay_task,"delay",256,NULL,6,NULL); 
    configASSERT(ret == pdPASS);

    ret = xTaskCreate(print_task,"print",256,NULL,8,NULL); 
    configASSERT(ret == pdPASS);

    stm_blinky_init();

    vTaskStartScheduler();       

    while (1);
}

void led_task()
{
    while(1)
    {
        toggle_led();
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            unset_timer_flag();
        }
    }
}

void print_task()
{
    int number;
    char c;
    while(1)
    {
        printf("Enter a character: \n\r");
        c = getchar();
        printf("You typed: %c\n\r", c);

        printf("Enter a number:\n\r");
        scanf("%d", &number);
        printf("You typed: %d\n\r", number);
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



