# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 8

**DATE:** 21/09/2026

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED

**HARDWARE SETUP / PLATFORM:** CubeMX + Keil MDK + STM32 Development Board Blue Pill STM32F103C8T6

---

## Overview

This experiment covers initial GPIO bring-up on the ARM Cortex-M3 STM32F103C8T6 Blue Pill board, configuring pins with STM32CubeMX, and implementing direct follow, software debounced toggle, and button press duration classification modes.

## Dedicated Tasks

- **[TASK 8A: GPIO Direct Follow Mode](TASK8A/)**: Direct mapping where onboard LED PC13 directly mirrors the state of button PA0.
- **[TASK 8B: Software Debounced Toggle Mode](TASK8B/)**: Edge-triggered button toggle with 20ms debounce filtering to eliminate contact bounce.
- **[TASK 8C: Button Press Duration Classifier](TASK8C/)**: Timing button hold duration: short press (<1s) toggles LED, long press (>1s) initiates blinking.

### Circuit Diagram

The overall hardware schematic for Continuous Assessment 8 is shown below:

![Circuit Diagram](circuit.png)

### Inference

GPIO digital input and output control using STM32 HAL functions was successfully established on the STM32F103C8T6 Blue Pill platform.
