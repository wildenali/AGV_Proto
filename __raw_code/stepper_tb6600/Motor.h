#include "TimerOne.h"
#include "TimerThree.h"


void motor_1_(void);
void motor_2_(void);

void Motor_Setup()
{
  pinMode(motor_1_StepPin, OUTPUT);
  pinMode(motor_1_DirPin, OUTPUT);
  pinMode(motor_2_StepPin, OUTPUT);
  pinMode(motor_2_DirPin, OUTPUT);
  
  Timer1.initialize(motor_1_Interval);          // 0.00125 seconds = 1250 * 1000000
  Timer1.attachInterrupt(motor_1_);

  Timer3.initialize(motor_2_Interval);          // 0.00125 seconds = 1250 * 1000000
  Timer3.attachInterrupt(motor_2_);

  Serial.println("Motor Setup..... Done");
}

void motor_1_(void)
{
  if (motor_1_StepState == LOW) {
    motor_1_StepState = HIGH;
  } else {
    motor_1_StepState = LOW;
  }

  digitalWrite(motor_1_DirPin, LOW);
  digitalWrite(motor_1_StepPin, motor_1_StepState);
}

void motor_2_(void)
{
  if (motor_2_StepState == LOW) {
    motor_2_StepState = HIGH;
  } else {
    motor_2_StepState = LOW;
  }

  digitalWrite(motor_2_DirPin, LOW);
  digitalWrite(motor_2_StepPin, motor_2_StepState);
}