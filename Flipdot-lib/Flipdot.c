/**
 * @file Flipdot.c
 * @author David Horvath
 * @brief Basic functionality for Flipdot controllers.
*/

//The cake is a lie.

#include "Flipdot.h"
#include <stdint.h>
#include <avr/io.h>

/************************************************************************/
/*                          BIT MACROS                                  */
/************************************************************************/

/**
 * @brief Set a single bit to 0.
 *
 * Set the @b B-th bit of @b A to @b 0.
 * @param A The variable being changed.
 * @param B The number of the bit being changed.
 */
#define clearBit(A,B) (A &= ~(1<<B))

/**
 * @brief Set a single bit to 1.
 *
 * Set the @b B-th bit of @b A to @b 1.
 * @param A The variable being changed.
 * @param B The number of the bit being changed.
 */
#define setBit(A,B) (A |= (1<<B))

/**
 * @brief Change the value of a single bit.
 *
 * Set the @b B-th bit of @b A to @b C.
 * @param A The variable being changed.
 * @param B The number of the bit being changed.
 * @param C The value the bit is being changed to.
 */
#define changeBit(A,B,C) (((C & 1) == 1) ? setBit(A,B) : clearBit(A,B))

/************************************************************************/
/*                               DATA                                   */
/************************************************************************/

/**
 * @brief Decoded pixel data for column drivers.
 *
 * Contains the correct output states for the column drivers to switch a pixel.
 * The corresponding outputs are from MSB to LSB: <b>EA, EB, EC, A, B, C</b>
 * @see Flipdot_setOutputPinData
 */
const uint8_t PROGMEM columns[XMAX][2] = {
	{0b001100,0b110100},
	{0b110010,0b001010},
	{0b001000,0b110000},
	{0b110110,0b001110},
	{0b011011,0b101011},
	{0b110001,0b001001},
	{0b011101,0b101101},
	{0b110101,0b001101},
	{0b011001,0b101001},
	{0b110011,0b001011},
	{0b011110,0b101110},
	{0b100000,0b010000},
	{0b011010,0b101010},
	{0b100100,0b010100},
	{0b011100,0b101100},
	{0b100010,0b010010},
	{0b011000,0b101000},
	{0b100110,0b010110},
	{0b111111,0b111010},
	{0b100001,0b010001},
	{0b111011,0b111100},
	{0b100101,0b010101},
	{0b111101,0b111000},
	{0b100011,0b010011}
};

/**
 * @brief Decoded pixel data for row drivers.
 *
 * Contains the correct output states for the row drivers to switch a pixel.
 * The corresponding outputs are from MSB to LSB: <b>RE, RA, RB, RC</b>
 * @see Flipdot_setOutputPinData
 */
const uint8_t PROGMEM rows[YMAX][2] = {
	{0b0111,0b1100},
	{0b1010,0b0011},
	{0b0101,0b1110},
	{0b1001,0b0001},
	{0b0110,0b1101},
	{0b1011,0b0010},
	{0b0100,0b1111}
};

/**
 * @brief Preprogrammed font data.
 *
 * Contains the data for each programmed character.
 * As the display is 7 pixels high, the first bit is used to determine the first byte of each character.
 * The MSB of the first byte of each character @b MUST be @b 1.
 * The character are encoded as each row, from top to bottom, from MSB to LSB.
 * @warning The number of programmed fonts @b MUST be updated in @b FONTS.
 * @see FONTS
 * @see Flipdot_setLetter
 */
