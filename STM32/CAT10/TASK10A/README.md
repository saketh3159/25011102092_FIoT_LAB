# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 10

**DATE:** 05/10/2026

**NAME OF EXP:** STM32 USART Serial Communication Modes

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + PC Terminal

---

## TASK 10A : USART2 Polling String Transmission

### 1. Circuit Diagram

The experiment demonstrates transmitting text strings to a PC serial terminal over USART2 using HAL polling functions.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PA2 (USART2_TX), PA3 (USART2_RX)
- **Power Supply / Interface:** ST-LINK Virtual COM Port @ 115200 8-N-1

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

USART2 is wired internally to the NUCLEO ST-LINK/V2-1 interface, creating a Virtual COM Port on the host PC. Strings are sent synchronously using `HAL_UART_Transmit()` which blocks until all characters have passed through the TX shift register.

**Pseudocode:**

1. Configure USART2 in CubeMX: 115200 baud, 8 data bits, no parity, 1 stop bit.
2. In main(), format welcome message banner string.
3. Call HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 1000).
4. In while(1) loop, transmit periodic timestamped message every second.
5. Open PuTTY on host PC connected to ST-LINK COM port.

**Code Base:**

- `huart2.Instance = USART2`.
- `HAL_UART_Transmit(&huart2, buffer, len, timeout)`: Polled transmission.
- `sprintf()`: Formats dynamic text with system tick values.

### 3. Inference

Serial strings were received cleanly in PuTTY at 115200 baud with no framing or baud-rate mismatch errors.
