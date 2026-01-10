# FreeRTOS Snake Game on STM32

This project implements a classic Snake game on an STM32 microcontroller using FreeRTOS.
The system is designed as a multi-task application with separate tasks for user input,
game logic, and screen rendering, communicating via queues, semaphores, and mutexes.

---

## Hardware Requirements

- STM32 development board (tested on STM32 series with STM32Cube support)
- SSD1306 OLED display (I2C interface)
- Analog joystick (connected to ADC channels)
- USB cable for programming and debugging

---

## Software Requirements

- STM32CubeIDE (recommended)
- STM32CubeMX (used for peripheral and FreeRTOS configuration)
- ARM GCC toolchain (included with STM32CubeIDE)
- ST-Link drivers (for flashing and debugging)

---

## Project Structure

```

FreeRTOS_SnakeGame/
├── Core/
│   ├── Inc/
│   │   ├── main.h              # Main application header, global definitions
│   │   ├── freertos.h          # FreeRTOS configuration interface
│   │   ├── cmsis_os.h          # CMSIS-RTOS abstraction layer
│   │   ├── gpio.h              # GPIO initialization and pin definitions
│   │   ├── adc.h               # ADC configuration (joystick input)
│   │   ├── i2c.h               # I2C configuration (SSD1306 display)
│   │   ├── dma.h               # DMA configuration (ADC DMA)
│   │   ├── usart.h             # USART configuration (debug output)
│   │   ├── snake.h             # Snake game data structures and logic interface
│   │   ├── ssd1306.h            # SSD1306 OLED display driver interface
│   │   ├── fonts.h              # Font definitions for OLED rendering
│   │   └── screen.h             # Screen rendering helper functions
│   │
│   └── Src/
│       ├── main.c              # Program entry point, hardware init, RTOS start
│       ├── freertos.c          # RTOS objects, tasks, queues, semaphores creation
│       ├── gpio.c              # GPIO initialization
│       ├── adc.c               # ADC + DMA initialization
│       ├── i2c.c               # I2C initialization
│       ├── dma.c               # DMA controller setup
│       ├── usart.c             # USART initialization
│       ├── snake.c             # Snake game core logic (movement, food, collision)
│       ├── ssd1306.c            # SSD1306 OLED display driver implementation
│       ├── fonts.c              # Font bitmap data
│       └── screen.c             # Screen drawing and pixel scaling functions
│
├── Drivers/                    # STM32 HAL drivers
├── FreeRTOS/                   # FreeRTOS kernel source
├── Middlewares/                # CMSIS and RTOS middleware
├── .ioc                        # STM32CubeMX configuration file
└── README.md


```

---

## How to Compile the Project

### Option 1: Using STM32CubeIDE (Recommended)

1. Open STM32CubeIDE
2. Select **File → Open Projects from File System**
3. Choose the project root directory
4. Wait for the IDE to import and index the project
5. Click **Build Project** (hammer icon)
6. If the build succeeds, an `.elf` file will be generated

---

## How to Run the Game

1. Connect the STM32 board to your computer via USB
2. Ensure the SSD1306 display and joystick are correctly wired
3. In STM32CubeIDE, click **Run** or **Debug**
4. The program will be flashed to the board automatically

After reset:

- The Snake game starts immediately
- The score is shown at the top of the OLED display
- Use the joystick to control the snake direction
- When the game ends, a **Game Over** message is displayed
- Move the joystick to restart the game

---

## Controls

| Joystick Direction | Snake Action |
|--------------------|-------------|
| Up                 | Move Up     |
| Down               | Move Down   |
| Left               | Move Left   |
| Right              | Move Right  |

