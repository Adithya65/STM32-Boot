#define I2C_SAMPLE      0
#define BLINKY_SAMPLE   0
#define FLASH_SAMPLE    1

void i2c_sample();
void stm_blinky_app();
void flash_sample();

void stm_samples()
{
#if I2C_SAMPLE
    i2c_sample();
#elif BLINKY_SAMPLE
    stm_blinky_app();
#elif FLASH_SAMPLE
    flash_sample();
#endif
}
