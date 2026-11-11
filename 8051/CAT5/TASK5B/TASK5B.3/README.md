# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 5

**DATE:** 10/08/2026

**NAME OF EXP:** Hardware Timers for PWM Waveform Generation & Stepper Motor Control

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + Timer 0 + 4 LEDs

---

## TASK 5B.3 : Multi-LED Breathing Controller

### 1. Circuit Diagram

The experiment demonstrates multi-channel software PWM creating phased breathing effects across four LEDs.

- **Development Board / Core:** 8051 Development Board
- **Microcontroller IC:** Atmel AT89S52 (40-Pin DIP)
- **GPIO Pin(s) / Peripherals:** P2.0 - P2.3 (4 Output LEDs)
- **Power Supply / Interface:** 4 LEDs with 330Ω Current-Limiting Resistors

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Four independent software PWM channels are updated inside the Timer 0 ISR. Each LED runs with a 90-degree phase offset in its brightness envelope, creating a fluid wave animation.

**Pseudocode:**

1. Initialize Timer 0 for 100µs interrupts.
2. Maintain 4 duty cycle variables: duty1, duty2, duty3, duty4.
3. In main loop, update duty cycles with phase differences.
4. In ISR, compare each duty cycle against master counter and update P2.0-P2.3.
5. Repeat indefinitely.

**Code Base:**

- `duty[4]`: Array of duty cycles for 4 LEDs.
- Phase shift formula creates cascading illumination.

### 3. Inference

All 4 LEDs displayed a smooth, synchronized phase-shifted breathing pattern without visual flicker.
