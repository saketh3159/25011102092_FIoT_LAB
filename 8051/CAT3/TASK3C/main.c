#include <reg52.h>

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

void main(void) {
    while (1) {
        /* Step 1: LEDs 1 & 3 ON, LEDs 2 & 4 OFF (Active-LOW: bits 0 & 2 LOW -> 0x05) */
        P2 = (P2 & 0xF0) | 0x05;
        delay_ms(300);
        /* Step 2: LEDs 2 & 4 ON, LEDs 1 & 3 OFF (Active-LOW: bits 1 & 3 LOW -> 0x0A) */
        P2 = (P2 & 0xF0) | 0x0A;
        delay_ms(300);
    }
}
