
#include <Arduino.h>
#include <Wire.h>
#include <TM1637Display.h>
#define SERIAL_BAUD 115200

#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);
#define PIEZOELECTRIC_LEN 10
int Piezoelectrics[PIEZOELECTRIC_LEN] = {0,0,0,0,0,0,0,0,0,0};
int Piezoelectrics_idx = 0;

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
  int Piezoelectric;
  Piezoelectrics_idx++;
  if(! (PIEZOELECTRIC_LEN > Piezoelectrics_idx) )
    Piezoelectrics_idx = 0;
  Piezoelectrics[Piezoelectrics_idx] = analogRead(A0);
  for(int i=0 ; i<PIEZOELECTRIC_LEN;i++){
    ave+=Piezoelectrics[i];
  }
  Piezoelectric = ave/PIEZOELECTRIC_LEN;

  display.showNumberDec(Piezoelectric, false); 
  Serial.print("Piezoelectric: ");
  Serial.print(Piezoelectric);
  delay(100);
}