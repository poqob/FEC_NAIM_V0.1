#ifndef MZ80_SERVICE_HPP
#define MZ80_SERVICE_HPP

#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "hardware/hardware_mz80.hpp"

#include <stdint.h>
#include "Arduino.h"
#include "HardwareSerial.h"
/*
 * @author: Haktan Serdar Genç
 * @date: 28.07.24
 * @file: MZ80  service.
 */

class Mz80Service : public CommService
{
  private: // constant
  Package *p;
  Device *device = Global::getInstance().device;

  Mz80Hardware *mz80Hardware0;
  Mz80Hardware *mz80Hardware1;
  Mz80Hardware *mz80Hardware2;
  Mz80Hardware *mz80Hardware3;
  public:
  DistanceService() : CommService(1, 3) // constant
  {
    GatewayService::getInstance().subscribeService(this);
    Mz80Hardware0 = new Mz80Hardware(10); // pin tanımı şuanlık rastgele
    Mz80Hardware1 = new Mz80Hardware(11);
    Mz80Hardware2 = new Mz80Hardware(12);
    Mz80Hardware3 = new Mz80Hardware(13);

  }
  void service() override
  {
    Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 0, Mz80Hardware0->read());
    p = new Package(_package.getContent());
    NetworkService::getInstance().send(p);
  };

  void handle(Package *package) override
  {

  };

  void response(String data) override {};

  ~DistanceService() {}
};

#endif // MZ80_SERVICE_HPP
