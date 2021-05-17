// untuk motor motor_1_  // motor_1_Interval = 1200; //600(kenceng) - 1200(pelan)
const int motor_1_StepPin = 3;
const int motor_1_DirPin  = 7;
const int enPin_1         = 8;
int motor_1_Interval;
bool motor_1_StepState = LOW;

// untuk motor motor_2_
const int motor_2_StepPin = 5;  // timer 3, pin 2,3,5
const int motor_2_DirPin  = 6;
const int enPin_2         = 9;
int motor_2_Interval;
bool motor_2_StepState = LOW;

void Param_Setup(){
  Serial.begin(115200); 
}
