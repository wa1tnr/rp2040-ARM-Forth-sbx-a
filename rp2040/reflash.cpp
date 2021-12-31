#include <Arduino.h>
#include "pico/bootrom.h"

void reflash_firmware(void) {
    reset_usb_boot(0, 0);
}

