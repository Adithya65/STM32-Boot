
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include "FreeRTOS.h"
#include "task.h"

static void i2c_scan_task(void *pvParameters);
static void i2c_oled_display();
static int32_t send_command(uint32_t cmd);
static void oled_send_data(uint8_t *data, uint16_t len);

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
                256,
                NULL,
                1,
                NULL);

    vTaskStartScheduler();

    while(1);
}


static void i2c_scan_task(void *pvParameters)
{
    (void)pvParameters;

        printf("Scanning I2C bus...\r\n");

        for (uint8_t addr = 1; addr < 128; addr++)
        {
            if (i2c_write_byte(addr,0x00,0) == 0)
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

    send_command(0x20);  
    send_command(0x00);  

    send_command(0xB0);  
    send_command(0xC8);  
    send_command(0x00);  
    send_command(0x10);  
    send_command(0x40);  

    send_command(0x81);  
    send_command(0xFF);  

    send_command(0xA1);  
    send_command(0xA6);  
    send_command(0xA8);  
    send_command(0x3F); 

    send_command(0xD3);  
    send_command(0x00);  
    send_command(0xD5);  
    send_command(0xF0);  
    send_command(0xD9);  
    send_command(0x22); 
    send_command(0xDA);  
    send_command(0x12); 
    send_command(0xDB); 
    send_command(0x20); 

    send_command(0x8D);  
    send_command(0x14);  

    send_command(0xAF);  
    send_command(0xB0); 
    send_command(0x00); 
    send_command(0x10); 

     
    uint8_t data[128];
    for(int volatile i=0;i<128;i++) 
        data[i] = 0xFF; 
    oled_send_data(data, 128);
   
   while(1);
}

static int32_t send_command(uint32_t cmd)
{
    int32_t ret;
    uint8_t data[2];
    data[0] = 0x0;
    data[1] = cmd;
     
    ret = i2c_write_byte(0x3C,data,2);        
    if(ret != 0)
        return -EINVAL;
    return 0;
}


 
static void oled_send_data(uint8_t *data, uint16_t len) 
{
    i2c_write_byte(0x3C,0x00,1);

    for(uint16_t volatile i = 0; i < len; i++) 
    {
        i2c_write_byte(0x3C,data[i],1);          
    }

   
}
