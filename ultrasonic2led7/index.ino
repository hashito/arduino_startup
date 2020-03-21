
#include <Arduino.h>
#include <TM1637Display.h>
#include <Wire.h>

#define SERIAL_BAUD 115200
#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);
int Trig = 5;
int Echo = 4;

void setup() {
  Serial.begin(SERIAL_BAUD);
  while(!Serial) {}
   pinMode(Trig,OUTPUT);
   pinMode(Echo,INPUT);

  Wire.begin();
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);
  display.setSegments(data);
  delay(1000);
}

void loop() {
  int Duration;
  float Distance;
    digitalWrite(Trig,LOW);
    delayMicroseconds(1);
    digitalWrite(Trig,HIGH);
    delayMicroseconds(11);
    digitalWrite(Trig,LOW);
    Duration = pulseIn(Echo,HIGH);
    if (Duration>0) {
      Distance = Duration/2;
      Distance = Distance*340*100/1000000; // 340m/s = 34000cm/s = 0.034cm/us 
      Serial.print(Distance);
      Serial.println(" cm");
      display.showNumberDec((unsigned int)(Distance*100), false);
//      analogWrite(11, (unsigned int)(100-Distance));//ビープ音
    }
  delay(100);
}