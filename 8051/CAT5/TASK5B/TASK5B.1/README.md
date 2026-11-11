# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 5

**DATE:** 10/08/2026

**NAME OF EXP:** Hardware Timers for PWM Waveform Generation & Stepper Motor Control

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + Timer 0 + LED

---

## TASK 5B.1 : Software PWM Triangular Wave Modulation

### 1. Circuit Diagram

The experiment demonstrates software PWM duty cycle modulation linearly increasing and decreasing to produce a triangular intensity ramp.

- **Development Board / Core:** 8051 Development Board
- **Microcontroller IC:** Atmel AT89S52 (40-Pin DIP)
- **GPIO Pin(s) / Peripherals:** P2.0 (PWM Output LED)
- **Power Supply / Interface:** LED with 330Ω Resistor

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Timer 0 generates a high-frequency timebase. An internal PWM counter (0 to 100) compares against a target duty cycle. The duty cycle ramps from 0% to 100% and back down to 0% continuously.

**Pseudocode:**

1. Configure Timer 0 for 100µs periodic interrupts.
2. In ISR, increment pwm_counter (0 to 99).
3. If pwm_counter < duty_cycle, set LED ON; else set LED OFF.
4. In main loop, increment duty_cycle from 0 to 100, then decrement from 100 to 0.
5. Repeat to produce smooth breathing effect.

**Code Base:**

- `unsigned char duty_cycle`: Controls pulse width.
- `unsigned char pwm_counter`: Fast carrier counter.
- Linear ramp generates smooth visual brightness modulation.

### 3. Inference

The LED brightness smoothly modulated between minimum and maximum following a linear triangular envelope.
