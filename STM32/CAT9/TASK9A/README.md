# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 9

**DATE:** 28/09/2026

**NAME OF EXP:** STM32 Hardware Timer Interrupts & PWM Generation

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE

---

## TASK 9A : Timer 2 Periodic Update Interrupt (1 Hz Blink)

### 1. Circuit Diagram

The experiment demonstrates configuring hardware timer TIM2 to generate a periodic interrupt every 500ms to toggle on-board LED PA5 at 1 Hz.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PA5 (On-board Green LED LD2)
- **Power Supply / Interface:** On-board ST-LINK/V2-1 Debugger

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

TIM2 receives an 84 MHz clock. With Prescaler (PSC) = 8399, the timer clock is 10 kHz. With Auto-Reload Register (ARR) = 4999, the timer generates an update interrupt every 500ms (2 Hz). In the callback, toggling PA5 produces a 1 Hz blink.

**Pseudocode:**

1. Configure TIM2 in STM32CubeMX: Prescaler = 8399, Counter Period = 4999.
2. Enable TIM2 global interrupt in NVIC.
3. In main(), start timer with HAL_TIM_Base_Start_IT(&htim2).
4. Implement HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim).
5. If htim == &htim2, toggle PA5 using HAL_GPIO_TogglePin().
6. Main while(1) loop remains completely free for other tasks.

**Code Base:**

- `HAL_TIM_Base_Start_IT(&htim2)`: Enables timer with interrupts.
- `HAL_TIM_PeriodElapsedCallback()`: HAL interrupt service hook.
- $T = \frac{(PSC+1) \times (ARR+1)}{f_{clk}} = \frac{8400 \times 5000}{84\text{ MHz}} = 0.5\text{ s}$.

### 3. Inference

The LED toggled at an exact 1.000 Hz frequency without utilizing CPU blocking delays.
