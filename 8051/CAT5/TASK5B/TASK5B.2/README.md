# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 5

**DATE:** 10/08/2026

**NAME OF EXP:** Hardware Timers for PWM Waveform Generation & Stepper Motor Control

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + Timer 0 + DSO

---

## TASK 5B.2 : PWM Carrier Frequency & Duty Cycle Analysis

### 1. Circuit Diagram

The experiment demonstrates generating a stable 1 kHz PWM carrier signal with verifiable duty cycle steps (25%, 50%, 75%).

- **Development Board / Core:** 8051 Development Board
- **Microcontroller IC:** Atmel AT89S52 (40-Pin DIP)
- **GPIO Pin(s) / Peripherals:** P2.0 (PWM Output Pin)
- **Power Supply / Interface:** Digital Storage Oscilloscope (DSO)

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

A 1 kHz PWM waveform requires a 1ms total period. Timer 0 divides this period into 10 discrete slots of 100µs each, allowing precise 10% duty cycle increments.

**Pseudocode:**

1. Configure Timer 0 to interrupt every 100µs.
2. In ISR, count from 0 to 9 (1 kHz period).
3. Keep output HIGH for N slots (e.g. 5 slots = 50% duty).
4. Pull output LOW for the remainder of the period.
5. Measure pulse width and frequency on DSO.

**Code Base:**

- `pwm_tick`: Counter modulo 10.
- `duty_val`: Sets ON duration.
- DSO verifies carrier frequency = 1.00 kHz.

### 3. Inference

The PWM waveform maintained an exact 1.0 kHz frequency across all tested duty cycle settings.
