/*
 * 传感器控制库
*/

#include "Sensor.h"
      
Sensor::Sensor(int mode):
threshod{480, 480}, black_pin{A0, A4}, feel_pin{A2, A3} , led_pin{4, 8}, trig_pin(2), echo_pin(A3)
{

    for(int i = 0; i < sizeof(led_pin)/sizeof(int); i++)
    {        
        pinMode(led_pin[i], OUTPUT);
    }
    
    switch(mode)
    {
      case USE_ULT: pinMode(trig_pin, OUTPUT); 
                    pinMode(echo_pin, INPUT);
                    break;

      case USE_FEEL: for(int i = 0; i < sizeof(feel_pin)/sizeof(int); i++)
                    {
                      pinMode(feel_pin[i], INPUT);
                    }
                    break;
    }
   
}

/*读取黑线传感器数据*/
int Sensor::readBlack()
{       
    int black_data = 0;         //存储传感器读取到的数据

    for(int i = 0; i < sizeof(black_pin)/sizeof(int); i++)
    {
        //设定阀值
        bitWrite(black_data, i, ((analogRead(black_pin[i]) <= threshod[i]) ? HIGH : LOW));
    }

    //亮对应方向的灯
    for(int i = 0; i < sizeof(led_pin)/sizeof(int); i++)
    {
        digitalWrite(led_pin[i], bitRead(black_data, i));
    }
    
    return black_data;
}

/*利用触须传感器判断现在是否碰到障碍物*/
boolean Sensor::getFeel()
{
    int feel_data = 0;
    
    for(int i = 0; i < sizeof(feel_pin)/sizeof(int); i++)
    {
       //检测到为低电平为触碰到
       bitWrite(feel_data, i, !digitalRead(feel_pin[i]));      
    }

    return feel_data == 3 ? false : true;
}

/*利用超声波传感器获得距离障碍物距离*/
float Sensor::getDistance()
{ 
    float cm;   //距离障碍物距离
    
    //发一个10ms的高脉冲去触发trig_pin 
    digitalWrite(trig_pin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trig_pin, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trig_pin, LOW); 
 
    cm = pulseIn(echo_pin, HIGH) / 58.0; //算成厘米 
    cm = (int(cm * 100.0)) / 100.0; //保留两位小数

//  负值为无障碍
    if(cm < 0)
        cm = 1000;
        
    return cm;
}
