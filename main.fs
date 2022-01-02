\ main.fs
\ Sun  2 Jan 17:11:50 UTC 2022

target
turnkey
    decimal
    initGPIO

: test  ." this is going to be good " ;

: id ."  2 Jan Sunday   17:11z" cr
     ." rp2040-dvlp-dd-multc-a"cr ;

: demob stop 8000 #, ms
       start 2000 #, ms
        stop 8000 #, ms
       start 2000 #, ms
        stop 8000 #, ms
       start 2000 #, ms
       stop
       ." demo complete. "
;

turnkey decimal initGPIO interpret
