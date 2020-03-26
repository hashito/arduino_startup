
#include <Arduino.h>
#include <Wire.h>
#include <TM1637Display.h>
#define SERIAL_BAUD 115200

#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);
#define IR_LEN 10
int IRs[IR_LEN] = {0,0,0,0,0,0,0,0,0,0};
int IRs_idx = 0;

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
  int IR;
  IRs_idx++;
  if(! (IR_LEN > IRs_idx) )
    IRs_idx = 0;
  IRs[IRs_idx] = analogRead(A0);
  for(int i=0 ; i<IR_LEN;i++){
    ave+=IRs[i];
  }
  IR = ave/IR_LEN;

  display.showNumberDec(IR, false); 
  Serial.print("IR: ");
  Serial.print(IR);
  delay(100);
}