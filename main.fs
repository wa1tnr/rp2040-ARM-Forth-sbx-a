\ main.fs
\ commit 70276f2
\ Sat Jan  1 22:24:18 UTC 2022

target
turnkey
    decimal
    initGPIO

: test  ." this is going to be good " ;

: wiggle blink blink blink blink blink ;

\ literals

: dlit dup 1+ ; \ simple and does what's wanted
: jlit dlit dlit swap - ; \ always exactly '1'

: id ."  1 Jan Saturday 23:31z" cr ;

: nxt jlit + echo ; \ show next char
: led 25 #, ;

: blik led on 100 #, ms led off 800 #, ms ;

: blinks ( n -- )
  1- for blik next ." ok " ;

turnkey decimal initGPIO interpret
