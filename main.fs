\ main.fs
\  Sun  2 Jan 23:24:31 UTC 2022

target
turnkey
    decimal
    initGPIO

: test  ." this is going to be good " ;

: demob stop 8000 #, ms
       start 2000 #, ms
        stop 8000 #, ms
       start 2000 #, ms
        stop 8000 #, ms
       start 2000 #, ms
       stop
       ." demo complete. "
;

\ parent branch was rp2040-dvlp-dd-multc-a

: id ." Tue  4 Jan 00:22:45 UTC 2022" cr
     ." has active shift register stuff" cr
     ." kelnica        " cr
     ." rp2040-multic-seven_seg-a-chekme " cr
     ." with ancestry of, possibly: " cr
     ." rp2040-multicore-c"  cr ;

turnkey decimal initGPIO interpret

\ END.
