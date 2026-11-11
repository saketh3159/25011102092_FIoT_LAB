# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 7

**DATE:** 24/08/2026

**NAME OF EXP:** HD44780 16x2 LCD Driver Development & Interactive Menu

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + HD44780 16x2 LCD

---

## TASK 7A : HD44780 LCD 4-Bit Mode Driver Bring-Up

### 1. Circuit Diagram

The experiment demonstrates configuring an HD44780 alphanumeric LCD in 4-bit data bus mode to display text strings.

- **Development Board / Core:** 8051 Development Board
- **Microcontroller IC:** Atmel AT89S52 (40-Pin DIP)
- **GPIO Pin(s) / Peripherals:** P2.4 - P2.7 (Data D4-D7), P2.0 (RS), P2.1 (RW), P2.2 (EN)
- **Power Supply / Interface:** HD44780 16x2 Alphanumeric LCD + 10kΩ Contrast Potentiometer

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

4-bit mode saves microcontroller GPIO pins by transferring 8-bit commands and data in two successive 4-bit nibbles (higher nibble first, then lower nibble), latched on a high-to-low pulse on the EN pin.

**Pseudocode:**

1. Wait 50ms after power-on for LCD internal reset.
2. Send initialization nibble sequence: 0x03, 0x03, 0x03, 0x02.
3. Send Function Set command (0x28: 4-bit, 2-line, 5x8 font).
4. Send Display ON, Cursor OFF command (0x0C).
5. Clear display (0x01).
6. Send ASCII string characters to DDRAM and display.

**Code Base:**

- `lcd_cmd()`: Sends command byte with RS = 0.
- `lcd_data()`: Sends character byte with RS = 1.
- `lcd_send_nibble()`: Latches 4 bits with EN pulse.
- `lcd_print(char *str)`: Displays text string.

### 3. Inference

Text displayed clearly on both Line 1 and Line 2 with optimal contrast and no character corruption.
