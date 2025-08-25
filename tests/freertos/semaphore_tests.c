#include <errno.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "freertos_tests.h"

#define PRIORITY_HIGH    (configMAX_PRIORITIES - 1)
#define PRIORITY_MEDIUM  (configMAX_PRIORITIES - 2)
#define PRIORITY_LOW     (configMAX_PRIORITIES - 3)


static SemaphoreHandle_t xBinarySem      = NULL;
static SemaphoreHandle_t xRecursiveMutex = NULL;

static void high_priority_task(void *params);
static void medium_priority_task(void *params);
static void low_priority_task(void *params);
static void timeout_task(void *params);
static void isr_simulator_task(void *params);

int semaphore_tests()
{
    BaseType_t xReturned;

    xBinarySem = xSemaphoreCreateBinary();
    TEST_ASSERT(xBinarySem != NULL, "Binary semaphore creation failed");

    xRecursiveMutex = xSemaphoreCreateRecursiveMutex();
    TEST_ASSERT(xRecursiveMutex != NULL, "Recursive mutex creation failed");

    xReturned = xTaskCreate(high_priority_task, "HighTask", 128, NULL, PRIORITY_HIGH, NULL);
    TEST_ASSERT(xReturned == pdPASS, "High task creation failed");

    xReturned = xTaskCreate(medium_priority_task, "MediumTask", 128, NULL, PRIORITY_MEDIUM, NULL);
    TEST_ASSERT(xReturned == pdPASS, "Medium task creation failed");

    xReturned = xTaskCreate(low_priority_task, "LowTask", 128, NULL, PRIORITY_LOW, NULL);
    TEST_ASSERT(xReturned == pdPASS, "Low task creation failed");

    xReturned = xTaskCreate(timeout_task, "TimeoutTask", 128, NULL, PRIORITY_LOW, NULL);
    TEST_ASSERT(xReturned == pdPASS, "Timeout task creation failed");

    xReturned = xTaskCreate(isr_simulator_task, "ISRSim", 128, NULL, PRIORITY_LOW, NULL);
    TEST_ASSERT(xReturned == pdPASS, "ISR simulator task creation failed");

    vTaskStartScheduler();
    return -EINVAL;
}

static void high_priority_task(void *params)
{
    (void)params;
    while (1)
    {
        if (xSemaphoreTake(xBinarySem, portMAX_DELAY) == pdTRUE)
        {
            TEST_LOG("High Priority Task: Took binary semaphore!");
        }
    }
}

static void medium_priority_task(void *params)
{
    (void)params;
    while (1)
    {
        TEST_LOG("Medium Priority Task: Executing");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void low_priority_task(void *params)
{
    (void)params;
    while (1)
    {
        if (xSemaphoreTakeRecursive(xRecursiveMutex, pdMS_TO_TICKS(1000)) == pdTRUE)
        {
            TEST_LOG("Low Priority Task: Took recursive mutex - level 1");

            if (xSemaphoreTakeRecursive(xRecursiveMutex, pdMS_TO_TICKS(1000)) == pdTRUE)
            {
                TEST_LOG("Low Priority Task: Took recursive mutex - level 2");
                vTaskDelay(pdMS_TO_TICKS(200));
                xSemaphoreGiveRecursive(xRecursiveMutex);
                TEST_LOG("Low Priority Task: Released recursive mutex - level 2");
            }

            xSemaphoreGiveRecursive(xRecursiveMutex);
            TEST_LOG("Low Priority Task: Released recursive mutex - level 1");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

static void timeout_task(void *params)
{
    (void)params;
    while (1)
    {
        TEST_LOG("Timeout Task: Waiting for binary semaphore (2s timeout)...");
        if (xSemaphoreTake(xBinarySem, pdMS_TO_TICKS(2000)) == pdTRUE)
        {
            TEST_LOG("Timeout Task: Got binary semaphore!");
        }
        else
        {
            TEST_LOG("Timeout Task: Timed out while waiting.");
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void isr_simulator_task(void *params)
{
    (void)params;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
        xSemaphoreGive(xBinarySem);
    }
}

