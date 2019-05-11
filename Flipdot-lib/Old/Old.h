/*
  Flipdot.h - Basic functionality for Flipdot controllers.
  The cake is a lie.
*/

#ifndef Flipdot_h
#define Flipdot_h

#include "Arduino.h"

#define DEFAULT_DELAY 700

#define XMAX 24
#define YMAX 7

#define RE A0
#define RA 8
#define RB 9
#define RC 10
#define EA 5
#define EB 6
#define EC 7
#define A 2
#define B 3
#define C 4

#define FONTS 45

class Flipdot{
  public:
    Flipdot(uint16_t d = DEFAULT_DELAY);                    //Sets the number of microseconds each pixel is powered

    void setBuffer(uint8_t x, uint8_t y, uint8_t state);    //Sets the given pixel in the screen buffer
	void setLetter(uint8_t letter, uint8_t indent = 0);		//Sets the given letter in the buffer
	void setWord(uint8_t *wordPointer, uint8_t speed);

    void writePixel(uint8_t x, uint8_t y, uint8_t state);   //Writes the given pixel to the screen
    void writeBuffer(uint8_t style = 0);                    //Writes the screen buffer to the screen with the given update style [0:down; 1:up; 2:right; 3:left]
    void writeAll(uint8_t state = 0);                       //Writes all pixels to the given state

	void clearBuffer();										//Clears the buffer
  private:
    uint8_t buffer[24];
    uint8_t data[10];
    uint16_t write_delay;
    void resetPins();
    void setData(uint8_t x, uint8_t y, uint8_t r, uint8_t c);
    const uint8_t columns[24][2] = {  {B010100,B110100},{B110010,B010010},{B010000,B110000},{B110110,B010110},{B011011,B101011},{B110001,B010001},{B011101,B101101},{B110101,B010101},{B011001,B101001},{B110011,B010011},{B011110,B101110},{B100000,B001000},{B011010,B101010},{B100100,B001100},{B011100,B101100},{B100010,B001010},{B011000,B101000},{B100110,B001110},{B111111,B111010},{B100001,B001001},{B111011,B111100},{B100101,B001101},{B111101,B111000},{B100011,B001011}  };
    const uint8_t rows[7][2] = {  {B0111,B1100},{B1010,B0011},{B0101,B1110},{B1001,B0001},{B0110,B1101},{B1011,B0010},{B0100,B1111}  };
    const uint8_t pins[10] = {2,3,4,5,6,7,8,9,10,A0};
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
			
			/*�:*/ B10001111, B00010010, B00110010, B01001111,
			/*�:*/ B10011111, B00010101, B00110101, B01010001,
			/*�:*/ B10010001, B00111111, B01010001,
			/*�:*/ B10001110, B00010001, B00110001, B01001110,
			/*�:*/ B11011110, B00100001, B00100001, B01011110,
			/*�:*/ B10001110, B00110001, B01010001, B00110001, B01001110,
			/*�:*/ B10011110, B00000001, B00100001, B01000001, B00011110,
			/*�:*/ B10011110, B00100001, B01000001, B00100001, B01011110,
			
			/*FGY-log�:*/ B10000001, B00000011, B00000111, B00001110, B00011100, B00111100, B01111100, B01101100, B01101000, B01100000, B01100000, B01001110, B00010001, B00100001, B01001001, B01001010, B01001100, B00000001, B00000010, B01110100, B00001000, B00010000, B00100000, B01000000
		};
};

#endif