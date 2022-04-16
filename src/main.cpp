#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>


//#include <oled.h>
#include "DFRobot_AS7341.h" // I2C address 0x39

#include <U8g2lib.h>


//#include "avr8-stub.h"
//#include "app_api.h"   // only needed with flash breakpoints

#include "OneButton.h"

#include "Enerlib.h"


DFRobot_AS7341 as7341;

//OLED display(A4,A5,NO_RESET_PIN,OLED::W_128,OLED::H_64,OLED::CTRL_SH1106,0x3C); 
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);



//OLED::OLED(uint8_t sda_pin, uint8_t scl_pin, uint8_t reset_pin, 
//tWidth width, tHeight height, tDisplayCtrl displayCtrl,
// uint8_t i2c_address)
uint16_t readings[12]; //AS7341 data array
float counts[12];
  DFRobot_AS7341::sModeOneData_t data1;
  DFRobot_AS7341::sModeTwoData_t data2;

void as7341_read(); 
void show_data();
void show_open();



void setup() {

//Serial.begin(115200);

  u8g2.begin();


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
    
        u8g2.setFont(u8g2_font_6x12_tr);  
        u8g2.setFontDirection(0);
        u8g2.firstPage();
        do {
            u8g2.setCursor(0, 12);
            u8g2.print("Ready for measureing ");
        } while ( u8g2.nextPage() );

    delay(2000);
  
}


void loop() {

    as7341_read(); 
    show_data();

}


void  as7341_read(){

  //Start spectrum measurement 
  //Channel mapping mode: 1.eF1F4ClearNIR,2.eF5F8ClearNIR
  as7341.startMeasure(as7341.eF1F4ClearNIR);
  //Read the value of sensor data channel 0~5, under eF1F4ClearNIR
  data1 = as7341.readSpectralDataOne();
  /*
  Serial.print("F1(405-425nm):");
  Serial.println(data1.ADF1);
  Serial.print("F2(435-455nm):");
  Serial.println(data1.ADF2);
  Serial.print("F3(470-490nm):");
  Serial.println(data1.ADF3);
  Serial.print("F4(505-525nm):");   
  Serial.println(data1.ADF4);
  //Serial.print("Clear:");
  //Serial.println(data1.ADCLEAR);
  //Serial.print("NIR:");
  //Serial.println(data1.ADNIR);
  */
  as7341.startMeasure(as7341.eF5F8ClearNIR);
  //Read the value of sensor data channel 0~5, under eF5F8ClearNIR
  data2 = as7341.readSpectralDataTwo();
  /*
  Serial.print("F5(545-565nm):");
  Serial.println(data2.ADF5);
  Serial.print("F6(580-600nm):");
  Serial.println(data2.ADF6);
  Serial.print("F7(620-640nm):");
  Serial.println(data2.ADF7);
  Serial.print("F8(670-690nm):");
  Serial.println(data2.ADF8);
  Serial.print("Clear:");
  Serial.println(data2.ADCLEAR);
  Serial.print("NIR:");
  Serial.println(data2.ADNIR);
  */
  delay(1000);
  
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
