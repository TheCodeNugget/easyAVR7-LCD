/*************************************************************************
 Title	:   C Demo file for the usage of easyAVRLCD.h include file
 Author:    Kaan "The Nugget" Yýlmaz <https://github.com/TheCodeNugget>
 File:	    LCD_Demo.c
 Software:  AVR-GCC / Atmel Studio
 Hardware:  easyAVRv7 Dev Board
 License:   GNU Public License v3
***************************************************************************/

//TODO: Delete This Comment
#define F_CPU 8000000ul // <-- Set this for the target MCU clock (in Hz) for timing purposes

#include "easyAVRLCD.h" // <-- Where Magic Happens
#include <inttypes.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	/* Method of Printing Chars and Strings */
    LCDInit();
	LCDChr('a');
	LCDChr('b');
	LCDChr('c');
	cursorRight(1);
	string2LCD("def");
	
	/* Method of Printing Integers Values Combined With Strings on LCD */
	moveCursor(0,1);
	int exampleVal = 12345;
	char str[11] = (" <--Integer");
	char buffer[5];
	itoa(exampleVal, buffer, 10); //<--- Integer to ASCII function, Read Here : https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-itoa-convert-int-into-string
	
	char* temp; //Create a temp pointer to store combined strings
	temp = malloc(strlen(buffer) + strlen(str) + 1); //Allocate memory according to the buffer sizes
	strcpy(temp, buffer); //Copy the Converted Integer
	strcat(temp, str); //Appends The String
	string2LCD(temp); //Print the result
	free(temp); //Free Memory after use <-- Never Forget This!
	/* Would Suggest Avoiding Repeated Uses as itoa and sprintf are heavy tasks for MCUs */
}
