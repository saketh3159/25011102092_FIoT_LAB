/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 7 - TASK 7B: Cursor Positioning & Dynamic Number Counter
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : 16x2 HD44780 LCD in 4-Bit Mode
 ******************************************************************************
 */

#include <reg52.h>

sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_EN = P2^2;
#define LCD_PORT P2

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

void lcd_pulse_en(void)
{
    LCD_EN = 1;
    delay_ms(1);
    LCD_EN = 0;
    delay_ms(1);
}

void lcd_send_nibble(unsigned char nibble)
{
    LCD_PORT = (LCD_PORT & 0x0F) | (nibble & 0xF0);
    lcd_pulse_en();
}

void lcd_cmd(unsigned char cmd)
{
    LCD_RS = 0;
    LCD_RW = 0;
    lcd_send_nibble(cmd);
    lcd_send_nibble(cmd << 4);
    delay_ms(2);
}

void lcd_data(unsigned char dat)
{
    LCD_RS = 1;
    LCD_RW = 0;
    lcd_send_nibble(dat);
    lcd_send_nibble(dat << 4);
    delay_ms(2);
}

void lcd_init(void)
{
    delay_ms(20);
    lcd_send_nibble(0x30);
    delay_ms(5);
    lcd_send_nibble(0x30);
    delay_ms(1);
    lcd_send_nibble(0x30);
    delay_ms(1);
    lcd_send_nibble(0x20);
    delay_ms(1);

    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    delay_ms(5);
}

void lcd_goto(unsigned char row, unsigned char col)
{
    unsigned char address = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_cmd(address);
}

void lcd_puts(char *str)
{
    while (*str)
    {
        lcd_data(*str++);
    }
}

void lcd_print_number(unsigned int num)
{
    char buf[6];
    int idx = 0;
    if (num == 0)
    {
        lcd_data('0');
        return;
    }
    while (num > 0)
    {
        buf[idx++] = (num % 10) + '0';
        num /= 10;
    }
    while (idx > 0)
    {
        lcd_data(buf[--idx]);
    }
}

void main(void)
{
    unsigned int count = 0;

    lcd_init();

    /* Header on Line 1 */
    lcd_goto(0, 0);
    lcd_puts("Dynamic Counter:");

    while (1)
    {
        /* Dynamic value update on Line 2 */
        lcd_goto(1, 0);
        lcd_puts("Count: ");
        lcd_print_number(count);
        lcd_puts("    "); /* Clear trailing characters */

        count++;
        delay_ms(250); /* Update every 250 ms */
    }
}
