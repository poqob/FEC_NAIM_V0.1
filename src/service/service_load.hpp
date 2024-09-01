#ifndef LOAD_SERVICE_HPP
#define LOAD_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "../model/hardware/hardware_load.hpp"

/*
 * @author: Haktan Serdar Genç
 * @date: 27.08.24
 * @file: load service.
 */

class LoadService : public CommService
{

private: // constant
  Package *p;
  Device *device = Global::getInstance().device;

  LoadHardware *loadHardware1;

public:
  LoadService(uint8_t group, uint8_t id) : CommService(group, id)
  {
    GatewayService::getInstance().subscribeService(this);
    loadHardware1 = new LoadHardware(30, 31);
  }

  void service() override
  {
    Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 0, loadHardware1->Load());
    p = new Package(_package.getContent());
    NetworkService::getInstance().send(p);
  };

  void handle(Package *package) override {};

  void response(String data) override {};

  ~LoadService() {}
};
#endif // LoadService
