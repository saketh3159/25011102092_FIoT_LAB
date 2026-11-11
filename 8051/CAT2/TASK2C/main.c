#include <reg52.h>

sbit LED = P2^0;

/* Parameterized Software Delay Library */
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++); /* Calibrated ~1 ms loop @ 11.0592 MHz */
    }
}

void delay_us(unsigned int us) {
    while (us--);
}

void main(void) {
    while (1) {
        LED = 0;         /* LED ON (Active-LOW) */
        delay_ms(250);   /* Parameterized 250 ms delay */
        LED = 1;         /* LED OFF */
        delay_ms(750);   /* Parameterized 750 ms delay */
    }
}
