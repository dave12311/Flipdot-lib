#include "Flipdot.h"

Flipdot flipdot;

void setup(){

}

void loop(){
    flipdot.writeAll();
    delay(200);

    flipdot.setLetter(0,0);
    flipdot.setLetter(1,5);
    flipdot.setLetter(2,10);
    flipdot.setLetter(3,15);
    flipdot.setLetter(4,20);
    flipdot.writeBuffer(2);
    delay(200);
}