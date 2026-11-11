/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 7 - TASK 7A: LCD 4-Bit Driver & Dual-Row Display
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : 16x2 HD44780 LCD in 4-Bit Mode
 *                  RS = P2.0, RW = P2.1, EN = P2.2
 *                  D4 = P2.4, D5 = P2.5, D6 = P2.6, D7 = P2.7
 ******************************************************************************
 */

#include <reg52.h>

/* Pin Definitions */
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
    LCD_RS = 0; /* Command mode */
    LCD_RW = 0; /* Write mode */
    lcd_send_nibble(cmd);        /* High nibble */
    lcd_send_nibble(cmd << 4);   /* Low nibble */
    delay_ms(2);
}

void lcd_data(unsigned char dat)
{
    LCD_RS = 1; /* Data mode */
    LCD_RW = 0; /* Write mode */
    lcd_send_nibble(dat);        /* High nibble */
    lcd_send_nibble(dat << 4);   /* Low nibble */
    delay_ms(2);
}

void lcd_init(void)
{
    delay_ms(20);
    LCD_RS = 0;
    LCD_RW = 0;

    /* 4-bit initialization sequence */
    lcd_send_nibble(0x30);
    delay_ms(5);
    lcd_send_nibble(0x30);
    delay_ms(1);
    lcd_send_nibble(0x30);
    delay_ms(1);
    lcd_send_nibble(0x20); /* 4-bit mode */
    delay_ms(1);

    lcd_cmd(0x28); /* 2 lines, 5x7 matrix */
    lcd_cmd(0x0C); /* Display ON, cursor OFF */
    lcd_cmd(0x06); /* Increment cursor */
    lcd_cmd(0x01); /* Clear display */
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

void main(void)
{
    lcd_init();

    /* Task 7A: Dual-Row String Display */
    lcd_goto(0, 0);
    lcd_puts("25011102018 FIoT");

    lcd_goto(1, 0);
    lcd_puts("LCD 16x2 4-Bit OK");

    while (1)
    {
        /* Static display */
    }
}
