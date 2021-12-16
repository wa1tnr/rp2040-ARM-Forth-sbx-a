// Wednesday 15 Dec 2021  22:09:17z

#define EXPOSED_DIGITS
#undef EXPOSED_DIGITS
#define EXPOSED_DIGITS
#undef EXPOSED_DIGITS

// PERSISTENCE OF VISION technology demonstration.

// common anode 7 seg display:

// DIGIT goes to Vcc
// COMMON goes to Vcc
// segments go to ground.

//  [ https://wokwi.com/arduino/new?template=pi-pico ]

const int latchPin = 2;  /* STCP */
const int clockPin = 3;  /* SHCP */
const int dataPin  = 4;  /* DS */

byte leds = 0;
byte uleds = 0;
byte pos = 15; // rightmost wrong value tho

byte slew = 5;

uint8_t ledval = 0;

void _digitSelect(void) {
    uleds = pos;
    shiftOut(dataPin, clockPin, MSBFIRST, uleds);
}

void updateShiftRegister(void) {
    digitalWrite(latchPin, LOW);
    _digitSelect(); // digit 0 1 2 3 4 5 6 or 7 using 'pos' as the index
     uleds = leds;   // A-F 0-9 and a few other glyphs
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
#define DURATION 72 // was '2' for exposed mode
#define REPETITIONS 2 // was '1'
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
    } else {
        delay(1); // bright duration wokwi 14 dec
    }
}

void flash_digit(void) { // paint a single digit brightly, then immediately blank all LEDs
    if (EXPOSE_DIGIT_PAINTING) {
      delay(1);
        if (SLOW_POV_DEMO) {
          // Serial1.print("debug - slow pov");
          delay(297);
        }
    }
    setleds();

    if (EXPOSE_DIGIT_PAINTING) { delay (200);}

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
    for (int i = REPETITIONS ; i>0; i--) {
        pos = 1 ; // neg 240 pos 15
        flash_digit();
    }
}

void in_column_one(void) { // DIGIT 2
proc_encoding();
    for (int i = REPETITIONS ; i>0; i--) {
        pos = 2 ; // neg 233 pos 22
        flash_digit();
    }
}

void in_column_two(void) {
  proc_encoding();
    for (int i = REPETITIONS ; i>0; i--) {
        pos = 4 ; // neg 228 pos 27
        flash_digit();
    }
}

void in_column_three(void) {
  proc_encoding();
    for (int i = REPETITIONS ; i>0; i--) {
       pos = 8 ; // neg 226 pos 29
       flash_digit();
    }
}

void in_column_four(void) {
  proc_encoding();
    for (int i = REPETITIONS ; i>0; i--) {
       pos = 16 ; // neg 226 pos 29
       flash_digit();
    }
}
void in_column_five(void) {
  proc_encoding();
    for (int i = REPETITIONS ; i>0; i--) {
       pos = 32 ; // neg 226 pos 29
       flash_digit();
    }
}
void in_column_six(void) {
  proc_encoding();
    for (int i = REPETITIONS ; i>0; i--) {
       pos = 64 ; // neg 226 pos 29
       flash_digit();
    }
}
void in_column_seven(void) {
  proc_encoding();
    for (int i = REPETITIONS ; i>0; i--) {
       pos = 128 ; // neg 226 pos 29
       flash_digit();
    }
}

void encode_hw_testing(void) { // 3
    ledval = 1 + 2 + 4 + 8 +  16 +  32 + 64 + 128;
}

void encode_bitpattern_aa(void) { // low nybble
    ledval = 1 + 2 + 4 + 8;
}

void encode_bitpattern_bb(void) { // high nybble
    ledval = 16 + 32 + 64 + 128;
}

void msg_tttt(void) { // message: '3223'
    for (int j = 2;  j>0; j--) {
        for (int k = DURATION; k>0; k--) {
            //  columns 3 2 1 0  -- painted right to left!
//          encode_three();  in_column_zero();   // print '3' in column '0'
            encode_hw_testing(); in_column_zero();
            encode_hw_testing(); in_column_two();
            encode_bitpattern_aa(); in_column_zero();
            encode_bitpattern_bb(); in_column_zero();
        }
    }
    delay(1000);
}

int count = -1;
char buffer[8];
int line_reset;

void encode_one(void) {   // 1
    ledval = 0 + 2 + 4 + 0 +  0 +  0 +  0 +   0;
}

void encode_seven(void) { // 7
    ledval = 1 + 2 + 4 + 0 +  0 +  0 +  0 +   0;
}

