#include "Flipdot.h"

Flipdot flipdot;

void setup() {
}

void loop() {
  for(int y = 0;y < 7;y++){
    for(int x = 0;x < 24;x++){
      flipdot.setPixel(x,y,true);
    }
  }
  delay(1000);
  for(int x = 0;x < 24;x++){
    for(int y = 0;y < 7;y++){
      flipdot.setPixel(x,y,false);
      delay(10);
    }
  }
  delay(1000);
}