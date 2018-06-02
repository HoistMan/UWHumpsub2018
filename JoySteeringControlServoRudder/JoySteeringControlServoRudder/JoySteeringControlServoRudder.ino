/* 
 * UW Human Powered Submarine
 * Tremaine Ng
 * 4/23/2018
 * Takes input from an analog joystick with 2 axes
 * and outputs control signals to connected servos
 */ 

#include <Wire.h>
#include <Servo.h>

// Joystick
const int xPin = 1;
const int yPin = 3;

// Servos
Servo servoP; // port servo
Servo servoS; // starboard servo
Servo servoR; // rudder servo
const int angleRangePitch = 30;  // angle range in each direction
const int angleRangeYaw = 30;
const int startAngleP = 108;
const int startAngleS = 103;
const int startAngleR = 98;
const int centerRudder = 550;
const int centerPitch = 490;

void setup() {
  Serial.begin(9600); // begin for terminal debugging
  servoP.attach(5);
  servoS.attach(10);
  servoR.attach(11);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
}

void loop() {
  // read joystick =================s===============
  int Ax = analogRead(xPin); // left/right
  int Ay = analogRead(yPin); // forward/back
  
  // set servo outputs ================================
  Serial.print("joystick input x: ");
  Serial.println(Ax);
  Serial.print("joystick input y: ");
  Serial.println(Ay);

  // mapping functions
  
  int servoOutP;// = map(Ax, 0, 1023, startAngleP-angleRangePitch, startAngleP+angleRangePitch);
  int servoOutS;// = map(Ax, 0, 1023, startAngleS+angleRangePitch, startAngleS-angleRangePitch);

  if (Ax >= centerPitch + 250) {
    servoOutP = map(Ax, centerPitch + 250, 900, startAngleP, startAngleP+angleRangePitch);
    //servoOutS = map(Ax, centerPitch + 100, 900, startAngleS, startAngleS+angleRangePitch);
    servoOutS = map(Ax, centerPitch + 250, 900, startAngleS, startAngleS-angleRangePitch);
  } else if (Ax < centerPitch - 100) {
    servoOutP = map(Ax, centerPitch - 100, 100, startAngleP, startAngleP-2*angleRangePitch);
    //servoOutS = map(Ax, 100, centerPitch - 100, startAngleS-angleRangePitch, startAngleS);
    servoOutS = map(Ax, centerPitch - 100, 100, startAngleS, startAngleS+2*angleRangePitch);
  } else {
    servoOutP = startAngleP;
    servoOutS = startAngleS;
  }

  
  //int servoOutR = map(Ay, 0, 1023, startAngleR+angleRangeYaw, startAngleR-angleRangeYaw);
  int servoOutR;
  if (Ay >= centerRudder + 50) {
    servoOutR = map(Ay, centerRudder + 50, 900, startAngleR, startAngleR+angleRangeYaw);
  } else if (Ay < centerRudder - 200) {
    servoOutR = map(Ay, 0, centerRudder - 200, startAngleR-angleRangeYaw, startAngleR);
  } else {
    servoOutR = startAngleR;
  }
  
  //Serial.print("Servo target angle P: ");
  //Serial.println(servoOutP);
  //Serial.print("Servo target angle R: ");
  //Serial.println(servoOutR);
  servoP.write(servoOutP);
  servoS.write(servoOutS);

  // Servo S and P error detect
  //if (Ax > 1000 || Ax < 100) {
    //servoS.write(startAngleS);
    //servoP.write(startAngleP);
  //} else {
   // servoS.write(servoOutS);
    //servoP.write(servoOutP);
  //}
  
  // Servo R error detect
  //if (Ay > 1000 || Ay < 100) {
    //servoR.write(startAngleR);
  //} else {
    servoR.write(servoOutR);
  //}
}

