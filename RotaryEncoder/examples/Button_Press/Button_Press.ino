/*
 * Arduino Library for Encremental Rotary Encoder,
 *    Tested with:
 *    Arduino Boards
 *    ESP Boards
 * 
 * Example Sketch: Button Press
 * 
 * by Siddhant Shah, 25th Jan 2021.
 * https://www.github.com/SiddhantShah2001/
 */

/*
 * #IMPORTANT: Function Documentation
 * 
 * "getBut()" Function: (Data Type: bool)
 *    Get Button Press,
 *        Returns "1" if the Button is Pressed.
 *        Returns "0" if the Button is Released or NOT Pressed.
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
  Serial.println(">> Button Press Example <<\n");
  
  Serial.println("Button State: -\n\n");
}

void loop()
{
  // Get Rotary Encoder Button Press
  bool but = RE.getBut();
  static bool lastBut = 0;

  // Print the Values, if Changed.
  if (lastBut != but)
  {
    Serial.println("> Button State: " + String((but) ? "Pressed!\n":"Released.\n"));
    lastBut = but;
  }
}
