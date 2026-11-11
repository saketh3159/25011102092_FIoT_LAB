#ifndef LCD_H
#define LCD_H

#include <reg52.h>

/* Pin Definitions for HD44780 16x2 LCD in 4-Bit Mode */
sbit LCD_RS = P2^0;   /* Register Select: 0 = Command, 1 = Data */
sbit LCD_EN = P2^1;   /* Enable Pin: Active High Latch Pulse */

/* Function Prototypes */
void lcd_delay_ms(unsigned int ms);
void lcd_delay_us(unsigned int us);
void lcd_pulse_enable(void);
void lcd_send_nibble(unsigned char nibble);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char dat);
void lcd_init(void);
void lcd_goto(unsigned char row, unsigned char col);
void lcd_puts(char *str);
void lcd_print_number(unsigned int val);
void lcd_clear(void);

#endif /* LCD_H */
