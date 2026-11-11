#include "keypad.h"
#include "lcd.h"

static const char code keymap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

/**
 * @brief Non-blocking scan of 4x4 matrix keypad
 * @return ASCII character of pressed key, or 0 if no key is pressed
 */
char keypad_scan(void)
{
    unsigned char row, col;
    unsigned char row_mask;

    for (row = 0; row < 4; row++)
    {
        /* Drive current row LOW, others HIGH, pull columns HIGH */
        row_mask = ~(1 << row) & 0x0F;
        KEYPAD_PORT = 0xF0 | row_mask;
        lcd_delay_us(10); /* Propagation delay */

        /* Check columns P1.4 - P1.7 */
        if ((KEYPAD_PORT & 0xF0) != 0xF0)
        {
            lcd_delay_ms(20); /* Software debounce */
            if ((KEYPAD_PORT & 0xF0) != 0xF0)
            {
                unsigned char col_val = (KEYPAD_PORT >> 4) & 0x0F;
                for (col = 0; col < 4; col++)
                {
                    if (!(col_val & (1 << col)))
                    {
                        /* Wait for key release */
                        while ((KEYPAD_PORT & 0xF0) != 0xF0);
                        lcd_delay_ms(15);
                        return keymap[row][col];
                    }
                }
            }
        }
    }

    return 0; /* No key detected */
}

/**
 * @brief Blocking key read
 */
char keypad_getkey_blocking(void)
{
    char k = 0;
    while (!(k = keypad_scan()));
    return k;
}
