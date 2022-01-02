\ main.fs
\ Sun  2 Jan 17:11:50 UTC 2022

target
turnkey
    decimal
    initGPIO

: test  ." this is going to be good " ;

: wiggle blink blink blink blink blink ;

\ literals

: dlit dup 1+ ; \ simple and does what's wanted
: jlit dlit dlit swap - ; \ always exactly '1'

: nxt jlit + echo ; \ show next char
: led 25 #, ;

: blik led on 100 #, ms led off 800 #, ms ;

: blinks ( n -- )
  1- for blik next ." ok " ;

: id ."  2 Jan Sunday   17:11z" cr
     ." rp2040-dvlp-dd-multc-a"cr ;

turnkey decimal initGPIO interpret
