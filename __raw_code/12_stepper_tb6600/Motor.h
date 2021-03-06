void motor_1_(void);
void motor_2_(void);

void Motor_Setup()
{
  pinMode(motor_1_StepPin, OUTPUT);
  pinMode(motor_1_DirPin, OUTPUT);
  pinMode(enPin_1,OUTPUT);
  pinMode(motor_2_StepPin, OUTPUT);
  pinMode(motor_2_DirPin, OUTPUT);
  pinMode(enPin_2,OUTPUT);
  
  Timer1.attachInterrupt(motor_1_);
  Timer3.attachInterrupt(motor_2_);
  
  digitalWrite(motor_1_DirPin,HIGH); // CW
  digitalWrite(motor_2_DirPin,HIGH); // CW  

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

/*----SPEED stepper------------------------------------------------*/
void speedPot_1()
{
    p_1 = analogRead(potmeterPin_1);
    motor_1_Interval = map(p_1,0,1023,1200,600);
    Timer1.initialize(motor_1_Interval);          // 0.00125 seconds = 1250 * 1000000
}
void speedPot_2()
{
    p_2 = analogRead(potmeterPin_2);
    motor_2_Interval = map(p_2,0,1023,1200,600);
    Timer3.initialize(motor_2_Interval);          // 0.00125 seconds = 1250 * 1000000
}
/*----STOP stepper------------------------------------------------*/

void motorSTOP_1()
{
 digitalWrite(motor_1_StepPin,LOW);
}
void motorSTOP_2()
{
 digitalWrite(motor_2_StepPin,LOW);
}
