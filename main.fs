\ main.fs
\ commit 70276f2
\ Fri Dec 31 18:22:12 UTC 2021

target
turnkey
    decimal
    initGPIO

: test  ." this is going to be good " ;

: wiggle blink blink blink blink blink ;

\ literals

: dlit dup 1+ ; \ simple and does what's wanted
: jlit dlit dlit swap - ; \ always exactly '1'

: id ." rp2040  31 Dec Friday   22:48z" cr ;

: nxt jlit + echo ; \ show next char

turnkey decimal interpret
