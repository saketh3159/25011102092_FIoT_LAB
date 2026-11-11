/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 5 - TASK 5B.2: Software PWM Carrier Frequency Analysis
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : PWM Signal Output on P1.1 & P1.2 for DSO verification
 ******************************************************************************
 */

#include <reg52.h>

/* Pin Definitions */
sbit PWM_OUT  = P1^1; /* PWM Output pin for oscilloscope & LED */
sbit SYNC_OUT = P1^2; /* Carrier sync trigger for DSO channel 2 */

void delay_short(void)
{
    unsigned char k;
    for (k = 0; k < 10; k++);
}

void main(void)
{
    /* Discrete duty cycle test table: 25%, 50%, 75%, 100% */
    unsigned char duty_levels[4] = {25, 50, 75, 100};
    unsigned char level_idx = 0;
    unsigned int period_counter = 0;
    unsigned char step;
    unsigned char active_duty = 50;

    while (1)
    {
        active_duty = duty_levels[level_idx];

        /* Fixed 500 Hz Carrier Period (composed of 100 time-slices) */
        SYNC_OUT = 1; /* Trigger pulse for DSO */
        for (step = 0; step < 100; step++)
        {
            if (step < active_duty)
            {
                PWM_OUT = 0; /* Active (ON) */
            }
            else
            {
                PWM_OUT = 1; /* Inactive (OFF) */
            }
            delay_short();
        }
        SYNC_OUT = 0;

        /* Switch duty level every 500 cycles (~1 second at 500 Hz) */
        period_counter++;
        if (period_counter >= 500)
        {
            period_counter = 0;
            level_idx = (level_idx + 1) % 4;
        }
    }
}
