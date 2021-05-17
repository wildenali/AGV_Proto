char myChar = 0;
int LED=13;
 
void setup() {
   Serial.begin(9600);
   pinMode(13,OUTPUT);
}
void loop() {
   while (Serial.available() > 0) 
   {
     myChar = Serial.read();
     Serial.println(myChar);
   }
}
