#include "ParamConfig.h"
#include "Motor.h"
#define button_Start  2

void setup() {
  pinMode(button_Start, INPUT_PULLUP);
  Param_Setup();
  Motor_Setup();

  Serial.println("Setup done...!!!");
}

void loop() {
  if (digitalRead(button_Start) == LOW) 
      {  
        digitalWrite(enPin_1,LOW);
        digitalWrite(enPin_2,LOW); 
        speedPot_1();
        speedPot_2();
      }
  else{
        digitalWrite(enPin_1,HIGH);
        digitalWrite(enPin_2,HIGH);
      }  
}
