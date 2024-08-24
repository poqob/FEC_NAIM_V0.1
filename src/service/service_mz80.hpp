#include <stdint.h>
#include "Arduino.h"
#ifndef MZ80_SERVICE_HPP
#define MZ80_SERVICE_HPP
#include "HardwareSerial.h"
#include "model_packet.hpp"
#include "service_lineer_motor.hpp"
/*
 * @author: Mustafa BICER
 * @date: 28.07.24
 * @file: MZ80  service.
 */

class Mz80Service
{
private:
  int value;
  bool newPackage;
  bool listen;
  LineerMotorService *lineerMotorService = LineerMotorService::getInstance();

  // PACKET DESIGN PATTERN
private:
  void sendPackage()
  {
    Packet _packet;
    _packet = Packet("ard", "mz", 1, "0");
    lineerMotorService->receivePackage(_packet);
  }

  void receivePackage()
  {
  }

public:
  
  void setup()
  {
    listen = false;
    newPackage = false;
    
    //pinMode(mz80->getPin(), INPUT);
  }

  void service()
  {
    value = digitalRead(28);
    if (value == 0) // dedector
      sendPackage();
  }

  Mz80Service()
  {
  }

  ~Mz80Service() {}
};
#endif // MZ80_SERVICE_HPP
