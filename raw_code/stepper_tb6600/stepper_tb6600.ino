#include "ParamConfig.h"
#include "Motor.h"

void setup() {
  Param_Setup();
  Motor_Setup();

  Serial.println("Setup done...!!!");
}

void loop() {
  
}
