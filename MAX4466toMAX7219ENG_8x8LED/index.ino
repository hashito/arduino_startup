/*
fft_adc.pde
guest openmusiclabs.com 8.18.12
example sketch for testing the fft library.
it takes in data on ADC0 (Analog0) and processes them
with the fft. the data is sent out over the serial
port at 115.2kb.  there is a pure data patch for
visualizing the data.
*/

#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft

#include <FFT.h> // include the library
#include <MatrizLed.h>
MatrizLed pantalla;

void setup() {
//  Serial.begin(115200); // use the serial port
    Serial.begin(2000000); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0

  pantalla.begin(12, 11, 10, 2); // dataPin, clkPin, csPin, numero de matrices de 8x8
}
char strbuf[64];
void loop() {
  while(1) { // reduces jitter
    cli();  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      fft_input[i] = k; // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0
    }
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    sei();
#if 0
    Serial.write(255); // send a start byte
    Serial.write(fft_log_out, 128); // send out the data
#endif
    int _sum = 0;
    for(int i=0;i<128;i++){
          _sum+=fft_log_out[i];
    }
    int ave = _sum/128/3;
    int cnt=0;
    for(int x=0;x<8;x++){
      for(int y=0;y<8;y++){
        if(ave > cnt){
           pantalla.setLed(0, x, y, true);
        }else{
           pantalla.setLed(0, x, y, false);
        }
        cnt++;
      }
    }
    
    memset(strbuf,0,64);
    memset(strbuf,'|',_sum/128/3);
    Serial.print(strbuf);
    Serial.print("\n");
    delayMicroseconds(1);
  }
}