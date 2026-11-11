# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 10

**DATE:** 05/10/2026

**NAME OF EXP:** STM32 USART Serial Communication Modes

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + PC Terminal

---

## TASK 10B : USART2 Interrupt-Driven Bidirectional Echo

### 1. Circuit Diagram

The experiment demonstrates asynchronous, non-blocking serial reception using USART interrupts and immediate echoing of received characters.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PA2 (USART2_TX), PA3 (USART2_RX)
- **Power Supply / Interface:** ST-LINK Virtual COM Port @ 115200 8-N-1

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Rather than holding the CPU in a polling loop, `HAL_UART_Receive_IT()` enables the USART RXNE interrupt. When a key is struck in the terminal, the interrupt fires, calls the HAL callback, stores the byte, echoes it back, and re-arms the receiver.

**Pseudocode:**

1. Enable USART2 global interrupt in NVIC via CubeMX.
2. In main(), arm the receiver using HAL_UART_Receive_IT(&huart2, &rx_char, 1).
3. When byte arrives, hardware calls HAL_UART_RxCpltCallback().
4. In callback, transmit echoed character back using HAL_UART_Transmit().
5. Re-call HAL_UART_Receive_IT() to await next character.
6. Main loop continuously toggles LED LD2 independently.

**Code Base:**

- `HAL_UART_Receive_IT(&huart2, &rx_char, 1)`: Arms 1-byte interrupt.
- `HAL_UART_RxCpltCallback()`: Interrupt handler re-arming receiver.
- Full duplex operation keeps foreground tasks active.

### 3. Inference

Terminal keystrokes were echoed instantaneously while the on-board LED blinked continuously in the background.
