// seven segment code - factory demo 74hc595 foo

// Refresh:


// Fri 10 Dec 17:36:17 UTC 2021

// DIGIT goes to Vcc
// COMMON goes to Vcc
// segments go to ground.


// Sat Apr 27 22:25:53 UTC 2019

// jeppifebbarkidia

// Originally:
// Wed Nov 28 09:52:54 UTC 2018

// finpaflik

#define DATENOW     "Wed Nov 28 09:52:54 UTC 2018"

// use #undef FASTDEMO for a more relaxed display of messages
#define FASTDEMO -1
#undef  FASTDEMO

// use #undef BASIC_POV_TECHNIQUE_DEMO to run without expsing POV techniques
#define BASIC_POV_TECHNIQUE_DEMO -1
#undef  BASIC_POV_TECHNIQUE_DEMO


//  ////////////////////////////////////////////////////////////////////////

#ifdef BASIC_POV_TECHNIQUE_DEMO
    #define EXPOSE_DIGIT_PAINTING -1
    // duration will be doubled in terms of iteration of message:
    #define DURATION 2
    #define REPETITIONS 1
#else
    #define EXPOSE_DIGIT_PAINTING  0
    #ifndef FASTDEMO
        #define DURATION 255
    #else
        #define DURATION 77
    #endif
    #define REPETITIONS 2
#endif




// #include "src/periph/dotstar.h"





/*
Adafruit Arduino - Lesson 4. 8 LEDs and a Shift Register
Simon Monk mods: wa1tnr  27 November 2018
*/

// Trinket M0
int latchPin = 3; // STCP  PB3  rpi_rp2040_pico: 2
int clockPin = 4; // SHCP  PB4  2040: 3
int dataPin  = 1; // DS    PB1  2040: 4

byte leds = 0;
byte uleds = 0;
byte pos = 15; // rightmost

byte slew = 5;

uint8_t ledval = 0;

void setup(void) {
    // setup_dotstar();

    // Serial.begin(9600);

    // while(!Serial) {

    // for (int i = 4 ; i > 0 ; i--) {
      // loop_dotstar(); // 4th iteration turns off dostar
    // }

    // Serial.print(DATENOW);

    pinMode(latchPin, OUTPUT);
    pinMode(dataPin,  OUTPUT);
    pinMode(clockPin, OUTPUT);
}

void _digitSelect(void) {
    uleds = pos;
    shiftOut(dataPin, clockPin, MSBFIRST, uleds);
}

void updateShiftRegister(void) {
    digitalWrite(latchPin, LOW);
    _digitSelect(); // digit 0 1 2 or 3 using 'pos' as the index

    uleds = leds;   // A-F 0-9 and a few other glyphs

    shiftOut(dataPin, clockPin, MSBFIRST, uleds); // paint the character's glyph!

    digitalWrite(latchPin, HIGH);
}

void blankleds(void) {
//    leds = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128;  // zero
    leds = 255;
    updateShiftRegister();
}

void setleds(void) {
    leds = ledval;
    updateShiftRegister();
    if (!EXPOSE_DIGIT_PAINTING) {
        delay(1); // CRITICAL - must be a finite, non-zero delay here
    } else {
        delay(400);
    }
}

void flash_digit(void) { // paint a single digit brightly, then immediately blank all LEDs
    if (EXPOSE_DIGIT_PAINTING) {
        // delay(122);
        delay(424); // to expose digit change
    }
    setleds();
    delay(1600);
    blankleds(); // waste no time in doing so!
}

void in_column_zero(void) {
    for (int i = REPETITIONS ; i>0; i--) {
        pos = 0 ; flash_digit();
    }
}

void in_column_one(void) {
    for (int i = REPETITIONS ; i>0; i--) {
        pos = 22 ; flash_digit();
    }
}

void in_column_two(void) {
    for (int i = REPETITIONS ; i>0; i--) {
        pos = 27 ; flash_digit();
    }
}

void in_column_three(void) {
    for (int i = REPETITIONS ; i>0; i--) {
       pos = 29 ; flash_digit();
    }
}

// encodings - use powers of two added together, to show a 7-segment glyph

void encode_zero(void) {  // 0
    ledval = 1 + 2 + 4 + 8 + 16 + 32 +  0 +   0;
}

void encode_one(void) {   // 1
    ledval = 0 + 2 + 4 + 0 +  0 +  0 +  0 +   0;
}

