#if !defined(HARDWARE_LED_HPP)
#define HARDWARE_LED_HPP
#include "../../../lib/network/service/hardware_service.hpp" // Ensure this path is correct

/*
 * @author: Mustafa BICER
 * @date: 5.9.24
 * @file: hardware_buzzer.hpp
 * @description: Buzzer.
 */

class BuzzerHardware
{
private:
    uint8_t pin;
    bool state;

public:
    BuzzerHardware(uint8_t pin)
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

    ~BuzzerHardware() {}
};

#endif // HARDWARE_LED_HPP
