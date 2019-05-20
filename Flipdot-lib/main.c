#include "Flipdot.h"

int main(void){
	Flipdot_init();
	uint8_t text[] = {0,0,0,0,0};
	while(1){
		Flipdot_setString(1, text);
		Flipdot_writeBuffer(0,0);
		Flipdot_delay(4000);
		Flipdot_setString(2, text);
		Flipdot_writeBuffer(0,0);
		Flipdot_delay(4000);
		Flipdot_setString(3, text);
		Flipdot_writeBuffer(0,0);
		Flipdot_delay(4000);
		Flipdot_setString(4, text);
		Flipdot_writeBuffer(0,0);
		Flipdot_delay(4000);
	}
}

