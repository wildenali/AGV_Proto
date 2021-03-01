#include "HID_RFID.h"

String inData;

void setup(){
  Serial.begin(115200);
  setupRFID_Data();
}

void loop(){
  Usb.Task();
  if (scanFinished == true)
  {
    Serial.println(scanResult);
    scanFinished = false;
  }
}
