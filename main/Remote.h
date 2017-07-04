/*
 * 蓝牙遥控控制类
 */

#ifndef Remote_h 
#define Remote_h

#include "Move.h"
#include "Test.h"

class Remote : public Test
{
    public:
        Remote();
        
        void control();

    protected:
        /*电机控制*/
        const int motor_pin[4];   //设定分别对应左， 右两对引脚
        const int motor_speed[6][4];    //存储在六种运动状态下的电机速度
};

#endif

