// Mon 20 Dec 10:56:12 UTC 2021

// good solid define structures 02z 19 Dec

// Sun 19 Dec 02:19:51 UTC 2021  ONLINE edits

// for:
//  [ https://wokwi.com/arduino/new?template=pi-pico ]

// added bank selection code - works well 19 Dec 02z

// PERSISTENCE OF VISION technology demonstration.

// swap these two cpp directives as required:
#define EXPOSED_DIGITS
// #undef  EXPOSED_DIGITS

// swap as required:
#define ULTRA_SLOW_ENABLED
// #undef ULTRA_SLOW_ENABLED

// common anode 7 seg display:

// DIGIT goes to Vcc
// COMMON goes to Vcc
// segments go to ground.

// common cathode is also available in this simulator.

const int latchPin = 4; /* STCP */
const int clockPin = 3; /* SHCP */
const int dataPin = 2; /* DS */

byte leds = 0;
byte uleds = 0;
byte pos = 15; // rightmost wrong value tho
byte bank = 0;

byte slew = 5;

uint8_t ledval = 0;

void _bankSelect(void) {
    if (bank == 1) {
        uleds = 255;
        shiftOut(dataPin, clockPin, MSBFIRST, uleds);
        shiftOut(dataPin, clockPin, MSBFIRST, uleds);
        return;
    }
    if (bank == 0) {
        uleds = 0;
        shiftOut(dataPin, clockPin, MSBFIRST, uleds);
        shiftOut(dataPin, clockPin, MSBFIRST, uleds);
    }
}

void _digitSelect(void) {
    uleds = pos;
    shiftOut(dataPin, clockPin, MSBFIRST, uleds);
}

#ifdef ULTRA_SLOW_ENABLED
#define ULTRA_SLOW -1
#endif

#ifndef ULTRA_SLOW_ENABLED
#define ULTRA_SLOW 0
#endif

void updateShiftRegister(void) {
    digitalWrite(latchPin, HIGH); // off
    if (ULTRA_SLOW) delay(1); // new 19 Dec 02:15z - decent effect

//    _bankSelect(); // highest shift register bits 0 and 1 (Q0, Q1)
    if (bank == 0) {
        uleds = 0;
        shiftOut(dataPin, clockPin, MSBFIRST, uleds);
    }
    _digitSelect(); // digit 0 1 2 3 4 5 6 or 7 using 'pos' as the index

    if (bank == 1) {
        uleds = 0;
        shiftOut(dataPin, clockPin, MSBFIRST, uleds);
    }

    uleds = leds; // A-F 0-9 and a few other glyphs
    shiftOut(dataPin, clockPin, MSBFIRST, uleds); // paint the character's glyph!
    digitalWrite(latchPin, LOW); // on
}

#ifdef EXPOSED_DIGITS
#define SLOW_POV_DEMO -1
#define DURATION 2 // was '2'
#define REPETITIONS 4 // was '2'
#define EXPOSE_DIGIT_PAINTING -1
#endif

#ifndef EXPOSED_DIGITS
#define SLOW_POV_DEMO 0
#define DURATION 1 // was '2' for exposed mode
#define REPETITIONS 1 // was '1'
#define EXPOSE_DIGIT_PAINTING 0
#endif

void blankleds(void) {
    leds = 255;
    updateShiftRegister();
}

void setleds(void) {
    leds = ledval;
    updateShiftRegister();
    if (!EXPOSE_DIGIT_PAINTING) {
        delay(1); // CRITICAL - must be a finite, non-zero delay here
    }
    else {
        delay(1); // bright duration wokwi 14 dec
    }
}

void flash_digit(void) { // paint a single digit brightly, then immediately blank all LEDs
    if (EXPOSE_DIGIT_PAINTING) {
        delay(1);
        if (SLOW_POV_DEMO) {
            // Serial1.print("debug - slow pov");
            delay(8);
        }
    }
    setleds();

    if (EXPOSE_DIGIT_PAINTING) {
        delay(12);
    }

    blankleds(); // waste no time in doing so!
}

