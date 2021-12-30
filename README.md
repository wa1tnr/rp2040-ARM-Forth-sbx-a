# ARM-Forth
ITC Forth in C, built and tested on the Adafruit QT Py
and on the Adafruit Itsy Bitsy M0.

This is a target compiled Forth that deviates from the
standard in several ways. Branching words don't consume
the stack. This is similar to the Green Arrays chips.

There are two address spaces, RAM and program memory.
RAM has an address "register" called A. Program memory
has one called P. Primitives such as c@+, c!+, @p+, use
those address registers. Also it's target compiled but
not exactly tethered. The target has separated heads and
a text interpreter, but no compiling. At least not yet.

The interpreter is specifically designed to work with the
Arduino IDE and its serial terminal.

See the file "main.fs" for a steno keyboard firmware.