const uint8_t PROGMEM font[] = {
	/*CAPITAL LETTERS*/
	/*A*/ 0b10111111, 0b01001000, 0b01001000, 0b00111111,
	/*B*/ 0b11111111, 0b01001001, 0b01001001, 0b00110110,
	/*C*/ 0b10111110, 0b01000001, 0b01000001, 0b00100010,
	/*D*/ 0b11111111, 0b01000001, 0b01000001, 0b00111110,
	/*E*/ 0b11111111, 0b01001001, 0b01001001, 0b01000001,
	/*F*/ 0b11111111, 0b01001000, 0b01001000, 0b01000000,
	/*G*/ 0b10111110, 0b01000001, 0b01001001, 0b00101110,
	/*H*/ 0b11111111, 0b00001000, 0b00001000, 0b01111111,
	/*I*/ 0b11000001, 0b01111111, 0b01000001,
	/*J*/ 0b10000110, 0b00000001, 0b00000001, 0b01111110,
	/*K*/ 0b11111111, 0b00001000, 0b00010100, 0b01100011,
	/*L*/ 0b11111111, 0b00000001, 0b00000001, 0b00000001,
	/*M*/ 0b11111111, 0b00100000, 0b00010000, 0b00100000, 0b01111111,
	/*N*/ 0b11111111, 0b00010000, 0b00001000, 0b01111111,
	/*O*/ 0b10111110, 0b01000001, 0b01000001, 0b00111110,
	/*P*/ 0b11111111, 0b01001000, 0b01001000, 0b00110000,
	/*Q*/ 0b10111110, 0b01000001, 0b01000101, 0b01000010, 0b00111101,
	/*R*/ 0b11111111, 0b01001100, 0b01001010, 0b00110001,
	/*S*/ 0b10110010, 0b01001001, 0b01001001, 0b00100110,
	/*T*/ 0b11000000, 0b01111111, 0b01000000,
	/*U*/ 0b11111110, 0b00000001, 0b00000001, 0b01111110,
	/*V*/ 0b11111000, 0b00000110, 0b00000001, 0b00000110, 0b01111000,
	/*W*/ 0b11111111, 0b00000010, 0b00000100, 0b00000010, 0b01111111,
	/*X*/ 0b11100011, 0b00010100, 0b00001000, 0b00010100, 0b01100011,
	/*Y*/ 0b11100000, 0b00010000, 0b00001111, 0b00010000, 0b01100000,
	/*Z*/ 0b11000111, 0b01001001, 0b01010001, 0b01100001,
	/*Á*/ 0b10001111, 0b00010010, 0b00110010, 0b01001111,
	/*É*/ 0b10011111, 0b00010101, 0b00110101, 0b01010001,
	/*Í*/ 0b10010001, 0b00111111, 0b01010001,
	/*Ó*/ 0b10001110, 0b00010001, 0b00110001, 0b01001110,
	/*Ö*/ 0b11011110, 0b00100001, 0b00100001, 0b01011110,
	/*Ő*/ 0b10001110, 0b00110001, 0b01010001, 0b00110001, 0b01001110,
	/*Ú*/ 0b10011110, 0b00000001, 0b00100001, 0b01000001, 0b00011110,
	/*Ü*/ 0b11011110, 0b00000001, 0b00000001, 0b00000001, 0b01011110,
	/*Ű*/ 0b10011110, 0b00100001, 0b01000001, 0b00100001, 0b01011110,
	
	/*SEMI-BOLD LETTERS*/
	/*A*/ 0b10111111, 0b01001000, 0b01001000, 0b01001000, 0b00111111,
	/*B*/ 0b11111111, 0b01001001, 0b01001001, 0b01001001, 0b00110110,
	/*C*/ 0b10111110, 0b01000001, 0b01000001, 0b01000001, 0b00100010,
	/*D*/ 0b11111111, 0b01000001, 0b01000001, 0b01000001, 0b00111110,
	/*E*/ 0b11111111, 0b01001001, 0b01001001, 0b01001001, 0b01000001,
	/*F*/ 0b11111111, 0b01001000, 0b01001000, 0b01001000, 0b01000000,
	/*G*/ 0b10111110, 0b01000001, 0b01001001, 0b01001001, 0b00101110,
	/*H*/ 0b11111111, 0b00001000, 0b00001000, 0b00001000, 0b01111111,
	/*I*/ 0b11000001, 0b01111111, 0b01000001,
	/*J*/ 0b10000110, 0b00000001, 0b00000001, 0b00000001, 0b01111110,
	/*K*/ 0b11111111, 0b00001000, 0b00010100, 0b00100010, 0b01000001,
	/*L*/ 0b11111111, 0b00000001, 0b00000001, 0b00000001, 0b00000001,
	/*M*/ 0b11111111, 0b00100000, 0b00010000, 0b00100000, 0b01111111,
	/*N*/ 0b11111111, 0b00100000, 0b00010000, 0b00001000, 0b01111111,
	/*O*/ 0b10111110, 0b01000001, 0b01000001, 0b01000001, 0b00111110,
	/*P*/ 0b11111111, 0b01001000, 0b01001000, 0b01001000, 0b00110000,
	/*Q*/ 0b10111110, 0b01000001, 0b01000101, 0b01000011, 0b00111110, 0b00000001,
	/*R*/ 0b11111111, 0b01001000, 0b01001100, 0b01001010, 0b00110001,
	/*S*/ 0b10110010, 0b01001001, 0b01001001, 0b01001001, 0b00100110,
	/*T*/ 0b11000000, 0b01000000, 0b01111111, 0b01000000, 0b01000000,
	/*U*/ 0b11111110, 0b00000001, 0b00000001, 0b00000001, 0b01111110,
	/*V*/ 0b11111100, 0b00000010, 0b00000001, 0b00000010, 0b01111100,
	/*W*/ 0b11111111, 0b00000010, 0b00000100, 0b00000010, 0b01111111,
	/*X*/ 0b11100011, 0b00010100, 0b00001000, 0b00010100, 0b01100011,
	/*Y*/ 0b11110000, 0b00001000, 0b00000111, 0b00001000, 0b01110000,
	/*Z*/ 0b11000011, 0b01000101, 0b01001001, 0b01010001, 0b01100001,
	/*Á*/ 0b10001111, 0b00010100, 0b00110100, 0b01010100, 0b00001111,
	/*É*/ 0b10011111, 0b00010101, 0b00110101, 0b01010101, 0b00010001,
	/*Í*/ 0b10010001, 0b00111111, 0b01010001,
	/*Ó*/ 0b10001110, 0b00010001, 0b00110001, 0b01010001, 0b00001110,
	/*Ö*/ 0b11011110, 0b00100001, 0b00100001, 0b00100001, 0b01011110,
	/*Ő*/ 0b10001110, 0b00110001, 0b01010001, 0b00110001, 0b01001110,
	/*Ú*/ 0b10011110, 0b00000001, 0b00100001, 0b01000001, 0b00011110,
	/*Ü*/ 0b11011110, 0b00000001, 0b00000001, 0b00000001, 0b01011110,
	/*Ű*/ 0b10011110, 0b00100001, 0b01000001, 0b00100001, 0b01011110,
	
	/*BOLD LETTERS*/
	/*A*/ 0b10011111, 0b00111111, 0b01001000, 0b01001000, 0b01001000, 0b00111111, 0b00011111,
	/*B*/ 0b11111111, 0b01111111, 0b01001001, 0b01001001, 0b01001001, 0b01111111, 0b00110110,
	/*C*/ 0b10011100, 0b00111110, 0b01100011, 0b01000001, 0b01000001, 0b01000001, 0b00100010,
	/*D*/ 0b11111111, 0b01111111, 0b01000001, 0b01000001, 0b01000001, 0b01111111, 0b00111110,
	/*E*/ 0b11111111, 0b01111111, 0b01001001, 0b01001001, 0b01001001, 0b01000001,
	/*F*/ 0b11111111, 0b01111111, 0b01001000, 0b01001000, 0b01001000, 0b01000000,
	/*G*/ 0b10011100, 0b00111110, 0b01000001, 0b01000001, 0b01001001, 0b01001001, 0b00101110, 0b00001100,
	/*H*/ 0b11111111, 0b01111111, 0b00001000, 0b00001000, 0b01111111, 0b01111111,
	/*I*/ 0b11111111, 0b01111111,
	/*J*/ 0b10000001, 0b01000001, 0b01111111, 0b01111110, 0b01000000,
	/*K*/ 0b11111111, 0b01111111, 0b00001000, 0b00011100, 0b00110110, 0b01100011, 0b01000001,
	/*L*/ 0b11111111, 0b01111111, 0b00000001, 0b00000001, 0b00000001,
	/*M*/ 0b11111111, 0b01111111, 0b00100000, 0b00011000, 0b00100000, 0b01111111, 0b01111111,
	/*N*/ 0b11111111, 0b00111111, 0b00010000, 0b00001000, 0b00000100, 0b01111110, 0b01111111,
	/*O*/ 0b10111110, 0b01111111, 0b01000001, 0b01000001, 0b01111111, 0b00111110,
	/*P*/ 0b11111111, 0b01111111, 0b01001000, 0b01001000, 0b01001000, 0b01111000, 0b00110000,
	/*Q*/ 0b10111110, 0b01111111, 0b01000001, 0b01000101, 0b01111111, 0b00111110, 0b00000001,
	/*R*/ 0b11111111, 0b01111111, 0b01001000, 0b01001100, 0b01001110, 0b01111011, 0b00110001,
	/*S*/ 0b10110010, 0b01111001, 0b01001001, 0b01001001, 0b01001111, 0b00000110,
	/*T*/ 0b11000000, 0b01000000, 0b01111111, 0b01111111, 0b01000000, 0b01000000,
	/*U*/ 0b11111110, 0b01111111, 0b00000001, 0b00000001, 0b00000001, 0b01111111, 0b01111110,
	/*V*/ 0b11111000, 0b01111100, 0b00000110, 0b00000001, 0b00000110, 0b01111100, 0b01111000,
	/*W*/ 0b11111111, 0b01111110, 0b00000100, 0b00001000, 0b00000100, 0b01111110, 0b01111111,
	/*X*/ 0b11100011, 0b00010100, 0b00001000, 0b00010100, 0b01100011,
	/*Y*/ 0b11100000, 0b00110000, 0b00001111, 0b00001111, 0b00110000, 0b01100000,
	/*Z*/ 0b11000011, 0b01000111, 0b01001101, 0b01011001, 0b01110001, 0b01100001,
	/*Á*/ 0b10001111, 0b00011111, 0b00010100, 0b00110100, 0b01110100, 0b01011111, 0b00001111,
	/*É*/ 0b10011111, 0b00011111, 0b00110101, 0b01110101, 0b01010101, 0b00010001,
	/*Í*/ 0b10010001, 0b00111111, 0b01111111, 0b01010001,
	/*Ó*/ 0b10001110, 0b00011111, 0b00010001, 0b00110001, 0b01110001, 0b01011111, 0b00001110,
	/*Ö*/ 0b10001100, 0b01011110, 0b01100001, 0b00100001, 0b00100001, 0b01100001, 0b01011110, 0b00001100,
	/*Ő*/ 0b10000100, 0b00001110, 0b00110001, 0b01010001, 0b00010001, 0b00110001, 0b01001110, 0b00000100,
	/*Ú*/ 0b10011100, 0b00011110, 0b00000001, 0b00100001, 0b01100001, 0b01000001, 0b00011110, 0b00011100,
	/*Ü*/ 0b11011100, 0b01011110, 0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b01011110, 0b01011100,
	/*Ű*/ 0b10011100, 0b00011110, 0b00100001, 0b01000001, 0b00000001, 0b00100001, 0b01011110, 0b00011100,
	
	/*NUMBERS*/
	/*1*/ 0b10010000, 0b00100001, 0b01111111, 0b00000001,
	/*2*/ 0b10100011, 0b01000101, 0b01001001, 0b00110001,
	/*3*/ 0b10100010, 0b01001001, 0b01001001, 0b00110110,
	/*4*/ 0b10001100, 0b00010100, 0b00100100, 0b01111111,
	/*5*/ 0b11111010, 0b01001001, 0b01001001, 0b01000110,
	/*6*/ 0b10111110, 0b01001001, 0b01001001, 0b00100110,
	/*7*/ 0b11000000, 0b01000111, 0b01001000, 0b01110000,
	/*8*/ 0b10110110, 0b01001001, 0b01001001, 0b00110110,
	/*9*/ 0b10110010, 0b01001001, 0b01001001, 0b00111110,
	/*0*/ 0b10111110, 0b01000001, 0b01000001, 0b00111110,
	
	/*SPECIAL CHARACTERS*/
	/*.*/ 0b10000011, 0b00000011,
	/*?*/ 0b10100000, 0b01000000, 0b01000101, 0b01001000, 0b00110000,
	/*!*/ 0b11111101,
	/*,*/ 0b10000001, 0b00000110,
	/*:*/ 0b10010010,
	/*(*/ 0b10011100, 0b00100010, 0b01000001,
	/*)*/ 0b11000001, 0b00100010, 0b00011100,
	/*&*/ 0b10000110, 0b00101001, 0b01011001, 0b01010101, 0b00100010, 0b00000101,
    /*slash*/ 0b10000001, 0b00000010, 0b00001100, 0b00010000, 0b00100000, 0b01000000,
	/*+*/ 0b10001000, 0b00001000, 0b00111110, 0b00001000, 0b00001000,
	/*-*/ 0b10001000, 0b00001000, 0b00001000, 0b00001000,
	/*=*/ 0b10010100, 0b00010100, 0b00010100, 0b00010100, 0b00010100,
    /*%*/ 0b10100000, 0b01010011, 0b00100100, 0b00001000, 0b00010010, 0b01100101, 0b00000010,
	/*rightarrow*/ 0b10001000, 0b00001000, 0b00111110, 0b00011100, 0b00001000,
	/*asterisk*/ 0b10001000, 0b01001001, 0b00101010, 0b00010100, 0b01111111, 0b00010100, 0b00101010, 0b01001001, 0b00001000,
	/*@*/ 0b10011110, 0b00100001, 0b01001101, 0b01010101, 0b01011001, 0b01000100, 0b00111000,
	
	/*EXTRAS*/
	/*FGY-logó*/ 0b10000001, 0b00000011, 0b00000111, 0b00001110, 0b00011100, 0b00111100, 0b01111100, 0b01101100, 0b01101000, 0b01100000, 0b01100000, 0b01001110, 0b00010001, 0b00100001, 0b01001001, 0b01001010, 0b01001100, 0b00000001, 0b00000010, 0b01110100, 0b00001000, 0b00010000, 0b00100000, 0b01000000,
    /*spaceinvader 1*/ 0b10001110, 0b00010000, 0b01011110, 0b00101101, 0b00111101, 0b00111100, 0b00111101, 0b00101101, 0b01011110, 0b00010000, 0b00001110,
    /*spaceinvader 2*/ 0b10111000, 0b00001101, 0b01011110, 0b00101100, 0b00111100, 0b00111100, 0b00111100, 0b00101100, 0b01011110, 0b00001101, 0b00111000,

	/*END*/
	0b11111111
};

