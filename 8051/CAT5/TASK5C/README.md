# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESMENT 5

**DATE:** 10/08/2026

**NAME OF EXP:** Hardware Timers for PWM Waveform Generation & Stepper Motor Control

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + ULN2003 Driver + 28BYJ-48 Stepper Motor

---

## TASK 5C : ULN2003 Full-Step Stepper Motor Driver

### 1. Circuit Diagram

The experiment demonstrates driving a 4-phase unipolar stepper motor using a ULN2003 Darlington transistor array.

- **Development Board / Core:** 8051 Development Board
- **Microcontroller IC:** Atmel AT89S52 (40-Pin DIP)
- **GPIO Pin(s) / Peripherals:** P1.0 - P1.3 (Motor Coils A, B, C, D)
- **Power Supply / Interface:** ULN2003 Driver Board + 28BYJ-48 5V Stepper Motor

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The 28BYJ-48 stepper motor has four stator coils energized in a 4-step sequence (A -> B -> C -> D). The microcontroller outputs coil energization patterns to the ULN2003 driver, which sinks the motor coil currents.

**Pseudocode:**

1. Connect P1.0-P1.3 to ULN2003 inputs IN1-IN4.
2. Define 4-step sequence array: {0x09, 0x0C, 0x06, 0x03}.
3. Loop through step sequence.
4. Write current step pattern to Port 1.
5. Introduce delay between steps to control rotational speed.
6. Reverse sequence order to reverse motor direction.

**Code Base:**

- `code unsigned char step_seq[] = {0x09, 0x0C, 0x06, 0x03}`: Full-step pattern.
- `P1 = step_seq[step_idx]`: Energizes stator coils.
- Inter-step delay controls RPM and torque.

### 3. Inference

The stepper motor rotated smoothly in both clockwise and counter-clockwise directions with full torque retention.
