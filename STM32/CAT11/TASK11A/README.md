# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 11

**DATE:** 12/10/2026

**NAME OF EXP:** HTTP Server: STM32–Wemos Wi-Fi Modem Using AT Commands

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + Wemos D1 (ESP8266)

---

## TASK 11A : ESP8266 TCP Server Configuration via AT Commands

### 1. Circuit Diagram

The experiment demonstrates configuring an ESP8266 Wi-Fi module as a TCP server listening on port 80 using automated AT commands.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PA9/PA10 (USART1 to ESP8266), PA2/PA3 (USART2 to PC Debug), PA5 (LED LD2)
- **Power Supply / Interface:** Wemos D1 WiFi Module + 3.3V/5V Supply

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The STM32 sends AT command packets over USART1 to configure the ESP8266 into Station mode, connect to Wi-Fi SSID "SNUC", enable multiple socket connections (`AT+CIPMUX=1`), and launch the TCP server on port 80 (`AT+CIPSERVER=1,80`).

**Pseudocode:**

1. Send AT to confirm communication.
2. Send AT+CWMODE=1 to set station mode.
3. Send AT+CWJAP="SNUC","snu12345" to connect to Wi-Fi.
4. Send AT+CIFSR to retrieve allocated IP address.
5. Send AT+CIPMUX=1 to allow multiple incoming connections.
6. Send AT+CIPSERVER=1,80 to start TCP server on port 80.
7. Light on-board LED LD2 when server is active.

**Code Base:**

- `AT+CIPMUX=1`: Required for multi-client TCP server operation.
- `AT+CIPSERVER=1,80`: Starts HTTP daemon on standard port 80.
- Diagnostic logs output to USART2 ST-LINK terminal at 115200 baud.

### 3. Inference

The ESP8266 connected to Wi-Fi, obtained an IP address, and began listening for TCP connections on port 80.
