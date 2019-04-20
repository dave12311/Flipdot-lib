#include "Flipdot.h"

int main(void){
	Flipdot_init();
	Flipdot_fillScreen(0);
	Flipdot_writePixel(0,0,1);
	Flipdot_setBuffer(1,1,0);
	uint8_t a = Flipdot_setLetter(1,5);
	Flipdot_writeBuffer(3,0);
}

