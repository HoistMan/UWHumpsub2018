#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

double depth = 3.5;
double pitch = 0;
double velocity = 15.12;

void setup() {
 // set up the LCD’s number of columns and rows:
 lcd.begin(16, 2);
 // Print a message to the LCD.
 //lcd.print(“hello, world!“);
}

void loop() {
 // set the cursor to column 0, line 1
 // (note: line 1 is the second row, since counting begins with 0):
 lcd.setCursor(0, 0);
 // print the number of seconds since reset:
 lcd.print(“D: “);
 lcd.setCursor(3, 0);
 lcd.print(depth);

 lcd.setCursor(8, 0);
 lcd.print(“P: “);
 lcd.setCursor(11, 0);
 lcd.print(pitch);

 lcd.setCursor(0,1);
 lcd.print(“S: “);
 lcd.setCursor(3,1);
 lcd.print(velocity);
}
