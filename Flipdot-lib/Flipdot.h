/**
 * @file Flipdot.h
 * @author David Horvath
 * @brief Basic functionality for Flipdot controllers.
 * @note Pin definitions can be changed in "Flipdot_pins.h"
*/

//The cake is a lie.

#include "Flipdot_pins.h"
#include <stdint.h>
#include <avr/pgmspace.h>

#ifndef FLIPDOT_H_
#define FLIPDOT_H_

/**
 * @brief Default delay value.
 *
 * Time each pixel is held high for magnetization. The default delay is around 500 microseconds.
 * @see Flipdot_delay
 */
#define DEFAULT_DELAY 5

/**
 * @brief Maximum delay.
 *
 * Maximum magnetization length allowed.
 * @see Flipdot_delay
 */
#define DELMAX 15

/**
 * @brief Minimum delay.
 *
 * Minimum magnetization length allowed.
 * @see Flipdot_delay
 */
#define DELMIN 2

/**
 * @brief Horizontal size.
 *
 * Number of horizontal pixels in one segment.
 */
#define XMAX 24

/**
 * @brief Vertical size.
 *
 * Number of vertical pixels in one segment.
 */
#define YMAX 7

/**
 * @brief Number of segments.
 *
 * Total number of segments.
 */
#define SEGNUM 4

/**
 * @brief Number of fonts.
 *
 * Total number of preprogrammed characters.
 * @see font
 */
#define FONTS 45

/**
 * @brief Display style.
 *
 * Refresh direction of the screen Can be @b down, @b up, @b right or @b left.
 * @see Flipdot_writeBuffer
 */
enum Style{down,up,right,left};

/************************************************************************/
/*                           FUNCTIONS                                  */
/************************************************************************/

/**
 * @brief Initialize the library.
 *
 * Must be called before using any functions. Sets outputs and delay.
 */
void Flipdot_init (void);

/**
 * @brief Change pixel delay.
 *
 * Sets the time each pixel is magnetized for and stores it in @b f_writeDelay.
 * @param delay Number of timer cycles.
 * @see Flipdot_delay
 * @see f_writeDelay
 * @see DEFAULT_DELAY
 * @see DELMAX
 * @see DELMIN
 */
void Flipdot_setDelay (uint8_t delay);

/**
 * @brief Write a single pixel.
 *
 * Turns on or off a single pixel on the screen.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param state Desired state of the pixel. @b 1 to turn @b on or @b 0 to turn @b off.
 */
void Flipdot_writePixel (uint8_t x, uint8_t y, uint8_t state);

/**
 * @brief Clear the whole screen.
 *
 * Quickly sets the whole screen on or off.
 * @param state Desired state of the screen. @b 1 to turn @b on or @b 0 to turn @b off.
 */
void Flipdot_fillScreen (uint8_t state);

/**
 * @brief Set a single character in buffer.
 *
 * Sets the given letter in buffer with the given indent from the left side of the screen.
 * @param letter Code of the character to write. These are stored in the @b font variable.
 * @param indent Number of columns to indent the letter from the left side of the screen.
 * @return The function returns the length of the written character.
 * @see font
 * @see Flipdot_writeBuffer
 */
uint8_t Flipdot_setLetter (uint8_t letter, uint8_t indent);

/**
 * @brief Set the value of a single pixel in the buffer.
 *
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param state Desired state of the pixel. @b 1 to turn @b on or @b 0 to turn @b off.
 * @see Flipdot_writeBuffer
 */
void Flipdot_setBuffer (uint8_t x, uint8_t y, uint8_t state);

/**
 * @brief Write the buffer to the screen.
 *
 * Copies the contents of the buffer to the screen with the given direction.
 * @param style Refresh direction of the screen.
 * @param delay Number of timer cycles to wait between each pixel.
 * @see Style
 * @see Flipdot_delay
 */
void Flipdot_writeBuffer (enum Style style, uint8_t delay);

/**
 * @brief Clear the buffer.
 *
 * Sets all cells of the internal buffer to @b 0 @b (off).
 */
void Flipdot_clearBuffer (void);

/************************************************************************/
/*                      INTERNAL FUNCTIONS                              */
/************************************************************************/

/**
 * @brief Reset outputs.
 *
 * Sets all outputs to @b LOW after delay.
 * @see f_writeDelay
 * @see Flipdot_delay
 */
void Flipdot_resetPins (void);

/**
 * @brief Set output states.
 *
 * Decodes the required outputs for the given pixel locations and stores it in @b f_frameBuffer.
 * @see f_frameBuffer
 * @see rows
 * @see columns
 */
void Flipdot_setOutputPinData (uint8_t x, uint8_t y, uint8_t rowInvert, uint8_t columnInvert);

/**
 * @brief Time delay function.
 *
 * Waits for @b t seconds. The number of cycles required for the given @b t can be calculated:
 * @verbatim n = (8e6*t-1110)/1024 @endverbatim
 * For example:
 * @code{.c}
 * Flipdot_delay(3);
 * @endcode
 * will result in a total @b t delay of around 500 microseconds.
 * @param n The number of timer cycles to wait.
 */
void Flipdot_delay(uint16_t n);

/************************************************************************/
/*                       INTERNAL VARIALBES                             */
/************************************************************************/

/**
 * @brief Screen buffer.
 *
 * Buffer to construct the contents of the screen without writing them.
 * @see Flipdot_writeBuffer
 */
uint8_t f_frameBuffer[XMAX];

/**
 * @brief Store decoded output data.
 *
 * After decoding, the correct output states for the given pixel are stored here.
 * @see Flipdot_setOutputPinData
 * @see rows
 * @see columns
 */
uint8_t f_outputPinData[10];

/**
 * @brief Magnetization delay.
 *
 * Number of timer cycles each pixel is magnetized for.
 * @see Flipdot_delay
 * @see Flipdot_setDelay
 * @see DEFAULT_DELAY
 * @see DELMAX
 * @see DELMIN
 */
uint8_t f_writeDelay;

#endif
