# STM32G491RET6U Bare-Metal Bring-Up with FreeRTOS

This project initializes the STM32G491RET6U microcontroller from reset, sets up a minimal runtime environment, and ports FreeRTOS with integrated UART driver support for printf(). It provides a simple command-line interface for interaction, along with configurable build options to run FreeRTOS test cases or sample applications such as an LED blink demo and an I²C-based OLED display example. Core features supported include I²C communication, UART logging, and multitasking via FreeRTOS.

---

## Target Information

- **MCU**: STM32G491RET6U  
- **Architecture**: ARM Cortex-M4   
- **Toolchain**: GNU Arm Embedded Toolchain (via CMake)

---

## Debugging with OpenOCD

OpenOCD configuration files for flashing and debugging the STM32G491RET6U target are located in the `tools/` directory.

---


## Build Instructions

```bash
git clone https://github.com/yourusername/STM32-Boot.git
cd STM32-Boot
mkdir build && cd build
cmake ..
make


