#ifndef MOTOR_HARDWARE_HPP
#define MOTOR_HARDWARE_HPP

#include "../../../lib/network/service/hardware_service.hpp" // Ensure this path is correct
#include "HardwareSerial.h"

/*
 * @author: Haktan Serdar Genç
 * @date: 24.08.24
 * @file: motor hardware.
 */

class MotorHardware : public HardwareService
{
private:
    uint8_t RPWM;
    uint8_t REN;
    uint8_t LPWM;
    uint8_t LEN;
    int velocity;
    int inverseVelocity;

public:
    void motor(int velocity)
    {
        if (velocity >= 0)
        {
            analogWrite(RPWM, velocity);
            digitalWrite(REN, HIGH);
            digitalWrite(LEN, HIGH);
        }
        else
        {
            inverseVelocity = velocity * -1;
            analogWrite(LPWM, inverseVelocity);
            digitalWrite(REN, HIGH);
            digitalWrite(LEN, HIGH);
        }
    }

    ~MotorHardware() {}
    MotorHardware(uint8_t RPWM, uint8_t REN, uint8_t LPWM, uint8_t LEN)
        : HardwareService(), RPWM(RPWM), REN(REN), LPWM(LPWM), LEN(LEN)
    {
        pinMode(RPWM, OUTPUT);
        pinMode(REN, OUTPUT);
        pinMode(LPWM, OUTPUT);
        pinMode(LEN, OUTPUT);
        digitalWrite(REN, HIGH);
        digitalWrite(LEN, HIGH);
    }
};

#endif // MOTOR_HARDWARE_HPP
