#include "Motor.h"

Motor::Motor():
motor_pin{9, 10,  5, 6},
motor_speed
{
    {LOW, 110, LOW, 110},  //直行
    {HIGH, 10, LOW, 240},  //左转
    {LOW, 250, HIGH, 0},  //右转
    {LOW, 250, LOW, 250},  //加速直行
    {HIGH, 100, HIGH, 100}, //后退
}
{
    for(int i = 0; i < sizeof(motor_pin)/sizeof(int); i++)
    {        
        pinMode(motor_pin[i], OUTPUT);
    }
}

/*运行电机*/
void Motor::run(int mode, boolean feel)
{    

    boolean center = bitRead(mode, 2);//取出最高位
    bitWrite(mode, 2, LOW);           //屏蔽最高位
    
    //触须感应到障碍物则加速
    if(feel)
    {
        //先后退
        if(millis() > last_back_time + 8000)
        {
            normalTreat(BACK);
            delay(1000);
        }
                
        last_back_time = millis();
        speed_up_dur = 2000;
    }

    //根据连续检测到黑线或悬空的持续时间决定是否加速
    if(mode == STRIGHT || mode == SPEED_UP)
    {
        if(!(center == HIGH && mode == STRIGHT))
        {
            if(black_start_time == 0)
            {
                black_start_time = millis();
            }
        
            if(black_start_time != 0 && millis() - black_start_time > (unsigned long)5000)
            {   
                black_start_time = 0;
                speed_up_dur = 3000;
            }
        }
        
        if(speed_up_dur > 0)
        {      
            speed_up_dur--;
            mode = SPEED_UP;
        }
        else
        {
            mode = STRIGHT;
        }  
    }
    else
    {
        black_start_time = 0;
    }

    //根据中间黑线传感器是否在黑线上决定采取哪种运动策略
    if(center)
    {
        normalTreat(mode);
    }
    else
    {
        abnormalTreat(mode);
    }
}

/*
 * 黑线传感器(中 右 左)状态表
 * 
 * 100 正常直线走
 * 101 向左大转
 * 110 向右大转
 * 111 单次检测到为正常直线走, 长时间连续检测到为加速直线走
 * 
 * 000 完全悬空, 长时间连续检测到为加速直线走
 * 001 向左小传并前进一小段距离, 使中间的黑线传感器落在黑线上
 * 010 向右小传并前进一小段距离, 使中间的黑线传感器落在黑线上
 * 011 几乎不可能出现的状态, 可以暂时处理为正常直线走
 */


void Motor::normalTreat(int mode)
{   
    digitalWrite(motor_pin[0], motor_speed[mode][0]); //控制方向
    digitalWrite(motor_pin[2], motor_speed[mode][2]); //控制方向
    
    analogWrite(motor_pin[1],  motor_speed[mode][1]); //调速
    analogWrite(motor_pin[3],  motor_speed[mode][3]); //调速
    
    if(mode == BACK)  //延长后退时间
    {
        //delay(100);   
    }
    else if(mode == LEFT || mode == RIGHT)//  延长转弯时间
    {
        delay(50);
    }
}

void Motor::abnormalTreat(int mode)
{
    int revise = 0;

    if(mode == LEFT)
    {
        revise = 80;
    }

    if(mode == RIGHT)
    {
        revise = -80;
    }
    
    digitalWrite(motor_pin[0], motor_speed[mode][0]); //控制方向
    digitalWrite(motor_pin[2], motor_speed[mode][2]); //控制方向
    
    analogWrite(motor_pin[1],  motor_speed[mode][1] + revise); //调速
    analogWrite(motor_pin[3],  motor_speed[mode][3] - revise); //调速

    if(mode == LEFT || mode == RIGHT)
    {
        normalTreat(STRIGHT);
        delay(10);
    }
}

