// wake up on a hardware interrupt from sleep
#include <GyverPower.h>

void setup() {
  Serial.begin(9600);

  // button connected to GND and D3
  pinMode(3, INPUT_PULLUP);

  // connect the interrupt on the pin  D3 (Arduino NANO)
  attachInterrupt(1, isr, FALLING);

  // deep sleep 
  power.setSleepMode(POWERDOWN_SLEEP);
}

// hardware interrupt handler
void isr() {
  // as opposed to  sleepDelay, you don't need to call anything!

void loop() {
  Serial.println("go sleep");
  delay(300);
  
  // it would be correct to enable the interrupt here
  // attachInterrupt(1, isr, FALLING);

  // спим ~8 секунд, но можем проснуться по кнопке
  power.sleep(SLEEP_8192MS);
  // then woke up, on the button or after a specified period  
  
  // but here immediately disable
  // detachInterrupt(1);

  Serial.println("wake up!");
  delay(300);
}
