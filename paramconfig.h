const int emergency_stop_pin = 45;
const int start_stop_pin = 44;
const int selector_pin = 43;
const int low_batt_indicator_pin = 42;

void paramconfig_setup(){
  pinMode(start_stop_pin, INPUT_PULLUP);
  pinMode(selector_pin, INPUT_PULLUP);
  pinMode(low_batt_indicator_pin, INPUT_PULLUP);

  Serial.println("Param Setup ..... Done");
  delay(500);
}
