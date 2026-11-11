# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 4

**DATE:** 03/08/2026

**NAME OF EXP:** Human-Machine Interface using Matrix Keypad, LEDs & 7-Segment Display

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 4x4 Keypad + 4 LEDs

---

## TASK 4C : Keypad-Controlled LED Patterns

### 1. Circuit Diagram

The experiment demonstrates triggering distinct LED animation patterns on Port 2 using inputs from the 4x4 matrix keypad.

- **Development Board / Core:** 8051 Development Board
- **Microcontroller IC:** Atmel AT89S52 (40-Pin DIP)
- **GPIO Pin(s) / Peripherals:** P1 (4x4 Keypad), P2.0 - P2.3 (4 Output LEDs)
- **Power Supply / Interface:** 4x4 Keypad + 4 LEDs with 330Ω Resistors

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The microcontroller continuously polls the matrix keypad. Pressing key 1 triggers a binary counter, key 2 triggers alternating blink, key 3 triggers synchronous flash, and key 4 turns all LEDs off.

**Pseudocode:**

1. Initialize keypad on Port 1 and LEDs on Port 2.
2. In superloop, scan keypad for active key.
3. If key is detected, branch to corresponding animation function:
   - Key 1: Binary count pattern.
   - Key 2: Alternating odd/even blink.
   - Key 3: Synchronous flashing.
   - Key 4: All LEDs OFF.
4. Repeat continuously.

**Code Base:**

- `keypad_scan()`: Scans Port 1 for button press.
- Switch-case branches to selected LED pattern routine on Port 2.
- Debouncing prevents erratic triggering on key release.

### 3. Inference

Interactive user input via the keypad directly controlled multiple dynamic LED sequences.
