# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 12

**DATE:** 19/10/2026

**NAME OF EXP:** STM32F401RE Cortex-M4: GPIO & User Input Programming

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE

---

## TASK 12C : Press Duration Classifier (Short vs Long Press)

### 1. Circuit Diagram

The experiment demonstrates measuring push-button hold duration on PC13 to classify between short presses (<1s) and long presses (>=1s).

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PC13 (Blue Button B1), PA5 (Green LED LD2)
- **Power Supply / Interface:** On-board Peripherals

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

When B1 is pressed, the start tick is captured via `HAL_GetTick()`. When released, duration is computed. A short press (<1000ms) toggles LED LD2 steadily, while a long press (>=1000ms) triggers rapid 5 Hz flashing for 2 seconds.

**Pseudocode:**

1. Wait for PC13 to go LOW.
2. Record t_start = HAL_GetTick().
3. Wait for PC13 to return HIGH.
4. Compute duration = HAL_GetTick() - t_start.
5. If duration < 1000: toggle PA5.
6. Else (duration >= 1000): flash PA5 rapidly 10 times at 100ms intervals.
7. Repeat loop.

**Code Base:**

- `HAL_GetTick()`: System timer tick counter.
- Duration comparison threshold = 1000ms.
- Rapid flash loop provides clear visual feedback for long press.

### 3. Inference

Short clicks reliably toggled the LED, while holds longer than 1 second initiated the rapid flash sequence.
