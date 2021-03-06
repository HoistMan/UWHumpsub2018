/ Joystick Controller Slave
// by Tremaine Ng
// based on code from Nicholas Zambetti at https://www.arduino.cc/en/Tutorial/MasterReader
// Collects, processes, then sends data on request to master servo Arduino
// x position, y position, z twist, b button
// reading rate limited by analog read rate ~10,000 times per second

#include <Wire.h>

const int POT_RESISTOR;    // resistance values of resistors connected to 4.5k potentiometer
const int VOLTAGE_BATTERY; // voltage level of battery connected to joystick
byte toSend[4];


void setup() {
 Wire.begin(8);                // join i2c bus with slave address 1
 Wire.onRequest(requestEvent); // register event
 Serial.begin(9600);
 
 // initialize x center, y center, z center on startup?
}

void loop() {
 delay(100);
 //Serial.print(“Ax:  “);
 Serial.println(analogRead(1));
 Serial.println(toSend[1]);
 Serial.println();
}

// function when event requested by master
void requestEvent() {
 // take all inputs
 // Analog reads 0-5V to value of 0-1023
 int Ax = analogRead(0);   // read x value from analog pin 0
 int Ay = analogRead(1);   // read y value from analog pin 1
 int Az = analogRead(2);   // read z value from analog pin 2
 int Db = digitalRead(2);  // read b value from digital pin 2

 // convert 10 bit analog inputs to 8 bits to be sendable
 // bit shift drops least significant 2
 Ax = Ax >> 2;
 Ay = Ay >> 2;
 Az = Az >> 2;
 
 // send 4 byte signal in order: 1 byte x, 1 byte y, 1 byte z, 1 byte b
 toSend[0] = Ax;
 toSend[1] = Ay;
 toSend[2] = Az;
 toSend[3] = Db;
 Wire.write(toSend, 4);
}
