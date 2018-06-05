#include "Flipdot_text.h"

Flipdot_text flipdot;

void setup(){
}

void loop(){
    for(int i=0;i<26;i++){
        flipdot.writeLetter(i);
        delay(3000);
    }
}