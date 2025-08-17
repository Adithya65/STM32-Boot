#define I2C_SAMPLE      1
#define BLINKY_SAMPLE   1


void stm_samples()
{
#if I2C_SAMPLE
    i2c_sample();
#elif BLINKY_SAMPLE
    stm_blinky_app();
#endif
}
