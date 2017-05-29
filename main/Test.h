#ifndef Test_h 
#define Test_h

#include "Motor.h"
#include "Sensor.h"

class Test : public Motor, Sensor
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

