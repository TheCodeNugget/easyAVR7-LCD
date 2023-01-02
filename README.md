# easyAVR7-LCD
HD44780 LCD Driver for easyAVRv7

## string2LCD function limitations
string2LCD() function is limited to char/string input by the HD44780 Controller. Any numerical data needs to be typecasted into char, which can be done by using [itoa()](https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-itoa-convert-int-into-string) under <stdlib.h>. 

Of Note: itoa() and its variants involve division and therefore are intensive processes for MCUs
