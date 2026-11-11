/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 5 - TASK 5A: 1 ms Hardware Timer 0 ISR & 1s LED Toggle
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : LED on P1.0 (Active-LOW)
 ******************************************************************************
 */

#include <reg52.h>

/* Pin Definitions */
sbit LED_1SEC = P1^0; /* Output LED toggling every 1 second */

/* Global Millisecond Tick Counter */
volatile unsigned int ms_count = 0;

/**
 * @brief  Timer 0 Interrupt Service Routine (Vector 1: 0x000B)
 *         Configured in Mode 1 (16-bit Timer).
 *         Preload FC66h generates an exact 1 ms interrupt period at 11.0592 MHz.
 */
void timer0_isr(void) interrupt 1
{
    /* Reload Timer 0 registers for 1 ms tick (65536 - 922 = 64614 = 0xFC66) */
    TH0 = 0xFC;
    TL0 = 0x66;

    ms_count++;
    if (ms_count >= 1000)
    {
        ms_count = 0;
        LED_1SEC = ~LED_1SEC; /* Toggle LED every 1000 ms (1.0 s) */
    }
}

void main(void)
{
    /* Initialize LED to OFF (Active-LOW: 1 = OFF) */
    LED_1SEC = 1;

    /* Configure Timer 0 in Mode 1: 16-bit Timer (TMOD bit 0 = 1) */
    TMOD &= 0xF0;
    TMOD |= 0x01;

    /* Load initial reload values for 1 ms */
    TH0 = 0xFC;
    TL0 = 0x66;

    /* Enable Timer 0 Interrupt (ET0) and Global Interrupts (EA) */
    ET0 = 1;
    EA  = 1;

    /* Start Timer 0 */
    TR0 = 1;

    while (1)
    {
        /* Main loop remains non-blocking; timing is handled by Timer 0 ISR */
    }
}
