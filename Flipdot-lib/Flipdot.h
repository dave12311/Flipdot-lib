/*
  Flipdot.h - Basic functionality for Flipdot controllers.
  The cake is a lie.
  
  NOTE:
	Pin definitions can be changed in "Flipdot_pins.h"
*/

#include "Flipdot_pins.h"
#include <stdint.h>
#include <avr/pgmspace.h>

#ifndef Flipdot_h
#define Flipdot_h

//Number of microseconds each pixel is held high for magnetization
#define DEFAULT_DELAY 5

//Maximum and minimum magnetization length allowed
#define DELMAX 15
#define DELMIN 2

//Size of a segment
#define XMAX 24
#define YMAX 7

//Number of segments
#define SEGNUM 4

//Number of programmed characters
#define FONTS 45

/* ---------------------------------------------------------- Functions ---------------------------------------------------------- */

void Flipdot_init (void);																		//Initialize the library
void Flipdot_setDelay (uint8_t delay);															//Set the number of microseconds each pixel is magnetized for
void Flipdot_writePixel (uint8_t x, uint8_t y, uint8_t state);									//Writes the given pixel to the screen
void Flipdot_fillScreen (uint8_t state);														//Fills the whole screen with 0 or 1
uint8_t Flipdot_setLetter (uint8_t letter, uint8_t indent);										//Sets the specified letter in buffer with the specified indent. Returns the length of the letter
void Flipdot_setBuffer (uint8_t x, uint8_t y, uint8_t state);									//Sets the given pixel in the buffer
void Flipdot_writeBuffer (uint8_t style, uint8_t delay);										//Writes the screen buffer to the screen with the given update style [0:down; 1:up; 2:right; 3:left] and waits [delay*125ns @8MHz] between each pixel
void Flipdot_clearBuffer (void);																//Clears the internal buffer

/* ----------------------------------------------------- Internal functions ------------------------------------------------------ */

void Flipdot_resetPins (void);																	//Sets all output to LOW after delay
void Flipdot_setOutputPinData (uint8_t x, uint8_t y, uint8_t rowInvert, uint8_t columnInvert);	//Decodes pixel locations in data register
void Flipdot_delay(uint16_t n);																	//Delay [t] seconds: n=(8e6*t-1110)/1024

/* ----------------------------------------------------- Internal variables ------------------------------------------------------ */
uint8_t f_frameBuffer[XMAX];
uint8_t f_outputPinData[10];
uint8_t f_writeDelay;

#endif
