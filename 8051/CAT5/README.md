# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 5

**DATE:** 10/08/2026

**NAME OF EXP:** Hardware Timers for PWM Waveform Generation & Stepper Motor Control

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + Timer 0 + ULN2003 Driver + 28BYJ-48 Stepper Motor + DSO

---

## Overview

This experiment covers 8051 hardware timer configuration, periodic interrupt service routines (ISR), software PWM generation with variable duty cycle, and four-phase stepper motor driving.

## Dedicated Tasks

- **[TASK 5A: 1ms Timer 0 Mode 1 Periodic ISR Driver](TASK5A/)**: Hardware Timer 0 configured in 16-bit mode generating periodic 1ms ticks.
- **[TASK 5B.1: Software PWM Triangular Wave Modulation](TASK5B/TASK5B.1/)**: PWM duty cycle ramp up and down creating a triangular intensity modulation.
- **[TASK 5B.2: PWM Carrier Frequency & Duty Cycle Analysis](TASK5B/TASK5B.2/)**: Fixed 1 kHz carrier PWM generation with oscilloscope measurement.
- **[TASK 5B.3: Multi-LED Breathing Controller](TASK5B/TASK5B.3/)**: Multi-phase soft-breathing LED animation using phased PWM signals.
- **[TASK 5C: ULN2003 Full-Step Stepper Motor Driver](TASK5C/)**: Four-step wave drive sequence rotating a 28BYJ-48 stepper motor.

### Circuit Diagram

The overall hardware schematic for Continuous Assessment 5 is shown below:

![Circuit Diagram](circuit.png)

### Inference

Hardware Timer 0 interrupts provided accurate non-blocking timebases for software PWM duty modulation and precise stepper motor rotation.
