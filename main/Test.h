/*
 * 调试用类, 用于显示各传感器的数值
*/


#ifndef Test_h 
#define Test_h

#include "Sensor.h"

class Test : public Sensor
{
    public:
      Test(int mode);
    
      void showBlack();

      void showFeel();

      void showDistance();

      void show(int delay_time);

    private:
};

#endif

