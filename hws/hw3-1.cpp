//This is an app to demonstarte GPIO
//We will control the onboard LEDA #10 PB6
//We will control the onboard LEDB #12 PD6
//We will control the onboard LEDC #6 PD7
//We will control the onboard LEDD #9 PB5
//We will control the onboard LEDE #2 PD1
//We will control the onboard LEDF #3 PD0
//We will control the onboard LEDG #0 PD2
#include <Arduino.h>
#define LED_PORT PORTC

void setup() {
  
  // put your setup code here, to run once:
  //Set PC7 to an output
  //*ptrDDRC |= 0b1000000;
  //*ptrDDRC |= 0x80;
  //*ptrDDRC |= (1<<7);
  DDRD |= (1<<7) | (1<<0) |(1<<6) | (1<<1)|(1<<2) ;
  DDRB |= (1<<5) | (1<<6);
  PORTB &= ~(1<<7)&~(1<<0)&~(1<<6)&~(1<<1)&~(1<<2);
  PORTD &= ~(1<<5) & ~(1<<6);
  Serial.begin(9600);
}
char state_input = 0;
void loop() {
  // put your main code here, to run repeatedly:
  // state = 0 AFBECD
  // turn on pb6 pd6 pd7 pb5 pd1 pd0 
  if (state_input == 0)
  {
  PORTD |= (1<<7) | (1<<0) |(1<<6) | (1<<1) ;
  PORTB |= (1<<5) | (1<<6);
  delay(1000);
  PORTB &= ~(1<<7)&~(1<<0)&~(1<<6)&~(1<<1)&~(1<<2);
  PORTD &= ~(1<<5) & ~(1<<6);
  Serial.println("output is 0");
  }
    //state = 1 BC
  else if (state_input == 1)
  {  PORTD |= (1<<7)|(1<<6) ;
  delay(1000);
  PORTB &= ~(1<<7)&~(1<<0)&~(1<<6)&~(1<<1)&~(1<<2);
  PORTD &= ~(1<<5) & ~(1<<6);
  Serial.println("output is 1");}
  // state = 2 ABGED
   else if (state_input == 2)
  {PORTD |= (1<<2) |(1<<6) | (1<<1) ;
  PORTB |= (1<<5) | (1<<6);
  delay(1000);
  PORTB &= ~(1<<7)&~(1<<0)&~(1<<6)&~(1<<1)&~(1<<2);
  PORTD &= ~(1<<5) & ~(1<<6);
  Serial.println("output is 2");}
  // STATE = 3 ABCDG.
    else if (state_input == 2)
  {PORTD |= (1<<7) |(1<<6) | (1<<2) ;
  PORTB |= (1<<5) | (1<<6);
  delay(1000);
  PORTB &= ~(1<<7)&~(1<<0)&~(1<<6)&~(1<<1)&~(1<<2);
  PORTD &= ~(1<<5) & ~(1<<6);
  Serial.println("output is 3");}
  // 4: FGBC.
    else if (state_input == 2)
  {PORTD |= (1<<2) |(1<<6) | (1<<0)|(1<<7)  ;
  delay(1000);
  PORTB &= ~(1<<7)&~(1<<0)&~(1<<6)&~(1<<1)&~(1<<2);
  PORTD &= ~(1<<5) & ~(1<<6);
  Serial.println("output is 4");}
  // 5:AFGCD.
    else if (state_input == 2)
  {PORTD |= (1<<2) |(1<<0) |(1<<7)  ;
  PORTB |= (1<<5) | (1<<6);
  delay(1000);
  PORTB &= ~(1<<7)&~(1<<0)&~(1<<6)&~(1<<1)&~(1<<2);
  PORTD &= ~(1<<5) & ~(1<<6);
  Serial.println("output is 5");}
  // 6:ACDefg.
    else if (state_input == 2)
  {PORTD |= (1<<2) |(1<<0) | (1<<1) |(1<<7) ;
  PORTB |= (1<<5) | (1<<6);
  delay(1000);
  PORTB &= ~(1<<7)&~(1<<0)&~(1<<6)&~(1<<1)&~(1<<2);
  PORTD &= ~(1<<5) & ~(1<<6);
  Serial.println("output is 6");}
  //7 : ABC .
    else if (state_input == 2)
  {PORTD |= (1<<6) | (1<<1) ;
  PORTB |=  (1<<6);
  delay(1000);
  PORTB &= ~(1<<7)&~(1<<0)&~(1<<6)&~(1<<1)&~(1<<2);
  PORTD &= ~(1<<5) & ~(1<<6);
  Serial.println("output is 7");}

}
