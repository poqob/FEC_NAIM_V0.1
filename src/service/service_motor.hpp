#ifndef MOTOR_SERVICE_HPP
#define MOTOR_SERVICE_HPP
#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "../model/hardware/hardware_motor.hpp"

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
  MotorService() : CommService(1, 1) // constant
  {
    GatewayService::getInstance().subscribeService(this);
    motorHardware1 = new MotorHardware(10, 11, 12, 13, firstThreeInt); // pin tanimi şimdilik rastgele sırasıyla R_EN, RPWM, L_EN, LPWM, verilen hız değeri 3 karakter olmaz zorunda
    motorHardware2 = new MotorHardware(14, 15, 16, 17, lastThreeInt);
  }

  void service() override{};

  void handle(Package *package) override
  {

    void processAndPrintData(const std::string &data)
    {
      if (data.length() == 6)
      {
        std::string firstThree = data.substr(0, 3);
        std::string lastThree = data.substr(3, 3);
        int firstThreeInt = std::stoi(firstThree);
        int lastThreeInt = std::stoi(lastThree);
      }
      receivedPackage = package;
      std::string data = receivedPackage->getData();
      processAndPrintData(data);
    }
  };

  void response(String data) override {};

  ~MotorService() {}
};
#endif // MotorService
