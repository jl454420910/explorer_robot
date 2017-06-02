#include "MoveServo.h"

const int servo_pin[] = {4, 7, 11,  3, 8, 12};//设定分别对应左, 右两对各三个轮
const int servo_speed[] = {10, 10, 10, 170, 170, 170};

void setup()
{
  for(int i = 0; i < sizeof(servo_pin)/sizeof(int); i++)
  {
    pinMode(servo_pin[i],OUTPUT);
  }
}

void loop()
{
    for(int i = 0; i < 3; i++)
    {
        servoPulse(servo_pin[i], servo_speed[i]); 
    }

    for(int i = 3; i < 6; i++)
    {
        servoPulse(servo_pin[i], servo_speed[i]); 
    }
}
