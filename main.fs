\ main.fs
\ Sun  2 Jan 18:38:07 UTC 2022

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

: id ." Sun  2 Jan 18:38:07" cr
     ." rp2040-multicore-a"  cr ;

turnkey decimal initGPIO interpret
