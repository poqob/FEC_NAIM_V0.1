#ifndef MZ80_HARDWARE_HPP
#define MZ80_HARDWARE_HPP

#include "../../../lib/network/service/hardware_service.hpp" 
#include "HardwareSerial.h"

/*
 * @author: Haktan Serdar Genç
 * @date: 24.08.24
 * @file: motor service.
 */
class Mz80Hardware : public Mz80Service
{
private:
  int value;
  bool listen;
  int pin;
  bool engelvar;

  Mz80Hardware(int pin) 
    : Mz80Service(), pin(pin), value(0), listen(false) {}

  void setup()
  {
    listen = false;
    pinMode(pin, INPUT);
  }
  void mzkontrol()
  {
    value = digitalRead(pin); 
    if (value == 0) {
     engelvar = true;
    }
    else{
     engelvar = false;
    }
    
  }
  String read()
    {
        return Bool (engelvar);
    }

  ~Mz80Hardware() {}
};
#endif // Mz80_HARDWARE_HPP
