/*
 * Arduino Library for Encremental Rotary Encoder,
 *    Tested with:
 *    Arduino Boards
 *    ESP Boards
 * 
 * Example Sketch: Long Button Press
 * 
 * by Siddhant Shah, 25th Jan 2021.
 * https://www.github.com/SiddhantShah2001/
 */

/*
 * #IMPORTANT: All Functions Available in the Library.
 * 
 * "getButDur()" Function: (Data Type: uint32_t (unsigned long))
 *    Get Long Button Press,
 *    
 *    Syntax:
 *        getButDur(DURATION, COUNT)
 *            DURATION: Threshold Duration/Interval of the Long Button Press, Or Counter Encrementation Speed. (Data Type: float) (Seconds)
 *                Default is 1 Second.
 *        
 *            COUNT: To Count or Not. Counter Mode or One-Shot Mode. (Data Type: bool)
 *                Default is False (One-Shot Mode).
 *            
 *            Example 1:
 *                getButDur(0.5) : The Long Press will Trigger after 1/2 Seconds of Button Press. (ONE-SHOT: Will Return Boolean Value when Timer Hits)
 *                
 *            Example 2:
 *                getButDur(2) : The Long Press will Trigger after 2 Seconds of Button Press. (One-Shot)
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
  Serial.println(">> Long Button Press Example <<\n");

  Serial.println("Long Button Press: -\n\n");
}

void loop()
{
  // Get Rotary Encoder Long Button Press Duration
  float dur = RE.getButDur(1.5); // getButDur() in One-Shot Mode with Threshold Time 1.5 Seconds.
  static float lastDur = 0;

  // Print the Values, if Changed.
  if (lastDur != dur)
  {
    if (dur) Serial.println("> Long Button Press!\n");
    lastDur = dur;
  }
}
