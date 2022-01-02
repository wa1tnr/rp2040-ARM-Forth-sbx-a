// works with this circuit sim in this one context ;)

// Wed 22 Dec 13:54:36 UTC 2021

// zurkipfe

#define DATENOW     "Wed Dec 22 14:10:57 UTC 2021"

/*
Adafruit Arduino - Lesson 4. 8 LEDs and a Shift Register
Simon Monk mods: wa1tnr  27 November 2018
*/

int latchPin = 4;
int clockPin = 3;
int dataPin  = 2;

byte leds = 0;
byte uleds = 0;
byte pos = 15; // rightmost

byte slew = 2;

uint8_t ledval = 0;

void setup(void) {
    Serial.begin(9600);
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
    leds = 0;
    updateShiftRegister();
}

#define EXPOSE_DIGIT_PAINTING 0

void setleds(void) {
    leds = ledval;
    updateShiftRegister();
    if (!EXPOSE_DIGIT_PAINTING) {
        delay(1); // CRITICAL - must be a finite, non-zero delay here
    } else {
        delay(4);
    }
}

void flash_digit(void) { // paint a single digit brightly, then immediately blank all LEDs
    setleds();
    blankleds(); // waste no time in doing so!
}

#define REPETITIONS 2

void in_column_zero(void) {
        pos = 15 ; flash_digit();
}

void in_column_one(void) {
        pos = 22 ; flash_digit();
}

void in_column_two(void) {
        pos = 27 ; flash_digit();
}

void in_column_three(void) {
       pos = 29 ; flash_digit();
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

#define DURATION 2

void msg_a_24(void) { // message:  'A824'
            encode_four();   in_column_zero();
            encode_two();    in_column_one();
            encode_eight();  in_column_two();
            encode_ltr_a();  in_column_three();
    delay(10);
}

void msg_tttt(void) { // message: '3223'
            //  columns 3 2 1 0  -- painted right to left!
            encode_three();  in_column_zero();   // print '3' in column '0'
            encode_two();    in_column_one();    // print '2' in column '1'
            encode_two();    in_column_two();    // print '2' in column '2'
            encode_three();  in_column_three();  // print '3' in column '3'
    delay(10);
}

void msg_le(void) { // message:  'LE  '
            encode_ltr_blank();  in_column_zero();
            encode_ltr_blank();  in_column_one();
            encode_ltr_e();      in_column_two();
            encode_ltr_l();      in_column_three();
    delay(2);
}

void msg_bef0(void) { // message: 'bEF0'
            encode_zero();   in_column_zero();
            encode_ltr_f();  in_column_one();
            encode_ltr_e();  in_column_two();
            encode_ltr_b();  in_column_three();
    delay(2);
}

void msg_foca(void) { // message: 'F0CA'
            encode_ltr_a();  in_column_zero();
            encode_ltr_c();  in_column_one(); 
            encode_zero();   in_column_two();
            encode_ltr_f();  in_column_three();
    delay(2);
}

void msg_cafe(void) { // message: 'CAFE'
            encode_ltr_e();  in_column_zero();
            encode_ltr_f();  in_column_one();
            encode_ltr_a();  in_column_two();
            encode_ltr_c();  in_column_three();
    delay(2);
}


void loop(void) {
    blankleds();
    delay(2);
    ledval = 0;
    int i = 0;
    delay(2);

 //   msg_tttt();
 //   msg_a_24();
    msg_le(); msg_foca(); msg_cafe();
    msg_bef0();

    // hold display blank for a while:
    i = 128; ledval = i; in_column_zero(); blankleds();
    delay(2 * (11 + slew));
}

// END.
