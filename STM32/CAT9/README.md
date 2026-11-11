# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 9

**DATE:** 28/09/2026

**NAME OF EXP:** STM32 Hardware Timer Interrupts & PWM Generation

**HARDWARE SETUP / PLATFORM:** CubeMX + Keil MDK + STM32 NUCLEO-F401RE (ARM Cortex-M4 @ 84 MHz) + DSO

---

## Overview

This experiment covers configuring STM32 hardware timers (TIM2) in STM32CubeMX, implementing non-blocking periodic timer interrupts at 1 Hz, and generating hardware PWM signals with adjustable duty cycle.

## Dedicated Tasks

- **[TASK 9A: Timer 2 Periodic Update Interrupt (1 Hz Blink)](TASK9A/)**: Hardware timer TIM2 update interrupt generating exact 1 Hz non-blocking LED blink.
- **[TASK 9B: Timer 2 PWM Generation with Variable Duty Cycle](TASK9B/)**: Hardware PWM on TIM2 Channel 1 producing 1 kHz pulses with variable duty.

### Circuit Diagram

The overall hardware schematic for Continuous Assessment 9 is shown below:

![Circuit Diagram](circuit.png)

### Inference

Hardware timer interrupts and hardware PWM generation were successfully verified on the STM32F401RE NUCLEO board using a digital oscilloscope.
