#include <reg52.h>

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

void main(void) {
    while (1) {
        /* All 4 LEDs ON (Active-LOW: bits 0-3 LOW) */
        P2 = (P2 & 0xF0) | 0x00;
        delay_ms(250);
        /* All 4 LEDs OFF (bits 0-3 HIGH) */
        P2 = (P2 & 0xF0) | 0x0F;
        delay_ms(250);
    }
}
