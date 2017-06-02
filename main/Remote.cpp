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

Remote::Remote() : Test(USE_FEEL)
{
  
}

boolean Remote::control()
{
    int mode;

    if(Serial.available() > 0)
    {
        do
        {
            mode = Serial.parseInt();
            Serial.println(mode);
            if(mode >= 0 && mode <= 6)
            {
                digitalWrite(motor_pin[0], motor_speed[mode][0]); //控制方向
                digitalWrite(motor_pin[2], motor_speed[mode][2]); //控制方向
    
                analogWrite(motor_pin[1],  motor_speed[mode][1]); //调速
                analogWrite(motor_pin[3],  motor_speed[mode][3]); //调速

                if(mode == STOP || mode == 6)
                {
                    while(true)
                    {
                        if(mode == 6)
                        {
                            show(1000);
                        }
                        
                        if(Serial.parseInt() == 9)
                        {
                            break;
                        }
                    }
                }
            }
            
        }while(mode != 9);

         return true;
    }
    else
    {
         return false;
    }

   
}

