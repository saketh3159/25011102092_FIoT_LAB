# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 14

**DATE:** 02/11/2026

**NAME OF EXP:** Environmental Sensing (BME280) & MQTT Cloud Analytics

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + BME280 Sensor

---

## TASK 14A : BME280 I2C Environmental Sensing & Compensation

### 1. Circuit Diagram

The experiment demonstrates low-level I2C register configuration and 64-bit fixed-point compensation algorithms for the Bosch BME280 sensor.

- **Development Board / Core:** STM32 NUCLEO-F401RE
- **Microcontroller IC:** STM32F401RET6 (ARM Cortex-M4 @ 84 MHz)
- **GPIO Pin(s) / Peripherals:** PB8 (I2C1_SCL), PB9 (I2C1_SDA)
- **Power Supply / Interface:** BME280 Environmental Sensor Module

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The BME280 uses factory-calibrated trim parameters to linearize raw ADC counts. The firmware reads registers 0x88 through 0xA1 and implements 64-bit integer compensation math to compute pressure to 1/256 Pa and humidity to 1/1024 %RH resolution.

**Pseudocode:**

1. Verify sensor ID register 0xD0 equals 0x60.
2. Read 24 calibration parameters from non-volatile memory.
3. Set humidity oversampling (ctrl_hum = 0x01).
4. Set temperature and pressure oversampling and normal power mode (ctrl_meas = 0x27).
5. Perform burst read of 8 data registers (0xF7-0xFE).
6. Apply 64-bit integer arithmetic to calculate compensated values.
7. Output high-resolution data to serial debug terminal.

**Code Base:**

- `BME280_compensate_T_int32()`: Temperature compensation.
- `BME280_compensate_P_int64()`: 64-bit pressure compensation formula.
- `BME280_compensate_H_int32()`: Relative humidity compensation formula.

### 3. Inference

High-resolution, calibrated environmental measurements were produced with industrial measurement accuracy.
