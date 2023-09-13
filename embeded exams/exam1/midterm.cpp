#include <Arduino.h>
//output 0-1V
// x > 0.5V represent the level of CO2, 0=no CO2
// rate: 1kHZ
// The  comment include the code using pointers instead of the known registers& timers&ADC
//
#define LED_PORT PORTB
#define LED_PIN 2
//Pointer to DDRB
unsigned char* ptrDDRB = (unsigned char*)0x37;
//Pointer to PORTB
unsigned char* ptrPORTB = (unsigned char*)0x38;
//TIMER
// I have to use a 8 bit timer to satisfy the requirments
unsigned char* ptrTCCR0A = (unsigned char*)0x50;
unsigned char* ptrTCCR0B = (unsigned char*)0x53;

// ADC 
unsigned char* ptrADMUX = (unsigned char*)0X27;
unsigned char* ptrADCSRA = (unsigned char*)0x26;
unsigned char* ptrADCSRB = (unsigned char*)0x23;
short MyADCCODE = 0;
short * ptrADCDATA = (short*)0x25; // the address of the ADCH
void SetupTimer(){
  //using timer0
  //*ptrTCCR0A = 0b00100010 using pointer
  TCCR0A = 0b00100010;
  //         00 -using it for TOP.
  //           10 - no PWM **
  //             00 - always 0 
  //               10 - nonpwm
  TCCR0B = 0b00000011;

  //*ptrTCCR0B = 0b00000011;
  //         00 - Dont Care
  //           00 - Dont Care
  //             0- Last bit of WGM is a 0 for no PWM generation
  //              011 - Set clock prescaler to 64 
  OCR0A = 125 ;

}
void SetupLED() {
  DDRB |= (1<<2); // using PB2 as output
  //*ptrDDRB |= (1<<2)

}
void SetupADC()  {
  /// put your setup code here, to run once:
  ADMUX=0b10000000;
  //*ptrADMUX = 0b10000000;
  //      10 - using 1.1 internal voltage since the output ranged from 0~1V
  //         0000000 - Use channel 0
  ADCSRA=0b10100100;
  //*ptrADCSRA=0b10100100;
  //       1 - Turn ON ADC 
  //        0 - Dont start yet     
  //         1 - Auto Trigger Enable
  //          00 - Interrupt stuff
  //            100 - 16 Clock prescaler
  ADCSRB = 0b00010100;
  // *ptrADCSRB = 0b00010100;
  //         0 - No high speed
  //          0 - DC
  //           0 - Other MUX bit
  //            1 - DC
  //             0100 -  overflow as an Auto Trigger Source for the ADC
  ADCSRA |= (1<<ADSC); 
  //Start up the conversion

  Serial.begin(9600);
}

void setup(){
  //call functions
 Serial.begin(9600);
SetupADC();
SetupLED();
SetupTimer();
}
void loop() {
  // put your main code here, to run repeatedly:

  // (1*1024)/1.1/2 =466 is when the voltage reaches 0.5 when the total voltage is 1V which is 50%
  // in order to aviod the LED flicker when the ADC hovers around 0.5V, i decided to make the limit higher
  // the led will light when the input data is greater than 466 which is about 490, and the LED will hold 100ms 
  // in order to avoid the filcker.
  // i do not want my code go over 1024/1.1 = 930 too
delay(1000);
MyADCCODE =* ptrADCDATA;
if (MyADCCODE > 490 && MyADCCODE < 930){
  PORTB |= (1<<2);
  delay(100);
}else{
  PORTB &= ~(1<<2);
  delay(100);
}


}