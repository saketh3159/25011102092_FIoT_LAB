# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 10

**DATE:** 05/10/2026

**NAME OF EXP:** STM32 USART Serial Communication Modes

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + Wemos D1 WiFi Module + PC Terminal

---

## TASK 10C : Dual-UART Transparent Bridge & Provisioning Engine

### 1. Circuit Diagram

The experiment demonstrates a dual-UART bridging engine connecting a PC debug console (USART2) and an ESP8266 Wi-Fi modem (USART1).

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PA2/PA3 (USART2 - PC Debug), PA9/PA10 (USART1 - ESP8266 Modem)
- **Power Supply / Interface:** Wemos D1 (ESP8266) @ 115200 Baud + ST-LINK VCP

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The STM32 acts as a transparent router. Characters received from PC (USART2) are forwarded to ESP8266 (USART1), and responses from ESP8266 are forwarded to PC. The firmware also executes an initial automated AT provisioning sequence.

**Pseudocode:**

1. Initialize USART1 and USART2 at 115200 baud.
2. Automated state machine transmits AT commands: AT, AT+CWMODE=1, AT+CWJAP.
3. Once Wi-Fi is connected, transition to transparent passthrough mode.
4. If byte arrives on huart1, forward to huart2.
5. If byte arrives on huart2, forward to huart1.
6. Observe AT command responses live on PC terminal.

**Code Base:**

- `huart1`: Communicates with ESP8266 on PA9/PA10.
- `huart2`: Communicates with PC on PA2/PA3.
- State machine steps through AT initialization before opening transparent bridge.

### 3. Inference

Bidirectional communication between the PC terminal and ESP8266 modem operated seamlessly with real-time command response.
