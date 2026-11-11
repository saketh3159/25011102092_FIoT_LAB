#include <reg52.h>

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}

unsigned char keypad_scan(void) {
    unsigned char row, col;
    unsigned char code row_mask[4] = {0xFE, 0xFD, 0xFB, 0xF7};
    for (row = 0; row < 4; row++) {
        P1 = row_mask[row];
        col = P1 & 0xF0;
        if (col != 0xF0) {
            delay_ms(20);
            col = P1 & 0xF0;
            if (col != 0xF0) {
                while ((P1 & 0xF0) != 0xF0);
                if (col == 0xE0) return (row * 4 + 1);
                if (col == 0xD0) return (row * 4 + 2);
                if (col == 0xB0) return (row * 4 + 3);
                if (col == 0x70) return (row * 4 + 4);
            }
        }
    }
    return 0;
}

void main(void) {
    unsigned char key;
    P2 = 0xFF; /* Turn OFF all LEDs initially */
    while (1) {
        key = keypad_scan();
        if (key >= 1 && key <= 4) {
            P2 = ~(1 << (key - 1)); /* Individual LED */
        } else if (key == 5) {
            P2 = 0xAA; /* Pattern A */
        } else if (key == 6) {
            P2 = 0x55; /* Pattern B */
        } else if (key == 7) {
            P2 = 0x00; /* All LEDs ON */
        } else if (key == 8) {
            P2 = 0xFF; /* All LEDs OFF */
        }
    }
}
