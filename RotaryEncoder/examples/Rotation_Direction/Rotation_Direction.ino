/*
 * Arduino Library for Encremental Rotary Encoder,
 *    Tested with:
 *    Arduino Boards
 *    ESP Boards
 * 
 * Example Sketch: Rotation Direction
 * 
 * by Siddhant Shah, 25th Jan 2021.
 * https://www.github.com/SiddhantShah2001/
 */

/*
 * #IMPORTANT: Function Documentation
 * 
 * "getDir()" Function: (Data Type: int32_t (long))
 *    Get Rotation Direction,   
 *                
 *      Returns "-1" if the Rotation is in the Anti-Clockwise/Counter-Clockwise Direction. (LEFT)
 *      Returns "0" if there is NO Rotation. (STEADY)
 *      Returns "1" if the Rotation is in the Clockwise Direction. (RIGHT)
 * 
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
  Serial.println(">> Rotation Direction Example <<\n");

  Serial.println("Rotation: -\n\n");
}

void loop()
{
  // Get Rotary Encoder Spindle Rotation Direction
  int dir = RE.getDir();
  
  if (dir != 0)
  {
    if (dir == 1)
    {
      Serial.println("> Rotation: Clockwise\n");
    }
    else if (dir == -1)
    {
      Serial.println("> Rotation: Anti-Clockwise\n");
    }
  }
}
