/*
 * 运行主程序
*/

//测试标志
#define nTEST

#ifdef TEST
#include "Test.h"
#endif

#include "Motor.h"
#include "Sensor.h"

//初始化电机对象
Motor myMotor;

//初始化传感器对象
Sensor mySensor(USE_FEEL);   

unsigned long obs_t = 0; //记录第一次碰到障碍物的时间
int black_count = 0; //记录同时检测到黑线的起始时间

void setup()
{     
    //Serial.begin(9600);
}

void loop()
{  
    #ifdef TEST
      Test test(USE_FEEL);
      test.show(2000);
      return ;
    #endif
    
    boolean find_black = false;
    
    switch(mySensor.readBlack())
    {
      //左转
      case 0x01:    if(myMotor.back_count >= 1)
                    {
                        myMotor.turnRight();
                        myMotor.back_count = 0;
                        break;
                    }
      
                    if(!myMotor.Back())
                    {
                        myMotor.turnLeft();
                    }

                    break;

      //右转
      case 0x02:     if(myMotor.back_count >= 1)
                    {
                        myMotor.turnLeft();
                        myMotor.back_count = 0;
                        break;
                    }
      
                    if(!myMotor.Back())
                    {
                        myMotor.turnRight();
                    }        

                    break;

      case 0x03: find_black = true;
                 if(black_count >= 2000)
                 {
                    obs_t = millis();
                 }
                 
      
      default:   //碰到障碍
                 if(millis() - obs_t < (unsigned long)500)
                 {
                      myMotor.stright(200);
                      
                      break; 
                 }
                 
                 if(mySensor.getFeel())
                 {
                    obs_t = millis();
                 }
                 else
                 {
                    myMotor.stright(90);
                 }
    }

    if(find_black)
    {
      black_count++;
    }
    else
    {
      black_count = 0;
    }
   
    myMotor.runMotor();
    
    //Serial.println(millis());
    
}
