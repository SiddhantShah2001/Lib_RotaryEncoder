/*
		> RotaryEncoder.cpp
		> Library to Interface Encremental Rotary Encoders with Arduino, ESP Boards.
			by Siddhant Shah, 25th Jan 2021

		Released into the Public Domain.
 */

#include "RotaryEncoder.h"

uint32_t RotaryEncoder::currentTimeMillis(bool update)
{
 	static uint32_t current_Time = 0;
  static uint8_t correctionFactor = 1;

  if (_CLK_SPD)
  {
    correctionFactor = 16/_CLK_SPD;
  }
  
  if (update) current_Time = millis()*correctionFactor;
  return current_Time;
}

uint64_t RotaryEncoder::currentTimeMicros(bool update)
{
  static uint64_t current_Time = 0;
  static uint8_t correctionFactor = 1;

  if (_CLK_SPD)
  {
    correctionFactor = 16/_CLK_SPD;
  }

  if (update) current_Time = micros()*correctionFactor;
  return current_Time;
}

RotaryEncoder::RotaryEncoder(uint16_t CLOCK_PIN, uint16_t DATA_PIN, uint16_t BUTTON_PIN, uint8_t CLK_SPD)
{
	_CLOCK_PIN = CLOCK_PIN;
	_DATA_PIN = DATA_PIN;
	_BUTTON_PIN = BUTTON_PIN;

  if ((AVR_uC == false) || (CLK_SPD > 16))
  {
    CLK_SPD = 0;
  }

  _CLK_SPD = CLK_SPD;

	pinMode(_CLOCK_PIN, INPUT_PULLUP);
	pinMode(_DATA_PIN, INPUT_PULLUP);
	pinMode(_BUTTON_PIN, INPUT_PULLUP);
}

