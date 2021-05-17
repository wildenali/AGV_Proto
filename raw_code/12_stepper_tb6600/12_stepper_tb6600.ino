#include "TimerOne.h"
#include "TimerThree.h"
#include "ParamConfig.h"
#include "Motor.h"

void setup() {
  pinMode(button_Start, INPUT_PULLUP);
  Param_Setup();
  Motor_Setup();

  Serial.println("Setup done...!!!");
}

void loop() {
//  if (digitalRead(button_Start) == LOW) 
//      {  
//        motor_1_();
//        motor_2_();
//        
//        digitalWrite(enPin_1,LOW);
//        digitalWrite(enPin_2,LOW);
//        speedPot_1();
//        speedPot_2();
//      }
//  else{
//        motorSTOP_1();
//        motorSTOP_2();
//        digitalWrite(enPin_1,HIGH);
//        digitalWrite(enPin_2,HIGH);
//      }
  if (digitalRead(button_Start) == LOW)
  {
    Timer1.start();
    speedPot_1();
    speedPot_2();
  }
  else
  {
    Timer1.stop();
  }
}