void encode_two(void) {   // 2
    ledval = 1 + 2 + 0 + 8 + 16 +  0 + 64 +   0;
}

void encode_three(void) { // 3
    ledval = 1 + 2 + 4 + 8 +  0 +  0 + 64 +   0;
}

void encode_four(void) {  // 4
    ledval = 0 + 2 + 4 + 0 +  0 + 32 + 64 +   0;
}

void encode_five(void) {  // 5
    ledval = 1 + 0 + 4 + 8 +  0 + 32 + 64 +   0;
}

void encode_six(void) {   // 6
    ledval = 1 + 0 + 4 + 8 + 16 + 32 + 64 +   0;
}

void encode_seven(void) { // 7
    ledval = 1 + 2 + 4 + 0 +  0 +  0 +  0 +   0;
}

void encode_eight(void) { // 8
    ledval = 1 + 2 + 4 + 8 + 16 + 32 + 64 +   0;
}

void encode_nine(void) {  // 9
    ledval = 1 + 2 + 4 + 0 +  0 + 32 + 64 +   0;
}

void encode_ltr_l(void) { // L
    ledval = 0 + 0 + 0 + 8 + 16 + 32 +  0 +   0;
}

void encode_ltr_a(void) { // A -- the letter, A
    ledval = 1 + 2 + 4 + 16 + 32 + 64;
}

void encode_ltr_b(void) { // b
    ledval = 4 + 8 + 16 + 32 + 64;
}

void encode_ltr_c(void) { // C
    ledval = 1 + 8 + 16 + 32;
}

void encode_ltr_d(void) { // d
    ledval = 2 + 4 + 8 + 16 + 64;
}

void encode_ltr_e(void) { // E
    ledval = 1 + 8 + 16 + 32 + 64;
}

void encode_ltr_f(void) { // F
    ledval = 1 + 0 + 16 + 32 + 64;
}

void encode_ltr_blank(void) { // blank
    ledval = 0 ;
}


// detailed messages to show on the 7-segment, 4-digit LED display:

void msg_a_24(void) { // message:  'A824'
    for (int j = 2;  j>0; j--) {
        for (int k = DURATION; k>0; k--) {
            encode_four();   in_column_zero();
            encode_two();    in_column_one();
            encode_eight();  in_column_two();
            encode_ltr_a();  in_column_three();
        }
    }
    delay(1000);
}

void msg_tttt(void) { // message: '3223'
    for (int j = 2;  j>0; j--) {
        for (int k = DURATION; k>0; k--) {
            //  columns 3 2 1 0  -- painted right to left!
            encode_three();  in_column_zero();   // print '3' in column '0'
            encode_two();    in_column_one();    // print '2' in column '1'
            encode_two();    in_column_two();    // print '2' in column '2'
            encode_three();  in_column_three();  // print '3' in column '3'
        }
    }
    delay(1000);
}

void msg_le(void) { // message:  'LE  '
    for (int j = 2;  j>0; j--) {
        for (int k = DURATION; k>0; k--) {
            encode_ltr_blank();  in_column_zero();
            encode_ltr_blank();  in_column_one();
            encode_ltr_e();      in_column_two();
            encode_ltr_l();      in_column_three();
        }
    }
    delay(1000);
}

void msg_bef0(void) { // message: 'bEF0'
    for (int j = 2;  j>0; j--) {
        for (int k = DURATION; k>0; k--) {
            encode_zero();   in_column_zero();
            encode_ltr_f();  in_column_one();
            encode_ltr_e();  in_column_two();
            encode_ltr_b();  in_column_three();
        }
    }
    delay(1000);
}

void msg_foca(void) { // message: 'F0CA'
    for (int j = 2;  j>0; j--) {
        for (int k = DURATION; k>0; k--) {
            encode_ltr_a();  in_column_zero();
            encode_ltr_c();  in_column_one(); 
            encode_zero();   in_column_two();
            encode_ltr_f();  in_column_three();
        }
    }
    delay(1000);
}

void msg_cafe(void) { // message: 'CAFE'
    for (int j = 2;  j>0; j--) {
        for (int k = DURATION; k>0; k--) {
            encode_ltr_e();  in_column_zero();
            encode_ltr_f();  in_column_one();
            encode_ltr_a();  in_column_two();
            encode_ltr_c();  in_column_three();
        }
    }
    delay(1000);
}






