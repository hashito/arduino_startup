
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
  pinMode(4,INPUT);
}

void loop() {
  int _ao = analogRead(A0);
  int _do=digitalRead(4);

  display.showNumberDec(_ao, false); 
  Serial.print("\nDO: ");
  Serial.print(_do);
  Serial.print(" AO: ");
  Serial.print(_ao);
  delay(1);
}