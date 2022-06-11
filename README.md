# RoDEP Robocup Soccer Light League Robot's PltformIO Library
![](https://img.shields.io/badge/VSCode-PlatformIO-blue.svg?logo=visualstudiocode)

![](https://img.shields.io/badge/ArduinoIDE-Arduino_Uno-green.svg?logo=arduino)

![](https://img.shields.io/badge/ArduinoIDE-Arduino_Duemilanove-green.svg?logo=arduino)



> このレポジトリはRoDEPのRCJサッカーライトリーグのルールに基づいた部内技術向上のためのロボットのために使うライブラリです．
> 
>使用した基板は[このリポジトリ](https://github.com/rodep-soft/RoDEP-Soccer-Robot-Circuit/releases/tag/release-v1)に上がっています

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


## Author
Shun Kayaki

guetan[at]guetan.dev