// 0xfe is horiz bar            // 1110
// 0xfb is lower horiz bar      // 1011
// 0xfd is lower right vert bar // 1101
// 0xf7 is lower left vert bar  // 0111
// ledval = 255 - 128 - 64 ; // upper right

void quickfive(void) {
  ledval = 255 - 128 -   0 - 32  - 16 - 0 - 4 - 2 - 1 ;
}

void quicksix(void) {
    ledval = 255 - 128 -  0 - 32 - 16 - 8 - 4 - 2 - 1 ;
}

void quickseven(void) {
    // seven: ledval = 255 - 128 -  64 - 2 - 16;
    ledval = 255 - 128 -  64 - 2 - 16;
}

void quickeight(void) {
  ledval = 0;
}


void quickfour(void) {
  ledval = 255 - 128 -  64 - 32   - 0 - 0 - 0 - 2 - 1 ;
}

void quickthree(void) {
  ledval = 255 -   0 -  64 -  0  - 16 - 0 - 4 - 2 - 1 ;
}

void quicktwo(void) {
  ledval = 255 - 128 -  64 -  0   - 16   - 8  -4   - 1 ;
}

void quickone(void) {
   ledval = 255 - 128 -  64 - 0 -  2 ;
}

void quicknine(void) {
  ledval = 255 - 64 - 32 - 16 - 4 - 2 - 1;
  //  -1 horiz mid bar
  //  -1 completes a '9' bottom segment
}

void quick_iteration(void) {
  in_column_zero();
  delay(899);
}
void loop(void) {
    // blankleds();
    // delay(40);
    // ledval = 255 - 128 - 64 - 32 - 16 - 8 - 4 - 2 - 1 ;

    // six:   ledval = 255 - 128 -   0 - 32  - 16 - 8 - 4 - 2 - 1 ;
    // five:  ledval = 255 - 128 -   0 - 32  - 16 - 0 - 4 - 2 - 1 ;
    // four:  ledval = 255 - 128 -  64 - 32   - 0 - 0 - 0 - 2 - 1 ;
    // three: ledval = 255 -   0 -  64 -  0  - 16 - 0 - 4 - 2 - 1 ;
    // two:   ledval = 255 - 128 -  64 -  0   - 16   - 8  -4   - 1 ;
    // one:   ledval = 255 - 128 -  64 - 0 -  2 ;
    // zero   ledval = 255 - 128 -  64 - 32 - 16 - 8 - 4 - 2;
    // seven: ledval = 255 - 128 -  64 - 2 - 16;
    // eight: ledval =   0;
    // blank: ledval = 255;

    // uint8_t ledval = 0;
    uint8_t cpyledval;

    ledval = 0;
    quicksix();

    cpyledval != ledval;

    ledval = cpyledval;

    // encode_ltr_a();
    // quicknine();
    // ledval ^= ledval;
    // in_column_zero();
    int i = 0;
    // delay(1000);
    quickone();
    quick_iteration();
    quicktwo();
    quick_iteration();
    quickthree();
    quick_iteration();
    quickfour();
    quick_iteration();
    quickfive();
    quick_iteration();
    quicksix();
    quick_iteration();
    quickseven();
    quick_iteration();
    quickeight();
    quick_iteration();
    quicknine();
    quick_iteration();

  //  in_column_zero(); delay(1000);
/*
    in_column_zero();
    in_column_zero();
    in_column_zero();
    in_column_zero();
    in_column_zero();
*/
    // msg_tttt();
    // msg_a_24();
    // msg_le();
    // msg_foca(); msg_cafe();
    // msg_bef0();

    // hold display blank for a while:
    // i = 128; ledval = i; in_column_zero(); blankleds();
    // delay(2 * (111 + slew));
}
// ENiD,



