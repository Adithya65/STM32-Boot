cmake_minimum_required(VERSION 3.15)
project(blinky C)
set(MCU "cortex-m0")
set(CPU_FLAGS "-mcpu=${MCU} -mthumb")
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/stm32g4.ld -nostartfiles -nolibc -Wl,--gc-sections")
set(CMAKE_C_FLAGS "${CPU_FLAGS} -std=c11 -g -O0 -Wall -Wextra -ffunction-sections -fdata-sections")
set(SOURCES
    ${CMAKE_SOURCE_DIR}/sources/stm_blinky.c
    ${CMAKE_SOURCE_DIR}/sources/startup_stm32.c
)
add_executable(blinky.elf ${SOURCES})
target_include_directories(blinky.elf PRIVATE ${CMAKE_SOURCE_DIR}/includes)

