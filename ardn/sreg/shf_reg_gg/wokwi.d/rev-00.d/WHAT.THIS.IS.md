Wed 15 Dec 07:13:04 UTC 2021

WHAT.THIS.IS

This is the lastest work, and the development base for the next
round of changes, for Wednesday 15 Dec 2021, forward.

Just two files:

    [ https://github.com/wa1tnr/tkm0_7seg-b/blob/dvlp-aa/ardn/sreg/shf_reg_gg/wokwi.d/rev-00.d/n_wokwi-rp2040-sreg-ee-rot-180.json ]

    [ https://github.com/wa1tnr/tkm0_7seg-b/blob/dvlp-aa/ardn/sreg/shf_reg_gg/wokwi.d/rev-00.d/shift_register_wokwi_bb.ino ]

Has:

  2x 74HC595 shift registers on wokwi simulator in JSON
  2x four-digit seven-segment LED display on simulator.

  All necessary wires and programming for the demonstration.

  Plays '01234567' on a pair of four-digit 7-segment displays,
  exposing digit 'painting' and using persistence-of-vision
  technique.
  
  All binary status LED's expose what's being output by the
  shift registers.  Although the red (singleton, bullet-shaped)
  LEDs require the shift register to output a voltage (to light
  them up) the 7-segment displays are Common Anode and require
  grounds to light those segments.
  
  An inversion construct was used to accomodate this, in the
  code:

      void proc_encoding(void) {
          uint8_t ledcpy;
          ledcpy = ledval ^ 0xff;
          //  XOR with 0xff seems to flip bits no problem.
          // this seems to be the only caveat when working
          // with common-OPPOSITE display (anode, cathode)  
          ledval = ledcpy;
      }
  

  Older description follows.  Most/all can be re-enabled (easily)
  in the (present) code.



  .
  .
  
  Plays 'Le Foca Cafe' on the four-digit 7-segment display,
  using Persistence-of-Vision technique, one digit 'painted'
  to this display at a time.

  Uses a 'data bus' for the 7 segments, and a digit selection
  mechanism, to say which digit is currently lit.

  Utilizes the all-important 'video blanking' where, for a
  brief instant, the entire display goes dark.

  Humans require this to 'see' what is intended.  Without it,
  on real hardware, there will be digit 'ghosting' (other
  figures seem to appear on the display - they can be at
  different-than-expected brightness and may not seem to
  correspond to the current 'message' being painted on the
  display.

  Video blanking cures this effect. ;)

END.
