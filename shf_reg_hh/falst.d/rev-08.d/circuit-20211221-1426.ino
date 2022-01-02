// Tue 21 Dec 14:30:17 UTC 2021

// working program? captured

const int sr_data = 2;
const int sr_clock = 3;
const int sr_latch = 4;

void setup(void) {
  pinMode(sr_data, 1);
  pinMode(sr_clock, 1);
  pinMode(sr_latch, 1);
  delay(4);
}

byte some_data = 1;

void loop(void) {
  digitalWrite(sr_latch, LOW) ;
  for (int iter = 3; iter > -1; iter--) {
    shiftOut(sr_data, sr_clock, MSBFIRST, 0); // clearing
  }
  shiftOut(sr_data, sr_clock, MSBFIRST, some_data);
  digitalWrite(sr_latch, HIGH) ;

for (volatile int count = 1400; count > 0; count--) { }
  // some_data = some_data * 2; // left shift
  some_data = some_data * 2 ;
  if (some_data > 127) {some_data = 1; }
}
