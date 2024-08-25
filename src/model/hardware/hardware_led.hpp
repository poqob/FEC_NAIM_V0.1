#if !defined(HARDWARE_LED_HPP)
#define HARDWARE_LED_HPP
#include "../../../lib/network/service/hardware_service.hpp" // Ensure this path is correct

/*
 * @author: Mustafa BICER
 * @date: 25.08.24
 * @file: hardware_led.hpp
 * @description: This is a led hardware service. Useful for basic testing purposes.
 */

class LedHardware
{
private:
    uint8_t pin;
    bool state;

public:
    LedHardware::LedHardware(uint8_t pin)
    {
        pinMode(pin, OUTPUT);
        this->pin = pin;
        this->state = false;
    }

    bool toggle()
    {
        state = !state;
        digitalWrite(pin, state);
        return state;
    }

    void on()
    {
        state = true;
        digitalWrite(pin, state);
    }

    void off()
    {
        state = false;
        digitalWrite(pin, state);
    }

    LedHardware::~LedHardware() {}
};

#endif // HARDWARE_LED_HPP
