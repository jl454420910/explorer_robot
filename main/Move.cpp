#include "Move.h"

Move::Move():black_start_time(0), speed_up_dur(0), last_back_time(0)
{

}

/*

    舵机控制实现

void Move::set_auxiliary_speed(int myspeed)
{
    for(int i = 0; i < sizeof(auxiliary_speed)/sizeof(int); i++)
    {        
        auxiliary_speed[i] = myspeed;
    }
}

void Move::run_servo()
{
  
}

void servoPulse(int servo_pin,int myangle)//定义一个脉冲函数
{
    pulse_width=(myangle*11)+500;//将角度转化为500-2480的脉宽值
    digitalWrite(servo_pin,HIGH);//将舵机接口电平至高
    delayMicroseconds(pulse_width);//延时脉宽值的微秒数
    digitalWrite(servo_pin,LOW);//将舵机接口电平至低
    delay(20-pulse_width/1000);
}
*/

