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

: id ."  1 Jan Saturday 22:48z" cr ;

: nxt jlit + echo ; \ show next char

turnkey decimal initGPIO interpret
