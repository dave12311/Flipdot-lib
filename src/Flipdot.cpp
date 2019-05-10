/*
  Flipdot.cpp - Basic functionality for Flipdot controllers.
  The cake is a lie.
*/

#include "Arduino.h"
#include "Flipdot.h"

Flipdot::Flipdot(uint16_t d){
  if(d > 0 && d < 6000){
    write_delay = d;
  } else {
    write_delay = DEFAULT_DELAY;
  }
  
  for(uint8_t i=0;i<10;i++){
    pinMode(pins[i], OUTPUT);
  }

  clearBuffer();
}

void Flipdot::writeAll(uint8_t state){
  if(state == 0 || state == 1){
    for(uint8_t y = 0;y < YMAX;y++){
      for(uint8_t x = 0;x < XMAX;x++){
        writePixel(x,y,state);
      }
    }
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

void Flipdot::writePixel(uint8_t x, uint8_t y, uint8_t state){
  if(x < XMAX && y < YMAX && state <= 1){
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

void Flipdot::setBuffer(uint8_t x, uint8_t y, uint8_t state){
  if(x < XMAX && y < YMAX && state <= 1){
    bitWrite(buffer[x],y,state);
  }
}

void Flipdot::writeBuffer(uint8_t style){
  if(style == 0){
    for(int y = 0;y < 7;y++){
      for(int x = 0;x < 24;x++){
        if(bitRead(buffer[x],y) == true){
          writePixel(x,y,true);
        }else{
          writePixel(x,y,false);
        }
      }
    }
  }else if(style == 1){
    for(int y = 6;y >= 0;y--){
      for(int x = 0;x < 24;x++){
        if(bitRead(buffer[x],y) == true){
          writePixel(x,y,true);
        }else{
          writePixel(x,y,false);
        }
      }
    }
  }else if(style == 2){
    for(int x = 0;x < 24;x++){
      for(int y = 0;y < 7;y++){
        if(bitRead(buffer[x],y) == true){
          writePixel(x,y,true);
        }else{
          writePixel(x,y,false);
        }
      }
    }
  }else if(style == 3){
    for(int x = 23;x >= 0;x--){
      for(int y = 0;y < 7;y++){
        if(bitRead(buffer[x],y) == true){
          writePixel(x,y,true);
        }else{
          writePixel(x,y,false);
        }
      }
    }
  }
}

void Flipdot::setLetter(uint8_t letter, uint8_t indent){
	if(letter <= FONTS && letter > 0 && indent < XMAX){
		uint8_t count = 0;
		//Find first byte of letter (count)
		for(uint8_t i = 0;i < letter;){
			while(true){
				if(bitRead(font[count],7) == 1){
					count++;
					break;
				}
				count++;
			}
			i++;
		}
		count--;

		uint8_t x = indent;
		while(true){
			for(uint8_t y = 0; y < 7;y++){
				if(bitRead(font[count],y) == 0){
					setBuffer(x,6-y,false);
				} else {
					setBuffer(x,6-y,true);
				}
			}
			x++;
			if(bitRead(font[count+1],7) == 1 || x+1 > XMAX){
				break;
			} else {
				count++;
			}
		}
	}
}

void Flipdot::clearBuffer(){
  for(uint8_t i=0;i<24;i++){
    buffer[i] = 0;
  }
}

void Flipdot::setWord(uint8_t *wordPointer, uint8_t speed){
  
}