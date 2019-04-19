/*
  Flipdot.h - Basic functionality for Flipdot controllers.
  The cake is a lie.
*/
#include <stdint.h>
#include <avr/pgmspace.h>

#ifndef Flipdot_h
#define Flipdot_h

//Number of microseconds each pixel is held high for magnetization
#define DEFAULT_DELAY 6		//6*125ns = 750ns

//Size of a segment
#define XMAX 24
#define YMAX 7

//Number of programmed characters
#define FONTS 45

/* ---------------------------------------------------------- Functions ---------------------------------------------------------- */

void Flipdot_init (void);																		//Initialize the library
void Flipdot_setDelay (uint16_t delay);															//Set the number of microseconds each pixel is magnetized for
void Flipdot_writePixel (uint8_t x, uint8_t y, uint8_t state);									//Writes the given pixel to the screen
void Flipdot_setBuffer (uint8_t x, uint8_t y, uint8_t state);									//Sets the given pixel in the buffer
void Flipdot_clearBuffer (void);																//Clears the internal buffer

/* ----------------------------------------------------- Internal functions ------------------------------------------------------ */

void Flipdot_resetPins (void);																	//Sets all output to LOW after delay
void Flipdot_setOutputPinData (uint8_t x, uint8_t y, uint8_t rowInvert, uint8_t columnInvert);	//Decodes pixel locations in data register
void Flipdot_delay(uint8_t t);																	//Delay t = 1 => 125ns @8MHz

/* ----------------------------------------------------- Internal variables ------------------------------------------------------ */
uint8_t f_frameBuffer[24];
uint8_t f_outputPinData[10];
uint16_t f_writeDelay;

#endif