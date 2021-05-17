#include "_parameter/GlobalVariable.h"
#include "emergency_stop/EmergencyStop.h"

void setup() {
  Serial.begin(115200);
  emergency_stop_setup();
}

void loop() {
  
}
