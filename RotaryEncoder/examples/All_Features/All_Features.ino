/*
 * Arduino Library for Encremental Rotary Encoder,
 *    Tested with:
 *    Arduino Boards
 *    ESP Boards
 * 
 * Full Features of the Library in a Single Sketch
 * 
 * by Siddhant Shah, 25th Jan 2021.
 * https://www.github.com/SiddhantShah2001/
 */

/*
 * #IMPORTANT: All Functions Available in the Library.
 * 
 * #A.
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
 *                
 *                    Returns "-1" if the Rotation is in the Anti-Clockwise/Counter-Clockwise Direction. (LEFT)
 *                    Returns "0" if there is NO Rotation. (STEADY)
 *                    Returns "1" if the Rotation is in the Clockwise Direction. (RIGHT)
 *      
 * 
 * #B.
 * 
 * "getBut()" Function: (Data Type: bool)
 *    Get Button Press,
 *        Returns "1" if the Button is Pressed.
 *        Returns "0" if the Button is Released or NOT Pressed.
 *    
 * 
 * #C.
 * 
 * "getButDur()" Function: (Data Type: uint32_t (unsigned long))
 *    Get Button Press Duration,
 *        Features:
 *            Set the Threshold Duration of the Press to be Detected. (In Seconds)
 *            Set the Function to Counter Mode or One-Shot Mode.
 *            
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
 *                getButDur(0.5, 0) : The Long Press will Trigger after 1/2 Seconds of Button Press. (ONE-SHOT: Will Return Boolean Value when Timer Hits)
 *                
 *            Example 2:
 *                getButDur(2, 1) : The Long Press will Trigger after Every 2 Seconds of Button Press. (Counter)
 *                getButDur(2, 0) : The Long Press will Trigger after 2 Seconds of Button Press. (One-Shot)
 * 
 */

// Declare the Pins, Include the Library and Declare it's Instance.

#define CLK 2 // CLK Pin Connects to Digital Pin 2 of Arduino
#define DT  3 // DT Pin Connects to Digital Pin 3 of Arduino
#define SW  4 // SW Pin Connects to Digital Pin 4 of Arduino
#include <RotaryEncoder.h>
RotaryEncoder RE(CLK, DT, SW, 16); // CLOCK, DATA, SWITCH, (Optional: Micro-Controller Clock Speed 1-16 MHz (AVR Only))

void setup()
{
  Serial.begin(9600);
  Serial.print("\n");
  Serial.println(">>>> Rotary Encoder Library <<<<");
  Serial.println(">> Full Features Example <<\n");

  Serial.println("Rotation: -");
  Serial.println("Button State: -");
  Serial.println("Long Button Press: -\n\n");
}

void loop()
{
  // Get Rotary Encoder Spindle Rotation Direction
  long dir = RE.getDir(RE_COUNT); // getDir() Function in Counter Mode. RE_COUNT is Equivalent to "true"/"1".
  static long lastDir = 0;
  String rotDir = "";

  // Get Rotary Encoder Button Press
  bool but = RE.getBut();
  static bool lastBut = 0;

  // Get Rotary Encoder Long Button Press Duration
  float dur = RE.getButDur(1.5, RE_COUNT); // getButDur() in Counter Mode with Threshold Time 1.5 Seconds. RE_COUNT is Equivalent to "true"/"1".
  static float lastDur = 0;

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
  
  if (lastBut != but)
  {
    Serial.println("> Button State: " + String((but) ? "Pressed!\n":"Released.\n"));
    lastBut = but;
  }
  
  if (lastDur != dur)
  {
    if (dur) Serial.println("> Long Button Press: " + String(dur) + " (Sec.)\n");
    lastDur = dur;
  }
}
