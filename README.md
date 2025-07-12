# STM32G491RET6U Bare-Metal Bring-Up with FreeRTOS

This project brings up the STM32G491RET6U microcontroller from reset, implements a minimal runtime environment, ports FreeRTOS, and integrates a UART driver with `printf()` support. It includes configurable build options to run either freertos tests or a simple sample application.

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


