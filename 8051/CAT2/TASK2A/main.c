#include <reg52.h>

sbit LED = P2^0;

void delay(void) {
    unsigned int i, j;
    for (i = 0; i < 300; i++)
        for (j = 0; j < 120; j++);
}

void main(void) {
    /* Board Bring-Up Verification Sequence */
    unsigned char k;
    for (k = 0; k < 6; k++) {
        LED = ~LED;
        delay();
    }
    LED = 0; /* Final state: Active-LOW LED ON confirming successful bring-up */
    while (1) {
        /* Stable bring-up idle state */
    }
}
