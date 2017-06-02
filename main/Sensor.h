/*
 * 传感器控制库
*/

#ifndef Sensor_h 
#define Sensor_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

enum
{
    USE_ULT,
    USE_FEEL,
};

class Sensor
{
    public:
        Sensor(int mode);
        
        int readBlack();
    
        boolean getFeel();
    
        float getDistance();
      
    protected:
        /*黑标*/
        const int black_pin[2]; //依次为右 左传感器 
        const int threshod[2]; //黑标传感器阀值，分别对应右 左传感器
        
        /*超声波*/
        const int trig_pin;  //超声波传感器引脚 输出
        const int echo_pin;  //输入
    
        /*触须*/
        const int feel_pin[2]; //触须传感器
    
        /*LED*/
        const int led_pin[2]; //led亮灯控制
};

#endif
