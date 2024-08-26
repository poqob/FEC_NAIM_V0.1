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
        led = new LedHardware(13);
    }

    DebugService(uint8_t group, uint8_t id, void (*cb)()) : CommService(group, id)
    {
        GatewayService::getInstance().subscribeService(this);
        led = new LedHardware(13);
        callbackFunc = cb; // TODO: implement callback function
    }

    // create package, send the package
    void service() override
    {
        int data = 0;
        String data0 = "haktan";
        data0.concat(data);

        Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, id, "datataa");
        p = new Package(_package.getContent());
        NetworkService::getInstance().send(p);
        delete p;
    };

    void handle(Package *package) override
    {
        if (package->fromService() == 1)
        {
            led->toggle();
            response("OK");
        }
        // String result = "debug(group:";
        // result.concat(this->group);
        // result.concat(", id:");
        // result.concat(this->id);
        // result.concat(") package(head:");
        // result.concat(package->getHead());
        // result.concat(" , data:");
        // result.concat(package->getData());
        // result.concat(")");
        // Serial.println(result);
    }; // Pure virtual function

    void response(String data) override
    {
        Package _package = Package::build(device->id, device->subnet, group, id, 3, 1, group, id, data);
        p = new Package(_package.getContent());
        NetworkService::getInstance().send(p);
        delete p;
    }; // Pure virtual function

    ~DebugService() {}
};
#endif // DebugService
