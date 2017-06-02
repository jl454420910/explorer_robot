#ifndef Move_h 
#define Move_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

enum
{
    STRIGHT,
    LEFT,
    RIGHT,
    SPEED_UP,
    BACK,
    STOP,
};

class Move
{
    public:
        Move();
        
        void runMotor(int mode, boolean feel); //运行电机

        // void set_auxiliary_speed(int myspeed); //设定辅助轮速度

        // void Move::run_servo(); //运行舵机       
    
    protected:
        /*前两对大轮电机控制*/
        const int motor_pin[4];   //设定分别对应左， 右两对引脚
        const int motor_speed[6][4];    //存储在四种运动状态下的电机速度
        
        // /*后一对辅助轮控制*/
        // const int auxiliary_pin[2]; //辅助后轮控制引脚
        // int auxiliary_speed[2];  //存储后辅助轮速度
        
        unsigned long black_start_time; //第一次检测到黑线时间记录
        unsigned long speed_up_dur; //加速持续时间
        
        unsigned long last_back_time; //上一次后退记录时间
};

#endif
