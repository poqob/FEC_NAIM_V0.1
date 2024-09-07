#ifndef MOTOR_SERVICE_HPP
#define MOTOR_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "../model/hardware/hardware_motor.hpp"
#include "WString.h"

/*
 * @author: Haktan Serdar Genç
 * @date: 27.08.24
 * @file: motor service.
 */

class MotorService : public CommService
{

private: // constant
  Package *p;
  Device *device = Global::getInstance().device;

  MotorHardware *motorHardware1;
  MotorHardware *motorHardware2;

public:
  MotorService() : CommService(2, 2) // constant
  {
    GatewayService::getInstance().subscribeService(this);
    motorHardware1 = new MotorHardware(10, 11, 12, 13); // pin tanimi şimdilik rastgele sırasıyla R_EN, RPWM, L_EN, LPWM, verilen hız değeri 3 karakter olmaz zorunda
    motorHardware2 = new MotorHardware(14, 15, 16, 17);
  }

  void service() override {
    // sendDumpData();
  };

  // data: direction(+,-) and velocity(0-255)
  // +200-100
  void handle(Package *package) override
  {
    receivedPackage = package;
    String data = receivedPackage->getData();
    int firstThreeInt = 0;
    int lastThreeInt = 0;

    String firstThree = data.substring(1, 4);
    String lastThree = data.substring(5, 8);

    firstThreeInt = firstThree.toInt();
    lastThreeInt = lastThree.toInt();

    if (data[0] == '-')
      firstThreeInt *= -1;
    if (data[4] == '-')
      lastThreeInt *= -1;
    ////////////////////////////////////////
    Serial.print(firstThreeInt);
    Serial.print(" ");
    Serial.println(lastThreeInt);
    ////////////////////////////////////////

    motorHardware1->motor(firstThreeInt);
    motorHardware2->motor(lastThreeInt);
  }

  void response(String data) override
  {
    Package _package = Package::build(device->id, device->subnet, group, id, receivedPackage->from(), receivedPackage->fromService(), group, id, data);
    p = new Package(_package.getContent());
    // NetworkService::getInstance().send(p);
    Serial.println(p->getData());
    delete p;
  }; // Pure virtual function

  void sendDumpData()
  {
    String virtualData = "255;255";
    Package _package0 = Package::build(device->id, device->subnet, group, id, 2, 2, group, id, virtualData);
    NetworkService::getInstance().send(p);
    delete p;
  }

  ~MotorService() {}
};
#endif // MotorService
