// circuit-20211220-0120-aa.ino
// 01:57z 20 Dec Monday
// staggered clocks running at different rates

#define SR_DATA 2
#define SR_CLK 3

void cpl(int pin) {
  bool state = digitalRead(pin);
  state = !state;
  digitalWrite(pin, state);
}

void setup() {
  pinMode(SR_DATA, 1); // output
  pinMode(SR_CLK, 1);
  cpl(SR_DATA); // alternating clock and data lines
  // while(-1); // hold here forever
}

int count = 0; // goes negative maybe
void loop() {
  count++; if (count > 4) count = 0;
  cpl(SR_DATA);
  delay(0+(count * 3));
  cpl(SR_CLK);
  delay(1+(count * 5));
}
