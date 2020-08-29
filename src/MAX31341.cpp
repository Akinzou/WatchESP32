#include "MAX31341.h"
#include <Arduino.h>
#include <Wire.h>

uint8_t DeviceAdress;
String requestBit; 


MAX31341::MAX31341(bool AD0 = true) 
{
    if (AD0) 
    {
        DeviceAdress = 0xD2;
    } 

    else 
    {
        DeviceAdress = 0xD4;
    }
    Wire.begin(DeviceAdress);
}

String MAX31341::GetSeconds()
{
    Wire.requestFrom(Seconds, 7);
    while(Wire.available()) 
        {
            char requestByte = Wire.read();   
            requestBit += requestByte;        
        }
    return requestBit;
}

void MAX31341::SetSeconds(int sec)
{
    Wire.beginTransmission(DeviceAdress);
    Wire.write(Seconds);
    Wire.write(sec);
    Wire.endTransmission();
}