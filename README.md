# RoDEP Robocup Soccer Light League Robot's PltformIO Library
![](https://img.shields.io/badge/VSCode-PlatformIO-blue.svg?logo=visualstudiocode)

![](https://img.shields.io/badge/ArduinoIDE-Arduino_Uno-green.svg?logo=arduino)

![](https://img.shields.io/badge/ArduinoIDE-Arduino_Duemilanove-green.svg?logo=arduino)



> このレポジトリはRoDEPのRCJサッカーライトリーグのルールに基づいた部内技術向上のためのロボットのために使うライブラリです．
> 
>使用した回路図は[これ](https://github.com/rodep-soft/RoDEP-Soccer-Robot-Circuit/blob/master/Adafruit-Shield.png)です．
## 使用部品
Adafruit Motor Shield v2.3  
https://akizukidenshi.com/catalog/g/gK-07748/

## Dependency
adafruit/Adafruit Motor Shield library@^1.0.1

## ピン接続
A5 : SDA (Adafruit Shield)  
A4 : SCL (Adafruit Shield)  

A8 : BALL1  
A9 : BALL2  
A10 : BALL3  
A11 : BALL4  
A12 : LINE1  
A13 : LINE2  
A14 : LINE3  
A15 : LINE4

16 : PING1  
17 : PING2  
18 : PING3  
19 : PING4  
20 : SDA  
21 : SCL  

# Usage

## 開発方法
Arduino IDEおよびVSCodeにPlatformIOを導入しての開発


## ロボットのすべてのセンサを確認するプログラム
```cpp
#include <Arduino.h>
#include "robot.h"

RoDEP_rcj_robot robot();

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    robot.update(true);
    robot.print_All_Sensors();
}
```

# 使用基板

# dependent library
adafruit/Adafruit Motor Shield library@^1.0.1


## Author
Shun Kayaki

guetan[at]guetan.dev