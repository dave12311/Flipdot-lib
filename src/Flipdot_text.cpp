/*
  Flipdot_text.h - Text library for Flipdot controller.
  The cake is a lie.
*/

#include "Arduino.h"
#include "Flipdot_base.h"
#include "Flipdot_text.h"

void Flipdot_text::clearAll(){
	for(uint8_t y = 0;y < 7;y++){
		for(uint8_t x = 0;x < 24;x++){
			Flipdot.setPixel(x,y,false);
		}
	}
}

void Flipdot_text::writeLetter(uint8_t l){
	uint8_t count = 0;
	//Find first byte of letter (count)
	for(uint8_t i = 0;i < l+1;){
		while(true){
			if(bitRead(font[count],7) == 1){
				count++;
				break;
			}
			count++;
		}
		i++;
	}
	count--;
	
	//-----------------------------
	Serial.println("Letter: ");
	Serial.println(count);
	Serial.println();
	
	//-----------------------------

	uint8_t x = 0;
	while(true){
		for(uint8_t y = 0; y < 7;y++){
			if(bitRead(font[count],y) == 0){
				Flipdot.setPixel(x,6-y,false);
			} else {
				Flipdot.setPixel(x,6-y,true);
			}
		}
		x++;
		if(bitRead(font[count+1],7) == 1){
			break;
		} else {
			count++;
		}
	}
}