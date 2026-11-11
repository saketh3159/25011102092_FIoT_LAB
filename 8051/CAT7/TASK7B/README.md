# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 7

**DATE:** 24/08/2026

**NAME OF EXP:** HD44780 16x2 LCD Driver Development & Interactive Menu

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + HD44780 16x2 LCD

---

## TASK 7B : Cursor Positioning & Dynamic Counter

### 1. Circuit Diagram

The experiment demonstrates cursor positioning commands and displaying a dynamic decimal counter updating every second.

- **Development Board / Core:** 8051 Development Board
- **Microcontroller IC:** Atmel AT89S52 (40-Pin DIP)
- **GPIO Pin(s) / Peripherals:** Port 2 (P2.0: RS, P2.1: RW, P2.2: EN, P2.4-P2.7: D4-D7)
- **Power Supply / Interface:** HD44780 16x2 LCD Display

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The LCD DDRAM address for Line 1 starts at 0x80 and Line 2 starts at 0xC0. Setting DDRAM address moves the cursor to specific coordinates. Integer values are converted to ASCII strings and written to fixed display locations.

**Pseudocode:**

1. Initialize LCD in 4-bit mode.
2. Position cursor at Line 1, Column 0: print static label "COUNT: ".
3. In a loop, format current integer value as decimal string.
4. Position cursor at Line 2, Column 0: print the updated value.
5. Delay 1000 milliseconds.
6. Increment counter and repeat.

**Code Base:**

- `lcd_set_cursor(row, col)`: Calculates DDRAM address (`0x80` or `0xC0` + col).
- `sprintf()` / integer-to-string conversion converts count to characters.
- Refreshing only numeric digits eliminates screen flicker.

### 3. Inference

The display accurately updated the decimal counter value every second at the specified LCD screen coordinate.
