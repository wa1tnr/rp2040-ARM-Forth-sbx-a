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
