/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 5 - TASK 5C: Stepper Motor Full-Step Sequence Generator
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : 28BYJ-48 4-Phase Stepper Motor via ULN2003 on Port 2 (P2.0-P2.3)
 ******************************************************************************
 */

#include <reg52.h>

/* Port Definition: Stepper Motor Coils A, B, C, D connected to P2.0 - P2.3 */
#define STEPPER_PORT P2

/**
 * @brief  Calibrated millisecond delay function
 */
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 120; j++)
        {
            /* ~1 ms */
        }
    }
}

/**
 * 4-Step Full-Step Stepper Excitation Sequence
 * Step 1: Coil A & Coil D ON -> 0x09 (0b00001001)
 * Step 2: Coil A & Coil B ON -> 0x0C (0b00001100)
 * Step 3: Coil B & Coil C ON -> 0x06 (0b00000110)
 * Step 4: Coil C & Coil D ON -> 0x03 (0b00000011)
 */
const unsigned char full_step_seq[4] = {0x09, 0x0C, 0x06, 0x03};

void main(void)
{
    unsigned char step_idx = 0;

    while (1)
    {
        /* Output current step to ULN2003 driver (P2.0 - P2.3) */
        STEPPER_PORT = (STEPPER_PORT & 0xF0) | full_step_seq[step_idx];

        /* Advance to next step */
        step_idx = (step_idx + 1) % 4;

        /* Delay controls motor rotation speed (20 ms per step = smooth rotation) */
        delay_ms(20);
    }
}
