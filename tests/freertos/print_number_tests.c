#include <errno.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "freertos_tests.h"

#define PRIORITY_HIGH    (configMAX_PRIORITIES - 1)
#define PRIORITY_MEDIUM  (configMAX_PRIORITIES - 2)
#define PRIORITY_LOW     (configMAX_PRIORITIES - 3)

static SemaphoreHandle_t xBinarySem1 = NULL;
static SemaphoreHandle_t xBinarySem2 = NULL;

static void even_num_task(void* params);
static void odd_num_task(void* params);

int atomic_num = 0;

int number_tests()
{
    BaseType_t xReturned;

    xBinarySem1 = xSemaphoreCreateBinary();
    TEST_ASSERT(xBinarySem1 != NULL, "Binary semaphore creation failed");

    xBinarySem2 = xSemaphoreCreateBinary();
    TEST_ASSERT(xBinarySem2 != NULL, "Binary semaphore creation failed");

    xReturned = xTaskCreate(even_num_task, "EvenNumTask", 512, NULL, PRIORITY_HIGH, NULL);
    TEST_ASSERT(xReturned == pdPASS, "even num print task creation failed");

    xReturned = xTaskCreate(odd_num_task, "OddNumTask", 512, NULL, PRIORITY_HIGH, NULL);
    TEST_ASSERT(xReturned == pdPASS, "odd num print creation failed");

    vTaskStartScheduler();
    return -EINVAL;
}

static void even_num_task(void* params)
{
    (void)params;
    xSemaphoreGive(xBinarySem2);
    while (1)
    {
        if (xSemaphoreTake(xBinarySem2, portMAX_DELAY) == pdTRUE)
        {
            printf("Printing even %d\r\n", atomic_num);
            atomic_num++;
        }
        xSemaphoreGive(xBinarySem1);
    }
}

static void odd_num_task(void* params)
{
    (void)params;
    while (1)
    {
        if (xSemaphoreTake(xBinarySem1, portMAX_DELAY) == pdTRUE)
        {
            printf("Printing odd %d\r\n", atomic_num);
            atomic_num++;
        }
        xSemaphoreGive(xBinarySem2);
    }
}

