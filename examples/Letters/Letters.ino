#include "Flipdot.h"

Flipdot flipdot;

void setup(){

}

void loop(){
    flipdot.writeAll();
    delay(200);

    flipdot.setLetter(1,0);
    flipdot.setLetter(2,5);
    flipdot.setLetter(3,10);
    flipdot.setLetter(4,15);
    flipdot.setLetter(5,20);
    flipdot.writeBuffer(2);
    delay(200);
}