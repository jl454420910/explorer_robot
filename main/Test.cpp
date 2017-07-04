#include "Test.h"

Test::Test(int mode):Sensor(mode)
{

}

/*整体显示*/
void Test::show(int delay_time)
{
    Serial.print("time: ");
    Serial.println(millis());
    Serial.println();
    
    showBlack();
    showFeel();

    Serial.println();

    delay(delay_time);
}

/*读取黑线传感器数据*/
void Test::showBlack()
{   
    Serial.print("black -- ");
    
    int black_data = 0;         //存储传感器读取到的数据

    int val; //临时变量

    for(int i = 0; i < sizeof(black_pin)/sizeof(int); i++)
    {
        val = analogRead(black_pin[i]);
        
        Serial.print(val);
        Serial.print(' ');

        //设定阀值
        bitWrite(black_data, i, ((val <= threshod[i]) ? HIGH : LOW));
    }

    for(int i = 0; i < sizeof(led_pin)/sizeof(int); i++)
    {
        digitalWrite(led_pin[i], bitRead(black_data, i));
    }
    
    Serial.print(' ');
    Serial.println(black_data);
    Serial.println();
}

/*利用触须传感器判断现在是否碰到障碍物*/
void Test::showFeel()
{
    Serial.print("Feel -- ");
  
    int feel_data = 0;
    
    for(int i = 0; i < sizeof(feel_pin)/sizeof(int); i++)
    {
        Serial.print(feel_pin[i]);
        Serial.print(": ");
        Serial.print(digitalRead(feel_pin[i]));
        Serial.print(' ');

        //检测到为低电平为触碰到
       bitWrite(feel_data, i, !digitalRead(feel_pin[i])); 
    }

    Serial.print(' ');
    Serial.println(feel_data);
    Serial.println();
}

/*利用超声波传感器获得距离障碍物距离*/
void Test::showDistance()
{ 
    Serial.print("Feel -- ");
    
    float cm;   //距离障碍物距离
    
    //发一个10ms的高脉冲去触发trig_pin 
    digitalWrite(trig_pin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trig_pin, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trig_pin, LOW); 
 
    cm = pulseIn(echo_pin, HIGH) / 58.0; //算成厘米 
    cm = (int(cm * 100.0)) / 100.0; //保留两位小数

    Serial.print(cm); 
    Serial.print("cm"); 
    Serial.println();         
}
