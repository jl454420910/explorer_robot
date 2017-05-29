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

        boolean Back(); //后退

        void stright(int stright_speed); //直行
        
        void runMotor(); //运行电机

        void set_auxiliary_speed(int myspeed); //设定辅助轮速度

        
        int back_count;
    
    protected:
        /*前两对大轮电机控制*/
        const int motor_pin[4];   //设定分别对应左， 右两对引脚
        int motor_speed[4];       //存储电机速度

        /*后一对辅助轮控制*/
        const int auxiliary_pin[2]; //辅助后轮控制引脚
        int auxiliary_speed[2];  //存储后辅助轮速度
        
        unsigned long last_time; //上一次记录时间
};

#endif
