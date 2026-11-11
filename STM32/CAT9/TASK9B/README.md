# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 9

**DATE:** 28/09/2026

**NAME OF EXP:** STM32 Hardware Timer Interrupts & PWM Generation

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + DSO

---

## TASK 9B : Timer 2 PWM Generation with Variable Duty Cycle

### 1. Circuit Diagram

The experiment demonstrates configuring TIM2 in PWM mode on Channel 1 to produce a 1 kHz square wave with adjustable pulse width.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PA0 (TIM2_CH1 PWM Output Pin)
- **Power Supply / Interface:** Digital Storage Oscilloscope (DSO)

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

TIM2 is configured for PWM Generation Channel 1 on pin PA0. With PSC = 83 and ARR = 999, the carrier frequency is 84 MHz / (84 * 1000) = 1 kHz. Setting the Capture/Compare Register (CCR1) adjusts duty cycle ($D = CCR1 / (ARR+1)$).

**Pseudocode:**

1. Configure TIM2 Channel 1 in CubeMX for PWM Generation.
2. Set PSC = 83, ARR = 999 (1 kHz carrier frequency).
3. Start PWM generation using HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1).
4. In superloop, ramp CCR1 from 100 (10%) to 900 (90%) in steps.
5. Connect PA0 to DSO probe and observe pulse width variation.

**Code Base:**

- `HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1)`: Starts PWM on PA0.
- `__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ccr_val)`: Updates duty cycle.
- Fully hardware-driven: CPU load is zero during waveform output.

### 3. Inference

The DSO confirmed a precise 1.00 kHz carrier frequency with duty cycle stepping cleanly between 10% and 90%.
