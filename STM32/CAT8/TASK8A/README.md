# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 8

**DATE:** 21/09/2026

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED

**HARDWARE SETUP / PLATFORM:** CubeMX + Keil MDK + STM32 Blue Pill STM32F103C8T6

---

## TASK 8A : GPIO Direct Follow Mode

### 1. Circuit Diagram

The experiment demonstrates configuring an onboard LED and external push button so that the LED directly follows the button state.

- **Development Board / Core:** STM32 Blue Pill
- **Microcontroller IC:** STM32F103C8T6 (ARM Cortex-M3 @ 72 MHz)
- **GPIO Pin(s) / Peripherals:** PC13 (Onboard Active-Low LED), PA0 (Push Button with Pull-Up)
- **Power Supply / Interface:** 3.3V DC Power Supply

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The PC13 pin is configured as a push-pull digital output. PA0 is configured as a digital input with an internal pull-up resistor. The microcontroller continuously polls PA0 and writes the exact corresponding state to PC13.

**Pseudocode:**

1. Initialize HAL library using HAL_Init().
2. Configure system clock to 72 MHz using SystemClock_Config().
3. Configure PC13 as GPIO_MODE_OUTPUT_PP.
4. Configure PA0 as GPIO_MODE_INPUT with GPIO_PULLUP.
5. In while(1): read pin PA0 using HAL_GPIO_ReadPin().
6. Write state to PC13 using HAL_GPIO_WritePin().
7. Repeat continuously.

**Code Base:**

- `HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)`: Reads button logic state.
- `HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, state)`: Writes to active-low LED.
- Zero software latency between switch engagement and LED response.

### 3. Inference

The onboard LED instantly illuminates when the push button is held down and turns off upon release.
