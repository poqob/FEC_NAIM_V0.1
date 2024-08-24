#ifndef EXAMPLE_SERVICE_HPP
#define EXAMPLE_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"

/*
 * @author: Mustafa BICER
 * @date: 24.08.24
 * @file: example service.
 * @description: This is an example service. Transmits data to motor.
 */

class ExampleService : public CommService
{

private: // constant
    Package *p;
    Device *device = Global::getInstance().device;

private:
    // special methods
    void pi2motor()
    {
        String gelenveri = receivedPackage->getData();
        Serial.println(gelenveri);
    }

public:
    ExampleService() : CommService(1, 0) // constant
    {
        GatewayService::getInstance().subscribeService(this);
    }

    // constant methods, only change the data and handle method.
    void service() override
    {
        String data = "255;159;1;1";
        Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 1, data);
        p = new Package(_package.getContent());
        NetworkService::getInstance().send(p);
    };

    void handle(Package *package) override
    {
        receivedPackage = package;
        pi2motor();
        response("OK");
    };

    void response(String data) override
    {
        Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 1, data);
        p = new Package(_package.getContent());
        NetworkService::getInstance().send(p);
    };

    ~ExampleService() {}
};
#endif // ExampleService
