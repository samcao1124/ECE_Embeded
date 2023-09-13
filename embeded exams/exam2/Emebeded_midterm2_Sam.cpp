#include <Arduino.h>
#include <Wire.h>

// AD5933 has a default serial bus address --> 0x0D ---> page 27
// address pointer --> 0b10110000 --> The master sends a pointer command code
// The temperature data are stored in register located in 0x92 and 0x93 --> page 23

void setup() {
  // put your setup code here, to run once:
  // 4. a. Write the TWCR register to enable the I2C bus and enable the I2C interrupt. 
  //(See 32U4 datasheet for TWCR details)
  TWCR |= 0b00000101;
  //             1  --> bit2;enables the I2C bus 
  //               1 --> bit0; enables the I2C interrupts; 

  //-----------------------------------------------------------------------------
  //4. b. Configure the onboard LED (Red) as an output to control the LED. 
  //Do this by setting the correct DDR register.
  
  DDRC = 0b10000000;
  PORTC = 0b00000000;

  //-----------------------------------------------------------------------------
  //4 c. Start the Serial bus so that we can display the temperature in the serial terminal.
  Serial.begin(9600);
  Wire.begin();

}
//-----------------------------------------------------------------------------
//5. Write a function called GetTemp() that communicates I2C to the chip and retrieves (and returns)
//the temperature in degrees Celsius. 
float GetTemp(){
  Wire.beginTransmission(0x0D);
  //begins a transmission to the I2C peripheral device with the given addres, in this case is the address of AD5933
  Wire.write(0b10110000);
  Wire.write(0x92);
  Wire.requestFrom(0x0D, 2);
  //This function is used by the controller device to request bytes from a peripheral device. 
  // in this case, we want to read the data from the AD5933 and the data size is 2 bytes
  Wire.read();
  //reads a byte that was transmitted from a peripheral device to a controller device 
  //after a call to requestFrom() or was transmitted from a controller device to a peripheral device
short binary_data; 
  if (Wire.available()) {
    binary_data = Wire.read();
  }
  // convert the binary data from the chip in to celcius degrees
  // In this situation, there are two cases; which it could be either positive or negative.
  // the following are the algorithm of translating the data to celcies degrees. 
  // for positive 
  short positive_binary_data = binary_data / 32; 
  // for negative
  short negative_binary_data = (binary_data - 16384) / 32;


  // now, we have to figure out how to determine the sign of the binary data.
  // it could be determined by the first digits left hand, when it is 1, it is signed which is negative;
  // when it is 0, it is positive; with the calculation showed above, it could return the corresponding data;
  if ((binary_data & (1<<13)) == 0){
  return positive_binary_data; 
  }
  else{
    return negative_binary_data;
  }
}

//-----------------------------------------------------------------------------
// 6. Write the ISR for the I2C Interrupt.
ISR(TWI_vect){
//a. This interrupt should do the following:
// i. Check the value of the TWSR register
// ii. If that register indicates that a data byte was transmitted with an ack, toggle the onboard red LED. See table 20-2 in your 32U4 datasheet for details on the TWSR register.
// iii. Clear the TWINT flag in the TWCR register.
    if (TWCR == 0x28){
      PORTC = 0b10000000;
      }
    else{
      PORTC = 0b00000000;
    }

  // clear TWI interrupt flag
  TWCR &= 0b01111111;
}

//-----------------------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:

  // 7. Write the loop() function to poll for the temperature once per second and display the
  // temperature on the serial terminal. 

  // get the converted temperature in celies from the Getter funtion. 
  float celtemp = GetTemp();

  // display the temperature on the serial terminal. 
  Serial.println(celtemp);

  // poll for the temperature once per second
  delay(1000);


}