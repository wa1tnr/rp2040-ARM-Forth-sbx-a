// program.h
// Mon Apr 26 01:06:59 UTC 2021
#warning seen program.h
#include "compatibility.h"
#include "forth_defines.h"
#define crlf(__a__); {Serial.print("\r\n");}

extern void reflash_firmware(void); // prototype
