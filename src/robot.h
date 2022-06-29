#ifndef RODEP_RCJ_ROBOT_LIBRARY
#define RODEP_RCJ_ROBOT_LIBRARY
#include <Arduino.h>
#include <stdint.h>
#include <AFMotor.h>

/*
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
*/

class RoDEP_rcj_robot
{
public:
    RoDEP_rcj_robot();                                                    // initialize
    void update(bool ping = false);                                       //センサ情報を更新する
    void print_All_Sensors(void);                                         //センサ情報を確認する
    void set_speed(float m1, float m2, float m3, float m4);               //モーターのパワーを設定する．[Range]: -MAX_power ~ MAX_power
    void set_motor_direction(int8_t m1, int8_t m2, int8_t m3, int8_t m4); //モーターのパワーの正負を設定する． 1 or -1を代入すること [default]:1,1,1,1
    uint16_t LINE[4];                                                     //[Unit]: None [Range]: 0~1023(10bit)
    uint16_t BALL[4];                                                     //[Unit]: None [Range]: 0~1023(10bit)
    float SONAR[4];                                                       //[Unit]: cm

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
        ping_ch1 = 16,
        ping_ch2,
        ping_ch3,
        ping_ch4
    } ping_ch_t;
    typedef enum
    {
        line_ch1 = 66,
        line_ch2,
        line_ch3,
        line_ch4
    } line_ch_t;
    typedef enum
    {
        ball_ch1 = 62,
        ball_ch2,
        ball_ch3,
        ball_ch4
    } ball_ch_t;

    uint16_t ADC_CH[8] = {line_ch1, line_ch2, line_ch3, line_ch4, ball_ch1, ball_ch2, ball_ch3, ball_ch4};

    int8_t MOTOR_DIREC[4] = {1, 1, 1, 1}; //モーターの向き　-1 or 1のみを設定すること
    AF_DCMotor *motors[4];
    const float MAX_power = 1.0;

    uint8_t power2duty(float p) //モーターのユーザーが設定する速度からdutyに変換する関数，非線形にするならここを弄る
    {
        return (p / MAX_power) * 255;
    }
    float read_ping(ping_ch_t ch); //超音波センサを読み込む関数
};

#endif