// Master Control
// UW Human Powered Submarine
// Zack Calipes
// Reads Serial input of a peripheral

const int DATA = 2; // Amount of data to be recieved per transmission
const byte START = 255; // Byte that signifies the start of transmission

byte rec[DATA];
byte Ax, Ay;

void setup() {
  Serial.begin(9600);
}

void loop() {

  // Wait for starting byte to begin reading the data
  if (Serial.available() > 0 && Serial.read() == START) {
    
    Serial.println("reading");

    // Wait until all desired data is in the buffer, then read the data
    while (Serial.available() < DATA);
    Serial.readBytes(rec, DATA);

    Ax = rec[0];
    Ay = rec[1];

    // Print values for debugging
    Serial.print("Ax: ");
    Serial.println(Ax);
    Serial.print("Ay: ");
    Serial.println(Ay);
  }
}
