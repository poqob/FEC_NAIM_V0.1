#ifndef MOTOR_HARDWARE_HPP
#define MOTOR_HARDWARE_HPP

#include "../../../lib/network/service/hardware_service.hpp" // Ensure this path is correct
#include "HardwareSerial.h"

/*
 * @author: Mustafa BICER
 * @date: 24.08.24
 * @file: motor service.
 * @description: This is an example service for motor. A service that transmits data to motor.
 */

class MotorHardware : public HardwareService
{
private:
    String name;

public:
    // Constructor with name parameter
    MotorHardware(String i) : HardwareService(), name(i) {}

    // Function to send service data to the motor
    void service(String data)
    {
        Serial.print("Motor Hardware ");
        Serial.print(name + " ");
        Serial.println(data);
    }

    String read()
    {
        return "motor " + name + " dataread()";
    }

    // Setup function
    void setup() {}

    // Destructor
    ~MotorHardware() {}
};

#endif // MOTOR_HARDWARE_HPP
