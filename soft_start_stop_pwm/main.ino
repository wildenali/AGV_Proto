#include "CountDown.h"

CountDown start_CD(CountDown::MILLIS);

int softPWM;
int flag;

void setup()
{
    Serial.begin(115200);
    pinMode(2, INPUT_PULLUP);
    pinMode(13, OUTPUT);
    
    start_CD.start(0);
    softPWM = 0;
    flag = 0;
}

void loop()
{
    if (digitalRead(2) == LOW)
    {
        delay(1000);
        start_CD.start(5000);
        flag++;
        if (flag > 2)
        {
            flag = 1;
        }
    }

    if (flag == 1)
    {
        softPWM = map(start_CD.remaining(), 5000, 0, 0, 255);
    }
    else if (flag == 2)
    {
        softPWM = map(start_CD.remaining(), 5000, 0, 255, 0);
    }
    
    Serial.println(softPWM);
    analogWrite(13, softPWM);    
}