void Flipdot_resetPins (void){
	Flipdot_delay(f_writeDelay);

	//Set all outputs to 0
	clearBit(f_PORT_A, f_BIT_A);
	clearBit(f_PORT_B, f_BIT_B);
	clearBit(f_PORT_C, f_BIT_C);
	clearBit(f_PORT_RA, f_BIT_RA);
	clearBit(f_PORT_RB, f_BIT_RB);
	clearBit(f_PORT_RC, f_BIT_RC);
	clearBit(f_PORT_RE, f_BIT_RE);
	clearBit(f_PORT_EA, f_BIT_EA);
	clearBit(f_PORT_EB, f_BIT_EB);
	clearBit(f_PORT_EC, f_BIT_EC);
	clearBit(f_PORT_SA, f_BIT_SA);
	clearBit(f_PORT_SB, f_BIT_SB);
	clearBit(f_PORT_SC, f_BIT_SC);
}

void Flipdot_delay (uint16_t n){
	OCR1A = n;				//Set output compare to parameter
	TCCR1B = 5;				//Set clk/1024 as source, START
	while(!(TIFR1 & 2));	//Wait...
	TCCR1B = 0;				//STOP
	TCNT1 = 0;				//Clear timer counter
	setBit(TIFR1,1);		//Clear flag
}

