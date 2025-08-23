#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "FreeRTOS.h"
#include "task.h"

static void i2c_scan_task(void *pvParameters);
static void i2c_oled_display();
static int32_t send_command(uint32_t cmd);
static int32_t oled_send_data(uint8_t *data, uint16_t len);

uint8_t data1[8192];

int32_t i2c_sample(void)
{
    i2c_init();

    xTaskCreate(i2c_scan_task,
                "I2C_Scan",
                256,
                NULL,
                1,
                NULL);

    xTaskCreate(i2c_oled_display,
                "I2C_OLED",
                512,
                NULL,
                1,
                NULL);

    vTaskStartScheduler();

    while(1);
}

static void i2c_scan_task(void *pvParameters)
{
    (void)pvParameters;
    uint8_t test_data =0;

        printf("Scanning I2C bus...\r\n");

        for (uint8_t addr = 1; addr < 128; addr++)
        {
            if (i2c_write_data(addr,&test_data,1) == 0)
                printf("Device found at 0x%02X\n\r", addr);
        }
    
        printf("Scan complete.\n\r");
        vTaskSuspend(NULL);
}

static void i2c_oled_display()
{
   int32_t ret;
   printf("\rStarting OLED display task \r\n");
   send_command(0xAE);  
   send_command(0xA8);  
   send_command(0x3F); 

    send_command(0xD3);  
    send_command(0x00);  

    send_command(0x40);  
    send_command(0xA1);  

    send_command(0xC8);  

    send_command(0xDA);  
    send_command(0x12); 

    send_command(0x81);  
    send_command(0x7F);  

    send_command(0xA4);  
    send_command(0xA6);  

    send_command(0xD5);  
    send_command(0x80);  

    send_command(0x8D);  
    send_command(0x14);

    send_command(0xAF);  
     
    memset(data1,0xFF ,8192);
    memset(&data1[255],0x0 ,1024);

    if(oled_send_data(data1,8192))
    {
        printf("\r ERRORR!!\n");
    }
   
   while(1);
}

static int32_t send_command(uint32_t cmd)
{
    int32_t ret;
    uint8_t data[2];
    data[0] = 0x0;
    data[1] = cmd;
     
    ret = i2c_write_data(0x3C,data,2);        
    if(ret != 0)
        return -EINVAL;
    i2c_stop();
    return 0;
}
uint8_t buff[256];
static int32_t oled_send_data(uint8_t *data, uint16_t len)
{
    uint32_t sent = 0;
    uint8_t ctl = 0x40;
    int32_t ret;

    while (sent < len)
    {
        uint16_t chunk = ((len - sent) < 255) ? (len - sent) : 255;
        buff[0] =0x40;
        memcpy(&buff[1], &data[sent], chunk);
        ret = i2c_write_data(0x3C, buff, chunk+1);
        if (ret != 0)
        {
            i2c_stop();
            return -EINVAL;
        }
        sent += chunk;
        // i2c_stop();
    }
    
    return ret;
}