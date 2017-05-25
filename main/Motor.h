#ifndef Motor_h 
#define Motor_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Motor
{
    public:
        Motor();

        void turnRight();

        void turnLeft();

        bool Back(); //后退

        void stright(int stright_speed);
        
        void runMotor(); //运行电机

        int back_count;
        
    private:
        const int motor_pin[4];//设定分别对应左， 右两对引脚
        
        int motor_speed[4];//存储电机速度

        unsigned long last_time; //上一次记录时间
};

#endif
