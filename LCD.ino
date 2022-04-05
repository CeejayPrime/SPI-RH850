
/*************This file contains macros for the use of the Parallax 27929 LCD module. It can utilizes all 4 lines of the LCD**************/


#include <SoftwareSerial.h>
SoftwareSerial LCD = SoftwareSerial(3,3);

#define backSpace 8 //Backspace / Left - The cursor is moved one position to the left. The command doesn’t erase the character.
#define formFeed 12 //Form Feed - The cursor is moved to position 0 on line 0 and the entire display is cleared. Users must pause 5ms after this command.
#define lineFeed 10 //Line Feed - The cursor is moved down one line. For the two line LCD model, if on line 0 it goes to line 1. If on line 1, it wraps around to line 0. The horizontal position remains the same
#define carriageReturn 13 //Carriage Return – For the two line LCD model, if on line 0 the cursor is moved to position 0 on line 1. If on line 1, it wraps around to position 0 on line 0.
#define backlightOn 17 //Turn backlight on
#define backlightOff 18 //Turn backlight off
#define displayOff 21 //Turn the display off
#define displayOn 24 //Turn the display on, with cursor on and no blink
#define line0pos0 128 //Move cursor to line 0, position 0
#define line1pos0 148 //Move cursor to line 1, position 0
#define line2pos0 168 //Move cursor to line 2, position 0
#define line3pos0 188 //Move cursor to line 3, position 0
void setup()
{
  pinMode(3, OUTPUT);
  digitalWrite(3,HIGH);//Normal state of serial port when it isnt sending data.
  LCD.begin(9600);
  delay(150);
  LCD.write(formFeed);
  delay(7);
  LCD.write(displayOn);
  delay(100);
  LCD.write(backlightOn);
  delay(100);
  LCD.write(carriageReturn);
  LCD.write(carriageReturn);
  LCD.print("H-bridge Simulator");
  delay(3000);
  LCD.write(carriageReturn);
  LCD.write(carriageReturn);
  LCD.print("H-bridge Simulator");
  LCD.write(line2pos0);
  delay(3000);
  LCD.print("                    ");//line of 20 spaces. Used to clear a line of the LCD
  
  //LCD.write(formFeed);
}

void loop() 
{
//  LCD.write(formFeed);
//  delay(7);
//  LCD.write(backlightOff);
//  delay(1000);
//  LCD.write(backlightOn);
//  LCD.write(displayOn);
//  LCD.print("LCD Testing");
//  delay(3000);
//  LCD.write(carriageReturn);
//  LCD.print("Carriage Testing");
//  delay(3000);
//  LCD.write(backlightOff);
//  delay(1200);
//  LCD.write(displayOff);
}
