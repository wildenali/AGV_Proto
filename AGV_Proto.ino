#include "paramconfig.h"
#include "emergencystop.h"

void setup() {
  Serial.begin(115200);
  paramconfig_setup();
  attachInterrupt(digitalPinToInterrupt(emergency_stop_pin), emergencystop_action, FALLING);
}

void loop() {
  
}
