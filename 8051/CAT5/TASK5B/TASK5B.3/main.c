/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 5 - TASK 5B.3: Software PWM Multi-LED Breathing Controller
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : 4 LEDs on Port 1 Pins 0 to 3 (P1.0 - P1.3)
 ******************************************************************************
 */

#include <reg52.h>

/* Pin Definitions */
#define LED_PORT P1  /* Port 1 pins drive 4 LEDs (Active-LOW) */

void delay_us(unsigned char t)
{
    while (t--);
}

void main(void)
{
    unsigned char duty = 0;
    bit ramp_up = 1;
    unsigned char step, loop_rep;

    LED_PORT = 0xFF; /* Turn OFF all LEDs initially */

    while (1)
    {
        /* Run 5 PWM cycles at current brightness level */
        for (loop_rep = 0; loop_rep < 5; loop_rep++)
        {
            for (step = 0; step < 100; step++)
            {
                if (step < duty)
                {
                    /* Turn ON LEDs P1.0 to P1.3 (Active-LOW: 0 = ON) */
                    LED_PORT = 0xF0;
                }
                else
                {
                    /* Turn OFF LEDs (1 = OFF) */
                    LED_PORT = 0xFF;
                }
                delay_us(8);
            }
        }

        /* Breathing Effect: Smooth sinusoidal/triangular ramp */
        if (ramp_up)
        {
            duty += 2;
            if (duty >= 98)
            {
                duty = 98;
                ramp_up = 0;
            }
        }
        else
        {
            duty -= 2;
            if (duty <= 2)
            {
                duty = 2;
                ramp_up = 1;
            }
        }
    }
}
