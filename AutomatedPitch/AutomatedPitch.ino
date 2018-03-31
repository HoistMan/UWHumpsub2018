// AutomatedPitch
// UW Human Powered Submarine
// Aiden
// (DATE)
// Supplies automated pitch control inputs to main control microcontroller
 
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

