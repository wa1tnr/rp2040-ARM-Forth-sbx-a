#include <Arduino.h>
#define EXPOSED_DIGITS
#undef  EXPOSED_DIGITS

#define ULTRA_SLOW_ENABLED
#undef ULTRA_SLOW_ENABLED

const int latchPin = 2; /* STCP */
const int clockPin = 3; /* SHCP */
const int dataPin = 4; /* DS */

byte leds = 0;
byte uleds = 0;
byte pos = 15; // rightmost wrong value tho
               // zero 15   one 22   two 27   three 29  03 Jan 2022
byte bank = 0;

byte slew = 5;

uint8_t ledval = 0;

#define BLANKING 870

#define TICKED 22000


void timing_slowed(void) {
    for (volatile unsigned long t_slo = TICKED; t_slo > 0; t_slo--) { }
}

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
    digitalWrite(latchPin, LOW);

/*
    if (bank == 0) {
        uleds = 0;
        shiftOut(dataPin, clockPin, MSBFIRST, uleds);
    }
*/
    // (near?) LAST artificial slowing 14:54z 03 Jan 2022: // timing_slowed();
    _digitSelect(); // digit 0 1 2 3 4 5 6 or 7 using 'pos' as the index

/*
    if (bank == 1) {
        uleds = 0;
        shiftOut(dataPin, clockPin, MSBFIRST, uleds);
    }
*/

    uleds = leds; // A-F 0-9 and a few other glyphs
    shiftOut(dataPin, clockPin, MSBFIRST, uleds); // paint the character's glyph!
    digitalWrite(latchPin, HIGH);
}

#ifdef EXPOSED_DIGITS
#define SLOW_POV_DEMO -1
#define DURATION 2 // was '2'
#define REPETITIONS 2 // was '1'
#define EXPOSE_DIGIT_PAINTING -1
#endif

#ifndef EXPOSED_DIGITS
#define SLOW_POV_DEMO 0
#define DURATION 1 // was '2' for exposed mode
#define REPETITIONS 2 // was '1'
#define EXPOSE_DIGIT_PAINTING 0
#endif

void blankleds(void) {
    // leds = 255;
    leds = 0;
    updateShiftRegister();
}

#define MIN_BLANKING 1700
#define MIN_SHOWING 444

void setleds(void) {
    leds = ledval;
    updateShiftRegister();
    if (!EXPOSE_DIGIT_PAINTING) {
        for (volatile unsigned long t_min = MIN_BLANKING; t_min > 0; t_min--) { }
        // delay(1); // CRITICAL - must be a finite, non-zero delay here
    }
    else {
        // timing_slowed();
        for (volatile unsigned long t_set = MIN_SHOWING; t_set > 0; t_set--) { }
        // delay(1); // bright duration wokwi 14 dec
    }
}

// #define MIN_ON_TIME 17000000 // 17 million great for slow demo
// #define MIN_ON_TIME 170000 
#define MIN_ON_TIME 1700

void flash_digit(void) { // paint a single digit brightly, then immediately blank all LEDs
    if (EXPOSE_DIGIT_PAINTING) {
        if (SLOW_POV_DEMO) {
            // Serial1.print("debug - slow pov");
        }
    }
    setleds();

    if (EXPOSE_DIGIT_PAINTING) {
        // timing_slowed();
    }

    // targetting
    for (volatile unsigned long t_min_on = MIN_ON_TIME; t_min_on > 0; t_min_on--) { }

    blankleds(); // waste no time in doing so!
    // timing_slowed();
    // for (volatile unsigned long bl = BLANKING; bl > 0; bl--) { }
}

void proc_encoding(void) {
    uint8_t ledcpy;
    // ledcpy = ledval ^ 0xff; // this seems very good
    ledcpy = ledval;
    ledval = ledcpy;
}

void in_column_zero(void) {
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 15;
        flash_digit();
    }
}

void in_column_one(void) { // DIGIT 2
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 22;
        flash_digit();
    }
}

void in_column_two(void) {
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 27;
        flash_digit();
    }
}

void in_column_three(void) {
    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 29;
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
}

void setup_sr(void) {
    Serial1.begin(115200);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

#ifdef EXPOSED_DIGITS
#define REPS 2
#endif

#ifndef EXPOSED_DIGITS
// #define REPS 123
// #define REPS 128
// #define REPS 32
#define REPS 960
#endif


void t_btwn_msgs(void) {
// 22000 x 256 = 5632000

// for (volatile int idx = 256; idx > 0; idx --) {
// for (volatile int idx = (256 * 256) ; idx > 0; idx --) {
// ##bookmark
for (volatile unsigned long idx = (32 * 2) ; idx > 0; idx --) {
        timing_slowed(); timing_slowed(); timing_slowed(); timing_slowed();
        timing_slowed(); timing_slowed(); timing_slowed(); timing_slowed();
        timing_slowed(); timing_slowed(); timing_slowed(); timing_slowed();
        timing_slowed(); timing_slowed(); timing_slowed(); timing_slowed();

        timing_slowed(); timing_slowed(); timing_slowed(); timing_slowed();
        timing_slowed(); timing_slowed(); timing_slowed(); timing_slowed();
        timing_slowed(); timing_slowed(); timing_slowed(); timing_slowed();
        timing_slowed(); timing_slowed(); timing_slowed(); timing_slowed();
    }
}

void loop_sr(void) {

    blankleds();
        // timing_slowed();

// 32 bit 0 to 4.2 billion
    for (unsigned long count = REPS; count > 0; count--) {
        bank = 0;

        encode_seven();
        in_column_zero();

        encode_six();
        in_column_one();

        encode_five();
        in_column_two();

        encode_four();
        in_column_three();
    }

    t_btwn_msgs();

    blankleds();

    for (unsigned long count = REPS; count > 0; count--) {
        encode_three();
        in_column_zero();

        encode_two();
        in_column_one();

        encode_one();
        in_column_two();

        encode_zero();
        in_column_three();
    }

/*

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
*/
}

// END.
