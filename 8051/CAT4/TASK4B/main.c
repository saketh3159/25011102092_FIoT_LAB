#include <reg52.h>

/* Common Anode 7-Segment Lookup Table for digits 0-9 */
code unsigned char seg_code[] = {
    0xC0, /* 0 */
    0xF9, /* 1 */
    0xA4, /* 2 */
    0xB0, /* 3 */
    0x99, /* 4 */
    0x92, /* 5 */
    0x82, /* 6 */
    0xF8, /* 7 */
    0x80, /* 8 */
    0x90  /* 9 */
};

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

void main(void) {
    unsigned char digit = 0;
    while (1) {
        P0 = seg_code[digit];
        delay_ms(500);
        digit = (digit + 1) % 10;
    }
}
