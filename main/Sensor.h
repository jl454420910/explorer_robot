#ifndef Sensor_h 
#define Sensor_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

enum
{
  USE_ULT = 1,
  USE_FEEL = 2,
};

class Sensor
{
    public:
      Sensor(int mode);
    
      int readBlack();

      float getDistance();

      bool getFeel();
      
    private:
      const int black_pin[2]; //依次为右 左传感器 
      const int threshod[2]; //黑标传感器阀值，分别对应右 左传感器
      
      static const int trig_pin = 2;  //超声波传感器引脚 输出
      static const int echo_pin = A3; //输入

      const int feel_pin[2]; //触须传感器
};

#endif
