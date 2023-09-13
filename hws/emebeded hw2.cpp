#include <Arduino.h>
// using timer1 to output 
// input A = B3 - use for top // 
// output B = PB6  (OC1B)
#define Max_limit 100;

void setup() {
  // put your setup code here, to run once:

  // set PB6 as an output 
  DDRB |= (1<<6);
  TCCR1A = 0b00100011;
  //         00 disconnect 0CA,using it for TOP 
  //          10 channle B register (non inverting) PWM - > 如果变成 11 的话就变成了inverting pwm 
  //           00 - not used 
  //             11 
  TCCR1B = 0b00001011;
  //         00 don't care 
  //          00  don't care 
  //            1 - last bit of wgm is a 1 
  //             011 - set closck prescaler to 64

  TCCR1C = 0b00001010;
  OCR1A = 128; //count tp to 128 
  OCR1B = 64; // 50% duty cycle 
}

unsigned char DC =0;
unsigned char Count_Up = 0;

void loop() {
  // put your main code here, to run repeatedly:
    Count_Up = 1.28* Max_limit;
  if (DC == Count_Up){
    DC = 0;
  }
  DC += 1.28;
  OCR1B = DC;
  delay (10); 
}