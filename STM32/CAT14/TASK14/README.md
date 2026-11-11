# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 14

**DATE:** 02/11/2026

**NAME OF EXP:** Environmental Sensing (BME280) & MQTT Cloud Analytics

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + BME280 + ESP8266 + MQTT Broker

---

## TASK 14 : Integrated Smart Edge Node (BME280 - MQTT Client)

### 1. Circuit Diagram

The experiment demonstrates an integrated smart IoT edge device acquiring BME280 sensor metrics and publishing MQTT telemetry to a public broker.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PB8/PB9 (I2C1 - BME280), PA9/PA10 (USART1 - ESP8266), PA2/PA3 (USART2 - PC)
- **Power Supply / Interface:** broker.emqx.io (TCP Port 1883) + Wi-Fi "SNUC"

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The firmware integrates I2C sensor acquisition, Bosch compensation, JSON payload formulation, and the ESPLib AT command driver. It connects to broker.emqx.io and publishes live telemetry to `stm32/test/data` every 10 seconds.

**Pseudocode:**

1. Initialize I2C1 and USART peripherals.
2. Bring up BME280 sensor and read calibration coefficients.
3. Connect ESP8266 to Wi-Fi SSID "SNUC".
4. Connect MQTT client to broker "broker.emqx.io" on port 1883.
5. In loop: read BME280, formulate JSON payload, publish to topic stm32/test/data.
6. Verify message receipt in Node-RED MQTT Subscriber or MQTTX tool.
7. Repeat every 10 seconds.

**Code Base:**

- `ESPLib.c` / `ESPLib.h`: Modem interface and MQTT client abstraction.
- `broker.emqx.io`: Public MQTT message broker.
- Topic: `stm32/test/data`.
- Payload: `{"temp": 24.3, "hum": 58.5, "press": 1012.8, "node": "STM32"}`.

### 3. Inference

The integrated edge node published continuous real-time environmental telemetry to the cloud with zero message drops.
