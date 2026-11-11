#include "lcd.h"

/**
 * @brief Millisecond delay for 11.0592 MHz crystal
 */
void lcd_delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

/**
 * @brief Microsecond delay loop
 */
void lcd_delay_us(unsigned int us)
{
    while (us--)
    {
        /* ~1.085 us per instruction */
        _nop_();
        _nop_();
    }
}

/**
 * @brief Generate high-to-low pulse on Enable pin to latch data
 */
void lcd_pulse_enable(void)
{
    LCD_EN = 1;
    lcd_delay_us(10);
    LCD_EN = 0;
    lcd_delay_us(50);
}

/**
 * @brief Write 4-bit nibble to LCD data bus (P2.4 - P2.7)
 */
void lcd_send_nibble(unsigned char nibble)
{
    /* Keep lower 4 control bits unchanged, update upper 4 data bits */
    P2 = (P2 & 0x0F) | (nibble & 0xF0);
    lcd_pulse_enable();
}

/**
 * @brief Send command byte to LCD
 */
void lcd_cmd(unsigned char cmd)
{
    LCD_RS = 0; /* Command mode */
    
    /* Send High Nibble first */
    lcd_send_nibble(cmd & 0xF0);
    
    /* Send Low Nibble shifted to upper 4 bits */
    lcd_send_nibble((cmd << 4) & 0xF0);
    
    if (cmd == 0x01 || cmd == 0x02)
        lcd_delay_ms(2); /* Clear display & return home require > 1.64 ms */
    else
        lcd_delay_us(50);
}

/**
 * @brief Send character data byte to LCD
 */
void lcd_data(unsigned char dat)
{
    LCD_RS = 1; /* Data mode */
    
    /* Send High Nibble first */
    lcd_send_nibble(dat & 0xF0);
    
    /* Send Low Nibble */
    lcd_send_nibble((dat << 4) & 0xF0);
    
    lcd_delay_us(50);
}

/**
 * @brief Initialize HD44780 LCD in 4-bit, 2-line, 5x8 font mode
 *        per the datasheet initialization sequence
 */
void lcd_init(void)
{
    /* Ensure control pins are low */
    LCD_RS = 0;
    LCD_EN = 0;
    
    /* Step 1: Wait > 15 ms after VCC rises to 4.5V */
    lcd_delay_ms(20);
    
    /* Step 2: Special 8-bit initialization sequence per HD44780 spec */
    lcd_send_nibble(0x30);
    lcd_delay_ms(5);
    
    lcd_send_nibble(0x30);
    lcd_delay_us(150);
    
    lcd_send_nibble(0x30);
    lcd_delay_us(150);
    
    /* Step 3: Switch to 4-bit interface */
    lcd_send_nibble(0x20);
    lcd_delay_ms(2);
    
    /* Step 4: Function Set: 4-bit mode, 2 display lines, 5x8 font (0x28) */
    lcd_cmd(0x28);
    
    /* Step 5: Display Control: Display ON, Cursor OFF, Blink OFF (0x0C) */
    lcd_cmd(0x0C);
    
    /* Step 6: Clear Display (0x01) */
    lcd_cmd(0x01);
    lcd_delay_ms(2);
    
    /* Step 7: Entry Mode Set: Increment cursor, No display shift (0x06) */
    lcd_cmd(0x06);
}

/**
 * @brief Position cursor at specified (row, col)
 *        Row 0: 0x80 to 0x8F (col 0 - 15)
 *        Row 1: 0xC0 to 0xCF (col 0 - 15)
 */
void lcd_goto(unsigned char row, unsigned char col)
{
    unsigned char addr;
    if (col > 15) col = 15;
    
    if (row == 0)
        addr = 0x80 + col;
    else
        addr = 0xC0 + col;
        
    lcd_cmd(addr);
}

/**
 * @brief Print null-terminated string to LCD
 */
void lcd_puts(char *str)
{
    while (*str)
    {
        lcd_data(*str++);
    }
}

/**
 * @brief Print unsigned integer value
 */
void lcd_print_number(unsigned int val)
{
    char buf[6];
    int i = 0;
    
    if (val == 0)
    {
        lcd_data('0');
        return;
    }
    
    while (val > 0)
    {
        buf[i++] = (val % 10) + '0';
        val /= 10;
    }
    
    /* Print digits in reverse order */
    while (i > 0)
    {
        lcd_data(buf[--i]);
    }
}

/**
 * @brief Clear display buffer
 */
void lcd_clear(void)
{
    lcd_cmd(0x01);
    lcd_delay_ms(2);
}
