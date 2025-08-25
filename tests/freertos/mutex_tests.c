#include <stdio.h>
#include <errno.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "freertos_tests.h"

#define PRIORITY_HIGH     (configMAX_PRIORITIES - 1)
#define PRIORITY_MEDIUM   (configMAX_PRIORITIES - 2)
#define PRIORITY_LOW      (configMAX_PRIORITIES - 3)

static SemaphoreHandle_t xMutex1 = NULL;
static SemaphoreHandle_t xMutex2 = NULL;

static void high_task(void *params);
static void medium_task(void *params);
static void low_task(void *params);
static void deadlock_task_A(void *params);
static void deadlock_task_B(void *params);

int mutex_tests()
{
    BaseType_t ret;

    xMutex1 = xSemaphoreCreateMutex();
    TEST_ASSERT(xMutex1 != NULL, "xMutex1 creation failed");

    xMutex2 = xSemaphoreCreateMutex();
    TEST_ASSERT(xMutex2 != NULL, "xMutex2 creation failed");

    ret = xTaskCreate(low_task, "LowTask", 128, NULL, PRIORITY_LOW, NULL);
    TEST_ASSERT(ret == pdPASS, "LowTask creation failed");

    ret = xTaskCreate(medium_task, "MediumTask", 128, NULL, PRIORITY_MEDIUM, NULL);
    TEST_ASSERT(ret == pdPASS, "MediumTask creation failed");

    ret = xTaskCreate(high_task, "HighTask", 128, NULL, PRIORITY_HIGH, NULL);
    TEST_ASSERT(ret == pdPASS, "HighTask creation failed");

    ret = xTaskCreate(deadlock_task_A, "DeadlockA", 128, NULL, PRIORITY_LOW, NULL);
    TEST_ASSERT(ret == pdPASS, "DeadlockA task creation failed");

    ret = xTaskCreate(deadlock_task_B, "DeadlockB", 128, NULL, PRIORITY_LOW, NULL);
    TEST_ASSERT(ret == pdPASS, "DeadlockB task creation failed");

    vTaskStartScheduler();
    return -EINVAL;
}

static void low_task(void *params)
{
    (void)params;
    for (;;)
    {
        if (xSemaphoreTake(xMutex1, pdMS_TO_TICKS(1000)) == pdTRUE)
        {
            printf("LowTask: Took Mutex1\n");
            vTaskDelay(pdMS_TO_TICKS(2000));
            xSemaphoreGive(xMutex1);
            printf("LowTask: Released Mutex1\n");
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void medium_task(void *params)
{
    (void)params;
    for (;;)
    {
        printf("MediumTask: Running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void high_task(void *params)
{
    (void)params;
    vTaskDelay(pdMS_TO_TICKS(500));

    printf("HighTask: Trying to take Mutex1\n");
    if (xSemaphoreTake(xMutex1, portMAX_DELAY) == pdTRUE)
    {
        printf("HighTask: Took Mutex1 (Priority Inheritance should have boosted LowTask)\n");
        xSemaphoreGive(xMutex1);
        printf("HighTask: Released Mutex1\n");
    }

    vTaskDelete(NULL);
}

static void deadlock_task_A(void *params)
{
    (void)params;
    for (;;)
    {
        if (xSemaphoreTake(xMutex1, pdMS_TO_TICKS(1000)) == pdTRUE)
        {
            printf("DeadlockA: Took Mutex1\n");
            vTaskDelay(pdMS_TO_TICKS(100));

            if (xSemaphoreTake(xMutex2, pdMS_TO_TICKS(1000)) == pdTRUE)
            {
                printf("DeadlockA: Took Mutex2\n");
                xSemaphoreGive(xMutex2);
                printf("DeadlockA: Released Mutex2\n");
            }

            xSemaphoreGive(xMutex1);
            printf("DeadlockA: Released Mutex1\n");
        }

        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

static void deadlock_task_B(void *params)
{
    (void)params;
    for (;;)
    {
        if (xSemaphoreTake(xMutex2, pdMS_TO_TICKS(1000)) == pdTRUE)
        {
            printf("DeadlockB: Took Mutex2\n");
            vTaskDelay(pdMS_TO_TICKS(100));

            if (xSemaphoreTake(xMutex1, pdMS_TO_TICKS(1000)) == pdTRUE)
            {
                printf("DeadlockB: Took Mutex1\n");
                xSemaphoreGive(xMutex1);
                printf("DeadlockB: Released Mutex1\n");
            }

            xSemaphoreGive(xMutex2);
            printf("DeadlockB: Released Mutex2\n");
        }

        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

