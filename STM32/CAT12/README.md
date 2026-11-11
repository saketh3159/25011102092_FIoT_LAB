# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 12

**DATE:** 19/10/2026

**NAME OF EXP:** STM32F401RE Cortex-M4: GPIO & User Input Programming

**HARDWARE SETUP / PLATFORM:** CubeMX + Keil MDK + STM32 NUCLEO-F401RE (STM32F401RET6)

---

## Overview

This experiment covers GPIO configuration on the ARM Cortex-M4 NUCLEO-F401RE board, driving on-board LED LD2 (PA5), reading blue user push-button B1 (PC13) with latching logic, and classifying press duration into short and long press events.

## Dedicated Tasks

- **[TASK 12A: User LED LD2 Bring-Up (PA5 Fixed Blink)](TASK12A/)**: Configuring PA5 as push-pull output with 500ms delay cycles for 1 Hz blinking.
- **[TASK 12B: User Push Button B1 Control with Latching State](TASK12B/)**: Debounced latching switch: each press permanently toggles the on-board LED state.
- **[TASK 12C: Press Duration Classifier (Short vs Long Press)](TASK12C/)**: Distinguishing between short presses (<1s) and long presses (>=1s) with distinct LED feedback.

### Circuit Diagram

The overall hardware schematic for Continuous Assessment 12 is shown below:

![Circuit Diagram](circuit.png)

### Inference

GPIO digital input and output control with state latching and duration timing was successfully implemented on the NUCLEO-F401RE platform.