int32_t RotaryEncoder::getDir(bool count)
{
/*
 * Clockwise Rotation (Right):
 *    First Half Rotation:
 *        DATA Pin contacts Ground First, then CLOCK Pin.
 *    
 *    Second Half Rotation:
 *        DATA Pin contacts VCC First, then CLOCK Pin.
 *    
 *    
 * Anti-Clockwise Rotation (Left):
 *    First Half Rotation:
 *        CLOCK Pin contacts Ground First, then DATA Pin.
 *    
 *    Second Half Rotation:
 *        CLOCK Pin contacts VCC First, then DATA Pin.
 */
  static int32_t value = 0;

  if (!count)
  {
    value = 0;
  }

  currentTimeMillis(1);
  currentTimeMicros(1);

  static uint32_t rotationTimeout = 0;

  static uint8_t CWC = 0; // Clockwise Count
  static uint8_t ACWC = 0; // Anti-Clockwise Count
  
  static uint32_t previousDA = 0; // For Debouncing
  static uint64_t DA_Start_Time = 0;
  static uint64_t DA_Stop_Time = 0;
  
  static uint32_t previousCL = 0; // For Debouncing
  static uint64_t CL_Start_Time = 0;
  static uint64_t CL_Stop_Time = 0;

  static bool DA_Val = 1;
  static bool CL_Val = 1;

  static bool DA_State = 1;
  static bool CL_State = 1;

  if (currentTimeMillis() - rotationTimeout >= 100)
  {
    if (CWC > 0 || ACWC > 0)
    {
      CWC = 0;
      ACWC = 0;
    }
  }

  if (currentTimeMillis() - previousDA >= 5)
  {
    DA_Val = digitalRead(_DATA_PIN);
  }

  if (currentTimeMillis() - previousCL >= 5)
  {
    CL_Val = digitalRead(_CLOCK_PIN);
  }

  if ((DA_State != DA_Val) || (CL_State != CL_Val))
  {
    if (DA_State != DA_Val)
    {
      DA_State = DA_Val;
      previousDA = currentTimeMillis();

      if (!DA_State)
      {
        DA_Start_Time = currentTimeMicros(1);
      }
      else
      {
        DA_Stop_Time = currentTimeMicros(1);
      }
    }

    if (CL_State != CL_Val)
    { 
      CL_State = CL_Val;
      previousCL = currentTimeMillis();

      if (!CL_State)
      {
        CL_Start_Time = currentTimeMicros(1);
      }
      else
      {
        CL_Stop_Time = currentTimeMicros(1);
      }
    }

    if((!DA_State) && (CL_State)) // Data is Grounded while Clock is not
    {
      if (DA_Start_Time > CL_Stop_Time) // Clockwise Start 1/4 (Entering...)
      {
        if ((CWC == 0) && (ACWC == 0))
        {
          CWC = 1;
          rotationTimeout = currentTimeMillis();
        }
      }
      else if (CL_Stop_Time > DA_Start_Time) // Anti-Clockwise Third 3/4 (Exiting...)
      {
        if ((CWC == 0) && (ACWC == 2))
        {
          ACWC = 3;
          rotationTimeout = currentTimeMillis();
        }
      }
    }
    else if((DA_State) && (!CL_State)) // Clock is Grounded while Data is not
    {
      if (CL_Start_Time > DA_Stop_Time) // Anti-Clockwise Start 1/4 (Entering...)
      {
        if ((CWC == 0) && (ACWC == 0))
        {
          ACWC = 1;
          rotationTimeout = currentTimeMillis();
        }
      }
      else if (DA_Stop_Time > CL_Start_Time) // Clockwise Third 3/4 (Exiting...)
      {
        if ((CWC == 2) && (ACWC == 0))
        {
          CWC = 3;
          rotationTimeout = currentTimeMillis();
        }
      }
    }
    else if((!DA_State) && (!CL_State)) // Both are Grounded (2/4) (Entered)
    {
      if (CL_Start_Time > DA_Start_Time) // Clockwise
      {
        if ((CWC == 1) && (ACWC == 0))
        {
          CWC = 2;
          rotationTimeout = currentTimeMillis();
        }
      }
      else if (DA_Start_Time > CL_Start_Time)
      {
        if ((CWC == 0) && (ACWC == 1))
        {
          ACWC = 2;
          rotationTimeout = currentTimeMillis();
        }
      }
    }
    else if ((DA_State) && (CL_State)) // Back to Normal (VCC) (4/4) (Exited)
    {
      if (CL_Stop_Time > DA_Stop_Time) // Clockwise
      {
        if ((CWC == 3) && (ACWC == 0))
        {
          CWC = 0;
          (count) ? (value++) : (value = 1);
          rotationTimeout = currentTimeMillis();
        }
      }
      else if (DA_Stop_Time > CL_Stop_Time) // Anti-Clockwise
      {
        if ((CWC == 0) && (ACWC == 3))
        {
          ACWC = 0;
          (count) ? (value--) : (value = -1);
          rotationTimeout = currentTimeMillis();
        }
      }
    }
  }
  
  return value;
}

bool RotaryEncoder::getBut()
{
	static bool value = 0;

	currentTimeMillis(1);
	static uint32_t previousButton = 0;

	bool ButtonPress = !digitalRead(_BUTTON_PIN);
	static bool ButtonState = 0;

	if (currentTimeMillis() - previousButton >= 250)
	{
		if ((ButtonPress) && (!ButtonState))
		{
			value = 1;
			ButtonState = 1;
			previousButton = currentTimeMillis();
		}
		else if ((!ButtonPress) && (ButtonState))
		{
			value = 0;
			ButtonState = 0;
			previousButton = currentTimeMillis();
		}
	}

	return value;
}

float RotaryEncoder::getButDur(float updateTime, bool count)
{
	static float value = 0;

	currentTimeMillis(1);
	static uint32_t previousDuration = 0;
	uint32_t timeDuration = 1000*updateTime;

	bool ButtonPress = getBut();

	if (ButtonPress)
	{
		if (currentTimeMillis() - previousDuration >= timeDuration)
		{
			if (count)
			{
				value += updateTime;
				previousDuration = currentTimeMillis();
			}
			else
			{
				value = 1;
			}
			
		}
	}
	else
	{
		value = 0;
		previousDuration = currentTimeMillis();
	}

	return value;
}