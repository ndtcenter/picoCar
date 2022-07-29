# picoCar
适用于RPI Pico的Arduino框架开发的智能小车

添加了几个项目用于基本测试。

## 基础blink测试
```
#include <Arduino.h>

int led = 25;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
}
```
## 增加toggle操作
```
#include <Arduino.h>

int led = 25;

void digitalToggle(int pin){
  digitalWrite(pin,!digitalRead(pin));
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalToggle(led);
  delay(500);
}
```
## 增加对输出端口的类封装
```
#include <Arduino.h>

class DigitalOut
{
public:
  DigitalOut(int pin) : _pin(pin)
  {
    pinMode(pin, OUTPUT);
  }

  DigitalOut(int pin, int value) : _pin(pin)
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, value);
  }

  void write(int value)
  {
    digitalWrite(_pin, value);
  }

  int read()
  {
    return digitalRead(_pin);
  }

  DigitalOut &operator=(int value)
  {
    write(value);
    return *this;
  }

  friend int operator!(DigitalOut &rhs)
  {
    return !rhs.read();
  }

  DigitalOut &operator=(DigitalOut &rhs);

  operator int()
  {
    return read();
  }

protected:
  int _pin;
};

DigitalOut led(25);

void setup()
{
  // put your setup code here, to run once:
}

// loop 示例 1
void loop()
{
  // put your main code here, to run repeatedly:
  delay(200);
  led = 1;
  delay(200);
  led = 0;
}

// loop 示例 2
// void loop()
// {
//   // put your main code here, to run repeatedly:
//   delay(200);
//   led = !led;  
// }
```

