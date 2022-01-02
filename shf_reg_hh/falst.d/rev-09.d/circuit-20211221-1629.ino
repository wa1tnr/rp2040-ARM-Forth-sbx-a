// Wed 22 Dec 13:18:23 UTC 2021

// working program? captured

const int sr_data = 2;
const int sr_clock = 3;
const int sr_latch = 4;

byte ledval = 0;
const byte ledv_a = 119;
/*
void encode_ltr_a(void) { // A -- the letter, A
    // ledval = 1 + 2 + 4 + 16 + 32 + 64;
    ledval = 119;
}
*/

const byte ledv_b = 124;
/*
void encode_ltr_b(void) { // b
    ledval = 4 + 8 + 16 + 32 + 64;
    ledval = 124 ;
}
*/
/*
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
*/
void encode_ltr_blank(void) { // blank
    ledval = 0 ;
}

byte some_data = 1;

void clear_display(void) {
  digitalWrite(sr_latch, LOW) ;
  for (int iter = 3; iter > -1; iter--) {
    shiftOut(sr_data, sr_clock, MSBFIRST, 0); // clearing
  }
}

void tell_display(void) {
  digitalWrite(sr_latch, LOW) ;
  cli();
  for (volatile int lag = 1288; lag > 0; lag--) { }
  shiftOut(sr_data, sr_clock, MSBFIRST, some_data);
  digitalWrite(sr_latch, HIGH);
  for (volatile int count = 25888; count > 0; count--) { }
}

/*
void incr_some_data(void) {
  some_data = some_data * 2 ;
  if (some_data > 66) { some_data = 1; }
}
*/
void setup(void) {
  pinMode(sr_data, 1);
  pinMode(sr_clock, 1);
  pinMode(sr_latch, 1);
}

void loop(void) {
  // encode_ltr_a();
  ledval = ledv_a;
  some_data = ledv_a ; ledval; // use encode words to fill ledval
  tell_display();

  // encode_ltr_b();
  ledval = ledv_b;
  some_data = ledval;
  tell_display();
/*
  encode_ltr_c();
  some_data = ledval;
  tell_display();

  encode_ltr_d();
  some_data = ledval;
  tell_display();

  encode_ltr_e();
  some_data = ledval;
  tell_display();

  encode_ltr_f();
  some_data = ledval;
  tell_display();
*/
  encode_ltr_blank();
  some_data = ledval;
  tell_display();

}

// 22 December 2021 at 13:18 UTC
// END.
