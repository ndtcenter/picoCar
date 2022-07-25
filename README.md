# picoCar
适用于RPI Pico的Arduino框架开发的智能小车

添加了几个项目用于基本测试。

## 基础blink测试

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

## 增加toggle操作
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
