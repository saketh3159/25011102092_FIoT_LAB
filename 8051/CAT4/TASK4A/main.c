/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : CAT 4 - TASK 4A: 4x4 Matrix Keypad Scanning & 7-Segment Display
 * Platform       : Atmel/Microchip AT89S52 (8051 Architecture @ 11.0592 MHz)
 * Hardware       : Keypad on Port 2 (Rows P2.0-P2.3, Cols P2.4-P2.7)
 *                  7-Segment on Port 0 (Common Cathode)
 *                  LEDs on Port 1 (P1.0 - P1.3)
 ******************************************************************************
 */

#include <reg52.h>

/* Port Assignments */
#define KEYPAD_PORT P2    /* Rows: P2.0-P2.3, Columns: P2.4-P2.7 */
#define SEG_PORT    P0    /* 7-Segment display (Segments a-g, dp) */
#define LED_PORT    P1    /* Output LEDs: P1.0-P1.3 */

/* Common Cathode 7-Segment Hex Lookup Table (Digits 0 - 9) */
const unsigned char seg_code[10] = {
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F  /* 9 */
};

/* 4x4 Keypad Key Map */
const unsigned char key_map[4][4] = {
    {1, 2, 3, 0x0A},
    {4, 5, 6, 0x0B},
    {7, 8, 9, 0x0C},
    {0x0E, 0, 0x0F, 0x0D}
};

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 120; j++);
    }
}

/**
 * @brief  Scan 4x4 Matrix Keypad
 * @retval Key value (0-15), or 0xFF if no key pressed
 */
unsigned char keypad_scan(void)
{
    unsigned char row, col, col_val;

    for (row = 0; row < 4; row++)
    {
        /* Set all rows HIGH then ground active row */
        KEYPAD_PORT = 0xFF;
        KEYPAD_PORT &= ~(1 << row);

        /* Read columns (P2.4 - P2.7) */
        col_val = (KEYPAD_PORT >> 4) & 0x0F;

        if (col_val != 0x0F)
        {
            delay_ms(20); /* Key debounce */
            col_val = (KEYPAD_PORT >> 4) & 0x0F;
            if (col_val != 0x0F)
            {
                for (col = 0; col < 4; col++)
                {
                    if (!(col_val & (1 << col)))
                    {
                        /* Wait until key is released */
                        while (((KEYPAD_PORT >> 4) & 0x0F) != 0x0F);
                        delay_ms(20);
                        return key_map[row][col];
                    }
                }
            }
        }
    }
    return 0xFF; /* No key pressed */
}

void display_digit(unsigned char value)
{
    if (value <= 9)
    {
        SEG_PORT = seg_code[value];
    }
    else
    {
        SEG_PORT = 0x00; /* Blank display for non-numeric keys */
    }
}

void main(void)
{
    unsigned char key = 0xFF;

    /* Initialize Ports */
    SEG_PORT = 0x00; /* 7-Seg OFF */
    LED_PORT = 0xFF; /* LEDs OFF */

    while (1)
    {
        key = keypad_scan();
        if (key != 0xFF)
        {
            display_digit(key);                  /* Display on 7-Segment */
            LED_PORT = (LED_PORT & 0xF0) | (key & 0x0F); /* Display binary on LEDs */
        }
    }
}
