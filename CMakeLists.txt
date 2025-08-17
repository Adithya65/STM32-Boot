cmake_minimum_required(VERSION 3.15)
set(FREERTOS_KERNEL_DIR ${CMAKE_SOURCE_DIR}/freertos/FreeRTOS-Kernel)
set(FREERTOS_PORT_DIR ${CMAKE_SOURCE_DIR}/freertos/)
set(FREERTOS_SRC
    ${FREERTOS_KERNEL_DIR}/tasks.c
    ${FREERTOS_KERNEL_DIR}/list.c
    ${FREERTOS_KERNEL_DIR}/queue.c
    ${FREERTOS_KERNEL_DIR}/timers.c
    ${FREERTOS_KERNEL_DIR}/event_groups.c
    ${FREERTOS_PORT_DIR}/heap_4.c
    ${FREERTOS_PORT_DIR}/port.c
)

set(FREERTOS_TESTS
    ${CMAKE_SOURCE_DIR}/tests/freertos/freertos_tests.c
    ${CMAKE_SOURCE_DIR}/tests/freertos/semaphore_tests.c
    ${CMAKE_SOURCE_DIR}/tests/freertos/mutex_tests.c
    ${CMAKE_SOURCE_DIR}/tests/freertos/queue_tests.c
    ${CMAKE_SOURCE_DIR}/tests/freertos/print_number_tests.c
)

set(UART_DRIVER
    ${CMAKE_SOURCE_DIR}/drivers/uart/stm_uart.c
    ${CMAKE_SOURCE_DIR}/drivers/uart/stm_uart_ll.c
)

set(I2C_DRIVER
    ${CMAKE_SOURCE_DIR}/drivers/i2c/stm_i2c.c
)


project(blinky C)
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/stm32g4.ld -nostartfiles -Wl,--gc-sections -specs=nano.specs")
set(CMAKE_C_FLAGS "${CPU_FLAGS} -std=c11 -g -O0 -Wall -Wextra -ffunction-sections -fdata-sections")
set(SOURCES
    ${CMAKE_SOURCE_DIR}/samples/stm_blinky.c
    ${CMAKE_SOURCE_DIR}/sources/startup_stm32.c
    ${CMAKE_SOURCE_DIR}/samples/blinky_abs.c
    ${CMAKE_SOURCE_DIR}/samples/stm_samples.c
    ${CMAKE_SOURCE_DIR}/sources/console.c
    ${CMAKE_SOURCE_DIR}/sources/main.c
    ${CMAKE_SOURCE_DIR}/cli/base/FreeRTOS_CLI.c
    ${CMAKE_SOURCE_DIR}/cli/app/cli_sample.c
    ${CMAKE_SOURCE_DIR}/cli/app/cli_cal.c
    ${CMAKE_SOURCE_DIR}/samples/i2c_sample.c
    ${UART_DRIVER}
    ${I2C_DRIVER}
    ${FREERTOS_SRC}
    ${FREERTOS_TESTS}
)

add_executable(RTOS.elf ${SOURCES})

target_include_directories(RTOS.elf PRIVATE 
    ${CMAKE_SOURCE_DIR}/includes  
    ${CMAKE_SOURCE_DIR}/drivers/uart  
    ${CMAKE_SOURCE_DIR}/drivers/i2c 
    ${CMAKE_SOURCE_DIR}/tests/freertos 
    ${CMAKE_SOURCE_DIR}/cli/base/ 
    ${CMAKE_SOURCE_DIR}/cli/app/ 
    ${FREERTOS_KERNEL_DIR}/include 
    ${FREERTOS_PORT_DIR}
)

