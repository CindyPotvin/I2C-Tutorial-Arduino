// I2C Slave for the tutorial at https://robotsbench.com/i2c-communication-arduino/
// The master request data from a slave that reads data from a sensor.
#include <Wire.h>
// Slave address of this arduino on the bus.
const int SLAVE_ADDRESS = 0x10; 
// Analog pin A0 for the potentiometer that will act as an analog sensor in this example.
const int SENSOR_ANALOG_PIN = 14; 
// Variable for the current value of the analog pin (declared here to declare it only once).
int analogPinValue;
const int BYTES_TO_SEND = 2;
uint8_t sendBuffer[BYTES_TO_SEND];

void setup() {
  // Enable I2C on the Arduino, including pull-up resistors and join the bus as a slave.
  Wire.begin(SLAVE_ADDRESS);
  
  // Register event to respond to request from the master.
  Wire.onRequest(respondToMasterEvent); 
  
  // Enable serial for debug information.
  Serial.begin(115200);
}

// This function is called when the master requests data from the slave.
void respondToMasterEvent() {
  // The analog pin can return values from 0 to 1023 (10 bits).
  analogPinValue = analogRead(SENSOR_ANALOG_PIN);
  // Put the value in two uint8_t to send in 8bit format over I2C
  sendBuffer[0] = analogPinValue >> 8;
  sendBuffer[1] = analogPinValue & 0xff; 
  Wire.write(sendBuffer, BYTES_TO_SEND); 
  Serial.println(analogPinValue);
}

void loop() {
  // Receiving the I2C message has priority over the code in the loop (it works with 
  // interrupts), but nothing happens in the loop in this sketch. 
  delay(1000);
}
