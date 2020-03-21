
#include <Arduino.h>
#include <BME280I2C.h>
#include <Wire.h>
#include <TM1637Display.h>
#define SERIAL_BAUD 115200

BME280I2C::Settings settings(
   BME280::OSR_X1,
   BME280::OSR_X1,
   BME280::OSR_X1,
   BME280::Mode_Forced,
   BME280::StandbyTime_1000ms,
   BME280::Filter_Off,
   BME280::SpiEnable_False,
   0x76
);
BME280I2C bme(settings);

#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(SERIAL_BAUD);
  while(!Serial) {}

  Wire.begin();
  while(!bme.begin()){
    Serial.println("not find BME280");
    delay(1000);
  }
  settings.tempOSR = BME280::OSR_X4;
  bme.setSettings(settings);

  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);
  display.setSegments(data);
  delay(1000);
}

void loop() {
   float temp(NAN), hum(NAN), pres(NAN);
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);

   bme.read(pres, temp, hum, tempUnit, presUnit);
//   display.showNumberDec((unsigned int)(temp*100), false); //温度
   display.showNumberDec((unsigned int)(hum*100), false); // 気圧
   Serial.print("Temp: ");
   Serial.print(temp);
   Serial.print("°"+ String(tempUnit == BME280::TempUnit_Celsius ? 'C' :'F'));
   Serial.print("\t\tHumidity: ");
   Serial.print(hum);
   Serial.print("% RH");
   Serial.print("\t\tPressure: ");
   Serial.print(pres);
   Serial.println(" Pa");
   delay(100);
}