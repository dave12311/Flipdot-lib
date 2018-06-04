/*
  Flipdot_text.h - Text library for Flipdot controller.
  The cake is a lie.
*/

#include "Arduino.h"
#include "Flipdot_base.h"
#include "Flipdot_text.h"

void Flipdot_text::writeLetter(uint8_t l){
	uint8_t row_counter = 0;
	uint8_t letter_counter = 0;
	
	while(letter_counter != l){
		if(bitRead(7,font[row_counter]) == 1){
			
		}
	}
}