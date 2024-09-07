#ifndef EXAMPLE_SERVICE_HPP
#define EXAMPLE_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "../model/hardware/hardware_led.hpp"
#include "HardwareSerial.h"

/*
 * @author: Mustafa BICER
 * @date: 24.08.24
 * @file: service_example.hpp
 * @description: This is an example debug service. It sends and handles receiving packages.
 */

class DebugService : public CommService
{

private:
    Package *p;
    Device *device = Global::getInstance().device;
    LedHardware *led;

    void (*callbackFunc)();

public:
    DebugService(uint8_t group, uint8_t id) : CommService(group, id)
    {
        GatewayService::getInstance().subscribeService(this);
        // led = new LedHardware(13);
    }

    DebugService(uint8_t group, uint8_t id, void (*cb)()) : CommService(group, id)
    {
        GatewayService::getInstance().subscribeService(this);
        // led = new LedHardware(13);
        callbackFunc = cb; // TODO: implement callback function
    }

    // create package, send the package
    void service() override {
        // Package _package = Package::build(device->id, device->subnet, group, id, 5, 2, 1, 1, "+220-110");
        // p = new Package(_package.getContent());
        // NetworkService::getInstance().send(p);
        // delete p;
    };

    void handle(Package *package) override
    {
        if (package->from() == 2)
        {
            Serial.println(package->getData());
        }
    }; // Pure virtual function

    void response(String data) override
    {
        Package _package = Package::build(device->id, device->subnet, group, id, 2, 1, group, id, data);
        p = new Package(_package.getContent());
        NetworkService::getInstance().send(p);
        delete p;
    }; // Pure virtual function

    ~DebugService() {}
};
#endif // DebugService
