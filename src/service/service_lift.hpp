#ifndef LIFT_SERVICE_HPP
#define LIFT_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "../model/hardware/hardware_lift.hpp"

/*
 * @author: Haktan Serdar Genç
 * @date: 27.08.24
 * @file: lift service.
 */

class LiftService : public CommService
{

private:
    Package *p;
    Device *device = Global::getInstance().device;

    LiftHardware *liftHardware1;

public:
    LiftService() : CommService(1, 6)
    {
        GatewayService::getInstance().subscribeService(this);
        liftHardware1 = new LiftHardware(20, 21, 22, 23, lift_status);
    }

    void service() override
    {
        Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 0, liftHardware->read());
        p = new Package(_package.getContent());
        NetworkService::getInstance().send(p);
    };

    void handle(Package *package) override
    {
        int lift_status = receivedPackage->getData();
    };

    void response(String data) override {};

    ~LiftService() {}
};
#endif // LiftService
