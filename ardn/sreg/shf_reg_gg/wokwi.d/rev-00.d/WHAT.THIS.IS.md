Tue 14 Dec 19:07:51 UTC 2021

WHAT.THIS.IS

This is the lastest work, and the development base
for the next round of changes, for Tuesday 14 Dec 2021,
forward.

Has:

  2x 74HC595 shift registers on wokwi simulator in JSON
  1x four-digit seven-segment LED display on simulator.

  All necessary wires and programming for the demonstration.

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
