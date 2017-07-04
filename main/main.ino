/*
 * 运行主程序
*/

//测试标志
#define nTEST

//远程控制标志
#define nREMOTE


#include "Motor.h"
#include "Sensor.h"

#include "Test.h"
#include "Remote.h"

//初始化电机对象
Motor myMotor;

//初始化传感器对象
Sensor mySensor(USE_FEEL);

#ifdef TEST
    Test test(USE_FEEL);
#endif

#ifdef REMOTE
    Remote myRemote;
#endif


void setup()
{     
    Serial.begin(9600);
    
    Serial.println("Connect success!");
}

void loop()
{  
    #ifdef TEST
        test.show(2000);
        return ;
    #endif

    #ifdef REMOTE
        myRemote.control();
    #endif   

    myMotor.run(mySensor.readBlack(), mySensor.getFeel());  
}
