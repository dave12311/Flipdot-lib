#include "Flipdot.h"

int main(void){
	Flipdot_init();
	uint8_t text[4][5] = { {1,0,0,0,0}, {1,2,0,0,0}, {1,2,3,0,0}, {1,2,3,4,0} };
	while(1){
		for(uint8_t i=0;i<4;i++){
			Flipdot_setString(&text[i][0]);
			Flipdot_writeBuffer(0,0);
			Flipdot_delay(4000);
		}
	}
}

