#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "stm_i2c.h"

/* Add Command */
static BaseType_t prvAddCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
                                const char *pcCommandString)
{
    const char *pcParameter1, *pcParameter2;
    BaseType_t  xParameter1Length, xParameter2Length;
    int         num1, num2;

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
static BaseType_t prvSubCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
                                const char *pcCommandString)
{
    const char *pcParameter1, *pcParameter2;
    BaseType_t  xParameter1Length, xParameter2Length;
    int         num1, num2;

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

static BaseType_t prvEchoCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
                                 const char *pcCommandString)
{
    const char *pcParameter1;
    BaseType_t  xParameter1Length;

    pcParameter1 = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameter1Length);

    if (pcParameter1 == NULL)
    {
        snprintf(pcWriteBuffer, xWriteBufferLen, "Error: Missing parameters\r\n");
        return pdFALSE;
    }
    memcpy(pcWriteBuffer, pcParameter1, xWriteBufferLen);
    strcat(pcWriteBuffer, "\r\n");
    return pdFALSE;
}

static inline uint8_t bcd2dec(uint8_t val)
{
    return ((val >> 4) * 10) + (val & 0x0F);
}

static BaseType_t prvDateCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
                                 const char *pcCommandString)
{
    (void)pcCommandString;
    uint8_t buf[7];
    uint8_t reg = 0x00;

    i2c_write_data(0x68, &reg, 1, 1, 0);

    i2c_read_data(0x68, buf, 7);

    uint8_t date  = bcd2dec(buf[4]);
    uint8_t month = bcd2dec(buf[5] & 0x1F);
    uint8_t year  = bcd2dec(buf[6]);

    snprintf(pcWriteBuffer, xWriteBufferLen, "%02d-%02d-20%02d \r\n", date, month, year);

    return pdFALSE;
}

static BaseType_t prvTimeCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
                                 const char *pcCommandString)
{
    (void)pcCommandString;

    uint8_t buf[7];
    uint8_t reg = 0x00;

    i2c_write_data(0x68, &reg, 1, 1, 0);

    i2c_read_data(0x68, buf, 7);

    uint8_t sec  = bcd2dec(buf[0] & 0x7F);
    uint8_t min  = bcd2dec(buf[1]);
    uint8_t hour = bcd2dec(buf[2] & 0x3F);

    snprintf(pcWriteBuffer, xWriteBufferLen, "%02d:%02d:%02d \r\n", hour, min, sec);

    return pdFALSE;
}

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

static const CLI_Command_Definition_t xEchoCommand =
{
    "echo",
    "echo <Message>:\r\n Echo input message\r\n",
    prvEchoCommand,
    -1
};

static const CLI_Command_Definition_t xDateCommand =
{
    "get_date",
    "get_date:\r\n Returns date,month and year\r\n",
    prvDateCommand,
    0
};

static const CLI_Command_Definition_t xTimeCommand =
{
    "get_time",
    "get_time:\r\n Returns current time\r\n",
    prvTimeCommand,
    0
};

void vRegisterCLICommands(void)
{
    FreeRTOS_CLIRegisterCommand(&xAddCommand);
    FreeRTOS_CLIRegisterCommand(&xSubCommand);
    FreeRTOS_CLIRegisterCommand(&xEchoCommand);
    FreeRTOS_CLIRegisterCommand(&xDateCommand);
    FreeRTOS_CLIRegisterCommand(&xTimeCommand);
}

