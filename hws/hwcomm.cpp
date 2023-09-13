//Talking to on board Accelerometer LIS3DH
//SPI, CS D8, PB4
//PULL CS low to select SPI interface, not i2c
#include <Arduino.h>
#include "SPI.h"
#define CS 8
#define STATUS_REG 0x27
volatile bool new_rx = false;
volatile uint8_t last_rx_byte = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  UCSR1A = 0b00100000;
  UCSR1B = 0b10110000;
  UCSR1C = 0b00000110;
  UBRR1 = 25;


}

void loop() {
  //Read a register at address 0x27
 digitalWrite(8,LOW);
  SPI.transfer(0x0F | (1<<7));
  uint8_t data = SPI.transfer(0xFF);
  digitalWrite(8,HIGH);
  delay(1000);
  // put your main code here, to run repeatedly:
  static bool button_pressed = false;
// check RX interrupt flag
if (new_rx) {
  new_rx = false;
  switch (GetNextReceivedByte())
{
  case '1':
  TransmitString("One\n", 4);
  break ;
  case '2':
  TransmitString("Two\n", 4);
  break ;
  default :
  TransmitString("Default\n", 8);
  break ;
}
}
}


