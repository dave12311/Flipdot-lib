#include "Flipdot.h"

int main(void){
	Flipdot_init();
	Flipdot_setDelay(3);

	Flipdot_setLetter(1,0);
	Flipdot_setLetter(2,5);
	Flipdot_setLetter(3,10);
	Flipdot_setLetter(4,15);
	Flipdot_setLetter(5,20);
	uint16_t t_delay = 0;

	while(1){
		Flipdot_writeBuffer(0,t_delay);
		Flipdot_delay(7811);
		Flipdot_fillScreen(0);
		Flipdot_delay(7811);
		
		Flipdot_writeBuffer(1,t_delay);
		Flipdot_delay(7811);
		Flipdot_fillScreen(0);
		Flipdot_delay(7811);
		
		Flipdot_writeBuffer(2,t_delay);
		Flipdot_delay(7811);
		Flipdot_fillScreen(0);
		Flipdot_delay(7811);
		
		Flipdot_writeBuffer(3,t_delay);
		Flipdot_delay(7811);
		Flipdot_fillScreen(0);
		Flipdot_delay(7811);
		
		t_delay++;
	}
}