void Flipdot_setDelay (uint8_t delay){
	if(delay > DELMIN && delay < DELMAX){
		f_writeDelay = delay;
	} else {
		f_writeDelay = DEFAULT_DELAY;
	}
}

void Flipdot_clearBuffer (void){
	for(uint8_t i=0;i<XMAX;i++){
		f_frameBuffer[i] = 0;
	}
}

void Flipdot_setBuffer (uint8_t x, uint8_t y, uint8_t state){
  if(x < XMAX && y < YMAX && state <= 1){
	  if(state == 1){
		  f_frameBuffer[x] |= (1<<y);
	  }else if(state == 0){
		  f_frameBuffer[x] &= ~(1<<y);
	  }
  }
}

void Flipdot_writeBuffer (enum Style style, uint8_t delay){
	if(style == down){
		for(uint8_t y = 0;y < YMAX;y++){
			for(uint8_t x = 0;x < XMAX;x++){
				if(((f_frameBuffer[x] & (1 << y)) >> y) == 1){
					Flipdot_writePixel(x,y,1);
				}else{
					Flipdot_writePixel(x,y,0);
				}
				if(delay > 0){
					Flipdot_delay(delay);
				}
			}
		}
	}else if(style == up){
		for(int8_t y = (YMAX-1);y >= 0;y--){
			for(uint8_t x = 0;x < XMAX;x++){
				if(((f_frameBuffer[x] & (1 << y)) >> y) == 1){
					Flipdot_writePixel(x,y,1);
				}else{
					Flipdot_writePixel(x,y,0);
				}
				if(delay > 0){
					Flipdot_delay(delay);
				}
			}
		}
	}else if(style == right){
		for(uint8_t x = 0;x < XMAX;x++){
			for(uint8_t y = 0;y < YMAX;y++){
				if(((f_frameBuffer[x] & (1 << y)) >> y) == 1){
					Flipdot_writePixel(x,y,1);
				}else{
					Flipdot_writePixel(x,y,0);
				}
				if(delay > 0){
					Flipdot_delay(delay);
				}
			}
		}
	}else if(style == left){
		for(int8_t x = (XMAX-1);x >= 0;x--){
			for(uint8_t y = 0;y < YMAX;y++){
				if(((f_frameBuffer[x] & (1 << y)) >> y) == 1){
					Flipdot_writePixel(x,y,1);
				}else{
					Flipdot_writePixel(x,y,0);
				}
				if(delay > 0){
					Flipdot_delay(delay);
				}
			}
		}
	}
}

