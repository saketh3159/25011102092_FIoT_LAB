# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 7

**DATE:** 24/08/2026

**NAME OF EXP:** HD44780 16x2 LCD Driver Development & Interactive Menu

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + HD44780 16x2 LCD + 4x4 Matrix Keypad

---

## Overview

This experiment covers interfacing an HD44780 alphanumeric LCD in 4-bit parallel mode, custom DDRAM cursor positioning, dynamic integer display, and keypad-navigated interactive multi-screen menus.

## Dedicated Tasks

- **[TASK 7A: HD44780 LCD 4-Bit Mode Driver Bring-Up](TASK7A/)**: 4-bit nibble multiplexing initialization and string display on Lines 1 and 2.
- **[TASK 7B: Cursor Positioning & Dynamic Counter](TASK7B/)**: Custom cursor positioning showing live decimal up-counter updating every second.
- **[TASK 7C: Interactive Keypad-Driven Multi-Screen Menu](TASK7C/)**: Multi-screen interactive menu navigating system diagnostics and sensor screens.

### Circuit Diagram

The overall hardware schematic for Continuous Assessment 7 is shown below:

![Circuit Diagram](circuit.png)

### Inference

The HD44780 16x2 LCD was successfully initialized in 4-bit mode, supporting dynamic real-time text updates and interactive menu navigation.
