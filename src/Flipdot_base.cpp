/*
  Flipdot.cpp - Flipdot controller library.
  The cake is a lie.
*/

#include "Arduino.h"
#include "Flipdot_base.h"

Flipdot::Flipdot(uint16_t d){
  if(d > 0 && d < 6000){
    write_delay = d;
  } else {
    write_delay = DEFAULT_DELAY;
  }
  
  for(int i=0;i<10;i++){
    pinMode(pins[i], OUTPUT);
  }
}

void Flipdot::resetPins(){
  delayMicroseconds(write_delay);
  
  digitalWrite(RE, LOW);
  digitalWrite(RA, LOW);
  digitalWrite(RB, LOW);
  digitalWrite(RC, LOW);
  digitalWrite(EA, LOW);
  digitalWrite(EB, LOW);
  digitalWrite(EC, LOW);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
}

void Flipdot::setData(uint8_t x, uint8_t y, uint8_t r, uint8_t c){
  data[0] = bitRead(rows[y][r],3);
  data[1] = bitRead(rows[y][r],2);
  data[2] = bitRead(rows[y][r],1);
  data[3] = bitRead(rows[y][r],0);
  
  data[4] = bitRead(columns[x][c],5);
  data[5] = bitRead(columns[x][c],4);
  data[6] = bitRead(columns[x][c],3);
  data[7] = bitRead(columns[x][c],2);
  data[8] = bitRead(columns[x][c],1);
  data[9] = bitRead(columns[x][c],0); 
}

void Flipdot::setPixel(uint8_t x, uint8_t y, uint8_t state){
  if(x < XMAX && y < YMAX){
    if(state == true){
      if(x % 2 == 0 && y % 2 == 0){
        setData(x,y,0,0);
      } else if(x % 2 == 0 && y % 2 != 0){
        setData(x,y,0,1);
      } else if(x % 2 != 0 && y % 2 == 0){
        setData(x,y,1,0);
      } else if(x % 2 != 0 && y % 2 != 0){
        setData(x,y,1,1);
      }
    } else {
      if(x % 2 == 0 && y % 2 == 0){
        setData(x,y,1,1);
      } else if(x % 2 == 0 && y % 2 != 0){
        setData(x,y,1,0);
      } else if(x % 2 != 0 && y % 2 == 0){
        setData(x,y,0,1);
      } else if(x % 2 != 0 && y % 2 != 0){
        setData(x,y,0,0);
      }
    }
    
    digitalWrite(RE, data[0]);
    digitalWrite(RA, data[1]);
    digitalWrite(RB, data[2]);
    digitalWrite(RC, data[3]);
    digitalWrite(EA, data[4]);
    digitalWrite(EB, data[5]);
    digitalWrite(EC, data[6]);
    digitalWrite(A, data[7]);
    digitalWrite(B, data[8]);
    digitalWrite(C, data[9]);

    resetPins();
  }
}

