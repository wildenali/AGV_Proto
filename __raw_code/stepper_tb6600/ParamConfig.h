// untuk motor motor_1_
const int motor_1_StepPin               = 3;
const int motor_1_DirPin                = 7;
const int motor_1_Interval = 1250;
bool motor_1_StepState = LOW;

// untuk motor motor_2_
const int motor_2_StepPin               = 2;  // timer 3, pin 2,3,5
const int motor_2_DirPin                = 6;
const long motor_2_Interval = 1250;
bool motor_2_StepState = LOW;

void Param_Setup(){
  Serial.begin(115200); 
}