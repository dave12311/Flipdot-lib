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

void Flipdot_text::writeBuffer(uint8_t style){
	Flipdot.writeBuffer(style);
}

void Flipdot_text::writeLetter(uint8_t letter, uint8_t indent){
	if(letter < FONTS && indent < YMAX){
		uint8_t count = 0;
		//Find first byte of letter (count)
		for(uint8_t i = 0;i < letter+1;){
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

		uint8_t x = indent;
		while(true){
			for(uint8_t y = 0; y < 7;y++){
				if(bitRead(font[count],y) == 0){
					Flipdot.setBuffer(x,6-y,false);
				} else {
					Flipdot.setBuffer(x,6-y,true);
				}
			}
			x++;
			if(bitRead(font[count+1],7) == 1 && x+1 >= YMAX){
				break;
			} else {
				count++;
			}
		}
	}
}