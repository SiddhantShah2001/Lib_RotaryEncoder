/*
		> RotaryEncoder.h
		> Library to Interface Encremental Rotary Encoders with Arduino, ESP Boards.
			by Siddhant Shah, 25th Jan 2021

		Released into the Public Domain.
 */

#include "Arduino.h"

#ifndef RotaryEncoder_h_
#define RotaryEncoder_h_

#ifdef __AVR__
  #define AVR_uC true
#else
  #define AVR_uC false
#endif

#define RE_COUNT true

class RotaryEncoder
{
  public:
  	RotaryEncoder(uint16_t CLOCK_PIN, uint16_t DATA_PIN, uint16_t BUTTON_PIN, uint8_t CLK_SPD = 0);
  	int32_t getDir(bool count = 0);
  	bool getBut();
  	float getButDur(float updateTime = 1, bool count = 0);

  private:
  	uint32_t currentTimeMillis(bool update = 0);
  	uint64_t currentTimeMicros(bool update = 0);
  	uint16_t _CLOCK_PIN;
  	uint16_t _DATA_PIN;
  	uint16_t _BUTTON_PIN;
    uint8_t _CLK_SPD;
};

#endif