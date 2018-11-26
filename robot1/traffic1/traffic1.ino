#include <IRremote.h>

int redA = 8;
int yellowA = 9;
int greenA = 10;
int redB = 11;
int yellowB = 12;
int greenB = 13;
int i = 0;
int input_pin = 3; //set D10 as input signal pin

int mode = 0; //regular mode, 1 for K, 2 for J
IRrecv irrecv(input_pin);
decode_results signals;
#define code1  0xC101E57B  // Hex Code for Button 1 of IRR Remote
#define code2  0x97483BFB  // Hex Code for Button 2 of IRR Remote

void setup() {
  Serial.begin(9600);
  attachInterrupt(0,CHECK_IR,CHANGE);
  irrecv.enableIRIn(); // enable input from IR receiver
  pinMode(redA, OUTPUT);
  pinMode(yellowA, OUTPUT);
  pinMode(greenA, OUTPUT);
  pinMode(redB, OUTPUT);
  pinMode(yellowB, OUTPUT);
  pinMode(greenB, OUTPUT);
  

}

void CHECK_IR(){
  while(irrecv.decode(&signals)){
  Serial.println(signals.value, HEX);
  if ( signals.value == 0xC101E57B || signals.value == 0xFF18EF)
    {
      mode = 1;
    }
    
  if ( signals.value == 0x9716BE3F  || signals.value == 0xFF30CF )
    {
      mode = 2;
    }
  irrecv.resume();
  }
}

void loop() {

    digitalWrite(redA, HIGH);
    digitalWrite(greenB, HIGH);
    if (mode == 2){
      delay(15000);
      mode == 0;
    }
    else 
    {
      delay(10000);
    }
    
    digitalWrite(greenB, LOW);        //10 seconds
    
                
    for (i=0;i<5;i++) {           //lights on as long as off
      digitalWrite(yellowB, HIGH);
      delay(500);
      digitalWrite(yellowB, LOW);
      delay(500);
    }
    digitalWrite(redA, LOW);        // 15 seconds
    
    digitalWrite(redB, HIGH);
    digitalWrite(greenA, HIGH);
    if (mode == 1){
      delay(15000);
      mode == 0;
    }
    else 
    {
      delay(10000);
    }                    //25 seconds
    
    digitalWrite(greenA,LOW);
    
    for (i=0;i<5;i++) {           //lights on longer than off
      digitalWrite(yellowA, HIGH);
      delay(700);                   
      digitalWrite(yellowA, LOW);
      delay(300);       
    }
    digitalWrite(redB, LOW);        //30 seconds

}