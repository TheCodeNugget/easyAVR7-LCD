/*************************************************************************
 Title	:   include file for using LCD module on easyAVRv7
 Author:    Kaan "The Nugget" Yýlmaz <https://github.com/TheCodeNugget>
 File:	    LCD_Demo.c
 Software:  AVR-GCC / Atmel Studio
 Hardware:  easyAVRv7 Dev Board
 License:   GNU Public License v3
***************************************************************************/

#ifndef LCD_H_
#define LCD_H_

//Dependencies
#include <inttypes.h>
#include <util/delay.h>
#include <avr/io.h>

//Define Keywords
#define RS 2 //RS Pin
#define E 6 //E Pin
#define D4 4 //Data-4 Pin
#define D5 5 //Data-5 Pin
#define D6 6 //Data-6 Pin
#define D7 7 //Data-7 Pin
#define RSP PORTA //RS Port
#define EP PORTD //E Port
#define DP PORTC //Data Port
#define RSD DDRA //RS Direction Register
#define ED DDRD //E Direction Register
#define DD DDRC //Data Direction Register

//Declare Functions
void LCDCmd(uint8_t); //Sends Command to LCD
void LCDChr(uint8_t); //Sends Char to LCD
void LCDInit(); //LCD Init
void pulseEnable(); //Pulses Enable Bit for Other Functions
void LCDClr(); //Clears LCD
void cursorHome(); //Moves Cursor Home
void moveCursor(uint8_t, uint8_t);
void cursorOff(); //Turns Cursor Off
void cursorOn(); //Turns Cursor On
void cursorBlink(); //Toggle Cursor Blink
void cursorLeft(uint8_t); //Move Cursor Left by given amount
void cursorRight(uint8_t); //Move Cursor Right by given amount
void displayLeft(uint8_t); //Shifts Display Left by given amount
void displayRight(uint8_t); //Shifts Display Right by given amount
void string2LCD(const char *s);

void LCDCmd(uint8_t cmd) {
	DP = (cmd & 0xf0) | (DP & 0x0f);
	pulseEnable();
	_delay_us(45);
	DP = ((cmd & 0x0f) << 4) | (DP & 0x0f);
	pulseEnable();
	_delay_us(45);
}

void LCDChr(uint8_t c) {
	RSP |= (1 << RS); //RS High for Char
	DP = (c & 0xf0) | (DP & 0x0f);
	pulseEnable();
	_delay_us(45);
	DP = ((c & 0x0f) << 4) | (DP & 0x0f);
	pulseEnable();
	RSP &= ~(1 << RS); //Clear RS on Done
	_delay_us(45);
}

void LCDInit() {
	//Clear Used Ports
	RSP &= ~(1 << RS);
	DP &= ~((1 << D4) | (1 << D5) | (1 << D6) | (1 << D7));
	EP &= ~(1 << E);
	//Set Used Port Dirs
	RSD |= (1 << RS);
	DD |= ((1 << D4) | (1 << D5) | (1 << D6) | (1 << D7));
	ED |= (1 <<E);
	
	//Send Boot Up Commands 4-Bit
	_delay_ms(20); //~15ms Powerup time
	
	DP = 0b00110000 | (DP & 0x0f); //Power On Controller
	pulseEnable();
	_delay_ms(5);
	
	DP = 0b00110000 | (DP & 0x0f); //4-Bit Init
	pulseEnable();
	_delay_us(110);
	
	DP = 0b00110000 | (DP & 0x0f); //4-Bit Init
	pulseEnable();
	_delay_us(110);
	
	DP = 0b00100000 | (DP & 0x0f); //Initialize Controller
	pulseEnable();
	_delay_us(110);
	
	LCDCmd(0x28); // 2-Line 5x8 display mode set
	
	LCDCmd(0x06); // Increment Mode
	
	LCDCmd(0x0f);
	
	LCDClr(); // Clear DDRAM
}

void pulseEnable() {
	EP |= (1 << E);
	EP &= ~(1 << E);
}

void LCDClr() {
	LCDCmd(0x01);
	_delay_ms(2);
}

void cursorHome() {
	LCDCmd(0x02);
	_delay_ms(2);
}

void moveCursor(uint8_t x, uint8_t y) {
	register uint8_t DDRAMAddr;
	switch(y) {
		case 0: 
			DDRAMAddr = x;
			break;
		case 1: 
			DDRAMAddr = 0x40 + x;
			break;
		case 2: 
			DDRAMAddr = 0x14 + x;
			break;
		case 3:
			DDRAMAddr = 0x56 + x;
			break;
		default: 
			DDRAMAddr = x;
	}
	LCDCmd(1 << 7 | DDRAMAddr);
	_delay_us(40);
}

void cursorOff() {
	LCDCmd(0x0c);
	_delay_us(45);
}

void cursorOn() {
	LCDCmd(0x0e);
	_delay_us(45);
}

void cursorLeft(uint8_t n) {
	for (uint8_t i=0;i<n;i++) {
		LCDCmd(0x10);
		_delay_us(45);
	}
}

void cursorRight(uint8_t n) {
	for (uint8_t i=0;i<n;i++) {
		LCDCmd(0x14);
		_delay_us(45);
	}
}

void displayLeft(uint8_t n) {
	for (uint8_t i=0;i<n;i++) {
		LCDCmd(0x1E);
		_delay_us(45);
	}
}

void displayRight(uint8_t n) {
	for (uint8_t i=0;i<n;i++) {
		LCDCmd(0x18);
		_delay_us(45);
	}
}

void string2LCD(const char *s) {
	register char c;

	while ( (c = *s++) ) {
		LCDChr(c);
	}
}
#endif /* LCD_H_ */