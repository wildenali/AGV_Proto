#include "oriental.h"
#define button_Start  2

void setup() {
  Serial.begin(9600);
  pinMode(button_Start, INPUT_PULLUP);
  pinMode(stepPin_1,OUTPUT);
  pinMode(dirPin_1,OUTPUT);
  pinMode(enPin_1,OUTPUT);
//  digitalWrite(enPin_1,LOW);
  digitalWrite(dirPin_1,HIGH); // CW

  pinMode(stepPin_2,OUTPUT);
  pinMode(dirPin_2,OUTPUT);
  pinMode(enPin_2,OUTPUT);
//  digitalWrite(enPin_2,LOW);
  digitalWrite(dirPin_2,HIGH); // CW
}

void loop() {

  if (digitalRead(button_Start) == LOW) 
      {  
        digitalWrite(enPin_1,LOW);
        digitalWrite(enPin_2,LOW);
//        speedPot_1();
        speedPot_2();
      }
  else{
        motorSTOP_1();
        motorSTOP_2();
        digitalWrite(enPin_1,HIGH);
        digitalWrite(enPin_2,HIGH);
      }
//int state = digitalRead(button_Start);
//       Serial.println(state);
}
