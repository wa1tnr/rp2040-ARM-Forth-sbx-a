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
    leds = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128;  // zero
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


void loop(void) {
    // blankleds();
    // delay(40);
    // ledval = 255 - 128 - 64 - 32 - 16 - 8 - 4 - 2 - 1 ;



    // six:   ledval = 255 - 128 -  0 - 32 - 16 - 8 - 4 - 2 - 1 ;
    // five:  ledval = 255 - 128 -  0 - 32  - 16 - 0 - 4 - 2 - 1 ;
    // four:  ledval = 255 - 128 -  64 - 32  - 0 - 0 - 0 - 2 - 1 ;
    // three: ledval = 255 - 0 -  64 - 0  - 16 - 0 - 4 - 2 - 1 ;
    // two:   ledval = 255 - 128 -  64  - 16  - 8  -4   - 1 ;
    // one:   ledval = 255 - 128 -  64 - 2 ;
    // zero   ledval =  255 - 128 - 64 - 32 - 16 - 8 - 4 - 2;
    // seven: ledval = 255 - 128 - 64 - 2 - 16;
    // eight: ledval = 0;
    // blank: ledval = 255;

    ledval = 0;


    in_column_zero();
    int i = 0;
    // delay(1000);

    // msg_tttt();
    // msg_a_24();
    // msg_le();
    // msg_foca(); msg_cafe();
    // msg_bef0();

    // hold display blank for a while:
    // i = 128; ledval = i; in_column_zero(); blankleds();
    // delay(2 * (111 + slew));
}
// END.
