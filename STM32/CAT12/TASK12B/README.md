# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 12

**DATE:** 19/10/2026

**NAME OF EXP:** STM32F401RE Cortex-M4: GPIO & User Input Programming

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE

---

## TASK 12B : User Push Button B1 Control with Latching State

### 1. Circuit Diagram

The experiment demonstrates reading blue user push-button B1 on pin PC13 to toggle and latch the state of LED LD2 on pin PA5.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PC13 (Blue Push Button B1), PA5 (Green LED LD2)
- **Power Supply / Interface:** On-board Peripherals

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Button B1 connects PC13 to GND when pressed (active-low). The firmware detects the falling edge, applies a 20ms debounce delay, toggles an internal latch variable, updates the LED, and waits for button release.

**Pseudocode:**

1. Configure PA5 as output and PC13 as input with no pull (external pull-up on board).
2. Read PC13 pin using HAL_GPIO_ReadPin().
3. If pin is LOW (pressed), call HAL_Delay(20) to debounce.
4. If still LOW, invert led_latch variable.
5. Write led_latch to PA5 using HAL_GPIO_WritePin().
6. Wait in while loop until PC13 returns HIGH.

**Code Base:**

- `HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET`: Active-low press.
- `led_latch = !led_latch`: Memory state latch.
- Edge-lock loop prevents repeated state changes while held.

### 3. Inference

Each single press of button B1 cleanly toggled and latched the LED state between ON and OFF.
