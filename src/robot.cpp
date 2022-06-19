#include <Arduino.h>
#include "robot.h"
#include <Wire.h>

RoDEP_rcj_robot::RoDEP_rcj_robot()
{
    for (uint8_t i = 0; i > 4; i++)
    {
        motors[i] = new AF_DCMotor(i + 1);
        motors[i]->setSpeed(0);
    }
}

void RoDEP_rcj_robot::update(bool ping)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        LINE[i] = analogRead(ADC_CH[i]);
    }
    for (uint8_t i = 4; i < 8; i++)
    {
        BALL[i - 4] = analogRead(ADC_CH[i]);
    }
    if (ping)
    {
        uint8_t pingch[4] = {ping_ch1, ping_ch2, ping_ch3, ping_ch4};
        for (uint8_t i = 0; i < 4; i++)
        {
            SONAR[i] = read_ping((ping_ch_t)pingch[i]);
        }
    }
}

void RoDEP_rcj_robot::print_All_Sensors(void)
{
    Serial.print("[PING]");
    for (uint8_t i = 0; i < 4; i++)
    {
        Serial.print(SONAR[i]);
        Serial.print(", ");
    }
    Serial.print("[LINE]");
    for (uint8_t i = 0; i < 4; i++)
    {
        Serial.print(LINE[i]);
        Serial.print(", ");
    }
    Serial.print("[BALL]");
    for (uint8_t i = 0; i < 4; i++)
    {
        Serial.print(BALL[i]);
        Serial.print(", ");
    }
    Serial.print("\n\r");
}

void RoDEP_rcj_robot::set_speed(float m1, float m2, float m3, float m4)
{
    m1 = power2duty(m1) * MOTOR_DIREC[0];
    m2 = power2duty(m2) * MOTOR_DIREC[1];
    m3 = power2duty(m3) * MOTOR_DIREC[2];
    m4 = power2duty(m4) * MOTOR_DIREC[3];

    if (m1 < 0)
    {
        motors[0]->run(BACKWARD);
    }
    else
    {
        motors[0]->run(FORWARD);
    }
    if (m2 < 0)
    {
        motors[1]->run(BACKWARD);
    }
    else
    {
        motors[1]->run(FORWARD);
    }
    if (m3 < 0)
    {
        motors[2]->run(BACKWARD);
    }
    else
    {
        motors[2]->run(FORWARD);
    }
    if (m4 < 0)
    {
        motors[3]->run(BACKWARD);
    }
    else
    {
        motors[3]->run(FORWARD);
    }
    motors[0]->setSpeed(abs(m1));
    motors[1]->setSpeed(abs(m2));
    motors[2]->setSpeed(abs(m3));
    motors[3]->setSpeed(abs(m4));
}

void RoDEP_rcj_robot::set_motor_direction(int8_t m1, int8_t m2, int8_t m3, int8_t m4)
{
    if (((abs(m1) == 1) && (abs(m2) == 1)) && ((abs(m3) == 1) && (abs(m4) == 1)))
    {
        MOTOR_DIREC[0] = m1;
        MOTOR_DIREC[1] = m2;
        MOTOR_DIREC[2] = m3;
        MOTOR_DIREC[3] = m4;
    }
    else
    {
        Serial.println("ERROR[set_motor_direction] : invalid data");
        return;
    }
}

float RoDEP_rcj_robot::read_ping(ping_ch_t ch)
{
    pinMode(ch, OUTPUT);
    digitalWrite(ch, LOW);
    delayMicroseconds(2);
    digitalWrite(ch, HIGH);
    delayMicroseconds(5); //超音波発信
    digitalWrite(ch, LOW);
    pinMode(ch, INPUT);
    digitalWrite(ch, HIGH);
    int16_t data = pulseIn(ch, HIGH);
    return (float)data / 2 * 0.034442;
}
