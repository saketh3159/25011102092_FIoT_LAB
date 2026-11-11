# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 8

**DATE:** 21/09/2026

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED

**HARDWARE SETUP / PLATFORM:** CubeMX + Keil MDK + STM32 Blue Pill STM32F103C8T6

---

## TASK 8B : Software Debounced Toggle Mode

### 1. Circuit Diagram

The experiment demonstrates edge-detection and software debouncing to toggle the onboard LED on each button press.

- **Development Board / Core:** STM32 Blue Pill
- **Microcontroller IC:** STM32F103C8T6 (ARM Cortex-M3 @ 72 MHz)
- **GPIO Pin(s) / Peripherals:** PC13 (Onboard LED), PA0 (Push Button with Pull-Up)
- **Power Supply / Interface:** 3.3V DC Supply

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Mechanical switches suffer from contact bounce lasting several milliseconds. The firmware detects a high-to-low falling edge on PA0, introduces a 20ms debounce delay, confirms the state, toggles the LED, and waits for button release.

**Pseudocode:**

1. Initialize HAL library and system clocks.
2. Configure PC13 as output and PA0 as input with pull-up.
3. Poll PA0 for transition from HIGH to LOW.
4. When falling edge detected, call HAL_Delay(20) to debounce.
5. Confirm button is still LOW, then toggle PC13 using HAL_GPIO_TogglePin().
6. Wait in loop while PA0 remains LOW to prevent multiple toggles on a single press.

**Code Base:**

- `HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13)`: Inverts output state.
- `HAL_Delay(20)`: Filters out high-frequency mechanical contact vibrations.
- While-loop lock ensures single-toggle per physical press.

### 3. Inference

The LED toggled cleanly on each individual button press with zero false double-triggers.
