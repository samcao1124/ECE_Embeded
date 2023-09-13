#include <Arduino.h>
#include <Adafruit_CircuitPlayground.h>
//ADC
//used to read analog readings from the sensor circuit
//use ADC 9
void ADCSETUP() 
{
  ADMUX = 0b01000001;
  //01 use vcc as reverence
  //  0 right justify
  //   00000 use channel 01
  ADCSRA = 0b10100100;
  //1 turn adc on
  // 0 dont start yet
  //  1 auto trigger enable
  //   00 interupt stuff
  //     100 16 clock prescaler
  ADCSRB = 0b00100000;
  //0 no high speed
  // 0 dont care
  //  0 other mux bit
  //   0 dont care
  //    0000 free running
  ADCSRA |= (1<<ADSC); 
}


// setup function
//ADC setup
//GPIO setup
//on board NEO pixl & Speaker setup
void setup() {
  ADCSETUP();
  Serial.begin(9600);
  DDRD |= (1<<1);
  PORTD &= ~(1<<1);
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();   
}


//main function variables
 short myadc = 0;
 short * ptradcdata = (short*)0x78;
 double temp = 0;
 int count = 0;
 int speakerLEDstate = 0;


//loop function
//main functions of the device
void loop() {
  //serial print the varable names
  delay(1000);
  myadc = * ptradcdata;
  Serial.print("myadc is=");
  Serial.print("Variable_1:");

  //signal processing algarithom
  //take the absolute value of discrete derivative 
  double change = myadc - temp;
  temp = myadc;
  double absv = abs(change);

  //find if the "non-breathing time is over 10 seconds"
  if (absv < 25)
  {
    count++;
  }
  else
  {
    count = 0;
    PORTD &= ~(1<<1);
  }

  //neo-pixel level and color according to processed ADC value while safe: breathing properly
  if (absv < 25)
  {
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(4, 255, 0, 0);
  }
  else if ( (absv >= 25)&&(absv < 50))
  {
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(4, 0, 255, 0);
    CircuitPlayground.setPixelColor(3, 0, 255, 0);
    CircuitPlayground.setPixelColor(2, 0, 255, 0);
  }
  else if ((absv >= 50)&&(absv < 100))
  {
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(4, 0, 255, 0);
    CircuitPlayground.setPixelColor(3, 0, 255, 0);
    CircuitPlayground.setPixelColor(2, 0, 255, 0);
    CircuitPlayground.setPixelColor(1, 0, 255, 0);
    CircuitPlayground.setPixelColor(0, 0, 255, 0);
    CircuitPlayground.setPixelColor(9, 0, 255, 0);
  }
  else if ((absv >= 100)&&(absv < 150))
  {
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(4, 0, 255, 0);
    CircuitPlayground.setPixelColor(3, 0, 255, 0);
    CircuitPlayground.setPixelColor(2, 0, 255, 0);
    CircuitPlayground.setPixelColor(1, 0, 255, 0);
    CircuitPlayground.setPixelColor(0, 0, 255, 0);
    CircuitPlayground.setPixelColor(9, 0, 255, 0);
    CircuitPlayground.setPixelColor(8, 0, 255, 0);
    CircuitPlayground.setPixelColor(7, 0, 255, 0);
  }
  else
  {
    CircuitPlayground.clearPixels();
    CircuitPlayground.setPixelColor(4, 0, 255, 0);
    CircuitPlayground.setPixelColor(3, 0, 255, 0);
    CircuitPlayground.setPixelColor(2, 0, 255, 0);
    CircuitPlayground.setPixelColor(1, 0, 255, 0);
    CircuitPlayground.setPixelColor(0, 0, 255, 0);
    CircuitPlayground.setPixelColor(9, 0, 255, 0);
    CircuitPlayground.setPixelColor(8, 0, 255, 0);
    CircuitPlayground.setPixelColor(7, 0, 255, 0);
    CircuitPlayground.setPixelColor(6, 0, 255, 0);
    CircuitPlayground.setPixelColor(5, 0, 255, 0);
  }
  
  //speaker alarm & RED light on neo pixels while non-breathing for 10 seconds
  if (count > 10)
  {
    PORTD |= (1<<1);
    if (speakerLEDstate == 0)
    {
      CircuitPlayground.clearPixels();
      CircuitPlayground.playTone(880,100);
      CircuitPlayground.setPixelColor(0, 255,   0,   0);
      CircuitPlayground.setPixelColor(1, 255,   0,   0);
      CircuitPlayground.setPixelColor(2, 255,   0,   0);
      CircuitPlayground.setPixelColor(3, 255,   0,   0);
      CircuitPlayground.setPixelColor(4, 255,   0,   0);
      CircuitPlayground.setPixelColor(5, 255,   0,   0);
      CircuitPlayground.setPixelColor(6, 255,   0,   0);
      CircuitPlayground.setPixelColor(7, 255,   0,   0);
      CircuitPlayground.setPixelColor(8, 255,   0,   0);
      CircuitPlayground.setPixelColor(9, 255,   0,   0);
      speakerLEDstate++;
    }
    else
    {
      CircuitPlayground.clearPixels();
      CircuitPlayground.playTone(440,100);
      CircuitPlayground.clearPixels();
      speakerLEDstate = 0;
    }
  }
  
  //print the final signal value
  Serial.println(absv);
}