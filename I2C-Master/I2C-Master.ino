// I2C Master for the tutorial at https://robotsbench.com/i2c-communication-arduino/
// The master request data from a slave that reads data from a sensor.
#include <Wire.h>
// Address of the slave on the bus.
const int SLAVE_ADDRESS = 0x10; 
// Number of bytes to request from the slave
const int BYTES_TO_REQUEST = 2;
// Last value received from the slave
int slaveIncomingValue = 0;

void setup() {
  // Enable I2C on the Arduino, including pull-up resistors.
  Wire.begin();
  // Enable serial for debug information
  Serial.begin(115200);
}

void loop() {
  Wire.beginTransmission(SLAVE_ADDRESS);
  // Request 4 bytes from slave device (slave may send less)
  Wire.requestFrom(SLAVE_ADDRESS, BYTES_TO_REQUEST);    
  // Read the bytes on the bus, two at a time
  while (Wire.available() >= BYTES_TO_REQUEST) { 
    slaveIncomingValue = Wire.read() << 8 | Wire.read(); 
  }
  // Print the complete value received.
  Serial.println(slaveIncomingValue);   
    
  Wire.endTransmission();
  // Read again from the slave in 5 seconds.
  delay(5000);
}