#if 0
{
  "version": 1,
  "author": "wa1tnr - factory demo modified",
  "editor": "wokwi",
  "parts": [
    { "type": "wokwi-attiny85", "id": "tiny", "top": 320, "left": 185, "attrs": {} },
    { "type": "wokwi-74hc595", "id": "sr1", "top": 260, "left": 100, "rotate": 180, "attrs": {} },
    { "type": "wokwi-74hc595", "id": "sr2", "top": 260, "left": 225, "rotate": 180, "attrs": {} },
    {
      "type": "wokwi-7segment",
      "id": "sevseg1",
      "top": 60,
      "left": 108,
      "attrs": { "digits": "4", "color": "#0f0", "colon": "true" }
    },
    { "type": "wokwi-ds1307", "id": "rtc1", "top": 310, "left": 260, "attrs": {} },
    {
      "type": "wokwi-resistor",
      "id": "r1",
      "top": 200.76,
      "left": -64.85,
      "rotate": 90,
      "attrs": { "value": "220" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r2",
      "top": 209.05,
      "left": 232.5,
      "attrs": { "value": "1" }
    },
    {
      "type": "wokwi-resistor",
      "id": "r3",
      "top": 194.75,
      "left": 151.95,
      "rotate": 90,
      "attrs": {}
    },
    {
      "type": "wokwi-resistor",
      "id": "r4",
      "top": 180.45,
      "left": 139.15,
      "rotate": 90,
      "attrs": {}
    },
    {
      "type": "wokwi-resistor",
      "id": "r5",
      "top": 192.5,
      "left": 128.62,
      "rotate": 90,
      "attrs": {}
    },
    {
      "type": "wokwi-resistor",
      "id": "r6",
      "top": 187.98,
      "left": 114.31,
      "rotate": 90,
      "attrs": {}
    },
    {
      "type": "wokwi-resistor",
      "id": "r7",
      "top": 184.21,
      "left": 106.79,
      "rotate": 90,
      "attrs": {}
    },
    {
      "type": "wokwi-resistor",
      "id": "r8",
      "top": 185.71,
      "left": 95.49,
      "rotate": 90,
      "attrs": {}
    },
    {
      "type": "wokwi-resistor",
      "id": "r9",
      "top": 190.99,
      "left": 69.15,
      "rotate": 90,
      "attrs": {}
    }
  ],
  "connections": [
    [ "sr1:GND", "tiny:GND", "black", [ "v-10", "h-34", "v110", "h149" ] ],
    [ "sr2:GND", "tiny:GND", "black", [ "v-10", "h-48", "v110", "h41" ] ],
    [ "tiny:VCC", "sevseg1:COM", "red", [ "v-153", "h69", "v-30", "h-27" ] ],
    [ "r1:2", "sr1:GND", "green", [ "h0" ] ],
    [ "r2:1", "sevseg1:COM", "green", [ "v0" ] ],
    [ "r2:2", "sevseg1:DIG2", "green", [ "v0.79", "h12.65", "v-225.09", "h-113.67" ] ],
    [ "sevseg1:DIG4", "r2:2", "green", [ "v65.96", "h79.81", "v24.84", "h3.76" ] ],
    [
      "sevseg1:DIG3",
      "r2:2",
      "green",
      [ "v-45.94", "h113.5", "v199.49", "h-33.88", "v7.53", "h2.26" ]
    ],
    [ "r3:1", "sevseg1:G", "green", [ "h0" ] ],
    [ "r3:2", "sr1:Q0", "white", [ "h18.82", "v84.22", "h-36.89", "v-26.35" ] ],
    [ "r4:2", "sr1:Q1", "green", [ "h0" ] ],
    [ "sevseg1:C", "r4:1", "green", [ "v0" ] ],
    [ "r5:2", "sr1:Q2", "green", [ "h0" ] ],
    [ "sevseg1:D", "r5:1", "green", [ "v0" ] ],
    [ "r6:2", "sr1:Q3", "green", [ "h0" ] ],
    [ "r6:1", "sevseg1:E", "green", [ "h0" ] ],
    [ "sr1:Q4", "r7:2", "green", [ "v0" ] ],
    [ "sevseg1:A", "r7:1", "green", [ "v-42.92", "h-119.67", "v129.48", "h4.52" ] ],
    [ "sevseg1:F", "r8:1", "green", [ "v-57.23", "h-159.38", "v157.34", "h12.8" ] ],
    [ "r8:2", "sr1:Q5", "green", [ "h0" ] ],
    [ "r9:2", "sr1:Q6", "green", [ "h0" ] ],
    [ "r9:1", "sevseg1:B", "green", [ "h-93.35", "v-179.73", "h177.66", "v-10.54", "h1.51" ] ]
  ]
}
#endif
#if 0
  above vandalized on purpose.  See upstream for proper implementation.
#endif
