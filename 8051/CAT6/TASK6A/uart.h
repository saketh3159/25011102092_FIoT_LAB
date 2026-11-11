#ifndef UART_H
#define UART_H

/**
 * @brief 8051 UART Driver for AT89S52 (9600-8-N-1 at 11.0592 MHz)
 */

void uart_init(void);
void uart_tx_char(char c);
void uart_tx_string(const char *str);
char uart_rx_char(void);
bit uart_available(void);

#endif /* UART_H */
