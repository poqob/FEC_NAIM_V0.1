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
  MotorService() : CommService(1, 3) // constant
  {
    GatewayService::getInstance().subscribeService(this);
    motorHardware1 = new MotorHardware(10, 11, 12, 13); // pin tanimi şimdilik rastgele sırasıyla R_EN, RPWM, L_EN, LPWM, verilen hız değeri 3 karakter olmaz zorunda
    motorHardware2 = new MotorHardware(14, 15, 16, 17);
  }

  void service() override {};

  void handle(Package *package) override
  {
    receivedPackage = package;
    String data = receivedPackage->getData();
    int firstThreeInt = 0;
    int lastThreeInt = 0;

    String firstThree = data.substring(0, 3);
    String lastThree = data.substring(3, 3);
    firstThreeInt = int(firstThreeInt);
    lastThreeInt = int(lastThreeInt);

    motorHardware1->motor(firstThreeInt);
    motorHardware2->motor(lastThreeInt);
  }

  void response(String data) override {};

  ~MotorService() {}
};
#endif // MotorService
