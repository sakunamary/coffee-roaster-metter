#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_AS7341.h>
#include <U8g2lib.h>


Adafruit_AS7341 as7341; // I2C address 0x39
//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R3, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 5, /* data=*/ 4); 
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


uint16_t readings[12]; //AS7341 data array
float counts[12];


void as7341_read(); 
void show_data();
void show_open();



void setup() {

u8g2.begin(); 
u8g2.setFont(u8g2_font_6x10_tr);
u8g2.firstPage();
    do{
        delay(500); 
        u8g2.drawStr(0,24,"AS7341 Initing...");
        }while( u8g2.nextPage());

delay(2000);


  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_256X);
  as7341.startReading();
}


void loop() {
  // put your main code here, to run repeatedly:
  as7341_read();
/*
u8g2.firstPage();
u8g2.setFont(u8g2_font_6x10_tr);
  do {
  show_data();
  } while ( u8g2.nextPage() );
 delay(1000);
*/
 u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0,24,"Hello World!");
  } while ( u8g2.nextPage() );
}


void  as7341_read(){

  //as7341.setLEDCurrent(100); // 100mA
  //as7341.enableLED(true);
  delay(1000);
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
    u8g2.setCursor(0,32);
    u8g2.print("String test");
    //u8g2.print(String(counts[1],2));
}
