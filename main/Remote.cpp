#include "Remote.h"

/*
 * 0 前进
 * 1 左转
 * 2 右转
 * 3 加速
 * 4 后退
 * 5 停止
 * 6 停止并测数据
 * 9 取消控制
 */

Remote::Remote() : Test(USE_FEEL),
motor_pin{9, 10,  5,  6}, 
motor_speed
{
    {LOW, 100, LOW, 100},  //直行
    {HIGH, 100, LOW, 150},  //左转
    {LOW, 150, HIGH, 100},  //右转
    {LOW, 250, LOW, 250},  //加速直行
    {HIGH, 150, HIGH, 150}, //后退
    {LOW, 0, LOW, 0}, //停止
}
{
  
}

void Remote::control()
{
    char mode;

    if(Serial.available() > 0)
    {   
        println("Now car is in remote mode!");
        println("Press q to finish remoting");
        
        do
        {
            mode = Serial.read();
            
            Serial.print("Get : ");
            Serial.println(mode);

            if(mode == -1)
            {
                break;
            }
            
            mode -= '0';
            if(mode >= 0 && mode <= 6)
            {
                digitalWrite(motor_pin[0], motor_speed[mode][0]); //控制方向
                digitalWrite(motor_pin[2], motor_speed[mode][2]); //控制方向
    
                analogWrite(motor_pin[1],  motor_speed[mode][1]); //调速
                analogWrite(motor_pin[3],  motor_speed[mode][3]); //调速

                if(mode == STOP || mode == STOP_AND_CHECK)
                {
                    while(true)
                    {
                        if(mode == STOP_AND_CHECK)
                        {
                            show(1500);
                        }
                        
                        if(Serial.read() == 'q')
                        {
                            break;
                        }
                    }
                }
            }
            
        }while(mode != 'q');
    }   
}

