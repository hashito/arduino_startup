
#include <Arduino.h>
#include <Wire.h>
#include <TM1637Display.h>
#define SERIAL_BAUD 115200

#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);
#define KY_03x_LEN 10
int KY_03xs[KY_03x_LEN] = {0,0,0,0,0,0,0,0,0,0};
int KY_03xs_idx = 0;

void setup() {
  Serial.begin(SERIAL_BAUD);
  while(!Serial) {}

  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);
  display.setSegments(data);
  delay(1000);
}

void loop() {
  int ave = 0;
  int KY_03x;
  KY_03xs_idx++;
  if(! (KY_03x_LEN > KY_03xs_idx) )
    KY_03xs_idx = 0;
  KY_03xs[KY_03xs_idx] = analogRead(A0);
  for(int i=0 ; i<KY_03x_LEN;i++){
    ave+=KY_03xs[i];
  }
  KY_03x = ave/KY_03x_LEN;

  display.showNumberDec(KY_03x, false); 
  Serial.print("ky_03x: ");
  Serial.print(KY_03x);
  delay(100);
}