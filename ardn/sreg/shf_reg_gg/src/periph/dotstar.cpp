#include <Arduino.h>
// #include "../../yaffa.h"

// #define HAS_DOTSTAR_LIB
// #ifdef HAS_DOTSTAR_LIB
#include "dotstar.h"

#ifdef HAS_DOTSTAR_LIB

#include <Adafruit_DotStar.h>

#define NUMPIXELS 1 // Number of LEDs in strip

#ifdef ADAFRUIT_TRINKET_M0

  #undef DATAPIN
  #undef CLOCKPIN

  #define DATAPIN  7
  #define CLOCKPIN 8

#endif // #ifdef ADAFRUIT_TRINKET_M0

Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

void setup_dotstar() {
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

int      head  = 0, tail = -3;  // Index of first 'on' and 'off' pixels

   uint32_t color = 0x500000;      // 'On' color (starts red)

void loop_dotstar() {

  strip.setPixelColor(0, 0x000000); // turn it off
  strip.show();                     // Refresh strip
  delay(200);

  strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail

  strip.show();                     // Refresh strip
  delay(20);                        // Pause 20 milliseconds (~50 FPS)

  delay(900);                        // Pause 20 milliseconds (~50 FPS)


  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
      color = 0x010000;             //   Yes, reset to red
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index

Serial.println("\r\nWent off tail.  Bye from dotstar.");

}

#endif

// END
