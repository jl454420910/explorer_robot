/*
 * 运动抽象类
*/

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
    STOP_AND_CHECK,
};

class Move
{
    public:
        Move();
    
        virtual void run(int mode, boolean feel); //运动实现总控制
        
    protected:
        /*加速控制*/
        unsigned long black_start_time; //第一次检测到黑线时间记录
        unsigned long speed_up_dur; //加速持续时间

        /*后退控制*/
        unsigned long last_back_time; //上一次后退记录时间
};

#endif
