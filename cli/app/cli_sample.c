#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS_CLI.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

extern void vRegisterCLICommands(void);

#define MAX_INPUT_SIZE 60
#define MAX_OUTPUT_SIZE 256

static char cInputBuffer[MAX_INPUT_SIZE];
static char cOutputBuffer[MAX_OUTPUT_SIZE];
static char cIsZeroBuffer[MAX_INPUT_SIZE];

void vCLITask(void *pvParameters)
{

    BaseType_t xMoreDataToFollow;
    int inputIndex = 0;
    char c;

    (void)pvParameters;

    printf("\r\nSTM32#"); 

    for (;;)
    {
        c = getchar(); 

        if (c == '\r' || c == '\n')
        {
            if(!(memcmp(cInputBuffer,cIsZeroBuffer,MAX_INPUT_SIZE)))
            {
                printf("\r\nSTM32#");
                continue;
            }
            printf("\r\n");
            do
            {
                xMoreDataToFollow = FreeRTOS_CLIProcessCommand(cInputBuffer, cOutputBuffer, MAX_OUTPUT_SIZE);
                printf("%s", cOutputBuffer);
            } while (xMoreDataToFollow != pdFALSE);

            memset(cInputBuffer, 0, MAX_INPUT_SIZE);
            inputIndex = 0;
            printf("STM32#");
        }
        else if (isprint((int)c) && inputIndex < MAX_INPUT_SIZE - 1)
        {
            cInputBuffer[inputIndex++] = c;
            putchar(c); 
        }
        else if (c == '\b' && inputIndex > 0)
        {
            inputIndex--;
            cInputBuffer[inputIndex] = '\0';
            printf("\b \b");
        }
    }
}

int cli_task(void)
{
    vRegisterCLICommands();

    xTaskCreate(vCLITask, "CLI", 1024, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1); 
}

