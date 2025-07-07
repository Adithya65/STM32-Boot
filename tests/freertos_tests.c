#include <errno.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "freertos_tests.h"

#define task_1_priority configMAX_PRIORITIES -2
#define task_2_priority configMAX_PRIORITIES -2
#define task_3_priority configMAX_PRIORITIES -2

static void task_1();
static void task_2();
static void task_3();

int freertos_tests()
{
    BaseType_t xReturned;
    TaskHandle_t task_handle_1 = NULL;
    TaskHandle_t task_handle_2 = NULL;
    TaskHandle_t task_handle_3 = NULL;

    xReturned = xTaskCreate(
            task_1,
            "task_1",
            256,
            NULL,
            tskIDLE_PRIORITY,
            &task_handle_1);

    if (xReturned != pdPASS)
    {
        return -EINVAL;
    }

    xReturned = xTaskCreate(
            task_2,
            "task_2",
            256,
            NULL,
            tskIDLE_PRIORITY,
            &task_handle_2);

    if (xReturned != pdPASS)
    {
        return -EINVAL;
    }

    xReturned = xTaskCreate(
            task_3,
            "task_3",
            256,
            NULL,
            tskIDLE_PRIORITY,
            &task_handle_3);

    if (xReturned != pdPASS)
    {
        return -EINVAL;
    }

    vTaskStartScheduler();

    /*Fall back,should not be reaching here*/
    return -EINVAL;
}

static void task_1()
{
    printf("hello from task 1\n");
    while(1);
}

static void task_2()
{
    printf("hello from task 2\n");
    while(1);
}

static void task_3()
{
    printf("hello from task 3\n");
    while(1);
}
