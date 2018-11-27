// This if for the second robot

#include <IRremote.h>

int RECV_PIN = 10;
int LED_1 = 4;
int LED_2 = 5;
int LED_3 = 6;
int LED_4 = 8;
int health = 4;

int count =0;

IRrecv irrecv(RECV_PIN);

IRsend irsend;

decode_results results;

void setup()
{
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
}

void loop()
{
  //Receiving
  if ((irrecv.decode(&results)) ) 
  {
    Serial.print("Protocol: ");
    Serial.println(results.decode_type, DEC);
    Serial.println(results.value, HEX);
    if (results.value == 0xffc23d || results.value == 0xFFC23D)
    {
    Serial.println("I'm shot");
    health--;
    Serial.println(health); 
    }
    irrecv.resume(); // Receive the next value
  }
  switch(health) {
    case 1:
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      break;
    case 2:
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      break;  
    case 3:
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, LOW);
      break;
    case 4:
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, HIGH);
      digitalWrite(LED_4, HIGH);
      break;   
    case 0:
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
      digitalWrite(LED_4, LOW);
      health = 5;
      break;
  }
    delay(100);
    count++;
    if (count == 30){
      count =0;
     //Shooting
     Serial.println("Shooting");
     irsend.sendRC5(0xff22dd, 32);
     irrecv.enableIRIn(); // Start the receiver  
     delay(100);
    }
}
