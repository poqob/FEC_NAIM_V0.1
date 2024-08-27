#ifndef QTR_HARDWARE_HPP
#define QTR_HARDWARE_HPP

#include "../../../lib/network/service/hardware_service.hpp" // Ensure this path is correct
#include "HardwareSerial.h"

/*
 * @author: Haktan Serdar Genç
 * @date: 24.08.24
 * @file: qtr hardware.
 */

class QtrHardware : public HardwareService
{
private:
    int sensor1Pin;
    int sensor2Pin;
    int sensor3Pin;
    int sensor4Pin;
    int sensor5Pin;
    int sensor6Pin;
    int sensor7Pin;
    int sensor8Pin;

    int sensor1Value;
    int sensor2Value;
    int sensor3Value;
    int sensor4Value;
    int sensor5Value;
    int sensor6Value;
    int sensor7Value;
    int sensor8Value;

public:
    String Qtr()
    {
        sensor1Value = analogRead(sensor1Pin);
        sensor2Value = analogRead(sensor2Pin);
        sensor3Value = analogRead(sensor3Pin);
        sensor4Value = analogRead(sensor4Pin);
        sensor5Value = analogRead(sensor5Pin);
        sensor6Value = analogRead(sensor6Pin);
        sensor7Value = analogRead(sensor7Pin);
        sensor8Value = analogRead(sensor8Pin);
    }
    
    ~QtrHardware() {}
    QtrHardware(int sensor1Pin, int sensor2Pin, int sensor3Pin, int sensor4Pin, int sensor5Pin, int sensor6Pin, int sensor7Pin, int sensor8Pin)
        : HardwareService(), sensor1Pin(sensor1Pin), sensor2Pin(sensor2Pin), sensor3Pin(sensor3Pin), sensor4Pin(sensor4Pin), sensor5Pin(sensor5Pin), sensor6Pin(sensor6Pin), sensor6Pin(sensor6Pin), sensor7Pin(sensor7Pin)
};

#endif // QTR_HARDWARE_HPP
