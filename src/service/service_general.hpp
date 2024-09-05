#ifndef LIFT_SERVICE_HPP
#define LIFT_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"

#include "../../src/model/hardware/hardware_buzzer.hpp"
#include "../../src/model/hardware/hardware_led.hpp"

/*
Service map:
0:toggle_alarm
1:off_alarm
2:on_alarm


*/

class GeneralService : public CommService
{

private:
    Package *p;
    Device *device = Global::getInstance().device;
    BuzzerHardware *buzzer;
    LedHardware *led;

public:
    // TODO: Hardware pin setup
    GeneralService(uint8_t group, uint8_t id) : CommService(group, id)
    {
        GatewayService::getInstance().subscribeService(this);
        buzzer = new BuzzerHardware(5);
        led = new LedHardware(3);
    }

    void service() override
    {
        sendDumpData(); // ACTUALLY NO NEED TO BROADCAST ANY PACKAGE.
    };

    void handle(Package *package) override
    {
        String data = receivedPackage->getData();
        data = data[0];
        if (data == "0")
            toggle_alarm();
        if (data == "1")
            off_alarm();
        if (data == "2")
            on_alarm();
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

    ~GeneralService() {}

private:
    void alarm()
    {
        String virtualData = "0";
        Package _package0 = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, id, virtualData);
        p = new Package(_package0.getContent());
        NetworkService::getInstance().send(p);
        delete p;
    }

    void toggle_alarm()
    {
        this->buzzer->toggle();
        // this->led->toggle();
    }

    void off_alarm()
    {
        this->buzzer->off();
        // this->led->off();
    }

    void on_alarm()
    {
        this->buzzer->on();
        // this->led->on();
    }
};
#endif // GeneralService
