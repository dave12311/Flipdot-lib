#include "Flipdot_base.h"

Flipdot_base flipdot;

void setup() {
}

void loop() {
  for(int y = 0;y < 7;y++){
    for(int x = 0;x < 24;x++){
      flipdot.setPixel(x,y,true);
    }
  }
  delay(3000);
  for(int x = 0;x < 24;x++){
    for(int y = 0;y < 7;y++){
      flipdot.setPixel(x,y,false);
      delay(10);
    }
  }
  delay(3000);
}
