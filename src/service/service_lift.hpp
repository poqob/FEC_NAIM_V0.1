#ifndef LIFT_SERVICE_HPP
#define LIFT_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service_network.hpp"
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
    LiftService(uint8_t group, uint8_t id) : CommService(group, id)
    {
        GatewayService::getInstance().subscribeService(this);
        liftHardware1 = new LiftHardware(20, 21, 22, 23);
    }

    void service() override {
        // only receives on of packages.
    };

    void handle(Package *package) override
    {
        receivedPackage = package;
        String data = receivedPackage->getData();
        data = data[0];
        if (data == "1")
        {
            liftHardware1->lift(true);
            Serial.println("Lift opened.");
        }
        else
        {

            liftHardware1->lift(false);
            Serial.println("Lift closed.");
        }
    };

    void response(String data) override {}

    void sendDumpData()
    {
        String virtualData = "1";
        Package _package0 = Package::build(device->id, device->subnet, group, id, 2, 2, group, id, virtualData);
        p = new Package(_package0.getContent());
        NetworkService::getInstance().send(p);
        delete p;
    }

    ~LiftService() {}
};
#endif // LiftService
