#include "Flipdot_text.h"

Flipdot_text flipdot;

void setup(){

}

void loop(){
    flipdot.clearAll();
    delay(200);

    flipdot.writeLetter(0,0);
    flipdot.writeLetter(1,5);
    flipdot.writeLetter(2,10);
    flipdot.writeBuffer(0);

}