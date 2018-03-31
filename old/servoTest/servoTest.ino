#include <Servo.h>
#include <Wire.h>

Servo servo1;
Servo servo2;

void setup() {
  // put your setup code here, to run once:
  // fuck you servoes
  servo1.attach(10);
  servo2.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo1.write(0);
  servo2.write(0);
  delay(2000);
  servo1.write(180);
  servo2.write(180);
}
