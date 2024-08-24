#ifndef MZ80_HARDWARE_HPP
#define MZ80_HARDWARE_HPP

#include "../../../lib/network/service/hardware_service.hpp"
#include "HardwareSerial.h"

/*
 * @author: Haktan Serdar Genç
 * @date: 24.08.24
 * @file: motor service.
 */
class Mz80Hardware : public HardwareService
{
private:
  uint8_t value = 255;
  uint8_t pin;

public:
  String service()
  {
    value = digitalRead(pin);
    if (value == 1)
      return "1";
    else if (value == 0)
      return "0";
    else
      return String(value);
  }

  Mz80Hardware(int pin)
      : HardwareService(), pin(pin), value(0)
  {
    pinMode(pin, INPUT_PULLUP); // TODO: INPUT_PULLUP
  }

  ~Mz80Hardware() {}
};
#endif // Mz80_HARDWARE_HPP
