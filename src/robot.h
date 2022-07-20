#ifndef RODEP_RCJ_ROBOT_LIBRARY
#define RODEP_RCJ_ROBOT_LIBRARY
#include <Arduino.h>
#include <Adafruit_MCP3008.h>
#include <stdint.h>
#include <Wire.h>

// ALT1~ALT4は未使用

class RoDEP_rcj_robot
{
public:
    RoDEP_rcj_robot(TwoWire &twi = Wire);                                 // initialize
    void update(bool ping = false);                                       //センサ情報を更新する
    void print_All_Sensors(void);                                         //センサ情報を確認する
    void set_speed(float m1, float m2, float m3, float m4);               //モーターのパワーを設定する．[Range]: -MAX_power ~ MAX_power
    void set_motor_direction(int8_t m1, int8_t m2, int8_t m3, int8_t m4); //モーターのパワーの正負を設定する． 1 or -1を代入すること [default]:1,1,1,1
    uint16_t LINE[4];                                                     //[Unit]: None [Range]: 0~1023(10bit)
    uint16_t BALL[4];                                                     //[Unit]: None [Range]: 0~1023(10bit)
    float PING_DISTANCE[4];                                                        //[Unit]: cm

private:
    typedef enum
    {
        motor_ch1,
        motor_ch2,
        motor_ch3,
        motor_ch4
    } motor_ch_t;
    typedef enum
    {
        ping_ch1 = 7,
        ping_ch2 = 8,
        ping_ch3 = 2,
        ping_ch4 = 4
    } ping_ch_t;
    int8_t MOTOR_DIREC[4] = {1, 1, 1, 1};    //モーターの向き　-1 or 1のみを設定すること
    uint8_t SCKlib, MISOlib, MOSIlib, SSlib; // for MCP3008 on SPI bus
    uint8_t M1PWM, M2PWM, M3PWM, M4PWM;
    Adafruit_MCP3008 *adc;
    uint8_t PCF_ADRESS = 0b00100111; // Address for PCF8574F on I2C bus
    TwoWire *i2c;
    const float MAX_power = 1.0;

    uint16_t readADC(uint8_t ch);                   // MCP3008から任意のchのデータをとってくる関数
    void readADC_AllCh(uint16_t *data);             // MCP3008のすべてのchのデータをとってくる関数
    void set_pwm(motor_ch_t motor_ch, uint8_t val); // TB6612FNGの任意のchのPWMピンにpwmを印加する関数
    void set_PCF8574(uint8_t io);                   // TB6612FNGのINA,INBを管理しているPCF8574に書き込む関数
    uint8_t power2duty(float p)                     //モーターのユーザーが設定する速度からdutyに変換する関数，非線形にするならここを弄る
    {
        return (p / MAX_power) * 255;
    }
    float read_ping(ping_ch_t ch); //超音波センサを読み込む関数
};

#endif