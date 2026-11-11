# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 3

**DATE:** 27/07/2026

**NAME OF EXP:** Timer-Based LED Pattern Generator & Push-Button Controller

**HARDWARE SETUP / PLATFORM:** 8051 Microcontroller (AT89S52) + 4 LEDs + Active-Low Push Button

---

## Overview

This experiment covers GPIO input reading, push-button debouncing, and multi-mode pattern sequencing including binary counting, alternating blink, and synchronous flash.

## Dedicated Tasks

- **[TASK 3A: Multi-Mode Switch Controller](TASK3A/)**: Switch-controlled mode selection cycling through patterns.
- **[TASK 3B: 4-Bit Binary Counter](TASK3B/)**: Sequential 4-bit binary up-counting from 0x0 to 0xF on LEDs.
- **[TASK 3C: Alternating LED Pattern](TASK3C/)**: Odd-even alternating LED flashing pattern.
- **[TASK 3D: All-LED Synchronous Flash](TASK3D/)**: Synchronous all-LED flash with variable duty cycle.

### Circuit Diagram

The overall hardware schematic for Continuous Assessment 3 is shown below:

![Circuit Diagram](circuit.png)

### Inference

GPIO input reading with switch debouncing was successfully implemented to cycle through diverse LED display patterns.
