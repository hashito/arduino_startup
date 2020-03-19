void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, INPUT);
}

void loop() {
  int pin4=digitalRead(4);
  digitalWrite(2, pin4); 
}