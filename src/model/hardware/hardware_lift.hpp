#ifndef LIFT_HARDWARE_HPP
#define LIFT_HARDWARE_HPP

#include "../../../lib/network/service/hardware_service.hpp" // Ensure this path is correct
#include "HardwareSerial.h"

/*
 * @author: Haktan Serdar Genç
 * @date: 24.08.24
 * @file: lift hardware.
 */

class LiftHardware : public HardwareService
{
private:
    uint8_t RPWM;
    uint8_t REN;
    uint8_t LPWM;
    uint8_t LEN;
    bool liftStatus;

public:
    void lift(bool liftStatus)
    {
        if (liftStatus == 1) // Lift Açılması
        {
            analogWrite(RPWM, 255);
            analogWrite(LPWM, 0);
            digitalWrite(REN, HIGH);
            digitalWrite(LEN, HIGH);
        }
        else // Lift Kapanması
        {
            analogWrite(LPWM, 255);
            analogWrite(RPWM, 0);
            digitalWrite(REN, HIGH);
            digitalWrite(LEN, HIGH);
        }
    }

    ~LiftHardware() {}
    LiftHardware(uint8_t RPWM, uint8_t REN, uint8_t LPWM, uint8_t LEN)
        : HardwareService(), RPWM(RPWM), REN(REN), LPWM(LPWM), LEN(LEN), liftStatus(false)
    {
        pinMode(RPWM, OUTPUT);
        pinMode(REN, OUTPUT);
        pinMode(LPWM, OUTPUT);
        pinMode(LEN, OUTPUT);

        digitalWrite(REN, HIGH);
        digitalWrite(LEN, HIGH);
    }
};

#endif // LIFT_HARDWARE_HPP
