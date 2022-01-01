// rp2040.cpp

#include <Arduino.h>
#include "program.h"
// #include "pico/stdlib.h" // LED_BUILTIN oriented stuff may need this one

// Forth code words

#define BLINK_TIME 80
#define DELTA_TIME 700

void quickly(void) {
    int elapsed=millis();
    do {
        for (volatile int slow = 3; slow > 0; slow--) { }
    } while ((millis() - elapsed) < BLINK_TIME);
}

void slowly(void) {
    int elapsed=millis();
    do {
        for (volatile int slow = 3; slow > 0; slow--) { }
    } while ((millis() - elapsed) < (BLINK_TIME + DELTA_TIME));
}

void _reflashing(void) {
    reflash_firmware();
}

void _blink_led(void) {
    digitalWrite(LED_BUILTIN, 1);
    quickly();
    digitalWrite(LED_BUILTIN, 0);
    slowly();
}
