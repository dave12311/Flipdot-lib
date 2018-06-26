/*
  Flipdot_text.h - Text library for Flipdot controller.
  The cake is a lie.
*/

#ifndef Flipdot_text_h
#define Flipdot_text_h

#include "Flipdot_base.h"
#include "Arduino.h"

#define FONTS 45

class Flipdot_text{
	public:
		void writeLetter(uint8_t letter, uint8_t indent = 0);				//Writes the given letter to the buffer
		void writeBuffer(uint8_t style = 0);								//Writes the screen buffer to the screen with the given update style
		void setAll(uint8_t state = 0);										//Sets all pixels to the given state
	private:
		Flipdot_base Flipdot;
		const uint8_t font[205] = {
			/*A:*/ B10111111, B01001000, B01001000, B00111111,
			/*B:*/ B11111111, B01001001, B01001001, B00110110,
			/*C:*/ B10111110, B01000001, B01000001, B00100010,
			/*D:*/ B11111111, B01000001, B01000001, B00111110,
			/*E:*/ B11111111, B01001001, B01001001, B01000001,
			/*F:*/ B11111111, B01001000, B01001000, B01000000,
			/*G:*/ B10111110, B01000001, B01001001, B00101110,
			/*H:*/ B11111111, B00001000, B00001000, B01111111,
			/*I:*/ B11000001, B01111111, B01000001,
			/*J:*/ B10000110, B00000001, B00000001, B01111110,
			/*K:*/ B11111111, B00001000, B00010100, B01100011,
			/*L:*/ B11111111, B00000001, B00000001, B00000001,
			/*M:*/ B11111111, B00100000, B00010000, B00100000, B01111111,
			/*N:*/ B11111111, B00010000, B00001000, B01111111,
			/*O:*/ B10111110, B01000001, B01000001, B00111110,
			/*P:*/ B11111111, B01001000, B01001000, B00110000,
			/*Q:*/ B10111110, B01000001, B01000101, B00000001,
			/*R:*/ B11111111, B01001100, B01001010, B00110001,
			/*S:*/ B10110010, B01001001, B01001001, B00100110,
			/*T:*/ B11000000, B01111111, B01000000,
			/*U:*/ B11111110, B00000001, B00000001, B01111110,
			/*V:*/ B11111000, B00000110, B00000001, B00000110, B01111000,
			/*W:*/ B11111111, B00000010, B00000100, B00000010, B01111111,
			/*X:*/ B11100011, B00010100, B00001000, B00010100, B01100011,
			/*Y:*/ B11100000, B00010000, B00001111, B00010000, B01100000,
			/*Z:*/ B11000111, B01001001, B01010001, B01100001,
			
			/*1:*/ B10010000, B00100001, B01111111, B00000001,
			/*2:*/ B10100011, B01000101, B01001001, B00110001,
			/*3:*/ B10100010, B01001001, B01001001, B00110110,
			/*4:*/ B10001100, B00010100, B00100100, B01111111,
			/*5:*/ B11111010, B01001001, B01001001, B01000110,
			/*6:*/ B10111110, B01001001, B01001001, B00100110,
			/*7:*/ B11000000, B01000111, B01001000, B01110000,
			/*8:*/ B10110110, B01001001, B01001001, B00110110,
			/*9:*/ B10110010, B01001001, B01001001, B00111110,
			/*0:*/ B10111110, B01000001, B01000001, B00111110,
			
			/*Á:*/ B10001111, B00010010, B00110010, B01001111,
			/*É:*/ B10011111, B00010101, B00110101, B01010001,
			/*Í:*/ B10010001, B00111111, B01010001,
			/*Ó:*/ B10001110, B00010001, B00110001, B01001110,
			/*Ö:*/ B11011110, B00100001, B00100001, B01011110,
			/*Õ:*/ B10001110, B00110001, B01010001, B00110001, B01001110,
			/*Ú:*/ B10011110, B00000001, B00100001, B01000001, B00011110,
			/*Û:*/ B10011110, B00100001, B01000001, B00100001, B01011110,
			
			/*FGY-logó:*/ B10000001, B00000011, B00000111, B00001110, B00011100, B00111100, B01111100, B01101100, B01101000, B01100000, B01100000, B01001110, B00010001, B00100001, B01001001, B01001010, B01001100, B00000001, B00000010, B01110100, B00001000, B00010000, B00100000, B01000000
		};
		
};
#endif