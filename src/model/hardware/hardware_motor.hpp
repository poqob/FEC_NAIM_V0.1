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
    uint8_t Velocity;

public:
    String Motor()
{
    pinMode(RPWM, OUTPUT);  
    pinMode(REN, OUTPUT);   
    pinMode(LPWM, OUTPUT);  
    pinMode(LEN, OUTPUT);   
    
    digitalWrite(REN, HIGH);
    digitalWrite(LEN, HIGH);
    
    if (Velocity >= 0)
    {
        analogWrite(RPWM, Velocity);
        digitalWrite(REN, HIGH);
        digitalWrite(LEN, HIGH);  
    }
    else
    {
        InverseVelocity = Velocity * -1;  
        analogWrite(LPWM, InverseVelocity);  
        digitalWrite(REN, HIGH);  
        digitalWrite(LEN, HIGH);
    }
    
    return "";  
}

    ~MotorHardware() {}
    MotorHardware(uint8_t RPWM, uint8_t REN, uint8_t LPWM, uint8_t LEN, uint8_t Velocity)
        : HardwareService(), RPWM(RPWM), REN(REN), LPWM(LPWM), LEN(LEN), Veloctiy(Velocity)
};

#endif // MOTOR_HARDWARE_HPP
