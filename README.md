# STM32-Boot
##arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -std=c11 -g -O0 -c stm_blinky.c -o blinky.o
##arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -std=c11 -g -O0 -c startup_stm32.c -o startup_stm32.o
##arm-none-eabi-gcc -nolibc -nostartfiles -T stm32g4.ld blinky.o startup_stm32.o -o blinky.elf

