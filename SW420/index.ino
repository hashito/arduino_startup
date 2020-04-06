
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
int cnt=0;
void loop() {
  int _do=digitalRead(4);
if(_do)cnt++;
  display.showNumberDec(cnt, false); 
  Serial.print("\nDO: ");
  Serial.print(_do);
  delay(1);
}