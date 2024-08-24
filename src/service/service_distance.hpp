#ifndef DISTANCE_SERVICE_HPP
#define DISTANCE_SERVICE_HPP

#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "hardware/hardware_distance.hpp"

#include "Arduino.h"
#include "HardwareSerial.h"
#include <WString.h>
#include <stdint.h>

/*
 * @author: Haktan Serdar Genç
 * @date: 24.08.24
 * @file: distance service.
 */
class DistanceService : public CommService
{

private: // constant
  Package *p;
  Device *device = Global::getInstance().device;

  DistanceHardware *distanceHardware0;
  DistanceHardware *distanceHardware1;
  DistanceHardware *distanceHardware2;
  DistanceHardware *distanceHardware3;
  public:
  DistanceService() : CommService(1, 2) // constant
  {
    GatewayService::getInstance().subscribeService(this);
    DistanceHardware0 = new DistanceHardware(1,2); // pin tanımı şuanlık rastgele
    DistanceHardware1 = new DistanceHardware(3,4);
    DistanceHardware2 = new DistanceHardware(4,5);
    DistanceHardware3 = new DistanceHardware(5,6);

  }
  void service() override
  {
    Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 0, DistanceHardware0->read());
    p = new Package(_package.getContent());
    NetworkService::getInstance().send(p);
  };

  void handle(Package *package) override
  {

  };

  void response(String data) override {};

  ~DistanceService() {}
};

#endif  // DISTANCE_SERVICE_HPP
