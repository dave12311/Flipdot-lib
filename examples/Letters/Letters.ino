#include "Flipdot_text.h"

Flipdot_text flipdot;

void setup(){
  Serial.begin(9600);
}

void loop(){
    for(int i=0;i<45;i++){
        flipdot.clearAll();
        flipdot.writeLetter(i);
        delay(500);
    }
}