void Flipdot_init (void){
	//Enable output pins

	setBit(f_DDR_A, f_BIT_A);
	setBit(f_DDR_B, f_BIT_B);
	setBit(f_DDR_C, f_BIT_C);
	setBit(f_DDR_RA, f_BIT_RA);
	setBit(f_DDR_RB, f_BIT_RB);
	setBit(f_DDR_RC, f_BIT_RC);
	setBit(f_DDR_RE, f_BIT_RE);
	setBit(f_DDR_EA, f_BIT_EA);
	setBit(f_DDR_EB, f_BIT_EB);
	setBit(f_DDR_EC, f_BIT_EC);
	setBit(f_DDR_SA, f_BIT_SA);
	setBit(f_DDR_SB, f_BIT_SB);
	setBit(f_DDR_SC, f_BIT_SC);
	
	Flipdot_clearBuffer();
	
	f_writeDelay = DEFAULT_DELAY;
}

void Flipdot_setOutputPinData (uint8_t x, uint8_t y, uint8_t rowInvert, uint8_t columnInvert){
	//																				NAME					CONNECTOR NAME
	f_outputPinData[0] = (pgm_read_byte(&rows[y][rowInvert]) >> 3) & 1;				//Row Enable			RE
	f_outputPinData[1] = (pgm_read_byte(&rows[y][rowInvert]) >> 2) & 1;				//Row A					RA
	f_outputPinData[2] = (pgm_read_byte(&rows[y][rowInvert]) >> 1) & 1;				//Row B					RB
	f_outputPinData[3] = (pgm_read_byte(&rows[y][rowInvert]) >> 0) & 1;				//Row C					RC
				 
	f_outputPinData[4] = (pgm_read_byte(&columns[x][columnInvert]) >> 5) & 1;		//Subsegment A			EA
	f_outputPinData[5] = (pgm_read_byte(&columns[x][columnInvert]) >> 4) & 1;		//Subsegment B			EB
	f_outputPinData[6] = (pgm_read_byte(&columns[x][columnInvert]) >> 3) & 1;		//Subsegment C			EC
	f_outputPinData[7] = (pgm_read_byte(&columns[x][columnInvert]) >> 2) & 1;		//A						A
	f_outputPinData[8] = (pgm_read_byte(&columns[x][columnInvert]) >> 1) & 1;		//B						B
	f_outputPinData[9] = (pgm_read_byte(&columns[x][columnInvert]) >> 0) & 1;		//C						C
}

