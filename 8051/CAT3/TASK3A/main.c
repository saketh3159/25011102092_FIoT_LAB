/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 3 - TASK 3A: Push-Button Event Detection & Debounce
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : Push-Button on P3.2 (Active-LOW with pull-up)
 *                  LED on P2.0 (Active-LOW)
 ******************************************************************************
 */

#include <reg52.h>

/* Pin Definitions */
sbit BUTTON = P3^2;  /* Push-Button input on P3.2 */
sbit LED    = P2^0;  /* Output LED on P2.0 */

/**
 * @brief  Calibrated software millisecond delay
 */
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 120; j++)
        {
            /* ~1 ms delay */
        }
    }
}

void main(void)
{
    /* Configure BUTTON pin as input by writing 1 to Port pin */
    BUTTON = 1;
    /* Initialize LED to OFF (Active-LOW) */
    LED = 1;

    while (1)
    {
        /* Check if button is pressed (Active-LOW: 0 = Pressed) */
        if (BUTTON == 0)
        {
            delay_ms(25); /* 25 ms software debounce filter */

            if (BUTTON == 0) /* Confirm button is still pressed */
            {
                LED = ~LED;  /* Toggle LED on valid button press */

                /* Wait for button release with debounce */
                while (BUTTON == 0);
                delay_ms(25);
            }
        }
    }
}
