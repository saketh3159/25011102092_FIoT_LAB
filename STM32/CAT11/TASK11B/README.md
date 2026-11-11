# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 11

**DATE:** 12/10/2026

**NAME OF EXP:** HTTP Server: STM32–Wemos Wi-Fi Modem Using AT Commands

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + Wemos D1 (ESP8266)

---

## TASK 11B : HTTP Request Parser & Static HTML Response

### 1. Circuit Diagram

The experiment demonstrates receiving an HTTP GET request frame (+IPD) from a web browser and returning a formatted static HTML response.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PA9/PA10 (USART1 to ESP8266), PA2/PA3 (USART2 to PC Debug)
- **Power Supply / Interface:** Wemos D1 + Web Browser on local Wi-Fi

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

When a browser navigates to the ESP8266 IP address, the modem issues a `+IPD,<link_id>,<len>:GET / HTTP/1.1` packet. The STM32 parses the connection ID, formats HTTP 200 OK headers with an HTML payload, and transmits using two-step `AT+CIPSEND`.

**Pseudocode:**

1. Initialize TCP server on port 80.
2. Monitor USART1 stream for "+IPD," prefix.
3. Extract link_id from frame header.
4. Construct HTTP response: Status line, Content-Type, Content-Length, and HTML body.
5. Send command: AT+CIPSEND=<link_id>,<len>\r\n.
6. Wait for "> " prompt from ESP8266.
7. Send full HTTP response payload.
8. Send AT+CIPCLOSE=<link_id> to close the TCP socket.

**Code Base:**

- `+IPD` Parser: Extracts link ID and request URI.
- Two-step `CIPSEND`: Step 1 specifies byte count; Step 2 sends raw data on `>` prompt.
- HTTP body: `<html><body><h1>STM32 IoT Node</h1><p>Hello from STM32</p></body></html>`.

### 3. Inference

Opening the ESP8266 IP address in a browser successfully displayed the HTML webpage rendered directly by the STM32.
