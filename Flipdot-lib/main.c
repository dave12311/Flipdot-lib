#include "Flipdot.h"

int main(void){
	Flipdot_init();
	while(1){
		uint8_t length = Flipdot_setLetter(132,0);
		Flipdot_clearBuffer();
		for(uint8_t i=1;i<XMAX-length+1;i++){
			Flipdot_clearBuffer();
			if(i%2==0){
				Flipdot_setLetter(132,i);
				}else{
				Flipdot_setLetter(133,i);
			}
			Flipdot_writeBuffer(0,0);
			Flipdot_delay(500);
		}
		for(int8_t i=(XMAX-length-1);i>=0;i--){
			Flipdot_clearBuffer();
			if(i%2==0){
				Flipdot_setLetter(132,i);
				}else{
				Flipdot_setLetter(133,i);
			}
			Flipdot_writeBuffer(0,0);
			Flipdot_delay(500);
		}
	}
}

