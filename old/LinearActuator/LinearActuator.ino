#include <Wire.h>

int goalPosition = 350; 
int currentPosition; 
boolean Extending = false;
boolean Retracting = false;
const int relay1Pin =  7;    
const int relay2Pin =  8;
volatile int receiveData[5];

void setup() {
 // put your setup code here, to run once:
 // one input
 Serial.begin(9600);
 Wire.begin();
 pinMode(relay1Pin, OUTPUT);
 pinMode(relay2Pin, OUTPUT);
}

void loop() {
 // put your main code here, to run repeatedly:
 // read from joystick
 // figure out what state youre in
 // output to h-bridge

 
 int byte_num = 0;
 Wire.requestFrom(8, 4);
 while (Wire.available()) {
   receiveData[byte_num] = Wire.read();
   byte_num++;
 }
 goalPosition = receiveData[1];
 currentPosition = analogRead(0);
 
 if (goalPosition > currentPosition) {
       Retracting = false;
       Extending = true;
       digitalWrite(relay1Pin, HIGH);  
       digitalWrite(relay2Pin, LOW);  
       Serial.println("Extending");  
   }        
   else if (goalPosition < currentPosition) {
       Retracting = true;
       Extending = false;
       digitalWrite(relay1Pin, LOW);  
       digitalWrite(relay2Pin, HIGH);
       Serial.println("Retracting");
   }
   //for (int i = 0; i < 5; i++) {
   //   Serial.print("Recieved Data: ");
   //   Serial.print(i);
   //   Serial.print("   ");
   //   Serial.println(recieveData[i]);
   //}
   Serial.print("Goal Position: ");
   Serial.println(goalPosition);
   Serial.print("Current Position: ");
   Serial.println(currentPosition);
}
