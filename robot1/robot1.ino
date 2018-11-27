#include <IRLibAll.h>

IRsendSony mySender;

int button_pin = 13; //set D10 as input signal pin

void setup(){
  Serial.begin(9600);
}

void loop(){
  if (Serial.read() != -1)
  {
    mySender.send(0xa8bca, 20);
    }
}
