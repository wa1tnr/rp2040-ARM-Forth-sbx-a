// Tue 21 Dec 06:10:21 UTC 2021
// Mon 20 Dec 11:50:35 UTC 2021

// for:
// falstad avrjs with both 7Seg LED arrays and shift registers
// includes latch circuit - mosfet N-Channel to sink current.
// reversed sense of latch to accomodate the MOSFET method.
// PERSISTENCE OF VISION technology demonstration.

#define COMMON_CATHODE_ARRAYS
// #undef COMMON_CATHODE_ARRAYS

#ifdef COMMON_CATHODE_ARRAYS
#define COMMON_CATHODE -1
#endif

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
    digitalWrite(latchPin, LOW); // off
    uleds = leds; // A-F 0-9 and a few other glyphs
    shiftOut(dataPin, clockPin, MSBFIRST, uleds); // paint the character's glyph!
    digitalWrite(latchPin, HIGH); // on
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
    leds = 0;
    updateShiftRegister();
}

void setleds(void) {
    leds = ledval;
    updateShiftRegister();
    delay(1); // bright duration wokwi 14 dec
}




void flash_digit(void) { // paint a single digit brightly, then immediately blank all LEDs
    setleds();
    Serial.println(" setleds. ");
    delay(22);
//  blankleds(); // waste no time in doing so!
}


void proc_encoding(void) {

    uint8_t ledcpy;
    ledcpy = ledval ^0xff; // potentially inverted
    ledval = ledcpy; // forgot this!


/*
    if (COMMON_CATHODE) { // undo the inversion
        ledcpy = ledval ^ 0xff; // this seems very good
        //  XOR with 0xff seems to flip bits no problem.
        // this seems to be the only caveat when working
        // with common-OPPOSITE display (anode, cathode)
    }
    ledval = ledcpy;
    */
//  in_column_zero(); delay(4);

}

// pinout pins 1-6 L to R bottom  7 to 12 r to L
// digit 1 on the left (in sim is default and lights with no connection)

// drawing shows 1 thru 6 and 7 thru 12 but acknowledges more pins.
// probably a physical registration matter, only.

void in_column_none(void) {
    // proc_encoding();
    flash_digit();
    Serial.print("  flash_digit column_none done.  ");
    delay(4);
}

void in_column_zero(void) {
//    proc_encoding();
    for (int i = REPETITIONS; i > 0; i--) {
        pos = 16; // neg 240 pos 15
        flash_digit();
        Serial.print("  flash_digit done.  ");
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

void encode_bitpattern_aa(void) { // low nybble
    ledval = 1 + 2 + 4 + 8;
}

void encode_bitpattern_bb(void) { // high nybble
    ledval = 16 + 32 + 64 + 128;
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

// cruft below

void encode_ltr_f(void) { // F
    ledval = 1 + 0 + 16 + 32 + 64;
    ledval = ledval  - 16; // kludge do not use in production system
}


// and above



void encode_ltr_blank(void) { // blank
    ledval = 0;
}

void setup() {
    Serial.begin(9600);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    digitalWrite (latchPin, LOW); // disable output
}

void encode_hw_testing(void) { // 3
    // ledval = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128;

    ledval =  1; // baseline
    //   1 is top bar     ('A')
    //   2 is upper right ('B')
    //   4 is lower right ('C')
    //   8 is confusingly also a 'D' - check on this
    //  16 is bottom ('D')
    //  32 is lower left ('E')
    //  64 is upper left ('F')
    // 128 is noled
}


void loop(void) {

  //   SYSTEM ITSELF inconsistent.  Nothing for that.


    // encode_nine(); // GOOD
    // encode_eight(); // GOOD
    // encode_seven(); // GOOD
    // encode_six(); // GOOD
    // encode_five(); // GOOD

    //  >>>>> ERROR encode_four(); // swapped left to right but otherwise okay

    // encode_three(); // GOOD
    //  >>>>> ERROR encode_two(); // comes in as a 9 perfectly.
    // encode_zero(); GOOD
    // encode_ltr_a(); // kerfuncten
    // encode_ltr_b(); // GOOD
    //   >>>>>> ERROR   encode_ltr_c(); // really strange result
    // encode_ltr_d(); // GOOD
    //   >>>>>>  ERROR   encode_ltr_e(); // testing
    // since '3' and 'E' are similar/symmetric (maybe) and 'E' is wrong ..


    encode_ltr_f(); // gave a perfect 'E' which is a new behavior.  wigo.



    // ltr_f comes in as c!
    // encode_ltr_f(); // d and b are fine but c is wrong
    // encode_eight(); // GOOD
    // encode_hw_testing();
    in_column_none();
    while (-1); // hold forever
}

/**********   d o c u m e n t a t i o n   **********/
#if 0


#endif
// END.