void Flipdot_writePixel (uint8_t x, uint8_t y, uint8_t state){
	x = XMAX-x-1;
	y = YMAX-y-1;
	if(x < XMAX && y < YMAX && state <= 1){
		uint8_t x_mod = x % 2;
		uint8_t y_mod = y % 2;
		if(state == 1){
			if(!x_mod && !y_mod){
				Flipdot_setOutputPinData(x,y,0,0);
			}else if(!x_mod && y_mod){
				Flipdot_setOutputPinData(x,y,0,1);
			}else if(x_mod && !y_mod){
				Flipdot_setOutputPinData(x,y,1,0);
			}else if(x_mod && y_mod){
				Flipdot_setOutputPinData(x,y,1,1);
			}
		}else{
			if(!x_mod && !y_mod){
				Flipdot_setOutputPinData(x,y,1,1);
			}else if(!x_mod && y_mod){
				Flipdot_setOutputPinData(x,y,1,0);
			}else if(x_mod && !y_mod){
				Flipdot_setOutputPinData(x,y,0,1);
			}else if(x_mod && y_mod){
				Flipdot_setOutputPinData(x,y,0,0);
			}
		}
	}
		
	//	I/O pins											NAME				CONNECTOR NAME
	changeBit(f_PORT_A, f_BIT_A, f_outputPinData[7]);		//A					A
	changeBit(f_PORT_B, f_BIT_B, f_outputPinData[8]);		//B					B
	changeBit(f_PORT_C, f_BIT_C, f_outputPinData[9]);		//C					C
	changeBit(f_PORT_RA, f_BIT_RA, f_outputPinData[1]);		//Row A				RA
	changeBit(f_PORT_RB, f_BIT_RB, f_outputPinData[2]);		//Row B				RB
	changeBit(f_PORT_RC, f_BIT_RC, f_outputPinData[3]);		//Row C				RC
	changeBit(f_PORT_EA, f_BIT_EA, f_outputPinData[4]);		//Subsegment A		EA
	changeBit(f_PORT_EB, f_BIT_EB, f_outputPinData[5]);		//Subsegment B		EB
	changeBit(f_PORT_EC, f_BIT_EC, f_outputPinData[6]);		//Subsegment C		EC
	changeBit(f_PORT_RE, f_BIT_RE, f_outputPinData[0]);		//Row Enable		RE

	//TODO: Add multi-segment management (preset for segment 1 soldered)
	changeBit(f_PORT_SA, f_BIT_SA, 1);						//Segment A			Internal(SA)
	changeBit(f_PORT_SB, f_BIT_SB, 0);						//Segment B			Internal(SB)
	changeBit(f_PORT_SC, f_BIT_SC, 0);						//Segment C			Internal(SC)
	
	 Flipdot_resetPins();
}