void proc_encoding(void) {
    uint8_t ledcpy;
    ledcpy = ledval ^ 0xff; // this seems very good
    //  XOR with 0xff seems to flip bits no problem.
    // this seems to be the only caveat when working
    // with common-OPPOSITE display (anode, cathode)
    ledval = ledcpy;
//  in_column_zero(); delay(4);
}

// pinout pins 1-6 L to R bottom  7 to 12 r to L
// digit 1 on the left (in sim is default and lights with no connection)

// drawing shows 1 thru 6 and 7 thru 12 but acknowledges more pins.
// probably a physical registration matter, only.

void in_column_zero(void) {
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 16; // neg 240 pos 15
        flash_digit();
    }
}

void in_column_one(void) { // DIGIT 2
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 32; // neg 233 pos 22
        flash_digit();
    }
}

void in_column_two(void) {
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 64; // neg 228 pos 27
        flash_digit();
    }
}

void in_column_three(void) {
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 128; // neg 226 pos 29
        flash_digit();
    }
}

void in_column_four(void) {
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 1; // neg 226 pos 29
        flash_digit();
    }
}
void in_column_five(void) {
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 2; // neg 226 pos 29
        flash_digit();
    }
}
void in_column_six(void) {
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 4; // neg 226 pos 29
        flash_digit();
    }
}
void in_column_seven(void) {
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 8; // neg 226 pos 29
        flash_digit();
    }
}

void encode_hw_testing(void) { // 3
    ledval = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128;
}

void encode_bitpattern_aa(void) { // low nybble
    ledval = 1 + 2 + 4 + 8;
}

void encode_bitpattern_bb(void) { // high nybble
    ledval = 16 + 32 + 64 + 128;
}

void msg_tttt(void) { // message: '3223'
    for (int j = 2; j > 0; j--) {
        for (int k = DURATION; k > 0; k--) {
            //  columns 3 2 1 0  -- painted right to left!
//          encode_three();  in_column_zero();   // print '3' in column '0'
            encode_hw_testing();
            in_column_zero();
            encode_hw_testing();
            in_column_two();
            encode_bitpattern_aa();
            in_column_zero();
            encode_bitpattern_bb();
            in_column_zero();
        }
    }
    delay(10);
}

int count = -1;
char buffer[8];
int line_reset;

void encode_one(void) { // 1
    ledval = 0 + 2 + 4 + 0 + 0 + 0 + 0 + 0;
}

void encode_seven(void) { // 7
    ledval = 1 + 2 + 4 + 0 + 0 + 0 + 0 + 0;
}

void encode_ltr_l(void) { // L
    ledval = 0 + 0 + 0 + 8 + 16 + 32 + 0 + 0;
}

void encode_zero(void) { // 0
    ledval = 1 + 2 + 4 + 8 + 16 + 32 + 0 + 0;
}

void encode_three(void) { // 3
    ledval = 1 + 2 + 4 + 8 + 0 + 0 + 64 + 0;
}

void encode_four(void) { // 4
    ledval = 0 + 2 + 4 + 0 + 0 + 32 + 64 + 0;
}

void encode_five(void) { // 5
    ledval = 1 + 0 + 4 + 8 + 0 + 32 + 64 + 0;
}

void encode_six(void) { // 6
    ledval = 1 + 0 + 4 + 8 + 16 + 32 + 64 + 0;
}

void encode_two(void) { // 2
    ledval = 1 + 2 + 0 + 8 + 16 + 0 + 64 + 0;
}

void encode_eight(void) { // 8
    ledval = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 0;
}

void encode_nine(void) { // 9
    ledval = 1 + 2 + 4 + 8 + 0 + 32 + 64 + 0;
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
    ledval = 0;
}

