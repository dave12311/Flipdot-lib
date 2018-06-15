/*
  Flipdot_base.h - Basic functions for Flipdot controller.
  The cake is a lie.
*/

#ifndef Flipdot_base_h
#define Flipdot_base_h

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

class Flipdot_base{
  public:
    Flipdot_base(uint16_t d = DEFAULT_DELAY);
    void setPixel(uint8_t x, uint8_t y, uint8_t state);     //Sets the given pixel on the screen
    void setBuffer(uint8_t x, uint8_t y, uint8_t state);    //Sets the given pixel in the screen buffer
    void writeBuffer(uint8_t style);                        //Writes the screen buffer to the screen with the given update style
  private:
    uint8_t buffer[24];
    uint8_t data[10];
    uint16_t write_delay;
    void resetPins();
    void setData(uint8_t x, uint8_t y, uint8_t r, uint8_t c);
    const uint8_t columns[24][2] = {  {B010100,B110100},{B110010,B010010},{B010000,B110000},{B110110,B010110},{B011011,B101011},{B110001,B010001},{B011101,B101101},{B110101,B010101},{B011001,B101001},{B110011,B010011},{B011110,B101110},{B100000,B001000},{B011010,B101010},{B100100,B001100},{B011100,B101100},{B100010,B001010},{B011000,B101000},{B100110,B001110},{B111111,B111010},{B100001,B001001},{B111011,B111100},{B100101,B001101},{B111101,B111000},{B100011,B001011}  };
    const uint8_t rows[7][2] = {  {B0111,B1100},{B1010,B0011},{B0101,B1110},{B1001,B0001},{B0110,B1101},{B1011,B0010},{B0100,B1111}  };
    const uint8_t pins[10] = {2,3,4,5,6,7,8,9,10,A0};
};

#endif

