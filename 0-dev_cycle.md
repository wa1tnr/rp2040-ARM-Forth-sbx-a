```text
Development Cycle - wa1tnr notes

Development cycle consists of editing main.fs, and
then using the 'c' (compile) shell script.

This prepares something useful for Forth.

Build the arduino program as usual, and upload it to your
SAMD21 target board, but only after compiling in gforth
in your host operating system (desktop Linux machine for
the reference system).

Use a nice tty program to talk to the target board
(Adfruit Feather M0 Express is the reference platform).


Example of a useful main.fs

\  - - -   snip!   - - -
\ main.fs
target
turnkey
    decimal
: test  ." this is going to be good 27 Dec 2021 at 12:17:31 UTC" ;
: kurtz 43 #, emit 32 #, emit cr 1 #, 2 #, 3 #, -99 #, -98 #, -97 #, .s ;
turnkey decimal interpret
\  - - -   snip!   - - -


When the target is connected to (via USB cable and /dev/ttyACM0)
the session for the above main.fs, it looks like this in your
(putty-like) terminal environment:

words  << you type this yourself and (as always, you pressed ENTER
          after typing the name of any word)

The system responds by printing its entire vocabulary, one word per
line, to your (putty-like) terminal:

kurtz 0328  << our new test word, defined in main.fs
test 02EF 
interpret 02DA 
.s 0280 
= 026D 
0= 0264 
? 0260 
' 025C 
h# 0244 
find 0224 
match 0208 
query 01E1 
echo 01DD 
tib! 01D1 
words 01C3 

.
.

\ many words omitted here for brevity

.
.

r> 000C 
>r 000B 
key 0005 
emit 0004 
quit 0003 
abort 0002 
exit 0001 
--> empty  << the system ended the list of words with a stack report - the stack was empty
kurtz +  << you typed this (but not the trailing plus symbol - that was output by the system!)
--> 1 2 3 -99 -98 -97 --> 1 2 3 -99 -98 -97  << the 'kurtz' word ran ..
    .. and populated the stack with six values
drop --> 1 2 3 -99 -98  << you typed 'drop' and one stack element was consumed
.s --> 1 2 3 -99 -98 --> 1 2 3 -99 -98   << you typed '.s' and a stack report was given
drop --> 1 2 3 -99  << you typed 'drop' and another stack element was consumed
.s --> 1 2 3 -99 --> 1 2 3 -99 
drop --> 1 2 3 
drop --> 1 2 
drop --> 1 
32 32 ? << you typed a number and the interpreter did not know what to do with your input
--> empty  << any 'huh' (that question mark is a 'huh') empties the stack

Exhibit:

 $ cat -n ARM-Forth.ino  | your_filter_here

359 void _huh(){
360     Serial.write(" ?\n");
361     _abort();
362 }

back to the narrative describing the session:

.s --> empty --> empty  <<  you typed dot-S and Forth reported it empty, twice
kurtz +  << you ran the 'kurtz' word again, and it once more populated the stack with six values
--> 1 2 3 -99 -98 -97 --> 1 2 3 -99 -98 -97 
* --> 1 2 3 -99 9506 << you multiplied the top two values on the stack
. 9506 --> 1 2 3 -99  << you printed the top of the stack
. -99 --> 1 2 3 
. 3 --> 1 2 
. 2 --> 1 
. 1 --> empty
kurtz +  << since the stack was empty, you typed 'kurtz' yet again, to repopulate it
--> 1 2 3 -99 -98 -97 --> 1 2 3 -99 -98 -97 
+ --> 1 2 3 -99 -195 
+ --> 1 2 3 -294 
+ --> 1 2 -291 
+ --> 1 -289 
+ --> -288 


AT THE TOP of the session, it looked like this (now, in full):

words  << this was all you typed
kurtz 0328 
test 02EF 
interpret 02DA 
.s 0280 
= 026D 
0= 0264 
? 0260 
' 025C 
h# 0244 
find 0224 
match 0208 
query 01E1 
echo 01DD 
tib! 01D1 
words 01C3 
dictionary 01BD 
r 0198 
d 0189 
hc. 0177 
hw. 0163 
h. 014B 
max 013E 
BL 0139 
true 0134 
false 012F 
. 012A 
0< 011D 
d. 0111 
dabs 010C 
u. 0106 
ud. 00FF 
#s 00F3 
# 00DA 
hex 00D3 
decimal 00CC 
base 00CA 
#> 00C1 
<# 00BC 
sign 00B3 
hold 00AA 
holder 00A8 
*/ 00A4 
*/mod 009E 
ud/mod 0091 
mod 0089 
/ 0080 
* 007C 
type 0073 
space 006D 
count 0067 
rot 0061 
pad 005F 
tib 005D 
ptype 0053 
1- 004D 
1+ 0047 
Keyboard.releaseAll 0045 
Keyboard.release 0044 
Keyboard.press 0043 
Keyboard.begin 0042 
rshift 0041 
lshift 0040 
@GPIO 003F 
initGPIO 003E 
@MCP23017 003D 
initMCP23017 003C 
nip 003B 
dnegate 0039 
w! 0038 
w@ 0037 
um/mod 0036 
um* 0035 
w@+ 0034 
c@+ 0033 
huh? 0032 
execute 0031 
depth 0030 
!+ 002F 
c!+ 002E 
! 002D 
c! 002C 
@p 002B 
w!+ 002A 
p! 0029 
p 0028 
a! 0027 
a 0026 
@p+ 0025 
@+ 0024 
@ 0023 
c@ 0022 
2/ 0021 
2* 0020 
abs 001F 
negate 001E 
invert 001D 
xor 001C 
or 001B 
and 001A 
cr 0019 
ms 0018 
- 0017 
+ 0016 
over 0015 
swap 0014 
drop 0013 
dup 0012 
timer 0011 
counter 0010 
d# 000F 
.sh 000E 
r@ 000D 
r> 000C 
>r 000B 
key 0005 
emit 0004 
quit 0003 
abort 0002 
exit 0001 
--> empty
kurtz + 

back to the present.

--> empty
kurtz + 
--> 1 2 3 -99 -98 -97 --> 1 2 3 -99 -98 -97 
drop --> 1 2 3 -99 -98 
.s --> 1 2 3 -99 -98 --> 1 2 3 -99 -98 
drop --> 1 2 3 -99 
.s --> 1 2 3 -99 --> 1 2 3 -99 
drop --> 1 2 3 
drop --> 1 2 
drop --> 1 
32 32 ?
--> empty
.s --> empty --> empty
kurtz + 
--> 1 2 3 -99 -98 -97 --> 1 2 3 -99 -98 -97 
* --> 1 2 3 -99 9506 
. 9506 --> 1 2 3 -99 
. -99 --> 1 2 3 
. 3 --> 1 2 
. 2 --> 1 
. 1 --> empty
kurtz + 
--> 1 2 3 -99 -98 -97 --> 1 2 3 -99 -98 -97 
+ --> 1 2 3 -99 -195 
+ --> 1 2 3 -294 
+ --> 1 2 -291 
+ --> 1 -289 
+ --> -288 

AS A BIT of an easter egg, note the odd placement of a '+' in your
terminal, after typing 'kurtz'.

This is what happened:

: kurtz 43 #, emit 32 #, emit cr 1 #, 2 #, 3 #, -99 #, -98 #, -97 #, .s ;

ASCII 43 was entered where 'emit' can find it.  43 is the plus symbol.

It was 'emit' (in Forth we say 'emit' to indicate a character prints)
.. to your console (like   Serial.print('+');   would do).

Similarly, with ASCII 32 (the space character).

The 'cr' word (carriage return) gives a newline, which will visually
apply when you follow with the '.s' word at the end of the definition
of the 'kurtz' word.


TAKE a diff of 'memory.h' after a light change to main.fs to see
what's going on, here.

(try editing a plain text string, as in this example snippet):

: test  ." this is going to be good 27 Dec 2021 at 13:35:10 UTC" ;

memory.h essentially is a program.  literally, it is a list of integer
values (held as an array of integers).  These feed the virtual forth
machine, with instructions and/or data.


gpio setups follow.

First, modify the .INO file to setup the (LED blinkie)
port pin for OUTPUT:

 $  git diff ARM-Forth.ino | cat
diff --git a/ARM-Forth.ino b/ARM-Forth.ino
index b77b234..2fee4bb 100644
--- a/ARM-Forth.ino
+++ b/ARM-Forth.ino
@@ -435,6 +435,7 @@ void _fetchMCP23017(){

 // all the I/O pins needed for the steno keyboard
 void _initGPIO(){
+    pinMode(13, OUTPUT); // tnr 27 dec
     pinMode(9, INPUT_PULLUP);
     pinMode(10, INPUT_PULLUP);
     pinMode(11, INPUT_PULLUP);
 $

It is assumed, at this point, that this is the right approach
to begin to blink an LED - leverage the Arduino IDE code base
for this one task.

Mon 27 Dec 13:26:38 UTC 2021

END
```
