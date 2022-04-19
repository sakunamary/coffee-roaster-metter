#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>


//#include <oled.h>
#include "DFRobot_AS7341.h" // I2C address 0x39

#include <U8g2lib.h>


//#include "avr8-stub.h"
//#include "app_api.h"   // only needed with flash breakpoints
#include "OneButton.h"
//arduino sleep and wakeup lib;
#include "LowPower.h"



//setupt OLED;
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Setup a new OneButton on pin A1.  
  OneButton button(2,true);

//setup AS7341 
  DFRobot_AS7341::sModeOneData_t data1;
  DFRobot_AS7341::sModeTwoData_t data2;

DFRobot_AS7341 as7341;



//Energy energy;
// Use pin 2 as wake up pin
const int wakeUpPin = 2;
uint16_t readings[12]; //AS7341 data array
float counts[12];
//funcitons declear for platformIO;

void as7341_read(); //read out the data from as7431
void show_data();
void show_init();
void doubleclick(); //as7341reding data
void singleclick(); //power on  
void wakeUp();


void setup() {

//debug_init();

  pinMode(wakeUpPin, INPUT);   
  pinMode(13, OUTPUT); 

  u8g2.begin();
  button.attachDoubleClick(doubleclick);

  while (as7341.begin() != 0) {
        u8g2.setFont(u8g2_font_6x12_tr);  
        u8g2.setFontDirection(0);
        u8g2.firstPage();
        do {
            u8g2.setCursor(0, 12);
            u8g2.print("AS7431 Initing ...");
        } while ( u8g2.nextPage() );
    delay(1000);
  }
       show_init();
}


void loop() {
    // Allow wake up pin to trigger interrupt on low.
    attachInterrupt(0, wakeUp, CHANGE);
    
    // Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
    
    // Disable external pin interrupt on wake up pin.
    detachInterrupt(0); 
    
    // Do something here
    // Example: Read sensor, data logging, data transmission.

  button.tick();
  delay(10);
  
}


void  as7341_read(){
// light up 
  as7341.controlLed(100);
  as7341.enableLed(true);
  delay(300);
  //Start spectrum measurement 
  //Channel mapping mode: 1.eF1F4ClearNIR,2.eF5F8ClearNIR
  as7341.startMeasure(as7341.eF1F4ClearNIR);
  //Read the value of sensor data channel 0~5, under eF1F4ClearNIR
  data1 = as7341.readSpectralDataOne();
  as7341.startMeasure(as7341.eF5F8ClearNIR);
  //Read the value of sensor data channel 0~5, under eF5F8ClearNIR
  data2 = as7341.readSpectralDataTwo();
  delay(300);
  as7341.enableLed(false);
  
}

void show_data(){

  u8g2.setFont(u8g2_font_6x12_tr);  
  u8g2.setFontDirection(0);
  u8g2.firstPage();
  do {
    u8g2.drawRFrame(0,0,128,64,0); 
    u8g2.drawLine(64,0,64,64);

    u8g2.setCursor(2, 12);
    u8g2.print("F1:");
    u8g2.setCursor(22, 12);
    u8g2.print(data1.ADF1);

    u8g2.setCursor(2, 24);
    u8g2.print("F2:");
    u8g2.setCursor(22, 24);
    u8g2.print(data1.ADF2);

    u8g2.setCursor(2, 36);
    u8g2.print("F3:");
    u8g2.setCursor(22,36);
    u8g2.print(data1.ADF3);

    u8g2.setCursor(2, 48);
    u8g2.print("F4:");
    u8g2.setCursor(22,48);
    u8g2.print(data1.ADF4);

     
    u8g2.setCursor(2, 60);
    u8g2.print("CLR:");
    u8g2.setCursor(26,60);
    u8g2.print(data2.ADCLEAR);

    u8g2.setCursor(66, 12);
    u8g2.print("F5:");
    u8g2.setCursor(86, 12);
    u8g2.print(data2.ADF5);

    u8g2.setCursor(66, 24);
    u8g2.print("F6:");
    u8g2.setCursor(86, 24);
    u8g2.print(data2.ADF6);

    u8g2.setCursor(66, 36);
    u8g2.print("F7:");
    u8g2.setCursor(86,36);
    u8g2.print(data2.ADF7);

    u8g2.setCursor(66, 48);
    u8g2.print("F8:");
    u8g2.setCursor(86,48);
    u8g2.print(data2.ADF8);
    
    u8g2.setCursor(66, 60);
    u8g2.print("NIR:");
    u8g2.setCursor(90,60);
    u8g2.print(data2.ADNIR);

  } while ( u8g2.nextPage() );
  delay(1000);
}

void show_init(){
 u8g2.setFont(u8g2_font_6x12_tr);  
        u8g2.setFontDirection(0);
        u8g2.firstPage();
        do {
            u8g2.setCursor(0, 12);
            u8g2.print("Ready for measureing ");

        } while ( u8g2.nextPage() );
}

void doubleclick() {
  static int m = LOW;
  // reverse the LED 
  m = !m;
  digitalWrite(13, m);

  as7341_read();
  show_data();
} // doubleclick


void wakeUp()
{
    
    doubleclick();
}