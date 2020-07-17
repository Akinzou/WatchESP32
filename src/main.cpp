#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>


#define TFT_DC 4
#define TFT_CS 15
#define TFT_RST 27
int hall = hallRead();


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void ActualizeSensors(void * parameter){
  for(;;){ // infinite loop
    hall = hallRead();
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() 
{
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(3);
  Serial.begin(9600);

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
  tft.fillRect(0, 0, 60, 17, ILI9341_BLUE);
  tft.fillRect(70, 90, 180, 55, ILI9341_BLUE);
  tft.fillRect(270, 0, 320, 17, ILI9341_BLUE);
  tft.setCursor(70, 95);
  tft.setTextSize(6);
  tft.println("14:10"); 
  tft.setTextSize(2);
  tft.setCursor(270, 0);
  tft.println("100%");
  tft.setCursor(0, 0);
  tft.print(hall);
  tft.setTextSize(1);
  tft.println("*");
  delay(500);
}

