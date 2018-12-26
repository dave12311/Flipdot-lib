/*
  Flipdot.h - Basic functionality for Flipdot controllers.
  The cake is a lie.
*/
#include <stdint.h>
#include <avr/pgmspace.h>

#ifndef Flipdot_h
#define Flipdot_h

//Number of microseconds each pixel is held high for magnetization
#define DEFAULT_DELAY 700

//Size of a segment
#define XMAX 24
#define YMAX 7

//Number of programmed characters
#define FONTS 45

/* ------------------------------------------- Functions ------------------------------------------- */

void Flipdot_init (void);											//Initialize the library
void Flipdot_setDelay (uint16_t delay);								//Set the number of microseconds each pixel is magnetized for
void Flipdot_setBuffer (uint8_t x, uint8_t y, uint8_t state);		//Sets the given pixel in the buffer
void Flipdot_clearBuffer (void);									//Clears the internal buffer

/* ------------------------------------------- Internal functions ------------------------------------------- */

void Flipdot_resetPins (void);										//Sets all output to LOW after delay

/* ------------------------------------------- Internal variables ------------------------------------------- */
uint8_t f_buffer[24];
uint8_t f_data[10];
uint16_t f_write_delay;

#endif