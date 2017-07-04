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
        const int black_pin[3]; //依次为左 右 中传感器 
        const int threshod[3]; //黑标传感器阀值，分别对应左 右 中传感器
        
        /*超声波*/
        const int trig_pin;  //超声波传感器引脚 输出
        const int echo_pin;  //输入
    
        /*触须*/
        const int feel_pin[1]; //触须传感器
    
        /*LED*/
        const int led_pin[2]; //led亮灯控制
};

#endif
