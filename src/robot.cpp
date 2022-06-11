#include <Arduino.h>
#include "robot.h"
#include <Wire.h>

RoDEP_rcj_robot::RoDEP_rcj_robot(TwoWire &twi) : SCKlib(13), MISOlib(12), MOSIlib(11), SSlib(10), M1PWM(6), M2PWM(9), M3PWM(5), M4PWM(3)
{
    twi.begin();
    if (adc == nullptr)
    {
        adc = new Adafruit_MCP3008;
    }
    adc->begin(SCKlib, MOSIlib, MISOlib, SSlib);

    i2c = &twi;
}

void RoDEP_rcj_robot::update(bool ping)
{
    uint16_t data[8];
    readADC_AllCh(data);
    for (uint8_t i = 0; i < 4; i++)
    {
        LINE[i] = data[i];
    }
    for (uint8_t i = 4; i < 8; i++)
    {
        BALL[i - 4] = data[i];
    }
    if (ping)
    {
        uint8_t pingch[4] = {ping_ch1, ping_ch2, ping_ch3, ping_ch4};
        for (uint8_t i = 0; i < 4; i++)
        {
            PING[i] = read_ping((ping_ch_t)pingch[i]);
        }
    }
}

void RoDEP_rcj_robot::print_All_Sensors(void)
{
    Serial.print("[PING]");
    for (uint8_t i = 0; i < 4; i++)
    {
        Serial.print(PING[i]);
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
    uint8_t pcf = 0;
    m1 *= MOTOR_DIREC[0];
    m2 *= MOTOR_DIREC[1];
    m3 *= MOTOR_DIREC[2];
    m4 *= MOTOR_DIREC[3];
    if (m1 == 0)
    {
        pcf |= 0b1100;
    }
    else if (m1 > 0)
    {
        pcf |= 0b1000;
    }
    else if (m1 < 0)
    {
        pcf |= 0b0100;
    }
    if (m2 == 0)
    {
        pcf |= 0b11;
    }
    else if (m2 > 0)
    {
        pcf |= 0b10;
    }
    else if (m2 < 0)
    {
        pcf |= 0b01;
    }
    if (m3 == 0)
    {
        pcf |= 0b11000000;
    }
    else if (m3 > 0)
    {
        pcf |= 0b10000000;
    }
    else if (m3 < 0)
    {
        pcf |= 0b01000000;
    }
    if (m4 == 0)
    {
        pcf |= 0b110000;
    }
    else if (m4 > 0)
    {
        pcf |= 0b100000;
    }
    else if (m4 < 0)
    {
        pcf |= 0b010000;
    }
    set_PCF8574(pcf);
    set_pwm(motor_ch1, power2duty(m1));
    set_pwm(motor_ch2, power2duty(m2));
    set_pwm(motor_ch3, power2duty(m3));
    set_pwm(motor_ch4, power2duty(m4));
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
        Serial.println("ERROR[set_motor_direction] : invailed data");
        return;
    }
}

uint16_t RoDEP_rcj_robot::readADC(uint8_t ch)
{
    return adc->readADC(ch);
}

void RoDEP_rcj_robot::readADC_AllCh(uint16_t *data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        *data = readADC(i);
        data++;
    }
}

void RoDEP_rcj_robot::set_pwm(motor_ch_t motor_ch, uint8_t val)
{
    switch (motor_ch)
    {
    case motor_ch1:
        analogWrite(M1PWM, val);
        break;
    case motor_ch2:
        analogWrite(M2PWM, val);
        break;
    case motor_ch3:
        analogWrite(M3PWM, val);
        break;
    case motor_ch4:
        analogWrite(M4PWM, val);
        break;
    default:
        break;
    }
}

void RoDEP_rcj_robot::set_PCF8574(uint8_t io)
{
    // 3B3A4A4B1B1A2A2B
    i2c->beginTransmission(PCF_ADRESS);
    i2c->write(io);
    i2c->endTransmission();
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
