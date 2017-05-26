#include "Sensor.h"
      
Sensor::Sensor(int mode):
threshod{400, 400}, black_pin{A4, A0}, feel_pin{A3, A2}
{
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
    int sensor_data = 0;         //存储传感器读取到的数据

    for(int i = 0; i < sizeof(black_pin)/sizeof(int); i++)
    {
        int val; //临时变量

        val = analogRead(black_pin[i]);
        //delay(100);
 
        #ifdef TEST
            Serial.print(val);
            Serial.print(' ');
        #endif

        //设定阀值
        if(val <= threshod[i])
        {
          val = 1;
        }
        else
        {
          val = 0;
        }

        //依次存储在sensor_data对应位中
        sensor_data = sensor_data | (val << i);
    }
    
    #ifdef TEST
          Serial.println();
          Serial.println(sensor_data);
          Serial.println();
    #endif

    return sensor_data;
}

/*利用触须传感器判断现在是否碰到障碍物*/
bool Sensor::getFeel()
{
    int result = 0;
    for(int i = 0; i < sizeof(feel_pin)/sizeof(int); i++)
    {
        //分别存储在十进制的每一位中
        if(i != 0)
        {
            result *= 10;
        }
       //检测到为低电平
        result += digitalRead(feel_pin[i]);      
    }
    
    #ifdef TEST
        for(int i = 0; i < sizeof(feel_pin)/sizeof(int); i++)
        {
           Serial.print(feel_pin[i]);
           Serial.print(": ");
           Serial.println(digitalRead(feel_pin[i]));
         }   
    #endif

    if(result == 11)
    {
        return false;
    }
    else
    {
        return true;
    }
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

    #ifdef TEST
        Serial.print(cm); 
        Serial.print("cm"); 
        Serial.println(); 
        delay(1000); 
    #endif

//    负值为无障碍
    if(cm < 0)
        cm = 1000;
        
    return cm;
}
