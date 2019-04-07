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
#include <avr/io.h>

//Bit macros
#define clearBit(A,B) (A &= ~(1<<B))
#define setBit(A,B) (A |= (1<<B))

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
	Flipdot_delay(f_write_delay);
	
	//TODO: Missing RE pin (sets the direction of the row controller), needs new PCB (RE data is the last bit
	//	I/O pins		    NAME			NAME ON BOARD
		
	clearBit(PORTB,0);		//A					MCU 2
	clearBit(PORTB,1);		//B					MCU 3
	clearBit(PORTB,2);		//C					MCU 4
	clearBit(PORTB,3);		//Row A				MCU 8
	clearBit(PORTB,4);		//Row B				MCU 9
	clearBit(PORTB,5);		//Row C				MCU 10
	clearBit(PORTB,6);		//Subsegment A		MCU 5
	clearBit(PORTB,7);		//Subsegment B		MCU 6
	clearBit(PORTD,0);		//Subsegment C		MCU 7
	clearBit(PORTD,1);		//Segment A			Internal
	clearBit(PORTD,2);		//Segment B			Internal
	clearBit(PORTD,3);		//Segment C			Internal
}

void Flipdot_delay (uint8_t t){
	OCR0A = t;				//Set output compare to parameter
	setBit(TCCR0B,0);		//Set clk/1 as source START
	while(!(TIFR0 & 2));	//Wait...
	clearBit(TCCR0B,0);		//STOP
	TCNT0 = 0;				//Clear timer counter
	setBit(TIFR0,1);		//Clear flag
}

void Flipdot_setDelay (uint16_t delay){
	if(delay > 0 && delay < 50){
		f_write_delay = delay;
	} else {
		f_write_delay = DEFAULT_DELAY;
	}
}

void Flipdot_clearBuffer (void){
	for(uint8_t i=0;i<24;i++){
		f_buffer[i] = 0;
	}
}

void Flipdot_setBuffer (uint8_t x, uint8_t y, uint8_t state){
  if(x < XMAX && y < YMAX && state <= 1){
	  if(state == 1){
		  f_buffer[x] |= (1<<y);
	  }else if(state == 0){
		  f_buffer[x] &= ~(1<<y);
	  }
  }
}

void Flipdot_init (void){
	//	I/O pins		NAME			NAME ON BOARD
	
	setBit(DDRB,0);		//A					MCU 2
	setBit(DDRB,1);		//B					MCU 3
	setBit(DDRB,2);		//C					MCU 4
	setBit(DDRB,3);		//Row A				MCU 8
	setBit(DDRB,4);		//Row B				MCU 9
	setBit(DDRB,5);		//Row C				MCU 10
	setBit(DDRB,6);		//Subsegment A		MCU 5
	setBit(DDRB,7);		//Subsegment B		MCU 6
	setBit(DDRD,0);		//Subsegment C		MCU 7
	setBit(DDRD,1);		//Segment A			Internal
	setBit(DDRD,2);		//Segment B			Internal
	setBit(DDRD,3);		//Segment C			Internal
	
	Flipdot_clearBuffer();
}

void Flipdot_setData (uint8_t x, uint8_t y, uint8_t row, uint8_t column){
	f_data[0] = (pgm_read_byte(&rows[y][row]) >> 3) & 1;
	f_data[1] = (pgm_read_byte(&rows[y][row]) >> 2) & 1;
	f_data[2] = (pgm_read_byte(&rows[y][row]) >> 1) & 1;
	f_data[3] = (pgm_read_byte(&rows[y][row]) >> 0) & 1;
				 
	f_data[4] = (pgm_read_byte(&columns[x][column]) >> 5) & 1;
	f_data[5] = (pgm_read_byte(&columns[x][column]) >> 4) & 1;
	f_data[6] = (pgm_read_byte(&columns[x][column]) >> 3) & 1;
	f_data[7] = (pgm_read_byte(&columns[x][column]) >> 2) & 1;
	f_data[8] = (pgm_read_byte(&columns[x][column]) >> 1) & 1;
	f_data[9] = (pgm_read_byte(&columns[x][column]) >> 0) & 1;
}

void Flipdot_writePixel (uint8_t x, uint8_t y, uint8_t state){
	if(x < XMAX && y < YMAX && state <= 1){
		uint8_t x_mod = x % 2;
		uint8_t y_mod = y % 2;
		if(state == 1){
			if(!x_mod && !y_mod){
				Flipdot_setData(x,y,0,0);
			}else if(!x_mod && y_mod){
				Flipdot_setData(x,y,0,1);
			}else if(x_mod && !y_mod){
				Flipdot_setData(x,y,1,0);
			}else if(x_mod && y_mod){
				Flipdot_setData(x,y,1,1);
			}
		}else{
			if(!x_mod && !y_mod){
				Flipdot_setData(x,y,1,1);
				}else if(!x_mod && y_mod){
				Flipdot_setData(x,y,1,0);
				}else if(x_mod && !y_mod){
				Flipdot_setData(x,y,0,1);
				}else if(x_mod && y_mod){
				Flipdot_setData(x,y,0,0);
			}
		}
	}
	
	//TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO 
	//	I/O pins		NAME			NAME ON BOARD
	//TODO: SET CORRECT BIT MASKING OPERATIONS ACCORDING TO THE COMMENTS BELOW!!!!! [digitalWrite]
	PORTB |= (f_data[0]<<0);		//A					MCU 2
	PORTB |= (f_data[1]<<1);		//B					MCU 3
	PORTB |= (f_data[2]<<2);		//C					MCU 4
	PORTB |= (f_data[3]<<3);		//Row A				MCU 8
	PORTB |= (f_data[4]<<4);		//Row B				MCU 9
	PORTB |= (f_data[5]<<5);		//Row C				MCU 10
	PORTB |= (f_data[6]<<6);		//Subsegment A		MCU 5
	PORTB |= (f_data[7]<<7);		//Subsegment B		MCU 6
	PORTD |= (f_data[8]<<0);		//Subsegment C		MCU 7
	PORTD |= (f_data[9]<<1);		//RE PIN MISSING FROM DESIGN!!!!!!!

	PORTD |= (f_data[]<<1);		//Segment A			Internal
	PORTD |= (f_data[]<<2);		//Segment B			Internal
	PORTD |= (f_data[]<<3);		//Segment C			Internal
	  
	  //digitalWrite(RE, data[0]);
	  //digitalWrite(RA, data[1]);
	  //digitalWrite(RB, data[2]);
	  //digitalWrite(RC, data[3]);
	  //digitalWrite(EA, data[4]);
	  //digitalWrite(EB, data[5]);
	  //digitalWrite(EC, data[6]);
	  //digitalWrite(A, data[7]);
	  //digitalWrite(B, data[8]);
	  //digitalWrite(C, data[9]);
//
	  //resetPins();
}