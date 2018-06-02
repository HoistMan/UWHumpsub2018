// Peripheral
// UW Human Powered Submarine
// Zack Calipes
// Reads joystick location, transmits to master via serial

const int X_PIN = 0; // x joystick input on A0
const int Y_PIN = 1; // y joystick input on A1

const byte START = 255; // byte to siginfiy start of data
const int DELAY = 100; //Delay between writing each data

int Ax, Ay;
byte AxByte, AyByte;


void setup() {
  Serial.begin(9600);
}

void loop() {
  
  // Read X and Y joystick values
  Ax = analogRead(X_PIN);
  Ay = analogRead(Y_PIN);

 
  // Maps Analog values to a single byte to be transmitted
  // Max is 254 to reserve 255 for the "start" byte
  AxByte = (byte) map(Ax, 0, 1023, 0, 254);
  AyByte = (byte) map(Ay, 0, 1023, 0, 254);

  Serial.write(START);
  delay(DELAY);
  Serial.write(AxByte);
  delay(DELAY);
  Serial.write(AyByte);
  delay (DELAY);
  
}
