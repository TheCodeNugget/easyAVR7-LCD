# easyAVR7-LCD
HD44780 LCD Driver for easyAVRv7

## string2LCD function limitations
string2LCD() function is limited to char/string input by the HD44780 Controller. Any numerical data needs to be typecasted into char, which can be done by using [itoa()](https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-itoa-convert-int-into-string) under <stdlib.h>. 

Of Note: itoa() and its variants involve division and therefore are intensive processes for MCUs

## Working with floating Point Data
Conversion of double or floating point data is often done with the usage of [sprintf()](https://www.ibm.com/docs/en/i/7.2?topic=functions-sprintf-print-formatted-data-buffer) function under <stdio.h>. However in most embedded systems usage of floating point extension of the function is disabled resulting in a "?" return. To enable this functionality following commands need to be added to the gcc command

`-Wl,-u,vfprintf -lprintf_flt -lm`

With Atmel Studio the commands can be added to the following

> Project -> Properties ->Toolchain->AVR/GNU linker->Misc
