/*
Bluetooth UART Rx/Tx example with Wemos Lolin 32 + Oled display
Example derived from Examples->ESP32 BLE Arduino->BLE_uart
(c) Giovanni Bernardo
https://www.settorezero.com
    
Video: https://www.youtube.com/watch?v=oCMOYS71NIU
Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
Ported to Arduino ESP32 by Evandro Copercini

Create a BLE server that, once we receive a connection, will send periodic notifications.
The service advertises itself as: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
Has a characteristic of: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E - used for receiving data with "WRITE" 
Has a characteristic of: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E - used to send data with  "NOTIFY"

The design of creating the BLE server is:
1. Create a BLE Server
2. Create a BLE Service
3. Create a BLE Characteristic on the Service
4. Create a BLE Descriptor on the characteristic
5. Start the service.
6. Start advertising.
*/

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
#include "LoraPin.h"
#include "SSD1306Wire.h"
#include "images.h"
//SSD1306Wire display(0x3c, 21, 22);
SSD1306Wire  display(0x3c, OLED_SDA, OLED_SCL);
#define BUFFER_LENGTH 20
char rxBuffer[BUFFER_LENGTH];
bool newBuffer=false;

String n = "on";
String f = "off";

class MyServerCallbacks: public BLEServerCallbacks 
      {
        void onConnect(BLEServer* pServer) 
            {
              deviceConnected = true;
            };
        void onDisconnect(BLEServer* pServer) 
            {
              deviceConnected = false;
            }
      };
class MyCallbacks: public BLECharacteristicCallbacks 
      {
        void onWrite(BLECharacteristic *pCharacteristic) 
            {
              std::string rxValue = pCharacteristic->getValue();
              if (rxValue.length() > 0) 
                  {
                    // transfer data received into a buffer
                    for (int i = 0; i < rxValue.length(); i++)
                        {
                          rxBuffer[i]=rxValue[i];
                          // new line received or : end of string
                          if (rxValue[i]==10 || rxValue[i]==13 || i==BUFFER_LENGTH-1)
                              {
                                if (i!=0)
                                    {
                                      newBuffer=true;          
                                    }
                                rxBuffer[i]=0;
                              }
                        }
                  }
            }
      };
void LedOn()
    {
    digitalWrite(LED, HIGH);
    }
void LedOff()
    {
    digitalWrite(LED, LOW);
    }
void startupImage()
  {
  display.clear();
  display.drawString(30, 0, "SETIYO");
  display.drawXbm(48, 17, 32, 32, bluetooth32_bits);
  display.drawString(24, 54, "BLUETOOTH ON");
  display.display();
  }
void setup() 
  {
  Serial.begin(9600);  
  pinMode(LED,OUTPUT); // Green Led
  
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  // Create the BLE Device
  BLEDevice::init("LoRa_Setiyoo");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic
                    (
										  CHARACTERISTIC_UUID_TX,
										  BLECharacteristic::PROPERTY_NOTIFY
									  );
                      
  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic
                    (
										  CHARACTERISTIC_UUID_RX,
										  BLECharacteristic::PROPERTY_WRITE
										);

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();

  startupImage();
  } // \setup

void loop() 
  {
  // this flag is used only for writing connected-disconnected on display
  static bool writeConnection=false;
    
  if (deviceConnected) 
      {      
      // write connected on display and set a flag
      if (!writeConnection)
          {
            display.clear();
            display.drawString(0, 0, "CONNECTED!");
            display.display();
            writeConnection=true;
          }
      // data received?
      if (newBuffer)
          {
            LedOn();
            // write received string on display
            display.clear();
            display.drawString(0, 0, "Ku Terima Perintahmu:");
            display.drawString(0, 30, String(rxBuffer));
            display.display();
            Serial.println(rxBuffer);
            
            if(String(rxBuffer)== n){
                Serial.print("n");
                }
                delay(20);
            if(String(rxBuffer)== f){
                Serial.print("f");
                }  
                delay(20);
            // write back "ok" (+CR+LF) on Bluetooth UART
            uint8_t ok[4]={'O','k',13,10};
            pTxCharacteristic->setValue(ok, 4);
            pTxCharacteristic->notify();

            // reset received command flag and buffer
            newBuffer=false;
            rxBuffer[0]=0;
          }
          delay(500);
  LedOff();
  delay(1000);
	    } // \connected
     else
      {
      // write disconnected on display if there was a previous connection
      if (writeConnection)
        {
        display.clear();
        display.drawString(0, 0, "DISCONNECTED!");
        display.display();
        delay(1000);
        startupImage();
        writeConnection=false;
        }  
      }
      
    
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) 
      {
      delay(500); // give the bluetooth stack the chance to get things ready
      pServer->startAdvertising(); // restart advertising
      oldDeviceConnected = deviceConnected;
      } // \disconnecting
    
    // connecting
    if (deviceConnected && !oldDeviceConnected) 
      {
		  // do stuff here on connecting
      oldDeviceConnected = deviceConnected;
      } // \connecting
      
} // \loop
