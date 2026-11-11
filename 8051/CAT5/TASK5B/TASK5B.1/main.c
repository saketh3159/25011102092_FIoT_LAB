/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 5 - TASK 5B.1: Software PWM Fading - Triangular Wave Modulation
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : LED on P1.1 (Active-LOW: 0 = ON, 1 = OFF)
 ******************************************************************************
 */

#include <reg52.h>

/* Pin Definitions */
sbit LED_PWM = P1^1; /* PWM Output pin driving LED */

void delay_us(unsigned char t)
{
    while (t--);
}

void main(void)
{
    unsigned char duty = 0;
    bit direction = 1; /* 1 = ramping up, 0 = ramping down */
    unsigned char i, cycle;

    while (1)
    {
        /* Run 10 PWM periods at the current duty cycle */
        for (cycle = 0; cycle < 10; cycle++)
        {
            /* PWM Period composed of 100 sub-steps */
            for (i = 0; i < 100; i++)
            {
                if (i < duty)
                {
                    LED_PWM = 0; /* LED ON (Active-LOW) */
                }
                else
                {
                    LED_PWM = 1; /* LED OFF */
                }
                delay_us(10);
            }
        }

        /* Triangular Modulation: ramp duty 0% -> 100% -> 0% */
        if (direction == 1)
        {
            duty += 2;
            if (duty >= 100)
            {
                duty = 100;
                direction = 0; /* Reverse direction */
            }
        }
        else
        {
            duty -= 2;
            if (duty <= 0)
            {
                duty = 0;
                direction = 1; /* Forward direction */
            }
        }
    }
}
