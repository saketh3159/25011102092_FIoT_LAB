# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 7

**DATE:** 24/08/2026

**NAME OF EXP:** HD44780 16x2 LCD Driver Development & Interactive Menu

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + HD44780 16x2 LCD + 4x4 Keypad

---

## TASK 7C : Interactive Keypad-Driven Multi-Screen Menu

### 1. Circuit Diagram

The experiment demonstrates an interactive menu system on the 16x2 LCD navigated via keypad inputs.

- **Development Board / Core:** 8051 Development Board
- **Microcontroller IC:** Atmel AT89S52 (40-Pin DIP)
- **GPIO Pin(s) / Peripherals:** P2 (LCD Interface), P1 (4x4 Matrix Keypad)
- **Power Supply / Interface:** HD44780 LCD + 4x4 Keypad

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The keypad keys 1, 2, and 3 select between distinct display screens: Screen 1 shows "System Status: OK", Screen 2 shows "Sensor Mode: ACTIVE", and Screen 3 shows "Diagnostic: PASS". Pressing key 0 clears the display.

**Pseudocode:**

1. Initialize LCD and matrix keypad.
2. Display default welcome message on Line 1 and Line 2.
3. Poll keypad for user keypress.
4. When key is pressed:
   - Key 1: Clear screen, display Screen 1 (System Status).
   - Key 2: Clear screen, display Screen 2 (Sensor Mode).
   - Key 3: Clear screen, display Screen 3 (Diagnostics).
5. Repeat loop continuously.

**Code Base:**

- `current_screen`: Tracks active menu index.
- `keypad_scan()`: Detects menu selection.
- `lcd_clear()`: Clears screen before drawing new view.

### 3. Inference

Keypad inputs instantly transitioned the LCD between multiple informative menu pages.
