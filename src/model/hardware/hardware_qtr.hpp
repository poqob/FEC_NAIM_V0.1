#ifndef QTR_HARDWARE_HPP
#define QTR_HARDWARE_HPP

#include "../../../lib/network/service/hardware_service.hpp" // Ensure this path is correct
#include "HardwareSerial.h"
#include "Arduino.h"

/*
 * @author: Haktan Serdar Genç
 * @date: 24.08.24
 * @file: qtr hardware.
 */

class QtrHardware : public HardwareService
{
private:
    int sensor1Value;
    int sensor2Value;
    int sensor3Value;
    int sensor4Value;
    int sensor5Value;
    int sensor6Value;
    int sensor7Value;
    int sensor8Value;

    // Ağırlıklar (bu örnekte 1'den 8'e kadar sıralı)
    int weights[8] = {1, 2, 3, 4, 5, 6, 7, 8};

public:
    QtrHardware()
        : HardwareService() {}

    ~QtrHardware() {}

    String qtr()
    {
        sensor1Value = analogRead(A1);
        sensor2Value = analogRead(A2);
        sensor3Value = analogRead(A3);
        sensor4Value = analogRead(A4);
        sensor5Value = analogRead(A5);
        // sensor6Value = analogRead(A6);
        // sensor7Value = analogRead(A7);
        // sensor8Value = analogRead(A8);

        // Sensor değerlerini bir diziye koy
        int sensorValues[5] = {sensor1Value, sensor2Value, sensor3Value, sensor4Value, sensor5Value}; // sensor6Value, sensor7Value, sensor8Value

        // Ağırlıklı toplamı hesapla
        long weightedSum = 0;
        int totalWeights = 0;
        for (int i = 0; i < 5; ++i) // TODO: 8
        {
            weightedSum += sensorValues[i] * weights[i];
            totalWeights += weights[i];
        }

        // Ağırlıklı ortalamayı hesapla
        float weightedAverage = (float)weightedSum / totalWeights;

        // Sonuçları formatlayıp döndür
        String result = "Weighted Average: " + String(weightedAverage);
        return String(weightedAverage);
    }
};
#endif // QTR_HARDWARE_HPP
