#ifndef MZ80_SERVICE_HPP
#define MZ80_SERVICE_HPP

#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "../model/hardware/hardware_mz80.hpp"
#include <stdint.h>
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
  Mz80Service(uint8_t group, uint8_t id) : CommService(group, id)
  {
    GatewayService::getInstance().subscribeService(this);
    mz80Hardware0 = new Mz80Hardware(12); // pin tanımı şuanlık rastgele
    // mz80Hardware1 = new Mz80Hardware(11);
    // mz80Hardware2 = new Mz80Hardware(12);
    // mz80Hardware3 = new Mz80Hardware(13);
  }
  void service() override
  {
    String data = mz80Hardware0->service();
    if (data == "1")
      return;
    Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 0, data);
    p = new Package(_package.getContent());
    Serial.println(p->getContent());
    NetworkService::getInstance().send(p);
    delete p;
  };

  void handle(Package *package) override {

  };

  void response(String data) override {};

  ~Mz80Service() {}
};

#endif // MZ80_SERVICE_HPP
