#include <reg52.h>
#include "uart.h"

#define RX_BUFFER_SIZE 32

/* Interrupt-Driven Circular RX Ring Buffer */
volatile char rx_buffer[RX_BUFFER_SIZE];
volatile unsigned char rx_head = 0;
volatile unsigned char rx_tail = 0;

/**
 * @brief Initialize UART for 9600-8-N-1 using Timer 1 in Mode 2 (8-bit auto-reload)
 * Crystal = 11.0592 MHz, SMOD = 0 -> TH1 = 0xFD
 */
void uart_init(void) {
    /* Configure Timer 1 in Mode 2: 8-bit Auto-Reload */
    TMOD &= 0x0F;
    TMOD |= 0x20;

    /* Baud Rate = 9600 bps: TH1 = 256 - (11059200 / (384 * 9600)) = 253 = 0xFD */
    TH1 = 0xFD;
    TL1 = 0xFD;

    /* SCON: Mode 1 (8-bit UART, variable baud), Enable Receiver (REN=1) -> 0x50 */
    SCON = 0x50;

    /* Enable Serial Interrupt and start Timer 1 */
    ES = 1;
    EA = 1;
    TR1 = 1;

    TI = 0;
    RI = 0;
}

/**
 * @brief Serial ISR: Handles incoming characters into circular ring buffer
 */
void serial_isr(void) interrupt 4 {
    if (RI) {
        RI = 0; /* Clear receive interrupt flag */
        rx_buffer[rx_head] = SBUF;
        rx_head = (rx_head + 1) % RX_BUFFER_SIZE;
    }
    if (TI) {
        TI = 0; /* Clear transmit interrupt flag if handled */
    }
}

/**
 * @brief Transmit a single character via UART
 */
void uart_tx_char(char c) {
    SBUF = c;       /* Write byte to serial data buffer */
    while (TI == 0);/* Wait until transmission completes */
    TI = 0;         /* Clear transmit interrupt flag */
}

/**
 * @brief Transmit a null-terminated string
 */
void uart_tx_string(const char *str) {
    while (*str) {
        uart_tx_char(*str++);
    }
}

/**
 * @brief Check if character is available in RX ring buffer
 */
bit uart_available(void) {
    return (rx_head != rx_tail);
}

/**
 * @brief Read one character from circular RX ring buffer
 */
char uart_rx_char(void) {
    char c = 0;
    if (rx_head != rx_tail) {
        c = rx_buffer[rx_tail];
        rx_tail = (rx_tail + 1) % RX_BUFFER_SIZE;
    }
    return c;
}
