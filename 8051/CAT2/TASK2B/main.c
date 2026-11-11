/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 2 - TASK 2B: Bare-Metal LED Blink (~1 Hz)
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : Active-LOW LED connected to Port 2 Pin 0 (P2.0)
 ******************************************************************************
 */

#include <reg52.h>

/* Pin Definitions */
sbit LED = P2^0;   /* Active-LOW LED on Port 2 Pin 0 */

/**
 * @brief  Calibrated software delay for ~500 ms at 11.0592 MHz
 *         Machine cycle = 12 / 11.0592 MHz = 1.085 us
 *         500 ms ON + 500 ms OFF = 1000 ms period = 1.0 Hz blink frequency
 */
void delay_500ms(void)
{
    unsigned int i, j;
    for (i = 0; i < 500; i++)
    {
        for (j = 0; j < 120; j++)
        {
            /* ~1 ms inner loop iteration */
        }
    }
}

void main(void)
{
    /* Initialize LED to OFF (Active-LOW: 1 = OFF, 0 = ON) */
    LED = 1;

    while (1)
    {
        LED = ~LED;        /* Toggle LED state */
        delay_500ms();     /* Wait 500 ms */
    }
}
