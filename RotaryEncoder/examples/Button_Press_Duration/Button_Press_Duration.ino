/*
 * Arduino Library for Encremental Rotary Encoder,
 *    Tested with:
 *    Arduino Boards
 *    ESP Boards
 * 
 * Example Sketch: Button Press Duration
 * 
 * by Siddhant Shah, 25th Jan 2021.
 * https://www.github.com/SiddhantShah2001/
 */

/*
 * #IMPORTANT: Function Documentation
 * 
 * "getButDur()" Function: (Data Type: uint32_t (unsigned long))
 *    Get Button Press Duration,
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
 *                getButDur(0.5, 1) : The Long Press will Trigger after Every 1/2 Seconds of Button Press. (COUNTER: Will Return Encremented Counter Value Every Time the Timer Hits)
 *                
 *            Example 2:
 *                getButDur(2, 1) : The Long Press will Trigger after Every 2 Seconds of Button Press. (Counter)
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
  Serial.println(">> Button Press Duration Example <<\n");

  Serial.println("Button Press Duration: -\n\n");
}

void loop()
{
  // Get Rotary Encoder Long Button Press Duration
  float dur = RE.getButDur(1.5, RE_COUNT); // getButDur() in Counter Mode with Threshold Time 1.5 Seconds. RE_COUNT is Equivalent to "true"/"1".
  static float lastDur = 0;

  // Print the Values, if Changed.
  if (lastDur != dur)
  {
    if (dur) Serial.println("> Button Press Duration: " + String(dur) + " (Sec.)\n");
    lastDur = dur;
  }
}
