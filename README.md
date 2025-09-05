# STM32G491RET6U Bare-Metal Bring-Up with FreeRTOS  

This project provides a bare-metal bring-up of the **STM32G491RET6U** microcontroller with **FreeRTOS integration**. It sets up a minimal runtime environment, integrates a **UART driver for `printf()`**, and provides a **command-line interface (CLI)** for runtime interaction.  

Core peripherals and demos include:  

- **UART logging** (printf() enabled)  
- **I²C communication** with an **OLED display and RTC demo **   
- **FreeRTOS multitasking** with test cases and sample applications (LED blink, OLED, RTC)  

The project is structured to support **selective build flags** for enabling CLI, FreeRTOS test cases, and peripheral demos.  

---

## Target Information  

- **MCU**: STM32G491RET6U  
- **Architecture**: ARM Cortex-M4  
- **Toolchain**: GNU Arm Embedded Toolchain (via **CMake**)  
- **Debugging**: OpenOCD (configs under `tools/`)  

---

## Features  

- **FreeRTOS Integration**  
  - Task creation, scheduling, and multitasking demos  
  - Configurable test case builds  
- **UART Driver**  
  - `printf()` redirection to UART for logging  
  - CLI interface for interactive commands  
- **I²C OLED Support**  
  - Example task displaying text/graphics  
- **RTC Support**  
  - RTC initialization with time/date setting and reading  
  - Example FreeRTOS task showing RTC updates on OLED + UART  
- **Configurable Build Options**  
  - Enable/disable **CLI**, **test cases**, and **sample apps** with CMake flags  
- **Code Quality Tools**  
  - Integrated **Uncrustify** formatting rules  
  - Example **pipeline hooks** for code style enforcement  

---
##  Tools

### Uncrustify  

- Config file: `tools/uncrustify.cfg`  
- Format code:  

```bash
uncrustify -c tools/uncrustify.cfg --replace --no-backup drivers/uart/*.c 
```

### OpenOCD  

- Configuration files are located in the `tools/` directory.  
- Example configuration file: `tools/launch.json`  

## Build Instructions  
```bash
# Clone the repository
git clone https://github.com/yourusername/STM32-Boot.git
cd STM32-Boot

# For CLI
make cli 
# For FreeRTOS tests
make tests
#for freeRTOS samples
make samples