void encode_ltr_l(void) { // L
    ledval = 0 + 0 + 0 + 8 + 16 + 32 +  0 +   0;
}

void encode_zero(void) {  // 0
    ledval = 1 + 2 + 4 + 8 + 16 + 32 +  0 +   0;
}

void encode_three(void) { // 3
    ledval = 1 + 2 + 4 + 8 +  0 +  0 + 64 +   0;
}

// three has 1 2 4 8 and 64 set.  needs mid bar.
// what bit has never been set so far? probably 64.

void encode_four(void) {  // 4
    ledval = 0 + 2 + 4 + 0 +  0 + 32 + 64 +   0;
}

void encode_five(void) {  // 5
    ledval = 1 + 0 + 4 + 8 +  0 + 32 + 64 +   0;
}

void encode_six(void) {   // 6
    ledval = 1 + 0 + 4 + 8 + 16 + 32 + 64 +   0;
}

void encode_two(void) {   // 2
    ledval = 1 + 2 + 0 + 8 + 16 +  0 + 64 +   0;
}

void encode_eight(void) { // 8
    ledval = 1 + 2 + 4 + 8 + 16 + 32 + 64 +   0;
}

void encode_nine(void) {  // 9
    ledval = 1 + 2 + 4 + 8 +  0 + 32 + 64 +   0;
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

// 1 7 L 0 3 4 5 6 2 8 9
// 1 2 3 4 5 6 7 8 9 0 L so far.


// a b c d e f blank


void msg_le(void) { // message:  'LE  '
    for (int j = 2;  j>0; j--) {
        for (int k = DURATION; k>0; k--) {
            encode_ltr_blank();  in_column_zero();
            encode_ltr_blank();  in_column_one();
            encode_ltr_e();      in_column_two();
            encode_ltr_l();      in_column_three();
        }
    }
    delay(1500);
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
    delay(1500);
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
    delay(1500);
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
    delay(1500);
}

void letter_test(void) {
    for (int j = 2;  j>0; j--) {
        for (int k = DURATION; k>0; k--) {
            encode_ltr_d(); in_column_four();
            blankleds(); // shifting not blanking

            encode_ltr_c(); in_column_five();
            blankleds();

            encode_ltr_b(); in_column_six();
            blankleds();

            encode_ltr_a(); in_column_seven();
        }
    }
    delay(1500);
}

void lfc_test(void) {
    msg_le();
    msg_foca();
    msg_cafe();
}


void msg_full_house(void) { // message: '01234567'
    for (int j = 2;  j>0; j--) {
        for (int k = DURATION; k>0; k--) {
            encode_seven();  in_column_zero();
            encode_six();    in_column_one();
            encode_five();   in_column_two();
            encode_four();   in_column_three();

            encode_three();  in_column_four();
            encode_two();    in_column_five();
            encode_one();    in_column_six();
            encode_zero();   in_column_seven();
        }
    }
    delay(1500);
}


void setup() {
    Serial1.begin(115200);
    // annoying // Serial1.println("Begin.");
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin,  OUTPUT);
}

void loop(void) {

    blankleds();
    delay(400);
    lfc_test();
    delay(4000);
    letter_test();

    delay(400);
    msg_full_house();
}

/**********   d o c u m e n t a t i o n   **********/
#if 0

Functional program and wiring.  (15 Dec 2021, 05:49z)

The program operates through persistence of vision.

The display shows information quite briefly, then blanks,
then shows something else.

Due to the way people experience rapidly flashing information
(digital signs) the effect is similar to as if the light source
was on constantly.

The program has adjustments built-in to expose the use of
persistence of vision techniques.  The technique has power-
savings features - there are never more than eight segments
lit at any one instant in time, limiting the maximum
current the hardware might draw.

#endif
#if 0

 [ http://www.cplusplus.com/reference/cstdio/snprintf/]

int snprintf ( char * s, size_t n, const char * format, ... );

Write formatted output to sized buffer composes a string with
the same text that would be printed if format was used on printf,
but instead of be printed, the content is stored as a C string in
the buffer pointed by s (taking n as the maxium buffer capacity
to fill).

#endif

#if 0
3V3 is the main 3.3V supply to RP2040 and its I/O, generated by
the on-board SMPS.

This pin can be used to power external circuitry (maximum
output current will depend on RP2040 load and VSYS voltage,
it is recommended to keep the load on this pin less than 300mA).

Tue 14 Dec 20:09:25 UTC 2021

#endif
// END.
