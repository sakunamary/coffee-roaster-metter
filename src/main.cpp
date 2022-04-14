#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_AS7341.h>

#include <oled.h>

#include "avr8-stub.h"
#include "app_api.h"   // only needed with flash breakpoints


Adafruit_AS7341 as7341; // I2C address 0x39

OLED display(A4,A5,NO_RESET_PIN,OLED::W_128,OLED::H_64,OLED::CTRL_SH1106,0x3c); 

//OLED::OLED(uint8_t sda_pin, uint8_t scl_pin, uint8_t reset_pin, 
//tWidth width, tHeight height, tDisplayCtrl displayCtrl,
// uint8_t i2c_address)
uint16_t readings[12]; //AS7341 data array
float counts[12];


void as7341_read(); 
void show_data();
void show_open();



void setup() {
 //delay(1000);


     debug_init();
    display.begin();   
    display.useOffset(true);//for sh1106 

    display.clear();
    display.setCursor(0,0);
    display.print("AS7341 Initing...");
    display.display();


    as7341.begin();

  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_256X);
  as7341.startReading();


    display.clear();
    display.setCursor(0,0);
    display.print("AS7341 OK");
    display.setCursor(0,20);
    display.print("Ready for measure");
    display.display();
     

}


void loop() {
  // put your main code here, to run repeatedly:
    as7341_read();
    delay(500);
    display.clear();
    display.setCursor(2,40);
    display.print(String(counts[2]));
    display.display();
}


void  as7341_read(){

  //as7341.setLEDCurrent(100); // 100mA
  //as7341.enableLED(true);
 // delay(1000);
if (!as7341.readAllChannels()){
   for(uint8_t i = 0; i < 12; i++) {
    if(i == 4 || i == 5) continue;
    // we skip the first set of duplicate clear/NIR readings
    // (indices 4 and 5)
    counts[i] = as7341.toBasicCounts(readings[i]);
  }
  }
  delay(1000);
  //as7341.enableLED(false);
  
}


void show_data(){

}
