\ main.fs
\ commit 70276f2
\ Mon Dec 27 18:20:16 UTC 2021

target
turnkey
    decimal
    initGPIO

: test  ." this is going to be good 27 Dec 2021 at 13:29:55 UTC" ;

: kurtz cr 1 #, 2 #, 3 #, -99 #, -98 #, -97 #, .s ;

: togpin 13 #, ;

: said
  43 #, emit
  32 #, emit
  43 #, emit cr
;

: wiggle blink blink blink blink blink ;

\ literals
\ : olit a dup drop 1 #, swap drop ;
\ : tlit a dup drop $0100000 #, swap drop ;
\ : vlit a dup 1+ swap - ;

: dlit dup 1+ ; \ simple and does what's wanted
: jlit dlit dlit swap - ; \ always exactly '1'

\ : lit0q dup 1+ dup 1+ swap - $00 #, swap drop ;
: lit0 dup $0 #, swap drop ;
: lit1 lit0 1+ ;
: lit2 lit1 1+ ;
: lit3 lit2 1+ ;

: lit16  dup $10 #, swap drop ;
: lit7f  dup $7f #, swap drop ;
: lit256 dup $100 #, swap drop ;

: id ." 30 Dec Thursday 21:20z" cr ;

\ : torst 43 #, echo ;
: nxt jlit + echo ; \ show next char
turnkey decimal interpret
