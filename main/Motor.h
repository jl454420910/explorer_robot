/*
 * 电机控制类
 */

#ifndef Motor_h 
#define Motor_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Move.h"

class Motor: virtual public Move
{
    public:
        Motor();
    
        virtual void run(int mode, boolean feel); //运行电机

    protected:
        /*电机控制*/
        const int motor_pin[4];         //设定分别对应左， 右两对引脚
        const int motor_speed[5][4];    //存储在五种运动状态下的电机速度

    private:
        void normalTreat(int mode);

        void abnormalTreat(int mode);
};

#endif
