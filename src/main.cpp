#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_AS7341.h>
#include <U8g2lib.h>


Adafruit_AS7341 as7341;
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


uint16_t readings[12]; //AS7341 data array



void setup() {

u8g2.begin();
u8g2.setFont(u8g2_font_6x12_tr);

delay(2000); // Pause for 2 seconds



  if (!as7341.begin()){
    //OLED output "Initing ....."
    while (1) { delay(10); }
  }

  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_256X);

}


void loop() {
  // put your main code here, to run repeatedly:
    if (!as7341.readAllChannels()){
    Serial.println("Error reading all channels!");
    return;
  }
u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0,24,"Hello World!");
  } while ( u8g2.nextPage() );

}