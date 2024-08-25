#if !defined(SERVICE_DISTANCE_HPP)
#define SERVICE_DISTANCE_HPP

#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "../model/hardware/hardware_distance.hpp"
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

public:
  DistanceService() : CommService(1, 2) // constant
  {
    GatewayService::getInstance().subscribeService(this);
    distanceHardware0 = new DistanceHardware(3, 4);
    distanceHardware1 = new DistanceHardware(5, 6);
  }

  void service() override
  {
    String data = distanceHardware0->service();
    data.concat(";");
    data.concat(distanceHardware1->service());

    Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 0, data);
    Package _package0 = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, 2, 0, data);
    p = new Package(_package.getContent());
    NetworkService::getInstance().send(p);
    delete p;
    p = new Package(_package0.getContent());
    NetworkService::getInstance().send(p);
    delete p;
  }

  void handle(Package *package) override {}

  void response(String data) override {}

  ~DistanceService() {}
};

#endif // SERVICE_DISTANCE_HPP
