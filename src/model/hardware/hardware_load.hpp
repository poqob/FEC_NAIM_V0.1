#ifndef LOAD_HARDWARE_HPP
#define LOAD_HARDWARE_HPP

#include "../../../lib/network/service/hardware_service.hpp" // Ensure this path is correct
#include "HardwareSerial.h"

/*
 * @author: Haktan Serdar Genç
 * @date: 24.08.24
 * @file: load hardware.
 */

class LoadHardware : public HardwareService
{
private:
    uint8_t HX711_DATA_PIN; // HX711 DATA pini
    uint8_t HX711_CLOCK_PIN;    // HX711 CLOCK pini
    long offset = 0;        // Kalibrasyon Sonucuna Göre Yazılacak
    float scale = 1;        // Kalibrasyon Sonucuna Göre Yazılacak

public:
    String Load()
    {
        pinMode(HX711_CLOCK_PIN, OUTPUT);
        pinMode(HX711_DATA_PIN, INPUT);

        long readHX711()
        {
            long count = 0;
            while (digitalRead(HX711_DATA_PIN))
                ;

            for (uint8_t i = 0; i < 24; i++)
            {
                digitalWrite(HX711_CLOCK_PIN, HIGH);
                count = count << 1;
                digitalWrite(HX711_CLOCK_PIN, LOW);
                if (digitalRead(HX711_DATA_PIN))
                {
                    count++;
                }
            }

            digitalWrite(HX711_CLOCK_PIN, HIGH);
            digitalWrite(HX711_CLOCK_PIN, LOW);

            count ^= 0x800000;

            return count;
        }

        long value = readHX711();
        float weight = (value - offset) / scale;
        return "weight";
    }
    
    ~LoadHardware() {}
    LoadHardware(uint8_t HX711_DATA_PIN, uint8_t HX711_CLOCK_PIN)
        : HardwareService(), HX711_DATA_PIN(HX711_DATA_PIN), HX711_CLOCK_PIN(HX711_CLOCK_PIN)
};

#endif // LOAD_HARDWARE_HPP
