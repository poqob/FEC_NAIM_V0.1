#ifndef QTR_SERVICE_HPP
#define QTR_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "../model/hardware/hardware_qtr.hpp"

/*
 * @author: Haktan Serdar Genç
 * @date: 27.08.24
 * @file: qtr service.
*/

class LoadService : public CommService
{

private: // constant
  Package *p;
  Device *device = Global::getInstance().device;

  QtrHardware *qtrHardware1;

public:
  LoadService() : CommService(1, 7) // constant
  {
    GatewayService::getInstance().subscribeService(this);
    qtrHardware1 = new QtrHardware(A1, A2, A3, A4, A5, A6, A7, A8)
  }

  void service() override
  {
    Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 0, LoadHardware1->read());
    p = new Package(_package.getContent());
    NetworkService::getInstance().send(p);
  };

  void handle(Package *package) override{};
  

  void response(String data) override {};

  ~LoadService() {}
};
#endif // LoadService