void Flipdot_fillScreen (uint8_t state){
	if(state == 0 || state == 1){
		for(uint8_t y = 0;y < YMAX;y++){
			for(uint8_t x = 0;x < XMAX;x++){
				Flipdot_writePixel(x,y,state);
			}
		}
	}
}

uint8_t Flipdot_setLetter (uint8_t letter, uint8_t indent){
		uint8_t length = 0;
		if(letter < FONTS && indent < XMAX){
			letter++;
			uint8_t arrayNum = 0;
			//Find first byte of letter (arrayNum)
			for(uint8_t i = 0;i < letter;){
				while(1){
					if(((pgm_read_byte(&font[arrayNum]) & (1 << 7)) >> 7) == 1){
						arrayNum++;
						break;
					}
					arrayNum++;
				}
				i++;
			}
			arrayNum--;

			uint8_t x = indent;
			while(1){
				for(uint8_t y = 0; y < 7;y++){
					if(((pgm_read_byte(&font[arrayNum]) & (1 << y)) >> y) == 0){
						Flipdot_setBuffer(x,6-y,0);
					} else {
						Flipdot_setBuffer(x,6-y,1);
					}
				}
				x++;
				length++;
				if(((pgm_read_byte(&font[arrayNum+1]) & (1 << 7)) >> 7) == 1 || (x+1) > XMAX){
					break;
				} else {
					arrayNum++;
				}
			}
		}
		return length;
}
