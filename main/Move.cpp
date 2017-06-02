/*
 * 电机控制库
*/

#include "Move.h"

Move::Move():
motor_pin{9, 10,  5,  6}, 
motor_speed
{
    {LOW, 110, LOW, 110},  //直行
    {HIGH, 10, LOW, 240},  //左转
    {LOW, 250, HIGH, 0},  //右转
    {LOW, 250, LOW, 250},  //加速直行
    {HIGH, 100, HIGH, 100}, //后退
    {LOW, 0, LOW, 0}, //后退
},
black_start_time(0), speed_up_dur(0), last_back_time(0)
{
    for(int i = 0; i < sizeof(motor_pin)/sizeof(int); i++)
    {        
        pinMode(motor_pin[i], OUTPUT);
    }
}

/*运行电机*/
void Move::runMotor(int mode, boolean feel)
{
//    Serial.println(mode);
    
    //转弯前先后退, 并设定死区，即在后退过后的一个时间段内不重复后退
    if((mode == LEFT || mode == RIGHT) && (millis() > last_back_time + 1000))
    {   
//        Serial.println("back");
        
        runMotor(BACK, feel);
        last_back_time = millis();
    }
    
    //根据连续检测到黑线的持续时间决定是否加速
    if(mode == SPEED_UP)
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
        
        mode = STRIGHT;
    }
    else
    {
        black_start_time = 0;
    }
    
    //触须感应到障碍物则加速
    if(feel)
    {
//        Serial.println("feel");

        if(millis() > last_back_time + 8000)
        {
            runMotor(BACK, false);
            delay(1000);
        }
        
        
        last_back_time = millis();
        speed_up_dur = 2000;
    }
    
    if(speed_up_dur > 0 && mode != LEFT && mode != RIGHT)
    {
//        Serial.println("speed_up");
        
        speed_up_dur--;
        mode = SPEED_UP;
    }

//    Serial.print("mode:");
//    Serial.println(mode);
    
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

