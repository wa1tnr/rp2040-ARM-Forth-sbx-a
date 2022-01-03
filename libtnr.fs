: \ESC 43 #, ;
: \\ 0 #,
    begin
        1+ key
        dup \ESC drop drop
        dup \ESC = drop
        dup \ESC =        -if 32 #, emit then drop
        dup \ESC = invert -if over emit then drop
        dup BL max \ESC xor while
        drop drop
    repeat
    drop drop 1- drop
    ;

: wiggle blink blink blink blink blink ;

\ literals

: dlit dup 1+ ; \ simple and does what's wanted
: jlit dlit dlit swap - ; \ always exactly '1'

: nxt jlit + echo ; \ show next char
: led 25 #, ;

: blik led on 100 #, ms led off 800 #, ms ;

: blinks ( n -- )
  1- for blik next ." ok " ;

\ arbitrary flag values -77 and -22 - systematic choices are a TODO item.
: stop -77 #, fl!  ." core_1 (loop1) " led off ;
: start -22 #, fl! 2 #, ms ." core_1 (loop1) " ;
