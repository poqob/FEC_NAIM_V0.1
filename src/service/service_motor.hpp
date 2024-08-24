#ifndef MOTOR_SERVICE_HPP
#define MOTOR_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "hardware/hardware_motor.hpp"

/*
 * @author: Mustafa BICER
 * @date: 24.08.24
 * @file: motor service.
 * @description: This is an example service for motor. A service that transmits data to motor.
 */

class MotorService : public CommService
{

private: // constant
  Package *p;
  Device *device = Global::getInstance().device;

  MotorHardware *motorHardware;
  MotorHardware *motorHardware1;
  MotorHardware motor;

public:
  MotorService() : CommService(1, 1) // constant
  {
    GatewayService::getInstance().subscribeService(this);
    motorHardware = new MotorHardware("1"); // pin tanimi
    motorHardware1 = new MotorHardware("2");
  }

  void service() override
  {
    Package _package = Package::build(device->id, device->subnet, group, id, device->id, device->subnet, group, 0, motorHardware1->read());
    p = new Package(_package.getContent());
    NetworkService::getInstance().send(p);
  };

  void handle(Package *package) override
  {
    receivedPackage = package;
    Serial.println(receivedPackage->getData());
  };

  void response(String data) override {};

  ~MotorService() {}
};
#endif // MotorService
