// демо возможностей библиотеки
#include <GyverPower.h>

void setup() {
  pinMode(13, OUTPUT); // настраиваем вывод со светодиодом на выход
  Serial.begin(9600);

  power.autoCalibrate(); // automatic calibration 

  // disable unnecessary peripherals
  power.hardwareDisable(PWR_ADC | PWR_TIMER1); // see the constant section in GyverPower.h separating the " | "

  // system frequency control
  power.setSystemPrescaler(PRESCALER_2); // see constants in GyverPower.h

  // adjust sleep settings
  power.setSleepMode(STANDBY_SLEEP); // if you need a different sleep mode, see constants in GyverPower.h (default POWERDOWN_SLEEP)
  //power.bodInSleep(false); // it is recommended to turn off bod in a dream to conserve energy (default false - already off!!)

  // пример однократного ухода в сон
  Serial.println("go to sleep");
  delay(100); // даем время на отправку
  
  power.sleep(SLEEP_2048MS); // спим ~ 2 секунды
  
  Serial.println("wake up!");
  delay(100); // даем время на отправку
}

void loop() {
  // пример циклического сна
  power.sleepDelay(1500);               // спим 1.5 секунды
  digitalWrite(13, !digitalRead(13));   // инвертируем состояние на пине
}