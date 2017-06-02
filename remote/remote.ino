/*
功能：红外遥控器控制LED灯　开,关,闪烁,呼吸
元件：
    红外接收管，红外遥控
接线：
    红外灯面向自己从左到右分别接 IO3 ,GND ,5V
    LED 负极接GND 正极串联电阻接 IO5
红外遥控器键盘1-9编码：
FF30CF    １
FF18E7    ２
FF7A85    ３
FF10EF    ４
FF38C7    ５
FF5AA5    ６
FF42BD    ７
FF4AB5    ８
FF52AD    ９
*/

#include <IRremote.h>

int ledPin = 12;
int recvPin = 3;//定义红外接收器的引脚为3
IRrecv irrecv(recvPin);
decode_results results;

long KEY_CODE_ONE = 0xFF30CF;
long KEY_CODE_TWO = 0xFF18E7;
long KEY_CODE_THREE = 0xFF7A85;
long KEY_CODE_FOUR = 0xFF10EF;
long KEY_CODE_LONG_PRESS = 0xFFFFFFFF;
long longPressKey = -1; //长按下的那个键

void setup() {
  pinMode(ledPin, OUTPUT);
  irrecv.enableIRIn(); // 初始化红外接收器
  Serial.begin(9600);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);//以16进制换行输出接收代码
    Serial.println();//为了便于观看输出结果增加一个空行
    irrecv.resume(); // 接收下一个值
  }

  //按下１键的事件
  if (results.value == KEY_CODE_ONE ) {
    ledOn(ledPin);
    longPressKey = KEY_CODE_ONE;
  }
  //长按１键的事件
  if ( results.value == KEY_CODE_LONG_PRESS && longPressKey == KEY_CODE_ONE) {
    ledOn(ledPin);
  }

  //按下２键的事件
  if (results.value == KEY_CODE_TWO ) {
    ledOff(ledPin);
    longPressKey = KEY_CODE_TWO;
  }
  //长按 ２键的事件
  if ( results.value == KEY_CODE_LONG_PRESS && longPressKey == KEY_CODE_TWO) {
    ledOff(ledPin);
  }
  //按下 3 键的事件
  if (results.value == KEY_CODE_THREE ) {
    flash(ledPin, 100, 100);
    longPressKey = KEY_CODE_THREE;
  }
  //长按 3 键的事件
  if ( results.value == KEY_CODE_LONG_PRESS && longPressKey == KEY_CODE_THREE) {
    flash(ledPin, 100, 100);
  }
  //按下 4 键的事件
  if (results.value == KEY_CODE_FOUR ) {
    fadeOn(1000, 5);
    fadeOff(1000, 5);
    longPressKey = KEY_CODE_FOUR;
  }
  //长按 4 键的事件
  if ( results.value == KEY_CODE_LONG_PRESS && longPressKey == KEY_CODE_FOUR) {
    fadeOn(1000, 5);
    fadeOff(1000, 5);
  }
}

// led亮灯
void ledOn(int ledPin) {
  digitalWrite(ledPin, HIGH);
}
// led熄灯
void ledOff(int ledPin) {
  digitalWrite(ledPin, LOW);
}
//led闪烁
void flash(int ledPin, long highDuration, long lowDuration) {
  digitalWrite(ledPin, HIGH);
  delay(highDuration);
  digitalWrite(ledPin, LOW);
  delay(lowDuration);
}
//呼吸灯On
void fadeOn(unsigned int time, int increament) {
  for (byte value = 0 ; value < 255; value += increament) {
    Serial.println(value);
    analogWrite(ledPin, value);
    delay(time / (255 / 5));
  }
}
//呼吸灯Off
void fadeOff(unsigned int time, int decreament) {
  for (byte value = 255; value > 0; value -= decreament) {
    Serial.println(value);
    analogWrite(ledPin, value);
    delay(time / (255 / 5));
  }
}
