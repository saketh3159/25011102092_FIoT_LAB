# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 12

**DATE:** 19/10/2026

**NAME OF EXP:** STM32F401RE Cortex-M4: GPIO & User Input Programming

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE

---

## TASK 12A : User LED LD2 Bring-Up (PA5 Fixed Blink)

### 1. Circuit Diagram

The experiment demonstrates configuring on-board green LED LD2 on pin PA5 as a push-pull digital output blinking at 1 Hz.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PA5 (On-board Green LED LD2)
- **Power Supply / Interface:** Integrated ST-LINK/V2-1 Debugger

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

PA5 is initialized as a general-purpose push-pull output with no pull-up/pull-down. The superloop toggles the pin state and introduces a 500ms delay using `HAL_Delay(500)`.

**Pseudocode:**

1. Initialize HAL and configure system clock to 84 MHz.
2. Configure PA5 as GPIO_MODE_OUTPUT_PP, speed LOW, no pull.
3. In while(1) loop:
4. Call HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5).
5. Call HAL_Delay(500).
6. Repeat continuously.

**Code Base:**

- `HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)`: Inverts output state.
- `HAL_Delay(500)`: 500ms SysTick delay.

### 3. Inference

The green LED LD2 blinked steadily at 1 Hz, confirming basic GPIO output configuration on the NUCLEO board.
