#ifndef QTR_SERVICE_HPP
#define QTR_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "../model/hardware/hardware_qtr.hpp"

/*
 * @author: Haktan Serdar Genç
 * @date: 27.08.24
 * @file: qtr service.
 */

class ServiceQtr : public CommService
{

private: // constant
  Package *p;
  Device *device = Global::getInstance().device;

  QtrHardware *qtrHardware1;

public:
  ServiceQtr(uint8_t group, uint8_t id) : CommService(group, id)
  {
    GatewayService::getInstance().subscribeService(this);
    // qtrHardware1 = new QtrHardware(); # TODO : problem on this line it broke the code
  }

  void service() override
  {
    // Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 0, qtrHardware1->qtr());
    // p = new Package(_package.getContent());
    // NetworkService::getInstance().send(p);
    sendDumpData();
  }

  void handle(Package *package) override {}

  void response(String data) override {}

  void sendDumpData()
  {
    String virtualData = "00110011";
    Package _package0 = Package::build(device->id, device->subnet, group, id, 2, 2, group, id, virtualData);
    p = new Package(_package0.getContent());
    NetworkService::getInstance().send(p);
    delete p;
  }

  ~ServiceQtr() {}
};
#endif // ServiceQtr
