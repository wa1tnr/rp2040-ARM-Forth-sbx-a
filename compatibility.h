// Sun  2 Jan 23:17:37 UTC 2022

#warning seen compatibility.h

#undef  RP2040_VARIANT
#define RP2040_VARIANT

#ifdef RP2040_VARIANT
#define RP2040_PRESENT -1 // TRUE
#endif

#ifndef RP2040_VARIANT
#define RP2040_PRESENT -0 // FALSE
#endif
