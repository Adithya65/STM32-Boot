#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include <stdlib.h>
#include <stdio.h>

/* Add Command */
static BaseType_t prvAddCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
    const char *pcParameter1, *pcParameter2;
    BaseType_t xParameter1Length, xParameter2Length;
    int num1, num2;

    pcParameter1 = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameter1Length);
    pcParameter2 = FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParameter2Length);

    if (pcParameter1 == NULL || pcParameter2 == NULL)
    {
        snprintf(pcWriteBuffer, xWriteBufferLen, "Error: Missing parameters\r\n");
        return pdFALSE;
    }

    num1 = atoi(pcParameter1);
    num2 = atoi(pcParameter2);

    snprintf(pcWriteBuffer, xWriteBufferLen, "Result: %d\r\n", num1 + num2);
    return pdFALSE;
}

/* Subtract Command */
static BaseType_t prvSubCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
    const char *pcParameter1, *pcParameter2;
    BaseType_t xParameter1Length, xParameter2Length;
    int num1, num2;

    pcParameter1 = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameter1Length);
    pcParameter2 = FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParameter2Length);

    if (pcParameter1 == NULL || pcParameter2 == NULL)
    {
        snprintf(pcWriteBuffer, xWriteBufferLen, "Error: Missing parameters\r\n");
        return pdFALSE;
    }

    num1 = atoi(pcParameter1);
    num2 = atoi(pcParameter2);

    snprintf(pcWriteBuffer, xWriteBufferLen, "Result: %d\r\n", num1 - num2);
    return pdFALSE;
}

/* Command Definitions */
static const CLI_Command_Definition_t xAddCommand =
{
    "add",
    "add <num1> <num2>:\r\n Adds two numbers.\r\n",
    prvAddCommand,
    2
};

static const CLI_Command_Definition_t xSubCommand =
{
    "sub",
    "sub <num1> <num2>:\r\n Subtracts second number from first.\r\n",
    prvSubCommand,
    2
};

void vRegisterCLICommands(void)
{
    FreeRTOS_CLIRegisterCommand(&xAddCommand);
    FreeRTOS_CLIRegisterCommand(&xSubCommand);
}

