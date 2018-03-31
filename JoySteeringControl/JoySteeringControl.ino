/* 
 * UW Human Powered Submarine
 * Tremaine Ng
 * 1/27/2018
 * Takes input from an analog joystick with 3 axes
 * and outputs control signals to connected actuators and servos
 */ 

#include <Wire.h>
#include <Servo.h>

// Joystick
const int POT_RESISTOR;    // resistance values of resistors connected to 4.5k potentiometer
const int VOLTAGE_BATTERY; // voltage level of battery connected to joystick
const int xPin = 1;
const int yPin = 3;
const int zPin = 4;
const int jumpRange = 7;

// Actuator/H-bridge
const int feedbackPin = 0;
const int maxPos = 930;
const int minPos = 810;
const int middlePos = (maxPos + minPos) / 2;
boolean extend;
boolean retract;
const int hbIn1 = 2;    
const int hbIn2 = 4;
const int hbPWM = 6;
const int hbSTBY = 11;

// Servos
Servo servoP; // port servo
Servo servoS; // starboard servo
const int angleRange = 15;  // angle range in each direction
const int startAngle = 78;
const int startAngle2 = 107;

void setup() {
  Serial.begin(9600); // begin for terminal debugging
  pinMode(hbIn1, OUTPUT);
  pinMode(hbIn2, OUTPUT);
  pinMode(hbPWM, OUTPUT);
  pinMode(hbSTBY, OUTPUT);
  servoP.attach(9);
  servoS.attach(10);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
}

void loop() {
  // read joystick =================s===============
  int Ax = analogRead(xPin); // left/right
  int Ay = analogRead(yPin); // forward/back
  int Az = analogRead(zPin); // twist
  int Db = digitalRead(2);
  
  // read actuator position =======================
  int currActPos = analogRead(feedbackPin);
  
  // set actuator outputs =========================
  int targetPos = middlePos + map(Ay, 0, 1023, -60, 60);
  if (abs(targetPos - currActPos) <= jumpRange) { // Anti-oscillation measure; Checks range before checking if adjustments are needed.
     setActuator(0);
     //Serial.println("At/Near goal position.");
  } else {
     if (targetPos > currActPos) {
        setActuator(1);
        Serial.println("Extending");
     }
     else if (targetPos < currActPos) {
        setActuator(-1);
        Serial.println("Retracting");
     } else {
        setActuator(0);
        Serial.println("Holding");
     }
  }

   Serial.print("Actuator target: ");
   Serial.println(targetPos);
   Serial.print("Actuator current: ");
   Serial.println(currActPos);
  
  // set servo outputs ================================
  int servoOut = map(Ax, 0, 1023, startAngle-angleRange, startAngle+angleRange);
  int servoOut2 = map(Ax, 0, 1023, startAngle2+angleRange, startAngle2-angleRange);
  Serial.print("Servo target angle: ");
  Serial.println(servoOut);
  servoP.write(servoOut);
  servoS.write(servoOut2);
}

// sets an actuator to extend, retract, or do nothing
// using a connected h-bridge
// -1 retracts, 0 does nothing, 1 extends
void setActuator(int dir) {
  switch (dir) {
    case 1:
      digitalWrite(hbIn1, LOW);
      digitalWrite(hbIn2, HIGH);
      digitalWrite(hbPWM, HIGH);
      digitalWrite(hbSTBY, HIGH);
      break;
    case 0:
      digitalWrite(hbSTBY, LOW);
      break;
    case -1:
      digitalWrite(hbIn1, HIGH);
      digitalWrite(hbIn2, LOW);
      digitalWrite(hbPWM, HIGH);
      digitalWrite(hbSTBY, HIGH);
      break;
  }
}

