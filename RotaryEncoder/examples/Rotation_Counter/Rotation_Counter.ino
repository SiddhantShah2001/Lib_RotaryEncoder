/*
 * Arduino Library for Encremental Rotary Encoder,
 *    Tested with:
 *    Arduino Boards
 *    ESP Boards
 * 
 * Example Sketch: Rotation Counter
 * 
 * by Siddhant Shah, 25th Jan 2021.
 * https://www.github.com/SiddhantShah2001/
 */

/*
 * #IMPORTANT: Function Documentation
 * 
 * "getDir()" Function: (Data Type: int32_t (long))
 *    Get Rotation Direction,
 *        Features:
 *            Set the Function to Counter Mode or Direction Only Mode.
 *            
 *          
 *    Syntax:
 *        getDir(COUNT)
 *            COUNT: To Count or Not. Counter Mode or Direction Only Mode. (Data Type: bool)
 *                Default is False (Direction-Only Mode).
 */

// Declare the Pins, Include the Library and Declare it's Instance.

#define CLK 2 // CLK Pin Connects to Digital Pin 2 of Arduino
#define DT  3 // DT Pin Connects to Digital Pin 3 of Arduino
#define SW  4 // SW Pin Connects to Digital Pin 4 of Arduino
#include <RotaryEncoder.h>
RotaryEncoder RE(CLK, DT, SW); // CLOCK, DATA, SWITCH

void setup()
{
  Serial.begin(9600);
  Serial.print("\n");
  Serial.println(">>>> Rotary Encoder Library <<<<");
  Serial.println(">> Rotation Counter Example <<\n");

  Serial.println("Rotation: -");
}

void loop()
{
  // Get Rotary Encoder Spindle Rotation Direction
  long dir = RE.getDir(RE_COUNT); // getDir() Function in Counter Mode. RE_COUNT is Equivalent to "true"/"1".
  static long lastDir = 0;
  String rotDir = "";

  // Print the Values, if Changed.
  if (lastDir != dir)
  {
    if (dir > lastDir)
    {
      rotDir = "\t(Clockwise)";
    }
    else
    {
      rotDir = "\t(Anti-Clockwise)";
    }
    
    Serial.println("> Rotation: " + String(dir) + rotDir + "\n");
    lastDir = dir;
  }
}
