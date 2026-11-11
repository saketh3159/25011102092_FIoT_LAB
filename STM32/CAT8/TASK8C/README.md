# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 8

**DATE:** 21/09/2026

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED

**HARDWARE SETUP / PLATFORM:** CubeMX + Keil MDK + STM32 Blue Pill STM32F103C8T6

---

## TASK 8C : Button Press Duration Classifier

### 1. Circuit Diagram

The experiment demonstrates measuring button press duration to distinguish between short presses (<1s) and long presses (>1s).

- **Development Board / Core:** STM32 Blue Pill
- **Microcontroller IC:** STM32F103C8T6 (ARM Cortex-M3 @ 72 MHz)
- **GPIO Pin(s) / Peripherals:** PC13 (Onboard LED), PA0 (Push Button with Pull-Up)
- **Power Supply / Interface:** 3.3V DC Supply

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

When PA0 goes LOW, the firmware captures a timestamp using `HAL_GetTick()`. When the button is released, the elapsed time is calculated: if duration < 1000ms, the LED toggles once; if duration >= 1000ms, the LED performs rapid blinking.

**Pseudocode:**

1. Initialize HAL and configure PC13 as output, PA0 as input.
2. Wait for PA0 to go LOW (press detected).
3. Record start_time = HAL_GetTick().
4. Wait for PA0 to return HIGH (release detected).
5. Calculate press_duration = HAL_GetTick() - start_time.
6. If press_duration < 1000ms: toggle LED state.
7. Else (>= 1000ms): flash LED rapidly 5 times to signal long press.

**Code Base:**

- `HAL_GetTick()`: 1ms resolution SysTick counter.
- `press_duration = release_time - press_time`: Hold-time calculation.
- Conditional branching executes different behaviors based on duration threshold.

### 3. Inference

The system accurately categorized short clicks and long holds, triggering corresponding visual feedback.
