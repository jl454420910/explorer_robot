#include "Motor.h"

Motor::Motor():
motor_pin{9, 10,  5,  6}, last_time(0), back_count(0)
{
    for(int i = 0; i < sizeof(motor_pin)/sizeof(int); i++)
    {        
        pinMode(motor_pin[i], OUTPUT);
    }
}

/*运行电机*/
void Motor::runMotor()
{
  digitalWrite(motor_pin[0], motor_speed[0]); //控制方向
  digitalWrite(motor_pin[2], motor_speed[2]); //控制方向
  
  analogWrite(motor_pin[1],  motor_speed[1]); //调速
  analogWrite(motor_pin[3],  motor_speed[3]); //调速

//  if(motor_speed[0] == HIGH && motor_speed[2] == HIGH)
//  {
//      delay(50);   
//  }
//  else if(!(motor_speed[0] == LOW && motor_speed[2] == LOW))//  延长转弯时间
//  {
//      delay(50);
//  }
}

void Motor::turnRight()//右转 左加速
{
    motor_speed[0] = LOW;
    motor_speed[1] = 140;
    motor_speed[2] = HIGH;
    motor_speed[3] = 110;
}

void Motor::turnLeft() //左转 右加速
{
    motor_speed[0] = HIGH;
    motor_speed[1] = 110;
    motor_speed[2] = LOW;
    motor_speed[3] = 140;
}

bool Motor::Back() //后退
{
    //设定死区，即在后退过后的一个时间段内不重复后退
    if(millis() > last_time + 3000)
    {
        last_time = millis();

        motor_speed[0] = HIGH;
        motor_speed[1] = 180;
        motor_speed[2] = HIGH;
        motor_speed[3] = 180;

        back_count = 1;

        return true;
    }
    else
    {
        return false;
    }
}

void Motor::stright(int stright_speed) //直行
{
    back_count = 0;
    
    motor_speed[0] = LOW;
    motor_speed[1] = stright_speed;
    motor_speed[2] = LOW;
    motor_speed[3] = stright_speed;
}