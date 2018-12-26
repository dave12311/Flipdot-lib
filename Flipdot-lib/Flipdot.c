/*
  Flipdot.cpp - Basic functionality for Flipdot controllers.
  The cake is a lie.
  
  NOTE:
  I/O PINS MUST BE CHANGED UNDER:
	- Flipdot_resetPins()
	- Flipdot_init()
*/

#include "Flipdot.h"
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>

//DATA
const uint8_t PROGMEM columns[24][2] = { {0b010100,0b110100},{0b110010,0b010010},{0b010000,0b110000},{0b110110,0b010110},{0b011011,0b101011},{0b110001,0b010001},{0b011101,0b101101},{0b110101,0b010101},{0b011001,0b101001},{0b110011,0b010011},{0b011110,0b101110},{0b100000,0b001000},{0b011010,0b101010},{0b100100,0b001100},{0b011100,0b101100},{0b100010,0b001010},{0b011000,0b101000},{0b100110,0b001110},{0b111111,0b111010},{0b100001,0b001001},{0b111011,0b111100},{0b100101,0b001101},{0b111101,0b111000},{0b100011,0b001011}  };
const uint8_t PROGMEM rows[7][2] = {  {0b0111,0b1100},{0b1010,0b0011},{0b0101,0b1110},{0b1001,0b0001},{0b0110,0b1101},{0b1011,0b0010},{0b0100,0b1111}  };
const uint8_t PROGMEM font[205] = {
	/*A:*/ 0b10111111, 0b01001000, 0b01001000, 0b00111111,
	/*B:*/ 0b11111111, 0b01001001, 0b01001001, 0b00110110,
	/*C:*/ 0b10111110, 0b01000001, 0b01000001, 0b00100010,
	/*D:*/ 0b11111111, 0b01000001, 0b01000001, 0b00111110,
	/*E:*/ 0b11111111, 0b01001001, 0b01001001, 0b01000001,
	/*F:*/ 0b11111111, 0b01001000, 0b01001000, 0b01000000,
	/*G:*/ 0b10111110, 0b01000001, 0b01001001, 0b00101110,
	/*H:*/ 0b11111111, 0b00001000, 0b00001000, 0b01111111,
	/*I:*/ 0b11000001, 0b01111111, 0b01000001,
	/*J:*/ 0b10000110, 0b00000001, 0b00000001, 0b01111110,
	/*K:*/ 0b11111111, 0b00001000, 0b00010100, 0b01100011,
	/*L:*/ 0b11111111, 0b00000001, 0b00000001, 0b00000001,
	/*M:*/ 0b11111111, 0b00100000, 0b00010000, 0b00100000, 0b01111111,
	/*N:*/ 0b11111111, 0b00010000, 0b00001000, 0b01111111,
	/*O:*/ 0b10111110, 0b01000001, 0b01000001, 0b00111110,
	/*P:*/ 0b11111111, 0b01001000, 0b01001000, 0b00110000,
	/*Q:*/ 0b10111110, 0b01000001, 0b01000101, 0b00000001,
	/*R:*/ 0b11111111, 0b01001100, 0b01001010, 0b00110001,
	/*S:*/ 0b10110010, 0b01001001, 0b01001001, 0b00100110,
	/*T:*/ 0b11000000, 0b01111111, 0b01000000,
	/*U:*/ 0b11111110, 0b00000001, 0b00000001, 0b01111110,
	/*V:*/ 0b11111000, 0b00000110, 0b00000001, 0b00000110, 0b01111000,
	/*W:*/ 0b11111111, 0b00000010, 0b00000100, 0b00000010, 0b01111111,
	/*X:*/ 0b11100011, 0b00010100, 0b00001000, 0b00010100, 0b01100011,
	/*Y:*/ 0b11100000, 0b00010000, 0b00001111, 0b00010000, 0b01100000,
	/*Z:*/ 0b11000111, 0b01001001, 0b01010001, 0b01100001,
	
	/*1:*/ 0b10010000, 0b00100001, 0b01111111, 0b00000001,
	/*2:*/ 0b10100011, 0b01000101, 0b01001001, 0b00110001,
	/*3:*/ 0b10100010, 0b01001001, 0b01001001, 0b00110110,
	/*4:*/ 0b10001100, 0b00010100, 0b00100100, 0b01111111,
	/*5:*/ 0b11111010, 0b01001001, 0b01001001, 0b01000110,
	/*6:*/ 0b10111110, 0b01001001, 0b01001001, 0b00100110,
	/*7:*/ 0b11000000, 0b01000111, 0b01001000, 0b01110000,
	/*8:*/ 0b10110110, 0b01001001, 0b01001001, 0b00110110,
	/*9:*/ 0b10110010, 0b01001001, 0b01001001, 0b00111110,
	/*0:*/ 0b10111110, 0b01000001, 0b01000001, 0b00111110,
	
	/*�:*/ 0b10001111, 0b00010010, 0b00110010, 0b01001111,
	/*�:*/ 0b10011111, 0b00010101, 0b00110101, 0b01010001,
	/*�:*/ 0b10010001, 0b00111111, 0b01010001,
	/*�:*/ 0b10001110, 0b00010001, 0b00110001, 0b01001110,
	/*�:*/ 0b11011110, 0b00100001, 0b00100001, 0b01011110,
	/*�:*/ 0b10001110, 0b00110001, 0b01010001, 0b00110001, 0b01001110,
	/*�:*/ 0b10011110, 0b00000001, 0b00100001, 0b01000001, 0b00011110,
	/*�:*/ 0b10011110, 0b00100001, 0b01000001, 0b00100001, 0b01011110,
	
	/*FGY-log�:*/ 0b10000001, 0b00000011, 0b00000111, 0b00001110, 0b00011100, 0b00111100, 0b01111100, 0b01101100, 0b01101000, 0b01100000, 0b01100000, 0b01001110, 0b00010001, 0b00100001, 0b01001001, 0b01001010, 0b01001100, 0b00000001, 0b00000010, 0b01110100, 0b00001000, 0b00010000, 0b00100000, 0b01000000
};

