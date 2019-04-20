/*
  Flipdot.cpp - Basic functionality for Flipdot controllers.
  The cake is a lie.
  
  NOTE:
  I/O PINS MUST BE CHANGED UNDER:
	- Flipdot_resetPins()
	- Flipdot_init()
	- Flipdot_writePixel()
*/

#include "Flipdot.h"
#include <stdint.h>
#include <avr/io.h>

//Bit macros
#define clearBit(A,B) (A &= ~(1<<B))										//Set the [B]-th bit of [A] to  0
#define setBit(A,B) (A |= (1<<B))											//Set the [B]-th bit of [A] to  1
#define changeBit(A,B,C) (((C & 1) == 1) ? setBit(A,B) : clearBit(A,B))		//Set the [B]-th bit of [A] to [C]

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
	
	/*Á:*/ 0b10001111, 0b00010010, 0b00110010, 0b01001111,
	/*É:*/ 0b10011111, 0b00010101, 0b00110101, 0b01010001,
	/*Í:*/ 0b10010001, 0b00111111, 0b01010001,
	/*Ó:*/ 0b10001110, 0b00010001, 0b00110001, 0b01001110,
	/*Ö:*/ 0b11011110, 0b00100001, 0b00100001, 0b01011110,
	/*Õ:*/ 0b10001110, 0b00110001, 0b01010001, 0b00110001, 0b01001110,
	/*Ú:*/ 0b10011110, 0b00000001, 0b00100001, 0b01000001, 0b00011110,
	/*Û:*/ 0b10011110, 0b00100001, 0b01000001, 0b00100001, 0b01011110,
	
	/*FGY-logó:*/ 0b10000001, 0b00000011, 0b00000111, 0b00001110, 0b00011100, 0b00111100, 0b01111100, 0b01101100, 0b01101000, 0b01100000, 0b01100000, 0b01001110, 0b00010001, 0b00100001, 0b01001001, 0b01001010, 0b01001100, 0b00000001, 0b00000010, 0b01110100, 0b00001000, 0b00010000, 0b00100000, 0b01000000
};

void Flipdot_resetPins (void){
	Flipdot_delay(f_writeDelay);

	//	I/O pins		    NAME				CONNECTOR NAME
	clearBit(PORTB,0);		//A					A
	clearBit(PORTB,1);		//B					B
	clearBit(PORTB,2);		//C					C
	clearBit(PORTD,0);		//Row A				RA
	clearBit(PORTD,1);		//Row B				RB
	clearBit(PORTD,2);		//Row C				RC
	clearBit(PORTD,3);		//Row Enable		RE
	clearBit(PORTD,5);		//Subsegment A		EA
	clearBit(PORTD,6);		//Subsegment B		EB
	clearBit(PORTD,7);		//Subsegment C		EC
	
	clearBit(PORTC,0);		//Segment A			Internal (SA)
	clearBit(PORTC,1);		//Segment B			Internal (SB)
	clearBit(PORTC,2);		//Segment C			Internal (SC)		
}

void Flipdot_delay (uint8_t t){
	OCR0A = t;				//Set output compare to parameter
	setBit(TCCR0B,0);		//Set clk/1 as source START
	while(!(TIFR0 & 2));	//Wait...
	clearBit(TCCR0B,0);		//STOP
	TCNT0 = 0;				//Clear timer counter
	setBit(TIFR0,1);		//Clear flag
}

void Flipdot_setDelay (uint8_t delay){
	if(delay > 0 && delay < 50){
		f_writeDelay = delay;
	} else {
		f_writeDelay = DEFAULT_DELAY;
	}
}

void Flipdot_clearBuffer (void){
	for(uint8_t i=0;i<24;i++){
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

void Flipdot_writeBuffer (uint8_t style, uint8_t delay){
	if(style == 0){
		for(uint8_t y = 0;y < 7;y++){
			for(uint8_t x = 0;x < 24;x++){
				if(((f_frameBuffer[x] & (1 << y)) >> y) == 1){
					Flipdot_writePixel(x,y,1);
				}else{
					Flipdot_writePixel(x,y,0);
				}
				Flipdot_delay(delay);
			}
		}
	}else if(style == 1){
		for(uint8_t y = 6;y >= 0;y--){
			for(uint8_t x = 0;x < 24;x++){
				if(((f_frameBuffer[x] & (1 << y)) >> y) == 1){
					Flipdot_writePixel(x,y,1);
				}else{
					Flipdot_writePixel(x,y,0);
				}
				Flipdot_delay(delay);
			}
		}
	}else if(style == 2){
		for(uint8_t x = 0;x < 24;x++){
			for(uint8_t y = 0;y < 7;y++){
				if(((f_frameBuffer[x] & (1 << y)) >> y) == 1){
					Flipdot_writePixel(x,y,1);
				}else{
					Flipdot_writePixel(x,y,0);
				}
				Flipdot_delay(delay);
			}
		}
	}else if(style == 3){
		for(uint8_t x = 23;x >= 0;x--){
			for(uint8_t y = 0;y < 7;y++){
				if(((f_frameBuffer[x] & (1 << y)) >> y) == 1){
					Flipdot_writePixel(x,y,1);
				}else{
					Flipdot_writePixel(x,y,0);
				}
				Flipdot_delay(delay);
			}
		}
	}
}

void Flipdot_init (void){
	//Set output pins
	
	//	I/O pins		    NAME				CONNECTOR NAME
	setBit(DDRB,0); 		//A					A
	setBit(DDRB,1); 		//B					B
	setBit(DDRB,2); 		//C					C
	setBit(DDRD,0); 		//Row A				RA
	setBit(DDRD,1); 		//Row B				RB
	setBit(DDRD,2); 		//Row C				RC
	setBit(DDRD,3); 		//Row Enable		RE
	setBit(DDRD,5); 		//Subsegment A		EA
	setBit(DDRD,6); 		//Subsegment B		EB
	setBit(DDRD,7); 		//Subsegment C		EC
	
	setBit(DDRC,0); 		//Segment A			Internal (SA)
	setBit(DDRC,1); 		//Segment B			Internal (SB)
	setBit(DDRC,2); 		//Segment C			Internal (SC)
	
	Flipdot_clearBuffer();
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
		
	//	I/O pins								NAME				CONNECTOR NAME
	changeBit(PORTB,0,f_outputPinData[7]);		//A					A
	changeBit(PORTB,1,f_outputPinData[8]);		//B					B
	changeBit(PORTB,2,f_outputPinData[9]);		//C					C
	changeBit(PORTD,0,f_outputPinData[1]);		//Row A				RA
	changeBit(PORTD,1,f_outputPinData[2]);		//Row B				RB
	changeBit(PORTD,2,f_outputPinData[3]);		//Row C				RC
	changeBit(PORTD,5,f_outputPinData[4]);		//Subsegment A		EA
	changeBit(PORTD,6,f_outputPinData[5]);		//Subsegment B		EB
	changeBit(PORTD,7,f_outputPinData[6]);		//Subsegment C		EC
	changeBit(PORTD,3,f_outputPinData[0]);		//Row Enable		RE

	//TODO: Add multi-segment management (preset for segment 1 soldered)
	changeBit(PORTC,0,1);						//Segment A			Internal(SA)
	changeBit(PORTC,1,0);						//Segment B			Internal(SB)
	changeBit(PORTC,2,0);						//Segment C			Internal(SC)
	
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
		if(letter <= FONTS && letter > 0 && indent < XMAX){
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
