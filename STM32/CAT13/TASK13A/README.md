# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 13

**DATE:** 26/10/2026

**NAME OF EXP:** BME280 Data Acquisition & HTTP Cloud Ingestion

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + BME280 Sensor

---

## TASK 13A : BME280 I2C Hardware Bring-Up & Bosch API Integration

### 1. Circuit Diagram

The experiment demonstrates interfacing a Bosch BME280 environmental sensor over I2C1 and reading calibrated temperature, pressure, and humidity.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PB8 (I2C1_SCL), PB9 (I2C1_SDA)
- **Power Supply / Interface:** BME280 Environmental Sensor Module (I2C address 0x76 / 0x77)

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The STM32 communicates with the BME280 via I2C at 100 kHz. Factory trimming parameters are read from sensor NVM during startup. Raw 20-bit ADC values are converted into physical units using standard Bosch integer compensation math.

**Pseudocode:**

1. Initialize I2C1 peripheral at 100 kHz.
2. Read chip ID register (0xD0) to confirm presence (expect 0x60).
3. Read calibration coefficients from registers 0x88-0xA1 and 0xE1-0xF0.
4. Configure sensor mode: Normal mode, 16x oversampling.
5. Read raw data registers 0xF7-0xFE.
6. Apply compensation formulas to calculate temperature (°C), pressure (hPa), and humidity (%RH).
7. Print values to USART2 terminal.

**Code Base:**

- `bme280.c` / `bme280.h`: Bosch official compensation library.
- `HAL_I2C_Mem_Read()` / `HAL_I2C_Mem_Write()`: I2C transaction routines.
- Sensor returns 3 calibrated environmental parameters concurrently.

### 3. Inference

Accurate real-time readings of ambient temperature, atmospheric pressure, and relative humidity were captured over I2C.
