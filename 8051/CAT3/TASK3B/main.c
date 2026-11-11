#include <reg52.h>

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

void main(void) {
    unsigned char count = 0;
    while (1) {
        /* Output inverted count for Active-LOW LEDs on P2.0-P2.3 */
        P2 = (P2 & 0xF0) | (~count & 0x0F);
        delay_ms(300);
        count = (count + 1) & 0x0F; /* Increment and wrap at 15 */
    }
}
