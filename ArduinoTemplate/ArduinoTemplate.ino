// ArduinoTemplate
// UW Human Powered Submarine
// (YOUR NAME HERE)
// (DATE)
// (DESCRIBE HIGH LEVEL FUNCTION, HARDWARE INPUT/OUTPUT)
 
// Globals ==============
/* subdivide globals with comments as needed */

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

/* Put helper functions below */

// calculates and returns 2 to the power of the given number
int sampleHelper(int base) {
  int result = 2;
  for (int i = 0; i < base; i++) {
    result = result * 2;
  }
  return result;
}

