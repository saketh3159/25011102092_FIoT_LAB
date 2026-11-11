/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 7 - TASK 7C: 4x4 Keypad Interactive LCD Menu Navigation
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : 16x2 HD44780 LCD on P2 + 4x4 Matrix Keypad on P0
 ******************************************************************************
 */

#include <reg52.h>

/* LCD Pin Definitions on Port 2 */
sbit LCD_RS = P2^0;
sbit LCD_RW = P2^1;
sbit LCD_EN = P2^2;
#define LCD_PORT P2

/* 4x4 Keypad Port on Port 0: Rows P0.0-P0.3, Cols P0.4-P0.7 */
#define KEYPAD_PORT P0

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

/* 4x4 Keypad Key Map */
const char key_table[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

char keypad_scan(void)
{
    unsigned char row, col, col_val;

    for (row = 0; row < 4; row++)
    {
        KEYPAD_PORT = 0xFF;
        KEYPAD_PORT &= ~(1 << row); /* Ground active row */

        col_val = (KEYPAD_PORT >> 4) & 0x0F;
        if (col_val != 0x0F)
        {
            delay_ms(20); /* Debounce */
            col_val = (KEYPAD_PORT >> 4) & 0x0F;
            if (col_val != 0x0F)
            {
                for (col = 0; col < 4; col++)
                {
                    if (!(col_val & (1 << col)))
                    {
                        while (((KEYPAD_PORT >> 4) & 0x0F) != 0x0F); /* Wait release */
                        delay_ms(20);
                        return key_table[row][col];
                    }
                }
            }
        }
    }
    return 0; /* No key pressed */
}

void main(void)
{
    char key;

    lcd_init();

    lcd_goto(0, 0);
    lcd_puts("Interactive Menu");

    lcd_goto(1, 0);
    lcd_puts("Key: [None]     ");

    while (1)
    {
        key = keypad_scan();
        if (key != 0)
        {
            lcd_goto(1, 5);
            lcd_data('[');
            lcd_data(key);
            lcd_data(']');
            lcd_puts("   ");
        }
    }
}
