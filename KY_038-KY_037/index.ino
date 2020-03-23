
#include <Arduino.h>
#include <Wire.h>
#include <TM1637Display.h>
#define SERIAL_BAUD 115200

#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(SERIAL_BAUD);
  while(!Serial) {}

  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);
  display.setSegments(data);
  delay(1000);
}

void loop() {
    int ky_03x=analogRead(A0);
    display.showNumberDec(ky_03x, false); 
    Serial.print("ky_03x: ");
    Serial.print(ky_03x);
    delay(100);
}