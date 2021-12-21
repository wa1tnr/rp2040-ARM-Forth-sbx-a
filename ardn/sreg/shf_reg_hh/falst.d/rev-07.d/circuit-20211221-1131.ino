// Tue 21 Dec 11:34:15 UTC 2021

const int sr_data = 2;
const int sr_clock = 3;
const int sr_latch = 4;

void setup(void) {
  pinMode(sr_data, 1);
  pinMode(sr_clock, 1);
  pinMode(sr_latch, 1);
}

byte some_data = 1;

void loop(void) {
  digitalWrite(sr_latch, LOW) ;
  shiftOut(sr_data, sr_clock, MSBFIRST, 255);
  digitalWrite(sr_latch, HIGH) ;

  delay(12);
  for (int iter = 4; iter > -1; iter--) {
    shiftOut(sr_data, sr_clock, MSBFIRST, 0); // clearing
  }
  delay(5);
  shiftOut(sr_data, sr_clock, MSBFIRST, some_data);
  digitalWrite(sr_latch, HIGH) ;
//  delay(1);
for (volatile int count = 800; count > 0; count--) { }
  some_data = some_data * 2; // left shift
  if (some_data == 128) { some_data = 1; }
  if (some_data > 127) {some_data = 1; }
  if (some_data < 1)  {some_data = 1; }
}
