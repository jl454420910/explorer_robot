#include "Motor.h"
#include "Sensor.h"

#define NOTTEST

Motor myMotor;
      
Sensor mySensor(USE_FEEL);   

unsigned long obs_t = -1; //记录第一次碰到障碍物的时间
int black_count = 0; //记录同时检测到黑线的起始时间

void setup()
{     
      #ifdef TEST
        Serial.begin(9600);
      #endif
}

void loop()
{    
    bool find_black = false;
    
    switch(mySensor.readBlack())
    {
      case 0x01:    if(myMotor.back_count >= 1)
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
      
      case 0x02:    if(myMotor.back_count >= 1)
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

      case 0x03: find_black = true;
                 if(black_count >= 40)
                 {
                    obs_t = millis();
                 }
                 
      
      default:   //碰到障碍
                 if(millis() - obs_t < (unsigned long)5000)
                 {
                      myMotor.stright(250);
                      break; 
                 }
                  
                 
                 if(mySensor.getFeel())
                 {
                    obs_t = millis();
                 }
                 else
                 {
                    myMotor.stright(100);
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

    #ifdef TEST
      delay(2000);
    #endif
}
