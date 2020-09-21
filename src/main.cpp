#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "AS_V1_PINS.h"                     // !!! Include PINS file !!!
#include <MAX31341.h>
#include <Arduino-MAX17055_Driver.h>
#include <Adafruit_BME280.h>
#include <SPI.h>
#include <SD.h>


int SEALEVELPRESSURE_HPA = 1013;
int temp;
int pressure;
int humidity;
int altidute;
int SOC;
int hall = hallRead();
String command;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
MAX31341 rtc(true);
MAX17055 battery;
Adafruit_BME280 bme;

void ReadSerial()
{
  while(Serial.available() > 0)
    {
      char buffer = char(Serial.read());
      if(buffer == '$')
      {
        break;
      } 
      else 
      {
        command += buffer;
      }
    }
}

void ActualizeSensors(void * parameter){
  for(;;){ // infinite loop
    hall = hallRead();
    SOC = battery.getSOC();
    temp = bme.readTemperature();
    pressure = bme.readPressure();
    humidity = bme.readHumidity();
    altidute = bme.readAltitude(SEALEVELPRESSURE_HPA);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void ReadSerialTask(void * parameter){
  for(;;){ 
    
    command = "";
    ReadSerial();

    if (command == "A0")
    {
      command = "";
      ReadSerial();
      rtc.SetYear(atoi(command.c_str()));
      command = "";
      ReadSerial();
      rtc.SetMonth(atoi(command.c_str()));
      command = "";
      ReadSerial();
      rtc.SetDay(atoi(command.c_str()));
      command = "";
      ReadSerial();
      rtc.SetHour(atoi(command.c_str()));
      command = "";
      ReadSerial();
      rtc.SetMinutes(atoi(command.c_str()));
      command = "";
      ReadSerial();
      rtc.SetSeconds(atoi(command.c_str()));

    }

    if (command == "A1")
    {
      command = "";
      ReadSerial();
      SEALEVELPRESSURE_HPA = atoi(command.c_str());
      Serial.println("Sea LVL pressure: ");
      Serial.print(SEALEVELPRESSURE_HPA);
    }
    
  }
}

void setup() 
{
  battery.setCapacity(1000);
  SOC = battery.getSOC();
  temp = bme.readTemperature();
  pressure = bme.readPressure();
  humidity = bme.readHumidity();
  altidute = bme.readAltitude(SEALEVELPRESSURE_HPA);
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(3);
  Serial.begin(9600);
  tft.setSPISpeed(SPIspeed);

  xTaskCreate
  (
  ActualizeSensors,    // Function that should be called
  "ActualizeSensors",   // Name of the task (for debugging)
  1000,            // Stack size (bytes)
  NULL,            // Parameter to pass
  1,               // Task priority
  NULL             // Task handle
  );

}


void loop(void) 
{
  tft.fillRect(0, 0, 60, 17, ILI9341_BLACK);         //Hall
  tft.fillRect(70, 40, 180, 55, ILI9341_BLACK);      //Hour
  tft.fillRect(270, 0, 320, 17, ILI9341_BLACK);      //battery %
  tft.fillRect(230, 220, 320, 240, ILI9341_BLACK);   //Accel
  tft.fillRect(0, 130, 135, 230, ILI9341_BLACK);     //heigh & temp & pressure & humidity


  tft.setCursor(70, 45);      //Hour
  tft.setTextSize(6);
  tft.println("14:10"); 

  tft.setTextSize(2);         //Battery %
  tft.setCursor(270, 0);
  tft.println(SOC);

  tft.setTextSize(2);
  tft.setCursor(230, 225);    //Accel
  tft.print("16");
  tft.println("m/s^2");

  tft.setTextSize(2);         //Hall
  tft.setCursor(0, 0);
  tft.print(hall);
  tft.setTextSize(1);
  tft.println("*");

  tft.setTextSize(2);        //altidute
  tft.setCursor(0, 135); 
  tft.print(altidute);
  tft.println("m a.s.l");

  tft.setTextSize(2);        //Temp
  tft.setCursor(0, 165); 
  tft.print(temp);
  tft.setTextSize(1);
  tft.print("*");
  tft.setTextSize(2);
  tft.println("C");

  tft.setTextSize(2);        //Pressure
  tft.setCursor(0, 195); 
  tft.print(pressure);
  tft.println("hPa");

  tft.setTextSize(2);        //Humidity
  tft.setCursor(0, 225); 
  tft.print(humidity);
  tft.println("%");
  

  delay(300);
}