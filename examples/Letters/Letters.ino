#include "Flipdot.h"

Flipdot flipdot;

void setup(){

}

void loop(){
    flipdot.setAll();
    delay(200);

    flipdot.writeLetter(0,0);
    flipdot.writeLetter(1,5);
    flipdot.writeLetter(2,10);
    flipdot.writeLetter(3,15);
    flipdot.writeLetter(4,20);
    flipdot.writeBuffer(0);
    delay(200);
}