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
project(blinky C)
#set(MCU "cortex-m4")
#set(CPU_FLAGS "-mcpu=${MCU} -mthumb ")
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/stm32g4.ld -nostartfiles -Wl,--gc-sections")
set(CMAKE_C_FLAGS "${CPU_FLAGS} -std=c11 -g -O0 -Wall -Wextra -ffunction-sections -fdata-sections")
set(SOURCES
    ${CMAKE_SOURCE_DIR}/sources/stm_blinky.c
    ${CMAKE_SOURCE_DIR}/sources/startup_stm32.c
    ${FREERTOS_SRC}
)
add_executable(blinky.elf ${SOURCES})
target_include_directories(blinky.elf PRIVATE ${CMAKE_SOURCE_DIR}/includes ${FREERTOS_KERNEL_DIR}/include ${FREERTOS_PORT_DIR} )

