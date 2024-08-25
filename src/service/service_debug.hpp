#ifndef EXAMPLE_SERVICE_HPP
#define EXAMPLE_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
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

public:
    DebugService() : CommService(1, 0)
    {
        GatewayService::getInstance().subscribeService(this);
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
    };

    void handle(Package *package) override
    {
        Serial.println(package->getContent());
    }; // Pure virtual function

    void response(String data) override {
    }; // Pure virtual function

    ~DebugService() {}
};
#endif // DebugService
