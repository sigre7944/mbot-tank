#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMCore.h>

MeIR ir;
MeBuzzer buzzer;
MeRGBLed rgbled_7(7, 7==7?2:4);
MeSerial se;

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
int health = 4;

void move(int direction, int speed)
{
      int leftSpeed = 0;
      int rightSpeed = 0;
      if(direction == 1){
          leftSpeed = speed;
          rightSpeed = speed;
      }else if(direction == 2){
          leftSpeed = -speed;
          rightSpeed = -speed;
      }else if(direction == 3){
          leftSpeed = -speed;
          rightSpeed = speed;
      }else if(direction == 4){
          leftSpeed = speed;
          rightSpeed = -speed;
      }
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}

void setup(){
    ir.begin();
    pinMode(A7,INPUT);
    Serial.begin(9600);
    rgbled_7.setColor(0,66,244,66);
    rgbled_7.show();
}

void loop(){
      if(ir.decode())
    {
      uint32_t value = ir.value;
      Serial.print("Raw Value: ");
      Serial.println(value);
      value = value >> 16 & 0xff;
      Serial.print("Button Code: ");
      Serial.println(value);
      Serial.print("Button: ");
       switch(value)
        {   
            case IR_BUTTON_B: Serial.println("B");
            ir.sendString("S");
            //if(se.equalString(ir.getString(),"S")){
             buzzer.tone(262, 125);
             health--;
     //  }
            break;

            case IR_BUTTON_LEFT: Serial.println("Left");
            move(3,100);
            _delay(0.2);
            move(1,0);
            break;
            
            case IR_BUTTON_RIGHT: Serial.println("Right");
            move(4,100);
            _delay(0.2);
            move(1,0);
            break;
            
            case IR_BUTTON_UP: Serial.println("Up");
            move(1,200);
            _delay(0.5);
            move(1,0);
            break;
            
            case IR_BUTTON_DOWN: Serial.println("Down");
            move(2,200);
            _delay(0.5);
            move(1,0);
            break;
            default:break;
        }

       switch(health)
       {
        case 4:
        rgbled_7.setColor(0,16,135,19);
        rgbled_7.show();
        break;
        
        case 3:
        rgbled_7.setColor(0,105,178,78);
        rgbled_7.show();
        break;
        
        case 2:
        rgbled_7.setColor(0,157,165,64);
        rgbled_7.show();
        break;
        
        case 1:
        rgbled_7.setColor(0,158,78,18);
        rgbled_7.show();
        break;

        case 0:
        rgbled_7.setColor(0,158,18,18);
        rgbled_7.show();
        health = 5;
        break;
       }
    }

    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
}
  
