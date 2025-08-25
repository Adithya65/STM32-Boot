#include <stdio.h>
#include <errno.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "freertos_tests.h"

#define PRIORITY_PRODUCER  (configMAX_PRIORITIES - 2)
#define PRIORITY_CONSUMER  (configMAX_PRIORITIES - 2)
#define PRIORITY_LOGGER    (configMAX_PRIORITIES - 1)

#define QUEUE_LENGTH        5
#define QUEUE_ITEM_SIZE     sizeof(int)

static QueueHandle_t     xQueue             = NULL;
static SemaphoreHandle_t xTestDoneSemaphore = NULL;

static void producer_task(void *params);
static void consumer_task(void *params);
static void logger_task(void *params);

int queue_tests()
{
    BaseType_t ret;

    xQueue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    TEST_ASSERT(xQueue != NULL, "Queue creation failed");

    xTestDoneSemaphore = xSemaphoreCreateBinary();
    TEST_ASSERT(xTestDoneSemaphore != NULL, "Test semaphore creation failed");

    ret = xTaskCreate(producer_task, "Producer1", 256, (void *)1, PRIORITY_PRODUCER, NULL);
    TEST_ASSERT(ret == pdPASS, "Producer task 1 creation failed");

    ret = xTaskCreate(producer_task, "Producer2", 256, (void *)2, PRIORITY_PRODUCER, NULL);
    TEST_ASSERT(ret == pdPASS, "Producer task 2 creation failed");

    ret = xTaskCreate(consumer_task, "Consumer", 256, NULL, PRIORITY_CONSUMER, NULL);
    TEST_ASSERT(ret == pdPASS, "Consumer task creation failed");

    ret = xTaskCreate(logger_task, "Logger", 256, NULL, PRIORITY_LOGGER, NULL);
    TEST_ASSERT(ret == pdPASS, "Logger task creation failed");

    vTaskStartScheduler();
    return -EINVAL;
}

static void producer_task(void *params)
{
    int          producer_id = (int)params;
    int volatile i;
    for (i = 0; i < 6; i++)
    {
        int value = (producer_id * 100) + i;

        if (xQueueSend(xQueue, &value, pdMS_TO_TICKS(1000)) == pdPASS)
        {
            printf("Producer %d: sent %d\n", producer_id, value);
        }
        else
        {
            printf("Producer %d: queue full, could not send %d\n", producer_id, value);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }

    vTaskDelete(NULL);
}

static void consumer_task(void *params)
{
    (void)params;
    int received;
    int received_count = 0;

    while (1)
    {
        if (xQueueReceive(xQueue, &received, pdMS_TO_TICKS(2000)) == pdPASS)
        {
            printf("Consumer: received %d\n", received);
            received_count++;

            if (received_count == 12)
            {
                xSemaphoreGive(xTestDoneSemaphore);
                vTaskDelete(NULL);
            }
        }
        else
        {
            printf("Consumer: timeout waiting for data\n");
        }
    }
}

static void logger_task(void *params)
{
    (void)params;

    if (xSemaphoreTake(xTestDoneSemaphore, pdMS_TO_TICKS(15000)) == pdTRUE)
    {
        TEST_LOG("All messages received correctly");
    }
    else
    {
        TEST_ASSERT(0, "Timeout waiting for test to finish");
    }

    for (;;)
        ;
}
