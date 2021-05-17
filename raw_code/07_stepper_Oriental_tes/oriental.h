/*---stepper 1 A ---------*/
const int stepPin_1 = 5;
const int dirPin_1 = 4;
const int enPin_1 = 8;
/*---stepper 2 B ---------*/
const int stepPin_2 = 6;
const int dirPin_2 = 7;
const int enPin_2 = 9;
float delay_time_1;
float delay_time_2;
int p_1;
int p_2;
#define potmeterPin_1 A0
#define potmeterPin_2 A1

/*----START stepper------------------------------------------------*/
void motorStep_1( int MAX){
   for(int x = 0; x < MAX; x++) { 
        digitalWrite(stepPin_1,HIGH);
        delayMicroseconds(delay_time_1);
        digitalWrite(stepPin_1,LOW);
        delayMicroseconds(delay_time_1);
      }
}
void motorStep_2( int MAX){
   for(int x = 0; x < MAX; x++) { 
        digitalWrite(stepPin_2,HIGH);
        delayMicroseconds(delay_time_2);
        digitalWrite(stepPin_2,LOW);
        delayMicroseconds(delay_time_2);
      }
}
void speedPot_1()
{
   motorStep_1(1);
   p_1 = analogRead(potmeterPin_1);
   delay_time_1 = map(p_1,0,1023,1000,500);
}
void speedPot_2()
{   
   motorStep_2(1);
   p_2 = analogRead(potmeterPin_2);
   delay_time_2 = map(p_2,0,1023,1000,500);
}
/*----STOP stepper------------------------------------------------*/
void motorSTOP_1()
{
 digitalWrite(stepPin_1,LOW);
}
void motorSTOP_2()
{
 digitalWrite(stepPin_2,LOW);
}
