# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 13

**DATE:** 26/10/2026

**NAME OF EXP:** BME280 Data Acquisition & HTTP Cloud Ingestion

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + BME280 + ESP8266

---

## TASK 13B : Dynamic JSON Payload Generation & HTTP POST Transmission

### 1. Circuit Diagram

The experiment demonstrates formatting environmental sensor readings into JSON strings and transmitting HTTP POST requests to an IoT cloud server.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PB8/PB9 (I2C1 - BME280), PA9/PA10 (USART1 - ESP8266)
- **Power Supply / Interface:** BME280 + Wemos D1 WiFi Module

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Environmental readings acquired from the BME280 are serialized into a lightweight JSON payload. The STM32 sends AT commands to the ESP8266 to open a TCP connection to the cloud server, transmits the HTTP POST request, and reads the server ACK.

**Pseudocode:**

1. Read temperature, pressure, and humidity from BME280.
2. Format JSON: {"temp":24.5,"press":1013.2,"hum":60.1}.
3. Construct HTTP POST headers with Host and Content-Length.
4. Connect to server: AT+CIPSTART="TCP","<server_ip>",1880.
5. Send AT+CIPSEND with total packet length.
6. Transmit HTTP POST headers and JSON payload.
7. Receive HTTP 200 OK server response and close connection.

**Code Base:**

- JSON payload serialization using `snprintf()`.
- HTTP POST formatting: headers, blank line, payload.
- Automated connection establishment and teardown via ESP8266.

### 3. Inference

Sensor telemetry was successfully formatted into valid JSON and transmitted over HTTP to the ingestion server.
