#ifndef KEYPAD_H
#define KEYPAD_H

#include <reg52.h>

#define KEYPAD_PORT P1

/* Function Prototypes */
char keypad_scan(void);
char keypad_getkey_blocking(void);

#endif /* KEYPAD_H */
