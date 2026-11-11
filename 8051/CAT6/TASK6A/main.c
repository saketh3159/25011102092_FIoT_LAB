/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 6 - TASK 6A: UART 9600-8-N-1 String Transmission
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : TXD on P3.1, RXD on P3.0 connected to USB-to-UART Converter
 ******************************************************************************
 */

#include <reg52.h>

/**
 * @brief  Initialize UART at 9600 Baud, 8 Data Bits, 1 Stop Bit, No Parity
 *         Timer 1 in Mode 2 (8-bit Auto-Reload).
 *         TH1 = 256 - ((11059200 / (32 * 12 * 9600))) = 256 - 3 = 0xFD
 */
void uart_init(void)
{
    TMOD &= 0x0F;
    TMOD |= 0x20;   /* Timer 1, Mode 2 (8-bit auto-reload) */
    TH1   = 0xFD;   /* 9600 Baud at 11.0592 MHz */
    TL1   = 0xFD;
    SCON  = 0x50;   /* Mode 1, 8-bit UART, Receiver enabled (REN = 1) */
    TR1   = 1;      /* Start Timer 1 */
    TI    = 0;      /* Clear Transmit Interrupt flag */
}

/**
 * @brief  Transmit a single character over UART
 */
void uart_tx_char(char c)
{
    SBUF = c;
    while (!TI);    /* Wait until byte transmission is complete */
    TI = 0;         /* Clear Transmit Interrupt flag */
}

/**
 * @brief  Transmit a null-terminated string over UART
 */
void uart_tx_string(char *str)
{
    while (*str)
    {
        uart_tx_char(*str++);
    }
}

/**
 * @brief  Calibrated millisecond delay
 */
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 120; j++);
    }
}

void main(void)
{
    /* Initialize UART peripheral */
    uart_init();

    while (1)
    {
        /* Transmit message periodically every 1 second */
        uart_tx_string("Hello from 8051\r\n");
        delay_ms(1000);
    }
}
