#include "Flipdot.h"

int main(void){
	Flipdot_init();
	
	while(1){
			for(uint8_t x=0;x<24;x++){
				for(uint8_t y=0;y<7;y++){
					Flipdot_writePixel(x,y,1);
					Flipdot_delay(200);
				}
			}
			
			for(uint8_t x=0;x<24;x++){
				for(uint8_t y=0;y<7;y++){
					Flipdot_writePixel(x,y,0);
					Flipdot_delay(200);
				}
			}
	}
}