uint8_t i;

void Flipdot_resetPins(){
	_delay_us(f_write_delay);
	
	//	I/O pins		    NAME			NAME ON BOARD
		
	PORTB &= ~(1<<0);		//A					MCU 2
	PORTB &= ~(1<<1);		//B					MCU 3
	PORTB &= ~(1<<2);		//C					MCU 4
	PORTB &= ~(1<<3);		//Row A				MCU 8
	PORTB &= ~(1<<4);		//Row B				MCU 9
	PORTB &= ~(1<<5);		//Row C				MCU 10
	PORTB &= ~(1<<6);		//Subsegment A		MCU 5
	PORTB &= ~(1<<7);		//Subsegment B		MCU 6
	PORTD &= ~(1<<0);		//Subsegment C		MCU 7
	PORTD &= ~(1<<1);		//Segment A			Internal
	PORTD &= ~(1<<2);		//Segment B			Internal
	PORTD &= ~(1<<3);		//Segment C			Internal
}

void Flipdot_setDelay (uint16_t delay){
	if(delay > 0 && delay < 6000){
		f_write_delay = delay;
	} else {
		f_write_delay = DEFAULT_DELAY;
	}
}

void Flipdot_clearBuffer (void){
	for(i=0;i<24;i++){
		f_buffer[i] = 0;
	}
}

void Flipdot_init (void){
	//	I/O pins		NAME			NAME ON BOARD
	
	DDRB |= (1<<0);		//A					MCU 2
	DDRB |= (1<<1);		//B					MCU 3
	DDRB |= (1<<2);		//C					MCU 4
	DDRB |= (1<<3);		//Row A				MCU 8
	DDRB |= (1<<4);		//Row B				MCU 9
	DDRB |= (1<<5);		//Row C				MCU 10
	DDRB |= (1<<6);		//Subsegment A		MCU 5
	DDRB |= (1<<7);		//Subsegment B		MCU 6
	DDRD |= (1<<0);		//Subsegment C		MCU 7
	DDRD |= (1<<1);		//Segment A			Internal
	DDRD |= (1<<2);		//Segment B			Internal
	DDRD |= (1<<3);		//Segment C			Internal
	
	Flipdot_clearBuffer();
}