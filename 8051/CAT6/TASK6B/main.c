/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 6 - TASK 6B: Interactive Terminal Echo Engine
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : TXD on P3.1, RXD on P3.0 connected to PuTTY Terminal
 ******************************************************************************
 */

#include <reg52.h>

/**
 * @brief  Initialize UART at 9600 Baud, 8-N-1
 */
void uart_init(void)
{
    TMOD &= 0x0F;
    TMOD |= 0x20;   /* Timer 1, Mode 2 (8-bit auto-reload) */
    TH1   = 0xFD;   /* 9600 Baud at 11.0592 MHz */
    TL1   = 0xFD;
    SCON  = 0x50;   /* Mode 1, 8-bit UART, Receiver enabled */
    TR1   = 1;      /* Start Timer 1 */
    TI    = 0;
    RI    = 0;
}

/**
 * @brief  Transmit a single character over UART
 */
void uart_tx_char(char c)
{
    SBUF = c;
    while (!TI);
    TI = 0;
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
 * @brief  Receive a single character over UART (blocking)
 */
char uart_rx_char(void)
{
    while (!RI);    /* Wait until byte reception is complete */
    RI = 0;         /* Clear Receive Interrupt flag */
    return SBUF;
}

void main(void)
{
    char received_char;

    /* Initialize UART */
    uart_init();

    /* Transmit Welcome Banner */
    uart_tx_string("\r\n========================================\r\n");
    uart_tx_string("  8051 AT89S52 Interactive Terminal Echo \r\n");
    uart_tx_string("  Type characters in PuTTY to echo back  \r\n");
    uart_tx_string("========================================\r\n\r\n");

    while (1)
    {
        /* Wait for incoming character and immediately echo back */
        received_char = uart_rx_char();

        /* If Enter key is pressed (\r), send both \r and \n */
        if (received_char == '\r')
        {
            uart_tx_string("\r\n");
        }
        else
        {
            uart_tx_char(received_char);
        }
    }
}