void msg_le(void) { // message:  'LE  '
    for (int j = 2; j > 0; j--) {
        for (int k = DURATION; k > 0; k--) {
            encode_ltr_blank();
            in_column_zero();
            encode_ltr_blank();
            in_column_one();
            encode_ltr_e();
            in_column_two();
            encode_ltr_l();
            in_column_three();
        }
    }
    delay(10);
}

void msg_bef0(void) { // message: 'bEF0'
    for (int j = 2; j > 0; j--) {
        for (int k = DURATION; k > 0; k--) {
            encode_zero();
            in_column_zero();
            encode_ltr_f();
            in_column_one();
            encode_ltr_e();
            in_column_two();
            encode_ltr_b();
            in_column_three();
        }
    }
    delay(10);
}

void msg_foca(void) { // message: 'F0CA'
    for (int j = 2; j > 0; j--) {
        for (int k = DURATION; k > 0; k--) {
            encode_ltr_a();
            in_column_zero();
            encode_ltr_c();
            in_column_one();
            encode_zero();
            in_column_two();
            encode_ltr_f();
            in_column_three();
        }
    }
    delay(10);
}

void msg_cafe(void) { // message: 'CAFE'
    for (int j = 2; j > 0; j--) {
        for (int k = DURATION; k > 0; k--) {
            encode_ltr_e();
            in_column_zero();
            encode_ltr_f();
            in_column_one();
            encode_ltr_a();
            in_column_two();
            encode_ltr_c();
            in_column_three();
        }
    }
    delay(10);
}

void letter_test(void) {
    for (int j = 2; j > 0; j--) {
        for (int k = DURATION; k > 0; k--) {
            encode_ltr_d();
            in_column_four();
            blankleds();

            encode_ltr_c();
            in_column_five();
            blankleds();

            encode_ltr_b();
            in_column_six();
            blankleds();

            encode_ltr_a();
            in_column_seven();
        }
    }
    delay(10);
}

void lfc_test(void) {
    msg_le();
    msg_foca();
    msg_cafe();
}

void msg_full_house(void) { // message: '01234567'
    for (int j = 2; j > 0; j--) {
        for (int k = DURATION; k > 0; k--) {
            encode_seven();
            in_column_zero();
            encode_six();
            in_column_one();
            encode_five();
            in_column_two();
            encode_four();
            in_column_three();

            encode_three();
            in_column_four();
            encode_two();
            in_column_five();
            encode_one();
            in_column_six();
            encode_zero();
            in_column_seven();
        }
    }
    delay(10);
}

void setup() {
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

#ifdef EXPOSED_DIGITS
#define REPS 1
#endif

#ifndef EXPOSED_DIGITS
#define REPS 4
#endif

void loop(void) {

    blankleds();
    delay(1);
/*
    lfc_test();
    delay(4000);
    letter_test();

    delay(400);
  
  */

    for (int count = REPS; count > 0; count--) {
        bank = 0;
        encode_seven();
        in_column_zero();
        encode_six();
        in_column_one();
        encode_five();
        in_column_two();
        encode_four();
        in_column_three();

        encode_three();
        in_column_four();
        encode_two();
        in_column_five();
        encode_one();
        in_column_six();
        encode_zero();
        in_column_seven();
    }

    for (int count = REPS; count > 0; count--) {

        bank = 1;
        encode_ltr_blank();
        in_column_zero();
        encode_ltr_e();
        in_column_one();
        encode_ltr_e();
        in_column_two();
        encode_ltr_f();
        in_column_three();

        encode_ltr_f();
        in_column_four();
        encode_zero();
        in_column_five();
        encode_ltr_c();
        in_column_six();
        encode_ltr_blank();
        in_column_seven();
    }

/*

    bank = 0;
    msg_full_house();
    delay(2000);
    blankleds();
    delay(2000);

    bank = 1;
    msg_full_house();
    delay(2000);
    blankleds();
    delay(2000);
*/

}

/**********   d o c u m e n t a t i o n   **********/
#if 0


#endif
// END.
