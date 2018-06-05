/*
  Flipdot_text.h - Text library for Flipdot controller.
  The cake is a lie.
*/

#include "Arduino.h"
#include "Flipdot_base.h"
#include "Flipdot_text.h"

void Flipdot_text::writeLetter(uint8_t l){
	uint8_t count = 0;
	//Find first byte of letter (count)
	for(uint8_t i = 0;i < l+1;){
		while(true){
			if(bitRead(7,font[count]) == 1){
				count++;
				break;
			}
			count++;
		}
		i++;
	}
	count--;

	uint8_t x = 0;
	while(true){
		for(uint8_t y = 0; y < 7;y++){
			if(bitRead(y,font[count]) == 0){
				setPixel(x,y,false);
			} else {
				setPixel(x,y,true);
			}
		}
		x++;
		if(bitRead(7,font[count+1]) == 1){
			break;
		} else {
			count++;
		}
	}
}