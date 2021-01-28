# Rotary Encoder

Arduino Library to Interface Incremental Rotary Encoders.

Tested with Arduino Boards, ESP8266, ESP32.

# Functions/Features:

> #  bool getBut()
    
        Get Button Press,
        Returns '1' if Pressed.
        Returns '0' if Released/Idle.
        
    
> # float getButDur(float THRESHOLD, bool MODE)
    
        Get Long Button Press with Customizable Threshold Value, as a Long Button Press Detector or Button Press Duration Counter.
        
        In Long Press Detection Mode:
            Returns '1' if Long Button Press is Detected.
            Returns '0' if the Button is Released or Idle.
            
        In Long Press Duration Counter Mode:
        Returns the Time in Seconds for which the Button was Presssed.
        
      > THRESHOLD: The Time in Seconds after which the Long Button Press is Detected. Also the Interval Time in Counter Mode.
            Default value is set to '1', i.e, Second.
          
      > MODE: The Mode of the Function, either Long Button Press Detector or Long Button Press Counter.
            False: Long Press Detection Mode.
            True: Long Press Counter Mode.
            Default is set to False, Long Press Detection Mode.
            
            
> # long getDir(bool MODE)
    
        Get Spindle Rotation Direction, as Direction or Counter.
        
        In Direction Mode:
            Returns '-1' if the Rotation is in Anti-Clockwise Direction.
            Returns '0' if No Rotation or Idle.
            Returns '1' if the Rotation is in Clockwise Direction.
            
        In Counter Mode:
            Returns Counter Value.
            
      > MODE: The Mode of the Function, either Direction Mode or Counter Mode.
            False: Direction Mode.
            True: Counter Mode.
            Default is set to False, Direction Mode.
            
