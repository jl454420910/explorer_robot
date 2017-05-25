
const int motor_pin[4] = {4, 3,  7,  8};//设定分别对应前左 前右 后左 后右

const int sensor_pin[2] = {A4, A0}; //依次为右， 左传感器

int sensor_datas;//存储传感器读取到的数据
bool motor_speeds[4]; 

int time_count = 0; //统计主循环次数

/*读取传感器数据*/
void readSensor(int i)
{ 
    int val; //临时变量  
    
    val = analogRead(sensor_pin[i]);
//    Serial.println(val);
//    Serial.println();
//    delay(10);

    //设定阀值
    if(val > 900)
    {
      val = 1;
    }
    else
    {
      val = 0;
    }

   //依次存储在sensor_datas对应位中
    sensor_datas = sensor_datas | (val << i);
}

/*运行电机*/
void runMotor() //分别对应前左 前右 后左 后右
{
        for(int i = 0; i < 4; i++)
        {
            digitalWrite(motor_pin[i], motor_speeds[i]);
            delay(1);
        }

//        for(int i = 4; i < 6; i++)
//        {  
//            digitalWrite(motor_pin[i], LOW);
//            delay(1);
//        }
        


  
//       analogWrite(motor_pin[0], motor_speed0);
//       analogWrite(motor_pin[1], motor_speed1);
//
////    if((time_count % motor_speed0) == 0)
////    {
////        digitalWrite(motor_pin[0], LOW);
////        delay(10);
////    }
////
////    if((time_count % motor_speed1) == 0)
////    {
////        digitalWrite(motor_pin[1], LOW);
////        delay(10);
////    }
//  
//
//    if((time_count % motor_speed2) == 0)
//    {
//        digitalWrite(motor_pin[2], LOW);
//        delay(10);
//    }
//
//    if((time_count % motor_speed3) == 0)
//    {
//        digitalWrite(motor_pin[3], LOW);
//        delay(10);
//    }
}

void setup()
{
  Serial.begin(9600);

  for(int i = 0; i < sizeof(motor_pin)/sizeof(int); i++)
  {
    pinMode(motor_pin[i],OUTPUT);
  }
  
  pinMode(sensor_pin[0],INPUT);
  pinMode(sensor_pin[1],INPUT);
}

void loop()
{
    sensor_datas = 0;
    for(int i = 0; i < 2; i++)
    {
      readSensor(i);
    }
//    Serial.println(sensor_datas);
//    Serial.println();

//    根据读取到的数值设定电机的速度
    switch(sensor_datas)
    {
      case 0x01: motor_speeds[0] = LOW;
                 motor_speeds[1] = HIGH;
                 motor_speeds[2] = LOW;
                 motor_speeds[3] = LOW;
                 break;
      
      case 0x02: motor_speeds[0] = HIGH;
                 motor_speeds[1] = LOW;
                 motor_speeds[2] = LOW;
                 motor_speeds[3] = LOW;
                 break;
      
      default:   motor_speeds[0] = LOW;
                 motor_speeds[1] = LOW;
                 motor_speeds[2] = LOW;
                 motor_speeds[3] = LOW;
    }

    runMotor();

//    time_count++;
//    if(time_count == 10000)
//    {
//      time_count = 0;
//    }
    
}
